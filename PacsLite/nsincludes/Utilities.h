// Utilities.h		This header prototypes the utility
//					functions used by Labeler.
//

#ifndef UTILITIES_H__
#define UTILITIES_H__


/////////////////////////////////////////////////////////////////////////////
// CUtilities:
// 
//
#include "trace.h"
#include "definitions.h"


class AFX_MFC_EXT_TYPE CUtilities : public CObject
{
public:
	long fOffsetTol ( float fOffset );
	float lOffsetTof ( long lOffset );
	long atol36 ( CString strLabel );
	CString ltoa36 ( long lSerNum );
	CString IncrementBase31 ( CString csSerialNumber );
	long atol34 ( CString strLabel );
	CString ltoa34 ( long lSerNum );
	int NextSerNum ( int nSerNum );
	void YieldToWindows ( void );
	CString UINTToAsciiHex ( UINT nNumber );
	UINT AsciiHexToUINT ( CString strHexNumber );
	void CurseAndSleep ( long lSleep );
	BOOL IsNumeric ( CString csNumber );
	BOOL IsValidHex ( CString csNumber, int nMinSize, int nMaxSize );
	BOOL IsValidSettings ( CString csSettings );
	BOOL IsValidPath ( CString csPath, BOOL bIncludesFile );
	CString CalculateDate ( void );
	CString GetDateTime ( void );
	BOOL CheckPositionFormat ( CString csPosition );

	CUtilities();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUtilities)

	//}}AFX_VIRTUAL

// Implementation

public:
	CString GetDateCode(CString format);
	int GetWeek();
	float ElapsedTime(SYSTEMTIME lpStartCurCycleTime,
					  SYSTEMTIME lpEndCurCycleTime);

	int GetPointType(CString csPointType);	

	CString GetShiftID();

	virtual ~CUtilities();

	//{{AFX_MSG(CUtilities)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
};


/////////////////////////////////////////////////////////////////////////////

#endif // UTILITIES_H__
