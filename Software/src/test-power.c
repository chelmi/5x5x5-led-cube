#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

int main(void) {
  //set led pin
  DDRD |= _BV(PD0); //set led pin as input

  DDRD &= ~_BV(PD2); //set button pin as input;
  PORTD &= ~_BV(PD2); //switch-off pull-up (external pull-up)

  //Configure interrupt
  EIMSK |= _BV(INT0); //enable interrupt
 
  EICRA |= _BV(ISC01); //triggered by falling edge
  EICRA &= ~_BV(ISC00);
  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  
  sei();
  
  while(1) {
    PORTD |= _BV(PD0); //switch led on
  }
}

ISR(INT0_vect, ISR_NOBLOCK) {
  PORTD &= ~_BV(PD0); //LED off

  EICRA &= ~_BV(ISC01) & ~_BV(ISC00); //triggered by low level
  
  sleep_mode();
  
  EICRA |= _BV(ISC01); //triggered by falling edge
  EICRA &= ~_BV(ISC00);
  
  sleep_disable();
}
