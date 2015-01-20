// SNManager.cpp: implementation of the CSNManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PACS.h"
#include "SNManager.h"
#include "Utilities.h"
#include "trace.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif




#define	MAX_CHAR_10		11
static char szBase10Table[MAX_CHAR_10] = "0123456789";

#define	MAX_CHAR_16		17
static char szBase16Table[MAX_CHAR_16] = "0123456789ABCDEF";

#define MAX_CHAR_29		30
static char szBase29Table[MAX_CHAR_29] = "0123456789CDEFGHJKLMNPRTUVWXY";

#define	MAX_CHAR_31		32
static char szBase31Table[MAX_CHAR_31] = "0123456789BCDFGHJKLMNPQRSTVWXYZ";

#define	MAX_CHAR_36		37
static char szBase36Table[MAX_CHAR_36] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSNManager::CSNManager()
{
	m_nPrevShiftID=0;
	m_nCurrentShiftID=0;
	m_blnChkForShiftChanges=FALSE;
	m_blnChkForJulianReset=FALSE;


}

CSNManager::~CSNManager()
{

}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		Initialize
//
//	Description:
//		Initialize the serial number info.
//
//	Arguments:
//		Serial number interface file string.
//
//	Return:
//		Status.
//
//	Called by:
//		CApplicatorControl::Run
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CSNManager::Initialize ( CString csJobName, CDatabase *poDatabase )
{

	CString
		csTemp,
		csLastJulianDate,
		csCheckDigitSource,
		csCheckDigitType;


	BOOL
		bUseSerialization,
		blnUseChkDigit;


	int
		nBase,
		nLength;

	CString 
		csSerialNumber;
	
	CTime tm;

	CUtilities oUtil;

	tm=CTime::GetCurrentTime(); 	


	m_poDatabase = poDatabase;

	// Retreive the serial number information from the database.

	
	
	
	if ( !m_poDatabase->GetSNAttributes (csJobName, 
										  &bUseSerialization,
										  &nBase,
										  &nLength,
										  &csSerialNumber,
										  &blnUseChkDigit,
										  &csCheckDigitSource,
										  &csCheckDigitType) )
	{
		csTemp.LoadString ( IDS_ERR_INIT_SN );
		AfxMessageBox ( csTemp );
		return ( FALSE );
	}

	m_bUseSerialization = bUseSerialization;
//	m_bResetJulianDate=bResetJulianDate;
	m_nSNType = nBase;
	m_nSNLength = nLength;
	m_csSerialNumber = csSerialNumber;
	m_csStartingSN = csSerialNumber;

	m_blnUseCheckDigit=blnUseChkDigit;
	m_csCheckDigitSource=csCheckDigitSource;
	m_csCheckDigitType=csCheckDigitType;

	// Used to monitor current serial number.

	m_csSerialNumber1 = csSerialNumber;
	m_csSerialNumber2 = csSerialNumber;



	return ( TRUE );

}









