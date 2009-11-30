#include "ShapePlane.h"

CShapePlane::CShapePlane(void)
{
}

CShapePlane::~CShapePlane(void)
{
}

CShapePlane::CShapePlane(CTuple3 origin, CMaterial mat, float ref_factor, bool is_light, float i_refract, float e_refract, CTuple3 normal)
{
	m_normal = normal;
	m_origin = origin;
	m_material = mat;
	m_refl_factor = ref_factor;
	m_light = is_light;
	m_normal.normalize();
	m_i_refract = i_refract;
	m_e_refract = e_refract;
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
