
/*
 * STM32F4xx_NVIC_Interface.h
 *
 *  Created on: May 10, 2023
 *      Author: ahmed
 */

#ifndef CORE_NVIC_INTERFACE_H_
#define CORE_NVIC_INTERFACE_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STD_TYPES.h"
#include "STM32F4xx_Device_Header.h"

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

	Group16_NoneSub     =     0b011,
	Group8_2Sub     =         0b100,
	Group4_4Sub     =         0b101,
	Group2_8Sub     =         0b110,
	GroupNone_16SubGroup  =   0b111
}NVIC_Grouping_t;

typedef enum {
	NVIC_IRQ_DISABLE = 0,
	NVIC_IRQ_ENABLE	= 1
}IRQ_State_t;



/**********************************************************************************************************************
 *  CONFIG STRUCTURES
 *********************************************************************************************************************/
typedef struct
{
	NVIC_Grouping_t NVIC_GroupBits;
	u8 	NVIC_GroupID;
	u8 NVIC_SubGroupID;
}NVIC_Cfg_t;

extern NVIC_Cfg_t NVIC_G_Config;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

void COR_NVIC_vEnableInterrupt(IRQ_Num_t Copy_xIRQId);
void COR_NVIC_vDisableInterrupt(IRQ_Num_t Copy_xIRQId);
void COR_NVIC_vSetPendFlag(IRQ_Num_t Copy_xIRQId);
void COR_NVIC_vClrPendFlag(IRQ_Num_t Copy_xIRQId);
STD_Bool CR_NVIC_vGetActiveFlag(IRQ_Num_t Copy_xIRQId);
void COR_NVIC_vSetPriorityCfg(NVIC_Grouping_t Copy_u8PriorityOption);
void COR_NVIC_vSetPriority(IRQ_Num_t Copy_xIRQId, u8 Copy_u8GroupId,  u8 Copy_u8SubGroupId);
#endif /* CORE_NVIC_INTERFACE_H_ */
