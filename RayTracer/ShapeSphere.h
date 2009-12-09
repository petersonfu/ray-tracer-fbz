#ifndef __SHAPESPHERE_H__
#define __SHAPESPHERE_H__
#include "shapebase.h"
#include "tuples.h"
#include "ray.h"

struct CShapeSphere :
	public CShapeBase
{
	DTYPE m_radius;

	CShapeSphere(void);
	CShapeSphere::CShapeSphere(CTuple3 origin, CMaterial mat, DTYPE ref_factor, bool is_light, DTYPE i_refract, DTYPE e_refract, DTYPE radius);
	~CShapeSphere(void);
	virtual int intersect( CRay& view_ray, CTuple3 &sect_point, DTYPE &sect_distace );
	virtual void drawByGlut();
	virtual void calcPlane( CTuple3 cpoint, CTuple3& normal);
	virtual DTYPE calcDistance ( CTuple3 point );
	virtual bool getTextureMap(CTuple3 p, DTYPE &u, DTYPE &v);
	virtual void getBoundaryBox(CTuple3 &left_down, CTuple3 &right_up);
	virtual bool intersectBox(CBox box);
};
#endif
