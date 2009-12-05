#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "global.h"
#include "tuples.h"

struct CTexture
{
	int m_width, m_height;
	bool m_assigned;
	CTuple3 **m_rgb;
	CTexture(void);
	~CTexture(void);
	void init(const char *texture_file, int width, int height);
	void reset();
	CTuple3 getTexture(float u, float v);
};

#endif
