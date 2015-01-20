//{{AFX_INCLUDES()
#include "mdcoptionbutton.h"
#include "commandbutton.h"
//}}AFX_INCLUDES
#if !defined(AFX_DBPANELLABELDLG_H__BC348962_C180_11D2_B805_9EBB88208F38__INCLUDED_)
#define AFX_DBPANELLABELDLG_H__BC348962_C180_11D2_B805_9EBB88208F38__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DBPanelLabelDlg.h : header file
//

#include "Database.h"
#include "Job.h"	// Added by ClassView

#include "definitions.h"
#include "NSPanelLabelResource.h"



/////////////////////////////////////////////////////////////////////////////
// CDBPanelLabelDlg dialog

class AFX_MFC_EXT_TYPE CDBPanelLabelDlg : public CDialog
{
// Construction
public:
	CDBPanelLabelDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDBPanelLabelDlg)
	enum { IDD = IDD_DB_PANEL_LABEL_DLG };
	CListBox	m_lstLabelPositions;
	CCommandButton	m_btnEditPoint;
	CCommandButton	m_btnAddPoint;
	CCommandButton  m_btnDeletePoint;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBPanelLabelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDBPanelLabelDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickOk();
	afx_msg void OnClickCancel();
	afx_msg void OnClickPointEdit();
	afx_msg void PointAdd();
	afx_msg void PointDelete();
	afx_msg void OnSelChangeLabelPositions();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL		m_bTemplateUpdated;

	BOOL GetJobInfo (); 

public:
	CJob		*m_poJob;			// Job object built from job name
	CDatabase	*m_poDatabase;		// Pointer to database object.
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBPANELLABELDLG_H__BC348962_C180_11D2_B805_9EBB88208F38__INCLUDED_)
