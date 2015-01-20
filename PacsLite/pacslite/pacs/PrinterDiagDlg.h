//{{AFX_INCLUDES()
#include "mdctext.h"
#include "commandbutton.h"
//}}AFX_INCLUDES
#if !defined(AFX_PRINTERDIAGDLG_H__F5235E23_E5DB_11D2_B806_9EBB88208F38__INCLUDED_)
#define AFX_PRINTERDIAGDLG_H__F5235E23_E5DB_11D2_B806_9EBB88208F38__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PrinterDiagDlg.h : header file
//

#include "PrinterControl.h"

/////////////////////////////////////////////////////////////////////////////
// CPrinterDiagDlg dialog

class CPrinterDiagDlg : public CDialog
{
// Construction
public:
	CDatabase * m_poDatabase;
	CPrinterControl * m_poPrinterControl;
	CPrinterDiagDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrinterDiagDlg)
	enum { IDD = IDD_PRINTER_DIAGNOSTICS };
	CComboBox	m_printerSelected;
	CMdcText	m_printerStatus;
	CCommandButton	m_formFeed;
	CCommandButton	m_setDefaults;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrinterDiagDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrinterDiagDlg)
	afx_msg void OnClickClosePrinterDiagnostics();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangePrinterSelected();
	afx_msg void OnClickSetDefaults();
	afx_msg void OnClickFormFeed();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void DisplayList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTERDIAGDLG_H__F5235E23_E5DB_11D2_B806_9EBB88208F38__INCLUDED_)
