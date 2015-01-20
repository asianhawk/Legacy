// DiagMsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PACS.h"
#include "DiagMsgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiagMsgDlg dialog


CDiagMsgDlg::CDiagMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDiagMsgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDiagMsgDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDiagMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDiagMsgDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDiagMsgDlg, CDialog)
	//{{AFX_MSG_MAP(CDiagMsgDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiagMsgDlg message handlers
