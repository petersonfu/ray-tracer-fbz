#include "ShapeSphere.h"

extern float sqrt(float x);

CShapeSphere::CShapeSphere(void)
{

}

CShapeSphere::CShapeSphere(CTuple3 origin, CMaterial mat, float ref_factor, bool is_light, float i_refract, float e_refract, float radius)
{
	m_material=mat;
	m_light=is_light;
	m_radius=radius;
	m_refl_factor=ref_factor;
	m_light=is_light;
	m_origin=origin;
	m_i_refract = i_refract;
	m_e_refract = e_refract;
}

CShapeSphere::~CShapeSphere(void)
{
}

//note that ray should have been normalized
int CShapeSphere::intersect(CRay &view_ray,  CTuple3 &sect_point, float &sect_distance)
{
	CTuple3 d_vec=this->m_origin-view_ray.GetOrigin();
	float d=d_vec.metric();
	float sita, sita1, product, d1, d2;
	product=d_vec * view_ray.GetDirection();
	float sum=m_radius*m_radius-d*d+product*product;
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
float CShapeSphere::calcDistance(CTuple3 point)
{
	return fabs((m_origin-point).metric()-m_radius);
}
