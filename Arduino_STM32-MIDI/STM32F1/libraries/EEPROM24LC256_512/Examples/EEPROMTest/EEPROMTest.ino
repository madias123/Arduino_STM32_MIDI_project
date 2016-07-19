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


#include <Wire.h>
#include <EEPROM24LC256_512.h>

unsigned int randomNum=0;

//define eeprom chip (1 per chip)
EEPROM256_512 mem_1;
EEPROM256_512 mem_2;

//arrays act as buffers for the EEPROM Chips
byte storage256[64];
byte storage512[128];

void setup() {

  //begin I2C Bus
  Wire.begin();
  
  //begin EEPROM with I2C Address 
  mem_1.begin(0,0);//addr 0 (DEC) type 0 (defined as 24LC256)
  
  mem_2.begin(1,1);//addr 1 (DEC) type 1 (defined as 24LC512)
  
  //begin serial for test driver output
  Serial.begin(9600);
  
  //Test 24LC256 Chip
  Test256();
  
  //Test 24LC512 Chip
  Test512();
}

void Test256()
{
  //print page size
  Serial.print("24LC256 Page Size: ");
  Serial.println(mem_1.getPageSize());
  
  //exercise byte write/read
  test256ByteSequence();
  
  //exercise page write/read
  test256PageSequence();
}

void Test512()
{
  //print page size
  Serial.print("24LC512 Page Size: ");
  Serial.println(mem_2.getPageSize());
  
  //exercise byte write/read
  test512ByteSequence();
  
  //exercise page write/read
  test512PageSequence();
}

void loop() {/*Run once Application*/}
