#if !defined(AFX_RESYNCDLG_H__5D46C081_B251_11D4_BED7_000000000700__INCLUDED_)
#define AFX_RESYNCDLG_H__5D46C081_B251_11D4_BED7_000000000700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReSyncDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReSyncDlg dialog

class CReSyncDlg : public CDialog
{
// Construction
public:
	CReSyncDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReSyncDlg)
	enum { IDD = IDD_RESYNC };
	CString	m_csNewSerialNumber;
	CString	m_csPrintedSerialNumber;
	CString	m_csScannedSerialNumber;
	int		m_nAdjustIndex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReSyncDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReSyncDlg)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESYNCDLG_H__5D46C081_B251_11D4_BED7_000000000700__INCLUDED_)
