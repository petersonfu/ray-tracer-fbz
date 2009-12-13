#include "ray.h"
#include "tuples.h"
#include "ShapeBase.h"
#include "ShapeSphere.h"
#include "ShapePlane.h"
#include "ShapeCubic.h"
#include "ShapeCylinder.h"
#include "ShapeTriangle.h"
#include "SimpleObject.h"
#include "TracerView.h"
#include <fstream>
using namespace std;
using namespace SimpleOBJ;

extern CShapeBase** g_shapes;
extern int g_shape_count;
extern CTexture g_textures[MAX_TEXTURES];
extern int g_text_count;
extern DTYPE myMax(DTYPE a,DTYPE b,DTYPE c);
extern CTracerView g_tracer_view;

void LoadTriangleModel(const char *textfile_name, const int texture)//set texture as -1 is no texture should be assigned.
{
	ifstream read_file;
	read_file.open(textfile_name);
	assert(read_file.is_open());
	DTYPE v1x,v1y,v1z,v2x,v2y,v2z,v3x,v3y,v3z;
	
	while(read_file.good())
	{
		read_file 
			>>v1x >>v1y >>v1z 
			>>v2x >>v2y >>v2z 
			>>v3x >>v3y >>v3z;
		g_shapes[g_shape_count]=new CShapeTriangle(
			//CMaterial(CTuple3(0.05,0.05,0.05),CTuple3(1.0,1.0,1.0),CTuple3(1.0,1.0,1.0),CTuple3(0.0,0.0,0.0)),20.0,false,
			//CMaterial(CTuple3(0.05,0.05,0.05),CTuple3(1.0,0.0,0.0),CTuple3(1.0,0.0,0.0),CTuple3(0.0,0.0,0.0)),20.0,false,
			CMaterial(CTuple3(0.0,0.0,0.0),CTuple3(0.2,0.2,0.2),CTuple3(0.2,0.2,0.2),CTuple3(1.0,1.0,1.0)),200.0,false,
			1.1,1.0,
			CTuple3(v1x,v1y,v1z),CTuple3(v2x,v2y,v2z),CTuple3(v3x,v3y,v3z)
			);
		if(texture>=0)
			g_shapes[g_shape_count]->setTexture(texture);
		g_shape_count++;
	}
	read_file.close();

}

void LoadObjModel(const char *textfile_name, const int texture, float cubic_scale = 0.5)
{
	int i;
	Array<int,3> face;
	Vec3f v1, v2, v3;
	CTuple3 sv1,sv2,sv3;
	CTuple3 shift;
	shift.SetValue(0.0,0.0,-1.0);
	CSimpleObject so;
	so.LoadFromObj(textfile_name);

	//scale the object to 0.0 to -1.0 cubic
	float scale = cubic_scale / (myMax(so.m_fXScaleH, so.m_fYScaleH, so.m_fZScaleH));

	for(i=0; i<so.m_nTriangles;i++)
	{
		face = so.m_pTriangleList[i];
		v1 = so.m_pVertexList[face[0]];
		v2 = so.m_pVertexList[face[1]];
		v3 = so.m_pVertexList[face[2]];
		sv1.SetValue(v1.x,v1.y,v1.z);
		sv2.SetValue(v2.x,v2.y,v2.z);
		sv3.SetValue(v3.x,v3.y,v3.z);
		sv1 = sv1 * scale;
		sv2 = sv2 * scale;
		sv3 = sv3 * scale;
		g_shapes[g_shape_count]=new CShapeTriangle(
			CMaterial(CTuple3(0.05,0.05,0.05),CTuple3(1.0,1.0,1.0),CTuple3(1.0,1.0,1.0),CTuple3(0.0,0.0,0.0)),20.0,false,
			1.0,1.0,
			sv1,sv2,sv3
			);
		if(texture>=0)
			g_shapes[g_shape_count]->setTexture(texture);
		g_shape_count++;
	}
	
}

