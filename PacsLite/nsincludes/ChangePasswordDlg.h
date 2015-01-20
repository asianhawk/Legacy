#if !defined(AFX_CHANGEPASSWORDDLG_H__198D3384_A324_11D2_A68A_641A11C1FB5F__INCLUDED_)
#define AFX_CHANGEPASSWORDDLG_H__198D3384_A324_11D2_A68A_641A11C1FB5F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ChangePasswordDlg.h : header file
//
#include "ChangePasswordDlgResource.h"
#define	PW_OFFSET			45


/////////////////////////////////////////////////////////////////////////////
// CChangePasswordDlg dialog
#include "definitions.h"


class AFX_MFC_EXT_TYPE CChangePasswordDlg : public CDialog
{
// Construction
public:
	CChangePasswordDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChangePasswordDlg)
	enum { IDD = IDD_CHANGE_PASSWORD_DLG };
	CEdit	m_txtPassword;
	CEdit	m_txtConfirmPassword;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangePasswordDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChangePasswordDlg)
	afx_msg void OnClickOk();
	afx_msg void OnClickCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdatePassword();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	CString Encrypt ( CString csPassword ); 

	BOOL m_bPasswordChange;

public:
	CString m_csPassword;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGEPASSWORDDLG_H__198D3384_A324_11D2_A68A_641A11C1FB5F__INCLUDED_)
