/**
 *
 * This file is a modified version of the HW_Teensy3.h created by Paul Stoffregen.
 *
 * Teensy 3.x pin definitions created by Dawnmist
 * http://forum.pjrc.com/threads/18002-Teensy-3-0-driving-an-SSD1289-with-utft?p=34719&viewfull=1#post34719
 *
 * This file only supports the B and D ports as defined by Dawnmist for 8-bit and 16-bit display modules.
 * Serial display modules are also supported.
 * 
 * NOTE: This file has only been tested on a Teensy 3.1
 *
**/
#include "SPI.h" 
#define digitalPinToBitMask(P)     (BIT(PIN_MAP[P].gpio_bit))
#define digitalPinToPort(P)        (PIN_MAP[P].gpio_device)
#define portOutputRegister(P)      (&(P->regs->ODR))

#define digitalWriteFast(pin,val) 

#define setBit(val) PIN_MAP[__p1].gpio_device->regs->BSRR=((B_SDA)<<((val==0)?16:0))

#define HighCLK PIN_MAP[__p2].gpio_device->regs->BSRR=B_SCL
#define LowCLK PIN_MAP[__p2].gpio_device->regs->BRR=B_SCL
#define CLK_pulse_low LowCLK; HighCLK;

typedef unsigned int word;

// *** Hardware specific functions ***
void UTFT::_hw_special_init()
{
//	__p1 = RS;
//	__p2 = WR;
//	__p3 = CS;
//	__p4 = RST;
//	__p5 = SER;
 // SPI.setClockDivider(SPI_CLOCK_DIV8);
 // SPI.setDataMode(3);
  SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV2);
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
    pinMode(__p4,OUTPUT);
    digitalWrite(__p4,HIGH);
    digitalWrite(__p4,LOW);
    digitalWrite(__p4,HIGH);
	if (display_transfer_mode == SERIAL_4PIN)
	{
		display_transfer_mode=1;
		display_serial_mode=SERIAL_4PIN;
	}
	if (display_transfer_mode == SERIAL_5PIN)
	{
		display_transfer_mode=1;
		display_serial_mode=SERIAL_5PIN;
	}

	if (display_transfer_mode!=1)
	{
		_set_direction_registers(display_transfer_mode);
		P_RS	= portOutputRegister(digitalPinToPort(__p1));
		P_WR	= portOutputRegister(digitalPinToPort(__p2));
		P_CS	= portOutputRegister(digitalPinToPort(__p3));
		P_RST	= portOutputRegister(digitalPinToPort(__p4));
		if (display_transfer_mode==LATCHED_16)
		{
		}
	}
	else
	{
		P_SDA	= portOutputRegister(digitalPinToPort(__p1));
		P_SCL	= portOutputRegister(digitalPinToPort(__p2));
		P_CS	= portOutputRegister(digitalPinToPort(__p3));
		if (__p4 = NOTINUSE) 
		  {P_RST = P_SCL; B_RST=1U<<16;} //Like NULL
		else 
		  P_RST	= portOutputRegister(digitalPinToPort(__p4));
		
		if (display_serial_mode!=SERIAL_4PIN) 
		  P_RS	= portOutputRegister(digitalPinToPort(__p5));
		
	}


}

/*void UTFT::LCD_Writ_SPI(char VH,char VL, byte mode)
{

}*/
void UTFT::LCD_Writ_Bus(char VH,char VL, byte mode)
{
	switch (mode)
	{
	case 1:
		if (VH==1)
			sbi(P_RS, B_RS);
		else
			cbi(P_RS, B_RS);
		SPI.write(VL); return;
		break;
	case 8:
	/*
		*(volatile uint8_t *)(&GPIOD_PDOR) = VH;
		pulse_low(P_WR, B_WR);
		*(volatile uint8_t *)(&GPIOD_PDOR) = VL;
		pulse_low(P_WR, B_WR);
		*/
		break;
	case 16:
	/*
		*(volatile uint8_t *)(&GPIOD_PDOR) = VH;
  		GPIOB_PCOR = 0x000F000F;							// clear data lines B0-3,B16-19
        GPIOB_PSOR = (0x0F & VL) | ((VL >> 4) << 16);  		// set data lines 0-3,16-19 if set in cl
		pulse_low(P_WR, B_WR);
		*/
		break;

	}
}

void UTFT::_set_direction_registers(byte mode)
{/*
	GPIOD_PDDR |= 0xFF;
	PORTD_PCR0  = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	PORTD_PCR1  = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	PORTD_PCR2  = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	PORTD_PCR3  = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	PORTD_PCR4  = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	PORTD_PCR5  = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	PORTD_PCR6  = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	PORTD_PCR7  = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);

	if (mode == 16)
    {
		GPIOB_PDDR |= 0x000F000F;
		PORTB_PCR0  = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
		PORTB_PCR1  = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
		PORTB_PCR2  = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
		PORTB_PCR3  = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
		PORTB_PCR16 = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
		PORTB_PCR17 = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
		PORTB_PCR18 = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
		PORTB_PCR19 = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
    }
*/}
void UTFT::_fast_fill_16(int ch, int cl, long pix)
{/*
	long blocks;

	*(volatile uint8_t *)(&GPIOD_PDOR) = ch;
  	GPIOB_PCOR = 0x000F000F;						// clear data lines B0-3,B16-19
    GPIOB_PSOR = (0x0F & cl) | ((cl >> 4) << 16);  	// set data lines 0-3,16-19 if set in cl

	blocks = pix/16;
	for (int i=0; i<blocks; i++)
	{
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
	}
	if ((pix % 16) != 0)
		for (int i=0; i<(pix % 16); i++)
		{
			pulse_low(P_WR, B_WR);
		}
*/}

void UTFT::_fast_fill_8(int ch, long pix)
{/*
	long blocks;

	*(volatile uint8_t *)(&GPIOD_PDOR) = ch;

	blocks = pix/16;
	for (int i=0; i<blocks; i++)
	{
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
	}
	if ((pix % 16) != 0)
		for (int i=0; i<(pix % 16); i++)
		{
			pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		}
*/}
