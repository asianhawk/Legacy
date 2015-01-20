#if !defined(AFX_HOLDDLG_H__105C7102_C0AB_11D2_A2AB_006008043EC4__INCLUDED_)
#define AFX_HOLDDLG_H__105C7102_C0AB_11D2_A2AB_006008043EC4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// HoldDlg.h : header file
//

#include "definitions.h"
#include "NSHoldDlgResource.h"
#include "NSDIOMain.h"


enum holdselections
{
	HOLD_SETUP_JOB,
	HOLD_SETUP_SYSTEM,
	HOLD_CONTINUE,
	HOLD_CHANGE_SN,
	HOLD_EXIT
};


/////////////////////////////////////////////////////////////////////////////
// CHoldDlg dialog

class AFX_MFC_EXT_TYPE CHoldDlg : public CDialog
{
// Construction
public:
	CHoldDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHoldDlg)
	enum { IDD = IDD_HOLD_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHoldDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHoldDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickSystemSetup();
	afx_msg void OnClickContinue();
	afx_msg void OnClickExit();
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int	m_nHoldSelection;			// Process to run under hold.
	CDioInput *m_oDIOInput;
	BOOL m_blnDelay;
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOLDDLG_H__105C7102_C0AB_11D2_A2AB_006008043EC4__INCLUDED_)
