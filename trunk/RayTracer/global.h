#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <assert.h>
#include <list>
using namespace std;

#define DBG_BUFF_LEN 100
//#define DBG_SPECIAL

#define MAX_WIDTH 1280
#define MAX_HEIGHT 1280
#define MAX_TEXTURES 10
#define INF_DISTANCE 100.0f
#define SHAPE_COUNT 410

#define SECT_MIN_DISTANCE 0.01f
#define SECT_DELTA_DISTANCE 0.0001f
#define IGNORE_DELTA_DISTANCE 0.0001f

#define ENABLE_AMBIENT

//Using phong model
//#define ENABLE_PHONG
#define ENABLE_DIFFUSE
#define ENABLE_REFLECT

//Using area light model
//#undef ENABLE_PHONG
#define ENABLE_TRACE_REFLECT
#define ENABLE_TRACE_REFRACT

#define PLANE_PROJECTION
//#define ENABLE_ANTIALIASE 2 //2 or 4 antialiase

#define DTYPE double

//3dda
//#define ENABLE_3DDA
#define INF_BOUNDARY 100.0f
/*scene6*/
/*
#define X_BOUND 4.5f
#define Y_BOUND 4.0f
#define Z_BOUND 4.0f
#define GRID_SIZE 31
*/
/*scene8*/

#define X_BOUND 1.0f
#define Y_BOUND 1.0f
#define Z_BOUND 2.0f
#define GRID_SIZE 20

