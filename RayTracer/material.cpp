#include "material.h"

CMaterial::CMaterial(void)
{
}

CMaterial::~CMaterial(void)
{
}

CMaterial::CMaterial(CTuple3 amb, CTuple3 diff, CTuple3 refl, CTuple3 refr)
{
	this->m_ambient=amb;
	this->m_diffuse=diff;
	this->m_reflect=refl;
	this->m_refract=refr;
}

CMaterial& CMaterial::operator =(CMaterial& p)
{
	this->m_ambient=p.m_ambient;
	this->m_diffuse=p.m_diffuse;
	this->m_reflect=p.m_reflect;
	this->m_refract=p.m_refract;
	return *this;
}
