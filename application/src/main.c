/*
 * main.c
 *
 *  Created on: 12 may. 2026
 *      Author: Ludo
 */

// Peripherals.
#include "exti.h"
#include "gpio.h"
#include "i2c_address.h"
#include "iwdg.h"
#include "lptim.h"
#include "mcu_mapping.h"
#include "nvic.h"
#include "nvic_priority.h"
#include "pwr.h"
#include "rcc.h"
#include "rtc.h"
// Components.
#include "aht2x.h"
#include "lis2dh12.h"
#include "ltr329.h"
#include "sensors_hw.h"
// Utils.
#include "error.h"
#include "types.h"
// Middleware.
#include "analog.h"
#include "cli.h"
#include "power.h"
#include "sigfox_ep_api.h"
#include "sigfox_ep_frames.h"
#include "sigfox_types.h"
#include "sigfox_rc.h"
// Applicative.
#include "at.h"
#include "error_base.h"
#include "sdm_flags.h"
#include "version.h"

/*** MAIN macros ***/

/*** MAIN structures ***/

/*** MAIN global variables ***/

/*** MAIN functions ***/

/*******************************************************************/
static void _SDM_init_hw(void) {
    // Local variables.
    RCC_status_t rcc_status = RCC_SUCCESS;
    RTC_status_t rtc_status = RTC_SUCCESS;
    LPTIM_status_t lptim_status = LPTIM_SUCCESS;
#ifndef SDM_MODE_DEBUG
    IWDG_status_t iwdg_status = IWDG_SUCCESS;
#endif
    // Init error stack
    ERROR_stack_init();
    // Init memory.
    NVIC_init();
    // Init power module and clock tree.
    PWR_init();
    rcc_status = RCC_init(NVIC_PRIORITY_CLOCK);
    RCC_stack_error(ERROR_BASE_RCC);
    // Init GPIOs.
    GPIO_init();
    POWER_init();
    EXTI_init();
    // Start independent watchdog.
#ifndef SDM_MODE_DEBUG
    iwdg_status = IWDG_init();
    IWDG_stack_error(ERROR_BASE_IWDG);
    IWDG_reload();
#endif
    // High speed oscillator.
    rcc_status = RCC_switch_to_hsi();
    RCC_stack_error(ERROR_BASE_RCC);
    // Calibrate clocks.
    rcc_status = RCC_calibrate_internal_clocks(NVIC_PRIORITY_CLOCK_CALIBRATION);
    RCC_stack_error(ERROR_BASE_RCC);
    // Init RTC.
    rtc_status = RTC_init(NULL, NVIC_PRIORITY_RTC);
    RTC_stack_error(ERROR_BASE_RTC);
    // Init delay timer.
    lptim_status = LPTIM_init(NVIC_PRIORITY_DELAY);
    LPTIM_stack_error(ERROR_BASE_LPTIM);
}

#ifndef SDM_MODE_CLI
/*******************************************************************/
int main(void) {
    // Init board.
    _SDM_init_hw();
    // Main loop.
    while (1) {
        // Enter stop mode.
        IWDG_reload();
        PWR_enter_deepsleep_mode(PWR_DEEPSLEEP_MODE_STOP);
        IWDG_reload();
    }
    return 0;
}
#endif

#ifdef SDM_MODE_CLI
/*******************************************************************/
int main(void) {
    // Local variables.
    CLI_status_t cli_status = CLI_SUCCESS;
    // Init board.
    _SDM_init_hw();
    // Init command line interface.
    cli_status = CLI_init();
    CLI_stack_error(ERROR_BASE_CLI);
    // Main loop.
    while (1) {
        // Enter sleep mode.
        IWDG_reload();
        PWR_enter_sleep_mode(PWR_SLEEP_MODE_NORMAL);
        IWDG_reload();
        // Process command line interface.
        cli_status = CLI_process();
        CLI_stack_error(ERROR_BASE_CLI);
    }
    return 0;
}
#endif

