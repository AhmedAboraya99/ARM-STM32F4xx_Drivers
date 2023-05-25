/*
 * EXTI_Program.c
 *
 *  Created on: Mar 28, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  EXTI_Program.c
 *        \brief  Nested Vector Interrupt Controller Driver
 *
 *      \details  The Driver Configure All MCU interrupts Priority into groups and subgroups
 *                Enable NVIC Interrupt Gate for Peripherals
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "CORE_NVIC_Interface.h"
#include "MCAL_GPIO_Interface.h"
#include "MCAL_EXTI_Config.h"
#include "MCAL_EXTI_Interface.h"
#include "MCAL_RCC_Private.h"
#include "MCAL_RCC_Interface.h"

#include "MCAL_EXTI_Private.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
void (*EXTI_gpCallBackFn[15])(void);
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


void MCL_EXTI_vInit(EXTI_PinCfg_t* Copy_EXTI_Cfg)
{


	//configure GPIO pin as AF input
	GPIO_Cfg_t Local_GPIO_PinCfg;
	GPIO_Pin_t Local_GPIO_Pin = Copy_EXTI_Cfg->EXTI_PinMap.GPIO_Pin;
	Local_GPIO_PinCfg.GPIO_Mode = GPIO_MODE_AF_IN_PD;
	MCL_GPIO_vSetPinCfg(Copy_EXTI_Cfg->EXTI_PinMap.GPIO_Port, Local_GPIO_Pin, &Local_GPIO_PinCfg);

	// Enable System Configuration Controler (needed for EXTI)
	MCL_RCC_vEnablePeriphClk(APB2_BUS, RCC_APB2ENR_SYSCFGEN);

	/* Configure the external interrupt controller */
	//update routing to EXTI line with port A, B, C
	u8	SYSCFG_EXTICR_Index = (Copy_EXTI_Cfg->EXTI_PinMap.EXTI_LineNum) / 4 ;
	u8	SYSCFG_EXTICR_Position = ((Copy_EXTI_Cfg->EXTI_PinMap.EXTI_LineNum) % 4) * 4;

	//reset and set SYSCFG_EXTICR to select the source input for EXTIx external interrupt
	SYSCFG->EXTICR[SYSCFG_EXTICR_Index] &= ~(0xF<<SYSCFG_EXTICR_Position);
	SYSCFG->EXTICR[SYSCFG_EXTICR_Index] |= ((GPIO_xSelectPort(Copy_EXTI_Cfg->EXTI_PinMap.GPIO_Port))<<SYSCFG_EXTICR_Position);

	//reset edge trigger registers
	EXTI->RTSR &= ~(1<<Copy_EXTI_Cfg->EXTI_PinMap.EXTI_LineNum );
	EXTI->FTSR &= ~(1<<Copy_EXTI_Cfg->EXTI_PinMap.EXTI_LineNum );

	switch(Copy_EXTI_Cfg->Trigger_State)
	{
	case (EXTI_RISING_EDGE):

		SET_BIT(EXTI->RTSR , Copy_EXTI_Cfg->EXTI_PinMap.EXTI_LineNum);
		CLEAR_BIT(EXTI->FTSR, Copy_EXTI_Cfg->EXTI_PinMap.EXTI_LineNum);

		break;
	case (EXTI_FALLING_EDGE):

		SET_BIT(EXTI->FTSR , Copy_EXTI_Cfg->EXTI_PinMap.EXTI_LineNum);
		CLEAR_BIT(EXTI->RTSR , Copy_EXTI_Cfg->EXTI_PinMap.EXTI_LineNum);
		break;
	case (EXTI_ON_CHANGE):

		SET_BIT(EXTI->RTSR , Copy_EXTI_Cfg->EXTI_PinMap.EXTI_LineNum);
		SET_BIT(EXTI->FTSR , Copy_EXTI_Cfg->EXTI_PinMap.EXTI_LineNum);
		break;
	}


	if(Copy_EXTI_Cfg -> IRQ_EN == NVIC_IRQ_ENABLE)
	{
		//Update IRQ Handling Callback
		EXTI_gpCallBackFn[Copy_EXTI_Cfg->EXTI_PinMap.EXTI_LineNum] = Copy_EXTI_Cfg->IRQ_pCallBack;

		SET_BIT(EXTI ->IMR, Copy_EXTI_Cfg->EXTI_PinMap.EXTI_LineNum);

	/* Configure the NVIC to handle the interrupt */
		COR_NVIC_vSetPriorityCfg( Copy_EXTI_Cfg->EXTI_Priority.NVIC_GroupBits);
		COR_NVIC_vSetPriority(Copy_EXTI_Cfg->EXTI_PinMap.IVT_IRQNumber,Copy_EXTI_Cfg->EXTI_Priority.NVIC_GroupID, Copy_EXTI_Cfg->EXTI_Priority.NVIC_SubGroupID);
		COR_NVIC_vEnableInterrupt(Copy_EXTI_Cfg->EXTI_PinMap.IVT_IRQNumber);
	}
	else
	{
		//Update IRQ Handling Callback
		EXTI_gpCallBackFn[Copy_EXTI_Cfg->EXTI_PinMap.EXTI_LineNum] = NULL_PTR;

		CLEAR_BIT(EXTI ->IMR, Copy_EXTI_Cfg->EXTI_PinMap.EXTI_LineNum);
		COR_NVIC_vDisableInterrupt(Copy_EXTI_Cfg->EXTI_PinMap.IVT_IRQNumber);
	}

}
/******************************************************************************
 * @Fn          -EXTI_vEnable
 * @brief       -Enable EXTI
 * @param [in]  -Copy_u8IntNo : to select EXTI number
 * @param [in]  -Copy_u8SenseControl
 * @return      -None
 *******************************************************************************/

