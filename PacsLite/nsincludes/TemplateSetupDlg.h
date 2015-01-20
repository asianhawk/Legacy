#if !defined(AFX_TEMPLATESETUPDLG_H__4D0C1C62_12BB_11D3_BFC3_B1DB7740A138__INCLUDED_)
#define AFX_TEMPLATESETUPDLG_H__4D0C1C62_12BB_11D3_BFC3_B1DB7740A138__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TemplateSetupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTemplateSetupDlg dialog
#include "definitions.h"
#include "NSTemplateSetupDlgResource.h"


class AFX_MFC_EXT_TYPE CTemplateSetupDlg : public CDialog
{
// Construction
public:
	CDatabase * m_poDatabase;
	CTemplateSetupDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTemplateSetupDlg)
	enum { IDD = IDD_TEMPLATE_SETUP };
	CComboBox	m_cmbTemplates;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTemplateSetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTemplateSetupDlg)
	afx_msg void OnClickDone();
	afx_msg void OnClickEdit();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickDelete();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void BuildTemplateList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEMPLATESETUPDLG_H__4D0C1C62_12BB_11D3_BFC3_B1DB7740A138__INCLUDED_)
