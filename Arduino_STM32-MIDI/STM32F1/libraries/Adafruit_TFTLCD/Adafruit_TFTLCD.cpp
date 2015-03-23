#include "Adafruit_TFTLCD.h"
#include <libmaple/libmaple.h>
#include <libmaple/gpio.h>
#include "PortMask.h"


// Graphics library by ladyada/adafruit with init code from Rossum 
// MIT license


//Read Strobe Signal Pin RD
#define RD  0 // PC0, pin 15
//Write Strobe Signal Pin nWR
#define WR  1 // PC1, pin 16
//Register Select Pin RS
#define RS  2 // PC2, pin 17
//Chip Select Pin nCS
#define CS  3 // PC3, pin 18
//All pins above are at Port GPIOC

//Same as above but with higher level pin numbers
#define RD_p  15 // PC0, pin 15
#define WR_p  16 // PC1, pin 16
#define RS_p  17 // PC2, pin 17
#define CS_p  18 // PC3, pin 18

#define _reset  43 //Reset PB4

//Data Pins DB[10~17]
#define _D1 10   // PA10, dpins[0], pin 8
#define _D2 7	// PB7, dpins[1], pin 9
#define _D3 4	// PA4, dpins[2], pin 10
#define _D4 7	// PA7, dpins[3], pin 11
#define _D5 5	// PB5, dpins[4], pin 4
#define _D6 5	// PA5, dpins[5], pin 13
#define _D7 8	// PA8, dpins[6], pin 6
#define _D8 9	// PA9, dpins[7], pin 7

//Fast Output
#define set(pin) dports[pin]->regs->BSRR = BIT(dpins[pin])
#define clear(pin) dports[pin]->regs->BRR = BIT(dpins[pin])

//Fast Output for Control Pins
	#define  RD_OUTPUT	gpio_set_mode(GPIOC, RD, GPIO_OUTPUT_PP ); 
	#define  WR_OUTPUT	gpio_set_mode(GPIOC, WR, GPIO_OUTPUT_PP ); 
	#define  RS_OUTPUT	gpio_set_mode(GPIOC, RS, GPIO_OUTPUT_PP ); 
	#define  CS_OUTPUT	gpio_set_mode(GPIOC, CS, GPIO_OUTPUT_PP ); 


	#define  RD_LOW		GPIOC->regs->BRR = RD_bit;
	#define  RD_HIGH	GPIOC->regs->BSRR = RD_bit;

	#define  WR_LOW		GPIOC->regs->BRR = WR_bit;
	#define  WR_HIGH	GPIOC->regs->BSRR = WR_bit;

	#define  RS_LOW		GPIOC->regs->BRR = RS_bit;
	#define  RS_HIGH	GPIOC->regs->BSRR = RS_bit;

	#define  CS_LOW		GPIOC->regs->BRR = CS_bit;
	#define  CS_HIGH	GPIOC->regs->BSRR = CS_bit;

//Which data pin it is       1874 63 
#define MASK_PORTA 0b0000011110110000

//Which data pin it is          2 5
#define MASK_PORTB 0b0000000010100000
//-------------------------------------------------------------

const unsigned char RD_bit = 1 << RD;
const unsigned char WR_bit = 1 << WR;
const unsigned char RS_bit = 1 << RS;
const unsigned char CS_bit = 1 << CS;

//Put Data Pins into array
const unsigned char dpins[] = {_D1,_D2,_D3,_D4,_D5,_D6,_D7,_D8}; 
//Match Pins with their appropriate GPIO Port
gpio_dev* dports[] = {GPIOA,GPIOB,GPIOA,GPIOA,GPIOB,GPIOA,GPIOA,GPIOA};



void Adafruit_TFTLCD::goTo(int x, int y) {
    writeRegister(0x0020, x);     // GRAM Address Set (Horizontal Address) (R20h)
    writeRegister(0x0021, y);     // GRAM Address Set (Vertical Address) (R21h)
    writeCommand(0x0022);            // Write Data to GRAM (R22h)  
}


unsigned int Adafruit_TFTLCD::Color565(unsigned char r, unsigned char g, unsigned char b) {
  unsigned int c;
  c = r >> 3;
  c <<= 6;
  c |= g >> 2;
  c <<= 5;
  c |= b >> 3;

  return c;
}


// fill a rectangle
void Adafruit_TFTLCD::fillRect(int x, int y, int w, int h, 
		      unsigned int fillcolor) {
  // smarter version
  while (h--)
    drawFastHLine(x, y++, w, fillcolor);
}


