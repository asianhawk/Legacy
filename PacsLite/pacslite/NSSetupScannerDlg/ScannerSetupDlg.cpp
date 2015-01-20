// ScannerSetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScannerSetupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScannerSetupDlg dialog


CScannerSetupDlg::CScannerSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScannerSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScannerSetupDlg)
	m_bUsePlacementScanner = FALSE;
	//}}AFX_DATA_INIT
}


void CScannerSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScannerSetupDlg)
	DDX_Control(pDX, IDC_PLACEMENT_ENABLE_SCANNER, m_chkEnablePlacementScanner);
	DDX_Control(pDX, IDC_PLACEMENT_SCANNERTYPE, m_lstPlacementScannerType);
	DDX_Control(pDX, IDC_PLACEMENT_INITIALIZATION_STRING, m_edtPlacementInitialization);
	DDX_Check(pDX, IDC_PLACEMENT_USE_SCANNER, m_bUsePlacementScanner);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScannerSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CScannerSetupDlg)
	ON_BN_CLICKED(IDC_PLACEMENT_ENABLE_SCANNER, OnPlacementEnableScanner)
	ON_BN_CLICKED(IDC_PLACEMENT_USE_SCANNER, OnPlacementUseScanner)
	ON_CBN_SELCHANGE(IDC_PLACEMENT_SCANNERTYPE, OnSelChangePlacementScannerType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScannerSetupDlg message handlers

BEGIN_EVENTSINK_MAP(CScannerSetupDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CScannerSetupDlg)
	ON_EVENT(CScannerSetupDlg, IDOK, -600 /* Click */, OnClickOk, VTS_NONE)
	ON_EVENT(CScannerSetupDlg, IDCANCEL, -600 /* Click */, OnClickCancel, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()



BOOL CScannerSetupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	// Initialize data.

	m_edtPlacementInitialization.SetWindowText ( m_csPlacementInitialization );
	m_lstPlacementScannerType.SetCurSel ( m_nPlacementScannerType );
	if ( m_bEnablePlacementScanner )
		m_chkEnablePlacementScanner.SetCheck ( TRUE );
	else
		m_chkEnablePlacementScanner.SetCheck ( FALSE );

	


	if ( !m_bUsePlacementScanner )
	{
		
		m_edtPlacementInitialization.EnableWindow ( FALSE );
		m_lstPlacementScannerType.EnableWindow ( FALSE );
		m_chkEnablePlacementScanner.EnableWindow ( FALSE );
	}



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}






void CScannerSetupDlg::OnClickOk() 
{

	// Get reset strings and verify.

	if ( m_bUsePlacementScanner && m_bEnablePlacementScanner )
	{

		m_edtPlacementInitialization.GetWindowText ( m_csPlacementInitialization );
		
		// Verify.

	}


	CDialog::OnOK();
	
}



void CScannerSetupDlg::OnClickCancel() 
{

	CDialog::OnCancel();
	
}



void CScannerSetupDlg::OnPlacementEnableScanner() 
{

	m_bEnablePlacementScanner = m_chkEnablePlacementScanner.GetCheck();

	if ( !m_bEnablePlacementScanner )
	{
		m_edtPlacementInitialization.EnableWindow ( FALSE );
		m_lstPlacementScannerType.EnableWindow ( FALSE );
	}
	else
	{
		m_edtPlacementInitialization.EnableWindow ( TRUE );
		m_lstPlacementScannerType.EnableWindow ( TRUE );
	}
	
}



void CScannerSetupDlg::OnPlacementUseScanner() 
{

	UpdateData ( TRUE );		// Get dialog information.

	if ( !m_bUsePlacementScanner )
	{
		m_edtPlacementInitialization.EnableWindow ( FALSE );
		m_lstPlacementScannerType.EnableWindow ( FALSE );
		m_chkEnablePlacementScanner.EnableWindow ( FALSE );
	}
	else
	{
		m_chkEnablePlacementScanner.EnableWindow ( TRUE );
		if ( m_bEnablePlacementScanner )
		{
			m_edtPlacementInitialization.EnableWindow ( TRUE );
			m_lstPlacementScannerType.EnableWindow ( TRUE );
		}
	}

}







void CScannerSetupDlg::OnSelChangePlacementScannerType() 
{

	m_nPlacementScannerType = m_lstPlacementScannerType.GetCurSel ( );
	
}



