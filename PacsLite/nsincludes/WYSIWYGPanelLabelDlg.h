//{{AFX_INCLUDES()
#include "commandbutton.h"
//}}AFX_INCLUDES
#if !defined(AFX_WYSIWYGPANELLABELDLG_H__D7880FA3_F684_11D2_A68A_641A11C1FB5F__INCLUDED_)
#define AFX_WYSIWYGPANELLABELDLG_H__D7880FA3_F684_11D2_A68A_641A11C1FB5F__INCLUDED_


typedef CArray<LPUNKNOWN, LPUNKNOWN> IUnknownArray;
typedef CArray<CLSID, const CLSID&>  CLSIDArray;

#include "Database.h"
#include "Job.h"	


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WYSIWYGPanelLabelDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWYSIWYGPanelLabelDlg dialog

class CWYSIWYGPanelLabelDlg : public CDialog
{
// Construction
public:
	CWYSIWYGPanelLabelDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWYSIWYGPanelLabelDlg)
	enum { IDD = IDD_WYSIWYG_PANEL_LABEL_DLG };
	CEdit	m_edtLabelStockYOffset;
	CEdit	m_edtLabelStockXOffset;
	CEdit	m_edtYOffset;
	CEdit	m_edtXOffset;
	CListBox	m_lstLabelList;
	CEdit	m_edtPanelSelection;
	CCommandButton	m_btnEditPoint;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWYSIWYGPanelLabelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWYSIWYGPanelLabelDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickOk();
	afx_msg void OnClickCancel();
	afx_msg void OnClickBrowse();
	afx_msg void OnClickPointEdit();
	afx_msg void OnSelChangeLabelPositions();
	afx_msg void OnClickViewLabels();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

  BOOL OLEProperties(HWND hwndOwner, LPCSTR szTitle, IUnknownArray& aUnks, CLSIDArray& aCLSIDs);
  void GetOLEPropPages(LPUNKNOWN lpObj, IUnknownArray& aUnks, CLSIDArray& aCLSIDs);


private:
	CString m_csPanelDesign;
	long m_lXPanelDim;
	long m_lYPanelDim;
	CString m_csPlacementAttributes;
	CString m_csOriginalAttributes;

private:
	BOOL GetLabel();
	void GetExistingAttributes ( CString csPoints, CString *csPrinterType, CString *csScannerEnable );


public:
	CString m_csJobName;				// Job name passed from parent
	CJob m_oJob;						// Job object built from job name
	CDatabase *m_poDatabase;		// Pointer to database object.


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WYSIWYGPANELLABELDLG_H__D7880FA3_F684_11D2_A68A_641A11C1FB5F__INCLUDED_)
