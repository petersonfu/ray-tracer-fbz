#pragma once
#include "shapebase.h"
#include "material.h"
#include "tuples.h"

struct CShapeLight :
	public CShapeBase
{
	CTuple3 m_origin;

	CShapeLight(void);
	CShapeLight(CTuple3 origin, CMaterial material, float refl_fact);
	~CShapeLight(void);
	virtual bool intersect( CRay& view_ray, CTuple3 &sect_point, float &sect_distace );
	virtual void drawByGlut();
	virtual void calcPlane( CTuple3 lpoint, CTuple3 vpoint, CTuple3 cpoint, CTuple3& light, CTuple3& normal, CTuple3& reflect, CTuple3& view);
};
