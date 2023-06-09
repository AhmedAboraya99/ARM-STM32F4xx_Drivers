/*
 * SPI_Private.h
 *
 *  Created on: Mar 27, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  SPI_Private.h
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>
 *
 *********************************************************************************************************************/
#ifndef MCAL_SPI_PRIVATE_H_
#define MCAL_SPI_PRIVATE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "STM32F4xx_Device_Header.h"
/**********************************************************************************************************************
 *  PRIVATE CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef struct {
    volatile union {
        struct{
            vu32  CPHA : 1;
            vu32  CPOL : 1;
            vu32  MSTR : 1;
            vu32  BR  : 3;
            vu32  SPE : 1;
            vu32  LSBFIRST : 1;
            vu32  SSI : 1;
            vu32  SSM : 1;
            vu32  RXONLY : 1;
            vu32  DFF : 1;
            vu32  CRCNEXT : 1;
            vu32  CRCEN : 1;
            vu32  BIDIOE : 1;
            vu32  BIDIMODE : 1;
        }SPI_CR1_Bits;
    vu32 SPI_CR1;
    };
    volatile union {
        struct
        {
            vu32  RXDMAEN: 1;
            vu32  TXDMAEN: 1;
            vu32  SSOE: 1;
            u32  : 1;
            vu32  FRF: 1;
            vu32  ERRIE: 1;
            vu32  RXNEIE: 1;
            vu32  TXEIE  : 1;
        }SPI_CR2_Bits;
	vu32 SPI_CR2;
    };
    volatile union {
        struct
        {
            vu32  RXNE : 1;
            vu32  TXE : 1;
            vu32  CHSIDE : 1;
            vu32  UDR : 1;
            vu32  CRCERR : 1;
            vu32  MODF : 1;
            vu32  OVR : 1;
            vu32  BSY : 1;
            vu32  TIFRFE : 1;
        }SPI_SR_Bits;
        vu32 SPI_SR;
    };
	vu32 SPI_DR;
	vu32 SPI_CRCPR;
	vu32 SPI_RXCRCR;
	vu32 SPI_TXCRCR;
	vu32 SPI_I2SCFGR;
	vu32 SPI_I2SPR;
}SPI_Reg_t;


#define SPI1         ((SPI_Reg_t *) SPI1_BASE)
#define SPI2         ((SPI_Reg_t *) SPI2_BASE)
#define SPI3         ((SPI_Reg_t *) SPI3_BASE)



/**********************************************************************************************************************
 *  PRIVATE FUNCTION PROTOTYPES
 *********************************************************************************************************************/
static void SPI_vSlaveSignal(SPI_Reg_t* SPIx,Pin_State_t Copy_SSPinState);
static SPI_Index_t SPI_xSelectIndex(SPI_Reg_t* SPIx);

#endif /* MCAL_SPI_PRIVATE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: SPI.h
 *********************************************************************************************************************/


