// Database.cpp: implementation of the CDatabase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Database.h"
#include "resource.h"
#include <trace.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDatabase::CDatabase()
{

}

CDatabase::~CDatabase()
{

}





/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetJobNames
//
//	Description:
//		Get name of each from the database.
//
//	Arguments:
//		Pointer to a list of job and printer location.
//
//	Return:
//		Status.
//
//	Called by:
//		CPACSDlg::SetupMainForm
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::GetJobNames ( CStringArray * csJobArray )
{

	int nCount;
	COleVariant var;
	
//	Initialize variables
	
	CString csTemp = "NULL";
	CString csDesc = "NULL";

	nCount=0;


	CDaoRecordset	*rcdJob;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdJob = new CDaoRecordset ( &m_dbJobDatabase );
	rcdJob->Open ( AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_job" );

	nCount = rcdJob->GetRecordCount();

	if ( nCount > 0 )
	{

		csJobArray->RemoveAll();

		// Retrieve all job file names and descriptions.

		rcdJob->MoveFirst();

		while ( !rcdJob->IsEOF() )
		{
			rcdJob->GetFieldValue ( "Job_Name", var );
			csTemp = var.pbVal;
			
			rcdJob->GetFieldValue ( "Description", var );
			csDesc = var.pbVal;

			csJobArray->Add ( csTemp + "\t" + csDesc );
			
			rcdJob->MoveNext();
		}
	}
	
	rcdJob->Close();

	if (rcdJob)
		delete rcdJob;

	// Close the database.

	Close();

	return ( TRUE );
	
}





/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetJobAttributes
//
//	Description:
//		Get job information from the database.
//
//	Arguments:
//		Job file name.
//		Pointer to job information.
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::GetJobAttributes ( CString csJobName, CJob * oJobInfo )
{
	int nCount, nTemp;
	COleVariant var;
	CString csTemp = " ";
	CString csDesc = " ";

	CDaoRecordset	*rcdJob;


	// Open the database.
	if ( !Open() )
		return ( FALSE );

	rcdJob = new CDaoRecordset ( &m_dbJobDatabase );
	rcdJob->Open ( AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_job" );

	nCount = rcdJob->GetRecordCount();

	if ( nCount < 1 )
	{

		AfxMessageBox ("There is no job information in the database. ");
		rcdJob->Close();
		if (rcdJob)
			delete rcdJob;
		Close();
		return ( FALSE );
	}


	if ( nCount > 0 )
	{
		rcdJob->MoveFirst();

		while ( !rcdJob->IsEOF() )
		{
			rcdJob->GetFieldValue( "Job_Name", var );
			csTemp = var.pbVal;
			if ( csJobName == csTemp  )
			{
				oJobInfo->SetJobName ( csTemp );

				rcdJob->GetFieldValue ( "Description", var );
				csTemp = var.pbVal;
				oJobInfo->SetDescription ( csTemp );
				rcdJob->GetFieldValue ( "Customer", var );
				csTemp = var.pbVal;
				oJobInfo->SetCustomer ( csTemp );

				rcdJob->GetFieldValue ( "Use_Data_Name1", var );
				csTemp = var.pbVal;
				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					oJobInfo->SetUseDataName1 ( TRUE );
				else
					oJobInfo->SetUseDataName1 ( FALSE );

				rcdJob->GetFieldValue ( "Use_Data_Name2", var );
				csTemp = var.pbVal;
				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					oJobInfo->SetUseDataName2 ( TRUE );
				else
					oJobInfo->SetUseDataName2 ( FALSE );
	
				rcdJob->GetFieldValue ( "Use_Data_Name3", var );
				csTemp = var.pbVal;
				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					oJobInfo->SetUseDataName3 ( TRUE );
				else
					oJobInfo->SetUseDataName3 ( FALSE );
				
				rcdJob->GetFieldValue ( "Use_Data_Name4", var );
				csTemp = var.pbVal;
				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					oJobInfo->SetUseDataName4 ( TRUE );
				else
					oJobInfo->SetUseDataName4 ( FALSE );

				rcdJob->GetFieldValue ( "Use_Data_Name5", var );
				csTemp = var.pbVal;
				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					oJobInfo->SetUseDataName5 ( TRUE );
				else
					oJobInfo->SetUseDataName5 ( FALSE );

				rcdJob->GetFieldValue ( "Data_Name1", var );
				csTemp = var.pbVal;
				oJobInfo->SetDataName1 ( csTemp );

				rcdJob->GetFieldValue ( "Data_Name2", var );
				csTemp = var.pbVal;
				oJobInfo->SetDataName2 ( csTemp );
	
				rcdJob->GetFieldValue ( "Data_Name3", var );
				csTemp = var.pbVal;
				oJobInfo->SetDataName3 ( csTemp );
				
				rcdJob->GetFieldValue ( "Data_Name4", var );
				csTemp = var.pbVal;
				oJobInfo->SetDataName4 ( csTemp );

				rcdJob->GetFieldValue ( "Data_Name5", var );
				csTemp = var.pbVal;
				oJobInfo->SetDataName5 ( csTemp );

				rcdJob->GetFieldValue ( "Data_Value1", var );
				csTemp = var.pbVal;
				oJobInfo->SetDataValue1 ( csTemp );

				rcdJob->GetFieldValue ( "Data_Value2", var );
				csTemp = var.pbVal;
				oJobInfo->SetDataValue2 ( csTemp );
	
				rcdJob->GetFieldValue ( "Data_Value3", var );
				csTemp = var.pbVal;
				oJobInfo->SetDataValue3 ( csTemp );
				
				rcdJob->GetFieldValue ( "Data_Value4", var );
				csTemp = var.pbVal;
				oJobInfo->SetDataValue4 ( csTemp );

				rcdJob->GetFieldValue ( "Data_Value5", var );
				csTemp = var.pbVal;
				oJobInfo->SetDataValue5 ( csTemp );

				rcdJob->GetFieldValue ( "Log_Data_Value1", var );
				csTemp = var.pbVal;
				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					oJobInfo->SetLogDataValue1 ( TRUE );
				else
					oJobInfo->SetLogDataValue1 ( FALSE );

				rcdJob->GetFieldValue ( "Log_Data_Value2", var );
				csTemp = var.pbVal;
				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					oJobInfo->SetLogDataValue2 ( TRUE );
				else
					oJobInfo->SetLogDataValue2 ( FALSE );
	
				rcdJob->GetFieldValue ( "Log_Data_Value3", var );
				csTemp = var.pbVal;
				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					oJobInfo->SetLogDataValue3 ( TRUE );
				else
					oJobInfo->SetLogDataValue3 ( FALSE );
				
				rcdJob->GetFieldValue ( "Log_Data_Value4", var );
				csTemp = var.pbVal;
				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					oJobInfo->SetLogDataValue4 ( TRUE );
				else
					oJobInfo->SetLogDataValue4 ( FALSE );

				rcdJob->GetFieldValue ( "Log_Data_Value5", var );
				csTemp = var.pbVal;
				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					oJobInfo->SetLogDataValue5 ( TRUE );
				else
					oJobInfo->SetLogDataValue5 ( FALSE );

				rcdJob->GetFieldValue ( "Print_Data_Value1", var );
				csTemp = var.pbVal;
				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					oJobInfo->SetPrintDataValue1 ( TRUE );
				else
					oJobInfo->SetPrintDataValue1 ( FALSE );

				rcdJob->GetFieldValue ( "Print_Data_Value2", var );
				csTemp = var.pbVal;
				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					oJobInfo->SetPrintDataValue2 ( TRUE );
				else
					oJobInfo->SetPrintDataValue2 ( FALSE );

				rcdJob->GetFieldValue ( "Print_Data_Value3", var );
				csTemp = var.pbVal;
				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					oJobInfo->SetPrintDataValue3 ( TRUE );
				else
					oJobInfo->SetPrintDataValue3 ( FALSE );

				rcdJob->GetFieldValue ( "Print_Data_Value4", var );
				csTemp = var.pbVal;
				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					oJobInfo->SetPrintDataValue4 ( TRUE );
				else
					oJobInfo->SetPrintDataValue4 ( FALSE );

				rcdJob->GetFieldValue ( "Print_Data_Value5", var );
				csTemp = var.pbVal;
				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					oJobInfo->SetPrintDataValue5 ( TRUE );
				else
					oJobInfo->SetPrintDataValue5 ( FALSE );

				rcdJob->GetFieldValue ( "XOffset", var );
				csTemp = var.pbVal;
				nTemp = atoi((LPCSTR)csTemp);
				oJobInfo->SetXOffset ( nTemp );
				
				rcdJob->GetFieldValue ( "YOffset", var );
				csTemp = var.pbVal;
				nTemp = atoi((LPCSTR)csTemp);
				oJobInfo->SetYOffset ( nTemp );

				rcdJob->GetFieldValue ( "LabelStockXOffset", var );
				csTemp = var.pbVal;
				nTemp = atoi((LPCSTR)csTemp);
				oJobInfo->SetLabelStockXOffset ( nTemp );

				rcdJob->GetFieldValue ( "LabelStockYOffset", var );
				csTemp = var.pbVal;
				nTemp = atoi((LPCSTR)csTemp);
				oJobInfo->SetLabelStockYOffset ( nTemp );

				rcdJob->GetFieldValue ("Job_TwoUp",var);
				csTemp = var.pbVal;
				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					oJobInfo->SetJob2up(TRUE);
				else
					oJobInfo->SetJob2up(FALSE);
				
				rcdJob->GetFieldValue ( "Use_WYSIWYG", var );
				csTemp = var.pbVal;
				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					oJobInfo->SetUseWYSIWYG ( TRUE );
				else
					oJobInfo->SetUseWYSIWYG ( FALSE );

				rcdJob->GetFieldValue ( "Placement_Attributes", var );
				csTemp = var.pbVal;
				oJobInfo->SetPlacementAttributes ( csTemp );

				rcdJob->GetFieldValue ( "Panel_Dim", var );
				csTemp = var.pbVal;
				oJobInfo->SetPanelDimension ( csTemp );

				break;

			}
			
			rcdJob->MoveNext();
		}
	}
	
	rcdJob->Close();
	if (rcdJob)
		delete rcdJob;

	// Close the database.
	Close();

	return ( TRUE );
}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetJobAttributes
//
//	Description:
//		Update the database with new job attributes.
//
//	Arguments:
//		Pointer to job information.
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::SetJobAttributes ( CJob * oJobInfo )
{

	int				nCount,nTemp;
	char			cTemp[100];
	COleVariant		var;
	CString			csTemp = " ";
	BOOL			bJobRecordExists,
					blnUpdateStatus;
	CString			csJobName;
	char			*p_chr_temp;
	CDaoRecordset	*rcdJob;
	double			dTemp;


	if (!VerifyJobAttributes( oJobInfo))
	{
		return FALSE;
	}
	
	
	
	// cache the job name
	csJobName = oJobInfo->GetJobName();

	// Open the database and recordset

	if ( !Open() )
		return ( FALSE );
	rcdJob = new CDaoRecordset ( &m_dbJobDatabase );
	rcdJob->Open ( AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_job" );

	// start assuming record doesn't exist
	bJobRecordExists = FALSE;
	blnUpdateStatus = TRUE;

	// get the number of records
	nCount = rcdJob->GetRecordCount();
	if ( nCount > 0 )
	{
		// move to the first record
		rcdJob->MoveFirst();

		// step through the records looking for the job
		while ( !rcdJob->IsEOF() && !bJobRecordExists )
		{
			// get the job name of the current record
			rcdJob->GetFieldValue( "Job_Name", var );
			csTemp = var.pbVal;
			
			// we found the job
			if ( csJobName == csTemp  )
			{
				rcdJob->Edit();

				// update the description field
				csTemp = oJobInfo->GetDescription();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Description", p_chr_temp );

				// update the customer field
				csTemp = oJobInfo->GetCustomer();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Customer", p_chr_temp );

				// Update the five customer specified fields.

				if ( oJobInfo->GetUseDataName1() )
					csTemp = "YES";
				else
					csTemp = "NO";
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Use_Data_Name1", p_chr_temp );

				if ( oJobInfo->GetUseDataName2() )
					csTemp = "YES";
				else
					csTemp = "NO";
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Use_Data_Name2", p_chr_temp );

				if ( oJobInfo->GetUseDataName3() )
					csTemp = "YES";
				else
					csTemp = "NO";
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Use_Data_Name3", p_chr_temp );

				if ( oJobInfo->GetUseDataName4() )
					csTemp = "YES";
				else
					csTemp = "NO";
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Use_Data_Name4", p_chr_temp );

				if ( oJobInfo->GetUseDataName5() )
					csTemp = "YES";
				else
					csTemp = "NO";
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Use_Data_Name5", p_chr_temp );

				csTemp = oJobInfo->GetDataName1();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Data_Name1", p_chr_temp );

				csTemp = oJobInfo->GetDataName2();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Data_Name2", p_chr_temp );

				csTemp = oJobInfo->GetDataName3();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Data_Name3", p_chr_temp );

				csTemp = oJobInfo->GetDataName4();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Data_Name4", p_chr_temp );

				csTemp = oJobInfo->GetDataName5();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Data_Name5", p_chr_temp );

				csTemp = oJobInfo->GetDataValue1();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Data_Value1", p_chr_temp );

				csTemp = oJobInfo->GetDataValue2();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Data_Value2", p_chr_temp );

				csTemp = oJobInfo->GetDataValue3();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Data_Value3", p_chr_temp );

				csTemp = oJobInfo->GetDataValue4();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Data_Value4", p_chr_temp );

				csTemp = oJobInfo->GetDataValue5();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Data_Value5", p_chr_temp );

				if ( oJobInfo->GetLogDataValue1() )
					csTemp = "YES";
				else
					csTemp = "NO";
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Log_Data_Value1", p_chr_temp );

				if ( oJobInfo->GetLogDataValue2() )
					csTemp = "YES";
				else
					csTemp = "NO";
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Log_Data_Value2", p_chr_temp );

				if ( oJobInfo->GetLogDataValue3() )
					csTemp = "YES";
				else
					csTemp = "NO";
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Log_Data_Value3", p_chr_temp );

				if ( oJobInfo->GetLogDataValue4() )
					csTemp = "YES";
				else
					csTemp = "NO";
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Log_Data_Value4", p_chr_temp );

				if ( oJobInfo->GetLogDataValue5() )
					csTemp = "YES";
				else
					csTemp = "NO";
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Log_Data_Value5", p_chr_temp );

				if ( oJobInfo->GetPrintDataValue1() )
					csTemp = "YES";
				else
					csTemp = "NO";
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Print_Data_Value1", p_chr_temp );

				if ( oJobInfo->GetPrintDataValue2() )
					csTemp = "YES";
				else
					csTemp = "NO";
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Print_Data_Value2", p_chr_temp );

				if ( oJobInfo->GetPrintDataValue3() )
					csTemp = "YES";
				else
					csTemp = "NO";
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Print_Data_Value3", p_chr_temp );

				if ( oJobInfo->GetPrintDataValue4() )
					csTemp = "YES";
				else
					csTemp = "NO";
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Print_Data_Value4", p_chr_temp );

				if ( oJobInfo->GetPrintDataValue5() )
					csTemp = "YES";
				else
					csTemp = "NO";
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Print_Data_Value5", p_chr_temp );


				// update the XOffset
				dTemp = oJobInfo->GetXOffset();
				csTemp.Format("%.2f",dTemp);
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "XOffset", p_chr_temp );

				// update the YOffset
				dTemp = oJobInfo->GetYOffset();
				csTemp.Format("%.2f",dTemp);
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "YOffset", p_chr_temp );

				// update the LabelStockXOffset
				nTemp = oJobInfo->GetLabelStockXOffset();
				_itoa(nTemp,cTemp,10);
				csTemp = cTemp;
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "LabelStockXOffset", p_chr_temp );

				// update the LabelStockYOffset
				nTemp = oJobInfo->GetLabelStockYOffset();
				_itoa(nTemp,cTemp,10);
				csTemp = cTemp;
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "LabelStockYOffset", p_chr_temp );

				// update the Job_TwoUp field
				if ( oJobInfo->GetJob2up() )
					csTemp = "YES";
				else
					csTemp = "NO";
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Job_TwoUp", p_chr_temp );

				// update the use WYSIWYG field
				if ( oJobInfo->GetUseWYSIWYG() )
					csTemp = "YES";
				else
					csTemp = "NO";
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Use_WYSIWYG", p_chr_temp );

				// update the placement attributes field
				csTemp = oJobInfo->GetPlacementAttributes();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Placement_Attributes", p_chr_temp );

				// update the panel dimension field
				csTemp = oJobInfo->GetPanelDimension();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdJob->SetFieldValue ( "Panel_Dim", p_chr_temp );

				
				rcdJob->Update();

				// we found the record
				bJobRecordExists = TRUE;
			}
			
			// we didn't find the record, try the next one
			rcdJob->MoveNext();
		} // end while
	} // end if

	// if the job doesn't exist create it
	if ( !bJobRecordExists )
	{
		// No record for this job. Add it to the database.
		rcdJob->AddNew();
		
		csTemp = csJobName;
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Job_Name", p_chr_temp );
		csTemp.ReleaseBuffer();


		csTemp = oJobInfo->GetDescription();
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Description", p_chr_temp );
		csTemp.ReleaseBuffer();

		csTemp = oJobInfo->GetCustomer();
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Customer", p_chr_temp );
		csTemp.ReleaseBuffer();

		if ( oJobInfo->GetUseDataName1() )
			csTemp = "YES";
		else
			csTemp = "NO";
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Use_Data_Name1", p_chr_temp );
		csTemp.ReleaseBuffer();


		if ( oJobInfo->GetUseDataName2() )
			csTemp = "YES";
		else
			csTemp = "NO";
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Use_Data_Name2", p_chr_temp );
		csTemp.ReleaseBuffer();

		if ( oJobInfo->GetUseDataName3() )
			csTemp = "YES";
		else
			csTemp = "NO";
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Use_Data_Name3", p_chr_temp );
		csTemp.ReleaseBuffer();

		if ( oJobInfo->GetUseDataName4() )
			csTemp = "YES";
		else
			csTemp = "NO";
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Use_Data_Name4", p_chr_temp );
		csTemp.ReleaseBuffer();

		if ( oJobInfo->GetUseDataName5() )
			csTemp = "YES";
		else
			csTemp = "NO";
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Use_Data_Name5", p_chr_temp );
		csTemp.ReleaseBuffer();

		csTemp = oJobInfo->GetDataName1();
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Data_Name1", p_chr_temp );
		csTemp.ReleaseBuffer();

		csTemp = oJobInfo->GetDataName2();
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Data_Name2", p_chr_temp );
		csTemp.ReleaseBuffer();

		csTemp = oJobInfo->GetDataName3();
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Data_Name3", p_chr_temp );
		csTemp.ReleaseBuffer();

		csTemp = oJobInfo->GetDataName4();
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Data_Name4", p_chr_temp );
		csTemp.ReleaseBuffer();

		csTemp = oJobInfo->GetDataName5();
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Data_Name5", p_chr_temp );
		csTemp.ReleaseBuffer();

		csTemp = oJobInfo->GetDataValue1();
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Data_Value1", p_chr_temp );
		csTemp.ReleaseBuffer();

		csTemp = oJobInfo->GetDataValue2();
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Data_Value2", p_chr_temp );
		csTemp.ReleaseBuffer();

		csTemp = oJobInfo->GetDataValue3();
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Data_Value3", p_chr_temp );
		csTemp.ReleaseBuffer();

		csTemp = oJobInfo->GetDataValue4();
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Data_Value4", p_chr_temp );
		csTemp.ReleaseBuffer();

		csTemp = oJobInfo->GetDataValue5();
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Data_Value5", p_chr_temp );
		csTemp.ReleaseBuffer();


		if ( oJobInfo->GetLogDataValue1() )
			csTemp = "YES";
		else
			csTemp = "NO";
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Log_Data_Value1", p_chr_temp );
		csTemp.ReleaseBuffer();

		if ( oJobInfo->GetLogDataValue2() )
			csTemp = "YES";
		else
			csTemp = "NO";
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Log_Data_Value2", p_chr_temp );
		csTemp.ReleaseBuffer();

		if ( oJobInfo->GetLogDataValue3() )
			csTemp = "YES";
		else
			csTemp = "NO";
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Log_Data_Value3", p_chr_temp );
		csTemp.ReleaseBuffer();

		if ( oJobInfo->GetLogDataValue4() )
			csTemp = "YES";
		else
			csTemp = "NO";
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Log_Data_Value4", p_chr_temp );
		csTemp.ReleaseBuffer();

		if ( oJobInfo->GetLogDataValue5() )
			csTemp = "YES";
		else
			csTemp = "NO";
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Log_Data_Value5", p_chr_temp );
		csTemp.ReleaseBuffer();

		if ( oJobInfo->GetPrintDataValue1() )
			csTemp = "YES";
		else
			csTemp = "NO";
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Print_Data_Value1", p_chr_temp );
		csTemp.ReleaseBuffer();

		if ( oJobInfo->GetPrintDataValue2() )
			csTemp = "YES";
		else
			csTemp = "NO";
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Print_Data_Value2", p_chr_temp );
		csTemp.ReleaseBuffer();

		if ( oJobInfo->GetPrintDataValue3() )
			csTemp = "YES";
		else
			csTemp = "NO";
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Print_Data_Value3", p_chr_temp );
		csTemp.ReleaseBuffer();

		if ( oJobInfo->GetPrintDataValue4() )
			csTemp = "YES";
		else
			csTemp = "NO";
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Print_Data_Value4", p_chr_temp );
		csTemp.ReleaseBuffer();

		if ( oJobInfo->GetPrintDataValue5() )
			csTemp = "YES";
		else
			csTemp = "NO";
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Print_Data_Value5", p_chr_temp );
		csTemp.ReleaseBuffer();

		dTemp = oJobInfo->GetXOffset();
		csTemp.Format("%.2f",dTemp);
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "XOffset", p_chr_temp );
		csTemp.ReleaseBuffer();

		dTemp = oJobInfo->GetYOffset();
		csTemp.Format("%.2f",dTemp);
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "YOffset", p_chr_temp );
		csTemp.ReleaseBuffer();

		nTemp = oJobInfo->GetLabelStockXOffset();
		_itoa(nTemp,cTemp,10);
		csTemp = cTemp;
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "LabelStockXOffset", p_chr_temp );
		csTemp.ReleaseBuffer();

		nTemp = oJobInfo->GetLabelStockYOffset();
		_itoa(nTemp,cTemp,10);
		csTemp = cTemp;
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "LabelStockYOffset", p_chr_temp );
		csTemp.ReleaseBuffer();

		if ( oJobInfo->GetJob2up() )
			csTemp = "YES";
		else
			csTemp = "NO";
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Job_TwoUp", p_chr_temp );
		csTemp.ReleaseBuffer();


		if ( oJobInfo->GetUseWYSIWYG() )
			csTemp = "YES";
		else
			csTemp = "NO";
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Use_WYSIWYG", p_chr_temp );
		csTemp.ReleaseBuffer();


		csTemp = oJobInfo->GetPlacementAttributes();
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdJob->SetFieldValue ( "Placement_Attributes", p_chr_temp );
		csTemp.ReleaseBuffer();


		csTemp = oJobInfo->GetPanelDimension();
		
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );

		rcdJob->SetFieldValue ( "Panel_Dim", p_chr_temp );
		csTemp.ReleaseBuffer();



		rcdJob->Update();

	}

	// close recordset and delete object
	rcdJob->Close();
	if (rcdJob)
		delete rcdJob;

	// Close the database.
	Close();


	return blnUpdateStatus;
}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetGeneralAttributes
//
//	Description:
//		Get general information from the database.
//
//	Arguments:
//		Pointer to Auto-rescans,
//		Pointer to Auto-repicks.
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::GetGeneralAttributes ( int *nRescans, int *nRepicks, BOOL *b2up, int *nNumberOfNosepieces )
{

	int nCount;
	BOOL bGoodFind;

	COleVariant var;
	CString csTemp = " ";
	CString csDesc = " ";
	bGoodFind=FALSE;

	CDaoRecordset	*rcdGeneral;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdGeneral = new CDaoRecordset( &m_dbJobDatabase);
	
	csTemp = "Select * from tbl_general"; 

	rcdGeneral->Open(AFX_DAO_USE_DEFAULT_TYPE, csTemp);

	nCount = rcdGeneral->GetRecordCount();

	if ( nCount > 0 ) 
	{
		rcdGeneral->MoveFirst();

		rcdGeneral->GetFieldValue ( "Auto_Rescans", var );
		csTemp = var.pbVal;
		*nRescans =  atoi(csTemp);
		if ((*nRescans)==0)
			(*nRescans)++;

		rcdGeneral->GetFieldValue ( "Auto_Repicks", var );
		csTemp = var.pbVal;
		*nRepicks =  atoi(csTemp);
		if ((*nRepicks)==0)
			(*nRepicks)++;

		rcdGeneral->GetFieldValue("Print2Up",var);
		csTemp = var.pbVal;
		if (csTemp.CompareNoCase ("YES") == 0)
			*b2up = TRUE;
		else
			*b2up = FALSE;

		rcdGeneral->GetFieldValue("NosepieceCount",var);
		csTemp = var.pbVal;
		*nNumberOfNosepieces = atoi(csTemp);

		bGoodFind = TRUE;
	}
	else
	{
		csTemp.LoadString ( IDS_NO_GENERAL_RECORDS );
		AfxMessageBox ( csTemp );
		bGoodFind = FALSE;
	}

	rcdGeneral->Close();

	if (rcdGeneral)			// do not free a NULL pointer
		delete rcdGeneral;

	Close();

	return ( bGoodFind );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetGeneralAttributes
//
//	Description:
//		Set the general information.
//
//	Arguments:
//		Number of rescans.
//		Number of repicks.
//
//	Return:
//		Status.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::SetGeneralAttributes ( int nRescans, int nRepicks, BOOL b2up, int nNumberOfNosepieces )
{

	int nCount;
	COleVariant var;
	CString csTemp = " ";

	BOOL bGoodFind;

	char *p_chr_temp;

	CDaoRecordset	*rcdGeneral;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdGeneral = new CDaoRecordset( &m_dbJobDatabase );
	
	csTemp = "Select * from tbl_general"; 

	rcdGeneral->Open(AFX_DAO_USE_DEFAULT_TYPE, csTemp);

	nCount = rcdGeneral->GetRecordCount();

	if ( nCount > 0 ) 
	{
		rcdGeneral->MoveFirst();

		csTemp.Format ( "%d", nRescans );
		rcdGeneral->Edit();
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdGeneral->SetFieldValue ( "Auto_Rescans", p_chr_temp );
		rcdGeneral->Update();

		csTemp.Format ( "%d", nRepicks );
		rcdGeneral->Edit();
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdGeneral->SetFieldValue ( "Auto_Repicks", p_chr_temp );
		rcdGeneral->Update();

		if (b2up)
			csTemp = "YES";
		else
			csTemp = "NO";
		rcdGeneral->Edit();
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdGeneral->SetFieldValue ( "Print2Up", p_chr_temp );
		rcdGeneral->Update();

		csTemp.Format ( "%d", nNumberOfNosepieces );
		rcdGeneral->Edit();
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdGeneral->SetFieldValue ( "NosepieceCount", p_chr_temp );
		rcdGeneral->Update();

		bGoodFind = TRUE;
	}
	else
	{
		csTemp.LoadString ( IDS_NO_GENERAL_RECORDS );
		AfxMessageBox ( csTemp );
		bGoodFind = FALSE;
	}

	rcdGeneral->Close();

	if (rcdGeneral)			// do not free a NULL pointer
		delete rcdGeneral;

	// Close the database.

	Close();

	if (p_chr_temp)
		delete p_chr_temp;
	return ( bGoodFind );

}






/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetScannerAttributes
//
//	Description:
//		Get the attributes of the scanner type.
//
//	Arguments:
//		Scanner system type.
//		Pointer to use flag.
//		Pointer to enable flag.
//		Pointer to scanner equipment type.
//		Pointer to trigger character.
//		Pointer to reset string.
//
//	Return:
//		Status.
//
//	Called by:
//		CSetupDlg::OnClickCmdScannerSetup
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::GetScannerAttributes ( CString csName, 
												   BOOL *pbUse, 
													BOOL *pbEnable, 
													int *pnType, 
													CString *pcsTrigger,
													CString *pcsTriggerOff,
													CString *pcsReset )
{

	int nCount=0;
	COleVariant var;
	CString csTemp = " ";
	BOOL bFound=FALSE;
	BOOL bGoodFind=FALSE;

	CDaoRecordset	*rcdScanner;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdScanner = new CDaoRecordset ( &m_dbJobDatabase );
	rcdScanner->Open ( AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_scanner" );

	nCount = rcdScanner->GetRecordCount();

	if ( nCount > 0 )
	{

		rcdScanner->MoveFirst();

		bFound = FALSE;
		while ( !rcdScanner->IsEOF() && !bFound )
		{
			rcdScanner->GetFieldValue ( "Scanner_Name", var );
			csTemp = var.pbVal;
			
			if ( csTemp.CompareNoCase ( csName ) == 0 )
				bFound = TRUE;

			if ( !bFound )
				rcdScanner->MoveNext();
		}

		if ( bFound )
		{

			bGoodFind = TRUE;

			// Get the rest of the record.

			rcdScanner->GetFieldValue ( "Use", var );
			csTemp = var.pbVal;
			if ( csTemp.CompareNoCase ( "YES" ) == 0 )
				*pbUse = TRUE;
			else
				*pbUse = FALSE;
			
			rcdScanner->GetFieldValue ( "Enable", var );
			csTemp = var.pbVal;
			if ( csTemp.CompareNoCase ( "YES" ) == 0 )
				*pbEnable = TRUE;
			else
				*pbEnable = FALSE;

			rcdScanner->GetFieldValue ( "Trigger", var );
			csTemp = var.pbVal;
			*pcsTrigger = csTemp;

			rcdScanner->GetFieldValue ( "TriggerOff", var );
			csTemp = var.pbVal;
			*pcsTriggerOff = csTemp;

			rcdScanner->GetFieldValue ( "Reset_String", var );
			csTemp = var.pbVal;
			*pcsReset = csTemp;

			rcdScanner->GetFieldValue ( "Type", var );
			csTemp = var.pbVal;
			if ( csTemp.CompareNoCase ( "Microscan VS310" ) == 0 )
				*pnType = MICROSCAN_VS310;
			else
			{
				if ( csTemp.CompareNoCase ( "Microscan VS710" ) == 0 )
					*pnType = MICROSCAN_VS710;
				else if ( csTemp.CompareNoCase ( "Welch Allyn 3900" ) == 0 )
					*pnType = WELCHALLYN_3900;

				else if ( csTemp.CompareNoCase ( "Welch Allyn 4700" ) == 0 )
					*pnType = WELCHALLYN_4700;
				else
				{
					if ( csTemp.CompareNoCase ( "Metanetics IR-2000HD" ) == 0 )
						*pnType = METANETICS_IR2000HD;
					else
					{
						csTemp.LoadString ( IDS_UNSUPPORTED_SCANNER );
						AfxMessageBox ( csTemp );
						bGoodFind = FALSE;
					}
				}
			}

		}
		else
		{
			bGoodFind = FALSE;
		}

	}
	else
		bGoodFind = FALSE;
	
	rcdScanner->Close();

	if (rcdScanner)			// do not free a NULL pointer
		delete rcdScanner;

	// Close the database.

	Close();

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_NO_SCANNING_RECORDS );
		AfxMessageBox ( csTemp );
	}

	return ( bGoodFind );
	
}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetScannerAttributes
//
//	Description:
//		Set the attributes of the scanner type.
//
//	Arguments:
//		Scanner name.
//		Use flag.
//		Enable flag.
//		Scanner equipment type.
//		Trigger character.
//		Reset string.
//
//	Return:
//		Status.
//
//	Called by:
//		CSetupDlg::OnClickCmdScannerSetup
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::SetScannerAttributes ( CString csName, 
												   BOOL bUse, 
													BOOL bEnable, 
													int nType, 
													CString csTrigger,
													CString csTriggerOff,
													CString csReset )
{

	char *p_chr_temp;

	int nCount;
	COleVariant var;
	CString csTemp = " ";
	BOOL bFound;
	BOOL bGoodFind;

	CDaoRecordset	*rcdScanner;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdScanner = new CDaoRecordset ( &m_dbJobDatabase );
	rcdScanner->Open ( AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_scanner" );

	nCount = rcdScanner->GetRecordCount();

	if ( nCount > 0 )
	{

		// Retrieve all job file names and descriptions.

		rcdScanner->MoveFirst();

		bFound = FALSE;
		while ( !rcdScanner->IsEOF() && !bFound )
		{
			rcdScanner->GetFieldValue ( "Scanner_Name", var );
			csTemp = var.pbVal;
			
			if ( csTemp.CompareNoCase ( csName ) == 0 )
				bFound = TRUE;

			if ( !bFound )
				rcdScanner->MoveNext();
		}

		if ( bFound )
		{

			bGoodFind = TRUE;

			// Set the rest of the record.

			if ( bUse )
				csTemp = "YES";
			else
				csTemp = "NO";

			p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
			rcdScanner->Edit();
			rcdScanner->SetFieldValue ( "Use", p_chr_temp );
			rcdScanner->Update();
			csTemp.ReleaseBuffer();

			if ( bEnable )
				csTemp = "YES";
			else
				csTemp = "NO";

			p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
			rcdScanner->Edit();
			rcdScanner->SetFieldValue ( "Enable", p_chr_temp );
			rcdScanner->Update();
			csTemp.ReleaseBuffer();
	
			csTemp = csTrigger; 

			p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
			rcdScanner->Edit();
			rcdScanner->SetFieldValue ( "Trigger", p_chr_temp );
			rcdScanner->Update();
			csTemp.ReleaseBuffer();
			

			csTemp = csTriggerOff; 

			p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
			rcdScanner->Edit();
			rcdScanner->SetFieldValue ( "TriggerOff", p_chr_temp );
			rcdScanner->Update();
			csTemp.ReleaseBuffer();
			
			
			csTemp = csReset;

			p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
			rcdScanner->Edit();
			rcdScanner->SetFieldValue ( "Reset_String", p_chr_temp );
			rcdScanner->Update();
			csTemp.ReleaseBuffer();

			switch ( nType )
			{
				
				case MICROSCAN_VS310:
					csTemp = "Microscan VS310";
					break;

				case MICROSCAN_VS710:
					csTemp = "Microscan VS710";
					break;

				case METANETICS_IR2000HD:
					csTemp = "Metanetics IR-2000HD";
					break;

				case WELCHALLYN_4700:
					csTemp = "Welch Allyn 4700";
					break;

				case WELCHALLYN_3900:
					csTemp = "Welch Allyn 3900";
					break;

				default:
					bGoodFind = FALSE;
					break;
			}
			
			if ( bGoodFind )
			{
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdScanner->Edit();
				rcdScanner->SetFieldValue ( "Type", p_chr_temp );
				rcdScanner->Update();
				csTemp.ReleaseBuffer();
			}
			else
			{
				csTemp.LoadString ( IDS_UNSUPPORTED_SCANNER );
				AfxMessageBox ( csTemp );
				bGoodFind = FALSE;
			}

		}
		else
		{
			bGoodFind = FALSE;
		}

	}
	else
		bGoodFind = FALSE;
	
	rcdScanner->Close();
	if (rcdScanner)			// do not free a NULL pointer
		delete rcdScanner;

	// Close the database.

	Close();

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_NO_SCANNING_RECORDS );
		AfxMessageBox ( csTemp );
	}

	return ( bGoodFind );
	
}





