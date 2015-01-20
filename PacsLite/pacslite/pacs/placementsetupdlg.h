#if !defined(AFX_PLACEMENTSETUPDLG_H__44718753_613F_11D4_8123_00B0D02FFCB4__INCLUDED_)
#define AFX_PLACEMENTSETUPDLG_H__44718753_613F_11D4_8123_00B0D02FFCB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlacementSetupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlacementSetupDlg dialog

class CPlacementSetupDlg : public CDialog
{
// Construction
public:
	CPlacementSetupDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPlacementSetupDlg)
	enum { IDD = IDD_PLACEMENT };
	int		m_nFrontDown;
	int		m_nFrontAcross;
	int		m_nSideAcross;
	int		m_nSideWidth;
	CString	m_csText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlacementSetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlacementSetupDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLACEMENTSETUPDLG_H__44718753_613F_11D4_8123_00B0D02FFCB4__INCLUDED_)
