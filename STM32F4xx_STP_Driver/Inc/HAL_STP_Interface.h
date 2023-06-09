/*
 * STP_Interface.h
 *
 * Created: 4/17/2023 5:52:21 PM
 *  Author: Ahmed Aboraya
 */


#ifndef HAL_STP_INTERFACE_H_
#define HAL_STP_INTERFACE_H_
//-----------------------------
//Includes
//-----------------------------
#include "MCAL_GPIO_Interface.h"
#include "HAL_STP_Private.h"

//-----------------------------
//Macros
//-----------------------------

//-----------------------------
//Global Variables
//-----------------------------


//-----------------------------
//Global Variables
//-----------------------------
typedef enum
{
	STP1,
	STP2
}STP_Index_t;


/*-------------------------------
 ------Function Prototypes-------
---------------------------------*/

void HAL_STP_vInit(STP_Index_t	Copy_xSTP);
void HAL_STP_vSendSynchronous(STP_Index_t Copy_xSTP, u8 Copy_u8TxData);

#endif /* HAL_STP_INTERFACE_H_ */
