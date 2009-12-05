#include "Texture.h"
#include <fstream>
using namespace std;

extern char g_debugbuff[DBG_BUFF_LEN];
CTexture::CTexture(void)
{
	m_assigned=false;
	m_height=0;
	m_width=0;
}

CTexture::~CTexture(void)
{
	reset();
}

void CTexture::reset()
{
	if(m_assigned)
	{
		int c;
		for(c=0;c<m_width;c++)
			delete [] (m_rgb[c]);
		delete []m_rgb;
		m_height=0;
		m_width=0;
		m_assigned=false;
	}
}

void CTexture::init(const char *textfile_name, int width, int height)
{
	int r,c;
	float rv,gv,bv;
	
	reset();

	m_height=height;
	m_width=width;
	
	m_rgb=new CTuple3* [m_width];
	for(c=0;c<m_width;c++)
	{
		m_rgb[c]=new CTuple3 [m_height];
	}


	ifstream read_file;
	read_file.open(textfile_name);
	assert(read_file.is_open());

	for(c=0;c<m_width;c++)
		for(r=0;r<m_height;r++)
		{
			assert(read_file.good());
			read_file >>rv >>gv >>bv;
			m_rgb[c][r].SetValue(rv,gv,bv);
		}
	
	m_assigned=true;
	read_file.close();
}

/*
we suppose u and v are [0.0,1.0) here.
*/
CTuple3 CTexture::getTexture(float u, float v)
{
	if(m_assigned)
	{
		int x=(int)(u*m_width);
		int y=(int)(v*m_height);
		return m_rgb[x][y];
	}
	else
		return CTuple3(0,0,0);
}