#include "TracerView.h"

CTracerView::CTracerView(void)
{
}

CTracerView::CTracerView(CTuple3 eye, CTuple3 o, CTuple3 xlimit, CTuple3 ylimit, int type )
{
	setView(eye, o,xlimit,ylimit,type);
}
CTracerView::~CTracerView(void)
{
}

void CTracerView::calcRay( float x, float y, CRay& view_ray )
{
	CTuple3 screen_p = 
		m_origin +
		(m_x * x) +
		(m_y * y);
	switch(m_type)
	{
	case TRACEVIEW_PLANE:
	default:
		view_ray.m_origin = screen_p;
		view_ray.m_direction = m_normal;
		break;
	case TRACEVIEW_TRANSMISSION:
		view_ray.m_origin = screen_p;
		view_ray.m_direction = screen_p - m_eye;
		view_ray.m_direction.normalize();
		break;
	}
}

void CTracerView::setView(CTuple3 eye, CTuple3 o, CTuple3 xlimit, CTuple3 ylimit, int type )
{
	m_eye=eye;
	m_origin=o;
	m_x= xlimit - o;
	m_y= ylimit - o;
	m_normal = (m_y ^ m_x);
	m_normal.normalize();
	m_type = type;
}