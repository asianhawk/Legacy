// DBPanelLabelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DBPanelLabelDlg.h"
#include "PointDlg.h"
#include "Database.h"
#include "Utilities.h"
#include <afxtempl.h>





#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBPanelLabelDlg dialog


CDBPanelLabelDlg::CDBPanelLabelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDBPanelLabelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDBPanelLabelDlg)
	//}}AFX_DATA_INIT
}


void CDBPanelLabelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBPanelLabelDlg)
	DDX_Control(pDX, IDC_LABEL_POSITIONS, m_lstLabelPositions);
	DDX_Control(pDX, IDC_POINT_EDIT, m_btnEditPoint);
	DDX_Control(pDX, IDC_POINT_ADD_1 , m_btnAddPoint);
	DDX_Control(pDX, IDC_POINT_DELETE_1 , m_btnDeletePoint);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDBPanelLabelDlg, CDialog)
	//{{AFX_MSG_MAP(CDBPanelLabelDlg)
	ON_LBN_SELCHANGE(IDC_LABEL_POSITIONS, OnSelChangeLabelPositions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBPanelLabelDlg message handlers

BEGIN_EVENTSINK_MAP(CDBPanelLabelDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CDBPanelLabelDlg)
	ON_EVENT(CDBPanelLabelDlg, IDOK, -600 /* Click */, OnClickOk, VTS_NONE)
	ON_EVENT(CDBPanelLabelDlg, IDCANCEL, -600 /* Click */, OnClickCancel, VTS_NONE)
	ON_EVENT(CDBPanelLabelDlg, IDC_POINT_EDIT, -600 /* Click */, OnClickPointEdit, VTS_NONE)
	ON_EVENT(CDBPanelLabelDlg, IDC_POINT_ADD_1, -600 /* Click */, PointAdd, VTS_NONE)
	ON_EVENT(CDBPanelLabelDlg, IDC_POINT_DELETE_1, -600 /* Click */, PointDelete, VTS_NONE)

	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()



BOOL CDBPanelLabelDlg::OnInitDialog() 
{
	// base class init
	CDialog::OnInitDialog();
	
	// some variables
	int	nIndex;
	CString	csName, csPoints;

	

	// Initialize label placement positions list.
	CString csTemp = m_poJob->GetPlacementAttributes();
   // ";" is the separator of the location points	
	nIndex = csTemp.Find ( ";" );
	while ( nIndex != -1 )
	{
		// Isolate a single label description for line.
		csPoints = csTemp.Left ( nIndex + 1 );
		m_lstLabelPositions.AddString ( csPoints );

		// Get next set of points.
		csTemp = csTemp.Right ( csTemp.GetLength() - nIndex - 1 );
		nIndex = csTemp.Find ( ";" );
	}
	// select the first label
//	m_lstLabelPositions.SetCurSel ( 0 );
	
	// disable edit and delete
	m_btnEditPoint.SetEnabled ( FALSE );
	m_btnDeletePoint.SetEnabled ( FALSE );
	
	// a template hasn't been changed
	m_bTemplateUpdated = FALSE;

	// we don't know what order the list is in assume no sort
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDBPanelLabelDlg::OnClickOk() 
{
	if ( GetJobInfo() )
		CDialog::OnOK();
}


void CDBPanelLabelDlg::OnClickCancel() 
{
	CString csTemp;

	if ( m_bTemplateUpdated )
	{
		csTemp.LoadString ( IDS_TEMPLATE_CHANGED );
		AfxMessageBox ( csTemp );
	}

	CDialog::OnCancel();
}



void CDBPanelLabelDlg::PointAdd() 
{
CString csNewPoint,csTemp;
CPointDlg PointEdit;
	// build a default blank point	
	// use the selected template
	m_poDatabase->GetTemplateList(&csTemp);
	csNewPoint=csTemp.Left(csTemp.Find(";"));
	
	csTemp="";
	m_poDatabase->GetUsablePrinterList(&csTemp);
	csTemp = csTemp.Left(csTemp.Find(";"));
	csNewPoint = csNewPoint + "," + csTemp;
	// don't scan the label
	csNewPoint = csNewPoint + ",NO;";

	// set the default starting point
	PointEdit.m_csPlacementAttribute = csNewPoint;
	
	// pass the database
	PointEdit.m_poDatabase = m_poDatabase;

	if ( IDOK == PointEdit.DoModal() )
	{
		// add returned point to the list
		m_lstLabelPositions.AddString (PointEdit.m_csPlacementAttribute);	

		// disable edit and delete
		m_btnEditPoint.SetEnabled ( FALSE );
		m_btnDeletePoint.SetEnabled ( FALSE );
	
	
	}
}



void CDBPanelLabelDlg::PointDelete() 
{
	// delete the selected point
	m_lstLabelPositions.DeleteString (m_lstLabelPositions.GetCurSel());

	// disable edit and delete
	m_btnEditPoint.SetEnabled (FALSE);
	m_btnDeletePoint.SetEnabled (FALSE);
}



void CDBPanelLabelDlg::OnClickPointEdit() 
{
	int  nIndex;
	CString csReturnedPoint;

	CString
		csTemp;


	if (m_lstLabelPositions.GetCurSel()==LB_ERR)
	{
		csTemp.LoadString ( IDS_SELECT_LABEL );	
		AfxMessageBox ( csTemp );
		return;
	}

	CPointDlg PointEdit;
	
	// Initialize point data and database
	m_lstLabelPositions.GetText(m_lstLabelPositions.GetCurSel(),PointEdit.m_csPlacementAttribute);
	PointEdit.m_poDatabase = m_poDatabase;

	if ( IDOK == PointEdit.DoModal() )
	{
		// change point in the list box
		csReturnedPoint = PointEdit.m_csPlacementAttribute;
		nIndex = m_lstLabelPositions.GetCurSel();
		m_lstLabelPositions.DeleteString ( nIndex );
		m_lstLabelPositions.InsertString ( nIndex, csReturnedPoint );
		m_lstLabelPositions.SetCurSel ( nIndex );

		// disable edit and delete
		m_btnEditPoint.SetEnabled ( FALSE );
		m_btnDeletePoint.SetEnabled ( FALSE );

	
	}


}


BOOL CDBPanelLabelDlg::GetJobInfo () 
{
	int i,nCount;
	CString	csPanelDimension,csPlacementAttributes;
	CString	csTemp,csDimX,csDimY,csMessage,csPoint;
	
	CUtilities Utility;

	// Get panel dimension.


	
	// Get the number of points in the listbox
	nCount = m_lstLabelPositions.GetCount();
	if ( nCount == 0 )
	{
		csTemp.LoadString ( IDS_EMPTY_LABEL_LIST );
		AfxMessageBox ( csTemp );
		return ( FALSE );
	}

	// make sure we start with an empty string
	csPlacementAttributes.Empty();

	// use the points to create the placement attributes
	for ( i = 0; i < nCount; i++ )
	{
		m_lstLabelPositions.GetText ( i, csPoint );	 
		csPlacementAttributes += csPoint;
	}

	// save the placement attributes in the job object
	m_poJob->SetPlacementAttributes(csPlacementAttributes);
	
	// use the job object to update the job table in the database
	m_poDatabase->SetJobAttributes(m_poJob);

	return ( TRUE );
}

void CDBPanelLabelDlg::OnSelChangeLabelPositions() 
{
	// ensure edit and delete are enabled
	m_btnEditPoint.SetEnabled ( TRUE );
	m_btnDeletePoint.SetEnabled ( TRUE );

}
