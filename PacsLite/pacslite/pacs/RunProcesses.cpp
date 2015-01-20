// RunProcesses.cpp: implementation of the CRunProcesses class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "pacs.h"
#include "DioController.h"
#include "Utilities.h"
#include "Job.h"
#include "PrinterControl.h"
#include "Password.h"
#include "HoldDlg.h"
#include "SetupDlg.h"
#include "ApplicatorControl.h"
#include "RescanDlg.h"
#include "SNManager.h"
#include "RunProcesses.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRunProcesses::CRunProcesses ()
{

}

CRunProcesses::~CRunProcesses()
{

}

////////////////////////////////////////////////////////////////////////////////////
//
//	Name: Initialize
//
//	Description:
//		sets member variables
//
//	Arguments:
//		poApplicatorControl, a pointer to the applicator control
//		object that owns this runprocesses object
//
//	Return:
//		void
//
//	Called by:
//		
//		
/////////////////////////////////////////////////////////////////////////////////////

void CRunProcesses::Initialize(CApplicatorControl * poApplicatorControl)
{
	m_pbRequestHold = poApplicatorControl->GetRequestHold();
	m_pnAutoRescans = poApplicatorControl->GetAutoRescans();

	m_poDatabase = poApplicatorControl->GetDatabaseObject();
	m_poDIOController = poApplicatorControl->GetDIOObject();
	m_poJob = poApplicatorControl->GetJob();
	m_poPrinter = poApplicatorControl->GetPrinterObject();
	m_poScanner = poApplicatorControl->GetScannerObject();
	m_poSNManager = poApplicatorControl->GetSNManager();
}




////////////////////////////////////////////////////////////////////////////////////
//
//	Name: ProcessScan
//
//	Description:
//		Execute the scan process for a particular printer and end-effector.
//
//	Arguments:
//		nosepiece designator.
//		Position of previous label.
//
//	Return:
//		Status.
//
//	Called by:
//		CApplicatorControl::Run
//
/////////////////////////////////////////////////////////////////////////////////////

int CRunProcesses::ProcessScan(CString * csLabelScanned)
{

	BOOL
		bVerifyScan,
		bDoneScanning;

	int
		nRescans,
		nMsgReturn;

	CString
		csLabelPrinted,
		csMessage;

	CString csRotation;

	CUtilities Utility;


	// Move to scan position. This may involve the rotation.




	csLabelPrinted = m_poPrinter->GetPrintedLabel ();		

	// Scan and verify. 
	nRescans = 0;
	bDoneScanning = FALSE;
	bVerifyScan=TRUE;

	// Outer loop is executed each time rescan is selected from the 
	// scan recovery dialog box.

	Trace("CRunProcesses::ProcessScan() Begin Scanning\n");
	m_nTotalScans=0;

	*(m_pnAutoRescans)=1;		// DJP clean up here


	
	
	
	
	while ( !bDoneScanning )
	{


		if ( (SIMULATION) & (SIMULATELABELSCANNER))
		{
			Trace("CRunProcesses::ProcessScan() Simulation Mode Good Scan\n");
			*csLabelScanned=csLabelPrinted;
			m_nTotalScans++;
			m_poScanner->m_csScannedLabel=csLabelPrinted; 
			bDoneScanning = TRUE;
			m_poScanner->ScanLabel ( csLabelScanned, 
										  m_poDIOController,
										  csLabelPrinted,
										  bVerifyScan );
			break;

		}



		// Retry scanning the specified amount. This is done for auto-rescan amount.
		while ( nRescans < *(m_pnAutoRescans) && !bDoneScanning )
		{
			if ( !m_poScanner->ScanLabel ( csLabelScanned, 
										  m_poDIOController,
										  csLabelPrinted,
										  bVerifyScan ) )
			{
				nRescans++;
				g_oStatistics.IncrementRescanCount();	// Update stats.
			}
			else
			{
				m_csScannedLabel=*csLabelScanned;
				bDoneScanning = TRUE;
			}
			m_nTotalScans++;

		}	// End while auto-rescans.

		nRescans = 0;

		if ( !bDoneScanning )
		{


			CRescanDlg ScanRecovery;

			ScanRecovery.DoModal();

			nMsgReturn = ScanRecovery.m_nRecovery;

			switch ( nMsgReturn )
			{
				case RELABEL_RECOVERY:
					g_oStatistics.IncrementRepickCount();	// Update stats.
					Trace("End of CRunProcesses::ProcessScan() STATUS_RELABEL");

					return ( STATUS_RELABEL );
					break;

				case RESCAN_RECOVERY:
					g_oStatistics.IncrementRescanCount();	// Update stats.
					break;

				case HALT_RECOVERY:
					Trace("End of CRunProcesses::ProcessScan() HALT_RECOVERY");
					return ( STATUS_EXIT );
					break;

				default:
					Trace("End of CRunProcesses::ProcessScan() USER EXIT");
					return ( STATUS_EXIT );
					break;
			}
		}
	}	// End while not re-scanning from scan recovery. 

	//***************check for HOLD button******************

	if (*(m_pbRequestHold))
	{
		if ( !ApplicatorHold() )
			return ( STATUS_EXIT );

		*(m_pbRequestHold) = FALSE;
	}
	//******************************************************
	Trace("End of CRunProcesses::ProcessScan() Good Scan \n");

	// Scanning is complete.
	return ( STATUS_GOOD );
}




