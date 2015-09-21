//this program tests the collision of 5 cubes floating in space
//the 'r' key resets the cubes
//the 'q' or 'esc' quits the program

#include <cmath>
#include <cstdio>
#include <cstdlib>

#include <GL/gl.h>
#include <GL/glut.h>
#ifdef FREEGLUT
#include <GL/freeglut_ext.h>
#endif
#include "cube.h"
#include "mymath.h"
#include "collision.h"

Cube cube_a;
Cube cube_b;
Cube cube_c;
Cube cube_d;
Cube cube_e;

//planes of the view frustum
float leftPlane[] = {0.0, 0.0, 0.0, 0.0};
float rightPlane[] = {0.0, 0.0, 0.0, 0.0};
float topPlane[] = {0.0, 0.0, 0.0, 0.0};
float bottomPlane[] = {0.0, 0.0, 0.0, 0.0};
float nearPlane[] = {0.0, 0.0, 0.0, 0.0};
float farPlane[] = {0.0, 0.0, 0.0, 0.0};

//sets only the rotation axis and velocity to random values
void randomizeCube(Cube *cube){
	cube->axis[0] = float(rand() % 10);
	cube->axis[1] = float(rand() % 10);
	cube->axis[2] = float(rand() % 10);
	vecNormalize3Float(cube->axis);

	cube->velocity[0] = float(rand() % 3 + 2) /100.0;
	cube->velocity[1] = float(rand() % 3 + 2) /100.0;
	cube->velocity[2] = float(rand() % 3 + 2) /100.0;
}

//sets the positions of the cubes
//then randomly the rotation axis and velocity
void setCubes(){
	cube_a.color[0] = 1.0; 

	cube_b.color[2] = 1.0;

	cube_c.color[1] = 1.0;

	cube_d.color[0] = 0.925;
	cube_d.color[1] = 0.925;

	cube_e.color[0] = 0.75;
	cube_e.color[2] = 0.75;

	for(int i = 0; i < 8; i++){
		cube_a.vertices[i][0] += -3.0;
		cube_a.vertices[i][1] += 2.0;
		cube_a.vertices[i][2] += 2.0;

		cube_b.vertices[i][0] += 3.0;
		cube_b.vertices[i][1] += -3.0;
		cube_b.vertices[i][2] += 5.0;

		cube_d.vertices[i][0] += -3.0;
		cube_d.vertices[i][1] += -4.0;
		cube_d.vertices[i][2] += -6.0;

		cube_e.vertices[i][0] += 3.0;
		cube_e.vertices[i][1] += 3.0;
		cube_e.vertices[i][2] += -5.0;
	}

	cube_a.center[0] += -3.0;
	cube_a.center[1] += 2.0;
	cube_a.center[2] += 2.0;

	cube_b.center[0] += 3.0;
	cube_b.center[1] += -3.0;
	cube_b.center[2] += 5.0;


	cube_d.center[0] += -3.0;
	cube_d.center[1] += -4.0;
	cube_d.center[2] += -6.0;

	cube_e.center[0] += 3.0;
	cube_e.center[1] += 3.0;
	cube_e.center[2] += -5.0;

	randomizeCube(&cube_a);
	randomizeCube(&cube_b);
	randomizeCube(&cube_c);
	randomizeCube(&cube_d);
	randomizeCube(&cube_e);
}


//check if any of the cube's vertices are outside the
//view frustum and change the velocity if any are
void checkInsideVF(Cube *cube){
	//check if any of the vertices are outside the left or right plane
	//and change the x component of the velocity
	for(int i = 0; i < 8; i++){
		if(vecDot3Float(cube->vertices[i], leftPlane) + leftPlane[3]  < 0.0){
			if(cube->velocity[0] < 0.0){
				cube->velocity[0] = -cube->velocity[0];
			}
			break;
		}

		if(vecDot3Float(cube->vertices[i], rightPlane) + rightPlane[3]  < 0.0){
			if(cube->velocity[0] > 0.0){
				cube->velocity[0] = -cube->velocity[0];
			}
			break;
		}
	}

	//check if any of the vertices are outside the top or bottom plane
	//and change the y component of the velocity
	for(int i = 0; i < 8; i++){
		if(vecDot3Float(cube->vertices[i], topPlane) + topPlane[3]  < 0.0){
			if(cube->velocity[1] > 0.0){
				cube->velocity[1] = -cube->velocity[1];
			}
			break;
		}

		if(vecDot3Float(cube->vertices[i], bottomPlane) + bottomPlane[3]  < 0.0){
			if(cube->velocity[1] < 0.0){
				cube->velocity[1] = -cube->velocity[1];
			}
			break;
		}
	}

	//check if any of the vertices are outside the near or far plane
	//and change the z component of the velocity
	for(int i = 0; i < 8; i++){
		if(vecDot3Float(cube->vertices[i], nearPlane) + nearPlane[3]  < 0.0){
			if(cube->velocity[2] > 0.0){
				cube->velocity[2] = -cube->velocity[2];
			}
			break;
		}

		if(vecDot3Float(cube->vertices[i], farPlane) + farPlane[3]  < 0.0){
			if(cube->velocity[2] < 0.0){
				cube->velocity[2] = -cube->velocity[2];
			}
			break;
		}
	}
}


