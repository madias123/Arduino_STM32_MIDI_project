// change CS to match your SD shield or module;
// Arduino Ethernet shield:         pin  4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield:              pin  8
const int chipSelect = PB5;         // PB5 == D17 Maple Mini
/*
Note: The Maple SPI hardware library instantiates the following named pins on SPI channel 1:
           CLK PA5 == D6
          MISO PA6 == D5
          MOSI PA7 == D4
            CS ....== User-Defined Pin
*/

// Instantiate SD objects:
Sd2Card card;
SdVolume volume;
SdFile root;