int CRunProcesses::ProcessScan(CString * csLabelScanned, BOOL blnVerify)
{

	BOOL
		bVerifyScan,
		bDoneScanning;

	int
		nRescans,
		nMsgReturn;

	CString
		csLabelPrinted,
		csMessage;

	CString csRotation;

	CUtilities Utility;

	bVerifyScan=blnVerify;

	// Move to scan position. This may involve the rotation.


	// Scan and verify. 
	nRescans = 0;
	bDoneScanning = FALSE;


	// Outer loop is executed each time rescan is selected from the 
	// scan recovery dialog box.

	Trace("CRunProcesses::ProcessScan() Begin Scanning\n");
	m_nTotalScans=0;

	*(m_pnAutoRescans)=1;		// DJP clean up here


	
	
	while ( !bDoneScanning )
	{


		if ( (SIMULATION) & (SIMULATELABELSCANNER))
		{
			Trace("CRunProcesses::ProcessScan() Simulation Mode Good Scan\n");
			csLabelPrinted="Preprinted";
			*csLabelScanned=csLabelPrinted;
			m_nTotalScans++;
			m_poScanner->m_csScannedLabel=csLabelPrinted; 
			bDoneScanning = TRUE;
			m_poScanner->ScanLabel ( csLabelScanned, 
										  m_poDIOController,
										  csLabelPrinted,
										  bVerifyScan );
			break;

		}



		// Retry scanning the specified amount. This is done for auto-rescan amount.
		while ( nRescans < *(m_pnAutoRescans) && !bDoneScanning )
		{
			if ( !m_poScanner->ScanLabel ( csLabelScanned, 
										  m_poDIOController,
										  csLabelPrinted,
										  bVerifyScan ) )
			{
				nRescans++;
				g_oStatistics.IncrementRescanCount();	// Update stats.
			}
			else
			{
				m_csScannedLabel=*csLabelScanned;
				bDoneScanning = TRUE;
			}
			m_nTotalScans++;

		}	// End while auto-rescans.

		nRescans = 0;

		if ( !bDoneScanning )
		{


			CRescanDlg ScanRecovery;

			ScanRecovery.DoModal();

			nMsgReturn = ScanRecovery.m_nRecovery;

			switch ( nMsgReturn )
			{
				case RELABEL_RECOVERY:
					g_oStatistics.IncrementRepickCount();	// Update stats.
					Trace("End of CRunProcesses::ProcessScan() STATUS_RELABEL");

					return ( STATUS_RELABEL );
					break;

				case RESCAN_RECOVERY:
					g_oStatistics.IncrementRescanCount();	// Update stats.
					break;

				case HALT_RECOVERY:
					Trace("End of CRunProcesses::ProcessScan() HALT_RECOVERY");
					return ( STATUS_EXIT );
					break;

				default:
					Trace("End of CRunProcesses::ProcessScan() USER EXIT");
					return ( STATUS_EXIT );
					break;
			}
		}
	}	// End while not re-scanning from scan recovery. 

	//***************check for HOLD button******************

	if (*(m_pbRequestHold))
	{
		if ( !ApplicatorHold() )
			return ( STATUS_EXIT );

		*(m_pbRequestHold) = FALSE;
	}
	//******************************************************
	Trace("End of CRunProcesses::ProcessScan() Good Scan \n");

	// Scanning is complete.
	return ( STATUS_GOOD );
}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		ApplicatorHold
//
//	Description:
//		Handle the hold situation.
//
//	Arguments:
//		None
//
//	Return:
//		None
//
//	Called by:
//		Run
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CRunProcesses::ApplicatorHold()
{

	BOOL 
		bDone;

	int
		nMsgReturn;

	CString
		csTemp;

	CUtilities Utility;

	CPassword Password;


	// Start the idle mode timer.

	g_oStatistics.StartIdleModeTime();

	
	

	
	// Display hold alternatives.

	CHoldDlg HoldDlg;

	// Repeat the display of the dialog as long as continue or exit is not selected.

	bDone = FALSE;
	while ( !bDone )
	{
		HoldDlg.m_oDIOInput= m_poDIOController->GetDIOInput(); 

		HoldDlg.DoModal();

		nMsgReturn = HoldDlg.m_nHoldSelection;

		switch ( nMsgReturn )
		{
			case HOLD_SETUP_SYSTEM:
				//  Run the setup system information process.
				g_oStatistics.EndIdleModeTime();
				
				// Password clearance is required to change job and system attributes.
				if ( Password.PasswordClearance (m_poDatabase) )
				{

					CSetupDlg	Setup;
					CString		csJobName;

					// get the job name
					csJobName = m_poJob->GetJobName();

					// set dialog box member variables
					Setup.SetDatabaseObject (m_poDatabase);
					Setup.m_csJobName=csJobName;
					Setup.SetPrinterControlObject (m_poPrinter);
					Setup.SetScannerControlObject (m_poScanner);

					// launch the dialog box
					Setup.DoModal();
				}
				
				g_oStatistics.StartIdleModeTime();
				break;

			case HOLD_CONTINUE:
				bDone = TRUE;
				break;

			case HOLD_EXIT:
//				bDone = TRUE;
				return FALSE;
				break;

		}

	} // End while.


	
	while ( m_poDIOController->ReadSystemInputs() )  				
	{
		csTemp.LoadString ( IDS_CLOSE_DOORS );
		AfxMessageBox ( csTemp );
		Utility.YieldToWindows();
		return FALSE;
	}
				

	

	g_oStatistics.EndIdleModeTime();

	return ( TRUE);

}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		ExitManualCleanup
//
//	Description:
//		Cleanup everything after an error during manual mode.
//
//	Arguments:
//		None
//
//	Return:
//		None
//
//	Called by:
//		Run
//
/////////////////////////////////////////////////////////////////////////////////////

void CRunProcesses::ExitManualCleanup ( )
{

	m_poDIOController->ApplicatorReadyBitOn(); 

}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		ParseApplicatorPoint
//
//	Description:
//		Retrieve the specified system point and convert into usable string.
//
//	Arguments:
//		Point type to retrieve
//		Pointer to x, y string
//		Pointer to rotation string.
//
//	Return:
//		Status.
//
//	Called by:
//		CApplicatorControl::Run, CApplicatorControl::ManualFeed
//
/////////////////////////////////////////////////////////////////////////////////////




