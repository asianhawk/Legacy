// Database.cpp: implementation of the CDatabase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSSysDBase.h"
#include "trace.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSysDBase::CSysDBase()
{

}

CSysDBase::~CSysDBase()
{

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

	TRY
	{
		m_dbJobDatabase.Open ( "c:\\computype\\database\\Statistics.mdb" );
		m_dbJobDatabase.Close ();
	} 
	CATCH_ALL(e)
	{

		csTemp.LoadString ( IDS_NO_STATISTICAL_DATABASE);
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

