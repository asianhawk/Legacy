// Printer.h: interface for the CPrinter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINTER_H__9FBC34C2_B174_11D2_A68A_641A11C1FB5F__INCLUDED_)
#define AFX_PRINTER_H__9FBC34C2_B174_11D2_A68A_641A11C1FB5F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "comPort.h"
#include "Database.h"
#include "SNManager.h"

const CString csZebraStatusReq = "~HS";			// Request the Zebra printer status.
const CString csIntermecStatusReq = char(5);		// Request the Intermec printer status.
const CString csDatamaxStatusReq = "SOH A";			// Request the Datamax printer status.
const int nWatchTime = 3;								// Seconds to watch for response.
const CString csApolloFlushQueue ="\033c \r";
const CString csZebraFlushQueue ="~JA";


class CPrinter  
{
public:
	void SetDefaults();
	void FormFeed();
	CString GetStatusString();
	CPrinter();
	virtual ~CPrinter();

	BOOL Initialize ( CDatabase *poDatabase, 
							CSNManager *poSNManager, 
							BOOL *bUsePrinter );
	void SetUse ( BOOL bUse );
	BOOL GetUse();
	void SetType ( int nType );
	int  GetType();
	void SetEnable ( BOOL bEnable );
	BOOL GetEnable();
	BOOL PrintLabel ( CString csLabel );
	void SetPrepickPosition ( CString csPrepickPos );
	CString GetPrepickPosition();
	void SetPickPosition ( CString csPickPos );
	CString GetPickPosition();
	void SetPrepickRotation ( CString csPrepickRot );
	CString GetPrepickRotation();
	void SetPickRotation ( CString csPickRot );
	CString GetPickRotation();
	BOOL GetStatus();
	BOOL SetPickPositions ( CString csPrepickPos, CString csPickPos );
	BOOL Refresh ( CDatabase *poDatabase );
	CString GetPrintedLabel ( );
	CString BuildLabel ( BOOL bRunMode, CJob *poJob, CString csTemplate );
	CString BuildSerialNumber(CJob *poJob);
	CString ReplaceKeyWord(CString csTemplate, CString csKeyWord, CString csValue);

	CString GetSerialNumberPrefix1();
	CString GetSerialNumberPrefix2();
	CString GetSerialNumberPrefix3();
	CString GetSerialNumberPrefix4();
	CString GetSerialNumberPrefix5();

	void SetSerialNumberPrefix1(CString csPrefixValue);
	void SetSerialNumberPrefix2(CString csPrefixValue);
	void SetSerialNumberPrefix3(CString csPrefixValue);
	void SetSerialNumberPrefix4(CString csPrefixValue);
	void SetSerialNumberPrefix5(CString csPrefixValue);

	CString GetPrintedSerialNumber();
	void  SetPrintedSerialNumber(CString csSerialNumber);

	int GetSerialNumberPrefix1Width();
	int GetSerialNumberPrefix2Width();
	int GetSerialNumberPrefix3Width();
	int GetSerialNumberPrefix4Width();
	int GetSerialNumberPrefix5Width();

	void SetSerialNumberPrefix1Width(CString csPrefixValue);
	void SetSerialNumberPrefix2Width(CString csPrefixValue);
	void SetSerialNumberPrefix3Width(CString csPrefixValue);
	void SetSerialNumberPrefix4Width(CString csPrefixValue);
	void SetSerialNumberPrefix5Width(CString csPrefixValue);


	void ResetPrinter();

	CString GetSuffix();
	int GetSuffixStrLength();
	CString GetCheckDigitValue();

	CString Convert_SSA(CString csBuffer);
	CString ConvertCode128_SSA(CString csSerialNumber);



private:
	CString ExtractBarCodeText(CString csPrintedLabel);
	BOOL	m_bUse;								// Use this printer;
	BOOL	m_bEnable;							// Enable this printer;
	int	m_nType;								// Printer type;
	BOOL	m_bInitialized;					// Object initialized flag.
	int	m_nPrinterLocation;				// Printer sub-system type.
	CString m_csPrintedLabel;
	
	CString m_csSerialNumber;

	CString m_csPrepickPos;					// Pre-pick x and y position.
	CString m_csPickPos;						// Pick x and y position.
	CString m_csPrepickRot;					// Pre-pick rotation.
	CString m_csPickRot;						// Pick rotation.

	CcomPort m_oComPort;						// The com port for the printer.
	CSNManager *m_poSNManager;				// Pointer to the serial number manager object.

	CDatabase *m_poDatabase;

	BOOL GetZebraStatus();
	BOOL GetIntermecStatus();
	BOOL GetDatamaxStatus();
	BOOL GetApolloStatus();
	CString GetApolloErrorMsg(CString csErrorType);



	CString m_csSerialNumberPrefix1;
	CString m_csSerialNumberPrefix2;
	CString m_csSerialNumberPrefix3;
	CString m_csSerialNumberPrefix4;
	CString m_csSerialNumberPrefix5;


	int m_nSerialNumberPrefix1Width;
	int m_nSerialNumberPrefix2Width;
	int m_nSerialNumberPrefix3Width;
	int m_nSerialNumberPrefix4Width;
	int m_nSerialNumberPrefix5Width;

	CString m_csSuffix;
	int m_csSuffixWidth;


	CString m_csCheckDigit;


};

#endif // !defined(AFX_PRINTER_H__9FBC34C2_B174_11D2_A68A_641A11C1FB5F__INCLUDED_)
