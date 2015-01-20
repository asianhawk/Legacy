// Statistics.cpp: implementation of the CStatistics class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Statistics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



#define EVERY_MIN		1			// Update every minute.
#define EVERY_HOUR	60			// Update every hour or 60 minutes.
#define EVERY_DAY		1440		// Update every day or 1440 minutes.


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStatistics::CStatistics()
{

	m_bUseStatistics = FALSE;
	m_bDisplayNoDB = FALSE;
	m_bInRunModeTime = FALSE;
	m_bInIdleModeTime = FALSE;
	m_bInSetupModeTime = FALSE;
	m_csProductName = " ";

}

CStatistics::~CStatistics()
{

}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		Initialize
//
//	Description:
//		Initialize the statistics gathering process.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//		Applicator::Initialize
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CStatistics::Initialize ( void )
{


	m_csProductName = " ";

	m_nDayOfLastLog    = 0;

	m_lPanelCycleTime  = 0L;					// Overall board cycle time ( real-time ) in seconds.
	m_fTimeInRunMode   = (float)0.0;			// Accumulative hours in run mode only.
	m_fTimeInIdleMode  = (float)0.0;			// Accumulative hours in hold or error.
	m_fTimeInSetupMode = (float)0.0;			// Accumulative hours in setup mode.
	m_lLabelsApplied   = 0L;					// The number of valid labels applied.
	m_lLabelsRescanned = 0L;					// The number of re-scanned.
	m_lLabelsRepicked  = 0L;					// The number of re-picks.
	m_lPanelsCompleted = 0L;					// Then number of boards populated.

	m_bTimeToUpdate = FALSE;

	return ( TRUE );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		StartNewProduct
//
//	Description:
//		Reset the internal statistics and product name.
//
//	Arguments:
//		Product name.
//
//	Return:
//		Status.
//
//	Called by:
//		Applicator::Run
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CStatistics::StartNewProduct ( CString csProductName )
{

	m_csProductName = csProductName;

	m_lLabelsApplied   = 0L;					// The number of valid labels applied.
	m_lLabelsRescanned = 0L;					// The number of re-scanned.
	m_lLabelsRepicked  = 0L;					// The number of re-picks.
	m_lPanelsCompleted = 0L;					// Then number of boards populated.

	return ( TRUE );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		UpdateStatistics
//
//	Description:
//		Update the statistics to a user specified log file and to the computype
//		statistics database.
//
//	Arguments:
//		Force user log flag.
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CStatistics::UpdateStatistics ( BOOL bForceLog )
{

	BOOL
		bRefresh,
		bFileUpdated = FALSE,
		bUpdated = FALSE,
		bGoodUpdate = TRUE;


	// Check for refresh time before modifying time stamp in log.

	bRefresh = IsRefreshTime();

	// Update file and database.

	if ( TimeToUpdate() || bForceLog )
	{

		// Update timing.

		UpdateTimers();

		// Update database.

		if ( !UpdateStatisticsDB ( ) )
		{
			// For now, do nothing.
//			return ( FALSE );
		}

		// Update file.

		if ( m_bUseStatistics )
		{
			bGoodUpdate = UpdateStatisticsFile();
			bFileUpdated = TRUE;
		}
		bUpdated = TRUE;
	}

	if ( m_bUseStatistics && bRefresh )
	{

		if ( !bUpdated )
			UpdateStatisticsDB ( );
		bUpdated = TRUE;

		// Copy local file to time stamped file.

		if ( !bFileUpdated )
			bGoodUpdate = UpdateStatisticsFile();

		RefreshStatistics();
	}

	if ( bUpdated )
	{

		// Reset the stat data.

		m_lLabelsApplied   = 0L;					
		m_lLabelsRescanned = 0L;					
		m_lLabelsRepicked  = 0L;					
		m_lPanelsCompleted = 0L;					

		
		m_fTimeInRunMode   = (float)0.0;			
		m_fTimeInIdleMode  = (float)0.0;			
		m_fTimeInSetupMode = (float)0.0;			

	}

	m_bTimeToUpdate = FALSE;

	return ( bGoodUpdate );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		StartPanelCycleTime
//
//	Description:
//		Start timer for board cycle rate.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//		Applicator::Run
//
/////////////////////////////////////////////////////////////////////////////////////

void CStatistics::StartPanelCycleTime ( void )
{

	m_ctStartPanelTime = CTime::GetCurrentTime();

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		EndPanelCycleTime
//
//	Description:
//		End timer for board cycle rate and store result.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//		Applicator::Run
//
/////////////////////////////////////////////////////////////////////////////////////

void CStatistics::EndPanelCycleTime ( void )
{

	CTime ctNow;

	CTimeSpan elapsedTime;

	ctNow = CTime::GetCurrentTime();

	elapsedTime = ctNow - m_ctStartPanelTime;
	m_lPanelCycleTime = elapsedTime.GetTotalSeconds();

}
  


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetPanelCycleTime
//
//	Description:
//		Get the board cycle rate.
//
//	Arguments:
//		None
//
//	Return:
//		Board cycle rate.
//
//	Called by:
//		Applicator::Run
//
/////////////////////////////////////////////////////////////////////////////////////

long CStatistics::GetPanelCycleTime ( void )
{

	return ( m_lPanelCycleTime );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		StartRunModeTime
//
//	Description:
//		Start timer for run mode.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//		Applicator::Run
//
/////////////////////////////////////////////////////////////////////////////////////

void CStatistics::StartRunModeTime ( void )
{

	m_ctStartRunModeTime = CTime::GetCurrentTime();
	m_bInRunModeTime = TRUE;

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		EndRunModeTime
//
//	Description:
//		End timer for time in run mode.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//		Applicator::Run
//
/////////////////////////////////////////////////////////////////////////////////////

void CStatistics::EndRunModeTime( void )
{

	CTime ctNow;

	CTimeSpan elapsedTime;

	long	lDuration;


	ctNow = CTime::GetCurrentTime();

	elapsedTime = ctNow - m_ctStartRunModeTime;					// Time in run mode since timing started.
	lDuration = elapsedTime.GetTotalSeconds();

	m_fTimeInRunMode += (float)lDuration / (float)3600.0;	// Time in run mode since start of
																			// logging in number of hours.
	m_bInRunModeTime = FALSE;

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetRunModeTime
//
//	Description:
//		Give up the run mode time. No hording.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

float CStatistics::GetRunModeTime ( void )
{

	return ( m_fTimeInRunMode );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		StartIdleModeTime
//
//	Description:
//		Start timer for time in idle or hold mode. Idle time is time any time not
//		actually running or setting up job or system information.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//		Applicator::Run
//
/////////////////////////////////////////////////////////////////////////////////////

void CStatistics::StartIdleModeTime ( void )
{

	m_ctStartIdleModeTime = CTime::GetCurrentTime();
	m_bInIdleModeTime = TRUE;

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		EndIdleModeTime
//
//	Description:
//		End timer for time in idle mode.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//		Applicator::Run
//
/////////////////////////////////////////////////////////////////////////////////////

void CStatistics::EndIdleModeTime ( void )
{

	CTime ctNow;

	CTimeSpan elapsedTime;

	long	lDuration;


	ctNow = CTime::GetCurrentTime();

	elapsedTime = ctNow - m_ctStartIdleModeTime;			// Time in idle mode since timing started.
	lDuration = elapsedTime.GetTotalSeconds();

	m_fTimeInIdleMode += (float)lDuration / (float)3600.0;		// Time in idle mode since start of
																					// logging in number of hours.
	m_bInIdleModeTime = FALSE;

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetIdleModeTime
//
//	Description:
//		Retrieve the idle mode time.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//		Applicator::Run
//
/////////////////////////////////////////////////////////////////////////////////////

float CStatistics::GetIdleModeTime ( void )
{

	return ( m_fTimeInIdleMode );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		StartSetupTime
//
//	Description:
//		Start timer for time in setup mode. Either job or system setup.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//		Applicator::Run
//
/////////////////////////////////////////////////////////////////////////////////////

void CStatistics::StartSetupModeTime ( void )
{

	m_ctStartSetupModeTime = CTime::GetCurrentTime();
	m_bInSetupModeTime = TRUE;

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		EndSetupModeTime
//
//	Description:
//		End timer for time in setup mode.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//		Applicator::Run
//
/////////////////////////////////////////////////////////////////////////////////////

void CStatistics::EndSetupModeTime ( void )
{

	CTime ctNow;

	CTimeSpan elapsedTime;

	long	lDuration;


	ctNow = CTime::GetCurrentTime();

	elapsedTime = ctNow - m_ctStartSetupModeTime;			// Time in setup mode since timing started.
	lDuration = elapsedTime.GetTotalSeconds();

	m_fTimeInSetupMode += (float)lDuration / (float)3600.0;	// Time in setup mode since start of
																				// logging in number of hours.
	m_bInSetupModeTime = FALSE;

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetSetupModeTime
//
//	Description:
//		Retrieve the setup mode time.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//		Applicator::Run
//
/////////////////////////////////////////////////////////////////////////////////////

float CStatistics::GetSetupModeTime ( void )
{

	return ( m_fTimeInSetupMode );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		IncrementLabelCount
//
//	Description:
//		Increment the number of labels applied.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//		Applicator::Run
//
/////////////////////////////////////////////////////////////////////////////////////

void CStatistics::IncrementLabelCount ( void )
{

	m_lLabelsApplied++;

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetLabelCount
//
//	Description:
//		Get the number of labels applied.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//		Applicator::Run
//
/////////////////////////////////////////////////////////////////////////////////////

long CStatistics::GetLabelCount ( void )
{

	return ( m_lLabelsApplied );

}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		IncrementRescanCount
//
//	Description:
//		Increment the number of labels rescanned.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//		Applicator::Run
//
/////////////////////////////////////////////////////////////////////////////////////

void CStatistics::IncrementRescanCount ( void )
{

	m_lLabelsRescanned++;

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetRescanCount
//
//	Description:
//		Get the count of the number of labels rescanned.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//		Applicator::Run
//
/////////////////////////////////////////////////////////////////////////////////////

long CStatistics::GetRescanCount ( void )
{

	return ( m_lLabelsRescanned );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		IncrementRepickCount
//
//	Description:
//		Increment the number of labels repicked ( and printed ).
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//		Applicator::Run
//
/////////////////////////////////////////////////////////////////////////////////////

void CStatistics::IncrementRepickCount ( void )
{

	m_lLabelsRepicked++;

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetRepickCount
//
//	Description:
//		Retrieve the total number of labels repicked.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//		Applicator::Run
//
/////////////////////////////////////////////////////////////////////////////////////

long CStatistics::GetRepickCount ( void )
{

	return ( m_lLabelsRepicked );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		IncrementPanelCount
//
//	Description:
//		Increment the number of completed boards.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//		Applicator::Run
//
/////////////////////////////////////////////////////////////////////////////////////

void CStatistics::IncrementPanelCount ( void )
{

	m_lPanelsCompleted++;

}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetPanelCount
//
//	Description:
//		Get the number of complete boards.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//		Applicator::Run
//
/////////////////////////////////////////////////////////////////////////////////////

long CStatistics::GetPanelCount ( void )
{

	return ( m_lPanelsCompleted );

}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetLogFilePath
//
//	Description:
//		Get the output log filename.
//
//	Arguments:
//		None
//
//	Return:
//		Filename.
//
//	Called by:
//		Applicator::
//
/////////////////////////////////////////////////////////////////////////////////////

CString CStatistics::GetLogFile ( void )
{

	return ( m_csLogFile );

}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetLogFile
//
//	Description:
//		Set the output log filename.
//
//	Arguments:
//		Log filename
//
//	Return:
//		None
//
//	Called by:
//		Applicator::
//
/////////////////////////////////////////////////////////////////////////////////////

void CStatistics::SetLogFile ( CString csLogFile )
{

	m_csLogFile = csLogFile;


}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetRefreshRate
//
//	Description:
//		Get the refresh rate.
//
//	Arguments:
//		None
//
//	Return:
//		Refresh rate.
//
//	Called by:
//		Applicator::
//
/////////////////////////////////////////////////////////////////////////////////////

int CStatistics::GetRefreshRate ( void )
{

	return ( m_nRefreshRate );

}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetRefreshRate
//
//	Description:
//		Set the refresh rate.
//
//	Arguments:
//		Refresh rate.
//
//	Return:
//		None
//
//	Called by:
//		Applicator::
//
/////////////////////////////////////////////////////////////////////////////////////

void CStatistics::SetRefreshRate ( int nRefreshRate )
{

	m_nRefreshRate = nRefreshRate;

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		IsStatisticsEnabled
//
//	Description:
//		Determine if statistics are enabled.
//
//	Arguments:
//		None
//
//	Return:
//		Enable/disable status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CStatistics::IsStatisticsEnabled ( void )
{

	return ( m_bUseStatistics );

}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetEnableStatistics
//
//	Description:
//		Set the statistics enable/disable flag.
//
//	Arguments:
//		enable/disable flag.
//
//	Return:
//		None
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

void CStatistics::SetEnableStatistics ( BOOL bEnable )
{

	m_bUseStatistics = bEnable;

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetUpdateRate
//
//	Description:
//		Get the log file update rate.
//
//	Arguments:
//		None
//
//	Return:
//		Update rate.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

int CStatistics::GetUpdateRate ( void )
{

	return ( m_nUpdateRate );

}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetUpdateRate
//
//	Description:
//		Set the log file update rate.
//
//	Arguments:
//		Refresh rate.
//
//	Return:
//		None
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

void CStatistics::SetUpdateRate ( int nUpdateRate )
{

	m_nUpdateRate = nUpdateRate;

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		UpdateStatisticalDB
//
//	Description:
//		Update the statistics to the computype
//		statistics database.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CStatistics::UpdateStatisticsDB ( void )
{


	CDaoDatabase	StatDB;

	BOOL
		bGoodUpdate;


	// Open computype statistics database.

	TRY
	{
		StatDB.Open ( "c:\\computype\\database\\statistics.mdb" );
	} 
	CATCH_ALL(e)
	{

		if ( !m_bDisplayNoDB )
		{
			AfxMessageBox("The program could not find the Computype statistics database.\n"
							  "The Statistics.mdb database file should reside in the "
							  "c:\\computype\\database folder.\n\nStatistics will not be saved "
							  "to the Computype database. This message will not be repeated.");
			m_bDisplayNoDB = TRUE;
			return ( FALSE );
		}
		else
			return ( FALSE );
	}
	END_CATCH_ALL

	// Update all totals.

	bGoodUpdate = UpdateTotalTable ( &StatDB );

	if ( bGoodUpdate && m_csProductName != " " )
		bGoodUpdate = UpdateProductTotalTable ( &StatDB );

	StatDB.Close();

	return ( bGoodUpdate );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		UpdateTotalTable
//
//	Description:
//		Update the total statistics to the computype
//		statistics database.
//
//	Arguments:
//		Pointer to database object
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CStatistics::UpdateTotalTable ( CDaoDatabase *StatDB )
{

	long			
		lPanelCycleTime,
		lLabelsApplied,
		lLabelsRescanned,
		lLabelsRepicked,
		lPanelsCompleted;

	float
		fTimeInRunMode,
		fTimeInIdleMode,
		fTimeInSetupMode;

	int nCount;
	COleVariant var;
	CString csTemp = " ";
	CString csJob = " ";
	char *pszTemp;

	CDaoRecordset	*recTotals;


	// Get totals table.

	recTotals = new CDaoRecordset( StatDB );
	csTemp = "Select * from tbl_totals" ;  

	recTotals->Open ( AFX_DAO_USE_DEFAULT_TYPE, csTemp );
	
	nCount = recTotals->GetRecordCount();

	if ( nCount < 1 )
	{

		// Unable to find database records.

		recTotals->Close();
		delete recTotals;
		return ( FALSE );
	}


	recTotals->MoveFirst();


	recTotals->GetFieldValue ( "time_in_run_mode", var );
	csTemp = var.pbVal;
	fTimeInRunMode = (float)atof ( (const char *)csTemp );

	recTotals->GetFieldValue ( "time_in_idle_mode", var );
	csTemp = var.pbVal;
	fTimeInIdleMode = (float)atof ( (const char *)csTemp );

	recTotals->GetFieldValue ( "time_in_setup_mode", var );
	csTemp = var.pbVal;
	fTimeInSetupMode = (float)atof ( (const char *)csTemp );

	recTotals->GetFieldValue ( "panel_cycle_time", var );
	csTemp = var.pbVal;
	lPanelCycleTime = atol ( (const char *)csTemp );

	recTotals->GetFieldValue ( "labels_applied", var );
	csTemp = var.pbVal;
	lLabelsApplied = atol ( (const char *)csTemp );

	recTotals->GetFieldValue ( "labels_rescanned", var );
	csTemp = var.pbVal;
	lLabelsRescanned = atol ( (const char *)csTemp );

	recTotals->GetFieldValue ( "labels_repicked", var );
	csTemp = var.pbVal;
	lLabelsRepicked = atol ( (const char *)csTemp );

	recTotals->GetFieldValue ( "panels_completed", var );
	csTemp = var.pbVal;
	lPanelsCompleted = atol ( (const char *)csTemp );

	// Update values.

	lPanelCycleTime  = m_lPanelCycleTime;		// Not an accumulation
	fTimeInRunMode   += m_fTimeInRunMode;
	fTimeInIdleMode  += m_fTimeInIdleMode;
	fTimeInSetupMode += m_fTimeInSetupMode;
	lLabelsApplied   += m_lLabelsApplied;
	lLabelsRescanned += m_lLabelsRescanned;
	lLabelsRepicked  += m_lLabelsRepicked;
	lPanelsCompleted += m_lPanelsCompleted;

	// Write to database.

	recTotals->MoveFirst();
	
	csTemp.Format ( "%f", fTimeInRunMode );

	pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
	recTotals->Edit();
	recTotals->SetFieldValue ( "time_in_run_mode", pszTemp);
	recTotals->Update();
	csTemp.ReleaseBuffer();

	csTemp.Format ( "%f", fTimeInIdleMode );

	pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
	recTotals->Edit();
	recTotals->SetFieldValue ( "time_in_idle_mode", pszTemp );
	recTotals->Update();
	csTemp.ReleaseBuffer();

	csTemp.Format ( "%f", fTimeInSetupMode );

	pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
	recTotals->Edit();
	recTotals->SetFieldValue ( "time_in_setup_mode", pszTemp );
	recTotals->Update();
	csTemp.ReleaseBuffer();

	csTemp.Format ( "%ld", lPanelCycleTime );

	pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
	recTotals->Edit();
	recTotals->SetFieldValue ( "panel_cycle_time", pszTemp );
	recTotals->Update();
	csTemp.ReleaseBuffer();

	csTemp.Format ( "%ld", lLabelsApplied );

	pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
	recTotals->Edit();
	recTotals->SetFieldValue ( "labels_applied", pszTemp );
	recTotals->Update();
	csTemp.ReleaseBuffer();

	csTemp.Format ( "%ld", lLabelsRescanned );

	pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
	recTotals->Edit();
	recTotals->SetFieldValue ( "labels_rescanned", pszTemp );
	recTotals->Update();
	csTemp.ReleaseBuffer();

	csTemp.Format ( "%ld", lLabelsRepicked );

	pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
	recTotals->Edit();
	recTotals->SetFieldValue ( "labels_repicked", pszTemp );
	recTotals->Update();
	csTemp.ReleaseBuffer();

	csTemp.Format ( "%ld", lPanelsCompleted );

	pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
	recTotals->Edit();
	recTotals->SetFieldValue ( "panels_completed", pszTemp );
	recTotals->Update();
	csTemp.ReleaseBuffer();

	recTotals->Close();
	delete recTotals;

	return ( TRUE );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		UpdateProductTotalTable
//
//	Description:
//		Update the product total statistics to the computype
//		statistics database.
//
//	Arguments:
//		Pointer to database object
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CStatistics::UpdateProductTotalTable ( CDaoDatabase *StatDB )
{

	BOOL
		bFound;

	long			
		lPanelCycleTime,
		lLabelsApplied,
		lLabelsRescanned,
		lLabelsRepicked,
		lPanelsCompleted;

	float
		fTimeInRunMode,
		fTimeInIdleMode,
		fTimeInSetupMode;

	int nCount;
	COleVariant var;
	CString csTemp = " ";
	CString csJob = " ";
	char *pszTemp;

	CDaoRecordset	*recProductTotals;


	// Get product totals table.

	recProductTotals = new CDaoRecordset( StatDB );
	csTemp = "Select * from tbl_product_totals" ;  

	recProductTotals->Open ( AFX_DAO_USE_DEFAULT_TYPE, csTemp );
	
	nCount = recProductTotals->GetRecordCount();

	if ( nCount < 1 )
	{

		recProductTotals->Close();
		delete recProductTotals;
		return ( FALSE );
	}

	if ( nCount > 0 )
	{
		recProductTotals->MoveFirst();

		while ( !recProductTotals->IsEOF() )
		{
			recProductTotals->GetFieldValue ( "product_name", var );
			csTemp = var.pbVal;
			if ( m_csProductName == csTemp  )
			{

				recProductTotals->GetFieldValue ( "time_in_run_mode", var );
				csTemp = var.pbVal;
				fTimeInRunMode = (float)atof ( (const char *)csTemp );

				recProductTotals->GetFieldValue ( "time_in_idle_mode", var );
				csTemp = var.pbVal;
				fTimeInIdleMode = (float)atof ( (const char *)csTemp );

				recProductTotals->GetFieldValue ( "time_in_setup_mode", var );
				csTemp = var.pbVal;
				fTimeInSetupMode = (float)atof ( (const char *)csTemp );

				recProductTotals->GetFieldValue ( "panel_cycle_time", var );
				csTemp = var.pbVal;
				lPanelCycleTime = atol ( (const char *)csTemp );

				recProductTotals->GetFieldValue ( "labels_applied", var );
				csTemp = var.pbVal;
				lLabelsApplied = atol ( (const char *)csTemp );

				recProductTotals->GetFieldValue ( "labels_rescanned", var );
				csTemp = var.pbVal;
				lLabelsRescanned = atol ( (const char *)csTemp );

				recProductTotals->GetFieldValue ( "labels_repicked", var );
				csTemp = var.pbVal;
				lLabelsRepicked = atol ( (const char *)csTemp );

				recProductTotals->GetFieldValue ( "panels_completed", var );
				csTemp = var.pbVal;
				lPanelsCompleted = atol ( (const char *)csTemp );

				break;

			}
			
			recProductTotals->MoveNext();
		}
	}

	// Update the database.

	bFound = FALSE;

	if ( nCount > 0 )
	{
		recProductTotals->MoveFirst();

		while ( !recProductTotals->IsEOF() )
		{
			recProductTotals->GetFieldValue ( "product_name", var );
			csTemp = var.pbVal;
			if ( m_csProductName == csTemp  )
			{

				// Update values.

				lPanelCycleTime  = m_lPanelCycleTime;	// Not an accumulation.
				fTimeInRunMode   += m_fTimeInRunMode;
				fTimeInIdleMode  += m_fTimeInIdleMode;
				fTimeInSetupMode += m_fTimeInSetupMode;
				lLabelsApplied   += m_lLabelsApplied;
				lLabelsRescanned += m_lLabelsRescanned;
				lLabelsRepicked  += m_lLabelsRepicked;
				lPanelsCompleted += m_lPanelsCompleted;

				csTemp.Format ( "%f", fTimeInRunMode );

				pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
				recProductTotals->Edit();
				recProductTotals->SetFieldValue ( "time_in_run_mode", pszTemp );
				recProductTotals->Update();
				csTemp.ReleaseBuffer();

				csTemp.Format ( "%f", fTimeInIdleMode );

				pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
				recProductTotals->Edit();
				recProductTotals->SetFieldValue ( "time_in_idle_mode", pszTemp );
				recProductTotals->Update();
				csTemp.ReleaseBuffer();

				csTemp.Format ( "%f", fTimeInSetupMode );

				pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
				recProductTotals->Edit();
				recProductTotals->SetFieldValue ( "time_in_setup_mode", pszTemp );
				recProductTotals->Update();
				csTemp.ReleaseBuffer();

				csTemp.Format ( "%ld", lPanelCycleTime );

				pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
				recProductTotals->Edit();
				recProductTotals->SetFieldValue ( "panel_cycle_time", pszTemp );
				recProductTotals->Update();
				csTemp.ReleaseBuffer();

				csTemp.Format ( "%ld", lLabelsApplied );

				pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
				recProductTotals->Edit();
				recProductTotals->SetFieldValue ( "labels_applied", pszTemp );
				recProductTotals->Update();
				csTemp.ReleaseBuffer();

				csTemp.Format ( "%ld", lLabelsRescanned );

				pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
				recProductTotals->Edit();
				recProductTotals->SetFieldValue ( "labels_rescanned", pszTemp );
				recProductTotals->Update();
				csTemp.ReleaseBuffer();

				csTemp.Format ( "%ld", lLabelsRepicked );

				pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
				recProductTotals->Edit();
				recProductTotals->SetFieldValue ( "labels_repicked", pszTemp );
				recProductTotals->Update();
				csTemp.ReleaseBuffer();

				csTemp.Format ( "%ld", lPanelsCompleted );

				pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
				recProductTotals->Edit();
				recProductTotals->SetFieldValue ( "panels_completed", pszTemp );
				recProductTotals->Update();
				csTemp.ReleaseBuffer();

				bFound = TRUE;

				break;

			}
			
			recProductTotals->MoveNext();
		}
	}

	if ( !bFound )
	{

		// Job record not found so insert a new record.
	
		// Update values.

		lPanelCycleTime  = m_lPanelCycleTime;
		fTimeInRunMode   = m_fTimeInRunMode;
		fTimeInIdleMode  = m_fTimeInIdleMode;
		fTimeInSetupMode = m_fTimeInSetupMode;
		lLabelsApplied   = m_lLabelsApplied;
		lLabelsRescanned = m_lLabelsRescanned;
		lLabelsRepicked  = m_lLabelsRepicked;
		lPanelsCompleted = m_lPanelsCompleted;

		recProductTotals->AddNew();

		csTemp = m_csProductName;

		pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
		recProductTotals->SetFieldValue ( "product_name", pszTemp );
		csTemp.ReleaseBuffer();

		csTemp.Format ( "%f", fTimeInRunMode );

		pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
		recProductTotals->SetFieldValue ( "time_in_run_mode", pszTemp );
		csTemp.ReleaseBuffer();

		csTemp.Format ( "%f", fTimeInIdleMode );

		pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
		recProductTotals->SetFieldValue ( "time_in_idle_mode", pszTemp );
		csTemp.ReleaseBuffer();

		csTemp.Format ( "%f", fTimeInSetupMode );

		pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
		recProductTotals->SetFieldValue ( "time_in_setup_mode", pszTemp );
		csTemp.ReleaseBuffer();

		csTemp.Format ( "%ld", lPanelCycleTime );

		pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
		recProductTotals->SetFieldValue ( "panel_cycle_time", pszTemp );
		csTemp.ReleaseBuffer();

		csTemp.Format ( "%ld", lLabelsApplied );

		pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
		recProductTotals->SetFieldValue ( "labels_applied", pszTemp );
		csTemp.ReleaseBuffer();

		csTemp.Format ( "%ld", lLabelsRescanned );

		pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
		recProductTotals->SetFieldValue ( "labels_rescanned", pszTemp );
		csTemp.ReleaseBuffer();

		csTemp.Format ( "%ld", lLabelsRepicked );

		pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
		recProductTotals->SetFieldValue ( "labels_repicked", pszTemp );
		csTemp.ReleaseBuffer();

		csTemp.Format ( "%ld", lPanelsCompleted );

		pszTemp = csTemp.GetBuffer ( csTemp.GetLength() );
		recProductTotals->SetFieldValue ( "panels_completed", pszTemp );
		csTemp.ReleaseBuffer();

		recProductTotals->Update();

	}

	recProductTotals->Close();
	delete recProductTotals;

	return ( TRUE );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		UpdateStatisticsFile
//
//	Description:
//		Update the statistics to a user specified log file.
//
//	Arguments:
//		Force user log flag.
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CStatistics::UpdateStatisticsFile ( void )
{

	CStdioFile 
		fTempFile,
		fLogFile;

	CString
		csProductName,
		csLine,
		csDate,
		csTime,
		csFileDate,
		csTemp;

	int
		nYear,
		nIndex,
		nLength;

	long			
		lPanelCycleTime,
		lLabelsApplied,
		lLabelsRescanned,
		lLabelsRepicked,
		lPanelsCompleted;

	float
		fTimeInRunMode,
		fTimeInIdleMode,
		fTimeInSetupMode;

	CTime 
		ctFileTime,
		ctNow;

	struct tm* 
		LocalTime;

	char tmpbuf[20];



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

	// Open logfile.

	if ( !fLogFile.Open ( c_csComputypeLog, CFile::modeCreate | CFile::modeRead | CFile::modeNoTruncate ) )
		return ( FALSE );

	fLogFile.SeekToBegin();

	// Open temp file Used to copy to customers file.

	if ( !fTempFile.Open ( "templog", CFile::modeCreate | CFile::modeWrite ) )
		return ( FALSE );


	// Get date from log.

	if ( !fLogFile.ReadString ( csLine ) )
	{

		// File is empty. All data is new.

		// Write date.

		fTempFile.WriteString (  "Date: " + csDate + "    " + csTime + "\n" );
	
		// Write time stamp.

		csTemp.Format ( "%ld", ctNow );
		fTempFile.WriteString (  "Time Stamp: " + csTemp + "\n" );
	
		// Write totals.

		csTemp.Format ( "%.2f,%.2f,%.2f,%ld,%ld,%ld,%ld,%ld",
								m_fTimeInRunMode,
								m_fTimeInIdleMode,
								m_fTimeInSetupMode,
								m_lPanelCycleTime,
								m_lLabelsApplied,
								m_lLabelsRescanned,
								m_lLabelsRepicked,
								m_lPanelsCompleted );
									
		fTempFile.WriteString (  "Totals:" + csTemp + "\n" );

		// Write product totals.

		fTempFile.WriteString (  m_csProductName + ":" + csTemp + "\n" );
	

	}
	else
	{
	
		// Write current date and time.

		fTempFile.WriteString ( "Date: " + csDate + "    " + csTime + "\n" );

		// Get time stamp of original write to file.

		if ( !fLogFile.ReadString ( csLine ) )
		{
			fLogFile.Close();
			fTempFile.Close();
			return ( FALSE );
		}

		// Parse the time stamp out.

		nIndex = csLine.Find ( ":" );
		nLength = csLine.GetLength();
		if ( nIndex == -1 )
		{
			fLogFile.Close();
			fTempFile.Close();
			return ( FALSE );
		}

		csTemp = csLine.Right ( nLength - nIndex - 1 );
		fTempFile.WriteString ( "Time Stamp:" + csTemp + "\n" );

		// Get totals line.

		if ( !fLogFile.ReadString ( csLine ) )
		{
			fLogFile.Close();
			fTempFile.Close();
			return ( FALSE );
		}

		// Parse the totals out.

		nIndex = csLine.Find ( ":" );
		nLength = csLine.GetLength();
		if ( nIndex == -1 )
		{
			fLogFile.Close();
			fTempFile.Close();
			return ( FALSE );
		}

		csLine = csLine.Right ( nLength - nIndex - 1 );

		if ( !ParseLine ( csLine,
								&lPanelCycleTime,
								&lLabelsApplied,
								&lLabelsRescanned,
								&lLabelsRepicked,
								&lPanelsCompleted,
								&fTimeInRunMode,
								&fTimeInIdleMode,
								&fTimeInSetupMode ) )
		{
			fLogFile.Close();
			fTempFile.Close();
			return ( FALSE );
		}

		// Always accumulate the stats for totals.

		lPanelCycleTime  = m_lPanelCycleTime;
		fTimeInRunMode   += m_fTimeInRunMode;
		fTimeInIdleMode  += m_fTimeInIdleMode;
		fTimeInSetupMode += m_fTimeInSetupMode;
		lLabelsApplied   += m_lLabelsApplied;
		lLabelsRescanned += m_lLabelsRescanned;
		lLabelsRepicked  += m_lLabelsRepicked;
		lPanelsCompleted += m_lPanelsCompleted;

		csTemp.Format ( "%.2f,%.2f,%.2f,%ld,%ld,%ld,%ld,%ld",
								fTimeInRunMode,
								fTimeInIdleMode,
								fTimeInSetupMode,
								lPanelCycleTime,
								lLabelsApplied,
								lLabelsRescanned,
								lLabelsRepicked,
								lPanelsCompleted );

		fTempFile.WriteString ( "Totals:" + csTemp + "\n" );


		// Loop through each product line.

		BOOL bFound;
		bFound = FALSE;
		while ( fLogFile.ReadString ( csLine ) )
		{

			// Parse the totals out.

			nIndex = csLine.Find ( ":" );
			nLength = csLine.GetLength();
			if ( nIndex == -1 )
			{
				fLogFile.Close();
				fTempFile.Close();
				return ( FALSE );
			}

			csProductName = csLine.Left ( nIndex );

			if ( csProductName != m_csProductName )
			{

				// This is not the line we need to update so just copy it over.
	
				fTempFile.WriteString ( csLine + "\n" );
			}
			else
			{

				bFound = TRUE;

				csLine = csLine.Right ( nLength - nIndex - 1 );

				if ( !ParseLine ( csLine,
										&lPanelCycleTime,
										&lLabelsApplied,
										&lLabelsRescanned,
										&lLabelsRepicked,
										&lPanelsCompleted,
										&fTimeInRunMode,
										&fTimeInIdleMode,
										&fTimeInSetupMode ) )
				{
					fLogFile.Close();
					fTempFile.Close();
					return ( FALSE );
				}

				// Accumulate the stats for product totals.

				lPanelCycleTime  = m_lPanelCycleTime;
				fTimeInRunMode   += m_fTimeInRunMode;
				fTimeInIdleMode  += m_fTimeInIdleMode;
				fTimeInSetupMode += m_fTimeInSetupMode;
				lLabelsApplied   += m_lLabelsApplied;
				lLabelsRescanned += m_lLabelsRescanned;
				lLabelsRepicked  += m_lLabelsRepicked;
				lPanelsCompleted += m_lPanelsCompleted;

				csTemp.Format ( "%.2f,%.2f,%.2f,%ld,%ld,%ld,%ld,%ld",
										fTimeInRunMode,
										fTimeInIdleMode,
										fTimeInSetupMode,
										lPanelCycleTime,
										lLabelsApplied,
										lLabelsRescanned,
										lLabelsRepicked,
										lPanelsCompleted );

				fTempFile.WriteString ( csProductName + ":" + csTemp + "\n" );
			}

		}	// End while loop through products.

		if ( !bFound && m_csProductName != " " )
		{

			// No match in log for product. Enter in new product stats.

			csTemp.Format ( "%.2f,%.2f,%.2f,%ld,%ld,%ld,%ld,%ld",
									m_fTimeInRunMode,
									m_fTimeInIdleMode,
									m_fTimeInSetupMode,
									m_lPanelCycleTime,
									m_lLabelsApplied,
									m_lLabelsRescanned,
									m_lLabelsRepicked,
									m_lPanelsCompleted );

			fTempFile.WriteString ( m_csProductName + ":" + csTemp + "\n" );

		}
	}	// End else update existing line.

	// Set tempfile to log file.

	fLogFile.Close ();
	fTempFile.Close ();
	CFile::Remove ( c_csComputypeLog );
	CFile::Rename ( "templog", c_csComputypeLog );

	return ( TRUE );

}





/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		ParseLine
//
//	Description:
//		Parse a line from the statistics file.
//
//	Arguments:
//		Line to be parsed
//		Panel cycle time
//		Number of labels applied
//		Number of rescans
//		Number of repicks
//		Number of panel completed.
//		Time in tun mode
//		Time in idle mode
//		Time in setup mode
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CStatistics::ParseLine ( CString csLine,
										long *lPanelCycleTime,
										long *lLabelsApplied,
										long *lLabelsRescanned,
										long *lLabelsRepicked,
										long *lPanelsCompleted,
										float *fTimeInRunMode,
										float *fTimeInIdleMode,
										float *fTimeInSetupMode )
{

	CString
		csTemp;

	int
		nIndex,
		nLength;


	// Get time in run mode.

	nIndex = csLine.Find ( "," );
	nLength = csLine.GetLength();
	if ( nIndex == -1 )
	{
		return ( FALSE );
	}
	csTemp = csLine.Left ( nIndex );

	*fTimeInRunMode = (float)atof ( (const char *)csTemp );

	csLine = csLine.Right ( nLength - nIndex - 1 );

	// Get time in idle mode.

	nIndex = csLine.Find ( "," );
	nLength = csLine.GetLength();
	if ( nIndex == -1 )
	{
		return ( FALSE );
	}
	csTemp = csLine.Left ( nIndex );

	*fTimeInIdleMode = (float)atof ( (const char *)csTemp );

	csLine = csLine.Right ( nLength - nIndex - 1 );

	// Get time in setup mode.

	nIndex = csLine.Find ( "," );
	nLength = csLine.GetLength();
	if ( nIndex == -1 )
	{
		return ( FALSE );
	}
	csTemp = csLine.Left ( nIndex );

	*fTimeInSetupMode = (float)atof ( (const char *)csTemp );

	csLine = csLine.Right ( nLength - nIndex - 1 );

	// Get board cycle time.

	nIndex = csLine.Find ( "," );
	nLength = csLine.GetLength();
	if ( nIndex == -1 )
	{
		return ( FALSE );
	}
	csTemp = csLine.Left ( nIndex );

	*lPanelCycleTime = atol ( (const char *)csTemp );

	csLine = csLine.Right ( nLength - nIndex - 1 );

	// Get number of labels applied.

	nIndex = csLine.Find ( "," );
	nLength = csLine.GetLength();
	if ( nIndex == -1 )
	{
		return ( FALSE );
	}
	csTemp = csLine.Left ( nIndex );

	*lLabelsApplied = atol ( (const char *)csTemp );

	csLine = csLine.Right ( nLength - nIndex - 1 );

	// Get number of rescans.

	nIndex = csLine.Find ( "," );
	nLength = csLine.GetLength();
	if ( nIndex == -1 )
	{
		return ( FALSE );
	}
	csTemp = csLine.Left ( nIndex );

	*lLabelsRescanned = atol ( (const char *)csTemp );

	csLine = csLine.Right ( nLength - nIndex - 1 );

	// Get number of repicks.

	nIndex = csLine.Find ( "," );
	nLength = csLine.GetLength();
	if ( nIndex == -1 )
	{
		return ( FALSE );
	}
	csTemp = csLine.Left ( nIndex );

	*lLabelsRepicked = atol ( (const char *)csTemp );

	csLine = csLine.Right ( nLength - nIndex - 1 );

	// Get number of panels completed.

	*lPanelsCompleted = atol ( (const char *)csLine );

	return ( TRUE );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		IsRefreshTime
//
//	Description:
//		Determine if it is time to refresh.
//
//	Arguments:
//		Current time.
//		Timestamp in file.
//
//	Return:
//		Status.
//
//	Called by:
//		UpdateStatistics
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CStatistics::IsRefreshTime ( void )
{

	struct tm* 
		tmNow;

	BOOL
		bRefresh = FALSE;

	CTime 
		ctFileTime;

	CTime 
		ctNow;

	struct tm*
		tmFileTime;

	int
		nNowDay,
		nNowMonth,
		nNowWeek,
		nNowYear,
		nNowHour,
		nNowMin,
		nNowSec,
		nFileDay,
		nFileMonth,
		nFileWeek,
		nFileYear,
		nFileHour,
		nFileMin,
		nFileSec;

	char tmpbuf[20];


	ctNow = CTime::GetCurrentTime();
	ctFileTime = GetFileTime();

	if ( ctFileTime == 0 )
		return ( FALSE );

	// Parse times into months, days and years.

	tmNow = ctNow.GetLocalTm ( NULL );
	nNowDay = tmNow->tm_mday;
	nNowMonth = tmNow->tm_mon;
	nNowYear = tmNow->tm_year;
	nNowHour = tmNow->tm_hour;
	nNowMin = tmNow->tm_min;
	nNowSec = tmNow->tm_sec;

	strftime( tmpbuf, 20, "%W", tmNow );
	nNowWeek = atoi ( tmpbuf );

	tmFileTime = ctFileTime.GetLocalTm ( NULL );
	nFileDay = tmFileTime->tm_mday;
	nFileMonth = tmFileTime->tm_mon;
	nFileYear = tmFileTime->tm_year;
	nFileHour = tmFileTime->tm_hour;
	nFileMin = tmFileTime->tm_min;
	nFileSec = tmFileTime->tm_sec;

	strftime( tmpbuf, 20, "%W", tmFileTime );
	nFileWeek = atoi ( tmpbuf );


	// Determine if it is about time to refresh.
	// Let's just take our time.


	switch ( m_nRefreshRate )
	{

		case REFRESH_ONCE_A_DAY:
			if ( nFileDay != nNowDay )
				bRefresh = TRUE;
			break;

		case REFRESH_ONCE_A_WEEK:	// Monday is the first day of the week.

			if ( nNowWeek != nFileWeek )
				bRefresh = TRUE;

			break;

		case REFRESH_ONCE_A_MONTH:
			if ( nFileMonth != nNowMonth )
				bRefresh = TRUE;
			break;

		case REFRESH_ONCE_A_YEAR:
			if ( nFileYear != nNowYear )
				bRefresh = TRUE;
			break;

		case REFRESH_NEVER:
			break;

		default:		// Refresh every day.
			if ( nFileDay != nNowDay )
				bRefresh = TRUE;
			break;
			
	}

	return ( bRefresh );
}





/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		TimeToUpdate
//
//	Description:
//		Determine if it is time to update the statistical log file.
//
//	Arguments:
//		None.
//
//	Return:
//		Status
//
//	Called by:
//		UpdateStatistics
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CStatistics::TimeToUpdate ( void )
{

	BOOL
		bUpdate = FALSE;


	switch ( m_nUpdateRate )
	{

		case EVERY_MIN:
			bUpdate = TRUE;
			break;

		case EVERY_HOUR:
			if ( CheckLogForTimeChange ( EVERY_HOUR ) )
				bUpdate = TRUE;
			break;

		case EVERY_DAY:
			if ( CheckLogForTimeChange ( EVERY_DAY ) )
				bUpdate = TRUE;
			break;

		default:			// Other.
			if ( m_nUpdateRate != 0 )
			{
				if ( CheckLogForTimeChange ( m_nUpdateRate ) )
					bUpdate = TRUE;
			}
			else
				bUpdate = FALSE;

			break;

	}

	return ( bUpdate );

}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		CheckLogForTimeChange
//
//	Description:
//		Determine if the update interval time has been exceeded
//    based on the time in the statistical log file.
//
//	Arguments:
//		Update interval.
//
//	Return:
//		Status
//
//	Called by:
//		TimeToUpdate
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CStatistics::CheckLogForTimeChange ( int nUpdateRate )
{

	CTime 
		ctFileTime,
		ctNow;

	CTimeSpan elapsedTime;

	struct tm* 
		tmNow;

	struct tm* 
		tmFileTime;

	BOOL
		bUpdate = FALSE;

	CString
		csTemp,
		csLine;

	long
		lDuration;

	int
		nNowDay,
		nNowMonth,
		nNowYear,
		nNowHour,
		nNowMin,
		nNowSec,
		nFileDay,
		nFileMonth,
		nFileYear,
		nFileHour,
		nFileMin,
		nFileSec;


	ctNow = CTime::GetCurrentTime();
	ctFileTime = GetFileTime();

	if ( ctFileTime == 0 )
		return ( FALSE );

	// Parse times into months, days and years.

	tmNow = ctNow.GetLocalTm ( NULL );
	nNowDay = tmNow->tm_mday;
	nNowMonth = tmNow->tm_mon;
	nNowYear = tmNow->tm_year;
	nNowHour = tmNow->tm_hour;
	nNowMin = tmNow->tm_min;
	nNowSec = tmNow->tm_sec;

	tmFileTime = ctFileTime.GetLocalTm ( NULL );
	nFileDay = tmFileTime->tm_mday;
	nFileMonth = tmFileTime->tm_mon;
	nFileYear = tmFileTime->tm_year;
	nFileHour = tmFileTime->tm_hour;
	nFileMin = tmFileTime->tm_min;
	nFileSec = tmFileTime->tm_sec;


	// Compare the file time with the current time and determine if
	// it is time to update the log file.

	switch ( nUpdateRate )
	{

		case EVERY_HOUR:
			if ( nNowHour !=nFileHour )
				bUpdate = TRUE;
			break;

		case EVERY_DAY:
			if ( nNowDay != nFileDay )
				bUpdate = TRUE;
			break;

		default:			// Other.
			
			// The update rate is in number of minutes. Determine the
			// duration in minutes between the current time and the file time.

			elapsedTime = ctNow - ctFileTime;				// Get elapsed seconds.
			lDuration = elapsedTime.GetTotalMinutes();	// Convert to minutes.

			if ( lDuration >= nUpdateRate )
				bUpdate = TRUE;									// Time to do its thing.

			break;

	}

	return ( bUpdate );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetFileTime
//
//	Description:
//		Get the time stamp from the statistics file.
//
//	Arguments:
//		None.
//
//	Return:
//		File time stamp
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

CTime CStatistics::GetFileTime ( void )
{


	CStdioFile
		fLogFile;

	CString
		csTemp,
		csLine;

	int
		nLength,
		nIndex;

	int
		nHour,
		nMin,
		nSec,
		nMonth,
		nDay,
		nYear;

	// Get time from log file.

	// Open logfile.

	if ( !fLogFile.Open ( c_csComputypeLog, CFile::modeRead ) )
		return ( 0 );	

	// Get date and write current date to file.

	if ( !fLogFile.ReadString ( csLine ) )
	{
		fLogFile.Close();
		return ( 0 );
	}

	// Get time stamp of original write to file.

//	if ( !fLogFile.ReadString ( csLine ) )
//	{
//		fLogFile.Close();
//		return ( "" );
//	}

	// Parse the time stamp out.

	nIndex = csLine.Find ( ":" );
	nLength = csLine.GetLength();
	if ( nIndex == -1 )
	{
		fLogFile.Close();
		return ( 0 );
	}

	fLogFile.Close();

	csTemp = csLine.Right ( nLength - nIndex - 1 );

	nMonth = atoi ( csTemp.Mid ( 1, 2 ) );
	nDay   = atoi ( csTemp.Mid ( 4, 2 ) );
	nYear  = atoi ( csTemp.Mid ( 7, 4 ) );
	nHour  = atoi ( csTemp.Mid ( 15, 2 ) );
	nMin   = atoi ( csTemp.Mid ( 18, 2 ) );
	nSec   = atoi ( csTemp.Mid ( 21, 2 ) );

	CTime ctFileTime ( nYear, nMonth, nDay, nHour, nMin, nSec );
	return ( ctFileTime );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		RefreshStatistics
//
//	Description:
//		Copy local statistical file to archived time stamped file.
//
//	Arguments:
//		None.
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CStatistics::RefreshStatistics ( void )
{

	CTime 
		ctNow;

	CString
		csTemp,
		csTime;

	int
		nLength;

	ctNow = CTime::GetCurrentTime();

	csTime.Format ( "%ld", ctNow );
	csTime += ".log";

	nLength = m_csLogFile.GetLength();

	if ( nLength > 0 )
	{

		csTemp = m_csLogFile;
		if ( m_csLogFile.Mid ( nLength-1, 1 ) == "\\" )
			csTemp += csTime;
		else
			csTemp += "\\" + csTime;

		CFile::Rename ( c_csComputypeLog, csTemp );

	}

	return ( TRUE );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetTimeToUpdate
//
//	Description:
//		Set the time to update flag.
//
//	Arguments:
//		Time to update flag.
//
//	Return:
//		None.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

void CStatistics::SetTimeToUpdate ( BOOL bTimeToUpdate )
{

	m_bTimeToUpdate = bTimeToUpdate;

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		IsTimeToUpdate
//
//	Description:
//		Retrieve the time to update flag.
//
//	Arguments:
//		None
//
//	Return:
//		Time to update.
//
//	Called by:
//		Applicator::Run
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CStatistics::IsTimeToUpdate ( void )
{

	return ( m_bTimeToUpdate );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		UpdateTimers
//
//	Description:
//		Get latest times for enabled timers.
//
//	Arguments:
//		None
//
//	Return:
//		None
//
//	Called by:
//		UpdateStatistics
//
/////////////////////////////////////////////////////////////////////////////////////

void CStatistics::UpdateTimers ( void )
{

	if ( m_bInRunModeTime )
	{
		EndRunModeTime();
		StartRunModeTime();
	}

	if ( m_bInIdleModeTime )
	{
		EndIdleModeTime();
		StartIdleModeTime();
	}

	if ( m_bInSetupModeTime )
	{
		EndSetupModeTime();
		StartSetupModeTime();
	}

}


