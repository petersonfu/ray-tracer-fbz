#include "ShapePlane.h"

CShapePlane::CShapePlane(void)
{
}

CShapePlane::~CShapePlane(void)
{
}

CShapePlane::CShapePlane(CTuple3 origin, CMaterial mat, float ref_factor, bool is_light, CTuple3 normal)
{
	m_normal = normal;
	m_origin = origin;
	m_material = mat;
	m_refl_factor = ref_factor;
	m_light = is_light;
	m_normal.normalize();
}

//note that ray should have been normalized
bool CShapePlane::intersect(CRay &view_ray,  CTuple3 &sect_point, float &sect_distance)
{
	if(view_ray.m_direction * m_normal == 0)
		return false;
	else
	{
		CTuple3 d_vec=m_origin-view_ray.GetOrigin();
		float d=d_vec.metric();
		sect_distance = ( d_vec * (m_normal * (-1)) ) / ( ( m_normal * (-1) ) * view_ray.GetDirection() );
		if(sect_distance<=0)
			return false;
		sect_point = view_ray.GetOrigin() + (view_ray.GetDirection() * sect_distance);
		return true;
	}
}

void CShapePlane::drawByGlut()
{
}

void CShapePlane::calcPlane( CTuple3 lpoint, CTuple3 vpoint, CTuple3 cpoint, CTuple3& light, CTuple3& normal, CTuple3& reflect, CTuple3& view)
{
	normal  = m_normal;// normal has been normalized
	light   = (lpoint - cpoint);
	light.normalize();
	view    = (vpoint - cpoint);
	view.normalize();
	reflect = (normal * 2.0 - light);
	reflect.normalize();
}