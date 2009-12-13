
#include "global.h"
#include "tuples.h"
DTYPE myMin(DTYPE a,DTYPE b,DTYPE c)
{
	DTYPE m=a;
	if(b<m) m=b;
	if(c<m) m=c;
	return m;
}

DTYPE myMax(DTYPE a,DTYPE b,DTYPE c)
{
	DTYPE m=a;
	if(b>m) m=b;
	if(c>m) m=c;
	return m;
}

/*
The matrix is 
[a,b,c]
where a,b,c are all 3*1 vector.
*/
DTYPE detMat3(CTuple3 a, CTuple3 b, CTuple3 c)
{
	return 
		(
		(a.m_x * b.m_y * c.m_z) +
		(b.m_x * c.m_y * a.m_z) +
		(c.m_x * a.m_y * b.m_z) -
		(a.m_x * c.m_y * b.m_z) -
		(b.m_x * a.m_y * c.m_z) -
		(c.m_x * b.m_y * a.m_z) 
		);
}