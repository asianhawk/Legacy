// AddEditJobDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AddEditJobDlg.h"
#include "PointDlg.h"
#include "Utilities.h"
#include "DBPanelLabelDlg.h"
#include "JobNameDlg.h"
#include "SetupSerializationDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddEditJobDlg dialog


CAddEditJobDlg::CAddEditJobDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddEditJobDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddEditJobDlg)
	m_csDescription = _T("");
	m_csCustomer = _T("");
	//}}AFX_DATA_INIT
	m_blnJulianDate=FALSE;    //for the future
	m_blnPriorSuffix=FALSE;
}


void CAddEditJobDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddEditJobDlg)
	DDX_Control(pDX, IDC_EDT_CUSTOMER, m_edtCustomer);
	DDX_Control(pDX, IDC_DESCRIPTION, m_edtDescription);
	DDX_Control(pDX, IDC_USE_SERIALIZATION, m_chkUseSerialization);
	DDX_Control(pDX, IDC_JOB_LIST, m_cmbJobList);
	DDX_Control(pDX, IDC_SETUP_SERIALIZATION, m_btnSetupSerialization);
	DDX_Text(pDX, IDC_DESCRIPTION, m_csDescription);
	DDX_Control(pDX, IDC_JOB_INFO, m_FGJobInfo);
	DDX_Text(pDX, IDC_EDT_CUSTOMER, m_csCustomer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddEditJobDlg, CDialog)
	//{{AFX_MSG_MAP(CAddEditJobDlg)
	ON_BN_CLICKED(IDC_USE_SERIALIZATION, OnUseSerialization)
	ON_CBN_SELCHANGE(IDC_JOB_LIST, OnSelchangeJobList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddEditJobDlg message handlers

BEGIN_EVENTSINK_MAP(CAddEditJobDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CAddEditJobDlg)
	ON_EVENT(CAddEditJobDlg, IDC_UPDATE_JOB, -600 /* Click */, OnClickUpdateJob, VTS_NONE)
	ON_EVENT(CAddEditJobDlg, IDC_CANCEL, -600 /* Click */, OnClickCancel, VTS_NONE)
	ON_EVENT(CAddEditJobDlg, IDC_EDIT_PANEL_LABEL, -600 /* Click */, OnClickEditPanelLabel, VTS_NONE)
	ON_EVENT(CAddEditJobDlg, IDC_ADD_JOB, -600 /* Click */, OnClickAddJob, VTS_NONE)
	ON_EVENT(CAddEditJobDlg, IDC_SETUP_SERIALIZATION, -600 /* Click */, OnClickSetupSerialization, VTS_NONE)
	ON_EVENT(CAddEditJobDlg, IDC_COPY_JOB, -600 /* Click */, OnClickCopyJob, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()



BOOL CAddEditJobDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int			nUpperBound,i;
	CString		csCurrentJobName;
	
	// Get Job listing from database
	m_poDatabase->GetJobNames ( &m_csJobArray );	

	// list all jobs in the array
	ListJobs();

	// select the job that was passed to us
	nUpperBound = m_cmbJobList.GetCount();
	for (i=0;i<nUpperBound;i++)
	{
		m_cmbJobList.GetLBText (i,csCurrentJobName);
		if (csCurrentJobName==m_csJobName)
			m_cmbJobList.SetCurSel(i);
	}

	// Get the selected job attributes.
	
	InitJobInfoGrid();	
	OnUseSerialization(); 	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAddEditJobDlg::OnClickUpdateJob() 
{
	// Get the job information from the dialog box fields.
CString csTemp;
	UpdateData(TRUE);

	m_oJob.SetJobName(m_csJobName);
	
	m_edtDescription.GetWindowText(csTemp);
	m_oJob.SetDescription(csTemp);
	
	m_edtCustomer.GetWindowText(csTemp);
	m_oJob.SetCustomer(csTemp);

	
	if ( GetJobInfo() )
	{
		m_poDatabase->SetJobAttributes ( &m_oJob );

		// Add serialization parameters to DB.

		m_poDatabase->SetSNAttributes ( m_csJobName, 
										m_bUseSerialization,
										m_nSNType,
										m_nSNLength,
										m_csStartingSN,
										m_blnUseCheckDigit,
										m_csCheckDigitType,
										m_csCheckDigitSource);


	}

}



void CAddEditJobDlg::OnClickCancel() 
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

void CAddEditJobDlg::ListJobs ( void ) 
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
			// get the next job
			csTemp = m_csJobArray[i];

			// Remove description.
			nPos = csTemp.Find ( "\t" );
			csName = csTemp.Left ( nPos );

			// add name to list
			m_cmbJobList.AddString ( csName );
		}
	}

}

