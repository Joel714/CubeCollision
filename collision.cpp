#include "collision.h"

void computeInterval(Cube *cube, float *D, float *min, float *max){
	*min = vecDot3Float(D, cube->vertices[0]);
	*max = *min;
	float value = 0.0;

	for(int i = 1; i < 8; i++){
		value = vecDot3Float(D, cube->vertices[i]);
		if(value < *min){
			*min = value;
		}else if(value > *max){
			*max = value;
		}
	}
}

//test for cubes colliding using speration of axis method
bool cubesColliding(Cube *cube0, Cube *cube1){
	float min0, max0, min1, max1;
	float D[3];

	//test the face normals of cube0
	for(int i = 0; i < 6; i++){
		vecCopy3Float(cube0->normals[i], D);
		computeInterval(cube0, D, &min0, &max0);
		computeInterval(cube1, D, &min1, &max1);
		if(max1 < min0 || max0 < min1){
			return false;
		}
	}

	//test the face normals of cube1
	for(int i = 0; i < 6; i++){
		vecCopy3Float(cube1->normals[i], D);
		computeInterval(cube0, D, &min0, &max0);
		computeInterval(cube1, D, &min1, &max1);
		if(max1 < min0 || max0 < min1){
			return false;
		}
	}

	//test cross product of the egdes of each cube
	for(int i = 0; i < 12; i++){
		for(int j = 0; j < 12; j++){
			vecCrossProduct3Float(cube0->edges[i], cube1->edges[j], D);
			computeInterval(cube0, D, &min0, &max0);
			computeInterval(cube1, D, &min1, &max1);
			if(max1 < min0 || max0 < min1){
				return false;
			}
		}
	}

	return true;
}