void init_scene1()
{
	/*
	g_shapes[g_shape_count++]=new CShapeSphere( CTuple3(0.0,-1.0, -1.0), 
		CMaterial(CTuple3(1.0,1.0,1.0),CTuple3(0.1,0.1,0.1),CTuple3(0.1,0.1,0.1),CTuple3(0.0,0.0,0.0)),200.0, false,
		1.0,1.0,
		0.5);
		*/
	g_textures[g_text_count].init("..\\Generator\\rgb.txt",2,2);
	g_text_count++;
	
	g_shapes[g_shape_count]=new CShapePlane(
		CTuple3(0.0,0.0,-1.0),
		CMaterial(CTuple3(1.0,0.0,0.0),CTuple3(1.0,0.0,0.0),CTuple3(1.0,0.0,0.0),CTuple3(0.0,0.0,0.0)),1.0,false,
		//CMaterial(CTuple3(0.0,0.0,0.0),CTuple3(0.0,0.0,0.0),CTuple3(0.0,0.0,0.0)),1.0,false,
		1.0,1.0,
		CTuple3(0.0,0.0,1.0));
	g_shapes[g_shape_count]->setTexture(0);
	g_shape_count++;

	g_shapes[g_shape_count++]=new CShapeSphere(
		CTuple3(0.0,0.0,1.0),
		CMaterial(CTuple3(0.0,0.0,0.0),CTuple3(1.0,1.0,1.0),CTuple3(1.0,1.0,1.0),CTuple3(1.0,1.0,1.0)),0.0,true,
		1.0,1.0,
		0.001);
	
}
void init_scene2()
{
	
	g_shapes[g_shape_count++]=new CShapeSphere( CTuple3(0.1,0.0,-1.0),
		CMaterial(CTuple3(1.0,0.0,0.0),CTuple3(1.0,0.0,0.0),CTuple3(1.0,0.0,0.0),CTuple3(0.0,0.0,0.0)),200.0, false,
		1.0,1.0,
		0.50);
	g_shapes[g_shape_count++]=new CShapeSphere( CTuple3(-0.55,0.0, -1.0),
		CMaterial(CTuple3(0.0,1.0,1.0),CTuple3(0.0,1.0,1.0),CTuple3(0.0,1.0,1.0),CTuple3(0.0,0.0,0.0)),200.0, false,
		1.0,1.0,
		0.1);
	g_shapes[g_shape_count++]=new CShapeSphere(
		CTuple3(0.2,0.7,-0.5),
		CMaterial(CTuple3(0.1,0.1,0.1),CTuple3(0.5,0.5,0.5),CTuple3(0.5,0.5,0.5),CTuple3(0.0,0.0,0.0)),1.0,true,
		1.0,1.0,
		0.01);
	g_shapes[g_shape_count++]=new CShapeSphere(
		CTuple3(-0.2,-0.6,-0.5),
		CMaterial(CTuple3(0.1,0.1,0.1),CTuple3(0.5,0.5,0.5),CTuple3(0.5,0.5,0.5),CTuple3(0.0,0.0,0.0)),1.0,true,
		1.0,1.0,
		0.01);
	/*
	g_shapes[g_shape_count++]=new CShapePlane(
		CTuple3(0,-3.0,-1.0),
		CMaterial(CTuple3(0.0,0.5,0.0),CTuple3(0.0,0.5,0.0),CTuple3(0.0,0.5,0.0),CTuple3(0.0,0.0,0.0)),1.0,false,
		1.0,1.0,
		CTuple3(0.0,1.0,0.0));
		*/

}




