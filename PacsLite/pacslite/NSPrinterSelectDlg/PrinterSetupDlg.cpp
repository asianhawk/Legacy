// PrinterSetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PrinterSetupDlg.h"
#include "Utilities.h"
#include "NSPrinterSetupDlgResource.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrinterSetupDlg dialog


CPrinterSetupDlg::CPrinterSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrinterSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrinterSetupDlg)
	//}}AFX_DATA_INIT
}



void CPrinterSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrinterSetupDlg)
	DDX_Control(pDX, IDC_PRINTER_TYPE, m_cmbPrinterType);
	DDX_Control(pDX, IDC_PRINTER_SELECTION, m_cmbPrinterSelection);
	DDX_Control(pDX, IDC_ENABLE, m_chkEnable);
	DDX_Control(pDX, IDC_UPDATE, m_btnUpdate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrinterSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CPrinterSetupDlg)
	ON_BN_CLICKED(IDC_ENABLE, OnEnable)
	ON_CBN_SELCHANGE(IDC_PRINTER_SELECTION, OnSelChangePrinterSelection)
	ON_CBN_SELCHANGE(IDC_PRINTER_TYPE, OnSelChangePrinterType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrinterSetupDlg message handlers

BEGIN_EVENTSINK_MAP(CPrinterSetupDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CPrinterSetupDlg)
	ON_EVENT(CPrinterSetupDlg, IDOK, -600 /* Click */, OnClickOk, VTS_NONE)
	ON_EVENT(CPrinterSetupDlg, IDCANCEL, -600 /* Click */, OnClickCancel, VTS_NONE)
	ON_EVENT(CPrinterSetupDlg, IDC_UPDATE, -600 /* Click */, OnClickUpdate, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()



BOOL CPrinterSetupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString
		csTemp;
	
	m_poDatabase.Initialize();
	
	// Get the printers used for this application. Use the first one in 
	// the list to display attributes of. The list is ; delimited.

	if ( !m_poDatabase.GetUsablePrinterList ( &m_csPrinterList ) )
		return ( TRUE );	

	DisplayList();					// Display the list of available printers.

	// Get first printer in the list.

	m_cmbPrinterSelection.SetCurSel ( 0 );
	
	m_cmbPrinterSelection.GetLBText ( 0, m_csCurrentPrinter );

	DisplayAttributes();			// Display the current printer.
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CPrinterSetupDlg::OnClickOk() 
{

	CDialog::OnOK();
	
}



void CPrinterSetupDlg::OnClickCancel() 
{

	CDialog::OnCancel();
	
}





void CPrinterSetupDlg::OnEnable() 
{

	if ( !m_chkEnable.GetCheck ( ) )
	{
		m_cmbPrinterType.EnableWindow ( FALSE );

	}
	else
	{
		m_cmbPrinterType.EnableWindow ( TRUE );

	}
	
}



void CPrinterSetupDlg::OnSelChangePrinterSelection() 
{

	m_cmbPrinterSelection.GetLBText ( m_cmbPrinterSelection.GetCurSel(), m_csCurrentPrinter );
	
	DisplayAttributes();

}



void CPrinterSetupDlg::OnSelChangePrinterType() 
{

	

}



void CPrinterSetupDlg::OnClickUpdate() 
{

	int
		nType;

	BOOL
		bEnable;

	CString
		csTemp;

	CUtilities Utility;


	// Get printer attributes for current printer and update
	// the database.

	bEnable = m_chkEnable.GetCheck ( );

	nType = m_cmbPrinterType.GetCurSel ();


	m_poDatabase.SetPrinterAttributes ( m_csCurrentPrinter,
													 TRUE,
													 bEnable,
													 nType);
}

 


void CPrinterSetupDlg::DisplayList() 
{

	CString
		csTemp,
		csName;

	int
		nIndex;

	csTemp = m_csPrinterList;

	nIndex = csTemp.Find ( ";" );    // ";" is the separator of the template names.

	while ( nIndex != -1 )
	{

		// Get name.

		csName = csTemp.Left ( nIndex );

		m_cmbPrinterSelection.AddString ( csName );

		// Get next name.

		csTemp = csTemp.Right ( csTemp.GetLength() - nIndex - 1 );
		nIndex = csTemp.Find ( ";" );

	}

}



void CPrinterSetupDlg::DisplayAttributes() 
{

	int
		nType;

	BOOL
		bUse,
		bEnable;


	CUtilities Utility;

	m_poDatabase.Initialize();
	
	// Get attributes from database for selected printer.

	m_poDatabase.GetPrinterAttributes ( m_csCurrentPrinter,
													 &bUse,
													 &bEnable,
													 &nType);

	m_cmbPrinterType.SetCurSel ( nType );


	m_chkEnable.SetCheck ( bEnable );

	if ( !bEnable )
	{
		m_cmbPrinterType.EnableWindow ( FALSE );


	}
	else
	{
		m_cmbPrinterType.EnableWindow ( TRUE );

	}

}



