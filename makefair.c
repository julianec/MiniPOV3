#include <avr/io.h>      // this contains all the IO port definitions
#include <avr/interrupt.h>
//#include <avr/signal.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "bitops.h"

void delay_ms( uint16_t milliseconds)
{
   for( ; milliseconds > 0; milliseconds--)
   {
      _delay_ms( 1);
   }
} 

// store all the image data in program memory (ROM)
// instead of RAM (the default)
const uint8_t large_image[] PROGMEM = {
  B8(11000011),
  B8(11111111),
  B8(11111111),
  B8(11000011),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00001110),
  B8(00011111),
  B8(00111111),
  B8(01111111),
  B8(11111110),
  B8(11111110),
  B8(01111111),
  B8(00111111),
  B8(00011111),
  B8(00001110),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(11111111),
  B8(11111111),
  B8(00001110),
  B8(00111100),
  B8(11110000),
  B8(11110000),
  B8(00111100),
  B8(00001110),
  B8(11111111),
  B8(11111111),
  B8(00000000),
  B8(01100000),
  B8(11110100),
  B8(10010100),
  B8(10010100),
  B8(11111100),
  B8(11111000),
  B8(10000000),
  B8(00000000),
  B8(11111111),
  B8(11111111),
  B8(00110000),
  B8(01111000),
  B8(11111100),
  B8(11001100),
  B8(10000000),
  B8(00000000),
  B8(01111000),
  B8(11111100),
  B8(11010100),
  B8(11010100),
  B8(11011100),
  B8(01011000),
  B8(00000000),
  B8(00000000),
  B8(00001110),
  B8(11011111),
  B8(11011111),
  B8(00001110),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
};

// special pointer for reading from ROM memory
PGM_P const largeimage_p PROGMEM = large_image;

int imagesize = NUM_ELEM(large_image);

// this function is called when timer1 compare matches OCR1A
uint8_t j = 0;
SIGNAL( TIMER1_COMPA_vect ) {
  if (j >= imagesize) 
    j = 0;

  // read the image data from ROM
  PORTB = pgm_read_byte(largeimage_p + j); 
 
  j++;
}

int main(void) {

  DDRB = 0xFF;       // set all 8 pins on port B to outputs

  /*
    the frequency of the interrupt overflow is determined by the 
    prescaler and overflow value.
    freq = clock_frequency / ( 2 * prescaler * overflow_val)
    where prescaler can be 1, 8, 64, 256, or 1024
    clock_freq is 8MHz
    and overflow_val is 16bit

    the overflow value is placed in OCR1A, the prescale is set in TCCR1B
    so for example:
    A good POV frequency is around 400Hz
    desired freq = 400Hz
    clock freq = 8MHz
    8MHz / (400Hz * 2) = 10000
    since 10000 is less than 655536 (largest 16 bit number)
    OCR1A = 10000 and the prescale is 1
  */

  TCCR1B = (1 << WGM12) | TIMER1_PRESCALE_1;
  OCR1A = (uint16_t)10000;

  TIMSK |= 1 << OCIE1A;   // Output Compare Interrupt Enable (timer 1, OCR1A) 

  sei();                 // Set Enable Interrupts

  while (1);
}