void init_scene3()
{
	g_shapes[g_shape_count++]=new CShapeSphere( CTuple3(0.0,0.0,-1.5),
		CMaterial(CTuple3(1.0,1.0,1.0),CTuple3(1.0,1.0,1.0),CTuple3(1.0,1.0,1.0),CTuple3(0.0,0.0,0.0)),20.0, false,
		1.0,1.0,
		0.30);
	g_shapes[g_shape_count++]=new CShapeSphere( CTuple3(-0.4,-0.2, -1.0), 
		CMaterial(CTuple3(0.0,1.0,0.0),CTuple3(0.0,1.0,0.0),CTuple3(0.0,1.0,0.0),CTuple3(0.0,0.0,0.0)),200.0, false,
		1.0,1.0,
		0.2);
	g_shapes[g_shape_count++]=new CShapeSphere(
		CTuple3(0.5,0.0,-0.5),
		CMaterial(CTuple3(0.1,0.1,0.1),CTuple3(0.5,0.5,0.5),CTuple3(0.5,0.5,0.5),CTuple3(0.0,0.0,0.0)),1.0,true,
		1.0,1.0,
		0.01);
	g_shapes[g_shape_count++]=new CShapeSphere(
		CTuple3(-0.7,0.3,0.0),
		CMaterial(CTuple3(0.1,0.1,0.1),CTuple3(0.5,0.5,0.5),CTuple3(0.5,0.5,0.5),CTuple3(0.0,0.0,0.0)),1.0,true,
		1.0,1.0,
		0.01);
	g_shapes[g_shape_count++]=new CShapePlane(
		CTuple3(0,-3.0,-1.0),
		CMaterial(CTuple3(0.2,0.2,0.2),CTuple3(0.2,0.2,0.2),CTuple3(0.2,0.2,0.2),CTuple3(0.0,0.0,0.0)),1.0,false,
		1.0,1.0,
		CTuple3(0.0,1.0,1.0));
	g_shapes[g_shape_count++]=new CShapeSphere( CTuple3(0.4,-0.2, -1.0), 
		CMaterial(CTuple3(0.0,0.0,1.0),CTuple3(0.0,0.0,1.0),CTuple3(0.0,0.0,1.0),CTuple3(0.0,0.0,0.0)),200.0, false,
		1.0,1.0,
		0.2);
	g_shapes[g_shape_count++]=new CShapeSphere( CTuple3(0,0.5, -1.0), 
		CMaterial(CTuple3(1.0,0.0,0.0),CTuple3(1.0,0.0,0.0),CTuple3(1.0,0.0,0.0),CTuple3(0.0,0.0,0.0)),200.0, false,
		1.0,1.0,
		0.2);
}








void init_scene4()
{
	g_shapes[g_shape_count++]=new CShapeSphere(
		CTuple3(-0.5,-0.5,-0.5),
		CMaterial(CTuple3(0.2,0.2,0.2),CTuple3(1.0,1.0,1.0),CTuple3(1.0,1.0,1.0),CTuple3(0.0,0.0,0.0)),1.0,true,
		1.0,1.0,
		0.01);
	/*g_shapes[g_shape_count++]=new CShapeSphere(
		CTuple3(-0.7,0.3,0.0),
		CMaterial(CTuple3(0.1,0.1,0.1),CTuple3(0.5,0.5,0.5),CTuple3(0.5,0.5,0.5)),1.0,true,
		1.0,1.0,
		0.001);
		*/
	
	g_shapes[g_shape_count++]=new CShapePlane(
		CTuple3(0.0,0.0,-2.0),
		CMaterial(CTuple3(1.0,0.0,0.0),CTuple3(1.0,0.0,0.0),CTuple3(1.0,0.0,0.0),CTuple3(0.0,0.0,0.0)),1.0,false,
		//CMaterial(CTuple3(0.0,0.0,0.0),CTuple3(0.0,0.0,0.0),CTuple3(0.0,0.0,0.0)),1.0,false,
		1.0,1.0,
		CTuple3(0.0,0.0,1.0));
		
	/*
	g_shapes[g_shape_count++]=new CShapeSphere( CTuple3(0.0,0.0,-1.5),
		CMaterial(CTuple3(1.0,1.0,1.0),CTuple3(1.0,1.0,1.0),CTuple3(1.0,1.0,1.0)),20.0, false,
		1.0,1.0,
		0.30);
	*/
	
	g_shapes[g_shape_count++]=new CShapeSphere( 
		CTuple3(0.0,0.0, -1.0), 
		CMaterial(CTuple3(0.1,0.1,0.1),CTuple3(0.1,0.1,0.1),CTuple3(0.1,0.1,0.1),CTuple3(1.0,1.0,1.0)),200.0, false,
		1.3,1.0,
		0.3);
	
	
	for ( DTYPE i=-0.6; i<=0.6; i+=0.3)
		for ( DTYPE j=-0.6; j<=0.6; j+=0.3)
			g_shapes[g_shape_count++]=new CShapeSphere( 
				CTuple3(i,j, -2.0), 
				CMaterial(CTuple3(0.0,1.0,1.0),CTuple3(0.0,1.0,1.0),CTuple3(0.0,1.0,1.0),CTuple3(0.0,0.0,0.0)),200.0, false,
				1.0,1.0,
				0.13);
}

