#if !defined(AFX_DELETEJOBDLG_H__4631DB02_BF5A_11D2_A2AB_006008043EC4__INCLUDED_)
#define AFX_DELETEJOBDLG_H__4631DB02_BF5A_11D2_A2AB_006008043EC4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DeleteJobDlg.h : header file
//

#include "Database.h"
#include "NSDeleteJobDlgResource.h"
#include "definitions.h"


/////////////////////////////////////////////////////////////////////////////
// CDeleteJobDlg dialog

class AFX_MFC_EXT_TYPE CDeleteJobDlg : public CDialog
{
// Construction
public:
	CDeleteJobDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDeleteJobDlg)
	enum { IDD = IDD_DELETE_JOB_DLG };
	CComboBox	m_cmbJobList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeleteJobDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDeleteJobDlg)
	afx_msg void OnClickCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelChangeJobList();
	afx_msg void OnClickDeleteJob();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CDatabase *m_poDatabase;

	CString	m_csJobName;

private:
	void ListJobs ( void );


	CStringArray	m_csJobArray;		// A list of jobs in the database.



};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELETEJOBDLG_H__4631DB02_BF5A_11D2_A2AB_006008043EC4__INCLUDED_)
