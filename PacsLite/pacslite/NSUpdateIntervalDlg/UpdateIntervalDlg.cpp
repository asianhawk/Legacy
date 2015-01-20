// UpdateIntervalDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UpdateIntervalDlg.h"
#include "Utilities.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUpdateIntervalDlg dialog


CUpdateIntervalDlg::CUpdateIntervalDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUpdateIntervalDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUpdateIntervalDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CUpdateIntervalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUpdateIntervalDlg)
	DDX_Control(pDX, IDC_UPDATE_INTERVAL, m_txtUpdateInterval);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUpdateIntervalDlg, CDialog)
	//{{AFX_MSG_MAP(CUpdateIntervalDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpdateIntervalDlg message handlers

BEGIN_EVENTSINK_MAP(CUpdateIntervalDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CUpdateIntervalDlg)
	ON_EVENT(CUpdateIntervalDlg, IDOK, -600 /* Click */, OnClickOk, VTS_NONE)
	ON_EVENT(CUpdateIntervalDlg, IDCANCEL, -600 /* Click */, OnClickCancel, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()



BOOL CUpdateIntervalDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString csTemp;


	csTemp.Format ( "%d", m_nUpdateInterval );
	m_txtUpdateInterval.SetWindowText ( csTemp );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CUpdateIntervalDlg::OnClickOk() 
{
	
	CString csTemp;
	CString csMessage;

	CUtilities Utility;


	m_txtUpdateInterval.GetWindowText ( csTemp );

	if ( csTemp.GetLength() > 4 )
	{
		csMessage.LoadString ( IDS_INVALID_INTERVAL );
		AfxMessageBox ( "Update Interval Error\n" + csMessage );
		return;
	}


	if ( !Utility.IsNumeric ( csTemp ) )
	{
		csMessage.LoadString ( IDS_INVALID_NUMERIC );
		AfxMessageBox ( "Update Interval Error\n" + csMessage );
		return;
	}

	m_nUpdateInterval = atoi ( (const char *)csTemp );

	CDialog::OnOK();
	
}


void CUpdateIntervalDlg::OnClickCancel() 
{
	

	CDialog::OnCancel();

}


