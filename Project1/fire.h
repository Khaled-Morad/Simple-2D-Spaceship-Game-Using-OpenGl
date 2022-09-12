#pragma once

#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <glaux.h>		// Header File For The Glaux Library
#include <math.h>
class fire
{
public:
	float posx,posy,posz;

	fire(void)
	{

	}
	fire(float x,float y)
	{
		posx=x;
		posy=y;
		posz=0;
	}
	void draw()
	{
		glPointSize(6);
		glColor3f(0.1,0.5,0.6);
		glBegin(GL_POINTS);
		glVertex3f(posx,posy,posz);
		glEnd();

	}
	~fire(void)
	{
	}
};

