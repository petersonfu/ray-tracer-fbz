#ifndef __TUPLES_H__
#define __TUPLES_H__
#include "math.h"

struct CTuple3
{
	float m_x,m_y,m_z;

	CTuple3(void);
	CTuple3(float x, float y, float z);
	~CTuple3(void);
	CTuple3 operator - (const CTuple3 &minus);
	CTuple3 operator + (const CTuple3 &add);
	float operator * (const CTuple3 &product);
	CTuple3 operator * (const float &re);
	CTuple3& operator = (const CTuple3& p);
	CTuple3 operator & (const CTuple3& p);
	void SetValue(float x,float y,float z);
	float metric();
	void normalize();
	bool all_zero();
	CTuple3 find_face();
	void reset_threshold(float threshold);
};
#endif
