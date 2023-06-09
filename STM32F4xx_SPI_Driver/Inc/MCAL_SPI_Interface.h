/*
 * SPI_Interface.h
 *
 * Created: 4/17/2023 5:52:21 PM
 *  Author: Ahmed Aboraya
 */


#ifndef MCAL_SPI_INTERFACE_H_
#define MCAL_SPI_INTERFACE_H_
//-----------------------------
//Includes
//-----------------------------
#include "MCAL_GPIO_Interface.h"
#include "MCAL_RCC_Interface.h"
#include "MCAL_SPI_Private.h"

//====================================
//=============MACROS=================
//====================================


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
#define RCC_SPI1_CLOCK_EN()			MCL_RCC_vEnablePeriphClk(APB2_BUS, BIT12)
#define RCC_SPI2_CLOCK_EN()			MCL_RCC_vEnablePeriphClk(APB1_BUS, BIT14)

#define RCC_SPI1_CLOCK_DIS()		MCL_RCC_vDisablePeriphClk(APB2_BUS, BIT12)
#define RCC_SPI2_CLOCK_DIS()		MCL_RCC_vDisablePeriphClk(APB1_BUS, BIT14)



/*************************************
* DataTypes
*************************************/


//@ref SPI_IRQ_Src_define
typedef struct {
	u8 	    SPI_TXE:1;		//TX Buffer is Empty
	u8		SPI_RXNE:1;		//RX Buffer is Not Empty
	u8		SPI_ERRI:1;		//Error interrupt
	u8		:5;
}SPI_IRQ_Src;

typedef enum
{
    SPI_SLAVE_MODE  =  ~(1<<2),
    SPI_MASTER_MODE = (u16) (1<<2),
}SPI_Mode_t;

typedef enum
{
  FRAME_FORMAT_MSB_FIRST		=		 ~(1<<7),
  FRAME_FORMAT_LSB_FIRST		=		(u16) (1<<7),
}SPI_FrameFormat_t;

typedef enum
{
    //@ref Frame_Size_define
    FRAME_SIZE_8BIT			=		 ~(1<<11),
    FRAME_SIZE_16BIT		=		(u16) (1<<11),
}SPI_FrameSize_t;

typedef enum
{
	//@ref Data_Communication_Mode_define
    DATA_MODE_UNIDI_FULL_DUPLEX	    =	 ~((1<<10) | (1<<14) | (1<<15)),
    DATA_MODE_UNIDI_RECEIVE_ONLY	=	(u16) (1<<10),
    DATA_MODE_BIDI_RECEIVE_ONLY	    =	(u16) (1<<15),
    DATA_MODE_BIDI_TRANSMIT_ONLY	=	(u16) (1<<15) | (1<<14),

}SPI_DataMode_t;

typedef enum
{
    //@ref Clock_Polarity_define
    CLOCK_POLARITY_IDLE_LOW	        =	   	 ~(1<<1),
    CLOCK_POLARITY_IDLE_HIGH	    =	   (u16) (1<<1)

}SPI_ClkPol_t;

typedef enum
{
//@ref Clock_Phase_define
    CLOCK_PHASE_FIRST_CAPTURE		=	 ~(1<<0),
    CLOCK_PHASE_SECOND_CAPTURE		=	(u16) (1<<0)
}SPI_ClkPhase_t;

typedef enum
{

    //@ref NSS_Management_define
    //HARDWARE (SPI_CR2 Register)
    NSS_MANAGEMENT_HW_SLV			    =	 ~((1<<2)),
    NSS_MANAGEMENT_HW_MSTR_SSOUT	    =	(u16) (1<<2),	//cannot work in a MultiMaster environment
    NSS_MANAGEMENT_HW_MSTR_SSIN	        =	 ~(1<<2) | ~(1<<9),			//the cell can work in multimaster configuration
    //SOFTWARE(NSS is driven by software for master or slave)
    //(SPI_CR1 Register)
    NSS_MANAGEMENT_SW_SSI_SET		    =	(u16) ((1<<9) | (1<<8)),
    NSS_MANAGEMENT_SW_SSI_RESET 	    =	(u16) (1<<9)

}SPI_NSSManage_t;

