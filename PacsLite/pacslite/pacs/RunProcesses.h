// RunProcesses.h: interface for the CRunProcesses class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RUNPROCESSES_H__98E9BA02_0142_11D3_B806_9EBB88208F38__INCLUDED_)
#define AFX_RUNPROCESSES_H__98E9BA02_0142_11D3_B806_9EBB88208F38__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CRunProcesses  
{
public:
	CRunProcesses ();
	virtual ~CRunProcesses();
	void Initialize(CApplicatorControl *poApplicatorControl);
	void ExitManualCleanup();

	int ProcessScan( CString *csLabelScanned);
	int ProcessScan(CString * csLabelScanned, BOOL blnVerify);
	BOOL ApplicatorHold();

	int m_nTotalScans;
private:
	int * m_pnAutoRescans;
	CScannerControl * m_poScanner;
	CDioController * m_poDIOController;
	BOOL * m_pbRequestHold;
	CJob * m_poJob;
	CPrinterControl * m_poPrinter;
	CDatabase * m_poDatabase;
	CSNManager *m_poSNManager;

	CString m_csScannedLabel;


};

#endif // !defined(AFX_RUNPROCESSES_H__98E9BA02_0142_11D3_B806_9EBB88208F38__INCLUDED_)
