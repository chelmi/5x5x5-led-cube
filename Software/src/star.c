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

#include <star.h>
#include <primitives.h>
#include <delay.h>
#include <transforms.h>

void star(uint8_t iteration, uint16_t delay_value1, uint16_t delay_value)
{
	set_voxel(2,2,2, ON);

	delay(delay_value1);

	line(1, 1, 1, 0, 0, 1, 3, ON);
	line(3, 3, 1, 0, 0, 1, 3, ON);

	delay(delay_value1);

	line_xy(0,0,1);
	line_xy(4,4,1);

	delay(delay_value1);

	for(uint8_t r = 0; r < iteration; r++) {
			delay(delay_value);
			rotate_cw_stepB();
			delay(delay_value);
			rotate_cw_stepA();
			delay(delay_value);
			rotate_cw_stepA();
			delay(delay_value);
			rotate_cw_stepB();
	}
}
