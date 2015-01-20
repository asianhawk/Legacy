#if !defined(AFX_SCANNERSETUPDLG_H__198D3383_A324_11D2_A68A_641A11C1FB5F__INCLUDED_)
#define AFX_SCANNERSETUPDLG_H__198D3383_A324_11D2_A68A_641A11C1FB5F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ScannerSetupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScannerSetupDlg dialog
#include "definitions.h"
#include "NSSetupScannerDlgResource.h"


class AFX_MFC_EXT_TYPE CScannerSetupDlg : public CDialog
{
// Construction
public:
	CScannerSetupDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScannerSetupDlg)
	enum { IDD = IDD_SETUP_SCANNER_DLG };
	CButton	m_chkEnablePlacementScanner;
	CComboBox	m_lstPlacementScannerType;
	CEdit	m_edtPlacementInitialization;
	BOOL	m_bUsePlacementScanner;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScannerSetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScannerSetupDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickOk();
	afx_msg void OnClickCancel();
	afx_msg void OnPlacementEnableScanner();
	afx_msg void OnPlacementUseScanner();
	afx_msg void OnSelChangePlacementScannerType();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CString	m_csPlacementInitialization;				// Placement scanner initialization string.
	int		m_nPlacementScannerType;					// Placement scanner type.
	int		m_nSystemScannerType;						// System scanner type.
	BOOL		m_bEnablePlacementScanner;					// Enable placement scanner flag.
	CString  m_csPlacementTrigger;
	CString  m_csPlacementTriggerOff;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCANNERSETUPDLG_H__198D3383_A324_11D2_A68A_641A11C1FB5F__INCLUDED_)
