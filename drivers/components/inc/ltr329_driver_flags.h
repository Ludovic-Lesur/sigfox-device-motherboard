/*
 * ltr329_driver_flags.h
 *
 *  Created on: 11 may. 2026
 *      Author: Ludo
 */

#ifndef __LTR329_DRIVER_FLAGS_H__
#define __LTR329_DRIVER_FLAGS_H__

#include "i2c.h"
#include "lptim.h"

/*** LTR329 driver compilation flags ***/

#define LTR329_DRIVER_I2C_ERROR_BASE_LAST       I2C_ERROR_BASE_LAST
#define LTR329_DRIVER_DELAY_ERROR_BASE_LAST     LPTIM_ERROR_BASE_LAST

#endif /* __LTR329_DRIVER_FLAGS_H__ */
