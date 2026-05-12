/*
 * aht2x_hw.c
 *
 *  Created on: 11 may. 2026
 *      Author: Ludo
 */

#include "aht2x_hw.h"

#ifndef AHT2X_DRIVER_DISABLE_FLAGS_FILE
#include "aht2x_driver_flags.h"
#endif
#include "error_base.h"
#include "sensors_hw.h"
#include "aht2x.h"
#include "types.h"

#ifndef AHT2X_DRIVER_DISABLE

/*** AHT2X HW functions ***/

/*******************************************************************/
AHT2X_status_t AHT2X_HW_init(void) {
    return ((AHT2X_status_t) SENSORS_HW_init(AHT2X_ERROR_BASE_I2C));
}

/*******************************************************************/
AHT2X_status_t AHT2X_HW_de_init(void) {
    return ((AHT2X_status_t) SENSORS_HW_de_init(ERROR_BASE_AHT20 + AHT2X_ERROR_BASE_I2C));
}

/*******************************************************************/
AHT2X_status_t AHT2X_HW_i2c_write(uint8_t i2c_address, uint8_t* data, uint8_t data_size_bytes, uint8_t stop_flag) {
    return ((AHT2X_status_t) SENSORS_HW_i2c_write(AHT2X_ERROR_BASE_I2C, i2c_address, data, data_size_bytes, stop_flag));
}

/*******************************************************************/
AHT2X_status_t AHT2X_HW_i2c_read(uint8_t i2c_address, uint8_t* data, uint8_t data_size_bytes) {
    return ((AHT2X_status_t) SENSORS_HW_i2c_read(AHT2X_ERROR_BASE_I2C, i2c_address, data, data_size_bytes));
}

/*******************************************************************/
AHT2X_status_t AHT2X_HW_delay_milliseconds(uint32_t delay_ms) {
    return ((AHT2X_status_t) SENSORS_HW_delay_milliseconds(AHT2X_ERROR_BASE_DELAY, delay_ms));
}

#endif /* AHT2X_DRIVER_DISABLE */
