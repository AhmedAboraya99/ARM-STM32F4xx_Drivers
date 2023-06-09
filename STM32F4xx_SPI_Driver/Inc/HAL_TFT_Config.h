/*
 * HAL_TFT_Config.h
 *
 *  Created on: Jun 5, 2023
 *      Author: Ahmed Aboraya
 */

#ifndef HAL_TFT_CONFIG_H_
#define HAL_TFT_CONFIG_H_

#define TFT_PORT		 GPIOA
#define TFT_A0_PIN       GPIO_PIN2
#define TFT_RST_PIN      GPIO_PIN1

#define TFT_CMD_SET_X_ADDRESS			0x2A
#define TFT_CMD_SET_Y_ADDRESS			0x2B
#define TFT_CMD_RAM_WRITE				0x2C

#define TFT_X_END			127
#define TFT_Y_END			159

#define TFT_IMAGE_SIZE		20480

#endif /* HAL_TFT_CONFIG_H_ */
