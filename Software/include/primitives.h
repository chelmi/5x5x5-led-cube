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

#ifndef _VOXEL_H
#define _VOXEL_H

#include <stdint.h>
#include <string.h>

#define ON 1
#define OFF 0

#define CUBE_WIDTH 5

extern volatile uint32_t frame_buffer[CUBE_WIDTH];

#define LED_INDEX(x,y) ((x) + (y) *  CUBE_WIDTH)

#define LED_MASK(x,y) (0x1UL << LED_INDEX((x), (y)))

static inline void clear_all(void) {
	memset((void*)frame_buffer, 0, CUBE_WIDTH * sizeof(uint32_t));
}

static inline void set_voxel_index(uint8_t i, uint8_t z, uint8_t state) {
    if(state) 
        frame_buffer[z] |=   0x1UL << i;
    else
        frame_buffer[z] &= ~(0x1UL << i);
}

static inline void set_voxel(uint8_t x, uint8_t y, uint8_t z, uint8_t state) {
    set_voxel_index(LED_INDEX(x,y), z, state);
}

static inline uint8_t get_voxel_index(uint8_t i, uint8_t z) {
    uint32_t state = frame_buffer[z] & (0x1UL << i);
    return (uint8_t) (state >> i);
}

static inline uint8_t get_voxel(uint8_t x, uint8_t y, uint8_t z) {
    return get_voxel_index(LED_INDEX(x,y), z);
}

static inline void line(uint8_t x, uint8_t y, uint8_t z,
                        uint8_t x_inc, uint8_t y_inc, uint8_t z_inc,
                        uint8_t length,
                        uint8_t state) {
    for(uint8_t i = 0; i < length; i++) {
        set_voxel(x, y, z, state);
        x += x_inc;
        y += y_inc;
        z += z_inc;
    }
}

static inline void line_xy(uint8_t x, uint8_t y, uint8_t state) {
    for(uint8_t z = 0; z < CUBE_WIDTH; z++) {
        set_voxel(x, y, z, state);
    }
}

static inline void line_xz(uint8_t x, uint8_t z, uint8_t state) {
    for(uint8_t y = 0; y < CUBE_WIDTH; y++) {
        set_voxel(x, y, z, state);
    }
}

static inline void line_yz(uint8_t y, uint8_t z, uint8_t state) {
    for(uint8_t x = 0; x < CUBE_WIDTH; x++) {
        set_voxel(x, y, z, state);
    }
}

static inline void plane_x(uint8_t x, uint8_t state) {
    for(uint8_t y = 0; y < CUBE_WIDTH; y++) {
        for(uint8_t z = 0; z < CUBE_WIDTH; z++) {
            set_voxel(x, y, z, state);
        }
    }
}

static inline void plane_y(uint8_t y, uint8_t state) {
        for(uint8_t x = 0; x < CUBE_WIDTH; x++) {
            for(uint8_t z = 0; z < CUBE_WIDTH; z++) {
                set_voxel(x, y, z, state);
        }
    }
}

static inline void plane_z(uint8_t z, uint8_t state) {
    frame_buffer[z] = state ? 0xffffffff : 0x0;
}

#endif
