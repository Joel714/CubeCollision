#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "cube.h"
#include "mymath.h"


void computeInterval(Cube *cube, float *D, float *min, float *max);

bool cubesColliding(Cube *cube0, Cube *cube1);

#endif
