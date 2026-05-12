/*
 * ltr329_hw.c
 *
 *  Created on: 11 may. 2026
 *      Author: Ludo
 */

#include "ltr329_hw.h"

#ifndef LTR329_DRIVER_DISABLE_FLAGS_FILE
#include "ltr329_driver_flags.h"
#endif
#include "error_base.h"
#include "sensors_hw.h"
#include "ltr329.h"
#include "types.h"

#ifndef LTR329_DRIVER_DISABLE

/*** LTR329 HW functions ***/

/*******************************************************************/
LTR329_status_t LTR329_HW_init(void) {
    return ((LTR329_status_t) SENSORS_HW_init(LTR329_ERROR_BASE_I2C));
}

/*******************************************************************/
LTR329_status_t LTR329_HW_de_init(void) {
    return ((LTR329_status_t) SENSORS_HW_de_init(ERROR_BASE_AHT20 + LTR329_ERROR_BASE_I2C));
}

/*******************************************************************/
LTR329_status_t LTR329_HW_i2c_write(uint8_t i2c_address, uint8_t* data, uint8_t data_size_bytes, uint8_t stop_flag) {
    return ((LTR329_status_t) SENSORS_HW_i2c_write(LTR329_ERROR_BASE_I2C, i2c_address, data, data_size_bytes, stop_flag));
}

/*******************************************************************/
LTR329_status_t LTR329_HW_i2c_read(uint8_t i2c_address, uint8_t* data, uint8_t data_size_bytes) {
    return ((LTR329_status_t) SENSORS_HW_i2c_read(LTR329_ERROR_BASE_I2C, i2c_address, data, data_size_bytes));
}

/*******************************************************************/
LTR329_status_t LTR329_HW_delay_milliseconds(uint32_t delay_ms) {
    return ((LTR329_status_t) SENSORS_HW_delay_milliseconds(LTR329_ERROR_BASE_DELAY, delay_ms));
}

#endif /* LTR329_DRIVER_DISABLE */