void init_scene5()
{
	
	g_shapes[g_shape_count++]=new CShapePlane(
		CTuple3(0.0,0.0,-1.50),
		CMaterial(CTuple3(0.0,1.0,1.0),CTuple3(0.0,0.5,0.5),CTuple3(0.0,0.5,0.5),CTuple3(0.0,0.5,0.5)),200.0,false,
		1.0,1.0,
		CTuple3(0.0,1.0,1.0));
	

	
	g_shapes[g_shape_count++]=new CShapeSphere( CTuple3(0.0,0.0, -1.0), 
		CMaterial(CTuple3(0.0,0.0,0.0),CTuple3(0.2,0.2,0.2),CTuple3(0.2,0.2,0.2),CTuple3(1.0,1.0,1.0)),20.0, false,
		1.1,1.0,
		0.3);
	
	
	g_shapes[g_shape_count++]=new CShapeSphere( CTuple3(0.0,0.0, -1.0), 
		//CMaterial(CTuple3(0.0,0.0,0.0),CTuple3(0.2,0.2,0.2),CTuple3(0.2,0.2,0.2),CTuple3(1.0,1.0,1.0)),200.0, false,
		CMaterial(CTuple3(0.0,0.0,0.0),CTuple3(2.0,0.0,0.0),CTuple3(2.0,0.0,0.0),CTuple3(0.0,0.0,0.00)),200.0, false,
		1.0,1.0,
		0.1);
		

	/*g_shapes[g_shape_count++]=new CShapePlane(
		CTuple3(0.0,0.0,2.0),
		CMaterial(CTuple3(0.1,0.1,0.1),CTuple3(1.0,1.0,1.0),CTuple3(1.0,1.0,1.0),CTuple3(1.0,1.0,1.0)),1.0,true,
		//CMaterial(CTuple3(0.0,0.0,0.0),CTuple3(0.0,0.0,0.0),CTuple3(0.0,0.0,0.0)),1.0,false,
		1.0,1.0,
		CTuple3(0.0,0.0,-1.0));*/
	g_shapes[g_shape_count++]=new CShapeSphere(
		CTuple3(0.5,0.5,-0.5),
		CMaterial(CTuple3(0.5,0.5,0.5),CTuple3(1.0,1.0,1.0),CTuple3(1.0,1.0,1.0),CTuple3(0.5,0.5,0.5)),0.0,true,
		1.0,1.0,
		0.01);
		
		
	
}

