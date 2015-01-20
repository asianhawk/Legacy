#if !defined(AFX_PASSWORDDLG_H__081ABF63_B854_11D2_A68A_641A11C1FB5F__INCLUDED_)
#define AFX_PASSWORDDLG_H__081ABF63_B854_11D2_A68A_641A11C1FB5F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PasswordDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPasswordDlg dialog
#include "NSPasswordDlgResource.h"
#include "definitions.h"



class AFX_MFC_EXT_TYPE CPasswordDlg : public CDialog
{
// Construction
public:
	CPasswordDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPasswordDlg)
	enum { IDD = IDD_PASSWORD_DLG };
	CEdit	m_txtPassword;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPasswordDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPasswordDlg)
	afx_msg void OnClickOk();
	afx_msg void OnClickCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CString m_csPassword;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PASSWORDDLG_H__081ABF63_B854_11D2_A68A_641A11C1FB5F__INCLUDED_)
