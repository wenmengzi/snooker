#if !defined(AFX_ARGSETTINGDLG_H__5D849AE5_5B4E_4695_AD73_A439371CD580__INCLUDED_)
#define AFX_ARGSETTINGDLG_H__5D849AE5_5B4E_4695_AD73_A439371CD580__INCLUDED_
#include "SnookerCore.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ArgSettingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CArgSettingDlg dialog

class CArgSettingDlg : public CDialog
{
// Construction
public:
	CArgSettingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CArgSettingDlg)
	enum { IDD = IDD_ARG_DLG };
	CComboBox	m_combox;
	CString	m_u1;
	CString	m_u2;
	CString	m_k1;
	CString	m_k2;
	CString	m_alpha1;
	CString	m_alpha2;
	CString	m_x;
	CString	m_y;
	CString	m_color_r;
	CString	m_color_g;
	CString	m_color_b;
	CString	m_color_a;
	CString	m_vmax;
	BOOL	m_reset;
	int		m_PPF;
	int		m_fps;
	//}}AFX_DATA
	GAMEOBJECT gobject[MAX_NUM_OBJ];
	int sel;
	FLOAT u1;
	FLOAT u2;
	FLOAT k1;
	FLOAT k2;
	FLOAT alpha1;
	FLOAT alpha2;
	FLOAT vmax;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArgSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CArgSettingDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo1();
	virtual void OnOK();
	afx_msg void OnKillfocusEdit3();
	afx_msg void OnKillfocusEdit4();
	afx_msg void OnKillfocusEdit11();
	afx_msg void OnKillfocusEdit12();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARGSETTINGDLG_H__5D849AE5_5B4E_4695_AD73_A439371CD580__INCLUDED_)
