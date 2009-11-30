#ifndef __RAY_H__
#define __RAY_H__

#include "tuples.h"

struct CRay
{

	CTuple3 m_origin;
	CTuple3 m_direction;

	CRay(void);
	~CRay(void);
	CRay::CRay(CTuple3 origin, CTuple3 dir);

	CTuple3& GetOrigin() {return m_origin;}
	CTuple3& GetDirection() {return m_direction;}
	void SetOrigin(CTuple3 origin)
	{
		m_origin=origin;
	}

	void SetDirection(CTuple3 direction)
	{
		m_direction=direction;
	}
};
#endif
