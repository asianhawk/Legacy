// Database.h: interface for the CDatabase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABASE_H__BCF778C3_9EE5_11D2_A2AB_006008043EC4__INCLUDED_)
#define AFX_DATABASE_H__BCF778C3_9EE5_11D2_A2AB_006008043EC4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include <afxdao.h>
#include "definitions.h"

class AFX_MFC_EXT_TYPE CSysDBase  
{
public:
	BOOL				m_bInitialized;						// Object initialized flag.
	CSysDBase();
	virtual ~CSysDBase();

	BOOL Initialize ( void );
	CString GetLastErrorMsg();
	void SetLastErrorMsg(CString csMessage);
	BOOL Open();												// Open the database.
	void Close();												// Close the database.
	CDaoDatabase	m_dbJobDatabase;						// DAO Database object.

private:

	CString m_csErrorMsg;
};

#endif // !defined(AFX_DATABASE_H__BCF778C3_9EE5_11D2_A2AB_006008043EC4__INCLUDED_)
