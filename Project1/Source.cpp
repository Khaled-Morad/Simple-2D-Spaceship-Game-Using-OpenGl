/*
*		This Code Was Created By Jeff Molofee 2000
*		A HUGE Thanks To Fredric Echols For Cleaning Up
*		And Optimizing This Code, Making It More Flexible!
*		If You've Found This Code Useful, Please Let Me Know.
*		Visit My Site At nehe.gamedev.net
*/

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <glaux.h>		// Header File For The Glaux Library
#include <math.h>
#include "zeta.h"
#include <random>
#include <texture.h>
#include "enemie.h"
#include "alpha.h"
#include "beta.h"
#include <string>
#include "gamma.h"
#include <freeglut.h>
#include "fire.h"
#include <map>
#include <tchar.h>
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Context
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active = TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen = TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}
zeta p(0,-3);

float i;
int j=0;
int image;
std::vector<fire>f;
std::vector<alpha>a;
std::vector<beta>b;
std::vector<gamma>g;
int posy=3;
void destroy()
{
	int i=0,j=0;
	for(i=0;i<a.size();i++)
	{
		for(j=0;j<f.size();j++)
		{
			if(abs(a[i].x-f[j].posx)<=0.4&&abs(a[i].y-f[j].posy)<=0.2&&f[j].posz==0)
			{
				a[i].z=+20;
				f[j].posz+=20;
			}
		}
	}
	for(i=0;i<b.size();i++)
	{
		if(b[i].sool){
			for(j=0;j<f.size();j++)
			{
				if(f[j].posz!=0)
					continue;
				if(abs(b[i].x-f[j].posx)<=0.4&&abs(b[i].y-f[j].posy)<=0.2&&b[i].sool==2)
				{
					f[j].posz+=20;
					b[i].sool--;
				}
				else if(abs(b[i].x-f[j].posx)<=0.4&&abs(b[i].y-f[j].posy)<=0.2&&b[i].sool==1)
				{

					b[i].z=+20;
					b[i].sool--;
					f[j].posz+=20;

				}

			}
		}
	}
	for(i=0;i<g.size();i++)
	{
		if(g[i].sool){
			for(j=0;j<f.size();j++)
			{
				if(f[j].posz!=0)
					continue;
				if(abs(g[i].x-f[j].posx)<=0.4&&abs(g[i].y-f[j].posy)<=0.2&&(g[i].sool==3||g[i].sool==2))
				{
					f[j].posz+=20;
					g[i].sool--;
				}
				else if(abs(g[i].x-f[j].posx)<=0.4&&abs(g[i].y-f[j].posy)<=0.2&&g[i].sool==1)
				{

					g[i].z=+20;
					g[i].sool--;
					f[j].posz+=20;

				}

			}
		}
	}
}

int numofpass()
{
	int i,j,cnt=0;
	for(i=0;i<a.size();i++)
	{
		if(a[i].z==0&&a[i].y<=p.y)
			cnt++;
	}
	for(i=0;i<b.size();i++)
	{
		if(b[i].z==0&&b[i].y<=p.y)
			cnt++;
	}
	for(i=0;i<g.size();i++)
	{
		if(g[i].z==0&&g[i].y<=p.y)
			cnt++;
	}
	return cnt;

}
bool gameover=0;

