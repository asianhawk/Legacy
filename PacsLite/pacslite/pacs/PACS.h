// PACS.h : main header file for the PACS application
//

#if !defined(AFX_PACS_H__AD710749_9E4A_11D2_A2AB_006008043EC4__INCLUDED_)
#define AFX_PACS_H__AD710749_9E4A_11D2_A2AB_006008043EC4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "Statistics.h"
#include "trace.h"



extern CStatistics g_oStatistics;
extern void KeypadMin();
extern void KeypadMax();




/////////////////////////////////////////////////////////////////////////////
// CPACSApp:
// See PACS.cpp for the implementation of this class
//

class CPACSApp : public CWinApp
{
public:
	CPACSApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPACSApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPACSApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PACS_H__AD710749_9E4A_11D2_A2AB_006008043EC4__INCLUDED_)
