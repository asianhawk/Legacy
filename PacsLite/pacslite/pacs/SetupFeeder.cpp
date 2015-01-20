// SetupFeeder.cpp : implementation file
//

#include "stdafx.h"
#include "PACS.h"
#include "SetupFeeder.h"
#include "Utilities.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupFeeder dialog


CSetupFeeder::CSetupFeeder(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupFeeder::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetupFeeder)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSetupFeeder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupFeeder)
	DDX_Control(pDX, IDC_Y_PREPICK, m_edtYPrePick);
	DDX_Control(pDX, IDC_Y_PICK, m_edtYPick);
	DDX_Control(pDX, IDC_X_PREPICK, m_edtXPrePick);
	DDX_Control(pDX, IDC_X_PICK, m_edtXPick);
	DDX_Control(pDX, IDC_ROT_PREPICK, m_edtRotPrePick);
	DDX_Control(pDX, IDC_ROT_PICK, m_edtRotPick);
	DDX_Control(pDX, IDC_FEEDER_SELECTION, m_cmbFeederList);
	DDX_Control(pDX, IDC_ENABLE_FEEDER, m_chkEnableFeeder);
	DDX_Control(pDX, IDC_ADVANCE_DELAY, m_edtAdvanceLabelDelay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupFeeder, CDialog)
	//{{AFX_MSG_MAP(CSetupFeeder)
	ON_BN_CLICKED(IDC_ENABLE_FEEDER, OnEnableFeeder)
	ON_CBN_SELCHANGE(IDC_FEEDER_SELECTION, OnSelChangeFeederSelection)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupFeeder message handlers

