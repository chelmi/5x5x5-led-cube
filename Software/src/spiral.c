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

