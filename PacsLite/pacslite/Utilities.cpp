// Utilities.cpp : Defines the class behaviors for the application.
//


#include "stdafx.h"
#include <stdlib.h>
#include <math.h>

#include "Utilities.h"
#include "resource.h"



#define	MAX_CHAR		32

static char szSerialNumberTable[MAX_CHAR] = "0123456789BCDFGHJKLMNPQRSTVWXYZ";



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUtilities



/////////////////////////////////////////////////////////////////////////////
// CUtilities construction

CUtilities::CUtilities()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}




////////////////////////////////////////////////////////////////////////////
// CUtilities destructor
CUtilities::~CUtilities()
{
}


/////////////////////////////////////////////////////////////////////////////
// CUtilities commands



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: lOffsetTof
//
//	Description:
//		Convert a long offset to a floating point offset.
//
//	Arguments:
//		Long value.
//
//	Return:
//		Floating point format of long value.
//
//	Called by:
//		CLabelerView::InitProperties
//
/////////////////////////////////////////////////////////////////////////////////////

float CUtilities::lOffsetTof ( long lOffset )
{

	// Offsets are entered as floats but are stored and transfered
	// to other subsystems as whole numbers in hundreths of mm.

	// To convert the long offset to a float offset the long
	// value is divide by 100.

	return ( (float)lOffset / (float)100.0 );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: fOffsetTol
//
//	Description:
//		Convert a float offset to long.
//
//	Arguments:
//		float value.
//
//	Return:
//		long format of floating point offset.
//
//	Called by:
//		CLabelerView::ReceiveProperties
//
/////////////////////////////////////////////////////////////////////////////////////

long CUtilities::fOffsetTol ( float fOffset )
{

	// Offsets are entered as floats but are stored and transfered
	// to other subsystems as whole numbers in hundreths of mm.

	// To convert a float to a long 2 digits of precision to the 
	// right of the decimal point must be ensured and the decimal 
	// point must be removed.

	CString strTemp, strLeft, strRight;
	long lOffset;
	int nIndex;

	strTemp.Format ( "%.2f", fOffset );		// Force 2 digits to right of decimal point.

	// Remove decimal point.

	nIndex = strTemp.Find ( "." );
	strLeft = strTemp.Left ( nIndex );		// Get left of decimal point.
	strRight = strTemp.Right ( 2 );			// Get right of decimal point.

	strTemp = strLeft + strRight;

	// Convert string back to long.

	lOffset = atol ( (const char *)strTemp );

	return ( lOffset );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: atol34
//
//	Description:
//		Converts a BASE 34 string to long number.
//
//	Arguments:
//		Serial number string.
//
//	Return:
//		long serial number format.
//
//	Called by:
//		JobControlThread - DoInitializeRun
//
/////////////////////////////////////////////////////////////////////////////////////

long CUtilities::atol34 ( CString strLabel )
{

	long  lPowerVal;
	long  lTempHex;
	long  lTempVal = 0;

	int   i, j;

	for ( i = 0; i < 4; i++ )
	{
		lPowerVal = 1;
		for (j = 1; j < (4-i); j++)
			lPowerVal *= (long) 34;

		if ( isdigit ( strLabel.GetAt ( i ) ) )
			lTempHex = strLabel.GetAt ( i ) - '0';
		else
			lTempHex = toupper( strLabel.GetAt ( i ) ) - 'A' + 10;

		lTempVal += (long) lPowerVal * lTempHex;
	}

	return ( lTempVal );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: ltoa34
//
//	Description:
//		Converts a long number to a BASE 34 string.
//
//	Arguments:
//		Serial number string.
//
//	Return:
//		long serial number format.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

CString CUtilities::ltoa34 ( long lSerNum )
{

	long  lPowerVal;
	long  lTempHex;
	long  lTempVal;

	int   i;

	CString strLabel = "0000";


	lTempVal = lSerNum;
	lPowerVal = 34;

	for ( i = 0; i < 4; i++ )
	{
		lTempHex = lTempVal % lPowerVal;

		if ( lTempHex < 10 )
			strLabel.SetAt ( 4-1-i, (_TCHAR)(lTempHex + '0') );
		else
			strLabel.SetAt ( 4-1-i, (_TCHAR)(lTempHex + 'A' - 10) );

		lTempVal -= lTempHex;
		lTempVal /= lPowerVal;
	}

	return ( strLabel );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: atol36
//
//	Description:
//		Converts a BASE 36 string to long number.
//
//	Arguments:
//		Serial number string.
//
//	Return:
//		long serial number format.
//
//	Called by:
//		JobControlThread - DoInitializeRun
//
/////////////////////////////////////////////////////////////////////////////////////

long CUtilities::atol36 ( CString strLabel )
{

	long  lPowerVal;
	long  lTempHex;
	long  lTempVal = 0;

	int   i, j;

	for ( i = 0; i < 4; i++ )
	{
		lPowerVal = 1;
		for (j = 1; j < (4-i); j++)
			lPowerVal *= (long) 36;

		if ( isdigit ( strLabel.GetAt ( i ) ) )
			lTempHex = strLabel.GetAt ( i ) - '0';
		else
			lTempHex = toupper( strLabel.GetAt ( i ) ) - 'A' + 10;

		lTempVal += (long) lPowerVal * lTempHex;
	}

	return ( lTempVal );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: ltoa36
//
//	Description:
//		Converts a long number to a BASE 36 string.
//
//	Arguments:
//		Serial number string.
//
//	Return:
//		long serial number format.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

CString CUtilities::ltoa36 ( long lSerNum )
{

	long  lPowerVal;
	long  lTempHex;
	long  lTempVal;

	int   i;

	CString strLabel = "0000";


	lTempVal = lSerNum;
	lPowerVal = 36;

	for ( i = 0; i < 4; i++ )
	{
		lTempHex = lTempVal % lPowerVal;

		if ( lTempHex < 10 )
			strLabel.SetAt ( 4-1-i, (_TCHAR)(lTempHex + '0') );
		else
			strLabel.SetAt ( 4-1-i, (_TCHAR)(lTempHex + 'A' - 10) );

		lTempVal -= lTempHex;
		lTempVal /= lPowerVal;
	}

	return ( strLabel );

}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: NextSerNum
//
//	Description:
//		Increments the serial number by 1 and wraps it if it is out of bounds.
//
//	Arguments:
//		Serial number.
//
//	Return:
//		Incremented serial number.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

int CUtilities::NextSerNum ( int nSerNum )
{


  nSerNum++;

  if ( nSerNum > 9999 )
    nSerNum = 0;

  return ( nSerNum );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: YieldToWindows
//
//	Description:
//		Give control back to windows to handle messages.
//
//	Arguments:
//		None.
//
//	Return:
//		None.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

void CUtilities::YieldToWindows ( void )
{


	// Process existing messages in the application's message queue.
	// When the queue is empty, do clean up and return.
	
	MSG msg;

	while ( ::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE) )
	{
		if (!AfxGetThread()->PumpMessage())
//		if (!CWinThread::PumpMessage())
			return;
	}

}




/////////////////////////////////////////////////////////////////////////////
//
//	Name:
//		AsciiHexToUINT
//
//
//	Description:		
//		Convert an ascii string of a hex number to a UINT
//
//	Arguments:
//		Hex string.
//	
//	Returns:
//		UINT converted number.
//
//	Called By:
//		CLabelerDoc::ReadJobFile
//		CLabelerView::OnSetupRunConditions
//
//////////////////////////////////////////////////////////////////////////////

UINT CUtilities::AsciiHexToUINT ( CString strHexNumber )
{
	int i, j;
	char ch;
	UINT nNumber = 0;


	if ( strHexNumber.GetLength() == 0 )
		return 0;

	for ( i = strHexNumber.GetLength() - 1; i >= 0; i-- )
	{

		// Isolate character.

		ch = strHexNumber[i];
		if( ch == '0')
			j = 0;
		else if( ch == '1')
			j = 1;
		else if(ch == '2')
			j = 2;
		else if(ch == '3')
			j = 3;
		else if(ch == '4')
			j = 4;
		else if(ch == '5')
			j = 5;
		else if(ch == '6')
			j = 6;
		else if(ch == '7')
			j = 7;
		else if(ch == '8')
			j = 8;
		else if(ch == '9')
			j = 9;
		else if( ch == 'A')
			j = 10;
		else if(ch == 'B')
			j = 11;
		else if(ch == 'C')
			j = 12;
		else if ( ch == 'D')
			j = 13;
		else if ( ch == 'E' )
			j = 14;
		else if (ch == 'F')
			j = 15;

		// Convert character to number.

		nNumber += j * ( (int) pow(16, strHexNumber.GetLength() - 1 - i) );

	}

	return ( nNumber );

}



/////////////////////////////////////////////////////////////////////////////
//
//	Name:
//		UINTToAsciiHex
//
//
//	Description:		
//		Convert an UINT number to an ascii string.
//
//	Arguments:
//		Number to convert.
//	
//	Returns:
//		Ascii string.
//
//	Called By:
//		CLabelerDoc::WriteJobFile
//		CLabelerView::OnSetupRunConditions
//
//////////////////////////////////////////////////////////////////////////////

CString CUtilities::UINTToAsciiHex ( UINT nNumber )
{


/****************  NOTE: There is a bug in this function. *****************/
/****************						DO NOT USE               *****************/

	div_t div_result;
	BOOL bDone = FALSE;

	CString strTemp, strHexNumber;

	// Use the radix divide technique to convert the decimal integer to
	// base 16.

	while ( !bDone )
	{

		div_result = div ( nNumber, 16 );
		
		if ( div_result.rem < 10 )
		{
			// Check for 0 remainder.

			if ( div_result.rem == 0 )
			{
				strTemp.Format ( "%d%d", div_result.quot, div_result.rem );
				bDone = TRUE;
			}
			else
				strTemp.Format ( "%d", div_result.rem );
		}
		else
		{

			switch ( div_result.rem )
			{

				case 10:
					strTemp = "A";
					break;

				case 11:
					strTemp = "B";
					break;

				case 12:
					strTemp = "C";
					break;

				case 13:
					strTemp = "D";
					break;

				case 14:
					strTemp = "E";
					break;

				case 15:
					strTemp = "F";
					break;

			}

			if ( div_result.quot == 0 )
				bDone = TRUE;
					
		}

		strHexNumber += strTemp;
		nNumber = div_result.quot;

	}

	return ( strHexNumber );

}




/////////////////////////////////////////////////////////////////////////////
//
//	Name:
//		CurseAndSleep
//
//	Description:		
//		Change to wait cursor and take a nap.
//
//	Arguments:
//		Nap time in milliseconds.
//	
//	Returns:
//		None.
//
//	Called By:
//
//////////////////////////////////////////////////////////////////////////////

void CUtilities::CurseAndSleep ( long lSleep )
{

	CWaitCursor	wcHourGlass;


	Sleep ( lSleep );

}






/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: IsNumeric
//
//	Description:
//		Determine if a string is numeric.
//
//	Arguments:
//		String to check.
//
//	Return:
//		Status of check.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CUtilities::IsNumeric ( CString csNumber )
{

	int int_len = csNumber.GetLength();
	int i;
	char chr_temp;


	if (int_len < 1 )
		return FALSE;

	for (i = 0; i < int_len; i++)
	{
			chr_temp = csNumber[i];
			
			if (((int(chr_temp) < 48) || (int(chr_temp) > 57 )))
			{
				if(!((int(chr_temp) == 43)|| (int(chr_temp) == 45)))
						return FALSE;
			}
	}

	return TRUE;

}



/////////////////////////////////////////////////////////////////////////////
//
//	Name:
//		IsValidHex
//
//
//	Description:		
//		Determine if the string is a valid hex number.
//
//	Arguments:
//		Hex string.
//		Minimum size in characters.
//		Maximum size in characters.
//	
//	Returns:
//		Status
//
//	Called By:
//
//////////////////////////////////////////////////////////////////////////////

BOOL CUtilities::IsValidHex ( CString csNumber, int nMinSize, int nMaxSize )
{

	int
		i,
		nLength;

	CString
		csTemp;


	// Check for correct length.

	nLength = csNumber.GetLength();

	if ( nLength < nMinSize || nLength > nMaxSize )
		return ( FALSE );

	// Check for correct characters.

	for ( i = 0; i < nLength; i++ )
	{
		csTemp = csNumber.Mid ( i, 1 );
		if ( csTemp != "0" && csTemp != "1" && csTemp != "2" && csTemp != "3" &&
			  csTemp != "4" && csTemp != "5" && csTemp != "6" && csTemp != "7" &&
			  csTemp != "8" && csTemp != "9" && csTemp != "a" && csTemp != "A" &&
			  csTemp != "b" && csTemp != "B" && csTemp != "c" && csTemp != "C" &&
			  csTemp != "d" && csTemp != "D" && csTemp != "e" && csTemp != "E" &&
			  csTemp != "f" && csTemp != "F" )
			return ( FALSE );
	}

	return ( TRUE );

}





/////////////////////////////////////////////////////////////////////////////
//
//	Name:
//		IsValidSettings
//
//
//	Description:		
//		Determine if the string is a com port setting string.
//
//	Arguments:
//		Com port setting string.
//	
//	Returns:
//		Status
//
//	Called By:
//
//////////////////////////////////////////////////////////////////////////////

BOOL CUtilities::IsValidSettings ( CString csSettings )
{

	CString csTemp;

	int
		nIndex,
		nLength;


	// Settings string should have the format of :
	//   baudrate,parity,databits,stopbit
	//
	//  Ex. 9600,N,8,1

	nIndex = csSettings.Find ( "," );
	nLength = csSettings.GetLength();
	if ( nIndex < 1 )
		return ( FALSE );

	csTemp = csSettings.Left ( nIndex );

	if (csTemp != "38400" &&
		csTemp != "19200" &&
		  csTemp != "9600" &&
		  csTemp != "4800" &&
		  csTemp != "2400" &&
		  csTemp != "1200" &&
		  csTemp != "600" &&
		  csTemp != "300" )
		return ( FALSE );

	csSettings = csSettings.Right ( nLength - nIndex - 1 );

	nIndex = csSettings.Find ( "," );
	nLength = csSettings.GetLength();
	if ( nIndex < 1 )
		return ( FALSE );

	csTemp = csSettings.Left ( nIndex );

	if ( csTemp != "N" &&
		  csTemp != "E" &&
		  csTemp != "O" )
		return ( FALSE );

	csSettings = csSettings.Right ( nLength - nIndex - 1 );

	nIndex = csSettings.Find ( "," );
	nLength = csSettings.GetLength();
	if ( nIndex < 1 )
		return ( FALSE );

	csTemp = csSettings.Left ( nIndex );

	if ( csTemp != "7" &&
		  csTemp != "8" )
		return ( FALSE );

	csSettings = csSettings.Right ( nLength - nIndex - 1 );

	if ( csSettings != "1" &&
		  csSettings != "0" )
		return ( FALSE );

	return ( TRUE );

}




/////////////////////////////////////////////////////////////////////////////
//
//	Name:
//		IsValidPath
//
//
//	Description:		
//		Determine if the string is a valid path.
//		Flag indicating whether or not the string contains a file.
//
//	Arguments:
//		Path string.
//	
//	Returns:
//		Status
//
//	Called By:
//
//////////////////////////////////////////////////////////////////////////////

BOOL CUtilities::IsValidPath ( CString csPath, BOOL bIncludesFile )
{

	CString csDirectory;

	int
		nIndex;


	if ( bIncludesFile )
	{

		// Separate directory from file.

		nIndex = csPath.ReverseFind ( '\\' );
		if ( nIndex != -1 )
			csDirectory = csPath.Left ( nIndex );
		else
		{
			if ( csPath.GetLength() > 0 )
				return ( TRUE );			// Use current directory for file.
			else
			{
				return ( FALSE );
			}
		}
	}
	else
		csDirectory = csPath;


	// Verify directory.

   char buffer[_MAX_PATH];

   /* Get the current working directory: */
   ::GetCurrentDirectory ( _MAX_PATH, buffer );

	if ( !::SetCurrentDirectory( csDirectory ) )
	{
		::SetCurrentDirectory( buffer );
		return ( FALSE );
	}

	::SetCurrentDirectory( buffer );			// Change working directory back to original.


	return ( TRUE );

}





/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: IncrementBase31
//
//	Description:
//		Increment a BASE 31 string. Base 31 is 0-9, A-Z except A,
//		E, I, O, and U.
//
//	Arguments:
//		Serial number string.
//
//	Return:
//		Incremented string.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

CString CUtilities::IncrementBase31 ( CString csSerialNumber )
{

	CString 
		csSerNum;

	int
		i,
		k,
		nLength;

	BOOL
		bDone;


	// Serial number must be filled with leading 0's.

	csSerNum = csSerialNumber;

	nLength = csSerialNumber.GetLength();

	// The serial number changes in the following way.
	// 
	// Each column can be incremented by 1 with valid
	// characters of 0 - 9; A - Z except characters A, E, 
	// I, O, and U. When one column reaches Z ( 31 
	// increments of valid characters ) increment the next
	// column to the left and then start at 0 with the
	// column to the right.

	// Start with the first digit. Bump it up by one character
	// if it doesn't need to be carried over to the next digit.
	// Else, set digit to 0 and bump up the next digit, and so on.

	k = nLength - 1;
	bDone = FALSE;

	while ( k >= 0 && !bDone )
	{

		i = 0;
		while ( i < MAX_CHAR-1 && !bDone )
		{
			if ( csSerialNumber.GetAt ( k ) == szSerialNumberTable[i] )
			{
				if ( csSerialNumber.GetAt ( k ) != 'Z' )
				{
					// Current digit.

					// Just increment column to the next character.

					csSerNum.SetAt ( k, szSerialNumberTable[i+1] );
					bDone = TRUE;	// Done. Lets blow this popcorn stand.
				}
				else
				{

					// Set current digit to 0 and index to next digit.

					csSerNum.SetAt ( k, '0' );
					k--;
				}
			}
			else
				i++;
		}	// End while.


		if ( i == MAX_CHAR-1 && !bDone )
		{

			// We have trouble. Reset serial number to 0.

			int l;
			l = nLength - 1;
			while ( l >= 0 )
				csSerNum.SetAt ( l, '0' );
			bDone = TRUE;
		}
	}	// End while.

	return ( csSerNum );

}



/////////////////////////////////////////////////////////////////////////////
//
//	Name:
//		CalculateDate
//
//	Description:		
//		Determine the date in MM/DD/YYYY.
//
//	Arguments:
//		None.
//	
//	Returns:
//		Date
//
//	Called By:
//
//////////////////////////////////////////////////////////////////////////////

CString CUtilities::CalculateDate ( void )
{

	time_t timer;

	struct tm *tmTime;

	int
	  nMon,
	  nDay,
	  nYear;

	CString csDate;


	timer = time(NULL);
	tmTime = localtime(&timer);

	nMon = tmTime->tm_mon + 1;
	nDay = tmTime->tm_mday;    
	nYear = tmTime->tm_year + 1900;

	csDate.Format ( "%02d/%02d/%04d", nMon, nDay, nYear );

	return ( csDate );

}





/////////////////////////////////////////////////////////////////////////////
//
//	Name:
//		GetDateTime
//
//	Description:		
//		Get the current date and time.
//
//	Arguments:
//		None.
//	
//	Returns:
//		Date and time string
//
//	Called By:
//
//////////////////////////////////////////////////////////////////////////////

CString CUtilities::GetDateTime ( void )
{

	time_t timer;

	struct tm *tmTime;

	CString csDateTime;


	timer = time(NULL);
	tmTime = localtime(&timer);

	csDateTime.Format ( "%s", asctime( tmTime ) );

	return ( csDateTime );

}



/////////////////////////////////////////////////////////////////////////////
//
//	Name:
//		CheckPositionFormat
//
//	Description:		
//		Check the format of the position string.
//
//	Arguments:
//		Position string
//	
//	Returns:
//		Status
//
//	Called By:
//
//////////////////////////////////////////////////////////////////////////////

BOOL CUtilities::CheckPositionFormat ( CString csPosition )
{

	int
		nLength;

	CString
		csRot;


	// The position must have the format of x,y;rot
	//		where:
	//			x = 6 digits,
	//			y = 6 digits,
	//			rot = 0 or 90.

	nLength = csPosition.GetLength();

	if ( csPosition[6] != ',' || csPosition[13] != ';' )
		return ( FALSE );

	csRot = csPosition.Right ( nLength - 14 );

	if ( !IsNumeric ( csPosition.Left ( 6 ) ) || !IsNumeric ( csPosition.Mid ( 7, 6 ) ) ||
		  !IsNumeric ( csRot )  || ( csRot != "0" && csRot != "00" && csRot != "90" ) )
		return ( FALSE );

	return ( TRUE );

}

CString CUtilities::GetDateCode(CString format)
{
	COleDateTime objOleTime;
    objOleTime = COleDateTime::GetCurrentTime();
   
	int		nYear,
		    nMonth,
			nDDD,
			nDD,
			nWeek;
	CString	csYear,
		    csMonth,
			csWeek,
			csDayOfYear,
			csDayOfWeek,
			csReturnString,
			csTemp;

	char	temp[100];
	
	nYear = objOleTime.GetYear();
	itoa(nYear,temp,10);
	csYear = temp;
	csYear = csYear.Right(2);

	nMonth = objOleTime.GetMonth();
	itoa(nMonth,temp,10);
	csMonth = temp;
	if (csMonth.GetLength()==1)
		csMonth = "0" + csMonth;
	
	nWeek=GetWeek();
	itoa(nWeek,temp,10);
	csWeek = temp;
	if (csWeek.GetLength()==1)
		csWeek = "0" + csWeek;

	nDD = objOleTime.GetDay()+1;
	itoa(nDD,temp,10);
	csDayOfWeek = temp;
	if (csDayOfWeek.GetLength()==1)
		csDayOfWeek = "0" + csDayOfWeek;


    nDDD = objOleTime.GetDayOfYear();
	itoa(nDDD,temp,10);
	csDayOfYear = temp;
	if (csDayOfYear.GetLength()==1)
		csDayOfYear = "00" + csDayOfYear;
	else if (csDayOfYear.GetLength()==1)
		csDayOfYear = "0" + csDayOfYear;

	if (format== "YYMM")
		csReturnString = csYear+csMonth;
	else if (format== "MMYY")
		csReturnString = csMonth+csYear;
	else if (format== "YYWW")
		csReturnString = csYear+csWeek;
	else if (format== "WWYY")
		csReturnString = csWeek+csYear;

	else if (format== "YYDD")	
		csReturnString = csYear+csDayOfWeek;
	else if (format== "DDYY")	
		csReturnString = csDayOfWeek+csYear;

	else if (format== "YYMMDD")	
		csReturnString = csYear  +
			             csMonth +
						 csDayOfWeek;
	else if (format== "YYDDMM")	
		csReturnString = csYear  +
			             csDayOfWeek +
						 csMonth;


	else if (format== "DDMMYY")	
		csReturnString = csDayOfWeek  +
			             csMonth +
						 csYear;


	else if (format== "MMDDYY")	
		csReturnString = csMonth  +
			             csDayOfWeek +
						 csYear;

	else if (format== "YYDDD")
	{

		if (csDayOfYear.GetLength()==1)
		{
			csDayOfYear="00"+csDayOfYear;
		}
		else if (csDayOfYear.GetLength()==2)
		{
			csDayOfYear="0"+csDayOfYear;

		}
		csReturnString = csYear  +
							 csDayOfYear;
	}
	else if (format== "DDDYY")	

			csReturnString = csDayOfYear  +
							 csYear;

	else if ((format== "DDD")||(format== "ddd"))	
	{

		if (csDayOfYear.GetLength()==1)
		{
			csDayOfYear="00"+csDayOfYear;
		}
		else if (csDayOfYear.GetLength()==2)
		{
			csDayOfYear="0"+csDayOfYear;

		}

		csReturnString = csDayOfYear;  

	}
	else if ((format== "Y")||(format== "y"))	

		csReturnString = csYear.Right(1);  
	
	else if ((format== "YY")||(format== "yy"))	

		csReturnString = csYear.Right(2);  

	else
	{
		
		csTemp.LoadString(IDS_ERR_UNRECOGNIZED_FORMAT_STRING);
		AfxMessageBox(csTemp);
		csReturnString = "00/00/00";
	}

	return (csReturnString);
}


int CUtilities::GetWeek()
{
	COleDateTime objOleTime;
    objOleTime = COleDateTime::GetCurrentTime();

CString nDDD = objOleTime.Format("%U");

int nWeek=atoi(nDDD);

   return nWeek;
}



float CUtilities::ElapsedTime(SYSTEMTIME lpStartCurCycleTime,
					  SYSTEMTIME lpEndCurCycleTime)
{

WORD wStartDay,
	 wEndDay;     
WORD wStartHour,
     wEndHour;
     
WORD wStartMinute,
     wEndMinute;     

WORD wStartSecond;
WORD wEndSecond;
 
WORD wStartMilliseconds;
WORD wEndMilliseconds;
 
float fDeltaMin,
	  fDeltaSec,
	  fDeltaMMSec,
	  fTotalDelta;

	wStartDay = lpStartCurCycleTime.wDay;
	wEndDay = lpEndCurCycleTime.wDay;


	wStartHour = lpStartCurCycleTime.wHour;
	wEndHour = lpEndCurCycleTime.wHour;

	wStartMinute = lpStartCurCycleTime.wMinute;
	wEndMinute = lpEndCurCycleTime.wMinute;

	wStartSecond = lpStartCurCycleTime.wSecond;
	wEndSecond = lpEndCurCycleTime.wSecond;

	wStartMilliseconds = lpStartCurCycleTime.wMilliseconds;
	wEndMilliseconds = lpEndCurCycleTime.wMilliseconds;

	
	if (wEndMinute<wStartMinute)
	{
	   fDeltaMin= (float)(60.0 - (wStartMinute-wEndMinute));
	}
	else
	{
	   fDeltaMin= (float)(wEndMinute-wStartMinute);
	}

	if (wEndSecond<wStartSecond)
	{
	   fDeltaSec= (float)(60 - (wStartSecond-wEndSecond));
	}
	else
	{
	   fDeltaSec= (float)(wEndSecond-wStartSecond);
	}
	
	if (wEndMilliseconds<wStartMilliseconds)
	{
	   fDeltaMMSec= (float)(1000 - (wStartMilliseconds-wEndMilliseconds));
	}
	else
	{
	   fDeltaMMSec= (float)(wEndMilliseconds-wStartMilliseconds);
	}

	if (fDeltaMin>0)
	{
		if (wEndSecond>wStartSecond)
			fTotalDelta=fDeltaMin*60+fDeltaSec+fDeltaMMSec/1000;
		else
			fTotalDelta=fDeltaSec+fDeltaMMSec/1000;

	}
	else
	{
		fTotalDelta=fDeltaSec+fDeltaMMSec/1000;

	}
	
	return fTotalDelta;

}

int CUtilities::GetPointType(CString csPointType)
{
int nRetVal;

	if (csPointType=="Orgin")
	{
		nRetVal=ORIGIN_KEY;
	}
	else if (csPointType=="Park")
	{
		nRetVal=PARK_KEY;
	}
	else if (csPointType=="RestPosition")
	{
	
		nRetVal=REST_POSITION_KEY;	
	}
	return nRetVal;
}

