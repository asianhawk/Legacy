#if !defined(AFX_SETUPFEEDER_H__87CDF542_C25B_11D2_B805_9EBB88208F38__INCLUDED_)
#define AFX_SETUPFEEDER_H__87CDF542_C25B_11D2_B805_9EBB88208F38__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SetupFeeder.h : header file
//

#include "Database.h"

/////////////////////////////////////////////////////////////////////////////
// CSetupFeeder dialog

class CSetupFeeder : public CDialog
{
// Construction
public:
	CSetupFeeder(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetupFeeder)
	enum { IDD = IDD_SETUP_FEEDER_DLG };
	CEdit	m_edtYPrePick;
	CEdit	m_edtYPick;
	CEdit	m_edtXPrePick;
	CEdit	m_edtXPick;
	CEdit	m_edtRotPrePick;
	CEdit	m_edtRotPick;
	CComboBox	m_cmbFeederList;
	CButton	m_chkEnableFeeder;
	CEdit	m_edtAdvanceLabelDelay;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetupFeeder)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetupFeeder)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickCancel();
	afx_msg void OnClickOk();
	afx_msg void OnEnableFeeder();
	afx_msg void OnSelChangeFeederSelection();
	afx_msg void OnClickUpdate();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void DisplayAttributes();
	void DisplayList(); 

	CString m_csCurrentFeeder;
	CString m_csFeederList;

public:
	CDatabase *m_poDatabase;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUPFEEDER_H__87CDF542_C25B_11D2_B805_9EBB88208F38__INCLUDED_)
