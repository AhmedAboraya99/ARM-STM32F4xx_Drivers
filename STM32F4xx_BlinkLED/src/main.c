
// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.

#include "STD_TYPES.h"
#include "MCAL_RCC_Interface.h"
#include "MCAL_RCC_Private.h"
#include "MCAL_RCC_Config.c"

#include "MCAL_GPIO_Interface.h"
#include "MCAL_GPIO_Config.c"

#include "MCAL_STK_Interface.h"

void APP_voidDelay(u32 Copy_32Delay);

int main()
{
  // At this stage the system clock should have already been configured
  // at high speed.

	MCAL_RCC_vInitSysClk(&RCC_GPIO_Config);
	MCA_STK_vInit(&STK_G_Config);

	MCA_GPIO_vSetPinCfg(GPIOA, GPIO_PIN0, &GPIO_LED_Config);
  // Infinite loop
  while (1)
    {
       MCA_GPIO_vDirectPinSetter(GPIOA, GPIO_PIN0, PIN_SET);
       MCA_STK_vSetBusyWait(1000000);	//1 second
       //APP_voidDelay(500);
       MCA_GPIO_vDirectPinSetter(GPIOA, GPIO_PIN0, PIN_RESET);
       MCA_STK_vSetBusyWait(1000000);	//1 second
       //APP_voidDelay(500);
    }
}


void APP_voidDelay(u32 Copy_32Delay)
{
	for(u32 i = 0; i < Copy_32Delay * 255; i++)
	{
		asm("NOP");
	}
}


// ----------------------------------------------------------------------------
