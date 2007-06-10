// ArgSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "core.h"
#include "ArgSettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArgSettingDlg dialog


CArgSettingDlg::CArgSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CArgSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CArgSettingDlg)
	m_u1 = _T("0.01");
	m_u2 = _T("0.01");
	m_k1 = _T("0.5");
	m_k2 = _T("0.4");
	m_alpha1 = _T("0.0001");
	m_alpha2 = _T("0.0001");
	m_x = _T("");
	m_y = _T("");
	m_color_r = _T("");
	m_color_g = _T("");
	m_color_b = _T("");
	m_color_a = _T("");
	m_vmax = _T("");
	m_reset = FALSE;
	m_PPF = 0;
	m_fps = 0;
	//}}AFX_DATA_INIT
}


void CArgSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArgSettingDlg)
	DDX_Control(pDX, IDC_COMBO1, m_combox);
	DDX_Text(pDX, IDC_EDIT5, m_u1);
	DDX_Text(pDX, IDC_EDIT6, m_u2);
	DDX_Text(pDX, IDC_EDIT7, m_k1);
	DDX_Text(pDX, IDC_EDIT8, m_k2);
	DDX_Text(pDX, IDC_EDIT9, m_alpha1);
	DDX_Text(pDX, IDC_EDIT10, m_alpha2);
	DDX_Text(pDX, IDC_EDIT1, m_x);
	DDX_Text(pDX, IDC_EDIT2, m_y);
	DDX_Text(pDX, IDC_EDIT3, m_color_r);
	DDX_Text(pDX, IDC_EDIT4, m_color_g);
	DDX_Text(pDX, IDC_EDIT11, m_color_b);
	DDX_Text(pDX, IDC_EDIT12, m_color_a);
	DDX_Text(pDX, IDC_EDIT13, m_vmax);
	DDX_Check(pDX, IDC_CHECK1, m_reset);
	DDX_Text(pDX, IDC_EDIT14, m_PPF);
	DDX_Text(pDX, IDC_EDIT15, m_fps);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArgSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CArgSettingDlg)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_EN_KILLFOCUS(IDC_EDIT3, OnKillfocusEdit3)
	ON_EN_KILLFOCUS(IDC_EDIT4, OnKillfocusEdit4)
	ON_EN_KILLFOCUS(IDC_EDIT11, OnKillfocusEdit11)
	ON_EN_KILLFOCUS(IDC_EDIT12, OnKillfocusEdit12)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArgSettingDlg message handlers

BOOL CArgSettingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	for(int i=0;i<22;++i)
	{
		CString str;
		str.Format("ball%d",i);
		m_combox.InsertString(i,str);
	}
	if(sel>=0 && sel<22)
	{
		m_combox.SetCurSel(sel);
		OnSelchangeCombo1();
	}
	m_k1.Format("%.8f",k1);
	m_k2.Format("%.8f",k2);
	m_u1.Format("%f",u1);
	m_u2.Format("%f",u2);
	m_alpha1.Format("%f",alpha1);
	m_alpha2.Format("%f",alpha2);
	m_vmax.Format("%f",vmax);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CArgSettingDlg::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	CString str;
	sel=m_combox.GetCurSel();
	
	m_x.Format("%f",gobject[sel].x);
	m_y.Format("%f",gobject[sel].y);
	m_color_r.Format("%f",gobject[sel].color_r);
	m_color_g.Format("%f",gobject[sel].color_g);
	m_color_b.Format("%f",gobject[sel].color_b);
	m_color_a.Format("%f",gobject[sel].color_a);

	UpdateData(FALSE);
	
}

void CArgSettingDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	u1=(float)atof(m_u1);
	u2=(float)atof(m_u2);
	k1=(float)atof(m_k1);
	k2=(float)atof(m_k2);
	alpha1=(float)atof(m_alpha1);
	alpha2=(float)atof(m_alpha2);
	sel=m_combox.GetCurSel();
	vmax=(float)atof(m_vmax);
	if(sel<0)
		sel=0;
	CDialog::OnOK();
}

void CArgSettingDlg::OnKillfocusEdit3() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	sel=m_combox.GetCurSel();
	gobject[sel].color_r=(float)atof(m_color_r);
}

void CArgSettingDlg::OnKillfocusEdit4() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	sel=m_combox.GetCurSel();
	gobject[sel].color_g=(float)atof(m_color_g);
}

void CArgSettingDlg::OnKillfocusEdit11() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	sel=m_combox.GetCurSel();
	gobject[sel].color_b=(float)atof(m_color_b);
}

void CArgSettingDlg::OnKillfocusEdit12() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	sel=m_combox.GetCurSel();
	gobject[sel].color_a=(float)atof(m_color_a);
}

void CArgSettingDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	OnOK();
}
