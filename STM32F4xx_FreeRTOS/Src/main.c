
#include "STD_TYPES.h"
#include "MCAL_RCC_Interface.h"
#include "MCAL_RCC_Private.h"
#include "MCAL_RCC_Config.c"

#include "MCAL_GPIO_Interface.h"
#include "MCAL_GPIO_Config.c"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
/* Functions ----------------------------------------------------------------*/
void LED_vTask1(void *pvParameters );
void LED_vTask2(void *pvParameters );
void LED_vTask3(void *pvParameters );
/* Data --------------------------------------------------------------------*/
SemaphoreHandle_t LED_Semaphore;

BaseType_t  LED_SemphState;
int main(void)
{

	MCL_GPIO_vSetPinCfg(LED_Port, LED1_Pin, &GPIO_LED_Config);
	MCL_GPIO_vSetPinCfg(LED_Port, LED2_Pin, &GPIO_LED_Config);
	MCL_GPIO_vSetPinCfg(LED_Port, LED3_Pin, &GPIO_LED_Config);
  /* Step 2 :Create 3 Tasks */
  xTaskCreate(LED_vTask1, "Task1", configMINIMAL_STACK_SIZE, NULL ,1, NULL);
  xTaskCreate(LED_vTask2, "Task2", configMINIMAL_STACK_SIZE, NULL ,2, NULL);
  xTaskCreate(LED_vTask3, "Task3", configMINIMAL_STACK_SIZE, NULL ,3, NULL);
  /* step 3: Create Semaphore*/
  vSemaphoreCreateBinary(LED_Semaphore);

  /* Step 4 :Start Schedular */
  vTaskStartScheduler();

  /* We should never reach here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */

}


void LED_vTask1(void *pvParameters )
{
	  while(1)
	    {
	        /* Task 1 code here */
		  	LED_SemphState = xSemaphoreTake(LED_Semaphore, 1100);
			MCL_GPIO_vTogglePin(GPIOB, LED1_Pin);
			LED_SemphState = xSemaphoreGive(LED_Semaphore);
			vTaskDelay(1000);
	    }
}
void LED_vTask2(void *pvParameters )
{
	  while(1)
	    {
	        /* Task 2 code here */
		  LED_SemphState = xSemaphoreTake(LED_Semaphore, 1100);
		  MCL_GPIO_vTogglePin(GPIOB, LED2_Pin);
		  LED_SemphState = xSemaphoreGive(LED_Semaphore);
		  vTaskDelay(1000);
	    }
}
void LED_vTask3(void *pvParameters )
{
	while(1)
	{
		/* Task 3 code here */
		LED_SemphState = xSemaphoreTake(LED_Semaphore, 1100);
		MCL_GPIO_vTogglePin(GPIOB, LED3_Pin);
		vTaskDelay(1000);
		LED_SemphState = xSemaphoreGive(LED_Semaphore);
	}

}