/*

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetDBApplicatorPoints
//
//	Description:
//		Get the applicator points from the database.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//		CApplicatorControl::Initialize
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::GetDBApplicatorPoints ( void )
{

	int nCount;
	COleVariant var;
	BOOL bGoodFind;

	CDaoRecordset	*rcdPoints;

	CString 
		csTemp,
		csPoint,
		csXPos,
		csYPos,
		csRot;

	// Open the database.
	if ( !Open() )
		return ( FALSE );

	TRY
	{
		rcdPoints = new CDaoRecordset( &m_dbJobDatabase );
		rcdPoints->Open ( AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_point" );
	} 
	CATCH_ALL(e)
	{
		csTemp.LoadString ( IDS_NO_POINT_TABLE );
		AfxMessageBox ( csTemp );
		m_bInitialized = FALSE;
		return ( FALSE );
	}
	END_CATCH_ALL


	nCount = rcdPoints->GetRecordCount();

	if ( nCount > 0 )
	{

		// Get all applicator points from the database. NOTE: Nosepiece 2 may
		// not be used by the customers requirements but we keep it arround
		// to minimize changes needed from customer to customer.

		rcdPoints->MoveFirst();

		while ( !rcdPoints->IsEOF() )
		{
			rcdPoints->GetFieldValue ( "Point_Name", var );
			csPoint = var.pbVal;
			rcdPoints->GetFieldValue ( "X", var );
			csXPos = var.pbVal;
			rcdPoints->GetFieldValue ( "Y", var  );
			csYPos = var.pbVal;
			rcdPoints->GetFieldValue ( "Rotation", var );
			csRot = var.pbVal;
			
			// both X and Y values should be in 6 bytes based on IAI format.
			// this should not happen. 

			if ( ( csXPos.GetLength() < 6 ) || ( csYPos.GetLength() < 6 ) )
			{
				csTemp.LoadString ( IDS_INVALID_POSITION );
				AfxMessageBox ( csTemp );
				rcdPoints->Close();
				if (rcdPoints)			// do not free a NULL pointer
					delete rcdPoints;
				Close();
				return ( FALSE );
			}
			
			// Origin and park position are
			// the same for both 1up and 2up
			if ( csPoint == c_csOriginPos )
			{
				m_csOriginX   = csXPos;
				m_csOriginY   = csYPos;
				m_csOriginRot = csRot;
			}
			if ( csPoint == c_csParkPos )
			{
				m_csParkX   = csXPos;
				m_csParkY   = csYPos;
				m_csParkRot = csRot;
			}
			if (csPoint==c_csNosePiece1ScanOffset0)
			{
				m_csNP1ScanOffset0X   = csXPos;
				m_csNP1ScanOffset0Y   = csYPos;
				m_csNP1ScanOffset0Rot = csRot;
			}
			if (csPoint==c_csNosePiece1ScanOffset90)
			{
				m_csNP1ScanOffset90X   = csXPos;
				m_csNP1ScanOffset90Y   = csYPos;
				m_csNP1ScanOffset90Rot = csRot;
			}
			if (csPoint == c_csNosePiece1Offset0)
			{
				m_csNP1Offset0X   = csXPos;
				m_csNP1Offset0Y   = csYPos;
				m_csNP1Offset0Rot = csRot;
			}
			if (csPoint == c_csNosePiece1Offset90)
			{
				m_csNP1Offset90X   = csXPos;
				m_csNP1Offset90Y   = csYPos;
				m_csNP1Offset90Rot = csRot;
			}
			// nosepiece2 settings
			if (csPoint == c_csNosePiece2ScanOffset0)
			{
				m_csNP2ScanOffset0X   = csXPos;
				m_csNP2ScanOffset0Y   = csYPos;
				m_csNP2ScanOffset0Rot = csRot;
			}
			if ( csPoint == c_csNosePiece2ScanOffset90 )
			{
				m_csNP2ScanOffset90X   = csXPos;
				m_csNP2ScanOffset90Y   = csYPos;
				m_csNP2ScanOffset90Rot = csRot;
			}
			if ( csPoint == c_csNosePiece2Offset0 )
			{
				m_csNP2Offset0X   = csXPos;
				m_csNP2Offset0Y   = csYPos;
				m_csNP2Offset0Rot = csRot;
			}
			if ( csPoint == c_csNosePiece2Offset90 )
			{
				m_csNP2Offset90X   = csXPos;
				m_csNP2Offset90Y   = csYPos;
				m_csNP2Offset90Rot = csRot;
			}
			if (csPoint == c_csRestPosition )
			{
				m_csRestPositionX		= csXPos;
				m_csRestPositionY		= csYPos;
				m_csRestPositionRot	= csRot;
			}

			rcdPoints->MoveNext();
		}
	
		rcdPoints->Close();
		if (rcdPoints)			// do not free a NULL pointer
			delete rcdPoints;
		bGoodFind = TRUE;
	}
	else
	{
		csTemp.LoadString ( IDS_NO_POINT_DATA );
		AfxMessageBox ( csTemp );
		rcdPoints->Close();
		if (rcdPoints)			// do not free a NULL pointer
			delete rcdPoints;

		bGoodFind = FALSE;
	}

	// Close the database.

	Close();

	return ( bGoodFind );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: GetApplicatorPoint
//
//	Description:
//		Get the X, Y, and rotation of an applicator point.
//
//	Arguments:
//		Point key.
//		Pointers to X, Y, and rotation.
//
//	Return:
//		None.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

void CDatabase::GetApplicatorPoint ( int nPoint,
												 CString *csXPos, 
												 CString *csYPos,
												 CString *csRot )
{

	switch ( nPoint )
	{

		case ORIGIN_KEY:
			*csXPos = m_csOriginX;
			*csYPos = m_csOriginY;
			*csRot  = m_csOriginRot;
			break;

		case PARK_KEY:
			*csXPos = m_csParkX;
			*csYPos = m_csParkY;
			*csRot  = m_csParkRot;
			break;

		case NP1_SCAN_OFFSET0_KEY:
			*csXPos = m_csNP1ScanOffset0X;
			*csYPos = m_csNP1ScanOffset0Y;
			*csRot  = m_csNP1ScanOffset0Rot;
			break;

		case NP1_SCAN_OFFSET90_KEY:
			*csXPos = m_csNP1ScanOffset90X;
			*csYPos = m_csNP1ScanOffset90Y;
			*csRot  = m_csNP1ScanOffset90Rot;
			break;

		case NP1_OFFSET0_KEY:
			*csXPos = m_csNP1Offset0X;
			*csYPos = m_csNP1Offset0Y;
			*csRot  = m_csNP1Offset0Rot;
			break;

		case NP1_OFFSET90_KEY:
			*csXPos = m_csNP1Offset90X;
			*csYPos = m_csNP1Offset90Y;
			*csRot  = m_csNP1Offset90Rot;
			break;

		case NP2_SCAN_OFFSET0_KEY:
			*csXPos = m_csNP2ScanOffset0X;
			*csYPos = m_csNP2ScanOffset0Y;
			*csRot  = m_csNP2ScanOffset0Rot;
			break;

		case NP2_SCAN_OFFSET90_KEY:
			*csXPos = m_csNP2ScanOffset90X;
			*csYPos = m_csNP2ScanOffset90Y;
			*csRot  = m_csNP2ScanOffset90Rot;
			break;

		case NP2_OFFSET0_KEY:
			*csXPos = m_csNP2Offset0X;
			*csYPos = m_csNP2Offset0Y;
			*csRot  = m_csNP2Offset0Rot;
			break;

		case NP2_OFFSET90_KEY:
			*csXPos = m_csNP2Offset90X;
			*csYPos = m_csNP2Offset90Y;
			*csRot  = m_csNP2Offset90Rot;
			break;

		case REST_POSITION_KEY:
			*csXPos = m_csRestPositionX;
			*csYPos = m_csRestPositionY;
			*csRot  = m_csRestPositionRot;
			break;

	}

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetApplicatorPoint
//
//	Description:
//		Update the database with the applicator point.
//
//	Arguments:
//		Map of applicator points
//
//	Return:
//		Status.
//
//	Called by:
//		CSystemSetup::UpdateApplicatorPoints
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::SetApplicatorPoint ( int nPoint,
												   CString csXPos, 
													CString csYPos,
													CString csRot )
{

	int nCount;
	COleVariant var;
	CString csTemp = " ";

	BOOL bGoodFind;

	char *p_chr_temp;

	CDaoRecordset	*rcsPoints;

	CString 
		csPoint;

	// Open the database.
	if ( !Open() )
		return ( FALSE );

	rcsPoints = new CDaoRecordset( &m_dbJobDatabase );
	csTemp = "Select * from tbl_point"; 
	rcsPoints->Open(AFX_DAO_USE_DEFAULT_TYPE, csTemp);
	nCount = rcsPoints->GetRecordCount();

	if ( nCount > 0 )
	{

		switch ( nPoint )
		{

			case ORIGIN_KEY:
				csPoint = c_csOriginPos;
				m_csOriginX   = csXPos;
				m_csOriginY   = csYPos;
				break;

			case PARK_KEY:
				csPoint = c_csParkPos;
				m_csParkX   = csXPos;
				m_csParkY   = csYPos;
				m_csParkRot = csRot;
				break;

			case NP1_SCAN_OFFSET0_KEY:
				csPoint = c_csNosePiece1ScanOffset0;
				m_csNP1ScanOffset0X   = csXPos;
				m_csNP1ScanOffset0Y   = csYPos;
				break;
			case NP1_SCAN_OFFSET90_KEY:
				csPoint = c_csNosePiece1ScanOffset90;
				m_csNP1ScanOffset90X   = csXPos;
				m_csNP1ScanOffset90Y   = csYPos;			
				break;
			case NP1_OFFSET0_KEY:
				csPoint = c_csNosePiece1Offset0;
				m_csNP1Offset0X   = csXPos;
				m_csNP1Offset0Y   = csYPos;
				break;
			case NP1_OFFSET90_KEY:
				csPoint = c_csNosePiece1Offset90;
				m_csNP1Offset90X   = csXPos;
				m_csNP1Offset90Y   = csYPos;
				break;
			case NP2_SCAN_OFFSET0_KEY:
				csPoint = c_csNosePiece2ScanOffset0;
				m_csNP2ScanOffset0X   = csXPos;
				m_csNP2ScanOffset0Y   = csYPos;
				break;
			case NP2_SCAN_OFFSET90_KEY:
				csPoint = c_csNosePiece2ScanOffset90;
				m_csNP2ScanOffset90X   = csXPos;
				m_csNP2ScanOffset90Y   = csYPos;
				break;
			case NP2_OFFSET0_KEY:
				csPoint = c_csNosePiece2Offset0;
				m_csNP2Offset0X   = csXPos;
				m_csNP2Offset0Y   = csYPos;
				break;
			case NP2_OFFSET90_KEY:
				csPoint = c_csNosePiece2Offset90;
				m_csNP2Offset90X   = csXPos;
				m_csNP2Offset90Y   = csYPos;
				break;
			case REST_POSITION_KEY:
				csPoint = c_csRestPosition;
				m_csRestPositionX = csXPos;
				m_csRestPositionY = csYPos;
				break;
			default:
				csPoint.Empty();
				break;
		}

		// Add to the database.

		rcsPoints->MoveFirst();

		bGoodFind = FALSE;
		while ( !rcsPoints->IsEOF() && !bGoodFind )
		{
			rcsPoints->GetFieldValue( "Point_Name", var );
			csTemp = var.pbVal;
			
			// Find the matching template name.
			if ( csPoint == csTemp )
			{
				// Set the X, Y, and rotation values.	
				p_chr_temp = csXPos.GetBuffer ( csXPos.GetLength() );
				rcsPoints->Edit();
				rcsPoints->SetFieldValue ( "X", p_chr_temp );
				rcsPoints->Update();

				p_chr_temp = csYPos.GetBuffer ( csYPos.GetLength() );
				rcsPoints->Edit();
				rcsPoints->SetFieldValue ( "Y", p_chr_temp );
				rcsPoints->Update();

				p_chr_temp = csRot.GetBuffer ( csRot.GetLength() );
				rcsPoints->Edit();
				rcsPoints->SetFieldValue ( "Rotation", p_chr_temp );
				rcsPoints->Update();

				csXPos.ReleaseBuffer();
				csYPos.ReleaseBuffer();
				csRot.ReleaseBuffer();

				bGoodFind = TRUE;

			}

			rcsPoints->MoveNext();

		}
	}
	else
	{
		bGoodFind = FALSE;
	}

	rcsPoints->Close();
	
	if (rcdPoints)			// do not free a NULL pointer
		delete rcsPoints;

	// Close the database.

	Close();

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_NO_POINT_DATA );
		AfxMessageBox ( csTemp );
	}

	return ( bGoodFind );
}

*/

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetStatisticalInfo
//
//	Description:
//		Get the statistical setup information.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetStatisticalInfo
//
//	Description:
//		Set the statistical setup information.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetActivePrinterAttributes
//
//	Description:
//		Get the printer information.
//
//	Arguments:
//		Printer name.
//		Pointer to printer use flag.
//		Pointer to enable flag.
//		Pointer to printer type.
//
//	Return:
//		Status.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::GetActivePrinterAttributes ( CString *csName, 
													BOOL *bUse,
													BOOL *bEnable,
													int *nType)
{

	int nCount;
	COleVariant var;
	CString csTemp;
	BOOL bGoodFind;

	CString
		csPrinter;


	CDaoRecordset	*rcdPrinter;

	// check the database for 1up or 2up
	int		nRescans,nRepicks,nNumberOfNosepieces;
	BOOL	b2up;
	GetGeneralAttributes(&nRescans,&nRepicks,&b2up,&nNumberOfNosepieces);



	// Open the database.

	if ( !Open() )
		return ( FALSE );

	// Get printer name string.


	rcdPrinter = new CDaoRecordset( &m_dbJobDatabase );
	
	csTemp = "Select * from tbl_printer" ;   // CDaoRecordset does not like one-record recordset ? 

	rcdPrinter->Open(AFX_DAO_USE_DEFAULT_TYPE, csTemp);

	nCount = rcdPrinter->GetRecordCount();

	if ( nCount > 0 ) 
	{
		rcdPrinter->MoveFirst();

		bGoodFind = FALSE;
		while ( !rcdPrinter->IsEOF() && !bGoodFind )
		{

			rcdPrinter->GetFieldValue ( "Use", var );
			csTemp = var.pbVal;

			if ( csTemp.CompareNoCase ( "YES" ) == 0 )
				*bUse = TRUE;
			else
				*bUse = FALSE;

			if ( *bUse)
			{

				// Printer found. Get the rest of the attributes.


				rcdPrinter->GetFieldValue ( "Printer_Name", var );
				*csName = var.pbVal;
	
				
				
				rcdPrinter->GetFieldValue ( "Use", var );
				csTemp = var.pbVal;

				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					*bUse = TRUE;
				else
					*bUse = FALSE;

				rcdPrinter->GetFieldValue ( "Enable", var );
				csTemp = var.pbVal;

				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					*bEnable = TRUE;
				else
					*bEnable = FALSE;

				rcdPrinter->GetFieldValue ( "Type", var );
				csTemp = var.pbVal;

				if ( csTemp == "Zebra" )
					*nType = ZEBRA;
				else if( csTemp == "Intermec" )
					*nType = INTERMEC;
				else if( csTemp == "Datamax" )
					*nType = DATAMAX;
				else if( csTemp == "Tharo" )
					*nType = THARO;
				else
					*nType =GENERIC;


				bGoodFind = TRUE;
				break;

			}

			rcdPrinter->MoveNext();
		}	// End while
	}
	else
	{
		bGoodFind = FALSE;
	}

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_INVALID_PRINTER_DATABASE );
		AfxMessageBox ( csTemp );
	}


	rcdPrinter->Close();
	if (rcdPrinter)			// do not free a NULL pointer
		delete rcdPrinter;

	// Close the database.

	Close();

	return ( bGoodFind );

}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetPrinterAttributes
//
//	Description:
//		Get the printer information.
//
//	Arguments:
//		Printer name.
//		Pointer to printer use flag.
//		Pointer to enable flag.
//		Pointer to printer type.
//		Pointer to pre-pick position.
//		Pointer to pick position.
//
//	Return:
//		Status.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::GetPrinterAttributes ( CString csName, 
													BOOL *bUse,
													BOOL *bEnable,
													int *nType)
{

	int nCount;
	COleVariant var;
	CString csTemp;
	BOOL bGoodFind;

	CString
		csPrinter;

	CUtilities Utility;

	CDaoRecordset	*rcdPrinter;

	// check the database for 1up or 2up
	int		nRescans,nRepicks,nNumberOfNosepieces;
	BOOL	b2up;
	GetGeneralAttributes(&nRescans,&nRepicks,&b2up,&nNumberOfNosepieces);



	// Open the database.

	if ( !Open() )
		return ( FALSE );

	// Get printer name string.


	rcdPrinter = new CDaoRecordset( &m_dbJobDatabase );
	
	csTemp = "Select * from tbl_printer" ;   // CDaoRecordset does not like one-record recordset ? 

	rcdPrinter->Open(AFX_DAO_USE_DEFAULT_TYPE, csTemp);

	nCount = rcdPrinter->GetRecordCount();

	if ( nCount > 0 ) 
	{
		rcdPrinter->MoveFirst();

		bGoodFind = FALSE;
		while ( !rcdPrinter->IsEOF() && !bGoodFind )
		{

			// Find printer match.

			rcdPrinter->GetFieldValue ( "Printer_Name", var );
			csTemp = var.pbVal;
	
			if ( csName.CompareNoCase ( csTemp ) == 0 )
			{

				// Printer found. Get the rest of the attributes.

				rcdPrinter->GetFieldValue ( "Use", var );
				csTemp = var.pbVal;

				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					*bUse = TRUE;
				else
					*bUse = FALSE;

				rcdPrinter->GetFieldValue ( "Enable", var );
				csTemp = var.pbVal;

				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					*bEnable = TRUE;
				else
					*bEnable = FALSE;

				rcdPrinter->GetFieldValue ( "Type", var );
				csTemp = var.pbVal;

				if ( csTemp == "Zebra" )
					*nType = ZEBRA;
				else if( csTemp == "Intermec" )
					*nType = INTERMEC;
				else if( csTemp == "Datamax" )
					*nType = DATAMAX;
				else if( csTemp == "Tharo" )
					*nType = THARO;
				else
					*nType =GENERIC;

				bGoodFind = TRUE;

			}

			rcdPrinter->MoveNext();
		}	// End while
	}
	else
	{
		bGoodFind = FALSE;
	}

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_INVALID_PRINTER_DATABASE );
		AfxMessageBox ( csTemp );
	}


	rcdPrinter->Close();
	if (rcdPrinter)			// do not free a NULL pointer
		delete rcdPrinter;

	// Close the database.

	Close();

	return ( bGoodFind );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetPrinterAttributes
