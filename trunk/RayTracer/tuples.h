#ifndef __TUPLES_H__
#define __TUPLES_H__
#include "global.h"
#include "math.h"

struct CTuple3
{
	DTYPE m_x,m_y,m_z;

	CTuple3(void);
	CTuple3(DTYPE x, DTYPE y, DTYPE z);
	~CTuple3(void);
	CTuple3 operator - (const CTuple3 &minus);
	CTuple3 operator + (const CTuple3 &add);
	DTYPE operator * (const CTuple3 &product);
	CTuple3 operator * (const DTYPE &re);
	CTuple3& operator = (const CTuple3& p);
	CTuple3 operator & (const CTuple3& p);
	CTuple3 operator ^ (const CTuple3& p);
	void SetValue(DTYPE x,DTYPE y,DTYPE z);
	DTYPE metric();
	void normalize();
	bool all_zero();
	CTuple3 find_face();
	void reset_threshold(DTYPE threshold);
};
#endif
