/*
 * aht2x_driver_flags.h
 *
 *  Created on: 11 may. 2026
 *      Author: Ludo
 */

#ifndef __AHT2X_DRIVER_FLAGS_H__
#define __AHT2X_DRIVER_FLAGS_H__

#include "i2c.h"
#include "lptim.h"

/*** AHT2x driver compilation flags ***/

#define AHT2X_DRIVER_I2C_ERROR_BASE_LAST    I2C_ERROR_BASE_LAST
#define AHT2X_DRIVER_DELAY_ERROR_BASE_LAST  LPTIM_ERROR_BASE_LAST

#endif /* __AHT2X_DRIVER_FLAGS_H__ */