void CAddEditJobDlg::OnClickEditPanelLabel() 
{
CString csTemp;

		// Use manual method.
		CDBPanelLabelDlg SetupPanelLabel;

		// pass along this job so both dialog boxes
		// are working with the same job and don't
		// trample over each other's work
		SetupPanelLabel.m_poJob = &m_oJob;
		
		// pass along the database pointer
		SetupPanelLabel.m_poDatabase = m_poDatabase;
	
		// launch the manual job setup dialog box
		SetupPanelLabel.DoModal();

		// refresh our job object from the database

}


void CAddEditJobDlg::OnClickAddJob() 
{
	CJobNameDlg	oJobNameDlg;
	CString csPlacementAttributes,csTemp;
	
	// launch the job name dialog
	oJobNameDlg.DoModal();

	// retrieve the new job name
	CString	csNewJobName = oJobNameDlg.m_csJobName;
	if (CheckForExistingJobRecord(csNewJobName)) // check for exiting job
	{
		csTemp.LoadString(IDS_DUPLICATE_JOB_EXIST);
		AfxMessageBox(csTemp);
		return;
	}
	if (!csNewJobName.IsEmpty())
	{
		// declare a new empty job
		CJob	oNewJob;
		oNewJob.SetJobName(csNewJobName);
		oNewJob.SetDescription("Enter description here.");
		oNewJob.SetXOffset(0);
		oNewJob.SetYOffset(0);
		oNewJob.SetLabelStockXOffset(0);
		oNewJob.SetLabelStockYOffset(0);
		oNewJob.SetPanelDimension("000000,000000");
		oNewJob.SetJob2up(FALSE);
		oNewJob.SetUseWYSIWYG(FALSE);
		oNewJob.SetUseDataName1(FALSE); 
		oNewJob.SetUseDataName2(FALSE); 
		oNewJob.SetUseDataName3(FALSE); 
		oNewJob.SetUseDataName4(FALSE); 
		oNewJob.SetUseDataName5(FALSE); 
		
		// set the placement attributes
		m_poDatabase->GetTemplateList(&csTemp);
		csTemp = csTemp.Left(csTemp.Find(";"));
		// x=0,y=0,rot=0, template
		csPlacementAttributes =  csTemp + ",";
		// empty the interim value
		csTemp.Empty();
		// add the first useable printer
		m_poDatabase->GetUsablePrinterList(&csTemp);
		csTemp = csTemp.Left(csTemp.Find(";"));
		csPlacementAttributes = csPlacementAttributes + csTemp;
		// scan the label
		csPlacementAttributes = csPlacementAttributes + ",YES;";
		oNewJob.SetPlacementAttributes(csPlacementAttributes);


		// write the new job to the database
		m_poDatabase->SetJobAttributes(&oNewJob);

		// add the new job to the combobox
		m_cmbJobList.AddString(csNewJobName);

		m_bUseSerialization = TRUE;
		m_nSNType = BASE10;
		m_nSNLength = 8;
		m_csStartingSN = "00000000";
		m_chkUseSerialization.SetCheck ( TRUE );
		m_btnSetupSerialization.SetEnabled ( TRUE );
		m_blnJulianDate=FALSE;


//	add check digit vars.

		m_blnUseCheckDigit=FALSE;
		m_csCheckDigitType="Not Defined";
		m_csCheckDigitSource="Not Defined";



		m_poDatabase->SetSNAttributes ( csNewJobName, 
												  m_bUseSerialization,
												  m_nSNType,
												  m_nSNLength,
												  m_csStartingSN,
												  m_blnUseCheckDigit,
												  m_csCheckDigitType,
												  m_csCheckDigitSource);

		// select the new job
		m_cmbJobList.SelectString(0,csNewJobName);
		m_csJobName = csNewJobName;

		m_oJob.SetJobName(m_csJobName);
	
		
		
		ResetGrid();
		
		InitJobInfoGrid();	
		OnUseSerialization(); 	


	}
}





