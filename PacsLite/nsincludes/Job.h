// Job.h: interface for the CJob class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JOB_H__42DB6A62_B06F_11D2_A68A_641A11C1FB5F__INCLUDED_)
#define AFX_JOB_H__42DB6A62_B06F_11D2_A68A_641A11C1FB5F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


//#include "resource.h"
#include "definitions.h"





class AFX_MFC_EXT_TYPE CLabel : public CObject 
{
public:
	CLabel();
	virtual ~CLabel();

public:
	long	GetXCoord ();
	void	SetXCoord ( long lXCoord );
	long	GetYCoord ();
	void	SetYCoord ( long lYCoord );
	int	GetRotation ();
	void	SetRotation ( int nRotation );
	int	GetPrinterLocation ();
	void	SetPrinterLocation ( int nLocation );
	CString GetTemplate ();
	void	SetTemplate ( CString csTemplate );
	CString GetTemplateName ();
	void	SetTemplateName ( CString csTemplateName );
	BOOL	GetEnableScan ();
	void	SetEnableScan ( BOOL bEnable );
	CString GetPrinterName ();
	void	SetPrinterName(CString csPrinterName);

private:
	long	m_lXCoord;					// X label placement coordinate.
	long	m_lYCoord;					// Y label placement coordinate.
	int	m_nRotation;				// Label rotation. 0 or 90.

	BOOL	m_bEnableScan;				// Scan this label.
	int	m_nPrinterLocation;		// Printer to print label from.

	CString m_csTemplate;			// Label template for printer.
	CString m_csTemplateName;		// Label template name for printer.
	CString m_csPrinterName;
};




class AFX_MFC_EXT_TYPE CJob  
{
public:
	CJob();
	virtual ~CJob();

public:
	void SetUseStaticDateCode ( BOOL bUseStaticDateCode);
	BOOL GetUseStaticDateCode();
	void SetStaticDateCode ( CString csDateCode );
	CString GetStaticDateCode();
	CString GetRelease();
	void SetRelease(CString csRelease);
	CString GetProductCode();
	void SetProductCode(CString csProductCode);
	CString GetManufacturingSite();
	void SetManufacturingSite(CString csManufacturingSite);
	CString GetCountry();
	void SetCountry(CString csCountry);
	void SetJob2up(BOOL b2up);
	BOOL GetJob2up();
	int GetLabelStockYOffset();
	int GetLabelStockXOffset();
	void SetLabelStockYOffset(int nOffset);
	void SetLabelStockXOffset(int nOffset);
	int GetYOffset();
	int GetXOffset();
	void SetYOffset(int nYOffset);
	void SetXOffset(int nXOffset);
	void SetJobName ( CString csJobName );
	CString GetJobName();
	void SetPoints ( CString csPoint );
	CString GetPoints();
	void SetDescription ( CString csDescription );
	CString GetDescription();
	void SetLabelCount ( long lLabelCount );
	long GetLabelCount();
	void SetPanelCount ( long lPanelCount );
	long GetPanelCount();
	void SetPanelDimension ( CString csPanelDimension );
	CString GetPanelDimension();
	BOOL SetPrinterLabelStatus ( int nPrinter, CString csStatus ); 
	CString GetPrinterLabelStatus ( int nPrinter ); 
	void SetPlacementAttributes ( CString csPlacementAttributes );
	CString GetPlacementAttributes();
	void SetUseWYSIWYG ( BOOL bUseWYSIWYG );
	BOOL GetUseWYSIWYG();
	int GetNumberOfLabels ( void );
	CLabel* GetFirstLabel ( void );
	CLabel* GetNextLabel ( void );
	CLabel* GetLabel ( int nIndex );
	CString GetPrinterLocationString ( int nLocation );
	int GetPrinterLocationID ( CString csLocation );


