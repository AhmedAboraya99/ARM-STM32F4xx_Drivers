#include "STD_TYPES.h"

#include "MCAL_RCC_Interface.h"
#include "MCAL_RCC_Config.h"

#include "MCAL_GPIO_Interface.h"
#include "MCAL_GPIO_Config.h"

#include "MCAL_STK_Interface.h"
#include "HAL_STP_Interface.h"

#include "HAL_STP_Config.h"
/**********************************************************************************************************************
 *  FUNCTION PROTOTYPE
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  MAIN FUNCTION
 *********************************************************************************************************************/
void STP_LedsTransition_App(void)
{
	u8 Local_u8TxData = 255;

	/* Step 1 : System Clock is 16 MHz from HSI */
	MCL_RCC_vInitSysClk(&RCC_GPIO_Config);

	MCL_STK_vInit(&STK_G_Config);

	/* Step 2 : Init GPIO STP Pins */
	HAL_STP_vInit(STP2);

/* Loop forever */
	while(1){
		for(u8 Local_u8Step = 0; Local_u8Step < 10; Local_u8Step++)
		{
			HAL_STP_vSendSynchronous(STP2, Local_u8TxData<< Local_u8Step);
			MCL_STK_vSetBusyWait(1000000);
		}
	}
}
