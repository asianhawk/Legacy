// CDioController.cpp: implementation of the CDioController class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PACS.h"
#include "definitions.h"
#include "DioController.h"
#include "Utilities.h"
#include "trace.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDioController::CDioController()
{

}

CDioController::~CDioController()
{

}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		Initialize
//
//	Description:
//		Initialize the system digital system and output functions.
//
//	Arguments:
//		Input address.
//		Output address.
//
//	Return:
//		Status.
//
//	Called by:
//		CApplicatorControl::Initialize
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDioController::Initialize ( CString csInput, CString csOutput )
{
	int nInput;
	int nOutput;
	
	CUtilities
		Utility;

	CString
		csMessage;

	Trace("[MachineState] MS= Initializing DIOController SubSystem");	

	Trace("[I] CDioController::Start of Initialize()\n\r");

//	if ((SIMULATION)&(SIMULATEDIOCONTROLLER))
//	{
//		return true;
//	}

	nInput = (int)Utility.AsciiHexToUINT ( csInput );
	nOutput = (int)Utility.AsciiHexToUINT ( csOutput );


	if ( ( !m_oDIOInput.Initialize ( nInput ) ) || ( !m_oDIOOutput.Initialize ( nOutput ) ) )
	{
		m_csErrorString.LoadString ( IDS_ERR_INIT_DIO );
		Trace("[E] CDioController::Failed To Initialize()\n\r");
		m_bInitialized = FALSE;
	}
	else
	{
		Trace("[S] CDioController::Successfully Initialized()\n\r");
		m_bInitialized = TRUE;
	}

	Trace("[I] CDioController::End of Initialize()\n\r");
	
	return ( m_bInitialized );

	m_oDIOOutput.LightsOff();

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		ReadSystemInputs
//
//	Description:
//		Read system inputs. Look for errors.
//
//	Arguments:
//		None.
//
//	Return:
//		Error status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDioController::ReadSystemInputs()
{

	BOOL bError;
	CString csTemp;
	Trace("[I] CDioController::Begin ReadSystemInputs()\n\r");


	bError = FALSE;

	if ((SIMULATION)&(SIMULATEDIOCONTROLLER))
	{
		return FALSE;
	}


	// Prepare to read a fresh set of inputs.

	m_oDIOInput.ClearArray();
	m_oDIOInput.ReadInputArray();
	
	if ( !m_oDIOInput.IsPowerOn() )
	{
		bError = TRUE;
		csTemp.LoadString ( IDS_ERR_POWER_OFF );
	
	}
	if ( bError )
	{

		// Get fresh inputs to ensure they did as instructed.

		m_oDIOInput.ClearArray();
		m_oDIOInput.ReadInputArray();
		
		if ( !m_oDIOInput.IsPowerOn() )
			bError = TRUE;
		else
		{
			bError = FALSE;
		}
	}
	
	Trace("[I] CDioController::End of ReadSystemInputs()\n\r");

	return ( bError );

}


BOOL CDioController::CheckSystemInputs(CString *csErrorMessage)
{

	CString csTemp;
	Trace("[I] CDioController::Begin CheckSystemInputs()");



	if ((SIMULATION)&(SIMULATEDIOCONTROLLER))
	{
		return TRUE;
	}


	// Prepare to read a fresh set of inputs.

	m_oDIOInput.ClearArray();
	m_oDIOInput.ReadInputArray();
	
	if ( !m_oDIOInput.IsPowerOn() )
	{
		csTemp.LoadString ( IDS_ERR_POWER_OFF );
		*csErrorMessage=csTemp;
		return FALSE;

	}
	
	return TRUE;

}






BOOL CDioController::IsPrinterReady()
{
BOOL blnReturnValue;
	Trace("[I] CDioController::Start Of IsPrinterReady()\n\r");

	if ((SIMULATION)&(SIMULATEDIOCONTROLLER))
	{
		return true;
	}

	Trace("[I] CDioController::End Of IsPrinterReady()\n\r");
	blnReturnValue =m_oDIOInput.IsPrinterReady();
	if(!blnReturnValue)
	{
		RedLightOn();
	}
	return blnReturnValue;
}


BOOL CDioController::IsPowerOn()
{
BOOL blnReturnValue;
	if ((SIMULATION)&(SIMULATEDIOCONTROLLER))
	{
		Trace("CDioController::IsPowerOn()\n\r");
		return true;
	}
	blnReturnValue=m_oDIOInput.IsPowerOn();
	if(!blnReturnValue)
	{
		RedLightOn();
	}

	return blnReturnValue;
}


BOOL CDioController::IsPartPresent ()
{
BOOL blnReturnValue;
	
	if ((SIMULATION)&(SIMULATEDIOCONTROLLER))
	{
		Trace("CDioController::IsPartPresent()\n\r");
		return true;
	}
	blnReturnValue=m_oDIOInput.IsPartPresent();

	return blnReturnValue;
}



BOOL CDioController::IsLabelApplied()
{
	if ((SIMULATION)&(SIMULATEDIOCONTROLLER))
	{
		Trace("CDioController::IsLabelApplied()\n\r");
		return true;
	}

	return m_oDIOInput.IsLabelApplied();	
}


BOOL CDioController::ApplyLabelBitOn()
{
	if ((SIMULATION)&(SIMULATEDIOCONTROLLER))
	{
		Trace("CDioController::ApplyLabelBitOn()\n\r");
		return true;
	}

	return m_oDIOOutput.ApplyLabelBitOn();	
}


BOOL CDioController::ApplyLabelBitOff()
{
	if ((SIMULATION)&(SIMULATEDIOCONTROLLER))
	{
		Trace("CDioController::ApplyLabelBitOff()\n\r");
		return true;
	}

	return m_oDIOOutput.ApplyLabelBitOff();	
}



BOOL CDioController::ApplicatorReadyBitOn()
{
	if ((SIMULATION)&(SIMULATEDIOCONTROLLER))
	{
		Trace("CDioController::ApplicatorReadyBitOn()\n\r");
		return true;
	}

	return m_oDIOOutput.ApplicatorReadyBitOn();	
}

BOOL CDioController::ApplicatorReadyBitOff()
{
	if ((SIMULATION)&(SIMULATEDIOCONTROLLER))
	{
		Trace("CDioController::ApplicatorReadyBitOff()\n\r");
		return true;
	}

	return m_oDIOOutput.ApplicatorReadyBitOff();	
}


BOOL CDioController::CycleCompleteBitOn()
{
	if ((SIMULATION)&(SIMULATEDIOCONTROLLER))
	{
		Trace("CDioController::CycleCompleteBitOn()\n\r");
		return true;
	}

	return m_oDIOOutput.CycleCompleteBitOn();	
}

BOOL CDioController::CycleCompleteBitOff()
{
	if ((SIMULATION)&(SIMULATEDIOCONTROLLER))
	{
		Trace("CDioController::CycleCompleteBitOff()\n\r");
		return true;
	}

	return m_oDIOOutput.CycleCompleteBitOff();	
}

BOOL CDioController::ErrorBitOn()
{
	if ((SIMULATION)&(SIMULATEDIOCONTROLLER))
	{
		Trace("CDioController::ErrorBitOn()\n\r");
		return true;
	}
	return m_oDIOOutput.ErrorBitOn();	
}

BOOL CDioController::ErrorBitOff()
{
	if ((SIMULATION)&(SIMULATEDIOCONTROLLER))
	{
		Trace("CDioController::ErrorBitOff()\n\r");
		return true;
	}
	return m_oDIOOutput.ErrorBitOff();	
}


BOOL CDioController::Reset ( void )
{
	if ((SIMULATION)&(SIMULATEDIOCONTROLLER))
	{
		Trace("CDioController::Reset()\n\r");
		return true;
	}

	return m_oDIOOutput.Reset ();
}


BOOL CDioController::RedLightOn ( void )
{
	if ((SIMULATION)&(SIMULATEDIOCONTROLLER))
	{
		Trace("CDioController::RedLightOn()\n\r");
		return true;
	}

	return m_oDIOOutput.RedLightOn();
}

BOOL CDioController::GreenLightOn ( void )
{
	if ((SIMULATION)&(SIMULATEDIOCONTROLLER))
	{
		Trace("CDioController::GreenLightOn()\n\r");
		return true;
	}

	return m_oDIOOutput.GreenLightOn();
}

BOOL CDioController::LightsOff( void )
{
	if ((SIMULATION)&(SIMULATEDIOCONTROLLER))
	{
		Trace("CDioController::LightsOff()\n\r");
		return true;
	}

	return m_oDIOOutput.LightsOff();
}


BOOL CDioController::IsStopButtonOn( void )
{
	if ((SIMULATION)&(SIMULATEDIOCONTROLLER))
	{
		Trace("CDioController::IsStopButtonOn()\n\r");
		return FALSE;
	}

	return m_oDIOInput.IsStopButtonOn();

}

BOOL CDioController::IsStartButtonOn( void )
{
	if ((SIMULATION)&(SIMULATEDIOCONTROLLER))
	{
		Trace("CDioController::IsStartButtonOn()\n\r");
		return true;
	}

	return m_oDIOInput.IsStartButtonOn();

}


CDioInput * CDioController::GetDIOInput()
{
	if ((SIMULATION)&(SIMULATEDIOCONTROLLER))
	{
		Trace("CDioController::GetDIOInput()\n\r");
	}

	return &m_oDIOInput;

}
