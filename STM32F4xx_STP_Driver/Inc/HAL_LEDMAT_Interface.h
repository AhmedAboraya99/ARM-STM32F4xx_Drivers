/*
 * LEDMAT_Interface.h
 *
 * Created: 4/17/2023 5:52:21 PM
 *  Author: Ahmed Aboraya
 */


#ifndef HAL_LEDMAT_INTERFACE_H_
#define HAL_LEDMAT_INTERFACE_H_
//-----------------------------
//Includes
//-----------------------------
#include "MCAL_GPIO_Interface.h"
#include "HAL_LEDMAT_Private.h"

//-----------------------------
//Macros
//-----------------------------
#define LEDMARTIX_SIZE		8
//-----------------------------
//Global Variables
//-----------------------------


/*-------------------------------
 ------Function Prototypes-------
---------------------------------*/

void HAL_LEDMAT_vInit(void) ;

void HAL_LEDMAT_vDisplay(u8 *Copy_u8Frame) ;


#endif /* HAL_LEDMAT_INTERFACE_H_ */
