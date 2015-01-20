//{{AFX_INCLUDES()
#include "commandbutton.h"
//}}AFX_INCLUDES
#if !defined(AFX_DIAGDLG_H__0EC1F0E2_E5B8_11D2_B806_9EBB88208F38__INCLUDED_)
#define AFX_DIAGDLG_H__0EC1F0E2_E5B8_11D2_B806_9EBB88208F38__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DiagDlg.h : header file
//

#include "DioController.h"
#include "PrinterControl.h"
#include "ScannerControl.h"
#include "PACSDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CDiagDlg dialog

class CDiagDlg : public CDialog
{
// Construction
public:
	CPACSDlg * m_poPACSDlg;
	CDioController * m_poDIOController;
	CScannerControl * m_poScannerControl;
	CPrinterControl * m_poPrinterControl;
	CDiagDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDiagDlg)
	enum { IDD = IDD_DIAGNOSTICS };
	CCommandButton	m_cmdScanner;
	CCommandButton	m_cmdPrinter;
	CCommandButton	m_cmdDIO;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiagDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDiagDlg)
	afx_msg void OnClickCloseDiagnostics();
	afx_msg void OnClickDioDiagnostics();
	afx_msg void OnClickPrinterDiagnostics();
	afx_msg void OnClickScannerDiagnostics();
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIAGDLG_H__0EC1F0E2_E5B8_11D2_B806_9EBB88208F38__INCLUDED_)