BEGIN_EVENTSINK_MAP(CSetupFeeder, CDialog)
    //{{AFX_EVENTSINK_MAP(CSetupFeeder)
	ON_EVENT(CSetupFeeder, IDCANCEL, -600 /* Click */, OnClickCancel, VTS_NONE)
	ON_EVENT(CSetupFeeder, IDOK, -600 /* Click */, OnClickOk, VTS_NONE)
	ON_EVENT(CSetupFeeder, ID_UPDATE, -600 /* Click */, OnClickUpdate, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

BOOL CSetupFeeder::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	
	// Get the feeders used for this application. Use the first one in 
	// the list to display attributes of. The list is ; delimited.

	if ( !m_poDatabase->GetUsableFeederList ( &m_csFeederList ) )
		return ( TRUE );	

	DisplayList();					// Display the list of available feeders.

	// Get first printer in the list.

	m_cmbFeederList.SetCurSel ( 0 );
	
	m_cmbFeederList.GetLBText ( 0, m_csCurrentFeeder );

	DisplayAttributes();			// Display the current feeder.



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetupFeeder::OnClickCancel() 
{

	CDialog::OnCancel();
	
}


void CSetupFeeder::OnClickOk() 
{

	CDialog::OnOK();
	
}



void CSetupFeeder::OnEnableFeeder() 
{

	if ( !m_chkEnableFeeder.GetCheck ( ) )
	{
		m_edtXPrePick.EnableWindow ( FALSE );
		m_edtYPrePick.EnableWindow ( FALSE );
		m_edtRotPrePick.EnableWindow ( FALSE );
		m_edtXPick.EnableWindow ( FALSE );
		m_edtYPick.EnableWindow ( FALSE );
		m_edtRotPick.EnableWindow ( FALSE );
		m_edtAdvanceLabelDelay.EnableWindow ( FALSE );
	}
	else
	{
		m_edtXPrePick.EnableWindow ( TRUE );
		m_edtYPrePick.EnableWindow ( TRUE );
		m_edtRotPrePick.EnableWindow ( TRUE );
		m_edtXPick.EnableWindow ( TRUE );
		m_edtYPick.EnableWindow ( TRUE );
		m_edtRotPick.EnableWindow ( TRUE );
		m_edtAdvanceLabelDelay.EnableWindow ( TRUE );
	}
	
}


void CSetupFeeder::OnSelChangeFeederSelection() 
{

	m_cmbFeederList.GetLBText ( m_cmbFeederList.GetCurSel(), m_csCurrentFeeder );
	
	DisplayAttributes();
	
}


void CSetupFeeder::OnClickUpdate() 
{

	int
		nTimer;

	BOOL
		bEnable;

	CString
		csTimer,
		csTemp,
		csPrePick,
		csPick,
		csXPrePick,
		csYPrePick,
		csRotPrePick,
		csXPick,
		csYPick,
		csRotPick;

	CUtilities Utility;


	// Get feeder attributes for current feeder and update
	// the database.

	m_edtAdvanceLabelDelay.GetWindowText ( csTimer );
	nTimer = atoi ( csTimer );

	bEnable = m_chkEnableFeeder.GetCheck ( );

	m_edtXPrePick.GetWindowText ( csXPrePick );
	m_edtYPrePick.GetWindowText ( csYPrePick );
	m_edtRotPrePick.GetWindowText ( csRotPrePick );
	m_edtXPick.GetWindowText ( csXPick );
	m_edtYPick.GetWindowText ( csYPick );
	m_edtRotPick.GetWindowText ( csRotPick );


	// Check validity.

	csPrePick = csXPrePick + "," + csYPrePick + ";" + csRotPrePick;
	csPick = csXPick + "," + csYPick + ";" + csRotPick;
	
	if ( !Utility.CheckPositionFormat ( csPrePick ) )
	{
		csTemp.LoadString ( IDS_INVALID_PREPICKPOS );
		AfxMessageBox ( csTemp );
		return;
	}

	if ( !Utility.CheckPositionFormat ( csPick ) )
	{
		csTemp.LoadString ( IDS_INVALID_PICKPOS );
		AfxMessageBox ( csTemp );
		return;
	}


	m_poDatabase->SetFeederAttributes ( m_csCurrentFeeder, 
													TRUE,
													bEnable,
													nTimer);
	
}





void CSetupFeeder::DisplayList() 
{

	CString
		csTemp,
		csName;

	int
		nIndex;


	csTemp = m_csFeederList;

	nIndex = csTemp.Find ( ";" );    // ";" is the separator of the template names.

	while ( nIndex != -1 )
	{

		// Get name.

		csName = csTemp.Left ( nIndex );

		m_cmbFeederList.AddString ( csName );

		// Get next name.

		csTemp = csTemp.Right ( csTemp.GetLength() - nIndex - 1 );
		nIndex = csTemp.Find ( ";" );

	}

}



void CSetupFeeder::DisplayAttributes() 
{

	int
		nIndex,
		nLength,
		nTimer;

	BOOL
		bUse,
		bEnable;

	CString
		csTimer,
		csPrePick,
		csPick,
		csTemp,
		csXPrePick,
		csYPrePick,
		csRotPrePick,
		csXPick,
		csYPick,
		csRotPick;

	CUtilities Utility;

	
	// Get attributes from database for selected printer.

	m_poDatabase->GetFeederAttributes ( m_csCurrentFeeder, 
													&bUse,
													&bEnable,
													&nTimer);

	csTimer.Format ( "%d", nTimer );
	m_edtAdvanceLabelDelay.SetWindowText ( csTimer );

	// Ensure proper format.

	if ( !Utility.CheckPositionFormat ( csPrePick ) )
	{
		csTemp.LoadString ( IDS_INVALID_PREPICKPOS );
		AfxMessageBox ( csTemp );
		return;
	}
		
	nIndex = csPrePick.Find ( ";" );
	nLength = csPrePick.GetLength();

	csXPrePick = csPrePick.Mid ( 0, 6 );
	csYPrePick = csPrePick.Mid ( 7, 6 );
	csRotPrePick = csPrePick.Right ( nLength - nIndex - 1 );

	if ( !Utility.CheckPositionFormat ( csPick ) )
	{
		csTemp.LoadString ( IDS_INVALID_PICKPOS );
		AfxMessageBox ( csTemp );
		return;
	}
		
	nIndex = csPick.Find ( ";" );
	nLength = csPick.GetLength();

	csXPick = csPick.Mid ( 0, 6 );
	csYPick = csPick.Mid ( 7, 6 );
	csRotPick = csPick.Right ( nLength - nIndex - 1 );

	m_edtXPrePick.SetWindowText ( csXPrePick );
	m_edtYPrePick.SetWindowText ( csYPrePick );
	m_edtRotPrePick.SetWindowText ( csRotPrePick );
	m_edtXPick.SetWindowText ( csXPick );
	m_edtYPick.SetWindowText ( csYPick );
	m_edtRotPick.SetWindowText ( csRotPick );

	m_chkEnableFeeder.SetCheck ( bEnable );


	if ( !bEnable )
	{
		m_edtXPrePick.EnableWindow ( FALSE );
		m_edtYPrePick.EnableWindow ( FALSE );
		m_edtRotPrePick.EnableWindow ( FALSE );
		m_edtXPick.EnableWindow ( FALSE );
		m_edtYPick.EnableWindow ( FALSE );
		m_edtRotPick.EnableWindow ( FALSE );
		m_edtAdvanceLabelDelay.EnableWindow ( FALSE );
	}
	else
	{
		m_edtXPrePick.EnableWindow ( TRUE );
		m_edtYPrePick.EnableWindow ( TRUE );
		m_edtRotPrePick.EnableWindow ( TRUE );
		m_edtXPick.EnableWindow ( TRUE );
		m_edtYPick.EnableWindow ( TRUE );
		m_edtRotPick.EnableWindow ( TRUE );
		m_edtAdvanceLabelDelay.EnableWindow ( TRUE );
	}

}


