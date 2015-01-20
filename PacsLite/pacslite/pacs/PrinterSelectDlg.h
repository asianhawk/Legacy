#if !defined(AFX_PRINTERSELECTDLG_H__70CD4062_8215_11D3_996D_006097244796__INCLUDED_)
#define AFX_PRINTERSELECTDLG_H__70CD4062_8215_11D3_996D_006097244796__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PrinterSelectDlg.h : header file
//
#include "definitions.h"
#include "resource.h"


/////////////////////////////////////////////////////////////////////////////
// CPrinterSelectDlg dialog

class CPrinterSelectDlg : public CDialog
{
// Construction
public:
	CPrinterSelectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrinterSelectDlg)
	enum { IDD = IDD_PRINTER_TYPE_DLG };
	int		m_nPrinterType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrinterSelectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrinterSelectDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTERSELECTDLG_H__70CD4062_8215_11D3_996D_006097244796__INCLUDED_)
