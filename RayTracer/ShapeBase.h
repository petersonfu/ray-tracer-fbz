#pragma once

#include "global.h"
#include "ray.h"
#include "tuples.h"
#include "material.h"

struct CShapeBase
{
	CTuple3 m_origin;
	CMaterial m_material;
	bool m_light;
	float m_refl_factor;

	CShapeBase(void);
	~CShapeBase(void);
	CShapeBase(CMaterial mat);
	virtual bool intersect( CRay& view_ray, CTuple3 &sect_point, float &sect_distance )=0;
	virtual void drawByGlut()=0;
	virtual void calcPlane( CTuple3 lpoint, CTuple3 vpoint, CTuple3 cpoint, CTuple3& light, CTuple3& normal, CTuple3& reflect, CTuple3& view)=0;
};


