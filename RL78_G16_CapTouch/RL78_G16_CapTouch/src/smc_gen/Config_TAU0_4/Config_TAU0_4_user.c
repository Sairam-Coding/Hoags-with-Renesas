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
* File Name        : Config_TAU0_4_user.c
* Component Version: 1.5.0
* Device(s)        : R5F121BCxFP
* Description      : This file implements device driver for Config_TAU0_4.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "Config_TAU0_4.h"


/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt r_Config_TAU0_4_interrupt(vect=INTTM04)
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
	unsigned char timer_counter4=0;
	unsigned char seconds=0;
	unsigned char timer_flag=0;
	unsigned char autoclean_time=9;

	extern void LED_One(void);
	extern void LED_Two(void);
	extern void LED_Three(void);
	extern void LED_Four(void);
	extern void LED_Five(void);
	extern void LED_Six(void);
	extern void LED_Seven(void);
	extern void LED_Eight(void);
	extern void LED_Nine(void);
	extern void LED_Zero(void);
	extern void LED_Blank(void);
	extern void Low_Speed(void);
	extern void High_Speed(void);
/***********************************************************************************************************************
* Function Name: R_Config_TAU0_4_Create_UserInit
* Description  : This function adds user code after initializing the TAU0 channel4.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_4_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */
//	unsigned char timer_counter4=0;
//	unsigned char seconds=0;
//	unsigned char timer_flag=0;
//	unsigned char autoclean_time=9;
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_TAU0_4_interrupt
* Description  : This function is INTTM04 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_Config_TAU0_4_interrupt(void)
{
    /* Start user code for r_Config_TAU0_4_interrupt. Do not edit comment generated here */
	if((++timer_counter4)==8)
	{
		timer_counter4=0;
		seconds++;
		if(timer_flag)
		{
			switch(autoclean_time)
			{
			case 0:LED_Zero();
			   	   High_Speed();
				break;
			case 1:LED_One();
				   Low_Speed();
				break;
			case 2:LED_Two();
				break;
			case 3:LED_Three();
				break;
			case 4:LED_Four();
				break;
			case 5:LED_Five();
				break;
			case 6:LED_Six();
				break;
			case 7:LED_Seven();
				break;
			case 8:LED_Eight();
				break;
			case 9:LED_Nine();
				break;
			}
			timer_flag=0;
		}
		else
		{
			LED_Blank();
			timer_flag=1;
		}

	}
	if(seconds==120)
	{
		seconds=0;
		if(autoclean_time==0)
		{
			R_Config_TAU0_4_Stop();
		}
		autoclean_time--;
	}
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

