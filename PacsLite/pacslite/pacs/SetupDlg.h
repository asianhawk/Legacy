//{{AFX_INCLUDES()
#include "commandbutton.h"
//}}AFX_INCLUDES
#if !defined(AFX_SETUPDLG_H__F7538022_A225_11D2_A68A_641A11C1FB5F__INCLUDED_)
#define AFX_SETUPDLG_H__F7538022_A225_11D2_A68A_641A11C1FB5F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SetupDlg.h : header file
//


#include "Database.h"
#include "Job.h"
#include "PrinterControl.h"
#include "ScannerControl.h"
#include "DioController.h"

#include "ApplicatorControl.h"


/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog

class CSetupDlg : public CDialog
{
// Construction
public:
	CSetupDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetupDlg)
	enum { IDD = IDD_SETUP_DLG };
	CCommandButton	m_btnFeederSetup;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetupDlg)
	afx_msg void OnClickCmdChangePassword();
	afx_msg void OnClickCmdEditJob();
	afx_msg void OnClickCmdPrinterSetup();
	afx_msg void OnClickOk();
	afx_msg void OnClickCmdScannerSetup();
	afx_msg void OnClickCmdDeleteJob();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickTemplateSetup();
	afx_msg void OnClickCmdWysiwyg();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void UpdateTemplateDB();
	void UpdateDB(CString csLabelTemplate,
				  CString csTemplateName);

	void SetDatabaseObject ( CDatabase *poDatabase );
	void SetPrinterControlObject ( CPrinterControl *poPrinterControl );
	void SetScannerControlObject ( CScannerControl *poScannerControl );
	void SetDIOController ( CDioController *poDioController );

	CApplicatorControl  *m_poApplicatorControl; 
	CString				m_csJobName;				// name of selected job in PACSDlg
	
	CString ReplaceKeyWord(CString csTemplate, CString csKeyWord, CString csValue);

private:
	CDatabase			*m_poDatabase;			// Pointer to the job and system database.
	CPrinterControl		*m_poPrinterControl;	// Pointer to printer control object.
	CScannerControl		*m_poScannerControl;	// Pointer to scanner control object.
	CDioController		*m_poDioController;  //pointer to DIO control class


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUPDLG_H__F7538022_A225_11D2_A68A_641A11C1FB5F__INCLUDED_)
