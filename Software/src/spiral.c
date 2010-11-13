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

void spiral(uint8_t iteration, uint8_t nb_rot, uint16_t delay_value)
{
	clear_all();
	line(0,0,0, 1, 0, 1,5,1);
	//line(4,0,0, 0, 1, 1,5,1);
	line(4,4,0,-1, 0, 1,5,1);
	//line(0,4,0, 0,-1, 1,5,1);

	for(uint8_t i = 0; i < iteration; i++) {
		for(uint8_t r = 0; r < nb_rot; r++) {
				delay(delay_value);
				rotate_right_stepB();
				delay(delay_value);
				rotate_right_stepA();
				delay(delay_value);
				rotate_right_stepA();
				delay(delay_value);
				rotate_right_stepB();
		}

		delay(delay_value);
		rotate_layer_right_stepB(0);

		delay(delay_value);
		rotate_layer_right_stepA(0);
		rotate_layer_right_stepA(1);

		delay(delay_value);
		rotate_layer_right_stepA(0);
		rotate_layer_right_stepA(1);
		rotate_layer_right_stepA(2);

		delay(delay_value);
		rotate_layer_right_stepB(0);
		rotate_layer_right_stepB(1);
		rotate_layer_right_stepB(2);
		rotate_layer_right_stepB(3);

		delay(delay_value);
		rotate_layer_right_stepB(0);

		delay(delay_value);
		rotate_layer_right_stepA(0);
		rotate_layer_right_stepA(1);

		delay(delay_value);
		rotate_layer_right_stepA(0);
		rotate_layer_right_stepA(1);
		rotate_layer_right_stepA(2);

		delay(delay_value);
		rotate_layer_right_stepB(0);
		rotate_layer_right_stepB(1);
		rotate_layer_right_stepB(2);
		rotate_layer_right_stepB(3);

		for(uint8_t r = 0; r < nb_rot; r++) {
				delay(delay_value);
				rotate_right_stepB();
				delay(delay_value);
				rotate_right_stepA();
				delay(delay_value);
				rotate_right_stepA();
				delay(delay_value);
				rotate_right_stepB();
		}

		delay(delay_value);
		rotate_layer_right_stepB(4);

		delay(delay_value);
		rotate_layer_right_stepA(4);
		rotate_layer_right_stepA(3);

		delay(delay_value);
		rotate_layer_right_stepA(4);
		rotate_layer_right_stepA(3);
		rotate_layer_right_stepA(2);

		delay(delay_value);
		rotate_layer_right_stepB(4);
		rotate_layer_right_stepB(3);
		rotate_layer_right_stepB(2);
		rotate_layer_right_stepB(1);

		delay(delay_value);
		rotate_layer_right_stepB(4);

		delay(delay_value);
		rotate_layer_right_stepA(4);
		rotate_layer_right_stepA(3);

		delay(delay_value);
		rotate_layer_right_stepA(4);
		rotate_layer_right_stepA(3);
		rotate_layer_right_stepA(2);

		delay(delay_value);
		rotate_layer_right_stepB(4);
		rotate_layer_right_stepB(3);
		rotate_layer_right_stepB(2);
		rotate_layer_right_stepB(1);
	}
}