//
//	Description:
//		Get the printer information.
//
//	Arguments:
//		Printer name.
//		Printer use flag.
//		Enable flag.
//		Printer type.
//
//	Return:
//		Status.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::SetPrinterAttributes ( CString csName, 
													BOOL bUse,
													BOOL bEnable,
													int nType)
{

	int nCount;
	COleVariant var;
	CString csTemp = " ";

	BOOL bGoodFind;

	char *p_chr_temp;


	CString
		csPrinter;


	CDaoRecordset	*rcdPrinter;


	// check the database for 1up or 2up
	int		nRescans,nRepicks,nNumberOfNosepieces;
	BOOL	b2up;
	GetGeneralAttributes(&nRescans,&nRepicks,&b2up,&nNumberOfNosepieces);


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	// Get printer name string.


	rcdPrinter = new CDaoRecordset( &m_dbJobDatabase );
	
	csTemp = "Select * from tbl_printer" ;   // CDaoRecordset does not like one-record recordset ? 

	rcdPrinter->Open(AFX_DAO_USE_DEFAULT_TYPE, csTemp);

	nCount = rcdPrinter->GetRecordCount();

	if ( nCount > 0 ) 
	{
		rcdPrinter->MoveFirst();

		bGoodFind = FALSE;
		while ( !rcdPrinter->IsEOF() && !bGoodFind )
		{

			// Find printer match.

			rcdPrinter->GetFieldValue ( "Printer_Name", var );
			csTemp = var.pbVal;
	
			if ( csName.CompareNoCase ( csTemp ) == 0 )
			{

				// Printer found. Set the rest of the attributes.

				if ( bUse )
					csTemp = "YES";
				else
					csTemp = "NO";

				rcdPrinter->Edit();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdPrinter->SetFieldValue ( "Use", p_chr_temp );
				rcdPrinter->Update();

				if ( bEnable )
					csTemp = "YES";
				else
					csTemp = "NO";

				rcdPrinter->Edit();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdPrinter->SetFieldValue ( "Enable", p_chr_temp );
				rcdPrinter->Update();

				switch ( nType )
				{

					case ZEBRA:
						csTemp = "Zebra";
						break;

					case INTERMEC:
						csTemp = "Intermec";
						break;

					case DATAMAX:
						csTemp = "Datamax";
						break;

					case THARO:
						csTemp = "Tharo";
						break;
					
					case GENERIC:
						csTemp = "Generic";
						break;
					
					default:
						csTemp.LoadString ( IDS_INVALID_PRINTER_TYPE );
						AfxMessageBox ( csTemp );
						rcdPrinter->Close();
						if (rcdPrinter)			// do not free a NULL pointer
							delete rcdPrinter;
						Close();
						return ( FALSE );
						break;
				}

				rcdPrinter->Edit();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdPrinter->SetFieldValue ( "Type", p_chr_temp );
				rcdPrinter->Update();

				bGoodFind = TRUE;

			}

			rcdPrinter->MoveNext();
		}	// End while
	}
	else
	{
		bGoodFind = FALSE;
	}

	if ( !bGoodFind )
	{

		// No record for printer. Add it to the database.

		rcdPrinter->AddNew();

		csTemp = csName;

		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdPrinter->SetFieldValue ( "Printer_Name", p_chr_temp );
		csTemp.ReleaseBuffer();
		
		if ( bUse )
			csTemp = "YES";
		else
			csTemp = "NO";

		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdPrinter->SetFieldValue ( "Use", p_chr_temp );
		csTemp.ReleaseBuffer();

		if ( bEnable )
			csTemp = "YES";
		else
			csTemp = "NO";

		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdPrinter->SetFieldValue ( "Enable", p_chr_temp );
		csTemp.ReleaseBuffer();

		switch ( nType )
		{

			case ZEBRA:
				csTemp = "Zebra";
				break;

			case INTERMEC:
				csTemp = "Intermec";
				break;

			case DATAMAX:
				csTemp = "Datamax";
				break;


			case THARO:
				csTemp = "Tharo";
				break;
			
			case GENERIC:
				csTemp = "Generic";
				break;

			default:
				csTemp.LoadString ( IDS_INVALID_PRINTER_TYPE );
				AfxMessageBox ( csTemp );
				rcdPrinter->Close();
				if (rcdPrinter)			// do not free a NULL pointer
					delete rcdPrinter;
				Close();
				return ( FALSE );
				break;
		}

		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdPrinter->SetFieldValue ( "Type", p_chr_temp );
		csTemp.ReleaseBuffer();
/*
		if ( bUseLabelDesigner )
			csTemp = "YES";
		else
			csTemp = "NO";

		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdPrinter->SetFieldValue ( "Use_Designer", p_chr_temp );
		csTemp.ReleaseBuffer();

		csTemp = csTemplate;
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdPrinter->SetFieldValue ( "Template", p_chr_temp );
		csTemp.ReleaseBuffer();
*/

		rcdPrinter->Update();

	}


	rcdPrinter->Close();
	if (rcdPrinter)			// do not free a NULL pointer
		delete rcdPrinter;

	// Close the database.

	Close();

	return ( bGoodFind );

}