void CAddEditJobDlg::OnUseSerialization() 
{
	
	m_bUseSerialization = m_chkUseSerialization.GetCheck();

	if ( m_bUseSerialization )
	{
//		m_edtData1.EnableWindow ( FALSE );
//		m_edtData2.EnableWindow ( FALSE );
		m_btnSetupSerialization.SetEnabled ( TRUE );
	}
	else
	{
//		m_edtData1.EnableWindow ( TRUE );
//		m_edtData2.EnableWindow ( TRUE );
		m_btnSetupSerialization.SetEnabled ( FALSE );
	}
	
}



void CAddEditJobDlg::OnClickSetupSerialization() 
{
BOOL blnSetupSerContinue=FALSE;
CString csTemp;
int  nRequiredLength;


	CSetupSerializationDlg SetupSerialization;
	

	SetupSerialization.m_nSNType = m_nSNType;
	SetupSerialization.m_nSNLength = m_nSNLength;
	SetupSerialization.m_csStartingSN = m_csStartingSN;
	SetupSerialization.m_blnUseCheckDigit=m_blnUseCheckDigit;
	SetupSerialization.m_csCheckDigitType=m_csCheckDigitType; //same as type
	SetupSerialization.m_csCheckDigitSource=m_csCheckDigitSource;

	do 
	{
		if (SetupSerialization.DoModal() == IDOK) 
		{
			nRequiredLength = SetupSerialization.m_nSNLength;
			csTemp = SetupSerialization.m_csStartingSN;
			
			if (csTemp.GetLength()!= nRequiredLength)
			{
				csTemp.LoadString(IDS_ERR_SERIALNUMBER_LENGTH);
				AfxMessageBox(csTemp);
				blnSetupSerContinue=TRUE;

			}
			else
			{
				m_nSNType = SetupSerialization.m_nSNType;
				m_nSNLength = SetupSerialization.m_nSNLength;
				m_csStartingSN = SetupSerialization.m_csStartingSN;

				m_blnUseCheckDigit=SetupSerialization.m_blnUseCheckDigit;

				if (m_blnUseCheckDigit)
				{
					m_csCheckDigitType=SetupSerialization.m_csCheckDigitType;
					m_csCheckDigitSource=SetupSerialization.m_csCheckDigitSource;
				}
				else
				{
					m_csCheckDigitType="Not Defined";
					m_csCheckDigitSource="Not Defined";


				}


				blnSetupSerContinue=FALSE;

			}
		}
		else
		{
			blnSetupSerContinue=FALSE;
		}
	} while (blnSetupSerContinue);

}


void CAddEditJobDlg::InitJobInfoGrid()
{

	m_FGJobInfo.InitFlexGrid(6,5);
	m_FGJobInfo.AddColumnHeaders("Field Name   ");
	m_FGJobInfo.AddColumnHeaders("Value        ");
	m_FGJobInfo.AddColumnHeaders("Used  ");
	m_FGJobInfo.AddColumnHeaders("Printed  ");
	m_FGJobInfo.AddColumnHeaders("Logged  ");


	

	AddJobInfoToFlexGrid();
	m_FGJobInfo.SetAllowEditing(true);


}

