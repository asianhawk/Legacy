//{{AFX_INCLUDES()
#include "labelcontrol.h"
#include "commandbutton.h"
//}}AFX_INCLUDES
#if !defined(AFX_RESCANDLG_H__AEC4DE02_C316_11D2_A2AB_006008043EC4__INCLUDED_)
#define AFX_RESCANDLG_H__AEC4DE02_C316_11D2_A2AB_006008043EC4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RescanDlg.h : header file
//



enum recovery
{
	RELABEL_RECOVERY,
	RESCAN_RECOVERY,
	HALT_RECOVERY
};


/////////////////////////////////////////////////////////////////////////////
// CRescanDlg dialog

class CRescanDlg : public CDialog
{
// Construction
public:
	CRescanDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRescanDlg)
	enum { IDD = IDD_RESCAN_DLG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRescanDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRescanDlg)
	afx_msg void OnClickHaltButton();
	afx_msg void OnClickRelabelButton();
	afx_msg void OnClickRescanButton();
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int	m_nRecovery;		// Type of scan recovery.
	BOOL m_bReSync;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESCANDLG_H__AEC4DE02_C316_11D2_A2AB_006008043EC4__INCLUDED_)
