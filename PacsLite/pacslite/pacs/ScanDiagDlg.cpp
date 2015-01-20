// ScanDiagDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pacs.h"
#include "ScanDiagDlg.h"
#include "DioDlg.h"
#include "definitions.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// global used to communicate between main and worker threads
threadCom	g_sThreadCommunication;

/////////////////////////////////////////////////////////////////////////////
// CScanDiagDlg dialog


CScanDiagDlg::CScanDiagDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScanDiagDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScanDiagDlg)
	m_resetString = _T("");
	//}}AFX_DATA_INIT
}


void CScanDiagDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScanDiagDlg)
	DDX_Control(pDX, IDC_SELECTED_SCANNER, m_selectedScanner);
	DDX_Control(pDX, IDC_VERSION_STRING, m_versionString);
	DDX_Control(pDX, IDC_SCAN_RESULTS, m_returnText);
	DDX_Text(pDX, IDC_RESET_STRING, m_resetString);
	DDX_Control(pDX, IDC_CONTINUOUS_TRIGGER, m_continuousTrigger);
	DDX_Control(pDX, IDC_SINGLE_TRIGGER, m_singleTrigger);
	DDX_Control(pDX, IDC_CLOSE_SCANNER_DIAGNOSTICS, m_closeButton);
	DDX_Control(pDX, IDC_SET_RESET_STRING, m_setResetString);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScanDiagDlg, CDialog)
	//{{AFX_MSG_MAP(CScanDiagDlg)
	ON_CBN_SELCHANGE(IDC_SELECTED_SCANNER, OnSelchangeSelectedScanner)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SCANNERDLGTHREADMESSAGE,OnThreadMessage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScanDiagDlg message handlers