void init_scene6()
{
	g_shapes[g_shape_count++]=new CShapeSphere(
		CTuple3(-0.2,0.3,-0.8),
		CMaterial(CTuple3(0.1,0.1,0.1),CTuple3(0.5,0.5,0.5),CTuple3(0.5,0.5,0.5),CTuple3(0.0,0.0,0.0)),1.0,true,
		1.0,1.0,
		0.001);
	g_shapes[g_shape_count++]=new CShapeSphere(
		CTuple3(-0.15,0.4,-0.75),
		CMaterial(CTuple3(0.1,0.1,0.1),CTuple3(0.5,0.5,0.5),CTuple3(0.5,0.5,0.5),CTuple3(0.0,0.0,0.0)),1.0,true,
		1.0,1.0,
		0.001);
	/*g_shapes[g_shape_count++]=new CShapeSphere(
		CTuple3(-0.7,0.3,0.0),
		CMaterial(CTuple3(0.1,0.1,0.1),CTuple3(0.5,0.5,0.5),CTuple3(0.5,0.5,0.5)),1.0,true,
		1.0,1.0,
		0.001);
		*/
	
	g_shapes[g_shape_count]=new CShapePlane(
		CTuple3(-3.0,0.0,-3.5),
		CMaterial(CTuple3(0.2,0.0,0.2),CTuple3(0.2,0.0,0.2),CTuple3(0.2,0.0,0.2),CTuple3(0.0,0.0,0.0)),1.0,false,
		//CMaterial(CTuple3(0.0,0.0,0.0),CTuple3(0.0,0.0,0.0),CTuple3(0.0,0.0,0.0)),1.0,false,
		1.0,1.0,
		CTuple3(0.1,0.0,2.0));
	g_textures[g_text_count++].init("..\\Generator\\tsinghua.txt",201,77);
	g_shapes[g_shape_count]->setTexture(0);
	g_shape_count++;

	g_shapes[g_shape_count++]=new CShapePlane(
		CTuple3(0.0,-1.5,0.0),
		CMaterial(CTuple3(0.2,0.2,0.2),CTuple3(0.2,0.2,0.2),CTuple3(0.2,0.2,0.2),CTuple3(0.0,0.0,0.0)),1.0,false,
		//CMaterial(CTuple3(0.0,0.0,0.0),CTuple3(0.0,0.0,0.0),CTuple3(0.0,0.0,0.0)),1.0,false,
		1.0,1.0,
		CTuple3(0.0,1.0,0.0));
		
	/*
	g_shapes[g_shape_count++]=new CShapeSphere( CTuple3(0.0,0.0,-1.5),
		CMaterial(CTuple3(1.0,1.0,1.0),CTuple3(1.0,1.0,1.0),CTuple3(1.0,1.0,1.0)),20.0, false,
		1.0,1.0,
		0.30);
	*/
	
	g_shapes[g_shape_count++]=new CShapeSphere( 
		CTuple3(0.8,0.2, -2.0), 
		CMaterial(CTuple3(0.0,0.0,0.0),CTuple3(0.2,0.2,0.2),CTuple3(0.2,0.2,0.2),CTuple3(1.0,1.0,1.0)),200.0, false,
		1.1,1.0,
		0.3);
	
	g_shapes[g_shape_count++]=new CShapeSphere( 
		CTuple3(-0.15,-0.25, -2.0), 
		CMaterial(CTuple3(0.0,0.0,0.0),CTuple3(0.2,0.2,0.2),CTuple3(0.2,0.2,0.2),CTuple3(2.0,2.0,2.0)),200.0, false,
		1.1,1.0,
		0.5);
	int odd=false;
	for ( DTYPE i=-1.2; i<=2.0; i+=0.8)
	{
		for ( DTYPE j=-1.0; j<=1.0; j+=0.5)
		{
			g_shapes[g_shape_count++]=new CShapeSphere( 
				CTuple3(i,j, -3.0), 
				CMaterial(
					CTuple3(0.0,0.0,0.0),
					CTuple3((odd?0.0:1.0),1.0,(odd?1.0:0.0)),
					CTuple3((odd?0.0:1.0),1.0,(odd?1.0:0.0)),
					CTuple3(0.0,0.0,0.0)),
				20000.0, false,
				1.0,1.0,
				0.15);
			odd=!odd;
		}
	}
}
void init_scene7()
{
	
	g_shapes[g_shape_count++]=new CShapeSphere( CTuple3(0.1,0.0,-1.0),
		CMaterial(CTuple3(0.1,0.1,0.1),CTuple3(0.1,0.1,0.1),CTuple3(0.1,0.1,0.1),CTuple3(1.0,1.0,1.0)),20.0, false,
		1.33,1.0,
		0.50);
	g_shapes[g_shape_count++]=new CShapeSphere( CTuple3(-0.4,0.0, -1.8),
		CMaterial(CTuple3(0.0,1.0,1.0),CTuple3(0.0,1.0,1.0),CTuple3(0.0,1.0,1.0),CTuple3(0.0,0.0,0.0)),200.0, false,
		1.0,1.0,
		0.1);
	g_shapes[g_shape_count++]=new CShapeSphere(
		CTuple3(0.2,0.7,-0.5),
		CMaterial(CTuple3(0.1,0.1,0.1),CTuple3(0.5,0.5,0.5),CTuple3(0.5,0.5,0.5),CTuple3(0.0,0.0,0.0)),1.0,true,
		1.0,1.0,
		0.01);
	g_shapes[g_shape_count++]=new CShapeSphere(
		CTuple3(-0.2,0.6,-1.0),
		CMaterial(CTuple3(0.1,0.1,0.1),CTuple3(0.5,0.5,0.5),CTuple3(0.5,0.5,0.5),CTuple3(0.0,0.0,0.0)),1.0,true,
		1.0,1.0,
		0.01);
	g_shapes[g_shape_count++]=new CShapePlane(
		CTuple3(0,-3.0,-1.0),
		CMaterial(CTuple3(0.0,0.5,0.0),CTuple3(0.0,0.5,0.0),CTuple3(0.0,0.5,0.0),CTuple3(0.0,0.0,0.0)),1.0,false,
		1.0,1.0,
		CTuple3(0.0,1.0,1.0));

}

