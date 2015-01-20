#if !defined(AFX_INITDLGMESSAGE_H__42848702_A9FC_11D2_A68A_641A11C1FB5F__INCLUDED_)
#define AFX_INITDLGMESSAGE_H__42848702_A9FC_11D2_A68A_641A11C1FB5F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// InitDlgMessage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInitDlgMessage dialog

class CInitDlgMessage : public CDialog
{
// Construction
public:
	CInitDlgMessage(CWnd* pParent = NULL);   // standard constructor
	BOOL Create();
	BOOL PeekAndPump();

// Dialog Data
	//{{AFX_DATA(CInitDlgMessage)
	enum { IDD = IDD_INIT_DLG_MESSAGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInitDlgMessage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInitDlgMessage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CWnd* mp_Parent;
	int m_int_ID;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INITDLGMESSAGE_H__42848702_A9FC_11D2_A68A_641A11C1FB5F__INCLUDED_)
