#include "cube.h"

Cube::Cube(){
	color[0] = 0.0;  color[1] = 0.0; color[2] = 0.0;

	vertices[0][0] = -1.0; vertices[0][1] = 1.0; vertices[0][2] = 1.0; vertices[0][3] = 1.0;//front top left
	vertices[1][0] = 1.0; vertices[1][1] = 1.0; vertices[1][2] = 1.0; vertices[1][3] = 1.0;//front top right
	vertices[2][0] = 1.0; vertices[2][1] = -1.0; vertices[2][2] = 1.0; vertices[2][3] = 1.0;//front bottom right
	vertices[3][0] = -1.0; vertices[3][1] = -1.0; vertices[3][2] = 1.0; vertices[3][3] = 1.0;//front bottom left
	vertices[4][0] = -1.0; vertices[4][1] = 1.0; vertices[4][2] = -1.0; vertices[4][3] = 1.0;//back top left
	vertices[5][0] = 1.0; vertices[5][1] = 1.0; vertices[5][2] = -1.0; vertices[5][3] = 1.0;//back top right
	vertices[6][0] = 1.0; vertices[6][1] = -1.0; vertices[6][2] = -1.0; vertices[6][3] = 1.0;//back bottom right
	vertices[7][0] = -1.0; vertices[7][1] = -1.0; vertices[7][2] = -1.0; vertices[7][3] = 1.0;//back bottom left

	center[0] = 0.0;  center[1] = 0.0; center[2] = 0.0; center[3] = 1.0;

	velocity[0] = 0.0;  velocity[1] = 0.0; velocity[2] = 0.0; velocity[3] = 1.0;

	axis[0] = 0.0; axis[1] = 0.0; axis[2] = 0.0; axis[3] = 1.0;

	angle = 0.25;

	for(int i = 0; i < 6; i++){
		normals[i][0] = 0.0;
		normals[i][1] = 0.0;
		normals[i][2] = 0.0;
	}

	for(int i = 0; i < 12; i++){
		edges[i][0] = 0.0;
		edges[i][1] = 0.0;
		edges[i][2] = 0.0;
	}
}

void Cube::createNormals(){
	float a[3];
	float b[3];

	vecFromPoints3Float(vertices[3], vertices[0], a);
	vecFromPoints3Float(vertices[1], vertices[0], b);
	vecCrossProduct3Float(a, b, normals[0]);
	vecNormalize3Float(normals[0]);

	vecFromPoints3Float(vertices[0], vertices[4], a);
	vecFromPoints3Float(vertices[5], vertices[4], b);
	vecCrossProduct3Float(a, b, normals[1]);
	vecNormalize3Float(normals[1]);

	vecFromPoints3Float(vertices[1], vertices[5], a);
	vecFromPoints3Float(vertices[6], vertices[5], b);
	vecCrossProduct3Float(a, b, normals[2]);
	vecNormalize3Float(normals[2]);

	vecFromPoints3Float(vertices[2], vertices[6], a);
	vecFromPoints3Float(vertices[7], vertices[6], b);
	vecCrossProduct3Float(a, b, normals[3]);
	vecNormalize3Float(normals[3]);

	vecFromPoints3Float(vertices[3], vertices[7], a);
	vecFromPoints3Float(vertices[4], vertices[7], b);
	vecCrossProduct3Float(a, b, normals[4]);
	vecNormalize3Float(normals[4]);

	vecFromPoints3Float(vertices[4], vertices[7], a);
	vecFromPoints3Float(vertices[6], vertices[7], b);
	vecCrossProduct3Float(a, b, normals[5]);
	vecNormalize3Float(normals[5]);
}

void Cube::createEdges(){
	//front face edges
	vecFromPoints3Float(vertices[0], vertices[1], edges[0]);
	vecFromPoints3Float(vertices[1], vertices[2], edges[1]);
	vecFromPoints3Float(vertices[2], vertices[3], edges[2]);
	vecFromPoints3Float(vertices[3], vertices[0], edges[3]);
	//back face edges
	vecFromPoints3Float(vertices[4], vertices[5], edges[4]);
	vecFromPoints3Float(vertices[5], vertices[6], edges[5]);
	vecFromPoints3Float(vertices[6], vertices[7], edges[6]);
	vecFromPoints3Float(vertices[7], vertices[4], edges[7]);
	//side face edges
	vecFromPoints3Float(vertices[4], vertices[0], edges[8]);
	vecFromPoints3Float(vertices[5], vertices[1], edges[9]);
	vecFromPoints3Float(vertices[6], vertices[2], edges[10]);
	vecFromPoints3Float(vertices[7], vertices[3], edges[11]);
}


