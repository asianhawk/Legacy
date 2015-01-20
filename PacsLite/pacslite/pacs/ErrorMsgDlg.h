#if !defined(AFX_ERRORMSGDLG_H__832B3921_1560_11D6_86AE_006008A02E8E__INCLUDED_)
#define AFX_ERRORMSGDLG_H__832B3921_1560_11D6_86AE_006008A02E8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ErrorMsgDlg.h : header file
//
#include "NSDIOMain.h"

/////////////////////////////////////////////////////////////////////////////
// CErrorMsgDlg dialog


class CErrorMsgDlg : public CDialog
{
// Construction
public:
	CErrorMsgDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CErrorMsgDlg)
	enum { IDD = IDD_DLG_ERRORMESSAGE };
	CString	m_csErrorMessage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CErrorMsgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CErrorMsgDlg)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

	CDioInput *m_oDIOInput;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERRORMSGDLG_H__832B3921_1560_11D6_86AE_006008A02E8E__INCLUDED_)
