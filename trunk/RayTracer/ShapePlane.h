#pragma once
#include "shapebase.h"
#include "tuples.h"

struct CShapePlane :
	public CShapeBase
{
	CTuple3 m_normal;

	CShapePlane(void);
	CShapePlane(CTuple3 origin, CMaterial mat, float ref_factor, bool is_light, CTuple3 normal);
	~CShapePlane(void);
	virtual bool intersect( CRay& view_ray, CTuple3 &sect_point, float &sect_distace );
	virtual void drawByGlut();
	virtual void calcPlane( CTuple3 lpoint, CTuple3 vpoint, CTuple3 cpoint, CTuple3& light, CTuple3& normal, CTuple3& reflect, CTuple3& view);
};