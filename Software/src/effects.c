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

#include "effects.h"
#include "delay.h"
#include "primitives.h"
#include "transforms.h"
#include <stdlib.h>

void one_by_one(void) {
  for(uint8_t x = 0; x < 5; x++) {
    for(uint8_t y = 0; y < 5; y++) {
      set_voxel(x, y, 0, 1);
      delay(T_250MS);
      set_voxel(x, y, 1, 1);
      delay(T_250MS);
    }
  }

  for(int8_t x = 4; x >= 0; x--) {
    for(int8_t y = 4; y >= 0; y--) {
      set_voxel(x, y, 1, 0);
      delay(T_250MS);
      set_voxel(x, y, 0, 0);
      delay(T_250MS);
    }
  }
}

void chenillard_z(uint8_t iteration, uint16_t delay_value) {

  for(uint8_t iter = 0; iter < iteration; iter++) {
    for(int8_t z = 0; z < CUBE_WIDTH; z++) {
      plane_z(z, ON);
      delay(delay_value);
    }
    
    for(int8_t z = 0; z < CUBE_WIDTH; z++) {
      plane_z(z, OFF);
      delay(delay_value);
    }
    
    for(int8_t z = CUBE_WIDTH -1 ; z >=0 ; z--) {
      plane_z(z, ON);
      delay(delay_value);
    }
    
    for(int8_t z = CUBE_WIDTH -1 ; z >=0 ; z--) {
      plane_z(z, OFF);
      delay(delay_value);
    }
  }
}

void rain(uint16_t delay_value) {
  srand(12355);
  
  plane_z(CUBE_WIDTH - 1, OFF);
  while(1) {
    //init upper layer
    
    for(uint8_t i = 0; i < 5; i++) {
      set_voxel_index(rand() % 25, CUBE_WIDTH - 1, ON);
    }
    
    delay(delay_value);
    
    shift_down();

    delay(delay_value);

    plane_z(CUBE_WIDTH - 1, OFF);
    
  }
}

void push_up(uint8_t x, uint8_t y, uint16_t delay_value) {
  for(int i = 0; i < CUBE_WIDTH-1; i++) {
    delay(delay_value);
    shift_up_xy(x, y);
  }
}

void push_down(uint8_t x, uint8_t y, uint16_t delay_value) {
  for(int i = 0; i < CUBE_WIDTH-1; i++) {
    delay(delay_value);
    shift_down_xy(x, y);
  }
}

void up_and_down(uint8_t iteration, uint16_t delay_value) {
  srand(579);
  
  //all voxels are down
  uint8_t voxels[CUBE_WIDTH][CUBE_WIDTH] = {{0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0}};
  plane_z(0, ON);

  for(uint8_t i = 0; i < 13; i++) {
    int8_t x = rand() % CUBE_WIDTH;
    int8_t y = rand() % CUBE_WIDTH;
    if(voxels[x][y] == 0) {
      push_up(x,y, delay_value);
      voxels[x][y] = 4;
    }
  }

  for(uint8_t i = 0; i < iteration; i++) {
    int8_t x = rand() % CUBE_WIDTH;
    int8_t y = rand() % CUBE_WIDTH;
    if(voxels[x][y] == 0) {
      push_up(x, y, delay_value);
      voxels[x][y] = 4;
    } else {
      push_down(x, y, delay_value);
      voxels[x][y] = 0;
    }
  }

  for(uint8_t x = 0; x < CUBE_WIDTH; x++) {
    for(uint8_t y = 0; y < CUBE_WIDTH; y++) {
      if(voxels[x][y] == 4) {
        push_down(x, y, delay_value);
        voxels[x][y] = 0;
      }
    }
  }

}
