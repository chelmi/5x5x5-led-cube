#include "worm.h"
#include "delay.h"
#include "primitives.h"
#include "transforms.h"
#include <stdlib.h>

#define WORM_LENGTH 4

#define NB_DECISIONS 6

#define UP       0
#define DOWN     1
#define LEFT     2
#define RIGHT    3
#define FORWARD  4
#define BACKWARD 5

#define OPPOSITE_DECISION(x) ((x)^0x1)

#define DEFAULT_DECISION_TTL 3

typedef struct {
  int8_t x;
  int8_t y;
  int8_t z;
} point_t;

typedef point_t worm_t[WORM_LENGTH];

static inline void set_point(point_t * point, uint8_t state)
{
  set_voxel((uint8_t)point->x, (uint8_t)point->y, (uint8_t)point->z, state);
}


void draw_worm(worm_t * worm);
void delete_worm(worm_t* worm);

void get_bad_decisions(uint8_t bad_decisions[NB_DECISIONS], worm_t* worm);
uint8_t get_next_decision(uint8_t bad_decisions[NB_DECISIONS], worm_t * worm);
point_t get_new_head(worm_t * worm, uint8_t decision);

void flash_led(uint8_t nb) {
  for(int i = 0; i < nb; i++) {
    set_voxel(2,2,2,ON);
    delay(T_250MS);
    set_voxel(2,2,2,OFF);
    delay(T_250MS);    
  }
}

void worm(uint8_t iteration, uint16_t delay_value)
{

  worm_t my_worm = { {4, 2, 2},
                     {3, 2, 2},
                     {2, 2, 2},
                     {1, 2, 2} };

  srand(579);

  uint8_t decision = UP;
  uint8_t bad_decisions[NB_DECISIONS] = {0, 0, 0, 0, 0, 0};
  uint8_t decision_ttl = DEFAULT_DECISION_TTL;
  for(uint8_t iter = 0; iter < iteration; iter++) {
    draw_worm(&my_worm);

    delay(delay_value);

    delete_worm(&my_worm);


    //flash_led(decision_ttl);
    get_bad_decisions(bad_decisions, &my_worm);

    if(decision_ttl == 1 || bad_decisions[decision] == 1) {
      decision = get_next_decision(bad_decisions, &my_worm);
      decision_ttl = 1 + rand() % 3;
    } else {
      decision_ttl--;
    }
    
    point_t new_head = get_new_head(&my_worm, decision);


    for(int i = WORM_LENGTH - 1; i >= 1; i--) {
      my_worm[i] = my_worm[i - 1];
    }
    my_worm[0] = new_head;
  }
}

void draw_worm(worm_t* worm)
{
  for(int i = 0; i < WORM_LENGTH; i++) {
    set_point(&((*worm)[i]), ON);
  }
}

void delete_worm(worm_t* worm)
{
  for(int i = 0; i < WORM_LENGTH; i++) {
    set_point(&((*worm)[i]), OFF);
  }
}

void vector(point_t * result, point_t * point1, point_t * point2)
{
  result->x = point1->x - point2->x;
  result->y = point1->y - point2->y;
  result->z = point1->z - point2->z;
}

void get_bad_decisions(uint8_t bad_decisions[NB_DECISIONS], worm_t * worm)
{
  point_t head = (*worm)[0];
  
  for(int i = 0; i < NB_DECISIONS; i++) {
    bad_decisions[i] = 0;
  }
  
  //Worm can't go backward
  point_t vec;
  vector(&vec, &(*worm)[0], &(*worm)[1]);

  if(vec.z == 1)  bad_decisions[DOWN] = 1;
  if(vec.z == -1) bad_decisions[UP] = 1;
  if(vec.y == 1)  bad_decisions[LEFT] = 1;
  if(vec.y == -1) bad_decisions[RIGHT] = 1;
  if(vec.x == 1)  bad_decisions[BACKWARD] = 1;
  if(vec.x == -1) bad_decisions[FORWARD] = 1;


  //Worm can't exit the cube
  if(head.x == 0) bad_decisions[BACKWARD] = 1;
  if(head.x == CUBE_WIDTH - 1) bad_decisions[FORWARD] = 1;

  if(head.y == 0) bad_decisions[LEFT] = 1;
  if(head.y == CUBE_WIDTH - 1) bad_decisions[RIGHT] = 1;

  if(head.z == 0) bad_decisions[DOWN] = 1;
  if(head.z == CUBE_WIDTH - 1) bad_decisions[UP] = 1;
}

uint8_t get_next_decision(uint8_t bad_decisions[NB_DECISIONS], worm_t * worm)
{
  uint8_t good_decisions[NB_DECISIONS] = {-1, -1, -1, -1, -1, -1};

  int gd_index = 0;
  for(int i = 0; i < NB_DECISIONS; i++) {
    if(bad_decisions[i] == 0) {
      good_decisions[gd_index++] = i;
    } else {
    	if(!bad_decisions[OPPOSITE_DECISION(i)]) {
    		good_decisions[gd_index++] = OPPOSITE_DECISION(i);
    	}
    }
  } 
 
  uint8_t nb_good_decisions = gd_index;

  return good_decisions[rand() % nb_good_decisions];
}

point_t get_new_head(worm_t * worm, uint8_t decision)
{
  point_t new_head = (*worm)[0];

  switch(decision) {
  case UP: new_head.z++; break;
  case DOWN: new_head.z--; break;

  case LEFT: new_head.y--; break;
  case RIGHT: new_head.y++; break;

  case FORWARD: new_head.x++; break;
  case BACKWARD: new_head.x--; break;
  }
  return new_head;
}