void MCL_EXTI_vEnable(EXTI_PinCfg_t* Copy_EXTI_Cfg, void (*Local_pCallBackFn)(void))
{
	if(Local_pCallBackFn != NULL_PTR)
		EXTI_gpCallBackFn[Copy_EXTI_Cfg->EXTI_PinMap.EXTI_LineNum] = Local_pCallBackFn;

	 MCL_EXTI_vInitGPIO(Copy_EXTI_Cfg->EXTI_PinMap.GPIO_Port, Copy_EXTI_Cfg->EXTI_PinMap.GPIO_Pin);

	//enable external interrupt request

	 SET_BIT(EXTI ->IMR, Copy_EXTI_Cfg->EXTI_PinMap.EXTI_LineNum);

}
/******************************************************************************
 * @Fn          -EXTI_vDisable
 * @brief       -Enable EXTI
 * @param [in]  -Copy_u8IntNo : to select EXTI number
 * @param [in]  -Copy_u8SenseControl
 * @return      -None
 *******************************************************************************/

void MCL_EXTI_vDisable(EXTI_Line_t Copy_xLineNo)
{


	EXTI_gpCallBackFn[Copy_xLineNo] = NULL_PTR;

	 CLEAR_BIT(EXTI ->IMR, Copy_xLineNo);

}

/******************************************************************************
 * @Fn          -EXTI_vInitGPIO
 * @brief       -Initialize EXTI pins
 * @param [in]  -Copy_u8IntNo : to select EXTI number
 * @param [in]  -Copy_u8SenseControl
 * @return      -None
 *******************************************************************************/
void MCL_EXTI_vInitGPIO(GPIO_Reg_t* GPIOx, GPIO_Pin_t Copy_EXTIPin)
{
	//configure GPIO pin as AF input
	GPIO_Cfg_t Local_GPIO_PinCfg;
	Local_GPIO_PinCfg.GPIO_Mode = GPIO_MODE_AF_IN_PD;
	MCL_GPIO_vSetPinCfg(GPIOx, Copy_EXTIPin, &Local_GPIO_PinCfg);
}
//====================
//ISR Functions
//====================

void EXTI0_IRQHandler(void){
	//Clear EXTI Pending Register by writing 1 to clear
	if(GET_BIT(EXTI -> PR, EXTI0))
	{
		EXTI -> PR |= 1<<EXTI0 ;
	//Call IRQ Call back function
	EXTI_gpCallBackFn[EXTI0]();
	}
}

