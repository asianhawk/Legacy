#if !defined(AFX_JOBNAMEDLG_H__B1FE65C2_DADE_11D2_A68A_641A11C1FB5F__INCLUDED_)
#define AFX_JOBNAMEDLG_H__B1FE65C2_DADE_11D2_A68A_641A11C1FB5F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// JobNameDlg.h : header file
//
#include "definitions.h"
#include "NSEnterJobNameDlgResource.h"


/////////////////////////////////////////////////////////////////////////////
// CJobNameDlg dialog

class DllExport CJobNameDlg : public CDialog
{
// Construction
public:
	CJobNameDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CJobNameDlg)
	enum { IDD = IDD_JOB_NAME_DLG };
	CEdit	m_edtJobName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJobNameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CJobNameDlg)
	afx_msg void OnClickOk();
	afx_msg void OnClickCancel();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CString m_csJobName;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JOBNAMEDLG_H__B1FE65C2_DADE_11D2_A68A_641A11C1FB5F__INCLUDED_)
