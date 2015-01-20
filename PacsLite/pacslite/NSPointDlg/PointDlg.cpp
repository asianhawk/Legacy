// PointDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PointDlg.h"
#include "Utilities.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPointDlg dialog


CPointDlg::CPointDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPointDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPointDlg)
	//}}AFX_DATA_INIT

	m_bManualEdit = TRUE;

}


void CPointDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPointDlg)
	DDX_Control(pDX, IDC_ENABLE_SCAN, m_chkEnableScan);
	DDX_Control(pDX, IDC_PRINTER_SELECTION, m_cmbPrinterSelection);
	DDX_Control(pDX, IDC_TEMPLATE_LIST, m_cmbTemplates);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPointDlg, CDialog)
	//{{AFX_MSG_MAP(CPointDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPointDlg message handlers

BEGIN_EVENTSINK_MAP(CPointDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CPointDlg)
	ON_EVENT(CPointDlg, IDC_OK, -600 /* Click */, OnClickOk, VTS_NONE)
	ON_EVENT(CPointDlg, IDC_CANCEL, -600 /* Click */, OnClickCancel, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()



BOOL CPointDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int
		nCurrentSel,
		nListIndex,
		nIndex;
	
	CString
		csName,
		csPoints,
		csTemp,
		csX,
		csY,
		csRot,
		csTemplateName,
		csPrinter,
		csEnableScan,
		csPrinterList;

	// Start with the full attribute string
	csTemp = m_csPlacementAttribute;

	// get the template used for this point
	nIndex = csTemp.Find(",");
	// if an error
	if ( nIndex == -1 )
	{
		csTemp.LoadString ( IDS_INVALID_LABEL_ATT );
		AfxMessageBox (csTemp);
		return(FALSE);
	}
	// extract the template name for this label, will select it
	// in the combobox of template names later
	csTemplateName = csTemp.Left(nIndex);
	// discard the left portion of the string
	csTemp = csTemp.Right(csTemp.GetLength()-nIndex-1);

	// save the printer
	nIndex = csTemp.Find(",");
	// if an error
	if ( nIndex == -1 )
	{
		csTemp.LoadString ( IDS_INVALID_LABEL_ATT );
		AfxMessageBox (csTemp);
		return(FALSE);
	}
	// extract printer, will select it in combobox list later
	csPrinter = csTemp.Left(nIndex);
	// discard the left portion of the string
	csTemp = csTemp.Right(csTemp.GetLength()-nIndex-1);

	
	// save the scanner enable flag
	nIndex = csTemp.Find(";");
	if ( nIndex == -1 )
	{
		csTemp.LoadString ( IDS_INVALID_LABEL_ATT );
		AfxMessageBox (csTemp);
		return(FALSE);
	}
	csEnableScan = csTemp.Left(nIndex);
	if ( csEnableScan.CompareNoCase ("YES") == 0 )
		m_chkEnableScan.SetCheck ( TRUE );
	else
		m_chkEnableScan.SetCheck ( FALSE );

	// retrieve all templates, put them in combobox as selections
	m_poDatabase->GetTemplateList(&csTemp);
    // ";" is the separator of the template names.	
	nIndex = csTemp.Find ( ";" );
	// initialize variable to record current point template's position
	// in the combobox so we can select the current template
	nListIndex = 0;
	while ( nIndex != -1 )
	{
		// Get name.
		csName = csTemp.Left ( nIndex );

		// Save index into list if it is this point's template.
		if (csName==csTemplateName)
			nCurrentSel = nListIndex;
	 
		// add the template name to the combobox
		m_cmbTemplates.AddString ( csName );

		// Increment the index into the combobox
		nListIndex++;
		
		// Get next name.
		csTemp = csTemp.Right ( csTemp.GetLength() - nIndex - 1 );
		nIndex = csTemp.Find ( ";" );
	}
	// select this label's template in the list
	m_cmbTemplates.SetCurSel ( nCurrentSel );

	// retrieve all printers, put them in printer combobox
	m_poDatabase->GetUsablePrinterList(&csPrinterList);
	// printers in list are seperated by ;
	nIndex = csPrinterList.Find ( ";" );
	// initialize variable to record current point template's position
	// in the combobox so we can select the current template
	nListIndex = 0;
	while ( nIndex != -1 )
	{
		// Get name.
		csName = csPrinterList.Left ( nIndex );

		// Save index into list if it is this point's template.
		if (csName==csPrinter)
			nCurrentSel = nListIndex;
	 
		// add the template name to the combobox
		m_cmbPrinterSelection.AddString ( csName );

		// Increment the index into the combobox
		nListIndex++;
		
		// Get next name.
		csPrinterList = csPrinterList.Right ( csPrinterList.GetLength() - nIndex - 1 );
		nIndex = csPrinterList.Find ( ";" );
	}
	// select this label's template in the list
	m_cmbPrinterSelection.SetCurSel ( nCurrentSel );


	// Ensure if using WYSIWYG that some controls are not accessed.

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CPointDlg::OnClickOk() 
{

	CString csEnableScan;
	CString csRot;
	CString csPrinter;
	CString csTemplate;

	CUtilities Utility;

	// get the x and y points from the controls

	// check label format


	// get selected template
	m_cmbTemplates.GetLBText(m_cmbTemplates.GetCurSel(),csTemplate);

	// get selected printer
	m_cmbPrinterSelection.GetLBText(m_cmbPrinterSelection.GetCurSel(),csPrinter);

	if (!TemplateMatchesPrinter(csTemplate,csPrinter))
	{
		AfxMessageBox ( "The template you have chosen does not match the printer you have chosen, please change one or both." );
		return;
	}


	// get scanner enabled value
	if ( m_chkEnableScan.GetCheck() )
		csEnableScan = "YES";
	else
		csEnableScan = "NO";


	// Build attribute string.
	// Each label placement substring contains the following attributes:
	//		X, Y, Rotation, Template Name, Printer Location, Enable Scanner;

	m_csPlacementAttribute = csTemplate;
	m_csPlacementAttribute += ",";
	m_csPlacementAttribute += csPrinter;
	m_csPlacementAttribute += ",";
	m_csPlacementAttribute += csEnableScan;
	m_csPlacementAttribute += ";";

	CDialog::OnOK();
}



void CPointDlg::OnClickCancel() 
{
	// base class cancel
	CDialog::OnCancel();
}

BOOL CPointDlg::TemplateMatchesPrinter(CString csTemplateName, CString csPrinterName)
{
	int			nType;
	char		cTemp;
	BOOL		bUse,bEnable,bReturnValue;
	CString		csTemplate,csPrePick,csPick,csSearch1,csSearch2;

	// get printer type
	m_poDatabase->GetPrinterAttributes(csPrinterName,&bUse,&bEnable,&nType);

	// switch on printer type
	switch (nType)
	{
		case  	ZEBRA:
			// search for beginning of format command
			csSearch1 = "^XA";
			cTemp = '\x002';
			csSearch2 = cTemp;
			break;
		case	INTERMEC:
			// search for the print command
			csSearch1 = "<STX><ETB><ETX>";
			cTemp = '\x002';
			csSearch2 = cTemp;
			cTemp = '\x017';
			csSearch2 = csSearch2 + cTemp;
			cTemp = '\x003';
			csSearch2 = csSearch2 + cTemp;
			break;
		case	DATAMAX:
			// search for label formatting command
			csSearch1 = "STX L";
			cTemp = '\x002';
			csSearch2 = cTemp;
			csSearch2 = csSearch2 + "L";
			break;
	}
	
	// get template from template name
	m_poDatabase->GetTemplate(csTemplateName,&csTemplate);
	
	// if we can't find either of the search strings
	if ((csTemplate.Find(csSearch1)==-1)&&(csTemplate.Find(csSearch2)==-1))
		bReturnValue = FALSE;
	else
		bReturnValue = TRUE;

	return (bReturnValue);
}
