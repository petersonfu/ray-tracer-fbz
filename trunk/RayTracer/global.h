#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

#define DBG_BUFF_LEN 100
//#define DBG_SPECIAL

#define MAX_WIDTH 1280
#define MAX_HEIGHT 800
#define INF_DISTANCE 100.0f
#define SHAPE_COUNT 200
#define SECT_MIN_DISTANCE 0.01f
#define SECT_DELTA_DISTANCE 0.0001f

#define ENABLE_AMBIENT
#define ENABLE_DIFFUSE
#define ENABLE_REFLECT
#define ENABLE_TRACE_REFLECT
#define ENABLE_TRACE_REFRACT



