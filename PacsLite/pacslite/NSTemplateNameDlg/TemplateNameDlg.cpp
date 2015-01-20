// TemplateNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TemplateNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTemplateNameDlg dialog


CTemplateNameDlg::CTemplateNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTemplateNameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTemplateNameDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTemplateNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTemplateNameDlg)
	DDX_Control(pDX, IDC_TEMPLATE_NAME, m_txtTemplateName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTemplateNameDlg, CDialog)
	//{{AFX_MSG_MAP(CTemplateNameDlg)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTemplateNameDlg message handlers

BEGIN_EVENTSINK_MAP(CTemplateNameDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CTemplateNameDlg)
	ON_EVENT(CTemplateNameDlg, IDC_OK, -600 /* Click */, OnClickOk, VTS_NONE)
	ON_EVENT(CTemplateNameDlg, IDC_CANCEL, -600 /* Click */, OnClickCancel, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()



BOOL CTemplateNameDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CTemplateNameDlg::OnDestroy() 
{

	m_txtTemplateName.GetWindowText ( m_csTemplateName );

	if ( m_csTemplateName != "" )
		CDialog::OnDestroy();
	else
		AfxMessageBox ( "Invalid template name." );
	
}



void CTemplateNameDlg::OnClickOk() 
{

	m_txtTemplateName.GetWindowText ( m_csTemplateName );

	if ( m_csTemplateName != "" )
		CDialog::OnOK();
	else
		AfxMessageBox ( "Invalid template name." );
	
}



void CTemplateNameDlg::OnClickCancel() 
{

	CDialog::OnCancel();
	
}


