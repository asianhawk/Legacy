// SetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PACS.h"
#include "Database.h"
//#include "SystemSetupDlg.h"
#include "ScannerSetupDlg.h"
#include "ChangePasswordDlg.h"
#include "PrinterSetupDlg.h"
#include "AddEditJobDlg.h"
#include "DeleteJobDlg.h"
#include "TemplateSetupDlg.h"
#include "SetupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog


CSetupDlg::CSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetupDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CSetupDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg message handlers

BEGIN_EVENTSINK_MAP(CSetupDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CSetupDlg)
	ON_EVENT(CSetupDlg, IDC_CMD_CHANGEPW, -600 /* Click */, OnClickCmdChangePassword, VTS_NONE)
	ON_EVENT(CSetupDlg, IDC_CMD_EDITJOB, -600 /* Click */, OnClickCmdEditJob, VTS_NONE)
	ON_EVENT(CSetupDlg, IDC_CMD_PRINTERSETUP, -600 /* Click */, OnClickCmdPrinterSetup, VTS_NONE)
	ON_EVENT(CSetupDlg, IDOK, -600 /* Click */, OnClickOk, VTS_NONE)
	ON_EVENT(CSetupDlg, IDC_CMD_SCANNERSETUP, -600 /* Click */, OnClickCmdScannerSetup, VTS_NONE)
	ON_EVENT(CSetupDlg, IDC_CMD_DELETEJOB, -600 /* Click */, OnClickCmdDeleteJob, VTS_NONE)
	ON_EVENT(CSetupDlg, IDC_TEMPLATE_SETUP, -600 /* Click */, OnClickTemplateSetup, VTS_NONE)
	ON_EVENT(CSetupDlg, IDC_CMD_WYSIWYG, -600 /* Click */, OnClickCmdWysiwyg, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetDatabaseObject
//
//	Description:
//		Sets the pointer to the database object
//
//	Arguments:
//		CDatabase *poDatabase
//
//	Return:
//		None.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

void CSetupDlg::SetDatabaseObject ( CDatabase *poDatabase )
{
	m_poDatabase = poDatabase;
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetPrinterControlObject
//
//	Description:
//		Set the pointer to the Printer Control Object
//
//	Arguments:
//		CPrinterControl *poPrinterControl
//
//	Return:
//		None.
//
//	Called by:
//		CPacsDlg before launching SetupDlg
/////////////////////////////////////////////////////////////////////////////////////

void CSetupDlg::SetPrinterControlObject ( CPrinterControl *poPrinterControl )
{
	m_poPrinterControl = poPrinterControl;
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetScannerControlObject
//
//	Description:
//		Set the pointer to the Scanner Control Object
//
//	Arguments:
//		CScannerControl *poScannerControl
//
//	Return:
//		None.
//
//	Called by:
//		CPacsDlg before launching SetupDlg
/////////////////////////////////////////////////////////////////////////////////////

void CSetupDlg::SetScannerControlObject ( CScannerControl *poScannerControl )
{
	m_poScannerControl = poScannerControl;
}






/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetDIOController
//
//	Description:
//		Set the pointer to the DIO Controll Class
//
//	Arguments:
//		CDioController *poDioController
//
//	Return:
//		None.
//
//	Called by:
//		CPacsDlg before launching SetupDlg
/////////////////////////////////////////////////////////////////////////////////////

void CSetupDlg::SetDIOController ( CDioController *poDioController )
{
	m_poDioController = poDioController;
}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickCmdChangePassword
//
//	Description:
//		Initialize and run the password change dialog box. Save accepted changes.
//
//	Arguments:
//		None.
//
//	Return:
//		None.
//
//	Called by:
//		Framework
/////////////////////////////////////////////////////////////////////////////////////

void CSetupDlg::OnClickCmdChangePassword() 
{

	CChangePasswordDlg ChangePassword;

	if ( ChangePassword.DoModal() == IDOK )
	{
		// Update the database.
		m_poDatabase->SetPassword ( ChangePassword.m_csPassword );
	}
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickCmdPrinterSetup
//
//	Description:
//		Initialize and run the printer setup dialog box. Save accepted changes.
//
//	Arguments:
//		None.
//
//	Return:
//		None.
//
//	Called by:
//		Framework
/////////////////////////////////////////////////////////////////////////////////////

void CSetupDlg::OnClickCmdPrinterSetup() 
{

	CString
		csTemp;

	CPrinterSetupDlg PrinterSetup;

	




	
	// set pointers to database and printer control

	PrinterSetup.DoModal();

	// Get the latest printer attributes for the current printers.

	if ( !m_poPrinterControl->UpdatePrinterAttributes ( m_poDatabase ) )
	{
	
		csTemp.LoadString ( IDS_ERR_PRINTER_REFRESH );
		AfxMessageBox ( csTemp );

	}
}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickOK
//
//	Description:
//		Closes setup dialog box
//
//	Arguments:
//		None.
//
//	Return:
//		None.
//
//	Called by:
//		Framework
/////////////////////////////////////////////////////////////////////////////////////

void CSetupDlg::OnClickOk() 
{
	CDialog::OnOK();	
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickCmdScannerSetup
//
//	Description:
//		Initialize and run the scanner setup dialog box. Save accepted changes.
//
//	Arguments:
//		None.
//
//	Return:
//		None.
//
//	Called by:
//		Framework
/////////////////////////////////////////////////////////////////////////////////////

void CSetupDlg::OnClickCmdScannerSetup() 
{
	// Scanner attributes.
	BOOL bUse;
	BOOL bEnable;
	CString csReset;
	CString csTriggerON;
	CString csTriggerOFF;
	CString csTemp;
	int nType;

	CScannerSetupDlg ScannerSetup;


	// Get placement scanner database information.
	if ( !m_poDatabase->GetScannerAttributes ( "Placement_Scanner", 
															 &bUse,
															 &bEnable,
															 &nType,
															 &csTriggerON,
															 &csTriggerOFF,
															 &csReset ) )
		return;

	ScannerSetup.m_csPlacementInitialization = csReset;
	ScannerSetup.m_bUsePlacementScanner      = bUse;
	ScannerSetup.m_bEnablePlacementScanner   = bEnable;
	ScannerSetup.m_nPlacementScannerType     = nType;
	ScannerSetup.m_csPlacementTrigger        = csTriggerON;
	ScannerSetup.m_csPlacementTriggerOff	 = csTriggerOFF;


	// Get system scanner database information.
	if ( !m_poDatabase->GetScannerAttributes ( "System_Scanner", 
															 &bUse,
															 &bEnable,
															 &nType,
															 &csTriggerON,
															 &csTriggerOFF,
															 &csReset ) )
		return;


	if ( ScannerSetup.DoModal() == IDOK )
	{
		// Set placement scanner database information.
		csReset   = ScannerSetup.m_csPlacementInitialization;
		bUse      = ScannerSetup.m_bUsePlacementScanner;
		bEnable   = ScannerSetup.m_bEnablePlacementScanner;
		nType     = ScannerSetup.m_nPlacementScannerType;
		csTriggerON = ScannerSetup.m_csPlacementTrigger;
		csTriggerOFF= ScannerSetup.m_csPlacementTriggerOff;


		if ( !m_poDatabase->SetScannerAttributes ( "Placement_Scanner", 
																 bUse,
																 bEnable,
																 nType,
																 csTriggerON,
																 csTriggerOFF,
																 csReset ) )
			return;

		// Update the information for the current placement scanner object.
		if ( bUse )
		{
			if ( !m_poScannerControl->UpdateScannerAttributes (  bUse,
																 bEnable,
																 nType,
																 csTriggerON,
																 csReset ) )
			{
				csTemp.LoadString ( IDS_SCANNER_UPDATE_ERR );
				AfxMessageBox ( csTemp );
				return;
			}
		}

	}
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickCmdEditJob
//		
//
//	Description:
//		Add/Edit a Job
//
//	Arguments:
//		None.
//
//	Return:
//		None.
//
//	Called by:
//		Framework
/////////////////////////////////////////////////////////////////////////////////////

void CSetupDlg::OnClickCmdEditJob() 
{
	CAddEditJobDlg	EditJob;

	// initialize the job edit dialog box
	EditJob.m_poDatabase = m_poDatabase;
	EditJob.m_csJobName = m_csJobName;

	// launch the job edit dialog box
	EditJob.DoModal();
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickCmdDeleteJob
//		
//
//	Description:
//		Delete a job.
//
//	Arguments:
//		None.
//
//	Return:
//		None.
//
//	Called by:
//		Framework
/////////////////////////////////////////////////////////////////////////////////////

void CSetupDlg::OnClickCmdDeleteJob() 
{
	CDeleteJobDlg DeleteJob;

	DeleteJob.m_poDatabase = m_poDatabase;
	DeleteJob.m_csJobName = m_csJobName;
	DeleteJob.DoModal();

}
/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnInitDialog
//		
//
//	Description:
//		Enable or disable buttons on launch depending on machine
//		configuration.
//	Arguments:
//		None.
//
//	Return:
//		None.
//
//	Called by:
//		Framework
/////////////////////////////////////////////////////////////////////////////////////


BOOL CSetupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickTemplateSetup
//		
//
//	Description:
//		Add, edit and delete Templates.
//
//	Arguments:
//		None.
//
//	Return:
//		None.
//
//	Called by:
//		Framework
/////////////////////////////////////////////////////////////////////////////////////

void CSetupDlg::OnClickTemplateSetup() 
{
	CTemplateSetupDlg	oTemplateSetupDlg;
	
	// pass database pointer
	oTemplateSetupDlg.m_poDatabase = m_poDatabase;

	// Launch the dialog
	oTemplateSetupDlg.DoModal();
}


void CSetupDlg::OnClickCmdWysiwyg() 
{
	AfxMessageBox("Option Not Available");
	    return;
	
STARTUPINFO si;
PROCESS_INFORMATION pi;

CFileFind ff;

	memset(&pi, 0, sizeof(pi));
	memset(&si, 0, sizeof(si));

	si.cb = sizeof(si);
	
	if (!ff.FindFile("c:\\barone\\bin\\labels.exe",NULL))
	{

		AfxMessageBox("Could Not Find Bar One Software");
		return;

	}

		
	CWaitCursor wait;

	int res = CreateProcess(

	"c:\\barone\\bin\\labels.exe", 0, 
		  0, 0, 0, 0, 0, 0, &si, &pi);


	HWND hwnd;
	CUtilities util;

	wait.Restore();

    ShowWindow(SW_HIDE); 

	while(FindWindow("tlabelmaker",NULL)==0)
	{

		util.YieldToWindows();
	}

	//Wait for it to shut down
	while (FindWindow("tlabelmaker",NULL)!=0)
	{

		util.YieldToWindows();
	}

	 hwnd = ::FindWindow("SRF1",NULL);

	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );
 
	 if (hwnd)
	 ::PostMessage(hwnd,WM_CLOSE,0,0);

	ShowWindow(SW_NORMAL); 



	UpdateTemplateDB();


}

void CSetupDlg::UpdateTemplateDB()
{

CFileFind ff;
CString	csBuffer;
CString csTemplateName;

	if(ff.FindFile("c:\\computype\\templates\\*.*")!=0)

	{
		
		while(ff.FindNextFile()!=0)
		{
			if (ff.IsDots()==0)
			{
				csBuffer=ff.GetFileName();
				csBuffer.MakeUpper();
				if (csBuffer.Find(".OUT")!=-1)
				{
					csBuffer=ff.GetFilePath();
					csTemplateName=ff.GetFileTitle();
					UpdateDB(csBuffer,csTemplateName);
				}
			}
		}
		if (ff.IsDots()==0)
		{
			csBuffer=ff.GetFileName();
			csBuffer.MakeUpper();
			if (csBuffer.Find(".OUT")!=-1)
			{
				csBuffer=ff.GetFilePath();
				csTemplateName=ff.GetFileTitle();
				UpdateDB(csBuffer,csTemplateName);
			}
		}

	}


}

void CSetupDlg::UpdateDB(CString csLabelTemplate,
						 CString csTemplateName)
{
CStdioFile f1;
CString csTemp,
		csBuffer;

CDatabase oDatabase;

	

	if( !f1.Open( csLabelTemplate,CFile::modeRead | CFile::typeText ) )
	{  
		 #ifdef _DEBUG
			 afxDump << "Unable to open file" << "\n";   
		#endif   exit( 1 );
	}
	csBuffer="";
	while (f1.ReadString(csTemp))
	{
		if (csTemp.IsEmpty()==0)
			csBuffer=csBuffer+csTemp+CString("\n");

	}
	// Check for "999999"

	if (csBuffer.Find("FD>9")!=-1)
	{
		csBuffer=ReplaceKeyWord(csBuffer, "FD>9", "xxxx");
	}


	while (csBuffer.Find("999")!=-1)
	{
		csBuffer=ReplaceKeyWord(csBuffer, "999", "Serial");
	}
	
	if (csBuffer.Find("xxxx")!=-1)
	{
		csBuffer=ReplaceKeyWord(csBuffer, "xxxx", "FD>9");
	}

	
	
	if (!csBuffer.IsEmpty())
	{
		oDatabase.Initialize();
		
		oDatabase.SetTemplate(csTemplateName,csBuffer);
		
		oDatabase.Close(); 


	}


	f1.Close();


}


CString CSetupDlg::ReplaceKeyWord(CString csTemplate, CString csKeyWord, CString csValue)
{
CString csNewLabel,
		csFrontText,
		csBackText,csBuffer;


int nKeyWordLength,
	nIndex,
	nLength;
	Trace("Start of CSetupDlg::ReplaceKeyWord()\n\r");
	Trace("-----------------------------------\n\r");

	nIndex = csTemplate.Find (csKeyWord);

	if (nIndex==-1)
		return csTemplate;

	
	if (nIndex!=-1)
	{
		csBuffer=csKeyWord;
		csBuffer=csBuffer+CString("9");
		nLength=3;
		while (csTemplate.Find (csBuffer)!=-1)
		{
			nLength+=1;
			csBuffer=csBuffer+CString("9");
		}

	}

	csKeyWord=csTemplate.Mid(nIndex,nLength);

	nKeyWordLength=csKeyWord.GetLength();

	csBuffer=csTemplate;
	while ( ( nIndex = csBuffer.Find (csKeyWord) ) != -1 )
	{
		nLength = csBuffer.GetLength();
		csFrontText = csBuffer.Left ( nIndex );
		csBackText = csBuffer.Right ( nLength - nIndex - nKeyWordLength );
		csNewLabel = csFrontText + csValue + csBackText;
		csBuffer=csNewLabel;
	}
	
	Trace("Replaced [%s] With [%s] \n\r",csKeyWord,csValue);
	Trace("End of CSetupDlg::ReplaceKeyWord()\n\r");

	if (csNewLabel=="")
		return csTemplate;
	return csNewLabel;

}