void CAddEditJobDlg::AddJobInfoToFlexGrid()
{

CJob *pJobInfo;
long nItem;
CString csTemp;
CString csBuffer;
COleVariant nVar;
	nItem=1;


    if (m_csJobName!="") 
	{

		GetSerialJobInfo();
		
		m_poDatabase->GetJobAttributes ( m_csJobName, &m_oJob );
		
		// retrieve the data for this dialog
		m_csDescription = m_oJob.GetDescription();
		m_csCustomer = m_oJob.GetCustomer();

		
		pJobInfo=&m_oJob;

		//nVar=1;

		m_FGJobInfo.CreateUsedChkBoxes(0, 1, 2);			
		m_FGJobInfo.CreatePrintedChkBoxes(0, 1, 3);			
		m_FGJobInfo.CreateLoggedChkBoxes(0, 1, 4);			

		nVar=(long)nItem;
		if (pJobInfo->GetUseDataName1())
		{
			csTemp = pJobInfo->GetDataName1();
			csTemp = csTemp +"\t" +	pJobInfo->GetDataValue1();

			m_FGJobInfo.AddItem(csTemp,nVar);

			m_FGJobInfo.m_btnUsedChkBox[0].SetCheck(1);
			if (pJobInfo->GetPrintDataValue1())
			{
				m_FGJobInfo.m_btnPrintedChkBox[0].SetCheck(1);

			}

			if (pJobInfo->GetLogDataValue1())
			{
				m_FGJobInfo.m_btnLoggedChkBox[0].SetCheck(1);

			}




		}
		else
		{
			m_FGJobInfo.AddItem("Not Used \t Not Used",nVar);

		}
		nItem+=1;
		nVar=(long)nItem;

		m_FGJobInfo.CreateUsedChkBoxes(1, 2, 2);			
		m_FGJobInfo.CreatePrintedChkBoxes(1, 2, 3);			
		m_FGJobInfo.CreateLoggedChkBoxes(1, 2, 4);			

		if (pJobInfo->GetUseDataName2())
		{

			csTemp = pJobInfo->GetDataName2();
			csTemp = csTemp +"\t" +	pJobInfo->GetDataValue2();
			m_FGJobInfo.AddItem(csTemp,nVar);

			m_FGJobInfo.m_btnUsedChkBox[1].SetCheck(1);
			if (pJobInfo->GetPrintDataValue2())
			{
				m_FGJobInfo.m_btnPrintedChkBox[1].SetCheck(1);
			}
			if (pJobInfo->GetLogDataValue2())
			{
				m_FGJobInfo.m_btnLoggedChkBox[1].SetCheck(1);
			}
		
		
		}
		else
		{
			m_FGJobInfo.AddItem("Not Used \t Not Used",nVar);

		}
		nItem+=1;
		nVar=(long)nItem;

		m_FGJobInfo.CreateUsedChkBoxes(2, 3, 2);			
		m_FGJobInfo.CreatePrintedChkBoxes(2, 3, 3);			
		m_FGJobInfo.CreateLoggedChkBoxes(2, 3, 4);			

		if (pJobInfo->GetUseDataName3())
		{

			csTemp = pJobInfo->GetDataName3();
			csTemp = csTemp +"\t" +	pJobInfo->GetDataValue3();
			m_FGJobInfo.AddItem(csTemp,nVar);

			m_FGJobInfo.m_btnUsedChkBox[2].SetCheck(1);
			if (pJobInfo->GetPrintDataValue3())
			{
				m_FGJobInfo.m_btnPrintedChkBox[2].SetCheck(1);
			}
			if (pJobInfo->GetLogDataValue3())
			{
				m_FGJobInfo.m_btnLoggedChkBox[2].SetCheck(1);
			}
		
		
		}
		else
		{
			m_FGJobInfo.AddItem("Not Used \t Not Used",nVar);

		}
		nItem+=1;
		nVar=(long)nItem;

		m_FGJobInfo.CreateUsedChkBoxes(3, 4, 2);			
		m_FGJobInfo.CreatePrintedChkBoxes(3, 4, 3);			
		m_FGJobInfo.CreateLoggedChkBoxes(3, 4, 4);			

		if (pJobInfo->GetUseDataName4())
		{

			csTemp = pJobInfo->GetDataName4();
			csTemp = csTemp +"\t" +	pJobInfo->GetDataValue4();
			m_FGJobInfo.AddItem(csTemp,nVar);

			m_FGJobInfo.m_btnUsedChkBox[3].SetCheck(1);
			if (pJobInfo->GetPrintDataValue4())
			{
				m_FGJobInfo.m_btnPrintedChkBox[3].SetCheck(1);
			}
			if (pJobInfo->GetLogDataValue4())
			{
				m_FGJobInfo.m_btnLoggedChkBox[3].SetCheck(1);
			}
		
		
		}
		else
		{
			m_FGJobInfo.AddItem("Not Used \t Not Used",nVar);

		}
		nItem+=1;
		nVar=(long)nItem;

		
		m_FGJobInfo.CreateUsedChkBoxes(4, 5, 2);			
		m_FGJobInfo.CreatePrintedChkBoxes(4, 5, 3);			
		m_FGJobInfo.CreateLoggedChkBoxes(4, 5, 4);			

		if (pJobInfo->GetUseDataName5())
		{
			csTemp = pJobInfo->GetDataName5();
			csTemp = csTemp +"\t" +	pJobInfo->GetDataValue5();
			m_FGJobInfo.AddItem(csTemp,nVar);

			m_FGJobInfo.m_btnUsedChkBox[4].SetCheck(1);
			if (pJobInfo->GetPrintDataValue5())
			{
				m_FGJobInfo.m_btnPrintedChkBox[4].SetCheck(1);
			}
			if (pJobInfo->GetLogDataValue5())
			{
				m_FGJobInfo.m_btnLoggedChkBox[4].SetCheck(1);
			}

		}
		else
		{
			m_FGJobInfo.AddItem("Not Used \t Not Used",nVar);

		}

	}


	UpdateData(FALSE);

}

