// CheckDgt.h : main header file for the CHECKDGT DLL
// $History: CheckDgt.h $
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

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCheckDgtApp
// See CheckDgt.cpp for the implementation of this class
//

class CCheckDgtApp : public CWinApp
{
public:
	CCheckDgtApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckDgtApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CCheckDgtApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

const CString	c_csInvalid = "Invalid Message";
const CString	c_csZero = "0";
const CString	c_csDoubleZero = "00";
const CString	c_csNothing = "";

// Main routine which maps to the correct check digit routine
int GetCheckDigit(char * Msg, char * Routine, char * ChkDig);


// Check routine for CHK001
CString CHK001(CString & numstr);
// Check routine for CHK002 - Mod 11 English Version
CString CHK002(CString & numstr);
// Check routine for CHK003
CString CHK003(CString & numstr);
// Check routine for CHK004
CString CHK004(CString & numstr);
// Check routine for CHK005
CString CHK005(CString & numstr);
// Check routine for CHK006
CString CHK006(CString & numstr);
// Check routine for Modulus 10
CString CHK007(CString & numstr);
// Check routine for Modulus 43
CString CHK008(CString & numstr);
// Check routine for M10DAD
CString CHK009(CString & numstr);
// Check routine for M10TAT
CString CHK010(CString & numstr);
// Check routine for GIM10W
CString CHK011(CString & numstr);
// Check routine for DRC001
CString CHK012(CString & numstr);
// Check routine for CHK014
CString CHK014(CString & numstr);
// Check routine for CHK015
CString CHK015(CString & numstr);
// Check routine for CHK016
CString CHK016(CString & numstr);
// Check routine for CHK017 - Mod 11 French Version
CString CHK017(CString & numstr);
// Check routine for CHK018
CString CHK018(CString & numstr);
// Check routine for CHK019
CString CHK019(CString & numstr);
// Check routine for CHK020
CString CHK020(CString & numstr);
// Check routine for CHK021
CString CHK021(CString & numstr);
// Check routine for CHK022
CString CHK022(CString & numstr);
// Check routine for Mod 10 weighted R->L  1,2,3,7,9....
CString CHK023(CString & numstr);
// Check routine for Mod 31 table weighted
CString CHK024(CString & numstr);
// Check routine for Mod 7 (not weighted)
CString CHK025(CString & numstr);
// Check routine for CHK026
CString CHK026(CString & numstr);
// Check routine for Mod 11 weight R->L  2,3,4,5,6,7....
CString CHK027(CString & numstr);
// Check routine for special Mod 10 Double Add Double
CString CHK028(CString & numstr);
// Check routine for CHK029
CString CHK029(CString & numstr);
// Check routine for CHK030 
CString CHK030(CString & numstr);
// Check routine for CHK031 
CString CHK031(CString & numstr);
// Check routine for CHK032
CString CHK032(CString & numstr);
// Check routine for CHK033 
CString CHK033(CString & numstr);
// Check routine for CHK034 
CString CHK034(CString & numstr);
// Check routine for CHK035 
CString CHK035(CString & numstr);
// Check routine for CHK036
CString CHK036(CString & numstr);
// Check routine for CHK037
CString CHK037(CString & numstr);
// Check routine for CHK038
CString CHK038(CString & numstr);
// Check routine for CHK039
CString CHK039(CString & numstr);
// Check routine for CHK040
CString CHK040(CString & numstr);
// Check routine for CHK041 - Mod 11 weighted L->R  3,1,7,9....
CString CHK041(CString & numstr);
// Check routine for CHK042
CString CHK042(CString & numstr);
// Check routine for CHK043
CString CHK043(CString & numstr);
// Check routine for CHK044
CString CHK044(CString & numstr);
// Check routine for CHK44B
CString CHK44B(CString & numstr);
// Check routine for CHK045
CString CHK045(CString & numstr);
// Check routine for CHK046
CString CHK046(CString & numstr);
// Check routine for CHK047
CString CHK047(CString & numstr);
// Check routine for CHK048
CString CHK048(CString & numstr);
// Check routine for CHK049
CString CHK049(CString & numstr);
// Check routine for CHK050
CString CHK050(CString & numstr);
// Check routine for CHK051
CString CHK051(CString & numstr);
// Check routine for CHK052
CString CHK052(CString & numstr);
// Check routine for CHK053
CString CHK053(CString & numstr);
// Check routine for CHK054
CString CHK054(CString & numstr);
// Check routine for CHK055
CString CHK055(CString & numstr);
// Check routine for CHK056
CString CHK056(CString & numstr);
// Check routine for CHK057
CString CHK057(CString & numstr);
// Check routine for CHK058
CString CHK058(CString & numstr);
// Check routine for CHK059
CString CHK059(CString & numstr);
// Check routine for CHK060
CString CHK060(CString & numstr);
// Check routine for CHK062
CString CHK062(CString & numstr);
// Check routine for CHK063
CString CHK063(CString & numstr);
// Check routine for CHK064
CString CHK064(CString & numstr);
// Check routine for CHK065
CString CHK065(CString & numstr);
// Check routine for CHK066
CString CHK066(CString & numstr);
// Check routine for CHK067
CString CHK067(CString & numstr);
// Check routine for CHK068
CString CHK068(CString & numstr);
// Check routine for CHK069
CString CHK069(CString & numstr);
// Check routine for CHK070
CString CHK070(CString & numstr);
// Check routine for CHK072
CString CHK072(CString & numstr);
// Check routine for CHK073
CString CHK073(CString & numstr);
// Check routine for CHK074
CString CHK074(CString & numstr);
// Check routine for CHK075
CString CHK075(CString & numstr);
// Check routine for CHK076
CString CHK076(CString & numstr);
// Check routine for CHK077
CString CHK077(CString & numstr);
// Check routine for CHK078
CString CHK078(CString & numstr);
// Check routine for CHK079 - Mod 97 weighted R->L  2,3,4,5,6,7...
CString CHK079(CString & numstr);
// Check routine for CHK080
CString CHK080(CString & numstr);
// Check routine for CHK081
CString CHK081(CString & numstr);
// Check routine for CHK082
CString CHK082(CString & numstr);
// Check routine for CHK083
CString CHK083(CString & numstr);
// Check routine for CHK084
CString CHK084(CString & numstr);
// Check routine for CHK085
CString CHK085(CString & numstr);
// Check routine for CHK086
CString CHK086(CString & numstr);
// Check routine for CHK087 - ISO 7064, Mod 37-2
CString CHK087(CString & numstr);
// Check routine for CHK088
CString CHK088(CString & numstr);
// Check routine for CHK089 - Mod 11, weight R->L { 1,2,3,4,5,6,7,8,9,10 }
CString CHK089(CString & numstr);
// Check routine for CHK090
CString CHK090(CString & numstr);
// Check routine for CHK091
CString CHK091(CString & numstr);
// Check routine for CHK092
CString CHK092(CString & numstr);
// Check routine for CHK093
CString CHK093(CString & numstr);
// Check routine for CHK094
CString CHK094(CString & numstr);
// Check routine for CHK095
CString CHK095(CString & numstr);
// Check routine for CHK096
CString CHK096(CString & numstr);
// Check routine for CHK097
CString CHK097(CString & numstr);
// Check routine for CHK098 - next highest power of 10 - ((sum of odd digits * 3) + (sum of even digits))
CString CHK098(CString & numstr);
// Check routine for CHK099 - Mod 10, weight R->L { 3,9,7,1 }
CString CHK099(CString & numstr);
// Check routine for CHK100
CString CHK100(CString & numstr);
// Check routine for CHK101
CString CHK101(CString & numstr);
// Check routine for CHK102
CString CHK102(CString & numstr);
// Check routine for CHK103
CString CHK103(CString & numstr);
// Check routine for CHK104
CString CHK104(CString & numstr);
// Check routine for CHK105
CString CHK105(CString & numstr);

// Check routine for SFM
CString SFM(CString & numstr);



// Routine to check to see if the input check routine is supported
int IsSupported(char * Routine);