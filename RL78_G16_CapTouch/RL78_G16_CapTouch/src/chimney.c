#include "chimney.h"
#include "Led.h"
#include "r_smc_entry.h"

extern void uart_integer(int);

extern unsigned char timer_counter4;
extern unsigned char timer_flag;
extern unsigned char seconds;
extern unsigned char autoclean_time;
extern unsigned char global_data[4];

unsigned char count=0;
unsigned char arr[4]="ABCD";

void Button_Action(unsigned int button_status)
{
	Renesaspack.Header=0xDA;
	Renesaspack.Src=3;
	Renesaspack.checksum=0xAD;
	switch(button_status)
	{
	case 1:
		Renesaspack.chimney.modestatus^=1;
		break;
	case 2:
		Renesaspack.chimney.micstatus^=1;
		break;
	case 4:
		switch(Renesaspack.chimney.speedstatus)
		{
		case 0:Renesaspack.chimney.speedstatus=1;
			break;
		case 1:Renesaspack.chimney.speedstatus=2;
			break;
		case 2:Renesaspack.chimney.speedstatus=3;
			break;
		case 3:Renesaspack.chimney.speedstatus=1;
			break;
		}
		break;
	case 8:
		Renesaspack.chimney.lightstatus^=1;
		break;
	case 16:
		Renesaspack.chimney.autocleanstatus^=1;
		if(Renesaspack.chimney.autocleanstatus)
		{
			Renesaspack.chimney.powerstatus=1;
			Renesaspack.chimney.speedstatus=0;
		}
		else
			Renesaspack.chimney.powerstatus=0;
		break;
	case 32:
		Renesaspack.chimney.powerstatus^=1;
		if(Renesaspack.chimney.powerstatus)
			Renesaspack.chimney.speedstatus=1;
		else
		{
			Renesaspack.chimney.speedstatus=0;
			Renesaspack.chimney.autocleanstatus=0;
		}
		break;
	}
	PIN_WRITE(1,3) =~ PIN_READ(1,3);
//	R_Config_UART1_Send(&Renesaspack,4);
//		uart_integer(Renesaspack.Header);
//		uart_integer(Renesaspack.Src);
//		uart_integer(Renesaspack.checksum);
	for(count=0;count<4;count++)
	{
		R_Config_UART1_Send(arr[count],1);
//		R_BSP_SoftwareDelay(100,BSP_DELAY_MILLISECS);
	}
}

void Receive_Action(void)
{
//	uart_integer(rcvpack[0]);
//	uart_integer(rcvpack[1]);
//	uart_integer(rcvpack[2]);
//	uart_integer(rcvpack[3]);
	if((global_data[0]==0xAC) && (global_data[1]==3) && (global_data[3]==0xFC))
	{
		Renesaspack.Header=0xAC;
		Renesaspack.Src=global_data[1];
		Renesaspack.chimney.micstatus=global_data[2]&1;
		Renesaspack.chimney.modestatus=(global_data[2]>>2)&1;
		Renesaspack.chimney.autocleanstatus=(global_data[2]>>3)&1;
		Renesaspack.chimney.lightstatus=(global_data[2]>>4)&1;
		Renesaspack.chimney.speedstatus=(global_data[2]>>5)&3;
		Renesaspack.chimney.powerstatus=(global_data[2]>>7)&1;
		Renesaspack.checksum=0xFC;
		if(Renesaspack.chimney.autocleanstatus)
		{
			R_Config_TAU0_4_Start();
			LED_Nine();
			timer_flag=0;
			seconds=0;
			autoclean_time=9;
		}
		else
		{
			R_Config_TAU0_4_Stop();
		}
		if(Renesaspack.chimney.lightstatus)
			PIN_WRITE(2,2)=1;
		else
			PIN_WRITE(2,2)=0;
		if(Renesaspack.chimney.speedstatus)
		{
			switch(Renesaspack.chimney.speedstatus)
			{
			case 1:Low_Speed();
				   LED_One();
				break;
			case 2:Medium_Speed();
				   LED_Two();
				break;
			case 3:High_Speed();
				   LED_Three();
				break;
			}
		}
		else
		{
			Idle_Mode();
		}
	//	if((Renesaspack.chimney.powerstatus==1) && (Renesaspack.chimney.autocleanstatus==0))
	//	{
	//		PIN_WRITE(0,7)=1;
	//		PIN_WRITE(0,6)=0;
	//		PIN_WRITE(4,2)=0;
	//		PIN_WRITE(1,1)=0;
	//		LED_One();
	//	}
		if((Renesaspack.chimney.powerstatus==0) && (Renesaspack.chimney.autocleanstatus==0))
		{
			Idle_Mode();
			LED_Zero();
		}
		R_Config_UART1_Send(&Renesaspack,4);
	}
	else
		//uart_integer(999);
		PIN_WRITE(1,3) =~ PIN_READ(1,3);


}

void Low_Speed(void)
{
	PIN_WRITE(0,7)=1;
	PIN_WRITE(0,6)=0;
	PIN_WRITE(4,2)=0;
	PIN_WRITE(1,1)=0;
	uart_integer(11);
}

void Medium_Speed(void)
{
	PIN_WRITE(0,7)=0;
	PIN_WRITE(0,6)=1;
	PIN_WRITE(4,2)=0;
	PIN_WRITE(1,1)=0;
	uart_integer(22);
}

void High_Speed(void)
{
	PIN_WRITE(0,7)=0;
	PIN_WRITE(0,6)=0;
	PIN_WRITE(4,2)=1;
	PIN_WRITE(1,1)=0;
	uart_integer(33);
}

void Idle_Mode(void)
{
	PIN_WRITE(0,7)=0;
	PIN_WRITE(0,6)=0;
	PIN_WRITE(4,2)=0;
	PIN_WRITE(1,1)=0;
}

void Left_Right(void)
{
//	R_Config_UART2_Send(&Renesaspack,4);
//	R_BSP_SoftwareDelay(100,BSP_DELAY_MILLISECS);
	Button_Action(4);
	uart_integer(19);
	R_BSP_SoftwareDelay(1,BSP_DELAY_MILLISECS);
//	unsigned char speed=Renesaspack.chimney.speedstatus;
//	switch(speed)
//	{
//	case 0:Renesaspack.chimney.speedstatus=1;
//		   break;
//	case 1:Renesaspack.chimney.speedstatus=2;
//		   break;
//	case 2:Renesaspack.chimney.speedstatus=3;
//	       break;
//	case 3:Renesaspack.chimney.speedstatus=1;
//		   break;
//	}
}

void Right_Left(void)
{
	uart_integer(91);
	R_BSP_SoftwareDelay(1,BSP_DELAY_MILLISECS);
	R_Config_TAU0_4_Start();
	LED_Three();
	timer_flag=0;
	seconds=0;
	autoclean_time=3;
}
