#include "r_smc_entry.h"
#include "Led.h"


void LED_One(void)
{
	PIN_WRITE(13,7)=0; //A
	PIN_WRITE(12,2)=1; //B
	PIN_WRITE(12,1)=1; //C
	PIN_WRITE(6,0)=0;  //D
	PIN_WRITE(6,1)=0;  //E
	PIN_WRITE(1,2)=0;  //F
	PIN_WRITE(1,3)=0;  //G
}

void LED_Two(void)
{
	PIN_WRITE(13,7)=1; //A
	PIN_WRITE(12,2)=1; //B
	PIN_WRITE(12,1)=0; //C
	PIN_WRITE(6,0)=1;  //D
	PIN_WRITE(6,1)=1;  //E
	PIN_WRITE(1,2)=0;  //F
	PIN_WRITE(1,3)=1;  //G
}

void LED_Three(void)
{
	PIN_WRITE(13,7)=1; //A
	PIN_WRITE(12,2)=1; //B
	PIN_WRITE(12,1)=1; //C
	PIN_WRITE(6,0)=1;  //D
	PIN_WRITE(6,1)=0;  //E
	PIN_WRITE(1,2)=0;  //F
	PIN_WRITE(1,3)=1;  //G
}

void LED_Four(void)
{
	PIN_WRITE(13,7)=0; //A
	PIN_WRITE(12,2)=1; //B
	PIN_WRITE(12,1)=1; //C
	PIN_WRITE(6,0)=0;  //D
	PIN_WRITE(6,1)=0;  //E
	PIN_WRITE(1,2)=1;  //F
	PIN_WRITE(1,3)=1;  //G
}

void LED_Five(void)
{
	PIN_WRITE(13,7)=1; //A
	PIN_WRITE(12,2)=0; //B
	PIN_WRITE(12,1)=1; //C
	PIN_WRITE(6,0)=1;  //D
	PIN_WRITE(6,1)=0;  //E
	PIN_WRITE(1,2)=1;  //F
	PIN_WRITE(1,3)=1;  //G
}

void LED_Six(void)
{
	PIN_WRITE(13,7)=0; //A
	PIN_WRITE(12,2)=0; //B
	PIN_WRITE(12,1)=1; //C
	PIN_WRITE(6,0)=1;  //D
	PIN_WRITE(6,1)=1;  //E
	PIN_WRITE(1,2)=1;  //F
	PIN_WRITE(1,3)=1;  //G
}

void LED_Seven(void)
{
	PIN_WRITE(13,7)=1; //A
	PIN_WRITE(12,2)=1; //B
	PIN_WRITE(12,1)=1; //C
	PIN_WRITE(6,0)=0;  //D
	PIN_WRITE(6,1)=0;  //E
	PIN_WRITE(1,2)=0;  //F
	PIN_WRITE(1,3)=0;  //G
}


void LED_Eight(void)
{
	PIN_WRITE(13,7)=1; //A
	PIN_WRITE(12,2)=1; //B
	PIN_WRITE(12,1)=1; //C
	PIN_WRITE(6,0)=1;  //D
	PIN_WRITE(6,1)=1;  //E
	PIN_WRITE(1,2)=1;  //F
	PIN_WRITE(1,3)=1;  //G
}

void LED_Nine(void)
{
	PIN_WRITE(13,7)=1; //A
	PIN_WRITE(12,2)=1; //B
	PIN_WRITE(12,1)=1; //C
	PIN_WRITE(6,0)=0;  //D
	PIN_WRITE(6,1)=0;  //E
	PIN_WRITE(1,2)=1;  //F
	PIN_WRITE(1,3)=1;  //G
}

void LED_Zero(void)
{
	PIN_WRITE(13,7)=1; //A
	PIN_WRITE(12,2)=1; //B
	PIN_WRITE(12,1)=1; //C
	PIN_WRITE(6,0)=1;  //D
	PIN_WRITE(6,1)=1;  //E
	PIN_WRITE(1,2)=1;  //F
	PIN_WRITE(1,3)=0;  //G
}

void LED_Blank(void)
{
	PIN_WRITE(13,7)=0; //A
	PIN_WRITE(12,2)=0; //B
	PIN_WRITE(12,1)=0; //C
	PIN_WRITE(6,0)=0;  //D
	PIN_WRITE(6,1)=0;  //E
	PIN_WRITE(1,2)=0;  //F
	PIN_WRITE(1,3)=0;  //G
}