/*

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetFeederAttributes
//
//	Description:
//		Get the feeder information.
//
//	Arguments:
//		Printer name.
//		Pointer to feeder use flag.
//		Pointer to enable flag.
//		Pointer to timer.
//		Pointer to pre-pick position.
//		Pointer to pick position.
//
//	Return:
//		Status.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::GetFeederAttributes ( CString csName, 
													BOOL *bUse,
													BOOL *bEnable,
													int *nTimer)
{

	int nCount;
	COleVariant var;
	CString csTemp;
	BOOL bGoodFind;

	CString
		csFeeder;


	CDaoRecordset	*rcdFeeder;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	// Get printer name string.


	rcdFeeder = new CDaoRecordset( &m_dbJobDatabase );
	
	csTemp = "Select * from tbl_feeder";   

	rcdFeeder->Open(AFX_DAO_USE_DEFAULT_TYPE, csTemp);

	nCount = rcdFeeder->GetRecordCount();

	if ( nCount > 0 ) 
	{
		rcdFeeder->MoveFirst();

		bGoodFind = FALSE;
		while ( !rcdFeeder->IsEOF() && !bGoodFind )
		{

			// Find feeder match.

			rcdFeeder->GetFieldValue ( "Feeder_Name", var );
			csTemp = var.pbVal;
	
			if ( csName.CompareNoCase ( csTemp ) == 0 )
			{

				// Feeder found. Get the rest of the attributes.

				rcdFeeder->GetFieldValue ( "Use", var );
				csTemp = var.pbVal;

				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					*bUse = TRUE;
				else
					*bUse = FALSE;

				rcdFeeder->GetFieldValue ( "Enable", var );
				csTemp = var.pbVal;

				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					*bEnable = TRUE;
				else
					*bEnable = FALSE;

				rcdFeeder->GetFieldValue ( "Timer", var );
				csTemp = var.pbVal;

				*nTimer = atoi ( csTemp );

				bGoodFind = TRUE;

			}

			rcdFeeder->MoveNext();
		}	// End while
	}
	else
	{
		bGoodFind = FALSE;
	}

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_INVALID_FEEDER_DATABASE );
		AfxMessageBox ( csTemp );
	}


	rcdFeeder->Close();
	if (rcdFeeder)			// do not free a NULL pointer
		delete rcdFeeder;

	// Close the database.

	Close();

	return ( bGoodFind );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetFeederAttributes
//
//	Description:
//		Get the feeder information.
//
//	Arguments:
//		Feeder name.
//		Feeder use flag.
//		Enable flag.
//		Timer.
//		Pre-pick position.
//		Pick position.
//
//	Return:
//		Status.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::SetFeederAttributes ( CString csName, 
													BOOL bUse,
													BOOL bEnable,
													int nTimer)
{

	int nCount;
	COleVariant var;
	CString csTemp = " ";

	BOOL bGoodFind;

	char *p_chr_temp;


	CString
		csFeeder;


	CDaoRecordset	*rcdFeeder;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	// Get feeder name string.


	rcdFeeder = new CDaoRecordset( &m_dbJobDatabase );
	
	csTemp = "Select * from tbl_feeder" ;   // CDaoRecordset does not like one-record recordset ? 

	rcdFeeder->Open(AFX_DAO_USE_DEFAULT_TYPE, csTemp);

	nCount = rcdFeeder->GetRecordCount();

	if ( nCount > 0 ) 
	{
		rcdFeeder->MoveFirst();

		bGoodFind = FALSE;
		while ( !rcdFeeder->IsEOF() && !bGoodFind )
		{

			// Find feeder match.

			rcdFeeder->GetFieldValue ( "Feeder_Name", var );
			csTemp = var.pbVal;
	
			if ( csName.CompareNoCase ( csTemp ) == 0 )
			{

				// Feeder found. Set the rest of the attributes.

				if ( bUse )
					csTemp = "YES";
				else
					csTemp = "NO";

				rcdFeeder->Edit();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdFeeder->SetFieldValue ( "Use", p_chr_temp );
				rcdFeeder->Update();

				if ( bEnable )
					csTemp = "YES";
				else
					csTemp = "NO";

				rcdFeeder->Edit();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdFeeder->SetFieldValue ( "Enable", p_chr_temp );
				rcdFeeder->Update();

				csTemp.Format ( "%d", nTimer );
				rcdFeeder->Edit();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdFeeder->SetFieldValue ( "Timer", p_chr_temp );
				rcdFeeder->Update();


				bGoodFind = TRUE;

			}

			rcdFeeder->MoveNext();
		}	// End while
	}
	else
	{
		bGoodFind = FALSE;
	}

	if ( !bGoodFind )
	{

		// No record for feeder. Add it to the database.

		rcdFeeder->AddNew();

		csTemp = csName;

		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdFeeder->SetFieldValue ( "Feeder_Name", p_chr_temp );
		csTemp.ReleaseBuffer();
		
		if ( bUse )
			csTemp = "YES";
		else
			csTemp = "NO";

		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdFeeder->SetFieldValue ( "Use", p_chr_temp );
		csTemp.ReleaseBuffer();

		if ( bEnable )
			csTemp = "YES";
		else
			csTemp = "NO";

		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdFeeder->SetFieldValue ( "Enable", p_chr_temp );
		csTemp.ReleaseBuffer();

		csTemp.Format ( "%d", nTimer );
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdFeeder->SetFieldValue ( "Timer", p_chr_temp );
		csTemp.ReleaseBuffer();
		rcdFeeder->Update();

	}


	rcdFeeder->Close();
	if (rcdFeeder)			// do not free a NULL pointer
		delete rcdFeeder;

	// Close the database.

	Close();

	return ( bGoodFind );

}

*/


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetComPortAttributes
//
//	Description:
//		Get the port attributes for the appropriate device.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::GetComPortAttributes ( CString csName,
													int *nTriggerDelay,
													int *nInputBufferSize,
													int *nOutputBufferSize,
													int *nPortID,
													CString *csPortSettings,
													BOOL *blnDTREnable,
													BOOL *blnRTSEnable,
													BOOL *blnNULLDiscard)
{

	int nCount;
	COleVariant var;
	CString csTemp;
	BOOL bGoodFind;

	CString
		csPrinter,
		csSQLCmd;


	CDaoRecordset	*rcdComPort;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdComPort = new CDaoRecordset( &m_dbJobDatabase );
	
	csSQLCmd = CString("Select * from tbl_com_ports Where Device_Name = ") +
				CString("'")+ csName + CString ("'");   

	rcdComPort->Open(AFX_DAO_USE_DEFAULT_TYPE, csSQLCmd);

	nCount = rcdComPort->GetRecordCount();

	if ( nCount==1) 
	{

		bGoodFind = TRUE;

		// Device found. Get the rest of the attributes.

		rcdComPort->GetFieldValue ( "Port_ID", var );
		csTemp = var.pbVal;

		int nPort;

		nPort = atoi ( csTemp );

		if ( nPort < 1 || nPort > 12 )
		{
			csTemp.LoadString ( IDS_INVALID_PORTID );
			AfxMessageBox ( csTemp );
			return FALSE;				
		}

		*nPortID = nPort;

		rcdComPort->GetFieldValue ( "Settings", var );
		csTemp = var.pbVal;
		*csPortSettings = csTemp;				

		rcdComPort->GetFieldValue ( "Trigger_Delay", var );
		csTemp = var.pbVal;
		*nTriggerDelay = atoi ( csTemp );				

		rcdComPort->GetFieldValue ( "Input_Buffer_Size", var );
		csTemp = var.pbVal;
		*nInputBufferSize = atoi ( csTemp );				

		rcdComPort->GetFieldValue ( "Output_Buffer_Size", var );
		csTemp = var.pbVal;
		*nOutputBufferSize = atoi ( csTemp );				


		rcdComPort->GetFieldValue ( "SetDTREnable", var );
		*blnDTREnable = var.bVal;

		rcdComPort->GetFieldValue ( "SetRTSEnable", var );
		*blnRTSEnable = var.bVal;
		
		
		rcdComPort->GetFieldValue ( "SetNULLDiscard", var );
		*blnNULLDiscard = var.bVal;

		
		bGoodFind = TRUE;

	}
	else
	{
		bGoodFind = FALSE;
		csTemp.LoadString ( IDS_INVALID_COMPORT_DATABASE );
		AfxMessageBox ( csTemp );
	}


	rcdComPort->Close();
	if (rcdComPort)			// do not free a NULL pointer
		delete rcdComPort;

	// Close the database.

	Close();

	return ( bGoodFind );

}

/*

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetConveyorDIOAddress
//
//	Description:
//		Get the DIO addresses for the conveyor system.
//
//	Arguments:
//		Pointer to input address.
//		Pointer to output address.
//
//	Return:
//		Status.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::GetConveyorDIOAddress ( CString * csInput, CString * csOutput )
{

	int nCount;
	COleVariant var;
	CString csTemp;
	BOOL bGoodFind;


	CDaoRecordset	*rcdDIO;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdDIO = new CDaoRecordset( &m_dbJobDatabase );    // all of same kind pointer
	rcdDIO->Open(AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_dio_settings");

	nCount = rcdDIO->GetRecordCount();

	if ( nCount > 0  )
	{
		rcdDIO->MoveFirst();

		while ( !rcdDIO->IsEOF() )
		{
			rcdDIO->GetFieldValue( "Name", var );
			csTemp = var.pbVal;
			
			if ( csTemp == "Conveyor_Input" )
			{
				rcdDIO->GetFieldValue ( "Base_Address", var );
				csTemp = var.pbVal;
				*csInput = csTemp;
			}

			if ( csTemp == "Conveyor_Output" )
			{
				rcdDIO->GetFieldValue ( "Base_Address", var );
				csTemp = var.pbVal;
				*csOutput = csTemp;
			}

			rcdDIO->MoveNext();
		}
	
		bGoodFind = TRUE;
	}
	else
	{

		bGoodFind = FALSE;
	}

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_INVALID_CONVEYORIO_DATABASE );
		AfxMessageBox ( csTemp );
	}


	rcdDIO->Close();
	if (rcdDIO)		// do not free NULL Pointer
		delete rcdDIO;

	// Close the database.

	Close();

	return ( bGoodFind );

}

*/

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetDIOAddress
//
//	Description:
//		Get the DIO addresses for the system.
//
//	Arguments:
//		Pointer to input address.
//		Pointer to output address.
//
//	Return:
//		Status.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::GetDIOAddress ( CString * csInput, CString * csOutput )
{

	int nCount;
	COleVariant var;
	CString csTemp;
	BOOL bGoodFind;


	CDaoRecordset	*rcdDIO;

	
	// initialize variables
	nCount=0;
	csTemp.FreeExtra();  
	bGoodFind=FALSE;
	


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdDIO = new CDaoRecordset( &m_dbJobDatabase );    // all of same kind pointer
	rcdDIO->Open(AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_dio_settings");

	nCount = rcdDIO->GetRecordCount();

	if ( nCount > 0  )
	{
		rcdDIO->MoveFirst();
		
		while ( !rcdDIO->IsEOF() )
		{
			var.Clear();
			rcdDIO->GetFieldValue( "Name", var );
			csTemp = var.pbVal;
			
			if ( csTemp.Find("System_Input")!=-1 )
			{
				rcdDIO->GetFieldValue ( "Base_Address", var );
				csTemp = var.pbVal;
				*csInput = csTemp;
			}

			if ( csTemp.Find("System_Output")!=-1)
			{
				rcdDIO->GetFieldValue ( "Base_Address", var );
				csTemp = var.pbVal;
				*csOutput = csTemp;
			}

			rcdDIO->MoveNext();
		}
	
		bGoodFind = TRUE;
	}
	else
	{

		bGoodFind = FALSE;
	}

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_INVALID_SYSTEMIO_DATABASE );
		AfxMessageBox ( csTemp );
	}


	rcdDIO->Close();
	if (rcdDIO)		// do not free NULL Pointer
		delete rcdDIO;

	// Close the database.

	Close();

	return ( bGoodFind );

}





/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetPassword
//
//	Description:
//		Update the database with the password.
//
//	Arguments:
//		Password
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::SetPassword ( CString csPassword )
{

	int nCount;
	COleVariant var;
	CString csTemp = " ";
	BOOL bGoodFind;

	char *p_chr_temp;

	CDaoRecordset	*rcdGeneral;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdGeneral = new CDaoRecordset( &m_dbJobDatabase );
	
	csTemp = "Select * from tbl_general" ;   // CDaoRecordset does not like one-record recordset ? 

	rcdGeneral->Open(AFX_DAO_USE_DEFAULT_TYPE, csTemp);

	nCount = rcdGeneral->GetRecordCount();

	if ( nCount > 0 ) 
	{
		rcdGeneral->MoveFirst();

		rcdGeneral->Edit();
		csTemp = csPassword;
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdGeneral->SetFieldValue ( "password", p_chr_temp );
		rcdGeneral->Update();

		bGoodFind = TRUE;
	}
	else
	{
		csTemp.LoadString ( IDS_NO_PASSWORD_DATA );
		AfxMessageBox ( csTemp );
		bGoodFind = FALSE;
	}

	rcdGeneral->Close();
	if (rcdGeneral)		// do not free NULL Pointer
		delete rcdGeneral;

	// Close the database.

	Close();

	return ( bGoodFind );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetPassword
//
//	Description:
//		Get the password from the database.
//
//	Arguments:
//		Pointer to password string
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::GetPassword ( CString *csPassword )
{


	int nCount;
	COleVariant var;
	CString csTemp;
	BOOL bGoodFind;


	CDaoRecordset	*rcdGeneral;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdGeneral = new CDaoRecordset( &m_dbJobDatabase );    // all of same kind pointer
	rcdGeneral->Open(AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_general");

	nCount = rcdGeneral->GetRecordCount();

	if ( nCount > 0  )
	{
		rcdGeneral->MoveFirst();

		rcdGeneral->GetFieldValue ( "Password", var );
		csTemp = var.pbVal;

		*csPassword = csTemp;

		bGoodFind = TRUE;
	}
	else
	{
		csTemp.LoadString ( IDS_NO_PASSWORD_DATA );
		AfxMessageBox ( csTemp );
		bGoodFind = FALSE;
	}

	rcdGeneral->Close();
	if (rcdGeneral)		// do not free NULL Pointer
		delete rcdGeneral;

	// Close the database.

	Close();

	return ( bGoodFind );

}





/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetConveyorAttributes
//
//	Description:
//		Get the attributes for the conveyor system.
//
//	Arguments:
//		Pointer to PC control flag.
//		Pointer to direction flag.
//
//	Return:
//		Status.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////









/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetUsablePrinterList
//
//	Description:
//		Get the attributes for the conveyor system.
//
//	Arguments:
//		Pointer to printer list.
//
//	Return:
//		Status.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::GetUsablePrinterList ( CString *csPrinterList )
{

	int nCount;
	COleVariant var;
	CString csTemp;
	BOOL bGoodFind;

	CString
		csPrinter;


	CDaoRecordset	*rcdPrinter;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	// Get printer name string.


	rcdPrinter = new CDaoRecordset( &m_dbJobDatabase );
	
	csTemp = "Select * from tbl_printer" ;   // CDaoRecordset does not like one-record recordset ? 

	rcdPrinter->Open(AFX_DAO_USE_DEFAULT_TYPE, csTemp);

	nCount = rcdPrinter->GetRecordCount();

	if ( nCount > 0 ) 
	{
		rcdPrinter->MoveFirst();

		bGoodFind = FALSE;
		while ( !rcdPrinter->IsEOF() && !bGoodFind )
		{

			// Find printer match.

			rcdPrinter->GetFieldValue ( "Printer_Name", var );
			csTemp = var.pbVal;

			csPrinter = csTemp;

			rcdPrinter->GetFieldValue ( "Use", var );
			csTemp = var.pbVal;

			if ( csTemp.CompareNoCase ( "YES" ) == 0 )
				*csPrinterList += csPrinter + ";";

			rcdPrinter->MoveNext();

		}	// End while

		bGoodFind = TRUE;

	}
	else
	{
		bGoodFind = FALSE;
	}

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_INVALID_PRINTER_DATABASE );
		AfxMessageBox ( csTemp );
	}


	rcdPrinter->Close();

	if (rcdPrinter)  // do not delete NULL pointer
		delete rcdPrinter;

	// Close the database.

	Close();

	return ( bGoodFind );

}





/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetStartingSN
//
//	Description:
//		Get the starting serial number from the database.
//
//	Arguments:
//		Job file name.
//		Pointer to serial number.
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::GetStartingSN ( CString csJobName, CString *csSerialNumber )
{

	int nCount;
	COleVariant var;
	CString csTemp = " ";

	BOOL bGoodFind;

	CDaoRecordset	*rcdSerialNumber;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdSerialNumber = new CDaoRecordset ( &m_dbJobDatabase );
	rcdSerialNumber->Open ( AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_serial_number" );

	nCount = rcdSerialNumber->GetRecordCount();


	if ( nCount > 0 )
	{
		rcdSerialNumber->MoveFirst();

		bGoodFind = FALSE;

		while ( !rcdSerialNumber->IsEOF() && !bGoodFind )
		{
			rcdSerialNumber->GetFieldValue( "Job_Name", var );
			csTemp = var.pbVal;
			if ( csJobName == csTemp  )
			{

				rcdSerialNumber->GetFieldValue ( "Serial_Number", var );
				csTemp = var.pbVal;
				*csSerialNumber = csTemp;

				bGoodFind = TRUE;
			}
			
			rcdSerialNumber->MoveNext();
		}
	}
	else
		bGoodFind = FALSE;
	
	rcdSerialNumber->Close();

	if (rcdSerialNumber)  // do not delete NULL pointer
		delete rcdSerialNumber;

	// Close the database.

	Close();

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_NO_SN_DATABASE );
		AfxMessageBox ( csTemp );
	}

	return ( bGoodFind );

}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetStartingSN
//
//	Description:
//		Update the database with the starting serial number.
//
//	Arguments:
//		Job file name.
//		Serial number.
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::SetStartingSN ( CString csJobName, CString csSerialNumber )
{

	int nCount;
	COleVariant var;
	CString csTemp = " ";
	BOOL bGoodFind;

	char *p_chr_temp;

	CDaoRecordset	*rcdSerialNumber;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdSerialNumber = new CDaoRecordset ( &m_dbJobDatabase );
	rcdSerialNumber->Open ( AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_serial_number" );

	nCount = rcdSerialNumber->GetRecordCount();


	if ( nCount > 0 )
	{
		rcdSerialNumber->MoveFirst();

		bGoodFind = FALSE;

		while ( !rcdSerialNumber->IsEOF() && !bGoodFind )
		{
			rcdSerialNumber->GetFieldValue( "Job_Name", var );
			csTemp = var.pbVal;
			if ( csJobName == csTemp  )
			{


				rcdSerialNumber->Edit();
				csTemp = csSerialNumber;
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdSerialNumber->SetFieldValue ( "Serial_Number", p_chr_temp );
				rcdSerialNumber->Update();


				bGoodFind = TRUE;
			}
			
			rcdSerialNumber->MoveNext();
		}
	}
	else
		bGoodFind = FALSE;
	
	rcdSerialNumber->Close();
	if (rcdSerialNumber)  // do not delete NULL pointer
		delete rcdSerialNumber;

	// Close the database.

	Close();

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_NO_SN_DATABASE );
		AfxMessageBox ( csTemp );
	}

	return ( bGoodFind );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetAutoRetries
