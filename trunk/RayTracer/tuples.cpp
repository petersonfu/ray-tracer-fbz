#include "tuples.h"

CTuple3::CTuple3(void)
{
}

CTuple3::CTuple3(float x, float y, float z)
{
	m_x=x;
	m_y=y;
	m_z=z;
}

CTuple3::~CTuple3(void)
{
}

CTuple3 CTuple3::operator - (const CTuple3 &minus)
{
	return CTuple3(m_x - minus.m_x , m_y - minus.m_y , m_z - minus.m_z );
}

CTuple3 CTuple3::operator + (const CTuple3 &add)
{
	return CTuple3(m_x+add.m_x,m_y+add.m_y,m_z+add.m_z);
}

float CTuple3::operator * (const CTuple3 &product)
{
	return m_x*product.m_x+m_y*product.m_y+m_z*product.m_z;
}

CTuple3 CTuple3::operator * (const float &re)
{
	return CTuple3(m_x*re,m_y*re,m_z*re);
}

CTuple3 CTuple3::operator & (const CTuple3 &product)
{
	return CTuple3(m_x*product.m_x, m_y*product.m_y, m_z*product.m_z);
}

float CTuple3::metric()
{
	
	return sqrt(m_x*m_x+m_y*m_y+m_z*m_z);
}

void CTuple3::SetValue(float x,float y,float z)
{
	m_x=x;
	m_y=y;
	m_z=z;
}


void CTuple3::normalize()
{
	float met=(1/metric());
	m_x=m_x*met;
	m_y=m_y*met;
	m_z=m_z*met;
}

CTuple3& CTuple3::operator = (const CTuple3& p)
{
	this->m_x=p.m_x;
	this->m_y=p.m_y;
	this->m_z=p.m_z;
	return *this;
}

bool CTuple3::all_zero()
{
	return ((m_x==0.0) && (m_y==0.0) && (m_z==0.0));
}

CTuple3 CTuple3::find_face()
{
	CTuple3 result;
	if(m_x==0.0)
		result.SetValue(0,-m_z,m_y);
	else if (m_y==0.0)
		result.SetValue(-m_z,0,m_x);
	else
		result.SetValue(-m_y,m_x,0);
	result.normalize();
	return result;
}