//swap the velocity of cubes that have collided
//and reverse the angle of rotation
//this is not a good physics implementation but for
//the most part it looks ok
void swapCubeProperties(Cube *cube0, Cube *cube1){
	float temp[3];
	vecCopy3Float(cube0->velocity, temp);
	vecCopy3Float(cube1->velocity, cube0->velocity);
	vecCopy3Float(temp, cube1->velocity);

	cube0->angle = -cube0->angle;
	cube1->angle = -cube1->angle;
}


void translateCube(Cube *cube){
	for(int i = 0; i < 8; i++){
		cube->vertices[i][0] += cube->velocity[0];
		cube->vertices[i][1] += cube->velocity[1];
		cube->vertices[i][2] += cube->velocity[2];
	}

	cube->center[0] += cube->velocity[0];
	cube->center[1] += cube->velocity[1];
	cube->center[2] += cube->velocity[2];
}

//first create a translation matrix that moves cube to (0,0,0)
//create rotation matrix from cube's axis, then multiply with translation matrix
//create a translation matrix that moves back to orginal position, multiply that
//matrix with the one above. Then multiply all vertices with final matrix
void rotateCube(Cube *cube){
	float translationMatrix[16];
	float rotationMatrix[16];
	float tempMatrix[16];
	float finalMatrix[16];

	createTranslationMatrix(-cube->center[0], -cube->center[1], -cube->center[2], translationMatrix);
	createRotationMatrix(rotationMatrix, cube->angle, cube->axis);
	mat4MultMat4Float(rotationMatrix, translationMatrix, tempMatrix);
	createTranslationMatrix(cube->center[0], cube->center[1], cube->center[2], translationMatrix);
	mat4MultMat4Float(translationMatrix, tempMatrix, finalMatrix);

	for(int i = 0; i < 8; i++){
		mat4MultVec4Float(finalMatrix, cube->vertices[i], cube->vertices[i]);
		cube->vertices[i][3] = 1.0;
	}
}


void drawCube(Cube *cube){
	//draw sides
	glColor3fv(cube->color);
	glBegin(GL_QUADS);
	glVertex3fv(cube->vertices[0]);
	glVertex3fv(cube->vertices[1]);
	glVertex3fv(cube->vertices[2]);
	glVertex3fv(cube->vertices[3]);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3fv(cube->vertices[4]);
	glVertex3fv(cube->vertices[5]);
	glVertex3fv(cube->vertices[1]);
	glVertex3fv(cube->vertices[0]);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3fv(cube->vertices[1]);
	glVertex3fv(cube->vertices[5]);
	glVertex3fv(cube->vertices[6]);
	glVertex3fv(cube->vertices[2]);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3fv(cube->vertices[7]);
	glVertex3fv(cube->vertices[6]);
	glVertex3fv(cube->vertices[2]);
	glVertex3fv(cube->vertices[3]);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3fv(cube->vertices[4]);
	glVertex3fv(cube->vertices[0]);
	glVertex3fv(cube->vertices[3]);
	glVertex3fv(cube->vertices[7]);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3fv(cube->vertices[4]);
	glVertex3fv(cube->vertices[5]);
	glVertex3fv(cube->vertices[6]);
	glVertex3fv(cube->vertices[7]);
	glEnd();

	//draw lines
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3fv(cube->vertices[0]);
	glVertex3fv(cube->vertices[1]);
	glEnd();

	glBegin(GL_LINES);
	glVertex3fv(cube->vertices[1]);
	glVertex3fv(cube->vertices[2]);
	glEnd();

	glBegin(GL_LINES);
	glVertex3fv(cube->vertices[2]);
	glVertex3fv(cube->vertices[3]);
	glEnd();

	glBegin(GL_LINES);
	glVertex3fv(cube->vertices[3]);
	glVertex3fv(cube->vertices[0]);
	glEnd();

	glBegin(GL_LINES);
	glVertex3fv(cube->vertices[4]);
	glVertex3fv(cube->vertices[5]);
	glEnd();

	glBegin(GL_LINES);
	glVertex3fv(cube->vertices[5]);
	glVertex3fv(cube->vertices[1]);
	glEnd();

	glBegin(GL_LINES);
	glVertex3fv(cube->vertices[4]);
	glVertex3fv(cube->vertices[0]);
	glEnd();

	glBegin(GL_LINES);
	glVertex3fv(cube->vertices[5]);
	glVertex3fv(cube->vertices[6]);
	glEnd();

	glBegin(GL_LINES);
	glVertex3fv(cube->vertices[6]);
	glVertex3fv(cube->vertices[2]);
	glEnd();

	glBegin(GL_LINES);
	glVertex3fv(cube->vertices[6]);
	glVertex3fv(cube->vertices[7]);
	glEnd();

	glBegin(GL_LINES);
	glVertex3fv(cube->vertices[4]);
	glVertex3fv(cube->vertices[7]);
	glEnd();

	glBegin(GL_LINES);
	glVertex3fv(cube->vertices[7]);
	glVertex3fv(cube->vertices[3]);
	glEnd();

}


