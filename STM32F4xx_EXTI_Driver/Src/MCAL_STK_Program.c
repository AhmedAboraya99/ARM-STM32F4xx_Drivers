/*
 * MCA_STK_Program.c
 *
 *  Created on: May 10, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STD_TYPES.h"
#include "MCAL_STK_Interface.h"
#include "MCAL_STK_Private.h"

#include "MCAL_STK_Config.c"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
void (*Global_STKCallBackPtr)(void) = NULL_PTR;

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  CONFIGURATIONS ASSIGNMENT
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
void MCL_STK_vInit(STK_Cfg_t* Copy_STK_Cfg)
{

	/* Disable SysTick */
	STK->STK_CTRL = 0;
	STK->STK_CTRL_Bits.CLKSOURCE = Copy_STK_Cfg->SysTick_ClkSrc;

	if (Copy_STK_Cfg->SysTick_Exception != DISABLE_EXCEPTION)
	{
		if(Copy_STK_Cfg->Systick_CallBackPtr != NULL_PTR)
			Global_STKCallBackPtr = Copy_STK_Cfg->Systick_CallBackPtr;

	}
		//STK->STK_CTRL_Bits.TICKINT = DISABLE_STATE;

}
void MCL_STK_vSetBusyWait(u32 Copy_u32Ticks)
{

	STK->STK_LOAD = (Copy_u32Ticks*1000)- 1UL; 	//Tick = 1ms

	STK->STK_CTRL_Bits.ENABLE = ENABLE_STATE;

	while (STK->STK_CTRL_Bits.COUNTFLAG != 1);


	STK->STK_CTRL_Bits.ENABLE = DISABLE_STATE;

	STK->STK_LOAD = 0;
	STK->STK_VAL = 0;
}
void MCL_STK_vSetIntervalSingle(u32 Copy_u32Ticks, void (*Copy_Ptr)(void))
{

	STK->STK_LOAD = Copy_u32Ticks - 1UL;
	STK->STK_VAL = 0;
	STK->STK_CTRL_Bits.TICKINT = ENABLE_STATE;

	if (Copy_Ptr != NULL_PTR)
		Global_STKCallBackPtr = Copy_Ptr;

	 // Enable SysTick timer
	STK->STK_CTRL_Bits.ENABLE = ENABLE_STATE;

}
void MCL_STK_vSetIntervalPeriodic(u32 Copy_u32Ticks, void (*Copy_Ptr)(void))
{
	STK->STK_LOAD = Copy_u32Ticks - 1UL;

	STK->STK_CTRL_Bits.TICKINT = ENABLE_STATE;

	if (Copy_Ptr != NULL_PTR)
		Global_STKCallBackPtr = Copy_Ptr;

	 // Enable SysTick timer
	STK->STK_CTRL_Bits.ENABLE = ENABLE_STATE;
}
void MCL_STK_vStopInterval(void)
{

	STK->STK_LOAD = 0;
	STK->STK_CTRL_Bits.ENABLE = DISABLE_STATE;
	STK->STK_CTRL_Bits.TICKINT = DISABLE_EXCEPTION;
}


u32 MCL_STK_u32GetElapsed(void)
{
	u32 Copy_u32Ticks;

    Copy_u32Ticks = STK->STK_LOAD - STK->STK_VAL;

    return Copy_u32Ticks;
}

u32 MCL_STK_u32GetRemaining(void)
{
 u32 Copy_u32Ticks;

 Copy_u32Ticks = STK->STK_VAL;

 return Copy_u32Ticks;
}


void SysTick_Handler(void)
{

	if(STK_G_Config.SysTick_Exception == ENABLE_SINGLE_EXCEPTION)
	{
		STK->STK_CTRL_Bits.ENABLE = DISABLE_STATE;
		STK->STK_CTRL_Bits.TICKINT = DISABLE_STATE;
		/* Disable SysTick */
		STK->STK_CTRL = 0;
	}

	if(STK_G_Config.Systick_CallBackPtr != NULL_PTR)
		Global_STKCallBackPtr();

	STK->STK_VAL = 0;
}
