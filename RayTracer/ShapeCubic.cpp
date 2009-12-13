#include "ShapeCubic.h"

CShapeCubic::CShapeCubic(void)
{
}

CShapeCubic::~CShapeCubic(void)
{
}

int CShapeCubic::intersect( CRay& view_ray, CTuple3 &sect_point, DTYPE &sect_distance )
{
	return 0;
}

void CShapeCubic::drawByGlut()
{

}

void CShapeCubic::calcPlane( CTuple3 cpoint, CTuple3& normal )
{

}

DTYPE CShapeCubic::calcDistance( CTuple3 point )
{
	return 0.0;
}

bool CShapeCubic::getTextureMap( CTuple3 p, DTYPE &u, DTYPE &v )
{
	return true;
}

void CShapeCubic::getBoundaryBox( CTuple3 &left_down, CTuple3 &right_up )
{

}

bool CShapeCubic::intersectBox( CBox box )
{
	return true;
}