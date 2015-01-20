// Printer.cpp: implementation of the CPrinter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PACS.h"
#include "Utilities.h"
#include "Printer.h"
#include "trace.h"
#include "CheckDgt.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPrinter::CPrinter()
{

	m_bUse = FALSE;

}


CPrinter::~CPrinter()
{

}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		Initialize
//
//	Description:
//		Initialize the printer.
//
//	Arguments:
//		Pointer to database.
//		Printer location ( printer name in database ).
//		Use printer flag.
//
//	Return:
//		Status.
//
//	Called by:
//		CApplicatorControl::Initialize
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CPrinter::Initialize ( CDatabase *poDatabase, 
									 CSNManager *poSNManager,
									 BOOL *bUsePrinter )
{

	Trace("[MachineState] MS= Initializing Printer SubSystem");	

	CString
		csTemp,
		csPortSettings;

	BOOL
		bEnable,
		bUse,
		blnDTREnable,
		blnRTSEnable,
		blnNULLDiscard;

	int 
		nTriggerDelay,
		nInputBufferSize,
		nOutputBufferSize,
		nPortID,
		nType;

	CString	csName;


	// Get printer information from database.

	m_poSNManager = poSNManager;
	if (poDatabase==NULL)
	{
//		TraceError
		csTemp.LoadString(IDS_DATABASE_INIT_ERROR); 
		AfxMessageBox(csTemp);
		return FALSE;

	}
	m_poDatabase = poDatabase;

	
	m_bInitialized = m_poDatabase->GetActivePrinterAttributes ( &csName, 
																		 &bUse,
																		 &bEnable,
																		 &nType);

	m_bUse  = bUse;
	m_nType = nType;
	m_bEnable = bEnable;

	*bUsePrinter = m_bUse;

	if (!m_bUse || !m_bEnable)
		return ( TRUE );			// Printer is not used so forget the rest.



	// Initialize the port for the printer.

	if ( m_bInitialized )
		m_bInitialized = poDatabase->GetComPortAttributes ( csName,
																			 &nTriggerDelay,
																			 &nInputBufferSize,
																			 &nOutputBufferSize,
																			 &nPortID,
																			 &csPortSettings,
																			 &blnDTREnable,
																			 &blnRTSEnable,
																			 &blnNULLDiscard);

	if ( m_bInitialized )
		m_bInitialized = m_oComPort.Initialize ( PRINTER, 
										nTriggerDelay,
										nInputBufferSize,
										nOutputBufferSize,
										nPortID,
										csPortSettings,
										blnDTREnable,
										blnRTSEnable,
										blnNULLDiscard);


	// Test the port for connection.
	
	if ( m_bInitialized )
	{

		if ( !GetStatus ( ) )
		{
			m_bInitialized = FALSE;
		}
	}

	return ( m_bInitialized );

}



void CPrinter::SetUse ( BOOL bUse )
{

	m_bUse = bUse;

}


void CPrinter::SetType ( int nType )
{

	m_nType = nType;

}


void CPrinter::SetEnable ( BOOL bEnable )
{

	m_bEnable = bEnable;

}


BOOL CPrinter::GetUse ()
{

	return ( m_bUse );

}


int CPrinter::GetType ()
{

	return ( m_nType );

}


BOOL CPrinter::GetEnable ()
{

	return ( m_bEnable );

}




BOOL CPrinter::PrintLabel (CString csLabel)
{
	Trace("[I] CPrinter:: Start of PrintLabel()\n\r");

	if ((SIMULATION)&(SIMULATEPRINTER))
	{

		Trace("[IS] CPrinter:: Begin Template\n\r");
		Trace("[IS] ---------------------------------\n\r");

		Trace("%s\n\r",csLabel);

		Trace("[IS] CPrinter:: End Template\n\r");
		Trace("[IS] ---------------------------------\n\r");

		Trace("[IS] CPrinter:: End of PrintLabel()\n\r");

		return true;

	}
	Trace("[IS] CPrinter:: Begin Template\n\r");
	Trace("[IS] ---------------------------------\n\r");
	
	int nLen;
	nLen=csLabel.GetLength();
	if (nLen<1000)
		Trace("%s\n\r",csLabel);

	Trace("[IS] CPrinter:: End Template\n\r");
	Trace("[IS] ---------------------------------\n\r");


	Trace("[IS] CPrinter:: End of PrintLabel()\n\r");

	switch ( m_nType )
	{

		case APOLLO:
		case THARO:
			if (!GetApolloStatus()) return FALSE;
			csLabel=csApolloFlushQueue+csLabel;
			break;

		case ZEBRA:
			csLabel=csLabel;    // for the future
			break;
	}

	return ( m_oComPort.Write ( csLabel) );
}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetStatus
//
//	Description:
//		Get the printer status.
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

