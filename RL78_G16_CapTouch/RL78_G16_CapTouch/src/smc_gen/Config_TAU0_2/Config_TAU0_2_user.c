/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2021, 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : Config_TAU0_2_user.c
* Component Version: 1.5.0
* Device(s)        : R5F121BCxFP
* Description      : This file implements device driver for Config_TAU0_2.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "Config_TAU0_2.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt r_Config_TAU0_2_interrupt(vect=INTTM02)
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* For TAU0_ch2 pulse measurement */
volatile uint32_t g_tau0_ch2_width = 0UL;
/* Start user code for global. Do not edit comment generated here */
//extern unsigned char comvar;
//extern unsigned char confirmed;
//extern unsigned char leftDetected;
//extern unsigned char rightDetected;
extern __saddr unsigned int g_pulse_width[4];    /* Store pulse width */
extern unsigned char g_times;                      /* Measurement times counter */

extern unsigned char status[2];
extern unsigned char index;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_2_Create_UserInit
* Description  : This function adds user code after initializing the TAU0 channel2.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_2_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_TAU0_2_interrupt
* Description  : This function is INTTM02 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_Config_TAU0_2_interrupt(void)
{
    if (1U == (TSR02 & _0001_TAU_OVERFLOW_OCCURS))    /* overflow occurs */
    {
        g_tau0_ch2_width = (uint32_t)(TDR02 + 1UL) + 0x10000UL;
    }
    else
    {
        g_tau0_ch2_width = (uint32_t)(TDR02 + 1UL);
    }
    g_pulse_width[4U - g_times] = g_tau0_ch2_width;



	if (0U == ( --g_times))        /* 8 times measurement finished ? */
	{
		R_Config_TAU0_2_Stop();    /* Stops timer counter */
	}
//	if(g_times==0)
//	{
//		if(((g_pulse_width[0] > 3000 && g_pulse_width[0] < 4000)  &&  (g_pulse_width[1] >2000 && g_pulse_width[1] < 3000)  &&  (g_pulse_width[0] > 3000 && g_pulse_width[0] < 4000) )  ||   ((g_pulse_width[0] > 2000 && g_pulse_width[0] < 3000)  &&  (g_pulse_width[1] >3000 && g_pulse_width[1] < 4000)  &&  (g_pulse_width[0] > 2000 && g_pulse_width[0] < 3000)))
//		{
//			uart_integer(1);
//			R_BSP_SoftwareDelay(100,BSP_DELAY_MILLISECS);
//			if(comvar)
//			{
//				confirmed = 1;
//			}
//			else
//			{
//				comvar = 1;
//				leftDetected = 1;
//				//timer enable
//				R_Config_TAU0_1_Start();
//				EI();
//			}
//		}
//		g_times = 4;
//    }

        	if(g_times==0)
        	{
//        		for(int i=0;i<4;i++)
//        		    {
        		    	uart_integer(1);
        		    	R_BSP_SoftwareDelay(100,BSP_DELAY_MILLISECS);
//        		    }
        		if((g_pulse_width[1] > 3000 && g_pulse_width[2] > 2000 && g_pulse_width[3] > 3000)   ||  (g_pulse_width[1] > 2000 && g_pulse_width[2] > 3000 && g_pulse_width[3] > 2000 ))
        		{
        			status[index]='L';
        			++index;
        		}
        		R_Config_TAU0_1_Start();
        		EI();
        	}
    /* Start user code for r_Config_TAU0_2_interrupt. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
