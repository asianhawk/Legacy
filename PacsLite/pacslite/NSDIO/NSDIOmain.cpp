// CDioInput.cpp: implementation of the CDioInput class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "PACS.h"
#include "NSDIOmain.h"
#include "trace.h"

#include <windows.h>
#include "dio.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



CDIODriver::CDIODriver()
{
}

CDIODriver::~CDIODriver()
{

}

   
BOOL CDIODriver::ReadInputLong(unsigned long *lng_read)
{
   return DIOReadLong(privbase,lng_read);
}
   
BOOL CDIODriver::ReadInputArray(unsigned long lng_array[])
{
   return DIOReadArray(privbase,lng_array);
}

BOOL CDIODriver::WriteOutputLong(unsigned long lng_write)
{
   return DIOWriteLong(privbase,lng_write);
}

BOOL CDIODriver::WriteOutputArray(unsigned long lng_array[])
{
   return DIOWriteArray(privbase,lng_array);
}


BOOL CDIODriver::Initialize(unsigned long base)
{
  privbase = base;
  return TRUE;
}












//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDioInput::CDioInput()
{
}

CDioInput::~CDioInput()
{

}

BOOL CDioInput::Initialize ( int nAddress )
{
int nBitNumber;	
	
	m_nBaseAddress = nAddress;

	m_bInit = TRUE;
	nBitNumber=0;

	m_bInit = m_oDIO.Initialize ( m_nBaseAddress );
	m_bInit = m_oDIO.ReadInputArray(m_ulg_input_array);



	if ( m_bInit == FALSE )
	{

		AfxMessageBox ( "There is problem in reading from the digital input board." );
		return FALSE;
	}

	for (nBitNumber=0;nBitNumber<32;nBitNumber++)
		TrueState[nBitNumber]=TRUE;  // i.e. true is set high
									 // or a high is read as true.
	SetPowerOnBit();
	SetPrinterReadyBit();
	SetPartPresentBit();
	SetLabelAppliedBit();
	SetStartButtonBit();
	SetStopButtonBit();

	return TRUE;
}


BOOL CDioInput::ClearArray()
{
	int i;

	for (i = 0; i< c_array_length; i++)
		m_ulg_input_array[i] = 0;
	
	return TRUE;
}

BOOL CDioInput::ReadInputArray()
{

	BOOL bGoodRead;

	ClearArray();
	bGoodRead = m_oDIO.ReadInputArray(m_ulg_input_array);

	return ( bGoodRead );
}


BOOL CDioInput::IsPowerOn()
{
BOOL blnRetState,
	 blnInputState;

    blnInputState= m_ulg_input_array[GetPowerOnBit()];

	if (TrueState[GetPowerOnBit()])
	{
		blnRetState=blnInputState;
	}
	else
	{
		blnRetState=!blnInputState;
	}
	return blnRetState;



}


BOOL CDioInput::IsPrinterReady()
{
BOOL blnRetState,
	 blnInputState;
   blnInputState= m_ulg_input_array[GetPrinterReadyBit()];

	if (TrueState[GetPrinterReadyBit()])
	{
		blnRetState=blnInputState;
	}
	else
	{
		blnRetState=!blnInputState;
	}
	return blnRetState;
}


BOOL CDioInput::IsPartPresent()
{

BOOL blnRetState,
	 blnInputState;

    blnInputState= m_ulg_input_array[GetPartPresentBit()];

	if (TrueState[GetPartPresentBit()])
	{
		blnRetState=blnInputState;
	}
	else
	{
		blnRetState=!blnInputState;
	}
	return blnRetState;



}


BOOL CDioInput::IsLabelApplied()
{

BOOL blnRetState,
	 blnInputState;

    blnInputState= m_ulg_input_array[GetLabelAppliedBit()];

	if (TrueState[GetLabelAppliedBit()])
	{
		blnRetState=blnInputState;
	}
	else
	{
		blnRetState=!blnInputState;
	}
	return blnRetState;


}


