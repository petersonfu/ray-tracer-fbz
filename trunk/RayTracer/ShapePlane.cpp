#include "ShapePlane.h"

CShapePlane::CShapePlane(void)
{
}

CShapePlane::~CShapePlane(void)
{
}

CShapePlane::CShapePlane(CTuple3 origin, CMaterial mat, float ref_factor, bool is_light, float i_refract, float e_refract, CTuple3 normal)
:CShapeBase(origin,mat,ref_factor,is_light,i_refract,e_refract)
{
	m_normal = normal;
	m_base1.SetValue(normal.m_z,0,-normal.m_x);
	m_base2=m_base1^normal;
	m_normal.normalize();
	m_base1.normalize();
	m_base2.normalize();
}

//note that ray should have been normalized
int CShapePlane::intersect(CRay &view_ray,  CTuple3 &sect_point, float &sect_distance)
{
	float product = view_ray.GetDirection() * m_normal ;
	if(product == 0)
		return 0;
	else
	{
		CTuple3 d_vec=m_origin-view_ray.GetOrigin();
		float d=d_vec.metric();
		float product1 = d_vec * m_normal ;
		if( product1 == 0)
		{
			return 0;
		}
		else if (product1 < 0)
		{
			//above the plane
			sect_distance = product1 / product;
			if(sect_distance<=0)
				return 0;
			sect_point = view_ray.GetOrigin() + (view_ray.GetDirection() * sect_distance);
			return 1;
		}
		else
		{
			//below the plane
			sect_distance = product1 / product;
			if(sect_distance<=0)
				return 0;
			sect_point = view_ray.GetOrigin() + (view_ray.GetDirection() * sect_distance);
			return -1;
		}

	}
}

void CShapePlane::drawByGlut()
{

}

void CShapePlane::calcPlane(  CTuple3 cpoint, CTuple3& normal )
{
	normal  = m_normal;// normal has been normalized
}
float CShapePlane::calcDistance ( CTuple3 point )
{
	CTuple3 d_vec=m_origin-point;
	return fabs(d_vec * m_normal);
}

bool CShapePlane::getTextureMap( CTuple3 p, float &u, float &v )
{
	if(m_texture<0)
		return false;

	CTuple3 vec = p - m_origin;
	float x = vec * m_base1;
	float y = vec * m_base2;
	float ratio = 1.0;
	//uniform to [0.0, 1.0)
	u = x/ratio - floor(x/ratio);
	v = y/ratio - floor(y/ratio);
	//deal with the float
	if(u>=1.0)
		u=0.999;
	if(v>=1.0)
		v=0.999;
	return true;
}