void init_scene8()
{
	g_shapes[g_shape_count++]=new CShapeSphere(
		CTuple3(0.8,-0.3,-0.5),
		CMaterial(CTuple3(0.1,0.1,0.1),CTuple3(0.5,0.5,0.5),CTuple3(0.5,0.5,0.5),CTuple3(0.0,0.0,0.0)),1.0,true,
		1.0,1.0,
		0.001);
	g_shapes[g_shape_count++]=new CShapeSphere(
		CTuple3(-0.3,0.4,-0.5),
		CMaterial(CTuple3(0.1,0.1,0.1),CTuple3(0.5,0.5,0.5),CTuple3(0.5,0.5,0.5),CTuple3(0.0,0.0,0.0)),1.0,true,
		1.0,1.0,
		0.001);

	
	g_shapes[g_shape_count]=new CShapePlane(
	CTuple3(0.0,0.0,-2.0),
	CMaterial(CTuple3(0.2,0.0,0.2),CTuple3(0.2,0.0,0.2),CTuple3(0.2,0.0,0.2),CTuple3(0.0,0.0,0.0)),1.0,false,
	//CMaterial(CTuple3(0.0,0.0,0.0),CTuple3(0.0,0.0,0.0),CTuple3(0.0,0.0,0.0)),1.0,false,
	1.0,1.0,
	CTuple3(0.0,0.0,1.0));
	//g_textures[g_text_count++].init("D:\\Projects\\ray-tracer-fbz\\Generator\\tsinghua.txt",201,77);
	g_textures[g_text_count++].init("..\\Generator\\rgb.txt",16,16);
	g_shapes[g_shape_count]->setTexture(0);
	g_shape_count++;

	g_shapes[g_shape_count++]=new CShapeSphere( 
		CTuple3(0.8,0.2, -1.0), 
		CMaterial(CTuple3(0.0,0.0,0.0),CTuple3(0.2,0.2,0.2),CTuple3(0.2,0.2,0.2),CTuple3(1.0,1.0,1.0)),20.0, false,
		1.1,1.0,
		0.3);

	g_shapes[g_shape_count++]=new CShapeSphere( 
		CTuple3(-0.15,-0.25, -1.0), 
		CMaterial(CTuple3(0.0,0.0,0.0),CTuple3(0.2,0.2,0.2),CTuple3(0.2,0.2,0.2),CTuple3(1.0,1.0,1.0)),200.0, false,
		1.1,1.0,
		0.3);

	int odd=false;
	for ( DTYPE i=-0.95; i<=0.95; i+=0.1)
	{
		for ( DTYPE j=-0.95; j<=0.95; j+=0.1)
		{
			g_shapes[g_shape_count++]=new CShapeSphere( 
				CTuple3(i,j, -1.8), 
				CMaterial(
				CTuple3(0.0,0.0,0.0),
				CTuple3((odd?0.0:1.0),1.0,(odd?1.0:0.0)),
				CTuple3((odd?0.0:1.0),1.0,(odd?1.0:0.0)),
				CTuple3(0.0,0.0,0.0)),
				20000.0, false,
				1.0,1.0,
				0.03);
			odd=!odd;
		}
	}
	
}

