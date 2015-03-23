/* Nokia GLCD
SOFTWARE SPI (using Maple Mini hardware SPI 2 Pins)
--------MapleMini----/Notes---------------------/-Nokia- */
#define PIN_SCE   31  // CE (Active High)          pin 2
#define PIN_RESET 30  // Reset (Active Lo)         pin 1
#define PIN_DC    29  // Data==1 Command==0        pin 3
#define PIN_SDIN  28  //  MOSI/DIN                 pin 4
#define PIN_SCLK  27  // CLK/clock                 pin 5

#define LCD_C     LOW
#define LCD_D     HIGH
#define LCD_X     84
#define LCD_Y     48

// global GLCD variables
byte nRow;                          // line count      (0-5 for NOKIA LCD = 6 lines)
byte nColumn;                       // character count (0-11 for NOKIA LCD= 12 chars)
byte NOKIAcontrast         = 0xBE;  // LCD initialization contrast values B0 thru BF
const byte ContrastPin     = 8;     // D8 low activates the Contrast adjustment

// Various static Screen messages
// Screen line....             012345678901 == 12 characters out of 72 char screen == 6 lines
char* msg0[] PROGMEM       = {"TerminalTest(C)2014 by  M. Burnette                         Ver 0.000000"}; // 72 characters == full screen
char* msg1[] PROGMEM       = {"Maple Mini  Serial Mon. Type ~ tildeto check SD card status Press AnyKey"};
char* msg2[] PROGMEM       = {"InitializingSD Card....."} ; // 2 lines
char* msg3[] PROGMEM       = {"Init failed!Insert or   "} ;
char* msg4[] PROGMEM       = {"Reseat Card."} ;             // 1 line
char* msg5[] PROGMEM       = {"Serial Ready"} ;
char* msg6[] PROGMEM       = {"All is OK..."} ;
char* BlankLine[] PROGMEM  = {"            "};  // Nokia 12 x 6 (84 * 48)