	CString GetCustomer();
	void SetCustomer ( CString csCustomer );
	
	
	CString GetDataName1();
	CString GetDataName2();
	CString GetDataName3();
	CString GetDataName4();
	CString GetDataName5();
	void SetDataName1 ( CString csDataName );
	void SetDataName2 ( CString csDataName );
	void SetDataName3 ( CString csDataName );
	void SetDataName4 ( CString csDataName );
	void SetDataName5 ( CString csDataName );
	CString GetDataValue1();
	CString GetDataValue2();
	CString GetDataValue3();
	CString GetDataValue4();
	CString GetDataValue5();
	void SetDataValue1 ( CString csDataValue );
	void SetDataValue2 ( CString csDataValue );
	void SetDataValue3 ( CString csDataValue );
	void SetDataValue4 ( CString csDataValue );
	void SetDataValue5 ( CString csDataValue );
	BOOL GetLogDataValue1();
	BOOL GetLogDataValue2();
	BOOL GetLogDataValue3();
	BOOL GetLogDataValue4();
	BOOL GetLogDataValue5();
	void SetLogDataValue1 ( BOOL bLog );
	void SetLogDataValue2 ( BOOL bLog );
	void SetLogDataValue3 ( BOOL bLog );
	void SetLogDataValue4 ( BOOL bLog );
	void SetLogDataValue5 ( BOOL bLog );
	BOOL GetPrintDataValue1();
	BOOL GetPrintDataValue2();
	BOOL GetPrintDataValue3();
	BOOL GetPrintDataValue4();
	BOOL GetPrintDataValue5();
	void SetPrintDataValue1 ( BOOL bPrint );
	void SetPrintDataValue2 ( BOOL bPrint );
	void SetPrintDataValue3 ( BOOL bPrint );
	void SetPrintDataValue4 ( BOOL bPrint );
	void SetPrintDataValue5 ( BOOL bPrint );
	BOOL GetUseDataName1();
	BOOL GetUseDataName2();
	BOOL GetUseDataName3();
	BOOL GetUseDataName4();
	BOOL GetUseDataName5();
	void SetUseDataName1 ( BOOL bUse );
	void SetUseDataName2 ( BOOL bUse );
	void SetUseDataName3 ( BOOL bUse );
	void SetUseDataName4 ( BOOL bUse );
	void SetUseDataName5 ( BOOL bUse );
	BOOL GetTemplate(CString csTemplateName, CString *csTemplate);

private:
	BOOL m_bUseStaticDateCode;
	CString m_csStaticDateCode;
	CString m_csRelease;
	CString m_csCountry;
	CString m_csManufacturingSite;
	CString m_csProductCode;
	CString m_csCustomer;
	BOOL m_bJob2up;
	int m_nLabelStockYOffset;
	int m_nLabelStockXOffset;
	int m_nYOffset;
	int m_nXOffset;
	CString m_csJobName;
	CString m_csPointList;
	CString m_csPrinterLabelStatus;
	CString m_csDescription;
	long m_lLabelCount;
	long m_lPanelCount;
	CString m_csPanelDimension;
	CString m_csFrontPrinterStatus;
	CString m_csBackUSPrinterStatus;
	CString m_csBackDSPrinterStatus;
	BOOL	m_bUseWYSIWYG;
	CObList m_LabelList;
	POSITION m_LabelPos;


	CString	m_csDataName1;					// User specified data fields.
	CString	m_csDataName2;
	CString	m_csDataName3;
	CString	m_csDataName4;
	CString	m_csDataName5;
	CString	m_csDataValue1;					
	CString	m_csDataValue2;
	CString	m_csDataValue3;
	CString	m_csDataValue4;
	CString	m_csDataValue5;
	BOOL		m_bUseDataName1;
	BOOL		m_bUseDataName2;
	BOOL		m_bUseDataName3;
	BOOL		m_bUseDataName4;
	BOOL		m_bUseDataName5;
	BOOL		m_bLogDataValue1;	
	BOOL		m_bLogDataValue2;	
	BOOL		m_bLogDataValue3;	
	BOOL		m_bLogDataValue4;	
	BOOL		m_bLogDataValue5;	
	BOOL		m_bPrintDataValue1;	
	BOOL		m_bPrintDataValue2;	
	BOOL		m_bPrintDataValue3;	
	BOOL		m_bPrintDataValue4;	
	BOOL		m_bPrintDataValue5;	



};

#endif // !defined(AFX_JOB_H__42DB6A62_B06F_11D2_A68A_641A11C1FB5F__INCLUDED_)
