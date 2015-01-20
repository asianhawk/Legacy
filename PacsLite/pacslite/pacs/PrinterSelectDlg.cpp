// PrinterSelectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PrinterSelectDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrinterSelectDlg dialog



CPrinterSelectDlg::CPrinterSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrinterSelectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrinterSelectDlg)
	m_nPrinterType = 0;
	//}}AFX_DATA_INIT
}


void CPrinterSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrinterSelectDlg)
	DDX_CBIndex(pDX, IDC_PRINTER_TYPES, m_nPrinterType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrinterSelectDlg, CDialog)
	//{{AFX_MSG_MAP(CPrinterSelectDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrinterSelectDlg message handlers
