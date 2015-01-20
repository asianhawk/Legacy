// ChangePasswordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChangePasswordDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChangePasswordDlg dialog


CChangePasswordDlg::CChangePasswordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChangePasswordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChangePasswordDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CChangePasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangePasswordDlg)
	DDX_Control(pDX, IDC_PASSWORD, m_txtPassword);
	DDX_Control(pDX, IDC_CONFIRM_PASSWORD, m_txtConfirmPassword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChangePasswordDlg, CDialog)
	//{{AFX_MSG_MAP(CChangePasswordDlg)
	ON_EN_UPDATE(IDC_PASSWORD, OnUpdatePassword)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangePasswordDlg message handlers

BEGIN_EVENTSINK_MAP(CChangePasswordDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CChangePasswordDlg)
	ON_EVENT(CChangePasswordDlg, IDOK, -600 /* Click */, OnClickOk, VTS_NONE)
	ON_EVENT(CChangePasswordDlg, IDCANCEL, -600 /* Click */, OnClickCancel, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()




BOOL CChangePasswordDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	m_txtConfirmPassword.SetReadOnly ( TRUE );

	m_bPasswordChange = FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CChangePasswordDlg::OnClickOk() 
{

	CString csTemp;

	CString csPassword;
	CString csConfirmPassword;

	m_txtPassword.GetWindowText ( csPassword );
	m_txtConfirmPassword.GetWindowText ( csConfirmPassword );
	
	if (csPassword=="customerservice")
	{
		csTemp.LoadString(IDS_INVALID_SYSPW);
		AfxMessageBox(csTemp);
		m_txtPassword.SetWindowText ( "" );
		m_txtConfirmPassword.SetWindowText ( "" );

		OnInitDialog();
		return;
	}

	if ( m_bPasswordChange )
	{
		if ( ( csPassword != "" ) && ( csPassword == csConfirmPassword ) )
		{

			// Encrypt the password.

			csPassword.MakeUpper();

			m_csPassword = Encrypt ( csPassword );

			CDialog::OnOK();
		}
		else
		{
			csTemp = "Password was not confirmed.\n";
			csTemp += "Please enter a new password or a confirmation password.";
			AfxMessageBox ( csTemp );
		}
	}
	else
	{
		if ( AfxMessageBox ( "Password was not changed. Do you wish to Cancel?", MB_YESNO ) == IDYES )
		{
			CDialog::OnCancel();
		}
	}


}




void CChangePasswordDlg::OnClickCancel() 
{

	
	CDialog::OnCancel();

}


void CChangePasswordDlg::OnUpdatePassword() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	

	m_txtConfirmPassword.SetReadOnly ( FALSE );

	m_bPasswordChange = TRUE;
	
}




CString CChangePasswordDlg::Encrypt ( CString csPassword ) 
{

	CString csEncryptedPW;

	int
		i,
		nLength;

	csEncryptedPW = csPassword;

	nLength = csPassword.GetLength();

	for ( i = 0; i < nLength; i++ )
		csEncryptedPW.SetAt ( i, csPassword.GetAt ( i ) - PW_OFFSET );

	return ( csEncryptedPW );

}