void Adafruit_TFTLCD::drawFastVLine(int x, int y, int length, unsigned int color)
{
  if (x >= _width) return;

  drawFastLine(x,y,length,color,1);
}


void Adafruit_TFTLCD::drawFastHLine(int x, int y, int length, unsigned int color)
{
  if (y >= _height) return;
  drawFastLine(x,y,length,color,0);
}


void Adafruit_TFTLCD::drawFastLine(int x, int y, int length, 
			  unsigned int color, unsigned char rotflag)
{
  unsigned int newentrymod;
  
  switch (rotation) {
  case 0:
    if (rotflag)
      newentrymod = 0x1028;   // we want a 'vertical line'
    else 
      newentrymod = 0x1030;   // we want a 'horizontal line'
    break;
  case 1:
    swap(x, y);
    // first up fix the X
    x = TFTWIDTH - x - 1;
    if (rotflag)
      newentrymod = 0x1000;   // we want a 'vertical line'
    else 
      newentrymod = 0x1028;   // we want a 'horizontal line'
    break;
  case 2:
    x = TFTWIDTH - x - 1;
    y = TFTHEIGHT - y - 1;
    if (rotflag)
      newentrymod = 0x1008;   // we want a 'vertical line'
    else 
      newentrymod = 0x1020;   // we want a 'horizontal line'
    break;
  case 3:
    swap(x,y);
    y = TFTHEIGHT - y - 1;
    if (rotflag)
      newentrymod = 0x1030;   // we want a 'vertical line'
    else 
      newentrymod = 0x1008;   // we want a 'horizontal line'
    break;
  }
  
    writeRegister(ILI932X_ENTRY_MOD, newentrymod);
    
    writeRegister(ILI932X_GRAM_HOR_AD, x); // GRAM Address Set (Horizontal Address) (R20h)
    writeRegister(ILI932X_GRAM_VER_AD, y); // GRAM Address Set (Vertical Address) (R21h)
    writeCommand(ILI932X_RW_GRAM);  // Write Data to GRAM (R22h)

  CS_LOW;
  RS_HIGH;
  RD_HIGH;
  WR_HIGH;

  setWriteDir();
  while (length--) {
    writeData_unsafe(color); 
  }

  // set back to default
  CS_HIGH;
  writeRegister(ILI932X_ENTRY_MOD, 0x1030);
}


void Adafruit_TFTLCD::fillScreen(unsigned int color) {
  goTo(0,0);

  int i;
  
  i = 320;
  i *= 240;

  CS_LOW;
  RS_HIGH;
  RD_HIGH;
  WR_HIGH;

  setWriteDir();
  while (i--) {
    writeData_unsafe(color); 
  }
  CS_HIGH;
}


void Adafruit_TFTLCD::drawPixel(int x, int y, unsigned int color)
{
  if ((x >= _width) || (y >= _height)) return;

  // check rotation, move pixel around if necessary
  switch (rotation) {
  case 1:
    swap(x, y);
    x = TFTWIDTH - x - 1;
    break;
  case 2:
    x = TFTWIDTH - x - 1;
    y = TFTHEIGHT - y - 1;
    break;
  case 3:
    swap(x, y);
    y = TFTHEIGHT - y - 1;
    break;
  }
    
    writeRegister(ILI932X_GRAM_HOR_AD, x); // GRAM Address Set (Horizontal Address)
    writeRegister(ILI932X_GRAM_VER_AD, y); // GRAM Address Set (Vertical Address)
    writeCommand(ILI932X_RW_GRAM);  // Write Data to GRAM

  writeData(color);
}

