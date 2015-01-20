#if !defined(AFX_INTERNALSETUPDLG_H__052A22E2_DBA5_11D2_A68A_641A11C1FB5F__INCLUDED_)
#define AFX_INTERNALSETUPDLG_H__052A22E2_DBA5_11D2_A68A_641A11C1FB5F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// InternalSetupDlg.h : header file
//
#include "NSInternalSetupResource.h"
#include "mdcoptionbutton.h"

#include <afxdao.h>
#include "definitions.h"




/////////////////////////////////////////////////////////////////////////////
// CInternalSetupDlg dialog

class AFX_MFC_EXT_TYPE CInternalSetupDlg : public CDialog
{
// Construction
public:
	CInternalSetupDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInternalSetupDlg)
	enum { IDD = IDD_INTERNAL_SETUP_DLG };
	CEdit	m_edtSettings;
	CEdit	m_edtTriggerDelay;
	CEdit	m_edtPortID;
	CEdit	m_edtOutputAddress;
	CEdit	m_edtOutBufferSize;
	CEdit	m_edtInputAddress;
	CEdit	m_edtInBufferSize;
	CComboBox	m_listDevice;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInternalSetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInternalSetupDlg)
	afx_msg void OnClickOk();
	afx_msg void OnClickCancel();
	afx_msg void OnSelChangeDeviceList();
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:


private:
	void BuildDeviceData ( CString csDevice );
	void SetDeviceData ( void );

	CStringArray m_csaDeviceInfo;
	int m_nLastSelected;



	BOOL Initialize ( void );

	BOOL GetDIOAddress ( CString * csInput, CString * csOutput );
	BOOL GetComPortAttributes ( CString csName,
										 int *nTriggerDelay,
										 int *nInputBufferSize,
										 int *nOutputBufferSize,
										 int *nPortID,
										 CString *csPortSettings );
	BOOL GetDeviceNames ( CString *csDevices );
	BOOL SetDIOAddress ( CString csInput, CString csOutput );
	BOOL SetComPortAttributes ( CString csName,
										 int nTriggerDelay,
										 int nInputBufferSize,
										 int nOutputBufferSize,
										 int nPortID,
										 CString csPortSettings );

	CDaoDatabase	m_dbJobDatabase;						// DAO Database object.

	BOOL Open();												// Open the database.
	void Close();												// Close the database.



	BOOL IsNumeric ( CString csNumber );
	BOOL IsValidHex ( CString csNumber, int nMinSize, int nMaxSize );
	BOOL IsValidSettings ( CString csSettings );
	BOOL IsValidPath ( CString csPath, BOOL bIncludesFile );
	BOOL CheckPositionFormat ( CString csPosition );




};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERNALSETUPDLG_H__052A22E2_DBA5_11D2_A68A_641A11C1FB5F__INCLUDED_)
