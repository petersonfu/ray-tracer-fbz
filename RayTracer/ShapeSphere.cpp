#include "ShapeSphere.h"

CShapeSphere::CShapeSphere(void)
{

}

CShapeSphere::CShapeSphere(CTuple3 origin, CMaterial mat, float ref_factor, bool is_light, float radius)
{
	m_material=mat;
	m_light=is_light;
	m_radius=radius;
	m_refl_factor=ref_factor;
	m_light=is_light;
	m_origin=origin;
}

CShapeSphere::~CShapeSphere(void)
{
}

//note that ray should have been normalized
bool CShapeSphere::intersect(CRay &view_ray,  CTuple3 &sect_point, float &sect_distance)
{
	CTuple3 d_vec=this->m_origin-view_ray.GetOrigin();
	float d=d_vec.metric();
	float sita=asin( this->m_radius/d );
	//view_ray.GetDirection().normalize();
	float product=d_vec * view_ray.GetDirection();
	if(product<=0)
		return false;
	float sita1=acos(product/d);
	if(sita>sita1)
	{
		float d1= d*sin(sita1);
		float d2= d*cos(sita1) - sqrt( m_radius*m_radius-d1*d1) ;
		sect_distance=d2;
		sect_point = this->m_origin + (view_ray.GetDirection() * d2 - d_vec);
		return true;
	}
	else
	{
		return false;
	}

}

void CShapeSphere::drawByGlut()
{
	glPushMatrix(); { /* draw the background sphere */
		glColor3f( 0.0, 0.8, 6.0 );
		glTranslated( m_origin.m_x, m_origin.m_y, m_origin.m_z );
		glutSolidSphere( m_radius, 40, 40 );
	} glPopMatrix();
}

void CShapeSphere::calcPlane( CTuple3 lpoint, CTuple3 vpoint, CTuple3 cpoint, CTuple3& light, CTuple3& normal, CTuple3& reflect, CTuple3& view)
{
	normal  = (cpoint - m_origin);
	normal.normalize();
	light   = (lpoint - cpoint);
	light.normalize();
	view    = (vpoint - cpoint);
	view.normalize();
	reflect = (normal * 2.0 - light);
	reflect.normalize();
}