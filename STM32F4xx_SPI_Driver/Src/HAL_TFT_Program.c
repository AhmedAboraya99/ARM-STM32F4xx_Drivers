/*
 * HAL_TFT_Program.c
 *
 *  Created on: Sep 5, 2022
 *      Author: ahmed.hammad
 */




#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MCAL_GPIO_Interface.h"
#include "MCAL_STK_Interface.h"
#include "MCAL_SPI_Interface.h"
#include "HAL_TFT_Interface.h"
#include "HAL_TFT_Config.h"
#include "HAL_TFT_Private.h"





/**********************************************************************************************/
/*                                      FUNCTIONS		                                     */
/********************************************************************************************/

void HAL_TFT_vInit(void)
{
	/*Rest Pulse*/
	MCL_GPIO_vDirectPinSetter(TFT_PORT,TFT_RST_PIN,PIN_SET ) ;
	MCL_STK_vSetBusyWait(100) ;
	MCL_GPIO_vDirectPinSetter(TFT_PORT,TFT_RST_PIN,PIN_RESET) ;
	MCL_STK_vSetBusyWait(1) ;
	MCL_GPIO_vDirectPinSetter(TFT_PORT,TFT_RST_PIN,PIN_SET ) ;
	MCL_STK_vSetBusyWait(100) ;
	MCL_GPIO_vDirectPinSetter(TFT_PORT,TFT_RST_PIN,PIN_RESET) ;
	MCL_STK_vSetBusyWait(100) ;
	MCL_GPIO_vDirectPinSetter(TFT_PORT,TFT_RST_PIN,PIN_SET ) ;
	MCL_STK_vSetBusyWait(120) ;

	/*Send Command Sleep Out*/
	HAL_TFT_vWriteCommand(0x11) ;

	/*wait 150 ms*/
	MCL_STK_vSetBusyWait(150) ;

	/*color mode Command*/
	HAL_TFT_vWriteCommand(0x3A) ;
	HAL_TFT_vWriteData(0x05) ; //RGB565

	/*Display Command*/
	HAL_TFT_vWriteCommand(0x29) ;
}

void HAL_TFT_vDisplayImage(const u16* Copy_ptrImage)
{
	u16 counter ;
	u8 Data ;
	if(Copy_ptrImage != NULL)
	{
		/*Set X Address*/
		HAL_TFT_vWriteCommand(TFT_CMD_SET_X_ADDRESS) ;
		/*start*/
		HAL_TFT_vWriteData(0) ;
		HAL_TFT_vWriteData(0) ;
		/*stop*/
		HAL_TFT_vWriteData(0) ;
		HAL_TFT_vWriteData(TFT_X_END) ;

		/*Set Y Address*/
		HAL_TFT_vWriteCommand(TFT_CMD_SET_Y_ADDRESS) ;
		/*start*/
		HAL_TFT_vWriteData(0) ;
		HAL_TFT_vWriteData(0) ;
		/*stop*/
		HAL_TFT_vWriteData(0) ;
		HAL_TFT_vWriteData(TFT_Y_END) ;
		/*RAM Write Command*/
		HAL_TFT_vWriteCommand(TFT_CMD_RAM_WRITE) ;
		/*Display Image*/
		for(counter = 0 ; counter < TFT_IMAGE_SIZE ; counter++)
		{
			Data  = Copy_ptrImage[counter] >> 8 ;
			/*write high byte -->MSB*/
			HAL_TFT_vWriteData(Data) ;

			Data  = Copy_ptrImage[counter] & 0x00FF ;
			/*write high Low*/
			HAL_TFT_vWriteData(Data) ;
		}
	}

}


static void  HAL_TFT_vWriteCommand(u16 Copy_u16Cmd)
{
	/*Set Pin A0 in TFT to Low*/
	MCL_GPIO_vDirectPinSetter(TFT_PORT,TFT_A0_PIN,PIN_RESET) ;
	/*Send Data over SPI*/
		MCL_SPI_vMasterTransmit(SPI1, &Copy_u16Cmd, SPI_POLLING_ENABLE) ;

}


static void  HAL_TFT_vWriteData(u16 Copy_u16Data)
{

	/*Set Pin A0 in TFT to HIGH*/
	MCL_GPIO_vDirectPinSetter(TFT_PORT,TFT_A0_PIN,PIN_SET) ;
	/*Send Data over SPI*/
	MCL_SPI_vMasterTransmit(SPI1, &Copy_u16Data, SPI_POLLING_ENABLE) ;


}


