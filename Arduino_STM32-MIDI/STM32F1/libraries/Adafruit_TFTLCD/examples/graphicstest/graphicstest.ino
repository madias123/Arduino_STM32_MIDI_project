#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <stdint.h>

// Color definitions
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0 
#define WHITE           0xFFFF


Adafruit_TFTLCD tft;

void setup(void) {
  //disableDebugPorts();
  delay(1000);
  Serial2.println("8 Bit LCD test!");
     tft.reset();

   delay(1000);
  Serial2.println("reset done");
   delay(1000); 
  uint16 identifier = tft.readRegister(0x0);
   delay(1000);
  
  Serial2.println(identifier, HEX);
   delay(1000);
  if (identifier == 0x9325) {
    Serial2.println("Found ILI9325");
  } else if (identifier == 0x9328) {
    Serial2.println("Found ILI9328");
  } else if (identifier == 0x7575) {
    Serial2.println("Found HX8347G");
  } else {
    Serial2.print("Unknown driver chip ");
    Serial2.println(identifier, HEX);
    while (1);
  }  
 
  tft.begin(identifier);
  
  int time = millis();
  testtext(RED);
  Serial2.println(millis() - time);
  delay(2000);
  time = millis();
  testlines(CYAN);
  Serial2.println(millis() - time);
  delay(500);
  time = millis();
  testfastlines(RED, BLUE);
  Serial2.println(millis() - time);
  delay(500);
  testdrawrects(GREEN);
  delay(500);
  testfillrects(YELLOW, MAGENTA);
  delay(500);
  tft.fillScreen(BLACK);
  testfillcircles(10, MAGENTA);
  testdrawcircles(10, WHITE);
  delay(500); 
  testtriangles();
  delay(500); 
  testfilltriangles();
  delay(500); 
  testRoundRect();
  delay(500); 
  testFillRoundRect(); 
}

void loop(void) {
  for (unsigned char rotation=0; rotation<4; rotation++) {
    tft.setRotation(rotation); 
    testtext(RED);
    delay(1000);
  }
}



void testFillRoundRect() {
  tft.fillScreen(BLACK);
  
  for (int x=tft.width(); x > 20 ; x-=6) {
    tft.fillRoundRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, x/8,  tft.Color565(0, x, 0));
 }
}

void testRoundRect() {
  tft.fillScreen(BLACK);
  
  for (int x=0; x < tft.width(); x+=6) {
    tft.drawRoundRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, x/8, tft.Color565(x, 0, 0));
 }
}

void testtriangles() {
  tft.fillScreen(BLACK);
  for (int i=0; i<tft.width()/2; i+=5) {
    tft.drawTriangle(tft.width()/2, tft.height()/2-i,
                     tft.width()/2-i, tft.height()/2+i,
                     tft.width()/2+i, tft.height()/2+i, tft.Color565(0, 0, i));
  }
}

void testfilltriangles() {
  tft.fillScreen(BLACK);
  
  for (int i=tft.width()/2; i>10; i-=5) {
    tft.fillTriangle(tft.width()/2, tft.height()/2-i,
                     tft.width()/2-i, tft.height()/2+i,
                     tft.width()/2+i, tft.height()/2+i, 
                     tft.Color565(0, i, i));
    tft.drawTriangle(tft.width()/2, tft.height()/2-i,
                     tft.width()/2-i, tft.height()/2+i,
                     tft.width()/2+i, tft.height()/2+i, tft.Color565(i, i, 0));    
  }
}
void testtext(unsigned int color) {
  tft.fillScreen(BLACK);
  tft.setCursor(0, 20);
  tft.setTextColor(color);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
}

void testfillcircles(unsigned char radius, unsigned int color) {
  for (unsigned int x=radius; x < tft.width(); x+=radius*2) {
    for (unsigned int y=radius; y < tft.height(); y+=radius*2) {
      tft.fillCircle(x, y, radius, color);
    }
  }  
}

void testdrawcircles(unsigned char radius, unsigned int color) {
  for (unsigned int x=0; x < tft.width()+radius; x+=radius*2) {
    for (unsigned int y=0; y < tft.height()+radius; y+=radius*2) {
      tft.drawCircle(x, y, radius, color);
    }
  }  
}


void testfillrects(unsigned int  color1, unsigned int  color2) {
 tft.fillScreen(BLACK);
 for (int x=tft.width()-1; x > 6; x-=6) {
   //Serial.println(x, DEC);
   tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
   tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
 }
}

void testdrawrects(unsigned int  color) {
 tft.fillScreen(BLACK);
 for (int x=0; x < tft.width(); x+=6) {
   tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
 }
}

void testfastlines(unsigned int  color1, unsigned int  color2) {
   tft.fillScreen(BLACK);
   for (int y=0; y < tft.height(); y+=5) {
     tft.drawFastHLine(0, y, tft.width(), color1);
   }
   for (int x=0; x < tft.width(); x+=5) {
     tft.drawFastVLine(x, 0, tft.height(), color2);
   }
  
}

void testlines(unsigned int  color) {
   tft.fillScreen(BLACK);
   for (int x=0; x < tft.width(); x+=6) {
     tft.drawLine(0, 0, x, tft.height()-1, color);
   }
   for (int y=0; y < tft.height(); y+=6) {
     tft.drawLine(0, 0, tft.width()-1, y, color);
   }
   
   tft.fillScreen(BLACK);
   for (int x=0; x < tft.width(); x+=6) {
     tft.drawLine(tft.width()-1, 0, x, tft.height()-1, color);
   }
   for (int y=0; y < tft.height(); y+=6) {
     tft.drawLine(tft.width()-1, 0, 0, y, color);
   }
   
   tft.fillScreen(BLACK);
   for (int x=0; x < tft.width(); x+=6) {
     tft.drawLine(0, tft.height()-1, x, 0, color);
   }
   for (int y=0; y < tft.height(); y+=6) {
     tft.drawLine(0, tft.height()-1, tft.width()-1, y, color);
   }

   tft.fillScreen(BLACK);
   for (int x=0; x < tft.width(); x+=6) {
     tft.drawLine(tft.width()-1, tft.height()-1, x, 0, color);
   }
   for (int y=0; y < tft.height(); y+=6) {
     tft.drawLine(tft.width()-1, tft.height()-1, 0, y, color);
   }
}


void testBars() {
  int i,j;
  for(i=0; i < tft.height(); i++)
  {
    for(j=0; j < tft.width(); j++)
    {
      if(i>279) tft.writeData(WHITE);
      else if(i>239) tft.writeData(BLUE);
      else if(i>199) tft.writeData(GREEN);
      else if(i>159) tft.writeData(CYAN);
      else if(i>119) tft.writeData(RED);
      else if(i>79) tft.writeData(MAGENTA);
      else if(i>39) tft.writeData(YELLOW);
      else tft.writeData(BLACK);
    }
  }
}