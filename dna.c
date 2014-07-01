#include <avr/io.h>      // this contains all the IO port definitions
#include <avr/interrupt.h>
//#include <avr/signal.h>
#include <util/delay.h>
#include "bitops.h"

void delay_ms( uint16_t milliseconds)
{
   for( ; milliseconds > 0; milliseconds--)
   {
      _delay_ms( 1);
   }
} 
const static int image[] = {
   0x18, 0x3c, 0x66, 0x42, 0xc3, 0x81, 0xff, 0x81, 0xff, 0x81, 0xc3, 0x42,
   0x66, 0x3c, 0x18,
};

int imagesize = NUM_ELEM(image);


// this function is called when timer1 compare matches OCR1A
uint8_t j = 0;
SIGNAL( TIMER1_COMPA_vect ) {
  if (j >= imagesize) 
    j = 0;

  PORTB = image[j];
 
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
