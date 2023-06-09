/*
 * MCAL_RCC_Config.c
 *
 *  Created on: May 10, 2023
 *      Author: ahmed
 */

#ifndef MCAL_RCC_CONFIG_C_
#define MCAL_RCC_CONFIG_C_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STM32F4xx_Device_Header.h"
#include "MCAL_RCC_Interface.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  CONFIGURATIONS ASSIGNMENT
 *********************************************************************************************************************/
RCC_Cfg_t RCC_GPIO_Config = {
		.System_ClkSelection = HSI_CLOCK,
		.System_ClkFreq = 25000000,
		.System_ClkPrescaler = SYSCLK_NOT_DIVIDE,
		.System_ClkType = RC_CLOCK,
};

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


#endif /* MCAL_RCC_CONFIG_C_ */
