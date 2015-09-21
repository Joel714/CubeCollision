#ifndef _CUBE_H_
#define _CUBE_H_

#include "mymath.h"

class Cube{
private:

public:
	float color[3];
	float vertices[8][4];
	float center[4];
	float velocity[4];
	float normals[6][3];
	float edges[12][3];
	float axis[4];
	float angle;
	Cube();
	void createNormals();
	void createEdges();
};

#endif 


