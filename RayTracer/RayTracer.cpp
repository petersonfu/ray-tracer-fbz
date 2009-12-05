#include "global.h"

#include "Texture.h"
#include "ray.h"
#include "tuples.h"
#include "ShapeBase.h"

extern char g_debugbuff[DBG_BUFF_LEN];
extern CShapeBase** g_shapes;
extern GLint g_width;
extern GLint g_height;
DTYPE current_x;
DTYPE current_y;
extern int g_shape_count;
extern CTuple3 g_att_reflect, g_att_refract;
extern DTYPE sqrt(DTYPE x);
extern CTexture g_textures[MAX_TEXTURES];
extern int g_text_count;

//we suppose the view angle is 90 degrees and the project screen with z=-1.0f . screen has an area of +-1.0*+-1.0
void calcRay(int screen_x, int screen_y, CTuple3 view_point, CRay& view_ray)
{
	DTYPE xfloat= -1.0 + (DTYPE)screen_x/(DTYPE)g_width * 2.0;
	DTYPE yfloat= -1.0 + (DTYPE)screen_y/(DTYPE)g_width * 2.0;
	current_x=xfloat;
	current_y=yfloat;
#ifndef PLANE_PROJECTION
	CTuple3 dir(xfloat-view_point.m_x,yfloat-view_point.m_y,-1.0-view_point.m_z);
	dir.normalize();
	view_ray.SetOrigin(view_point);
	view_ray.SetDirection(dir);
#else
	view_ray.SetOrigin(CTuple3(xfloat,yfloat,view_point.m_z));
	view_ray.SetDirection(CTuple3(0,0,-1.0-view_point.m_z));
#endif
}

//check intersect
int intersect(CRay view_ray, int &sect_shape, CTuple3 &sect_point)
{
	int i;
	DTYPE min_distance=INF_DISTANCE, distance;
	int min_shape=-1, shape=-1;
	int result=0, min_result;
	int shape_count=g_shape_count;

	CTuple3 min_point, point;
	for(i=0;i<shape_count;i++)
	{
		if(result=(g_shapes[i]->intersect(view_ray, point, distance)))
		{
			if(distance < min_distance)// && distance>SECT_MIN_DISTANCE)
			{
				min_distance=distance;
				min_shape=i;
				min_result=result;
				min_point.SetValue(point.m_x,point.m_y,point.m_z);
			}
		}
	}
	if(min_shape!=-1)
	{
		sect_shape=min_shape;
		sect_point=min_point;
		return min_result;
	}
	else
	{
		sect_shape=-1;
		sect_point=view_ray.GetOrigin();
		return 0;
	}
}

/*
returns:
1 if intersected;
0 if not at all intersected;
-1 if intersected by a transparent primitive and saves the the hall_factor of this primitive.
*/
int shadow_intersect(CRay shadow_ray, int start_shape, int light, CTuple3 &hall_factor)
{
	int i;
	bool find_trans=false;
	DTYPE source_distance = g_shapes[light]->calcDistance(shadow_ray.m_origin);
	int result;
	CTuple3 point;
	CTuple3 refr_factor;
	DTYPE distance;
	int shape_count=g_shape_count;
	for(i=0;i<shape_count;i++)
	{
		if(i==light) 
			continue;
		if(result=(g_shapes[i]->intersect(shadow_ray, point, distance)))
		{
			if(distance < source_distance)// && distance>SECT_MIN_DISTANCE)
			{
				if(start_shape!=i || result==1)
					return 1;
				refr_factor = g_shapes[i]->m_material.m_refract;
				if(refr_factor.all_zero())
					return 1;
				else if(find_trans) //has been intersected by another transparent primitive
					return 1;
				else
				{
					find_trans=true;
					hall_factor=refr_factor;
				}				
			}
		}
	}
	if(find_trans)
		return -1;
	else
		return 0;
}