static const unsigned short ILI932x_regValues[] __FLASH__ = {
  ILI932X_START_OSC, 0x0001,     // start oscillator

  TFTLCD_DELAYCMD, 50,          // this will make a delay of 50 milliseconds

  ILI932X_DRIV_OUT_CTRL, 0x0100, 
  ILI932X_DRIV_WAV_CTRL, 0x0700,
  ILI932X_ENTRY_MOD, 0x1030,
  ILI932X_RESIZE_CTRL, 0x0000,
  ILI932X_DISP_CTRL2, 0x0202,
  ILI932X_DISP_CTRL3, 0x0000,
  ILI932X_DISP_CTRL4, 0x0000,
  ILI932X_RGB_DISP_IF_CTRL1, 0x0,
  ILI932X_FRM_MARKER_POS, 0x0,
  ILI932X_RGB_DISP_IF_CTRL2, 0x0,
  
  ILI932X_POW_CTRL1, 0x0000,
  ILI932X_POW_CTRL2, 0x0007,
  ILI932X_POW_CTRL3, 0x0000,
  ILI932X_POW_CTRL4, 0x0000,

  TFTLCD_DELAYCMD, 200,  
  
  ILI932X_POW_CTRL1, 0x1690,
  ILI932X_POW_CTRL2, 0x0227,

  TFTLCD_DELAYCMD, 50,  

  ILI932X_POW_CTRL3, 0x001A,

  TFTLCD_DELAYCMD, 50,  

  ILI932X_POW_CTRL4, 0x1800,
  ILI932X_POW_CTRL7, 0x002A,

  TFTLCD_DELAYCMD,50,
  
  ILI932X_GAMMA_CTRL1, 0x0000,    
  ILI932X_GAMMA_CTRL2, 0x0000, 
  ILI932X_GAMMA_CTRL3, 0x0000,
  ILI932X_GAMMA_CTRL4, 0x0206,   
  ILI932X_GAMMA_CTRL5, 0x0808,  
  ILI932X_GAMMA_CTRL6, 0x0007,  
  ILI932X_GAMMA_CTRL7, 0x0201,
  ILI932X_GAMMA_CTRL8, 0x0000,  
  ILI932X_GAMMA_CTRL9, 0x0000,  
  ILI932X_GAMMA_CTRL10, 0x0000,  
 
  ILI932X_GRAM_HOR_AD, 0x0000,  
  ILI932X_GRAM_VER_AD, 0x0000,  
  ILI932X_HOR_START_AD, 0x0000,
  ILI932X_HOR_END_AD, 0x00EF,
  ILI932X_VER_START_AD, 0X0000,
  ILI932X_VER_END_AD, 0x013F,
   

  ILI932X_GATE_SCAN_CTRL1, 0xA700,     // Driver Output Control (R60h)
  ILI932X_GATE_SCAN_CTRL2, 0x0003,     // Driver Output Control (R61h)
  ILI932X_GATE_SCAN_CTRL3, 0x0000,     // Driver Output Control (R62h)

  ILI932X_PANEL_IF_CTRL1, 0X0010,     // Panel Interface Control 1 (R90h)
  ILI932X_PANEL_IF_CTRL2, 0X0000,
  ILI932X_PANEL_IF_CTRL3, 0X0003,
  ILI932X_PANEL_IF_CTRL4, 0X1100,
  ILI932X_PANEL_IF_CTRL5, 0X0000,
  ILI932X_PANEL_IF_CTRL6, 0X0000,

  // Display On
  ILI932X_DISP_CTRL1, 0x0133,     // Display Control (R07h)
};

void Adafruit_TFTLCD::begin(unsigned int id) {
  unsigned int a, d;

  constructor(TFTWIDTH, TFTHEIGHT);

  //reset();
  driver = id;
  unsigned char size = sizeof(ILI932x_regValues) / 4;
    for (unsigned char i = 0; i < size; i++) {
      //a = pgm_read_word(ILI932x_regValues + i*2);
      //d = pgm_read_word(ILI932x_regValues + i*2 + 1);
      a = ILI932x_regValues[i*2];
      d = ILI932x_regValues[i*2+1];
      if (a == 0xFF) {
	delay(d);
      } else {
	writeRegister(a, d);
	//SerialUSB.print("addr: "); SerialUSB.print(a); 
	//SerialUSB.print(" data: "); SerialUSB.println(d, HEX);
      }
    }
}

/********************************* low level pin initialization */
Adafruit_TFTLCD::Adafruit_TFTLCD() {
   
  //init GPIO
  gpio_init(GPIOA);
  gpio_init(GPIOB);  
  //gpio_init(GPIOC); <- kills SerialUSB

  rotation = 0;
  _width = TFTWIDTH;
  _height = TFTHEIGHT;

  // disable the LCD
  pinMode(CS_p, OUTPUT);  
  digitalWrite(CS_p, HIGH);
  
  pinMode(RS_p, OUTPUT);  
  digitalWrite(RS_p, HIGH);
 
  pinMode(WR_p, OUTPUT);  
  digitalWrite(WR_p, HIGH);
   
  pinMode(RD_p, OUTPUT);  
  digitalWrite(RD_p, HIGH);

  //Set not used but connected pins to LOW
  pinMode(5, OUTPUT);  
  digitalWrite(5, LOW);    
  pinMode(12, OUTPUT);  
  digitalWrite(12, LOW);

  pinMode(_reset, OUTPUT); 
  digitalWrite(_reset, HIGH); 

  setWriteDir();
  write8(0); 

  cursor_y = cursor_x = 0;
  textsize = 1;
  textcolor = 0xFFFF;
}



