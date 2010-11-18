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

#ifndef _TRANSFORMS_H
#define _TRANSFORMS_H

#include <stdint.h>
#include "primitives.h"

#define MAP_FUNC_Z(func_name) \
static inline void func_name(void) {\
	for(uint8_t z = 0; z < CUBE_WIDTH; z++) {\
		func_name ## _z(z);\
	}\
}\

static inline void shift_up_xy(uint8_t x, uint8_t y) {
    for(uint8_t z = CUBE_WIDTH - 1; z > 0; z--) {
        uint32_t mask = LED_MASK(x,y);
        if((frame_buffer[z-1] & mask) != 0) {
            frame_buffer[z] |= mask;
        } else {
            frame_buffer[z] &= ~mask;
        }
    }
    set_voxel(x, y ,0 , OFF);
}

static inline void shift_down_xy(uint8_t x, uint8_t y) {
    for(uint8_t z = 0; z < CUBE_WIDTH - 1; z++) {
        uint32_t mask = LED_MASK(x,y);
        if((frame_buffer[z+1] & mask) != 0) {
            frame_buffer[z] |= mask;
        } else {
            frame_buffer[z] &= ~mask;
        }
    }
    set_voxel(x, y, CUBE_WIDTH - 1 , OFF);
}

static inline void shift_down(void) {
    for(uint8_t layer = 0; layer < CUBE_WIDTH - 1; layer++) {
        frame_buffer[layer] = frame_buffer[layer + 1];
    }
}

static inline void rotate_cw_stepA_z(uint8_t z) {
	uint32_t layer = frame_buffer[z];
	uint32_t l = layer & 0x739c0;
	l |= (layer & 0xf) << 1;
	l |= (layer & 0x1e00000) >> 1;
	l |= (layer & 0x84210) << 5;
	frame_buffer[z] = l | ((layer & 0x108420) >> 5);
}

MAP_FUNC_Z(rotate_cw_stepA)

static inline void rotate_cw_stepB_z(uint8_t z) {
	uint32_t layer = frame_buffer[z];
	uint32_t l = layer & 0x1000;
	l |= (layer & 0xcf) << 1;
	l |= (layer & 0x1e60000) >> 1;
	l |= (layer & 0x86310) << 5;
	frame_buffer[z] = l | ((layer & 0x118c20) >> 5);
}

MAP_FUNC_Z(rotate_cw_stepB)

static inline void rotate_ccw_stepA_z(uint8_t z) {
	uint32_t layer = frame_buffer[z];
	uint32_t l = layer & 0x739c0;
	l |= (layer & 0xf00000) << 1;
	l |= (layer & 0x1e) >> 1;
	l |= (layer & 0x8421) << 5;
	frame_buffer[z] = l | ((layer & 0x1084200) >> 5);
}

MAP_FUNC_Z(rotate_ccw_stepA)

static inline void rotate_ccw_stepB_z(uint8_t z) {
	uint32_t layer = frame_buffer[z];
	uint32_t l = layer & 0x1000;
	l |= (layer & 0xf30000) << 1;
	l |= (layer & 0x19e) >> 1;
	l |= (layer & 0x8c61) << 5;
	frame_buffer[z] = l | ((layer & 0x10c6200) >> 5);
}

MAP_FUNC_Z(rotate_ccw_stepB)

static inline void shift_left_z(uint8_t z) {
  uint32_t layer = frame_buffer[z];
  uint32_t l = layer & 0x1f;
  l |= (layer & 0x1ffffe0) >> 5;
  frame_buffer[z] = l;
}

MAP_FUNC_Z(shift_left)

static inline void shift_right_z(uint8_t z) {
  uint32_t layer = frame_buffer[z];
  uint32_t l = layer & 0x1f00000;
  l |= (layer & 0xfffff) << 5;
  frame_buffer[z] = l;
}

MAP_FUNC_Z(shift_right)

static inline void shift_bw_z(uint8_t z) {
  uint32_t layer = frame_buffer[z];
  uint32_t l = layer & 0x1084210;
  l |= (layer & 0xf7bdef) << 1;
  frame_buffer[z] = l;
}

MAP_FUNC_Z(shift_bw)

static inline void shift_fw_z(uint8_t z) {
  uint32_t layer = frame_buffer[z];
  uint32_t l = layer & 0x108421;
  l |= (layer & 0x1ef7bde) >> 1;
  frame_buffer[z] = l;
}

MAP_FUNC_Z(shift_fw)

static inline void shift_left_xz(uint8_t x, uint8_t z) {
  uint32_t layer = frame_buffer[z];
  uint32_t mask = 0x108420 << x;
  uint32_t l = layer & (~mask & 0x1ffffff);
  l |= (layer & mask) >> 5;
  frame_buffer[z] = l;
}

static inline void shift_right_xz(uint8_t x, uint8_t z) {
  uint32_t layer = frame_buffer[z];
  uint32_t mask = 0x108420 << x;
  uint32_t l = layer & (~mask & 0x1ffffff);
  l |= (layer & mask) << 5;
  frame_buffer[z] = l;
}

static inline void shift_bw_yz(uint8_t y, uint8_t z) {
  uint32_t layer = frame_buffer[z];
  uint32_t mask = 0xf << y*5;
  uint32_t l = layer & (~mask & 0x1ffffff);
  l |= (layer & mask) << 1;
  frame_buffer[z] = l;
}

static inline void shift_fw_yz(uint8_t y, uint8_t z) {
  uint32_t layer = frame_buffer[z];
  uint32_t mask = 0xf << y*5;
  uint32_t l = layer & (~mask & 0x1ffffff);
  l |= (layer & mask) >> 1;
  frame_buffer[z] = l;
}

#endif
