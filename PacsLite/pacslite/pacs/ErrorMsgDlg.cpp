// ErrorMsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pacs.h"
#include "ErrorMsgDlg.h"
#include "AutoFont.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CErrorMsgDlg dialog


CErrorMsgDlg::CErrorMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CErrorMsgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CErrorMsgDlg)
	m_csErrorMessage = _T("");
	//}}AFX_DATA_INIT
}


void CErrorMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CErrorMsgDlg)
	DDX_Text(pDX, IDC_LBL_MESSAGE, m_csErrorMessage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CErrorMsgDlg, CDialog)
	//{{AFX_MSG_MAP(CErrorMsgDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CErrorMsgDlg message handlers

void CErrorMsgDlg::OnTimer(UINT nIDEvent) 
{

	KillTimer(nIDEvent);
	if ( nIDEvent == 1002 )
	{
		if(m_oDIOInput->IsStartButtonOn())
		{
			OnOK();
			return;

		}
		if(m_oDIOInput->IsStopButtonOn())
		{
			OnCancel();
			return;
		}


		SetTimer ( 1002, 100, NULL );  // time interval is 1 minute
	}

	CDialog::OnTimer(nIDEvent);
}

BOOL CErrorMsgDlg::OnInitDialog() 
{
CAutoFont fntObj("Arial");

	CDialog::OnInitDialog();
	
	SetTimer(1002,100,NULL);
	fntObj.SetBold(TRUE);
	fntObj.SetHeight(48);
	fntObj.SetItalic(TRUE);
	
	GetDlgItem(IDC_LBL_MESSAGE)->SetFont(&fntObj);
	GetDlgItem(IDOK)->SetFont(&fntObj);
	GetDlgItem(IDCANCEL)->SetFont(&fntObj);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CErrorMsgDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CErrorMsgDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
