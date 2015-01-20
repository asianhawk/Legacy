// PACSDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PACS.h"
#include "PACSDlg.h"
#include "Utilities.h"
#include "SetupDlg.h"
#include "Password.h"
#include "RunDialog.h"
#include "DBLabelSelectionDlg.h"
#include "InternalSetupDlg.h"
#include "DiagDlg.h"
#include "StartupErrorsDlg.h"
#include "PlacementSetupDlg.h"

#include "process.h"
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT




	

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPACSDlg dialog

IMPLEMENT_DYNAMIC(CPACSDlg, CDialog);

CPACSDlg::CPACSDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPACSDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPACSDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
	m_bNoPower=FALSE;

	m_lLabelCount = 0;
	m_lPanelCount = 0;
	m_bError = FALSE;
	m_csCurrentJob = "";
	m_bNoPower = FALSE;
	m_csJobArray.SetSize(100,5);




}

CPACSDlg::~CPACSDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
}

void CPACSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPACSDlg)
	DDX_Control(pDX, IDC_PANEL_QUANTITY, m_edtPanelQuantity);
	DDX_Control(pDX, IDC_CMD_PRINT, m_btnTestPrinter);
	DDX_Control(pDX, IDC_CMD_RUN, m_btnRun);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_DATETIME_LABEL, m_lblDateTime);
	DDX_Control(pDX, IDC_CMD_DIAGNOSTICS, m_btnDiagnostics);
	DDX_Control(pDX, IDC_CMD_SETUPSYSTEM, m_btnSetup);
	DDX_Control(pDX, IDC_JOB_NAMES, m_FGJobList);
	DDX_Control(pDX, IDC_JOB_INFO_FG, m_FGJobInfo);
	DDX_Control(pDX, IDC_LABEL_POINTS_FG, m_FGLabelPoints);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPACSDlg, CDialog)
	//{{AFX_MSG_MAP(CPACSDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPACSDlg message handlers




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnInitDialog
//
//	Description:
//		Initialize the system and begin control.
//
//	Arguments:
//		None.
//
//	Return:
//		None.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CPACSDlg::OnInitDialog()
{


	CDialog::OnInitDialog();

	BOOL		bGlobalInit;
	int		nCount;
	CString	csErrorMessage;

//	Initialize Variables

	nCount=0;
	bGlobalInit=FALSE;

	
	
	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	

	// Initialize the system.

	bGlobalInit = m_oApplicatorControl.Initialize();

	if (!bGlobalInit)
	{
		CStartupErrorsDlg		StartupErrors;
		StartupErrors.m_poDatabase = m_oApplicatorControl.GetDatabaseObject();
		StartupErrors.m_poDioController = m_oApplicatorControl.GetDIOObject();
		StartupErrors.m_poPrinterControl = m_oApplicatorControl.GetPrinterObject();
		StartupErrors.m_poScannerControl = m_oApplicatorControl.GetScannerObject();

		StartupErrors.DoModal();
	}

	// Get list of jobs from database and list them.
	
	m_poDatabase = m_oApplicatorControl.GetDatabaseObject();

	if (m_poDatabase->m_bInitialized)
	{

		m_poDatabase->GetJobNames ( &m_csJobArray );	
		ListJobs();
	
		// Default initial job selection to the first one if available.
		nCount = m_csJobArray.GetSize();
		InitJobListGrid();
		if ( nCount > 0 )
		{
			m_nCurrentSelect = 1;
			RefreshDisplay();
		}
	}

	// start with all buttons disabled, except cancel is always true
	m_btnCancel.SetEnabled (TRUE);
	m_btnRun.SetEnabled (FALSE);
	m_btnTestPrinter.SetEnabled (FALSE);
	m_btnSetup.SetEnabled (FALSE);
	m_btnDiagnostics.SetEnabled (FALSE);



	// access setup if database is a available
	if (m_poDatabase->m_bInitialized)
		m_btnSetup.SetEnabled (TRUE);
	

	// Printer test button enabled if PrinterControl is initialized
	m_poPrinterControl = m_oApplicatorControl.GetPrinterObject();
	if (m_poPrinterControl->m_bInitialized)
		m_btnTestPrinter.SetEnabled (TRUE);



	// Diagnostics button enabled if one of the diagnostic subsystems is initialized
	m_poScannerControl = m_oApplicatorControl.GetScannerObject();
	m_poDioController  = m_oApplicatorControl.GetDIOObject();

	m_poDioController->LightsOff();

	if ( m_poPrinterControl->m_bInitialized || 
		  m_poScannerControl->m_bInitialized ||
		  m_poDioController->m_bInitialized )
		m_btnDiagnostics.SetEnabled (TRUE);
	
	// everything initialized, turn on run and manual feed
	if (bGlobalInit)
	{
		m_btnRun.SetEnabled (TRUE);
	}

	// additional check to make sure the job doesn't use invalid printers
	if (!JobHasValidPrinters())
	{
		m_btnRun.SetEnabled (FALSE);
		m_btnTestPrinter.SetEnabled(FALSE);
		csErrorMessage.LoadString(IDS_USE_DISABLED_PRINTER);
		AfxMessageBox(csErrorMessage);
	}

	// Timer for updating date and time.
	SetTimer ( 1001, 1000, NULL );  // time interval is 1 second
	
	// Timer for updating date and time.
	SetTimer ( 1002, 30000, NULL );  // time interval is 1 minute

	// set label indicating either 1-up or 2-up
	if (m_poDatabase->m_bInitialized)
	{
		int		nRescans,nRepicks,nNumberOfNosepieces;
		BOOL	b2up;

		m_poDatabase->GetGeneralAttributes ( &nRescans, &nRepicks, &b2up, &nNumberOfNosepieces );

	}


	return TRUE;  // return TRUE  unless you set the focus to a control
}




void CPACSDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}


void CPACSDlg::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPACSDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPACSDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


BEGIN_EVENTSINK_MAP(CPACSDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CPACSDlg)
	ON_EVENT(CPACSDlg, IDCANCEL, -600 /* Click */, OnClickCancel, VTS_NONE)
	ON_EVENT(CPACSDlg, IDC_CMD_PRINT, -600 /* Click */, OnClickCmdPrint, VTS_NONE)
	ON_EVENT(CPACSDlg, IDC_CMD_RUN, -600 /* Click */, OnClickCmdRun, VTS_NONE)
	ON_EVENT(CPACSDlg, IDC_CMD_SETUPSYSTEM, -600 /* Click */, OnClickCmdSetupSystem, VTS_NONE)
	ON_EVENT(CPACSDlg, IDC_ABOUTBUTTON, -600 /* Click */, OnClickAboutButton, VTS_NONE)
	ON_EVENT(CPACSDlg, IDC_CMD_DIAGNOSTICS, -600 /* Click */, OnClickCmdDiagnostics, VTS_NONE)
	ON_EVENT(CPACSDlg, IDC_JOB_NAMES, 69 /* SelChange */, OnSelChangeJobNames, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()



// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CPACSDlg::OnClose() 
{
	if (CanExit())
		CDialog::OnClose();
}

void CPACSDlg::OnOK() 
{

	m_oApplicatorControl.Reset();

	if (CanExit())
		CDialog::OnOK();
}

void CPACSDlg::OnClickCancel() 
{
	CWaitCursor wait;
	m_oApplicatorControl.Reset();

	CDialog::OnCancel();
	wait.Restore();
}

BOOL CPACSDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickCmdPrint
//
//	Description:
//		Test the connection and output of the selected printers.
//
//	Arguments:
//		None.
//
//	Return:
//		None.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

void CPACSDlg::OnClickCmdPrint() 
{
	CJob	*poJobInfo;
	CLabel	*poLabel;
	int		nLabel;
	int		nLabelCount=0;
	int		nCount;
	// get an instance of the selected job
	poJobInfo = m_oApplicatorControl.SetupJob ( m_csCurrentJob );
	
	// declare the dialog box
	CDBLabelSelectionDlg LabelSelection;
	
	// pass it the job pointer
	LabelSelection.m_poJob = poJobInfo;

	// if we didn't cancel look for the selected labels
	if ( LabelSelection.DoModal() == IDOK )
	{
		// get returned label numbers
		nLabel  = LabelSelection.m_nLabel;
        
		nLabelCount=LabelSelection.m_nLabelCount; 
		// get first label
		poLabel  = poJobInfo->GetLabel(nLabel);
		// get second label if valid
	}
	else
		return;

	// disable button
	m_btnTestPrinter.SetEnabled ( FALSE );

	// if two labels else one label
	for (nCount=0;nCount<nLabelCount;nCount++)
	{
	   m_oApplicatorControl.PrintOneSample(poLabel);
	}

	// enable button
	m_btnTestPrinter.SetEnabled ( TRUE );
}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickCmdRun
//
//	Description:
//		Begin the pick and apply process. The Run dialog box and applicator process
//		now takes control.
//
//	Arguments:
//		None.
//
//	Return:
//		None.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

void CPACSDlg::OnClickCmdRun() 
{

	CString csTemp,
			csMessage;

	long
		lPanelQuantity;

	CUtilities Utility;

	CSNManager *poSNManager;

	CJob		*pJobInfo;
	CRunDialog	*p_dlg_run;
	CLabel *poLabel;				// Pointer to label.

BOOL bScannerActive;


	pJobInfo = m_oApplicatorControl.GetJob();
	
	pJobInfo->SetLabelCount ( m_lLabelCount );
	pJobInfo->SetPanelCount ( m_lPanelCount );
	m_csCurrentJob = pJobInfo->GetJobName ();


	//Need to know if scanner was not enabled at startup
		
	bScannerActive=m_oApplicatorControl.IsScannerActive();


	poLabel = pJobInfo->GetFirstLabel();
	if ( poLabel == NULL )
	{
		csMessage.LoadString ( IDS_ERR_LABEL_LIST );
		AfxMessageBox ( csMessage );
		return;
	}
	while (poLabel !=NULL)
	{

		if ((poLabel->GetEnableScan())&&(!bScannerActive))
		{
			AfxMessageBox ( "This Job Requires An Active Scanner, But None Are Available");
			return;
		}
		poLabel = pJobInfo->GetNextLabel();

	}

	
	// Get quantity.

	m_edtPanelQuantity.GetWindowText ( csTemp );
	m_lPanelQuantity = atoi ( csTemp );

	// Initialize serial number information.


	
	
	poSNManager = m_oApplicatorControl.GetSNManager();
	if ( !poSNManager->Initialize ( m_csCurrentJob, m_poDatabase ) )
		return;

	p_dlg_run = new CRunDialog ( this );

	if (p_dlg_run->Create() ==FALSE)
	{
		csTemp.LoadString ( IDS_CREATE_RUN_ERR );
		AfxMessageBox ( csTemp );
		delete p_dlg_run;
		return;
	}

	p_dlg_run->Initialize ( &m_oApplicatorControl );

	p_dlg_run->ShowWindow(SW_NORMAL);
	Utility.YieldToWindows();
	this->ShowWindow(SW_HIDE);
	Utility.YieldToWindows();

	lPanelQuantity = m_lPanelQuantity;

	if ( p_dlg_run->Run ( &lPanelQuantity ) == TRUE )  // job is finished
		m_bError = FALSE;
	else   // job is interrupted  or the run-time error
		m_bError = TRUE;
		

	// UI code to deal with the form
		
	if ( m_bError == TRUE )  // error return
	{
		
	}
	else   // done
	{
		
		// Job is done so execute any job ending processes.

		m_lPanelQuantity = 0;
	}

	csTemp.Format ( "%d", m_lPanelQuantity );
	m_edtPanelQuantity.SetWindowText ( csTemp );
	

		// clean the run-form 
	this->ShowWindow(SW_NORMAL);
	Utility.YieldToWindows();
	p_dlg_run->ShowWindow(SW_HIDE);
	Utility.YieldToWindows();
	delete p_dlg_run;
	Utility.YieldToWindows();

}


//////////////////////////////////
// job listbox handler.
// Functionality:
// update the job info shown on the screen.
//
//////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		ListJobs
//
//	Description:
//		List all available jobs.
//
//	Arguments:
//		None.
//
//	Return:
//		None.
//
//	Called by:
//		OnInitDialog
//
/////////////////////////////////////////////////////////////////////////////////////

void CPACSDlg::ListJobs ( void ) 
{

	InitJobListGrid();
}





/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickCmdSetupSystem
//
//	Description:
//		Begin the process of manipulating all job and system data.
//
//	Arguments:
//		None.
//
//	Return:
//		None.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

void CPACSDlg::OnClickCmdSetupSystem() 
{

	int
		nPWType;

	CPassword Password;


	nPWType = Password.PasswordClearance ( m_poDatabase );

	// Password clearance is required to change job and system attributes.

	if (  nPWType == SYSTEM_PW )
	{
		// clear any error conditions so RefreshDisplay works
		// and updates anything changed in setup
		m_bError = FALSE;
		
		// get the current job's name
		CString	csJobName;
		csJobName = m_FGJobList.GetData(m_nCurrentSelect, 1);
		
		CSetupDlg Setup;

		Setup.SetDatabaseObject ( m_poDatabase );
		Setup.m_csJobName = csJobName;
		Setup.m_poApplicatorControl = &m_oApplicatorControl;

		Setup.SetPrinterControlObject ( m_oApplicatorControl.GetPrinterObject() );
		Setup.SetScannerControlObject ( m_oApplicatorControl.GetScannerObject() );

		Setup.SetDIOController(m_oApplicatorControl.GetDIOObject());

		Setup.DoModal();

		// update the array with jobs from the database
		m_poDatabase->GetJobNames(&m_csJobArray);

		// add all jobs to the list control
		ListJobs();		
		

		int nIndex = m_FGJobList.FindString(csJobName,1);

		// if the job was deleted, select the first job
		if (nIndex!=LB_ERR)
		{
			m_FGJobList.SetDataCursor(nIndex);
			m_nCurrentSelect = nIndex;
		}
		else
		{
			m_FGJobList.SetDataCursor(1);
			m_nCurrentSelect = 1;
		}
		
		// refresh the other fields based on selected job
		RefreshDisplay();
	}
	else
	{

		if ( nPWType == INTERNAL_PW )
		{

			// Customer service setup parameters.

			CInternalSetupDlg InternalSetup;

			if ( InternalSetup.DoModal() == IDOK )
			{


			}

		}
	}


}



void CPACSDlg::OnTimer(UINT nIDEvent) 
{
	CUtilities Utility;
	CString csDateTime;

	KillTimer(nIDEvent);

	// if we are successfully initialized
	if (m_oApplicatorControl.m_bInitialized)
	{
		// get the dio controller object
		CDioController *poDIOControl;
		poDIOControl = m_oApplicatorControl.GetDIOObject();

	
		
		if (m_bNoPower)
		{

		   // refresh the inputs
 		      poDIOControl->ReadSystemInputs();

			// refresh the inputs
			if (poDIOControl->IsPowerOn())
			{
				m_bNoPower = FALSE;
				m_btnRun.SetEnabled(TRUE);
				m_poDioController->ErrorBitOff(); 
			}

		}
		else
		{
 		    poDIOControl->ReadSystemInputs();

			if (!m_oApplicatorControl.m_bRequestHold)
			{

/*				if (!poDIOControl->IsPowerOn())		// This bit is now used to detect errors from
													//  the LAP4100
				{
		  		  m_bNoPower = TRUE;
				  m_btnRun.SetEnabled(FALSE);

				  AfxMessageBox("A LAP4100 PLC - Error ");
				  m_poDioController->ErrorBitOn();
				  m_poDioController->ApplicatorReadyBitOff(); 

				}
*/
			}
		}
	}


	if ( nIDEvent == 1001 )
	{

		csDateTime = Utility.GetDateTime();
		m_lblDateTime.SetCaption ( csDateTime );
		SetTimer ( nIDEvent, 1000, NULL );

	}
	
	if ( nIDEvent == 1002 )
	{
		g_oStatistics.SetTimeToUpdate ( TRUE );
  	    SetTimer ( 1002, 60000, NULL );  // time interval is 1 minute

	}

	CDialog::OnTimer(nIDEvent);
}

void CPACSDlg::OnClickAboutButton() 
{

	CAboutDlg AboutBox;

	AboutBox.DoModal();

}


void CPACSDlg::OnClickCmdDiagnostics() 
{
	CPassword Password;
	int nPWType;

	nPWType = Password.PasswordClearance ( m_poDatabase );

	// Password clearance is required to change job and system attributes.

	if (  nPWType == SYSTEM_PW )
	{
		// clear any error conditions so RefreshDisplay works
		// and updates anything changed in setup
		m_bError = FALSE;


		// declare the dialog object
		CDiagDlg Diagnostics(this);

	// get and pass along pointers to the controller objects
		Diagnostics.m_poPrinterControl = m_oApplicatorControl.GetPrinterObject();
		Diagnostics.m_poScannerControl = m_oApplicatorControl.GetScannerObject();
		Diagnostics.m_poDIOController = m_oApplicatorControl.GetDIOObject();

		// launch the dialog
		Diagnostics.DoModal();
	}
}



void CPACSDlg::RefreshDisplay() 
{

	CString csJobName;
	CString csMessage;


	csJobName = m_FGJobList.GetData(m_nCurrentSelect, 1);

	// Check if selecting a new job and old job is not done.

	if ( m_bError )
	{
		if ( csJobName != m_csCurrentJob)
		{

			csMessage = "The job " + m_csCurrentJob + 
				         " has not completed. Do you wish to run a new job?";
			if ( IDYES == AfxMessageBox ( csMessage, MB_YESNO ) )
			{

				m_bError = FALSE;
			}
			else
				return;
		}
		else
			return;
	}


	m_csCurrentJob = csJobName;

	InitLabelPointGrid();
	ResetLabelPointGrid(csJobName);

	InitJobInfoGrid();


}


BOOL CPACSDlg::PeekAndPump()
{
	MSG msg;

	while (::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE))
	{
		if (!AfxGetThread()->PumpMessage())
			return (TRUE);
	}

	return (TRUE);
}