void CDioInput::SetPowerOnBit()
{

	int nCount;
	COleVariant var;
	CString csSQLCmd;
	BOOL blnTrueState;

	CDaoRecordset	*rsPtr;


	// Open the database.

	if ( !Open() )
		return ;

	csSQLCmd = CString("Select * from tbl_DIO_InputBit_Assignments ")+
		       CString("Where Name = ")+
			   CString("'PowerOn'");

	rsPtr = new CDaoRecordset ( &m_dbJobDatabase );
	rsPtr->Open ( AFX_DAO_USE_DEFAULT_TYPE, csSQLCmd);

	nCount = rsPtr->GetRecordCount();
	if (nCount!=1)
	{
		AfxMessageBox("Power On Bit Number Not Defined");
		return;
	}
		
	rsPtr->GetFieldValue ( "BitNumber", var );
	m_nPowerOn_Bit = var.intVal;
	
	rsPtr->GetFieldValue ( "BitNumber", var );
	m_nPowerOn_Bit = var.intVal;
	
	rsPtr->GetFieldValue ( "DefaultTrueState", var );
	blnTrueState = var.bVal; 

	TrueState[m_nPowerOn_Bit]=blnTrueState;
	
	rsPtr->Close();
	delete rsPtr;

	// Close the database.

	Close();



}


int CDioInput::GetPowerOnBit()
{
	return m_nPowerOn_Bit;
}


void CDioInput::SetPrinterReadyBit()
{

	int nCount;
	COleVariant var;
	CString csSQLCmd;
	BOOL blnTrueState;
	

	CDaoRecordset	*rsPtr;


	// Open the database.

	if ( !Open() )
		return ;

	csSQLCmd = CString("Select * from tbl_DIO_InputBit_Assignments ")+
		       CString("Where Name = ")+
			   CString("'PrinterReady'");

	rsPtr = new CDaoRecordset ( &m_dbJobDatabase );
	rsPtr->Open ( AFX_DAO_USE_DEFAULT_TYPE, csSQLCmd);

	nCount = rsPtr->GetRecordCount();
	if (nCount!=1)
	{
		AfxMessageBox("Printer Ready Bit Number Not Defined");
		return;
	}
		
	rsPtr->GetFieldValue ( "BitNumber", var );
	m_nPrinterReady_Bit = var.intVal;
			
	rsPtr->GetFieldValue ( "DefaultTrueState", var );
	blnTrueState = var.bVal; 

	TrueState[m_nPrinterReady_Bit]=blnTrueState;
	
	rsPtr->Close();
	delete rsPtr;

	// Close the database.

	Close();



}


int CDioInput::GetPrinterReadyBit()
{
	return m_nPrinterReady_Bit;
}


void CDioInput::SetPartPresentBit()
{

	int nCount;
	COleVariant var;
	CString csSQLCmd;
	BOOL blnTrueState;

	CDaoRecordset	*rsPtr;


	// Open the database.

	if ( !Open() )
		return ;

	csSQLCmd = CString("Select * from tbl_DIO_InputBit_Assignments ")+
		       CString("Where Name = ")+
			   CString("'PartPresent'");

	rsPtr = new CDaoRecordset ( &m_dbJobDatabase );
	rsPtr->Open ( AFX_DAO_USE_DEFAULT_TYPE, csSQLCmd);

	nCount = rsPtr->GetRecordCount();
	if (nCount!=1)
	{
		AfxMessageBox("Part Present Bit Number Not Defined");
		return;
	}
		
	rsPtr->GetFieldValue ( "BitNumber", var );
	m_nPartPresent_Bit = var.intVal;
			
	rsPtr->GetFieldValue ( "DefaultTrueState", var );
	blnTrueState = var.bVal; 

	TrueState[m_nPartPresent_Bit]=blnTrueState;

	
	rsPtr->Close();
	delete rsPtr;

	// Close the database.

	Close();



}


int CDioInput::GetPartPresentBit()
{
	return m_nPartPresent_Bit;
}


void CDioInput::SetLabelAppliedBit()
{

	int nCount;
	COleVariant var;
	CString csSQLCmd;

	CDaoRecordset	*rsPtr;
	BOOL blnTrueState;


	// Open the database.

	if ( !Open() )
		return ;

	csSQLCmd = CString("Select * from tbl_DIO_InputBit_Assignments ")+
		       CString("Where Name = ")+
			   CString("'LabelApplied'");

	rsPtr = new CDaoRecordset ( &m_dbJobDatabase );
	rsPtr->Open ( AFX_DAO_USE_DEFAULT_TYPE, csSQLCmd);

	nCount = rsPtr->GetRecordCount();
	if (nCount!=1)
	{
		AfxMessageBox("Label Applied Bit Number Not Defined");
		return;
	}
		
	rsPtr->GetFieldValue ( "BitNumber", var );
	m_nLabelAppled_Bit = var.intVal;
			
	rsPtr->GetFieldValue ( "DefaultTrueState", var );
	blnTrueState = var.bVal; 

	TrueState[m_nLabelAppled_Bit]=blnTrueState;

	
	rsPtr->Close();
	delete rsPtr;

	// Close the database.

	Close();



}


