#pragma once

#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <glaux.h>		// Header File For The Glaux Library
#include <math.h>
class enemie
{
public:
	int sool ;
	float x,y,z;
	enemie()
	{
	}
	enemie(float x1,float y1)
	{
		x=x1;
		y=y1;
		z=0;
	}
	void draw(float x,float y)
	{		
		glColor3f(0,0.2,0.2);
		glBegin(GL_TRIANGLES);
		glVertex3d(x,y,z);
		glVertex3d(x-0.3,y+0.3,z);
		glVertex3d(x+0.3,y+0.3,z);
		glEnd();
	}

	~enemie(void)
	{
	}
};

