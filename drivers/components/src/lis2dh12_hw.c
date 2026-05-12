/*
 * lis2dh12_hw.c
 *
 *  Created on: 11 may. 2026
 *      Author: Ludo
 */

#include "lis2dh12_hw.h"

#ifndef LIS2DH12_DRIVER_DISABLE_FLAGS_FILE
#include "lis2dh12_driver_flags.h"
#endif
#include "error_base.h"
#include "lis2dh12.h"
#include "sensors_hw.h"
#include "types.h"

#ifndef LIS2DH12_DRIVER_DISABLE

/*** LIS2DH12 HW functions ***/

/*******************************************************************/
LIS2DH12_status_t LIS2DH12_HW_init(void) {
    return ((LIS2DH12_status_t) SENSORS_HW_init(LIS2DH12_ERROR_BASE_I2C));
}

/*******************************************************************/
LIS2DH12_status_t LIS2DH12_HW_de_init(void) {
    return ((LIS2DH12_status_t) SENSORS_HW_de_init(ERROR_BASE_LIS2DH12 + LIS2DH12_ERROR_BASE_I2C));
}

/*******************************************************************/
LIS2DH12_status_t LIS2DH12_HW_i2c_write(uint8_t i2c_address, uint8_t* data, uint8_t data_size_bytes, uint8_t stop_flag) {
    return ((LIS2DH12_status_t) SENSORS_HW_i2c_write(LIS2DH12_ERROR_BASE_I2C, i2c_address, data, data_size_bytes, stop_flag));
}

/*******************************************************************/
LIS2DH12_status_t LIS2DH12_HW_i2c_read(uint8_t i2c_address, uint8_t* data, uint8_t data_size_bytes) {
    return ((LIS2DH12_status_t) SENSORS_HW_i2c_read(LIS2DH12_ERROR_BASE_I2C, i2c_address, data, data_size_bytes));
}

#endif /* LIS2DH12_DRIVER_DISABLE */
