#if !defined(AFX_POINTDLG_H__6E9F60A2_A4AA_11D2_A68A_641A11C1FB5F__INCLUDED_)
#define AFX_POINTDLG_H__6E9F60A2_A4AA_11D2_A68A_641A11C1FB5F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PointDlg.h : header file
//

#include "mdcoptionbutton.h"

#include "Database.h"
#include "NSPointDlgResource.h"
#include "definitions.h"


/////////////////////////////////////////////////////////////////////////////
// CPointDlg dialog

class AFX_MFC_EXT_TYPE CPointDlg : public CDialog
{
// Construction
public:
	CPointDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPointDlg)
	enum { IDD = IDD_POINT_DLG };
	CButton	m_chkEnableScan;
	CComboBox	m_cmbPrinterSelection;
	CComboBox	m_cmbTemplates;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPointDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPointDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickOk();
	afx_msg void OnClickCancel();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL TemplateMatchesPrinter(CString csTemplateName, CString csPrinterName);
	CString	m_csInitialRotation;

public:
	CDatabase *m_poDatabase;
	CString m_csPlacementAttribute;
	BOOL m_bManualEdit;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POINTDLG_H__6E9F60A2_A4AA_11D2_A68A_641A11C1FB5F__INCLUDED_)
