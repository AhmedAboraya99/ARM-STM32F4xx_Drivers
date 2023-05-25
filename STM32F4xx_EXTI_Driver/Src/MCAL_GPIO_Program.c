/*
 * MCAL_GPIO_Program.c
 *
 *  Created on: May 10, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "BIT_MATH.h"
#include "MCAL_GPIO_Interface.h"
#include "MCAL_GPIO_Config.h"
#include "MCAL_GPIO_Private.h"
#include "MCAL_RCC_Interface.h"
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
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
void MCL_GPIO_vInitPort(GPIO_Reg_t* GPIOx, GPIO_Cfg_t* Copy_GPIO_Cfg)
{
	/* Enable RCC GPIO port clock. */
	MCL_RCC_vEnablePeriphClk(AHB1_BUS, GPIO_xSelectPort(GPIOx));

 	/* 1. Configure the GPIO port. */
 	for(u8 Local_u8PinId = GPIO_PIN0; Local_u8PinId <= GPIO_PIN15;Local_u8PinId++)
 		ASSIGN_BITS(GPIOx->GPIO_MODER, (Local_u8PinId*TWO_BITS), TWO_BITS,Copy_GPIO_Cfg->GPIO_Mode);



  /* 2. Configure the GPIO pull-up/pull-down. */
		if(		Copy_GPIO_Cfg->GPIO_Mode == GPIO_MODE_IN_FLOAT 
			|| 	Copy_GPIO_Cfg->GPIO_Mode == GPIO_MODE_IN_PU
			|| 	Copy_GPIO_Cfg->GPIO_Mode == GPIO_MODE_IN_PD
			||  Copy_GPIO_Cfg->GPIO_Mode == GPIO_MODE_AF_IN_PU 
			||	Copy_GPIO_Cfg->GPIO_Mode == GPIO_MODE_AF_IN_PD)
	{
		for(u8 Local_u8PinId = GPIO_PIN0; Local_u8PinId <= GPIO_PIN15;Local_u8PinId++)
 			ASSIGN_BITS(GPIOx->GPIO_PUPDR, (Local_u8PinId*TWO_BITS), TWO_BITS,Copy_GPIO_Cfg->GPIO_Mode>>THREE_BITS);
	}
	/* 3. Configure the GPIO output. */
 	/* 4.  Configure the GPIO output speed. */
	/* Check mode is output */
	else if(   Copy_GPIO_Cfg->GPIO_Mode == GPIO_MODE_OUT_PP 
			|| Copy_GPIO_Cfg->GPIO_Mode == GPIO_MODE_OUT_OD
			|| Copy_GPIO_Cfg->GPIO_Mode == GPIO_MODE_AF_OUT_OD 
			|| Copy_GPIO_Cfg->GPIO_Mode == GPIO_MODE_AF_OUT_PP)
	{
		for(u8 Local_u8PinId = GPIO_PIN0; Local_u8PinId <= GPIO_PIN15;Local_u8PinId++)
		{
			ASSIGN_BITS(GPIOx->GPIO_OTYPER, Local_u8PinId, ONE_BIT,Copy_GPIO_Cfg->GPIO_Mode>>TWO_BITS);
			ASSIGN_BITS(GPIOx->GPIO_OSPEEDR, (Local_u8PinId*TWO_BITS), TWO_BITS,Copy_GPIO_Cfg->GPIO_Speed);
		}
	}



}
void MCL_GPIO_vSetPinCfg(GPIO_Reg_t* GPIOx, GPIO_Pin_t Copy_PinId, GPIO_Cfg_t* Copy_GPIO_Cfg)
{

	MCL_RCC_vEnablePeriphClk(AHB1_BUS, GPIO_xSelectPort(GPIOx));
 	/* 1. Configure the GPIO port. */
 	ASSIGN_BITS(GPIOx->GPIO_MODER, (Copy_PinId*TWO_BITS), TWO_BITS,Copy_GPIO_Cfg->GPIO_Mode);
  	/* 2. Configure the GPIO pull-up/pull-down. */
	if(			Copy_GPIO_Cfg->GPIO_Mode == GPIO_MODE_IN_FLOAT 
			|| 	Copy_GPIO_Cfg->GPIO_Mode == GPIO_MODE_IN_PU
			|| 	Copy_GPIO_Cfg->GPIO_Mode == GPIO_MODE_IN_PD
			||  Copy_GPIO_Cfg->GPIO_Mode == GPIO_MODE_AF_IN_PU 
			||	Copy_GPIO_Cfg->GPIO_Mode == GPIO_MODE_AF_IN_PD)
	{
 			ASSIGN_BITS(GPIOx->GPIO_PUPDR, (Copy_PinId*TWO_BITS), TWO_BITS,Copy_GPIO_Cfg->GPIO_Mode>>THREE_BITS);
	}
	/* 3. Configure the GPIO output. */
 	/* 4.  Configure the GPIO output speed. */
	/* Check mode is output */
	else if(Copy_GPIO_Cfg->GPIO_Mode == GPIO_MODE_OUT_PP || Copy_GPIO_Cfg->GPIO_Mode == GPIO_MODE_OUT_OD
	|| Copy_GPIO_Cfg->GPIO_Mode == GPIO_MODE_AF_OUT_OD || Copy_GPIO_Cfg->GPIO_Mode == GPIO_MODE_AF_OUT_PP)
	{

			ASSIGN_BITS(GPIOx->GPIO_OTYPER, Copy_PinId, ONE_BIT,Copy_GPIO_Cfg->GPIO_Mode>>TWO_BITS);
			ASSIGN_BITS(GPIOx->GPIO_OSPEEDR, (Copy_PinId*TWO_BITS), TWO_BITS,Copy_GPIO_Cfg->GPIO_Speed);
	}


}
void MCL_GPIO_vDirectPinSetter(GPIO_Reg_t* GPIOx, GPIO_Pin_t Copy_PinId, Pin_State_t Copy_xPinVal)
{
	if(Copy_PinId < GPIO_PIN0 && Copy_PinId > GPIO_PIN15)
	{
		/* Do nothing */
	}else
	{
	switch (Copy_xPinVal)
	{
		case PIN_SET:
			ASSIGN_BIT(GPIOx->GPIO_BSRR_Bits.BS, Copy_PinId, PIN_SET);
			break;
		case PIN_RESET:
			ASSIGN_BIT(GPIOx->GPIO_BSRR_Bits.BR, Copy_PinId, PIN_SET);
			break;
		default:
			break;
		}
	}

}

