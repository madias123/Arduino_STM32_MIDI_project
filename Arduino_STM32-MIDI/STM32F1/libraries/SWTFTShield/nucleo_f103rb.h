#ifndef _UNO_24_SHIELD_
#define _UNO_24_SHIELD_

// Code provided by Smoke And Wires
// http://www.smokeandwires.co.nz
// This code has been taken from the Adafruit TFT Library and modified
//  by us for use with our TFT Shields / Modules
// For original code / licensing please refer to
// https://github.com/adafruit/TFTLCD-Library
 

// This header file serves two purposes:
//
// 1) Isolate non-portable MCU port- and pin-specific identifiers and
//    operations so the library code itself remains somewhat agnostic
//    (PORTs and pin numbers are always referenced through macros).
//
// 2) GCC doesn't always respect the "inline" keyword, so this is a
//    ham-fisted manner of forcing the issue to minimize function calls.
//    This sometimes makes the library a bit bigger than before, but fast++.
//    However, because they're macros, we need to be SUPER CAREFUL about
//    parameters -- for example, write8(x) may expand to multiple PORT
//    writes that all refer to x, so it needs to be a constant or fixed
//    variable and not something like *ptr++ (which, after macro
//    expansion, may increment the pointer repeatedly and run off into
//    la-la land).  Macros also give us fine-grained control over which
//    operations are inlined on which boards (balancing speed against
//    available program space).




// Smoke And Wires 2.4 Shield pin usage:
// LCD Data Bit :    7    6    5    4    3    2    1    0
// Digital pin #:    7    6    5    4    3    2    9    8
// Uno port/pin :  PD7  PD6  PD5  PD4  PD3  PD2  PB1  PB0

#define LCD_CS 19 // Chip Select goes to Analog 3
#define LCD_CD 18 // Command/Data goes to Analog 2
#define LCD_WR 17 // LCD Write goes to Analog 1
#define LCD_RD 16 // LCD Read goes to Analog 0

#define LCD_RESET 20 // Can alternately just connect to Arduino's reset pin
// Pixel read operations require a minimum 400 nS delay from RD_ACTIVE
// to polling the input pins.  At 16 MHz, one machine cycle is 62.5 nS.
// This code burns 7 cycles (437.5 nS) doing nothing; the RJMPs are
// equivalent to two NOPs each, final NOP burns the 7th cycle, and the
// last line is a radioactive mutant emoticon.
#define DELAY7   
/*\
  asm volatile(       \
    "rjmp .+0" "\n\t" \
    "rjmp .+0" "\n\t" \
    "rjmp .+0" "\n\t" \
    "nop"      "\n"   \
    ::);
 */


  // // These set the PORT directions as required before the write and read
  // // operations.  Because write operations are much more common than reads,
  // // the data-reading functions in the library code set the PORT(s) to
  // // input before a read, and restore them back to the write state before
  // // returning.  This avoids having to set it for output inside every
  // // drawing method.  The default state has them initialized for writes.
  // #define setWriteDirInline() { DDRD |=  B11010000; DDRB |=  B00101111; }
  // #define setReadDirInline()  { DDRD &= ~B11010000; DDRB &= ~B00101111; }

#define BIT0_MSK_8BIT  B00000001
#define BIT1_MSK_8BIT  B00000010
#define BIT2_MSK_8BIT  B00000100
#define BIT3_MSK_8BIT  B00001000
#define BIT4_MSK_8BIT  B00010000
#define BIT5_MSK_8BIT  B00100000
#define BIT6_MSK_8BIT  B01000000
#define BIT7_MSK_8BIT  B10000000
 //
// Write port pins:
/*
 gpio_write_bit(GPIOA, 9, (d) & BIT0_MSK_8BIT) = D8
 gpio_write_bit(GPIOC, 7, (d) & BIT1_MSK_8BIT) = D9
 gpio_write_bit(GPIOA, 10, (d) & BIT2_MSK_8BIT) = D2
 gpio_write_bit(GPIOB, 3, (d) & BIT3_MSK_8BIT) = D3
 gpio_write_bit(GPIOB, 5, (d) & BIT4_MSK_8BIT) = D4
 gpio_write_bit(GPIOB, 4, (d) & BIT5_MSK_8BIT) = D5
 gpio_write_bit(GPIOB, 10, (d) & BIT6_MSK_8BIT) = D6
 gpio_write_bit(GPIOA, 8, (d) & BIT7_MSK_8BIT) = D7
 */

  #define write8inline(d){\
gpio_write_bit(GPIOA, 9, (d) & BIT0_MSK_8BIT);\
gpio_write_bit(GPIOC, 7, (d) & BIT1_MSK_8BIT);\
gpio_write_bit(GPIOA, 10, (d) & BIT2_MSK_8BIT);\
gpio_write_bit(GPIOB, 3, (d) & BIT3_MSK_8BIT);\
gpio_write_bit(GPIOB, 5, (d) & BIT4_MSK_8BIT);\
gpio_write_bit(GPIOB, 4, (d) & BIT5_MSK_8BIT);\
gpio_write_bit(GPIOB, 10, (d) & BIT6_MSK_8BIT);\
gpio_write_bit(GPIOA, 8, (d) & BIT7_MSK_8BIT);\
WR_STROBE; }
 
