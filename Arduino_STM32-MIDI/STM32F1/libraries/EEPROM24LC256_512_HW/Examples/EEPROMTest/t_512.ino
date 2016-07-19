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

 //See output for actual operations of device
 
void test512ByteSequence()
{
    int i=0;
    byte d;
   //get 512 random bytes... write to them.  read them
   Serial.println("Testing Corner Cases");
   test512ByteBounds();
   
   randomSeed(analogRead(0));
   Serial.println("Testing Byte Sequence (24LC512) - 512 random bytes");
   for(i=0; i<512;i++)
   {
     randomNum = random(0,524287);//get random byte number
     mem_2.writeByte(randomNum, 0b10111101);
     d=mem_2.readByte(randomNum);
     Serial.print("Seq: "); Serial.print(i);
     Serial.print(" Address: "); Serial.print(randomNum);
     Serial.print(" Read Data: "); Serial.println(d, BIN);
   }
}

void test512ByteBounds()
{
  byte d;
  mem_2.writeByte(0, 0b10111101);
  d=mem_2.readByte(0);
  
  Serial.print(" Address: 0");
  Serial.print(" Read Data: "); Serial.println(d, BIN);
     
  mem_2.writeByte(524287, 0b10111101);
  d=mem_2.readByte(524287);
  
  Serial.print(" Address: 524287");
  Serial.print(" Read Data: "); Serial.println(d, BIN);
}

void test512PageSequence()
{
  
  int i=0;
  
  Serial.println("Testing Corner Cases");
  test512Page(0);
  test512Page(511);
  
  randomSeed(analogRead(0));
  Serial.println("Testing Page Sequence (24LC512) - 5 random pages");
  
  for(i=0;i<5;i++)
  {
    randomNum = random(0,511);//get random page number
    test512Page(randomNum);
  } 
}

void test512Page(int num)
{
   Serial.print("Operating on Page: "); Serial.println(num);
    Serial.println("Filling Buffer");
    fill512Buffer();
    Serial.println("Printing Buffer");
    print512Buffer();
    Serial.println("Writing Buffer to Page");
    mem_2.writePage(num,storage512);
    Serial.println("Clearing Buffer");
    clear512Buffer();
    Serial.println("Printing Buffer");
    print512Buffer();
    Serial.println("Reading Page to Buffer");
    mem_2.readPage(num,storage512);
    Serial.println("Printing Buffer");
    print512Buffer();
    Serial.println("Clearing Buffer");
    clear512Buffer();
    Serial.println("Printing Buffer");
    print512Buffer();
}

void fill512Buffer()
{ 
  int i=0;
  for(i=0; i<128;i++)
  {
    if(i%2==0)
    {
        storage512[i]=0b11001100 ;
    }
    else
    {
       storage512[i]=0b00110011; 
    }
  } 
}

void clear512Buffer()
{
  int i=0;
  for(i=0;i<128;i++)
  {
       storage512[i]=(byte)(0b00000000);
  }
}

void print512Buffer()
{
  int i=0;
  for(i=0;i<128;i++)
  {
    Serial.print("Byte: "); Serial.print(i);
    Serial.print(" Data: "); Serial.println(storage512[i],BIN);
  } 
}
