#include "mymath.h"

void vecCopy3Float(float *src, float *dest){
	for(int i = 0; i < 3; i++){
		dest[i] = src[i];
	}
}


void vecCopy4Float(float *src, float *dest){
	for(int i = 0; i < 4; i++){
		dest[i] = src[i];
	}
}


void matCopy4Float(float *src, float *dest){
	for(int i = 0; i < 16; i++){
		dest[i] = src[i];
	}
}


void vecFromPoints3Float(float *head, float *tail, float *dest){
	for(int i = 0; i < 3; i++){
		dest[i] = head[i] - tail[i];
	}
}


void mat4TransposeFloat(float *m){
	float temp[16];
	matCopy4Float(m, temp);

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			m[i*4 + j] = temp[j*4 + i];
		}
	}
}


float vecLength3Float(float *a){
  float sum = 0.0;
  int i;
  for(i = 0; i < 3; i++){
    sum += (a[i] * a[i]);
  }
  return(sqrt(sum));
}


void vecNormalize3Float(float* v){
  float length;
  length = vecLength3Float(v);
   if( length <= 0.0 ){
     v[0] = 0.0;
     v[1] = 0.0;
     v[2] = 0.0;
   }

   if( length != 1.0 ){
    length = 1.0 / length;
    v[0] = v[0] * length;
    v[1] = v[1] * length;
    v[2] = v[2] * length;
  }
}


float vecDot3Float(float *a, float *b){
  float sum = 0.0;
  int i;
  for(i = 0; i < 3; i++){
    sum += a[i] * b[i];
  }
  return(sum);
}


void vecCrossProduct3Float(float *a, float *b, float *c){
	c[0] = a[1]*b[2] - a[2]*b[1];
	c[1] = a[2]*b[0] - a[0]*b[2];
	c[2] = a[0]*b[1] - a[1]*b[0];
}


void mat4MultVec4Float(float *m, float *vSrc, float *vDest){
	float c[4];
	vecCopy4Float(vSrc, c);

	vDest[0] = m[0]*c[0] + m[1]*c[1] + m[2]*c[2] + m[3]*c[3];
	vDest[1] = m[4]*c[0] + m[5]*c[1] + m[6]*c[2] + m[7]*c[3];
	vDest[2] = m[8]*c[0] + m[9]*c[1] + m[10]*c[2] + m[11]*c[3];
	vDest[3] = m[12]*c[0] + m[13]*c[1] + m[14]*c[2] + m[15]*c[3];
}


void mat4MultMat4Float( float *a, float *b, float *dest){
	dest[0] = a[0]*b[0] + a[1]*b[4] + a[2]*b[8] + a[3]*b[12]; 
	dest[1] = a[0]*b[1] + a[1]*b[5] + a[2]*b[9] + a[3]*b[13];
	dest[2] = a[0]*b[2] + a[1]*b[6] + a[2]*b[10] + a[3]*b[14];
	dest[3] = a[0]*b[3] + a[1]*b[7] + a[2]*b[11] + a[3]*b[15];
  
	dest[4] = a[4]*b[0] + a[5]*b[4] + a[6]*b[8] + a[7]*b[12];
	dest[5] = a[4]*b[1] + a[5]*b[5] + a[6]*b[9] + a[7]*b[13];
	dest[6] = a[4]*b[2] + a[5]*b[6] + a[6]*b[10] + a[7]*b[14];
	dest[7] = a[4]*b[3] + a[5]*b[7] + a[6]*b[11] + a[7]*b[15];
  
	dest[8] = a[8]*b[0] + a[9]*b[4] + a[10]*b[8] + a[11]*b[12];
	dest[9] = a[8]*b[1] + a[9]*b[5] + a[10]*b[9] + a[11]*b[13];
	dest[10] = a[8]*b[2] + a[9]*b[6] + a[10]*b[10] + a[11]*b[14];
	dest[11] = a[8]*b[3] + a[9]*b[7] + a[10]*b[11] + a[11]*b[15];
  
	dest[12] = a[12]*b[0] + a[13]*b[4] + a[14]*b[8] + a[15]*b[12];
	dest[13] = a[12]*b[1] + a[13]*b[5] + a[14]*b[9] + a[15]*b[13];
	dest[14] = a[12]*b[2] + a[13]*b[6] + a[14]*b[10] + a[15]*b[14];
	dest[15] = a[12]*b[3] + a[13]*b[7] + a[14]*b[11] + a[15]*b[15];
}


void createTranslationMatrix(float x, float y, float z, float *matrix){
	for(int i = 0; i < 16; i++){
		matrix[i] = 0.0;
	}

	matrix[0] = 1.0;
	matrix[3] = x;
	matrix[5] = 1.0;
	matrix[7] = y;
	matrix[10] = 1.0;
	matrix[11] = z;
	matrix[15] = 1.0; 
}


void createRotationMatrix(float *matrix, float angle, float *axis){
	for(int i = 0; i < 16; i++){
		matrix[i] = 0.0;
	}

	//angle is converted from degrees to radians
	float s = sin(0.017453 * angle);
	float c = cos(0.017453 * angle);

	matrix[0] = c + (axis[0]*axis[0]) * (1.0 - c);
	matrix[1] = (axis[0]*axis[1]) * (1.0 - c) - axis[2]*s;
	matrix[2] = axis[1]*s + (axis[0]*axis[2]) * (1.0 - c);

	matrix[4] = axis[2]*s + (axis[0]*axis[1]) * (1.0 - c);
	matrix[5] = c + (axis[1]*axis[1]) * (1.0 - c);
	matrix[6] = -axis[0]*s + (axis[1]*axis[2]) * (1.0 - c);

	matrix[8] = -axis[1]*s + (axis[0]*axis[1]) * (1.0 - c);
	matrix[9] = axis[0]*s + (axis[01]*axis[2]) * (1.0 - c);
	matrix[10] = c + (axis[2]*axis[2]) * (1.0 - c);

	matrix[15] = 1.0;
}



