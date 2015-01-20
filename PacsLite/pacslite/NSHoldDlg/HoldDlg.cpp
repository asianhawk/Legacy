// HoldDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HoldDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHoldDlg dialog


CHoldDlg::CHoldDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHoldDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHoldDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHoldDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHoldDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHoldDlg, CDialog)
	//{{AFX_MSG_MAP(CHoldDlg)
		// NOTE: the ClassWizard will add message map macros here
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHoldDlg message handlers


BEGIN_EVENTSINK_MAP(CHoldDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CHoldDlg)
	ON_EVENT(CHoldDlg, IDC_SYSTEM_SETUP, -600 /* Click */, OnClickSystemSetup, VTS_NONE)
	ON_EVENT(CHoldDlg, IDC_CONTINUE, -600 /* Click */, OnClickContinue, VTS_NONE)
	ON_EVENT(CHoldDlg, IDC_EXIT, -600 /* Click */, OnClickExit, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()





void CHoldDlg::OnClickSystemSetup() 
{

	m_nHoldSelection = HOLD_SETUP_SYSTEM;

	CDialog::OnOK();
	
}



void CHoldDlg::OnClickContinue() 
{

	m_nHoldSelection = HOLD_CONTINUE;

	CDialog::OnOK();
	
}



void CHoldDlg::OnClickExit() 
{

	m_nHoldSelection = HOLD_EXIT;

	CDialog::OnOK();

	
	
}


void CHoldDlg::OnTimer(UINT nIDEvent) 
{

	KillTimer(nIDEvent);



	if ( nIDEvent == 1002 )
	{
		if(m_oDIOInput->IsStartButtonOn())
		{
			OnClickContinue();
			return;

		}
		if((m_oDIOInput->IsStopButtonOn())&&(m_blnDelay))
		{
			OnClickExit();
			return;

		}

		SetTimer ( 1002, 100, NULL );  // time interval is 1 minute
	}
	if ( nIDEvent == 1003 )
	{
		m_blnDelay=TRUE;


	}

	CDialog::OnTimer(nIDEvent);
}


BOOL CHoldDlg::OnInitDialog()
{


	CDialog::OnInitDialog();
	SetTimer ( 1002, 100, NULL );  // time interval is 1/10 sec
	SetTimer ( 1003, 7000, NULL );  // time interval is 7 sec
	m_blnDelay=FALSE;


	return TRUE;  // return TRUE  unless you set the focus to a control
}