/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetNextSerialNumber
//
//	Description:
//		Retrieve the serial number from the serial number file. Save it for the next label.
//		Increment the serial number and save in file for the next usage.
//
//	Arguments:
//		Job name.
//
//	Return:
//		Status. 
//
//	Called by:
//		Applicator::Run
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CSNManager::GetNextSerialNumber ( CString csJobName )
{

	CString csSerialNumber;
	CString csMessage;
	CString csTemp;
	CString csFormat;

	CUtilities oUtil;
	BOOL
		bDBGood;
	CTime tm;

	Trace("[IS] Start of CSNManager::GetNextSerialNumber() JobName = [%s] ",csJobName);

	tm= CTime::GetCurrentTime();
	

	// Get next serial number from the database.


	Trace("[IS] Start of CSNManager::GetNextSerialNumber() Before GetStartingSN");
	
	bDBGood = m_poDatabase->GetStartingSN ( csJobName, &csSerialNumber );
	if ( !bDBGood )
	{
		csTemp.LoadString ( IDS_ERR_GET_SN );
		AfxMessageBox ( csTemp );
		return ( FALSE );
	}
	Trace("[IS] Start of CSNManager::GetNextSerialNumber() After GetStartingSN = [%s]",csSerialNumber);

	// Save serial number to be printed.

	// Ensure leading 0's.

	
/*	if (m_bResetJulianDate)
	{
	    m_csCurrentJulianDate=oUtil.GetDateCode("DDD"); 

		if (m_csCurrentJulianDate!=m_csPrevJulianDate)
		{
			csSerialNumber="1";
			m_csPrevJulianDate=m_csCurrentJulianDate;
		}
	}
*/
	
	csTemp.Format ( "%d", m_nSNLength );
	csFormat = "%0" + csTemp + "s";
	csSerialNumber.Format ( csFormat, csSerialNumber );


	m_csSerialNumber = csSerialNumber;

	// Increment serial number and save it to the database for the
	// next time. The database always stores the next serial number.

	csSerialNumber = IncrementSerialNumber();

	csSerialNumber.Format ( csFormat, csSerialNumber );

	bDBGood = m_poDatabase->SetStartingSN ( csJobName, csSerialNumber );
	m_csSerialNumber=csSerialNumber;
	if ( !bDBGood )
	{
		csTemp.LoadString ( IDS_ERR_GET_SN );
		AfxMessageBox ( csTemp );
		return ( FALSE );
	}
	else
	{

	//   m_poDatabase->SetLastJulianDate ( csJobName, csSerialNumber, m_csCurrentJulianDate );


	}
	Trace("[IS] End of CSNManager::GetNextSerialNumber() SerialNumber = [%s] ",csSerialNumber);
	return ( TRUE );

}





/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetSerialNumber
//
//	Description:
//		Get the serial number.
//
//	Arguments:
//		None.
//
//	Return:
//		Serial number.
//
//	Called by:
//		PrinterScanner::BuildLabel
//
/////////////////////////////////////////////////////////////////////////////////////

