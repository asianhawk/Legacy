// RunDialog.cpp : implementation file
//

#include "stdafx.h"
#include "PACS.h"
#include "RunDialog.h"
#include "Utilities.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define ID_TIMER_1 1000
#define ID_TIMER_2 1001
CRunDialog *g_poRunDalog;

/////////////////////////////////////////////////////////////////////////////
// CRunDialog dialog


CRunDialog::CRunDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CRunDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRunDialog)
	m_nRelabelCount = 0;
	//}}AFX_DATA_INIT

	
		ASSERT(pParent != NULL);

		mp_Parent = pParent;
		m_int_ID = CRunDialog::IDD;
		m_blnExitRunMode=FALSE;
}


void CRunDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRunDialog)
	DDX_Control(pDX, IDC_SPIN1, m_ctrlRelabelSpinner);
	DDX_Control(pDX, IDC_PANEL_PROGRESS, m_pgrPanelProgress);
	DDX_Control(pDX, IDC_CMD_HOLD, m_cmd_hold);
	DDX_Control(pDX, IDC_LABEL_COUNT, m_lblLabelCount);
	DDX_Control(pDX, IDC_LABEL_JOB_NAME, m_lblJobName);
	DDX_Control(pDX, IDC_DATETIME_LABEL, m_lblDateTime);
	DDX_Control(pDX, IDC_FG_JOB_STATUS, m_FGJobStatus);
	DDX_Control(pDX, IDC_FG_JOB_STATS, m_FGJobStats);
	DDX_Control(pDX, IDC_LBL_CURRENT_STATUS, m_lblCurrentJobStatus);
	DDX_Text(pDX, IDC_RELABEL, m_nRelabelCount);
	DDV_MinMaxInt(pDX, m_nRelabelCount, 0, 1000);
	DDX_Control(pDX, IDC_LABEL_JOB_DESCRIPTION, m_lblJobDescription);
	DDX_Control(pDX, IDC_LBL_PRINTERTEMPLATE_NAME, m_lblPrinterTemplateName);
	DDX_Control(pDX, IDC_LBL_LINDEX, m_lblCurrentLabelIndex);
	DDX_Control(pDX, IDC_LBL_MAX_LBL, m_lblMaxLabelsPerPlate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRunDialog, CDialog)
	//{{AFX_MSG_MAP(CRunDialog)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRunDialog message handlers

