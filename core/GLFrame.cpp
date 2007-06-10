// GLFrame.cpp: implementation of the CGLFrame class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GLFrame.h"


#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGLFrame::CGLFrame()
{
	m_hrc=NULL;
	m_pdc=NULL;
	m_width=0;
	m_height=0;
	m_bFullScreen=FALSE;
	//test
	rot=0.0f;
	rspeed=1.0f;
}

CGLFrame::~CGLFrame()
{
    ::wglMakeCurrent(NULL,NULL);
	
    if(m_hrc)
        ::wglDeleteContext(m_hrc);

    if(m_pdc)
	    delete m_pdc;
}

BOOL CGLFrame::CreateRC(CDC *pdc, CRect &rect, BOOL bMWA)
{
	PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR), 
			1,
			PFD_DRAW_TO_WINDOW |
			PFD_SUPPORT_OPENGL|
			PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			24,
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			/*32,*/0,
			0,
			0,
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
	};
	int pixelformat;
	
	if ( (pixelformat = ChoosePixelFormat(pdc->m_hDC, &pfd)) == 0 )
	{
		AfxMessageBox("ChoosePixelFormat failed");
		return FALSE;
	}
	
	if (SetPixelFormat(pdc->m_hDC, pixelformat, &pfd) == FALSE)
	{
		AfxMessageBox("SetPixelFormat failed");
		return FALSE;
	}
	
	/*
	n =::GetPixelFormat(my_pDC->GetSafeHdc());
	::DescribePixelFormat(my_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);
	*/
	
	m_hrc = wglCreateContext(pdc->m_hDC);
	wglMakeCurrent(pdc->m_hDC, m_hrc);
	m_pdc=pdc;

	m_width=rect.Width();
	m_height=rect.Height();

	SetViewport(m_width, m_height);

	OnCreate();

	if(bMWA)
		wglMakeCurrent(NULL,NULL);

	return TRUE;
}

BOOL CGLFrame::SetViewport(int cx, int cy)
{
	if(cx>0)
	{
		//wglMakeCurrent(m_pdc->m_hDC, m_hrc);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		glFrustum(-1.0,1.0,-1.0*cy/cx,1.0*cy/cx,5.0,9.0);
		glViewport(0, 0, cx, cy);

		//wglMakeCurrent(NULL, NULL);
		return TRUE;
	}
	return FALSE;
}

BOOL CGLFrame::SetScreen(HWND hWnd, int width, int height, int depth, BOOL bFullScr)
{
	if(bFullScr==m_bFullScreen)
		return TRUE;
	if(bFullScr)
	{
		DEVMODE dem;
		ZeroMemory(&dem,sizeof(dem));
		dem.dmSize=sizeof(dem);
		dem.dmPelsWidth=width;
		dem.dmPelsHeight=height;
		dem.dmBitsPerPel=depth;
		dem.dmFields=DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		if(DISP_CHANGE_SUCCESSFUL == ChangeDisplaySettings(&dem,CDS_FULLSCREEN))
		{
			m_bFullScreen=bFullScr;
		}
		else
			return FALSE;
		LONG style=GetWindowLong(hWnd,GWL_STYLE);
		style &=~ (WS_CAPTION | WS_SYSMENU);
		SetWindowLong(hWnd,GWL_STYLE,style);
		SetWindowPos(hWnd,HWND_TOPMOST,0,0,width,height,SWP_SHOWWINDOW);
		SetViewport(width,height);
	}
	else
	{
		
		if(DISP_CHANGE_SUCCESSFUL == ChangeDisplaySettings(NULL,0))
		{
			m_bFullScreen=bFullScr;
		}
		else
			return FALSE;
		LONG style=GetWindowLong(hWnd,GWL_STYLE);
		style |= (WS_CAPTION | WS_SYSMENU);
		SetWindowLong(hWnd,GWL_STYLE,style);
		SetWindowPos(hWnd,HWND_NOTOPMOST,0,80,width,height,SWP_SHOWWINDOW);
		SetViewport(width,height);
	}
	return TRUE;
}

void CGLFrame::Render()
{
	//glClearColor(0.2f,0.2f,0.5f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	OnPaint();
	
	glFinish();

	SwapBuffers(m_pdc->m_hDC);
}

void CGLFrame::RenderMWA()
{
	wglMakeCurrent(m_pdc->m_hDC, m_hrc);

	//glClearColor(0.2f,0.2f,0.5f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	OnPaint();
	
	glFinish();

	SwapBuffers(m_pdc->m_hDC);

	wglMakeCurrent(NULL, NULL);
}

void CGLFrame::OnCreate()
{
	glShadeModel(GL_SMOOTH); // Enable Smooth Shading
	glClearColor(0.0f, 0.3f, 1.0f, 0.5f); // Black Background
	glClearDepth(1.0f); // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations
	glEnable(GL_TEXTURE_2D); // Enable Texture Mapping
}

void CGLFrame::OnPaint()
{
	// EXAMPLE OPENGL CODE START ////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	
	glPushMatrix(); // Push Matrix Onto Stack (Copy The Current Matrix)
	glLoadIdentity(); // Reset The Current Modelview Matrix
	glTranslatef(0.0f,0.0f,-6.0f); // Move Left 1.5 Units And Into The Screen 6.0
	
	glRotatef(rot, 0.0f, 0.0f, 1.0f);
	
	glBegin(GL_TRIANGLES);
	glColor3f( 1.0f, 0.0f, 0.0f ); glVertex2f( -1.0f, 1.0f );
	glColor3f( 0.0f, 1.0f, 0.0f ); glVertex2f( -1.0f, -1.0f );
	glColor3f( 0.0f, 0.0f, 1.0f ); glVertex2f( 1.0f, 0.0f );
	glEnd();
	
	//Ball();
	
	glLoadIdentity();
	glPopMatrix();
	
	rot += rspeed;
}