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

void test256ByteSequence()
{
    int i=0;
    byte d;
   //get 512 random bytes... write to them.  read them 
   
   Serial.println("Testing Corner Cases");
   test256ByteBounds();
   
   randomSeed(analogRead(0));
   Serial.println("Testing Byte Sequence (24LC256) - 512 random bytes");
   for(i=0; i<512;i++)
   {
     randomNum = random(0,262143);//get random byte number
     mem_1.writeByte(randomNum, 0b10111101);
     d=mem_1.readByte(randomNum);
     Serial.print("Seq: "); Serial.print(i);
     Serial.print(" Address: "); Serial.print(randomNum);
     Serial.print(" Read Data: "); Serial.println(d, BIN);
   }
}

void test256ByteBounds()
{
  byte d;
  mem_1.writeByte(0, 0b10111101);
  d=mem_1.readByte(0);
  
  Serial.print(" Address: 0");
  Serial.print(" Read Data: "); Serial.println(d, BIN);
     
  mem_1.writeByte(262143, 0b10111101);
  d=mem_1.readByte(262143);
  
  Serial.print(" Address: 262143");
  Serial.print(" Read Data: "); Serial.println(d, BIN);
}

void test256PageSequence()
{
  
  int i=0;
  
  Serial.println("Testing Corner Cases");
  test256Page(0);
  test256Page(511);
  
  randomSeed(analogRead(0));
  Serial.println("Testing Page Sequence (24LC256) - 5 random pages");
  
  for(i=0;i<5;i++)
  {
    randomNum = random(0,511);//get random page number
    test256Page(randomNum);
  } 
}

void test256Page(int num)
{
   Serial.print("Operating on Page: "); Serial.println(num);
    Serial.println("Filling Buffer");
    fill256Buffer();
    Serial.println("Printing Buffer");
    print256Buffer();
    Serial.println("Writing Buffer to Page");
    mem_1.writePage(num,storage256);
    Serial.println("Clearing Buffer");
    clear256Buffer();
    Serial.println("Printing Buffer");
    print256Buffer();
    Serial.println("Reading Page to Buffer");
    mem_1.readPage(num,storage256);
    Serial.println("Printing Buffer");
    print256Buffer();
    Serial.println("Clearing Buffer");
    clear256Buffer();
    Serial.println("Printing Buffer");
    print256Buffer();
}

void fill256Buffer()
{ 
  int i=0;
  for(i=0; i<64;i++)
  {
    if(i%2==0)
    {
        storage256[i]=0b11001100 ;
    }
    else
    {
       storage256[i]=0b00110011; 
    }
  } 
}

void clear256Buffer()
{
  int i=0;
  for(i=0;i<64;i++)
  {
       storage256[i]=(byte)(0b00000000);
  }
}

void print256Buffer()
{
  int i=0;
  for(i=0;i<64;i++)
  {
    Serial.print("Byte: "); Serial.print(i);
    Serial.print(" Data: "); Serial.println(storage256[i],BIN);
  } 
}
