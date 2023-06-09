/*
 * STM32F4xx_STK_Interface.h
 *
 *  Created on: May 10, 2023
 *      Author: ahmed
 */

#ifndef MCAL_STK_INTERFACE_H_
#define MCAL_STK_INTERFACE_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STD_TYPES.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum {
	AHB_8_DIVIDE,
	CPU_CLOCK_AHB
}STK_ClkSrc_t;

typedef enum {
	DISABLE_EXCEPTION = 0,
	ENABLE_SINGLE_EXCEPTION  = 1,
	ENABLE_PERIODIC_EXCEPTION  = 2
}STK_ExceptionMode_t;
/**********************************************************************************************************************
 *  CONFIG STRUCTURES
 *********************************************************************************************************************/
typedef struct
{
	STK_ClkSrc_t			SysTick_ClkSrc;
	STK_ExceptionMode_t 	SysTick_Exception;
	void (*Systick_CallBackPtr)(void);
}STK_Cfg_t;

extern STK_Cfg_t STK_G_Config;
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

void MCL_STK_vInit(STK_Cfg_t* Copy_STK_Cfg);
void MCL_STK_vRestartTimer(void);
void MCL_STK_vSetBusyWait(u32 Copy_u32Ticks);
void MCL_STK_vSetIntervalSingle(u32 Copy_u32Ticks, void (*Copy_Ptr)(void));
void MCL_STK_vSetIntervalPeriodic(u32 Copy_u32Ticks, void (*Copy_Ptr)(void));
void MCL_STK_vStopInterval(void);
u32 MCL_STK_u32GetElapsed(void);
u32 MCL_STK_u32GetRemaining(void);

#endif /* MCAL_STK_INTERFACE_H_ */