void init_scene9()
{
	g_textures[g_text_count++].init("..\\Generator\\rgb.txt",16,16);
	LoadTriangleModel("..\\Models\\Pyramid2.txt",-1);
	
	g_shapes[g_shape_count]=new CShapePlane(
		CTuple3(0.0,0.0,-2.0),
		CMaterial(CTuple3(0.2,0.0,0.2),CTuple3(0.2,0.0,0.2),CTuple3(0.2,0.0,0.2),CTuple3(0.0,0.0,0.0)),1.0,false,
		//CMaterial(CTuple3(0.0,0.0,0.0),CTuple3(0.0,0.0,0.0),CTuple3(0.0,0.0,0.0)),1.0,false,
		1.0,1.0,
		CTuple3(0.0,0.0,1.0));
	//g_textures[g_text_count++].init("D:\\Projects\\ray-tracer-fbz\\Generator\\tsinghua.txt",201,77);
	g_textures[g_text_count++].init("..\\Generator\\tsinghua.txt",201,77);
	g_shapes[g_shape_count]->setTexture(1);
	g_shape_count++;

	g_shapes[g_shape_count++]=new CShapeSphere(
		CTuple3(0.8,-0.3,0.5),
		CMaterial(CTuple3(0.1,0.1,0.1),CTuple3(0.5,0.5,0.5),CTuple3(0.5,0.5,0.5),CTuple3(0.0,0.0,0.0)),1.0,true,
		1.0,1.0,
		0.001);
	g_shapes[g_shape_count++]=new CShapeSphere(
		CTuple3(-0.8,0.3,0.5),
		CMaterial(CTuple3(0.1,0.1,0.1),CTuple3(0.5,0.5,0.5),CTuple3(0.5,0.5,0.5),CTuple3(0.0,0.0,0.0)),1.0,true,
		1.0,1.0,
		0.001);

}