BOOL CPACSDlg::HomeAfterPowerRestore()
{
	// enable the two buttons set flag to false
	m_btnRun.SetEnabled(TRUE);
	m_bNoPower = FALSE;

	return (TRUE);
}

BOOL CPACSDlg::JobHasValidPrinters()
{
	CJob		*poJob;
	CString	csAttributes;
	
	// get the job's placement attributes
	poJob = m_oApplicatorControl.GetJob();
	csAttributes = poJob->GetPlacementAttributes();

	// find FRONT_DOWNSTREAM_PRINTER
	if (csAttributes.Find("Front_Downstream")!=-1)
	{
		if (!m_poPrinterControl->GetEnable())
			return FALSE;
	}
	return TRUE;
}

void CPACSDlg::InitJobListGrid()
{

	m_FGJobList.InitFlexGrid(10,3);
	m_FGJobList.AddColumnHeaders("Job #");
	m_FGJobList.AddColumnHeaders("Job Name     ");
	m_FGJobList.AddColumnHeaders("Job Description          ");

	AddJobsToFlexGrid();
}



void CPACSDlg::AddJobsToFlexGrid()
{

	int nCount;
	int i;
	char buffer[5];

	CString csTemp;
	COleVariant ii;


	nCount = m_csJobArray.GetSize();

	
	if ( nCount > 0 )
	{
		// List descriptions of all jobs.

		for ( i = 0; i < nCount; i++ )

		{
			csTemp = CString(_itoa(i+1,buffer,10)) + CString("\t") +  m_csJobArray[i];
			ii= long(i+1);
			m_FGJobList.AddItem(csTemp, ii);
			
		}
	}

}


