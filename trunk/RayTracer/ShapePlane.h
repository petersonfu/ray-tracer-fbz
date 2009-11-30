#ifndef __SHAPEPLANE_H__
#define __SHAPEPLANE_H__

#include "shapebase.h"
#include "tuples.h"

struct CShapePlane :
	public CShapeBase
{
	CTuple3 m_normal;

	CShapePlane(void);
	CShapePlane(CTuple3 origin, CMaterial mat, float ref_factor, bool is_light, float i_refract, float e_refract, CTuple3 normal);
	~CShapePlane(void);
	virtual int intersect( CRay& view_ray, CTuple3 &sect_point, float &sect_distace );
	virtual void drawByGlut();
	virtual void calcPlane( CTuple3 cpoint, CTuple3& normal);
	virtual float calcDistance ( CTuple3 point );
};
#endif
