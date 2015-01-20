// PrinterDiagDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PACS.h"
#include "PrinterDiagDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrinterDiagDlg dialog


CPrinterDiagDlg::CPrinterDiagDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrinterDiagDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrinterDiagDlg)
	//}}AFX_DATA_INIT
}


void CPrinterDiagDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrinterDiagDlg)
	DDX_Control(pDX, IDC_PRINTER_SELECTED, m_printerSelected);
	DDX_Control(pDX, IDC_PRINTER_STATUS, m_printerStatus);
	DDX_Control(pDX, IDC_FORM_FEED, m_formFeed);
	DDX_Control(pDX, IDC_SET_DEFAULTS, m_setDefaults);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrinterDiagDlg, CDialog)
	//{{AFX_MSG_MAP(CPrinterDiagDlg)
	ON_CBN_SELCHANGE(IDC_PRINTER_SELECTED, OnSelchangePrinterSelected)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrinterDiagDlg message handlers

BEGIN_EVENTSINK_MAP(CPrinterDiagDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CPrinterDiagDlg)
	ON_EVENT(CPrinterDiagDlg, IDC_CLOSE_PRINTER_DIAGNOSTICS, -600 /* Click */, OnClickClosePrinterDiagnostics, VTS_NONE)
	ON_EVENT(CPrinterDiagDlg, IDC_SET_DEFAULTS, -600 /* Click */, OnClickSetDefaults, VTS_NONE)
	ON_EVENT(CPrinterDiagDlg, IDC_FORM_FEED, -600 /* Click */, OnClickFormFeed, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnInitDialog
//
//	Description:
//		Set up the dialog for initial display
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

BOOL CPrinterDiagDlg::OnInitDialog() 
{
	// base class call
	CDialog::OnInitDialog();

	// put the valid printers in the combobox
	DisplayList();

	// select the first printer in the list
	m_printerSelected.SetCurSel(0);

	// get the text of the current selection
	CString	csSelectedPrinter;
	m_printerSelected.GetLBText(0,csSelectedPrinter);

	// get initial printer status, only one if will be true
	CString	csPrinterStatus;

	if (csSelectedPrinter == "Front Downstream Printer")
	{
		if (m_poPrinterControl->GetEnable())
			csPrinterStatus = m_poPrinterControl->GetStatusString();
		else
			csPrinterStatus.LoadString(IDS_PRINTER_DISABLED);
	}

	
	if (csPrinterStatus.IsEmpty())
		csPrinterStatus = "The printer is not responding.";	
	
	// display the retrieved printer status
	m_printerStatus.SetText((LPCTSTR)csPrinterStatus);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickClosePrinterDiagnostics() 
//
//	Description:
//		Closes and cleans up the dialog
//
//	Arguments:
//		none
//
//	Return:
//		void
//
//	Called by:
//		MFC framework on close button click
/////////////////////////////////////////////////////////////////////////////////////

void CPrinterDiagDlg::OnClickClosePrinterDiagnostics() 
{
	// base class EndDialog()
	CDialog::EndDialog(0);		
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnSelchangePrinterSelected() 
//
//	Description:
//		Updates the printer status for the newly selected printer
//
//	Arguments:
//		none
//
//	Return:
//		void
//
//	Called by:
//		MFC framework, when the combobox selection is changed
/////////////////////////////////////////////////////////////////////////////////////

void CPrinterDiagDlg::OnSelchangePrinterSelected() 
{
	CString	csSelectedPrinter,csPrinterStatus;
	
	// get the text of the current selection
	m_printerSelected.GetLBText(m_printerSelected.GetCurSel(),csSelectedPrinter);

	if (csSelectedPrinter == "Front Downstream Printer")
	{
		if (m_poPrinterControl->GetEnable())
			csPrinterStatus = m_poPrinterControl->GetStatusString();
		else
			csPrinterStatus.LoadString(IDS_PRINTER_DISABLED);
	}

	if (csPrinterStatus.IsEmpty())
		csPrinterStatus = "The printer is not responding.";
	
	// display the retrieved printer status
	m_printerStatus.SetText((LPCTSTR)csPrinterStatus);
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickSetDefaults()
//
//	Description:
//		Resets the defaults on the currently selected printer
//
//	Arguments:
//		none
//
//	Return:
//		void
//
//	Called by:
//		MFC framework, on Set Defaults button click
/////////////////////////////////////////////////////////////////////////////////////

void CPrinterDiagDlg::OnClickSetDefaults() 
{
	// the error message we may need to display
	CString	csErrorMessage;
	csErrorMessage.LoadString(IDS_PRINTER_DISABLED);
	
	// disable the button
	m_setDefaults.SetEnabled(FALSE);
	
	// get the current selected printer
	CString csSelectedPrinter;
	m_printerSelected.GetLBText(m_printerSelected.GetCurSel(),csSelectedPrinter);

	
	if (csSelectedPrinter == "Front Downstream Printer")
	{
		if (m_poPrinterControl->GetEnable())
			m_poPrinterControl->SetDefaults();
		else
			AfxMessageBox(csErrorMessage);
	}


	// enable the button
	m_setDefaults.SetEnabled(TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickFormFeed() 
//
//	Description:
//		Sends a form feed to the selected printer
//
//	Arguments:
//		none
//
//	Return:
//		void
//
//	Called by:
//		MFC framework, on form feed button click
/////////////////////////////////////////////////////////////////////////////////////

void CPrinterDiagDlg::OnClickFormFeed() 
{
	// the error message we may need to display
	CString	csErrorMessage;
	csErrorMessage.LoadString(IDS_PRINTER_DISABLED);

	// get the current selected printer
	CString csSelectedPrinter;
	m_printerSelected.GetLBText(m_printerSelected.GetCurSel(),csSelectedPrinter);

	// send form feed to the correct printer
	
	if (csSelectedPrinter == "Front Downstream Printer")
	{
		if (m_poPrinterControl->GetEnable())
			m_poPrinterControl->FormFeed();
		else
			AfxMessageBox(csErrorMessage);
	}


}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		DisplayList() 
//
//	Description:
//		displays useable printers in the combobox
//
//	Arguments:
//		none
//
//	Return:
//		void
//
//	Called by:
//		OnInitDialog()
/////////////////////////////////////////////////////////////////////////////////////


void CPrinterDiagDlg::DisplayList()
{
	CString
		csTemp,
		csName;

	int
		nIndex;

	// get the printer list from the db
	CDatabase	oDatabase;
	oDatabase.Initialize();
	oDatabase.GetUsablePrinterList(&csTemp);

	nIndex = csTemp.Find ( ";" );    // ";" is the separator of the template names.

	while ( nIndex != -1 )
	{

		// Get name.

		csName = csTemp.Left ( nIndex );

		m_printerSelected.AddString ( csName );

		// Get next name.

		csTemp = csTemp.Right ( csTemp.GetLength() - nIndex - 1 );
		nIndex = csTemp.Find ( ";" );

	}

}
