
// written by mrburnette
void SendCharLCD( char temp ) {
  gotoXY(nColumn * 7, nRow); // Nokia LCD function to place character 6 lines of 12 characters in font
  LcdCharacter ( temp ); 
  ++nColumn;
  if (nColumn >= 12) {  // lines fill to 12 characters and increase through line 6 then line 1 is cleared
    nColumn = 0;
    nRow = ++nRow % 6;
    gotoXY(nColumn, nRow);
  }
}

void SD_Card_Demo( void )
{
   LcdClear();  // also resets nRow, nColumn
   LcdString(*msg2);
   Serial.print(F("\nInitializing SD card..."));
  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, chipSelect))
  {
    nRow = 0; nColumn = 0; gotoXY(nColumn, nRow);
    LcdString(*msg3);
    LcdString(*msg4);
    nRow = 4;
    gotoXY(nColumn, nRow);
    LcdString(*msg5);
    Serial.println(F("initialization failed. Things to check:"));
    Serial.println(F("* is a card is inserted?"));
    Serial.println(F("* Is your wiring correct?"));
    Serial.println(F("* did you change the chipSelect pin to match your shield or module?"));
  } 
  else 
  {
    LcdString(*msg6);
    nRow = 4;
    gotoXY(nColumn, nRow);
    LcdString(*msg5);
    Serial.println(F("Wiring is correct and a card is present."));
    Serial.print(F("\nCard type: "));
    switch (card.type())
    {
      case SD_CARD_TYPE_SD1:
        Serial.println(F("SD1"));
        break;
      case SD_CARD_TYPE_SD2:
        Serial.println(F("SD2"));
        break;
      case SD_CARD_TYPE_SDHC:
        Serial.println(F("SDHC"));
        break;
      default:
        Serial.println(F("Unknown"));
  }
}

/* =============================Stock functions from SD library example program ============================ */
  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card))
  {
    Serial.println(F("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card"));
    return;
  }
  
  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print(F("\nVolume type is FAT"));
  Serial.println(volume.fatType(), DEC);
  Serial.println();

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize *= 512;                            // SD card blocks are always 512 bytes
  Serial.print(F("Volume size (bytes): "));
  Serial.println(volumesize);
  Serial.print(F("Volume size (Kbytes): "));
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print(F("Volume size (Mbytes): "));
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.println(F("\nFiles found on the card (name, date and size in bytes): "));
  root.openRoot(volume);

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);
}