int CDioInput::GetLabelAppliedBit()
{
	return m_nLabelAppled_Bit;
}


/*********************************************************/



CDioOutput::CDioOutput()
{

}

CDioOutput::~CDioOutput()
{

}


BOOL CDioOutput::Initialize ( int nBase )
{
	int
		i,
		nBitNumber;



	m_nBaseAddress = nBase;

	for (i = 0; i< c_output_length; i++)
		m_ulg_output_array[i] = 0;


	for (nBitNumber=0;nBitNumber<32;nBitNumber++)
		TrueState[nBitNumber]=TRUE;  // i.e. true is set high



	SetApplyLabelBit();
	SetApplicatorReadyBit();
	SetCycleCompleteBit();
	SetErrorBit();

	SetGreenTowerLightBit();
	SetRedTowerLightBit();
	
	
	return m_oDIO.Initialize ( m_nBaseAddress );
}

BOOL CDioOutput::ApplyLabelBitOn()
{
BOOL bReturnStatus;
	
	if (TrueState[GetApplyLabelBit()])	
	{
	   bReturnStatus= DioSetBit( GetApplyLabelBit());  // true is high, low is false

    }
	else
	{
	   bReturnStatus= DioClearBit(GetApplyLabelBit());

	}
	return bReturnStatus;
}


BOOL CDioOutput::ApplyLabelBitOff()
{

BOOL bReturnStatus;

	
	if (TrueState[GetApplyLabelBit()])	
	{
	   return DioClearBit( GetApplyLabelBit());  // high is true, low is false

    }
	else
	{
		return DioSetBit(GetApplyLabelBit());   // low is true, high is false

	}

	return bReturnStatus;

}


BOOL CDioOutput::ApplicatorReadyBitOn()
{
BOOL bReturnStatus;

	if (TrueState[GetApplicatorReadyBit()])	
	{
	   bReturnStatus= DioSetBit( GetApplicatorReadyBit());  // true is high, low is false

    }
	else
	{
	   bReturnStatus= DioClearBit(GetApplicatorReadyBit());

	}
	return bReturnStatus;
}


BOOL CDioOutput::ApplicatorReadyBitOff()
{
BOOL bReturnStatus;
	
	if (TrueState[GetApplicatorReadyBit()])	
	{
	   return DioClearBit( GetApplicatorReadyBit());  // high is true, low is false

    }
	else
	{
		return DioSetBit(GetApplicatorReadyBit());   // low is true, high is false

	}

	return bReturnStatus;
}


BOOL CDioOutput::CycleCompleteBitOn()
{
BOOL bReturnStatus;

	if (TrueState[GetCycleCompleteBit()])	
	{
	   bReturnStatus= DioSetBit( GetCycleCompleteBit());  // true is high, low is false

    }
	else
	{
	   bReturnStatus= DioClearBit(GetCycleCompleteBit());

	}
	return bReturnStatus;
}


BOOL CDioOutput::CycleCompleteBitOff()
{
BOOL bReturnStatus;
	
	if (TrueState[GetCycleCompleteBit()])	
	{
	   return DioClearBit( GetCycleCompleteBit());  // high is true, low is false

    }
	else
	{
		return DioSetBit(GetCycleCompleteBit());   // low is true, high is false

	}

	return bReturnStatus;
}


BOOL CDioOutput::ErrorBitOn()
{
BOOL bReturnStatus;

	if (TrueState[GetErrorBit()])	
	{
	   bReturnStatus= DioSetBit( GetErrorBit());  // true is high, low is false

    }
	else
	{
	   bReturnStatus= DioClearBit(GetErrorBit());

	}
	return bReturnStatus;
}


BOOL CDioOutput::ErrorBitOff()
{
BOOL bReturnStatus;
	
	if (TrueState[GetErrorBit()])	
	{
	   return DioClearBit( GetErrorBit());  // high is true, low is false

    }
	else
	{
		return DioSetBit(GetErrorBit());   // low is true, high is false

	}

	return bReturnStatus;

}



BOOL CDioOutput::DioClearBit(int int_bit)
{


	m_ulg_output_array[int_bit] = 0;

	return m_oDIO.WriteOutputArray(m_ulg_output_array);
}


BOOL CDioOutput::DioSetBit(int int_bit)
{


	m_ulg_output_array[int_bit] = 1;

	return m_oDIO.WriteOutputArray(m_ulg_output_array);	
}



