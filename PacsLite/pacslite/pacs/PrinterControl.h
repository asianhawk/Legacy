// PrinterControl.h: interface for the CPrinterControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINTERCONTROL_H__BCF778C6_9EE5_11D2_A2AB_006008043EC4__INCLUDED_)
#define AFX_PRINTERCONTROL_H__BCF778C6_9EE5_11D2_A2AB_006008043EC4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "Printer.h"
#include "Database.h"
#include "SNManager.h"

class CPrinterControl  
{
public:
	CString m_csErrorString;
	void FormFeed();
	void SetDefaults();
	CString GetStatusString();
	CPrinterControl();
	virtual ~CPrinterControl();


	BOOL Initialize ( CDatabase *poDatabase, CSNManager *poSNManager );
	BOOL PrintLabel ( int nStatus, BOOL bRunMode, CJob *poJob, CString csTemplate, int nFirstLabel );
	BOOL GetPrinterTemplate ( CString *csTemplate );
	BOOL UpdatePrinterAttributes ( CDatabase *poDatabase );
	void SetUse ( BOOL bUse);
	void SetType ( int nType);
	void SetEnable ( BOOL bEnable);
	BOOL GetUse ();
	int GetType ();
	BOOL GetEnable () ;
	BOOL GetStatus ();
	CString GetPrintedLabel ();
	BOOL	m_bInitialized;
	CString GetPrefix1();
	CString GetPrefix2();
	CString GetPrefix3();
	CString GetPrefix4();
	CString GetPrefix5();

	CString GetPrefixes(CString csDelimiter);
	
	CString GetPrintedSerialNumber();
	void SetPrintedSerialNumber(CString csSerialNumber);

	int GetPrintedSerialNumberPrefix1Width();
	int GetPrintedSerialNumberPrefix2Width();
	int GetPrintedSerialNumberPrefix3Width();
	int GetPrintedSerialNumberPrefix4Width();
	int GetPrintedSerialNumberPrefix5Width();


	void ResetPrinter();
	void ReSyncSerialNumber(CJob *poJob);

	int GetSuffixStrLength();
	CString GetSuffix();
	CString GetCheckDigitValue();

private:
	CString m_csTemplate;

	CSNManager * m_poSNManager;
	CPrinter m_oPrinter;
	CString m_csCheckDigit;
};

#endif // !defined(AFX_PRINTERCONTROL_H__BCF778C6_9EE5_11D2_A2AB_006008043EC4__INCLUDED_)
