#ifndef __SHAPESPHERE_H__
#define __SHAPESPHERE_H__
#include "shapebase.h"
#include "tuples.h"
#include "ray.h"

struct CShapeSphere :
	public CShapeBase
{
	float m_radius;

	CShapeSphere(void);
	CShapeSphere::CShapeSphere(CTuple3 origin, CMaterial mat, float ref_factor, bool is_light, float i_refract, float e_refract, float radius);
	~CShapeSphere(void);
	virtual int intersect( CRay& view_ray, CTuple3 &sect_point, float &sect_distace );
	virtual void drawByGlut();
	virtual void calcPlane( CTuple3 cpoint, CTuple3& normal);
	virtual float calcDistance ( CTuple3 point );
	virtual bool getTextureMap(CTuple3 p, float &u, float &v);
};
#endif
