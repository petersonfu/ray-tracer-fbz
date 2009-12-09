#ifndef __BOX_H__
#define __BOX_H__

#include "tuples.h"
struct CBox
{
	CTuple3 m_left_down;
	CTuple3 m_right_up;
	list<int> m_shapes;
	int m_xi,m_yi,m_zi;
	void init(CTuple3 left_down, CTuple3 right_up, int x, int y, int z);
	CBox(void);
	~CBox(void);
};

struct CTraceRecord
{
	bool m_sected;
	int m_sect_result;
	CTuple3 m_spoint;
	float m_distance;
	int m_box_x,m_box_y,m_box_z;
	CTraceRecord();
	~CTraceRecord();
};
#endif
