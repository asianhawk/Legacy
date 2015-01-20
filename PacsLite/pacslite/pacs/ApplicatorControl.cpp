// ApplicatorControl.cpp: implementation of the CApplicatorControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PACS.h"
#include "ApplicatorControl.h"
#include "InitDlgMessage.h"
#include "Utilities.h"
#include "HoldDlg.h"
#include "RescanDlg.h"
#include "Password.h"
#include "RunProcesses.h"
#include "SetupDlg.h"
#include "Trace.h"
#include "RunDialog.h"
#include "ErrorMsgDlg.h"


extern CRunDialog *g_poRunDalog;



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CApplicatorControl::CApplicatorControl()
{
	m_fLabeltoLabelCycleTime=0;
	m_fAveLabeltoLabelCycleTime=0;
	m_fBoardtoBoardCycleTime=0;
	m_fAveBoardtoBoardCycleTime=0;
	m_dAveScannerPerformance=0;
	m_dScannerPerformance=0;
	m_blnIsPrinting=FALSE;
	m_bScannerActive=FALSE;

}

CApplicatorControl::~CApplicatorControl()
{

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		Initialize
//
//	Description:
//		Get current system configuration from the database and initialize
//    all sub-systems.
//
//	Arguments:
//		None.
//
//	Return:
//		Status.
//
//	Called by:
//		CPACSDlg::OnInitDialog()
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CApplicatorControl::Initialize ( void )
{
CStringArray csDummyArray;

//	Trace("[MachineState] MS= Initializing SubSystems");	
	
	BOOL	bInitCreated, bTempInit;

	CUtilities Utility;

	CInitDlgMessage *pInitDlg;

	CString
		csTemp;

	CString
		csMessage;

	CString csInput;
	CString csOutput;

//	Initialize Variables

	bTempInit=FALSE;
	m_bInitialized = FALSE;
	csInput	="NULL";
	csOutput="NULL";
	csTemp	="NULL";



	// Display an initialization message during this process.
	pInitDlg = new CInitDlgMessage (AfxGetMainWnd());


	// Display init msg.
	if ( pInitDlg->Create() == TRUE )
	{

		pInitDlg->ShowWindow ( SW_NORMAL );
		bInitCreated = TRUE;
	}
	else
		bInitCreated = FALSE;


	// Ensure database exists.
	pInitDlg->PeekAndPump();	// fixed problem with init' screen message 
	m_bInitialized = m_oDatabase.Initialize();



	if (!m_bInitialized)
	{
		m_oDIOController.m_bInitialized = FALSE;
		m_oDIOController.m_csErrorString.Empty();
		m_oPrinter.m_bInitialized       = FALSE;
		m_oPrinter.m_csErrorString.Empty();
		m_oScanner.m_bInitialized       = FALSE;
		m_oScanner.m_csErrorString.Empty();
		
		if (bInitCreated)
		{
			pInitDlg->ShowWindow ( SW_HIDE );
			delete pInitDlg;
		}
		return (m_bInitialized);
	}
	

	// Get digital I/O and initalize.

	if (m_oDatabase.GetDIOAddress ( &csInput, &csOutput))
	{
		bTempInit = m_oDIOController.Initialize ( csInput, csOutput );
		m_bInitialized = m_bInitialized && bTempInit;
	}
	else
		m_bInitialized = FALSE;


	// Initialize printer control.
	bTempInit = m_oPrinter.Initialize ( &m_oDatabase, &m_oSNManager );
	m_bInitialized = m_bInitialized && bTempInit;



	// Initialize scanner control.

	bTempInit = m_oScanner.Initialize ( &m_oDatabase, &m_oSNManager, &m_oPrinter);
	m_bInitialized = m_bInitialized && bTempInit;

	m_bScannerActive = m_oScanner.IsScannerActive();


	if ( bInitCreated )
	{

		pInitDlg->ShowWindow ( SW_HIDE );
		delete pInitDlg;
	}
	Trace("[MachineState] MS= Idle");	

	return ( m_bInitialized );
}






CJob * CApplicatorControl::GetJob ( void )
{

	return ( &m_oJob );

}



CDatabase * CApplicatorControl::GetDatabaseObject ( void )
{

	return ( &m_oDatabase );

}





CPrinterControl * CApplicatorControl::GetPrinterObject ( void )
{

	return ( &m_oPrinter );

}


CScannerControl * CApplicatorControl::GetScannerObject ( void )
{

	return ( &m_oScanner );

}





CSNManager * CApplicatorControl::GetSNManager ( void )
{

	return ( &m_oSNManager );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		Run
//
//	Description:
//		Control the execution of the label placement for the job.
//
//	Arguments:
//		Pointer to a label counter.
//		Pointer to a panel counter.
//
//	Return:
//		Status.
//
//	Called by:
//		CPACSDlg::OnClickCmdRun
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CApplicatorControl::Run ( long * lpPanelCount )
{

	Trace("[MachineState] MS= Running");	

	CString csMessage,
			csJobDescription;

	CString csLabelScanned;
	
	int nLabelsApplied;


	int	nRescans;
	int	nRepicks;
	int	nStatus;
	int nCnt;
	CTime	ctStart; 
	CTime ctNow;

	CTimeSpan elapsedTime;


	CUtilities	Utility;
	CErrorMsgDlg dlgError;

	long
		lPanelCount = 0,
		lNLabels,
		lTotalPanels;

	CString
		csScannedLabel;

	BOOL
		bForever,
		bDone,
		bPrePrinted;


	SYSTEMTIME lpStartCurCycleTime;
	SYSTEMTIME lpEndCurCycleTime;

	SYSTEMTIME lpStartCurBoardCycleTime;
	SYSTEMTIME lpEndCurBoardCycleTime;

	SYSTEMTIME lpStartTime;
	SYSTEMTIME lpEndTime;

	
	CLabel *poLabel;				// Pointer to label.

	int		nPrinter;
	nPrinter=1;

	CRunProcesses oRunProcesses;
	oRunProcesses.Initialize(this);
	
	m_oDIOController.ErrorBitOff(); 

	if (!SystemIntegrityCheck())   //check power on and Printer Ready bits
	{
		m_oDIOController.ErrorBitOn(); 
	
		return FALSE;
	}

	m_oDIOController.GreenLightOn();
	
//	Tell outside world we are busy.

	m_oDIOController.ApplicatorReadyBitOn();  // swing tamp head down
	m_oDIOController.ErrorBitOff(); 
	
	
	m_bRequestStop = FALSE;
	m_bRequestHold = FALSE;

	lNLabels = 0;
	lTotalPanels = *lpPanelCount;

	
	// Begin run mode timing.
	g_oStatistics.StartRunModeTime();

	// Get label count per panel.
	m_nMaxLabelsPerPanel = m_oJob.GetNumberOfLabels();

	m_oJob.SetLabelCount ( 0L );
	m_oJob.SetPanelCount ( 0L );

	// Setup number of auto retries.
	nRescans = 0;
	nRepicks = 0;

	// Check for E-errors.
	if ( m_oDIOController.ReadSystemInputs() )
	{
		m_oDIOController.ApplicatorReadyBitOff();  

		g_oStatistics.EndRunModeTime();
		return ( FALSE );
	}
		




	// Main loop begins. Do not stop unless Stop button is pressed or error
	// or out of panels. A total number of panels of 0 means to run until 
	// stopped by the operator.

	if ( lTotalPanels == 0 )
		bForever = TRUE;
	else
		bForever = FALSE;

	// The main loop is tailored to the customer's requirements.
	
	m_fAveLabeltoLabelCycleTime=0;
	m_fTotalLabeltoLabelCycleTime=0;
		
	m_fAveBoardtoBoardCycleTime=0;
	m_fTotalBoardtoBoardCycleTime=0;
	nLabelsApplied=0;

	m_nTotalGoodScans=0;
	m_nTotalScans=0;


	g_poRunDalog->m_cmd_hold.EnableWindow(TRUE);
	g_poRunDalog->UpDateDisplay("  "); 
	m_blnIsPrinting=FALSE;
	Sleep(1000);     // Seems to need time to reset
	nStatus=STATUS_GOOD;

	int nMaxLabelCount,
		nCurrentLabelCount;

	poLabel = m_oJob.GetFirstLabel();
	if ( poLabel == NULL )
	{
		csMessage.LoadString ( IDS_ERR_LABEL_LIST );
		AfxMessageBox ( csMessage );
		ExitRunCleanup();
		return ( FALSE );
	}
	nMaxLabelCount=0;
	while (poLabel !=NULL)
	{
		nMaxLabelCount+=1;
		poLabel = m_oJob.GetNextLabel();


	}
	poLabel = m_oJob.GetFirstLabel();
	
	csJobDescription=m_oJob.GetDescription();
	csJobDescription.MakeUpper();
	if (csJobDescription.Find("PREPRINT")!=-1)
		bPrePrinted=TRUE;
	else
		bPrePrinted=FALSE;

	
	bDone=FALSE;	
	m_oDIOController.GreenLightOn();

	
	while ( !m_bRequestStop && ( ( lPanelCount < lTotalPanels ) || bForever ) )
	{
		m_csCurrentJobStatus="";

		m_oDIOController.ErrorBitOff(); 


		Trace("[MachineState] MS= Running");	

		GetLocalTime((LPSYSTEMTIME) &lpStartCurBoardCycleTime);

		// Start timing the panel.

		if ( m_oDIOController.ReadSystemInputs() )
		{
			m_oDIOController.ApplicatorReadyBitOff();  

			g_oStatistics.EndRunModeTime();
			return ( FALSE );
		}
		
		Utility.YieldToWindows(); 
		if (!CheckForNotInHold())
		{
			m_oDIOController.LightsOff();
			return FALSE;
		}
		if (g_poRunDalog->m_blnExitRunMode)
		{
			m_oDIOController.LightsOff(); 	
			return FALSE;
		}
	    bDone=FALSE;		
		m_csCurrentJobStatus="Waiting For Board";
		g_poRunDalog->m_poDatabase = &m_oDatabase;
		g_poRunDalog->m_poSNManager = &m_oSNManager;
		g_poRunDalog->UpDateStatus(m_csCurrentJobStatus);
	
		nCurrentLabelCount=1;
		poLabel = m_oJob.GetFirstLabel();


		while (nCurrentLabelCount<=nMaxLabelCount)
		{
			g_poRunDalog->UpDatePlateInfo(nCurrentLabelCount,nMaxLabelCount);

			if ( m_oDIOController.ReadSystemInputs() )
			{
				m_oDIOController.ApplicatorReadyBitOff();
				m_oDIOController.LightsOff(); 
				return ( FALSE );
			}

			
			
			if (nCurrentLabelCount>1)
			{
				m_csCurrentJobStatus="Rotate Plate";
				g_poRunDalog->UpDateStatus(m_csCurrentJobStatus);
			}
			g_poRunDalog->m_cmd_hold.EnableWindow(TRUE);

			Utility.YieldToWindows(); 
			if (g_poRunDalog->m_blnExitRunMode)
			{
				m_oDIOController.LightsOff(); 	
				return FALSE;
			}	
			if (!CheckForNotInHold())
			{
				m_oDIOController.LightsOff(); 
				return FALSE;
			}
			m_oDIOController.GreenLightOn();
			
			bDone=FALSE;

			while ((m_oDIOController.IsPartPresent())&&
				(m_oDIOController.IsPrinterReady())&&!bDone )
			{
				m_blnIsPrinting=FALSE; //Needed for PrinterStatusChecking in
									  // RunDialog
				m_csCurrentJobStatus="Board Detected";
				m_oDIOController.GreenLightOn();
				if (!CheckFingerTraps(&lpStartTime))
				{
					m_oDIOController.LightsOff(); 	
					return FALSE;
				}
				g_poRunDalog->UpDateStatus(m_csCurrentJobStatus);

				if (g_poRunDalog->m_blnExitRunMode)
				{
					m_oDIOController.LightsOff(); 	
					return FALSE;
				}
				g_poRunDalog->m_cmd_hold.EnableWindow(FALSE);

				if ( poLabel == NULL )
				{
					m_oDIOController.RedLightOn();
					csMessage.LoadString ( IDS_ERR_LABEL_LIST );
					AfxMessageBox ( csMessage );
					ExitRunCleanup();
					m_oDIOController.LightsOff();
					return ( FALSE );
				}

				g_oStatistics.StartPanelCycleTime();
				// Get the first label.
			
				g_poRunDalog->UpDateDisplay(poLabel->GetTemplateName()); 
				
				if ( g_oStatistics.IsTimeToUpdate() )
					g_oStatistics.UpdateStatistics ( TRUE );

				// Reset auto rescan and repick counters. This is done on a panel level.

				nRescans = 0;
				nRepicks = 0;

				GetLocalTime((LPSYSTEMTIME) &lpStartCurCycleTime);

				if (!m_oPrinter.GetEnable())
				{
					m_oDIOController.RedLightOn();
					AfxMessageBox("No Printer Enabled");
					m_oDIOController.LightsOff();
					return FALSE;

				}

				m_csCurrentJobStatus="Printing Label";
				g_poRunDalog->UpDateStatus(m_csCurrentJobStatus);
		
				m_blnIsPrinting=TRUE;
				
				if (!m_oPrinter.PrintLabel(nStatus,TRUE, &m_oJob, poLabel->GetTemplate(),nCurrentLabelCount))
					return FALSE;
				
				m_blnIsPrinting=FALSE;				
				
				m_csCurrentJobStatus="Tamping Label";
				g_poRunDalog->UpDateStatus(m_csCurrentJobStatus);
				m_oDIOController.ApplyLabelBitOn();
				m_csCurrentJobStatus=" Printing and Applying Label";
				GetLocalTime((LPSYSTEMTIME) &lpStartTime);
				
				CString csTemp;
				
				g_poRunDalog->UpDateStatus(m_csCurrentJobStatus);
				Utility.YieldToWindows(); 

				BOOL bRetry = FALSE;

				do
				{	
					if (g_poRunDalog->m_blnExitRunMode)
					{
						m_oDIOController.LightsOff(); 	
						return FALSE;
					}
					if (!CheckFingerTraps(&lpStartTime))
					{
						m_oDIOController.LightsOff(); 	
						return FALSE;
					}
					if ( m_oDIOController.ReadSystemInputs() )
					{
						if (!CheckFingerTraps(&lpStartTime))
						{
							m_oDIOController.LightsOff(); 	
							return FALSE;
						}
						csTemp.LoadString(IDS_ERR_RETRY_CANCEL);
						m_oDIOController.RedLightOn();
						m_oDIOController.ErrorBitOn();

						m_oDIOController.RedLightOn();
						m_oDIOController.ApplicatorReadyBitOff();  
						m_oDIOController.ErrorBitOn();
						dlgError.m_oDIOInput = m_oDIOController.GetDIOInput();
						dlgError.m_csErrorMessage=csTemp;
				
						if(dlgError.DoModal()== IDCANCEL)
						{
							g_oStatistics.EndRunModeTime();
							m_oDIOController.ErrorBitOn();
							m_oDIOController.ApplicatorReadyBitOff();  
							m_oDIOController.LightsOff();
							return ( FALSE );
						}
						bDone=FALSE;
						m_oDIOController.GreenLightOn();
						m_csCurrentJobStatus="Recovering";
						g_poRunDalog->UpDateStatus(m_csCurrentJobStatus);
						Utility.YieldToWindows(); 
						if (bPrePrinted)
						{
							if (!CheckFingerTraps(&lpStartTime))
								return FALSE;

							m_oDIOController.ApplicatorReadyBitOn();  
							m_oDIOController.ApplyLabelBitOff();
							Sleep(200);
							m_oDIOController.ApplyLabelBitOn();
							m_oDIOController.ErrorBitOff(); 

							if (nMaxLabelCount==1)
							{
								nStatus=STATUS_GOOD;
								m_csCurrentJobStatus="ReSyncing";
							}
							else
							{


								if (!ReSync(nCurrentLabelCount,
											nMaxLabelCount,
											poLabel->GetTemplate()))
								{
								    m_oDIOController.LightsOff();
									return FALSE;
								}
								else
								{
									CReSyncDlg dlgReSync;

									dlgReSync.m_csScannedSerialNumber = "NA";
									dlgReSync.m_csNewSerialNumber = m_oPrinter.GetPrintedLabel ();

									if (dlgReSync.DoModal()==IDOK)
									{

										m_oDatabase.SetStartingSN ( m_oJob.GetJobName(),
															dlgReSync.m_csNewSerialNumber);

										
										if (dlgReSync.m_nAdjustIndex!=0)
										{
											nCurrentLabelCount=dlgReSync.m_nAdjustIndex;
											poLabel = m_oJob.GetFirstLabel();

											for (nCnt=0;nCnt<nCurrentLabelCount-1;nCnt++)
												poLabel = m_oJob.GetNextLabel();

										}
										else

											nCurrentLabelCount=nMaxLabelCount+1;
										bDone=TRUE;	
									}
									nStatus=STATUS_GOOD;
								}
							}
						}
						else
						{
							nStatus=STATUS_RELABEL;
							m_csCurrentJobStatus="ReLabeling";
						}
						if (!CheckFingerTraps(&lpStartTime))
							return FALSE;

						bRetry=TRUE;
						m_oDIOController.ApplicatorReadyBitOn();  
						m_oDIOController.ApplyLabelBitOff();
						Sleep(200);
						m_oDIOController.ApplyLabelBitOn();
						m_oDIOController.ErrorBitOff(); 
						g_poRunDalog->UpDateStatus(m_csCurrentJobStatus);

						break;

					}

					Utility.YieldToWindows(); 

					if (!CheckFingerTraps(&lpStartTime))
						return FALSE;

					if (!CheckForNotInHold())
					{
						m_oDIOController.ApplicatorReadyBitOff();  
						m_oDIOController.LightsOff();
						return FALSE;
					}			

					GetLocalTime((LPSYSTEMTIME) &lpEndTime);
					if (Utility.ElapsedTime(lpStartTime,lpEndTime)>5)
					{
							if (!CheckFingerTraps(&lpStartTime))
								return FALSE;

							m_oDIOController.RedLightOn();
							m_oDIOController.ApplicatorReadyBitOff();  
							m_oDIOController.ErrorBitOn();
							dlgError.m_oDIOInput = m_oDIOController.GetDIOInput();
							dlgError.m_csErrorMessage="Label Has Not Been Applied";
				
							if(dlgError.DoModal()== IDCANCEL)
							{
								GetLocalTime((LPSYSTEMTIME) &lpStartTime);
								m_oPrinter.ResetPrinter();
								m_oDIOController.ApplicatorReadyBitOff();  
								m_oDIOController.ErrorBitOn();
								m_oDIOController.LightsOff();
								return FALSE;
							}
							m_oDIOController.GreenLightOn();
							m_csCurrentJobStatus="Recovering";
							g_poRunDalog->UpDateStatus(m_csCurrentJobStatus);
							g_poRunDalog->InvalidateRect(NULL);
							Utility.YieldToWindows();
							
							if (bPrePrinted)
							{
								if (!CheckFingerTraps(&lpStartTime))
									return FALSE;

								m_oDIOController.ApplicatorReadyBitOn();  
								m_oDIOController.ApplyLabelBitOff();
								Sleep(200);
								m_oDIOController.ApplyLabelBitOn();
								m_oDIOController.ErrorBitOff(); 

								if (nMaxLabelCount==1)
								{
									nStatus=STATUS_GOOD;
									m_csCurrentJobStatus="ReSyncing";
								}
								else
								{

									if (!CheckFingerTraps(&lpStartTime))
										return FALSE;
									
									if (!ReSync(nCurrentLabelCount,
												nMaxLabelCount,
												poLabel->GetTemplate()))
									{
										m_oDIOController.LightsOff();
										return FALSE;
									}
									else
									{
										CReSyncDlg dlgReSync;


										dlgReSync.m_csScannedSerialNumber = "NA";
										dlgReSync.m_csNewSerialNumber = m_oPrinter.GetPrintedLabel ();


										if (dlgReSync.DoModal()==IDOK)
										{

											m_oDatabase.SetStartingSN ( m_oJob.GetJobName(),
																dlgReSync.m_csNewSerialNumber);

											
											if (dlgReSync.m_nAdjustIndex!=0)
											{
												nCurrentLabelCount=dlgReSync.m_nAdjustIndex;
												poLabel = m_oJob.GetFirstLabel();

												for (nCnt=0;nCnt<nCurrentLabelCount-1;nCnt++)
													poLabel = m_oJob.GetNextLabel();

											}
											else

												nCurrentLabelCount=nMaxLabelCount+1;
											bDone=TRUE;	
										}
										nStatus=STATUS_GOOD;


									}

								}

							}
							else
							{
								nStatus=STATUS_RELABEL;

							}

							bRetry = TRUE;
							bDone=FALSE;
							
							if (!CheckFingerTraps(&lpStartTime))
								return FALSE;
							
							m_csCurrentJobStatus="ReLabeling";
							
					
							m_oDIOController.ApplicatorReadyBitOn();  
							m_oDIOController.ApplyLabelBitOff();
							Sleep(200);
							m_oDIOController.ApplyLabelBitOn();
							m_oDIOController.ErrorBitOff(); 
							g_poRunDalog->UpDateStatus(m_csCurrentJobStatus);
							break;



					}
					if (!CheckFingerTraps(&lpStartTime))
						return FALSE;
					
					if (g_poRunDalog->m_blnExitRunMode)
					{
						m_oDIOController.LightsOff();
						return FALSE;
					}


				}while (!m_oDIOController.IsLabelApplied() && !bRetry ) ;
				if (bRetry) break;
				m_oDIOController.ApplyLabelBitOff();
				m_csCurrentJobStatus="Label Sucessfully Applied";
				g_poRunDalog->UpDateStatus(m_csCurrentJobStatus);

				
				Utility.YieldToWindows(); 

				if (poLabel->GetEnableScan())
				{

					m_csCurrentJobStatus="Scanning Barcode";
					g_poRunDalog->UpDateStatus(m_csCurrentJobStatus);

					// Continue repick until user quits or good pick.
					m_csCurrentJobStatus=" Scanning Barcode Label";
					if (!bPrePrinted)
						nStatus = oRunProcesses.ProcessScan (&csScannedLabel);
					else
						nStatus = oRunProcesses.ProcessScan (&csScannedLabel, FALSE);


					switch ( nStatus )
					{
						case STATUS_GOOD:
//							nCurrentLabelCount+=1;
							m_csCurrentJobStatus="Good Read";
							nStatus=STATUS_GOOD;

							m_csScannedPrinter1 = csScannedLabel;
							SetScannerPerformance(oRunProcesses.m_nTotalScans);
							SetAveScannerPerformance(oRunProcesses.m_nTotalScans);

							do
							{
								if (g_poRunDalog->m_blnExitRunMode) return FALSE;

								if ( m_oDIOController.ReadSystemInputs() )
								{
									csTemp.LoadString(IDS_ERR_RETRY_CANCEL);
									m_oDIOController.RedLightOn();
									if(AfxMessageBox(csTemp,MB_RETRYCANCEL) == IDCANCEL)
									{
										g_oStatistics.EndRunModeTime();
										m_oDIOController.ApplicatorReadyBitOff();  
										m_oDIOController.LightsOff();
										return ( FALSE );
									}
									m_oDIOController.ErrorBitOn();
									Sleep(250);
									m_oDIOController.ErrorBitOff();
									m_oDIOController.GreenLightOn();
								}
								if (!CheckForNotInHold()) 
								{
									m_oDIOController.ApplicatorReadyBitOff();  
									m_oDIOController.LightsOff();
									return FALSE;
								}
								g_poRunDalog->UpDateStatus(m_csCurrentJobStatus);
					
								if ((SIMULATION)&(SIMULATEDIOCONTROLLER))
									break;
								m_csCurrentJobStatus="Waiting For Labeled Item To Exit";
								Utility.YieldToWindows(); 
							}while (m_oDIOController.IsPartPresent());
							m_oDIOController.ApplyLabelBitOff();
						
							
							bDone=TRUE;
							m_oDIOController.ApplicatorReadyBitOn();  
							m_csCurrentJobStatus="Labeling Complete ";
							g_poRunDalog->UpDateStatus(m_csCurrentJobStatus);




									// Update output data file. This file is hard coded since
									// we did not get any direction from the customer as to the
									// requirements of the file and its use. The format of the file
									// is:
									//		jobname,serialnumber,date(mm/dd/yy),time(hh:mm)
									//
									// The name of the file is EXPORT.CSV and will be located in the
									// C:\COMPUTYPE\DATABASE folder.

								UpdateOutputFile ( nPrinter, csScannedLabel );
								bDone = TRUE;
								break;

						case STATUS_EXIT:
							m_oDIOController.RedLightOn();
							m_csCurrentJobStatus="Bad Scan";
							g_poRunDalog->UpDateStatus(m_csCurrentJobStatus);

							m_oDIOController.ApplicatorReadyBitOff();  
							m_oDIOController.ErrorBitOn(); 
							m_oDIOController.ApplyLabelBitOff();

							ExitRunCleanup();
							m_oDIOController.LightsOff();
							return ( FALSE );
							break;

						case STATUS_RELABEL:

							if (bPrePrinted)
							{
							
								
								if (nMaxLabelCount==1)
								{

									CReSyncDlg dlgReSync;
									dlgReSync.m_csScannedSerialNumber = csScannedLabel;
									dlgReSync.m_csPrintedSerialNumber = m_oPrinter.GetPrintedLabel ();
									dlgReSync.m_csPrintedSerialNumber = "PrePrinted";

									if ((csScannedLabel.Find("FAIL"))!=-1)
										dlgReSync.m_csNewSerialNumber = m_oPrinter.GetPrintedLabel ();
									else
										dlgReSync.m_csNewSerialNumber = csScannedLabel;

									if (dlgReSync.DoModal()==IDOK)
									{

										m_oDatabase.SetStartingSN ( m_oJob.GetJobName(),
																	dlgReSync.m_csNewSerialNumber);
									}


									nStatus=STATUS_GOOD;
									m_csCurrentJobStatus="ReSyncing - Waiting for Part Present Signal";
								}
								else
								{
									if (!ReSync(nCurrentLabelCount,
												nMaxLabelCount,
												poLabel->GetTemplate()))
									{
										m_oDIOController.LightsOff();
										return FALSE;
									}
									else
									{
										CReSyncDlg dlgReSync;
										dlgReSync.m_csScannedSerialNumber = csScannedLabel;
										dlgReSync.m_csPrintedSerialNumber = m_oPrinter.GetPrintedLabel ();
										if ((csScannedLabel.Find("FAIL"))!=-1)
											dlgReSync.m_csNewSerialNumber = m_oPrinter.GetPrintedLabel ();
										else
											dlgReSync.m_csNewSerialNumber = csScannedLabel;

										if (dlgReSync.DoModal()==IDOK)
										{

											m_oDatabase.SetStartingSN ( m_oJob.GetJobName(),
																dlgReSync.m_csNewSerialNumber);

											
											if (dlgReSync.m_nAdjustIndex!=0)
											{
												nCurrentLabelCount=dlgReSync.m_nAdjustIndex;
												poLabel = m_oJob.GetFirstLabel();

												for (nCnt=0;nCnt<nCurrentLabelCount-1;nCnt++)
													poLabel = m_oJob.GetNextLabel();


											}
											else

												nCurrentLabelCount=nMaxLabelCount+1;
											bDone=TRUE;	
										}
										nStatus=STATUS_GOOD;


									}

								}
							}
							else
							{
								
  								bRetry = TRUE;

								bDone=FALSE;
								nStatus=STATUS_RELABEL;
								m_csCurrentJobStatus="ReLabeling";

							}
							
							
							m_oDIOController.ApplicatorReadyBitOn();  
							m_oDIOController.ApplyLabelBitOff();
							Sleep(200);
							m_oDIOController.ApplyLabelBitOn();
							m_oDIOController.ErrorBitOff(); 
							g_poRunDalog->UpDateStatus(m_csCurrentJobStatus);

							break;
						
						default:			// Repick
							SetScannerPerformance(oRunProcesses.m_nTotalScans);
							SetAveScannerPerformance(oRunProcesses.m_nTotalScans);
							bDone=FALSE;
							nStatus=STATUS_RELABEL;
							
							m_oDatabase.SetStartingSN ( m_oJob.GetJobName(), m_oSNManager.GetSerialNumber() );

							m_oDIOController.ApplyLabelBitOff();
							Sleep(200);
							m_oDIOController.ApplyLabelBitOn();
							m_oDIOController.ErrorBitOff(); 
							break;
					
			

					}

				}
				else
				{
					do
					{
						if (g_poRunDalog->m_blnExitRunMode) return FALSE;

						if ( m_oDIOController.ReadSystemInputs() )
						{
							csTemp.LoadString(IDS_ERR_RETRY_CANCEL);
							m_oDIOController.RedLightOn();
							if(AfxMessageBox(csTemp,MB_RETRYCANCEL) == IDCANCEL)
							{
								g_oStatistics.EndRunModeTime();
								m_oDIOController.ApplicatorReadyBitOff();  
								m_oDIOController.LightsOff();
								return ( FALSE );
							}
							m_oDIOController.ErrorBitOn();
							Sleep(200);
							m_oDIOController.ErrorBitOff();
						}
						if (!CheckForNotInHold()) 
						{
							m_oDIOController.ApplicatorReadyBitOff();  
							m_oDIOController.LightsOff();
							return FALSE;
						}
						g_poRunDalog->UpDateStatus(m_csCurrentJobStatus);
			
						if ((SIMULATION)&(SIMULATEDIOCONTROLLER))
							break;
						m_csCurrentJobStatus="Waiting For Labeled Item To Exit";
						Utility.YieldToWindows();
						nStatus=STATUS_GOOD;


					}while (m_oDIOController.IsPartPresent());
					m_oDIOController.ApplyLabelBitOff();
				

				
					bDone=TRUE;
					m_oDIOController.ApplicatorReadyBitOn();  
					m_csCurrentJobStatus="Labeling Complete ";
					g_poRunDalog->UpDateStatus(m_csCurrentJobStatus);
		
				}
				if (bDone)
				{
					lNLabels++;	
					m_oJob.SetLabelCount ( lNLabels );
					nCurrentLabelCount+=1;
					g_poRunDalog->UpDatePlateInfo(nCurrentLabelCount,nMaxLabelCount);

					// Get next labels to be printed.
					poLabel  = m_oJob.GetNextLabel();


					GetLocalTime((LPSYSTEMTIME) &lpEndCurCycleTime);
					m_fLabeltoLabelCycleTime=Utility.ElapsedTime(lpStartCurCycleTime,lpEndCurCycleTime);
					Trace("[Stats] LtoLi= [%.2f]",m_fLabeltoLabelCycleTime);
					m_fTotalLabeltoLabelCycleTime+=m_fLabeltoLabelCycleTime;
					
					nLabelsApplied++;
					
					m_fAveLabeltoLabelCycleTime=m_fTotalLabeltoLabelCycleTime/nLabelsApplied;
					Trace("[Stats] LtoLa= [%.2f]",m_fTotalLabeltoLabelCycleTime);

					Utility.YieldToWindows(); 


					lPanelCount++;
					m_oJob.SetPanelCount ( lPanelCount );
					*lpPanelCount = lPanelCount;

					// Increment board statistics.

					g_oStatistics.IncrementPanelCount();

					// Stop timing the panel.

					g_oStatistics.EndPanelCycleTime();

					GetLocalTime((LPSYSTEMTIME) &lpEndCurBoardCycleTime);
					m_fBoardtoBoardCycleTime=Utility.ElapsedTime(lpStartCurBoardCycleTime,lpEndCurBoardCycleTime);
					m_fTotalBoardtoBoardCycleTime+=m_fBoardtoBoardCycleTime;
				
					m_fAveBoardtoBoardCycleTime=m_fTotalBoardtoBoardCycleTime/lPanelCount;
					m_csCurrentJobStatus="";
					g_poRunDalog->UpDateStatus(m_csCurrentJobStatus);

				}
				if ( m_oDIOController.ReadSystemInputs() )
				{
					csTemp.LoadString(IDS_ERR_RETRY_CANCEL);
					m_oDIOController.RedLightOn(); 
					if(AfxMessageBox(csTemp,MB_RETRYCANCEL) == IDCANCEL)
					{
						g_oStatistics.EndRunModeTime();
						m_oDIOController.ApplicatorReadyBitOff();
						m_oDIOController.LightsOff();
						return ( FALSE );
					}
					m_oDIOController.ErrorBitOn();
					Sleep(200);
					m_oDIOController.ErrorBitOff();

				}

			}
		}
		Utility.YieldToWindows(); 
		g_poRunDalog->m_cmd_hold.EnableWindow(TRUE);

		if (g_poRunDalog->m_blnExitRunMode) return FALSE;

		if (!CheckForNotInHold())
		{
			m_oDIOController.LightsOff();
			return FALSE;
		}
	} // end of main loop





//	Tell outside world we are waiting.

	m_oDIOController.ApplicatorReadyBitOff();  

	m_oPrinter.ResetPrinter();
	
	
	m_oDIOController.LightsOff();
	
	return ( TRUE );
}



BOOL CApplicatorControl::ReSync(int nCurrentLabelCount,
								int nMaxLabelCount,
								CString csTemplate)
{
int nStart,
	nMax;

BOOL bFirstTime;
	

CString csTemp;

CUtilities	Utility;


SYSTEMTIME lpStartTime;
SYSTEMTIME lpEndTime;




	nStart=nCurrentLabelCount;
	nMax = nMaxLabelCount;

	if (nStart==nMax)
	{

		return TRUE;
	}

	bFirstTime=FALSE;
	AfxMessageBox("Place Block To Catch Dispensed Labels");

	while (nStart<nMax)
	{	

		if (g_poRunDalog->m_blnExitRunMode) return FALSE;
		AfxMessageBox("Apply Part Present Signal");

		if ( m_oDIOController.ReadSystemInputs() )
		{
			csTemp.LoadString(IDS_ERR_RETRY_CANCEL);
			if(AfxMessageBox(csTemp,MB_RETRYCANCEL) == IDCANCEL)
			{
				g_oStatistics.EndRunModeTime();
				m_oDIOController.ApplicatorReadyBitOff();  
				return ( FALSE );
			}
			m_oDIOController.ErrorBitOn();
			Sleep(200);
			m_oDIOController.ErrorBitOff();

		}

		g_poRunDalog->UpDateStatus("Waiting For PartPresent Signal");
		Utility.YieldToWindows(); 
		

		
		while ((m_oDIOController.IsPartPresent())&&
			(m_oDIOController.IsPrinterReady()))
		{
			if (nStart==nMax)
			{
				AfxMessageBox("Remove Block and Place Microwell");
				return TRUE;
			}
			m_blnIsPrinting=TRUE;
			m_oPrinter.PrintLabel(STATUS_GOOD,FALSE, &m_oJob, csTemplate,1);
			nStart+=1;
			
			m_blnIsPrinting=FALSE;				

			GetLocalTime((LPSYSTEMTIME) &lpStartTime);

			m_oDIOController.ApplyLabelBitOn();
			m_csCurrentJobStatus="Resyncing Printer and Scanner";
			Sleep(2000);

			Utility.YieldToWindows(); 

			do
			{	
				if (g_poRunDalog->m_blnExitRunMode) return FALSE;

				if ( m_oDIOController.ReadSystemInputs() )
				{
					AfxMessageBox("Correct Picking Problem");
					m_oDIOController.ApplicatorReadyBitOff();  
					return ( FALSE );

				}
				Utility.YieldToWindows(); 

				if (!CheckForNotInHold())
				{
					m_oDIOController.ApplicatorReadyBitOff();  

					return FALSE;
				}			

				GetLocalTime((LPSYSTEMTIME) &lpEndTime);
				if (Utility.ElapsedTime(lpStartTime,lpEndTime)>5)
				{
					AfxMessageBox("Correct Picking Problem");
					m_oPrinter.ResetPrinter();
					m_oDIOController.ApplicatorReadyBitOff();  
					m_oDIOController.ErrorBitOn();
					return FALSE;
				}
				if (g_poRunDalog->m_blnExitRunMode) return FALSE;


			}while (!m_oDIOController.IsLabelApplied());
			m_oDIOController.ApplyLabelBitOff();
			AfxMessageBox("Release Part Present Signal");
			
		}
	}

	return TRUE;
}



BOOL CApplicatorControl::CheckForNotInHold()
{

CString csTemp;

CRunProcesses oRunProcesses;

	oRunProcesses.Initialize(this);
	if (m_oDIOController.IsStopButtonOn())
	{
		m_bRequestHold=TRUE;
		m_oDIOController.ApplicatorReadyBitOff();
		m_oDIOController.ErrorBitOn();
		Sleep(200);						// need dwell to induce a pulse
		m_oDIOController.ErrorBitOff();

		m_oDIOController.RedLightOn();

	}

	if (m_bRequestHold)
	{
		if (!oRunProcesses.ApplicatorHold())
		{
			
			m_oDIOController.ApplicatorReadyBitOff();
			m_oDIOController.ErrorBitOn();
			Sleep(200);						// need dwell to induce a pulse
			m_oDIOController.ErrorBitOff();
			m_oDIOController.RedLightOn();
			
			return FALSE;
		}
		else
		{
			m_oDIOController.ErrorBitOff(); 
			Sleep(300);
			m_oDIOController.ApplicatorReadyBitOn();  // swing tamp head down

			m_oDIOController.GreenLightOn();
							
			m_bRequestHold=FALSE;
		}
	}
	return TRUE;

}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		ExitRunCleanup
//
//	Description:
//		Cleanup everything after an error during run mode.
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
void CApplicatorControl::ExitRunCleanup ( )
{

	CString
		csSerialNumber,
		csMessage;

	CUtilities Utility;

	// Shut everything down.
	m_oPrinter.ResetPrinter();


	m_oDIOController.ErrorBitOn(); // Swing Tamp Head Up
	
	m_oDIOController.ApplyLabelBitOff();
	m_oDIOController.ApplicatorReadyBitOff() ;
	Sleep(30);



	if ( m_oSNManager.UseSerialization() )
	{
		if ( m_csCurrentSN != m_oSNManager.GetSerialNumber () )
		{
			// The label has been printed and incremented in the database
			// but it has not been placed. We need to reset the starting 
			// serial number in the database.
			csSerialNumber = m_oSNManager.GetSerialNumberN ( 1 );
			m_oDatabase.SetStartingSN ( m_oJob.GetJobName(), csSerialNumber );
		}
	}

	// End run mode timing.
	g_oStatistics.EndRunModeTime();

	// flush statistics
	g_oStatistics.UpdateStatistics ( TRUE );

}


BOOL CApplicatorControl::ExitRunCleanup (BOOL blnRetState)
{

	CString
		csSerialNumber,
		csMessage;

	CUtilities Utility;

	// Shut everything down.
	m_oPrinter.ResetPrinter();
	m_oDIOController.ErrorBitOn(); 
	m_oDIOController.ApplyLabelBitOff();
	m_oDIOController.ApplicatorReadyBitOff() ;
	Sleep(30);



	if ( m_oSNManager.UseSerialization() )
	{
		if ( m_csCurrentSN != m_oSNManager.GetSerialNumber () )
		{
			// The label has been printed and incremented in the database
			// but it has not been placed. We need to reset the starting 
			// serial number in the database.
			csSerialNumber = m_oSNManager.GetSerialNumberN ( 1 );
			m_oDatabase.SetStartingSN ( m_oJob.GetJobName(), csSerialNumber );
		}
	}

	// End run mode timing.
	g_oStatistics.EndRunModeTime();

	// flush statistics
	g_oStatistics.UpdateStatistics ( TRUE );

	return blnRetState;
}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetupJob
//
//	Description:
//		Collect the job information from the database.
//
//	Arguments:
//		Job name.
//
//	Return:
//		Pointer to the job object.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

CJob * CApplicatorControl::SetupJob ( CString csJobName )
{

	m_oDatabase.GetJobAttributes ( csJobName, &m_oJob );
	
	return ( &m_oJob );

}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		ReqHold
//
//	Description:
//		Signal from Run dialog that hold button has been pressed.
//
//	Arguments:
//		None
//
//	Return:
//		None
//
//	Called by:
//		RunDialog::UpdateForm
//
/////////////////////////////////////////////////////////////////////////////////////

void CApplicatorControl::ReqHold()
{
	m_bRequestHold = TRUE;
}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		Reset
//
//	Description:
//		Reset the subsystems.
//
//	Arguments:
//		None
//
//	Return:
//		Status
//
//	Called by:
//		CPACSDlg::OnClickCancel
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CApplicatorControl::Reset ( )
{
	Trace("[MachineState] MS= Resetting Actuators");

	if ( m_bInitialized )	
	{
		m_oDIOController.Reset ();
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		PrintOneSample
//
//	Description:
//		Print a sample of the template of the selected job.
//
//	Arguments:
//		Label to print.
//
//	Return:
//		Status.
//
//	Called by:
//		CPACSDlg::OnClickCmdPrint
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CApplicatorControl::PrintOneSample ( CLabel *poLabel )
{

	CString
		csTemplate;

	csTemplate =  poLabel->GetTemplate();
	return ( m_oPrinter.PrintLabel ( STATUS_GOOD, FALSE,  &m_oJob, csTemplate, 1 ) );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetRequestHold
//
//	Description:
//		Returns whether a user has pressed hold
//
//	Arguments:
//		none
//
//	Return:
//		hold status.
//
//	Called by:
//
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL * CApplicatorControl::GetRequestHold()
{
	return (&m_bRequestHold);
}
/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetAutoRescans()
//
//	Description:
//		Gets the number of autorescans
//
//	Arguments:
//		none
//
//	Return:
//		int * - pointer to the number of rescans
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

int * CApplicatorControl::GetAutoRescans()
{
	return (&m_nAutoRescans);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetDIOObject()
//
//	Description:
//		Gets the dio controller object
//
//	Arguments:
//		none
//
//	Return:
//		CDioController * - pointer to the dio object
//
//	Called by:
//
//
/////////////////////////////////////////////////////////////////////////////////////

CDioController * CApplicatorControl::GetDIOObject()
{
	return (&m_oDIOController);
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		UpdateOutputFile()
//
//	Description:
//		Append the latest serial number information to the output file.
//
//	Arguments:
//		Printer.
//
//	Return:
//		Status.
//
//	Called by:
//		Run
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CApplicatorControl::UpdateOutputFile ( int nPrinter, CString csScanned )
{

	CString
		csDate,
		csTime,
		csRecord,
		csSerialNumber;

	CStdioFile fOutputFile;

	CTime 
		ctFileTime,
		ctNow;

	struct tm* 
		LocalTime;

	char tmpbuf[20];

	BOOL
		bStatus;

	int
		nYear;


	ctNow = CTime::GetCurrentTime();

	LocalTime = ctNow.GetLocalTm ( NULL );

	/* Use strftime to get the year with century. */

	strftime( tmpbuf, 20, "%Y", LocalTime );
	nYear = atoi ( tmpbuf );

	csDate.Format ( "%02d/%02d/%04d", LocalTime->tm_mon+1,
									  LocalTime->tm_mday,
									  nYear );

	csTime.Format ( "%02d:%02d:%02d", LocalTime->tm_hour,
									  LocalTime->tm_min,
									  LocalTime->tm_sec );



	if ( csScanned == "" )
	{
//		if ( m_oSNManager.UseSerialization() )
//			csSerialNumber = m_oSNManager.GetSerialNumberN ( 1 );
//		else
			csSerialNumber = m_oPrinter.GetPrintedLabel ( );
	}
	else
		csSerialNumber = csScanned;

	csRecord = m_oJob.GetJobName();
	csRecord += "," + csSerialNumber + "," + csDate + "," + csTime + "\n";

	if ( !fOutputFile.Open( "c:\\computype\\database\\export.csv", 
			CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite ) )
	{
		AfxMessageBox ( "Unable to open c:\\computype\\database\\export.csv. The serial number information" 
			            " will be written to c:\\computype\\database\\sernum.dat" );

		fOutputFile.Open( "c:\\computype\\database\\sernum.dat", 
			CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite );

		bStatus = FALSE;
	}
	else
	{

		bStatus = TRUE;
	}

	fOutputFile.SeekToEnd();

	fOutputFile.WriteString ( csRecord );


	fOutputFile.Close ();

	return ( bStatus );

}


void CApplicatorControl::SetScannerPerformance(int nScanCount)
{
	if (nScanCount==-1) 
	{
		m_dScannerPerformance=0;
		return;
	}
	if (nScanCount!=0)
	{
		m_dScannerPerformance=1./nScanCount*100;

	}
	else
	{
		m_dScannerPerformance=0;
	}

}

CString	CApplicatorControl::GetScannerPerformance()
{
CString csTemp;

	if (m_dScannerPerformance!=0)
	{
		csTemp.Format("%6.2f",m_dScannerPerformance);

	}
	else
	{
		csTemp="N/A";
	}
	return csTemp;

}


void CApplicatorControl::SetAveScannerPerformance(int nScanCount)
{
	if (nScanCount==-1) 
	{
		m_dScannerPerformance=0;
		return;
	}

	
	m_nTotalGoodScans+=1;
	m_nTotalScans+=nScanCount;
	if (m_nTotalScans!=0)
	{
		m_dAveScannerPerformance=(double)(m_nTotalGoodScans)/((double)m_nTotalScans)*100;

	}
	else
	{
		m_dAveScannerPerformance=0;
	}

}

CString	CApplicatorControl::GetAveScannerPerformance()
{
CString csTemp;

	if (m_dAveScannerPerformance!=0)
	{
		csTemp.Format("%6.2f",m_dAveScannerPerformance);

	}
	else
	{
		csTemp="N/A";
	}
	return csTemp;

}


BOOL CApplicatorControl::SystemIntegrityCheck()
{

	if ( m_oDIOController.ReadSystemInputs() )
		return ( FALSE );

	
	if (!m_oDIOController.IsPowerOn())
	{
		AfxMessageBox("Power Is Off");
		return FALSE;

	}


/*	if (!m_oDIOController.IsPrinterReady())
	{
		AfxMessageBox("The Applicator/Printer Is Not Ready");
		return FALSE;

	}
*/
	return TRUE;
}




void CApplicatorControl::StartVirtualKeyboard() 
{
STARTUPINFO si;
PROCESS_INFORMATION pi;

CFileFind ff;

long WM_KEYON_HIDE;       	 
	HWND hwnd;
	CUtilities util;
    

	WM_KEYON_HIDE  = RegisterWindowMessage("KEYON HIDE");


	memset(&pi, 0, sizeof(pi));
	memset(&si, 0, sizeof(si));

	si.cb = sizeof(si);
	
    hwnd = ::FindWindow("TfmMain",NULL);
	if (hwnd)
	{
		::PostMessage(hwnd,WM_KEYON_HIDE ,0,0);
	return;
	}

	
	
	if (!ff.FindFile("C:\\Computype\\Virtual Keyboard\\Keyon.exe",NULL))
	{

		AfxMessageBox("Could Not Find Virtual Keyboard Software");
		return;

	}

		

	int res = CreateProcess(

	"C:\\Computype\\Virtual Keyboard\\Keyon.exe", 0, 
		  0, 0, 0, 0, 0, 0, &si, &pi);




	while(FindWindow("TfmMain",NULL)==0)
	{

		util.YieldToWindows();
	}


    hwnd = ::FindWindow("TfmMain",NULL);

 
	 if (hwnd)
	 ::PostMessage(hwnd,WM_KEYON_HIDE ,0,0);

}


BOOL CApplicatorControl::IsScannerActive()
{
	return m_bScannerActive;
}

BOOL CApplicatorControl::CheckFingerTraps(LPSYSTEMTIME lpStartTime)
{
CUtilities oUtil;

	m_oDIOController.ReadSystemInputs();

	if (!m_oDIOController.IsPartPresent())
	{
		g_poRunDalog->UpDateStatus("Finger Traps Vacant");
		g_poRunDalog->Invalidate();
		oUtil.YieldToWindows();
	}

	while(!m_oDIOController.IsPartPresent())
	{
		m_oDIOController.RedLightOn(); 

		m_oDIOController.ApplyLabelBitOff();
		m_oDIOController.ReadSystemInputs();

		if (m_oDIOController.IsStopButtonOn())
		{
			//m_oDIOController.ApplicatorReadyBitOff();
			m_oDIOController.ErrorBitOn();
		//	Sleep(200);						// need dwell to induce a pulse
		//	m_oDIOController.ErrorBitOff();
	
			m_oDIOController.LightsOff(); 
			return FALSE;
		}

		GetLocalTime((LPSYSTEMTIME) *&lpStartTime);

	}
	m_oDIOController.GreenLightOn(); 
	m_oDIOController.ApplyLabelBitOn();

	return TRUE;
}