void CPACSDlg::OnSelChangeJobNames() 
{
	CString		csErrorMessage;
	
	m_nCurrentSelect = m_FGJobList.GetRowSel();
	RefreshDisplay();

	// Reset counters for run.
	m_lLabelCount = 0;
	m_lPanelCount = 0;

	// cancel is always true
	m_btnCancel.SetEnabled ( TRUE );

	// access setup if database is a available
	if (m_poDatabase->m_bInitialized)
		m_btnSetup.SetEnabled(TRUE);
	else
		m_btnSetup.SetEnabled(FALSE);
	

	// Printer test button enabled if PrinterControl is initialized
	m_poPrinterControl = m_oApplicatorControl.GetPrinterObject();
	if (m_poPrinterControl->m_bInitialized)
		m_btnTestPrinter.SetEnabled(TRUE);
	else
		m_btnTestPrinter.SetEnabled(FALSE);	

	// determine whether to enable or disable diagnostics
	if ( m_poPrinterControl->m_bInitialized || 
		  m_poScannerControl->m_bInitialized ||
		  m_poDioController->m_bInitialized )
		m_btnDiagnostics.SetEnabled (TRUE);	
	else
		m_btnDiagnostics.SetEnabled (FALSE);

	// determine whether to enable or disable run and manual feed
	if (m_oApplicatorControl.m_bInitialized)
	{
		m_btnRun.SetEnabled (TRUE);
	}
	else
	{
		m_btnRun.SetEnabled (FALSE);
	}

	// additional check to make sure the job doesn't use invalid printers	
	if (!JobHasValidPrinters())
	{
		m_btnRun.SetEnabled (FALSE);
		m_btnTestPrinter.SetEnabled(FALSE);
		csErrorMessage.LoadString(IDS_USE_DISABLED_PRINTER);
		AfxMessageBox(csErrorMessage);
	}


	m_bJobSelected = TRUE;	
	
}