typedef enum
{
    // @ref BaudRate_Prescalar_define
    BAUDRATE_PCLCK_PRESCALAR_2			=		 ~(1<<3),
    BAUDRATE_PCLCK_PRESCALAR_4			=		(u16) (1<<3),
    BAUDRATE_PCLCK_PRESCALAR_8			=		(u16) (2<<3),
    BAUDRATE_PCLCK_PRESCALAR_16		    =		(u16) (3<<3),
    BAUDRATE_PCLCK_PRESCALAR_32		    =		(u16) (4<<3),
    BAUDRATE_PCLCK_PRESCALAR_64		    =		(u16) (5<<3),
    BAUDRATE_PCLCK_PRESCALAR_128	    =		(u16) (6<<3),
    BAUDRATE_PCLCK_PRESCALAR_256	    =		(u16) (7<<3),

}SPI_BaudRate_t;

typedef enum
{
    SPI_IRQ_DISABLE				=	     ~(7<<5),			// IRQ Disable
    SPI_IRQ_ENABLE_TXEIE		=		(u16) (1<<7),		// TX buffer empty interrupt enable
    SPI_IRQ_ENABLE_RXNEIE		=		(u16) (1<<6),		// RX buffer not empty interrupt enable
    SPI_IRQ_ENABLE_ERRIE		=		(u16) (1<<5),		// Error interrupt enable
}SPI_IRQState_t;
typedef enum
{
	SPI_POLLING_DIASBLE,
	SPI_POLLING_ENABLE
}Polling_Mechanism_t;

typedef struct
{
    SPI_Mode_t  SPI_Mode;

    SPI_FrameFormat_t Frame_Format;			//specifies Data be shifted out either MSB-first or LSB-first
	//@ref Frame_Format_define

	SPI_FrameSize_t Frame_Size;			//specifies the size of the data programmed 8-bit or 16_bit
	//@ref Frame_Size_define

	SPI_DataMode_t Transfer_Mode;	//specifies SPI Communication mode
	//@ref Data_Communication_Mode_define

	SPI_ClkPol_t Clock_Polarity;		// specifies SPI clock Polarity idle on low or idle on high
	//@ref Clock_Polarity_define

	SPI_ClkPhase_t Clock_Phase;			// specifies SPI clock Phase "first clock capture or second clock capture"
	//@ref Clock_Phase_define

	SPI_NSSManage_t NSS_Management;		// specifies slave select management by hardware or by software
	//@ref NSS_Management_define

	SPI_BaudRate_t BaudRate_Prescalar;		//  define the serial clock baud rate prescalar
	// @ref BaudRate_Prescalar_define

	SPI_IRQState_t IRQ_State;				// enable or disable SPI interrupt request
	// @ref IRQ_Enable_define

	void (*P_IRQ_CallBack)(SPI_IRQ_Src Curr_IRQ_Src);		//pointer to IRQ call back function which will be called once IRQ happened
	//specify the source of the IRQ @ref SPI_IRQ_Src_define

}SPI_Cfg_t;

/************************************
 * GLOBAL VARIABLES
*************************************/
extern SPI_Cfg_t SPI_Mstr_Config;

/************************************
 * Function Prototypes
*************************************/
void MCL_SPI_vMasterInit(SPI_Reg_t* SPIx, SPI_Cfg_t* Copy_SPI_Cfg);
void MCL_SPI_vSlaveInit(SPI_Reg_t* SPIx, SPI_Cfg_t* Copy_SPI_Cfg);
void MCL_SPI_vSetGPIOPins(SPI_Reg_t* SPIx);
void MCL_SPI_vMasterTransmit(SPI_Reg_t * SPIx, u16 *Copy_pTxBuffer,Polling_Mechanism_t Copy_PollingState);
void MCL_SPI_vMasterReceive(SPI_Reg_t * SPIx, u16 *Copy_pRxBuffer,Polling_Mechanism_t Copy_PollingState);

void MCL_SPI_vSlaveTransmit(SPI_Reg_t * SPIx, u16 *Copy_pTxBuffer,Polling_Mechanism_t Copy_PollingState);
void MCL_SPI_vSlaveReceive(SPI_Reg_t * SPIx, u16 *Copy_pRxBuffer,Polling_Mechanism_t Copy_PollingState);

void MCL_SPI_vTransmitReceive(SPI_Reg_t * SPIx, u16 *Copy_pBuffer,Polling_Mechanism_t Copy_PollingState);



#endif /* MCAL_SPI_INTERFACE_H_ */