void RayTrace(CRay &view_ray, CTuple3& total_color, int depth)
{
	if(depth==0)
	{
		total_color.SetValue(0.0,0.0,0.0);
		return;
	}

	int sect_shape, i, result, shadow_result, texture;
	CTuple3 color(0.0,0.0,0.0),rcolor,tcolor;
	CTuple3 vlight, vsect;
	CTuple3 sect_point(0.0,0.0,0.0);
	CTuple3 l,n,r,v,t,s,ht;
	CTuple3 vamb,vdiff,vrefl,vrefr;
	CRay shadow_ray,rray,tray;
	int shadow_shape;
	CTuple3 shadow_point, hall_factor;
	DTYPE shadow_distance;
	DTYPE product;
	DTYPE eita_inv,eita2,eita1;
	DTYPE temp_float;
	DTYPE cos_sita1, cos_sita2;
	DTYPE text_u, text_v;
	bool has_ambient, has_diffuse, has_reflect;
	int shape_count=g_shape_count;
	if( result = intersect(view_ray,sect_shape,sect_point))
	{
		
		vdiff = g_shapes[sect_shape]->m_material.m_diffuse;
		vrefr = g_shapes[sect_shape]->m_material.m_refract;

		texture=g_shapes[sect_shape]->m_texture;
		if(texture<0)
		{
			vamb = g_shapes[sect_shape]->m_material.m_ambient;
			vrefl = g_shapes[sect_shape]->m_material.m_reflect;
		}
		else
		{
			g_shapes[sect_shape]->getTextureMap(sect_point,text_u,text_v);
			vrefl = g_textures[texture].getTexture(text_u,text_v);
			vamb = vrefl * 0.1;
		}


		if(g_shapes[sect_shape]->m_light)
		{
			//we should suppose here that a light source has equal reflect and diffuse I.
			
			color = color + vrefl;
			
			//color.SetValue(0.0,0.0,0.0);
			
		}
		else
		{
			if(fabs(current_x)<0.2 && fabs(current_y)<0.2)
			{
				n=n;
			}

			g_shapes[sect_shape]->calcPlane(sect_point, n);
			if(result==-1)
				n = n * (-1);
			v = ( view_ray.GetOrigin() - sect_point );
			v.normalize();

			for(i=0;i<shape_count;i++)
			{
				if(g_shapes[i]->m_light)
				{
#ifdef ENABLE_AMBIENT
					//calculate the ambient light
					vlight = g_shapes[i]->m_material.m_ambient;
					color = color + (vlight & vamb);
#endif

#ifdef ENABLE_PHONG
					if(g_shapes[sect_shape]->m_material.m_reflect.all_zero() && g_shapes[sect_shape]->m_material.m_diffuse.all_zero())
						continue;
#else

#endif

					l = (g_shapes[i]->m_origin - sect_point);
					l.normalize();
					r = (n * 2.0) * ( n * l) - l;
					r.normalize();

					//calculate the shadow
					shadow_ray.SetDirection(l);
					shadow_ray.SetOrigin( sect_point + ( v * SECT_DELTA_DISTANCE ) );
					
					//determine shadows
					
					shadow_result = shadow_intersect(shadow_ray, sect_shape, i, hall_factor);
					
					
#ifdef ENABLE_PHONG
					if(shadow_result!=0)
						continue;
#ifdef ENABLE_DIFFUSE
					//calculate the diffuse light
					if(!g_shapes[sect_shape]->m_material.m_diffuse.all_zero())
					{
						vlight = g_shapes[i]->m_material.m_diffuse;
						product=l*n;
						if(product>0)
							color = color + (vlight & ( vdiff * product));
					}
#endif

#ifdef ENABLE_REFLECT
					//calculate the reflected light
					if(!g_shapes[sect_shape]->m_material.m_reflect.all_zero())
					{
						vlight = g_shapes[i]->m_material.m_reflect;
						product=r*v;
						if(product>0)
							color = color + (vlight & ( vrefl * (pow(product, g_shapes[sect_shape]->m_refl_factor))));
					}
#endif
#else
					switch(shadow_result)
					{
					case 1:
						continue;
						break;
					case 0:

						if(vrefl.all_zero())
							continue;

						vlight = g_shapes[i]->m_material.m_reflect;
						color=color + ( ( vlight & vrefl) * ( n * l) );
						break;
					case -1:
						//Hall diff-refraction
						
						if(n*l<0)
						{
							vlight = g_shapes[i]->m_material.m_refract;
							color=color + ( ( vlight & hall_factor) * ( - (n * l) ) );
						}
						
						//Hall refraction
						if(result>0)
						{
							//from outer to inner
							eita1=g_shapes[sect_shape]->m_e_refract;
							eita2=g_shapes[sect_shape]->m_i_refract;
						}
						else
						{
							//from outer to inner
							eita2=g_shapes[sect_shape]->m_e_refract;
							eita1=g_shapes[sect_shape]->m_i_refract;
						}
						ht= (l*eita2)+(v*eita1);
						ht.normalize();
						if(eita2>eita1)
							ht=ht*(-1);
						color=color + ( ( vlight & vrefr) * ( pow ( n * ht, g_shapes[sect_shape]->m_refl_factor) ) );
						break;
					default:
						break;
					}
#endif

				}
			}
#ifndef ENABLE_PHONG

#ifdef ENABLE_TRACE_REFLECT
			//calculate the reflect 
			if(! vrefl.all_zero() && result>0 )
			{
				s= n * ( 2 * ( n * v ) ) - v; 
				rray.SetOrigin( sect_point + ( s * SECT_DELTA_DISTANCE ) );
				rray.SetDirection(s);
				s.normalize();
				RayTrace(rray,rcolor,depth-1);
				if(! rcolor.all_zero())
					color = color + ( (rcolor & vrefl & g_att_reflect));
			}
			
#endif

#ifdef ENABLE_TRACE_REFRACT
			if(! vrefr.all_zero() )
			{
				eita_inv = (result > 0)? ( g_shapes[sect_shape]->m_e_refract / g_shapes[sect_shape]->m_i_refract):
					(g_shapes[sect_shape]->m_i_refract/g_shapes[sect_shape]->m_e_refract);
				eita_inv = -eita_inv;
				cos_sita1 = (n * v);
				//total reflection check
				temp_float=(1.0-cos_sita1*cos_sita1)*(eita_inv*eita_inv);
				if(temp_float<=1.0)
				{
					cos_sita2 = sqrt(1.0-temp_float);
					t = (v * eita_inv) - (n * (cos_sita2 + (eita_inv * cos_sita1)));
					t.normalize();
					tray.SetOrigin(sect_point + ( t * SECT_DELTA_DISTANCE ) );
					tray.SetDirection(t);
					RayTrace(tray,tcolor,depth-1);
					color = color + (tcolor & g_shapes[sect_shape]->m_material.m_refract & g_att_refract);
				}
				
			}
#endif
#endif
		}
	}
	else
	{
		color.SetValue(0.0,0.0,0.0);
	}
	/*
	_snprintf(::g_debugbuff,DBG_BUFF_LEN,"%d: point(%f,%f,%f),color(%f,%f,%f).\n",
		sect_shape,sect_point.m_x,sect_point.m_y,sect_point.m_z,
		color.m_x,color.m_y,color.m_z);
	OutputDebugStringA(::g_debugbuff);
	*/
	total_color=color;

	total_color.reset_threshold(1.0);
}

