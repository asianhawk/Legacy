//CAutoFont class definition
//
//This class will simplify the creation and use of the CFont object
//By Jamie Nordmeyer

#ifndef AUTOFONT
#define AUTOFONT


#include "definitions.h"

class AFX_MFC_EXT_TYPE CAutoFont : public CFont
{
private:
	LOGFONT lf;//Stores this fonts LogFont for quick retrieval
	CString GetToken(CString& str, LPCTSTR c);//Used in Expand function

public:
	CAutoFont();//Default Constructor
	CAutoFont(CString facename);//Font name constructor
	CAutoFont(LOGFONT& logfont);//LogFont constructor
	CAutoFont(CFont font);//Constructs font based on existing font
	~CAutoFont();//Destructor

	LONG SetHeight(LONG height);
	LONG SetWidth(LONG width);
	LONG SetEscapement(LONG esc);
	LONG SetOrientation(LONG or);
	LONG SetWeight(LONG weight);
	BYTE SetCharset(BYTE charset);
	BYTE SetOutPrecision(BYTE op);
	BYTE SetClipPrecision(BYTE cp);
	BYTE SetQuality(BYTE qual);
	BYTE SetPitchAndFamily(BYTE paf);
	CString SetFaceName(CString facename);
	LPCTSTR SetFaceName(LPCTSTR facename);
	BOOL SetBold(BOOL B);
	BOOL SetItalic(BOOL i);
	BOOL SetUnderline(BOOL u);
	BOOL SetStrikeOut(BOOL s);
	void SetLogFont(LOGFONT& logfont);

	LONG GetHeight();
	LONG GetWidth();
	LONG GetEscapement();
	LONG GetOrientation();
	LONG GetWeight();
	BYTE GetCharset();
	BYTE GetOutPrecision();
	BYTE GetClipPrecision();
	BYTE GetQuality();
	BYTE GetPitchAndFamily();
	LPCTSTR GetFaceName();
	BOOL GetBold();
	BOOL GetItalic();
	BOOL GetUnderline();
	BOOL GetStrikeOut();
	//GetLogFont is a member of CFont, and is used as normal.

	//These two functions are good for registry...
	CString ContractFont();//Places font info into single string
	void ExtractFont(CString& str);//Parses single string font info.
};

#endif