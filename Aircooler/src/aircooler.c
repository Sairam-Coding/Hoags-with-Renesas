
#include "aircooler.h"

extern volatile uint32_t time_us;
extern volatile uint32_t count;
extern volatile uint32_t data[32];

 //uint8_t speeD=0,swing=0,pump=0;
 uint8_t ar[100];
 uint8_t mode;
 uint8_t modeStatus;
 uint8_t speed;
 uint8_t speedStatus;
 uint8_t uartSendEnd=0;
// uint8_t stateSwing=0,statePump=0;
 aircooler state; //air cooler state structure variable

static void __near Timer_ISR(void)
{
	time_us+=100UL; // Increment the microsecond counter
	//time_us++; // Increment the microsecond counter
}

void resetpins(void)
{
	 PIN_WRITE(SWING) = LOW;
	 PIN_WRITE(PUMP) = LOW;
	 PIN_WRITE(SPEED1) = LOW;
	 PIN_WRITE(SPEED2) = LOW;
	 PIN_WRITE(SPEED3) = LOW;
	 PIN_WRITE(BUZZER) = LOW;
}

void modeAction(uint8_t Mode)
{
	print(" Knob -");
	switch(Mode)
	{
		case 0 :	print(" Mode - 0\r\n");
					PIN_WRITE(SWING) = LOW;
					PIN_WRITE(PUMP) = LOW;
					break;

		case 1 :  	print(" Mode - 1\r\n");
					PIN_WRITE(SWING) = HIGH;
					PIN_WRITE(PUMP) = LOW;
					state.swing=1;
					state.pump=0;
					PIN_WRITE(BUZZER) = HIGH;
					R_BSP_SoftwareDelay(DELAY, BSP_DELAY_MILLISECS);
					PIN_WRITE(BUZZER) = LOW;
					break ;

		case 2 :	print(" Mode - 2\r\n");
					PIN_WRITE(SWING) = HIGH;
					PIN_WRITE(PUMP) = HIGH;
					state.swing=1;
					state.pump=1;
					PIN_WRITE(BUZZER) = HIGH;
					R_BSP_SoftwareDelay(DELAY, BSP_DELAY_MILLISECS);
					PIN_WRITE(BUZZER) = LOW;
					break ;

		case 3 :	print(" Mode - 3\r\n");
					PIN_WRITE(SWING) = LOW;
					PIN_WRITE(PUMP) = HIGH;
					state.swing=0;
					state.pump=1;
					PIN_WRITE(BUZZER) = HIGH;
					R_BSP_SoftwareDelay(DELAY, BSP_DELAY_MILLISECS);
					PIN_WRITE(BUZZER) = LOW;
					break ;

		default :	print(" Unknown KNOB Position \r\n");
					break;

	}
}

void speedAction(uint8_t Speed)
{
	print(" Knob - ");
	state.motor=Speed;
	switch(Speed)
	{
		case 0:
		print("Speed - 0\r\n");
		PIN_WRITE(SPEED1)=LOW;
		PIN_WRITE(SPEED2)=LOW;
		PIN_WRITE(SPEED3)=LOW;
		state.speed=0;
		break;

		case 1:
		print("Speed - 1\r\n");
		PIN_WRITE(SPEED1)=HIGH;
		PIN_WRITE(SPEED2)=LOW;
		PIN_WRITE(SPEED3)=LOW;
		state.speed=1;
		PIN_WRITE(BUZZER) = HIGH;
		R_BSP_SoftwareDelay(DELAY, BSP_DELAY_MILLISECS);
		PIN_WRITE(BUZZER) = LOW;
		break ;

		case 2:
		print("Speed - 2\r\n");
		PIN_WRITE(SPEED1)=LOW;
		PIN_WRITE(SPEED2)=HIGH;
		PIN_WRITE(SPEED3)=LOW;
		state.speed=1;
		PIN_WRITE(BUZZER) = HIGH;
		R_BSP_SoftwareDelay(DELAY, BSP_DELAY_MILLISECS);
		PIN_WRITE(BUZZER) = LOW;
		break ;

		case 3:
		print("Speed - 3\r\n");
		PIN_WRITE(SPEED1)=LOW;
		PIN_WRITE(SPEED2)=LOW;
		PIN_WRITE(SPEED3)=HIGH;
		state.speed=1;
		PIN_WRITE(BUZZER) = HIGH;
		R_BSP_SoftwareDelay(DELAY, BSP_DELAY_MILLISECS);
		PIN_WRITE(BUZZER) = LOW;
		break ;

		default:print(" Unknown Speed Knob Position \r\n");
		break ;

	}
}

