#ifndef _TRANSFORMS_H
#define _TRANSFORMS_H

#include <stdint.h>
#include "primitives.h"

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

static inline void rotate_layer_right_stepA(uint8_t layer_index) {
	uint32_t layer = frame_buffer[layer_index];
	uint32_t l = layer & 0x739c0;
	l |= (layer & 0xf) << 1;
	l |= (layer & 0x1e00000) >> 1;
	l |= (layer & 0x84210) << 5;
	frame_buffer[layer_index] = l | ((layer & 0x108420) >> 5);
}

static inline void rotate_right_stepA(void) {
	for(uint8_t layer_index = 0; layer_index < CUBE_WIDTH; layer_index++) {
		rotate_layer_right_stepA(layer_index);
	}
}

static inline void rotate_layer_right_stepB(uint8_t layer_index) {
	uint32_t layer = frame_buffer[layer_index];
	uint32_t l = layer & 0x1000;
	l |= (layer & 0xcf) << 1;
	l |= (layer & 0x1e60000) >> 1;
	l |= (layer & 0x86310) << 5;
	frame_buffer[layer_index] = l | ((layer & 0x118c20) >> 5);
}

static inline void rotate_right_stepB(void) {
	for(uint8_t layer_index = 0; layer_index < CUBE_WIDTH; layer_index++) {
		rotate_layer_right_stepB(layer_index);
	}
}

static inline void rotate_layer_left_stepA(uint8_t layer_index) {
	uint32_t layer = frame_buffer[layer_index];
	uint32_t l = layer & 0x739c0;
	l |= (layer & 0xf00000) << 1;
	l |= (layer & 0x1e) >> 1;
	l |= (layer & 0x8421) << 5;
	frame_buffer[layer_index] = l | ((layer & 0x1084200) >> 5);
}

static inline void rotate_left_stepA(void) {
	for(uint8_t layer_index = 0; layer_index < CUBE_WIDTH; layer_index++) {
		rotate_layer_left_stepA(layer_index);
	}
}

static inline void rotate_layer_left_stepB(uint8_t layer_index) {
	uint32_t layer = frame_buffer[layer_index];
	uint32_t l = layer & 0x1000;
	l |= (layer & 0xf30000) << 1;
	l |= (layer & 0x19e) >> 1;
	l |= (layer & 0x8c61) << 5;
	frame_buffer[layer_index] = l | ((layer & 0x10c6200) >> 5);
}

static inline void rotate_left_stepB(void) {
	for(uint8_t layer_index = 0; layer_index < CUBE_WIDTH; layer_index++) {
		rotate_layer_left_stepB(layer_index);
	}
}


#endif
