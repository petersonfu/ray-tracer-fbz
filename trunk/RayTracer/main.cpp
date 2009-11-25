#include "global.h"

#include "ray.h"
#include "tuples.h"
#include "ShapeBase.h"
#include "ShapeSphere.h"
#include "ShapePlane.h"


char g_debugbuff[DBG_BUFF_LEN];
GLint g_width = 500;
GLint g_height = 500;
int g_depth;
int g_refresh_count;
float* g_pixels;
bool g_use_tracer=true;
CShapeBase** g_shapes;

/* Prototypes */
void init();
void display();
void draw();
void timer();
void keyboard( unsigned char key, int x, int y );
bool intersect(CRay view_ray, int &sect_shape, CTuple3 &sect_point);
void RayTrace(CRay &view_ray, CTuple3& color, int depth);
void calcRay(int screen_x, int screen_y, CTuple3 view_point, CRay& view_ray);


void init() {
	glShadeModel( GL_FLAT );
	glClearColor( 0.0, 0.0, 0.0, 1.0 );

	g_use_tracer=true;
	g_shapes=new CShapeBase* [SHAPE_COUNT];

	g_shapes[0]=new CShapeSphere( CTuple3(0.1,0.0,-1.0),
		CMaterial(CTuple3(1.0,0.0,0.0),CTuple3(1.0,0.0,0.0),CTuple3(1.0,0.0,0.0)),20.0, false,
		0.50);
	g_shapes[1]=new CShapeSphere( CTuple3(-0.55,0.0, -1.0), 
		CMaterial(CTuple3(0.0,1.0,1.0),CTuple3(0.0,1.0,1.0),CTuple3(0.0,1.0,1.0)),200.0, false,
		0.1);
	g_shapes[2]=new CShapeSphere(
		CTuple3(0.2,0.7,0.5),
		CMaterial(CTuple3(0.1,0.1,0.1),CTuple3(0.5,0.5,0.5),CTuple3(0.5,0.5,0.5)),1.0,true,
		0.001);
	g_shapes[3]=new CShapeSphere(
		CTuple3(-0.2,0.6,-1.0),
		CMaterial(CTuple3(0.1,0.1,0.1),CTuple3(0.5,0.5,0.5),CTuple3(0.5,0.5,0.5)),1.0,true,
		0.001);
	g_shapes[4]=new CShapePlane(
		CTuple3(0,-3.0,-1.0),
		CMaterial(CTuple3(0.0,0.5,0.0),CTuple3(0.0,0.5,0.0),CTuple3(0.0,0.5,0.0)),1.0,false,
		CTuple3(0.0,1.0,0.0));

		//Need to dispose here!!!!!!!!!!!!!!!
	g_depth=1;
	g_refresh_count=0;
	g_pixels=new float[3*MAX_WIDTH*MAX_HEIGHT];
}

void display() {
	
	int i,j;
	CTuple3 view_point(0.0,0.0,0.0), pixel_color;
	float* current_pixel=NULL;

	g_width = glutGet( GLUT_WINDOW_WIDTH );
	g_height = glutGet( GLUT_WINDOW_HEIGHT );
	
	if(g_use_tracer)
	{
		current_pixel=g_pixels;
		CRay view_ray;
		//for each point on screen
		if(g_refresh_count==0)
		{
			int nPretimer = GetTickCount();
			for(i=0;i<g_height;i++)
			{
				for(j=0;j<g_width;j++)
				{
					calcRay(j, i, view_point, view_ray);
					RayTrace(view_ray, pixel_color, g_depth); //depth here
					*(current_pixel++)=pixel_color.m_x;
					*(current_pixel++)=pixel_color.m_y;
					*(current_pixel++)=pixel_color.m_z;
				}
			}
			_snprintf(::g_debugbuff,DBG_BUFF_LEN,"Execution time: %d ms, %d*%d.\n",GetTickCount() - nPretimer, g_width, g_height);
			OutputDebugStringA(::g_debugbuff);
		}

		g_refresh_count++;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, g_width, 0, g_height);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glPixelStorei( GL_UNPACK_ROW_LENGTH, g_width );
		glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );
		glRasterPos2i(0,0);		// Position at base of window
		glDrawPixels( g_width, g_height, GL_RGB, GL_FLOAT, g_pixels );

		glFlush();
		glutSwapBuffers();
	}
	else
	{
	glClear( GL_COLOR_BUFFER_BIT );
	/* Don't need reshape with these function calls */
	g_width = glutGet( GLUT_WINDOW_WIDTH );
	g_height = glutGet( GLUT_WINDOW_HEIGHT );
	GLfloat aspectRatio;
	
	if( g_height > 0 ) { /* Make sure it's not minimized */
		aspectRatio = (double)g_width/g_height;
		/* Setup the projection and model view matricies */
		glViewport( 0, 0, g_width, g_height );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		//gluPerspective( 90, aspectRatio, 1.0, 40.0 );
		gluPerspective( 90, aspectRatio, 1.0, 40.0 );
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		//gluLookAt( 0.0, 1.0, -1.0, 0.0, 0.0, 10.0, 0.0, 1.0, 0.0 );
		gluLookAt( 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 );
	
		draw();
		glutSwapBuffers();
	}
	}
}

/* Draw the objects */
void draw() {
	int i;
	for(i=0;i<SHAPE_COUNT;i++)
	{
		g_shapes[i]->drawByGlut();
	}
	return;
}

/* Redraw the scene every 10 milliseconds */
void timer( int value ) {
	glutPostRedisplay();
	glutTimerFunc( 3000, timer, 0 );
}

/* Exit when the escape key is pressed */
void keyboard( unsigned char key, int x, int y ) {
	switch( key ) {
		case 27: /* Escape key pressed */
			exit(1);
			break;
		default:
			break;
	}
}

int main( int argc, char *argv[] ) {
	
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
	glutInitWindowPosition( 200, 200 );
	glutInitWindowSize( g_width, g_height ); 
	glutCreateWindow( argv[0] );
	init();
	glutDisplayFunc( display );  /* call back functions */
	glutTimerFunc( 10, timer, 0 );
	glutKeyboardFunc( keyboard );
	glutMainLoop();
	
	return 0;
}

