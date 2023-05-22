/*
 * STM32F4xx_Device_Header.h
 *
 *  Created on: May 10, 2023
 *      Author: ahmed
 */

#ifndef STM32F4XX_DEVICE_HEADER_H_
#define STM32F4XX_DEVICE_HEADER_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STD_TYPES.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
//-----------------------------
//Base addresses for Memories
//-----------------------------

#define FLASH_MEMORY_BASE 				0x08000000UL
#define	SYSTEM_MEMORY_BASE				0x1FFFF000UL

#define	SRAM_BASE						0x20000000UL
#define PERIPHERALS_BASE 				0x40000000UL
#define CORTEX_M4_PERIPHERALS_BASE 		0xE000E010UL
//------------------------------------
//Base addresses for Core Peripherals
//------------------------------------
#define SYSTICK_BASE					(CORTEX_M4_PERIPHERALS_BASE+0x00000000UL)

//------------------------------------
//Base addresses for APB1 Peripherals
//------------------------------------

//------------------------------------
//Base addresses for ABP2 Peripherals
//------------------------------------

//-----------------------------------
//Base addresses for AHB1 Peripherals
//-----------------------------------
#define RCC_BASE					(PERIPHERALS_BASE+0x00023800UL)

#define GPIOA_BASE					(PERIPHERALS_BASE+0x00020000UL)
#define GPIOB_BASE					(PERIPHERALS_BASE+0x00020400UL)
#define GPIOC_BASE					(PERIPHERALS_BASE+0x00020800UL)
#define GPIOD_BASE					(PERIPHERALS_BASE+0x00020C00UL)
#define GPIOE_BASE					(PERIPHERALS_BASE+0x00021000UL)
#define GPIOH_BASE					(PERIPHERALS_BASE+0x00021C00UL)

//-----------------------------------
//Base addresses for AHB2 Peripherals
//-----------------------------------
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum
{
	GPIOA_EN,
	GPIOB_EN,
	GPIOC_EN,
}GPIO_Select_t;

typedef enum {
	APB1_BUS,
	APB2_BUS,
	AHB1_BUS,
	AHB2_BUS
}SysBus_t;

typedef enum {
	HSI_CLOCK,
	HSE_CLOCK,
	PLL_CLOCK
}SysClk_t;

typedef enum
{
	RC_CLOCK,
	CRYSTAL_CLOCK,
}ClkType_t;

typedef enum{
SYSCLK_NOT_DIVIDE = 0000,
SYSCLK_PRESCALER_BY2 = 1000,
SYSCLK_PRESCALER_BY4 = 1001,
SYSCLK_PRESCALER_BY8 = 1010,
SYSCLK_PRESCALER_BY16 = 1011,
SYSCLK_PRESCALER_BY64 = 1100,
SYSCLK_PRESCALER_BY128 = 1101,
SYSCLK_PRESCALER_BY256  = 1110,
SYSCLK_PRESCALER_BY512 = 1111
}SysClk_Prescaler_t;

typedef enum
{
	PIN_RESET		=		0,
  	PIN_SET			=		1,
}Pin_State_t;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/



#endif /* STM32F4XX__PRIVATE_H_ */
