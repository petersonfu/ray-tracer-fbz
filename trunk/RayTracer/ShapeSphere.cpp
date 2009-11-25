#include "ShapeSphere.h"

CShapeSphere::CShapeSphere(void)
{
	init(0.0,0.0,0.0,0.0,CMaterial(CTuple3(1.0,1.0,1.0),CTuple3(1.0,1.0,1.0),CTuple3(1.0,1.0,1.0)),1.0,false);
}
CShapeSphere::CShapeSphere(float x, float y, float z, float r)
{
	init(x,y,z,r,CMaterial(CTuple3(1.0,1.0,1.0),CTuple3(1.0,1.0,1.0),CTuple3(1.0,1.0,1.0)),1.0,false);
}

CShapeSphere::CShapeSphere(float x, float y, float z, float r, CMaterial mat,float ref, bool is_light)
{
	init(x,y,z,r,mat,ref,is_light);
}

void CShapeSphere::init(float x, float y, float z, float r, CMaterial mat, float ref, bool is_light)
{
	this->m_material=mat;
	this->m_light=false;
	m_center.SetValue(x,y,z);
	m_radius=r;
	m_refl_factor=ref;
	m_light=is_light;
}

CShapeSphere::~CShapeSphere(void)
{
}

//note that ray should have been normalized
bool CShapeSphere::intersect(CRay &view_ray,  CTuple3 &sect_point, float &sect_distance)
{
	CTuple3 d_vec=this->m_center-view_ray.GetOrigin();
	float d=d_vec.metric();
	float sita=asin( this->m_radius/d );
	//view_ray.GetDirection().normalize();
	float sita1=acos(fabs(d_vec * view_ray.GetDirection()/d));
	if(sita>sita1)
	{
		float d1= d*sin(sita1);
		float d2= d*cos(sita1) - sqrt( m_radius*m_radius-d1*d1) ;
		sect_distance=d2;
		sect_point = this->m_center + (view_ray.GetDirection() * d2 - d_vec);
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
		glTranslated( m_center.m_x, m_center.m_y, m_center.m_z );
		glutSolidSphere( m_radius, 40, 40 );
	} glPopMatrix();
}

void CShapeSphere::calcPlane( CTuple3 lpoint, CTuple3 vpoint, CTuple3 cpoint, CTuple3& light, CTuple3& normal, CTuple3& reflect, CTuple3& view)
{
	normal  = (cpoint - m_center);
	normal.normalize();
	light   = (lpoint - cpoint);
	light.normalize();
	view    = (vpoint - cpoint);
	view.normalize();
	reflect = (normal * 2.0 - light);
	reflect.normalize();
}