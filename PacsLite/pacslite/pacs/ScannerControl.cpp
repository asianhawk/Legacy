// ScannerControl.cpp: implementation of the CScannerControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PACS.h"
#include "ScannerControl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CScannerControl::CScannerControl()
{
	m_bScannerActive=FALSE;

}

CScannerControl::~CScannerControl()
{

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		Initialize
//
//	Description:
//		Initialize all scanners and control.
//
//	Arguments:
//		Pointer to database.
//
//	Return:
//		Status.
//
//	Called by:
//		Applicator::Initialize
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CScannerControl::Initialize ( CDatabase *poDatabase, CSNManager *poSNManager, CPrinterControl *poPrinter )
{
	BOOL 
		bInit,
		bUse;

	CString
		csTemp;


	m_bInitialized = TRUE;

	// Initialize all scanners. This is done to all. If the scanner is not in
	// use for this customer, we just ignore it. We do this because we don't
	// know if the scanner is used yet and to minimize the amount of custom
	// work that is required for each customer.

	bInit = m_oPlacementScanner.Initialize ( poDatabase, PLACEMENT_SCANNER, poSNManager, &bUse, poPrinter );

	if ( !bInit && bUse )
	{
		m_bInitialized = FALSE;
		m_csErrorString.LoadString ( IDS_ERR_PLACEMENT_SCANNER_INIT );
		return ( FALSE );
	}
	
	m_bScannerActive=bUse;
	m_bInitialized = bInit;

	return ( m_bInitialized );

}

BOOL CScannerControl::Initialize ( CDatabase *poDatabase, CSNManager *poSNManager )
{
	BOOL 
		bInit,
		bUse;

	CString
		csTemp;


	m_bInitialized = TRUE;

	// Initialize all scanners. This is done to all. If the scanner is not in
	// use for this customer, we just ignore it. We do this because we don't
	// know if the scanner is used yet and to minimize the amount of custom
	// work that is required for each customer.

	bInit = m_oPlacementScanner.Initialize ( poDatabase, PLACEMENT_SCANNER, poSNManager, &bUse );

	if ( !bInit && bUse )
	{
		m_bInitialized = FALSE;
		m_csErrorString.LoadString ( IDS_ERR_PLACEMENT_SCANNER_INIT );
		return ( FALSE );
	}
	
	m_bScannerActive=bUse;
	m_bInitialized = bInit;

	return ( m_bInitialized );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		Reset
//
//	Description:
//		Reset the scanner.
//
//	Arguments:
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CScannerControl::Reset ()
{


	return ( m_oPlacementScanner.Reset() );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		ScanLabel
//
//	Description:
//		Scan the label.
//
//	Arguments:
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CScannerControl::ScanLabel (CString *csLabelScanned, 
								 CDioController *poDIOController, 
								 CString csPrintedLabel,
								 BOOL bVerifyScan )
{

	BOOL bStatus;
	m_csScannedLabel="";
	bStatus = m_oPlacementScanner.ScanLabel ( csLabelScanned, 
	   										  poDIOController,
											  csPrintedLabel,
											  bVerifyScan );


	if (bStatus)
	{

		m_csScannedLabel=m_oPlacementScanner.GetScannedLabel();
	}
	else
	{

		m_csScannedLabel=m_oPlacementScanner.GetScannedLabel();

		if (csLabelScanned->IsEmpty())
			m_csScannedLabel="Scan Failed";
		else
			m_csScannedLabel=*csLabelScanned;	//user would like to see what is goin on

	}

	return ( bStatus );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		ScanLabel
//
//	Description:
//		Scan the label.
//
//	Arguments:
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////
	
BOOL CScannerControl::UpdateScannerAttributes (BOOL bUse,
											 BOOL bEnable,
											 int nType,
											 CString csTrigger,
											 CString csReset )
{
	BOOL		bStatus;

	m_oPlacementScanner.SetUse ( bUse );
	m_oPlacementScanner.SetType ( nType );
	m_oPlacementScanner.SetEnable ( bEnable );
	m_oPlacementScanner.SetTrigger ( csTrigger );
	m_oPlacementScanner.SetReset ( csReset );

	bStatus = m_oPlacementScanner.Refresh();
	return ( bStatus );
}




BOOL CScannerControl::GetEnable ()
{


	return ( m_oPlacementScanner.GetEnable() );

}





BOOL CScannerControl::GetUse ()
{


	return ( m_oPlacementScanner.GetUse());

}




CString CScannerControl::GetVersionString()
{
	CString	csVersionString;
	
	m_oPlacementScanner.GetVersion(&csVersionString);
	return (csVersionString);
}

CString CScannerControl::GetResetString()
{
	return (m_oPlacementScanner.GetReset());
}

CString CScannerControl::SingleTrigger()
{
	CString	csScanString;

	// start at empty
	csScanString.Empty();
	
	csScanString = m_oPlacementScanner.SingleTrigger();
	return (csScanString);
}

BOOL CScannerControl::SetResetString(CString csResetString)
{
	m_oPlacementScanner.SetReset(csResetString);
	return TRUE;
}


BOOL CScannerControl::GetMatchLabel ()
{
			
	return (m_oPlacementScanner.GetMatchLabel());
}

BOOL CScannerControl::IsScannerActive()
{

	return m_bScannerActive;

}