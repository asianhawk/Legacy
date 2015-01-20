// Password.h: interface for the CPassword class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PASSWORD_H__081ABF62_B854_11D2_A68A_641A11C1FB5F__INCLUDED_)
#define AFX_PASSWORD_H__081ABF62_B854_11D2_A68A_641A11C1FB5F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Database.h"

enum password
{
	NO_PW,
	SYSTEM_PW,
	INTERNAL_PW
};



class CPassword  
{
public:
	CPassword();
	virtual ~CPassword();

	int PasswordClearance ( CDatabase *poDatabase );


	CString m_csPassword;


};

#endif // !defined(AFX_PASSWORD_H__081ABF62_B854_11D2_A68A_641A11C1FB5F__INCLUDED_)