//
//	Description:
//		Update the database with the auto retries.
//
//	Arguments:
//		Rescans
//		Repicks
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::SetAutoRetries ( int nRescans, int nRepicks )
{

	int nCount;
	COleVariant var;
	CString csTemp = " ";
	BOOL bGoodFind;

	char *p_chr_temp;

	CDaoRecordset	*rcdGeneral;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdGeneral = new CDaoRecordset( &m_dbJobDatabase );
	
	csTemp = "Select * from tbl_general" ;   // CDaoRecordset does not like one-record recordset ? 

	rcdGeneral->Open(AFX_DAO_USE_DEFAULT_TYPE, csTemp);

	nCount = rcdGeneral->GetRecordCount();

	if ( nCount > 0 ) 
	{
		rcdGeneral->MoveFirst();

		rcdGeneral->Edit();
		csTemp.Format ( "%d", nRescans );
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdGeneral->SetFieldValue ( "Auto_Rescans", p_chr_temp );
		rcdGeneral->Update();

		rcdGeneral->Edit();
		csTemp.Format ( "%d", nRepicks );
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdGeneral->SetFieldValue ( "Auto_Repicks", p_chr_temp );
		rcdGeneral->Update();

		bGoodFind = TRUE;
	}
	else
	{
		csTemp.LoadString ( IDS_NO_RETRY_DATA );
		AfxMessageBox ( csTemp );
		bGoodFind = FALSE;
	}

	rcdGeneral->Close();
	if (rcdGeneral)  // do not delete NULL pointer
		delete rcdGeneral;

	// Close the database.

	Close();

	return ( bGoodFind );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetTemplate
//
//	Description:
//		Get the printer template of the selected template.
//
//	Arguments:
//		Template name
//		Pointer to template
//
//	Return:
//		Template string.
//
//	Called by:
//		SetupDBPanelLabelDlg::OnClickEditTemplate
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::GetTemplate ( CString csTemplateName, CString *csTemplate )
{

	int nCount;
	COleVariant var;
	CString csTemp = " ";

	BOOL bGoodFind;

	CDaoRecordset	*rcdTemplate;

	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdTemplate = new CDaoRecordset ( &m_dbJobDatabase );
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
	if (rcdTemplate)  // do not delete NULL pointer
		delete rcdTemplate;

	// Close the database.

	Close();

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_NO_MATCHING_DATABASE_TEMP );
		AfxMessageBox ( csTemp );
	}

	return ( bGoodFind );

	
}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetTemplate
//
//	Description:
//		Update the database with the printer template of the selected template.
//
//	Arguments:
//		Template name
//		Template string.
//
//	Return:
//		Status
//
//	Called by:
//		SetupDBPanelLabelDlg::OnClickEditTemplate
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::SetTemplate ( CString csTemplateName, CString csTemplate )
{

	int nCount;
	COleVariant var;
	CString csTemp = " ";

	BOOL bGoodFind;

	char *p_chr_temp;

	CDaoRecordset	*rcdTemplate;


	// Open the database.

	if ( !Open() )
		return ( FALSE );


	rcdTemplate = new CDaoRecordset( &m_dbJobDatabase );
	
	csTemp = "Select * from tbl_templates"; 

	rcdTemplate->Open(AFX_DAO_USE_DEFAULT_TYPE, csTemp);

	nCount = rcdTemplate->GetRecordCount();

	if ( nCount > 0 ) 
	{
		rcdTemplate->MoveFirst();

		bGoodFind = FALSE;
		while ( !rcdTemplate->IsEOF() && !bGoodFind )
		{

			// Find template match.

			rcdTemplate->GetFieldValue( "Template_Name", var );
			csTemp = var.pbVal;

			// Find the matching template name.

			if ( csTemplateName == csTemp )
			{

				// Set the printer template.

				p_chr_temp = csTemplate.GetBuffer ( csTemplate.GetLength() );
				rcdTemplate->Edit();
				rcdTemplate->SetFieldValue ( "Template", p_chr_temp );
				rcdTemplate->Update();

				bGoodFind = TRUE;
			}
			
			rcdTemplate->MoveNext();

		}	// End while
	}
	else
	{
		bGoodFind = FALSE;
	}

	if ( !bGoodFind )
	{

		// No record for template. Add it to the database.
		rcdTemplate->AddNew();

		// write the template name field
		p_chr_temp = csTemplateName.GetBuffer ( csTemplateName.GetLength() );
		rcdTemplate->SetFieldValue ( "Template_Name", p_chr_temp );
		csTemplateName.ReleaseBuffer();

		// write the template field
		p_chr_temp = csTemplate.GetBuffer ( csTemplate.GetLength() );
		rcdTemplate->SetFieldValue ( "Template", p_chr_temp );
		csTemplate.ReleaseBuffer();

		// update the recordset
		rcdTemplate->Update();

	}


	rcdTemplate->Close();
	if (rcdTemplate)  // do not delete NULL pointer
		delete rcdTemplate;

	// Close the database.

	Close();

	return ( bGoodFind );

}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		RemoveJob
//
//	Description:
//		Remove a job from the database.
//
//	Arguments:
//		Job name
//
//	Return:
//		Status.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::RemoveJob ( CString csJobName )
{

	int nCount;
	COleVariant var;
	CString csTemp;

	BOOL bGoodFind;


	CDaoRecordset	*rcdJob;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdJob = new CDaoRecordset ( &m_dbJobDatabase );
	rcdJob->Open ( AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_job" );

	nCount = rcdJob->GetRecordCount();

	if ( nCount > 0 )
	{
		rcdJob->MoveFirst();

		bGoodFind = FALSE;
		while ( !rcdJob->IsEOF() && !bGoodFind )
		{
			rcdJob->GetFieldValue( "Job_Name", var );
			csTemp = var.pbVal;
			
			// Find the matching job name.

			if ( csJobName == csTemp )
			{

				// Remove the record.

				rcdJob->Delete();
				bGoodFind = TRUE;
			}
			
			rcdJob->MoveNext();
		}
	
	}
	else
	{
		bGoodFind = FALSE;
	}

	rcdJob->Close();
	if (rcdJob)  // do not delete NULL pointer
		delete rcdJob;

	// Close the database.

	Close();

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_ERR_JOB_DELETE );
		AfxMessageBox ( csTemp );
	}

	return ( bGoodFind );
	
}





/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetTemplateList
//
//	Description:
//		Get a list of templates from the database.
//
//	Arguments:
//		Pointer to template list.
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::GetTemplateList ( CString *csTemplateList )
{

	int nCount;
	COleVariant var;
	CString csTemp;
	CString csTemplates = "";
	BOOL bGoodFind;

	CDaoRecordset	*rcdTemplate;


	// Open the database.
	if ( !Open() )
		return ( FALSE );

	rcdTemplate = new CDaoRecordset( &m_dbJobDatabase);
	
	csTemp = "Select * from tbl_templates"; 

	rcdTemplate->Open(AFX_DAO_USE_DEFAULT_TYPE, csTemp);

	nCount = rcdTemplate->GetRecordCount();

	if ( nCount > 0 ) 
	{
		rcdTemplate->MoveFirst();

		while ( !rcdTemplate->IsEOF() )
		{
			rcdTemplate->GetFieldValue( "Template_Name", var );
			csTemp = var.pbVal;
			
			// Save list of templates.

			csTemplates += csTemp + ";";
		
			rcdTemplate->MoveNext();
		}
		bGoodFind = TRUE;
	}
	else
	{
		csTemp.LoadString ( IDS_NO_TEMPLATES );
		AfxMessageBox ( csTemp );
		bGoodFind = FALSE;
	}

	rcdTemplate->Close();

	if (rcdTemplate)  // do not delete NULL pointer
		delete rcdTemplate;

	*csTemplateList = csTemplates;

	// Close the database.

	Close();

	return ( bGoodFind );

}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetDeviceNames
//
//	Description:
//		Get a list of the com port devices from the database.
//
//	Arguments:
//		Pointer to device string.
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::GetDeviceNames ( CString *csDevices )
{

	int nCount;
	COleVariant var;
	CString csTemp;
	BOOL bGoodFind;

	CString
		csName = "";


	CDaoRecordset	*rcdComPort;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdComPort = new CDaoRecordset( &m_dbJobDatabase );
	
	csTemp = "Select * from tbl_com_ports" ;   // CDaoRecordset does not like one-record recordset ? 

	rcdComPort->Open(AFX_DAO_USE_DEFAULT_TYPE, csTemp);

	nCount = rcdComPort->GetRecordCount();

	if ( nCount > 0 ) 
	{
		rcdComPort->MoveFirst();

		bGoodFind = FALSE;
		while ( !rcdComPort->IsEOF() && !bGoodFind )
		{

			// Find device name.

			rcdComPort->GetFieldValue ( "Device_Name", var );
			csName += var.pbVal;
			
			csName += ";";

			rcdComPort->MoveNext();
		}	// End while

		bGoodFind = TRUE;

	}
	else
	{
		bGoodFind = FALSE;
	}

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_INVALID_COMPORT_DATABASE );
		AfxMessageBox ( csTemp );
	}

	rcdComPort->Close();
	if (rcdComPort)  // do not delete NULL pointer
		delete rcdComPort;

	// Close the database.

	Close();

	*csDevices = csName;

	return ( bGoodFind );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetDIOAddress
//
//	Description:
//		Set the system DIO address information.
//
//	Arguments:
//		Input string.
//		Output string.
//
//	Return:
//		Status.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::SetDIOAddress ( CString csInput, CString csOutput )
{

	int nCount;
	COleVariant var;
	CString csTemp = " ";
	BOOL bGoodFind;

	char *p_chr_temp;

	CDaoRecordset	*rcdDIO;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdDIO = new CDaoRecordset( &m_dbJobDatabase );
	
	csTemp = "Select * from tbl_dio_settings" ;    

	rcdDIO->Open(AFX_DAO_USE_DEFAULT_TYPE, csTemp);

	nCount = rcdDIO->GetRecordCount();

	if ( nCount > 0 )
	{
		rcdDIO->MoveFirst();

		while ( !rcdDIO->IsEOF() )
		{
			rcdDIO->GetFieldValue( "Name", var);
			csTemp = var.pbVal;
			
			if ( csTemp == "System_Input" )
			{

				rcdDIO->Edit();
				p_chr_temp = csInput.GetBuffer ( csInput.GetLength() );
				rcdDIO->SetFieldValue ( "Base_Address", p_chr_temp );
				rcdDIO->Update();

			}
			if ( csTemp =="System_Output" )
			{

				rcdDIO->Edit();
				p_chr_temp = csOutput.GetBuffer ( csOutput.GetLength() );
				rcdDIO->SetFieldValue ( "Base_Address", p_chr_temp );
				rcdDIO->Update();

			}
			rcdDIO->MoveNext();
		}
	
		bGoodFind = TRUE;
	}
	else
	{

		bGoodFind = FALSE;
	}

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_INVALID_SYSTEMIO_DATABASE );
		AfxMessageBox ( csTemp );
	}


	rcdDIO->Close();
	if (rcdDIO)  // do not delete NULL pointer
		delete rcdDIO;

	// Close the database.

	Close();

	return ( bGoodFind );

}

/*

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetConveyorDIOAddress
//
//	Description:
//		Set the Conveyor DIO address information.
//
//	Arguments:
//		Input string.
//		Output string.
//
//	Return:
//		Status.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::SetConveyorDIOAddress ( CString csInput, CString csOutput )
{

	int nCount;
	COleVariant var;
	CString csTemp = " ";
	BOOL bGoodFind;

	char *p_chr_temp;

	CDaoRecordset	*rcdDIO;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdDIO = new CDaoRecordset( &m_dbJobDatabase );
	
	csTemp = "Select * from tbl_dio_settings" ;    

	rcdDIO->Open(AFX_DAO_USE_DEFAULT_TYPE, csTemp);

	nCount = rcdDIO->GetRecordCount();

	if ( nCount > 0 )
	{
		rcdDIO->MoveFirst();

		while ( !rcdDIO->IsEOF() )
		{
			rcdDIO->GetFieldValue( "Name", var);
			csTemp = var.pbVal;
			
			if ( csTemp == "Conveyor_Input" )
			{

				rcdDIO->Edit();
				p_chr_temp = csInput.GetBuffer ( csInput.GetLength() );
				rcdDIO->SetFieldValue ( "Base_Address", p_chr_temp );
				rcdDIO->Update();

			}
			if ( csTemp =="Conveyor_Output" )
			{

				rcdDIO->Edit();
				p_chr_temp = csOutput.GetBuffer ( csOutput.GetLength() );
				rcdDIO->SetFieldValue ( "Base_Address", p_chr_temp );
				rcdDIO->Update();

			}
			rcdDIO->MoveNext();
		}
	
		bGoodFind = TRUE;
	}
	else
	{

		bGoodFind = FALSE;
	}

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_INVALID_SYSTEMIO_DATABASE );
		AfxMessageBox ( csTemp );
	}


	rcdDIO->Close();
	if (rcdDIO)  // do not delete NULL pointer
		delete rcdDIO;

	// Close the database.

	Close();

	return ( bGoodFind );

}


*/

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetComPortAttributes
//
//	Description:
//		Set the port attributes for the appropriate device.
//
//	Arguments:
//		
//
//	Return:
//		Status.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::SetComPortAttributes ( CString csName,
													int nTriggerDelay,
													int nInputBufferSize,
													int nOutputBufferSize,
													int nPortID,
													CString csPortSettings,
													BOOL blnDTREnable,
													BOOL blnRTSEnable,
													BOOL blnNULLDiscard)
{

	int nCount;
	COleVariant var;
	CString csTemp = " ";
	BOOL bGoodFind;

	char *p_chr_temp;

	CDaoRecordset	*rcdComPort;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdComPort = new CDaoRecordset( &m_dbJobDatabase );
	
	csTemp = "Select * from tbl_com_ports" ;    

	rcdComPort->Open(AFX_DAO_USE_DEFAULT_TYPE, csTemp);

	nCount =rcdComPort->GetRecordCount();

	if ( nCount > 0 )
	{
		rcdComPort->MoveFirst();

		while ( !rcdComPort->IsEOF() )
		{
			
			rcdComPort->GetFieldValue ( "Device_Name", var );
			csTemp = var.pbVal;
	
			if ( csName.CompareNoCase ( csTemp ) == 0 )
			{

				// Device found. Update the record.

				csTemp.Format ( "%d", nPortID );
				rcdComPort->Edit();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdComPort->SetFieldValue ( "Port_ID", p_chr_temp );
				rcdComPort->Update();

				csTemp = csPortSettings;
				rcdComPort->Edit();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdComPort->SetFieldValue ( "Settings", p_chr_temp );
				rcdComPort->Update();

				csTemp.Format ( "%d", nTriggerDelay );
				rcdComPort->Edit();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdComPort->SetFieldValue ( "Trigger_Delay", p_chr_temp );
				rcdComPort->Update();

				csTemp.Format ( "%d", nInputBufferSize );
				rcdComPort->Edit();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdComPort->SetFieldValue ( "Input_Buffer_Size", p_chr_temp );
				rcdComPort->Update();

				csTemp.Format ( "%d", nOutputBufferSize );
				rcdComPort->Edit();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdComPort->SetFieldValue ( "Output_Buffer_Size", p_chr_temp );
				rcdComPort->Update();

				var.bVal=blnDTREnable;
				rcdComPort->SetFieldValue ( "SetDTREnable", var.bVal);
				rcdComPort->Update();
			
				var.bVal=blnRTSEnable;
				rcdComPort->SetFieldValue ( "SetRTSEnable", var.bVal);
				rcdComPort->Update();
			
				var.bVal=blnNULLDiscard;
				rcdComPort->SetFieldValue ( "SetNULLDiscard", var.bVal);
				rcdComPort->Update();

			
			}
			rcdComPort->MoveNext();
		}
	
		bGoodFind = TRUE;
	}
	else
	{

		bGoodFind = FALSE;
	}

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_INVALID_SYSTEMIO_DATABASE );
		AfxMessageBox ( csTemp );
	}


	rcdComPort->Close();
	if (rcdComPort)  // do not delete NULL pointer
		delete rcdComPort;

	// Close the database.

	Close();

	return ( bGoodFind );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetSNAttributes
//
//	Description:
//		Get the serial number attributes from the database.
//
//	Arguments:
//		Job file name.
//		Pointer to serialization flag.
//		Pointer to serialization base.
//		Pointer to serial number length.
//		Pointer to starting serial number.
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::GetSNAttributes ( CString csJobName, 
											 BOOL *bUseSerialization,
											 int *nBase,
											 int *nLength,
											 CString *csSerialNumber )
{

	int nCount;
	COleVariant var;
	CString csTemp = " ";

	BOOL bGoodFind;

	CDaoRecordset	*rcdSerialNumber;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdSerialNumber = new CDaoRecordset ( &m_dbJobDatabase );
	rcdSerialNumber->Open ( AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_serial_number" );

	nCount = rcdSerialNumber->GetRecordCount();


	if ( nCount > 0 )
	{
		rcdSerialNumber->MoveFirst();

		bGoodFind = FALSE;

		while ( !rcdSerialNumber->IsEOF() && !bGoodFind )
		{
			rcdSerialNumber->GetFieldValue( "Job_Name", var );
			csTemp = var.pbVal;
			if ( csJobName == csTemp  )
			{

				rcdSerialNumber->GetFieldValue ( "Use_Serialization", var );
				csTemp = var.pbVal;
				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					*bUseSerialization = TRUE;
				else
					*bUseSerialization = FALSE;

				rcdSerialNumber->GetFieldValue ( "Serialization_Base", var );
				csTemp = var.pbVal;
				if ( csTemp.CompareNoCase ( "Base10" ) == 0 )
					*nBase = BASE10;
				else
					if ( csTemp.CompareNoCase ( "Base16" ) == 0 )
						*nBase = BASE16;
					else
						if (csTemp.CompareNoCase( "Base29" ) == 0 )
							*nBase = BASE29;
						else
							if ( csTemp.CompareNoCase ( "Base31" ) == 0 )
								*nBase = BASE31;
							else
								if ( csTemp.CompareNoCase ( "Base36" ) == 0 )
									*nBase = BASE36;
								else
									*nBase = OTHER;

				rcdSerialNumber->GetFieldValue ( "Length", var );
				csTemp = var.pbVal;
				*nLength = atoi ( csTemp );

				rcdSerialNumber->GetFieldValue ( "Serial_Number", var );
				csTemp = var.pbVal;
				*csSerialNumber = csTemp;

				bGoodFind = TRUE;
			}
			
			rcdSerialNumber->MoveNext();
		}
	}
	else
		bGoodFind = FALSE;
	
	rcdSerialNumber->Close();
	if (rcdSerialNumber)  // do not delete NULL pointer
		delete rcdSerialNumber;

	// Close the database.

	Close();

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_NO_SN_DATABASE );
		AfxMessageBox ( csTemp );
	}

	return ( bGoodFind );

}

