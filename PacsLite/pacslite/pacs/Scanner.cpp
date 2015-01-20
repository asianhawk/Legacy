// Scanner.cpp: implementation of the CScanner class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PACS.h"
#include "Scanner.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CScanner::CScanner()
{

}

CScanner::~CScanner()
{

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		Initialize
//
//	Description:
//		Initialize the scanners.
//
//	Arguments:
//		Pointer to database.
//		Scanner location ( scanner name in database ).
//		Pointer to serial number manager.
//		Use scanner flag.
//
//	Return:
//		Status.
//
//	Called by:
//		CScannerControl::Initialize
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CScanner::Initialize ( CDatabase *poDatabase, 
									 int nScannerLocation,
									 CSNManager * oSNManager,
									 BOOL *bUseScanner )
{

	BOOL 
		bEnable,
		bUse;

	int 
		nType;

	CString
		csTriggerOn,
		csTriggerOff,
		csResetString,
		csName;



	// Get scanner information from database.

	m_nScannerLocation = nScannerLocation;
	m_poDatabase = poDatabase;
	m_poSNManager = oSNManager;


	csName = GetScannerName();
	
	m_bInitialized = m_poDatabase->GetScannerAttributes ( csName, 
														 &bUse,
														 &bEnable,
														 &nType,
														 &csTriggerOn,
														 &csTriggerOff,
														 &csResetString );

	// NOTE: The use flag should never change during runtime. It is setup 
	// as more of a hardware constraint. It can not change throught 
	// runtime setup.

	m_bUse  = bUse;
	m_nType = nType;
	m_bEnable = bEnable;
	if (m_nType ==WELCHALLYN_4700)
	{
	    m_csReset = c_csWelchAllyn_Preamble+csResetString;
	    m_csTrigger =csTriggerOn;
		m_csTriggerOff = csTriggerOff;
	}
	else if (m_nType ==WELCHALLYN_3900)
	{
	    m_csReset = c_csWelchAllyn_Preamble+csResetString;
	    m_csTrigger =c_csWelchAllyn_3900_TriggerOn;
		m_csTriggerOff = c_csWelchAllyn_3900_TriggerOff;

	}
	else
	{
	    m_csReset = csResetString;
	    m_csTrigger = csTriggerOn;


	}

	if ( !m_bUse || !m_bEnable )
	{
		*bUseScanner = FALSE;
		m_bInitialized = FALSE;
		return ( TRUE );			// Scanner is not used so forget the rest.
	}
	else
		*bUseScanner = TRUE;

	// Ensure that the trigger character is in reset string if applicable.


	// Initialize hardware.

	m_bInitialized = InitializeScannerHardware ( );

	return ( m_bInitialized );

}


BOOL CScanner::Initialize ( CDatabase *poDatabase, 
									 int nScannerLocation,
									 CSNManager * oSNManager,
									 BOOL *bUseScanner,
									 CPrinterControl *oPrinter)
{

	BOOL 
		bEnable,
		bUse;

	int 
		nType;

	CString
		csTriggerOn,
		csTriggerOff,
		csResetString,
		csName;



	// Get scanner information from database.

	m_nScannerLocation = nScannerLocation;
	m_poDatabase = poDatabase;
	m_poSNManager = oSNManager;
	m_poPrinter = oPrinter;


	csName = GetScannerName();
	
	m_bInitialized = m_poDatabase->GetScannerAttributes ( csName, 
														 &bUse,
														 &bEnable,
														 &nType,
														 &csTriggerOn,
														 &csTriggerOff,
														 &csResetString );

	// NOTE: The use flag should never change during runtime. It is setup 
	// as more of a hardware constraint. It can not change throught 
	// runtime setup.

	m_bUse  = bUse;
	m_nType = nType;
	m_bEnable = bEnable;
	if (m_nType ==WELCHALLYN_4700)
	{
	    m_csReset = c_csWelchAllyn_Preamble+csResetString;
	    m_csTrigger =csTriggerOn;
		m_csTriggerOff = csTriggerOff;
	}
	else if (m_nType ==WELCHALLYN_3900)
	{
	    m_csReset = c_csWelchAllyn_Preamble+csResetString;
	    m_csTrigger =c_csWelchAllyn_3900_TriggerOn;
		m_csTriggerOff = c_csWelchAllyn_3900_TriggerOff;
	}

	else
	{
	    m_csReset = csResetString;
	    m_csTrigger = csTriggerOn;


	}

	if ( !m_bUse || !m_bEnable )
	{
		*bUseScanner = FALSE;
		m_bInitialized = FALSE;
		return ( TRUE );			// Scanner is not used so forget the rest.
	}
	else
		*bUseScanner = TRUE;

	// Ensure that the trigger character is in reset string if applicable.


	// Initialize hardware.

	m_bInitialized = InitializeScannerHardware ( );

	return ( m_bInitialized );

}


void CScanner::SetUse ( BOOL bUse )
{

	m_bUse = bUse;

}


void CScanner::SetType ( int nType )
{

	m_nType = nType;

}



BOOL CScanner::GetUse ()
{

	return ( m_bUse );

}


int CScanner::GetType ()
{

	return ( m_nType );

}



BOOL CScanner::GetEnable ()
{

	return ( m_bEnable );

}


void CScanner::SetEnable ( BOOL bEnable )
{

	m_bEnable = bEnable;

}



void CScanner::SetTrigger ( CString csTrigger )
{

	m_csTrigger = csTrigger;

}



void CScanner::SetReset ( CString csReset )
{

	m_csReset = csReset;

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		Refresh
//
//	Description:
//		Scanner attributes may have changed and we may have to initialize the
//    com port and the scanner.
//
//	Arguments:
//		None.
//
//	Return:
//		Status.
//
//	Called by:
//		CScannerControl::UpdateScannerAttributes
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CScanner::Refresh ( )
{

	// Check for prior conditions.

	if ( m_bEnable && !m_bInitialized )
	{

		// The scanner attributes have been swtiched to enabled
		// and the scanner hardware has not been initialized
		// yet. Initialize the scanner.

		m_bInitialized = InitializeScannerHardware();

	}

	return ( m_bInitialized );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		InitializeScannerHardware
//
//	Description:
//		Initialize the com port and reset the scanner.
//
//	Arguments:
//		None.
//
//	Return:
//		Status.
//
//	Called by:
//		Initialize, Refresh
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CScanner::InitializeScannerHardware ( )
{

	BOOL blnDTREnable,
		 blnRTSEnable,
		 blnNULLDiscard;

	
	int 
		nTriggerDelay,
		nInputBufferSize,
		nOutputBufferSize,
		nPortID;

	CString
		csPortSettings,
		csName;


	csName = GetScannerName();

	// Initialize the port for the scanner.
	m_bInitialized = m_poDatabase->GetComPortAttributes ( csName,
						         						 &nTriggerDelay,
														 &nInputBufferSize,
														 &nOutputBufferSize,
														 &nPortID,
														 &csPortSettings,
														 &blnDTREnable,
														 &blnRTSEnable,
														 &blnNULLDiscard);
	if ( m_bInitialized )
	{
		m_oComPort.Initialize ( SCANNER, 
				                 nTriggerDelay,
				                 nInputBufferSize,
				                 nOutputBufferSize,
				                 nPortID,
							     csPortSettings,
								 blnDTREnable,
								 blnRTSEnable,
								 blnNULLDiscard);


	}

	// Test the port for connection and do a reset at the same time.
	
	if ( m_bInitialized )
	{


		if ((m_nType ==WELCHALLYN_4700)||
			(m_nType ==WELCHALLYN_3900))
		{
			TriggerOff();
		}


		if ( !Reset ( ) )
		{
			m_oComPort.Terminate();
			m_bInitialized = FALSE;
		}
	}

	return ( m_bInitialized );

}





/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetScannerName
//
//	Description:
//		Return scanner name based on the scanner sub-system type.
//
//	Arguments:
//		None.
//
//	Return:
//		Scanner name.
//
//	Called by:
//		Initialize
//
/////////////////////////////////////////////////////////////////////////////////////

CString CScanner::GetScannerName (  )
{

	CString
		csName;


	switch ( m_nScannerLocation )
	{

		case PLACEMENT_SCANNER:
			csName = "Placement_Scanner";
			break;

		case SYSTEM_SCANNER:
			csName = "System_Scanner";
			break;

		default:
			csName = "NA";
			break;

	}

	return ( csName );

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
//		Initialize
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CScanner::Reset ( )
{

	BOOL
		bStatus;

	CString
		csReturn,
		csTemp;


	bStatus = FALSE;
	
	// Reset the particular scanner.
	if ((SIMULATION)&(SIMULATELABELSCANNER))
		return TRUE;

	if ( m_oComPort.Write ( m_csReset ) )
	{

		// See if the scanner is returning anything.

		Sleep ( 2000 );
		if ( !GetVersion ( &csReturn ) )
		{
			csTemp.LoadString ( IDS_SCANNER_RESET_ERR );
			AfxMessageBox ( csTemp );
			bStatus = FALSE;
		}
		else
		{
			bStatus = TRUE;
		}
	}
	else
	{
		bStatus = FALSE;
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
//		Pointer to system digital I/O.
//
//	Return:
//		Status.
//
//	Called by:
//		GetStatus
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CScanner::ScanLabel ( CString *csLabelScanned, 
								   CDioController *poDIOController, 
									CString csPrintedLabel,
									BOOL bVerifyScan )
{

	BOOL
		bStatus;

	int nResult;
	
	CString
		csTemp,
		csScanResult,
		csLabel;

	int
		nLength,
		nIndex,
		nTriggerTimeOutSave;
	
	nResult=0;

	if (!bVerifyScan)
	{

		csScanResult=SingleTrigger();
		if ((SIMULATION)&(SIMULATELABELSCANNER))
		{

			*csLabelScanned="Simulator";
			SetScannedLabel ("Simulator");
		}
		else
		{
			
			if(!csScanResult.IsEmpty())
			{
				*csLabelScanned=csScanResult;
				SetScannedLabel (csScanResult);

			}
		}

	}
	else
	{

		if (m_poSNManager->m_blnUseCheckDigit) 
			if (m_poSNManager->m_csCheckDigitSource=="Printer")
				csPrintedLabel+=m_poPrinter->GetCheckDigitValue();

		
		if ((SIMULATION)&(SIMULATELABELSCANNER))
		{
			TRACE(CString("CScanner::ScanLabel():LabelID = ")+csPrintedLabel+CString("\n\r"));
			*csLabelScanned=csPrintedLabel;
			m_csScannedLabel=csPrintedLabel;
			return TRUE;
		}

			
		// Send delay between trigger and read depending on size of label.
		nLength = csPrintedLabel.GetLength();
		nTriggerTimeOutSave=m_oComPort.GetTriggerDelay();
		if ((nLength > 10)&&(nLength<20))
			m_oComPort.SetTriggerDelay(m_oComPort.GetTriggerDelay()*3/2);
		if (nLength > 20)
			m_oComPort.SetTriggerDelay(m_oComPort.GetTriggerDelay()*5/2);

		
		if (m_poSNManager->m_blnUseCheckDigit)
		{
			if (m_poPrinter->GetCheckDigitValue()==" ")
				csScanResult=SingleTrigger(FALSE);
			else
				csScanResult=SingleTrigger();

		}
		else
			csScanResult=SingleTrigger();

	}

	if ( csScanResult =="" )
	{

		// Must stop scanner from triggering.

		if ( m_nType == METANETICS_IR2000HD )
			m_oComPort.Write ( "q" );					// For Metanetics only.


		if ( (m_nType == WELCHALLYN_4700)||
			  (m_nType == WELCHALLYN_3900))
		{
			  TriggerOff();
		}		
		csTemp.LoadString ( IDS_ERR_SCANNER_RESPONSE );
		AfxMessageBox ( csTemp );
		return ( FALSE );
	}
	
	// Ensure the label scanned matches label printed.
	csScanResult.Replace("\n",NULL);
	csScanResult.Replace("\r",NULL);

	if ( bVerifyScan )
	{
		if (m_nType==WELCHALLYN_4700)
		{
		   nIndex = csScanResult.Find(".");
		   csTemp=csScanResult.Mid(nIndex+1);
		   if (!csTemp.IsEmpty())  // Mod 43 scan check
				csScanResult=csScanResult.Mid(nIndex+1);
		}
		
		if (m_nType==WELCHALLYN_3900)
		{
		   nIndex = csScanResult.Find(".");
		   csTemp=csScanResult.Mid(nIndex+1);
		   if (!csTemp.IsEmpty())  // Mod 43 scan check
				csScanResult=csScanResult.Mid(nIndex+1);
		}

		csScanResult.MakeUpper();
		csPrintedLabel.MakeUpper();


		csScanResult.MakeUpper();
		csPrintedLabel.MakeUpper();


		if ( csScanResult.Find(csPrintedLabel)==0 )
		{

			if ((csScanResult.GetLength())==(csPrintedLabel.GetLength()))
			{
				*csLabelScanned = csScanResult;
				SetScannedLabel(csScanResult);
				bStatus =  TRUE;
			}
			else
			{
				nResult=AfxMessageBox("Warning! The Scanned String is Longer than the Printed String. Continue?",MB_YESNO);
				if (nResult==IDNO)
				{
					*csLabelScanned = csScanResult;
					SetScannedLabel(csScanResult);
					bStatus = FALSE;


				}
				else
				{
					*csLabelScanned = csScanResult;
					SetScannedLabel(csScanResult);
					bStatus =  TRUE;
				}

			}
		}
		else
		{
			if (!csScanResult.IsEmpty())
				*csLabelScanned = csScanResult;
			else
				*csLabelScanned = "Scan Failed";
			bStatus = FALSE;

		}
	}

	else
		bStatus = TRUE;			// Do not verify scan.

	return ( bStatus );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetVersion
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
//		Initialize
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CScanner::GetVersion ( CString *csVersion )
{

	BOOL
		bStatus;

	CString
		csReturn;


	bStatus = TRUE;
	
	// Get the version of the particular scanner.

	switch ( m_nType )
	{

		case MICROSCAN_VS310:
		case MICROSCAN_VS710:
			m_oComPort.SetTriggerDelay ( 300 );
			if ((SIMULATION)&(SIMULATELABELSCANNER))
			{
				csReturn="SIMULATOR MODE";
				*csVersion=csReturn;
				return true;
			}

			m_oComPort.SetTriggerDelay ( 500 );
			csReturn = m_oComPort.WriteAndRead ( c_csMicroscanVersion, c_nWatchTime );
			break;

		case METANETICS_IR2000HD:
			m_oComPort.SetTriggerDelay ( 500 );
			csReturn = m_oComPort.WriteAndRead ( c_csMetaneticsVersion, c_nWatchTime );
			break;

		case WELCHALLYN_4700:
			
			if ((SIMULATION)&(SIMULATELABELSCANNER))
			{
				csReturn="SIMULATOR MODE";
				*csVersion=csReturn;
				return true;
			}
			
		case WELCHALLYN_3900:
			
			if ((SIMULATION)&(SIMULATELABELSCANNER))
			{
				csReturn="SIMULATOR MODE";
				*csVersion=csReturn;
				return true;
			}

			csReturn = m_oComPort.WriteAndRead ( c_csWelchAllyn_4700, c_nWatchTime );
			break;

		default:
			csReturn = "";
			break;

	}

	if ( csReturn == "" )
		bStatus = FALSE;
	else
		*csVersion = csReturn;

	return ( bStatus );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		CheckTriggerReset
//
//	Description:
//		Ensure that the trigger character is the same in the reset string
//		if applicable.
//
//	Arguments:
//		None.
//
//	Return:
//		Status
//
//	Called by:
//		Initialize
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CScanner::CheckTriggerReset ( )
{

	int
		nIndex;

	CString csTemp;

	BOOL 
		bStatus;
	

	// Match up the trigger character with the reset string if
	// the reset string requires it.

	bStatus = FALSE;
	switch ( m_nType )
	{

		case MICROSCAN_VS310:
		case MICROSCAN_VS710:

			// Get trigger character designator.

			nIndex = m_csReset.Find ( "i" );
			if ( nIndex == -1 )
			{
				csTemp.LoadString ( IDS_ERR_SCANNER_RESET_STRING );
				AfxMessageBox ( csTemp );
				bStatus = FALSE;			
			}
			else
			{

				// Replace character.

				m_csReset.SetAt ( nIndex + 1, m_csTrigger.GetAt ( 0 ) );
				bStatus = TRUE;
			}
			break;

		case METANETICS_IR2000HD:
			bStatus = TRUE;
			break;

		case WELCHALLYN_4700:
			bStatus = TRUE;
			break;

		case WELCHALLYN_3900:
			bStatus = TRUE;
			break;

		default:
			bStatus = FALSE;
			break;
	}

	return ( bStatus );

}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetReset()
//
//	Description:
//		Returns the current reset string
//
//	Arguments:
//		None.
//
//	Return:
//		CString containing the reset string
//
//	Called by:
//		CScanDlg::OnInitDialog
//
/////////////////////////////////////////////////////////////////////////////////////

CString CScanner::GetReset()
{
	return (m_csReset);
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SingleTrigger()
//
//	Description:
//		Triggers the scanner, returns value
//
//	Arguments:
//		None.
//
//	Return:
//		CString containing the read string
//
//	Called by:
//		CScanDlg::OnClickSingleTrigger, CScanDlg::OnClickContinuousTrigger
//
/////////////////////////////////////////////////////////////////////////////////////

CString CScanner::SingleTrigger()
{
	CString csScanResult;
	if ((SIMULATION)&(SIMULATELABELSCANNER))
	{
		return "SIMULATION MODE";
	}

	
	switch ( m_nType )
	{

		case MICROSCAN_VS310:
		case MICROSCAN_VS710:
			m_oComPort.Write(m_csTrigger);
			while(csScanResult.Find("**") == -1)
			{
				csScanResult += m_oComPort.Read();
				Utility.YieldToWindows();
			}

//			csScanResult = m_oComPort.WriteAndRead ( m_csTrigger, c_nWatchTime );
			break;
		case METANETICS_IR2000HD:
			// long trigger delay, read long labels
			m_oComPort.SetTriggerDelay ( 1000 );

			// execute scan
			csScanResult = m_oComPort.WriteAndRead ( m_csTrigger, c_nWatchTime );

			if ( csScanResult =="" )
			{
				// Must stop scanner from triggering.
				m_oComPort.Write ( "q" );
				return ( "" );
			}
			break;
		case WELCHALLYN_4700:
			csScanResult = m_oComPort.WriteAndRead (m_csTrigger, c_nWatchTime );

			if ( csScanResult =="" )
			{
				// Must stop scanner from triggering.
				m_oComPort.Write ( m_csTriggerOff );
				return ( CString("Scanned Failed:")+csScanResult );
			}
			else
			{
				csScanResult.TrimRight();
			}
			break;

		case WELCHALLYN_3900:
			csScanResult = m_oComPort.WriteAndRead (m_csTrigger, c_nWatchTime );

			if ( csScanResult =="" )
			{
				// Must stop scanner from triggering.
				m_oComPort.Write ( m_csTriggerOff );
				return ( CString("Scanned Failed:")+csScanResult );
			}
			else
			{
				csScanResult.TrimRight();
			}
			break;

	}

	
	return(csScanResult);
}


CString CScanner::SingleTrigger(BOOL blnTrim)
{
	CString csScanResult;
	if ((SIMULATION)&(SIMULATELABELSCANNER))
	{
		return "SIMULATION MODE";
	}

	
	switch ( m_nType )
	{

		case MICROSCAN_VS310:
		case MICROSCAN_VS710:
			m_oComPort.Write(m_csTrigger);
			while(csScanResult.Find("**") == -1)
			{
				csScanResult += m_oComPort.Read();
				Utility.YieldToWindows();
			}

//			csScanResult = m_oComPort.WriteAndRead ( m_csTrigger, c_nWatchTime );
			break;
		case METANETICS_IR2000HD:
			// long trigger delay, read long labels
			m_oComPort.SetTriggerDelay ( 1000 );

			// execute scan
			csScanResult = m_oComPort.WriteAndRead ( m_csTrigger, c_nWatchTime );

			if ( csScanResult =="" )
			{
				// Must stop scanner from triggering.
				m_oComPort.Write ( "q" );
				return ( "" );
			}
			break;
		case WELCHALLYN_4700:
			csScanResult = m_oComPort.WriteAndRead (m_csTrigger, c_nWatchTime );

			if ( csScanResult =="" )
			{
				// Must stop scanner from triggering.
				m_oComPort.Write ( m_csTriggerOff );
				return ( CString("Scanned Failed:")+csScanResult );
			}
			else
			{
				if (blnTrim)
					csScanResult.TrimRight();
			}
			break;

		case WELCHALLYN_3900:
			csScanResult = m_oComPort.WriteAndRead (m_csTrigger, c_nWatchTime );

			if ( csScanResult =="" )
			{
				// Must stop scanner from triggering.
				m_oComPort.Write ( m_csTriggerOff );
				return ( CString("Scanned Failed:")+csScanResult );
			}
			else
			{
				if (blnTrim)
					csScanResult.TrimRight();
			}
			break;

	}

	
	return(csScanResult);
}



BOOL CScanner::TriggerOff()
{

	BOOL
		bStatus;

	CString
		csReturn,
		csTemp;


	bStatus = TRUE;
	
	if ((SIMULATION)&(SIMULATELABELSCANNER)) return true;

	m_oComPort.Write ( m_csTriggerOff );

	return ( bStatus );

}

BOOL CScanner::GetMatchLabel()
{
	return (m_bMatchLabel);
}

void CScanner::SetMatchLabel(BOOL bMatchLabel)
{
	m_bMatchLabel = bMatchLabel;
	return;
}


CString CScanner::GetScannedLabel()
{
	return m_csScannedLabel;

}

void CScanner::SetScannedLabel (CString csScanResult)
{

	m_csScannedLabel=csScanResult;
}
