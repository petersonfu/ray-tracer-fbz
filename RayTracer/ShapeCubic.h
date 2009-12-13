#ifndef __SHAPECUBIC_H__
#define __SHAPECUBIC_H__
#include "shapebase.h"

struct CShapeCubic :
	public CShapeBase
{
	CShapeCubic(void);
	~CShapeCubic(void);
	virtual int intersect( CRay& view_ray, CTuple3 &sect_point, DTYPE &sect_distance );
	virtual void drawByGlut();
	virtual void calcPlane( CTuple3 cpoint, CTuple3& normal);
	virtual DTYPE calcDistance ( CTuple3 point );
	virtual bool getTextureMap(CTuple3 p, DTYPE &u, DTYPE &v);
	virtual void getBoundaryBox(CTuple3 &left_down, CTuple3 &right_up);
	virtual bool intersectBox(CBox box);
};
#endif // _DEBUG
