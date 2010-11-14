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
#include "utils.h"
#include "delay.h"
#include "effects.h"
#include "primitives.h"

//SPI pins

#define SS_PORT B
#define SS_PIN  2

#define MOSI_PORT B
#define MOSI_PIN  3

#define MISO_PORT B
#define MISO_PIN  4

#define SCK_PORT B
#define SCK_PIN  5

//Misc pins

#define ENABLE_PORT C
#define ENABLE_PIN  0

#define LATCH_PORT B
#define LATCH_PIN  1

#define LAYER0_PORT C
#define LAYER0_PIN  5

#define LAYER1_PORT C
#define LAYER1_PIN  4

#define LAYER2_PORT C
#define LAYER2_PIN  3

#define LAYER3_PORT C
#define LAYER3_PIN  2

#define LAYER4_PORT C
#define LAYER4_PIN  1

#define LED_PORT D
#define LED_PIN  0

#define START_BUTTON_PORT D
#define START_BUTTON_PIN  2

volatile uint8_t current_layer = 0;
volatile uint8_t is_sleeping = 0;

void display_current_frame(uint32_t frame);

void setup_refresh_timer(void) {
  TCCR0A |= _BV(WGM01); //CTC mode
  TCCR0B &= ~_BV(CS02) & ~_BV(CS01) & ~_BV(CS00); //stop timer
  OCR0A = 40 ; //run int. routine every 2,56 ms.
  TIMSK0 |= _BV(OCIE0A);

}

void start_refresh_timer(void) {
  TCCR0B |= _BV(CS02) | _BV(CS00); // clk/1024
}

ISR(TIMER0_COMPA_vect, ISR_NOBLOCK) {
  PIN_HIGH(LAYER0);
  PIN_HIGH(LAYER1);
  PIN_HIGH(LAYER2);
  PIN_HIGH(LAYER3);
  PIN_HIGH(LAYER4);

  switch(current_layer) {
  case 0: PIN_LOW(LAYER0); break;
  case 1: PIN_LOW(LAYER1); break;
  case 2: PIN_LOW(LAYER2); break;
  case 3: PIN_LOW(LAYER3); break;
  case 4: PIN_LOW(LAYER4); break;
  }
  display_current_frame(frame_buffer[current_layer]);
  current_layer++;
  if(current_layer == CUBE_WIDTH)
    current_layer = 0;
}

void setup_spi(void) {
  PIN_OUT(SS);

  PIN_OUT(MOSI);

  PIN_IN(MISO);
  PULL_UP(MISO);

  PIN_OUT(SCK);
  PIN_LOW(SCK);


  SPCR = 0;
  SPCR |= /*_BV(SPIE) |*/ _BV(SPE) | _BV(MSTR)/* | _BV(CPOL) | _BV(CPHA)*/;
  SPSR |= _BV(SPI2X);

  //clear flags
  uint8_t tmp = SPSR;
  tmp = SPDR;
}

void setup_A6279(void) {
  setup_spi();
  PIN_OUT(LATCH);
  PIN_OUT(ENABLE);
}

void setup_start_button(void) {
  PIN_IN(START_BUTTON);
  

  //Configure interrupt
  // EICRA &= ~_BV(ISC01) & ~_BV(ISC01); //triggered by low level
  // EIMSK |= _BV(INT0); //enable interrupt

  // set_sleep_mode(SLEEP_MODE_PWR_DOWN);

}

/*ISR(INT0_vect) {
  if(is_sleeping == 1) {
    PIN_HIGH(LED);
    is_sleeping = 0;
    sleep_disable();
  } else {
    PIN_LOW(LED);
    is_sleeping = 1;
    EIMSK |= _BV(INT0);
    sei();
    sleep_mode();
  }
  }*/

void send_byte(uint8_t data) {
  SPDR = data;
  while(!(SPSR & _BV(SPIF)));
}

void display_current_frame(uint32_t frame) {
  PIN_HIGH(ENABLE); // active low

  PIN_LOW(LATCH);

  PIN_LOW2(B, 5);
  send_byte((uint8_t)((frame >> 24) & 0xff));
  send_byte((uint8_t)((frame >> 16) & 0xff));
  send_byte((uint8_t)((frame >> 8) & 0xff));
  send_byte((uint8_t)(frame & 0xff));
  PIN_LOW2(B, 5);


  PIN_HIGH(LATCH);
  PIN_LOW(LATCH);
    
  PIN_LOW(ENABLE);  
}

int main(void) {

  PIN_OUT(LED);

  PIN_OUT(LAYER0);
  PIN_OUT(LAYER1);
  PIN_OUT(LAYER2);
  PIN_OUT(LAYER3);
  PIN_OUT(LAYER4);

  PIN_HIGH(LAYER0);
  PIN_HIGH(LAYER1);
  PIN_HIGH(LAYER2);
  PIN_HIGH(LAYER3);
  PIN_HIGH(LAYER4);

  setup_refresh_timer();
  setup_timer();
  setup_A6279();

  sei();

  start_refresh_timer();

  PIN_HIGH(LED);

  //rain(T_1S);

  //up_and_down(20, T_50MS);
  //cube_expand(10, T_125MS);
  //chenillard_z(2 , T_50MS);
  //worm(1000, T_50MS);
  spiral(4, 2, T_50MS);
  
  while(1) {
    
  }
  return 0;
}