BOOL CAddEditJobDlg::GetJobInfo () 
{
	UpdateData(TRUE);

	if (m_csJobName !="")
	{
		m_oJob.SetJobName ( m_csJobName );
		if (!GetJobInfoData1())
		{
			m_blnPriorSuffix=FALSE;
			return FALSE;
		}
		if (!GetJobInfoData2())
		{
			m_blnPriorSuffix=FALSE;
			return FALSE;
		}

		if (!GetJobInfoData3())
		{
			m_blnPriorSuffix=FALSE;
			return FALSE;
		}

		if (!GetJobInfoData4())
		{
			m_blnPriorSuffix=FALSE;
			return FALSE;
		}

		if (!GetJobInfoData5())
		{
			m_blnPriorSuffix=FALSE;
			return FALSE;
		}
	}


	return ( TRUE );
}


BOOL CAddEditJobDlg::GetSerialJobInfo () 
{

	BOOL
		bUseSerialization,
		blnUseChkDigit;

	int
		nBase,
		nLength;

	CString
		csSerialNumber,
		csCheckDigitSource,
		csCheckDigitType;



	// refresh the job object
	m_poDatabase->GetJobAttributes ( m_csJobName, &m_oJob );
	

//	int		nRescans,nRepicks,nNumberOfNosepieces;
//	BOOL	b2up;
//	m_poDatabase->GetGeneralAttributes(&nRescans,&nRepicks,&b2up,&nNumberOfNosepieces);


		// update the controls in this dialog

	
	// Get serial number info.

	m_poDatabase->GetSNAttributes (m_csJobName, 
										  &bUseSerialization,
										  &nBase,
										  &nLength,
										  &csSerialNumber,
										  &blnUseChkDigit,
										  &csCheckDigitSource,
										  &csCheckDigitType);


	m_bUseSerialization = bUseSerialization;
	m_nSNType = nBase;
	m_nSNLength = nLength;
	m_csStartingSN = csSerialNumber;

// for check digit handling

	m_blnUseCheckDigit=blnUseChkDigit;
	m_csCheckDigitType=csCheckDigitType;
	m_csCheckDigitSource=csCheckDigitSource;




	if ( m_bUseSerialization )
	{
		m_chkUseSerialization.SetCheck(1);
	}
	else
	{
		m_chkUseSerialization.SetCheck(0);
	}

	return ( TRUE );
}


BOOL CAddEditJobDlg::GetJobInfoData1()
{
int nRowSave,
	nColSave;

CString csBuffer;


	nRowSave=m_FGJobInfo.GetRow();	
	nColSave=m_FGJobInfo.GetCol();	


	m_oJob.SetUseDataName1(m_FGJobInfo.m_btnUsedChkBox[0].GetCheck());
	m_oJob.SetPrintDataValue1(m_FGJobInfo.m_btnPrintedChkBox[0].GetCheck());
	m_oJob.SetLogDataValue1(m_FGJobInfo.m_btnLoggedChkBox[0].GetCheck());

	csBuffer=m_FGJobInfo.GetTextData(1,0);
	csBuffer.MakeUpper();

	if (csBuffer.Find("SUFFIX")!=-1)
		if (m_blnPriorSuffix)
		{
			AfxMessageBox("Data Item [1]: Only One Suffix String Allowed");
			return FALSE;
		}
		else
			m_blnPriorSuffix=TRUE;


	
	m_oJob.SetDataName1(m_FGJobInfo.GetTextData(1,0));
	m_oJob.SetDataValue1(m_FGJobInfo.GetTextData(1,1));

	
	m_FGJobInfo.SetRow(nRowSave);	
	m_FGJobInfo.SetCol(nColSave);	

	return TRUE;
}