void init_scene10()
{
	g_textures[g_text_count].init("..\\Generator\\skin.txt",225,225);
	LoadObjModel("..\\Models\\dinosaur.2k.obj",g_text_count);
	g_text_count++;

	g_shapes[g_shape_count]=new CShapePlane(
		CTuple3(0.0,0.0,-2.0),
		CMaterial(CTuple3(0.2,0.0,0.2),CTuple3(0.2,0.0,0.2),CTuple3(0.2,0.0,0.2),CTuple3(0.0,0.0,0.0)),1.0,false,
		//CMaterial(CTuple3(0.0,0.0,0.0),CTuple3(0.0,0.0,0.0),CTuple3(0.0,0.0,0.0)),1.0,false,
		1.0,1.0,
		CTuple3(0.0,0.0,1.0));
	//g_textures[g_text_count++].init("D:\\Projects\\ray-tracer-fbz\\Generator\\tsinghua.txt",201,77);
	g_textures[g_text_count].init("..\\Generator\\brick.txt",450,450);
	g_shapes[g_shape_count]->setTexture(g_text_count);
	g_text_count++;
	g_shape_count++;

	g_shapes[g_shape_count++]=new CShapeSphere(
		CTuple3(0.0,0.0,0.5),
		CMaterial(CTuple3(0.1,0.1,0.1),CTuple3(1.0,1.0,1.0),CTuple3(1.0,1.0,1.0),CTuple3(0.0,0.0,0.0)),1.0,true,
		1.0,1.0,
		0.001);
	g_shapes[g_shape_count++]=new CShapeSphere(
		CTuple3(-0.8,0.3,0.5),
		CMaterial(CTuple3(0.1,0.1,0.1),CTuple3(0.5,0.5,0.5),CTuple3(0.5,0.5,0.5),CTuple3(0.0,0.0,0.0)),1.0,true,
		1.0,1.0,
		0.001);

	g_tracer_view.setView(
		CTuple3(0.0,0.0,0.0),
		CTuple3(-1.0,-1.0,1.0),
		CTuple3(1.0,-1.0,1.0),
		CTuple3(-1.0,1.0,1.0),
		TRACEVIEW_PLANE
		);
}

void init_scene_dinosaur()
{

	g_textures[g_text_count].init("..\\Generator\\skin.txt",225,225);
	LoadObjModel("..\\Models\\dinosaur.2k.obj",g_text_count);
	g_text_count++;

	g_shapes[g_shape_count]=new CShapePlane(
		CTuple3(0.0,0.0,-1.0),
		CMaterial(CTuple3(0.2,0.0,0.2),CTuple3(0.2,0.0,0.2),CTuple3(0.2,0.0,0.2),CTuple3(0.0,0.0,0.0)),1.0,false,
		//CMaterial(CTuple3(0.0,0.0,0.0),CTuple3(0.0,0.0,0.0),CTuple3(0.0,0.0,0.0)),1.0,false,
		1.0,1.0,
		CTuple3(0.0,0.0,1.0));
	//g_textures[g_text_count++].init("D:\\Projects\\ray-tracer-fbz\\Generator\\tsinghua.txt",201,77);
	g_textures[g_text_count].init("..\\Generator\\brick.txt",450,450);
	g_shapes[g_shape_count]->setTexture(g_text_count);
	g_text_count++;
	g_shape_count++;

	g_shapes[g_shape_count++]=new CShapeSphere(
		CTuple3(0.8,-0.3,0.5),
		CMaterial(CTuple3(0.1,0.1,0.1),CTuple3(1.0,1.0,1.0),CTuple3(1.0,1.0,1.0),CTuple3(0.0,0.0,0.0)),1.0,true,
		1.0,1.0,
		0.001);
	g_shapes[g_shape_count++]=new CShapeSphere(
		CTuple3(-0.8,0.3,0.5),
		CMaterial(CTuple3(0.1,0.1,0.1),CTuple3(0.5,0.5,0.5),CTuple3(0.5,0.5,0.5),CTuple3(0.0,0.0,0.0)),1.0,true,
		1.0,1.0,
		0.001);
		
	g_tracer_view.setView(
		CTuple3(0.0,0.0,0.0),
		CTuple3(-1.0,1.0,0.0),
		CTuple3(-1.0,-1.0,0.0),
		CTuple3(0.0,1.0,1.0),
		TRACEVIEW_PLANE
		);
		
}