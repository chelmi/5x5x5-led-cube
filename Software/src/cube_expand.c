/*
 * square_expand.c
 *
 *  Created on: 2010-11-11
 *      Author: Michel Metzger (michel.metzger@gmail.com)
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