void normalizePlane(float *plane){
	float L = 1.0f/vecLength3Float(plane);
  
	plane[0] = plane[0] * L;
	plane[1] = plane[1] * L;
	plane[2] = plane[2] * L;
	plane[3] = plane[3] * L;
}

//get the planes of the view frustrum
void getPlanes(){
	float projMatrix[16];
	float modelMatrix[16];
	glGetFloatv( GL_PROJECTION_MATRIX, projMatrix );
	glGetFloatv( GL_MODELVIEW_MATRIX, modelMatrix );
	mat4TransposeFloat(projMatrix);
	mat4TransposeFloat(modelMatrix);
	float combinedMatrix[16];
	mat4MultMat4Float(projMatrix, modelMatrix, combinedMatrix);

	leftPlane[0] = combinedMatrix[12] + combinedMatrix[0];
	leftPlane[1] = combinedMatrix[13] + combinedMatrix[1];
	leftPlane[2] = combinedMatrix[14] + combinedMatrix[2];
	leftPlane[3] = combinedMatrix[15] + combinedMatrix[3];
  
	rightPlane[0] = combinedMatrix[12] - combinedMatrix[0];
	rightPlane[1] = combinedMatrix[13] - combinedMatrix[1];
	rightPlane[2] = combinedMatrix[14] - combinedMatrix[2];
	rightPlane[3] = combinedMatrix[15] - combinedMatrix[3];
  
	topPlane[0] = combinedMatrix[12] - combinedMatrix[4];
	topPlane[1] = combinedMatrix[13] - combinedMatrix[5];
	topPlane[2] = combinedMatrix[14] - combinedMatrix[6];
	topPlane[3] = combinedMatrix[15] - combinedMatrix[7];
  
	bottomPlane[0] = combinedMatrix[12] + combinedMatrix[4];
	bottomPlane[1] = combinedMatrix[13] + combinedMatrix[5];
	bottomPlane[2] = combinedMatrix[14] + combinedMatrix[6];
	bottomPlane[3] = combinedMatrix[15] + combinedMatrix[7];
  
	nearPlane[0] = combinedMatrix[12] + combinedMatrix[8];
	nearPlane[1] = combinedMatrix[13] + combinedMatrix[9];
	nearPlane[2] = combinedMatrix[14] + combinedMatrix[10];
	nearPlane[3] = combinedMatrix[15] + combinedMatrix[11];

	farPlane[0] = combinedMatrix[12] - combinedMatrix[8];
	farPlane[1] = combinedMatrix[13] - combinedMatrix[9];
	farPlane[2] = combinedMatrix[14] - combinedMatrix[10];
	farPlane[3] = combinedMatrix[15] - combinedMatrix[11];
  
	normalizePlane(topPlane);
	normalizePlane(bottomPlane);
	normalizePlane(leftPlane);
	normalizePlane(rightPlane);
	normalizePlane(nearPlane);
	normalizePlane(farPlane);
}



