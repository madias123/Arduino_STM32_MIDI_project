
#include "SPI.h"
#include <UTFT_fast.h>

extern uint8_t SmallFont[];
UTFT tft(TFT01_24SP,4,6,7,1,0);                // ElecFreaks TFT01-2.4SP

void setup() {
  randomSeed(analogRead(0));
  tft.InitLCD(LANDSCAPE);
  tft.setFont(SmallFont);
 
//  tft.begin();

  // read diagnostics (optional but can help debug problems)
//  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
//  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
//  x = tft.readcommand8(ILI9341_RDMADCTL);
//  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
//  x = tft.readcommand8(ILI9341_RDPIXFMT);
//  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
//  x = tft.readcommand8(ILI9341_RDIMGFMT);
//  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
//  x = tft.readcommand8(ILI9341_RDSELFDIAG);
//  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); 
    uint32 sTime;
  int buf[318];
  int x, x2;
  int y, y2;
  int r;
  sTime = millis();
// Clear the screen and draw the frame
  tft.clrScr();

  tft.setColor(255, 0, 0);
  tft.fillRect(0, 0, 319, 13);
  tft.setColor(64, 64, 64);
  tft.fillRect(0, 226, 319, 239);
  tft.setColor(255, 255, 255);
  tft.setBackColor(255, 0, 0);
  tft.print("* Universal Color TFT Display Library *", CENTER, 1);
  tft.setBackColor(64, 64, 64);
  tft.setColor(255,255,0);
  tft.print("<http://electronics.henningkarlsen.com>", CENTER, 227);

  tft.setColor(0, 0, 255);
  tft.drawRect(0, 14, 319, 225);

// Draw crosshairs
  tft.setColor(0, 0, 255);
  tft.setBackColor(0, 0, 0);
  tft.drawLine(159, 15, 159, 224);
  tft.drawLine(1, 119, 318, 119);
  for (int i=9; i<310; i+=10)
    tft.drawLine(i, 117, i, 121);
  for (int i=19; i<220; i+=10)
    tft.drawLine(157, i, 161, i);

  delay(5000);
  Serial.println("ILI9341 Test!"); 

  Serial.println(tft.disp_y_size); 
  Serial.println(tft.disp_x_size); 

  Serial.println(F("Benchmark                Time (microseconds)"));

  Serial.print(F("Screen fill              "));
  Serial.println(testFillScreen());
  delay(500);
/*
  Serial.print(F("Text                     "));
  Serial.println(testText());
  delay(3000);
*/
  Serial.print(F("Lines                    "));
  Serial.println(testLines(VGA_AQUA));
  delay(500);

  Serial.print(F("Horiz/Vert Lines         "));
  Serial.println(testFastLines(VGA_RED, VGA_BLUE));
  delay(1500);

  Serial.print(F("Rectangles (outline)     "));
  Serial.println(testRects(VGA_GREEN));
  delay(1500);

  Serial.print(F("Rectangles (filled)      "));
  Serial.println(testFilledRects(VGA_WHITE, VGA_FUCHSIA));
  delay(1000);

  Serial.print(F("Circles (filled)         "));
  Serial.println(testFilledCircles(10, VGA_FUCHSIA));

  Serial.print(F("Circles (outline)        "));
  Serial.println(testCircles(10, VGA_WHITE));
  delay(500);
/*
  Serial.print(F("Triangles (outline)      "));
  Serial.println(testTriangles());
  delay(500);

  Serial.print(F("Triangles (filled)       "));
  Serial.println(testFilledTriangles());
  delay(500);
*/
  Serial.print(F("Rounded rects (outline)  "));
  Serial.println(testRoundRects());
  delay(500);

  Serial.print(F("Rounded rects (filled)   "));
  Serial.println(testFilledRoundRects());
  delay(500);

  Serial.println(F("Done!"));

}


void loop(void) {
/*
  for(uint8_t rotation=0; rotation<4; rotation++) {
    tft.setRotation(rotation);
    testText();
    delay(1000);

  }*/
}

unsigned long testFillScreen() {
  unsigned long start = micros();
  tft.clrScr();
  tft.fillScr(VGA_BLACK);
  tft.fillScr(VGA_RED);
  tft.fillScr(VGA_GREEN);
  tft.fillScr(VGA_BLUE);
  tft.fillScr(VGA_BLACK);
  return micros() - start;
}
/*
unsigned long testText() {
  tft.fillScreen(ILI9341_BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(ILI9341_RED);    tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");
  return micros() - start;
}
*/
unsigned long testLines(uint16_t color) {
  unsigned long start, t;
  int           x1, y1, x2, y2,
                w = tft.disp_y_size,
                h = tft.disp_x_size;
  tft.setColor(color);
  tft.fillScr(VGA_BLACK);

  x1 = y1 = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2);
  t     = micros() - start; // fillScreen doesn't count against timing

  tft.fillScr(VGA_BLACK);

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2);
  t    += micros() - start;

  tft.fillScr(VGA_BLACK);

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2);
  t    += micros() - start;

  tft.fillScr(VGA_BLACK);

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2);

  return micros() - start;
}

