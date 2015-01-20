//  SeqMath.h - header file for math functions for CString objects
// $History: SeqMath.h $
//
//*****************  Version 3  *****************
//User: Neil.vaneps  Date: 10/10/00   Time: 9:32a
//Updated in $/C++ Code/CheckDgt DLL
//Fixed keyword comment bug.
//
//*****************  Version 2  *****************
//User: Neil.vaneps  Date: 10/06/00   Time: 11:43a
//Updated in $/C++ Code/CheckDgt DLL
//Enabled history-keyword expansion.

// Trim off any leading or trailing blanks from a CString object
void Trim(CString & s);

// Convert a character array to a CString object
void CnvrtStr(char str[], int len, CString & s);

// Add two CString objects
CString AddCStrs(CString & Num1,CString & Num2);

// Add two CString Float objects
CString AddCStrsFL(CString & Num1, CString & Num2);

// Subtract two CString objects.  N1 and N2 are
// positive and N1 is greater than N2
CString SubCStrs(CString & N1, CString & N2);

// Subtract two CString Float objects.  N1 and N2 are
// positive floats.
CString SubCStrsFL(CString & N1, CString & N2);

// Multiply two CString objects
CString MultCStrs(CString & Num1, CString & Num2);

// Multiply two CString Float objects
CString MultCStrsFL(CString & Num1, CString & Num2);

// Divide two CString objects
// INPUT:    Dividend and Divisor
// OUTPUT:	 Quotient and Remainder
//           0 is returned if Dividend and Divisor are equal
//           1 is returned if Dividend > Divisor
//           2 is returned if Dividend < Divisor
int DivCStrs(CString & Dividend, CString & Divisor, CString & Quotient, CString & Remainder);

// Divide two CString Float objects
// INPUT:   Dividend and Divisor
// OUTPUT:  Quotient as a Float CString
CString DivCStrsFL(CString & Dividend, CString & Divisor);


// Compare two CString base 10 objects and return:
//    0 if equal
//    1 if Num1 > Num2
//    2 if Num2 > Num1
int Compare(CString & Num1, CString & Num2);

// Compare two CString Float base 10 objects and return:
//    0 if equal
//    1 if Num1 > Num2
//    2 if Num2 > Num1
int CompareFL(CString & Num1, CString & Num2);

