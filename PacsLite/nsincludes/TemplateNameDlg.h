#if !defined(AFX_TEMPLATENAMEDLG_H__1F426483_BF1C_11D2_A68A_641A11C1FB5F__INCLUDED_)
#define AFX_TEMPLATENAMEDLG_H__1F426483_BF1C_11D2_A68A_641A11C1FB5F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TemplateNameDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTemplateNameDlg dialog

#include "NSTemplateNameDlgResource.h"
#include "definitions.h"

class AFX_MFC_EXT_TYPE CTemplateNameDlg : public CDialog
{
// Construction
public:
	CTemplateNameDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTemplateNameDlg)
	enum { IDD = IDD_TEMPLATENAME_DLG };
	CEdit	m_txtTemplateName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTemplateNameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTemplateNameDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnClickOk();
	afx_msg void OnClickCancel();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CString m_csTemplateName;

};
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEMPLATENAMEDLG_H__1F426483_BF1C_11D2_A68A_641A11C1FB5F__INCLUDED_)
