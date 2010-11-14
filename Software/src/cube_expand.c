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

#include "cube_expand.h"
#include "delay.h"
#include "primitives.h"
#include <stdlib.h>

void draw_medium_cube(uint8_t state);
void draw_large_cube(uint8_t state);


void cube_expand(uint8_t iteration, uint16_t delay_value)
{
	clear_all();
	set_voxel(2,2,2, 1);
	delay(delay_value);

	for(uint8_t i = 0; i < iteration; i++) {
		set_voxel(2,2,2, 0);
		draw_medium_cube(1);
		delay(delay_value);

		clear_all();
		draw_large_cube(1);
		delay(delay_value);

		clear_all();
		draw_medium_cube(1);
		delay(delay_value);

		clear_all();
		set_voxel(2,2,2, 1);
		delay(delay_value);
	}
	clear_all();
}

void draw_medium_cube(uint8_t state)
{
	set_voxel(1,1,1, state);
	set_voxel(1,2,1, state);
	set_voxel(1,3,1, state);
	set_voxel(1,1,3, state);
	set_voxel(1,1,2, state);
	set_voxel(1,3,2, state);
	set_voxel(1,2,3, state);
	set_voxel(1,3,3, state);

	set_voxel(2,1,1, state);
	set_voxel(2,1,3, state);
	set_voxel(2,3,1, state);
	set_voxel(2,3,3, state);

	set_voxel(3,1,1, state);
	set_voxel(3,2,1, state);
	set_voxel(3,3,1, state);
	set_voxel(3,1,3, state);
	set_voxel(3,1,2, state);
	set_voxel(3,3,2, state);
	set_voxel(3,2,3, state);
	set_voxel(3,3,3, state);
}

void draw_square(uint8_t z, uint8_t state)
{
  line_yz(0, z, state);
  line_yz(4, z, state);
  line_xz(0, z, state);
  line_xz(4, z, state);
}

void draw_large_cube(uint8_t state)
{
	draw_square(0, state);
	draw_square(4, state);
	line(0, 0, 1, 0, 0, 1, 3, state);
	line(0, 4, 1, 0, 0, 1, 3, state);
	line(4, 0, 1, 0, 0, 1, 3, state);
	line(4, 4, 1, 0, 0, 1, 3, state);
}
