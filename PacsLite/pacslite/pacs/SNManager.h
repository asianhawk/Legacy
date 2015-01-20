// SNManager.h: interface for the CSNManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNMANAGER_H__43A44D41_2B68_11D2_A68A_641A11C1FB5F__INCLUDED_)
#define AFX_SNMANAGER_H__43A44D41_2B68_11D2_A68A_641A11C1FB5F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Database.h"
#include "Job.h"


class CSNManager  
{
public:
	CSNManager();
	virtual ~CSNManager();

	BOOL Initialize ( CString csJobName, CDatabase *poDatabase );
	CString GetSerialNumber ( void );
	BOOL GetNextSerialNumber ( CString csJobName );
	CString GetSerialNumberFile ( void );
	void  SetSerialNumberFile ( CString csSNServerFile );
	void SetSerialNumber ( CString csSerialNumber );
	CString IncrementSerialNumber ( void );
	BOOL UseSerialization ( void );
	void SetSerialNumberN ( int nSN, CString csSerialNumber );
	CString GetSerialNumberN ( int nSN );
	CString DecrementSerialNumber (  CString csJobName  );
	BOOL m_blnUseCheckDigit;
	CString m_csCheckDigitSource;
	CString m_csCheckDigitType;


private:

	CString m_csSerialNumber;
	CString m_csSerialNumberFile;

	BOOL m_bUseSerialization;
	BOOL m_bResetJulianDate;
	int m_nSNType;
	int m_nSNLength;
	CString m_csStartingSN;

	CString m_csSerialNumber1;
	CString m_csSerialNumber2;

	CDatabase *m_poDatabase;

	CString IncrementBase10 ( );
	CString IncrementBase16 ( );
	CString IncrementBase31 ( );
	CString IncrementBase29 ( );
	CString IncrementBase36 ( );

	CString DecrementBase10 ( );
	CString DecrementBase16 ( );
	CString DecrementBase29 ( );
	CString DecrementBase31 ( );
	CString DecrementBase36 ( );

	
	BOOL m_blnChkForShiftChanges;
	BOOL m_blnChkForJulianReset;
	int  m_nPrevShiftID;
	int	 m_nCurrentShiftID;

	int m_nPrevDate;
	int m_nCurrentDate;
	CString m_csPrevJulianDate;
	CString m_csCurrentJulianDate;

};

#endif // !defined(AFX_SNMANAGER_H__43A44D41_2B68_11D2_A68A_641A11C1FB5F__INCLUDED_)
