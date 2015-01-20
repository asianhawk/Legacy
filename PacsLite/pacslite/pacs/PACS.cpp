// PACS.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PACS.h"
#include "PACSDlg.h"
#include "trace.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// Global statisitcs class.

CStatistics g_oStatistics;



/////////////////////////////////////////////////////////////////////////////
// CPACSApp

BEGIN_MESSAGE_MAP(CPACSApp, CWinApp)
	//{{AFX_MSG_MAP(CPACSApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPACSApp construction

CPACSApp::CPACSApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPACSApp object

CPACSApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPACSApp initialization

BOOL CPACSApp::InitInstance()
{


	
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif


	
	// Parse the command line to see if launched as OLE server
	if (RunEmbedded() || RunAutomated())
	{
		// Register all OLE server (factories) as running.  This enables the
		//  OLE libraries to create objects from other applications.
		COleTemplateServer::RegisterAll();
	}
	else
	{
		// When a server application is launched stand-alone, it is a good idea
		//  to update the system registry in case it has been damaged.
		COleObjectFactory::UpdateRegistryAll();
	}

	CPACSDlg dlg;
	m_pMainWnd = &dlg;

	
	CWnd *pWnd=CWnd::FindWindow(NULL,"Printing Automation Control System");

	if (pWnd)
	{	
		// already running, activate it
		pWnd->SetForegroundWindow();
	}
	else
	{
		TraceStart("c:\\computype\\database\\tracesettings.txt");

		int nResponse = dlg.DoModal();

	
		if (nResponse == IDOK)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with OK
		}
		else if (nResponse == IDCANCEL)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with Cancel
		}
		TraceStop();

	}
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.

	return FALSE;
}


