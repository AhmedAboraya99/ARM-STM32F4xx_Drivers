/*
 * MCAL_RCC_Program.c
 *
 *  Created on: May 10, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "BIT_MATH.h"

#include "MCAL_RCC_Config.h"
#include "MCAL_RCC_Interface.h"
#include "MCAL_RCC_Private.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void MCAL_RCC_vInitSysClk(RCC_Cfg_t* Copy_xRCC_Cfg)
{
	 /********Enable All System Clocks***********/
	RCC->RCC_CR.HSION = 1;
	RCC->RCC_CR.HSEON = 1;
	RCC->RCC_CR.PLLON = 1;

	 /************Select System Clock***********/
	RCC->RCC_CFGR_bits.SWn = Copy_xRCC_Cfg->System_ClkSelection;
	 /************Select System Clock Type***********/
	RCC->RCC_CR.HSEBYP = Copy_xRCC_Cfg->System_ClkType;
	switch (Copy_xRCC_Cfg->System_ClkSelection)
	{
	case HSI_CLOCK:
		RCC->RCC_CFGR_bits.HPRE = Copy_xRCC_Cfg->System_ClkPrescaler;
		break;
	case HSE_CLOCK:
		RCC->RCC_CFGR_bits.RTCPRE = Copy_xRCC_Cfg->System_ClkPrescaler;
		break;
	case PLL_CLOCK:
		break;
	}

}

void MCAL_RCC_vEnablePeriphClk(SysBus_t Copy_u8Bus, GPIO_Select_t Copy_u8Periph)
{
	switch(Copy_u8Bus)
	{
     case AHB1_BUS  : SET_BIT(RCC->RCC_AHB1ENR,Copy_u8Periph) ; break ;
     case AHB2_BUS  : SET_BIT(RCC->RCC_AHB2ENR,Copy_u8Periph) ; break ;
     case APB1_BUS  : SET_BIT(RCC->RCC_APB1ENR,Copy_u8Periph) ; break ;
     case APB2_BUS  : SET_BIT(RCC->RCC_APB2ENR,Copy_u8Periph) ; break ;
	 default    : /* ERROR*/         break ;
	}
}
void MCAL_RCC_vDisablePeriphClk(SysBus_t Copy_u8Bus, GPIO_Select_t Copy_u8Periph)
{

	switch(Copy_u8Bus)
	{
     case AHB1_BUS  : CLEAR_BIT(RCC->RCC_AHB1ENR,Copy_u8Periph) ; break ;
     case AHB2_BUS  : CLEAR_BIT(RCC->RCC_AHB2ENR,Copy_u8Periph) ; break ;
     case APB1_BUS  : CLEAR_BIT(RCC->RCC_APB1ENR,Copy_u8Periph) ; break ;
     case APB2_BUS  : CLEAR_BIT(RCC->RCC_APB2ENR,Copy_u8Periph) ; break ;
	 default    : /* ERROR*/         break ;
	}
}
