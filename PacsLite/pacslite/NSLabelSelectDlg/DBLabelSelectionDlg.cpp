// DBLabelSelectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "DBLabelSelectionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBLabelSelectionDlg dialog


CDBLabelSelectionDlg::CDBLabelSelectionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDBLabelSelectionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDBLabelSelectionDlg)
	m_nLabelCount = 1;
	//}}AFX_DATA_INIT
}


void CDBLabelSelectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBLabelSelectionDlg)
	DDX_Control(pDX, IDC_LABEL_POSITIONS, m_lstLabelPositions);
	DDX_Text(pDX, IDC_LABEL_COUNT, m_nLabelCount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDBLabelSelectionDlg, CDialog)
	//{{AFX_MSG_MAP(CDBLabelSelectionDlg)
	ON_LBN_SELCHANGE(IDC_LABEL_POSITIONS, OnSelChangeLabelPositions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBLabelSelectionDlg message handlers

BEGIN_EVENTSINK_MAP(CDBLabelSelectionDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CDBLabelSelectionDlg)
	ON_EVENT(CDBLabelSelectionDlg, IDOK, -600 /* Click */, OnClickOk, VTS_NONE)
	ON_EVENT(CDBLabelSelectionDlg, IDCANCEL, -600 /* Click */, OnClickCancel, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()




BOOL CDBLabelSelectionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString	csPoint1,csPoint2,csTemp;
	int		nIndex,nRescans,nRepicks,nNumberOfNosepieces;
	BOOL	bSystem2up;

	CDatabase	oDatabase;
	oDatabase.Initialize();
	oDatabase.GetGeneralAttributes(&nRescans,&nRepicks,&bSystem2up,&nNumberOfNosepieces);


	// Initialize label placement positions list.
	csTemp = m_poJob->GetPlacementAttributes();

	nIndex = csTemp.Find ( ";" );    // ";" is the separator of the location points

	while ( nIndex != -1 )
	{
		// Isolate first label
		csPoint1 = csTemp.Left ( nIndex + 1 );

		// delete it from the string
		csTemp = csTemp.Right ( csTemp.GetLength() - nIndex - 1 );

		// find next seperator
		nIndex = csTemp.Find ( ";" );

		m_lstLabelPositions.AddString(csPoint1);
	}

	m_nLabel  = 0;
	m_lstLabelPositions.SetCurSel ( 0 );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CDBLabelSelectionDlg::OnClickOk() 
{

	CDialog::OnOK();
	
}



void CDBLabelSelectionDlg::OnClickCancel() 
{

	CDialog::OnCancel();
	
}



void CDBLabelSelectionDlg::OnSelChangeLabelPositions() 
{
	CString		csSelectedLabels;
	int			nSelectionIndex;

	nSelectionIndex = m_lstLabelPositions.GetCurSel();
	m_lstLabelPositions.GetText(nSelectionIndex,csSelectedLabels);

	// number of the first label
	m_nLabel = nSelectionIndex;

}
