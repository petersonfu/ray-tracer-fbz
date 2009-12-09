#include "Box.h"

CBox::CBox(void)
{
}

CBox::~CBox(void)
{
}

void CBox::init( CTuple3 left_down, CTuple3 right_up, int x, int y, int z )
{
	m_left_down=left_down;
	m_right_up=right_up;
	m_xi=x;
	m_yi=y;
	m_zi=z;
}

CTraceRecord::~CTraceRecord()
{

}

CTraceRecord::CTraceRecord()
{
	m_sected=false;
}