/********************************** low level pin interface */

void Adafruit_TFTLCD::reset(void) {
  if (_reset)
    digitalWrite(_reset, LOW);
  delay(10); 
  if (_reset)
    digitalWrite(_reset, HIGH);
  // resync
  writeData(0);
  writeData(0);
  writeData(0);  
  writeData(0);
}

inline void Adafruit_TFTLCD::setWriteDir(void) {
  unsigned char i = 8;
  while(i--) {
    gpio_set_mode(dports[i], dpins[i], GPIO_OUTPUT_PP ); 
  }
}

inline void Adafruit_TFTLCD::setReadDir(void) {
  unsigned char i = 8;
  while(i--) {
    gpio_set_mode(dports[i], dpins[i], GPIO_INPUT_FLOATING);    
  }
}

inline void Adafruit_TFTLCD::write8(unsigned char d) {

	//set all pins to low;
	GPIOA->regs->BRR =  MASK_PORTA;
	GPIOB->regs->BRR =  MASK_PORTB;

	//set pins to values defined in PortMask.h
	GPIOA->regs->BSRR = mask_A[d];
	GPIOB->regs->BSRR = mask_B[d];
}


inline unsigned char Adafruit_TFTLCD::read8(void) {
	unsigned char d=0;
	unsigned char i = 8;
	while(i--) {
		if (gpio_read_bit(dports[i], dpins[i]) << i) d |= (1 << i);
	}
 	return d;
}

/********************************** low level readwrite interface */

// the RS pin is high during write
void Adafruit_TFTLCD::writeData(unsigned int data) {
	/*WR_HIGH
	CS_LOW
	RS_HIGH
	RD_HIGH*/

	setWriteDir();
	write8((data&0xff00)>>8);


	WR_LOW
	WR_HIGH

	write8(data&0xff);

	WR_LOW
	WR_HIGH
	CS_HIGH 
}


// this is a 'sped up' version, with no direction setting, or pin initialization
// not for external usage, but it does speed up stuff like a screen fill
inline void Adafruit_TFTLCD::writeData_unsafe(unsigned int data) {
//	SerialUSB.print("writeData_unsafe: ");
//	SerialUSB.println(data, BIN);
	write8(data >> 8);

	WR_LOW
	WR_HIGH

	write8(data);

	WR_LOW
	WR_HIGH
}

// the C/D pin is low during write
void Adafruit_TFTLCD::writeCommand(unsigned int cmd) {
	WR_HIGH
	CS_LOW
	RS_LOW
	RD_HIGH
	
	setWriteDir();
	write8(0);

	WR_LOW
	WR_HIGH

    	write8(cmd);

	WR_LOW
	WR_HIGH
	RS_HIGH

}

unsigned int Adafruit_TFTLCD::readData() {
	unsigned int d = 0;

	WR_LOW
	CS_HIGH
	RS_LOW //low before
	RD_HIGH
	 
	setReadDir();

	RD_LOW

	//delayMicroseconds(10);
	d = read8() << 8;

	RD_HIGH
	//delayMicroseconds(10);	
	RD_LOW

	//delayMicroseconds(10);
	d |= read8();

	RD_HIGH
	RS_HIGH
	CS_HIGH
	
	return d;
}

/************************************* medium level data reading/writing */

unsigned int Adafruit_TFTLCD::readRegister(unsigned int addr) {
   /*writeCommand(addr);
   return readData();*/
    unsigned int data=0;

  	WR_HIGH
	CS_LOW
	RS_LOW
	RD_HIGH
	
	setWriteDir();
	write8(0);

	WR_LOW
	WR_HIGH

    	write8(addr);

	WR_LOW
	WR_HIGH
	RS_HIGH
	
	setReadDir();	

	RD_LOW
  	delayMicroseconds(10);
    	data |= read8()<<8;

	RD_HIGH
	RD_LOW
	
	delayMicroseconds(10);
   	data |= read8();

	RD_HIGH
	CS_HIGH
	return data;
}


void Adafruit_TFTLCD::writeRegister(unsigned int addr, unsigned int data) {
  writeCommand(addr);
  writeData(data);
}