BOOL CPrinter::GetStatus ( )
{

	BOOL
		bStatus;

	bStatus = TRUE;
	
	// Get the status of the particular printer.

	switch ( m_nType )
	{

		case ZEBRA:
			bStatus = GetZebraStatus();
			break;

		case INTERMEC:
			bStatus = GetIntermecStatus();
			break;

		case DATAMAX:
			bStatus = GetDatamaxStatus();
			break;

	}

	return ( bStatus );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetZebraStatus
//
//	Description:
//		Get the zebra printer status.
//
//	Arguments:
//
//	Return:
//		Status.
//
//	Called by:
//		GetStatus
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CPrinter::GetZebraStatus ( )
{


	CString csStatus;
	CString csTemp;
	
	if ((SIMULATION)&(SIMULATEPRINTER))
	{
		return true;
	}
//	m_oComPort.SetTriggerDelay ( 1000);

	csStatus = m_oComPort.WriteAndRead ( csZebraStatusReq, 6 );

	// The return string is the status of a Zebra printer. 

	if ( csStatus == "" )//|| csStatus.GetLength() < 60 ) 
	{
		csTemp.LoadString ( IDS_ERR_PRINTER_RESP );
		AfxMessageBox ( csTemp );
		return ( FALSE );
	}
	
	if (  csStatus.GetLength() < 60 ) 
	{
		return ( TRUE );
	}

	// Check for paper out.

	if ( csStatus.GetAt ( 5 ) == '1' )
	{
		csTemp.LoadString ( IDS_PRINTER_OUTOFPAPER );
		AfxMessageBox ( csTemp );
		return ( FALSE );
	}

	// Check for pause mode.

	if ( csStatus.GetAt ( 7 ) == '1' )
	{
		csTemp.LoadString ( IDS_PRINTER_INPAUSE );
		AfxMessageBox ( csTemp );
		return ( FALSE );
	}
	
	// Check for buffer full.

	if ( csStatus.GetAt ( 18 ) == '1' )
	{
		csTemp.LoadString ( IDS_PRINTER_BUFFERFULL );
		AfxMessageBox ( csTemp );
		return ( FALSE );
	}

	// Check for corrupt RAM.

	if ( csStatus.GetAt ( 28 ) == '1' )
	{
		csTemp.LoadString ( IDS_PRINTER_BADRAM );
		AfxMessageBox ( csTemp );
		return ( FALSE );
	}

	// Check for head up.

	if ( csStatus.GetAt ( 43 ) == '1' )
	{
		csTemp.LoadString ( IDS_PRINTER_HEADUP );
		AfxMessageBox ( csTemp );
		return ( FALSE );
	}

	// Check for ribbon out.

	if ( csStatus.GetAt ( 45 ) == '1' )
	{
		csTemp.LoadString ( IDS_PRINTER_RIBBONOUT );
		AfxMessageBox ( csTemp );
		return ( FALSE );
	}

	// WOW! We made it.

	return ( TRUE );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetIntermecStatus
//
//	Description:
//		Get the intermec printer status.
//
//	Arguments:
//
//	Return:
//		Status.
//
//	Called by:
//		GetStatus
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CPrinter::GetIntermecStatus ( )
{

	return (TRUE);

	CString csStatus;
	CString csTemp;
	

	csStatus = m_oComPort.WriteAndRead ( csIntermecStatusReq, nWatchTime );

	// The return string is the status of an Intermec printer. 
	if ( ( csStatus == "<DC2>" ) || ( csStatus == char(18) ) )
		return ( TRUE );
	
	if ( csStatus == "" ) 
	{
		csTemp.LoadString ( IDS_ERR_PRINTER_RESP );
		AfxMessageBox ( csTemp );
		return ( FALSE );
	}
	
	
	if ( ( csStatus == "<US>" ) || ( csStatus == char(31) ) || 
		  ( csStatus == "<DC3>" ) || ( csStatus == char(19) ) )
	{
		csTemp.LoadString ( IDS_PRINTER_BUFFERFULL );
		AfxMessageBox ( csTemp );
		return ( FALSE );
	}
	
	if ( ( csStatus == "<GS>" ) || ( csStatus == char(29) ) )
	{
		csTemp.LoadString ( IDS_PRINTER_RIBBONOUT );
		AfxMessageBox ( csTemp );
		return ( FALSE );
	}
	
	if ( ( csStatus == "<EM>" ) || ( csStatus == char(25) ) )
	{
		csTemp.LoadString ( IDS_PRINTER_OUTOFPAPER );
		AfxMessageBox ( csTemp );
		return ( FALSE );
	}

	if ( ( csStatus == "<FS>" ) || ( csStatus == char(28) ) )
	{
		csTemp.LoadString ( IDS_PRINTER_STRIPPIN );
		AfxMessageBox ( csTemp );
		return ( FALSE );
	}

	return ( TRUE );
}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetDatamaxStatus
//
//	Description:
//		Get the Datamax printer status.
//
//	Arguments:
//
//	Return:
//		Status.
//
//	Called by:
//		GetStatus
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CPrinter::GetDatamaxStatus ( )
{
	CString csStatus;
	CString csTemp;
	
	// request the status string
	csTemp = m_oComPort.WriteAndRead (csDatamaxStatusReq,nWatchTime);

	// out of paper
	if (csTemp.Mid(1,1)=="Y")
	{
		csStatus.LoadString ( IDS_PRINTER_OUTOFPAPER );
		AfxMessageBox(csStatus);
		return(FALSE);
	}
	
	// out of ribbon
	if (csTemp.Mid(2,1)=="Y")
	{
		csStatus.LoadString ( IDS_PRINTER_RIBBONOUT );
		AfxMessageBox(csStatus);
		return(FALSE);
	}
	
	// printer is paused
	if (csTemp.Mid(5,1)=="Y")
	{
		csStatus.LoadString ( IDS_PRINTER_INPAUSE );
		AfxMessageBox(csStatus);
		return(FALSE);
	}

	// status is ok
	return(TRUE);
}





/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		Refresh
//
//	Description:
//		Refresh the attributes of the printer.
//
//	Arguments:
//		Pointer to database.
//
//	Return:
//		Status.
//
//	Called by:
//		CPrinterControl::UpdatePrinterAttributes
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CPrinter::Refresh ( CDatabase *poDatabase )
{

	CString
		csTemp;

	BOOL
		bEnable,
		bUse,
		blnDTREnable,
		blnRTSEnable,
		blnNULLDiscard;
		
	BOOL bOldEnable = m_bEnable;
	BOOL bOldUse = m_bUse;

	int 
		nTriggerDelay,
		nInputBufferSize,
		nOutputBufferSize,
		nPortID,
		nType;

	CString
		csPrepickPos,
		csPickPos,
		csPortSettings,
		csName;

	// Get printer information from database.
	m_bInitialized = poDatabase->GetActivePrinterAttributes ( &csName, 
														 &bUse,
														 &bEnable,
														 &nType);

	m_bUse  = bUse;
	m_nType = nType;
	m_bEnable = bEnable;

	// if not using or disabled don't initialize
	if ( !m_bUse || !m_bEnable)
	{
		// if we used it before and are disabling it now
		// close previous port and terminate object
		if (bOldUse && bOldEnable)
			m_oComPort.Terminate();
		return ( TRUE );
	}


	// Get comport attributes
	if ( m_bInitialized && ( !bOldUse || !bOldEnable ) )
		m_bInitialized = poDatabase->GetComPortAttributes ( csName,
						         							&nTriggerDelay,
															&nInputBufferSize,
															&nOutputBufferSize,
															&nPortID,
															&csPortSettings,
															&blnDTREnable,
															&blnRTSEnable,
															&blnNULLDiscard);
	// Initialize the port for the printer.
	if ( m_bInitialized && ( !bOldUse || !bOldEnable ) )
		m_bInitialized = m_oComPort.Initialize ( m_nPrinterLocation, 
							 			                 nTriggerDelay,
										                 nInputBufferSize,
										                 nOutputBufferSize,
										                 nPortID,
													     csPortSettings,
														 blnDTREnable,
														 blnRTSEnable,
														 blnNULLDiscard);

	// Test the port for connection.
	if ( m_bInitialized && ( !bOldUse || !bOldEnable ) )
		m_bInitialized = GetStatus();

	// return success or failure
	return ( m_bInitialized );
}


CString CPrinter::BuildLabel ( BOOL bRunMode, CJob *poJob, CString csTemplate )
{


	CString
		csNewLabel,
		csSerialNumber,
		csData1,
		csData2,
		csKeyWord,
		csKeyValue,
		csData4,
		csData5,
		csFrontText,
		csBackText,
		csChkDigit;

		char *p_chr_Source;
		char *p_chr_Target;

CString csNewSerialNumber;

	
	Trace("[I] Start of CPrinter::BuildLabel\n\r");	

 
	
	

	// Make adjustments to the template to build the label.
	// Save the label string data for scan verification.


	if ( !bRunMode )
	{
		if (csTemplate.Find("HRSerial")!=-1)
		{
			csTemplate=ReplaceKeyWord(csTemplate, "HRSerial", "999999");
		}

		if (csTemplate.Find("hrserial")!=-1)
		{
			csTemplate=ReplaceKeyWord(csTemplate, "hrserial", "999999");
		}
		
		if (csTemplate.Find("HRSERIAL")!=-1)
		{
			csTemplate=ReplaceKeyWord(csTemplate, "HRSERIAL", "999999");
		}
		
		if (csTemplate.Find("FD>9")!=-1)
		{
			if (csTemplate.Find("SERIAL")!=-1)
			{
				csNewSerialNumber=ConvertCode128_SSA("SERIAL");
				csTemplate=ReplaceKeyWord(csTemplate, "SERIAL", csNewSerialNumber);
			}
			else if (csTemplate.Find("Serial")!=-1)
			{
				csNewSerialNumber=ConvertCode128_SSA("Serial");
				csTemplate=ReplaceKeyWord(csTemplate, "Serial", csNewSerialNumber);
			}
			else if (csTemplate.Find("serial")!=-1)
			{
				csNewSerialNumber=ConvertCode128_SSA("serial");
				csTemplate=ReplaceKeyWord(csTemplate, "serial", csNewSerialNumber);
			}


		}
		else if (csTemplate.Find("FD>;")!=-1)  //subset C does not print alpha's
		{
			if (csTemplate.Find("SERIAL")!=-1)
			{
				csTemplate=ReplaceKeyWord(csTemplate, "SERIAL", "999999");
			}
			else if (csTemplate.Find("Serial")!=-1)
			{
				csTemplate=ReplaceKeyWord(csTemplate, "Serial", "999999");
			}
			else if (csTemplate.Find("serial")!=-1)
			{
				csTemplate=ReplaceKeyWord(csTemplate, "serial", "999999");
			}


		}

		return ( csTemplate );
	}



	// Nortel always has serialization, there are six
	// data fields to build and substitute
		// start with the template
	csNewLabel = csTemplate;

	if (poJob->GetUseDataName1())
	{
		csKeyWord=poJob->GetDataName1();
		
		csKeyValue =
		m_poDatabase->GetPrintedValue(poJob->GetDataName1(),
							   poJob->GetDataValue1());

		csKeyWord.TrimRight();
		csKeyWord.TrimLeft();

		csKeyValue.TrimRight();
		csKeyValue.TrimLeft();

		
		csNewLabel=ReplaceKeyWord(csNewLabel, csKeyWord, csKeyValue);
	}

	if (poJob->GetUseDataName2())
	{
		csKeyWord=poJob->GetDataName2();
		
		csKeyValue =
		m_poDatabase->GetPrintedValue(poJob->GetDataName2(),
							   poJob->GetDataValue2());

		csKeyWord.TrimRight();
		csKeyWord.TrimLeft();

		csKeyValue.TrimRight();
		csKeyValue.TrimLeft();
		
		
		csNewLabel=ReplaceKeyWord(csNewLabel, csKeyWord, csKeyValue);
	}
		

	if (poJob->GetUseDataName3())
	{
		csKeyWord=poJob->GetDataName3();
		
		csKeyValue =
		m_poDatabase->GetPrintedValue(poJob->GetDataName3(),
							   poJob->GetDataValue3());

		csKeyWord.TrimRight();
		csKeyWord.TrimLeft();

		csKeyValue.TrimRight();
		csKeyValue.TrimLeft();

		csNewLabel=ReplaceKeyWord(csNewLabel, csKeyWord, csKeyValue);
	}
		

	if (poJob->GetUseDataName4())
	{
		csKeyWord=poJob->GetDataName4();
		
		csKeyValue =
		m_poDatabase->GetPrintedValue(poJob->GetDataName4(),
							   poJob->GetDataValue4());

		csKeyWord.TrimRight();
		csKeyWord.TrimLeft();

		csKeyValue.TrimRight();
		csKeyValue.TrimLeft();

		csNewLabel=ReplaceKeyWord(csNewLabel, csKeyWord, csKeyValue);
	}
		

	if (poJob->GetUseDataName5())
	{
		csKeyWord=poJob->GetDataName5();
		
		csKeyValue =
		m_poDatabase->GetPrintedValue(poJob->GetDataName5(),
							   poJob->GetDataValue5());
		csKeyWord.TrimRight();
		csKeyWord.TrimLeft();

		csKeyValue.TrimRight();
		csKeyValue.TrimLeft();

		
		csNewLabel=ReplaceKeyWord(csNewLabel, csKeyWord, csKeyValue);
	}
		
	csSerialNumber = BuildSerialNumber(poJob);
	csChkDigit	="";
	if (m_poSNManager->m_blnUseCheckDigit)
	{
	
		p_chr_Source=csSerialNumber.GetBuffer ( csSerialNumber.GetLength() );;
		p_chr_Target=csChkDigit.GetBuffer ( 10 );

		if (m_poSNManager->m_csCheckDigitType=="Mod 43") 
		   GetCheckDigit(p_chr_Source, "Mod43",p_chr_Target);
		else if (m_poSNManager->m_csCheckDigitType=="Mod 10 [Zebra Printer]")
			GetCheckDigit(p_chr_Source, "CHK105",p_chr_Target);
		else
			AfxMessageBox("No Valid CheckSum Formula Was Found");

		csSerialNumber.ReleaseBuffer();
		csChkDigit.ReleaseBuffer();
		if (!csChkDigit.IsEmpty())
		{
			m_csCheckDigit=csChkDigit;
			if (m_poSNManager->m_csCheckDigitSource.Find("Computer")!=-1)
			{
				csSerialNumber=csSerialNumber+csChkDigit;
			}
		}

	}
	m_csPrintedLabel = csSerialNumber;	// To compare with scan later.

	if (csNewLabel.Find("HRSerial")!=-1)
	{
		csNewLabel=ReplaceKeyWord(csNewLabel, "HRSerial", m_csPrintedLabel);
	}

	if (csNewLabel.Find("HRSERIAL")!=-1)
	{
		csNewLabel=ReplaceKeyWord(csNewLabel, "HRSERIAL", m_csPrintedLabel);
	}

	if (csNewLabel.Find("hrserial")!=-1)
	{
		csNewLabel=ReplaceKeyWord(csNewLabel, "hrserial", m_csPrintedLabel);
	}

	if (csNewLabel.Find("FD>;")!=-1)
	{
		if ((csSerialNumber.GetLength() % 2)!=0)
		{
			AfxMessageBox("Warning. String Length Is Not A Multiple Of 2. \n\r Job Will End.");
		    return "";
		}
	}
	
	
	if (csNewLabel.Find("FD>9")!=-1)
	{
		csSerialNumber=ConvertCode128_SSA(csSerialNumber);
	}

	if ( m_poSNManager->UseSerialization() )
	{
		csNewLabel=ReplaceKeyWord(csNewLabel, "SERIAL", csSerialNumber);
	}

	if ( m_poSNManager->UseSerialization() )
	{
		csNewLabel=ReplaceKeyWord(csNewLabel, "Serial", csSerialNumber);
	}
	
	if ( m_poSNManager->UseSerialization() )
	{
		csNewLabel=ReplaceKeyWord(csNewLabel, "serial", csSerialNumber);
	}

	
	
//	m_csPrintedLabel = csSerialNumber;	// To compare with scan later.
	Trace("[IS] CPrinter::BuildLabel Printed SerialNumber[%s] \n\r",m_csPrintedLabel);	


	// extract the bar code text to compare to the scan later
	// m_csPrintedLabel = ExtractBarCodeText(csNewLabel);

	Trace("[IS] End of CPrinter::BuildLabel\n\r");	

	return ( csNewLabel );
}

CString CPrinter::ReplaceKeyWord(CString csTemplate, CString csKeyWord, CString csValue)
{
CString csNewLabel,
		csFrontText,
		csBackText,csBuffer;


int nKeyWordLength,
	nIndex,
	nLength;
	Trace("Start of CPrinter::ReplaceKeyWord()\n\r");
	Trace("-----------------------------------\n\r");


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
	Trace("End of CPrinter::ReplaceKeyWord()\n\r");

	if (csNewLabel=="")
		return csTemplate;
	return csNewLabel;

}



CString CPrinter::BuildSerialNumber(CJob *poJob)
{
CString csBaseSerialNumber;
CString csTemp,
		csBuffer,
		csDataFieldName,
		csReturnString;

 

	csBaseSerialNumber=m_poSNManager->GetSerialNumber();
	SetPrintedSerialNumber(csBaseSerialNumber);
	m_csSuffix="";
	if (poJob->GetPrintDataValue1())
	{
		
		csDataFieldName=poJob->GetDataName1();
		csDataFieldName.MakeUpper();

		if (csDataFieldName.Find("SUFFIX")==-1)
		{
			csTemp=
			m_poDatabase->GetPrintedValue(poJob->GetDataName1(),
									   poJob->GetDataValue1());
		}
		else
		{
			if (!poJob->GetDataValue1().IsEmpty())
				m_csSuffix=poJob->GetDataValue1();

		}



	}
	if (csTemp!="")
	{
		SetSerialNumberPrefix1(csTemp);
		csBuffer=csTemp;
	}
	else
	{
		SetSerialNumberPrefix1("");

	}
	csTemp="";
	if (poJob->GetPrintDataValue2())
	{

		csDataFieldName=poJob->GetDataName2();
		csDataFieldName.MakeUpper();

		if (csDataFieldName.Find("SUFFIX")==-1)
		{
			csTemp=
			m_poDatabase->GetPrintedValue(poJob->GetDataName2(),
									   poJob->GetDataValue2());
		}
		else
		{
			if (!poJob->GetDataValue2().IsEmpty())
			{
				if (m_csSuffix.IsEmpty())
					m_csSuffix=poJob->GetDataValue2();
				else
					m_csSuffix+=poJob->GetDataValue2();
			}

		}

	}
	if (csTemp!="")
	{
		SetSerialNumberPrefix2(csTemp);
		csBuffer+=csTemp;
	}
	else
	{
		SetSerialNumberPrefix2("");
	}
	csTemp="";

	if (poJob->GetPrintDataValue3())
	{

		csDataFieldName=poJob->GetDataName3();
		csDataFieldName.MakeUpper();

		if (csDataFieldName.Find("SUFFIX")==-1)
		{
			csTemp=
			m_poDatabase->GetPrintedValue(poJob->GetDataName3(),
									   poJob->GetDataValue3());
		}
		else
		{
			if (!poJob->GetDataValue3().IsEmpty())
			{
				if (m_csSuffix.IsEmpty())
					m_csSuffix=poJob->GetDataValue3();
				else
					m_csSuffix+=poJob->GetDataValue3();
			}

		}
		
	}
	if (csTemp!="")
	{
		SetSerialNumberPrefix3(csTemp);
		csBuffer+=csTemp;
	}
	else
	{
		SetSerialNumberPrefix3("");
	}
	csTemp="";

	if (poJob->GetPrintDataValue4())
	{

		csDataFieldName=poJob->GetDataName4();
		csDataFieldName.MakeUpper();

		if (csDataFieldName.Find("SUFFIX")==-1)
		{
			csTemp=
			m_poDatabase->GetPrintedValue(poJob->GetDataName4(),
									   poJob->GetDataValue4());
		}
		else
		{
			if (!poJob->GetDataValue4().IsEmpty())
			{
				if (m_csSuffix.IsEmpty())
					m_csSuffix=poJob->GetDataValue4();
				else
					m_csSuffix+=poJob->GetDataValue4();
			}
		
		}
		

	}

	if (csTemp!="")
	{
		SetSerialNumberPrefix4(csTemp);
		csBuffer+=csTemp;
	}
	else
	{
		SetSerialNumberPrefix4("");
	}

	csTemp="";

	if (poJob->GetPrintDataValue5())
	{

		csDataFieldName=poJob->GetDataName5();
		csDataFieldName.MakeUpper();

		if (csDataFieldName.Find("SUFFIX")==-1)
		{
			csTemp=
			m_poDatabase->GetPrintedValue(poJob->GetDataName5(),
									   poJob->GetDataValue5());
		}
		else
		{
			if (!poJob->GetDataValue5().IsEmpty())
			{
				if (m_csSuffix.IsEmpty())
					m_csSuffix=poJob->GetDataValue5();
				else
					m_csSuffix+=poJob->GetDataValue5();
			}
		
		}
		
	}
	if (csTemp!="")
	{
		SetSerialNumberPrefix5(csTemp);
		csBuffer+=csTemp;
	}
	else
	{
		SetSerialNumberPrefix5("");
	}
	

	if (m_csSuffix.IsEmpty())
		csReturnString=csBuffer+csBaseSerialNumber;
	else
		csReturnString=csBuffer+csBaseSerialNumber+m_csSuffix;

	return csReturnString;

}



CString CPrinter::GetPrintedLabel ( )
{

	return ( m_csPrintedLabel );

}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetStatusString
//
//	Description:
//		Get the printer status string for this printer object.
//
//	Arguments:
//		none
//	Return:
//		the status string
//
//	Called by:
//    CPrinterControl::GetStatusString()
/////////////////////////////////////////////////////////////////////////////////////

CString CPrinter::GetStatusString()
{
	CString	csTemp,csReturnString;

	switch ( m_nType )
	{
		case ZEBRA:
			csTemp = m_oComPort.WriteAndRead (csZebraStatusReq,nWatchTime);
			// printer not responding
			if ( csTemp == "" || csTemp.GetLength() < 60 ) 
			{
				csReturnString.LoadString ( IDS_ERR_PRINTER_RESP );
				return (csReturnString);
			}
			// Check for paper out.
			if ( csTemp.GetAt ( 5 ) == '1' )
			{
				csReturnString.LoadString ( IDS_PRINTER_OUTOFPAPER );
				return (csReturnString);
			}
			// Check for pause mode.
			if ( csTemp.GetAt ( 7 ) == '1' )
			{
				csReturnString.LoadString ( IDS_PRINTER_INPAUSE );
				return (csReturnString);
			}
			// Check for buffer full.
			if ( csTemp.GetAt ( 18 ) == '1' )
			{
				csReturnString.LoadString ( IDS_PRINTER_BUFFERFULL );
				return (csReturnString);
			}
			// Check for corrupt RAM.
			if ( csTemp.GetAt ( 28 ) == '1' )
			{
				csReturnString.LoadString ( IDS_PRINTER_BADRAM );
				return (csReturnString);
			}
			// Check for head up.
			if ( csTemp.GetAt ( 43 ) == '1' )
			{
				csReturnString.LoadString ( IDS_PRINTER_HEADUP );
				return (csReturnString);
			}
			// Check for ribbon out.
			if ( csTemp.GetAt ( 45 ) == '1' )
			{
				csReturnString.LoadString ( IDS_PRINTER_RIBBONOUT );
				return (csReturnString);
			}
			return ( "Printer is ready." );

		case INTERMEC:
			return ( "Printer is ready." );	// This printer does not handle the
											// status command.

			csTemp = m_oComPort.WriteAndRead (csIntermecStatusReq,nWatchTime);
			// printer ready
			if ( ( csTemp == "<DC2>" ) || ( csTemp == char(18) ) )
				return ( "Printer is ready." );
			// printer not responding
			if ( csTemp == "" ) 
			{
				csReturnString.LoadString ( IDS_ERR_PRINTER_RESP );
				return (csReturnString);
			}
			// print buffer full
			if ( ( csTemp == "<US>" ) || ( csTemp == char(31) ) || 
				( csTemp == "<DC3>" ) || ( csTemp == char(19) ) )
			{
				csReturnString.LoadString ( IDS_PRINTER_BUFFERFULL );
				return (csReturnString);
			}
			// printer out of ribbon
			if ( ( csTemp == "<GS>" ) || ( csTemp == char(29) ) )
			{
				csReturnString.LoadString ( IDS_PRINTER_RIBBONOUT );
				return (csReturnString);
			}
			// printer out of labels
			if ( ( csTemp == "<EM>" ) || ( csTemp == char(25) ) )
			{
				csReturnString.LoadString ( IDS_PRINTER_OUTOFPAPER );
				return (csReturnString);
			}
			// Printer label material is at strip pin
			if ( ( csTemp == "<FS>" ) || ( csTemp == char(28) ) )
			{
				csReturnString.LoadString ( IDS_PRINTER_STRIPPIN );
				return (csReturnString);
			}

		case DATAMAX:
			csTemp = m_oComPort.WriteAndRead (csDatamaxStatusReq,nWatchTime);

			// if there are no Y's
			if ((csTemp.Find("Y"))==-1)
				csReturnString = "The printer is ready.";
			else
			{
				if (csTemp.Mid(0,1)=="Y")
					csReturnString="The command interpreter is busy.";
				if (csTemp.Mid(1,1)=="Y")
					csReturnString.LoadString ( IDS_PRINTER_OUTOFPAPER );
				if (csTemp.Mid(2,1)=="Y")
					csReturnString.LoadString ( IDS_PRINTER_RIBBONOUT );
				if (csTemp.Mid(3,1)=="Y")
					csReturnString="The printer is busy batch printing.";
				if (csTemp.Mid(4,1)=="Y")
					csReturnString="The printer is busy printing.";
				if (csTemp.Mid(5,1)=="Y")
					csReturnString.LoadString ( IDS_PRINTER_INPAUSE );
				if (csTemp.Mid(6,1)=="Y")
					csReturnString="The printer has presented a label.";
			}
			
			return(csReturnString);
	}
	// we shouldn't get here
	return("");
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		FormFeed
//
//	Description:
//		Send a form feed to the printer
//
//	Arguments:
//		none
//	Return:
//		void
//
//	Called by:
//    CPrinterControl::FormFeed()
/////////////////////////////////////////////////////////////////////////////////////

void CPrinter::FormFeed()
{
	switch ( m_nType )
	{
		case ZEBRA:
			m_oComPort.Write("~PH");
			break;

		case INTERMEC:
			m_oComPort.Write("<STX>R<ETX><STX><FF><ETX>");
			break;

		case DATAMAX:
			m_oComPort.Write("STX F");
			break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetDefaults
//
//	Description:
//		Resets the defaults on the printer
//
//	Arguments:
//		none
//	Return:
//		void
//
//	Called by:
//    CPrinterControl::SetDefaults()
/////////////////////////////////////////////////////////////////////////////////////

void CPrinter::SetDefaults()
{
	switch ( m_nType )
	{
		case ZEBRA:
			m_oComPort.Write("^JUF");
			break;

		case INTERMEC:
			m_oComPort.Write("<STX><ESC>T;D;R<ETX>");
			// the intermec reset sequence takes a long time
			Sleep(10000);
			break;

		case DATAMAX:
			m_oComPort.Write("SOH #");
			break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		ExtractBarCodeText
//
//	Description:
//		Extracts only the bar code text from an entire label
//
//	Arguments:
//		CString csPrintedLabel: the entire label string sent to the printer
//	Return:
//		CString, the bar code portion of the printer string
//
//	Called by:
//    CPrinter::BuildLabel
/////////////////////////////////////////////////////////////////////////////////////

CString CPrinter::ExtractBarCodeText(CString csPrintedLabel)
{
	CString  csBarCodeString,csTempString;
	int		nIndex;
	char		tempChar;

	csBarCodeString = csPrintedLabel;
	
	switch ( m_nType )
	{
		case ZEBRA:
			nIndex = csBarCodeString.Find("^B");
			if (nIndex==-1)
			{
				tempChar = '\x1E';
				csTempString = tempChar;
				csTempString += "B";
				nIndex = csBarCodeString.Find(csTempString);
			}
			if (nIndex!=-1)
			{
				csBarCodeString  = csBarCodeString.Mid(nIndex);
				nIndex = csBarCodeString.Find("^FD");
				if (nIndex==-1)
				{
					tempChar = '\x1E';
					csTempString = tempChar;
					csTempString += "FD";
					nIndex = csBarCodeString.Find(csTempString);
				}
				if (nIndex!=-1)
				{
					csBarCodeString  = csBarCodeString.Mid(nIndex+3);
					nIndex = csBarCodeString.Find("^FS");
					if (nIndex==-1)
					{
						tempChar = '\x1E';
						csTempString = tempChar;
						csTempString += "FS";
						nIndex = csBarCodeString.Find(csTempString);
					}
					if (nIndex!=-1)
						csBarCodeString = csBarCodeString.Left(nIndex);
					else
						csBarCodeString.Empty();
				}
				else
					csBarCodeString.Empty();
			}
			else
				csBarCodeString.Empty();
			break;
		case INTERMEC:
			nIndex = csBarCodeString.Find("<STX>B");
			if (nIndex==-1)
			{
				tempChar = '\x002';
				csTempString = tempChar;
				csTempString += "B";
				nIndex = csBarCodeString.Find(csTempString);
			}
			if (nIndex!=-1)
			{
				csBarCodeString  = csBarCodeString.Mid(nIndex);
				nIndex = csBarCodeString.Find(";d");
				if (nIndex!=-1)
				{
					csBarCodeString  = csBarCodeString.Mid(nIndex);
					nIndex = csBarCodeString.Find(",");
					if (nIndex!=-1)
					{
						csBarCodeString = csBarCodeString.Mid(nIndex+1);
						nIndex = csBarCodeString.Find(";");
						if (nIndex!=-1)
							csBarCodeString = csBarCodeString.Left(nIndex);
						else
							csBarCodeString.Empty();
					}
					else
						csBarCodeString.Empty();
				}
				else
					csBarCodeString.Empty();
			}
			else
				csBarCodeString.Empty();
			break;
		case DATAMAX:
			break;
	}
	return(csBarCodeString);
}

CString CPrinter::GetSerialNumberPrefix1()
{
	return m_csSerialNumberPrefix1;
}

CString CPrinter::GetSerialNumberPrefix2()
{
	return m_csSerialNumberPrefix2;
}

CString CPrinter::GetSerialNumberPrefix3()
{
	return m_csSerialNumberPrefix3;

}

CString CPrinter::GetSerialNumberPrefix4()
{
	return m_csSerialNumberPrefix4;

}

CString CPrinter::GetSerialNumberPrefix5()
{
	return m_csSerialNumberPrefix5;

}

CString CPrinter::GetSuffix()
{
	return m_csSuffix;

}

int CPrinter::GetSuffixStrLength()
{
	return m_csSuffix.GetLength();

}


void CPrinter::SetSerialNumberPrefix1(CString csPrefixValue)
{
	m_csSerialNumberPrefix1=csPrefixValue;
	SetSerialNumberPrefix1Width(csPrefixValue);
}

void CPrinter::SetSerialNumberPrefix2(CString csPrefixValue)
{
	m_csSerialNumberPrefix2=csPrefixValue;
	SetSerialNumberPrefix2Width(csPrefixValue);

}

void CPrinter::SetSerialNumberPrefix3(CString csPrefixValue)
{
	m_csSerialNumberPrefix3=csPrefixValue;
	SetSerialNumberPrefix3Width(csPrefixValue);

}

void CPrinter::SetSerialNumberPrefix4(CString csPrefixValue)
{
	m_csSerialNumberPrefix4=csPrefixValue;
	SetSerialNumberPrefix4Width(csPrefixValue);

}

void CPrinter::SetSerialNumberPrefix5(CString csPrefixValue)
{
	m_csSerialNumberPrefix5=csPrefixValue;
	SetSerialNumberPrefix5Width(csPrefixValue);

}


CString CPrinter::GetPrintedSerialNumber()
{
	return m_csSerialNumber;

}

void CPrinter::SetPrintedSerialNumber(CString csSerialNumber)
{
	m_csSerialNumber=csSerialNumber;
}

int CPrinter::GetSerialNumberPrefix1Width()
{
	return m_nSerialNumberPrefix1Width;
}

int CPrinter::GetSerialNumberPrefix2Width()
{
	return m_nSerialNumberPrefix2Width;
}

int CPrinter::GetSerialNumberPrefix3Width()
{
	return m_nSerialNumberPrefix3Width;
}

int CPrinter::GetSerialNumberPrefix4Width()
{
	return m_nSerialNumberPrefix4Width;
}

int CPrinter::GetSerialNumberPrefix5Width()
{
	return m_nSerialNumberPrefix5Width;
}

void CPrinter::SetSerialNumberPrefix1Width(CString csPrefixValue)
{
	m_nSerialNumberPrefix1Width=csPrefixValue.GetLength();
}

void CPrinter::SetSerialNumberPrefix2Width(CString csPrefixValue)
{
	m_nSerialNumberPrefix2Width=csPrefixValue.GetLength();
}

void CPrinter::SetSerialNumberPrefix3Width(CString csPrefixValue)
{
	m_nSerialNumberPrefix3Width=csPrefixValue.GetLength();
}

void CPrinter::SetSerialNumberPrefix4Width(CString csPrefixValue)
{
	m_nSerialNumberPrefix4Width=csPrefixValue.GetLength();
}

void CPrinter::SetSerialNumberPrefix5Width(CString csPrefixValue)
{
	m_nSerialNumberPrefix5Width=csPrefixValue.GetLength();
}


BOOL CPrinter::GetApolloStatus( )
{


CString csStatus;
CString csTemp;
CString csOnlineStatus;
	
	if ((SIMULATION)&(SIMULATEPRINTER))
	{
		return true;
	}
	m_oComPort.SetTriggerDelay ( 100 );

	csStatus = m_oComPort.WriteAndRead ( "\033s \r", 1 );

	// The return string is the status of a THARO printer. 

	if ( csStatus == "" || csStatus.GetLength() < 9 ) 
	{
		csTemp.LoadString ( IDS_ERR_PRINTER_RESP );
		AfxMessageBox ( csTemp );
		return ( FALSE );
	}

	csOnlineStatus=csStatus.Mid(0,1);
	if (csOnlineStatus=="N") 
	{
		AfxMessageBox ( "Printer Not Online." );
		return ( FALSE );


	}
	
	csOnlineStatus=csStatus.Mid(1,1);
	if (csOnlineStatus!="-") 
	{
		AfxMessageBox ( GetApolloErrorMsg(csOnlineStatus) );
		return ( FALSE );
	}
	return TRUE;
}

CString CPrinter::GetApolloErrorMsg(CString csErrorType)
{
CString csReturnMessage;

	if (csErrorType=="A")
	{
		csReturnMessage="Applicator Error";
	}
	else if (csErrorType=="B")
	{
		csReturnMessage="Protocal Error";

	}
	else if (csErrorType=="C")
	{
		csReturnMessage="Memory Card Error";

	}
	else if (csErrorType=="D")
	{
		csReturnMessage="Printhead Open";

	}
	else if (csErrorType=="E")
	{
		csReturnMessage="No Label Found";

	}
	else if (csErrorType=="F")
	{
		csReturnMessage="End Of Ribbon";

	}
	else if (csErrorType=="G")
	{
		csReturnMessage="Illegal Heating Voltage";

	}
	else if (csErrorType=="M")
	{
		csReturnMessage="Cutter Jammed";

	}
	else if (csErrorType=="N")
	{
		csReturnMessage="Media Too Thick For Cutting";

	}
	else if (csErrorType=="O")
	{
		csReturnMessage="Out Of Memory";

	}
	else if (csErrorType=="P")
	{
		csReturnMessage="Out Of Paper";

	}
	else if (csErrorType=="S")
	{
		csReturnMessage="Ribbon Saver Malfunction";

	}
	else if (csErrorType=="V")
	{
		csReturnMessage="Input Buffer Overflow";

	}
	else if (csErrorType=="W")
	{
		csReturnMessage="Print Head Too Hot";

	}
	else if (csErrorType=="X")
	{
		csReturnMessage="External I/O Error";

	}
	else if (csErrorType=="Z")
	{
		csReturnMessage="Printhead Damaged";

	}

	return csReturnMessage;

}


void CPrinter::ResetPrinter()
{
CString csFlushCmd;

	Trace("[I] CPrinter:: Start of ResetPrinter()\n\r");

	if ((SIMULATION)&(SIMULATEPRINTER))
	{


		Trace("[IS] CPrinter:: End of ResetPrinter()\n\r");

		return ;

	}


	switch ( m_nType )
	{

		case APOLLO:
		case THARO:
			if (!GetApolloStatus()) return;
			csFlushCmd=csApolloFlushQueue;
			m_oComPort.Write ( csFlushCmd); 
			break;

		case ZEBRA:
			csFlushCmd=csZebraFlushQueue;
			m_oComPort.Write ( csFlushCmd); 

			break;
	}

	return;

}

CString CPrinter::GetCheckDigitValue()
{
	return m_csCheckDigit;

}

CString CPrinter::ConvertCode128_SSA(CString csSerialNumber)
{
int nOffset,
	nLen;


CString csCode128_SSA;
	nLen=csSerialNumber.GetLength();

	for (nOffset=0;nOffset<nLen;nOffset++)
	{
		csCode128_SSA+=Convert_SSA(csSerialNumber.Mid(nOffset,1));
	}

	if (csCode128_SSA.IsEmpty())
		return csSerialNumber;

	return csCode128_SSA;


}

CString CPrinter::Convert_SSA(CString csBuffer)
{
	if (csBuffer==" ")
		return "0";
	else if (csBuffer=="!")
		return "1";
	else if (csBuffer=="#")
		return "3";
	else if (csBuffer=="$")
		return "4";
	else if (csBuffer=="%")
		return "5";
	else if (csBuffer=="&")
		return "6";
	else if (csBuffer=="(")
		return "8";
	else if (csBuffer==")")
		return "9";
	else if (csBuffer=="*")
		return "10";
	else if (csBuffer=="++")
		return "11";
	else if (csBuffer==",")
		return "12";
	else if (csBuffer=="-")
		return "13";
	else if (csBuffer==".")
		return "14";
	else if (csBuffer=="/")
		return "15";
	else if (csBuffer=="0")
		return "16";
	else if (csBuffer=="1")
		return "17";
	else if (csBuffer=="2")
		return "18";
	else if (csBuffer=="3")
		return "19";
	else if (csBuffer=="4")
		return "20";
	else if (csBuffer=="5")
		return "21";
	else if (csBuffer=="6")
		return "22";
	else if (csBuffer=="7")
		return "23";
	else if (csBuffer=="8")
		return "24";
	else if (csBuffer=="9")
		return "25";
	else if (csBuffer==":")
		return "26";
	else if (csBuffer==";")
		return "27";
	else if (csBuffer=="<")
		return "28";
	else if (csBuffer=="=")
		return "29";
	else if (csBuffer==">")
		return "30";
	else if (csBuffer=="?")
		return "31";
	else if (csBuffer=="@")
		return "32";
	else if (csBuffer=="A")
		return "33";
	else if (csBuffer=="B")
		return "34";
	else if (csBuffer=="C")
		return "35";
	else if (csBuffer=="D")
		return "36";
	else if (csBuffer=="E")
		return "37";
	else if (csBuffer=="F")
		return "38";
	else if (csBuffer=="G")
		return "39";
	else if (csBuffer=="H")
		return "40";
	else if (csBuffer=="I")
		return "41";
	else if (csBuffer=="J")
		return "42";
	else if (csBuffer=="K")
		return "43";
	else if (csBuffer=="L")
		return "44";
	else if (csBuffer=="M")
		return "45";
	else if (csBuffer=="N")
		return "46";
	else if (csBuffer=="O")
		return "47";
	else if (csBuffer=="P")
		return "48";
	else if (csBuffer=="Q")
		return "49";
	else if (csBuffer=="R")
		return "50";
	else if (csBuffer=="S")
		return "51";
	else if (csBuffer=="T")
		return "52";
	else if (csBuffer=="U")
		return "53";
	else if (csBuffer=="V")
		return "54";
	else if (csBuffer=="W")
		return "55";
	else if (csBuffer=="X")
		return "56";
	else if (csBuffer=="Y")
		return "57";
	else if (csBuffer=="Z")
		return "58";
	else if (csBuffer=="[")
		return "59";
//	else if (csBuffer=="\")
//		return "60";
	else if (csBuffer=="]")
		return "61";

	return csBuffer;

}