void numofsools(int numofpass,int numofkillsb)
{
	
	if(!numofpass&& numofkillsb<10){
		glColor3f(0,1,0);
		glBegin(GL_QUADS);
		glVertex3f(-6,p.y+7,0);
		glVertex3f(-5,p.y+7,0);
		glVertex3f(-5,p.y+6.75,0);
		glVertex3f(-6,p.y+6.75,0);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(-6,p.y+6.50,0);
		glVertex3f(-5,p.y+6.50,0);
		glVertex3f(-5,p.y+6.25,0);
		glVertex3f(-6,p.y+6.25,0);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(-6,p.y+6,0);
		glVertex3f(-5,p.y+6,0);
		glVertex3f(-5,p.y+5.75,0);
		glVertex3f(-6,p.y+5.75,0);
		glEnd();
	}
	else if(!numofpass&& numofkillsb>=10)
	{

			glColor3f(0,1,0);
		glBegin(GL_QUADS);
		glVertex3f(-6,p.y+7,0);
		glVertex3f(-5,p.y+7,0);
		glVertex3f(-5,p.y+6.75,0);
		glVertex3f(-6,p.y+6.75,0);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(-6,p.y+6.50,0);
		glVertex3f(-5,p.y+6.50,0);
		glVertex3f(-5,p.y+6.25,0);
		glVertex3f(-6,p.y+6.25,0);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(-6,p.y+6,0);
		glVertex3f(-5,p.y+6,0);
		glVertex3f(-5,p.y+5.75,0);
		glVertex3f(-6,p.y+5.75,0);
		glEnd();
	
	}
	else if(numofpass==1&& numofkillsb<10)
	{
		glColor3f(0,1,0);
		glBegin(GL_QUADS);
		glVertex3f(-6,p.y+7,0);
		glVertex3f(-5,p.y+7,0);
		glVertex3f(-5,p.y+6.75,0);
		glVertex3f(-6,p.y+6.75,0);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(-6,p.y+6.50,0);
		glVertex3f(-5,p.y+6.50,0);
		glVertex3f(-5,p.y+6.25,0);
		glVertex3f(-6,p.y+6.25,0);
		glEnd();
	}
	else if(numofpass==1&& numofkillsb>=10)
	{
			glColor3f(0,1,0);
		glBegin(GL_QUADS);
		glVertex3f(-6,p.y+7,0);
		glVertex3f(-5,p.y+7,0);
		glVertex3f(-5,p.y+6.75,0);
		glVertex3f(-6,p.y+6.75,0);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(-6,p.y+6.50,0);
		glVertex3f(-5,p.y+6.50,0);
		glVertex3f(-5,p.y+6.25,0);
		glVertex3f(-6,p.y+6.25,0);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(-6,p.y+5.50,0);
		glVertex3f(-5,p.y+5.50,0);
		glVertex3f(-5,p.y+5.25,0);
		glVertex3f(-6,p.y+5.25,0);
		glEnd();
	}
	else if(numofpass==2&&  numofkillsb<10)
	{

		glColor3f(0,1,0);
		glBegin(GL_QUADS);
		glVertex3f(-6,p.y+7,0);
		glVertex3f(-5,p.y+7,0);
		glVertex3f(-5,p.y+6.75,0);
		glVertex3f(-6,p.y+6.75,0);
		glEnd();
	}
	else if(numofpass ==2 && numofkillsb>=10)
	{
		glColor3f(0,1,0);
		glBegin(GL_QUADS);
		glVertex3f(-6,p.y+7,0);
		glVertex3f(-5,p.y+7,0);
		glVertex3f(-5,p.y+6.75,0);
		glVertex3f(-6,p.y+6.75,0);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(-6,p.y+6.50,0);
		glVertex3f(-5,p.y+6.50,0);
		glVertex3f(-5,p.y+6.25,0);
		glVertex3f(-6,p.y+6.25,0);
		glEnd();

	}
	else {
		gameover=1;
	}

}
int numberofkillb()
{

	int i=0,cntb=0;
	for(i=0;i<b.size();i++)
	{
		if(b[i].z!=0&&b[i].useforcount==0){
			cntb++;
			b[i].useforcount=1;
		}
	}
	return cntb;
}
void generate_enemies()
{	 

	for(i=0;i<30;i++){
		 float x=-5 +(rand()%11);
		float y= p.y+3+(rand()%(int)(40-p.y+2));
		a.push_back(alpha(x,y));

		
	}
	
	for(i=0;i<25;i++){
		 float x=-5 +(rand()%11);
		float y= p.y+3+(rand()%(int)(40-p.y+2));
		b.push_back(beta(x,y));
	}
	
	for(i=0;i<20;i++){
		 float x=-5 +(rand()%11);
		float y= p.y+3+(rand()%(int)(40-p.y+2));
		g.push_back(gamma(x,y));

		
	}

}


