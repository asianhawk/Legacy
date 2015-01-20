// DioInput.h: interface for the DioInput class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIOINPUT_H__D9D53362_A2BA_11D1_9FD5_006008043EC4__INCLUDED_)
#define AFX_DIOINPUT_H__D9D53362_A2BA_11D1_9FD5_006008043EC4__INCLUDED_


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////


#include "definitions.h"

class AFX_MFC_EXT_TYPE CDBase  
{
public:
	BOOL		m_bInitialized;						// Object initialized flag.
	CDBase();
	virtual ~CDBase();

	BOOL Open();												// Open the database.
	void Close();												// Close the database.
	CDaoDatabase	m_dbJobDatabase;						// DAO Database object.

};






const int c_array_length = 32;

// input



class AFX_MFC_EXT_TYPE CDIODriver 
{
public:
	BOOL Initialize (unsigned long);
	CDIODriver();
	virtual ~CDIODriver();

	BOOL ReadInputLong(unsigned long *lng_read);
	BOOL ReadInputArray(unsigned long lng_array[]);

	BOOL WriteOutputLong(unsigned long lng_write);
	BOOL WriteOutputArray(unsigned long lng_array[]);

private:
   unsigned long privbase;
	

};






///////////////////////////

class AFX_MFC_EXT_TYPE CDioInput  : CDBase  
{
public:
	void SetPowerOnBit();
	void SetPrinterReadyBit();
	void SetPartPresentBit();
	void SetLabelAppliedBit();

	void SetStartButtonBit();
	void SetStopButtonBit();


	int GetPowerOnBit();
	int GetPrinterReadyBit();
	int GetPartPresentBit();
	int GetLabelAppliedBit();

	int GetStartButtonBit();
	int GetStopButtonBit();
	

	BOOL ReadInputArray();
	BOOL ClearArray();
	BOOL Initialize(int);
	BOOL TrueState[32];

	CDioInput();
	virtual ~CDioInput();





	// Inputs
	BOOL IsPowerOn();	
	BOOL IsPrinterReady();
	BOOL IsPartPresent();
	BOOL IsLabelApplied();

	BOOL IsStartButtonOn();
	BOOL IsStopButtonOn();



private:
	CDIODriver m_oDIO;
	
	BOOL	m_bInit;
	int	m_nBaseAddress;
	unsigned long	m_ulg_input_array[32];

	int m_nPowerOn_Bit;
	int m_nPrinterReady_Bit;
	int m_nPartPresent_Bit;
	int m_nLabelAppled_Bit;

	int m_nStartButton_Bit;
	int m_nStopButton_Bit;


};

const int c_output_length = 32;


class AFX_MFC_EXT_TYPE CDioOutput : CDBase
{
public:
	

	BOOL Reset ( void );
	void SetApplyLabelBit();
	void SetApplicatorReadyBit();
	void SetCycleCompleteBit();
	void SetErrorBit();

	// Added 01/27/02
	void SetGreenTowerLightBit();
	void SetRedTowerLightBit();

	//

	int GetApplyLabelBit();
	int GetApplicatorReadyBit();
	int GetCycleCompleteBit();
	int GetErrorBit();

	// Added 01/27/02
	int GetGreenTowerLightBit();
	int GetRedTowerLightBit();
	//

	BOOL ReadInputArray();
	BOOL ClearArray();
	BOOL Initialize(int);
	BOOL TrueState[32];

	CDioOutput();
	virtual ~CDioOutput();


	// OutPuts
	BOOL ApplyLabelBitOn();	
	BOOL ApplyLabelBitOff();	

	BOOL ApplicatorReadyBitOn();
	BOOL ApplicatorReadyBitOff();

	BOOL CycleCompleteBitOn();
	BOOL CycleCompleteBitOff();

	BOOL ErrorBitOn();
	BOOL ErrorBitOff();

	BOOL LightsOff();
	BOOL RedLightOn();
	BOOL GreenLightOn();


private:
	unsigned long m_ulg_output_array[c_array_length];
	BOOL DioSetBit(int);
	BOOL DioClearBit(int);
	CDIODriver m_oDIO;
	int m_nBaseAddress;


	int m_nApplyLabel_Bit;
	int m_nApplicatorReady_Bit;
	int m_nCycleComplete_Bit;
	int m_nError_Bit;
	int m_nRedTowerLight_Bit;
	int m_nGreenTowerLight_Bit;

};






#endif // !defined(AFX_DIOINPUT_H__D9D53362_A2BA_11D1_9FD5_006008043EC4__INCLUDED_)
