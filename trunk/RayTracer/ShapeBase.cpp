#include "ShapeBase.h"

CShapeBase::CShapeBase(void)
{
	m_texture=-1;
}

CShapeBase::~CShapeBase(void)
{
}

CShapeBase::CShapeBase(CTuple3 origin, CMaterial mat, DTYPE ref_factor, bool is_light, DTYPE i_refract, DTYPE e_refract)
{
	init(origin,mat,ref_factor,is_light,i_refract,e_refract);
}

void CShapeBase::init(CTuple3 origin, CMaterial mat, DTYPE ref_factor, bool is_light, DTYPE i_refract, DTYPE e_refract)
{
	m_texture=-1;
	m_origin = origin;
	m_material = mat;
	m_refl_factor = ref_factor;
	m_light = is_light;
	m_i_refract = i_refract;
	m_e_refract = e_refract;
}

void CShapeBase::setTexture( int texture )
{
	m_texture=texture;
}