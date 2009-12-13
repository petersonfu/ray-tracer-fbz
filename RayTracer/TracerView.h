#ifndef __TRACERVIEW_H__
#define __TRACERVIEW_H__

#include "tuples.h"
#include "ray.h"
#define TRACEVIEW_PLANE 0x0001
#define TRACEVIEW_TRANSMISSION 0x0002

class CTracerView
{
public:
	CTracerView(void);
	CTracerView(CTuple3 eye, CTuple3 o, CTuple3 xlimit, CTuple3 ylimit, int type);
	~CTracerView(void);
private:
	CTuple3		m_origin;
	CTuple3		m_x;
	CTuple3		m_y;
	int			m_type;
	CTuple3		m_normal;
	CTuple3		m_eye;
public: 
	void calcRay(float x, float y, CRay& view_ray);
	void setView(CTuple3 eye, CTuple3 o, CTuple3 xlimit, CTuple3 ylimit, int type);
};

#endif