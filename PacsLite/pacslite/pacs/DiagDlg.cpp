// DiagDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PACS.h"
#include "DiagDlg.h"
#include "DioDlg.h"
#include "ScanDiagDlg.h"

#include "PrinterDiagDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiagDlg dialog


CDiagDlg::CDiagDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDiagDlg::IDD, pParent)
{
	m_poPACSDlg = (CPACSDlg *)pParent;
	
	//{{AFX_DATA_INIT(CDiagDlg)
	//}}AFX_DATA_INIT
}


void CDiagDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDiagDlg)
	DDX_Control(pDX, IDC_SCANNER_DIAGNOSTICS, m_cmdScanner);
	DDX_Control(pDX, IDC_PRINTER_DIAGNOSTICS, m_cmdPrinter);
	DDX_Control(pDX, IDC_DIO_DIAGNOSTICS, m_cmdDIO);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDiagDlg, CDialog)
	//{{AFX_MSG_MAP(CDiagDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiagDlg message handlers

BEGIN_EVENTSINK_MAP(CDiagDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CDiagDlg)
	ON_EVENT(CDiagDlg, IDC_CLOSE_DIAGNOSTICS, -600 /* Click */, OnClickCloseDiagnostics, VTS_NONE)
	ON_EVENT(CDiagDlg, IDC_DIO_DIAGNOSTICS, -600 /* Click */, OnClickDioDiagnostics, VTS_NONE)
	ON_EVENT(CDiagDlg, IDC_PRINTER_DIAGNOSTICS, -600 /* Click */, OnClickPrinterDiagnostics, VTS_NONE)
	ON_EVENT(CDiagDlg, IDC_SCANNER_DIAGNOSTICS, -600 /* Click */, OnClickScannerDiagnostics, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnInitDialog()
//
//	Description:
//		Called to initialize a created dialog
//
//	Arguments:
//		none
//
//	Return:
//		void
//
//	Called by:
//		MFC framework
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDiagDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// start with buttons disabled
	m_cmdDIO.SetEnabled(FALSE);
	m_cmdPrinter.SetEnabled(FALSE);
	m_cmdScanner.SetEnabled(FALSE);

	// turn on dio if we can
	if (m_poDIOController->m_bInitialized)
		m_cmdDIO.SetEnabled(TRUE);
	
	
	// turn on printer if we can
	if (m_poPrinterControl->m_bInitialized)
		m_cmdPrinter.SetEnabled(TRUE);
	
	// if the scanner is initialized
	if (m_poScannerControl->m_bInitialized)
	{
		// check to see if scanner is enabled and initialized
		CString		csName,csTriggerOn,csTriggerOff,csResetString;
		BOOL			bUse,bEnable;
		int			nType;
		CDatabase	oDatabase;

		// check database to see whether to enable it
		oDatabase.Initialize();
		csName = "Placement_Scanner";
		if (oDatabase.GetScannerAttributes(csName,&bUse,&bEnable,&nType,&csTriggerOn,&csTriggerOn, &csResetString))
			if (bUse)
				m_cmdScanner.SetEnabled(TRUE);
		csName = "System_Scanner";
		if (oDatabase.GetScannerAttributes(csName,&bUse,&bEnable,&nType,&csTriggerOn,&csTriggerOn, &csResetString))
			if (bUse)
				m_cmdScanner.SetEnabled(TRUE);
	}

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickCloseDiagnostics()
//
//	Description:
//		Clean up and close the dialog
//
//	Arguments:
//		none
//
//	Return:
//		void
//
//	Called by:
//		MFC framework via button click
/////////////////////////////////////////////////////////////////////////////////////

void CDiagDlg::OnClickCloseDiagnostics() 
{
	CDialog::EndDialog(0);	
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickDioDiagnostics()
//
//	Description:
//		Launch the DIO diagnostics dialog
//
//	Arguments:
//		none
//
//	Return:
//		void
//
//	Called by:
//		MFC framework via button click
/////////////////////////////////////////////////////////////////////////////////////

void CDiagDlg::OnClickDioDiagnostics() 
{
	CDioDlg	DIODiagnostics;

	DIODiagnostics.DoModal();
}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickPrinterDiagnostics()
//
//	Description:
//		Launch the Printer diagnostics dialog
//
//	Arguments:
//		none
//
//	Return:
//		void
//
//	Called by:
//		MFC framework via button click
/////////////////////////////////////////////////////////////////////////////////////

void CDiagDlg::OnClickPrinterDiagnostics() 
{
	// declare the dialog
	CPrinterDiagDlg	PrinterDiagnostics;

	// pass along the pointer
	PrinterDiagnostics.m_poPrinterControl = m_poPrinterControl;

	// launch the dialog
	PrinterDiagnostics.DoModal();
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickScannerDiagnostics()
//
//	Description:
//		Launch the Scanner diagnostics dialog
//
//	Arguments:
//		none
//
//	Return:
//		void
//
//	Called by:
//		MFC framework via button click
/////////////////////////////////////////////////////////////////////////////////////

void CDiagDlg::OnClickScannerDiagnostics() 
{
	// declare the dialog
	CScanDiagDlg	ScannerDiagnostics;

	// pass along the pointer to the scanner control
	ScannerDiagnostics.m_poScannerControl = m_poScannerControl;
	
	// launch the dialog
	ScannerDiagnostics.DoModal();
}

