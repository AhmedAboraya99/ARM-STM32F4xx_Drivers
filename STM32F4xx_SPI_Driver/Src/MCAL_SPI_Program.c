/*
 * MCAL_SPI_Program.c
 *
 *  Created on: Mar 28, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  MCAL_SPI_Program.c
 *        \brief  Nested Vector Interrupt Controller Driver
 *
 *      \details  The Driver Configure All MCU interrupts Priority into groups and subgroups
 *                Enable NVIC Interrupt Gate for Peripherals
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "BIT_MATH.h"
#include "CORE_NVIC_Interface.h"
#include "MCAL_SPI_Private.h"
#include "MCAL_SPI_Config.h"
#include "MCAL_SPI_Interface.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

SPI_Cfg_t* Global_SPI_Config[2] = {NULL,NULL} ;

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void MCL_SPI_vMasterInit(SPI_Reg_t* SPIx, SPI_Cfg_t* Copy_SPI_Cfg)
{
	/* Set SPI GPIO Pins */
	MCL_SPI_vSetGPIOPins(SPIx);
	//enable SPI clock
	if(SPIx == SPI1)
	{	RCC_SPI1_CLOCK_EN(); }
	else if((SPIx == SPI2))
	{RCC_SPI2_CLOCK_EN(); }

	/*1. Set the DFF bit to define 8- or 16-bit data frame format*/
	ASSIGN_PARAM(SPIx->SPI_CR1, Copy_SPI_Cfg->Frame_Size);
	/*2. Select the Clock phase and clock polarity*/
	ASSIGN_PARAM(SPIx->SPI_CR1, Copy_SPI_Cfg->Clock_Phase);
	ASSIGN_PARAM(SPIx->SPI_CR1, Copy_SPI_Cfg->Clock_Polarity);
	/*3. The frame format (MSB-first or LSB-first)*/
	ASSIGN_PARAM(SPIx->SPI_CR1, Copy_SPI_Cfg->Frame_Format);
	/*4. Select Hardware mode (refer to Slave select (NSS) pin management) */
	if(Copy_SPI_Cfg->NSS_Management==NSS_MANAGEMENT_SW_SSI_SET||Copy_SPI_Cfg->NSS_Management==NSS_MANAGEMENT_SW_SSI_RESET)
	{ASSIGN_PARAM(SPIx->SPI_CR1, Copy_SPI_Cfg->NSS_Management);}
	else if(Copy_SPI_Cfg->NSS_Management==NSS_MANAGEMENT_HW_MSTR_SSOUT)
		{ASSIGN_PARAM(SPIx->SPI_CR2, Copy_SPI_Cfg->NSS_Management);}
	/*5. select the TI mode protocol for serial communications.*/
	ASSIGN_PARAM(SPIx->SPI_CR1, Copy_SPI_Cfg->Transfer_Mode);

	//enable NVIC for SPI IRQ
	ASSIGN_PARAM(SPIx->SPI_CR2, Copy_SPI_Cfg->IRQ_State);
	if(Copy_SPI_Cfg->IRQ_State != SPI_IRQ_DISABLE)
	{
		if(SPIx == SPI1)
		{COR_NVIC_vEnableInterrupt(SPI1_IRQn); }
		else if((SPIx == SPI2))
		{COR_NVIC_vEnableInterrupt(SPI2_IRQn); }
	}

	/*6.Assign the pins to alternate functions. Clear the MSTR bit and set the SPE bit (both in the SPI_CR1 register) */
	ASSIGN_PARAM(SPIx->SPI_CR1, Copy_SPI_Cfg->SPI_Mode);
	SET_BITFIELD(SPIx->SPI_CR1_Bits.SPE);



}

