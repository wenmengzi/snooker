// coreDlg.cpp : implementation file
//

#include "stdafx.h"
#include "core.h"
#include "coreDlg.h"
#include "ArgSettingDlg.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCoreDlg dialog

CCoreDlg::CCoreDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCoreDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCoreDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	sel=0;
}

void CCoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCoreDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCoreDlg, CDialog)
	//{{AFX_MSG_MAP(CCoreDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCoreDlg message handlers

BOOL CCoreDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	SetWindowPos(&wndNoTopMost,0,0,780,447,SWP_NOMOVE);
	CClientDC *pdc=new CClientDC(this);
	CRect rect;
	GetClientRect(&rect);
	/*
	CString str;
	str.Format("w %d h %d",rect.Width(),rect.Height());
	MessageBox(str);
	*/
	m_snooker.CreateRC(pdc,rect);

	SetTimer(1,14,NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCoreDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
//		m_snooker.Render();
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCoreDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCoreDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==1)
	{
		m_snooker.Render();
	}
	CDialog::OnTimer(nIDEvent);
}

void CCoreDlg::OnOK() 
{
	// TODO: Add extra validation here
	int fps;
	DWORD now=GetTickCount();
	fps=1000*m_snooker.frames/(now-m_snooker.startTime);
	CArgSettingDlg dlg;
	memcpy(dlg.gobject,m_snooker.gobject,sizeof(GAMEOBJECT)*MAX_NUM_OBJ);

	dlg.m_fps=fps;//set fps
	dlg.sel=sel;
	dlg.u1=GAMEOBJECT::u1;
	dlg.u2=GAMEOBJECT::u2;
	dlg.k1=GAMEOBJECT::k1;
	dlg.k2=GAMEOBJECT::k2;
	dlg.alpha1=GAMEOBJECT::alpha1;
	dlg.alpha2=GAMEOBJECT::alpha2;
	dlg.vmax=GAMEOBJECT::vmax;
	dlg.m_PPF=GAMEOBJECT::PPF;
	dlg.DoModal(); //
	GAMEOBJECT::PPF=dlg.m_PPF;
	GAMEOBJECT::vmax=dlg.vmax;
	GAMEOBJECT::alpha2=dlg.alpha2;
	GAMEOBJECT::alpha1=dlg.alpha1;
	GAMEOBJECT::k2=dlg.k2;
	GAMEOBJECT::k1=dlg.k1;
	GAMEOBJECT::u2=dlg.u2;
	GAMEOBJECT::u1=dlg.u1;
	sel=dlg.sel;
	memcpy(m_snooker.gobject,dlg.gobject,sizeof(GAMEOBJECT)*MAX_NUM_OBJ);
	if(dlg.m_reset)
		m_snooker.ResetObject();
	m_snooker.gobject[0].vx=GAMEOBJECT::vmax;
	Invalidate(FALSE);
}

void CCoreDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(nFlags==MK_LBUTTON)
	{
		float fx=-1.114f+(point.x-27)*2.228f/719.0f;
		float fy=0.559f-(point.y-27)*1.118f/360.0f;
		if(sel>=0 && sel<22)
		{
			m_snooker.gobject[sel].x=fx;
			m_snooker.gobject[sel].y=fy;
			Invalidate(FALSE);
		}
	}
	CDialog::OnMouseMove(nFlags, point);
}

void CCoreDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	float fx=-1.114f+(point.x-27)*2.228f/719.0f;
	float fy=0.559f-(point.y-27)*1.118f/360.0f;

	for(int i=0;i<22;++i)
	{
		if(fabsf(m_snooker.gobject[i].x-fx)<0.029f &&
			fabsf(m_snooker.gobject[i].y-fy)<0.029f)
		{
			break;
		}
	}
	sel=i;
	CDialog::OnLButtonDown(nFlags, point);
}

void CCoreDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	// give white ball a speed and game start
	float fx=-1.114f+(point.x-27)*2.228f/719.0f;
	float fy=0.559f-(point.y-27)*1.118f/360.0f;
	
	CDialog::OnRButtonUp(nFlags, point);
}