BEGIN_EVENTSINK_MAP(CScanDiagDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CScanDiagDlg)
	ON_EVENT(CScanDiagDlg, IDC_CLOSE_SCANNER_DIAGNOSTICS, -600 /* Click */, OnClickCloseScannerDiagnostics, VTS_NONE)
	ON_EVENT(CScanDiagDlg, IDC_SINGLE_TRIGGER, -600 /* Click */, OnClickSingleTrigger, VTS_NONE)
	ON_EVENT(CScanDiagDlg, IDC_CONTINUOUS_TRIGGER, -600 /* Click */, OnClickContinuousTrigger, VTS_NONE)
	ON_EVENT(CScanDiagDlg, IDC_SET_RESET_STRING, -600 /* Click */, OnClickSetResetString, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnInitDialog
//
//	Description:
//		function to initialize dialog box
//
//	Arguments:
//		none
//	Return:
//		BOOL - true
//
//	Called by:
//		MFC Framework
/////////////////////////////////////////////////////////////////////////////////////

BOOL CScanDiagDlg::OnInitDialog() 
{
	// run base class method
	CDialog::OnInitDialog();
	
	// add selections to the combobox
	if (m_poScannerControl->GetUse())
	{
		m_selectedScanner.AddString("Placement scanner");
		m_placementScannerReset = m_poScannerControl->GetResetString();
	}

	// select the first index of the combobox
	m_selectedScanner.SetCurSel(0);

	// get the text of the current selection
	CString	csSelectedScanner;
	m_selectedScanner.GetLBText(0,csSelectedScanner);

	// declare and empty version string object
	CString csVersion;
	csVersion.Empty();
	
	// only one scanner will be selected, use it to get version + reset strings
	if (csSelectedScanner == "Placement scanner")
	{
		csVersion = m_poScannerControl->GetVersionString();
		m_resetString = m_poScannerControl->GetResetString();
	}

	// check for no response
	if (csVersion.IsEmpty())
		csVersion = "The scanner is not responding.";
	if (m_resetString.IsEmpty())
		m_resetString = "The scanner is not responding.";

	// set version text, use update data to display reset string
	m_versionString.SetText((LPCTSTR)csVersion);
	UpdateData(FALSE);

	// reset returned text
	m_returnText.SetText("");
	
	// thread doesn't live until press continuous scan
	g_sThreadCommunication.bThreadLives = FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickCloseScannerDiagnostics
//
//	Description:
//		closes and cleans up dialog box
//
//	Arguments:
//		none
//	Return:
//		void
//
//	Called by:
//		MFC Framework on button click
/////////////////////////////////////////////////////////////////////////////////////

void CScanDiagDlg::OnClickCloseScannerDiagnostics() 
{
	// set back to the original reset strings
	if (m_poScannerControl->GetUse())
	{
		m_poScannerControl->SetResetString(m_placementScannerReset);
		m_poScannerControl->Reset();
	}

	// call base class EndDialog	
	CDialog::EndDialog(0);
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickSingleTrigger()
//
//	Description:
//		Single trigger for the selected scanner
//
//	Arguments:
//		none
//	Return:
//		void
//
//	Called by:
//		MFC Framework on button click
/////////////////////////////////////////////////////////////////////////////////////

void CScanDiagDlg::OnClickSingleTrigger() 
{
	// get the text of the current selection
	CString	csSelectedScanner,csTempText;
	m_selectedScanner.GetLBText(m_selectedScanner.GetCurSel(),csSelectedScanner);

	// figure out which scanner to call single trigger on
	CString csScanReturn;
	// if using placement scanner	
	if (csSelectedScanner == "Placement scanner")
		csScanReturn = m_poScannerControl->SingleTrigger();
	// if using system scanner
	
	// get current results text
	CString csCurrentText = m_returnText.GetText();

	// if no current results scanned text else add scanned text
	if (csCurrentText.IsEmpty())
	{
		csTempText = csScanReturn + '\n';
		m_returnText.SetText(csTempText);
	}
	else
	{
		csTempText = csCurrentText + csScanReturn;
		csTempText = csTempText + '\n';
		m_returnText.SetText(csTempText);
	}
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickContinuousTrigger()
//
//	Description:
//		Continuous trigger for the selected scanner
//
//	Arguments:
//		none
//	Return:
//		void
//
//	Called by:
//		MFC Framework on button click
/////////////////////////////////////////////////////////////////////////////////////

void CScanDiagDlg::OnClickContinuousTrigger() 
{
	// if we are in continuous trigger
	if (g_sThreadCommunication.bThreadLives)
	{
		// set global boolean, thread is dead
		g_sThreadCommunication.bThreadLives = FALSE;
		// wait for the thread to die
		WaitForSingleObject(m_myThread->m_hThread,INFINITE);
		// update button caption
		m_continuousTrigger.SetCaption("Continuous Trigger");
		// continuous trigger is stopped, enabled other buttons
		m_closeButton.SetEnabled(TRUE);
		m_setResetString.SetEnabled(TRUE);
		m_singleTrigger.SetEnabled(TRUE);
		m_selectedScanner.EnableWindow(TRUE);
	}
	else
	{
		// you must stop continuous trigger before anything else
		m_closeButton.SetEnabled(FALSE);
		m_setResetString.SetEnabled(FALSE);
		m_singleTrigger.SetEnabled(FALSE);
		m_selectedScanner.EnableWindow(FALSE);
		// update button caption
		m_continuousTrigger.SetCaption("Stop Continuous Trigger");
		// set global boolean, thread is alive
		g_sThreadCommunication.bThreadLives = TRUE;
		// spawn the thread to continuously trigger the scanner
		m_myThread = AfxBeginThread(ScannerThreadFunction,this,THREAD_PRIORITY_BELOW_NORMAL);
	}	
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickSetResetString()
//
//	Description:
//		Sets the reset string for the current scanner
//
//	Arguments:
//		none
//	Return:
//		void
//
//	Called by:
//		MFC Framework on button click
/////////////////////////////////////////////////////////////////////////////////////

void CScanDiagDlg::OnClickSetResetString() 
{
	// retrieve current value of m_resetString from control
	UpdateData(TRUE);
	
	// get the text of the current selection
	CString	csSelectedScanner;
	m_selectedScanner.GetLBText(m_selectedScanner.GetCurSel(),csSelectedScanner);

	// if using placement scanner
	if (csSelectedScanner == "Placement scanner")
	{
		m_poScannerControl->SetResetString(m_resetString);
		m_poScannerControl->Reset();
	}
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnSelchangeSelectedScanner() 
//
//	Description:
//		Update version and reset string after changing selected scanner
//
//	Arguments:
//		none
//	Return:
//		void
//
//	Called by:
//		MFC framework after change selected in combobox
/////////////////////////////////////////////////////////////////////////////////////

void CScanDiagDlg::OnSelchangeSelectedScanner() 
{
	// get the text of the current selection
	CString	csSelectedScanner;
	m_selectedScanner.GetLBText(m_selectedScanner.GetCurSel(),csSelectedScanner);

	// declare and empty version string object
	CString csVersion;
	csVersion.Empty();
	
	// only one scanner will be selected, use it to get version + reset strings
	if (csSelectedScanner == "Placement scanner")
	{
		csVersion = m_poScannerControl->GetVersionString();
		m_resetString = m_poScannerControl->GetResetString();
	}
	// check for no response
	if (csVersion.IsEmpty())
		csVersion = "The scanner is not responding.";	
	if (m_resetString.IsEmpty())
		m_resetString = "The scanner is not responding.";

	// set version text, use update data to display reset string
	m_versionString.SetText((LPCTSTR)csVersion);
	UpdateData(FALSE);

	// reset returned text
	m_returnText.SetText("");	
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnThreadMessage
//
//	Description:
//		Dialog response to thread telling it to update
//
//	Arguments:
//		wParam, lParam unused
//	Return:
//		void
//
//	Called by:
//		ScannerThreadFunction via ::PostMessage
/////////////////////////////////////////////////////////////////////////////////////

void CScanDiagDlg::OnThreadMessage(WPARAM wParam, LPARAM lParam)
{
	// current and new text
	CString csCurrentText;

	// get the current text
	csCurrentText = m_returnText.GetText();


	if (csCurrentText.IsEmpty())
		m_returnText.SetText(g_sThreadCommunication.csReturnScan);
	else
	{
		csCurrentText = csCurrentText + g_sThreadCommunication.csReturnScan;
		csCurrentText = csCurrentText + '\n';
		m_returnText.SetText(csCurrentText);
	}

	// focus to the control
	m_returnText.SetFocus();
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		ScannerThreadFunction
//
//	Description:
//		worker thread to execute continuous scanner trigger
//
//	Arguments:
//		LPVOID *p_dialog: cast thread owner
//	Return:
//		UINT always zero
//
//	Called by:
//		CScannerDiagnosticsDlg::OnClickContinuousTrigger via AfxBeginThread
/////////////////////////////////////////////////////////////////////////////////////

UINT ScannerThreadFunction (LPVOID pParam)
{
	CScanDiagDlg *theDialog;

	// correctly cast the parameter
	theDialog = (CScanDiagDlg *) pParam;

	// get safe handle to post the message to
	HWND MessageTarget = theDialog->GetSafeHwnd();
	
	// while the dialog hasn't killed us
	while (g_sThreadCommunication.bThreadLives)
	{
		// get the text of the current selection
		CString	csSelectedScanner;
		theDialog->m_selectedScanner.GetLBText(theDialog->m_selectedScanner.GetCurSel(),csSelectedScanner);
		
		g_sThreadCommunication.csReturnScan = theDialog->m_poScannerControl->SingleTrigger();
				
		// post the message to update the dialog
		::PostMessage(MessageTarget,WM_SCANNERDLGTHREADMESSAGE,0,0);

		// wait for message to be posted and used
		Sleep(600);
	}

	// we've been killed time to leave
	return (0);
}
