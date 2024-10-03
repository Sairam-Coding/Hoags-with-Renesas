

struct ChimneyState
{
	unsigned char micstatus:1;
	unsigned char gasleakstatus:1;
	unsigned char modestatus:1;
	unsigned char autocleanstatus:1;
	unsigned char lightstatus:1;
	unsigned char speedstatus:2;
	unsigned char powerstatus:1;
};

struct Cmdpacket
{
	unsigned char Header;
	unsigned char Src;
	struct ChimneyState chimney;
	unsigned char checksum;
}Renesaspack;

unsigned char rcvpack[4];

void Button_Action(unsigned int);
void Receive_Action(void);
void Low_Speed(void);
void Medium_Speed(void);
void High_Speed(void);
void Idle_Mode(void);
void Left_Right(void);
void Right_Left(void);

