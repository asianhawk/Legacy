// ManualFeed.cpp: implementation of the CManualFeed class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "pacs.h"
#include "ManualFeed.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CManualFeed::CManualFeed(CApplicatorControl *poApplicator,
						 CString csCurrentJob)
{
	m_poApplicator=poApplicator;
	m_csCurrentJob=csCurrentJob;
}

CManualFeed::~CManualFeed()
{

}

void CManualFeed::MFeed () 
{
	CJob *poJobInfo;
	CLabel *poLabel;
	int	nLabel;

	// get an instance of the selected job
	poJobInfo = m_poApplicator->SetupJob ( m_csCurrentJob );

	// declare the dialog box
	CDBLabelSelectionDlg LabelSelection;
	
	// pass the job pointer to the dialog box
	LabelSelection.m_poJob = poJobInfo;

	// if the user didn't cancel
	if ( LabelSelection.DoModal() == IDOK )
	{
		// retrieve the ordinal number of the labels selected
		nLabel  = LabelSelection.m_nLabel;

		// get the first label from the number
		poLabel  = poJobInfo->GetLabel (nLabel);
	}
	else
		return;

	// execute a manual feed
	m_poApplicator->ManualFeed (poLabel,NULL);

}

