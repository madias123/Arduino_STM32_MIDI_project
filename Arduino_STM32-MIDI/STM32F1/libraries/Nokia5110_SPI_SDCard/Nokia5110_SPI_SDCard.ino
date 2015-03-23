/*
  This implementation specific to Maple Mini and used with a NOKIA 5110 Craphic LCD and generic SD Card
  Note: that both Maple Mini and Nokia GLCD and SD Card operate at 3.3V
  Please refer to the ReadMe.h file (tab) for credits, links, and licensing information
*/

#include <Streaming.h>
#include <SPI.h>   // Using library SPI in folder: \Documents\Arduino\hardware\STM32\STM32F1XX\libraries\SPI
#include <SD.h>    // Using library SD in folder: \Program Files (x86)\Arduino_158\libraries\SD 
#include "NokiaLCD.h" // Nokia 5110 LCD pin usage as controlled by "ScrnFuncts.ino"
#include "SDcard.h"// Generic SD Card defines and constants

const int  BAUD = 9600;  // any standard serial value: 300 - 115200 (not used for SerialUSB)
char temp;

void setup(void)
  {
    pinMode(ContrastPin, INPUT);
    digitalWrite(ContrastPin, HIGH); // activate internal pullup resistor
    Serial.begin(BAUD);    // Maple SerialUSB .begin() is void... reminder for Serial1, 2, 3
    Serial << (F("(c) 2013 - 2014 by M. R. Burnette")) << endl;
    Serial << (F("Version 0.20140126")) << endl;

    LcdInitialise();
    LcdClear();
    LcdString(*msg0);
    delay(2000);
    LcdClear(); delay(500); nRow = 1;
    LcdString(*msg1);
    nRow = 0; nColumn = 0;
    gotoXY(nColumn, nRow);
    // wait with display until user sends a keystroke
    do {} while (Serial.available() == 0) ;
    LcdClear();  // nRow = 0; nColumn = 0 done by function LcdClear()
}


void loop(void)
{
    if (Serial.available() > 0)    // anything to put on the screen?
    {
      char temp = Serial.read();
      Serial << temp;              // for diagnostic and Arduino term echo
      switch (temp)                // the case routines can be expanded for control-sequences
        {
          case '\n' :
            ++nRow; nColumn = 0;
            if (nRow == 6) nRow = 0;
            LcdString(BlankLine[0]);  // clear line
            break;

          case '\r' :
            ++nRow; nColumn = 0;
            if (nRow == 6) nRow = 0;
            LcdString(BlankLine[0]);
            break;
            
           case '~' :    // mount or test for SD card logic
             nRow = 0; nColumn = 0;
             gotoXY(nColumn, nRow);
             SD_Card_Demo() ;
             nRow = 0; nColumn = 0;
             temp = Serial.read();
             temp = '\0' ;
             LcdString(BlankLine[0]);
             break;

            default :
            gotoXY(nColumn, nRow);
            if (nColumn == 0 ) LcdString(BlankLine[0]);
            if (temp > 31 && temp < 128) SendCharLCD(temp);
        }
    }
}