BOOL CDioOutput::Reset ( void )
{

	int
		i;


	for (i = 0; i< c_output_length; i++)
		m_ulg_output_array[i] = 0;

	return m_oDIO.WriteOutputArray(m_ulg_output_array);

}


void CDioOutput::SetApplyLabelBit()
{

	int nCount;
	COleVariant var;
	CString csSQLCmd;
	BOOL blnTrueState;

	CDaoRecordset	*rsPtr;


	// Open the database.

	if ( !Open() )
		return ;

	csSQLCmd = CString("Select * from tbl_DIO_OutputBit_Assignments ")+
		       CString("Where Name = ")+
			   CString("'ApplyLabel'");

	rsPtr = new CDaoRecordset ( &m_dbJobDatabase );
	rsPtr->Open ( AFX_DAO_USE_DEFAULT_TYPE, csSQLCmd);

	nCount = rsPtr->GetRecordCount();
	if (nCount!=1)
	{
		AfxMessageBox("Apply Label Bit Number Not Defined");
		return;
	}
		
	rsPtr->GetFieldValue ( "BitNumber", var );
	m_nApplyLabel_Bit = var.intVal;
			

	rsPtr->GetFieldValue ( "DefaultTrueState", var );
	blnTrueState = var.bVal; 

	TrueState[m_nApplyLabel_Bit]=blnTrueState;

	
	rsPtr->Close();
	delete rsPtr;

	// Close the database.

	Close();



}


int CDioOutput::GetApplyLabelBit()
{
	return m_nApplyLabel_Bit;
}



void CDioOutput::SetApplicatorReadyBit()
{

	int nCount;
	COleVariant var;
	CString csSQLCmd;
	BOOL blnTrueState;
	CDaoRecordset	*rsPtr;


	// Open the database.

	if ( !Open() )
		return ;

	csSQLCmd = CString("Select * from tbl_DIO_OutputBit_Assignments ")+
		       CString("Where Name = ")+
			   CString("'ApplicatorReady'");

	rsPtr = new CDaoRecordset ( &m_dbJobDatabase );
	rsPtr->Open ( AFX_DAO_USE_DEFAULT_TYPE, csSQLCmd);

	nCount = rsPtr->GetRecordCount();
	if (nCount!=1)
	{
		AfxMessageBox("Applicator Ready Bit Number Not Defined");
		return;
	}
		
	rsPtr->GetFieldValue ( "BitNumber", var );
	m_nApplicatorReady_Bit = var.intVal;
			

	rsPtr->GetFieldValue ( "DefaultTrueState", var );
	blnTrueState = var.bVal; 

	TrueState[m_nApplicatorReady_Bit]=blnTrueState;


	
	rsPtr->Close();
	delete rsPtr;

	// Close the database.

	Close();



}


int CDioOutput::GetApplicatorReadyBit()
{
	return m_nApplicatorReady_Bit;
}



void CDioOutput::SetCycleCompleteBit()
{

	int nCount;
	COleVariant var;
	CString csSQLCmd;
	BOOL blnTrueState;
	CDaoRecordset	*rsPtr;


	// Open the database.

	if ( !Open() )
		return ;

	csSQLCmd = CString("Select * from tbl_DIO_OutputBit_Assignments ")+
		       CString("Where Name = ")+
			   CString("'CycleComplete'");

	rsPtr = new CDaoRecordset ( &m_dbJobDatabase );
	rsPtr->Open ( AFX_DAO_USE_DEFAULT_TYPE, csSQLCmd);

	nCount = rsPtr->GetRecordCount();
	if (nCount!=1)
	{
		AfxMessageBox("Cycle Complete Bit Number Not Defined");
		return;
	}
		
	rsPtr->GetFieldValue ( "BitNumber", var );
	m_nCycleComplete_Bit = var.intVal;
			
	rsPtr->GetFieldValue ( "DefaultTrueState", var );
	blnTrueState = var.bVal; 

	TrueState[m_nCycleComplete_Bit]=blnTrueState;

	
	rsPtr->Close();
	delete rsPtr;

	// Close the database.

	Close();



}


int CDioOutput::GetCycleCompleteBit()
{
	return m_nCycleComplete_Bit;
}


