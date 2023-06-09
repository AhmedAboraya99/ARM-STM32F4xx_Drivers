/*
 * STM32F4xx_GPIO_Interface.h
 *
 *  Created on: May 10, 2023
 *      Author: ahmed
 */

#ifndef MCAL_GPIO_INTERFACE_H_
#define MCAL_GPIO_INTERFACE_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STD_TYPES.h"
#include "MCAL_GPIO_Private.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
//@ pin_id_options
typedef enum {
    GPIO_PIN0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7,
	GPIO_PIN8,
	GPIO_PIN9,
	GPIO_PIN10,
	GPIO_PIN11,
	GPIO_PIN12,
	GPIO_PIN13,
	GPIO_PIN14,
	GPIO_PIN15,
}GPIO_Pin_t;


//-----------------------------
//Macros Configuration References
//-----------------------------

/*@ref GPIO_Mode_define
 * 0 : Analog Mode
 * 1 : floating input (reset state)
 * 2 : Input with pull-up
 * 3 : Input with Pull-down
 * 4 : General purpose Output Push-pull
 * 5 : General purpose Output Open-drain
 * 6 : Alternate function Output Push-pull
 * 7 : Alternate function Output Open-drain
 * 8 : Alternate function Input
*/
typedef enum
{
	GPIO_MODE_IN_FLOAT		=		0b000000U,
	GPIO_MODE_IN_PU			=		0b001000U,
 	GPIO_MODE_IN_PD			=		0b010000U,
	GPIO_MODE_OUT_PP		=		0b000001U,
	GPIO_MODE_OUT_OD		=		0b000101U,
	GPIO_MODE_AF_IN_PU		=		0b001010U,
	GPIO_MODE_AF_IN_PD		=		0b010010U,
 	GPIO_MODE_AF_OUT_PP		=		0b000010U,
 	GPIO_MODE_AF_OUT_OD		=		0b000110U,
	GPIO_MODE_ANALOG		=		0b000011U,

}GPIO_Mode_t;

/*@ref GPIO_Speed_define
  0 : Output mode, Low speed max 2 MHz.
  1 : Output mode, Medium speed max 10 MHz.
  2 : Output mode, High speed max 50 MHz.
  2 : Output mode, Very High speed max 84 MHz.

*/
typedef enum
{
 GPIO_SPEED_LOW			=	0,
 GPIO_SPEED_MEDIUM		=	1,
 GPIO_SPEED_HIGH		=	2,
 GPIO_SPEED_VERY_HIGH   =   3,
}GPIO_Speed_t;

#define GPIO_PIN_MASK			0x0000FFFFU //pin mask to test





typedef struct
{

	GPIO_Mode_t GPIO_Mode;			//mode of GPIO selected port/pin
	//this parameter can be a value of  @ref GPIO_Mode_define

	uint8_t GPIO_Speed;			//speed of GPIO selected port/pin
	//this parameter can be a value of  @ref GPIO_Speed_define

}GPIO_Cfg_t;


extern GPIO_Cfg_t GPIO_OUT_Config;
extern GPIO_Cfg_t GPIO_IN_Config;
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

void MCL_GPIO_vInitPort(GPIO_Reg_t* GPIOx, GPIO_Cfg_t* Copy_GPIO_Cfg);
void MCL_GPIO_vSetPinCfg(GPIO_Reg_t* GPIOx, GPIO_Pin_t Copy_PinId, GPIO_Cfg_t* Copy_GPIO_Cfg);
void MCL_GPIO_vDirectPinSetter(GPIO_Reg_t* GPIOx, GPIO_Pin_t Copy_PinId, Pin_State_t Copy_xPinVal);
u8 	MCL_GPIO_u8GetPinVal(GPIO_Reg_t* GPIOx, GPIO_Pin_t Copy_PinId);
void MCL_GPIO_vWritePort(GPIO_Reg_t* GPIOx, u32 Copy_u32PortVal);
u32 MCL_GPIO_u32ReadPort(GPIO_Reg_t* GPIOx);
void MCL_GPIO_vTogglePin(GPIO_Reg_t* GPIOx, GPIO_Pin_t Copy_PinId);


#endif /* MCAL_GPIO_INTERFACE_H_ */