void update(int x){
	cube_a.createNormals();
	cube_b.createNormals();
	cube_c.createNormals();
	cube_d.createNormals();
	cube_e.createNormals();

	cube_a.createEdges();
	cube_b.createEdges();
	cube_c.createEdges();
	cube_d.createEdges();
	cube_e.createEdges();

	checkInsideVF(&cube_a);
	checkInsideVF(&cube_b);
	checkInsideVF(&cube_c);
	checkInsideVF(&cube_d);
	checkInsideVF(&cube_e);

	//check for cubes colliding with each other
	if(cubesColliding(&cube_a, &cube_b)){
		swapCubeProperties(&cube_a, &cube_b);
	}

	if(cubesColliding(&cube_a, &cube_c)){
		swapCubeProperties(&cube_a, &cube_c);
	}

	if(cubesColliding(&cube_a, &cube_d)){
		swapCubeProperties(&cube_a, &cube_d);
	}

	if(cubesColliding(&cube_a, &cube_e)){
		swapCubeProperties(&cube_a, &cube_e);
	}

	if(cubesColliding(&cube_b, &cube_c)){
		swapCubeProperties(&cube_b, &cube_c);
	}

	if(cubesColliding(&cube_b, &cube_d)){
		swapCubeProperties(&cube_b, &cube_d);
	}

	if(cubesColliding(&cube_b, &cube_e)){
		swapCubeProperties(&cube_b, &cube_e);
	}

	if(cubesColliding(&cube_c, &cube_d)){
		swapCubeProperties(&cube_c, &cube_d);
	}

	if(cubesColliding(&cube_c, &cube_e)){
		swapCubeProperties(&cube_c, &cube_e);
	}

	if(cubesColliding(&cube_d, &cube_e)){
		swapCubeProperties(&cube_d, &cube_e);
	}

	translateCube(&cube_a);
	translateCube(&cube_b);
	translateCube(&cube_c);
	translateCube(&cube_d);
	translateCube(&cube_e);

	rotateCube(&cube_a);
	rotateCube(&cube_b);
	rotateCube(&cube_c);
	rotateCube(&cube_d);
	rotateCube(&cube_e);

	glutTimerFunc(16, update, 0);
	glutPostRedisplay();  
}


void display(){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	drawCube(&cube_a);
	drawCube(&cube_b);
	drawCube(&cube_c);
	drawCube(&cube_d);
	drawCube(&cube_e);

	glutSwapBuffers();
}


void reshape(int width, int height){
	if(height == 0){
		height = 1;
	}
	glViewport(0,0, (GLsizei)width, (GLsizei)height);
	double ratio = double(width)/double(height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, ratio, 10.0, 30.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );

	getPlanes();
}

//resets cube position
void resetCube(Cube *cube){
	cube->vertices[0][0] = -1.0; cube->vertices[0][1] = 1.0; cube->vertices[0][2] = 1.0; cube->vertices[0][3] = 1.0;
	cube->vertices[1][0] = 1.0; cube->vertices[1][1] = 1.0; cube->vertices[1][2] = 1.0; cube->vertices[1][3] = 1.0;
	cube->vertices[2][0] = 1.0; cube->vertices[2][1] = -1.0; cube->vertices[2][2] = 1.0; cube->vertices[2][3] = 1.0;
	cube->vertices[3][0] = -1.0; cube->vertices[3][1] = -1.0; cube->vertices[3][2] = 1.0; cube->vertices[3][3] = 1.0;
	cube->vertices[4][0] = -1.0; cube->vertices[4][1] = 1.0; cube->vertices[4][2] = -1.0; cube->vertices[4][3] = 1.0;
	cube->vertices[5][0] = 1.0; cube->vertices[5][1] = 1.0; cube->vertices[5][2] = -1.0; cube->vertices[5][3] = 1.0;
	cube->vertices[6][0] = 1.0; cube->vertices[6][1] = -1.0; cube->vertices[6][2] = -1.0; cube->vertices[6][3] = 1.0;
	cube->vertices[7][0] = -1.0; cube->vertices[7][1] = -1.0; cube->vertices[7][2] = -1.0; cube->vertices[7][3] = 1.0;

	cube->center[0] = 0.0;  cube->center[1] = 0.0; cube->center[2] = 0.0; cube->center[3] = 1.0;
}


void keyboardDown( unsigned char key, int x, int y ){
	switch( key ){
	case 27: // The 'esc' key
	case 'q'://quit program
		#ifdef FREEGLUT
		glutLeaveMainLoop( );
		#else
		exit( 0 );
		#endif
	break;
	case 'r'://reset cubes
		resetCube(&cube_a);
		resetCube(&cube_b);
		resetCube(&cube_c);
		resetCube(&cube_d);
		resetCube(&cube_e);
		setCubes();
	break;
	default:
	break;
	}
}


int main(int argc, char** argv){
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize( 600, 600);
	glutCreateWindow( "Demo" );

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glEnable( GL_DEPTH_TEST );
	glDepthRange(0.0, 1.0);
	glDepthFunc(GL_LEQUAL);

	setCubes();

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	glFrontFace(GL_CCW);
	glEnable(GL_NORMALIZE);
	glutKeyboardFunc( keyboardDown );
	glutReshapeFunc( reshape );
	glutDisplayFunc( display );
	glutTimerFunc(16, update, 0);
	glutMainLoop( );
	return(0);
}
