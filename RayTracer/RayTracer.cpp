#include "global.h"

#include "ray.h"
#include "tuples.h"
#include "ShapeBase.h"

extern char g_debugbuff[DBG_BUFF_LEN];
extern CShapeBase** g_shapes;
extern GLint g_width;
extern GLint g_height;
float current_x;
float current_y;

//we suppose the view angle is 90 degrees and the project screen with z=-1.0f . screen has an area of +-1.0*+-1.0
void calcRay(int screen_x, int screen_y, CTuple3 view_point, CRay& view_ray)
{
	float xfloat= -1.0 + (float)screen_x/(float)g_width * 2.0;
	float yfloat= -1.0 + (float)screen_y/(float)g_width * 2.0;
	current_x=xfloat;
	current_y=yfloat;

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
			if(distance < min_distance && distance>SECT_MIN_DISTANCE)
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
	if(depth==0)
	{
		total_color.SetValue(0.0,0.0,0.0);
		return;
	}

	int sect_shape, i;
	CTuple3 color(0.0,0.0,0.0),rcolor;
	CTuple3 vlight, vsect;
	CTuple3 sect_point(0.0,0.0,0.0);
	CTuple3 l,n,r,v;
	CRay shadow_ray,rray;
	int shadow_shape;
	CTuple3 shadow_point;
	float shadow_distance;
	float product;
	bool has_ambient, has_diffuse, has_reflect;
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
#ifdef ENABLE_AMBIENT
					//calculate the ambient light
					vlight = g_shapes[i]->m_material.m_ambient;
					vsect  = g_shapes[sect_shape]->m_material.m_ambient;
					color = color + (vlight & vsect);
#endif
					
					//calculate the view plane
					g_shapes[sect_shape]->calcPlane(g_shapes[i]->m_origin,view_ray.m_origin,sect_point,l,n,r,v);
					
					shadow_ray.SetDirection(l);
					shadow_ray.SetOrigin(sect_point);
					
					//determine shadows
					if(intersect(shadow_ray, shadow_shape, shadow_point) && shadow_shape!=i)
					{
						shadow_distance=(shadow_point-sect_point).metric();
						if(shadow_distance<(g_shapes[i]->m_origin - sect_point).metric())
							continue;
					}
#ifdef ENABLE_DIFFUSE
					//calculate the diffuse light
					vlight = g_shapes[i]->m_material.m_diffuse;
					vsect  = g_shapes[sect_shape]->m_material.m_diffuse;
					product=l*n;
					if(product>0)
						color = color + (vlight & ( vsect * product));
					
#endif

#ifdef ENABLE_REFLECT
					//calculate the reflected light
					vlight = g_shapes[i]->m_material.m_reflect;
					vsect  = g_shapes[sect_shape]->m_material.m_reflect;
					product=r*v;
					if(product>0)
						color = color + (vlight & ( vsect * (pow(product, g_shapes[sect_shape]->m_refl_factor))));
					
					//calculate the reflect 
					rray.SetOrigin(sect_point);
					rray.SetDirection(r);
					RayTrace(rray,rcolor,depth-1);
					color = color + (rcolor & vsect);
#endif
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