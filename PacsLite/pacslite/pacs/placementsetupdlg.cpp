// PlacementSetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pacs.h"
#include "PlacementSetupDlg.h"
#include "PlacementSchemaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlacementSetupDlg dialog


CPlacementSetupDlg::CPlacementSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlacementSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlacementSetupDlg)
	m_nFrontDown = 2;
	m_nFrontAcross = 10;
	m_nSideAcross = 34;
	m_nSideWidth = 8;
	m_csText = _T("");
	//}}AFX_DATA_INIT
}


void CPlacementSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlacementSetupDlg)
	DDX_Text(pDX, IDC_FRONT_DOWN, m_nFrontDown);
	DDX_Text(pDX, IDC_FRONT_ACROSS, m_nFrontAcross);
	DDX_Text(pDX, IDC_SIDE_ACROSS, m_nSideAcross);
	DDX_Text(pDX, IDC_SIDE_WIDTH, m_nSideWidth);
	DDX_Text(pDX, IDC_COMMENTS, m_csText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlacementSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CPlacementSetupDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlacementSetupDlg message handlers

void CPlacementSetupDlg::OnOK() 
{
	UpdateData(TRUE);
	CPlacementSchemaDlg oPlacementSchemaDlg;
	oPlacementSchemaDlg.m_nFrontDown = m_nFrontDown;
	oPlacementSchemaDlg.m_nFrontAcross = m_nFrontAcross;
	oPlacementSchemaDlg.m_nSideAcross = m_nSideAcross;
	oPlacementSchemaDlg.m_nSideWidth = m_nSideWidth;
	oPlacementSchemaDlg.m_csText = m_csText;
	oPlacementSchemaDlg.DoModal();
	
	CDialog::OnOK();
}

BOOL CPlacementSetupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
