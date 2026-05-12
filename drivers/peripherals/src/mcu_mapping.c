/*
 * gpio_mapping.c
 *
 *  Created on: 11 may. 2026
 *      Author: Ludo
 */

#include "mcu_mapping.h"

#include "gpio.h"
#include "gpio_registers.h"
#include "i2c.h"
#include "lpuart.h"
#include "spi.h"
#include "usart.h"

/*** GPIO MAPPING local global variables ***/

// Analog inputs.
static const GPIO_pin_t GPIO_ADC_SOURCE_VOLTAGE =  { GPIOB, 1, 0, 0 };
static const GPIO_pin_t GPIO_ADC_STORAGE_VOLTAGE = { GPIOB, 1, 1, 0 };
// Analog inputs list.
static const GPIO_pin_t* const GPIO_ADC_PINS_LIST[ADC_CHANNEL_INDEX_LAST] = {
    &GPIO_ADC_SOURCE_VOLTAGE,
    &GPIO_ADC_STORAGE_VOLTAGE
};
// I2C sensors.
static const GPIO_pin_t GPIO_I2C1_SCL = { GPIOB, 1, 6, 1 };
static const GPIO_pin_t GPIO_I2C1_SDA = { GPIOB, 1, 7, 1 };
// SPI radio.
static const GPIO_pin_t GPIO_SPI1_SCK =  { GPIOB, 1, 3, 0 };
static const GPIO_pin_t GPIO_SPI1_MISO = { GPIOB, 1, 4, 0 };
static const GPIO_pin_t GPIO_SPI1_MOSI = { GPIOB, 1, 5, 0 };
// USART AT.
static const GPIO_pin_t GPIO_USART1_TX = { GPIOA, 0, 9, 4 };
static const GPIO_pin_t GPIO_USART1_RX = { GPIOA, 0, 10, 4 };

/*** GPIO MAPPING global variables ***/

// GPIOs.
const GPIO_pin_t GPIO0 = { GPIOA, 0, 0, 0 };
const GPIO_pin_t GPIO1 = { GPIOA, 0, 1, 0 };
const GPIO_pin_t GPIO2 = { GPIOA, 0, 2, 0 };
const GPIO_pin_t GPIO3 = { GPIOA, 0, 3, 0 };
const GPIO_pin_t GPIO4 = { GPIOA, 0, 4, 0 };
const GPIO_pin_t GPIO5 = { GPIOA, 0, 5, 0 };
const GPIO_pin_t GPIO6 = { GPIOA, 0, 6, 0 };
const GPIO_pin_t GPIO7 = { GPIOA, 0, 7, 0 };
// Analog inputs.
const GPIO_pin_t GPIO_ADC_POWER_ENABLE = { GPIOB, 1, 2, 0 };
const ADC_gpio_t ADC_GPIO = { (const GPIO_pin_t**) &GPIO_ADC_PINS_LIST, ADC_CHANNEL_INDEX_LAST };
// S2LP.
const SPI_gpio_t SPI_GPIO_S2LP = { &GPIO_SPI1_SCK, &GPIO_SPI1_MOSI, &GPIO_SPI1_MISO };
const GPIO_pin_t GPIO_S2LP_CS = { GPIOA, 0, 15, 0 };
const GPIO_pin_t GPIO_S2LP_SDN = { GPIOA, 0, 11, 0 };
const GPIO_pin_t GPIO_S2LP_GPIO0 = { GPIOA, 0, 12, 0 };
// Sensors.
const GPIO_pin_t GPIO_SENSORS_POWER_ENABLE = { GPIOB, 1, 8, 0 };
const I2C_gpio_t I2C_GPIO_SENSORS = { &GPIO_I2C1_SCL, &GPIO_I2C1_SDA };
// External power supply.
const GPIO_pin_t GPIO_EXTERNAL_POWER_ENABLE = { GPIOA, 0, 8, 0 };
// AT interface.
const USART_gpio_t USART_GPIO_AT = { &GPIO_USART1_TX, &GPIO_USART1_RX };
