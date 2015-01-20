#if !defined(AFX_DBLABELSELECTIONDLG_H__A8AB15E2_DC73_11D2_A68A_641A11C1FB5F__INCLUDED_)
#define AFX_DBLABELSELECTIONDLG_H__A8AB15E2_DC73_11D2_A68A_641A11C1FB5F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DBLabelSelectionDlg.h : header file
//

#include "definitions.h"
#include "NSLabelSelectionDlgResource.h"

/////////////////////////////////////////////////////////////////////////////
// CDBLabelSelectionDlg dialog

class AFX_MFC_EXT_TYPE CDBLabelSelectionDlg : public CDialog
{
// Construction
public:
	CDBLabelSelectionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDBLabelSelectionDlg)
	enum { IDD = IDD_LABEL_SELECT_DLG };
	CListBox	m_lstLabelPositions;
	int		m_nLabelCount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBLabelSelectionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDBLabelSelectionDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickOk();
	afx_msg void OnClickCancel();
	afx_msg void OnSelChangeLabelPositions();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CJob * m_poJob;
	int m_nLabel;
private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBLABELSELECTIONDLG_H__A8AB15E2_DC73_11D2_A68A_641A11C1FB5F__INCLUDED_)
