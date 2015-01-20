// TemplateEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "TemplateEditDlg.h"
#include "TemplateNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTemplateEditDlg dialog


CTemplateEditDlg::CTemplateEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTemplateEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTemplateEditDlg)
	//}}AFX_DATA_INIT
}


void CTemplateEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTemplateEditDlg)
	DDX_Control(pDX, IDC_TEMPLATE_EDIT, m_txtTemplate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTemplateEditDlg, CDialog)
	//{{AFX_MSG_MAP(CTemplateEditDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTemplateEditDlg message handlers

BEGIN_EVENTSINK_MAP(CTemplateEditDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CTemplateEditDlg)
	ON_EVENT(CTemplateEditDlg, IDOK, -600 /* Click */, OnClickOk, VTS_NONE)
	ON_EVENT(CTemplateEditDlg, IDCANCEL, -600 /* Click */, OnClickCancel, VTS_NONE)
	ON_EVENT(CTemplateEditDlg, IDC_SAVEASNEW, -600 /* Click */, OnClickSaveAsNew, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()



void CTemplateEditDlg::OnClickOk() 
{
	// this is the save button
	CString csTemplate = m_txtTemplate.GetText();
	// save the template in the database
	m_poDatabase->SetTemplate ( m_csTemplateName, csTemplate );

	// base class call
	CDialog::OnOK();	
}


void CTemplateEditDlg::OnClickCancel() 
{	
	CDialog::OnCancel();
}


BOOL CTemplateEditDlg::OnInitDialog() 
{
	// call framework initdialog
	CDialog::OnInitDialog();

	CString csTemplate;
	
	// retrieve the template
	m_poDatabase->GetTemplate ( m_csTemplateName, &csTemplate );
	
	// put the template in the textbox
	m_txtTemplate.SetText ( csTemplate );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CTemplateEditDlg::OnClickSaveAsNew() 
{

	CString
		csName;

	BOOL
		bDone,
		bGoodName;

	// declare template name dialog object
	CTemplateNameDlg TemplateName;

	// get the list of templates
	CString csTemplateList;
	m_poDatabase->GetTemplateList(&csTemplateList);
	
	// Loop until valid name or cancel.
	bDone = FALSE;
	bGoodName = FALSE;
	while ( !bDone )
	{
		if ( IDOK == TemplateName.DoModal() )
		{
			csName = TemplateName.m_csTemplateName;
			
			// Look for match in template list.
			if ( csTemplateList.Find ( csName ) == -1 )
			{
				m_csTemplateName = csName;
				bGoodName = TRUE;
				bDone = TRUE;
			}			
		}
		else
			bDone = TRUE;
	}
	if (bGoodName)
		OnClickOk();
}

