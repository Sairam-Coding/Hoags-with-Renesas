/*
 * aircooler.h
 *
 *  Created on: 17-Aug-2024
 *      Author: Admin
 */

#ifndef AIRCOOLER_H_
#define AIRCOOLER_H_

#include "r_smc_entry.h"


#pragma interrupt Timer_ISR(vect=INTTM00)

/****************************************************************
 * 					Global variables
 ***************************************************************/

/************************************************
 * 			Timer Variables
 ************************************************/


#define RC5CMD_DURATION 30000  //30ms for entire pulse
#define PULSECOUNT 24    // 24 edges for one set of pulse

#define HIGH 1
#define LOW 0
#define DELAY 150
#define BUZZER 1,1 //P11

/***************************************************************************
 *   pin1,2,3,4,5 are INPUT PINS from port 1, pin 3,4,5,6,7 repectively    *
 ****************************************************************************/
#define pin1 1,3
#define pin2 1,4
#define pin3 1,5
#define pin4 1,6
#define pin5 1,7

/*****************************************************************************
 *  SWING, PUMP, SPEED1,2,3 are OUTPUT PINS P21,P20,P02,P06,P07 repectively  *
 *   This pins will be connected to relays of the corresponding terminals    *
 *****************************************************************************/
#define SWING 2,1
#define PUMP 2,0
#define SPEED1 0,2
#define SPEED2 0,6
#define SPEED3 0,7

#define ON_OFF 0x52caab
#define COOL 0x52caca
#define SWING_M 0x52cab2
#define SPEED 0x52caac

struct STATE
{
	uint8_t speed;
	uint8_t swing;
	uint8_t pump;
	uint8_t speedState; //whether motor is on or not 1==> ON, 0==>OFF
	uint8_t motor; //motor speed (1/2/3)
};
typedef struct STATE aircooler;

/*******************************************************************
 * 					KNOB function declarations
 *******************************************************************/

void readSpeedPin(void);
void readModePin(void);
void modeAction(uint8_t );
void speedAction(uint8_t );

/*****************************************************************/
void resetpins(void);
void Timer_Init(void);
void print(char *);
void processData(void);
uint32_t Get_Current_Time_us(void);
e_bsp_err_t R_BSP_SoftwareDelay(uint32_t , e_bsp_delay_units_t );
void irAction(uint32_t );
int _strlen(char *);


#endif /* AIRCOOLER_H_ */
