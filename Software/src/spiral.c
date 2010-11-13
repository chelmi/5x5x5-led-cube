/*
 * spiral.c
 *
 *  Created on: 2010-11-13
 *      Author: michel
 */

#include <spiral.h>
#include <primitives.h>
#include <delay.h>
#include <transforms.h>

void spiral(uint8_t iteration, uint16_t delay_value)
{
	clear_all();
	line(0,0,0, 1, 0, 1,5,1);
	//line(4,0,0, 0, 1, 1,5,1);
	line(4,4,0,-1, 0, 1,5,1);
	//line(0,4,0, 0,-1, 1,5,1);

	for(uint8_t i = 0; i<iteration/4; i++) {
		delay(delay_value);
		rotate_right_stepB();
		delay(delay_value);
		rotate_right_stepA();
		delay(delay_value);
		rotate_right_stepA();
		delay(delay_value);
		rotate_right_stepB();
	}

	if(iteration % 2 == 1) {
		delay(delay_value);
		rotate_right_stepB();
	}
	if(iteration % 2 == 2) {
		delay(delay_value);
		rotate_right_stepA();
	}
	if(iteration % 2 == 3) {
		delay(delay_value);
		rotate_right_stepA();
	}
}