BOOL CAddEditJobDlg::GetJobInfoData2()
{
int nRowSave,
	nColSave;

CString csBuffer;


	nRowSave=m_FGJobInfo.GetRow();	
	nColSave=m_FGJobInfo.GetCol();	


	m_oJob.SetUseDataName2(m_FGJobInfo.m_btnUsedChkBox[1].GetCheck());
	m_oJob.SetPrintDataValue2(m_FGJobInfo.m_btnPrintedChkBox[1].GetCheck());
	m_oJob.SetLogDataValue2(m_FGJobInfo.m_btnLoggedChkBox[1].GetCheck());


	csBuffer=m_FGJobInfo.GetTextData(2,0);
	csBuffer.MakeUpper();
	

	if (csBuffer.Find("SUFFIX")!=-1)
		if (m_blnPriorSuffix)
		{
			AfxMessageBox("Data Item [2]: Only One Suffix String Allowed");
			return FALSE;
		}
		else
			m_blnPriorSuffix=TRUE;
	
	
	
	m_oJob.SetDataName2(m_FGJobInfo.GetTextData(2,0));
	m_oJob.SetDataValue2(m_FGJobInfo.GetTextData(2,1));
	

	


	m_FGJobInfo.SetRow(nRowSave);	
	m_FGJobInfo.SetCol(nColSave);	

	return TRUE;
}


BOOL CAddEditJobDlg::GetJobInfoData3()
{
int nRowSave,
	nColSave;

CString csBuffer;

	nRowSave=m_FGJobInfo.GetRow();	
	nColSave=m_FGJobInfo.GetCol();	


	m_oJob.SetUseDataName3(m_FGJobInfo.m_btnUsedChkBox[2].GetCheck());
	m_oJob.SetPrintDataValue3(m_FGJobInfo.m_btnPrintedChkBox[2].GetCheck());
	m_oJob.SetLogDataValue3(m_FGJobInfo.m_btnLoggedChkBox[2].GetCheck());


	csBuffer=m_FGJobInfo.GetTextData(3,0);
	csBuffer.MakeUpper();
	

	if (csBuffer.Find("SUFFIX")!=-1)
		if (m_blnPriorSuffix)
		{
			AfxMessageBox("Data Item [3]: Only One Suffix String Allowed");
			return FALSE;
		}
		else
			m_blnPriorSuffix=TRUE;
	
	
	m_oJob.SetDataName3(m_FGJobInfo.GetTextData(3,0));
	m_oJob.SetDataValue3(m_FGJobInfo.GetTextData(3,1));



	m_FGJobInfo.SetRow(nRowSave);	
	m_FGJobInfo.SetCol(nColSave);	

	return TRUE;
}

BOOL CAddEditJobDlg::GetJobInfoData4()
{
int nRowSave,
	nColSave;

CString csBuffer;

	nRowSave=m_FGJobInfo.GetRow();	
	nColSave=m_FGJobInfo.GetCol();	


	m_oJob.SetUseDataName4(m_FGJobInfo.m_btnUsedChkBox[3].GetCheck());
	m_oJob.SetPrintDataValue4(m_FGJobInfo.m_btnPrintedChkBox[3].GetCheck());
	m_oJob.SetLogDataValue4(m_FGJobInfo.m_btnLoggedChkBox[3].GetCheck());

	csBuffer=m_FGJobInfo.GetTextData(4,0);
	csBuffer.MakeUpper();
	

	if (csBuffer.Find("SUFFIX")!=-1)
		if (m_blnPriorSuffix)
		{
			AfxMessageBox("Data Item [4]: Only One Suffix String Allowed");
			return FALSE;
		}
		else
			m_blnPriorSuffix=TRUE;

	
	m_oJob.SetDataName4(m_FGJobInfo.GetTextData(4,0));
	m_oJob.SetDataValue4(m_FGJobInfo.GetTextData(4,1));

	m_FGJobInfo.SetRow(nRowSave);	
	m_FGJobInfo.SetCol(nColSave);	

	return TRUE;

}

