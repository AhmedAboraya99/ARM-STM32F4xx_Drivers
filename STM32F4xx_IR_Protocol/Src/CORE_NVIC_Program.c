/*
 * CORE_NVIC_Program.c
 *
 *  Created on: May 10, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "CORE_NVIC_Private.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "CORE_NVIC_Interface.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
void (*Global_NVICCallBackPtr)(void) = NULL;

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  CONFIGURATIONS ASSIGNMENT
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
void COR_NVIC_vEnableInterrupt(IRQ_Num_t Copy_xIRQId)
{
	if(Copy_xIRQId < 240)
	{
		NVIC->NVIC_ISER[Copy_xIRQId / 32] = (1 << (Copy_xIRQId%32));
	}

}
void COR_NVIC_vDisableInterrupt(IRQ_Num_t Copy_xIRQId)
{
	if(Copy_xIRQId < 240)
	{
		NVIC->NVIC_ICER[Copy_xIRQId / 32] = (1 << (Copy_xIRQId%32));
	}

}
void COR_NVIC_vSetPendFlag(IRQ_Num_t Copy_xIRQId)
{
 NVIC->NVIC_ISPR[Copy_xIRQId / 32] = (1 << (Copy_xIRQId%32));
}

void COR_NVIC_vClrPendFlag(IRQ_Num_t Copy_xIRQId)
{
 NVIC->NVIC_ICPR[Copy_xIRQId / 32] = (1 << (Copy_xIRQId%32));

}

STD_Bool COR_NVIC_vGetActiveFlag(IRQ_Num_t Copy_xIRQId)
{
	return (GET_BIT(NVIC->NVIC_IABR[Copy_xIRQId / 32], Copy_xIRQId%32 ));
}


void COR_NVIC_vSetPriorityCfg(NVIC_Grouping_t Copy_u8PriorityOption)
{
    SCB->AIRCR = (VECTKEY << 16) |(Copy_u8PriorityOption<<8);
}

void COR_NVIC_vSetPriority(IRQ_Num_t Copy_xIRQId, u8 Copy_u8GroupId,  u8 Copy_u8SubGroupId)
{
	u8 Copy_u8PriorityId = (Copy_u8SubGroupId | (Copy_u8GroupId<<READ_BITS(SCB->AIRCR,BIT8,THREE_BITS))) ;
    NVIC->NVIC_IPR[Copy_xIRQId] =  (Copy_u8PriorityId<<4);
}

