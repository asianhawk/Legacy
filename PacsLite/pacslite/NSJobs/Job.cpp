// Job.cpp: implementation of the CJob class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Job.h"
#include "NSSysDBase.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CJob::CJob()
{

	m_csFrontPrinterStatus = "Normal";
	m_csBackUSPrinterStatus = "Normal";
	m_csBackDSPrinterStatus = "Normal";
	m_LabelPos = NULL;
}


CJob::~CJob()
{

}


void CJob::SetJobName ( CString csJobName ) 
{	
	m_csJobName = csJobName;
}


void CJob::SetPoints ( CString csPoint ) 
{	
	m_csPointList= csPoint; 
}


CString CJob::GetJobName() 
{	
	return ( m_csJobName );
}


CString CJob::GetPoints() 
{	
	return ( m_csPointList );
}


CString CJob::GetPrinterLabelStatus ( int nPrinter ) 
{	

	CString 
		csStatus;

	switch ( nPrinter )
	{
		case FRONT_DOWNSTREAM_PRINTER:
			csStatus = m_csFrontPrinterStatus;
			break;

		case BACK_UPSTREAM_PRINTER:
			csStatus = m_csBackUSPrinterStatus;
			break;

		case BACK_DOWNSTREAM_PRINTER:
			csStatus = m_csBackDSPrinterStatus;
			break;
	}

	return ( csStatus ); 

}


BOOL CJob::SetPrinterLabelStatus ( int nPrinter, CString csStatus ) 
{ 

	switch ( nPrinter )
	{
		case FRONT_DOWNSTREAM_PRINTER:
			m_csFrontPrinterStatus = csStatus;
			break;

		case BACK_UPSTREAM_PRINTER:
			m_csBackUSPrinterStatus = csStatus;
			break;

		case BACK_DOWNSTREAM_PRINTER:
			m_csBackDSPrinterStatus = csStatus;
			break;
	}

	return ( TRUE );

}


void CJob::SetDescription ( CString csDescription )
{
	m_csDescription = csDescription;
}


CString CJob::GetDescription ( void )
{
	return ( m_csDescription );
}


void CJob::SetLabelCount ( long lLabelCount )
{
	m_lLabelCount = lLabelCount;
}


void CJob::SetPanelCount ( long lPanelCount )
{
	m_lPanelCount = lPanelCount;
}


long CJob::GetLabelCount ( void )
{
	return ( m_lLabelCount );
}


long CJob::GetPanelCount ( void )
{
	return ( m_lPanelCount );
}


void CJob::SetPanelDimension ( CString csPanelDimension )
{
	m_csPanelDimension = csPanelDimension;
}


CString CJob::GetPanelDimension ( void )
{
	return ( m_csPanelDimension );
}


BOOL CJob::GetUseWYSIWYG ( void )
{
	return ( m_bUseWYSIWYG );
}



void CJob::SetUseWYSIWYG ( BOOL bUseWYSIWYG )
{
	m_bUseWYSIWYG = bUseWYSIWYG;
}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetPlacementAttributes
//
//	Description:
//		Build a label attribute string based on the label list.
//
//	Arguments:
//		None
//
//	Return:
//		Label attribute string.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

CString CJob::GetPlacementAttributes ( void )
{

	CString csTemp;
	CString csAttributes = "";

	CLabel *Label;

	POSITION pos;

	
	// Each label attribute string contains the following attributes:
	//
	//		X, Y, Rotation, Template name, Printer Location, Enable Scanner;

	// Loop through label list and build entire string. Placement order
	// is correct from head to tail of list.

	
	pos = m_LabelList.GetHeadPosition();

	while ( pos != NULL )
	{

		Label = (CLabel *)m_LabelList.GetNext ( pos );

		if (csAttributes.IsEmpty())
			csAttributes = Label->GetTemplateName();
		else
			csAttributes = csAttributes + Label->GetTemplateName();

		csAttributes += ",";

		csTemp = Label->GetPrinterName();
 		csAttributes += csTemp;

		csAttributes += ",";

		if ( Label->GetEnableScan () )
			csTemp = "YES";
		else
			csTemp = "NO";
		csAttributes += csTemp;
		csAttributes += ";";

	}

	return ( csAttributes );

}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetPlacementAttributes
//
//	Description:
//		Build a label object list based on a placement attribute string.
//
//	Arguments:
//		Attribute string
//
//	Return:
//		None
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

