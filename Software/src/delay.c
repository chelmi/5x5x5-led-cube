#include "delay.h"
#include <avr/io.h>

void setup_timer(void)
{
  TCCR1B |= _BV(WGM12); //CTC mode
  TCCR1B &= ~_BV(CS12) & ~_BV(CS10) & ~_BV(CS10); //stop timer
  //TIMSK1 |= _BV(OCIE1A);
}

void delay(uint16_t value) {
  OCR1A = value ;
  TCCR1B |= _BV(CS12) | _BV(CS10); //start timer with clk/1024
  while(!(TIFR1 & _BV(OCF1A))); //wait
  TCCR1B &= ~_BV(CS12) & ~_BV(CS10) & ~_BV(CS10); //stop timer
  TIFR1 |= _BV(OCF1A); //clear flag
}
