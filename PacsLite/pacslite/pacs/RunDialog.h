//{{AFX_INCLUDES()		
#include "labelcontrol.h"
#include "commandbutton.h"
#include "customflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_RUNDIALOG_H__D220DD42_C0D2_11D2_A2AB_006008043EC4__INCLUDED_)
#define AFX_RUNDIALOG_H__D220DD42_C0D2_11D2_A2AB_006008043EC4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RunDialog.h : header file
//

#include "ApplicatorControl.h" 

/////////////////////////////////////////////////////////////////////////////
// CRunDialog dialog

#include "SNManager.h"	// Added by ClassView
class CRunDialog : public CDialog
{
// Construction
public:
	CSNManager *m_poSNManager;
	CDatabase *m_poDatabase;
	BOOL UpdateForm();
	BOOL Create();
	BOOL Run ( long *lPanelCount );
	BOOL Initialize(CApplicatorControl *);
	void InitJobStatusGrid();
	void InitJobStats();
	void UpdateJobStats();
	void GetColumnHeaders();
	void UpDateStatus(CString csJobStatusMessage); 
	CRunDialog(CWnd* pParent = NULL);   // standard constructor
	CString  ParseScannedLabel(CString csScannedLabel, CString csDeliminator);

	CPrinterControl *m_poPrinterControl;
	CScannerControl *m_poScannerControl;
	BOOL m_blnExitRunMode;

	void UpDateDisplay(CString csPrinterTemplateName);
	void UpDatePlateInfo(int nCurrentIndex,  int nMaxLabelsPerPlate); 

	// Dialog Data
	//{{AFX_DATA(CRunDialog)
	enum { IDD = IDD_RUN_DIALOG };
	CSpinButtonCtrl	m_ctrlRelabelSpinner;
	CButton	m_frmSerialFrame;
	CProgressCtrl	m_pgrPanelProgress;
	CCommandButton	m_cmd_hold;
	CLabelControl	m_lblLabelCount;
	CLabelControl	m_lblJobName;
	CLabelControl	m_lblDateTime;
	CFlexGrid	m_FGJobStatus;
	CFlexGrid	m_FGJobStats;
	CLabelControl	m_lblCurrentJobStatus;
	int		m_nRelabelCount;
	CLabelControl	m_lblJobDescription;
	CLabelControl	m_lblPrinterTemplateName;
	CLabelControl	m_lblCurrentLabelIndex;
	CLabelControl	m_lblMaxLabelsPerPlate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRunDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_int_ID;
	CWnd* mp_Parent;

	// Generated message map functions
	//{{AFX_MSG(CRunDialog)
	afx_msg void OnClickCmdHold();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickCmdRelabel();
	afx_msg void OnClickCmdExit();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
private:
	BOOL m_bln_first_run;
	CApplicatorControl * m_opLabeler;

	long m_lMaxPanels;
	CStatic m_lblData1;
	CStatic m_lblData2;
	CStatic m_lblData3;
	CStatic m_lblData4;
	CStatic m_lblData5;
	int m_nLogX;
	int m_nLogY;


	CString m_csHeader1;
	CString m_csHeader2;
	CString m_csHeader3;
	CString m_csHeader4;
	CString m_csHeader5;

	CString m_csScanPrefix1;
	CString m_csScanPrefix2;
	CString m_csScanPrefix3;
	CString m_csScanPrefix4;
	CString m_csScanPrefix5;

	CString m_csScannedLabel;

};


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RUNDIALOG_H__D220DD42_C0D2_11D2_A2AB_006008043EC4__INCLUDED_)
