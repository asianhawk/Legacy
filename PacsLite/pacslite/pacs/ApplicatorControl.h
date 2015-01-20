// ApplicatorControl.h: interface for the CApplicatorControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPLICATORCONTROL_H__BCF778C2_9EE5_11D2_A2AB_006008043EC4__INCLUDED_)
#define AFX_APPLICATORCONTROL_H__BCF778C2_9EE5_11D2_A2AB_006008043EC4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "Database.h"
#include "PrinterControl.h"
#include "ScannerControl.h"
#include "Database.h"
#include "SNManager.h"
#include "Utilities.h"
#include "DIOController.h"
#include "job.h"

#include "ReSyncDlg.h"


enum status
{
	STATUS_GOOD,
	STATUS_RELABEL,
	STATUS_RESTART,
	STATUS_EXIT
};


class CApplicatorControl  
{

public:
	CDioController			*GetDIOObject();
	int						*GetAutoRescans();
	BOOL					*GetRequestHold();

	CApplicatorControl();
	virtual ~CApplicatorControl();
	BOOL					SystemIntegrityCheck();
	BOOL					m_blnIsPrinting;

	BOOL					Initialize ( void );
	CDatabase				*GetDatabaseObject ( void );
	CPrinterControl			*GetPrinterObject ( void );
	CScannerControl			*GetScannerObject ( void );
	CJob					*GetJob ( void );
	CSNManager				*GetSNManager ( void );


	CJob					*SetupJob ( CString csJobName );

//	BOOL					ManualFeed ( CLabel *poLabel, CLabel *poLabel2 );
	void					ReqHold();
	BOOL					Reset ( );
	BOOL					Run ( long * lpPanelCount );
	BOOL					PrintOneSample ( CLabel *poLabel );
	BOOL					CheckForNotInHold();

	BOOL					m_bRequestHold;					// Operator hold request flag.
	CString					m_csPlaceRotation;

	BOOL					m_bInitialized;					// System initialized flag.
	float					m_fLabeltoLabelCycleTime;
	float					m_fTotalLabeltoLabelCycleTime;
	float					m_fAveLabeltoLabelCycleTime;

	float					m_fBoardtoBoardCycleTime;
	float					m_fTotalBoardtoBoardCycleTime;
	float					m_fAveBoardtoBoardCycleTime;

	void					SetScannerPerformance(int  nScanCount);
	void					SetAveScannerPerformance(int  nScanCount);

	CString					GetScannerPerformance();
	CString					GetAveScannerPerformance();
	CString					m_csCurrentJobStatus;

	void					ExitRunCleanup ( );
	BOOL					ExitRunCleanup (BOOL blnRetState);
	void					StartVirtualKeyboard();
	BOOL					IsScannerActive();
	BOOL					ReSync(int nCurrentLabelCount,
									int nMaxLabelCount,
									CString csTemplate);

	BOOL					CheckFingerTraps(LPSYSTEMTIME lpStartTime);

private:
	int						m_nAutoRescans;					// Number of automatic rescans.
	BOOL					m_bRequestStop;					// Operator stop request flag.
	int						m_nMaxLabelsPerPanel;			// Label quantity per panel.
	CString					m_csCurrentSN;

	CDatabase				m_oDatabase;		// Job and system database interface object.
	CDioController			m_oDIOController;	// System digital I/O hardware interface object.
	CPrinterControl			m_oPrinter;			// Control the use of all printers object.
	CScannerControl			m_oScanner;			// Control the use of all scanners object.
	CJob					m_oJob;				// Job object.
	CSNManager				m_oSNManager;		// Serial number manager object.

	CStringArray			m_csaLabelPoints;	// Array of label points.

	CString					m_csScannedPrinter1;			// The scanned front printer label.

	BOOL					PeekAndPump();						// Force messaging.
	BOOL					UpdateOutputFile ( int nPrinter, CString csScanned );

	double					m_dScannerPerformance;
	double					m_dAveScannerPerformance;
	int						m_nTotalGoodScans;
	int						m_nTotalScans;
	BOOL					m_bScannerActive;

};

#endif // !defined(AFX_APPLICATORCONTROL_H__BCF778C2_9EE5_11D2_A2AB_006008043EC4__INCLUDED_)
