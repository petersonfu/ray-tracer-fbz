#ifndef __SHAPE_BASE_H__
#define __SHAPE_BASE_H__

#include "global.h"
#include "ray.h"
#include "tuples.h"
#include "material.h"
#include "Texture.h"
#include "Box.h"

struct CShapeBase
{
	CTuple3 m_origin;
	CMaterial m_material;
	bool m_light;
	DTYPE m_refl_factor;
	DTYPE m_i_refract;
	DTYPE m_e_refract;
	int m_texture;

	CShapeBase(void);
	~CShapeBase(void);
	CShapeBase(CTuple3 origin, CMaterial mat, DTYPE ref_factor, bool is_light, DTYPE i_refract, DTYPE e_refract);

	void init(CTuple3 origin, CMaterial mat, DTYPE ref_factor, bool is_light, DTYPE i_refract, DTYPE e_refract);
	virtual int intersect( CRay& view_ray, CTuple3 &sect_point, DTYPE &sect_distance )=0;
	virtual void drawByGlut()=0;
	virtual void calcPlane( CTuple3 cpoint, CTuple3& normal)=0;
	virtual DTYPE calcDistance ( CTuple3 point )=0;
	virtual bool getTextureMap(CTuple3 p, DTYPE &u, DTYPE &v)=0;
	virtual void getBoundaryBox(CTuple3 &left_down, CTuple3 &right_up)=0;
	virtual bool intersectBox(CBox box)=0;
	void setTexture(int texture);
};

#endif