void EXTI1_IRQHandler(void){
	//Clear EXTI Pending Register by writing 1 to clear
	if(GET_BIT(EXTI -> PR, EXTI1))
	{
		EXTI -> PR |= 1<<EXTI1 ;
		//Call IRQ Call back function
		EXTI_gpCallBackFn[EXTI1]();
	}
}

void EXTI2_IRQHandler(void){
	if(GET_BIT(EXTI -> PR, EXTI2))
	{
		//Clear EXTI Pending Register by writing 1 to clear
		EXTI -> PR |= 1<<EXTI2 ;
		//Call IRQ Call back function
		EXTI_gpCallBackFn[EXTI2]();
	}
}
void EXTI3_IRQHandler(void){
	//Clear EXTI Pending Register by writing 1 to clear
	EXTI -> PR |= 1<<EXTI3 ;
	//Call IRQ Call back function
	EXTI_gpCallBackFn[EXTI3]();
}
void EXTI4_IRQHandler(void){
	//Clear EXTI Pending Register by writing 1 to clear
	EXTI -> PR |= 1<<EXTI4 ;
	//Call IRQ Call back function
	EXTI_gpCallBackFn[EXTI4]();
}
void EXTI9_5_IRQHandler(void){
	if (EXTI->PR & 1<<EXTI5){
		//Clear EXTI Pending Register by writing 1 to clear
		EXTI -> PR |= 1<<EXTI5 ;
		//Call IRQ Call back function
		EXTI_gpCallBackFn[EXTI5]();
	}
	if (EXTI->PR & 1<<EXTI6){
		//Clear EXTI Pending Register by writing 1 to clear
		EXTI -> PR |= 1<<EXTI6 ;
		//Call IRQ Call back function
		EXTI_gpCallBackFn[EXTI6]();
	}
	if (EXTI->PR & 1<<EXTI7){
		//Clear EXTI Pending Register by writing 1 to clear
		EXTI -> PR |= 1<<EXTI7 ;
		//Call IRQ Call back function
		EXTI_gpCallBackFn[EXTI7]();
	}
	if (EXTI->PR & 1<<EXTI8){
		//Clear EXTI Pending Register by writing 1 to clear
		EXTI -> PR |= 1<<EXTI8 ;
		//Call IRQ Call back function
		EXTI_gpCallBackFn[EXTI8]();
	}
	if (EXTI->PR & 1<<EXTI9){
		//Clear EXTI Pending Register by writing 1 to clear
		EXTI -> PR |= 1<<EXTI9 ;
		//Call IRQ Call back function
		EXTI_gpCallBackFn[EXTI9]();
	}
}
void EXTI15_10_IRQHandler(void){
	if (EXTI->PR & 1<<EXTI10){
		//Clear EXTI Pending Register by writing 1 to clear
		EXTI -> PR |= 1<<EXTI10 ;
		//Call IRQ Call back function
		EXTI_gpCallBackFn[EXTI10]();
	}
	if (EXTI->PR & 1<<EXTI11){
		//Clear EXTI Pending Register by writing 1 to clear
		EXTI -> PR |= 1<<EXTI11 ;
		//Call IRQ Call back function
		EXTI_gpCallBackFn[EXTI11]();
	}
	if (EXTI->PR & 1<<EXTI12){
		//Clear EXTI Pending Register by writing 1 to clear
		EXTI -> PR |= 1<<EXTI12 ;
		//Call IRQ Call back function
		EXTI_gpCallBackFn[EXTI12]();
	}
	if (EXTI->PR & 1<<EXTI13){
		//Clear EXTI Pending Register by writing 1 to clear
		EXTI -> PR |= 1<<EXTI13 ;
		//Call IRQ Call back function
		EXTI_gpCallBackFn[EXTI13]();
	}
	if (EXTI->PR & 1<<EXTI14){
		//Clear EXTI Pending Register by writing 1 to clear
		EXTI -> PR |= 1<<EXTI14 ;
		//Call IRQ Call back function
		EXTI_gpCallBackFn[EXTI14]();
	}
	if (EXTI->PR & 1<<EXTI15){
		//Clear EXTI Pending Register by writing 1 to clear
		EXTI -> PR |= 1<<EXTI15 ;
		//Call IRQ Call back function
		EXTI_gpCallBackFn[EXTI15]();
	}
}
