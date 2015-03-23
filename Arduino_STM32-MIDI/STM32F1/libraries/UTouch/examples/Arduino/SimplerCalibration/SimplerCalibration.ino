// UTouch_QuickDraw (C)2010-2012 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics

//Change "selector" to the # of the program you want to run:
//1: Map out the display coordinates
//2: Map out the touch screen coordinates

#define selector 1

#include <UTFT.h>
#include <UTouch.h>
extern uint8_t SmallFont[];

//for the Arduino Mega
UTFT        myGLCD(SSD1289,38,39,40,41);   // Remember to change the model parameter to suit your display module!
UTouch      myTouch(6,5,4,3,2);

long x, y;

void setup()
{
  myGLCD.InitLCD(LANDSCAPE);
  myGLCD.setFont(SmallFont);
  myGLCD.clrScr();

  myTouch.InitTouch(LANDSCAPE);
  myTouch.setPrecision(PREC_LOW);
}

void loop()
{
//Program 1
 if (selector == 1){
   myGLCD.setColor(255,255,255);
   y=0;
   for (x=0; x <= 320; x=x+5){ // change the 320 to your x resolution
     myGLCD.fillScr(0,0,0); //clear the screen
     myGLCD.printNumI(x,x,100);
     delay(100);
   }
   for (y=0; y <= 240; y=y+5){ //change the 240 to your y resolution
     myGLCD.fillScr(0,0,0); //clear the screen
     myGLCD.printNumI(y,100,y);
     delay(100);
   }
 }
  
 //Program 2
 if (selector == 2){
   while (myTouch.dataAvailable() == true){
     delay(50);  //This delay is crucial!!!
     myTouch.read();
     x = myTouch.getTouchX();
     y = myTouch.getTouchY();
     
     if (x!=-1 && y!=-1){
     myGLCD.fillScr(0,0,0); //clear the screen
     myGLCD.printNumI((int)x,100,120); //print the X location of the touch at 100,120   
     myGLCD.printNumI((int)y,100,150); //print the Y location of the touch at 100,150
     }
   }
 }
   
 //Program 3
 if (selector == 3){
   while (myTouch.dataAvailable() == true){
     delay(50);  //This delay is crucial!!!
     myTouch.read();
     x = myTouch.getX(); //scales and offsets in the .cpp file
     y = myTouch.getY(); //scales and offsets in the .cpp file
     
     if (x!=-1 && y!=-1){
     myGLCD.fillScr(0,0,0); //clear the screen
     myGLCD.printNumI((int)x,x,120); //print the X location of the touch at x,120   
     myGLCD.printNumI((int)y,100,y); //print the Y location of the touch at 100,y
     }
   }
 }
 
 //Program 4
 if (selector == 4){
   while (myTouch.dataAvailable() == true){
     delay(50);  //This delay is crucial!!!
     myTouch.read();
     x = myTouch.getX(); //scales and offsets in the .cpp file
     y = myTouch.getY(); //scales and offsets in the .cpp file
     
     if (x!=-1 && y!=-1){
       myGLCD.drawPixel (x, y);
     }
   }
 }
}