BOOL CDatabase::GetSNAttributes ( CString csJobName, 
											 BOOL *bUseSerialization,
											 int *nBase,
											 int *nLength,
											 CString *csSerialNumber,
											 BOOL *blnJulianDateReset)
{

	int nCount;
	COleVariant var;
	CString csTemp = " ";

	BOOL bGoodFind;

	CDaoRecordset	*rcdSerialNumber;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdSerialNumber = new CDaoRecordset ( &m_dbJobDatabase );
	rcdSerialNumber->Open ( AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_serial_number" );

	nCount = rcdSerialNumber->GetRecordCount();


	if ( nCount > 0 )
	{
		rcdSerialNumber->MoveFirst();

		bGoodFind = FALSE;

		while ( !rcdSerialNumber->IsEOF() && !bGoodFind )
		{
			rcdSerialNumber->GetFieldValue( "Job_Name", var );
			csTemp = var.pbVal;
			if ( csJobName == csTemp  )
			{

				rcdSerialNumber->GetFieldValue ( "Use_Serialization", var );
				csTemp = var.pbVal;
				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					*bUseSerialization = TRUE;
				else
					*bUseSerialization = FALSE;

				rcdSerialNumber->GetFieldValue ( "Serialization_Base", var );
				csTemp = var.pbVal;
				if ( csTemp.CompareNoCase ( "Base10" ) == 0 )
					*nBase = BASE10;
				else
					if ( csTemp.CompareNoCase ( "Base16" ) == 0 )
						*nBase = BASE16;
					else
						if (csTemp.CompareNoCase( "Base29" ) == 0 )
							*nBase = BASE29;
						else
							if ( csTemp.CompareNoCase ( "Base31" ) == 0 )
								*nBase = BASE31;
							else
								if ( csTemp.CompareNoCase ( "Base36" ) == 0 )
									*nBase = BASE36;
								else
									*nBase = OTHER;

				rcdSerialNumber->GetFieldValue ( "Length", var );
				csTemp = var.pbVal;
				*nLength = atoi ( csTemp );

				rcdSerialNumber->GetFieldValue ( "Serial_Number", var );
				csTemp = var.pbVal;
				*csSerialNumber = csTemp;
/*
				rcdSerialNumber->GetFieldValue ( "ResetOnJulian", var );
				
				
				if (var.iVal==0)
					*blnJulianDateReset = FALSE ;
				else
					*blnJulianDateReset = TRUE ;

*/
				blnJulianDateReset = FALSE;
				
				bGoodFind = TRUE;
			}
			
			rcdSerialNumber->MoveNext();
		}
	}
	else
		bGoodFind = FALSE;
	
	rcdSerialNumber->Close();
	if (rcdSerialNumber)  // do not delete NULL pointer
		delete rcdSerialNumber;

	// Close the database.

	Close();

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_NO_SN_DATABASE );
		AfxMessageBox ( csTemp );
	}

	return ( bGoodFind );

}

