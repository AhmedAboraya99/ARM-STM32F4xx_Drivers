/*
 * MCA_RTO_Program.c
 *
 *  Created on: May 10, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STD_TYPES.h"
#include "SRV_RTO_Interface.h"
#include "SRV_RTO_Private.h"
#include "SRV_RTO_Config.h"
#include "MCAL_STK_Interface.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

RTO_TCB_t RTO_pxTaskStatus[NUM_OF_TASKS];
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  CONFIGURATIONS ASSIGNMENT
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
void SRV_RTO_vStartOS()
{
	STK_G_Config.Systick_CallBackPtr = &RTO_vSchedular;
    MCL_STK_vInit(&STK_G_Config);
    MCL_STK_vSetIntervalPeriodic(1000, STK_G_Config.Systick_CallBackPtr);
}

static void RTO_vSchedular()
{
    u8 Local_u8Count = 0;
    for(Local_u8Count = 0;Local_u8Count < NUM_OF_TASKS; Local_u8Count++)
    {
    //u32 Local_u8Period = RTO_pxTaskStatus[Local_u8Count].First_Delay;
        if((RTO_pxTaskStatus[Local_u8Count].First_Delay ==0)  && (RTO_pxTaskStatus[Local_u8Count].Pf != NULL))
        {
            RTO_pxTaskStatus[Local_u8Count].Pf();
            RTO_pxTaskStatus[Local_u8Count].First_Delay = (RTO_pxTaskStatus[Local_u8Count].Periodicity) - 1;
        }else{
            RTO_pxTaskStatus[Local_u8Count].First_Delay--;

        }
    }
}


void SRV_RTO_vCreateTask(u8 Copy_u8Priority, u32 Copy_u32Periodicity, u32 Copy_u32FirstDelay, void (*pfnTask)(void))
{

        if(RTO_pxTaskStatus[Copy_u8Priority].Pf == NULL)
        {
            RTO_pxTaskStatus[Copy_u8Priority].Pf = pfnTask;
            RTO_pxTaskStatus[Copy_u8Priority].Periodicity = Copy_u32Periodicity;
            RTO_pxTaskStatus[Copy_u8Priority].First_Delay = Copy_u32FirstDelay;
            RTO_pxTaskStatus[Copy_u8Priority].Priority = Copy_u8Priority;
        }

}
