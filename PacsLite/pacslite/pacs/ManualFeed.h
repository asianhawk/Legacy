// ManualFeed.h: interface for the CManualFeed class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MANUALFEED_H__5DEA51C4_06E2_11D4_B1D5_000000000093__INCLUDED_)
#define AFX_MANUALFEED_H__5DEA51C4_06E2_11D4_B1D5_000000000093__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ApplicatorControl.h"
#include "Job.h"
#include "DBLabelSelectionDlg.h"

class CManualFeed  
{
public:
	CManualFeed(CApplicatorControl *poApplicator,
				CString csCurrentJob);

	virtual ~CManualFeed();
	CApplicatorControl *m_poApplicator;
	void MFeed(); 
	CString m_csCurrentJob;
};

#endif // !defined(AFX_MANUALFEED_H__5DEA51C4_06E2_11D4_B1D5_000000000093__INCLUDED_)