void readModePin(void)
{
	if(PIN_READ(pin1)==0)
	{
		if(PIN_READ(pin2)==0)
			mode=2;
		else
			mode =1;
	}
	else if(PIN_READ(pin2)==0)
	{
		if(PIN_READ(pin1)==0)
			mode=2;
		else
			mode =3;
	}
	else
	{
		mode = 0;
	}
	if(mode != modeStatus)
	{
		modeAction(mode);
	}
	modeStatus=mode;
}

void readSpeedPin(void)
{
	if(PIN_READ(pin3)==0)
	{
		speed=1;
	}
	else if(PIN_READ(pin4)==0)
	{
		speed=2;
	}
	else if(PIN_READ(pin5)==0)
	{
		speed=3;
	}
	else
	{
		speed=0;
	}

	if(speed != speedStatus)
	{
		speedAction(speed);
	}
	speedStatus=speed;
}

/***************************************************
 *     		Timer Code Starts
 **************************************************/

void Timer_Init(void)
{
	// Initialize Timer Array Unit (TAU) channel 0 to generate an interrupt every 1µs
	TAU0EN = 1;                 // Enable TAU0 clock
	TPS0 = 0x0000;              // Set the clock source to fCLK (16 MHz)
	TMR00 = 0x0000;             // Timer mode, interval timer
	TDR00 = 1599;                 // Set the timer period to 16 clock cycles (1 µs with 16 MHz clock)
//	TDR00 = 15;                 // Set the timer period to 16 clock cycles (1 µs with 16 MHz clock)
	TOE0 &= ~0x01;              // Disable output
	TS0 |= 0x01;                // Start the timer// Enable the interrupt
	TMMK00 = 0;                 // Clear the interrupt mask (enable interrupt)
	TMIF00 = 0;                 // Clear the interrupt flag
}


uint32_t Get_Current_Time_us(void)
{
	uint32_t num=TCR00;
	num=1599-num;
	num=num/16;
	num=time_us+num;
	return num; // Return the current time in microseconds
	//return time_us; // Return the current time in microseconds

}
/**************************************************
 * 			Period - 1700ms
 ***************************************************/
void processData(void)
{
	int j=0;
	int32_t t;
	uint32_t code =0,code1=0;
	for(j=1;j<count;j++)
	{
		t=data[j]-data[j-1];
		if((abs(t-420))<150)
		{
			code = code << 1 ; //Low
		}
		else if((abs(t-1200))<240)
		{
			code = (code << 1)|1; //High
		}
		else
		{
			print(" ERROR ");
			sprintf(ar," %x %x",t,j);
			print(ar);
			for(j=0;j<count;j++)
			{
				sprintf(ar," %x%x ",data[j]>>16,data[j]);
				print(ar);
			}
			break;
		}

	}
	code1=code>>16;
	sprintf(ar," %x",code1);
	print(ar);
	sprintf(ar,"%x ",code);
	print(ar);
	print("DONE");
	irAction(code);
}

void print(char *str)
{
	R_Config_UART0_Send(str,_strlen(str));
	while(uartSendEnd==0);
	uartSendEnd=0;
}

int _strlen(char *p)
{
	int i=0;
	while(*p)
	{
		i++;
		p++;
	}
	return i;
}

