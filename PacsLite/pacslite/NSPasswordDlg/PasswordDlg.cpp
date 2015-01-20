// PasswordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PasswordDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPasswordDlg dialog

CPasswordDlg::CPasswordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPasswordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPasswordDlg)
	//}}AFX_DATA_INIT
}


void CPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPasswordDlg)
	DDX_Control(pDX, IDC_PASSWORD, m_txtPassword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPasswordDlg, CDialog)
	//{{AFX_MSG_MAP(CPasswordDlg)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPasswordDlg message handlers

BEGIN_EVENTSINK_MAP(CPasswordDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CPasswordDlg)
	ON_EVENT(CPasswordDlg, IDOK, -600 /* Click */, OnClickOk, VTS_NONE)
	ON_EVENT(CPasswordDlg, IDCANCEL, -600 /* Click */, OnClickCancel, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()



BOOL CPasswordDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CPasswordDlg::OnClickOk() 
{

	m_txtPassword.GetWindowText ( m_csPassword );

	CDialog::OnOK();

}



void CPasswordDlg::OnClickCancel() 
{

	CDialog::OnCancel();
	
}




void CPasswordDlg::OnDestroy() 
{

	m_txtPassword.GetWindowText ( m_csPassword );

	CDialog::OnDestroy();
	
}

