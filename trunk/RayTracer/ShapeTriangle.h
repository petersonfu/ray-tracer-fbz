#ifndef __SHAPETRIANGLE_H__
#define __SHAPETRIANGLE_H__

#include "shapebase.h"
#include "tuples.h"
struct CShapeTriangle :
	public CShapeBase
{
private:
	CTuple3 m_normal, m_u,m_v;

public:
	CTuple3 m_v1,m_v2,m_v3;

	CShapeTriangle(void);
	CShapeTriangle(CMaterial mat, DTYPE ref_factor, bool is_light, DTYPE i_refract, DTYPE e_refract, CTuple3 v1,CTuple3 v2, CTuple3 v3);
	~CShapeTriangle(void);
	virtual int intersect( CRay& view_ray, CTuple3 &sect_point, DTYPE &sect_distance );
	virtual void drawByGlut();
	virtual void calcPlane( CTuple3 cpoint, CTuple3& normal);
	virtual DTYPE calcDistance ( CTuple3 point );
	virtual bool getTextureMap(CTuple3 p, DTYPE &u, DTYPE &v);
	virtual void getBoundaryBox(CTuple3 &left_down, CTuple3 &right_up);
	virtual bool intersectBox(CBox box);
};
#endif // _DEBUG