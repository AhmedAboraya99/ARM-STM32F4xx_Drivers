/*
 * HAL_LEDMAT_Program.c
 *
 *  Created on: May 10, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MCAL_STK_Interface.h"
#include "MCAL_STK_Private.h"
#include "MCAL_GPIO_Config.h"
#include "HAL_LEDMAT_Interface.h"
#include "HAL_LEDMAT_Config.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
void (*Global_LEDMATCallBackPtr)(void) = NULL_PTR;

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  CONFIGURATIONS ASSIGNMENT
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
void HAL_LEDMAT_vInit()
{
	for(u8 Local_u8Index =LEDMAT_ROW0_PIN; Local_u8Index <= LEDMAT_ROW7_PIN; Local_u8Index++)
	{
	MCL_GPIO_vSetPinCfg(LEDMAT_ROW_PORT, Local_u8Index, &GPIO_OUT_Config);
	MCL_GPIO_vSetPinCfg(LEDMAT_COL_PORT, Local_u8Index, &GPIO_OUT_Config);
	}
}

void HAL_LEDMAT_vDisplay(u8 *Copy_u8Frame)
{
	for(u8 Local_u8Index =LEDMAT_COL0_PIN; Local_u8Index <= LEDMAT_COL7_PIN; Local_u8Index++)
	{
		/*Disable All Columns*/
		HAL_LEDMAT_vDarkCols();
		/*Set Row Value*/
		HAL_LEDMAT_vSetRowsVal(Copy_u8Frame[Local_u8Index]);
		/*Enable Column */
		MCL_GPIO_vDirectPinSetter(LEDMAT_COL_PORT, Local_u8Index, PIN_RESET);
		//Delay for POV transition
		MCL_STK_vSetBusyWait(2500);
	}
}



void HAL_LEDMAT_vDarkCols(void)
{
	for(u8 Local_u8Index =LEDMAT_COL0_PIN; Local_u8Index <= LEDMAT_COL7_PIN; Local_u8Index++)
	{
		MCL_GPIO_vDirectPinSetter(LEDMAT_COL_PORT, Local_u8Index, PIN_SET);
	}
}
static void HAL_LEDMAT_vSetRowsVal(u8 Copy_u8Frame)
{
	u8 Local_u8DotBit;
	for(u8 Local_u8Index =LEDMAT_ROW0_PIN; Local_u8Index <= LEDMAT_ROW7_PIN; Local_u8Index++)
	{
		Local_u8DotBit = GET_BIT(Copy_u8Frame, Local_u8Index);
		MCL_GPIO_vDirectPinSetter(LEDMAT_COL_PORT, Local_u8Index, Local_u8DotBit);
	}
}
