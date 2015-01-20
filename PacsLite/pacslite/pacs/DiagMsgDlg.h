#if !defined(AFX_DIAGMSGDLG_H__20B34AC3_CA6E_11D2_B806_9EBB88208F38__INCLUDED_)
#define AFX_DIAGMSGDLG_H__20B34AC3_CA6E_11D2_B806_9EBB88208F38__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DiagMsgDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDiagMsgDlg dialog

class CDiagMsgDlg : public CDialog
{
// Construction
public:
	CDiagMsgDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDiagMsgDlg)
	enum { IDD = IDD_DIAG_MSG_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiagMsgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDiagMsgDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIAGMSGDLG_H__20B34AC3_CA6E_11D2_B806_9EBB88208F38__INCLUDED_)
