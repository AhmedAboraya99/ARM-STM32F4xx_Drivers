#include "STD_TYPES.h"
#include "MCAL_RCC_Interface.h"
#include "MCAL_RCC_Private.h"
#include "MCAL_RCC_Config.c"

#include "MCAL_GPIO_Interface.h"
#include "MCAL_GPIO_Config.c"

#include "MCAL_EXTI_Interface.h"

#include "MCAL_STK_Interface.h"

/**********************************************************************************************************************
 *  FUNCTION PROTOTYPE
 *********************************************************************************************************************/

void Blink_EXTI0CallBack(void);
void Blink_EXTI1CallBack(void);
/**********************************************************************************************************************
 *  MAIN FUNCTION
 *********************************************************************************************************************/

void EXTI_NestedApp()
{
  // At this stage the system clock should have already been configured
  // at high speed.

	MCL_RCC_vInitSysClk(&RCC_GPIO_Config);
	MCL_STK_vInit(&STK_G_Config);
	EXTI_G_Cfg[EXTI0].IRQ_pCallBack = Blink_EXTI0CallBack;
	MCL_EXTI_vInit(&EXTI_G_Cfg[EXTI0]);

	EXTI_G_Cfg[EXTI1].IRQ_pCallBack = Blink_EXTI1CallBack;
	MCL_EXTI_vInit(&EXTI_G_Cfg[EXTI1]);

    MCL_STK_vSetBusyWait(1000);

   	MCL_GPIO_vSetPinCfg(GPIOB, GPIO_PIN0, &GPIO_LED_Config);
   	MCL_GPIO_vSetPinCfg(GPIOB, GPIO_PIN1, &GPIO_LED_Config);

	/* Loop forever */
	while(1){

	}
}



// ----------------------------------------------------------------------------

void Blink_EXTI0CallBack(void)
{

	MCL_GPIO_vTogglePin(GPIOB, GPIO_PIN0);
}

void Blink_EXTI1CallBack(void)
{

	MCL_GPIO_vTogglePin(GPIOB, GPIO_PIN1);
	while(MCL_GPIO_u8GetPinVal(GPIOA, GPIO_PIN1));
}