void irAction(uint32_t irCode)
{
	switch(irCode)
	{
		case ON_OFF:	print(" Power button pressed to turn  ");
						if(state.speed==0)
						{
							print("ON\r\n");
							PIN_WRITE(SPEED1)=HIGH;
							PIN_WRITE(SPEED2)=LOW;
							PIN_WRITE(SPEED3)=LOW;
							PIN_WRITE(BUZZER) = HIGH;
							R_BSP_SoftwareDelay(DELAY, BSP_DELAY_MILLISECS);
							PIN_WRITE(BUZZER) = LOW;
							state.speed=1;
							state.motor=1;
						}
						else
						{
							print("OFF\r\n");
							PIN_WRITE(SPEED1)=LOW;
							PIN_WRITE(SPEED2)=LOW;
							PIN_WRITE(SPEED3)=LOW;
							PIN_WRITE(SWING)=LOW;
							PIN_WRITE(PUMP)=LOW;
							PIN_WRITE(BUZZER) = HIGH;
							R_BSP_SoftwareDelay(DELAY, BSP_DELAY_MILLISECS);
							PIN_WRITE(BUZZER) = LOW;
							state.speed=0;
							state.motor=0;
							state.swing=0;
							state.pump=0;
						}
						break;

		case COOL:		print(" Pump button pressed to Turn ");
						if(state.pump==0)
						{
							print("ON\r\n");
							PIN_WRITE(PUMP)=HIGH;
							PIN_WRITE(BUZZER) = HIGH;
							R_BSP_SoftwareDelay(DELAY, BSP_DELAY_MILLISECS);
							PIN_WRITE(BUZZER) = LOW;
							state.pump=1;
						}
						else
						{
							print("OFF\r\n");
							PIN_WRITE(PUMP)=LOW;
							PIN_WRITE(BUZZER) = HIGH;
							R_BSP_SoftwareDelay(DELAY, BSP_DELAY_MILLISECS);
							PIN_WRITE(BUZZER) = LOW;
							state.pump=0;
						}
						break;

		case SWING_M:	print(" Swing button pressed to Turn ");
						if(state.swing==0)
						{
							if(state.speed==1)
							{
								print("ON\r\n");
								PIN_WRITE(SWING)=HIGH;
								PIN_WRITE(BUZZER) = HIGH;
								R_BSP_SoftwareDelay(DELAY, BSP_DELAY_MILLISECS);
								PIN_WRITE(BUZZER) = LOW;
								state.swing=1;
							}
							else
							{
								print(" Fan is OFF\r\n");
							}
						}
						else
						{
							print("OFF\r\n");
							PIN_WRITE(SWING)=LOW;
							PIN_WRITE(BUZZER) = HIGH;
							R_BSP_SoftwareDelay(DELAY, BSP_DELAY_MILLISECS);
							PIN_WRITE(BUZZER) = LOW;
							state.swing=0;
						}
						break;

		case SPEED:		print(" Speed button pressed to Turn ");
			state.motor=state.motor+1;

					if(state.motor>3)
					{
						state.motor=1;
					}
					switch(state.motor)
					{
					case 1: print("SPEED - 1\r\n");
							PIN_WRITE(SPEED1)=HIGH;
							PIN_WRITE(SPEED2)=LOW;
							PIN_WRITE(SPEED3)=LOW;
							state.speed=1;
							PIN_WRITE(BUZZER) = HIGH;
							R_BSP_SoftwareDelay(DELAY, BSP_DELAY_MILLISECS);
							PIN_WRITE(BUZZER) = LOW;
							break;

					case 2:	print("SPEED - 2\r\n");
							PIN_WRITE(SPEED1)=LOW;
							PIN_WRITE(SPEED2)=HIGH;
							PIN_WRITE(SPEED3)=LOW;
							state.speed=1;
							PIN_WRITE(BUZZER) = HIGH;
							R_BSP_SoftwareDelay(DELAY, BSP_DELAY_MILLISECS);
							PIN_WRITE(BUZZER) = LOW;
							break;

					case 3:	print("SPEED - 3\r\n");
							PIN_WRITE(SPEED1)=LOW;
							PIN_WRITE(SPEED2)=LOW;
							PIN_WRITE(SPEED3)=HIGH;
							state.speed=1;
							PIN_WRITE(BUZZER) = HIGH;
							R_BSP_SoftwareDelay(DELAY, BSP_DELAY_MILLISECS);
							PIN_WRITE(BUZZER) = LOW;
							break;

					default:
							break;
					}

					break;
		default:	print(" Unknown Button pressed \r\n");
					break;
	}
}
