// TemplateSetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "TemplateEditDlg.h"
#include "TemplateSetupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTemplateSetupDlg dialog


CTemplateSetupDlg::CTemplateSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTemplateSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTemplateSetupDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTemplateSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTemplateSetupDlg)
	DDX_Control(pDX, IDC_TEMPLATE_LIST, m_cmbTemplates);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTemplateSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CTemplateSetupDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTemplateSetupDlg message handlers

BEGIN_EVENTSINK_MAP(CTemplateSetupDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CTemplateSetupDlg)
	ON_EVENT(CTemplateSetupDlg, IDC_DONE, -600 /* Click */, OnClickDone, VTS_NONE)
	ON_EVENT(CTemplateSetupDlg, IDC_EDIT, -600 /* Click */, OnClickEdit, VTS_NONE)
	ON_EVENT(CTemplateSetupDlg, IDC_DELETE, -600 /* Click */, OnClickDelete, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnInitDialog()
//
//	Description:
//		Setup dialog on opening
//
//	Arguments:
//		None.
//
//	Return:
//		None.
//
//	Called by:
//		Framework
/////////////////////////////////////////////////////////////////////////////////////

BOOL CTemplateSetupDlg::OnInitDialog() 
{
	// Base class initdialog
	CDialog::OnInitDialog();

	// fill the combobox with the template list
	BuildTemplateList();	
	
	// Select the first template
	m_cmbTemplates.SetCurSel (0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		BuildTemplateList()
//
//	Description:
//		Fills the combobox with the list of templates
//		from the database
//	Arguments:
//		None.
//
//	Return:
//		None.
//
//	Called by:
//		OnInitDialog, OnClickDelete
/////////////////////////////////////////////////////////////////////////////////////

void CTemplateSetupDlg::BuildTemplateList()
{
	int			nIndex,nListIndex;
	CString		csTemp,csName;
	
	// retrieve the list of template names
	m_poDatabase->GetTemplateList(&csTemp);

	// ";" is the separator of the template names.
	nIndex = csTemp.Find ( ";" );
	nListIndex = 0;
	while ( nIndex != -1 )
	{
		// Get name.
		csName = csTemp.Left ( nIndex );
		m_cmbTemplates.AddString ( csName );

		// Get next name.
		csTemp = csTemp.Right ( csTemp.GetLength() - nIndex - 1 );
		nIndex = csTemp.Find ( ";" );
	}	
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickDelete()
//
//	Description:
//		Delete a Template
//
//	Arguments:
//		None.
//
//	Return:
//		None.
//
//	Called by:
//		Framework
/////////////////////////////////////////////////////////////////////////////////////

void CTemplateSetupDlg::OnClickDelete() 
{
CString		csTemplateToDelete;
CString		csTemp;
	// get the current selected template
	m_cmbTemplates.GetLBText(m_cmbTemplates.GetCurSel(),csTemplateToDelete);
	
	if (m_poDatabase->IsTemplateActive(csTemplateToDelete))
	{
		csTemp.LoadString(IDS_WARNING_TEMPLATE_ACTIVE);
		AfxMessageBox(csTemp);
		return;

	}
	if (m_poDatabase->RemoveTemplate (csTemplateToDelete))
	{
		// clear combo box entries
		m_cmbTemplates.ResetContent();
		
		// fill the combo box with the updated template list
		BuildTemplateList();
	
		// Select the first template
		m_cmbTemplates.SetCurSel (0);
	}
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickEdit()
//
//	Description:
//		Edit selected template
//
//	Arguments:
//		None.
//
//	Return:
//		None.
//
//	Called by:
//		Framework
/////////////////////////////////////////////////////////////////////////////////////

void CTemplateSetupDlg::OnClickEdit() 
{
	CString
		csName,
		csTemp,
		csTemplateName;

	int
		nListIndex,
		nCurrentSel,
		nIndex;

	// declare the edit template dialog object
	CTemplateEditDlg EditTemplate;

	// pass currently selected template to edit template dialog
	m_cmbTemplates.GetLBText(m_cmbTemplates.GetCurSel(),EditTemplate.m_csTemplateName);
	// pass the database to the edit template dialog
	EditTemplate.m_poDatabase = m_poDatabase;

	if ( IDOK == EditTemplate.DoModal() )
	{
		// reset the combobox, we will rebuild content
		// to reflect any user changes
		m_cmbTemplates.ResetContent();
		
		// csTemplate = EditTemplate.m_csTemplate;
		csTemplateName = EditTemplate.m_csTemplateName;
		
		// Initialize printer template list.
		m_poDatabase->GetTemplateList(&csTemp);

		// ";" is the separator of the template names.
		nIndex = csTemp.Find ( ";" );
		
		nListIndex = 0;
		while ( nIndex != -1 )
		{
			// Get name.
			csName = csTemp.Left ( nIndex );
			if (csName==csTemplateName)
				nCurrentSel = nListIndex;
			m_cmbTemplates.AddString ( csName );

			// we're filling the next index
			nListIndex++;

			// Get next name.
			csTemp = csTemp.Right ( csTemp.GetLength() - nIndex - 1 );
			nIndex = csTemp.Find ( ";" );
		}
		// Select the correct template name
		m_cmbTemplates.SetCurSel ( nCurrentSel );
	}
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickDone()
//
//	Description:
//		Closes the Template Setup dialog
//
//	Arguments:
//		None.
//
//	Return:
//		None.
//
//	Called by:
//		Framework
/////////////////////////////////////////////////////////////////////////////////////

void CTemplateSetupDlg::OnClickDone() 
{
	CDialog::OnOK();	
}


