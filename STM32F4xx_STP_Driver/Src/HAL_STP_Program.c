/*
 * HAL_STP_Program.c
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
#include "HAL_STP_Interface.h"
#include "HAL_STP_Config.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
void (*Global_STPCallBackPtr)(void) = NULL_PTR;

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  CONFIGURATIONS ASSIGNMENT
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
void HAL_STP_vInit(STP_Index_t Copy_xSTP)
{
		MCL_GPIO_vSetPinCfg(GPIO_xSelectReg(Copy_xSTP), STP_SERIAL_DATA, &GPIO_OUT_Config);
		MCL_GPIO_vSetPinCfg(GPIO_xSelectReg(Copy_xSTP), STP_SHIFT_CLOCK, &GPIO_OUT_Config);
		MCL_GPIO_vSetPinCfg(GPIO_xSelectReg(Copy_xSTP), STP_STORE_CLOCK, &GPIO_OUT_Config);

}

void HAL_STP_vSendSynchronous(STP_Index_t Copy_xSTP, u8 Copy_u8TxData)
{
	u8 Local_u8SerialBit;
	for(s8 Local_u8Counter = 0; Local_u8Counter < 8 ; Local_u8Counter++)
	{
		Local_u8SerialBit = GET_BIT(Copy_u8TxData, Local_u8Counter);
		MCL_GPIO_vDirectPinSetter(GPIO_xSelectReg(Copy_xSTP), STP_SERIAL_DATA, Local_u8SerialBit);
		MCL_STK_vSetBusyWait(1);
		/*Send Pulse to Shift Clock*/
		MCL_GPIO_vDirectPinSetter(GPIO_xSelectReg(Copy_xSTP), STP_SHIFT_CLOCK, PIN_SET);
		MCL_STK_vSetBusyWait(1);
		MCL_GPIO_vDirectPinSetter(GPIO_xSelectReg(Copy_xSTP), STP_SHIFT_CLOCK, PIN_RESET);

	}
	  /*Send Pulse to Store Clock*/
	MCL_GPIO_vDirectPinSetter(GPIO_xSelectReg(Copy_xSTP), STP_STORE_CLOCK, PIN_SET);
	MCL_STK_vSetBusyWait(1);
	MCL_GPIO_vDirectPinSetter(GPIO_xSelectReg(Copy_xSTP), STP_STORE_CLOCK, PIN_RESET);

}
