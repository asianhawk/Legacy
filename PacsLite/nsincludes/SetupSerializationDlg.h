#if !defined(AFX_SETUPSERIALIZATIONDLG_H__005EFE02_0D70_11D3_A68A_641A11C1FB5F__INCLUDED_)
#define AFX_SETUPSERIALIZATIONDLG_H__005EFE02_0D70_11D3_A68A_641A11C1FB5F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SetupSerializationDlg.h : header file
//
#include "definitions.h"

#include "NSSerializationResource.h"

/////////////////////////////////////////////////////////////////////////////
// CSetupSerializationDlg dialog

class AFX_MFC_EXT_TYPE CSetupSerializationDlg : public CDialog
{
// Construction
public:
	CSetupSerializationDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetupSerializationDlg)
	enum { IDD = IDD_SETUP_SERIALIZATION_DLG };
	CComboBox	m_cmbCheckDigitType;
	CButton	m_chkUseCheckDigit;
	CButton	m_frmChkDigitSource;
	CComboBox	m_cmbSNType;
	CEdit	m_edtSNStart;
	CEdit	m_edtSNLength;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetupSerializationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetupSerializationDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickOk();
	afx_msg void OnClickCancel();
	afx_msg void OnOptChkDgtSourceComputer();
	afx_msg void OnOptChkDgtSourcePrinter();
	afx_msg void OnChkUseCheckDigit();
	afx_msg void OnSelchangeCmbFormula();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int m_nSNType;
	int m_nSNLength;
	CString m_csStartingSN;
	BOOL	m_blnUseCheckDigit;
	CString	m_csCheckDigitType;
	CString m_csCheckDigitSource;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUPSERIALIZATIONDLG_H__005EFE02_0D70_11D3_A68A_641A11C1FB5F__INCLUDED_)
