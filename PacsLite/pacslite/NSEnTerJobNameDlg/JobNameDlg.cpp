// JobNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "JobNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJobNameDlg dialog


CJobNameDlg::CJobNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJobNameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJobNameDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CJobNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJobNameDlg)
	DDX_Control(pDX, IDC_JOBNAME, m_edtJobName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CJobNameDlg, CDialog)
	//{{AFX_MSG_MAP(CJobNameDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJobNameDlg message handlers

BEGIN_EVENTSINK_MAP(CJobNameDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CJobNameDlg)
	ON_EVENT(CJobNameDlg, IDOK, -600 /* Click */, OnClickOk, VTS_NONE)
	ON_EVENT(CJobNameDlg, IDCANCEL, -600 /* Click */, OnClickCancel, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()




void CJobNameDlg::OnClickOk() 
{

	CString
		csTemp;


	m_edtJobName.GetWindowText ( m_csJobName );

	if ( m_csJobName != "" )
		CDialog::OnOK();
	else
	{
		csTemp.LoadString ( IDS_INVALID_JOBNAME );
		AfxMessageBox ( csTemp );
	}

	
}



void CJobNameDlg::OnClickCancel() 
{

	CDialog::OnCancel();
	
}
