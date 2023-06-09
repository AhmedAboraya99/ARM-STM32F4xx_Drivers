#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MCAL_RCC_Interface.h"
#include "MCAL_RCC_Config.h"

#include "MCAL_GPIO_Interface.h"
#include "MCAL_GPIO_Config.h"

#include "MCAL_STK_Interface.h"
#include "HAL_STP_Interface.h"
#include "HAL_STP_Config.h"

#include "HAL_LEDMAT_Interface.h"
#include "HAL_LEDMAT_Config.h"

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

//u8 Global_u8AhmedMat[][8] = {{0, 0, 4, 7, 245, 5, 0, 0}, {32, 32, 32, 36, 36, 36, 36, 5}, {32, 32, 112, 136, 136, 112, 32, 32}, {0, 0, 36, 36, 36, 56, 32, 32}};
u8 Global_u8AhmedMat[][8] = {{28, 16, 60, 0, 8, 8, 8, 8}, {0, 0, 24, 36, 2, 254, 0, 0}, {0, 0, 0, 24, 36, 231, 36, 24}, {0, 0, 56, 4, 4, 63, 0, 0}};

/**********************************************************************************************************************
 *  FUNCTION PROTOTYPE
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  MAIN FUNCTION
 *********************************************************************************************************************/
void STP_LedMatrixTransition_App(void)
{
	u8 Local_u8TxData = 255;

	/* Step 1 : System Clock is 16 MHz from HSI */
	MCL_RCC_vInitSysClk(&RCC_GPIO_Config);

	MCL_STK_vInit(&STK_G_Config);

	/* Step 2 : Init GPIO STP Pins */
	HAL_STP_vInit(STP1);
	HAL_STP_vInit(STP2);


/* Loop forever */
	while(1){
		for(u8 Local_u8Step = 0; Local_u8Step < 4; Local_u8Step++)
		{
			for(u8 Local_u8Iter = 0; Local_u8Iter < 100; Local_u8Iter++)
			{
				for(u8 Local_u8Index = 0; Local_u8Index < LEDMARTIX_SIZE; Local_u8Index++)
				{
					Local_u8TxData = 255;
					/*Disable All Columns*/
					HAL_STP_vSendSynchronous(STP2, 255);
					/*Set Row Value*/
					HAL_STP_vSendSynchronous(STP1, Global_u8AhmedMat[Local_u8Step][Local_u8Index]);
					/*Enable Column */
					CLEAR_BIT(Local_u8TxData ,Local_u8Index);
					HAL_STP_vSendSynchronous(STP2, Local_u8TxData);
					MCL_STK_vSetBusyWait(2500);
				}
			}
			MCL_STK_vSetBusyWait(2000000);
		}
	}
}
