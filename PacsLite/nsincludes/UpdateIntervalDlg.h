#if !defined(AFX_UPDATEINTERVALDLG_H__58F4F442_A928_11D2_A2AB_006008043EC4__INCLUDED_)
#define AFX_UPDATEINTERVALDLG_H__58F4F442_A928_11D2_A2AB_006008043EC4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// UpdateIntervalDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUpdateIntervalDlg dialog

#include "definitions.h"
#include "NSUpdateIntervalDlgResource.h"

class AFX_MFC_EXT_TYPE CUpdateIntervalDlg : public CDialog
{
// Construction
public:
	CUpdateIntervalDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUpdateIntervalDlg)
	enum { IDD = IDD_UPDATE_INTERVAL_DLG };
	CEdit	m_txtUpdateInterval;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUpdateIntervalDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUpdateIntervalDlg)
	afx_msg void OnClickOk();
	afx_msg void OnClickCancel();
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int	m_nUpdateInterval;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPDATEINTERVALDLG_H__58F4F442_A928_11D2_A2AB_006008043EC4__INCLUDED_)
