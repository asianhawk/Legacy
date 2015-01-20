// RescanDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PACS.h"
#include "RescanDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRescanDlg dialog


CRescanDlg::CRescanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRescanDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRescanDlg)
	//}}AFX_DATA_INIT

	m_bReSync=FALSE;
}


void CRescanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRescanDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRescanDlg, CDialog)
	//{{AFX_MSG_MAP(CRescanDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRescanDlg message handlers

BEGIN_EVENTSINK_MAP(CRescanDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CRescanDlg)
	ON_EVENT(CRescanDlg, IDC_HALTBUTTON, -600 /* Click */, OnClickHaltButton, VTS_NONE)
	ON_EVENT(CRescanDlg, IDC_RELABELBUTTON, -600 /* Click */, OnClickRelabelButton, VTS_NONE)
	ON_EVENT(CRescanDlg, IDC_RESCANBUTTON, -600 /* Click */, OnClickRescanButton, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CRescanDlg::OnClickHaltButton() 
{

	m_nRecovery = HALT_RECOVERY;

	CDialog::OnOK();
	
}


void CRescanDlg::OnClickRelabelButton() 
{

	m_nRecovery = RELABEL_RECOVERY;

	CDialog::OnOK();
	
}


void CRescanDlg::OnClickRescanButton() 
{

	m_nRecovery = RESCAN_RECOVERY;

	CDialog::OnOK();
	
	
}



BOOL CRescanDlg::OnInitDialog() 
{

	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
