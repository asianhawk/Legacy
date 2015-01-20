// Scanner.h: interface for the CScanner class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCANNER_H__C6DE2D22_B1D7_11D2_A68A_641A11C1FB5F__INCLUDED_)
#define AFX_SCANNER_H__C6DE2D22_B1D7_11D2_A68A_641A11C1FB5F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


//const CString c_csMicroscanTrigger = "<b>" ;   // trigger should always be "<b>"
//const CString c_csMicroscanReset = "<Ka4,1,0,0><Kg4><Kh0,XXX><Kib><Km1><KL1><Kk1,NOREAD><Kd0><Kr1,0,0,8,0><Ke0><Z>";
const int c_nWatchTime = 6; // seconds;
const CString c_csMicroscanVersion = "<#>";			// Microscan version command.
const CString c_csMetaneticsVersion = "?x500batch0260?";
const CString c_csWelchAllyn_4700 = "\x16M\x0DREV?.";
const CString c_csWelchAllyn_Preamble="\x16M\x0D";
const CString c_csWelchAllyn_3900_TriggerOn="\x16T\x0D";
const CString c_csWelchAllyn_3900_TriggerOff="\x16U\x0D";

const CString c_csWelchAllyn_TriggerOff="\x16M\x0DTRGOFFB.";
#include "Database.h"
#include "comPort.h"
#include "SNManager.h"
#include "DioController.h"
#include "PrinterControl.h"

class CScanner  
{
public:
	CUtilities Utility;
	void SetMatchLabel(BOOL bMatchLabel);
	BOOL GetMatchLabel();

	CString SingleTrigger();
	CString SingleTrigger(BOOL blnTrim);

	CString GetReset();
	CScanner();
	virtual ~CScanner();

	BOOL Initialize ( CDatabase *poDatabase, 
							int nScannerLocation,
							CSNManager * oSNManager,
							BOOL *bUseScanner );

	BOOL Initialize ( CDatabase *poDatabase, 
						 int nScannerLocation,
						 CSNManager * oSNManager,
						 BOOL *bUseScanner,
						 CPrinterControl *oPrinter);
	
	
	void SetUse ( BOOL bUse );
	BOOL GetUse();
	void SetEnable ( BOOL bEnable );
	BOOL GetEnable();
	void SetType ( int nType );
	int  GetType();
	BOOL Reset();
	BOOL ScanLabel ( CString *csLabelScanned, 
								   CDioController *poDIOController, 
									CString csPrintedLabel,
									BOOL bVerifyScan );

	BOOL GetVersion ( CString *csVersion );
	CString GetScannerName();
	BOOL Refresh ( );
	void SetTrigger ( CString csTrigger );
	void SetReset ( CString csReset );
	BOOL CScanner::TriggerOff();
	CString GetScannedLabel();
	void SetScannedLabel(CString csScannedLabel);
	CString m_csScannedLabel;

private:
	BOOL	m_bUse;								// Use this scanner;
	int	m_nType;								// Scanner type;
	BOOL	m_bEnable;							// Eanble this scanner.
	BOOL	m_bInitialized;					// Object initialized flag.
	int	m_nScannerLocation;				// Scanner sub-system type.
	CString m_csTrigger;						// The scanner trigger character.
	CString m_csTriggerOff;						// The scanner trigger character.
	BOOL m_bMatchLabel;
	
	CString m_csReset;						// The scanner reset string.

	CcomPort m_oComPort;						// The com port for the printer.
	CDatabase *m_poDatabase;				// Pointer to the database object.
	CSNManager *m_poSNManager;				// Pointer serial number manager.

	CPrinterControl *m_poPrinter;
	BOOL CheckTriggerReset();
	BOOL InitializeScannerHardware ( );

};

#endif // !defined(AFX_SCANNER_H__C6DE2D22_B1D7_11D2_A68A_641A11C1FB5F__INCLUDED_)
