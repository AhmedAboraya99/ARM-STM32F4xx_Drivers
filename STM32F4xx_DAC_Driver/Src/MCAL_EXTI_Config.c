/*
 * MCAL_EXTI_Config.c
 *
 *  Created on: May 10, 2023
 *      Author: ahmed
 */



/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "MCAL_EXTI_Interface.h"
#include "MCAL_EXTI_Config.h"
#include "CORE_NVIC_Interface.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  CONFIGURATIONS OPTIONS
 *********************************************************************************************************************/

#define EXTI0PA0		(EXTI_GPIO_Mapping_t){EXTI0, GPIOA, GPIO_PIN0, EXTI0_IRQn}
#define EXTI0PB0		(EXTI_GPIO_Mapping_t){EXTI0, GPIOB, GPIO_PIN0, EXTI0_IRQn}
#define EXTI0PC0		(EXTI_GPIO_Mapping_t){EXTI0, GPIOC, GPIO_PIN0, EXTI0_IRQn}

//EXTI1
 #define EXTI1PA1	(EXTI_GPIO_Mapping_t){EXTI1, GPIOA, GPIO_PIN1, EXTI1_IRQn}
 #define EXTI1PB1	(EXTI_GPIO_Mapping_t){EXTI1, GPIOB, GPIO_PIN1, EXTI1_IRQn}
 #define EXTI1PC1	(EXTI_GPIO_Mapping_t){EXTI1, GPIOC, GPIO_PIN1, EXTI1_IRQn}

 //EXTI2
 #define EXTI2PA2    (EXTI_GPIO_Mapping_t){EXTI2, GPIOA, GPIO_PIN2, EXTI2_IRQn}
 #define EXTI2PB2    (EXTI_GPIO_Mapping_t){EXTI2, GPIOB, GPIO_PIN2, EXTI2_IRQn}
 #define EXTI2PC2    (EXTI_GPIO_Mapping_t){EXTI2, GPIOC, GPIO_PIN2, EXTI2_IRQn}

 //EXTI3
 #define EXTI3PA3    (EXTI_GPIO_Mapping_t){EXTI3, GPIOA, GPIO_PIN3, EXTI3_IRQn}
 #define EXTI3PB3    (EXTI_GPIO_Mapping_t){EXTI3, GPIOB, GPIO_PIN3, EXTI3_IRQn}
 #define EXTI3PC3    (EXTI_GPIO_Mapping_t){EXTI3, GPIOC, GPIO_PIN3, EXTI3_IRQn}

 //EXTI4
 #define EXTI4PA4    (EXTI_GPIO_Mapping_t){EXTI4, GPIOA, GPIO_PIN4, EXTI4_IRQn}
 #define EXTI4PB4    (EXTI_GPIO_Mapping_t){EXTI4, GPIOB, GPIO_PIN4, EXTI4_IRQn}
 #define EXTI4PC4    (EXTI_GPIO_Mapping_t){EXTI4, GPIOC, GPIO_PIN4, EXTI4_IRQn}

 //EXTI5
 #define EXTI5PA5    (EXTI_GPIO_Mapping_t){EXTI5, GPIOA, GPIO_PIN5, EXTI9_5_IRQn}
 #define EXTI5PB5    (EXTI_GPIO_Mapping_t){EXTI5, GPIOB, GPIO_PIN5, EXTI9_5_IRQn}
 #define EXTI5PC5    (EXTI_GPIO_Mapping_t){EXTI5, GPIOC, GPIO_PIN5, EXTI9_5_IRQn}

 //EXTI6
 #define EXTI6PA6    (EXTI_GPIO_Mapping_t){EXTI6, GPIOA, GPIO_PIN6, EXTI9_5_IRQn}
 #define EXTI6PB6    (EXTI_GPIO_Mapping_t){EXTI6, GPIOB, GPIO_PIN6, EXTI9_5_IRQn}
 #define EXTI6PC6    (EXTI_GPIO_Mapping_t){EXTI6, GPIOC, GPIO_PIN6, EXTI9_5_IRQn}

 //EXTI7
 #define EXTI7PA7    (EXTI_GPIO_Mapping_t){EXTI7, GPIOA, GPIO_PIN7, EXTI9_5_IRQn}
 #define EXTI7PB7    (EXTI_GPIO_Mapping_t){EXTI7, GPIOB, GPIO_PIN7, EXTI9_5_IRQn}
 #define EXTI7PC7    (EXTI_GPIO_Mapping_t){EXTI7, GPIOC, GPIO_PIN7, EXTI9_5_IRQn}

 //EXTI8
 #define EXTI8PA8    (EXTI_GPIO_Mapping_t){EXTI8, GPIOA, GPIO_PIN8, EXTI9_5_IRQn}
 #define EXTI8PB8    (EXTI_GPIO_Mapping_t){EXTI8, GPIOB, GPIO_PIN8, EXTI9_5_IRQn}
 #define EXTI8PC8    (EXTI_GPIO_Mapping_t){EXTI8, GPIOC, GPIO_PIN8, EXTI9_5_IRQn}

 //EXTI9
 #define EXTI9PA9    (EXTI_GPIO_Mapping_t){EXTI9, GPIOA, GPIO_PIN9, EXTI9_5_IRQn}
 #define EXTI9PB9    (EXTI_GPIO_Mapping_t){EXTI9, GPIOB, GPIO_PIN9, EXTI9_5_IRQn}
 #define EXTI9PC9    (EXTI_GPIO_Mapping_t){EXTI9, GPIOC, GPIO_PIN9, EXTI9_5_IRQn}

 //EXTI10
 #define EXTI10PA10    (EXTI_GPIO_Mapping_t){EXTI10, GPIOA, GPIO_PIN10, EXTI15_10_IRQn}
 #define EXTI10PB10    (EXTI_GPIO_Mapping_t){EXTI10, GPIOB, GPIO_PIN10, EXTI15_10_IRQn}
 #define EXTI10PC10    (EXTI_GPIO_Mapping_t){EXTI10, GPIOC, GPIO_PIN10, EXTI15_10_IRQn}

 //EXTI11
 #define EXTI11PA11    (EXTI_GPIO_Mapping_t){EXTI11, GPIOA, GPIO_PIN11, EXTI15_10_IRQn}
 #define EXTI11PB11    (EXTI_GPIO_Mapping_t){EXTI11, GPIOB, GPIO_PIN11, EXTI15_10_IRQn}
 #define EXTI11PC11    (EXTI_GPIO_Mapping_t){EXTI11, GPIOC, GPIO_PIN11, EXTI15_10_IRQn}

 //EXTI12
 #define EXTI12PA12    (EXTI_GPIO_Mapping_t){EXTI12, GPIOA, GPIO_PIN12, EXTI15_10_IRQn}
 #define EXTI12PB12    (EXTI_GPIO_Mapping_t){EXTI12, GPIOB, GPIO_PIN12, EXTI15_10_IRQn}
 #define EXTI12PC12    (EXTI_GPIO_Mapping_t){EXTI12, GPIOC, GPIO_PIN12, EXTI15_10_IRQn}

 //EXTI13
 #define EXTI13PA13    (EXTI_GPIO_Mapping_t){EXTI13, GPIOA, GPIO_PIN13, EXTI15_10_IRQn}
 #define EXTI13PB13    (EXTI_GPIO_Mapping_t){EXTI13, GPIOB, GPIO_PIN13, EXTI15_10_IRQn}
 #define EXTI13PC13    (EXTI_GPIO_Mapping_t){EXTI13, GPIOC, GPIO_PIN13, EXTI15_10_IRQn}

 //EXTI14
 #define EXTI14PA14    (EXTI_GPIO_Mapping_t){EXTI14, GPIOA, GPIO_PIN14, EXTI15_10_IRQn}
 #define EXTI14PB14    (EXTI_GPIO_Mapping_t){EXTI14, GPIOB, GPIO_PIN14, EXTI15_10_IRQn}
 #define EXTI14PC14    (EXTI_GPIO_Mapping_t){EXTI14, GPIOC, GPIO_PIN14, EXTI15_10_IRQn}

 //EXTI15
 #define EXTI15PA15    (EXTI_GPIO_Mapping_t){EXTI15, GPIOA, GPIO_PIN15, EXTI15_10_IRQn}
 #define EXTI15PB15    (EXTI_GPIO_Mapping_t){EXTI15, GPIOB, GPIO_PIN15, EXTI15_10_IRQn}
 #define EXTI15PC15    (EXTI_GPIO_Mapping_t){EXTI15, GPIOC, GPIO_PIN15, EXTI15_10_IRQn}


EXTI_PinCfg_t EXTI_G_Cfg[] = {
	{.EXTI_PinMap = EXTI0PA0,
	.EXTI_Priority = {Group8_2Sub,0, 0},
	.Trigger_State = EXTI_FALLING_EDGE,
	.IRQ_EN = NVIC_IRQ_ENABLE,
	},
	{.EXTI_PinMap = EXTI1PA1,
	.EXTI_Priority = {Group8_2Sub,1, 0},
	.Trigger_State = EXTI_RISING_EDGE,
	.IRQ_EN = NVIC_IRQ_ENABLE,
	},
	{.EXTI_PinMap = EXTI2PA2,
	.EXTI_Priority = {Group8_2Sub,2, 0},
    .Trigger_State = EXTI_RISING_EDGE,
    .IRQ_EN = NVIC_IRQ_ENABLE,
    },
	
};

/**********************************************************************************************************************
 *  CONFIGURATIONS ASSIGNMENT
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