void CPACSDlg::InitJobInfoGrid()
{

	m_FGJobInfo.InitFlexGrid(25,2);
	m_FGJobInfo.AddColumnHeaders("Description    ");
	m_FGJobInfo.AddColumnHeaders("Value                  ");

	

	AddJobInfoToFlexGrid();
//	m_FGJobInfo.CreateChkBoxes(3, 1);
	m_FGJobInfo.SetAllowEditing(true);



}

void CPACSDlg::AddJobInfoToFlexGrid()
{
CJob *pJobInfo;
long nItem;
CString csTemp;
CString csBuffer;
COleVariant nVar;
CDatabase oDatabase;

	oDatabase.Initialize();

	nItem=1;

	if (m_csCurrentJob!="") 
	{
		pJobInfo = m_oApplicatorControl.SetupJob ( m_csCurrentJob );

		if (pJobInfo->GetUseDataName1())
		{
			csTemp =
				oDatabase.GetDisplayedValue(pJobInfo->GetDataName1(),
											   pJobInfo->GetDataValue1());
			nVar=(long)nItem;
			m_FGJobInfo.AddItem(csTemp,nVar);
			nItem+=1;
		}

		if (pJobInfo->GetUseDataName2())
		{
			csTemp =
				oDatabase.GetDisplayedValue(pJobInfo->GetDataName2(),
											   pJobInfo->GetDataValue2());
			nVar=(long)nItem;
			m_FGJobInfo.AddItem(csTemp,nVar);
			nItem+=1;
		}

		if (pJobInfo->GetUseDataName3())
		{
			csTemp =
				oDatabase.GetDisplayedValue(pJobInfo->GetDataName3(),
											   pJobInfo->GetDataValue3());
			nVar=(long)nItem;
			m_FGJobInfo.AddItem(csTemp,nVar);
			nItem+=1;
		}

		if (pJobInfo->GetUseDataName4())
		{
			csTemp =
				oDatabase.GetDisplayedValue(pJobInfo->GetDataName4(),
											   pJobInfo->GetDataValue4());
			nVar=(long)nItem;
			m_FGJobInfo.AddItem(csTemp,nVar);
			nItem+=1;
		}

		if (pJobInfo->GetUseDataName5())
		{
			csTemp =
				oDatabase.GetDisplayedValue(pJobInfo->GetDataName5(),
											   pJobInfo->GetDataValue5());
			nVar=(long)nItem;
			m_FGJobInfo.AddItem(csTemp,nVar);
			nItem+=1;
		}

	}




}


