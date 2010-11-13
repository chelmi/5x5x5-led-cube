#ifndef _EFFECTS_H
#define _EFFECTS_H

#include <stdint.h>

#include <worm.h>
#include <cube_expand.h>
#include <spiral.h>

void one_by_one(void);
void chenillard_z(uint8_t iteration, uint16_t delay_value);
void rain(uint16_t delay_value);
void up_and_down(uint8_t iteration, uint16_t delay_value);

#endif
