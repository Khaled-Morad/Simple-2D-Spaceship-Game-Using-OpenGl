
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <glaux.h>		// Header File For The Glaux Library
#include <math.h>
class zeta
{
	
public:
	
	float x,y,health,z;
		
	zeta(float x1,float y1 )
	{
		x=x1;
		y=y1;
		health=3;
	}
	void draw(float x,float y)
	{
		glColor3f(0,1,1);
		glBegin(GL_TRIANGLES);
		glVertex3d(x,y,0);
		glVertex3d(x-0.3,y-0.3,0);
		glVertex3d(x+0.3,y-0.3,0);
		glEnd();
		glColor3f(1,1,0);
		glBegin(GL_TRIANGLES);
		glVertex3d(x,y,0);
		glVertex3d(x+1,y-0.5,0);
		glVertex3d(x+0.3,y-0.3,0);
		glEnd();

		glColor3f(1,1,0);
		glBegin(GL_TRIANGLES);
		glVertex3d(x,y,0);
		glVertex3d(x-1,y-0.5,0);
		glVertex3d(x-0.3,y-0.3,0);
		glEnd();

	}
	void fire()
	{
		glColor3f(0,1,1);
		glBegin(GL_POINTS);
		
		glEnd();
	}
	~zeta(void)
	{
	}
};

