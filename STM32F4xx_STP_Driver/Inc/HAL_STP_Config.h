/*
 * STP_Config.h
 *
 *  Created on: Mar 28, 2023
 *      Author: ahmed
 */

#ifndef HAL_STP_CONFIG_H_
#define HAL_STP_CONFIG_H_


/**********************************************************************************************************************
 *  CONFIGURATION MACROS
 *********************************************************************************************************************/


//@STP_u8Type

#define STP1_PORT            GPIOA
#define STP2_PORT            GPIOB


#define STP_SERIAL_DATA         GPIO_PIN8
#define STP_SHIFT_CLOCK         GPIO_PIN10
#define STP_STORE_CLOCK         GPIO_PIN9

#endif /* HAL_STP_CONFIG_H_ */
