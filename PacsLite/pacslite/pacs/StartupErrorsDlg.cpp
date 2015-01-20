// StartupErrorsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pacs.h"
#include "StartupErrorsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStartupErrorsDlg dialog


CStartupErrorsDlg::CStartupErrorsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStartupErrorsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStartupErrorsDlg)
	//}}AFX_DATA_INIT
}


void CStartupErrorsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStartupErrorsDlg)
	DDX_Control(pDX, IDC_TEXTBOX1, m_txtboxErrorMessages);
	DDX_Control(pDX, IDC_CONVEYOR_LABEL, m_lblConveyor);
	DDX_Control(pDX, IDC_DATABASE_LABEL, m_lblDatabase);
	DDX_Control(pDX, IDC_DIO_LABEL, m_lblDIO);
	DDX_Control(pDX, IDC_PRINTER_LABEL, m_lblPrinter);
	DDX_Control(pDX, IDC_SCANNER_LABEL, m_lblScanner);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStartupErrorsDlg, CDialog)
	//{{AFX_MSG_MAP(CStartupErrorsDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStartupErrorsDlg message handlers


BOOL CStartupErrorsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString	csTemp;

	
	// check the Database for errors
	if (!m_poDatabase->m_bInitialized)
	{
		csTemp = m_poDatabase->GetLastErrorMsg();
		m_lblDatabase.SetCaption((LPCTSTR)"Error");
	}
	else
		m_lblDatabase.SetCaption((LPCTSTR)"OK");




	// check the DIO for errors
	if (!m_poDioController->m_bInitialized)
	{
		m_lblDIO.SetCaption((LPCTSTR)"Error");
		csTemp = csTemp + "  ";		
		csTemp = csTemp + m_poDioController->m_csErrorString;
	}
	else
		m_lblDIO.SetCaption((LPCTSTR)"OK");



	// check the printer for errors
	if (!m_poPrinterControl->m_bInitialized)
	{
		m_lblPrinter.SetCaption((LPCTSTR)"Error");
		csTemp = csTemp + "  ";
		csTemp = csTemp + m_poPrinterControl->m_csErrorString;
	}
	else
		m_lblPrinter.SetCaption((LPCTSTR)"OK");

	// check the scanner for errors
	if (!m_poScannerControl->m_bInitialized)
	{
		m_lblScanner.SetCaption((LPCTSTR)"Error");
		csTemp = csTemp + "  ";
		csTemp = csTemp + m_poScannerControl->m_csErrorString;
	}
	else
		m_lblScanner.SetCaption((LPCTSTR)"OK");

	// if there is an error message, put it in the box
	if (!csTemp.IsEmpty())
		m_txtboxErrorMessages.SetText((LPCTSTR)csTemp);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
