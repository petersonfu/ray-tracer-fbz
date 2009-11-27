#pragma once

#include "global.h"
#include "ray.h"
#include "tuples.h"

struct CMaterial
{
	CTuple3 m_diffuse;
	CTuple3 m_ambient;
	CTuple3 m_reflect;
	CTuple3 m_refract;
	
	CMaterial(void);
	~CMaterial(void);
	CMaterial(CTuple3 amb, CTuple3 diff,  CTuple3 refl, CTuple3 refr);
	CMaterial& operator =(CMaterial& p);
};
