#if !defined(AFX_PLACEMENTSCHEMADLG_H__8715AB6C_6798_11D4_9025_00105A170700__INCLUDED_)
#define AFX_PLACEMENTSCHEMADLG_H__8715AB6C_6798_11D4_9025_00105A170700__INCLUDED_

#include "3Dpoint.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlacementSchemaDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlacementSchemaDlg dialog

class CPlacementSchemaDlg : public CDialog
{
// Construction
public:
	C3Dpoint m_oB4;
	C3Dpoint m_oB3;
	C3Dpoint m_oB2;
	C3Dpoint m_oB1;
	C3Dpoint m_oA4;
	C3Dpoint m_oA3;
	C3Dpoint m_oA2;
	C3Dpoint m_oA1;
	C3Dpoint m_oA2marker1;
	C3Dpoint m_oA2marker2;

	C3Dpoint m_oLabelB4;
	C3Dpoint m_oLabelB3;
	C3Dpoint m_oLabelB2;
	C3Dpoint m_oLabelB1;

	C3Dpoint m_oLabelA4;
	C3Dpoint m_oLabelA3;
	C3Dpoint m_oLabelA2;
	C3Dpoint m_oLabelA1;

	CString m_csText;
	int	m_nFrontDown;
	int	m_nFrontAcross;
	int	m_nSideAcross;
	int	m_nSideWidth;


	CPlacementSchemaDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPlacementSchemaDlg)
	enum { IDD = IDD_PLACEMENT_SCHEMATIC };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlacementSchemaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlacementSchemaDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLACEMENTSCHEMADLG_H__8715AB6C_6798_11D4_9025_00105A170700__INCLUDED_)
