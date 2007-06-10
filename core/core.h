// core.h : main header file for the CORE application
//

#if !defined(AFX_CORE_H__96A6CAEC_9F5E_4AF2_9E8E_1D6A74FB91C8__INCLUDED_)
#define AFX_CORE_H__96A6CAEC_9F5E_4AF2_9E8E_1D6A74FB91C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCoreApp:
// See core.cpp for the implementation of this class
//

class CCoreApp : public CWinApp
{
public:
	CCoreApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoreApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCoreApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CORE_H__96A6CAEC_9F5E_4AF2_9E8E_1D6A74FB91C8__INCLUDED_)