void MCL_SPI_vSetGPIOPins(SPI_Reg_t* SPIx){

	GPIO_Cfg_t SPI_PinConfig;

	if(SPIx == SPI1)
	{

		//=========MASTER========//
		if(Global_SPI_Config[SPI1_INDEX]->SPI_Mode == SPI_MASTER_MODE){

			//	SPIx_SCK -> PA5

			SPI_PinConfig.GPIO_Mode = GPIO_MODE_AF_OUT_PP;
			SPI_PinConfig.GPIO_Speed = GPIO_SPEED_MEDIUM;
			MCL_GPIO_vSetPinCfg (SPI1_PORT, SPI1_SCLK_PIN,&SPI_PinConfig);
			//	SPIx_MISO -> PA6
			SPI_PinConfig.GPIO_Mode = GPIO_MODE_IN_FLOAT;
			MCL_GPIO_vSetPinCfg (SPI1_PORT, SPI1_MISO_PIN, &SPI_PinConfig);
			//SPIx_MOSI -> PA7
			SPI_PinConfig.GPIO_Mode = GPIO_MODE_AF_OUT_PP;
			SPI_PinConfig.GPIO_Speed = GPIO_SPEED_MEDIUM;
			MCL_GPIO_vSetPinCfg (SPI1_PORT, SPI1_MOSI_PIN, &SPI_PinConfig);
			//SPIx_NSS -> PA4
			if(Global_SPI_Config[SPI1_INDEX]->NSS_Management == NSS_MANAGEMENT_HW_MSTR_SSIN){

				SPI_PinConfig.GPIO_Mode = GPIO_MODE_IN_FLOAT;
				MCL_GPIO_vSetPinCfg (SPI1_PORT, SPI1_SSEL_PIN, &SPI_PinConfig);
			}
			else if (Global_SPI_Config[SPI1_INDEX]->NSS_Management == NSS_MANAGEMENT_HW_MSTR_SSOUT){
				//	SPI1_RTS PA12
				SPI_PinConfig.GPIO_Mode = GPIO_MODE_AF_OUT_PP;
				SPI_PinConfig.GPIO_Speed = GPIO_SPEED_MEDIUM;
				MCL_GPIO_vSetPinCfg (SPI1_PORT, SPI1_SSEL_PIN, &SPI_PinConfig);
			}
		}
		//=========SLAVE========//
		else if(Global_SPI_Config[SPI1_INDEX]->SPI_Mode == SPI_SLAVE_MODE){
			//	SPIx_SCK -> PA5
			SPI_PinConfig.GPIO_Mode = GPIO_MODE_IN_FLOAT;
			MCL_GPIO_vSetPinCfg (SPI1_PORT,SPI1_SCLK_PIN,&SPI_PinConfig);
			//	SPIx_MISO -> PA6
			SPI_PinConfig.GPIO_Mode = GPIO_MODE_AF_OUT_PP;
			SPI_PinConfig.GPIO_Speed = GPIO_SPEED_MEDIUM;
			MCL_GPIO_vSetPinCfg (SPI1_PORT,SPI1_MISO_PIN,&SPI_PinConfig);
			//SPIx_MOSI -> PA7
			SPI_PinConfig.GPIO_Mode = GPIO_MODE_IN_FLOAT;
			MCL_GPIO_vSetPinCfg (SPI1_PORT,SPI1_MOSI_PIN,&SPI_PinConfig);
			//SPIx_NSS -> PA4
			if(Global_SPI_Config[SPI1_INDEX]->NSS_Management == NSS_MANAGEMENT_HW_SLV){

				SPI_PinConfig.GPIO_Mode = GPIO_MODE_IN_FLOAT;
				MCL_GPIO_vSetPinCfg (SPI1_PORT,SPI1_SSEL_PIN,&SPI_PinConfig);
			}

		}
	}
	if(SPIx == SPI2)
	{

		//=========MASTER========//
		if(Global_SPI_Config[SPI2_INDEX]->SPI_Mode == SPI_MASTER_MODE){

			//	SPIx_SCK -> PA13
			SPI_PinConfig.GPIO_Mode = GPIO_MODE_AF_OUT_PP;
			SPI_PinConfig.GPIO_Speed = GPIO_SPEED_MEDIUM;
			MCL_GPIO_vSetPinCfg (SPI2_PORT, SPI2_SCLK_PIN,&SPI_PinConfig);
			//	SPIx_MISO -> PA14
			SPI_PinConfig.GPIO_Mode = GPIO_MODE_IN_FLOAT;
			MCL_GPIO_vSetPinCfg (SPI2_PORT,SPI2_MISO_PIN, &SPI_PinConfig);
			//SPIx_MOSI -> PA15
			SPI_PinConfig.GPIO_Mode = GPIO_MODE_AF_OUT_PP;
			SPI_PinConfig.GPIO_Speed = GPIO_SPEED_MEDIUM;
			MCL_GPIO_vSetPinCfg (SPI2_PORT,SPI2_MOSI_PIN,&SPI_PinConfig);
			//SPIx_NSS -> PA2
			if(Global_SPI_Config[SPI2_INDEX]->NSS_Management == NSS_MANAGEMENT_HW_MSTR_SSIN){

				SPI_PinConfig.GPIO_Mode = GPIO_MODE_IN_FLOAT;
				MCL_GPIO_vSetPinCfg (SPI2_PORT,SPI2_SSEL_PIN,&SPI_PinConfig);
			}
			else if (Global_SPI_Config[SPI2_INDEX]->NSS_Management == NSS_MANAGEMENT_HW_MSTR_SSOUT){

				SPI_PinConfig.GPIO_Mode = GPIO_MODE_AF_OUT_PP;
				SPI_PinConfig.GPIO_Speed = GPIO_SPEED_MEDIUM;
				MCL_GPIO_vSetPinCfg (SPI2_PORT,SPI2_SSEL_PIN,&SPI_PinConfig);
			}
		}
		//=========SLAVE========//
		else if(Global_SPI_Config[SPI2_INDEX]->SPI_Mode == SPI_SLAVE_MODE){
			//	SPIx_SCK -> PA13
			SPI_PinConfig.GPIO_Mode = GPIO_MODE_IN_FLOAT;
			MCL_GPIO_vSetPinCfg (SPI2_PORT,SPI2_SCLK_PIN,&SPI_PinConfig);
			//	SPIx_MISO -> PA14
			SPI_PinConfig.GPIO_Mode = GPIO_MODE_AF_OUT_PP;
			MCL_GPIO_vSetPinCfg (SPI2_PORT,SPI2_MISO_PIN,&SPI_PinConfig);
			//SPIx_MOSI -> PA15
			SPI_PinConfig.GPIO_Mode = GPIO_MODE_IN_FLOAT;
			MCL_GPIO_vSetPinCfg (SPI2_PORT,SPI2_MOSI_PIN,&SPI_PinConfig);
			//SPIx_NSS -> PA12
			if(Global_SPI_Config[SPI2_INDEX]->NSS_Management == NSS_MANAGEMENT_HW_MSTR_SSIN){

				SPI_PinConfig.GPIO_Mode = GPIO_MODE_IN_FLOAT;
				MCL_GPIO_vSetPinCfg (SPI2_PORT,SPI2_SSEL_PIN,&SPI_PinConfig);
			}

		}
	}
}
void MCL_SPI_vMasterTransmit(SPI_Reg_t * SPIx, u16 *Copy_pTxBuffer,Polling_Mechanism_t Copy_PollingState)
{
	// Activate slave
	if(SPIx->SPI_CR1_Bits.SSM){SPI_vSlaveSignal (SPIx,PIN_RESET);}
	//wait until TXE flag is set
	if (Copy_PollingState == SPI_POLLING_ENABLE)
		while(! SPIx->SPI_SR_Bits.TXE );
	/* Put data into buffer, sends the data */
	SPIx->SPI_DR = *Copy_pTxBuffer;

	 // Deactivate slave
	if(SPIx->SPI_CR1_Bits.SSM){SPI_vSlaveSignal (SPIx,PIN_SET);}
}
void MCL_SPI_vSlaveTransmit(SPI_Reg_t * SPIx, u16 *Copy_pTxBuffer,Polling_Mechanism_t Copy_PollingState)
{


	//wait until TXE flag is set
	if (Copy_PollingState == SPI_POLLING_ENABLE)
		while(! SPIx->SPI_SR_Bits.TXE );
	/* Put data into buffer, sends the data */
	SPIx->SPI_DR = *Copy_pTxBuffer;

}
void MCL_SPI_vMasterReceive(SPI_Reg_t * SPIx, u16 *Copy_pRxBuffer,Polling_Mechanism_t Copy_PollingState)
{

	 // Activate slave
	if(SPIx->SPI_CR1_Bits.SSM){SPI_vSlaveSignal (SPIx,PIN_RESET);}

	/* Wait for transfer to complete */
	//wait until RXNE flag is set
	if (Copy_PollingState == SPI_POLLING_ENABLE)
		while(! SPIx->SPI_SR_Bits.RXNE );


	/* Get and return received data from buffer */
	*Copy_pRxBuffer = SPIx->SPI_DR;

	 // Deactivate slave
	if(SPIx->SPI_CR1_Bits.SSM){SPI_vSlaveSignal (SPIx,PIN_SET);}

}

