// Password.cpp: implementation of the CPassword class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PACS.h"
#include "Password.h"
#include "PasswordDlg.h"
#include "Utilities.h"
#define	PW_OFFSET			45

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


const CString c_csInternalPW = "customerservice";


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPassword::CPassword()
{

}

CPassword::~CPassword()
{

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: PasswordClearance
//
//	Description:
//		Get a password from the user.
//
//	Arguments:
//		Password type requested.
//
//	Return:
//		Status of password retrieval.
//
//	Called by:
//		CPACSDlg::OnClickCmdSetupSystem
//
/////////////////////////////////////////////////////////////////////////////////////

int CPassword::PasswordClearance ( CDatabase *poDatabase )
{

	BOOL
		bPass;

	CString csPassword,
			csTemp;

	CPasswordDlg PasswordDlg;

	CString csEnteredPW;

	CString csEncryptedPW;
	CString csDate;
	CString csBackDoor;

	int
		nDate,
		i,
		nLength;

	CUtilities Utility;

//	PasswordDlg.SetWindowPos(NULL,0,0,200,200,SWP_HIDEWINDOW);


	if ( IDOK == PasswordDlg.DoModal() )
	{

		csEnteredPW = PasswordDlg.m_csPassword;

		// First check of password is for customer service.

		if ( csEnteredPW.CompareNoCase ( c_csInternalPW ) == 0 )
			return ( INTERNAL_PW );

		// Check entered password against password stored in database.

		if ( poDatabase->GetPassword ( &csPassword ) )
		{

			// Encrypt entered password.

			csEnteredPW.MakeUpper();

			csBackDoor = csEnteredPW;

			csEncryptedPW = csEnteredPW;

			nLength = csEnteredPW.GetLength();

			for ( i = 0; i < nLength; i++ )
				csEncryptedPW.SetAt ( i, csEnteredPW.GetAt ( i ) - PW_OFFSET );

			// Get password from database.

			if ( csPassword.CompareNoCase ( csEncryptedPW ) == 0 )
				bPass = TRUE;
			else
			{

				// Check for back door. Back door is ( day + month + year ) * 3.
				// Note: csDate must be mm/dd/yyyy.

				csDate = Utility.CalculateDate();

				nDate = ( atoi ( csDate.Mid ( 0, 2 ) ) + 
							 atoi ( csDate.Mid ( 3, 2 ) ) +
							 atoi ( csDate.Right ( 4 ) ) ) * 3;

				csDate.Format ( "%d", nDate );

				if ( csBackDoor.CompareNoCase ( csDate ) == 0 )
					bPass = TRUE;
				else
					bPass = FALSE;
			}
		}
		else
			bPass = FALSE;
	}
	else
		bPass = FALSE;

	if ( bPass )
		return ( SYSTEM_PW );
	else
	{
	   csTemp.LoadString(IDS_INVALID_PW);
	   AfxMessageBox(csTemp);

	}
	return ( NO_PW );

}






