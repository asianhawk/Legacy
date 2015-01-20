//{{AFX_INCLUDES()
#include "labelcontrol.h"
#include "mdctext.h"
#include "commandbutton.h"
//}}AFX_INCLUDES
#if !defined(AFX_SCANDIAGDLG_H__EC72B804_E84E_11D2_B806_9EBB88208F38__INCLUDED_)
#define AFX_SCANDIAGDLG_H__EC72B804_E84E_11D2_B806_9EBB88208F38__INCLUDED_

// custom message
#define WM_SCANNERDLGTHREADMESSAGE	WM_USER + 53

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ScanDiagDlg.h : header file
//

// prototype thread function
UINT ScannerThreadFunction (LPVOID);

#include "ScannerControl.h"

/////////////////////////////////////////////////////////////////////////////
// CScanDiagDlg dialog

class CScanDiagDlg : public CDialog
{
// Construction
public:
	CString m_systemScannerReset;
	CString m_placementScannerReset;
	CWinThread * m_myThread;
	CScannerControl * m_poScannerControl;
	CScanDiagDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScanDiagDlg)
	enum { IDD = IDD_SCANNER_DIAGNOSTICS };
	CComboBox	m_selectedScanner;
	CMdcText	m_versionString;
	CMdcText	m_returnText;
	CString	m_resetString;
	CCommandButton	m_continuousTrigger;
	CCommandButton	m_singleTrigger;
	CCommandButton	m_closeButton;
	CCommandButton	m_setResetString;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScanDiagDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScanDiagDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickCloseScannerDiagnostics();
	afx_msg void OnClickSingleTrigger();
	afx_msg void OnClickContinuousTrigger();
	afx_msg void OnClickSetResetString();
	afx_msg void OnSelchangeSelectedScanner();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg	void OnThreadMessage(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCANDIAGDLG_H__EC72B804_E84E_11D2_B806_9EBB88208F38__INCLUDED_)
