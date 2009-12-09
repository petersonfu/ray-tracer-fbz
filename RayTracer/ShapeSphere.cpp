#include "ShapeSphere.h"

extern DTYPE sqrt(DTYPE x);
extern long intersect_count;
CShapeSphere::CShapeSphere(void)
{

}

CShapeSphere::CShapeSphere(CTuple3 origin, CMaterial mat, DTYPE ref_factor, bool is_light, DTYPE i_refract, DTYPE e_refract, DTYPE radius)
:CShapeBase(origin,mat,ref_factor,is_light,i_refract,e_refract)
{
	m_radius=radius;
}

CShapeSphere::~CShapeSphere(void)
{
}

//note that ray should have been normalized
int CShapeSphere::intersect(CRay &view_ray,  CTuple3 &sect_point, DTYPE &sect_distance)
{
	intersect_count++;
	CTuple3 d_vec=this->m_origin-view_ray.GetOrigin();
	DTYPE d=d_vec.metric();
	DTYPE product,  d2;
	product=d_vec * view_ray.GetDirection();
	DTYPE sum=m_radius*m_radius-d*d+product*product;
	if(m_radius<=d)
	{
		//sita=asin( this->m_radius/d );
		//view_ray.GetDirection().normalize();
		if(product<=0)
			return 0;
		//sita1=acos(product/d);
		if( sum > 0 )
		{
			//d1= d*sin(sita1);
			d2= product - sqrt( sum ) ;
			sect_distance=d2;
			sect_point = this->m_origin + (view_ray.GetDirection() * d2 - d_vec);
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		//inside the sphere
		//sita = acos ( product / d );
		//d1 = d * sin(sita);
		d2 = product + sqrt( sum );
		sect_distance = d2;
		sect_point = this->m_origin + (view_ray.GetDirection() * d2 - d_vec);
		return -1;
	}

}

void CShapeSphere::drawByGlut()
{
	glPushMatrix(); { /* draw the background sphere */
		glColor3f(m_material.m_diffuse.m_x,m_material.m_diffuse.m_y,m_material.m_diffuse.m_z);
		glTranslated( m_origin.m_x, m_origin.m_y, m_origin.m_z );
		glutSolidSphere( m_radius, 40, 40 );
	} glPopMatrix();
}

void CShapeSphere::calcPlane( CTuple3 cpoint, CTuple3& normal )
{
	normal  = (cpoint - m_origin);
	normal.normalize();
}
DTYPE CShapeSphere::calcDistance(CTuple3 point)
{
	return fabs((m_origin-point).metric()-m_radius);
}

bool CShapeSphere::getTextureMap( CTuple3 p, DTYPE &u, DTYPE &v )
{
	return true;
}

void CShapeSphere::getBoundaryBox( CTuple3 &left_down, CTuple3 &right_up )
{
	left_down = m_origin + CTuple3(-m_radius,-m_radius,-m_radius);
	right_up = m_origin + CTuple3(m_radius,m_radius,m_radius);
}

bool CShapeSphere::intersectBox( CBox box )
{
	return true;
}