#ifndef _MYMATH_H_
#define _MYMATH_H_

#include <cmath>
#include "mymath.h"

void vecCopy3Float(float *src, float *dest);

void vecCopy4Float(float *src, float *dest);

void matCopy4Float(float *src, float *dest);

void vecFromPoints3Float(float *head, float *tail, float *dest);

void mat4TransposeFloat(float *m);

float vecLength3Float(float *a);

void vecNormalize3Float(float* v);

float vecDot3Float(float *a, float *b);

void vecCrossProduct3Float(float *a, float *b, float *c);

void mat4MultVec4Float(float *m, float *vSrc, float *vDest);

void mat4MultMat4Float( float *a, float *b, float *dest);

void createTranslationMatrix(float x, float y, float z, float *matrix);

void createRotationMatrix(float *matrix, float angle, float *axis);

#endif
