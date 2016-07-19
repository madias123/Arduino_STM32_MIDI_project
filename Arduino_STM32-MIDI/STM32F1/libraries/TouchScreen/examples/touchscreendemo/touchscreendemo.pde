// Touch screen library with X Y and Z (pressure) readings as well
// as oversampling to avoid 'bouncing'
// This demo code returns raw readings, public domain

#include <stdint.h>
#include "TouchScreen.h"

#define YP 18  // must be an analog pin
#define XM 17  // must be an analog pin
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 361);

void setup(void) {
}

void loop(void) {
  // a point object holds x y and z coordinates
  Point p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > ts.pressureThreshhold) {
     SerialUSB.print("X = "); SerialUSB.print(p.x);
     SerialUSB.print("\tY = "); SerialUSB.print(p.y);
     SerialUSB.print("\tPressure = "); SerialUSB.println(p.z);
  }

  delay(1);   // 1ms better results for maple
}
