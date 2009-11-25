#pragma once

#include "global.h"
#include "ray.h"
#include "tuples.h"

struct CMaterial
{
	CTuple3 m_diffuse;
	CTuple3 m_ambient;
	CTuple3 m_reflect;
	
	CMaterial(void);
	~CMaterial(void);
	CMaterial(CTuple3 amb, CTuple3 diff,  CTuple3 refl);
	CMaterial& operator =(CMaterial& p);
};
