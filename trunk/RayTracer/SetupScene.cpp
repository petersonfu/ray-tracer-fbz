#include "ray.h"
#include "tuples.h"
#include "ShapeBase.h"
#include "ShapeSphere.h"
#include "ShapePlane.h"

extern CShapeBase** g_shapes;
extern int g_shape_count;
extern CTexture g_textures[MAX_TEXTURES];
extern int g_text_count;

void init_scene1()
{
	/*
	g_shapes[g_shape_count++]=new CShapeSphere( CTuple3(0.0,-1.0, -1.0), 
		CMaterial(CTuple3(1.0,1.0,1.0),CTuple3(0.1,0.1,0.1),CTuple3(0.1,0.1,0.1),CTuple3(0.0,0.0,0.0)),200.0, false,
		1.0,1.0,
		0.5);
		*/
	g_textures[g_text_count].init("D:\\texture.txt",2,2);
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
	g_textures[g_text_count++].init("D:\\Projects\\ray-tracer-fbz\\Generator\\rgb.txt",16,16);
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
		CTuple3(-0.8,0.3,0.8),
		CMaterial(CTuple3(0.1,0.1,0.1),CTuple3(0.5,0.5,0.5),CTuple3(0.5,0.5,0.5),CTuple3(0.0,0.0,0.0)),1.0,true,
		1.0,1.0,
		0.001);
	g_shapes[g_shape_count++]=new CShapeSphere(
		CTuple3(-0.15,0.4,0.75),
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
	CTuple3(0.0,0.0,-2.0),
	CMaterial(CTuple3(0.2,0.0,0.2),CTuple3(0.2,0.0,0.2),CTuple3(0.2,0.0,0.2),CTuple3(0.0,0.0,0.0)),1.0,false,
	//CMaterial(CTuple3(0.0,0.0,0.0),CTuple3(0.0,0.0,0.0),CTuple3(0.0,0.0,0.0)),1.0,false,
	1.0,1.0,
	CTuple3(0.0,0.0,1.0));
	g_textures[g_text_count++].init("D:\\Projects\\ray-tracer-fbz\\Generator\\tsinghua.txt",201,77);
	//g_textures[g_text_count++].init("D:\\Projects\\ray-tracer-fbz\\Generator\\rgb.txt",16,16);
	g_shapes[g_shape_count]->setTexture(0);
	g_shape_count++;

	/*g_shapes[g_shape_count++]=new CShapePlane(
	CTuple3(0.0,-1.5,0.0),
	CMaterial(CTuple3(0.2,0.2,0.2),CTuple3(0.2,0.2,0.2),CTuple3(0.2,0.2,0.2),CTuple3(0.0,0.0,0.0)),1.0,false,
	//CMaterial(CTuple3(0.0,0.0,0.0),CTuple3(0.0,0.0,0.0),CTuple3(0.0,0.0,0.0)),1.0,false,
	1.0,1.0,
	CTuple3(0.0,1.0,0.0));
	*/	
	/*
	g_shapes[g_shape_count++]=new CShapeSphere( CTuple3(0.0,0.0,-1.5),
	CMaterial(CTuple3(1.0,1.0,1.0),CTuple3(1.0,1.0,1.0),CTuple3(1.0,1.0,1.0)),20.0, false,
	1.0,1.0,
	0.30);
	*/

	g_shapes[g_shape_count++]=new CShapeSphere( 
		CTuple3(0.8,0.2, -1.0), 
		CMaterial(CTuple3(0.0,0.0,0.0),CTuple3(0.2,0.2,0.2),CTuple3(0.2,0.2,0.2),CTuple3(1.0,1.0,1.0)),200.0, false,
		1.1,1.0,
		0.3);

	g_shapes[g_shape_count++]=new CShapeSphere( 
		CTuple3(-0.15,-0.25, -1.0), 
		CMaterial(CTuple3(0.0,0.0,0.0),CTuple3(0.2,0.2,0.2),CTuple3(0.2,0.2,0.2),CTuple3(3.0,3.0,3.0)),200.0, false,
		1.1,1.0,
		0.5);

	int odd=false;
	for ( DTYPE i=-0.9; i<=0.9; i+=0.2)
	{
		for ( DTYPE j=-0.9; j<=0.9; j+=0.2)
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
				0.08);
			odd=!odd;
		}
	}
	
}