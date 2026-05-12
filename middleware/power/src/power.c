/*
 * power.c
 *
 *  Created on: 11 may. 2026
 *      Author: Ludo
 */

#include "power.h"

#include "aht2x.h"
#include "analog.h"
#include "error.h"
#include "error_base.h"
#include "gpio.h"
#include "i2c_address.h"
#include "lis2dh12.h"
#include "lptim.h"
#include "ltr329.h"
#include "mcu_mapping.h"
#include "s2lp.h"
#include "types.h"

/*** POWER local global variables ***/

static uint32_t power_domain_state[POWER_DOMAIN_LAST] = { [0 ... (POWER_DOMAIN_LAST - 1)] = 0 };

/*** POWER local functions ***/

/*******************************************************************/
#define _POWER_stack_driver_error(driver_status, driver_success, driver_error_base, power_status) { \
    if (driver_status != driver_success) { \
        ERROR_stack_add(driver_error_base + driver_status); \
        ERROR_stack_add(ERROR_BASE_POWER + power_status); \
    } \
}

/*** POWER functions ***/

/*******************************************************************/
void POWER_init(void) {
    // Local variables.
    uint8_t idx = 0;
    // Init context.
    for (idx = 0; idx < POWER_DOMAIN_LAST; idx++) {
        power_domain_state[idx] = 0;
    }
    // Init power control pins.
    GPIO_configure(&GPIO_ADC_POWER_ENABLE, GPIO_MODE_OUTPUT, GPIO_TYPE_PUSH_PULL, GPIO_SPEED_LOW, GPIO_PULL_NONE);
    GPIO_configure(&GPIO_SENSORS_POWER_ENABLE, GPIO_MODE_OUTPUT, GPIO_TYPE_PUSH_PULL, GPIO_SPEED_LOW, GPIO_PULL_NONE);
    GPIO_configure(&GPIO_EXTERNAL_POWER_ENABLE, GPIO_MODE_OUTPUT, GPIO_TYPE_PUSH_PULL, GPIO_SPEED_LOW, GPIO_PULL_NONE);
}

/*******************************************************************/
void POWER_enable(POWER_requester_id_t requester_id, POWER_domain_t domain, LPTIM_delay_mode_t delay_mode) {
    // Local variables.
    ANALOG_status_t analog_status = ANALOG_SUCCESS;
    LPTIM_status_t lptim_status = LPTIM_SUCCESS;
    LTR329_status_t ltr329_status = LTR329_SUCCESS;
    AHT2X_status_t aht2x_status = AHT2X_SUCCESS;
    LIS2DH12_status_t lis2dh12_status = LIS2DH12_SUCCESS;
    S2LP_status_t s2lp_status = S2LP_SUCCESS;
    uint32_t delay_ms = 0;
    uint8_t action_required = 0;
    // Check parameters.
    if (requester_id >= POWER_REQUESTER_ID_LAST) {
        ERROR_stack_add(ERROR_BASE_POWER + POWER_ERROR_REQUESTER_ID);
        goto errors;
    }
    if (domain >= POWER_DOMAIN_LAST) {
        ERROR_stack_add(ERROR_BASE_POWER + POWER_ERROR_DOMAIN);
        goto errors;
    }
    action_required = ((power_domain_state[domain] == 0) ? 1 : 0);
    // Update state.
    power_domain_state[domain] |= (0b1 << requester_id);
    // Directly exit if this is not the first request.
    if (action_required == 0) goto errors;
    // Check domain.
    switch (domain) {
    case POWER_DOMAIN_ANALOG:
        // Turn analog front-end on.
        GPIO_write(&GPIO_ADC_POWER_ENABLE, 1);
        delay_ms = POWER_ON_DELAY_MS_ANALOG;
        // Init attached drivers.
        analog_status = ANALOG_init();
        _POWER_stack_driver_error(analog_status, ANALOG_SUCCESS, ERROR_BASE_ANALOG, POWER_ERROR_DRIVER_ANALOG);
        break;
    case POWER_DOMAIN_SENSORS:
        // Turn digital sensors.
        GPIO_write(&GPIO_SENSORS_POWER_ENABLE, 1);
        delay_ms = POWER_ON_DELAY_MS_SENSORS;
        // Init attached drivers.
        aht2x_status = AHT2X_init(I2C_ADDRESS_AHT20);
        _POWER_stack_driver_error(aht2x_status, AHT2X_SUCCESS, ERROR_BASE_AHT20, POWER_ERROR_DRIVER_AHT20);
        lis2dh12_status = LIS2DH12_init();
        _POWER_stack_driver_error(lis2dh12_status, LIS2DH12_SUCCESS, ERROR_BASE_LIS2DH12, POWER_ERROR_DRIVER_LIS2DH12);
        ltr329_status = LTR329_init();
        _POWER_stack_driver_error(ltr329_status, LTR329_SUCCESS, ERROR_BASE_LTR329, POWER_ERROR_DRIVER_LTR329);
        break;
    case POWER_DOMAIN_RADIO:
        // Init attached drivers.
        s2lp_status = S2LP_init();
        _POWER_stack_driver_error(s2lp_status, S2LP_SUCCESS, ERROR_BASE_S2LP, POWER_ERROR_DRIVER_S2LP);
        break;
    case POWER_DOMAIN_EXTERNAL:
        // Turn external power on.
        GPIO_write(&GPIO_EXTERNAL_POWER_ENABLE, 1);
        delay_ms = POWER_ON_DELAY_MS_EXTERNAL;
        break;
    default:
        ERROR_stack_add(ERROR_BASE_POWER + POWER_ERROR_DOMAIN);
        goto errors;
    }
    // Power on delay.
    if (delay_ms != 0) {
        lptim_status = LPTIM_delay_milliseconds(delay_ms, delay_mode);
        _POWER_stack_driver_error(lptim_status, LPTIM_SUCCESS, ERROR_BASE_LPTIM, POWER_ERROR_DRIVER_LPTIM);
    }
errors:
    return;
}

