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
		int r;
		for(r=0;r<m_height;r++)
			delete [] (m_rgb[4]);
		delete []m_rgb;
		m_height=0;
		m_width=0;
		m_assigned=false;
	}
}

void CTexture::init(const char *textfile_name, int width, int height)
{
	int r,c;
	DTYPE rv,gv,bv;
	
	reset();

	m_height=height;
	m_width=width;
	
	m_rgb=new CTuple3* [m_height];
	for(r=0;r<m_height;r++)
	{
		m_rgb[r]=new CTuple3 [m_width];
	}


	ifstream read_file;
	read_file.open(textfile_name);
	assert(read_file.is_open());

	for(r=0;r<m_height;r++)
		for(c=0;c<m_width;c++)
		{
			assert(read_file.good());
			read_file >>rv >>gv >>bv;
			m_rgb[r][c].SetValue(rv,gv,bv);
		}
	
	m_assigned=true;
	read_file.close();
}

/*
we suppose u and v are [0.0,1.0) here.
*/
CTuple3 CTexture::getTexture(DTYPE u, DTYPE v)
{
	if(m_assigned)
	{
		int x=(int)(v*m_height);
		int y=(int)(u*m_width);
		return m_rgb[x][y];
	}
	else
		return CTuple3(0,0,0);
}