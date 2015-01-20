//{{AFX_INCLUDES()
#include "commandbutton.h"
#include "customflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_ADDEDITJOBDLG_H__7AFE6F03_C113_11D2_A68A_641A11C1FB5F__INCLUDED_)
#define AFX_ADDEDITJOBDLG_H__7AFE6F03_C113_11D2_A68A_641A11C1FB5F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AddEditJobDlg.h : header file
//



#include "Database.h"
#include "Job.h"

#include "definitions.h"
#include "NSAddEditJobDlgResource.h"


/////////////////////////////////////////////////////////////////////////////
// CAddEditJobDlg dialog

class AFX_MFC_EXT_TYPE CAddEditJobDlg : public CDialog
{
// Construction
public:
	CAddEditJobDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL GetJobInfo ();
	void ResetGrid();
	BOOL GetJobInfoData1();
	BOOL GetJobInfoData2();
	BOOL GetJobInfoData3();
	BOOL GetJobInfoData4();
	BOOL GetJobInfoData5();

// Dialog Data
	//{{AFX_DATA(CAddEditJobDlg)
	enum { IDD = IDD_ADD_EDIT_JOB_DLG };
	CEdit	m_edtCustomer;
	CEdit	m_edtDescription;
	CButton	m_chkUseSerialization;
	CComboBox	m_cmbJobList;
	CCommandButton	m_btnSetupSerialization;
	CString	m_csDescription;
	CFlexGrid	m_FGJobInfo;
	CString	m_csCustomer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddEditJobDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	void InitJobInfoGrid();
	void AddJobInfoToFlexGrid();
	BOOL GetSerialJobInfo ();
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddEditJobDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickUpdateJob();
	afx_msg void OnClickCancel();
	afx_msg void OnSelChangeListJob();
	afx_msg void OnClickEditPanelLabel();
	afx_msg void OnClickAddJob();
	afx_msg void OnUseSerialization();
	afx_msg void OnClickSetupSerialization();
	afx_msg void OnSelchangeJobList();
	afx_msg void OnClickCopyJob();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	BOOL	m_bUseWYSIWYG;
	void ListJobs( void );
	CStringArray	m_csJobArray;		// A list of jobs in the database.
	CJob				m_oJob;				// A job container.
public:
	BOOL m_bUseStaticDateCode;
	CString m_csStaticDateCode;
	CString m_csRelease;
	CString m_csManufacturingSite;
	CString m_csCountry;
	CString m_csProductCode;
	CString	m_csJobName;
	CDatabase *m_poDatabase;
	BOOL m_bUseSerialization;
	int m_nSNType;
	int m_nSNLength;
	CString m_csStartingSN;
	BOOL m_blnJulianDate;
	BOOL CheckForExistingJobRecord(CString csJobName);

// added for check digit handling

	BOOL m_blnUseCheckDigit;
	CString m_csCheckDigitType;
	CString m_csCheckDigitSource;
private:
	BOOL m_blnPriorSuffix;


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDEDITJOBDLG_H__7AFE6F03_C113_11D2_A68A_641A11C1FB5F__INCLUDED_)
