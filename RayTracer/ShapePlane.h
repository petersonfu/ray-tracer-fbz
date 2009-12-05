#ifndef __SHAPEPLANE_H__
#define __SHAPEPLANE_H__

#include "shapebase.h"
#include "tuples.h"

struct CShapePlane :
	public CShapeBase
{
	CTuple3 m_normal;
	CTuple3 m_base1,m_base2;

	CShapePlane(void);
	CShapePlane(CTuple3 origin, CMaterial mat, DTYPE ref_factor, bool is_light, DTYPE i_refract, DTYPE e_refract, CTuple3 normal);
	~CShapePlane(void);
	virtual int intersect( CRay& view_ray, CTuple3 &sect_point, DTYPE &sect_distace );
	virtual void drawByGlut();
	virtual void calcPlane( CTuple3 cpoint, CTuple3& normal);
	virtual DTYPE calcDistance ( CTuple3 point );
	virtual bool getTextureMap(CTuple3 p, DTYPE &u, DTYPE &v);
};
#endif
