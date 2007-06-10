// coreDlg.h : header file
//

#if !defined(AFX_COREDLG_H__181AB4CD_3F44_4110_8EF4_28A4A7FED7E7__INCLUDED_)
#define AFX_COREDLG_H__181AB4CD_3F44_4110_8EF4_28A4A7FED7E7__INCLUDED_

#include "SnookerCore.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCoreDlg dialog

class CCoreDlg : public CDialog
{
// Construction
public:
	CCoreDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCoreDlg)
	enum { IDD = IDD_CORE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoreDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCoreDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CSnookerCore m_snooker;
	int sel;
	float lastradius;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COREDLG_H__181AB4CD_3F44_4110_8EF4_28A4A7FED7E7__INCLUDED_)
