// SetupSerializationDlg.cpp : implementation file
//

#include "stdafx.h"

#include "SetupSerializationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupSerializationDlg dialog


CSetupSerializationDlg::CSetupSerializationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupSerializationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetupSerializationDlg)
	//}}AFX_DATA_INIT
}


void CSetupSerializationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupSerializationDlg)
	DDX_Control(pDX, IDC_CMB_FORMULA, m_cmbCheckDigitType);
	DDX_Control(pDX, IDC_CHK_USE_CHECKDIGIT, m_chkUseCheckDigit);
	DDX_Control(pDX, IDC_FRM_CHKDIGITSOURCE, m_frmChkDigitSource);
	DDX_Control(pDX, IDC_SN_TYPE, m_cmbSNType);
	DDX_Control(pDX, IDC_STARTING_SN, m_edtSNStart);
	DDX_Control(pDX, IDC_SN_LENGTH, m_edtSNLength);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupSerializationDlg, CDialog)
	//{{AFX_MSG_MAP(CSetupSerializationDlg)
	ON_BN_CLICKED(IDC_OPT_COMPUTER, OnOptChkDgtSourceComputer)
	ON_BN_CLICKED(IDC_OPT_PRINTER, OnOptChkDgtSourcePrinter)
	ON_BN_CLICKED(IDC_CHK_USE_CHECKDIGIT, OnChkUseCheckDigit)
	ON_CBN_SELCHANGE(IDC_CMB_FORMULA, OnSelchangeCmbFormula)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupSerializationDlg message handlers

BEGIN_EVENTSINK_MAP(CSetupSerializationDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CSetupSerializationDlg)
	ON_EVENT(CSetupSerializationDlg, IDC_OK, -600 /* Click */, OnClickOk, VTS_NONE)
	ON_EVENT(CSetupSerializationDlg, IDC_CANCEL, -600 /* Click */, OnClickCancel, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

BOOL CSetupSerializationDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString
		csTemp;

	csTemp.Format ( "%d", m_nSNLength );
	m_edtSNLength.SetWindowText ( csTemp );

	m_edtSNStart.SetWindowText ( m_csStartingSN );
	
	m_cmbSNType.SetCurSel ( m_nSNType );

	m_cmbCheckDigitType.AddString("Mod 43");
	m_cmbCheckDigitType.AddString("Mod 10 [Zebra Printer]");


	if (m_blnUseCheckDigit)
	{
		m_chkUseCheckDigit.SetCheck(1);
		m_frmChkDigitSource.EnableWindow(TRUE);
		m_cmbCheckDigitType.EnableWindow(TRUE);

		m_cmbCheckDigitType.SetCurSel(
			m_cmbCheckDigitType.FindString(0,m_csCheckDigitType));
		if (m_csCheckDigitSource.Find("Printer")!=-1)
		{
			CheckDlgButton(IDC_OPT_PRINTER,BST_CHECKED);
		}
		else
		{
			CheckDlgButton(IDC_OPT_COMPUTER,BST_CHECKED);

		}


	}
	else
	{
		m_frmChkDigitSource.EnableWindow(FALSE);
		m_cmbCheckDigitType.EnableWindow(FALSE);


	}
	UpdateData(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CSetupSerializationDlg::OnClickOk() 
{

	CString
		csTemp;


	m_edtSNLength.GetWindowText ( csTemp );
	m_nSNLength = atoi ( csTemp );
	m_edtSNStart.GetWindowText ( m_csStartingSN );
	m_nSNType = m_cmbSNType.GetCurSel();

	
	if (m_blnUseCheckDigit)
	{
		
		m_cmbCheckDigitType.GetLBText(m_cmbCheckDigitType.GetCurSel(),
										m_csCheckDigitType);
		if (m_csCheckDigitType.IsEmpty())
		{
			m_csCheckDigitType="Not Defined";
			m_csCheckDigitSource="Not Defined";
		}
		else
		{
		
			if (IsDlgButtonChecked(IDC_OPT_PRINTER))
			{
				AfxMessageBox("Warning. The printer template must be configured properly",
							  MB_ICONEXCLAMATION);
				m_csCheckDigitSource="Printer";
			}
			else
				m_csCheckDigitSource="Computer";


		}

	}
	else
	{
		m_csCheckDigitType="NotDefined";
		m_csCheckDigitSource="NotDefined";

	}
	

	// CHECK VALIDITY!

	CDialog::OnOK();
}


void CSetupSerializationDlg::OnClickCancel() 
{

	CDialog::OnCancel();
}

void CSetupSerializationDlg::OnOptChkDgtSourceComputer() 
{
	// TODO: Add your control notification handler code here
	
}

void CSetupSerializationDlg::OnOptChkDgtSourcePrinter() 
{
	// TODO: Add your control notification handler code here
	
}

void CSetupSerializationDlg::OnChkUseCheckDigit() 
{

	if (m_chkUseCheckDigit.GetCheck())
	{
		m_frmChkDigitSource.EnableWindow(TRUE);
		m_cmbCheckDigitType.EnableWindow(TRUE);
		m_cmbCheckDigitType.SetCurSel(0);
		CheckDlgButton(IDC_OPT_COMPUTER,1);

		m_blnUseCheckDigit=TRUE;
	}
	else
	{
		m_frmChkDigitSource.EnableWindow(FALSE);
		m_cmbCheckDigitType.EnableWindow(FALSE);
		m_blnUseCheckDigit=FALSE;
		m_cmbCheckDigitType.SetWindowText("");
		CheckDlgButton(IDC_OPT_PRINTER,0);
		CheckDlgButton(IDC_OPT_COMPUTER,0);
	}
	UpdateData(FALSE);

}

void CSetupSerializationDlg::OnSelchangeCmbFormula() 
{

	

}
