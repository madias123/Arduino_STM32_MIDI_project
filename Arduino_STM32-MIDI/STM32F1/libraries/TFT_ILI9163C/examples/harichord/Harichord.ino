/*
  Compiled under Arduino 1.6.1  2015/04/01
  Adafruit code updated to use SPI DMA
    Sketch uses 29,048 bytes (26%) of program storage space. Maximum is 108,000 bytes.
    Global variables use 5,288 bytes of dynamic memory.

			OLD STM Port			non-DMA STM Port          STM DMA Port
ILI9341 Test!
Benchmark                Time (microseconds)		Time (microseconds)        Time (microseconds)
Screen fill              1,026,635			716,291                    174,901
Text                     74,910				46,087                      65,358
Lines                    702,724			400,688                    692,868
Horiz/Vert Lines         84,359				57,074                      23,342
Rectangles (outline)     54,489				36,604                      16,625
Rectangles (filled)      2,132,392			1,487,410                  371,832
Circles (filled)         344,984			220,662                    181,100
Circles (outline)        306,326			174,199                    302,904
Triangles (outline)      222,948			127,154                    219,106
Triangles (filled)       715,597			472,077                    243,512
Rounded rects (outline)  130,131			78,591                      91,564
Rounded rects (filled)   2,331,405			1,615,938                  488,708
Done!

https://github.com/hwiguna/g33k/blob/master/ArduinoProjects/128x64_OLED/HariChord/HariChord.ino 
 */


#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>

// Pinout for Maple Mini (// For the Adafruit shield, these are the default)
#define __CS 8
#define __RST 9
#define __DC 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
TFT_ILI9163C tft = TFT_ILI9163C(__CS, __DC, __RST); // Use hardware SPI

int nFrames = 100;    // higher number, slower full-cycle annimation

void setup() {

  tft.begin();
  tft.fillScreen(BLACK);
}


void loop(void) {
  
 
  for (int frame=0; frame < nFrames; frame++)
  {
    HariChord(frame);
  }

  tft.fillScreen(BLACK);

  for (int frame=(nFrames-1); frame >= 0; frame--)
  {
    HariChord(frame);
  }

  tft.fillScreen(BLACK);
}

void HariChord(int frame)
{
  static boolean flipflop = true;
  flipflop = !flipflop;
  int n = 7;
  int r = frame * 64 / nFrames;    // half  of 128
  float rot = frame * 2*PI / nFrames;
  for (int i=0; i<(n-1); i++)
  {
    float a = rot + i * 2*PI / n;
    int x1 = 64 + cos(a) * r;    // half 128
    int y1 = 64 + sin(a) * r;    // half 128
    for (int j=i+1; j<n; j++)
    {
      a = rot + j * 2*PI / n;
      int x2 = 64 + cos(a) * r;
      int y2 = 64 + sin(a) * r;
      if ( flipflop) tft.drawLine(x1,y1, x2,y2, (long) random(65535));
      if (!flipflop) tft.drawLine(x1,y1, x2,y2, (long) random(65535));
    }
  }
}