void CJob::SetPlacementAttributes ( CString csPlacementAttributes )
{
	
	// Each label placement substring contains the following attributes:
	//
	//		X, Y, Rotation, Template Name, Printer Location, Enable Scanner;

	// The pointer to each label to add to the list
	CLabel* pLabel;
	
	// empty the label list
	while ( !m_LabelList.IsEmpty() )
	{
		pLabel = (CLabel *)m_LabelList.RemoveHead();
		delete pLabel;
	}

	// count the number of labels
	CString	csTemp = csPlacementAttributes;
	int		nLabelCount = 1;
	int		nIndex;

	// find the first seperator
	nIndex = csTemp.Find(";");
	while (nIndex!=-1)
	{
		// if its not the last character
		if (nIndex!=(csTemp.GetLength()-1))
			nLabelCount++;
		
		// discard the left portion of the string
		csTemp = csTemp.Right(csTemp.GetLength()-nIndex-1);

		// find the next seperator character
		nIndex = csTemp.Find ( ";" );
	}
	
	// start with the full string again
	csTemp = csPlacementAttributes;
	// declare and initialize variables needed in the for loop
	int i;
	CString	csScannerFlag,csTemplate,csTemplateName,csTemplateNameList;
	
	// add all the labels to the label list
	for(i=0;i<nLabelCount;i++)
	{
		// declare a new label
		pLabel = new CLabel();
		
		// save the X value
		nIndex = csTemp.Find(",");
		// if an error
		if ( nIndex == -1 )
		{
			csTemp = "Invalid Label Attribute";
			AfxMessageBox (csTemp);
			return;
		}
		// save the template name
		nIndex = csTemp.Find(",");
		// if an error
		if ( nIndex == -1 )
		{
			csTemp = "Invalid Label Attribute";

			AfxMessageBox (csTemp);
			return;
		}
		
		// extract the template name for this label
		csTemplateName = csTemp.Left(nIndex);
		// get the template
		GetTemplate(csTemplateName,&csTemplate);
		// save the template name and the template
		pLabel->SetTemplateName (csTemplateName);
		pLabel->SetTemplate(csTemplate);
		// if we haven't had this template name before add it to the list
		if (csTemplateNameList.Find(csTemplateName)==-1)
		{
			csTemplateNameList+=csTemplateName;
			csTemplateNameList+=";";
		}

		// discard the left portion of the string
		csTemp = csTemp.Right(csTemp.GetLength()-nIndex-1);

		// save the printer location
		nIndex = csTemp.Find(",");
		// if an error
		if ( nIndex == -1 )
		{
			csTemp = "Invalid Label Attribute";
			AfxMessageBox (csTemp);
			return;
		}
		pLabel->SetPrinterName ( csTemp.Left(nIndex));

		csTemp = csTemp.Right(csTemp.GetLength()-nIndex-1);

		// save the scanner enable flag
		nIndex = csTemp.Find(";");
		if ( nIndex == -1 )
		{
			csTemp = "Invalid Label Attribute";
			AfxMessageBox (csTemp);
			return;
		}
		csScannerFlag = csTemp.Left(nIndex);
		if ( csScannerFlag.CompareNoCase ("YES") == 0 )
			pLabel->SetEnableScan ( TRUE );
		else
			pLabel->SetEnableScan ( FALSE );
		// discard the left portion of the string
		csTemp = csTemp.Right(csTemp.GetLength()-nIndex-1);

		// add label to tail of list
		m_LabelList.AddTail( pLabel );
	}

	// save the list of templates used in this job
	//	SetTemplateList(csTemplateNameList);
}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetNumberOfLabels
//
//	Description:
//		Get the size of the label list.
//
//	Arguments:
//		None
//
//	Return:
//		Number of Labels.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

