#pragma once
#include "shapebase.h"
#include "tuples.h"
#include "ray.h"

struct CShapeSphere :
	public CShapeBase
{
	CTuple3 m_center;
	float m_radius;

	CShapeSphere(void);
	CShapeSphere(float x, float y, float z, float r);
	CShapeSphere::CShapeSphere(float x, float y, float z, float r, CMaterial mat, float ref_factor, bool is_light);
	void init(float x, float y, float z, float r, CMaterial mat, float ref_factor,bool is_light);
	~CShapeSphere(void);
	virtual bool intersect( CRay& view_ray, CTuple3 &sect_point, float &sect_distace );
	virtual void drawByGlut();
	virtual void calcPlane( CTuple3 lpoint, CTuple3 vpoint, CTuple3 cpoint, CTuple3& light, CTuple3& normal, CTuple3& reflect, CTuple3& view);
};
