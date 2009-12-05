#ifndef __SHAPE_BASE_H__
#define __SHAPE_BASE_H__

#include "global.h"
#include "ray.h"
#include "tuples.h"
#include "material.h"
#include "Texture.h"

struct CShapeBase
{
	CTuple3 m_origin;
	CMaterial m_material;
	bool m_light;
	float m_refl_factor;
	float m_i_refract;
	float m_e_refract;
	int m_texture;

	CShapeBase(void);
	~CShapeBase(void);
	CShapeBase(CTuple3 origin, CMaterial mat, float ref_factor, bool is_light, float i_refract, float e_refract);

	void init(CTuple3 origin, CMaterial mat, float ref_factor, bool is_light, float i_refract, float e_refract);
	virtual int intersect( CRay& view_ray, CTuple3 &sect_point, float &sect_distance )=0;
	virtual void drawByGlut()=0;
	virtual void calcPlane( CTuple3 cpoint, CTuple3& normal)=0;
	virtual float calcDistance ( CTuple3 point )=0;
	virtual bool getTextureMap(CTuple3 p, float &u, float &v)=0;
	void setTexture(int texture);
};

#endif

