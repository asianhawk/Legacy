//{{AFX_INCLUDES()
#include "commandbutton.h"
//}}AFX_INCLUDES
#if !defined(AFX_PRINTERSETUPDLG_H__009E5442_B8EA_11D2_A2AB_006008043EC4__INCLUDED_)
#define AFX_PRINTERSETUPDLG_H__009E5442_B8EA_11D2_A2AB_006008043EC4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PrinterSetupDlg.h : header file
//


#include "Database.h"

#include "definitions.h"
#include "NSPrinterSetupDlgResource.h"


/////////////////////////////////////////////////////////////////////////////
// CPrinterSetupDlg dialog

class AFX_MFC_EXT_TYPE CPrinterSetupDlg : public CDialog
{
// Construction
public:
	CPrinterSetupDlg(CWnd* pParent = NULL);   // standard constructor


// Dialog Data
	//{{AFX_DATA(CPrinterSetupDlg)
	enum { IDD = IDD_SETUP_PRINTER_DLG };
	CComboBox	m_cmbPrinterType;
	CComboBox	m_cmbPrinterSelection;
	CButton	m_chkEnable;
	CCommandButton	m_btnUpdate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrinterSetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrinterSetupDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickOk();
	afx_msg void OnClickCancel();
	afx_msg void OnEnable();
	afx_msg void OnSelChangePrinterSelection();
	afx_msg void OnSelChangePrinterType();
	afx_msg void OnClickUpdate();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CDatabase m_poDatabase;



private:
	void DisplayList(); 
	void DisplayAttributes(); 

	CString m_csCurrentPrinter;
	CString m_csPrinterList;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTERSETUPDLG_H__009E5442_B8EA_11D2_A2AB_006008043EC4__INCLUDED_)
