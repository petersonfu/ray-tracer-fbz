#include "global.h"

#include "ray.h"
#include "tuples.h"
#include "Texture.h"
#include "ShapeBase.h"
#include "ShapeSphere.h"
#include "ShapePlane.h"


char g_debugbuff[DBG_BUFF_LEN];
GLint g_width = 600;
GLint g_height = 600;
int g_depth;
int g_refresh_count;
float* g_pixels;
CTexture g_textures[MAX_TEXTURES];
int g_text_count=0;
bool g_use_tracer;
CShapeBase** g_shapes;
int g_shape_count=0;
DTYPE g_att_refl=0.3,g_att_refr=1.0;
CTuple3 g_att_reflect(g_att_refl,g_att_refl,g_att_refl), g_att_refract(g_att_refr,g_att_refr,g_att_refr);//1.0,1.0,1.0
void init_scene1();
void init_scene2();
void init_scene3();
void init_scene4();
void init_scene5();
void init_scene6();
void init_scene7();
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
	g_shapes=new CShapeBase * [SHAPE_COUNT];

	g_shape_count=0;

	init_scene6();
		//Need to dispose here!!!!!!!!!!!!!!!

	_snprintf(::g_debugbuff,DBG_BUFF_LEN,"%d shapes.\n",g_shape_count);
	OutputDebugStringA(::g_debugbuff);

	g_depth=8;
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
#ifdef DBG_SPECIAL
			calcRay(150, 150, view_point, view_ray);
			RayTrace(view_ray, pixel_color, g_depth); //depth here
				*(current_pixel++)=pixel_color.m_x;
				*(current_pixel++)=pixel_color.m_y;
				*(current_pixel++)=pixel_color.m_z;
#else
			for(i=0;i<g_height;i++)
			{
				for(j=0;j<g_width;j++)
				{
					calcRay(j, i, view_point, view_ray);
					RayTrace(view_ray, pixel_color, g_depth); //depth here
					*(current_pixel++)=(float) pixel_color.m_x;
					*(current_pixel++)=(float) pixel_color.m_y;
					*(current_pixel++)=(float) pixel_color.m_z;
				}
			}
#endif
#ifdef ENABLE_ANTIALIASE
			current_pixel=g_pixels;
			int anti=ENABLE_ANTIALIASE;
			int ri,ci,rgbi;
			for (ri=0;ri<g_height-1;ri++)
			{
				for(ci=0;ci<g_width-1;ci++)
				{
					for(rgbi=0;rgbi<3;rgbi++)
					{
						//right-down corner
						*(current_pixel) = 
							(
								*(current_pixel)
							+	*(current_pixel+3)
							+	*(current_pixel+3*g_width)
							+	*(current_pixel+3*g_width+3)
							)/4;
						current_pixel++;
					}

				}
			}
#endif
			//change to float
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
	for(i=0;i<g_shape_count;i++)
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

