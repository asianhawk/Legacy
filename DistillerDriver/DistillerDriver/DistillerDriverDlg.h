
// DistillerDriverDlg.h : header file
//

#pragma once


// CDistillerDriverDlg dialog
class CDistillerDriverDlg : public CDialogEx
{
// Construction
public:
	CDistillerDriverDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DISTILLERDRIVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	CString m_strSourceDir;
	CString m_strTargetDir;
	CString m_strOptionsFile;
	CString m_strWorkOrder;


	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:


private:

	BOOL GetDirectory(CString &csDirectory);
public:
	afx_msg void OnEnSetfocusTxbSourceDirectory();
	afx_msg void OnEnSetfocusTxbTargetDirectory();
	afx_msg void OnEnSetfocusTxbOptionsfile();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnKillfocusTxbWorkorder();
};
