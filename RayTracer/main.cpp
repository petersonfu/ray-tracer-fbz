#include "global.h"

#include "ray.h"
#include "tuples.h"
#include "Texture.h"
#include "ShapeBase.h"
#include "ShapeSphere.h"
#include "ShapePlane.h"
#include "Box.h"

//vars for debug
char g_debugbuff[DBG_BUFF_LEN];
int g_refresh_count;

long intersect_count=0;
long shadow_intersect_count=0;
//vars for storage
float* g_pixels;
GLint g_width = 600;
GLint g_height = 600;

//vars for texture
CTexture g_textures[MAX_TEXTURES];
int g_text_count=0;

//
bool g_use_tracer;

//vars for shapes
CShapeBase** g_shapes;
int g_shape_count=0;

//vars for recursion
int g_depth;
DTYPE g_att_refl=0.1,g_att_refr=1.0;
CTuple3 g_att_reflect(g_att_refl,g_att_refl,g_att_refl), g_att_refract(g_att_refr,g_att_refr,g_att_refr);//1.0,1.0,1.0

#ifdef ENABLE_3DDA
//vars for 3dda
CBox g_box_list[GRID_SIZE][GRID_SIZE][GRID_SIZE];
CTuple3 g_leftdown(-X_BOUND,-Y_BOUND,-Z_BOUND),g_rightup(X_BOUND,Y_BOUND,Z_BOUND);
CTuple3 g_delta;
#endif


void init_scene1();
void init_scene2();
void init_scene3();
void init_scene4();
void init_scene5();
void init_scene6();
void init_scene7();
void init_scene8();
void init_scene9();
void init_scene10();

/* Prototypes */
void init();
void display();
void draw();
void timer();
void keyboard( unsigned char key, int x, int y );
bool intersect(CRay view_ray, int &sect_shape, CTuple3 &sect_point);
void RayTrace(CRay &view_ray, CTuple3& color, int depth);
void calcRay(int screen_x, int screen_y, CTuple3 view_point, CRay& view_ray);

#ifdef ENABLE_3DDA

void find_grid(CTuple3 point, int &xi, int &yi, int &zi)
{
	CTuple3 delta = point - g_leftdown;
	xi= (int)(floor(delta.m_x/g_delta.m_x));
	yi= (int)(floor(delta.m_y/g_delta.m_y));
	zi= (int)(floor(delta.m_z/g_delta.m_z));
}

void setup_grids()
{
	int i,x,y,z;
	CTuple3 left_down,right_up;
	int xl,yl,zl,xu,yu,zu;
	int shape_box_count;
	for(i=0;i<g_shape_count;i++)
	{
		shape_box_count=0;

		g_shapes[i]->getBoundaryBox(left_down,right_up);
		find_grid(left_down,xl,yl,zl);
		find_grid(right_up,xu,yu,zu);
		
		if(xl<0) xl=0;
		if(yl<0) yl=0;
		if(zl<0) zl=0;
		if(xu>=GRID_SIZE) xu=GRID_SIZE-1;
		if(yu>=GRID_SIZE) yu=GRID_SIZE-1;
		if(zu>=GRID_SIZE) zu=GRID_SIZE-1;

		//we need to find the grid for the 
		for(x=xl;x<=xu;x++)
			for(y=yl;y<=yu;y++)
				for(z=zl;z<=zu;z++)
				{
					if(g_shapes[i]->intersectBox(g_box_list[x][y][z]))
					{
						shape_box_count++;
						g_box_list[x][y][z].m_shapes.push_back(i);
					}
				}
	//	_snprintf(::g_debugbuff,DBG_BUFF_LEN,"Shape %d: %d boxes. From (%d,%d,%d) to (%d,%d,%d).\n",i,shape_box_count,xl,yl,zl,xu,yu,zu);
	//	OutputDebugStringA(::g_debugbuff);
	}
}
void init_3dda()
{
	int nPretimer = GetTickCount();
	g_delta = ( g_rightup - g_leftdown) * (1/(float)GRID_SIZE);
	int x,y,z;
	CTuple3 current_left_down;
	for(x=0;x<GRID_SIZE;x++)
		for(y=0;y<GRID_SIZE;y++)
			for(z=0;z<GRID_SIZE;z++)
			{
				current_left_down =  g_leftdown + CTuple3 ( g_delta.m_x * x,g_delta.m_y * y,g_delta.m_z * z);
				g_box_list[x][y][z].init(current_left_down, current_left_down+g_delta, x, y, z);
			}
	setup_grids();
	_snprintf(::g_debugbuff,DBG_BUFF_LEN,"Init 3DDA time: %d ms. \n",GetTickCount() - nPretimer);
	OutputDebugStringA(::g_debugbuff);
}

#endif

void init() {
	glShadeModel( GL_FLAT );
	glClearColor( 0.0, 0.0, 0.0, 1.0 );

	g_use_tracer=true;
	g_shapes=new CShapeBase * [SHAPE_COUNT];

	g_shape_count=0;

	init_scene10();

		//Need to dispose here!!!!!!!!!!!!!!!
#ifdef ENABLE_3DDA
	init_3dda();
#endif



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
			_snprintf(::g_debugbuff,DBG_BUFF_LEN,"%d ms, %d*%d, %d/%d shadow/total. %d shapes.\n",GetTickCount() - nPretimer, g_width, g_height,shadow_intersect_count,intersect_count,g_shape_count);
			glutSetWindowTitle(g_debugbuff);
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