int CJob::GetNumberOfLabels ( void )
{

	int
		nLabels = 0;


	nLabels = m_LabelList.GetCount();

	return ( nLabels );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetFirstLabel
//
//	Description:
//		Get the first label in the label list.
//
//	Arguments:
//		None
//
//	Return:
//		Pointer to label
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

CLabel* CJob::GetFirstLabel ( void )
{
	// save the head position for GetNext
	m_LabelPos = m_LabelList.GetHeadPosition();

	// return the head label
	return((CLabel *)m_LabelList.GetNext(m_LabelPos));
}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetNextLabel
//
//	Description:
//		Get the next label in the label list.
//
//	Arguments:
//		None
//
//	Return:
//		Pointer to label
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

CLabel* CJob::GetNextLabel ( void )
{

	CLabel *pLabel;

	if ( m_LabelPos != NULL )
	{
		pLabel = (CLabel *)m_LabelList.GetNext ( m_LabelPos );
		return ( pLabel );
	}
	else
		return ( NULL );
}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetLabel
//
//	Description:
//		Get the label in the label list at the index.
//
//	Arguments:
//		Index into list.
//
//	Return:
//		Pointer to label
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////


CLabel* CJob::GetLabel ( int nIndex )
{
	// save the index position for GetNext
	m_LabelPos = m_LabelList.FindIndex(nIndex);
	
	// return the label at this index
	return((CLabel *)m_LabelList.GetAt(m_LabelPos));
}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetPrinterLocationID
//
//	Description:
//		Get the physical location of the printer. Kind of like a printer ID.
//
//	Arguments:
//		Name of printer location.
//
//	Return:
//		Pointer to label
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////


int CJob::GetPrinterLocationID ( CString csLocation )
{
	if (csLocation.CompareNoCase("Front_Downstream")==0)
		return(FRONT_DOWNSTREAM_PRINTER);
	if ( csLocation.CompareNoCase ("Back_Upstream")==0)
		return(BACK_UPSTREAM_PRINTER);
	if ( csLocation.CompareNoCase ("Back_Downstream")==0)
		return(BACK_DOWNSTREAM_PRINTER);

	return(FRONT_DOWNSTREAM_PRINTER);
}



CString CJob::GetPrinterLocationString ( int nLocation )
{

	CString
		csName;


	switch ( nLocation )
	{

		case FRONT_DOWNSTREAM_PRINTER:
			csName = "Front_Downstream";
			break;

		case BACK_UPSTREAM_PRINTER:
			csName = "Back_Upstream";
			break;

		case BACK_DOWNSTREAM_PRINTER:
			csName = "Back_Downstream";
			break;


		default:
			csName = "NA";

	}

	return ( csName );

}

int CJob::GetXOffset()
{
	return(m_nXOffset);
}

int CJob::GetYOffset()
{
	return(m_nYOffset);
}

void CJob::SetXOffset(int nXOffset)
{
	m_nXOffset = nXOffset;
	return;
}

void CJob::SetYOffset(int nYOffset)
{
	m_nYOffset = nYOffset;
	return;
}

void CJob::SetLabelStockXOffset(int nOffset)
{
	m_nLabelStockXOffset = nOffset;
	return;
}

void CJob::SetLabelStockYOffset(int nOffset)
{
	m_nLabelStockYOffset = nOffset;
	return;
}

int CJob::GetLabelStockXOffset()
{
	return (m_nLabelStockXOffset);
}

int CJob::GetLabelStockYOffset()
{
	return (m_nLabelStockYOffset);
}

void CJob::SetJob2up(BOOL b2up)
{
	m_bJob2up = b2up;
}

BOOL CJob::GetJob2up()
{
	return (m_bJob2up);
}

void CJob::SetCountry(CString csCountry)
{
	m_csCountry = csCountry;
	return;
}

CString CJob::GetCountry()
{
	return (m_csCountry);
}

void CJob::SetManufacturingSite(CString csManufacturingSite)
{
	m_csManufacturingSite = csManufacturingSite;
	return;
}

CString CJob::GetManufacturingSite()
{
	return (m_csManufacturingSite);
}

void CJob::SetProductCode(CString csProductCode)
{
	m_csProductCode = csProductCode;
	return;
}

CString CJob::GetProductCode()
{
	return (m_csProductCode);
}

void CJob::SetRelease(CString csRelease)
{
	m_csRelease = csRelease;
	return;
}

CString CJob::GetRelease()
{
	return (m_csRelease);
}


CString CJob::GetCustomer ( void )
{
	return ( m_csCustomer );
}


void CJob::SetCustomer ( CString csCustomer )
{
	m_csCustomer = csCustomer;
}


CString CJob::GetStaticDateCode()
{
	return (m_csStaticDateCode);
}

void CJob::SetStaticDateCode(CString csDateCode)
{
	m_csStaticDateCode = csDateCode;
	return;
}

BOOL CJob::GetUseStaticDateCode()
{
	return (m_bUseStaticDateCode);
}

void CJob::SetUseStaticDateCode(BOOL bUseStaticDateCode)
{
	m_bUseStaticDateCode = bUseStaticDateCode;
	return;
}


// The following data name functions support the dynamic capabilites
// of setting up job information. There are 5 data fields that are
// user configurable. Each one of those fields can have a user specified
// name and string value.

void CJob::SetDataName1 ( CString csDataName )
{
	m_csDataName1 = csDataName;
}

void CJob::SetDataName2 ( CString csDataName )
{
	m_csDataName2 = csDataName;
}

void CJob::SetDataName3 ( CString csDataName )
{
	m_csDataName3 = csDataName;
}

void CJob::SetDataName4 ( CString csDataName )
{
	m_csDataName4 = csDataName;
}

void CJob::SetDataName5 ( CString csDataName )
{
	m_csDataName5 = csDataName;
}

CString CJob::GetDataName1()
{
	return ( m_csDataName1 );
}

CString CJob::GetDataName2()
{
	return ( m_csDataName2 );
}

CString CJob::GetDataName3()
{
	return ( m_csDataName3 );
}

CString CJob::GetDataName4()
{
	return ( m_csDataName4 );
}

CString CJob::GetDataName5()
{
	return ( m_csDataName5 );
}


void CJob::SetDataValue1 ( CString csDataValue )
{
	m_csDataValue1 = csDataValue;
}

void CJob::SetDataValue2 ( CString csDataValue )
{
	m_csDataValue2 = csDataValue;
}

void CJob::SetDataValue3 ( CString csDataValue )
{
	m_csDataValue3 = csDataValue;
}

void CJob::SetDataValue4 ( CString csDataValue )
{
	m_csDataValue4 = csDataValue;
}

void CJob::SetDataValue5 ( CString csDataValue )
{
	m_csDataValue5 = csDataValue;
}

CString CJob::GetDataValue1()
{
	return ( m_csDataValue1 );
}

CString CJob::GetDataValue2()
{
	return ( m_csDataValue2 );
}

CString CJob::GetDataValue3()
{
	return ( m_csDataValue3 );
}

CString CJob::GetDataValue4()
{
	return ( m_csDataValue4 );
}

CString CJob::GetDataValue5()
{
	return ( m_csDataValue5 );
}


BOOL CJob::GetLogDataValue1()
{
	return ( m_bLogDataValue1 );
}

BOOL CJob::GetLogDataValue2()
{
	return ( m_bLogDataValue2 );
}

BOOL CJob::GetLogDataValue3()
{
	return ( m_bLogDataValue3 );
}

BOOL CJob::GetLogDataValue4()
{
	return ( m_bLogDataValue4 );
}

BOOL CJob::GetLogDataValue5()
{
	return ( m_bLogDataValue5 );
}

void CJob::SetLogDataValue1 ( BOOL bLog )
{
	m_bLogDataValue1 = bLog;
}

void CJob::SetLogDataValue2 ( BOOL bLog )
{
	m_bLogDataValue2 = bLog;
}

void CJob::SetLogDataValue3 ( BOOL bLog )
{
	m_bLogDataValue3 = bLog;
}

void CJob::SetLogDataValue4 ( BOOL bLog )
{
	m_bLogDataValue4 = bLog;
}

void CJob::SetLogDataValue5 ( BOOL bLog )
{
	m_bLogDataValue5 = bLog;
}

BOOL CJob::GetPrintDataValue1()
{
	return ( m_bPrintDataValue1 );
}

BOOL CJob::GetPrintDataValue2()
{
	return ( m_bPrintDataValue2 );
}

BOOL CJob::GetPrintDataValue3()
{
	return ( m_bPrintDataValue3 );
}

BOOL CJob::GetPrintDataValue4()
{
	return ( m_bPrintDataValue4 );
}

BOOL CJob::GetPrintDataValue5()
{
	return ( m_bPrintDataValue5 );
}

void CJob::SetPrintDataValue1 ( BOOL bPrint )
{
	m_bPrintDataValue1 = bPrint;
}

void CJob::SetPrintDataValue2 ( BOOL bPrint )
{
	m_bPrintDataValue2 = bPrint;
}

void CJob::SetPrintDataValue3 ( BOOL bPrint )
{
	m_bPrintDataValue3 = bPrint;
}

void CJob::SetPrintDataValue4 ( BOOL bPrint )
{
	m_bPrintDataValue4 = bPrint;
}

void CJob::SetPrintDataValue5 ( BOOL bPrint )
{
	m_bPrintDataValue5 = bPrint;
}


void CJob::SetUseDataName1 ( BOOL bUse )
{
	m_bUseDataName1 = bUse;
}


void CJob::SetUseDataName2 ( BOOL bUse )
{
	m_bUseDataName2 = bUse;
}


void CJob::SetUseDataName3 ( BOOL bUse )
{
	m_bUseDataName3 = bUse;
}


void CJob::SetUseDataName4 ( BOOL bUse )
{
	m_bUseDataName4 = bUse;
}


void CJob::SetUseDataName5 ( BOOL bUse )
{
	m_bUseDataName5 = bUse;
}


BOOL CJob::GetUseDataName1()
{
	return ( m_bUseDataName1 );
}


BOOL CJob::GetUseDataName2()
{
	return ( m_bUseDataName2 );
}


BOOL CJob::GetUseDataName3()
{
	return ( m_bUseDataName3 );
}


BOOL CJob::GetUseDataName4()
{
	return ( m_bUseDataName4 );
}


BOOL CJob::GetUseDataName5()
{
	return ( m_bUseDataName5 );
}



BOOL CJob::GetTemplate(CString csTemplateName, CString *csTemplate)
{

	CSysDBase	oDatabase;

	int nCount;
	COleVariant var;
	CString csTemp = " ";

	BOOL bGoodFind;

	CDaoRecordset	*rcdTemplate;

	// Open the database.
	if (!oDatabase.Initialize())
		return FALSE;

	if ( !oDatabase.Open() )
		return ( FALSE );

	rcdTemplate = new CDaoRecordset ( &oDatabase.m_dbJobDatabase);
	rcdTemplate->Open ( AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_templates" );

	nCount = rcdTemplate->GetRecordCount();


	if ( nCount > 0 )
	{
		rcdTemplate->MoveFirst();

		bGoodFind = FALSE;

		while ( !rcdTemplate->IsEOF() && !bGoodFind )
		{
			rcdTemplate->GetFieldValue( "Template_Name", var );
			csTemp = var.pbVal;
			
			// Find the matching template name.

			if ( csTemplateName == csTemp )
			{

				// Retrieve the printer template.

				rcdTemplate->GetFieldValue ( "Template", var );
				csTemp = var.pbVal;
				*csTemplate = csTemp;

				bGoodFind = TRUE;
			}
			
			rcdTemplate->MoveNext();
		}
	}
	else
		bGoodFind = FALSE;
	
	rcdTemplate->Close();
	delete rcdTemplate;

	// Close the database.

	oDatabase.Close();

	if ( !bGoodFind )
	{
		csTemp = "Missing Template Table";
		AfxMessageBox ( csTemp );
	}

	return ( bGoodFind );





}
/*************************************************************/



CLabel::CLabel()
{

}

CLabel::~CLabel()
{

}



long CLabel::GetXCoord ()
{

	return ( m_lXCoord );

}


void CLabel::SetXCoord ( long lXCoord )
{

	m_lXCoord = lXCoord;

}



long CLabel::GetYCoord ()
{

	return ( m_lYCoord );

}


void CLabel::SetYCoord ( long lYCoord )
{

	m_lYCoord = lYCoord;

}


int CLabel::GetRotation ()
{

	return ( m_nRotation );

}


void CLabel::SetRotation ( int nRotation )
{

	m_nRotation = nRotation;

}




int CLabel::GetPrinterLocation ()
{

	return ( m_nPrinterLocation );

}


void CLabel::SetPrinterLocation ( int nLocation )
{

	m_nPrinterLocation = nLocation;

}




CString CLabel::GetTemplate ()
{

	return ( m_csTemplate );

}


void CLabel::SetTemplate ( CString csTemplate )
{

	m_csTemplate = csTemplate;

}


CString CLabel::GetPrinterName ()
{

	return ( m_csPrinterName );

}


void CLabel::SetPrinterName ( CString csPrinterName )
{

	m_csPrinterName = csPrinterName;

}




BOOL CLabel::GetEnableScan ()
{

	return ( m_bEnableScan );

}


void CLabel::SetEnableScan ( BOOL bEnable )
{

	m_bEnableScan = bEnable;

}




CString CLabel::GetTemplateName ()
{

	return ( m_csTemplateName );

}


void CLabel::SetTemplateName ( CString csTemplateName )
{

	m_csTemplateName = csTemplateName;

}


