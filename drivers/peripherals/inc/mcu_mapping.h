/*
 * mcu_mapping.h
 *
 *  Created on: 11 may. 2026
 *      Author: Ludo
 */

#ifndef __MCU_MAPPING_H__
#define __MCU_MAPPING_H__

#include "adc.h"
#include "gpio.h"
#include "i2c.h"
#include "lpuart.h"
#include "spi.h"
#include "usart.h"

/*** MCU MAPPING macros ***/

#define ADC_CHANNEL_SOURCE_VOLTAGE      ADC_CHANNEL_IN8
#define ADC_CHANNEL_STORAGE_VOLTAGE     ADC_CHANNEL_IN9

#define I2C_INSTANCE_SENSORS            I2C_INSTANCE_I2C1

#define SPI_INSTANCE_RADIO              SPI_INSTANCE_SPI1

#define TIM_INSTANCE_MCU_API            TIM_INSTANCE_TIM2

#define USART_INSTANCE_GPS              USART_INSTANCE_USART2
#define USART_INSTANCE_AT               USART_INSTANCE_USART1

#define GPIO_ACCELERO_IRQ               GPIO0

/*** MCU MAPPING structures ***/

/*!******************************************************************
 * \enum ADC_channel_index_t
 * \brief ADC channels index.
 *******************************************************************/
typedef enum {
    ADC_CHANNEL_INDEX_SOURCE_VOLTAGE = 0,
    ADC_CHANNEL_INDEX_STORAGE_VOLTAGE,
    ADC_CHANNEL_INDEX_LAST
} ADC_channel_index_t;

/*** MCU MAPPING global variables ***/

// GPIOs.
extern const GPIO_pin_t GPIO0;
extern const GPIO_pin_t GPIO1;
extern const GPIO_pin_t GPIO2;
extern const GPIO_pin_t GPIO3;
extern const GPIO_pin_t GPIO4;
extern const GPIO_pin_t GPIO5;
extern const GPIO_pin_t GPIO6;
extern const GPIO_pin_t GPIO7;
// Analog inputs.
extern const GPIO_pin_t GPIO_ADC_POWER_ENABLE;
extern const ADC_gpio_t ADC_GPIO;
// S2LP.
extern const SPI_gpio_t SPI_GPIO_S2LP;
extern const GPIO_pin_t GPIO_S2LP_CS;
extern const GPIO_pin_t GPIO_S2LP_GPIO0;
extern const GPIO_pin_t GPIO_S2LP_SDN;
// Sensors.
extern const GPIO_pin_t GPIO_SENSORS_POWER_ENABLE;
extern const I2C_gpio_t I2C_GPIO_SENSORS;
// External power supply.
extern const GPIO_pin_t GPIO_EXTERNAL_POWER_ENABLE;
// AT interface.
extern const USART_gpio_t USART_GPIO_AT;

#endif /* __MCU_MAPPING_H__ */
