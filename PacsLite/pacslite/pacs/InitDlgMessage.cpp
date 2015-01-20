// InitDlgMessage.cpp : implementation file
//

#include "stdafx.h"
#include "PACS.h"
#include "InitDlgMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInitDlgMessage dialog


CInitDlgMessage::CInitDlgMessage(CWnd* pParent /*=NULL*/)
	: CDialog(CInitDlgMessage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInitDlgMessage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	ASSERT(pParent != NULL);

	mp_Parent = pParent;
	m_int_ID = CInitDlgMessage::IDD;

}


void CInitDlgMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInitDlgMessage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInitDlgMessage, CDialog)
	//{{AFX_MSG_MAP(CInitDlgMessage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInitDlgMessage message handlers

BOOL CInitDlgMessage::Create() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::Create(m_int_ID, mp_Parent);
}


BOOL CInitDlgMessage::PeekAndPump()
{
	MSG msg;

	while (::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE))
	{
		if (!AfxGetThread()->PumpMessage())
			return (TRUE);
	}

	return (TRUE);
}
