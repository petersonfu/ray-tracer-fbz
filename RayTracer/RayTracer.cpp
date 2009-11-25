#include "global.h"

#include "ray.h"
#include "tuples.h"
#include "ShapeBase.h"
#include "ShapeLight.h"

extern char g_debugbuff[DBG_BUFF_LEN];
extern CShapeBase** g_shapes;
extern GLint g_width;
extern GLint g_height;

//we suppose the view angle is 90 degrees and the project screen with z=-1.0f . screen has an area of +-1.0*+-1.0
void calcRay(int screen_x, int screen_y, CTuple3 view_point, CRay& view_ray)
{
	float xfloat= -1.0 + (float)screen_x/(float)g_width * 2.0;
	float yfloat= -1.0 + (float)screen_y/(float)g_width * 2.0;

	CTuple3 dir(xfloat-view_point.m_x,yfloat-view_point.m_y,-1.0-view_point.m_z);
	dir.normalize();
	view_ray.SetOrigin(view_point);
	view_ray.SetDirection(dir);
}

//check intersect
bool intersect(CRay view_ray, int &sect_shape, CTuple3 &sect_point)
{
	int i;
	float min_distance=INF_DISTANCE, distance;
	int min_shape=-1, shape=-1;
	int shape_count=SHAPE_COUNT;

	CTuple3 min_point, point;
	for(i=0;i<shape_count;i++)
	{
		if(g_shapes[i]->intersect(view_ray, point, distance))
		{
			if(distance < min_distance)
			{
				min_distance=distance;
				min_shape=i;
				min_point.SetValue(point.m_x,point.m_y,point.m_z);
			}
		}
	}
	if(min_shape!=-1)
	{
		sect_shape=min_shape;
		sect_point=min_point;
		return true;
	}
	else
	{
		sect_shape=-1;
		sect_point=view_ray.GetOrigin();
		return false;
	}
}

void RayTrace(CRay &view_ray, CTuple3& total_color, int depth)
{
	int sect_shape, i;
	CTuple3 color(0.0,0.0,0.0);
	CTuple3 vlight, vsect;
	CTuple3 sect_point(0.0,0.0,0.0);
	CTuple3 l,n,r,v;
	float product;
	int shape_count=SHAPE_COUNT;
	if( intersect(view_ray,sect_shape,sect_point))
	{
		if(g_shapes[sect_shape]->m_light)
		{
			vsect  = g_shapes[sect_shape]->m_material.m_reflect;
			color = color + vsect;
			vsect  = g_shapes[sect_shape]->m_material.m_diffuse;
			color = color + vsect;

		}
		else
		{
			for(i=0;i<shape_count;i++)
			{
				if(g_shapes[i]->m_light)
				{
					//calculate the ambient light
					vlight = g_shapes[i]->m_material.m_ambient;
					vsect  = g_shapes[sect_shape]->m_material.m_ambient;
					color = color + (vlight & vsect);

					//calculate the view plane
					g_shapes[sect_shape]->calcPlane(((CShapeLight*)g_shapes[i])->m_origin,view_ray.m_origin,sect_point,l,n,r,v);

					//calculate the diffuse light
					vlight = g_shapes[i]->m_material.m_diffuse;
					vsect  = g_shapes[sect_shape]->m_material.m_diffuse;
					product=l*n;
					//_snprintf(::g_debugbuff,DBG_BUFF_LEN,"(%f,%f,%f),%f\n",sect_point.m_x,sect_point.m_y,sect_point.m_z,product);
					//OutputDebugStringA(::g_debugbuff);
					if(product>0)
						color = color + (vlight & ( vsect * product));

					//calculate the reflected light
					vlight = g_shapes[i]->m_material.m_reflect;
					vsect  = g_shapes[sect_shape]->m_material.m_reflect;
					product=r*v;
					if(product>0)
						color = color + (vlight & ( vsect * (pow(product, g_shapes[sect_shape]->m_refl_factor))));
				}
			}
		}
	}
	else
	{
		color.SetValue(0.0,0.0,0.0);
	}

	total_color=color;
}