CString CSNManager::GetSerialNumber ( void )
{

	return ( m_csSerialNumber );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetSerialNumber
//
//	Description:
//		Set the serial number.
//
//	Arguments:
//		None.
//
//	Return:
//		Serial number.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

void CSNManager::SetSerialNumber ( CString csSerialNumber )
{

	m_csSerialNumber = csSerialNumber;

}





void CSNManager::SetSerialNumberFile ( CString csSerialNumberFile )
{

	m_csSerialNumberFile = csSerialNumberFile;

}


CString CSNManager::GetSerialNumberFile ( void )
{

	return ( m_csSerialNumberFile );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		IncrementSerialNumber
//
//	Description:
//		Increment the current serial number. Ensure it rolls over at the 
//		proper time.
//
//	Arguments:
//		None.
//
//	Return:
//		Serial number.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

CString CSNManager::IncrementSerialNumber ( void )
{

	CString
		csSerialNumber;


	// Someday:  combine these routines.

	switch ( m_nSNType )
	{
		case BASE10:
			csSerialNumber = IncrementBase10();
			break;

		case BASE16:
			csSerialNumber = IncrementBase16();
			break;

		case BASE29:
			csSerialNumber = IncrementBase29();
			break;

		case BASE31:
			csSerialNumber = IncrementBase31();
			break;

		case BASE36:
			csSerialNumber = IncrementBase36();
			break;

		default:
			break;
	}

	return ( csSerialNumber );

}







/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: IncrementBase10
//
//	Description:
//		Increment a BASE 10 string. Base 10 is 0-9.
//
//	Arguments:
//		None.
//
//	Return:
//		Incremented string.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

CString CSNManager::IncrementBase10 ( )
{

	CString 
		csTemp,
		csSerialNumber,
		csSerNum;

	int
		i,
		k;

	BOOL
		bDone;


	// Temp serial number must be set to max size.

	csSerialNumber = m_csSerialNumber;

	csSerNum = m_csSerialNumber;

	// The serial number changes in the following way.
	// 
	// Each column can be incremented by 1 with valid
	// characters of 0 - 9. When one column reaches 9 ( 10 
	// increments of valid characters ) increment the next
	// column to the left and then start at 0 with the
	// column to the right.

	// Start with the first digit. Bump it up by one character
	// if it doesn't need to be carried over to the next digit.
	// Else, set digit to 0 and bump up the next digit, and so on.

	k = m_nSNLength - 1;
	bDone = FALSE;

	while ( k >= 0 && !bDone )
	{

		i = 0;
		while ( i < MAX_CHAR_10-1 && !bDone )
		{
			if ( csSerialNumber.GetAt ( k ) == szBase10Table[i] )
			{
				if ( csSerialNumber.GetAt ( k ) != '9' )
				{
					// Current digit.

					// Just increment column to the next character.

					csSerNum.SetAt ( k, szBase10Table[i+1] );
					bDone = TRUE;	// Done. Lets blow this popcorn stand.
				}
				else
				{

					// Set current digit to 0 and index to next digit.

					csSerNum.SetAt ( k, '0' );
					k--;
					if ( k < 0 )
					{

						// Roll over condition. Reset serial number.
						csSerNum = "0";
						bDone = TRUE;
					}
					else
					{
						// Go to the next digit and check that.
						// The index to the serial number has been
						// moved to the next digit.

						i = 0;

					}
				}
			}
			else
				i++;
		}	// End while.


		if ( i == MAX_CHAR_10-1 && !bDone )
		{

			// We have trouble. Reset serial number to 0.

			int l;
			l = m_nSNLength - 1;
			while ( l >= 0 )
			{
				csSerNum.SetAt ( l, '0' );
				l--;
			}
			bDone = TRUE;
		}
	}	// End while.


	return ( csSerNum );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: IncrementBase16
//
//	Description:
//		Increment a BASE 16 string. Base 31 is 0-9, A-F.
//
//	Arguments:
//		None.
//
//	Return:
//		Incremented string.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

CString CSNManager::IncrementBase16 ( )
{

	CString 
		csTemp,
		csSerialNumber,
		csSerNum;

	int
		i,
		k;

	BOOL
		bDone;


	// Temp serial number must be set to max size.

	csSerialNumber = m_csSerialNumber;

	csSerNum = m_csSerialNumber;

	// The serial number changes in the following way.
	// 
	// Each column can be incremented by 1 with valid
	// characters of 0 - 9; A - F. When one column reaches F ( 16 
	// increments of valid characters ) increment the next
	// column to the left and then start at 0 with the
	// column to the right.

	// Start with the first digit. Bump it up by one character
	// if it doesn't need to be carried over to the next digit.
	// Else, set digit to 0 and bump up the next digit, and so on.

	k = m_nSNLength - 1;
	bDone = FALSE;

	while ( k >= 0 && !bDone )
	{

		i = 0;
		while ( i < MAX_CHAR_16-1 && !bDone )
		{
			if ( csSerialNumber.GetAt ( k ) == szBase16Table[i] )
			{
				if ( csSerialNumber.GetAt ( k ) != 'F' )
				{
					// Current digit.

					// Just increment column to the next character.

					csSerNum.SetAt ( k, szBase16Table[i+1] );
					bDone = TRUE;	// Done. Lets blow this popcorn stand.
				}
				else
				{

					// Set current digit to 0 and index to next digit.

					csSerNum.SetAt ( k, '0' );
					k--;
					if ( k < 0 )
					{

						// Roll over condition. Reset serial number.
						csSerNum = "0";
						bDone = TRUE;
					}
					else
					{
						// Go to the next digit and check that.
						// The index to the serial number has been
						// moved to the next digit.

						i = 0;

					}
				}
			}
			else
				i++;
		}	// End while.


		if ( i == MAX_CHAR_16-1 && !bDone )
		{

			// We have trouble. Reset serial number to 0.

			int l;
			l = m_nSNLength - 1;
			while ( l >= 0 )
			{
				csSerNum.SetAt ( l, '0' );
				l--;
			}
			bDone = TRUE;
		}
	}	// End while.


	return ( csSerNum );

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
//		None.
//
//	Return:
//		Incremented string.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

CString CSNManager::IncrementBase31 ( )
{

	CString 
		csTemp,
		csSerialNumber,
		csSerNum;

	int
		i,
		k;

	BOOL
		bDone;


	// Temp serial number must be set to max size.

	csSerialNumber = m_csSerialNumber;

	csSerNum = m_csSerialNumber;

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

	k = m_nSNLength - 1;
	bDone = FALSE;

	while ( k >= 0 && !bDone )
	{

		i = 0;
		while ( i < MAX_CHAR_31-1 && !bDone )
		{
			if ( csSerialNumber.GetAt ( k ) == szBase31Table[i] )
			{
				if ( csSerialNumber.GetAt ( k ) != 'Z' )
				{
					// Current digit.

					// Just increment column to the next character.

					csSerNum.SetAt ( k, szBase31Table[i+1] );
					bDone = TRUE;	// Done. Lets blow this popcorn stand.
				}
				else
				{

					// Set current digit to 0 and index to next digit.

					csSerNum.SetAt ( k, '0' );
					k--;
					if ( k < 0 )
					{

						// Roll over condition. Reset serial number.
						csSerNum = "0";
						bDone = TRUE;
					}
					else
					{
						// Go to the next digit and check that.
						// The index to the serial number has been
						// moved to the next digit.

						i = 0;

					}
				}
			}
			else
				i++;
		}	// End while.


		if ( i == MAX_CHAR_31-1 && !bDone )
		{

			// We have trouble. Reset serial number to 0.

			int l;
			l = m_nSNLength - 1;
			while ( l >= 0 )
			{
				csSerNum.SetAt ( l, '0' );
				l--;
			}
			bDone = TRUE;
		}
	}	// End while.


	return ( csSerNum );

}





/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: IncrementBase36
//
//	Description:
//		Increment a BASE 36 string. Base 31 is 0-9, A-Z.
//
//	Arguments:
//		None.
//
//	Return:
//		Incremented string.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

CString CSNManager::IncrementBase36 ( )
{

	CString 
		csTemp,
		csSerialNumber,
		csSerNum;

	int
		i,
		k;

	BOOL
		bDone;


	// Temp serial number must be set to max size.

	csSerialNumber = m_csSerialNumber;

	csSerNum = m_csSerialNumber;

	// The serial number changes in the following way.
	// 
	// Each column can be incremented by 1 with valid
	// characters of 0 - 9; A - Z. When one column reaches Z ( 36 
	// increments of valid characters ) increment the next
	// column to the left and then start at 0 with the
	// column to the right.

	// Start with the first digit. Bump it up by one character
	// if it doesn't need to be carried over to the next digit.
	// Else, set digit to 0 and bump up the next digit, and so on.

	k = m_nSNLength - 1;
	bDone = FALSE;

	while ( k >= 0 && !bDone )
	{

		i = 0;
		while ( i < MAX_CHAR_36-1 && !bDone )
		{
			if ( csSerialNumber.GetAt ( k ) == szBase36Table[i] )
			{
				if ( csSerialNumber.GetAt ( k ) != 'Z' )
				{
					// Current digit.

					// Just increment column to the next character.

					csSerNum.SetAt ( k, szBase36Table[i+1] );
					bDone = TRUE;	// Done. Lets blow this popcorn stand.
				}
				else
				{

					// Set current digit to 0 and index to next digit.

					csSerNum.SetAt ( k, '0' );
					k--;
					if ( k < 0 )
					{

						// Roll over condition. Reset serial number.
						csSerNum = "0";
						bDone = TRUE;
					}
					else
					{
						// Go to the next digit and check that.
						// The index to the serial number has been
						// moved to the next digit.

						i = 0;

					}
				}
			}
			else
				i++;
		}	// End while.


		if ( i == MAX_CHAR_36-1 && !bDone )
		{

			// We have trouble. Reset serial number to 0.

			int l;
			l = m_nSNLength - 1;
			while ( l >= 0 )
			{
				csSerNum.SetAt ( l, '0' );
				l--;
			}
			bDone = TRUE;
		}
	}	// End while.


	return ( csSerNum );

}





BOOL CSNManager::UseSerialization ( void )
{

	return ( m_bUseSerialization );

}



void CSNManager::SetSerialNumberN ( int nSN, CString csSerialNumber )
{

	switch ( nSN )
	{
		case 1:
			m_csSerialNumber1 = csSerialNumber;
			break;
	
		case 2:
			m_csSerialNumber2 = csSerialNumber;
			break;
	}

}


CString CSNManager::GetSerialNumberN ( int nSN )
{

	CString
		csSerialNumber;


	switch ( nSN )
	{
		case 1:
			csSerialNumber = m_csSerialNumber1;
			break;
	
		case 2:
			csSerialNumber = m_csSerialNumber2;
			break;
	}

	return ( csSerialNumber );

}


CString CSNManager::IncrementBase29()
{

	CString 
		csTemp,
		csSerialNumber,
		csSerNum;

	int
		i,
		k;

	BOOL
		bDone;


	// Temp serial number must be set to max size.

	csSerialNumber = m_csSerialNumber;

	csSerNum = m_csSerialNumber;

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

	k = m_nSNLength - 1;
	bDone = FALSE;

	while ( k >= 0 && !bDone )
	{

		i = 0;
		while ( i < MAX_CHAR_29-1 && !bDone )
		{
			if ( csSerialNumber.GetAt ( k ) == szBase29Table[i] )
			{
				if ( csSerialNumber.GetAt ( k ) != 'Y' )
				{
					// Current digit.

					// Just increment column to the next character.

					csSerNum.SetAt ( k, szBase29Table[i+1] );
					bDone = TRUE;	// Done. Lets blow this popcorn stand.
				}
				else
				{

					// Set current digit to 0 and index to next digit.

					csSerNum.SetAt ( k, '0' );
					k--;
					if ( k < 0 )
					{

						// Roll over condition. Reset serial number.
						csSerNum = "0";
						bDone = TRUE;
					}
					else
					{
						// Go to the next digit and check that.
						// The index to the serial number has been
						// moved to the next digit.

						i = 0;

					}
				}
			}
			else
				i++;
		}	// End while.


		if ( i == MAX_CHAR_29-1 && !bDone )
		{

			// We have trouble. Reset serial number to 0.

			int l;
			l = m_nSNLength - 1;
			while ( l >= 0 )
			{
				csSerNum.SetAt ( l, '0' );
				l--;
			}
			bDone = TRUE;
		}
	}	// End while.


	return ( csSerNum );
}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		IncrementSerialNumber
//
//	Description:
//		Increment the current serial number. Ensure it rolls over at the 
//		proper time.
//
//	Arguments:
//		None.
//
//	Return:
//		Serial number.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

CString CSNManager::DecrementSerialNumber (  CString csJobName  )
{

	CString
		csSerialNumber;


	// Someday:  combine these routines.

	switch ( m_nSNType )
	{
		case BASE10:
			csSerialNumber = DecrementBase10();
			break;

		case BASE16:
			csSerialNumber = DecrementBase16();
			break;

		case BASE29:
			csSerialNumber = DecrementBase29();
			break;

		case BASE31:
			csSerialNumber = IncrementBase31();
			break;

		case BASE36:
			csSerialNumber = IncrementBase36();
			break;

		default:
			break;
	}
	
	
	m_poDatabase->SetStartingSN ( csJobName, csSerialNumber );
	m_csSerialNumber = csSerialNumber;
	return ( csSerialNumber );

}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: DecrementBase10
//
//	Description:
//		Increment a BASE 10 string. Base 10 is 0-9.
//
//	Arguments:
//		None.
//
//	Return:
//		Incremented string.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

CString CSNManager::DecrementBase10 ( )
{

	CString 
		csTemp,
		csSerialNumber,
		csSerNum;

	int
		nTableCharacter,
		nSerialNumberCharacter;

	BOOL
		bDone;


	// Temp serial number must be set to max size.

	csSerialNumber = m_csSerialNumber;

	csSerNum = m_csSerialNumber;

	// The serial number changes in the following way.
	// 
	// Each column can be incremented by 1 with valid
	// characters of 0 - 9. When one column reaches 9 ( 10 
	// increments of valid characters ) increment the next
	// column to the left and then start at 0 with the
	// column to the right.

	// Start with the first digit. decrement it up by one character
	// if it doesn't need to be carried over to the next digit.
	// Else, set digit to 0 and bump up the next digit, and so on.

	nSerialNumberCharacter = m_nSNLength - 1;
	bDone = FALSE;

	while ( nSerialNumberCharacter >= 0 && !bDone )
	{

		nTableCharacter = 0;
		while ( nTableCharacter < MAX_CHAR_10-1 && !bDone ) //reference character in table
		{
			if ( csSerialNumber.GetAt ( nSerialNumberCharacter ) == szBase10Table[nTableCharacter] )
			{
				if ( csSerialNumber.GetAt ( nSerialNumberCharacter ) != '0' )
				{
					// Current digit.

					// Just decrement column to the next character.

					csSerNum.SetAt ( nSerialNumberCharacter, szBase10Table[nTableCharacter-1] );
					bDone = TRUE;	// Done. Lets blow this popcorn stand.
				}
				else
				{

					// Set current digit to 9 and index to next digit.

					csSerNum.SetAt ( nSerialNumberCharacter, szBase10Table[MAX_CHAR_10-2] );
					nSerialNumberCharacter--;
					if ( nSerialNumberCharacter < 0 )
					{

						// Roll over condition. Reset serial number.
						csSerNum = "0";
						bDone = TRUE;
					}
					else
					{
						// Go to the next digit and check that.
						// The index to the serial number has been
						// moved to the next digit.

						nTableCharacter = 0;

					}
				}
			}
			else
				nTableCharacter++;
		}	// End while.


		if ( nTableCharacter == MAX_CHAR_10-1 && !bDone )
		{

			// We have trouble. Reset serial number to 0.

			int l;
			l = m_nSNLength - 1;
			while ( l >= 0 )
			{
				csSerNum.SetAt ( l, '0' );
				l--;
			}
			bDone = TRUE;
		}
	}	// End while.


	return ( csSerNum );

}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: DecrementBase16
//
//	Description:
//		Increment a BASE 16 string. Base 16 is 0-F.
//
//	Arguments:
//		None.
//
//	Return:
//		Incremented string.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

CString CSNManager::DecrementBase16 ( )
{

	CString 
		csTemp,
		csSerialNumber,
		csSerNum;

	int
		nTableCharacter,
		nSerialNumberCharacter;

	BOOL
		bDone;


	// Temp serial number must be set to max size.

	csSerialNumber = m_csSerialNumber;

	csSerNum = m_csSerialNumber;

	// The serial number changes in the following way.
	// 
	// Each column can be incremented by 1 with valid
	// characters of 0 - 9. When one column reaches 9 ( 10 
	// increments of valid characters ) increment the next
	// column to the left and then start at 0 with the
	// column to the right.

	// Start with the first digit. decrement it up by one character
	// if it doesn't need to be carried over to the next digit.
	// Else, set digit to 0 and bump up the next digit, and so on.

	nSerialNumberCharacter = m_nSNLength - 1;
	bDone = FALSE;

	while ( nSerialNumberCharacter >= 0 && !bDone )
	{

		nTableCharacter = 0;
		while ( nTableCharacter < MAX_CHAR_16-1 && !bDone ) //reference character in table
		{
			if ( csSerialNumber.GetAt ( nSerialNumberCharacter ) == szBase16Table[nTableCharacter] )
			{
				if ( csSerialNumber.GetAt ( nSerialNumberCharacter ) != '0' )
				{
					// Current digit.

					// Just decrement column to the next character.

					csSerNum.SetAt ( nSerialNumberCharacter, szBase16Table[nTableCharacter-1] );
					bDone = TRUE;	// Done. Lets blow this popcorn stand.
				}
				else
				{

					// Set current digit to 9 and index to next digit.

					csSerNum.SetAt ( nSerialNumberCharacter, szBase16Table[MAX_CHAR_16-2] );
					nSerialNumberCharacter--;
					if ( nSerialNumberCharacter < 0 )
					{

						// Roll over condition. Reset serial number.
						csSerNum = "0";
						bDone = TRUE;
					}
					else
					{
						// Go to the next digit and check that.
						// The index to the serial number has been
						// moved to the next digit.

						nTableCharacter = 0;

					}
				}
			}
			else
				nTableCharacter++;
		}	// End while.


		if ( nTableCharacter == MAX_CHAR_16-1 && !bDone )
		{

			// We have trouble. Reset serial number to 0.

			int l;
			l = m_nSNLength - 1;
			while ( l >= 0 )
			{
				csSerNum.SetAt ( l, '0' );
				l--;
			}
			bDone = TRUE;
		}
	}	// End while.


	return ( csSerNum );

}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: DecrementBase29
//
//	Description:
//		Increment a BASE 16 string. Base 16 is 0-F.
//
//	Arguments:
//		None.
//
//	Return:
//		Incremented string.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

CString CSNManager::DecrementBase29 ( )
{

	CString 
		csTemp,
		csSerialNumber,
		csSerNum;

	int
		nTableCharacter,
		nSerialNumberCharacter;

	BOOL
		bDone;


	// Temp serial number must be set to max size.

	csSerialNumber = m_csSerialNumber;

	csSerNum = m_csSerialNumber;

	// The serial number changes in the following way.
	// 
	// Each column can be incremented by 1 with valid
	// characters of 0 - 9. When one column reaches 9 ( 10 
	// increments of valid characters ) increment the next
	// column to the left and then start at 0 with the
	// column to the right.

	// Start with the first digit. decrement it up by one character
	// if it doesn't need to be carried over to the next digit.
	// Else, set digit to 0 and bump up the next digit, and so on.

	nSerialNumberCharacter = m_nSNLength - 1;
	bDone = FALSE;

	while ( nSerialNumberCharacter >= 0 && !bDone )
	{

		nTableCharacter = 0;
		while ( nTableCharacter < MAX_CHAR_29-1 && !bDone ) //reference character in table
		{
			if ( csSerialNumber.GetAt ( nSerialNumberCharacter ) == szBase29Table[nTableCharacter] )
			{
				if ( csSerialNumber.GetAt ( nSerialNumberCharacter ) != '0' )
				{
					// Current digit.

					// Just decrement column to the next character.

					csSerNum.SetAt ( nSerialNumberCharacter, szBase29Table[nTableCharacter-1] );
					bDone = TRUE;	// Done. Lets blow this popcorn stand.
				}
				else
				{

					// Set current digit to 9 and index to next digit.

					csSerNum.SetAt ( nSerialNumberCharacter, szBase29Table[MAX_CHAR_29-2] );
					nSerialNumberCharacter--;
					if ( nSerialNumberCharacter < 0 )
					{

						// Roll over condition. Reset serial number.
						csSerNum = "0";
						bDone = TRUE;
					}
					else
					{
						// Go to the next digit and check that.
						// The index to the serial number has been
						// moved to the next digit.

						nTableCharacter = 0;

					}
				}
			}
			else
				nTableCharacter++;
		}	// End while.


		if ( nTableCharacter == MAX_CHAR_29-1 && !bDone )
		{

			// We have trouble. Reset serial number to 0.

			int l;
			l = m_nSNLength - 1;
			while ( l >= 0 )
			{
				csSerNum.SetAt ( l, '0' );
				l--;
			}
			bDone = TRUE;
		}
	}	// End while.


	return ( csSerNum );

}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: DecrementBase31
//
//	Description:
//		Increment a BASE 31 string. Base 31 is 0-F.
//
//	Arguments:
//		None.
//
//	Return:
//		Incremented string.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

CString CSNManager::DecrementBase31 ( )
{

	CString 
		csTemp,
		csSerialNumber,
		csSerNum;

	int
		nTableCharacter,
		nSerialNumberCharacter;

	BOOL
		bDone;


	// Temp serial number must be set to max size.

	csSerialNumber = m_csSerialNumber;

	csSerNum = m_csSerialNumber;

	// The serial number changes in the following way.
	// 
	// Each column can be incremented by 1 with valid
	// characters of 0 - 9. When one column reaches 9 ( 10 
	// increments of valid characters ) increment the next
	// column to the left and then start at 0 with the
	// column to the right.

	// Start with the first digit. decrement it up by one character
	// if it doesn't need to be carried over to the next digit.
	// Else, set digit to 0 and bump up the next digit, and so on.

	nSerialNumberCharacter = m_nSNLength - 1;
	bDone = FALSE;

	while ( nSerialNumberCharacter >= 0 && !bDone )
	{

		nTableCharacter = 0;
		while ( nTableCharacter < MAX_CHAR_31-1 && !bDone ) //reference character in table
		{
			if ( csSerialNumber.GetAt ( nSerialNumberCharacter ) == szBase31Table[nTableCharacter] )
			{
				if ( csSerialNumber.GetAt ( nSerialNumberCharacter ) != '0' )
				{
					// Current digit.

					// Just decrement column to the next character.

					csSerNum.SetAt ( nSerialNumberCharacter, szBase31Table[nTableCharacter-1] );
					bDone = TRUE;	// Done. Lets blow this popcorn stand.
				}
				else
				{

					// Set current digit to 9 and index to next digit.

					csSerNum.SetAt ( nSerialNumberCharacter, szBase31Table[MAX_CHAR_31-2] );
					nSerialNumberCharacter--;
					if ( nSerialNumberCharacter < 0 )
					{

						// Roll over condition. Reset serial number.
						csSerNum = "0";
						bDone = TRUE;
					}
					else
					{
						// Go to the next digit and check that.
						// The index to the serial number has been
						// moved to the next digit.

						nTableCharacter = 0;

					}
				}
			}
			else
				nTableCharacter++;
		}	// End while.


		if ( nTableCharacter == MAX_CHAR_31-1 && !bDone )
		{

			// We have trouble. Reset serial number to 0.

			int l;
			l = m_nSNLength - 1;
			while ( l >= 0 )
			{
				csSerNum.SetAt ( l, '0' );
				l--;
			}
			bDone = TRUE;
		}
	}	// End while.


	return ( csSerNum );

}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: DecrementBase36
//
//	Description:
//		Increment a BASE 36 string. Base 36 is 0-F.
//
//	Arguments:
//		None.
//
//	Return:
//		Incremented string.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

CString CSNManager::DecrementBase36 ( )
{

	CString 
		csTemp,
		csSerialNumber,
		csSerNum;

	int
		nTableCharacter,
		nSerialNumberCharacter;

	BOOL
		bDone;


	// Temp serial number must be set to max size.

	csSerialNumber = m_csSerialNumber;

	csSerNum = m_csSerialNumber;

	// The serial number changes in the following way.
	// 
	// Each column can be incremented by 1 with valid
	// characters of 0 - 9. When one column reaches 9 ( 10 
	// increments of valid characters ) increment the next
	// column to the left and then start at 0 with the
	// column to the right.

	// Start with the first digit. decrement it up by one character
	// if it doesn't need to be carried over to the next digit.
	// Else, set digit to 0 and bump up the next digit, and so on.

	nSerialNumberCharacter = m_nSNLength - 1;
	bDone = FALSE;

	while ( nSerialNumberCharacter >= 0 && !bDone )
	{

		nTableCharacter = 0;
		while ( nTableCharacter < MAX_CHAR_36-1 && !bDone ) //reference character in table
		{
			if ( csSerialNumber.GetAt ( nSerialNumberCharacter ) == szBase36Table[nTableCharacter] )
			{
				if ( csSerialNumber.GetAt ( nSerialNumberCharacter ) != '0' )
				{
					// Current digit.

					// Just decrement column to the next character.

					csSerNum.SetAt ( nSerialNumberCharacter, szBase36Table[nTableCharacter-1] );
					bDone = TRUE;	// Done. Lets blow this popcorn stand.
				}
				else
				{

					// Set current digit to 9 and index to next digit.

					csSerNum.SetAt ( nSerialNumberCharacter, szBase36Table[MAX_CHAR_36-2] );
					nSerialNumberCharacter--;
					if ( nSerialNumberCharacter < 0 )
					{

						// Roll over condition. Reset serial number.
						csSerNum = "0";
						bDone = TRUE;
					}
					else
					{
						// Go to the next digit and check that.
						// The index to the serial number has been
						// moved to the next digit.

						nTableCharacter = 0;

					}
				}
			}
			else
				nTableCharacter++;
		}	// End while.


		if ( nTableCharacter == MAX_CHAR_36-1 && !bDone )
		{

			// We have trouble. Reset serial number to 0.

			int l;
			l = m_nSNLength - 1;
			while ( l >= 0 )
			{
				csSerNum.SetAt ( l, '0' );
				l--;
			}
			bDone = TRUE;
		}
	}	// End while.


	return ( csSerNum );

}