void MCL_GPIO_vTogglePin(GPIO_Reg_t* GPIOx, GPIO_Pin_t Copy_PinId)
{
	if(Copy_PinId < GPIO_PIN0 && Copy_PinId > GPIO_PIN15)
	{
		/* Do nothing */
	}else
	{
		TOGGLE_BIT(GPIOx->GPIO_ODR, Copy_PinId);
	}

}
u8 	MCL_GPIO_u8GetPinVal(GPIO_Reg_t* GPIOx, GPIO_Pin_t Copy_PinId)
{
	if(Copy_PinId < GPIO_PIN0 && Copy_PinId > GPIO_PIN15)
	{
		return -1;
	}else
	{
		return (GET_BIT(GPIOx->GPIO_IDR, Copy_PinId));
	}
}
void MCL_GPIO_vWritePort(GPIO_Reg_t* GPIOx, u32 Copy_u32PortVal)
{
	WRITE_REG(GPIOx->GPIO_ODR, Copy_u32PortVal);
}
u32 MCL_GPIO_u32ReadPort(GPIO_Reg_t* GPIOx)
{
	return READ_REG(GPIOx->GPIO_IDR);
}

GPIO_Port_t GPIO_xSelectPort(GPIO_Reg_t* GPIOx)
{
	u32 Local_PortOffset = 0;
	Local_PortOffset = (u32)((u32)GPIOx - (u32)GPIOA);
		return ((GPIO_Port_t)(Local_PortOffset/0x400));

}
