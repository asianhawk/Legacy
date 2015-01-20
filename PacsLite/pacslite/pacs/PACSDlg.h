// PACSDlg.h : header file
//
//{{AFX_INCLUDES()
#include "commandbutton.h"
#include "labelcontrol.h"
#include "richtext.h"
#include "customflexgrid.h"
//}}AFX_INCLUDES

#if !defined(AFX_PACSDLG_H__AD71074B_9E4A_11D2_A2AB_006008043EC4__INCLUDED_)
#define AFX_PACSDLG_H__AD71074B_9E4A_11D2_A2AB_006008043EC4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CPACSDlgAutoProxy;

/////////////////////////////////////////////////////////////////////////////
// CPACSDlg dialog


#include <afxdao.h>

#include "Database.h"
#include "ApplicatorControl.h"
#include "Job.h"


class CPACSDlg : public CDialog
{
	DECLARE_DYNAMIC(CPACSDlg);
	friend class CPACSDlgAutoProxy;

// Construction
public:
	CDioController * m_poDioController;
	CScannerControl * m_poScannerControl;
	BOOL HomeAfterPowerRestore();
	BOOL m_bNoPower;
	BOOL PeekAndPump();
	CPACSDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CPACSDlg();

	void ListJobs ( void );
	void InitJobListGrid();
	void AddJobsToFlexGrid();
	void InitJobInfoGrid();
	void AddJobInfoToFlexGrid();
	void ResetLabelPointGrid(CString csJobName);
	void InitLabelPointGrid();



// Dialog Data
	//{{AFX_DATA(CPACSDlg)
	enum { IDD = IDD_PACS_DIALOG };
	CEdit	m_edtPanelQuantity;
	CCommandButton	m_btnTestPrinter;
	CCommandButton	m_btnRun;
	CCommandButton	m_btnCancel;
	CLabelControl	m_lblDateTime;
	CCommandButton	m_btnDiagnostics;
	CCommandButton	m_btnSetup;
	CFlexGrid	m_FGJobList;
	CFlexGrid	m_FGJobInfo;
	CFlexGrid	m_FGLabelPoints;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPACSDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CPACSDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	//{{AFX_MSG(CPACSDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	afx_msg void OnClickCancel();
	afx_msg void OnClickCmdPrint();
	afx_msg void OnClickCmdRun();
	afx_msg void OnSelchangeListJobs();
	afx_msg void OnClickCmdSetupSystem();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClickAboutButton();
	afx_msg void OnClickCmdDiagnostics();
	afx_msg void OnSelChangeJobNames();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	BOOL JobHasValidPrinters();
	CPrinterControl * m_poPrinterControl;
	CDatabase			 *m_poDatabase;							// Pointer to job and system database.
	CJob					 *m_poJob;									// Pointer to job information.
	CApplicatorControl m_oApplicatorControl;					// The main PACS controller.

	CStringArray	m_csJobArray;							// A list of jobs in the database.

	long m_lLabelCount;
	long m_lPanelCount;

	CString m_csCurrentJob;
	long m_lPanelQuantity;
	BOOL m_bError;
	int m_nCurrentSelect;
	BOOL m_bJobSelected;
	void RefreshDisplay();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PACSDLG_H__AD71074B_9E4A_11D2_A2AB_006008043EC4__INCLUDED_)