int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	
	generate_enemies();
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	//	glEnable(GL_TEXTURE_2D);
	//image=LoadTexture("1.bmp",255);

	return TRUE;										// Initialization Went OK
}

float x=0,y=1,q=4;
float liney=40,speedyalpah=0.08,speedybeta=0.06,speedygamma=0.03;
void DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix


	glTranslated(0,0,-10);
	
	glPushMatrix();
	if(keys[VK_LEFT]&&!gameover)
	{
		float mxl=-5;
		if(p.x>mxl)
			p.x-=0.5;
	}
	if(keys[VK_RIGHT]&&!gameover)
	{
		float mxr=5;
		if(p.x<mxr)
			p.x+=0.5;
	}
	if(keys[VK_UP]&&!gameover)
	{
		f.push_back(fire(p.x,p.y));
	}
	glColor3f(1,0,0);
	glBegin(GL_LINES);
	liney-=0.05;
	glVertex3d(-10,liney,0);
	glVertex3d(10,liney,0);
	glEnd();
	p.draw(p.x,p.y);
	glPopMatrix();
	destroy();
	glPushMatrix();	
	for(j=0;j<a.size();j++)//move the enemies alpha to me
	{
		if(!gameover)
		a[j].y-=speedyalpah;
		a[j].draw(a[j].x,a[j].y);
	}
	for(j=0;j<b.size();j++)//move the enemies  beta to me
	{
		if(!gameover)
		b[j].y-=speedybeta;
		b[j].draw(b[j].x,b[j].y);
	}
	for(j=0;j<g.size();j++)//move the enemies  gamma to me
	{
		if(!gameover)
		g[j].y-=speedygamma;
		g[j].draw(g[j].x,g[j].y);
	}
	for(j=0;j<f.size();j++)//move the fire 
	{
		if(f[j].posz==0&&!gameover){
			f[j].posy+=0.2;
			f[j].draw();
	}
	}

	numofsools(numofpass(),numberofkillb());
	glPopMatrix();
	if(liney<p.y)
	{
		speedyalpah=0.1;
		speedybeta=0.08;
		speedygamma=0.06;
	}
	

	glFlush();										// Done Drawing The Quad	

	//DO NOT REMOVE THIS
	SwapBuffers(hDC);
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
*	title			- Title To Appear At The Top Of The Window				*
*	width			- Width Of The GL Window Or Fullscreen Mode				*
*	height			- Height Of The GL Window Or Fullscreen Mode			*
*	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
*	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL CreateGLWindow(const char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	fullscreen = fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle = WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
						 UINT	uMsg,			// Message For This Window
						 WPARAM	wParam,			// Additional Message Information
						 LPARAM	lParam)			// Additional Message Information
{
	static PAINTSTRUCT ps;

	switch (uMsg)									// Check For Windows Messages
	{
	case WM_PAINT:
		DrawGLScene();
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_TIMER:
		DrawGLScene();
		return 0;

	case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active = TRUE;						// Program Is Active
			}
			else
			{
				active = FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

	case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
			case SC_SCREENSAVE:					// Screensaver Trying To Start?
			case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

	case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

	case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}

	case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}

	case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
				   HINSTANCE	hPrevInstance,		// Previous Instance
				   LPSTR		lpCmdLine,			// Command Line Parameters
				   int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done = FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen = FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	char c[] = "";
	if (!CreateGLWindow(c, 640, 480, 16, fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}


	//Set drawing timer to 20 frame per second
	UINT timer = SetTimer(hWnd, 0, 50, (TIMERPROC)NULL);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;

}
