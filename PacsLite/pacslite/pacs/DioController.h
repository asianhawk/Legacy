// DioController.h: interface for the DioController class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIOCONTROLLER_H__20DA9CE2_A389_11D1_9FD5_006008043EC4__INCLUDED_)
#define AFX_DIOCONTROLLER_H__20DA9CE2_A389_11D1_9FD5_006008043EC4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
//////////////////////////zhu
 
#include "NSDIOmain.h"

//////////////////////////end

class CDioController  
{
public:
	CString m_csErrorString;
	BOOL m_bInitialized;


	BOOL ReadSystemInputs();	
	BOOL CheckSystemInputs(CString *csErrorMessage);


	BOOL Initialize(CString, CString);
	BOOL Reset ( void );
	
	CDioController();
	virtual ~CDioController();

	//Implementation
	
			//    *********** Inputs
	BOOL IsPrinterReady();
	BOOL IsPowerOn();
	BOOL IsPartPresent ();
	BOOL IsLabelApplied();

			//    *********** Outputs
	BOOL ApplyLabelBitOn();
	BOOL ApplyLabelBitOff();
	BOOL ApplicatorReadyBitOn();
	BOOL ApplicatorReadyBitOff();
	BOOL CycleCompleteBitOn();
	BOOL CycleCompleteBitOff();
	BOOL ErrorBitOn();
	BOOL ErrorBitOff();

	BOOL LightsOff( void );
	BOOL RedLightOn(void);
	BOOL GreenLightOn(void);
	BOOL IsStartButtonOn( void );
	BOOL IsStopButtonOn( void );

	CDioInput m_oDIOInput;
	CDioInput *GetDIOInput();


private:

	CDioOutput m_oDIOOutput;

};

#endif // !defined(AFX_DIOCONTROLLER_H__20DA9CE2_A389_11D1_9FD5_006008043EC4__INCLUDED_)
