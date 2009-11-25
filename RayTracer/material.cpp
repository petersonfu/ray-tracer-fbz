#include "material.h"

CMaterial::CMaterial(void)
{
}

CMaterial::~CMaterial(void)
{
}

CMaterial::CMaterial(CTuple3 amb, CTuple3 diff, CTuple3 refl)
{
	this->m_ambient=amb;
	this->m_diffuse=diff;
	this->m_reflect=refl;
}

CMaterial& CMaterial::operator =(CMaterial& p)
{
	this->m_ambient=p.m_ambient;
	this->m_diffuse=p.m_diffuse;
	this->m_reflect=p.m_reflect;
	return *this;
}