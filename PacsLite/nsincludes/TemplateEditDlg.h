//{{AFX_INCLUDES()
#include "richtext.h"
//}}AFX_INCLUDES
#if !defined(AFX_TEMPLATEEDITDLG_H__1F426482_BF1C_11D2_A68A_641A11C1FB5F__INCLUDED_)
#define AFX_TEMPLATEEDITDLG_H__1F426482_BF1C_11D2_A68A_641A11C1FB5F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TemplateEditDlg.h : header file
//


#include "definitions.h"
#include "NSTEmplateEditDlgResource.h"

/////////////////////////////////////////////////////////////////////////////
// CTemplateEditDlg dialog

class AFX_MFC_EXT_TYPE CTemplateEditDlg : public CDialog
{
// Construction
public:
	CTemplateEditDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTemplateEditDlg)
	enum { IDD = IDD_TEMPLATE_EDIT_DLG };
	CRichText	m_txtTemplate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTemplateEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTemplateEditDlg)
	afx_msg void OnClickOk();
	afx_msg void OnClickCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickSaveAsNew();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CDatabase * m_poDatabase;
	CString m_csTemplateName;
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEMPLATEEDITDLG_H__1F426482_BF1C_11D2_A68A_641A11C1FB5F__INCLUDED_)
