#include "ShapeTriangle.h"

extern DTYPE myMin(DTYPE a,DTYPE b,DTYPE c);
extern DTYPE myMax(DTYPE a,DTYPE b,DTYPE c);
extern DTYPE detMat3(CTuple3 a, CTuple3 b, CTuple3 c);

CShapeTriangle::CShapeTriangle(void)
{
}

CShapeTriangle::CShapeTriangle( CMaterial mat, DTYPE ref_factor, bool is_light, DTYPE i_refract, DTYPE e_refract, CTuple3 v1,CTuple3 v2, CTuple3 v3 )
:CShapeBase(v1,mat,ref_factor,is_light,i_refract,e_refract)
{
	m_v1=v1;
	m_v2=v2;
	m_v3=v3;
	m_u=v2-v1;
	m_v=v3-v1;
	m_normal=m_u ^ m_v;
	m_normal.normalize();
}
CShapeTriangle::~CShapeTriangle(void)
{
}

int CShapeTriangle::intersect( CRay& view_ray, CTuple3 &sect_point, DTYPE &sect_distance )
{
	CTuple3 b = view_ray.m_origin - m_v1;
	CTuple3 minusD=(view_ray.m_direction * (-1.0));
	//sovle it!
	//(-d,u,v)(T,U,V) = b
	DTYPE u,v,t,det;
	det = detMat3(minusD,m_u,m_v);
	if(det!=0.0)//det!=0
	{
		t = detMat3(b,m_u,m_v)/det;
		u = detMat3(minusD,b,m_v)/det;
		v = detMat3(minusD,m_u,b)/det;
		//solve u,v,t
		if ( t>0 && u>0 && u<1 && v>0 && v<1 && u+v<1)
		{
			sect_point = m_v1 + (m_u * u) + (m_v * v);
			sect_distance = t;
			if(b * m_normal > 0)
				return 1;
			else 
				return -1;
		}
		else
			return 0;
	}
	else
		return 0;
}

void CShapeTriangle::drawByGlut()
{
	glBegin(GL_TRIANGLES);
		glVertex3f( m_v1.m_x, m_v1.m_y, m_v1.m_z);
		glVertex3f( m_v2.m_x, m_v2.m_y, m_v2.m_z);
		glVertex3f( m_v3.m_x, m_v3.m_y, m_v3.m_z);
	glEnd();
}

void CShapeTriangle::calcPlane( CTuple3 cpoint, CTuple3& normal )
{
	normal = m_normal;
}

DTYPE CShapeTriangle::calcDistance( CTuple3 point )
{
	return fabs( (point-m_v1) * m_normal);
}

bool CShapeTriangle::getTextureMap( CTuple3 p, DTYPE &u, DTYPE &v )
{
	//we suppose that p is in the triangle
	CTuple3 a = p - m_v1;
	DTYPE x,y,x1,y1,x2,y2,q;
	x1 = m_u.m_x;
	y1 = m_u.m_y;
	x2 = m_v.m_x;
	y2 = m_v.m_y;
	q = x2 * y1 - x1 * y2;
	if(q!=0.0)
	//solve (x,y)=u(x1,y1)+v(x2,y2);
	{
		x = a.m_x;
		y = a.m_y;
		u = (x2 * y - x * y2)/q;
		v = (x * y1 - x1 * y)/q;
	}
	else
	{
		x1 = m_u.m_x;
		y1 = m_u.m_z;
		x2 = m_v.m_x;
		y2 = m_v.m_z;
		q = x2 * y1 - x1 * y2;
		if(q!=0.0)
			//solve (x,y)=u(x1,y1)+v(x2,y2);
		{
			x = a.m_x;
			y = a.m_z;
			u = (x2 * y - x * y2)/q;
			v = (x * y1 - x1 * y)/q;
		}
		else
			return false;
	}

	return true;
}

void CShapeTriangle::getBoundaryBox( CTuple3 &left_down, CTuple3 &right_up )
{
	left_down.SetValue(
		myMin(m_v1.m_x,m_v2.m_x,m_v3.m_x),
		myMin(m_v1.m_y,m_v2.m_y,m_v3.m_y),
		myMin(m_v1.m_z,m_v2.m_z,m_v3.m_z));
	right_up.SetValue(
		myMax(m_v1.m_x,m_v2.m_x,m_v3.m_x),
		myMax(m_v1.m_y,m_v2.m_y,m_v3.m_y),
		myMax(m_v1.m_z,m_v2.m_z,m_v3.m_z));
}

bool CShapeTriangle::intersectBox( CBox box )
{
	return true;
}