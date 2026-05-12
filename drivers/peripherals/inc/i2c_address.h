/*
 * i2c_address.h
 *
 *  Created on: 11 may. 2026
 *      Author: Ludo
 */

#ifndef __I2C_ADDRESS_H__
#define __I2C_ADDRESS_H__

/*!******************************************************************
 * \enum I2C_address_mapping_t
 * \brief I2C slaves address mapping.
 *******************************************************************/
typedef enum {
    I2C_ADDRESS_AHT20 = 0x70,
    I2C_ADDRESS_LIS2DH12 = 0x32,
    I2C_ADDRESS_LTR329 = 0x52
} I2C_address_mapping_t;

#endif /* __I2C_ADDRESS_H__ */
