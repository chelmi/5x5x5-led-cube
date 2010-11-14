/**********************************************************************************
 * Copyright 2010 Michel Metzger (michel.metzger@gmail.com). All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice, this
 *     list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY MICHEL METZGER ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL MICHEL METZGER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