BOOL CDatabase::GetSNAttributes ( CString csJobName, 
											 BOOL *bUseSerialization,
											 int *nBase,
											 int *nLength,
											 CString *csSerialNumber,
											 BOOL *blnJulianDateReset,
											 CString *csLastJulianDate)
{

	int nCount;
	COleVariant var;
	CString csTemp = " ";

	BOOL bGoodFind;

	CDaoRecordset	*rcdSerialNumber;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdSerialNumber = new CDaoRecordset ( &m_dbJobDatabase );
	rcdSerialNumber->Open ( AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_serial_number" );

	nCount = rcdSerialNumber->GetRecordCount();


	if ( nCount > 0 )
	{
		rcdSerialNumber->MoveFirst();

		bGoodFind = FALSE;

		while ( !rcdSerialNumber->IsEOF() && !bGoodFind )
		{
			rcdSerialNumber->GetFieldValue( "Job_Name", var );
			csTemp = var.pbVal;
			if ( csJobName == csTemp  )
			{

				rcdSerialNumber->GetFieldValue ( "Use_Serialization", var );
				csTemp = var.pbVal;
				if ( csTemp.CompareNoCase ( "YES" ) == 0 )
					*bUseSerialization = TRUE;
				else
					*bUseSerialization = FALSE;

				rcdSerialNumber->GetFieldValue ( "Serialization_Base", var );
				csTemp = var.pbVal;
				if ( csTemp.CompareNoCase ( "Base10" ) == 0 )
					*nBase = BASE10;
				else
					if ( csTemp.CompareNoCase ( "Base16" ) == 0 )
						*nBase = BASE16;
					else
						if (csTemp.CompareNoCase( "Base29" ) == 0 )
							*nBase = BASE29;
						else
							if ( csTemp.CompareNoCase ( "Base31" ) == 0 )
								*nBase = BASE31;
							else
								if ( csTemp.CompareNoCase ( "Base36" ) == 0 )
									*nBase = BASE36;
								else
									*nBase = OTHER;

				rcdSerialNumber->GetFieldValue ( "Length", var );
				csTemp = var.pbVal;
				*nLength = atoi ( csTemp );

				rcdSerialNumber->GetFieldValue ( "Serial_Number", var );
				csTemp = var.pbVal;
				*csSerialNumber = csTemp;

/*				rcdSerialNumber->GetFieldValue ( "ResetOnJulian", var );
				
				if (var.iVal==0)
				  *blnJulianDateReset = FALSE ;
				else
				  *blnJulianDateReset = TRUE ;

				if (*blnJulianDateReset==TRUE)
				{
		
					rcdSerialNumber->GetFieldValue ( "LastJulianDate", var );
					csTemp = var.pbVal;
					if (csTemp=="")
					{
						*csLastJulianDate = "";
					}
					else
					{
						*csLastJulianDate = csTemp;
					}
				
				}				
*/
				bGoodFind = TRUE;
			}
			blnJulianDateReset = FALSE;
			*csLastJulianDate="Feature NA";
			rcdSerialNumber->MoveNext();
		}
	}
	else
		bGoodFind = FALSE;
	
	rcdSerialNumber->Close();
	if (rcdSerialNumber)  // do not delete NULL pointer
		delete rcdSerialNumber;

	// Close the database.

	Close();

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_NO_SN_DATABASE );
		AfxMessageBox ( csTemp );
	}

	return ( bGoodFind );

}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetSNAttributes
//
//	Description:
//		Update the database with new serial number attributes.
//
//	Arguments:
//		Job file name.
//		Serialization flag.
//		Serialization base.
//		Serial number length.
//		Starting serial number.
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::SetSNAttributes ( CString csJobName, 
											 BOOL bUseSerialization,
											 int nBase,
											 int nLength,
											 CString csSerialNumber )
{

	int nCount;
	COleVariant var;
	CString csTemp = " ";
	BOOL bSNRecordExists;
	char *p_chr_temp;

	CString
		csBase;

	CDaoRecordset	*rcdSerialNumber;


	// Open the database and recordset
	if ( !Open() )
		return ( FALSE );

	rcdSerialNumber = new CDaoRecordset ( &m_dbJobDatabase );
	rcdSerialNumber->Open ( AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_serial_number" );

	// start assuming record doesn't exist
	bSNRecordExists = FALSE;

	// Convert serialization base.

	switch ( nBase )
	{
		case BASE10:
			csBase = "Base10";
			break;

		case BASE16:
			csBase = "Base16";
			break;

		case BASE29:
			csBase = "Base29";
			break;

		case BASE31:
			csBase = "Base31";
			break;

		case BASE36:
			csBase = "Base36";
			break;

		default:
			csBase = "OTHER";
			break;
	}


	// get the number of records
	nCount = rcdSerialNumber->GetRecordCount();
	if ( nCount > 0 )
	{
		// move to the first record
		rcdSerialNumber->MoveFirst();

		// step through the records looking for the job
		while ( !rcdSerialNumber->IsEOF() && !bSNRecordExists )
		{
			// get the job name of the current record
			rcdSerialNumber->GetFieldValue( "Job_Name", var );
			csTemp = var.pbVal;
			
			// we found the job
			if ( csJobName == csTemp  )
			{

				// Update the serialization use.

				if ( bUseSerialization )
					csTemp = "YES";
				else
					csTemp = "NO";
				rcdSerialNumber->Edit();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdSerialNumber->SetFieldValue ( "Use_Serialization", p_chr_temp );
				rcdSerialNumber->Update();

				// Update the serialization base.

				rcdSerialNumber->Edit();
				p_chr_temp = csBase.GetBuffer ( csBase.GetLength() );
				rcdSerialNumber->SetFieldValue ( "Serialization_Base", p_chr_temp );
				rcdSerialNumber->Update();

				// Update the length of the serial number.

				csTemp.Format ( "%d", nLength );
				rcdSerialNumber->Edit();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdSerialNumber->SetFieldValue ( "Length", p_chr_temp );
				rcdSerialNumber->Update();

				// Update the serial number.

				csTemp = csSerialNumber;
				rcdSerialNumber->Edit();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdSerialNumber->SetFieldValue ( "Serial_number", p_chr_temp );
				rcdSerialNumber->Update();

				// We found the record.

				bSNRecordExists = TRUE;
			}
			
			// we didn't find the record, try the next one
			rcdSerialNumber->MoveNext();

		} // end while
	} // end if

	// if the job doesn't exist create it
	if ( !bSNRecordExists )
	{
		// No record for this job. Add it to the database.
		rcdSerialNumber->AddNew();
		
		csTemp = csJobName;

		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdSerialNumber->SetFieldValue ( "Job_Name", p_chr_temp );
		csTemp.ReleaseBuffer();

		
		if ( bUseSerialization )
			csTemp = "YES";
		else
			csTemp = "NO";
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdSerialNumber->SetFieldValue ( "Use_Serialization", p_chr_temp );
		csTemp.ReleaseBuffer();

		p_chr_temp = csBase.GetBuffer ( csBase.GetLength() );
		rcdSerialNumber->SetFieldValue ( "Serialization_Base", p_chr_temp );
		csBase.ReleaseBuffer();

		csTemp.Format ( "%d", nLength );
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdSerialNumber->SetFieldValue ( "Length", p_chr_temp );
		csTemp.ReleaseBuffer();

		csTemp = csSerialNumber;
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdSerialNumber->SetFieldValue ( "Serial_number", p_chr_temp );
		csTemp.ReleaseBuffer();


		rcdSerialNumber->Update();
	}

	// close recordset and delete object
	rcdSerialNumber->Close();
	if (rcdSerialNumber)  // do not delete NULL pointer
		delete rcdSerialNumber;

	// Close the database.
	Close();

	return (TRUE);
}

BOOL CDatabase::SetSNAttributes ( CString csJobName, 
											 BOOL bUseSerialization,
											 int nBase,
											 int nLength,
											 CString csSerialNumber,
											 BOOL blnResetJulianDate)
{

	int nCount;
	COleVariant var;
	CString csTemp = " ";
	BOOL bSNRecordExists;
	char *p_chr_temp;

	CString
		csBase;

	CDaoRecordset	*rcdSerialNumber;


	// Open the database and recordset
	if ( !Open() )
		return ( FALSE );

	rcdSerialNumber = new CDaoRecordset ( &m_dbJobDatabase );
	rcdSerialNumber->Open ( AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_serial_number" );

	// start assuming record doesn't exist
	bSNRecordExists = FALSE;

	// Convert serialization base.

	switch ( nBase )
	{
		case BASE10:
			csBase = "Base10";
			break;

		case BASE16:
			csBase = "Base16";
			break;

		case BASE29:
			csBase = "Base29";
			break;

		case BASE31:
			csBase = "Base31";
			break;

		case BASE36:
			csBase = "Base36";
			break;

		default:
			csBase = "OTHER";
			break;
	}


	// get the number of records
	nCount = rcdSerialNumber->GetRecordCount();
	if ( nCount > 0 )
	{
		// move to the first record
		rcdSerialNumber->MoveFirst();

		// step through the records looking for the job
		while ( !rcdSerialNumber->IsEOF() && !bSNRecordExists )
		{
			// get the job name of the current record
			rcdSerialNumber->GetFieldValue( "Job_Name", var );
			csTemp = var.pbVal;
			
			// we found the job
			if ( csJobName == csTemp  )
			{

				// Update the serialization use.

				if ( bUseSerialization )
					csTemp = "YES";
				else
					csTemp = "NO";
				rcdSerialNumber->Edit();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdSerialNumber->SetFieldValue ( "Use_Serialization", p_chr_temp );
				rcdSerialNumber->Update();

				// Update the serialization base.

				rcdSerialNumber->Edit();
				p_chr_temp = csBase.GetBuffer ( csBase.GetLength() );
				rcdSerialNumber->SetFieldValue ( "Serialization_Base", p_chr_temp );
				rcdSerialNumber->Update();

				// Update the length of the serial number.

				csTemp.Format ( "%d", nLength );
				rcdSerialNumber->Edit();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdSerialNumber->SetFieldValue ( "Length", p_chr_temp );
				rcdSerialNumber->Update();

				// Update the serial number.

				csTemp = csSerialNumber;
				rcdSerialNumber->Edit();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdSerialNumber->SetFieldValue ( "Serial_number", p_chr_temp );
				rcdSerialNumber->Update();

				rcdSerialNumber->Edit();
				var.bVal=blnResetJulianDate;
				rcdSerialNumber->SetFieldValue ( "ResetOnJulian", var.bVal );
				rcdSerialNumber->Update();

				
				
				// We found the record.

				bSNRecordExists = TRUE;
			}
			
			// we didn't find the record, try the next one
			rcdSerialNumber->MoveNext();

		} // end while
	} // end if

	// if the job doesn't exist create it
	if ( !bSNRecordExists )
	{
		// No record for this job. Add it to the database.
		rcdSerialNumber->AddNew();
		
		csTemp = csJobName;

		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdSerialNumber->SetFieldValue ( "Job_Name", p_chr_temp );
		csTemp.ReleaseBuffer();

		
		if ( bUseSerialization )
			csTemp = "YES";
		else
			csTemp = "NO";
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdSerialNumber->SetFieldValue ( "Use_Serialization", p_chr_temp );
		csTemp.ReleaseBuffer();

		p_chr_temp = csBase.GetBuffer ( csBase.GetLength() );
		rcdSerialNumber->SetFieldValue ( "Serialization_Base", p_chr_temp );
		csBase.ReleaseBuffer();

		csTemp.Format ( "%d", nLength );
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdSerialNumber->SetFieldValue ( "Length", p_chr_temp );
		csTemp.ReleaseBuffer();

		csTemp = csSerialNumber;
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdSerialNumber->SetFieldValue ( "Serial_number", p_chr_temp );
		csTemp.ReleaseBuffer();


		rcdSerialNumber->Update();
	}

	// close recordset and delete object
	rcdSerialNumber->Close();
	if (rcdSerialNumber)  // do not delete NULL pointer
		delete rcdSerialNumber;

	// Close the database.
	Close();

	return (TRUE);
}



////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		RemoveTemplate
//
//	Description:
//		Get the printer template of the selected template.
//
//	Arguments:
//		Template name
//
//	Return:
//		Status.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::RemoveTemplate ( CString csTemplateName )
{
	int nCount;
	COleVariant var;
	CString csTemp = " ";
	CString csTemplate = "";

	// Ensure the template is not used by another job.
	if (!TemplateInUse(csTemplateName))
	{
		AfxMessageBox ( "This template is in use by another job. Unable to delete template." );
		return ( FALSE );
	}
	
	// Open the database.
	if ( !Open() )
		return ( FALSE );
	
	// look for the template
	CDaoRecordset	*rcdTemplate;
	BOOL			bTemplateFound = FALSE;
	BOOL			bReturnValue;

	rcdTemplate = new CDaoRecordset( &m_dbJobDatabase);
	
	csTemp = "Select * from tbl_templates";
	rcdTemplate->Open ( AFX_DAO_USE_DEFAULT_TYPE, csTemp );

	nCount = rcdTemplate->GetRecordCount();
	if ( nCount > 0 ) 
	{
		rcdTemplate->MoveFirst();

		while ( !rcdTemplate->IsEOF() )
		{
			rcdTemplate->GetFieldValue( "Template_Name", var );
			csTemp = var.pbVal;
			
			// Find the matching template name.
			if ( csTemplateName == csTemp )
			{	
				// Remove the record.
				rcdTemplate->Delete();
				break;
			}
			
			rcdTemplate->MoveNext();
		}
	
		rcdTemplate->Close();
		if (rcdTemplate)  // do not delete NULL pointer
			delete rcdTemplate;
		bReturnValue = TRUE;
	}
	else
	{
		AfxMessageBox ("There is no template data in the database. ");
		rcdTemplate->Close();
		if (rcdTemplate)  // do not delete NULL pointer
			delete rcdTemplate;
		bReturnValue = FALSE;
	}

	// Close the database.
	Close();
	
	return (bReturnValue);
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		TemplateInUse
//
//	Description:
//		Check to see if any jobs are using this template.
//
//	Arguments:
//		Template name.
//
//	Return:
//		Status.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::TemplateInUse ( CString csTemplateName )
{

	int nCount;
	COleVariant var;
	CString csTemp = " ";
	CString csJob = " ";
	CDaoRecordset	*rcdTemplate;

	BOOL
		bFound;

	// Open the database.
	if ( !Open() )
		return ( FALSE );
	
	// Get general job information.
	rcdTemplate = new CDaoRecordset( &m_dbJobDatabase );
	csTemp = "Select * from tbl_templates" ;   // CDaoRecordset does not like one-record recordset ? 

	rcdTemplate->Open ( AFX_DAO_USE_DEFAULT_TYPE, csTemp );
	
	nCount = rcdTemplate->GetRecordCount();

	if ( nCount < 1 )
	{

		AfxMessageBox ("There is no job information in the database. ");
		rcdTemplate->Close();
		delete rcdTemplate;
		return ( TRUE );
	}

	bFound = FALSE;
	if ( nCount > 0 )
	{
		rcdTemplate->MoveFirst();

		while ( !rcdTemplate->IsEOF() )
		{
			rcdTemplate->GetFieldValue ( "Template_Name", var );
			csTemp = var.pbVal;

			if ( csTemplateName == csTemp )
			{
				bFound = TRUE;
				break;
			}

			rcdTemplate->MoveNext();
		}
	}
	
	rcdTemplate->Close();
	if (rcdTemplate)  // do not delete NULL pointer
		delete rcdTemplate;

	// Close the database.
	Close();

	return ( bFound );
}

unsigned long CDatabase::GetFGBackGroundColor()
{

	COleVariant var;
	CDaoRecordset	*rcdTemplate;
	unsigned long lTemp;
	int nCount;


	// Open the database.
	if ( !Open() )
		return ( FALSE );
	
	// Get general job information.
	rcdTemplate = new CDaoRecordset( &m_dbJobDatabase );

	rcdTemplate->Open ( AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_system_config");
	
	nCount = rcdTemplate->GetRecordCount();

	if ( nCount < 1 )
	{

		AfxMessageBox ("There is no System configuration information in the database. ");
		rcdTemplate->Close();
		if (rcdTemplate)  // do not delete NULL pointer
			delete rcdTemplate;
		return ( TRUE );
	}

	rcdTemplate->MoveFirst();

	rcdTemplate->GetFieldValue ( "FGBackGroundColor", var );
	lTemp = (ULONG)var.lVal;
	

	
	rcdTemplate->Close();
	if (rcdTemplate)  // do not delete NULL pointer
		delete rcdTemplate;

	// Close the database.
	Close();
	 
	return lTemp;

}

unsigned long CDatabase::GetFGHighlightColor()
{

	COleVariant var;
	CDaoRecordset	*rcdTemplate;
	unsigned long lTemp;
	int nCount;


	// Open the database.
	if ( !Open() )
		return ( FALSE );
	
	// Get general job information.
	rcdTemplate = new CDaoRecordset( &m_dbJobDatabase );

	rcdTemplate->Open ( AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_system_config");
	
	nCount = rcdTemplate->GetRecordCount();

	if ( nCount < 1 )
	{

		AfxMessageBox ("There is no System configuration information in the database. ");
		rcdTemplate->Close();
		if (rcdTemplate)  // do not delete NULL pointer
			delete rcdTemplate;
		return ( TRUE );
	}

	rcdTemplate->MoveFirst();

	rcdTemplate->GetFieldValue ( "FGRowSelectColor", var );
	lTemp = (ULONG)var.lVal;
	

	
	rcdTemplate->Close();
	if (rcdTemplate)  // do not delete NULL pointer
		delete rcdTemplate;

	// Close the database.
	Close();
	 
	return lTemp;

}


BOOL CDatabase::CheckForReservedWord(CString csBuffer, CString *csFormat)
{


	COleVariant var;
	CDaoRecordset	*rcdReservedWord;
	int nCount;
	CString csSQLCmd;
	CString csTemp;
	BOOL blnRetStatus=FALSE;


	// Open the database.
	if ( !Open() )
		return ( FALSE );
	
	// Get general job information.
	rcdReservedWord = new CDaoRecordset( &m_dbJobDatabase );
	csSQLCmd = "Select * from tbl_Reserved_Words Where [Reserved Word]='"+ csBuffer + "'";
		      

	rcdReservedWord->Open ( AFX_DAO_USE_DEFAULT_TYPE,csSQLCmd);
	
	nCount = rcdReservedWord->GetRecordCount();

	if ( nCount < 1 )
	{
		blnRetStatus=FALSE;
	}
	else
	{
		blnRetStatus=TRUE;
		rcdReservedWord->GetFieldValue ( "[Required Format]", var );
		csTemp=var.pbVal;
		*csFormat = var.pbVal;
	}
	

	
	rcdReservedWord->Close();
	if (rcdReservedWord)  // do not delete NULL pointer
		delete rcdReservedWord;

	// Close the database.
	Close();
	 
	return blnRetStatus;

}



BOOL CDatabase::IsReservedWord(CString csBuffer)
{
	CDaoRecordset	*rcdReservedWord;
	int nCount;
	CString csSQLCmd;
	BOOL blnRetStatus=FALSE;


	// Open the database.
	if ( !Open() )
		return ( FALSE );
	
	// Get general job information.
	rcdReservedWord = new CDaoRecordset( &m_dbJobDatabase );

	csSQLCmd = "Select * from tbl_Reserved_Words Where [Reserved Word]='"+ csBuffer + "'";
		      

	rcdReservedWord->Open ( AFX_DAO_USE_DEFAULT_TYPE,csSQLCmd);
	
	nCount = rcdReservedWord->GetRecordCount();

	if ( nCount < 1 )
	{
		blnRetStatus=FALSE;
	}
	else
	{
		blnRetStatus=TRUE;
	}
	

	
	rcdReservedWord->Close();
	if (rcdReservedWord)  // do not delete NULL pointer
		delete rcdReservedWord;

	// Close the database.
	Close();
	 
	return blnRetStatus;

}

BOOL CDatabase::IsReservedWordFormatValid(CString csBuffer, CString csFormat)
{


	CDaoRecordset	*rcdReservedWord;
	int nCount;
	CString csSQLCmd;
	BOOL blnRetStatus;


	// Open the database.
	if ( !Open() )
		return ( FALSE );
	
	// Get general job information.
	rcdReservedWord = new CDaoRecordset( &m_dbJobDatabase );
	csSQLCmd = "Select * from tbl_Reserved_Words Where [Reserved Word]='"+ csBuffer + "'"
		        + " AND [Required Format]='" + csFormat + "'";
		      

	rcdReservedWord->Open ( AFX_DAO_USE_DEFAULT_TYPE,csSQLCmd);
	
	nCount = rcdReservedWord->GetRecordCount();

	if ( nCount < 1 )
	{
		blnRetStatus=FALSE;
	}
	else
	{
		blnRetStatus=TRUE;
	}
	

	
	rcdReservedWord->Close();
	if (rcdReservedWord)  // do not delete NULL pointer
		delete rcdReservedWord;

	// Close the database.
	Close();
	 
	return blnRetStatus;

}

BOOL CDatabase::VerifyData(CString csName, CString csValue)
{
BOOL blnRetVal;
CString csTemp;

	if (IsReservedWord(csName))
	{
		blnRetVal=VerifyDynamicData(csName, csValue);
	}
	else
	{
		blnRetVal=TRUE;
	}
	return blnRetVal;

}




BOOL CDatabase::VerifyDynamicData(CString csName, CString csValue)
{
BOOL blnRetVal;
CString csTemp;

	if (IsReservedWordFormatValid(csName,csValue))
	{
		blnRetVal=TRUE;
	}
	else
	{
		csTemp.LoadString(IDS_INVALID_RESERVED_WORD_VALUE);
		AfxMessageBox(csTemp+csName);
		blnRetVal=FALSE;
	}
	return blnRetVal;

}

BOOL CDatabase::VerifyJobAttributes( CJob * oJobInfo)
{

	if (oJobInfo->GetUseDataName1())
	{
		if (!VerifyData(oJobInfo->GetDataName1(),oJobInfo->GetDataValue1()))
		{
			return FALSE;
		}
	}

	if (oJobInfo->GetUseDataName2())
	{
		if (!VerifyData(oJobInfo->GetDataName2(),oJobInfo->GetDataValue2()))
		{
			return FALSE;
		}
	}

	if (oJobInfo->GetUseDataName3())
	{
		if (!VerifyData(oJobInfo->GetDataName3(),oJobInfo->GetDataValue3()))
		{
			return FALSE;
		}
	}

	if (oJobInfo->GetUseDataName4())
	{
		if (!VerifyData(oJobInfo->GetDataName4(),oJobInfo->GetDataValue4()))
		{
			return FALSE;
		}
	}

	if (oJobInfo->GetUseDataName5())
	{
		if (!VerifyData(oJobInfo->GetDataName5(),oJobInfo->GetDataValue5()))
		{
			return FALSE;
		}
	}

	return TRUE;

}

BOOL CDatabase::GetInputBits(CStringArray *csInputBits)
{
	int nCount,
		nIndex,
		nLastBitID;
	COleVariant var;
	CString csTemp = " ";
	CString csDesc = " ";

	CDaoRecordset	*rsPtr;


	// Open the database.

	if ( !Open() )
	{
		csTemp.LoadString(IDS_DATABASE_INIT_ERROR);
	    AfxMessageBox(csTemp);
		return ( FALSE );
	}

	rsPtr = new CDaoRecordset ( &m_dbJobDatabase );
	rsPtr->Open ( AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_DIO_InputBit_Assignments" );

	if (rsPtr->IsEOF())
	{
		rsPtr->Close();
		if (rsPtr)  // do not delete NULL pointer
			delete rsPtr;

		// Close the database.

		Close();

		return ( FALSE );

	}
	rsPtr->MoveLast();
	nCount = rsPtr->GetRecordCount();
	csInputBits->RemoveAll();
	nLastBitID=0;
	rsPtr->MoveFirst();
	nLastBitID=0;

	for (nIndex=0;nIndex<nCount;nIndex++)
	{

		if ( !rsPtr->IsEOF() )
		{
			rsPtr->GetFieldValue ( "BitNumber", var );
			nLastBitID = var.intVal;

   		    rsPtr->GetFieldValue ( "Name", var );
			csTemp = var.pbVal;
			
			if (csTemp=="")
			{
					csTemp.LoadString(IDS_ERROR_INPUT_BITS_DESC);
				    AfxMessageBox(csTemp);
					return FALSE;
			 }
			 Trace("[DIN] DSCR[%d]=%s",nIndex,csTemp);
			 csInputBits->Add (csTemp);
			
		}
	    rsPtr->MoveNext();
	}
	
	rsPtr->Close();
	if (rsPtr)  // do not delete NULL pointer
		delete rsPtr;

	// Close the database.

	Close();

	return ( TRUE );

}



BOOL CDatabase::GetOutputBits(CStringArray *csOutputBits)
{
	int nCount,
		nIndex,
		nLastBitID;

	COleVariant var;
	CString csTemp = " ";
	CString csDesc = " ";

	CDaoRecordset	*rsPtr;


	// Open the database.

	if ( !Open() )
	{
		csTemp.LoadString(IDS_DATABASE_INIT_ERROR);
	    AfxMessageBox(csTemp);
		return ( FALSE );
	}

	rsPtr = new CDaoRecordset ( &m_dbJobDatabase );
	rsPtr->Open ( AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_DIO_OutputBit_Assignments" );

	if (rsPtr->IsEOF())
	{
		rsPtr->Close();
		if (rsPtr)  // do not delete NULL pointer
			delete rsPtr;

		// Close the database.

		Close();

		return ( FALSE );

	}
	rsPtr->MoveLast();
	nCount = rsPtr->GetRecordCount();
	csOutputBits->RemoveAll();
	nLastBitID=0;
	rsPtr->MoveFirst();
	nLastBitID=0;

	
	for (nIndex=0;nIndex<nCount;nIndex++)
	{

		

		if ( !rsPtr->IsEOF() )
		{
			rsPtr->GetFieldValue ( "BitNumber", var );
			nLastBitID = var.intVal ;


		     rsPtr->GetFieldValue ( "Name", var );
		     csTemp = var.pbVal;
		     if (csTemp=="")
			 {
				csTemp.LoadString(IDS_ERROR_INPUT_BITS_DESC);
				AfxMessageBox(csTemp);
				return FALSE;
			 }
		     csOutputBits->Add (csTemp);
		
		}
		rsPtr->MoveNext();
	}
	
	rsPtr->Close();
	if (rsPtr)  // do not delete NULL pointer
		delete rsPtr;

	// Close the database.

	Close();

	return ( TRUE );

}


BOOL CDatabase::GetPointTypes(CStringArray *csPointTypes)
{
	COleVariant var;
	CString csTemp = " ";

	CDaoRecordset	*rsPtr;


	// Open the database.

	if ( !Open() )
	{
		csTemp.LoadString(IDS_DATABASE_INIT_ERROR);
	    AfxMessageBox(csTemp);
		return ( FALSE );
	}

	rsPtr = new CDaoRecordset ( &m_dbJobDatabase );
	rsPtr->Open ( AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_point" );

	if (rsPtr->IsEOF())
	{
		rsPtr->Close();
		if (rsPtr)  // do not delete NULL pointer
			delete rsPtr;

		// Close the database.

		Close();

		return ( FALSE );

	}
	rsPtr->MoveFirst();
	csPointTypes->RemoveAll();

	while ( !rsPtr->IsEOF() )
	{
		rsPtr->GetFieldValue ( "Point_Name", var );
		csTemp = var.pbVal;
		csPointTypes->Add (csTemp);
		rsPtr->MoveNext();
	}
	
	rsPtr->Close();
	if (rsPtr)  // do not delete NULL pointer
		delete rsPtr;

	// Close the database.

	Close();

	return ( TRUE );

}


BOOL CDatabase::GetPointAttributes(CString csPointName, CString *csXPos, CString *csYPos, CString *csRot)
{
	COleVariant var;
	CString csTemp = " ";
	CString csSQLCmd=" ";
	CDaoRecordset	*rsPtr;


	// Open the database.

	if ( !Open() )
	{
		csTemp.LoadString(IDS_DATABASE_INIT_ERROR);
	    AfxMessageBox(csTemp);
		return ( FALSE );
	}
	csSQLCmd="Select * from tbl_point Where Point_Name = '" + csPointName +"'";
	rsPtr = new CDaoRecordset ( &m_dbJobDatabase );
	rsPtr->Open ( AFX_DAO_USE_DEFAULT_TYPE, csSQLCmd);

	if (rsPtr->IsEOF())
	{
		rsPtr->Close();
		if (rsPtr)  // do not delete NULL pointer
			delete rsPtr;

		// Close the database.

		Close();

		return ( FALSE );

	}

	rsPtr->GetFieldValue ( "X", var );
	csTemp = var.pbVal;
	*csXPos=csTemp;

	rsPtr->GetFieldValue ( "Y", var );
	csTemp = var.pbVal;
	*csYPos=csTemp;

	rsPtr->GetFieldValue ( "Rotation", var );
	csTemp = var.pbVal;
	*csRot=csTemp;

	
	rsPtr->Close();
	if (rsPtr)  // do not delete NULL pointer
		delete rsPtr;

	// Close the database.

	Close();

	return ( TRUE );

}

CString CDatabase::GetLastErrorMsg()
{
	return m_csErrorMsg;

}

void CDatabase::SetLastErrorMsg(CString csMessage)
{
	m_csErrorMsg=csMessage;

}


BOOL CDatabase::IsTemplateActive(CString csTemplateName)
{
	COleVariant var;
	CString csTemp = " ";
	CString csSQLCmd=" ";
	CDaoRecordset	*rsPtr;

	Trace(" Checking for Active Template");	

	// Open the database.

	if ( !Open() )
	{
		csTemp.LoadString(IDS_DATABASE_INIT_ERROR);
	    AfxMessageBox(csTemp);
		return ( FALSE );
	}
	csSQLCmd="Select * from tbl_job ";
	
	rsPtr = new CDaoRecordset ( &m_dbJobDatabase );
	rsPtr->Open ( AFX_DAO_USE_DEFAULT_TYPE, csSQLCmd);

	if (rsPtr->IsEOF())
	{
		rsPtr->Close();
		if (rsPtr)  // do not delete NULL pointer
			delete rsPtr;
		// Close the database.
		Close();
		return ( FALSE );

	}


	rsPtr->MoveFirst();

	while ( !rsPtr->IsEOF() )
	{
		rsPtr->GetFieldValue ( "Placement_Attributes", var );
		csTemp = var.pbVal;
		if (csTemp.Find(csTemplateName)!=-1)
		{
			rsPtr->Close();
			if (rsPtr)  // do not delete NULL pointer
				delete rsPtr;
			// Close the database.
			Close();
			return ( TRUE );
		}
		rsPtr->MoveNext();
	}
	
	rsPtr->Close();
	if (rsPtr)  // do not delete NULL pointer
		delete rsPtr;
	

	// Close the database.

	Close();

	return ( FALSE );

}


BOOL CDatabase::ChkForShiftChanges(CString csJobName)
{
	COleVariant var;
	CString csTemp = " ";
	CString csSQLCmd=" ";
	CDaoRecordset	*rsPtr;

	Trace(" Checking for Job Name with Serial ID");	

	// Open the database.

	if ( !Open() )
	{
		csTemp.LoadString(IDS_DATABASE_INIT_ERROR);
	    AfxMessageBox(csTemp);
		return ( FALSE );
	}
	csSQLCmd="Select * from tbl_job ";
	
	rsPtr = new CDaoRecordset ( &m_dbJobDatabase );
	rsPtr->Open ( AFX_DAO_USE_DEFAULT_TYPE, csSQLCmd);

	if (rsPtr->IsEOF())
	{
		rsPtr->Close();
		if (rsPtr)  // do not delete NULL pointer
			delete rsPtr;
		// Close the database.
		Close();
		return ( FALSE );

	}


	rsPtr->MoveFirst();

	while ( !rsPtr->IsEOF() )
	{

		rsPtr->GetFieldValue ( "Job_Name", var );
		csTemp = var.pbVal;

		if (csTemp==csJobName)
		{
			rsPtr->GetFieldValue ( "Data_Name1", var );
			csTemp = var.pbVal;
			if (csTemp.Find("Shift ID")!=-1)
			{
				rsPtr->GetFieldValue ( "Use_Data_Name1", var );
				csTemp = var.pbVal;
				if (csTemp=="YES")
				{
					rsPtr->Close();
					if (rsPtr)  // do not delete NULL pointer
						delete rsPtr;
					// Close the database.
					Close();
					return ( TRUE );
				}
			}

			rsPtr->GetFieldValue ( "Data_Name2", var );
			csTemp = var.pbVal;
			if (csTemp.Find("Shift ID")!=-1)
			{
				rsPtr->GetFieldValue ( "Use_Data_Name2", var );
				csTemp = var.pbVal;
				if (csTemp=="YES")
				{
					rsPtr->Close();
					if (rsPtr)  // do not delete NULL pointer
						delete rsPtr;
					// Close the database.
					Close();
					return ( TRUE );
				}
			}

			rsPtr->GetFieldValue ( "Data_Name3", var );
			csTemp = var.pbVal;
			if (csTemp.Find("Shift ID")!=-1)
			{
				rsPtr->GetFieldValue ( "Use_Data_Name3", var );
				csTemp = var.pbVal;
				if (csTemp=="YES")
				{
					rsPtr->Close();
					if (rsPtr)  // do not delete NULL pointer
						delete rsPtr;
					// Close the database.
					Close();
					return ( TRUE );
				}
			}
		
			rsPtr->GetFieldValue ( "Data_Name4", var );
			csTemp = var.pbVal;
			if (csTemp.Find("Shift ID")!=-1)
			{
				rsPtr->GetFieldValue ( "Use_Data_Name4", var );
				csTemp = var.pbVal;
				if (csTemp=="YES")
				{
					rsPtr->Close();
					if (rsPtr)  // do not delete NULL pointer
						delete rsPtr;
					// Close the database.
					Close();
					return ( TRUE );
				}
			}
			rsPtr->GetFieldValue ( "Data_Name5", var );
			csTemp = var.pbVal;
			if (csTemp.Find("Shift ID")!=-1)
			{
				rsPtr->GetFieldValue ( "Use_Data_Name5", var );
				csTemp = var.pbVal;
				if (csTemp=="YES")
				{
					rsPtr->Close();
					if (rsPtr)  // do not delete NULL pointer
						delete rsPtr;
					// Close the database.
					Close();
					return ( TRUE );
				}
			}
		
		}
		rsPtr->MoveNext();
	}
	
	rsPtr->Close();
	if (rsPtr)  // do not delete NULL pointer
		delete rsPtr;
	

	// Close the database.

	Close();

	return ( FALSE );

}


int CDatabase::GetLastShiftID(CString csJobName)
{
	COleVariant var;
	CString csTemp = " ";
	CString csSQLCmd=" ";
	CDaoRecordset	*rsPtr;

	Trace(" Checking for Last Shift ID");	

	// Open the database.

	if ( !Open() )
	{
		csTemp.LoadString(IDS_DATABASE_INIT_ERROR);
	    AfxMessageBox(csTemp);
		return 0 ;
	}
	csSQLCmd="Select * from tbl_Shift_Info Where [JobName] = '"+csJobName+"'";
	
	rsPtr = new CDaoRecordset ( &m_dbJobDatabase );
	rsPtr->Open ( AFX_DAO_USE_DEFAULT_TYPE, csSQLCmd);

	if (rsPtr->IsEOF())
	{

		rsPtr->Close();
		if (rsPtr)  // do not delete NULL pointer
			delete rsPtr;
	
		// Close the database.

		Close();
		
		return 0;
	}



	rsPtr->GetFieldValue ( "LastShiftID", var );
	csTemp = var.pbVal;
	
	rsPtr->Close();
	if (rsPtr)  // do not delete NULL pointer
		delete rsPtr;
	
	if (csTemp=="")
		csTemp="0";
	// Close the database.

	Close();

	return atoi(csTemp);

}

void CDatabase::SetLastShiftID(CString csJobName, CString csShiftID)
{
	COleVariant var;
	CString csTemp = " ";
	CString csSQLCmd=" ";
	CDaoRecordset	*rsPtr;
	char			*p_chr_temp;

	Trace(" Setting Last Shift ID");	

	// Open the database.

	if ( !Open() )
	{
		csTemp.LoadString(IDS_DATABASE_INIT_ERROR);
	    AfxMessageBox(csTemp);
		return;
	}
	csSQLCmd="Select * from tbl_Shift_Info  Where [JobName] = '"+csJobName+"'";
	
	rsPtr = new CDaoRecordset ( &m_dbJobDatabase );
	rsPtr->Open ( AFX_DAO_USE_DEFAULT_TYPE, csSQLCmd);

	if( !rsPtr->IsEOF() )
	{
		rsPtr->Edit();
			
		p_chr_temp = csShiftID.GetBuffer ( csShiftID.GetLength() );
		rsPtr->SetFieldValue ( "LastShiftID", p_chr_temp );

		rsPtr->Update(); 
	}
	else
	{

		rsPtr->AddNew();

		p_chr_temp = csJobName.GetBuffer ( csJobName.GetLength() );
		rsPtr->SetFieldValue ( "JobName", p_chr_temp );

		
		p_chr_temp = csShiftID.GetBuffer ( csShiftID.GetLength() );
		rsPtr->SetFieldValue ( "LastShiftID", p_chr_temp );

		rsPtr->Update(); 

	}


	rsPtr->Close();
	if (rsPtr)  // do not delete NULL pointer
		delete rsPtr;
	
	// Close the database.

	Close();


}


BOOL CDatabase::SetLastJulianDate ( CString csJobName, CString csSerialNumber, CString csLastJulianDate )
{

	int nCount;
	COleVariant var;
	CString csTemp = " ";
	BOOL bGoodFind;

	char *p_chr_temp;

	CDaoRecordset	*rcdSerialNumber;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdSerialNumber = new CDaoRecordset ( &m_dbJobDatabase );
	rcdSerialNumber->Open ( AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_serial_number" );

	nCount = rcdSerialNumber->GetRecordCount();


	if ( nCount > 0 )
	{
		rcdSerialNumber->MoveFirst();

		bGoodFind = FALSE;

		while ( !rcdSerialNumber->IsEOF() && !bGoodFind )
		{
			rcdSerialNumber->GetFieldValue( "Job_Name", var );
			csTemp = var.pbVal;
			if ( csJobName == csTemp  )
			{


				rcdSerialNumber->Edit();
				csTemp = csSerialNumber;
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdSerialNumber->SetFieldValue ( "Serial_Number", p_chr_temp );


				csTemp = csLastJulianDate;
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdSerialNumber->SetFieldValue ( "LastJulianDate", p_chr_temp );
				rcdSerialNumber->Update();

				bGoodFind = TRUE;
				break;
			}
			
			rcdSerialNumber->MoveNext();
		}
	}
	else
		bGoodFind = FALSE;
	
	rcdSerialNumber->Close();
	if (rcdSerialNumber)  // do not delete NULL pointer
		delete rcdSerialNumber;

	// Close the database.

	Close();

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_NO_SN_DATABASE );
		AfxMessageBox ( csTemp );
	}

	return ( bGoodFind );

}


/////////////////////////////////////////////////////////////////////////////
//
//	Name:
//		CheckPositionFormat
//
//	Description:		
//		Check the format of the position string.
//
//	Arguments:
//		Position string
//	
//	Returns:
//		Status
//
//	Called By:
//
//////////////////////////////////////////////////////////////////////////////

BOOL CDatabase::CheckPositionFormat ( CString csPosition )
{

	CUtilities oUtil;
	int
		nLength;

	CString
		csRot;


	// The position must have the format of x,y;rot
	//		where:
	//			x = 6 digits,
	//			y = 6 digits,
	//			rot = 0 or 90.

	nLength = csPosition.GetLength();

	if ( csPosition[6] != ',' || csPosition[13] != ';' )
		return ( FALSE );

	csRot = csPosition.Right ( nLength - 14 );

	if ( !oUtil.IsNumeric ( csPosition.Left ( 6 ) ) || !oUtil.IsNumeric ( csPosition.Mid ( 7, 6 ) ) ||
		  !oUtil.IsNumeric ( csRot )  || ( csRot != "0" && csRot != "00" && csRot != "90" ) )
		return ( FALSE );

	return ( TRUE );

}

CString CDatabase::GetDisplayedValue(CString csType, CString csDefault)
{
BOOL blnReservedWord;
CString csFormat,
		csReturn;
	CUtilities oUtil;

	blnReservedWord=CheckForReservedWord(csType, &csFormat);
	if (blnReservedWord)
	{
		if (csType=="Julian Date")
		{
			csReturn=oUtil.GetDateCode(csFormat);
		}
		else if (csType=="Year Code")
		{
			csReturn=oUtil.GetDateCode(csFormat);
		}
		
		else if (csType=="Shift ID")
		{
			csReturn=GetShiftID();
		}

		csReturn = csType +"\t"+csReturn;


	}
	else
	{
		 csReturn= csType+"\t"+csDefault;
	}

	return csReturn;

	
}

CString CDatabase::GetPrintedValue(CString csType, CString csDefault)
{
BOOL blnReservedWord;
CString csFormat,
		csReturn;
	CUtilities oUtil;


	blnReservedWord=CheckForReservedWord(csType, &csFormat);
	if (blnReservedWord)
	{
		if (csType=="Julian Date")
		{
			csReturn=oUtil.GetDateCode(csFormat);
		}
		else if (csType=="Year Code")
		{
			csReturn=oUtil.GetDateCode(csFormat);
		}
		else if (csType=="Shift ID")
		{
			csReturn=GetShiftID();
		}

	}
	else
	{
		 csReturn= csDefault;
	}

	return csReturn;

	
}


BOOL CDatabase::VerifyReservedWordValue(CString csType, CString csUserValue)
{
BOOL blnRetStatus;
CString csFormat,
		csReturn;


	blnRetStatus=CheckForReservedWord(csType, &csFormat);
	if (blnRetStatus)
	{
		if (!(csUserValue==csFormat))
			blnRetStatus=FALSE;
	}
	return blnRetStatus;
	
}

CString CDatabase::GetShiftID()
{
CTime tmValue;
int nHour;
CString csRetValue;


	tmValue=CTime::GetCurrentTime() ; 
	
	nHour=tmValue.GetHour();
	
	if (nHour<6)
	{
		csRetValue="3";

	}
	else if ((nHour>=6)&&(nHour<14))
	{
		csRetValue="1";


	}
	else if ((nHour>=14)&&(nHour<22))
	{
		csRetValue="2";


	}
	else
	{
		csRetValue="3";
	}

	return csRetValue;
}


CSysDBase::CSysDBase()
{

}

CSysDBase::~CSysDBase()
{

}




BOOL CDatabase::GetSNAttributes ( CString csJobName, 
										  BOOL *bUseSerialization,
										  int *nBase,
										  int *nLength,
										  CString *csSerialNumber,
										  BOOL *blnUseChkDigit,
										  CString *csCheckDigitSource,
										  CString *csCheckDigitType)
										  
{

	int nCount;
	COleVariant var;
	CString csTemp = " ";
	CString csSQLCmd;

	BOOL bGoodFind;

	CDaoRecordset	*rcdSerialNumber;


	// Open the database.

	if ( !Open() )
		return ( FALSE );


	csSQLCmd=CString("Select * from tbl_serial_number where Job_Name = '") +
		     csJobName +
			 CString("'");

	rcdSerialNumber = new CDaoRecordset ( &m_dbJobDatabase );
	rcdSerialNumber->Open ( AFX_DAO_USE_DEFAULT_TYPE,csSQLCmd);

	if (!rcdSerialNumber->IsEOF())
	{
		rcdSerialNumber->MoveLast();
		rcdSerialNumber->MoveFirst();
	}
	else
	{
		csTemp.LoadString ( IDS_NO_SN_DATABASE );
		AfxMessageBox ( csTemp );
		return FALSE;


	}

	nCount = rcdSerialNumber->GetRecordCount();

	
	if ( nCount > 0 )
	{
		bGoodFind=TRUE;
		rcdSerialNumber->GetFieldValue( "Job_Name", var );
		csTemp = var.pbVal;

		rcdSerialNumber->GetFieldValue ( "Use_Serialization", var );
		csTemp = var.pbVal;
		if ( csTemp.CompareNoCase ( "YES" ) == 0 )
			*bUseSerialization = TRUE;
		else
			*bUseSerialization = FALSE;

		rcdSerialNumber->GetFieldValue ( "Serialization_Base", var );
		csTemp = var.pbVal;
		if ( csTemp.CompareNoCase ( "Base10" ) == 0 )
			*nBase = BASE10;
		else
		if ( csTemp.CompareNoCase ( "Base16" ) == 0 )
				*nBase = BASE16;
			else
				if (csTemp.CompareNoCase( "Base29" ) == 0 )
					*nBase = BASE29;
				else
					if ( csTemp.CompareNoCase ( "Base31" ) == 0 )
						*nBase = BASE31;
					else
						if ( csTemp.CompareNoCase ( "Base36" ) == 0 )
							*nBase = BASE36;
						else
							*nBase = OTHER;

		rcdSerialNumber->GetFieldValue ( "Length", var );
		csTemp = var.pbVal;
		*nLength = atoi ( csTemp );

		rcdSerialNumber->GetFieldValue ( "Serial_Number", var );
		csTemp = var.pbVal;
		*csSerialNumber = csTemp;




		rcdSerialNumber->GetFieldValue ( "UseCheckDigit", var );
		if ( var.vt != VT_NULL )
		{
			*blnUseChkDigit=var.boolVal;
		}
		else
		{
			*blnUseChkDigit=FALSE;
		}

		rcdSerialNumber->GetFieldValue ( "CheckDigitFrom", var );
		if ( var.vt != VT_NULL )
		{
			csTemp = var.pbVal;
			*csCheckDigitSource=csTemp;
		}
		else
		{
			*csCheckDigitSource="Not Defined";
		}

		rcdSerialNumber->GetFieldValue ( "ChkDgtType", var );
		if ( var.vt != VT_NULL )
		{
			csTemp = var.pbVal;
			*csCheckDigitType=csTemp;
		}
		else
		{
			*csCheckDigitType="Not Defined";
		}
	
	
	}
	else
		bGoodFind = FALSE;
	
	rcdSerialNumber->Close();
	if (rcdSerialNumber)  // do not delete NULL pointer
		delete rcdSerialNumber;

	// Close the database.

	Close();

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_NO_SN_DATABASE );
		AfxMessageBox ( csTemp );
	}

	return ( bGoodFind );

}



BOOL CDatabase::SetSNAttributes ( CString csJobName, 
											 BOOL bUseSerialization,
											 int nBase,
											 int nLength,
											 CString csSerialNumber,
											 BOOL blnUseCheckDigit,
											 CString csCheckDigitType,
											 CString csCheckDigitSource)
{

	int nCount;
	COleVariant var;
	CString csTemp = " ";
	BOOL bSNRecordExists;
	char *p_chr_temp;

	CString
		csBase,
		csSQLCmd;

	CDaoRecordset	*rcdSerialNumber;


	// Open the database and recordset
	if ( !Open() )
		return ( FALSE );

	csSQLCmd=CString("Select * from tbl_serial_number where Job_Name = '") +
		     csJobName +
			 CString("'");

	rcdSerialNumber = new CDaoRecordset ( &m_dbJobDatabase );
	rcdSerialNumber->Open ( AFX_DAO_USE_DEFAULT_TYPE,csSQLCmd);

	if (!rcdSerialNumber->IsEOF())
	{
		rcdSerialNumber->MoveLast();
		rcdSerialNumber->MoveFirst();
	}
	else
	{
		bSNRecordExists = FALSE;

	}


	// Convert serialization base.

	switch ( nBase )
	{
		case BASE10:
			csBase = "Base10";
			break;

		case BASE16:
			csBase = "Base16";
			break;

		case BASE29:
			csBase = "Base29";
			break;

		case BASE31:
			csBase = "Base31";
			break;

		case BASE36:
			csBase = "Base36";
			break;

		default:
			csBase = "OTHER";
			break;
	}


	// get the number of records
	nCount = rcdSerialNumber->GetRecordCount();
	if ( nCount > 0 )
	{
		bSNRecordExists = TRUE;

			
		// Update the serialization use.

		if ( bUseSerialization )
			csTemp = "YES";
		else
			csTemp = "NO";
		rcdSerialNumber->Edit();
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdSerialNumber->SetFieldValue ( "Use_Serialization", p_chr_temp );
		rcdSerialNumber->Update();

		// Update the serialization base.

		rcdSerialNumber->Edit();
		p_chr_temp = csBase.GetBuffer ( csBase.GetLength() );
		rcdSerialNumber->SetFieldValue ( "Serialization_Base", p_chr_temp );
		rcdSerialNumber->Update();

		// Update the length of the serial number.

		csTemp.Format ( "%d", nLength );
		rcdSerialNumber->Edit();
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdSerialNumber->SetFieldValue ( "Length", p_chr_temp );
		rcdSerialNumber->Update();

		// Update the serial number.

		csTemp = csSerialNumber;
		rcdSerialNumber->Edit();
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdSerialNumber->SetFieldValue ( "Serial_number", p_chr_temp );
		rcdSerialNumber->Update();


//Add code for handling check digits		
		
		rcdSerialNumber->Edit();
		var.boolVal=blnUseCheckDigit;
		rcdSerialNumber->SetFieldValue ( "UseCheckDigit", var.boolVal );
		rcdSerialNumber->Update();


		csTemp = csCheckDigitType;
		rcdSerialNumber->Edit();
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdSerialNumber->SetFieldValue ( "ChkDgtType", p_chr_temp );
		rcdSerialNumber->Update();
	
		csTemp = csCheckDigitSource;
		rcdSerialNumber->Edit();
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdSerialNumber->SetFieldValue ( "CheckDigitFrom", p_chr_temp );
		rcdSerialNumber->Update();
	
	
	
	} // end if

	// if the job doesn't exist create it
	if ( !bSNRecordExists )
	{
		// No record for this job. Add it to the database.
		rcdSerialNumber->AddNew();
		
		csTemp = csJobName;

		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdSerialNumber->SetFieldValue ( "Job_Name", p_chr_temp );
		csTemp.ReleaseBuffer();

		
		if ( bUseSerialization )
			csTemp = "YES";
		else
			csTemp = "NO";
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdSerialNumber->SetFieldValue ( "Use_Serialization", p_chr_temp );
		csTemp.ReleaseBuffer();

		p_chr_temp = csBase.GetBuffer ( csBase.GetLength() );
		rcdSerialNumber->SetFieldValue ( "Serialization_Base", p_chr_temp );
		csBase.ReleaseBuffer();

		csTemp.Format ( "%d", nLength );
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdSerialNumber->SetFieldValue ( "Length", p_chr_temp );
		csTemp.ReleaseBuffer();

		csTemp = csSerialNumber;
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdSerialNumber->SetFieldValue ( "Serial_number", p_chr_temp );
		csTemp.ReleaseBuffer();


//Add code for handling check digits		
		
		var.boolVal=blnUseCheckDigit;
		rcdSerialNumber->SetFieldValue ( "UseCheckDigit", var.boolVal );


		csTemp = csCheckDigitType;
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdSerialNumber->SetFieldValue ( "ChkDgtType", p_chr_temp );
		csTemp.ReleaseBuffer();	


		csTemp = csCheckDigitSource;
		p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
		rcdSerialNumber->SetFieldValue ( "CheckDigitFrom", p_chr_temp );
		csTemp.ReleaseBuffer();	


		rcdSerialNumber->Update();
	}

	// close recordset and delete object
	rcdSerialNumber->Close();
	if (rcdSerialNumber)  // do not delete NULL pointer
		delete rcdSerialNumber;

	// Close the database.
	Close();

	return (TRUE);
}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		Initialize
//
//	Description:
//		Open the job database. Check for existance. Close the database.
//
//	Arguments:
//		None.
//
//	Return:
//		Status.
//
//	Called by:
//		CApplicatorControl::Initialize
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CSysDBase::Initialize ( void ) 
{

	CString
		csTemp;

	Trace("[MachineState] MS= Initializing Database SubSystem");	

	m_bInitialized = TRUE;

	TRY
	{
		m_dbJobDatabase.Open ( "c:\\computype\\database\\JobAdmin.mdb" );
		m_dbJobDatabase.Close ();
	} 
	CATCH_ALL(e)
	{
		csTemp.LoadString ( IDS_NO_DATABASE );
		SetLastErrorMsg(csTemp);
		AfxMessageBox( csTemp );
		m_bInitialized=FALSE;

		return FALSE;
	}
	END_CATCH_ALL

	return ( m_bInitialized );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		Open
//
//	Description:
//		Open the job database.
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

BOOL CSysDBase::Open ( void )  
{
static int nRepeatCount=0;
	CString csTemp;
	


	if ( !m_bInitialized )
	{
		csTemp.LoadString ( IDS_INIT_DATABASE_ERR );
		AfxMessageBox ( csTemp );

		return ( FALSE );
	}
	TRY
	{
		if (m_dbJobDatabase.IsOpen())
			m_dbJobDatabase.Close(); 
		m_dbJobDatabase.Open ( "c:\\computype\\database\\JobAdmin.mdb" );
	} 
	CATCH_ALL(e)
	{
		nRepeatCount+=1;

		if (nRepeatCount>3)
		{
			TCHAR   szCause[255];

 			e->GetErrorMessage(szCause,255); 
			csTemp.LoadString ( IDS_NO_DATABASE );
			AfxMessageBox ( csTemp );
			return FALSE;

		}
		else
		{
			if (m_dbJobDatabase.IsOpen())
				m_dbJobDatabase.Close(); 

			m_dbJobDatabase.m_pWorkspace->RepairDatabase("c:\\computype\\database\\JobAdmin.mdb"); 
			Open();	
		}

	
	}
	END_CATCH_ALL

	return ( TRUE );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		Close
//
//	Description:
//		Close the job database.
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

void CSysDBase::Close ( void ) 
{

	m_dbJobDatabase.Close ();

}



CString CSysDBase::GetLastErrorMsg()
{
	return m_csErrorMsg;

}

void CSysDBase::SetLastErrorMsg(CString csMessage)
{
	m_csErrorMsg=csMessage;

}



