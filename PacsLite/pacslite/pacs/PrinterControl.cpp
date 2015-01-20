// PrinterControl.cpp: implementation of the CPrinterControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PACS.h"
#include "ApplicatorControl.h"
#include "PrinterControl.h"
#include "trace.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPrinterControl::CPrinterControl()
{

}

CPrinterControl::~CPrinterControl()
{

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		Initialize
//
//	Description:
//		Initialize all printers and control.
//
//	Arguments:
//		Pointer to database.
//
//	Return:
//		Status.
//
//	Called by:
//		CApplicatorControl::Initialize 
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CPrinterControl::Initialize ( CDatabase *poDatabase, CSNManager *poSNManager )
{
	BOOL		bInit,bUse;

	CString	csTemp;


	// save pointer to snmanager
	m_poSNManager = poSNManager;

	m_bInitialized = TRUE;

	// Initialize all printers. This is done to all. If the printer is not in
	// use for this customer, we just ignore it. We do this because we don't
	// know if the printer is used yet and to minimize the amount of custom
	// work that is required for each customer.

	bInit = m_oPrinter.Initialize ( poDatabase, poSNManager,  &bUse );


	return ( m_bInitialized );
}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		PrintLabel
//
//	Description:
//		Build printer template and send to printer.
//
//	Arguments:
//		Run or manual mode.
//		Printer to drive.
//		Template to send to printer.
//
//	Return:
//		Printing status.
//
//	Called by:
//		ApplicatorControl::Run, ApplicatorControl::ManualFeed
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CPrinterControl::PrintLabel ( int nStatus, BOOL bRunMode, CJob *poJob, CString csTemplate, int nFirstLabel )
{

	BOOL bStatus;
	CString	csSerialNumber;

	Trace("[I] Start of CPrinterControl::PrintLabel ");

	if ((nStatus!=STATUS_RELABEL)&&(nFirstLabel==1))
	{
		// empty any old values
		m_csTemplate.Empty();
		

		if ( bRunMode )
		{
			m_poSNManager->GetNextSerialNumber(poJob->GetJobName());
			csSerialNumber = m_poSNManager->GetSerialNumber();
			m_poSNManager->SetSerialNumberN ( 1, csSerialNumber );
		}

		m_csTemplate = m_oPrinter.BuildLabel (bRunMode, poJob, csTemplate);
	
		
		if (m_csTemplate.IsEmpty())	// Error Condition exist.
			return FALSE;

	
	}
	else
	{

		m_csTemplate.Empty();
		
		m_csTemplate = m_oPrinter.BuildLabel (bRunMode, poJob, csTemplate);



	}
	

	
	bStatus = m_oPrinter.PrintLabel ( m_csTemplate );
	Trace("[I] End of CPrinterControl::PrintLabel ");

	return ( bStatus );

}

void CPrinterControl::ReSyncSerialNumber(CJob *poJob)
{
CString csSerialNumber;

	m_poSNManager->GetNextSerialNumber(poJob->GetJobName());
	csSerialNumber = m_poSNManager->GetSerialNumber();
	m_poSNManager->SetSerialNumberN ( 1, csSerialNumber );

}


BOOL CPrinterControl::GetPrinterTemplate ( CString *csTemplate )
{

	// Get printer CLSID from label file. The label file name is stored
	// in the database. If CLSID does not exist then ????
	



	return ( TRUE );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		UpdatePrinterAttributes
//
//	Description:
//		Printer attributes may have changed. Update new attributes for all printers.
//
//	Arguments:
//		Pointer to database.
//
//	Return:
//		Status.
//
//	Called by:
//		CSetupDlg::OnClickCmdPrinterSetup
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CPrinterControl::UpdatePrinterAttributes ( CDatabase *poDatabase )
{
	
	// start as true
	m_bInitialized = TRUE;
	
	// Update the attributes of all printers that are in use.
	if ( m_oPrinter.GetUse() )
	{
		if ( !m_oPrinter.Refresh ( poDatabase ) )
			m_bInitialized = FALSE;
	}


	// return success or failure	
	return ( m_bInitialized );
}




void CPrinterControl::SetUse ( BOOL bUse)
{

	m_oPrinter.SetUse ( bUse );

}


void CPrinterControl::SetType ( int nType)
{

	m_oPrinter.SetType ( nType );

}


void CPrinterControl::SetEnable ( BOOL bEnable)
{

	m_oPrinter.SetEnable ( bEnable );

}


BOOL CPrinterControl::GetUse ( )
{

	
	return ( m_oPrinter.GetUse());

}


int CPrinterControl::GetType ()
{

	

	return ( m_oPrinter.GetType());

}


BOOL CPrinterControl::GetEnable ()
{

	return ( m_oPrinter.GetEnable() );

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
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CPrinterControl::GetStatus ()
{

	return ( m_oPrinter.GetStatus() );

}



CString CPrinterControl::GetPrintedLabel ()
{


	return ( m_oPrinter.GetPrintedLabel() );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetStatusString
//
//	Description:
//		Get the printer status string for the specified printer.
//
//	Arguments:
//		integer nPrinter, the printer we want the status string for
//	Return:
//		the status string
//
//	Called by:
//    CPrinterDiagDlg::OnInitDialog, CPrinterDiagDlg::OnSelchangePrinterSelected
/////////////////////////////////////////////////////////////////////////////////////

CString CPrinterControl::GetStatusString()
{
	CString	csReturnString;
	
	// start with an empty string
	csReturnString.Empty();

	csReturnString = m_oPrinter.GetStatusString();
	return(csReturnString);
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetDefaults
//
//	Description:
//		Resets the defaults for the chosen printer
//
//	Arguments:
//		integer nPrinter, the printer we want the status string for
//	Return:
//		void
//
//	Called by:
//    CPrinterDiagDlg::OnClickSetDefaults
/////////////////////////////////////////////////////////////////////////////////////

void CPrinterControl::SetDefaults()
{
	m_oPrinter.SetDefaults();
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		FormFeed
//
//	Description:
//		Sends form feed command to the specified printer
//
//	Arguments:
//	Return:
//		void
//
//	Called by:
//    CPrinterDiagDlg::OnClickFormFeed
/////////////////////////////////////////////////////////////////////////////////////

void CPrinterControl::FormFeed()
{
	m_oPrinter.FormFeed();
}



CString CPrinterControl::GetPrefix1 ( )
{
	return ( m_oPrinter.GetSerialNumberPrefix1());
}


CString CPrinterControl::GetPrefix2( )
{
	return ( m_oPrinter.GetSerialNumberPrefix2());
}


CString CPrinterControl::GetPrefix3 ( )
{
	return ( m_oPrinter.GetSerialNumberPrefix3());
}


CString CPrinterControl::GetPrefix4( )
{
	return ( m_oPrinter.GetSerialNumberPrefix4());
}

CString CPrinterControl::GetPrefix5( )
{
	return ( m_oPrinter.GetSerialNumberPrefix4());
}



CString CPrinterControl::GetPrefixes(CString csDelimiter)
{

	CString
		csLabel, csTemp,csTemp2;


	csTemp=m_oPrinter.GetSerialNumberPrefix1();

	if (csTemp!="")
	{
		csLabel+=csTemp+csDelimiter;
	}
			
	csTemp2=m_oPrinter.GetSerialNumberPrefix2();

	if (csTemp2!="")
	{
		csTemp=m_oPrinter.GetSerialNumberPrefix2();

		csLabel+=csTemp+csDelimiter;
	}

	csTemp2=m_oPrinter.GetSerialNumberPrefix3();

	if (csTemp2!="")
	{
		csTemp=m_oPrinter.GetSerialNumberPrefix3();

		csLabel+=csTemp+csDelimiter;
	}

	csTemp2=m_oPrinter.GetSerialNumberPrefix4();

	if (csTemp2!="")
	{
		csTemp=m_oPrinter.GetSerialNumberPrefix4();

		csLabel+=csTemp+csDelimiter;
	}

	csTemp2=m_oPrinter.GetSerialNumberPrefix5();

	if (csTemp2!="")
	{
		csTemp=m_oPrinter.GetSerialNumberPrefix5();
		csLabel+=csTemp+csDelimiter;
	}

	return ( csLabel );


}

CString CPrinterControl::GetPrintedSerialNumber()
{

	CString
		csSerialNumber;

	csSerialNumber = m_oPrinter.GetPrintedSerialNumber();

	return (csSerialNumber);
}


void CPrinterControl::SetPrintedSerialNumber(CString csSerialNumber)
{


	m_oPrinter.SetPrintedSerialNumber(csSerialNumber);

}



int CPrinterControl::GetPrintedSerialNumberPrefix1Width()
{

int
	nPrefixWidth=0;

	nPrefixWidth = m_oPrinter.GetSerialNumberPrefix1Width();

	return (nPrefixWidth);
}


int CPrinterControl::GetPrintedSerialNumberPrefix2Width()
{

int
	nPrefixWidth=0;

	nPrefixWidth = m_oPrinter.GetSerialNumberPrefix2Width();
	return (nPrefixWidth);
}


int CPrinterControl::GetPrintedSerialNumberPrefix3Width()
{

int
	nPrefixWidth=0;
	nPrefixWidth = m_oPrinter.GetSerialNumberPrefix3Width();

	return (nPrefixWidth);
}


int CPrinterControl::GetPrintedSerialNumberPrefix4Width()
{

int
	nPrefixWidth=0;

	nPrefixWidth = m_oPrinter.GetSerialNumberPrefix4Width();

	return (nPrefixWidth);
}


int CPrinterControl::GetPrintedSerialNumberPrefix5Width()
{

int
	nPrefixWidth=0;

	nPrefixWidth = m_oPrinter.GetSerialNumberPrefix5Width();

	return (nPrefixWidth);
}


void CPrinterControl::ResetPrinter()
{
	m_oPrinter.ResetPrinter();

}

CString CPrinterControl::GetSuffix()
{
	return m_oPrinter.GetSuffix();

}

int CPrinterControl::GetSuffixStrLength()
{
	return m_oPrinter.GetSuffixStrLength();

}

CString CPrinterControl::GetCheckDigitValue()
{
	return m_oPrinter.GetCheckDigitValue();

}