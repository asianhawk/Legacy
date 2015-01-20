// ReSyncDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pacs.h"
#include "ReSyncDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReSyncDlg dialog


CReSyncDlg::CReSyncDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReSyncDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReSyncDlg)
	m_csNewSerialNumber = _T("");
	m_csPrintedSerialNumber = _T("");
	m_csScannedSerialNumber = _T("");
	m_nAdjustIndex = 0;
	//}}AFX_DATA_INIT
}


void CReSyncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReSyncDlg)
	DDX_Text(pDX, IDC_NEW_SN, m_csNewSerialNumber);
	DDX_Text(pDX, IDC_PRINTED_SN, m_csPrintedSerialNumber);
	DDX_Text(pDX, IDC_SCANNED_SN, m_csScannedSerialNumber);
	DDX_Text(pDX, IDC_EDT_ADJUSTINDEX, m_nAdjustIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReSyncDlg, CDialog)
	//{{AFX_MSG_MAP(CReSyncDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReSyncDlg message handlers

void CReSyncDlg::OnOK() 
{
	
	UpdateData(TRUE);
	CDialog::OnOK();
}

void CReSyncDlg::OnCancel() 
{
	
	CDialog::OnCancel();
}
