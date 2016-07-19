/*************************************************** 
  This is a library for the 24LC256 & 24LC512 i2c EEPROM under the
  Arduino Platform.
  
  It provides an easy way to use the above chips while supplying 
  the functionality to read and write pages (64 or 128 bytes) and 
  individual bytes to a page number or address on the EEPROM.
  
  Each page is written in a 16 byte burst mode to account for the
  buffer limit of the Wire library in the Arduino Platform.

  This library is to be used "as-is" without warranty. Please report
  bugs to the GitHub Project.
  
  Written by Michael Neiderhauser.  October 10, 2012
  LGPL license, all text above must be included in any redistribution
 ****************************************************/

#ifndef EEPROM24LC256_512_H
#define EEPROM24LC256_512_H

#define PAGE256 64
#define PAGE512 128
#define MINIBUFFER 16
#define MODE_256 0
#define MODE_512 1
#define I2CBASEADDR 0x50

class EEPROM256_512
{
public:
	EEPROM256_512();//constructor
	~EEPROM256_512();//deconstructor
	void begin(uint8_t addr, uint8_t mode);
	uint8_t readByte(unsigned int addr);
	void writeByte(unsigned int addr, uint8_t data);
	void readPage(unsigned int page_number, uint8_t* data);
	void writePage(unsigned int page_number, uint8_t* data);
	int getPageSize();
	uint8_t fulladdr;
	
private:
	void readMiniBuffer(unsigned int addr);
	void writeMiniBuffer(unsigned int addr);
	uint8_t minibuffer[MINIBUFFER];
	int page_size;	
};//end class


class EEPROM256 : public EEPROM256_512
{
public:
	EEPROM256(); //constructor
	~EEPROM256(); //deconstructor
	void begin(uint8_t addr);
};//end class


class EEPROM512 : public EEPROM256_512
{
public:
	EEPROM512(); //constructor
	~EEPROM512(); //deconstructor
	void begin(uint8_t addr);
};//end class


#endif