BOOL CAddEditJobDlg::GetJobInfoData5()
{
int nRowSave,
	nColSave;

CString csBuffer;


	nRowSave=m_FGJobInfo.GetRow();	
	nColSave=m_FGJobInfo.GetCol();	


	m_oJob.SetUseDataName5(m_FGJobInfo.m_btnUsedChkBox[4].GetCheck());
	m_oJob.SetPrintDataValue5(m_FGJobInfo.m_btnPrintedChkBox[4].GetCheck());
	m_oJob.SetLogDataValue5(m_FGJobInfo.m_btnLoggedChkBox[4].GetCheck());

	csBuffer=m_FGJobInfo.GetTextData(5,0);
	csBuffer.MakeUpper();
	

	if (csBuffer.Find("SUFFIX")!=-1)
		if (m_blnPriorSuffix)
		{
			AfxMessageBox("Data Item [5]: Only One Suffix String Allowed");
			return FALSE;
		}
		else
			m_blnPriorSuffix=TRUE;

	
	
	m_oJob.SetDataName5(m_FGJobInfo.GetTextData(5,0));
	m_oJob.SetDataValue5(m_FGJobInfo.GetTextData(5,1));

	m_FGJobInfo.SetRow(nRowSave);	
	m_FGJobInfo.SetCol(nColSave);	

	return TRUE;
}

void CAddEditJobDlg::ResetGrid()
{
int nIndex;
CString csTemp;
COleVariant nVar;
	m_FGJobInfo.Clear();
	m_FGJobInfo.InitFlexGrid(6,5);
	m_FGJobInfo.AddColumnHeaders("Field Name   ");
	m_FGJobInfo.AddColumnHeaders("Value        ");
	m_FGJobInfo.AddColumnHeaders("Used  ");
	m_FGJobInfo.AddColumnHeaders("Printed  ");
	m_FGJobInfo.AddColumnHeaders("Logged  ");

	csTemp = CString(" ") +"\t" +	CString(" ") ;

	m_csDescription = "";
	m_csCustomer = "";
	UpdateData(FALSE);

	for(nIndex=0;nIndex<5;nIndex++)
	{
		nVar=(long)(nIndex+1);
		m_FGJobInfo.m_btnUsedChkBox[nIndex].SetCheck(0);
		m_FGJobInfo.m_btnPrintedChkBox[nIndex].SetCheck(0);
		m_FGJobInfo.m_btnLoggedChkBox[nIndex].SetCheck(0);
		m_FGJobInfo.AddItem(" ",nVar);
	
	}

}

void CAddEditJobDlg::OnSelchangeJobList() 
{
	m_cmbJobList.GetLBText (m_cmbJobList.GetCurSel(),m_csJobName);

	InitJobInfoGrid();	
	OnUseSerialization();	

	
}

BOOL CAddEditJobDlg::CheckForExistingJobRecord(CString csJobName)
{
int nCount,
	nIndex;


	nCount=m_csJobArray.GetSize();

	for (nIndex=0;nIndex<nCount;nIndex++)
	{
		if (m_csJobArray[nIndex].Find(csJobName)!=-1)
		{
			return TRUE;
		}
	}
	return FALSE;
}

void CAddEditJobDlg::OnClickCopyJob() 
{
	CJobNameDlg	oJobNameDlg;
	CString csPlacementAttributes,csTemp;
	
	// launch the job name dialog
	oJobNameDlg.DoModal();

	// retrieve the new job name
	CString	csNewJobName = oJobNameDlg.m_csJobName;
	if (CheckForExistingJobRecord(csNewJobName)) // check for exiting job
	{
		csTemp.LoadString(IDS_DUPLICATE_JOB_EXIST);
		AfxMessageBox(csTemp);
		return;
	}
	m_cmbJobList.AddString(csNewJobName);
		// select the new job
	m_cmbJobList.SelectString(0,csNewJobName);
	m_csJobName = csNewJobName;

	m_poDatabase->SetSNAttributes ( csNewJobName, 
												  m_bUseSerialization,
												  m_nSNType,
												  m_nSNLength,
												  m_csStartingSN,
												  m_blnUseCheckDigit,
												  m_csCheckDigitType,
												  m_csCheckDigitSource);


	UpdateData(TRUE);

	m_oJob.SetJobName(m_csJobName);
	
	
	
}