void CDioOutput::SetErrorBit()
{

	int nCount;
	COleVariant var;
	CString csSQLCmd;
	BOOL blnTrueState;

	CDaoRecordset	*rsPtr;


	// Open the database.

	if ( !Open() )
		return ;

	csSQLCmd = CString("Select * from tbl_DIO_OutputBit_Assignments ")+
		       CString("Where Name = ")+
			   CString("'Error'");

	rsPtr = new CDaoRecordset ( &m_dbJobDatabase );
	rsPtr->Open ( AFX_DAO_USE_DEFAULT_TYPE, csSQLCmd);

	nCount = rsPtr->GetRecordCount();
	if (nCount!=1)
	{
		AfxMessageBox("Error Bit Number Not Defined");
		return;
	}
		
	rsPtr->GetFieldValue ( "BitNumber", var );
	m_nError_Bit = var.intVal;
			

	rsPtr->GetFieldValue ( "DefaultTrueState", var );
	blnTrueState = var.bVal; 

	TrueState[m_nError_Bit]=blnTrueState;


	
	rsPtr->Close();
	delete rsPtr;

	// Close the database.

	Close();



}


int CDioOutput::GetErrorBit()
{
	return m_nError_Bit;
}


CDBase::CDBase()
{

}

CDBase::~CDBase()
{

}


