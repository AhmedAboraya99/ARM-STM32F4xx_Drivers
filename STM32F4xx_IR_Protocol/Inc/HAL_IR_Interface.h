/*
 * IR_Interface.h
 *
 * Created: 4/17/2023 5:52:21 PM
 *  Author: Ahmed Aboraya
 */


#ifndef HAL_IR_INTERFACE_H_
#define HAL_IR_INTERFACE_H_
//-----------------------------
//Includes
//-----------------------------
#include "MCAL_GPIO_Interface.h"
#include "HAL_IR_Private.h"

//-----------------------------
//Macros
//-----------------------------

#define IR_SEGMENTS_COUNT	7
#define IR_MAX_COUNT		10
//-----------------------------
//Global Variables
//-----------------------------

// Array of 7 segment shapes of Numbers
extern u8 IR_Au8NumShapes[10];


/*-------------------------------
 ------Function Prototypes-------
---------------------------------*/

void HAL_IR_vInit(GPIO_Reg_t* Copy_IRGPIOx, GPIO_Cfg_t* Copy_IRGpioCfg,u8 IR_u8Type);

void HAL_IR_vReceive(GPIO_Reg_t* Copy_IRGPIOx);


#endif /* HAL_IR_INTERFACE_H_ */