void CPACSDlg::InitLabelPointGrid()
{

	m_FGLabelPoints.InitFlexGrid(10,3);
	m_FGLabelPoints.AddColumnHeaders(" Template ");
	m_FGLabelPoints.AddColumnHeaders(" Printer  ");
	m_FGLabelPoints.AddColumnHeaders("Scan Labels  ");
}


void CPACSDlg::ResetLabelPointGrid(CString csJobName)
{
CJob *pJobInfo;
CString csTemp,
		csInfo,
		csLabelPoints;

int nPos,
	nLength,
	nIndex,
	nLabelPointCount;

COleVariant ii;

	pJobInfo = m_oApplicatorControl.SetupJob ( csJobName );
	csTemp = pJobInfo->GetPlacementAttributes();
	
	nPos = csTemp.Find (";");    // ";" is the separator of the location points

	// Just display the placement locations.

	nLabelPointCount=1;
	csLabelPoints="";
	while ( nPos != -1 )
	{


		csInfo = csTemp.Left( nPos + 1 );
		nIndex = csInfo.Find ( "," );
		if ( nIndex == -1 )
		{
			csTemp.LoadString ( IDS_INVALID_LABEL_ATT );
			AfxMessageBox ( csTemp );
			return;
		}
		csLabelPoints+=csInfo.Left ( nIndex )+"\t";

		// Get Y position.

		nLength = csInfo.GetLength();
		csInfo = csInfo.Right ( nLength - nIndex - 1 );
		nIndex = csInfo.Find ( "," );
		if ( nIndex == -1 )
		{
			csTemp.LoadString ( IDS_INVALID_LABEL_ATT );
			AfxMessageBox ( csTemp );
			return;
		}
		csLabelPoints+=csInfo.Left ( nIndex )+"\t";

		// Get rotation.

		nLength = csInfo.GetLength();
		csInfo = csInfo.Right ( nLength - nIndex - 1 );
		nIndex = csInfo.Find ( ";" );
		if ( nIndex == -1 )
		{
			csTemp.LoadString ( IDS_INVALID_LABEL_ATT );
			AfxMessageBox ( csTemp );
			return;
		}
		csLabelPoints+=csInfo.Left ( nIndex );

		ii=  (long) nLabelPointCount;
		nLabelPointCount+=1;
		m_FGLabelPoints.AddItem(csLabelPoints,ii);
		csLabelPoints="";

		csTemp = csTemp.Right ( csTemp.GetLength() - nPos -1 );
		nPos = csTemp.Find (";");
	}


}



