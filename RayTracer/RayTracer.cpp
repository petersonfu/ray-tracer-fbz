#include "global.h"

#include "Texture.h"
#include "ray.h"
#include "tuples.h"
#include "ShapeBase.h"
#include "TracerView.h"

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
extern CTracerView g_tracer_view;

#ifdef ENABLE_3DDA
extern CBox g_box_list[GRID_SIZE][GRID_SIZE][GRID_SIZE];
extern CTuple3 g_leftdown,g_rightup;
extern CTuple3 g_delta;
#endif

extern long intersect_count;
extern void find_grid(CTuple3 point, int &xi, int &yi, int &zi);
extern long shadow_intersect_count;
CTraceRecord rec[SHAPE_COUNT];

//we suppose the view angle is 90 degrees and the project screen with z=-1.0f . screen has an area of +-1.0*+-1.0
void calcRay(int screen_x, int screen_y, CRay& view_ray)
{
	DTYPE xfloat= (DTYPE)screen_x/(DTYPE)g_width;
	DTYPE yfloat= (DTYPE)screen_y/(DTYPE)g_width;
	current_x=xfloat;
	current_y=yfloat;
	g_tracer_view.calcRay(xfloat,yfloat,view_ray);

/*
#ifndef PLANE_PROJECTION
	CTuple3 dir(xfloat-view_point.m_x,yfloat-view_point.m_y,-1.0-view_point.m_z);
	dir.normalize();
	view_ray.SetOrigin(view_point);
	view_ray.SetDirection(dir);
#else
	view_ray.SetOrigin(CTuple3(xfloat,yfloat,view_point.m_z));
	view_ray.SetDirection(CTuple3(0,0,-1.0-view_point.m_z));
#endif
*/
}
#ifdef ENABLE_3DDA
void getNextBox(CTuple3 direction,
				CTuple3 in_point, int in_x,int in_y,int in_z,
				CTuple3 &next_point, int &next_x, int &next_y, int &next_z)
{
	CTuple3 target;
	CBox *cur_box = &(g_box_list[in_x][in_y][in_z]);
	target.m_x=(direction.m_x>0)? (cur_box->m_right_up.m_x):(cur_box->m_left_down.m_x);
	target.m_y=(direction.m_y>0)? (cur_box->m_right_up.m_y):(cur_box->m_left_down.m_y);
	target.m_z=(direction.m_z>0)? (cur_box->m_right_up.m_z):(cur_box->m_left_down.m_z);
	target = target - in_point;
	float xdis = (direction.m_x!=0.0)? (target.m_x / direction.m_x):(INF_DISTANCE);
	float ydis = (direction.m_y!=0.0)? (target.m_y / direction.m_y):(INF_DISTANCE);
	float zdis = (direction.m_z!=0.0)? (target.m_z / direction.m_z):(INF_DISTANCE);
	if(xdis<=ydis && xdis<=zdis)
	{
		//select x change
		next_point = in_point + (direction * xdis);
		next_x = (direction.m_x>0) ? (in_x+1):(in_x-1);
		next_y = in_y;
		next_z = in_z;
	}
	else if(ydis<=xdis && ydis<=zdis)
	{
		//select x change
		next_point = in_point + (direction * ydis);
		next_y = (direction.m_y>0) ? (in_y+1):(in_y-1);
		next_x = in_x;
		next_z = in_z;
	}
	else if(zdis<=xdis && zdis<=xdis)
	{
		//select x change
		next_point = in_point + (direction * zdis);
		next_z = (direction.m_z>0) ? (in_z+1):(in_z-1);
		next_y = in_y;
		next_x = in_x;
	}
	return;
	
}
#endif
//check intersect
int intersect(CRay view_ray, int &sect_shape, CTuple3 &sect_point)
{
#ifndef ENABLE_3DDA
	int i;
	DTYPE min_distance=INF_DISTANCE, distance;
	int min_shape=-1, shape=-1;
	int result=0, min_result;
	int shape_count=g_shape_count;

	CTuple3 min_point, point;
	for(i=0;i<shape_count;i++)
	{
		intersect_count++;
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
#else
	//1.find the view point grid
	int cur_x,cur_y,cur_z,chk_x,chk_y,chk_z;
	//
	CTuple3 cur_point=view_ray.m_origin;
	find_grid(cur_point,cur_x,cur_y,cur_z);

	int i;
	list<int>::iterator it;
	DTYPE min_distance=INF_DISTANCE, distance;
	int min_shape, shape;
	int result, min_result;
	
	for(i=0;i<g_shape_count;i++)
		rec[i].m_sected=false;

	while(cur_x>=0 && cur_x<GRID_SIZE
		&& cur_y>=0 && cur_y<GRID_SIZE
		&& cur_z>=0 && cur_z<GRID_SIZE)
	{
		//2. search current grid
		min_shape=-1;
		shape=-1;
		result=0;
		CTuple3 min_point, point;
		for(it=g_box_list[cur_x][cur_y][cur_z].m_shapes.begin();it!=g_box_list[cur_x][cur_y][cur_z].m_shapes.end();it++)
		{
			i=(*it);
			
			if(rec[i].m_sected)
			{
				//has been tested
				result=rec[i].m_sect_result;
				distance=rec[i].m_distance;
				chk_x=rec[i].m_box_x;
				chk_y=rec[i].m_box_y;
				chk_z=rec[i].m_box_z;
				point=rec[i].m_spoint;
			}
			else
			{
				intersect_count++;
				result=(g_shapes[i]->intersect(view_ray, point, distance));
				//check if the sect point is in current grid!!!
				rec[i].m_sected=true;
				rec[i].m_sect_result=result;
				if(result!=0)
				{
					find_grid(point,chk_x,chk_y,chk_z);
					rec[i].m_box_x=chk_x;
					rec[i].m_box_y=chk_y;
					rec[i].m_box_z=chk_z;
					rec[i].m_spoint=point;
					rec[i].m_distance=distance;
				}
			}
			
			if(result!=0 && cur_x==chk_x && cur_y==chk_y && cur_z==chk_z)
			{
				if(distance < min_distance)
				{
					min_distance=distance;
					min_shape=i;
					min_result=result;
					min_point=point;
				}
			}
			
			/*
			if(result=(g_shapes[i]->intersect(view_ray, point, distance)))
			{
				//check if the sect point is in current grid!!!
				find_grid(point,chk_x,chk_y,chk_z);
				if(cur_x==chk_x && cur_y==chk_y && cur_z==chk_z)
				{
					if(distance < min_distance)
					{
						min_distance=distance;
						min_shape=i;
						min_result=result;
						min_point.SetValue(point.m_x,point.m_y,point.m_z);
					}
				}
			}
			*/
		}
		if(min_shape!=-1)
		{
			sect_shape=min_shape;
			sect_point=min_point;
			return min_result;
		}
		else
		{
			//go to next cell
			getNextBox(view_ray.m_direction, cur_point,cur_x,cur_y,cur_z,cur_point,cur_x,cur_y,cur_z);
		}
	}
	sect_shape=-1;
	sect_point=view_ray.GetOrigin();
	return 0;

#endif
}

/*
returns:
1 if intersected;
0 if not at all intersected;
-1 if intersected by a transparent primitive and saves the the hall_factor of this primitive.
*/
int shadow_intersect(CRay shadow_ray, int start_shape, int light, CTuple3 &hall_factor)
{
#ifndef ENABLE_3DDA
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
		shadow_intersect_count++;
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
#else
	CTuple3 refr_factor;
	bool find_trans=false;

	//1.find the view point grid
	int cur_x,cur_y,cur_z,chk_x,chk_y,chk_z;
	//
	CTuple3 cur_point=shadow_ray.m_origin;
	find_grid(cur_point,cur_x,cur_y,cur_z);

	int i;
	list<int>::iterator it;
	DTYPE min_distance=INF_DISTANCE, distance;
	int min_shape, shape;
	int result, min_result;

	for(i=0;i<g_shape_count;i++)
		rec[i].m_sected=false;

	while(cur_x>=0 && cur_x<GRID_SIZE
		&& cur_y>=0 && cur_y<GRID_SIZE
		&& cur_z>=0 && cur_z<GRID_SIZE)
	{
		//2. search current grid
		min_shape=-1;
		shape=-1;
		result=0;
		CTuple3 min_point, point;
		for(it=g_box_list[cur_x][cur_y][cur_z].m_shapes.begin();it!=g_box_list[cur_x][cur_y][cur_z].m_shapes.end();it++)
		{
			i=(*it);

			if(rec[i].m_sected)
			{
				//has been tested
				result=rec[i].m_sect_result;
				distance=rec[i].m_distance;
				chk_x=rec[i].m_box_x;
				chk_y=rec[i].m_box_y;
				chk_z=rec[i].m_box_z;
				point=rec[i].m_spoint;
			}
			else
			{
				shadow_intersect_count++;
				result=(g_shapes[i]->intersect(shadow_ray, point, distance));
				//check if the sect point is in current grid!!!
				rec[i].m_sected=true;
				rec[i].m_sect_result=result;
				if(result!=0)
				{
					find_grid(point,chk_x,chk_y,chk_z);
					rec[i].m_box_x=chk_x;
					rec[i].m_box_y=chk_y;
					rec[i].m_box_z=chk_z;
					rec[i].m_spoint=point;
					rec[i].m_distance=distance;
				}
			}

			if(result!=0 && cur_x==chk_x && cur_y==chk_y && cur_z==chk_z)
			{
				if(distance < min_distance)
				{
					min_distance=distance;
					min_shape=i;
					min_result=result;
					min_point=point;
				}
			}
		}
		if(min_shape!=-1)
		{
			refr_factor = g_shapes[i]->m_material.m_refract;
			
			if(min_shape==light)
			{
				return (find_trans)?(-1):0;
			}
			else if(min_shape!=start_shape || refr_factor.all_zero())
				return 1;
			else
			{
				//hit self and it's transparent
				find_trans=true;
				hall_factor=refr_factor;
			}
		}
		else
		{
			//go to next cell
			getNextBox(shadow_ray.m_direction, cur_point,cur_x,cur_y,cur_z,cur_point,cur_x,cur_y,cur_z);
		}
	}
	return 0;
#endif
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

