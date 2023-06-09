/*
 * SRV_RTO_Private.h
 *
 *  Created on: May 10, 2023
 *      Author: ahmed aboraya
 */

#ifndef SRV_RTO_PRIVATE_H_
#define SRV_RTO_PRIVATE_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STM32F4xx_Device_Header.h"
#include "SRV_RTO_Interface.h"
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
typedef struct{

    void (*Pf)(void);
    u32 First_Delay;
    u32 Periodicity;
    u8 Priority;
    Task_State_t State;
}RTO_TCB_t;



extern RTO_TCB_t RTO_pxTaskStatus[];
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/



#endif /* SRV_RTO_PRIVATE_H_ */
