#ifndef __GLOBAL_H__
#define __GLOBAL_H__

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

#define MAX_WIDTH 800
#define MAX_HEIGHT 800
#define MAX_TEXTURES 10
#define INF_DISTANCE 100.0
#define SHAPE_COUNT 4300

#define SECT_MIN_DISTANCE 0.01f
#define SECT_DELTA_DISTANCE 0.00001
#define IGNORE_DELTA_DISTANCE 0.0001

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

#define DTYPE float

//3dda
#define ENABLE_3DDA
#define INF_BOUNDARY 100.0
/*scene6*/
/*
#define X_BOUND 4.5f
#define Y_BOUND 4.0f
#define Z_BOUND 4.0f
#define GRID_SIZE 31
*/
/*scene8*/
/*
#define X_BOUND 1.0f
#define Y_BOUND 1.0f
#define Z_BOUND 2.0f
#define GRID_SIZE 20
*/
/*scene_dinosaur*/
#define X_BOUND 1.2f
#define Y_BOUND 1.2f
#define Z_BOUND 1.2f
#define GRID_SIZE 5
#endif