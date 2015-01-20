// ScannerControl.h: interface for the CScannerControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCANNERCONTROL_H__BCF778C7_9EE5_11D2_A2AB_006008043EC4__INCLUDED_)
#define AFX_SCANNERCONTROL_H__BCF778C7_9EE5_11D2_A2AB_006008043EC4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "Scanner.h"
//#include "SNManager.h"
//#include "DioController.h"

class CScannerControl  
{
public:
	CString m_csErrorString;
	BOOL SetResetString(int nScannerPosition, CString csResetString);
	CString SingleTrigger(int nScannerPosition);
	CString GetResetString(int nScannerPosition);
	CString GetVersionString(int nScannerPosition);
	CScannerControl();
	virtual ~CScannerControl();

	BOOL Initialize ( int nPosition, CDatabase *poDatabase);
	BOOL ScanLabel ( int nScannerPosition);
	Reset (int nScannerPosition);
	BOOL UpdateScannerAttributes ( int nScannerPosition,
									 BOOL bUse,
									 BOOL bEnable,
									 int nType,
									 CString csTrigger,
									 CString csReset );
	BOOL GetUse (int nScannerPosition);
	BOOL GetEnable (int nScannerPosition);

	BOOL	m_bInitialized;
	CString m_csScannedLabel;

	void InitError(int nPosition);

	CScanner	m_oScanner[4];				// Placement scanner object.

	CString m_csTopScannedLabel;
	CString m_csBottomScannedLabel;
	CString m_csLeftScannedLabel;
	CString m_csRightScannedLabel;

};

#endif // !defined(AFX_SCANNERCONTROL_H__BCF778C7_9EE5_11D2_A2AB_006008043EC4__INCLUDED_)