BEGIN_EVENTSINK_MAP(CRunDialog, CDialog)
    //{{AFX_EVENTSINK_MAP(CRunDialog)
	ON_EVENT(CRunDialog, IDC_CMD_HOLD, -600 /* Click */, OnClickCmdHold, VTS_NONE)
	ON_EVENT(CRunDialog, IDC_CMD_RELABEL, -600 /* Click */, OnClickCmdRelabel, VTS_NONE)
	ON_EVENT(CRunDialog, IDC_CMD_EXIT, -600 /* Click */, OnClickCmdExit, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()




///////////////////////////////////
//
// Initialize the Rundialog with the applicator
//
/////////////////////////////////////

BOOL CRunDialog::Initialize ( CApplicatorControl * p_applicator )
{

	m_opLabeler = p_applicator;

	m_bln_first_run = TRUE;

	return TRUE;
}

///////////////////////////////////
//
// run the job
//
/////////////////////////////////////

BOOL CRunDialog::Run ( long *lPanelCount )
{
	
	BOOL bReturn;

	m_poPrinterControl= m_opLabeler->GetPrinterObject();
	m_poScannerControl= m_opLabeler->GetScannerObject();

	
	m_poPrinterControl->SetPrintedSerialNumber("");
	m_poScannerControl->m_csScannedLabel="";

	m_lMaxPanels = *lPanelCount;
	
	if (m_lMaxPanels>0)
	{
		m_pgrPanelProgress.SetRange ( 0, 100 );
		m_pgrPanelProgress.SetPos ( 0 );
	}
	else
	{
		m_pgrPanelProgress.ShowWindow(FALSE); 

	}


	
	
	UpdateForm();
	
	// a timer is used here to update the form continuously
	SetTimer ( ID_TIMER_1, 1000, NULL );  // time interval is 1 second
	SetTimer ( ID_TIMER_2, 5000, NULL );  // time interval is 5 second
	

	InitJobStatusGrid();
	InitJobStats();
	g_poRunDalog=this;
	ShowWindow(TRUE);
	bReturn = m_opLabeler->Run (lPanelCount );

	KillTimer ( ID_TIMER_1 );
	KillTimer ( ID_TIMER_2 );

	return ( bReturn );

}



///////////////////////////////////
//
// create a dialog box
//
/////////////////////////////////////
BOOL CRunDialog::Create()
{


	return CDialog::Create(m_int_ID, mp_Parent);
}

///////////////////////////////////
//
//  Handler for <Hold> button
//
//
//
///////////////////////////////////

void CRunDialog::OnClickCmdHold() 
{
	m_opLabeler->GetDIOObject()->ErrorBitOn(); 
	m_opLabeler->GetDIOObject()->ApplyLabelBitOff();
	m_opLabeler->GetDIOObject()->ApplicatorReadyBitOff() ;
	Sleep(30);
	m_opLabeler->ReqHold();
}

///////////////////////////////////
//
//	Functionality:
//  Update all the run-form 
//  info.
//
//////////////////////////////////
BOOL CRunDialog::UpdateForm()
{
	

	CString csTemp;

	CJob *p_oJobInfo;

	CSNManager *p_oSNManager;
	CUtilities Utility;

	long
		lPanelCount;

	float
		fPanelPercent;



	// Get serial number manager and serial number if applicable.

	p_oSNManager = m_opLabeler->GetSNManager();


	if ( p_oSNManager->UseSerialization() )
	{

		if (m_poPrinterControl->GetPrintedSerialNumber ()!="")
		{
			if (m_poPrinterControl->GetSuffix().IsEmpty())
			{
				csTemp = m_poPrinterControl->GetPrefixes("\t")+
		 			  m_poPrinterControl->GetPrintedSerialNumber ();
			}
			else
			{
				csTemp = m_poPrinterControl->GetPrefixes("\t")+
		 			     m_poPrinterControl->GetPrintedSerialNumber ()+
						 CString("\t")+
					     m_poPrinterControl->GetSuffix();

			}
			if (p_oSNManager->m_blnUseCheckDigit)
			{
				csTemp=csTemp + CString("\t") + m_poPrinterControl->GetCheckDigitValue();


			}



		}
		else
			csTemp="";

		if (csTemp!="")
		{
			m_FGJobStatus.UpdateRow(1,csTemp);
			UpdateJobStats();
		}
		
		if (m_poScannerControl->m_csScannedLabel!="")
		{
			csTemp=ParseScannedLabel(m_poScannerControl->m_csScannedLabel,"\t");
			if (csTemp.IsEmpty())
				csTemp=m_poScannerControl->m_csScannedLabel;
			m_FGJobStatus.UpdateRow(2,csTemp);
		}
		

	}		 
	else
	{

		m_FGJobStatus.UpdateRow(1,"PrePrinted");
		csTemp=m_poScannerControl->m_csScannedLabel;
		m_FGJobStatus.UpdateRow(2,csTemp);
		UpdateJobStats();


	}
	
	
	// Get job info and update the screen.
	
	
	p_oJobInfo = m_opLabeler->GetJob ();
	

	m_lblJobName.SetCaption ( p_oJobInfo->GetJobName() );
	m_lblJobDescription.SetCaption ( p_oJobInfo->GetDescription()  );
	
	csTemp.Format ( "%ld", p_oJobInfo->GetLabelCount() );
	m_lblLabelCount.SetCaption ( csTemp );

	// Show job progress.

	if ( m_lMaxPanels > 0 )
	{
		lPanelCount = p_oJobInfo->GetPanelCount();
		csTemp.Format ( "%ld of %ld", lPanelCount, m_lMaxPanels );
		fPanelPercent = ( (float)lPanelCount / (float)m_lMaxPanels ) * (float)100.0;
		m_pgrPanelProgress.SetPos ( (int)fPanelPercent );
	}
	else
	{
		csTemp.Format ( "%ld of %s", p_oJobInfo->GetPanelCount(), "Unlimited" );
		m_pgrPanelProgress.SetPos ( 0 );
	}


	csTemp = Utility.GetDateTime();
	m_lblDateTime.SetCaption ( csTemp );
   
	GetDlgItem(IDC_LBL_CURRENT_STATUS)->SetWindowText(m_opLabeler->m_csCurrentJobStatus);
	return ( TRUE );

}




void CRunDialog::OnTimer(UINT nIDEvent) 
{
	// only one timer here
	


	if (nIDEvent == ID_TIMER_1)
	{
		CDialog::OnTimer(nIDEvent);
		KillTimer(ID_TIMER_1);
		UpdateForm();
		SetTimer ( ID_TIMER_1, 1000, NULL );  // time interval is 1 second

	}
	CDialog::OnTimer(nIDEvent);

	if (nIDEvent == ID_TIMER_2)
	{
		if (!m_opLabeler->m_blnIsPrinting)
		{
			KillTimer(ID_TIMER_1);
			KillTimer(ID_TIMER_2);

			m_poPrinterControl->GetStatus();
			// a timer is used here to update the form continuously
			SetTimer ( ID_TIMER_1, 1000, NULL );  // time interval is 1 second
			SetTimer ( ID_TIMER_2, 10000, NULL );  // time interval is 5 second

		}
	}
	


}

void CRunDialog::UpDateStatus(CString csJobStatusMessage) 
{
    
	if (!csJobStatusMessage.IsEmpty())
		m_lblCurrentJobStatus.SetCaption((LPCTSTR) csJobStatusMessage);
	
}

void CRunDialog::UpDateDisplay(CString csPrinterTemplateName) 
{
    
	if (!csPrinterTemplateName.IsEmpty())
		m_lblPrinterTemplateName.SetCaption((LPCTSTR) csPrinterTemplateName);
	
}

void CRunDialog::UpDatePlateInfo(int nCurrentIndex,  int nMaxLabelsPerPlate) 
{
CString csTemp;  
	
	csTemp.Format("%d",nCurrentIndex);
	m_lblCurrentLabelIndex.SetCaption((LPCTSTR) csTemp);
	
	csTemp.Format("%d",nMaxLabelsPerPlate);
	m_lblMaxLabelsPerPlate.SetCaption((LPCTSTR) csTemp);

	UpdateData(TRUE);


}


void CRunDialog::OnCancel() 
{
		

	// Do not allow to be cancelled.

}

BOOL CRunDialog::OnInitDialog() 
{
//	m_ctrlRelabelSpinner.SetRange(0,1000);
	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRunDialog::InitJobStatusGrid()
{
int nTotalCols=8;
CString csBuffer,
		csSuffix1,
		csSuffix2,
		csSuffix3,
		csSuffix4,
		csSuffix5;

CSNManager *p_oSNManager;

	p_oSNManager=NULL;
    GetColumnHeaders();	


	p_oSNManager = m_opLabeler->GetSNManager();

	

	if (!p_oSNManager->m_blnUseCheckDigit) 
		nTotalCols=nTotalCols-1;


	if (m_csHeader1=="")
		nTotalCols=nTotalCols-1;
	
	if (m_csHeader2=="")
		nTotalCols=nTotalCols-1;

	if (m_csHeader3=="")
		nTotalCols=nTotalCols-1;

	if (m_csHeader4=="")
		nTotalCols=nTotalCols-1;
	
	if (m_csHeader5=="")
		nTotalCols=nTotalCols-1;


	
	m_FGJobStatus.InitFlexGrid(1,1,4,nTotalCols);



	m_FGJobStatus.AddColumnHeaders("               ");
	if (m_csHeader1!="")
	{
		csBuffer=m_csHeader1;
		csBuffer.MakeUpper();
		if (csBuffer.Find("SUFFIX")==-1)
			if (m_csHeader1.GetLength()<11)
				m_FGJobStatus.AddColumnHeaders(CString("  ")+m_csHeader1+CString("  "));
			else
				m_FGJobStatus.AddColumnHeaders(m_csHeader1);
		else
			csSuffix1=m_csHeader1;
	}

	if (m_csHeader2!="")
	{
		csBuffer=m_csHeader2;
		csBuffer.MakeUpper();
		if (csBuffer.Find("SUFFIX")==-1)
			if (m_csHeader2.GetLength()<11)
				m_FGJobStatus.AddColumnHeaders(CString("  ")+m_csHeader2+CString("  "));
			else
				m_FGJobStatus.AddColumnHeaders(m_csHeader2);
		else
			csSuffix2=m_csHeader2;
	}
	if (m_csHeader3!="")
	{
		csBuffer=m_csHeader3;
		csBuffer.MakeUpper();
		if (csBuffer.Find("SUFFIX")==-1)
			if (m_csHeader3.GetLength()<11)
				m_FGJobStatus.AddColumnHeaders(CString("  ")+m_csHeader3+CString(" "));
			else
				m_FGJobStatus.AddColumnHeaders(m_csHeader3);
		else
			csSuffix3=m_csHeader3;
	}
	
	if (m_csHeader4!="")
	{
		csBuffer=m_csHeader4;
		csBuffer.MakeUpper();
		if (csBuffer.Find("SUFFIX")==-1)
			if (m_csHeader4.GetLength()<11)
				m_FGJobStatus.AddColumnHeaders(CString("  ")+m_csHeader4+CString("  "));
			else
				m_FGJobStatus.AddColumnHeaders(m_csHeader4);
		else
			csSuffix4=m_csHeader4;
	}
	
	if (m_csHeader5!="")
	{
		csBuffer=m_csHeader5;
		csBuffer.MakeUpper();
		if (csBuffer.Find("SUFFIX")==-1)
			if (m_csHeader5.GetLength()<11)
				m_FGJobStatus.AddColumnHeaders(CString("  ")+m_csHeader5+CString("  "));
			else
				m_FGJobStatus.AddColumnHeaders(m_csHeader5);
		else
			csSuffix5=m_csHeader5;
	}
	
	m_FGJobStatus.AddColumnHeaders("Serial Number");

	if (!csSuffix1.IsEmpty())
	{
		m_FGJobStatus.AddColumnHeaders("    Suffix  ");
	}

	if (!csSuffix2.IsEmpty())
	{
		m_FGJobStatus.AddColumnHeaders("    Suffix ");
	}

	if (!csSuffix3.IsEmpty())
	{
		m_FGJobStatus.AddColumnHeaders("    Suffix   ");
	}

	if (!csSuffix4.IsEmpty())
	{
		m_FGJobStatus.AddColumnHeaders("    Suffix   ");
	}
	
	if (!csSuffix5.IsEmpty())
	{
		m_FGJobStatus.AddColumnHeaders("    Suffix    ");
	}

	if(p_oSNManager->m_blnUseCheckDigit)
	{
		m_FGJobStatus.AddColumnHeaders(" CheckDigit ");

	}


	
	m_FGJobStatus.AddFixedRowHeaders("     ");
	m_FGJobStatus.AddFixedRowHeaders("Printed");
	m_FGJobStatus.AddFixedRowHeaders("Scanned");





}

void CRunDialog::GetColumnHeaders()
{
CJob *p_oJobInfo;

	p_oJobInfo = m_opLabeler->GetJob ();

	if (p_oJobInfo->GetPrintDataValue1())
	{
		m_csHeader1=p_oJobInfo->GetDataName1(); 
	}
	if (p_oJobInfo->GetPrintDataValue2())
	{
		m_csHeader2=p_oJobInfo->GetDataName2(); 
	}
	if (p_oJobInfo->GetPrintDataValue3())
	{
		m_csHeader3=p_oJobInfo->GetDataName3(); 
	}
	if (p_oJobInfo->GetPrintDataValue4())
	{
		m_csHeader4=p_oJobInfo->GetDataName4(); 
	}
	if (p_oJobInfo->GetPrintDataValue5())
	{
		m_csHeader5=p_oJobInfo->GetDataName5(); 
	}




}


CString  CRunDialog::ParseScannedLabel(CString csScannedLabel, CString csDeliminator)
{
int nStart,
	nCurrentLength,
	nStop,
	nSerialNumberLength,
	nScannedLength;

	CSNManager *p_oSNManager;


BOOL bSuffixFound;

CString csTemp;

CPrinterControl *p_oPrtr;    
	p_oPrtr=m_opLabeler->GetPrinterObject();
	p_oSNManager = m_opLabeler->GetSNManager();

	

	nStart=0;
	csTemp="";
	bSuffixFound=FALSE;
	nSerialNumberLength=0;

	nCurrentLength= p_oPrtr->GetPrintedSerialNumberPrefix1Width();
	if (nCurrentLength!=0)
	{
		m_csScanPrefix1=csScannedLabel.Mid(nStart,nCurrentLength);
		csTemp=m_csScanPrefix1;
		nStart+=nCurrentLength;
	}
	
	nCurrentLength= p_oPrtr->GetPrintedSerialNumberPrefix2Width();
	if (nCurrentLength!=0)
	{

		m_csScanPrefix2=csScannedLabel.Mid(nStart,nCurrentLength);

		if (csTemp.IsEmpty())
		{
			csTemp=m_csScanPrefix2;
		}
		else
		{
			csTemp=csTemp+csDeliminator+m_csScanPrefix2;
		}
		nStart+=nCurrentLength;
	}

	nCurrentLength= p_oPrtr->GetPrintedSerialNumberPrefix3Width();
	if (nCurrentLength!=0)
	{
		m_csScanPrefix3=csScannedLabel.Mid(nStart,nCurrentLength);
		if (csTemp.IsEmpty())
		{
			csTemp=m_csScanPrefix3;
		}
		else
		{
			csTemp=csTemp+csDeliminator+m_csScanPrefix3;
		}
		nStart+=nCurrentLength;
	}

	nCurrentLength= p_oPrtr->GetPrintedSerialNumberPrefix4Width();
	if (nCurrentLength!=0)
	{
		m_csScanPrefix4=csScannedLabel.Mid(nStart,nCurrentLength);
		if (csTemp.IsEmpty())
		{
			csTemp=m_csScanPrefix4;
		}
		else
		{
			csTemp=csTemp+csDeliminator+m_csScanPrefix4;
		}
		nStart+=nCurrentLength;
	}

	nCurrentLength= p_oPrtr->GetPrintedSerialNumberPrefix5Width();
	if (nCurrentLength!=0)
	{

		m_csScanPrefix5=csScannedLabel.Mid(nStart,nCurrentLength);

		if (csTemp.IsEmpty())
		{
			csTemp=m_csScanPrefix5;
		}
		else
		{
			csTemp=csTemp+csDeliminator+m_csScanPrefix5;
		}
		nStart+=nCurrentLength;

	}

	nCurrentLength= p_oPrtr->GetSuffixStrLength();
	if (nCurrentLength!=0)
	{
		nStop=nCurrentLength;
		bSuffixFound=TRUE;
	}

	nSerialNumberLength=p_oPrtr->GetPrintedSerialNumber().GetLength();

	if (!csTemp.IsEmpty())	
	{
		if(!bSuffixFound)
		{
			if (p_oSNManager->m_blnUseCheckDigit)
			{
				nScannedLength=csScannedLabel.GetLength();
				csTemp=csTemp+csDeliminator+csScannedLabel.Mid(nStart,nSerialNumberLength)
				             +csDeliminator+csScannedLabel.Mid(nStart+nSerialNumberLength,1);

			}
			else
			{	// no suffixes , no checkdigits
				csTemp=csTemp+csDeliminator+csScannedLabel.Mid(nStart);
			}
		}
		else
		{
			
//			nSerialNumberLength=csScannedLabel.GetLength()-
//									(nStart+nStop);



			if (p_oSNManager->m_blnUseCheckDigit)
			{
				nScannedLength=csScannedLabel.GetLength();
				csTemp=csTemp+csDeliminator+csScannedLabel.Mid(nStart,nSerialNumberLength)
				             +csDeliminator
							 +csScannedLabel.Mid(nStart+nSerialNumberLength,nStop)
							 +csDeliminator
							 +csScannedLabel.Mid(nStart+nSerialNumberLength+nStop,1);

			}
			else
			{
				csTemp=csTemp+csDeliminator
					   +csScannedLabel.Mid(nStart,nSerialNumberLength)
					   +csDeliminator
					   +csScannedLabel.Mid(nStart+nSerialNumberLength);
			}


		
		}
	}
	else  // prefixes
	{
		if(!bSuffixFound)
		{
		
			
			if (p_oSNManager->m_blnUseCheckDigit)
			{
			
			   csTemp=csScannedLabel.Mid(nStart,nSerialNumberLength)
					  +csDeliminator+
					  csScannedLabel.Mid(nStart+nSerialNumberLength,1);
			}
			else
				csTemp=csScannedLabel;

		}
		else
		{
			

			if (p_oSNManager->m_blnUseCheckDigit)
			{
			
			   csTemp=csScannedLabel.Mid(nStart,nSerialNumberLength)
					  +csDeliminator
					  +csScannedLabel.Mid(nStart+nSerialNumberLength,nStop)
					  +csDeliminator
					  +csScannedLabel.Mid(nStart+nSerialNumberLength+nStop,1);
			}
			else
			{
			   csTemp=csScannedLabel.Mid(nStart,nSerialNumberLength-1)
					  +csDeliminator
					  +csScannedLabel.Mid(nStart+nSerialNumberLength);
			}

		}


	}

	return csTemp;
}

void CRunDialog::InitJobStats()
{

	m_FGJobStats.InitFlexGrid(1,1,5,3);


    GetColumnHeaders();	
	
	m_FGJobStats.AddColumnHeaders("             ");
	m_FGJobStats.AddColumnHeaders("Current (secs.)");
	
	m_FGJobStats.AddColumnHeaders("Ave (secs.)");



	m_FGJobStats.AddFixedRowHeaders("           ");
	m_FGJobStats.AddFixedRowHeaders("Label To Label Cycle Time");
	m_FGJobStats.AddFixedRowHeaders("Board To Board Cycle Time");
	m_FGJobStats.AddFixedRowHeaders("Scanner Performance   ");




}

void CRunDialog::UpdateJobStats()
{

CString csTemp1,
		csTemp2,
		csTemp;

	
	// Label to Label Statistics
	csTemp1.Format("%.2f",m_opLabeler->m_fLabeltoLabelCycleTime);
	csTemp2.Format("%.2f",m_opLabeler->m_fAveLabeltoLabelCycleTime);

	csTemp=csTemp1 + "\t" + csTemp2;

	m_FGJobStats.UpdateRow(1,csTemp);


	// Board to Board Statistics
	csTemp1.Format("%.2f",m_opLabeler->m_fBoardtoBoardCycleTime);
	csTemp2.Format("%.2f",m_opLabeler->m_fAveBoardtoBoardCycleTime);

	csTemp=csTemp1 + "\t" + csTemp2;

	m_FGJobStats.UpdateRow(2,csTemp);

	//Scanner Stats
	csTemp=m_opLabeler->GetScannerPerformance()+ "\t" +
		   m_opLabeler->GetAveScannerPerformance(); 
	m_FGJobStats.UpdateRow(3,csTemp);

}

void CRunDialog::OnClickCmdRelabel() 
{
	CJob *p_oJobInfo;
	p_oJobInfo = m_opLabeler->GetJob ();
	
	UpdateData(TRUE);
	UpdateData(FALSE);
	int nRelabelCount;
	for(nRelabelCount = 0; nRelabelCount < m_nRelabelCount; nRelabelCount++)
	{
		m_poSNManager->DecrementSerialNumber(p_oJobInfo->GetJobName());
	}
//	UpdateForm();

}

void CRunDialog::OnClickCmdExit() 
{
	
	m_opLabeler->ExitRunCleanup();
	m_blnExitRunMode=TRUE;
	
}
