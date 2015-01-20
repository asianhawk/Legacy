// DeleteJobDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DeleteJobDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeleteJobDlg dialog


CDeleteJobDlg::CDeleteJobDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeleteJobDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeleteJobDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDeleteJobDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeleteJobDlg)
	DDX_Control(pDX, IDC_JOB_LIST, m_cmbJobList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDeleteJobDlg, CDialog)
	//{{AFX_MSG_MAP(CDeleteJobDlg)
	ON_CBN_SELCHANGE(IDC_JOB_LIST, OnSelChangeJobList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeleteJobDlg message handlers

BEGIN_EVENTSINK_MAP(CDeleteJobDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CDeleteJobDlg)
	ON_EVENT(CDeleteJobDlg, IDC_CANCEL, -600 /* Click */, OnClickCancel, VTS_NONE)
	ON_EVENT(CDeleteJobDlg, IDC_DELETEJOB, -600 /* Click */, OnClickDeleteJob, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()




BOOL CDeleteJobDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	// Get Job listing from database and list them.

	m_poDatabase->GetJobNames ( &m_csJobArray );	
	ListJobs();

	int			i,nUpperBound;
	CString		csCurrentJobName;

	// select the job that was passed to us
	nUpperBound = m_cmbJobList.GetCount();
	for (i=0;i<nUpperBound;i++)
	{
		m_cmbJobList.GetLBText (i,csCurrentJobName);
		if (csCurrentJobName==m_csJobName)
			m_cmbJobList.SetCurSel(i);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CDeleteJobDlg::OnClickCancel() 
{

	CDialog::OnCancel();
	
}






/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		ListJobs
//
//	Description:
//		List all available jobs.
//
//	Arguments:
//		None.
//
//	Return:
//		None.
//
//	Called by:
//		OnInitDialog
//
/////////////////////////////////////////////////////////////////////////////////////

void CDeleteJobDlg::ListJobs ( void ) 
{
	int nCount;
	int i;
	int nPos;

	CString csTemp;
	CString csName;

	nCount = m_csJobArray.GetSize();

	if ( nCount > 0 )
	{
		m_cmbJobList.ResetContent();

		// List descriptions of all jobs.

		for ( i = 0; i < nCount; i++ )
		{
			csTemp = m_csJobArray[i];

			// Remove descrition.

			nPos = csTemp.Find ( "\t" );

			csName = csTemp.Left ( nPos );

			m_cmbJobList.AddString ( csName );
		}
	}
}


void CDeleteJobDlg::OnSelChangeJobList() 
{
	m_cmbJobList.GetLBText ( m_cmbJobList.GetCurSel(), m_csJobName );	
}



void CDeleteJobDlg::OnClickDeleteJob() 
{
	m_poDatabase->RemoveJob(m_csJobName);
	{
		// get the modified job list
		m_poDatabase->GetJobNames (&m_csJobArray);	
		// put them in the control
		ListJobs();
		// select the first job in the list
		if (m_cmbJobList.SetCurSel(0)!=CB_ERR)
			m_cmbJobList.GetLBText (0,m_csJobName);
	}	
}
