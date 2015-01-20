// ScannerControl.h: interface for the CScannerControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCANNERCONTROL_H__BCF778C7_9EE5_11D2_A2AB_006008043EC4__INCLUDED_)
#define AFX_SCANNERCONTROL_H__BCF778C7_9EE5_11D2_A2AB_006008043EC4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "Scanner.h"
#include "SNManager.h"
//#include "DioController.h"

class CScannerControl  
{
public:
	CString m_csErrorString;
	BOOL SetResetString(CString csResetString);
	CString SingleTrigger();
	CString GetResetString();
	CString GetVersionString();
	CScannerControl();
	virtual ~CScannerControl();

	BOOL Initialize ( CDatabase *poDatabase, CSNManager *poSNManager );
	BOOL Initialize ( CDatabase *poDatabase, CSNManager *poSNManager, CPrinterControl *poPrinter );
	BOOL ScanLabel ( CString *csLabelScanned, 
					 CDioController *poDIOController, 
					 CString csPrintedLabel,
					 BOOL bVerifyScan );
	BOOL Reset ();
	BOOL UpdateScannerAttributes ( BOOL bUse,
									 BOOL bEnable,
									 int nType,
									 CString csTrigger,
									 CString csReset );
	BOOL GetUse ();
	BOOL GetEnable ();
	BOOL GetMatchLabel ();
	BOOL IsScannerActive();
	BOOL	m_bInitialized;
	CString m_csScannedLabel;

private:
	CScanner	m_oPlacementScanner;				// Placement scanner object.

	BOOL		m_bScannerActive;	//System scanner status check.
};

#endif // !defined(AFX_SCANNERCONTROL_H__BCF778C7_9EE5_11D2_A2AB_006008043EC4__INCLUDED_)