/*
 #define write8inline(d){\
uint16_t maskA;\
uint16_t maskB;\
bitWrite(maskA,10,(d) & BIT2_MSK_8BIT);\
bitWrite(maskA,8,(d) & BIT7_MSK_8BIT);\
bitWrite(maskA,9,(d) & BIT0_MSK_8BIT);\
bitWrite(maskB,3,(d) & BIT3_MSK_8BIT);\
bitWrite(maskB,5,(d) & BIT4_MSK_8BIT);\
bitWrite(maskB,4,(d) & BIT5_MSK_8BIT);\
bitWrite(maskB,10,(d) & BIT6_MSK_8BIT);\
GPIOA_BASE->BSRR = (0b0000011100000000 << 16) | (maskA);\
GPIOB_BASE->BSRR = (0b0000010000111000 << 16) | (maskB);\
gpio_write_bit(GPIOC, 7, (d) & BIT1_MSK_8BIT);\
WR_STROBE; }
 */

/*
{                          \
    PORTD = (PORTD & B00000011) | ((d) & B11111100); \
    PORTB = (PORTB & B11111100) | ((d) & B00000011); \
    WR_STROBE; }
 */
  #define read8inline(result) {\
 RD_ACTIVE;\
delayMicroseconds(1);      \
result =gpio_read_bit(GPIOA, 9)<<0;\
result |=gpio_read_bit(GPIOC, 7)<<1;\
result |=gpio_read_bit(GPIOA, 10)<<2;\
result |=gpio_read_bit(GPIOB, 3)<<3;\
result |=gpio_read_bit(GPIOB, 5)<<4;\
result |=gpio_read_bit(GPIOB, 4)<<5;\
result |=gpio_read_bit(GPIOB, 10)<<6;\
result |=gpio_read_bit(GPIOA, 8)<<7;\
 RD_IDLE; }
/*
{                       \
    RD_ACTIVE;                                        \
    DELAY7;                                           \
    result = (PIND & B11111100) | (PINB & B00000011); \
    RD_IDLE; }
*/
  #define setReadDirInline(){\
    gpio_set_mode(GPIOA, 9, GPIO_INPUT_FLOATING);\
    gpio_set_mode(GPIOC, 7, GPIO_INPUT_FLOATING);\
    gpio_set_mode(GPIOA, 10, GPIO_INPUT_FLOATING);\
    gpio_set_mode(GPIOB, 3, GPIO_INPUT_FLOATING);\
    gpio_set_mode(GPIOB, 5, GPIO_INPUT_FLOATING);\
    gpio_set_mode(GPIOB, 4, GPIO_INPUT_FLOATING);\
    gpio_set_mode(GPIOB, 10, GPIO_INPUT_FLOATING);\
    gpio_set_mode(GPIOA, 8, GPIO_INPUT_FLOATING);\
}
#define setWriteDirInline() {\
gpio_set_mode(GPIOA, 9, GPIO_OUTPUT_PP);\
gpio_set_mode(GPIOC, 7, GPIO_OUTPUT_PP);\
gpio_set_mode(GPIOA, 10, GPIO_OUTPUT_PP);\
gpio_set_mode(GPIOB, 3, GPIO_OUTPUT_PP);\
gpio_set_mode(GPIOB, 5, GPIO_OUTPUT_PP);\
gpio_set_mode(GPIOB, 4, GPIO_OUTPUT_PP);\
gpio_set_mode(GPIOB, 10, GPIO_OUTPUT_PP);\
gpio_set_mode(GPIOA, 8, GPIO_OUTPUT_PP);\
}
//{ DDRD |=  B11111100; DDRB |=  B00000011; }
   // { DDRD &= ~B11111100; DDRB &= ~B00000011; }

 
 

  // As part of the inline control, macros reference other macros...if any
  // of these are left undefined, an equivalent function version (non-inline)
  // is declared later.  The Uno has a moderate amount of program space, so
  // only write8() is inlined -- that one provides the most performance
  // benefit, but unfortunately also generates the most bloat.  This is
  // why only certain cases are inlined for each board.
  #define write8 write8inline



 // When using the TFT breakout board, control pins are configurable.
 #define RD_ACTIVE  GPIOA->regs->BRR=BIT(0);
 #define RD_IDLE    GPIOA->regs->BSRR=BIT(0);
 #define WR_ACTIVE  GPIOA->regs->BRR=BIT(1);
 #define WR_IDLE    GPIOA->regs->BSRR=BIT(1);
 #define CD_COMMAND GPIOA->regs->BRR=BIT(4);
 #define CD_DATA    GPIOA->regs->BSRR=BIT(4);
 #define CS_ACTIVE  GPIOB->regs->BRR=BIT(0);
 #define CS_IDLE    GPIOB->regs->BSRR=BIT(0);

// #endif
// #endif

// Data write strobe, ~2 instructions and always inline
#define WR_STROBE { WR_ACTIVE; WR_IDLE; }

// These higher-level operations are usually functionalized,
// except on Mega where's there's gobs and gobs of program space.

// Set value of TFT register: 8-bit address, 8-bit value
#define writeRegister8inline(a, d) { \
  CD_COMMAND; write8(a); CD_DATA; write8(d); }

// Set value of TFT register: 16-bit address, 16-bit value
// See notes at top about macro expansion, hence hi & lo temp vars
#define writeRegister16inline(a, d) { \
  uint8_t hi, lo; \
  hi = (a) >> 8; lo = (a); CD_COMMAND; write8(hi); write8(lo); \
  hi = (d) >> 8; lo = (d); CD_DATA   ; write8(hi); write8(lo); }

// Set value of 2 TFT registers: Two 8-bit addresses (hi & lo), 16-bit value
#define writeRegisterPairInline(aH, aL, d) { \
  uint8_t hi = (d) >> 8, lo = (d); \
  CD_COMMAND; write8(aH); CD_DATA; write8(hi); \
  CD_COMMAND; write8(aL); CD_DATA; write8(lo); }

#endif // _UUNO_24_SHIELD_
