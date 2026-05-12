/*
 * error.h
 *
 *  Created on: 11 may. 2026
 *      Author: Ludo
 */

#ifndef __ERROR_BASE_H__
#define __ERROR_BASE_H__

// Peripherals.
#include "iwdg.h"
#include "lptim.h"
#include "nvm.h"
#include "rcc.h"
#include "rtc.h"
#include "tim.h"
// Utils.
#include "error.h"
#include "maths.h"
#include "terminal.h"
// Components.
#include "aht2x.h"
#include "lis2dh12.h"
#include "ltr329.h"
#include "s2lp.h"
// Middleware.
#include "analog.h"
#include "cli.h"
#include "power.h"
// Sigfox.
#include "sigfox_error.h"

/*** ERROR BASE structures ***/

/*!******************************************************************
 * \enum ERROR_base_t
 * \brief Board error bases.
 *******************************************************************/
typedef enum {
    SUCCESS = 0,
    // Peripherals.
    ERROR_BASE_IWDG = ERROR_BASE_STEP,
    ERROR_BASE_LPTIM = (ERROR_BASE_IWDG + IWDG_ERROR_BASE_LAST),
    ERROR_BASE_NVM = (ERROR_BASE_LPTIM + LPTIM_ERROR_BASE_LAST),
    ERROR_BASE_RCC = (ERROR_BASE_NVM + NVM_ERROR_BASE_LAST),
    ERROR_BASE_RTC = (ERROR_BASE_RCC + RCC_ERROR_BASE_LAST),
    ERROR_BASE_TIM_MCU_API = (ERROR_BASE_RTC + RTC_ERROR_BASE_LAST),
    ERROR_BASE_TIM_RF_API = (ERROR_BASE_TIM_MCU_API + TIM_ERROR_BASE_LAST),
    // Utils.
    ERROR_BASE_MATH = (ERROR_BASE_TIM_RF_API + TIM_ERROR_BASE_LAST),
    ERROR_BASE_TERMINAL_AT = (ERROR_BASE_MATH + MATH_ERROR_BASE_LAST),
    // Components.
    ERROR_BASE_AHT20 = (ERROR_BASE_TERMINAL_AT + TERMINAL_ERROR_BASE_LAST),
    ERROR_BASE_LIS2DH12 = (ERROR_BASE_AHT20 + TERMINAL_ERROR_BASE_LAST),
    ERROR_BASE_LTR329 = (ERROR_BASE_LIS2DH12 + LIS2DH12_ERROR_BASE_LAST),
    ERROR_BASE_S2LP = (ERROR_BASE_LTR329 + LTR329_ERROR_BASE_LAST),
    // Middleware.
    ERROR_BASE_ANALOG = (ERROR_BASE_S2LP + S2LP_ERROR_BASE_LAST),
    ERROR_BASE_CLI = (ERROR_BASE_ANALOG + ANALOG_ERROR_BASE_LAST),
    ERROR_BASE_POWER = (ERROR_BASE_CLI + CLI_ERROR_BASE_LAST),
    ERROR_BASE_SIGFOX_EP_LIB = (ERROR_BASE_POWER + POWER_ERROR_BASE_LAST),
    ERROR_BASE_SIGFOX_EP_ADDON_RFP = (ERROR_BASE_SIGFOX_EP_LIB + (SIGFOX_ERROR_SOURCE_LAST * ERROR_BASE_STEP)),
    ERROR_BASE_SIGFOX_EP_ADDON_WIFI = (ERROR_BASE_SIGFOX_EP_ADDON_RFP + ERROR_BASE_STEP),
    // Last base value.
    ERROR_BASE_LAST = (ERROR_BASE_SIGFOX_EP_ADDON_WIFI + ERROR_BASE_STEP)
} ERROR_base_t;

#endif /* __ERROR_BASE_H__ */
