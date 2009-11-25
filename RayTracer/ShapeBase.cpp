#include "ShapeBase.h"

CShapeBase::CShapeBase(void)
{
}

CShapeBase::~CShapeBase(void)
{
}

CShapeBase::CShapeBase(CMaterial mat)
{
	this->m_material=mat;
	this->m_light=false;
}