unsigned long testFastLines(uint16_t color1, uint16_t color2) {
  unsigned long start;
  int           x, y, w = tft.disp_y_size, h = tft.disp_x_size;

  tft.fillScr(VGA_BLACK);
  start = micros();
  tft.setColor(color1);
  for(y=0; y<h; y+=5) tft.drawHLine(0, y, w);
  tft.setColor(color2);
  for(x=0; x<w; x+=5) tft.drawVLine(x, 0, h);

  return micros() - start;
}

unsigned long testRects(uint16_t color) {
  unsigned long start;
  int           n, i, i2,
                cx = tft.disp_y_size /2,
                cy = tft.disp_x_size /2;

  tft.setColor(color);
  tft.fillScr(VGA_BLACK);
  n     = min(tft.disp_y_size, tft.disp_x_size);
  start = micros();
  for(i=2; i<n; i+=6) {
    i2 = i / 2;
    tft.drawRect( cx-i2, cy-i2,cx+i2, cy+i2);
  }

  return micros() - start;
}
/*
unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = tft.disp_y_size  / 2 - 1,
                cy = tft.disp_x_size  / 2 - 1;

  tft.fillScr(VGA_BLACK);
  n     = min(tft.disp_y_size, tft.disp_x_size);
  for(i=n; i>0; i-=6) {
    i2    = i / 2;
    start = micros();
    tft.fillRect(cx-i2, cy-i2, i, i, color1);
    t    += micros() - start;
    // Outlines are not included in timing results
    tft.drawRect(cx-i2, cy-i2, i, i, color2);
  }

  return t;
}

*/
unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = tft.disp_y_size / 2 -1,
                cy = tft.disp_x_size / 2 -1;

  tft.fillScr(VGA_BLACK);
  n     = min(tft.disp_y_size, tft.disp_x_size);
  for(i=n; i>0; i-=6) {
    i2    = i / 2;
    start = micros();
    tft.setColor(color1);
    tft.fillRect(cx-i2, cy-i2, cx+i2, cy+i2);
    t    += micros() - start;
    // Outlines are not included in timing results
    tft.setColor(color2);
    tft.drawRect(cx-i2, cy-i2, cx+i2, cy+i2);
  }

  return t;
}

unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int x, y, w = tft.disp_y_size, h = tft.disp_x_size, r2 = radius * 2;

  tft.setColor(color);
  tft.fillScr(VGA_BLACK);
  start = micros();
  for(x=radius; x<w; x+=r2) {
    for(y=radius; y<h; y+=r2) {
      tft.fillCircle(x, y, radius);
    }
  }

  return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int           x, y, r2 = radius * 2,
                w = tft.disp_y_size  + radius,
                h = tft.disp_x_size + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  tft.setColor(color);
  start = micros();
  for(x=0; x<w; x+=r2) {
    for(y=0; y<h; y+=r2) {
      tft.drawCircle(x, y, radius);
    }
  }

  return micros() - start;
}
/*
unsigned long testTriangles() {
  unsigned long start;
  int           n, i, cx = tft.disp_y_size  / 2 - 1,
                      cy = tft.disp_x_size / 2 - 1;

  tft.fillScreen(VGA_BLACK);
  n     = min(cx, cy);
  start = micros();
  for(i=0; i<n; i+=5) {
    tft.drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      tft.color565(0, 0, i));
  }

  return micros() - start;
}

unsigned long testFilledTriangles() {
  unsigned long start, t = 0;
  int           i, cx = tft.width()  / 2 - 1,
                   cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  start = micros();
  for(i=min(cx,cy); i>10; i-=5) {
    start = micros();
    tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft.color565(0, i, i));
    t += micros() - start;
    tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft.color565(i, i, 0));
  }

  return t;
}*/

unsigned long testRoundRects() {
  unsigned long start;
  int           w, i, i2,
                cx = tft.disp_y_size  / 2 - 1,
                cy = tft.disp_x_size / 2 - 1;

  tft.fillScr(VGA_BLACK);
  w     = min(tft.disp_y_size, tft.disp_x_size);
  start = micros();
  for(i=0; i<w; i+=6) {
    i2 = i / 2;
    tft.setColor(i,0, 0);
    tft.drawRoundRect(cx-i2, cy-i2, cx+i2, cy+i2);
  }

  return micros() - start;
}

unsigned long testFilledRoundRects() {
  unsigned long start;
  int           i, i2,
                cx = tft.disp_y_size  / 2 - 1,
                cy = tft.disp_x_size / 2 - 1;

  tft.fillScr(VGA_BLACK);
  start = micros();
  for(i=min(tft.disp_y_size, tft.disp_x_size); i>20; i-=6) {
    i2 = i / 2;
    tft.setColor(0, i, 0);
    tft.fillRoundRect(cx-i2, cy-i2, cx+i2, cy+i2);
  }

  return micros() - start;
}

