/*
 * MCAL_STK_Private.h
 *
 *  Created on: May 10, 2023
 *      Author: ahmed aboraya
 */

#ifndef MCAL_STK_PRIVATE_H_
#define MCAL_STK_PRIVATE_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STM32F4xx_Device_Header.h"
#include "STD_TYPES.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


typedef struct
{
	union{
	struct {
		vu32 ENABLE:1;
		vu32 TICKINT:1;
		vu32 CLKSOURCE:1;
		u32 :13;
		vu32 COUNTFLAG:1;
		u32 :15;
	} STK_CTRL_Bits;
	vu32 STK_CTRL;
	};

	vu32 STK_LOAD;

	vu32 STK_VAL;
	vu32 STK_CALIB;

}STK_Reg_t;

#define STK				((volatile STK_Reg_t *)SYSTICK_BASE)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/



#endif /* MCAL_STK_PRIVATE_H_ */