void MCL_SPI_vSlaveReceive(SPI_Reg_t * SPIx, u16 *Copy_pRxBuffer,Polling_Mechanism_t Copy_PollingState)
{

	/* Wait for data to be received */
	//wait until RXNE flag is set
	if (Copy_PollingState == SPI_POLLING_ENABLE)
		while(! SPIx->SPI_SR_Bits.RXNE );

	/* Get and return received data from buffer */
	*Copy_pRxBuffer = SPIx->SPI_DR;

}

static void SPI_vSlaveSignal(SPI_Reg_t* SPIx,Pin_State_t Copy_SSPinState)
{
	if (SPIx == SPI1)
	{MCL_GPIO_vDirectPinSetter(SPI1_PORT, SPI1_SSEL_PIN, Copy_SSPinState);}
	else if (SPIx == SPI2)
		MCL_GPIO_vDirectPinSetter(SPI2_PORT, SPI2_SSEL_PIN, Copy_SSPinState);

}

static SPI_Index_t SPI_xSelectIndex(SPI_Reg_t* SPIx)
{
	SPI_Index_t Local_SpiIndex;
	if (SPIx == SPI1)
	{Local_SpiIndex = SPI1_INDEX;}
	else if (SPIx == SPI2)
		Local_SpiIndex = SPI2_INDEX;
	else if (SPIx == SPI3)
		Local_SpiIndex = SPI3_INDEX;
	else
		Local_SpiIndex = SPI1_INDEX;

	return ((SPI_Index_t)(Local_SpiIndex));

}




/**********************************************************************************************************************
 *  END OF FILE: MCAL_SPI_Program.c
 *********************************************************************************************************************/


