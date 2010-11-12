#ifndef _DELAY_H
#define _DELAY_H
#include <stdint.h>

#define T_50MS  781
#define T_100MS 1562
#define T_125MS 1953
#define T_250MS 3906
#define T_500MS 7812
#define T_1S    15625

void setup_timer(void);


// value = delay in us / 64
// max ~= 4.2 s
void delay(uint16_t value);

#endif
