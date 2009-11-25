#include "ray.h"
CRay::CRay(void)
{
}

CRay::~CRay(void)
{
}
CRay::CRay(CTuple3 origin, CTuple3 dir)
{
	m_direction=dir;
	m_origin=origin;
}