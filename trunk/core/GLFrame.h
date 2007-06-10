// GLFrame.h: interface for the CGLFrame class.
//
//////////////////////////////////////////////////////////////////////
#include <gl/gl.h>
#include <gl/glu.h>

#if !defined(AFX_GLFRAME_H__3C30C154_4F58_4330_A14E_0711FCB65672__INCLUDED_)
#define AFX_GLFRAME_H__3C30C154_4F58_4330_A14E_0711FCB65672__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGLFrame
{
public:
	CGLFrame();
	virtual ~CGLFrame();

	// 创建RC及初始化视口 - 内部调用 OnCreate()
	BOOL CreateRC(CDC *pdc, CRect &rect, BOOL bMWA = FALSE);

	// 改变视区
	BOOL SetViewport(int cx, int cy);

	// 改变屏幕
	BOOL SetScreen(HWND hWnd, int width, int height, int depth, BOOL bFullScr = TRUE);

// 关键接口

	// 渲染过程 - 内部调用 OnPaint()
	void Render();

	// 多窗口渲染
	void RenderMWA();

	// 初始化过程
	virtual void OnCreate();

	// 画图过程
	virtual void OnPaint();
	
private:
	//HDC m_hCurrentDC;
	CDC *m_pdc;
	HGLRC m_hrc;
	int m_width,m_height;
	BOOL m_bFullScreen;
	// Test
	float rot,rspeed;
};

#endif // !defined(AFX_GLFRAME_H__3C30C154_4F58_4330_A14E_0711FCB65672__INCLUDED_)