BOOL CDBase::Open ( void )  
{
static int nRepeatCount=0;
	CString csTemp;


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
			csTemp= "Database Not Found" ;
			AfxMessageBox (csTemp+CString(szCause) );
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

void CDBase::Close ( void ) 
{

	m_dbJobDatabase.Close ();

}



int CDioOutput::GetRedTowerLightBit()
{
	return m_nRedTowerLight_Bit;
}

int CDioOutput::GetGreenTowerLightBit()
{
	return m_nGreenTowerLight_Bit;
}


void CDioOutput::SetRedTowerLightBit()
{

	int nCount;
	COleVariant var;
	CString csSQLCmd;
	BOOL blnTrueState;
	CDaoRecordset	*rsPtr;


	// Open the database.

	if ( !Open() )
		return ;

	csSQLCmd = CString("Select * from tbl_DIO_OutputBit_Assignments ")+
		       CString("Where Name = ")+
			   CString("'RedTowerLight'");

	rsPtr = new CDaoRecordset ( &m_dbJobDatabase );
	rsPtr->Open ( AFX_DAO_USE_DEFAULT_TYPE, csSQLCmd);

	nCount = rsPtr->GetRecordCount();
	if (nCount!=1)
	{
		AfxMessageBox("Red Tower Light Bit Number Not Defined");
		return;
	}
		
	rsPtr->GetFieldValue ( "BitNumber", var );
	m_nRedTowerLight_Bit = var.intVal;
			
	rsPtr->GetFieldValue ( "DefaultTrueState", var );
	blnTrueState = var.bVal; 

	TrueState[m_nRedTowerLight_Bit]=blnTrueState;

	
	rsPtr->Close();
	delete rsPtr;

	// Close the database.

	Close();



}


void CDioOutput::SetGreenTowerLightBit()
{

	int nCount;
	COleVariant var;
	CString csSQLCmd;
	BOOL blnTrueState;
	CDaoRecordset	*rsPtr;


	// Open the database.

	if ( !Open() )
		return ;

	csSQLCmd = CString("Select * from tbl_DIO_OutputBit_Assignments ")+
		       CString("Where Name = ")+
			   CString("'GreenTowerLight'");

	rsPtr = new CDaoRecordset ( &m_dbJobDatabase );
	rsPtr->Open ( AFX_DAO_USE_DEFAULT_TYPE, csSQLCmd);

	nCount = rsPtr->GetRecordCount();
	if (nCount!=1)
	{
		AfxMessageBox("Green Tower Light Bit Number Not Defined");
		return;
	}
		
	rsPtr->GetFieldValue ( "BitNumber", var );
	m_nGreenTowerLight_Bit = var.intVal;
			
	rsPtr->GetFieldValue ( "DefaultTrueState", var );
	blnTrueState = var.bVal; 

	TrueState[m_nGreenTowerLight_Bit]=blnTrueState;

	
	rsPtr->Close();
	delete rsPtr;

	// Close the database.

	Close();



}


BOOL CDioOutput::GreenLightOn()
{
BOOL bReturnStatus;
	
	if (TrueState[GetApplyLabelBit()])	
	{
	   bReturnStatus= DioSetBit( GetGreenTowerLightBit());  // true is high, low is false
	   bReturnStatus= DioClearBit(GetRedTowerLightBit());

    }
	else
	{
	   bReturnStatus= DioClearBit(GetGreenTowerLightBit());
	   bReturnStatus= DioSetBit( GetRedTowerLightBit());  // true is high, low is false

	}
	return bReturnStatus;
}

BOOL CDioOutput::RedLightOn()
{
BOOL bReturnStatus;
	
	if (TrueState[GetApplyLabelBit()])	
	{
	   bReturnStatus= DioSetBit( GetRedTowerLightBit());  // true is high, low is false
	   bReturnStatus= DioClearBit(GetGreenTowerLightBit());

    }
	else
	{
	   bReturnStatus= DioClearBit(GetRedTowerLightBit());
	   bReturnStatus= DioSetBit( GetGreenTowerLightBit());  // true is high, low is false

	}
	return bReturnStatus;
}

BOOL CDioOutput::LightsOff()
{
BOOL bReturnStatus;
	
	if (TrueState[GetApplyLabelBit()])	
	{
	   bReturnStatus= DioClearBit( GetRedTowerLightBit());  // true is high, low is false
	   bReturnStatus= DioClearBit(GetGreenTowerLightBit());

    }
	else
	{
	   bReturnStatus= DioSetBit(GetRedTowerLightBit());
	   bReturnStatus= DioSetBit( GetGreenTowerLightBit());  // true is high, low is false

	}
	return bReturnStatus;
}


void CDioInput::SetStartButtonBit()
{

	int nCount;
	COleVariant var;
	CString csSQLCmd;
	BOOL blnTrueState;
	CDaoRecordset	*rsPtr;


	// Open the database.

	if ( !Open() )
		return ;

	csSQLCmd = CString("Select * from tbl_DIO_InputBit_Assignments ")+
		       CString("Where Name = ")+
			   CString("'StartButton'");

	rsPtr = new CDaoRecordset ( &m_dbJobDatabase );
	rsPtr->Open ( AFX_DAO_USE_DEFAULT_TYPE, csSQLCmd);

	nCount = rsPtr->GetRecordCount();
	if (nCount!=1)
	{
		AfxMessageBox("Start Button Bit Number Not Defined");
		return;
	}
		
	rsPtr->GetFieldValue ( "BitNumber", var );
	m_nStartButton_Bit = var.intVal;
			
	rsPtr->GetFieldValue ( "DefaultTrueState", var );
	blnTrueState = var.bVal; 

	TrueState[m_nStartButton_Bit]=blnTrueState;

	
	rsPtr->Close();
	delete rsPtr;

	// Close the database.

	Close();



}

void CDioInput::SetStopButtonBit()
{

	int nCount;
	COleVariant var;
	CString csSQLCmd;
	BOOL blnTrueState;
	CDaoRecordset	*rsPtr;


	// Open the database.

	if ( !Open() )
		return ;

	csSQLCmd = CString("Select * from tbl_DIO_InputBit_Assignments ")+
		       CString("Where Name = ")+
			   CString("'StopButton'");

	rsPtr = new CDaoRecordset ( &m_dbJobDatabase );
	rsPtr->Open ( AFX_DAO_USE_DEFAULT_TYPE, csSQLCmd);

	nCount = rsPtr->GetRecordCount();
	if (nCount!=1)
	{
		AfxMessageBox("Stop Button Bit Number Not Defined");
		return;
	}
		
	rsPtr->GetFieldValue ( "BitNumber", var );
	m_nStopButton_Bit = var.intVal;
			
	rsPtr->GetFieldValue ( "DefaultTrueState", var );
	blnTrueState = var.bVal; 

	TrueState[m_nStopButton_Bit]=blnTrueState;

	
	rsPtr->Close();
	delete rsPtr;

	// Close the database.

	Close();



}

int CDioInput::GetStartButtonBit()
{
	return m_nStartButton_Bit;
}

int CDioInput::GetStopButtonBit()
{
	return m_nStopButton_Bit;
}


BOOL CDioInput::IsStopButtonOn()
{
BOOL blnRetState,
	 blnInputState;

    blnInputState= m_ulg_input_array[GetStopButtonBit()];

	if (TrueState[GetStopButtonBit()])
	{
		blnRetState=blnInputState;
	}
	else
	{
		blnRetState=!blnInputState;
	}
	return blnRetState;

}

BOOL CDioInput::IsStartButtonOn()
{
BOOL blnRetState,
	 blnInputState;

    blnInputState= m_ulg_input_array[GetStartButtonBit()];

	if (TrueState[GetStartButtonBit()])
	{
		blnRetState=blnInputState;
	}
	else
	{
		blnRetState=!blnInputState;
	}
	return blnRetState;

}
