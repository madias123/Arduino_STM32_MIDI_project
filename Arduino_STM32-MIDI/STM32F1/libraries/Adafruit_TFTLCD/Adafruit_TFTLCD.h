// Graphics library by ladyada/adafruit with init code from Rossum 
// MIT license

#ifndef _ADAFRUIT_TFTLCD_H_
#define _ADAFRUIT_TFTLCD_H_


#include "WProgram.h"
#include "Adafruit_GFX.h"
#include <libmaple/gpio.h>

// register names from Peter Barrett's Microtouch code

#define ILI932X_START_OSC			0x00
#define ILI932X_DRIV_OUT_CTRL		0x01
#define ILI932X_DRIV_WAV_CTRL		0x02
#define ILI932X_ENTRY_MOD			0x03
#define ILI932X_RESIZE_CTRL			0x04
#define ILI932X_DISP_CTRL1			0x07
#define ILI932X_DISP_CTRL2			0x08
#define ILI932X_DISP_CTRL3			0x09
#define ILI932X_DISP_CTRL4			0x0A
#define ILI932X_RGB_DISP_IF_CTRL1	0x0C
#define ILI932X_FRM_MARKER_POS		0x0D
#define ILI932X_RGB_DISP_IF_CTRL2	0x0F
#define ILI932X_POW_CTRL1			0x10
#define ILI932X_POW_CTRL2			0x11
#define ILI932X_POW_CTRL3			0x12
#define ILI932X_POW_CTRL4			0x13
#define ILI932X_GRAM_HOR_AD			0x20
#define ILI932X_GRAM_VER_AD			0x21
#define ILI932X_RW_GRAM				0x22
#define ILI932X_POW_CTRL7			0x29
#define ILI932X_FRM_RATE_COL_CTRL	0x2B
#define ILI932X_GAMMA_CTRL1			0x30
#define ILI932X_GAMMA_CTRL2			0x31
#define ILI932X_GAMMA_CTRL3			0x32
#define ILI932X_GAMMA_CTRL4			0x35 
#define ILI932X_GAMMA_CTRL5			0x36
#define ILI932X_GAMMA_CTRL6			0x37
#define ILI932X_GAMMA_CTRL7			0x38
#define ILI932X_GAMMA_CTRL8			0x39
#define ILI932X_GAMMA_CTRL9			0x3C
#define ILI932X_GAMMA_CTRL10			0x3D
#define ILI932X_HOR_START_AD			0x50
#define ILI932X_HOR_END_AD			0x51
#define ILI932X_VER_START_AD			0x52
#define ILI932X_VER_END_AD			0x53
#define ILI932X_GATE_SCAN_CTRL1		0x60
#define ILI932X_GATE_SCAN_CTRL2		0x61
#define ILI932X_GATE_SCAN_CTRL3		0x6A
#define ILI932X_PART_IMG1_DISP_POS	0x80
#define ILI932X_PART_IMG1_START_AD	0x81
#define ILI932X_PART_IMG1_END_AD		0x82
#define ILI932X_PART_IMG2_DISP_POS	0x83
#define ILI932X_PART_IMG2_START_AD	0x84
#define ILI932X_PART_IMG2_END_AD		0x85
#define ILI932X_PANEL_IF_CTRL1		0x90
#define ILI932X_PANEL_IF_CTRL2		0x92
#define ILI932X_PANEL_IF_CTRL3		0x93
#define ILI932X_PANEL_IF_CTRL4		0x95
#define ILI932X_PANEL_IF_CTRL5		0x97
#define ILI932X_PANEL_IF_CTRL6		0x98

#define HX8347G_COLADDRSTART2 0x02
#define HX8347G_COLADDRSTART1 0x03
#define HX8347G_COLADDREND2 0x04
#define HX8347G_COLADDREND1 0x05

#define HX8347G_ROWADDRSTART2 0x06
#define HX8347G_ROWADDRSTART1 0x07
#define HX8347G_ROWADDREND2 0x08
#define HX8347G_ROWADDREND1 0x09

#define TFTLCD_DELAYCMD                 0xFF

#define swap(a, b) { int t = a; a = b; b = t; }

class Adafruit_TFTLCD: public Adafruit_GFX {
 public:
  //Adafruit_TFTLCD(unsigned char cs, unsigned char cd, unsigned char wr, unsigned char rd, unsigned char reset);
  Adafruit_TFTLCD(void);

  unsigned int Color565(unsigned char r, unsigned char g, unsigned char b);

  // drawing primitives!
  void drawPixel(int x, int y, unsigned int color);
  void fillScreen(unsigned int color);
  void drawFastVLine(int x0, int y0, int length, unsigned int color);
  void drawFastHLine(int x0, int y0, int length, unsigned int color);

  void fillRect(int x0, int y0, int w, int h, unsigned int color);

  // commands
  void begin(unsigned int id = 0x9325);
  void goTo(int x, int y);
  void reset(void);

  /* low level */

  void writeData(unsigned int d);
  void writeCommand(unsigned int c);
  unsigned int readData(void);
  unsigned int readRegister(unsigned int addr);
  void writeRegister(unsigned int addr, unsigned int data);

  static const unsigned int TFTWIDTH = 240;
  static const unsigned int TFTHEIGHT = 320;

  void writeData_unsafe(unsigned int d);

  void setWriteDir(void);
  void setReadDir(void);
  void write8(unsigned char d);

 private:

  unsigned int driver;

  void drawFastLine(int x0, int y0, int l, unsigned int color, unsigned char flag);
  
  unsigned char read8(void);

  unsigned char _cs, _cd, _reset, _wr, _rd;

  unsigned char csport, cdport, wrport, rdport;
  unsigned char cspin, cdpin, wrpin, rdpin;
};

#endif