/*******************************************************************/
void POWER_disable(POWER_requester_id_t requester_id, POWER_domain_t domain) {
    // Local variables.
    ANALOG_status_t analog_status = ANALOG_SUCCESS;
    AHT2X_status_t aht2x_status = AHT2X_SUCCESS;
    LIS2DH12_status_t lis2dh12_status = LIS2DH12_SUCCESS;
    LTR329_status_t ltr329_status = LTR329_SUCCESS;
    S2LP_status_t s2lp_status = S2LP_SUCCESS;
    // Check parameters.
    if (requester_id >= POWER_REQUESTER_ID_LAST) {
        ERROR_stack_add(ERROR_BASE_POWER + POWER_ERROR_REQUESTER_ID);
        goto errors;
    }
    if (domain >= POWER_DOMAIN_LAST) {
        ERROR_stack_add(ERROR_BASE_POWER + POWER_ERROR_DOMAIN);
        goto errors;
    }
    if (power_domain_state[domain] == 0) goto errors;
    // Update state.
    power_domain_state[domain] &= ~(0b1 << requester_id);
    // Directly exit if this is not the last request.
    if (power_domain_state[domain] != 0) goto errors;
    // Check domain.
    switch (domain) {
    case POWER_DOMAIN_ANALOG:
        // Release attached drivers.
        analog_status = ANALOG_de_init();
        _POWER_stack_driver_error(analog_status, ANALOG_SUCCESS, ERROR_BASE_ANALOG, POWER_ERROR_DRIVER_ANALOG);
        // Turn analog front-end off.
        GPIO_write(&GPIO_ADC_POWER_ENABLE, 0);
        break;
    case POWER_DOMAIN_SENSORS:
        // Release attached drivers.
        aht2x_status = AHT2X_de_init();
        _POWER_stack_driver_error(aht2x_status, AHT2X_SUCCESS, ERROR_BASE_AHT20, POWER_ERROR_DRIVER_AHT20);
        lis2dh12_status = LIS2DH12_de_init();
        _POWER_stack_driver_error(lis2dh12_status, LIS2DH12_SUCCESS, ERROR_BASE_LIS2DH12, POWER_ERROR_DRIVER_LIS2DH12);
        ltr329_status = LTR329_de_init();
        _POWER_stack_driver_error(ltr329_status, LTR329_SUCCESS, ERROR_BASE_LTR329, POWER_ERROR_DRIVER_LTR329);
        // Turn digital sensors off.
        GPIO_write(&GPIO_SENSORS_POWER_ENABLE, 0);
        break;
    case POWER_DOMAIN_RADIO:
        // Release attached drivers.
        s2lp_status = S2LP_de_init();
        _POWER_stack_driver_error(s2lp_status, S2LP_SUCCESS, ERROR_BASE_S2LP, POWER_ERROR_DRIVER_S2LP);
        break;
    case POWER_DOMAIN_EXTERNAL:
        // Turn external power off.
        GPIO_write(&GPIO_EXTERNAL_POWER_ENABLE, 0);
        break;
    default:
        ERROR_stack_add(ERROR_BASE_POWER + POWER_ERROR_DOMAIN);
        goto errors;
    }
errors:
    return;
}

/*******************************************************************/
uint8_t POWER_get_state(POWER_domain_t domain) {
    // Local variables.
    uint8_t state = 0;
    // Check parameters.
    if (domain >= POWER_DOMAIN_LAST) {
        ERROR_stack_add(ERROR_BASE_POWER + POWER_ERROR_DOMAIN);
        goto errors;
    }
    state = (power_domain_state[domain] == 0) ? 0 : 1;
errors:
    return state;
}
