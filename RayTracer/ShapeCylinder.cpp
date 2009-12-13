#include "ShapeCylinder.h"

CShapeCylinder::CShapeCylinder(void)
{
}

CShapeCylinder::~CShapeCylinder(void)
{
}

int CShapeCylinder::intersect( CRay& view_ray, CTuple3 &sect_point, DTYPE &sect_distance )
{
	return 0;
}

void CShapeCylinder::drawByGlut()
{

}

void CShapeCylinder::calcPlane( CTuple3 cpoint, CTuple3& normal )
{

}

DTYPE CShapeCylinder::calcDistance( CTuple3 point )
{
	return 0.0;
}

bool CShapeCylinder::getTextureMap( CTuple3 p, DTYPE &u, DTYPE &v )
{
	return false;
}

bool CShapeCylinder::intersectBox( CBox box )
{
	return true;
}

void CShapeCylinder::getBoundaryBox( CTuple3 &left_down, CTuple3 &right_up )
{

}