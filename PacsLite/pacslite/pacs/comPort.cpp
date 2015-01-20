// comPort.cpp: implementation of the comPort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "comPort.h"
#include "definitions.h"


///////////////////////////////////
#include <math.h>

//////////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


const int ID_COMMCTRL = 2000;

// Handshake Constants

#define comNone			0		// No handshaking.
#define comXonXoff		1		// XOn/XOff handshaking.
#define comRTS				2		// Request-to-send/clear-to-send handshaking.
#define comRTSXOnXOff	3		// Both request-to-send and XOn/XOff handshaking.



//////////////////////////////////////////////////////////////////////
// Construction/Destruction 
//////////////////////////////////////////////////////////////////////

CcomPort::CcomPort() {}

CcomPort::~CcomPort(){}

///////////////////////////////
//
//	Functionality:
//  using the passed-in portinfo object 
//  to set comm port and open it
//
////////////////////////////////

BOOL CcomPort::Initialize ( int nPortType, 
									 int nTriggerDelay,
									 int nInputBufferSize,
									 int nOutputBufferSize,
									 int nPortID,
									 CString csPortSettings,
									 BOOL blnDTREnable,
									 BOOL blnRTSEnable,
									 BOOL blnNULLDiscard)

{

	
	m_bInitialized = FALSE;

	m_nPortType = nPortType;
	m_nTriggerDelay = nTriggerDelay;
	m_nInputBufferSize = nInputBufferSize;
	m_nOutputBufferSize = nOutputBufferSize;
	m_nPortID = nPortID;
	m_csPortSettings = csPortSettings;
	

	// "Copyright (c) 1994 ".
	WCHAR pwchLicenseKey[] = { 0x0043, 0x006f, 0x0070,
		0x0079, 0x0072, 0x0069, 0x0067, 0x0068, 0x0074,
		0x0020, 0x0028, 0x0063, 0x0029, 0x0020, 0x0031,
		0x0039, 0x0039, 0x0034, 0x0020 };

	BSTR bstrLicense = ::SysAllocStringLen ( pwchLicenseKey, 
					sizeof ( pwchLicenseKey ) / sizeof ( WCHAR ) );

	if ( !m_oComControl.Create ( NULL,					 			// A pointer to window text.
									  0,										// Window styles.
									  CRect(0,0,0,0),						// Size and position.
									  AfxGetMainWnd(),					// Any accessible CWnd*
									  ID_COMMCTRL+m_nPortID,			// Control ID for com port.
									  NULL,
									  FALSE,
									  bstrLicense ) )						// Required license key.
	{
		TRACE0("Failed to create OLE Communications Control\n");
		::SysFreeString ( bstrLicense );

		return FALSE;      // fail to create 
	}

	::SysFreeString ( bstrLicense );

	// Set RThreshold property to 1. The default RThreshold value (0)
	// causes the OnComm event to NOT fire when a character is detected
	// in the serial port. 

	// Set threshold and handshaking parameters.

	m_oComControl.SetRThreshold ( 1 );					// Set transfer for one character.
	m_oComControl.SetSThreshold ( 1 );

	m_oComControl.SetDTREnable ( blnDTREnable );				
	m_oComControl.SetRTSEnable ( blnRTSEnable );				
	m_oComControl.SetNullDiscard ( blnNULLDiscard );				// Discard NULL characters.

	m_oComControl.SetHandshaking ( comNone );			//	Set handshaking to RTS/CTS.
	m_oComControl.SetParityReplace ( "" );				// Parity error replacement character.


	m_oComControl.SetInBufferSize ( m_nInputBufferSize );	
	m_oComControl.SetOutBufferSize ( m_nOutputBufferSize );		
	m_oComControl.SetSettings ( m_csPortSettings );

	if (m_nPortType==PRINTER)
		if ((SIMULATION)&(SIMULATEPRINTER))
		{
		   m_oComControl.SetCommPort ( m_nPortID );
		   return true;
		}
		

	if (m_nPortType==SCANNER)
		if ((SIMULATION)&(SIMULATELABELSCANNER))
		{
		   m_oComControl.SetCommPort ( m_nPortID );
		   return true;
		}



    m_oComControl.SetCommPort ( m_nPortID );

	
	TRY
	{
		

		// Open the port.
		m_oComControl.SetPortOpen ( TRUE );
		m_bInitialized = TRUE;
		return ( TRUE );
	}
	CATCH (CException, e)
	{
		m_bInitialized = FALSE;

		TCHAR   szCause[255];      
		CString strFormatted;
        e->GetErrorMessage(szCause, 255);
        strFormatted = _T("Com Port Error: ");
        strFormatted += szCause;   
		AfxMessageBox(strFormatted);
		return ( FALSE );
	}
	END_CATCH


}



//////////////////////////////////
//
//
// Write a string to the port
//
//////////////////////////////////
BOOL CcomPort::Write ( CString csTrigger )
{

	CString
		csTemp;


	if ( !m_bInitialized )
	{
		csTemp= "Com Port Error";
		AfxMessageBox ( csTemp );
		return ( FALSE );
	}


/*	if (((SIMULATION)&(SIMULATEPRINTER)))
	{
		return TRUE;
    }
	else if (((SIMULATION)&(SIMULATELABELSCANNER)))
	{
		return TRUE;
    }
	else if (((SIMULATION)&(SIMULATEDIOCONTROLLER)))
	{
		return TRUE;
    }
*/
	VARIANT var;
	var.vt = VT_BSTR;
	var.bstrVal = csTrigger.AllocSysString();
	m_oComControl.SetOutput ( var );
	SysFreeString ( var.bstrVal );
	return ( TRUE );

}



//////////////////////////////
//
//Read a string from the port
//
//
//////////////////////////////
CString CcomPort::Read()
{

	CString
		csTemp;


	if ( !m_bInitialized )
	{

		csTemp= "Error Opening Com Port"; //LoadString ( "Error Opening Com Port");//IDS_ERR_OPEN_COMPORT );
		AfxMessageBox ( csTemp );
		return "";
	}

	CString csRead;
	
	VARIANT var;
	var.vt = VT_BSTR ;
	
	var = m_oComControl.GetInput();
	csRead = var.bstrVal;

	return ( csRead );

}



///////////////////////////////////
//
//WriteAndRead function is a conbination for convenience
// when caller wants to send a trigger and see the response.
// 
// 
//
//////////////////////////////////
CString CcomPort::WriteAndRead ( CString csTrigger, int nSecond )
{

	//*****************
	//passed-in int_second is the seconds to wait for read
	//after the trigger is sent to the port

	//*****************

	CString	csRead;
	
	// Clear port first.
	
	csRead = Read();
	csRead = "";
	
	//Write

	Write ( csTrigger );

	//Read

	// Sleep a specified anount of time to ensure the whole
	// string has been communicated.

	Sleep ( m_nTriggerDelay );

	csRead = Read();

	return ( csRead );   // return "" if nothing back

}


//////////////////////////////
//
// close the port
//
//
//////////////////////////////

BOOL CcomPort::Terminate()
{

	m_oComControl.SetPortOpen ( FALSE );
	m_oComControl.DestroyWindow();

	return ( TRUE );

}



void CcomPort::SetTriggerDelay ( int nDelay )
{

	m_nTriggerDelay = nDelay;

}

int CcomPort::GetTriggerDelay ()
{

	return m_nTriggerDelay;

}