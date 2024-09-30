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
* File Name        : Config_TAU0_3_user.c
* Component Version: 1.4.3
* Device(s)        : R5F121BCxFP
* Description      : This file implements device driver for Config_TAU0_3.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "Config_TAU0_3.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt r_Config_TAU0_3_interrupt(vect=INTTM03)
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* For TAU0_ch3 pulse measurement */
volatile uint32_t g_tau0_ch3_width = 0UL;
extern unsigned char comvar;
extern unsigned char confirmed;
unsigned char rightDetected = 0;
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_3_Create_UserInit
* Description  : This function adds user code after initializing the TAU0 channel3.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_3_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_TAU0_3_interrupt
* Description  : This function is INTTM03 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_Config_TAU0_3_interrupt(void)
{
    if (1U == (TSR03 & _0001_TAU_OVERFLOW_OCCURS))    /* overflow occurs */
    {
        g_tau0_ch3_width = (uint32_t)(TDR03 + 1UL) + 0x10000UL;
    }
    else
    {
        g_tau0_ch3_width = (uint32_t)(TDR03 + 1UL);
    }
    g_pulse_width1[4 - g_times1] = g_tau0_ch3_width;
    if((--g_times1) == 0)
    {
    	if(((g_pulse_width1[1] > 3000 && g_pulse_width1[1] < 4000) && (g_pulse_width1[2] > 2000 && g_pulse_width1[2] < 3000) && (g_pulse_width1[3] > 3000 && g_pulse_width1[3] < 4000))   ||  ((g_pulse_width1[1] > 2000 && g_pulse_width1[1] < 3000) && (g_pulse_width1[2] > 3000 && g_pulse_width1[2] < 4000) && (g_pulse_width1[3] > 2000 && g_pulse_width1[3] < 3000) ))
    	{
    		if(comvar)
    		{
    			confirmed = 1;
    		}
    		else
    		{
    			comvar = 1;
    			rightDetected = 1;
    			//timer start()
    			TMMK01 = 0U; //enable timer
    		}
    	}
    }
    /* Start user code for r_Config_TAU0_3_interrupt. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
