/*
#include <FatStructs.h>
#include <Sd2Card.h>
#include <Sd2PinMap.h>
#include <SdFatmainpage.h>
#include <SdFatUtil.h>
#include <SdInfo.h>
*/

#include <SdFat.h>
#include <HardwareSPI.h>
#include <stdint.h>

HardwareSPI spi(1);
Sd2Card card;
SdVolume volume;
SdFile root;
SdFile file;

void setup() 
{
  SerialUSB.begin();
  spi.begin(SPI_281_250KHZ, MSBFIRST, 0);
  SerialUSB.println("type any char to start");
  while (!SerialUSB.available());
  SerialUSB.println();

  if (!card.init(&spi)) 
    SerialUSB.println("card.init failed");
  else
    SerialUSB.println("card.init passed");
//  spi.end();
  
//  spi.begin(SPI_9MHZ, MSBFIRST, 0);
  spi.begin(SPI_4_5MHZ, MSBFIRST, 0);
  
  delay(100);
  
  // initialize a FAT volume
  if (!volume.init(&card,1)) 
    SerialUSB.println("volume.init failed");
  else
    SerialUSB.println("volume.init passed");
    
  // open the root directory
  if (!root.openRoot(&volume)) 
    SerialUSB.println("openRoot failed");
  else
    SerialUSB.println("openRoot passed");
    
  // open a file
  if (file.open(&root, "Read.txt", O_READ)) 
  {
    SerialUSB.println("Opened Read.txt");
    for(int i=0; i<15; i++)
      SerialUSB.print((char)file.read());
    SerialUSB.println("");
  }
  else
  {
    SerialUSB.println("file.open failed");
  }
  SerialUSB.println();  
  
  int16_t n;
  uint8_t buf[7];// nothing special about 7, just a lucky number.
  while ((n = file.read(buf, sizeof(buf))) > 0) 
  {
    for (uint8_t i = 0; i < n; i++) 
      SerialUSB.print(buf[i]);
  }
  /* easier way
  int16_t c;
  while ((c = file.read()) > 0) Serial.print((char)c);
  */
  SerialUSB.println("\nDone");
  spi.end();
  
}

void loop() 
{
}


