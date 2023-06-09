/*
 * EXTI_Private.h
 *
 *  Created on: Mar 27, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  EXTI_Private.h
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>
 *
 *********************************************************************************************************************/
#ifndef MCAL_EXTI_PRIVATE_H_
#define MCAL_EXTI_PRIVATE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "MCAL_GPIO_Private.h"




/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct{
  vu32 MEMRMP;       /*!< SYSCFG memory remap register,                      Address offset: 0x00      */
  vu32 PMC;          /*!< SYSCFG peripheral mode configuration register,     Address offset: 0x04      */
  vu32 EXTICR[4];    /*!< SYSCFG external interrupt configuration registers, Address offset: 0x08-0x14 */
  u32  RESERVED[2];  /*!< Reserved, 0x18-0x1C                                                          */
  vu32 CMPCR;        /*!< SYSCFG Compensation cell control register,         Address offset: 0x20      */
}SYSCFG_Reg_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{

	vu32 IMR;
	vu32 EMR;
	vu32 RTSR;
	vu32 FTSR;
	vu32 SWIER;
	vu32 PR;

}EXTI_Reg_t;
/**********************************************************************************************************************
 *  PRIVATE CONSTANT MACROS
 *********************************************************************************************************************/

#define SYSCFG 			((SYSCFG_Reg_t *)SYSCFG_BASE)
#define EXTI 			  ((EXTI_Reg_t *)EXTI_BASE)




#endif /* MCAL_EXTI_PRIVATE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: EXTI.h
 *********************************************************************************************************************/


