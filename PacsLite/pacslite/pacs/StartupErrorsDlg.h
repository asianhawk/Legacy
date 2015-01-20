//{{AFX_INCLUDES()
#include "mdctext.h"
#include "labelcontrol.h"
//}}AFX_INCLUDES
#if !defined(AFX_STARTUPERRORSDLG_H__AD5FED82_611C_11D3_996D_006097244796__INCLUDED_)
#define AFX_STARTUPERRORSDLG_H__AD5FED82_611C_11D3_996D_006097244796__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// StartupErrorsDlg.h : header file
//

#include "DioController.h"
#include "PrinterControl.h"
#include "ScannerControl.h"
#include "Database.h"


/////////////////////////////////////////////////////////////////////////////
// CStartupErrorsDlg dialog

class CStartupErrorsDlg : public CDialog
{
// Construction
public:
	CDioController			*m_poDioController;
	CPrinterControl			*m_poPrinterControl;
	CScannerControl			*m_poScannerControl;
	CDatabase				*m_poDatabase;

	CStartupErrorsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStartupErrorsDlg)
	enum { IDD = IDD_STARTUP_ERRORS };
	CMdcText	m_txtboxErrorMessages;
	CLabelControl	m_lblConveyor;
	CLabelControl	m_lblDatabase;
	CLabelControl	m_lblDIO;
	CLabelControl	m_lblPrinter;
	CLabelControl	m_lblScanner;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStartupErrorsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStartupErrorsDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARTUPERRORSDLG_H__AD5FED82_611C_11D3_996D_006097244796__INCLUDED_)
