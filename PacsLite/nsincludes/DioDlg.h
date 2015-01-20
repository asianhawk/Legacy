//{{AFX_INCLUDES()
#include "commandbutton.h"
//}}AFX_INCLUDES
#if !defined(AFX_DIODLG_H__EA028E44_E35F_11D2_B806_9EBB88208F38__INCLUDED_)
#define AFX_DIODLG_H__EA028E44_E35F_11D2_B806_9EBB88208F38__INCLUDED_

// custom message
#define WM_DIODLGTHREADMESSAGE	WM_USER + 50

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DioDlg.h : header file
//

#include "definitions.h"



// prototype thread function
UINT AFX_MFC_EXT_TYPE DioThreadFunction (LPVOID);
#include "resource.h"
#include "Database.h"
#include "Utilities.h"

#include "NSDIOMain.h"





/////////////////////////////////////////////////////////////////////////////
// CDioDlg dialog



class AFX_MFC_EXT_TYPE CDioDlg : public CDialog
{
// Construction
public:
	CDioDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDioDlg)
	enum { IDD = IDD_DIO_DIAGNOSTICS };
	CButton	m_output9;
	CButton	m_output8;
	CButton	m_output7;
	CButton	m_output6;
	CButton	m_output5;
	CButton	m_output4;
	CButton	m_output31;
	CButton	m_output30;
	CButton	m_output3;
	CButton	m_output29;
	CButton	m_output28;
	CButton	m_output26;
	CButton	m_output27;
	CButton	m_output25;
	CButton	m_output24;
	CButton	m_output23;
	CButton	m_output22;
	CButton	m_output21;
	CButton	m_output20;
	CButton	m_output2;
	CButton	m_output19;
	CButton	m_output18;
	CButton	m_output17;
	CButton	m_output16;
	CButton	m_output15;
	CButton	m_output14;
	CButton	m_output13;
	CButton	m_output12;
	CButton	m_output11;
	CButton	m_output10;
	CButton	m_output0;
	CButton	m_output1;
	CString	m_inputAddress;
	CString	m_outputAddress;
	CCommandButton	m_input0;
	CCommandButton	m_input1;
	CCommandButton	m_input10;
	CCommandButton	m_input11;
	CCommandButton	m_input12;
	CCommandButton	m_input13;
	CCommandButton	m_input14;
	CCommandButton	m_input15;
	CCommandButton	m_input16;
	CCommandButton	m_input17;
	CCommandButton	m_input18;
	CCommandButton	m_input19;
	CCommandButton	m_input2;
	CCommandButton	m_input20;
	CCommandButton	m_input21;
	CCommandButton	m_input22;
	CCommandButton	m_input23;
	CCommandButton	m_input24;
	CCommandButton	m_input25;
	CCommandButton	m_input26;
	CCommandButton	m_input27;
	CCommandButton	m_input28;
	CCommandButton	m_input29;
	CCommandButton	m_input3;
	CCommandButton	m_input30;
	CCommandButton	m_input31;
	CCommandButton	m_input4;
	CCommandButton	m_input5;
	CCommandButton	m_input6;
	CCommandButton	m_input7;
	CCommandButton	m_input8;
	CCommandButton	m_input9;
	CString	m_csInputBit_10;
	CString	m_csInputBit_11;
	CString	m_csInputBit_12;
	CString	m_csInputBit_13;
	CString	m_csInputBit_14;
	CString	m_csInputBit_15;
	CString	m_csInputBit_16;
	CString	m_csInputBit_17;
	CString	m_csInputBit_18;
	CString	m_csInputBit_19;
	CString	m_csInputBit_00;
	CString	m_csInputBit_01;
	CString	m_csInputBit_02;
	CString	m_csInputBit_20;
	CString	m_csInputBit_21;
	CString	m_csInputBit_22;
	CString	m_csInputBit_23;
	CString	m_csInputBit_24;
	CString	m_csInputBit_25;
	CString	m_csInputBit_26;
	CString	m_csInputBit_27;
	CString	m_csInputBit_28;
	CString	m_csInputBit_29;
	CString	m_csInputBit_30;
	CString	m_csInputBit_31;
	CString	m_csInputBit_03;
	CString	m_csInputBit_04;
	CString	m_csInputBit_05;
	CString	m_csInputBit_06;
	CString	m_csInputBit_07;
	CString	m_csInputBit_08;
	CString	m_csInputBit_09;
	CString	m_csOutputBit_00;
	CString	m_csOutputBit_01;
	CString	m_csOutputBit_10;
	CString	m_csOutputBit_11;
	CString	m_csOutputBit_12;
	CString	m_csOutputBit_13;
	CString	m_csOutputBit_14;
	CString	m_csOutputBit_15;
	CString	m_csOutputBit_16;
	CString	m_csOutputBit_17;
	CString	m_csOutputBit_18;
	CString	m_csOutputBit_19;
	CString	m_csOutputBit_02;
	CString	m_csOutputBit_20;
	CString	m_csOutputBit_21;
	CString	m_csOutputBit_22;
	CString	m_csOutputBit_23;
	CString	m_csOutputBit_24;
	CString	m_csOutputBit_25;
	CString	m_csOutputBit_26;
	CString	m_csOutputBit_27;
	CString	m_csOutputBit_28;
	CString	m_csOutputBit_29;
	CString	m_csOutputBit_03;
	CString	m_csOutputBit_30;
	CString	m_csOutputBit_31;
	CString	m_csOutputBit_04;
	CString	m_csOutputBit_05;
	CString	m_csOutputBit_06;
	CString	m_csOutputBit_07;
	CString	m_csOutputBit_08;
	CString	m_csOutputBit_09;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDioDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDioDlg)
	afx_msg void OnClickCloseDioDiagnostics();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheck0();
	afx_msg void OnCheck1();
	afx_msg void OnCheck10();
	afx_msg void OnCheck11();
	afx_msg void OnCheck12();
	afx_msg void OnCheck13();
	afx_msg void OnCheck14();
	afx_msg void OnCheck15();
	afx_msg void OnCheck16();
	afx_msg void OnCheck17();
	afx_msg void OnCheck18();
	afx_msg void OnCheck19();
	afx_msg void OnCheck2();
	afx_msg void OnCheck20();
	afx_msg void OnCheck21();
	afx_msg void OnCheck22();
	afx_msg void OnCheck23();
	afx_msg void OnCheck24();
	afx_msg void OnCheck25();
	afx_msg void OnCheck26();
	afx_msg void OnCheck27();
	afx_msg void OnCheck28();
	afx_msg void OnCheck29();
	afx_msg void OnCheck3();
	afx_msg void OnCheck30();
	afx_msg void OnCheck31();
	afx_msg void OnCheck4();
	afx_msg void OnCheck5();
	afx_msg void OnCheck6();
	afx_msg void OnCheck7();
	afx_msg void OnCheck8();
	afx_msg void OnCheck9();
	afx_msg void OnClickSetInputAddress();
	afx_msg void OnClickSetOutputAddress();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg	void OnThreadMessage(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	CDIODriver	*m_oDioInput;
	CDIODriver	*m_oDioOutput;
	void InitInputBitDescription();
	void InitOutputBitDescription();
private:
	CWinThread *m_myThread;
	void SetSingleBit(BOOL bState, int nPosition);
	void SetInputDisplay(unsigned long bitField);
	void setOutputBits();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIODLG_H__EA028E44_E35F_11D2_B806_9EBB88208F38__INCLUDED_)
