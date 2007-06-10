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

	// ����RC����ʼ���ӿ� - �ڲ����� OnCreate()
	BOOL CreateRC(CDC *pdc, CRect &rect, BOOL bMWA = FALSE);

	// �ı�����
	BOOL SetViewport(int cx, int cy);

	// �ı���Ļ
	BOOL SetScreen(HWND hWnd, int width, int height, int depth, BOOL bFullScr = TRUE);

// �ؼ��ӿ�

	// ��Ⱦ���� - �ڲ����� OnPaint()
	void Render();

	// �ര����Ⱦ
	void RenderMWA();

	// ��ʼ������
	virtual void OnCreate();

	// ��ͼ����
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
