/*
 * MCAL_SPI_Config.h
 *
 *  Created on: Mar 28, 2023
 *      Author: ahmed
 */

#ifndef MCAL_SPI_CONFIG_H_
#define MCAL_SPI_CONFIG_H_

#include "MCAL_GPIO_Interface.h"

/**********************************************************************************************************************
 *  CONFIGURATION MACROS
 *********************************************************************************************************************/
#define SPI1_PORT		GPIOA

#define SPI1_SSEL_PIN	GPIO_PIN4
#define SPI1_SCLK_PIN	GPIO_PIN5
#define SPI1_MISO_PIN	GPIO_PIN6
#define SPI1_MOSI_PIN	GPIO_PIN7

#define SPI2_PORT		GPIOB

#define SPI2_SSEL_PIN	GPIO_PIN12
#define SPI2_SCLK_PIN	GPIO_PIN13
#define SPI2_MISO_PIN	GPIO_PIN14
#define SPI2_MOSI_PIN	GPIO_PIN15


#endif /* MCAL_SPI_CONFIG_H_ */
