#include "ShapeLight.h"

CShapeLight::CShapeLight(void)
{
	this->m_origin=CTuple3(0.0,0.0,0.0);
	this->m_light=true;
	this->m_refl_factor=1.0;
	this->m_material=CMaterial(CTuple3(0.0,0.0,0.0),CTuple3(0.0,0.0,0.0),CTuple3(0.0,0.0,0.0));
}

CShapeLight::CShapeLight(CTuple3 origin, CMaterial material, float refl_factor)
{
	this->m_origin=origin;
	this->m_light=true;
	this->m_refl_factor=refl_factor;
	this->m_material=material;
}

CShapeLight::~CShapeLight(void)
{
}

bool CShapeLight::intersect( CRay& view_ray, CTuple3 &sect_point, float &sect_distace )
{
	return false;
}

void CShapeLight::drawByGlut()
{

}

void CShapeLight::calcPlane( CTuple3 lpoint, CTuple3 vpoint, CTuple3 cpoint, CTuple3& light, CTuple3& normal, CTuple3& reflect, CTuple3& view)
{
}
