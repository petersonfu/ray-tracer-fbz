#ifndef __SHAPE_BASE_H__
#define __SHAPE_BASE_H__

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
	float m_i_refract;
	float m_e_refract;
	

	CShapeBase(void);
	~CShapeBase(void);
	virtual int intersect( CRay& view_ray, CTuple3 &sect_point, float &sect_distance )=0;
	virtual void drawByGlut()=0;
	virtual void calcPlane( CTuple3 cpoint, CTuple3& normal)=0;
	virtual float calcDistance ( CTuple3 point )=0;
};

#endif

