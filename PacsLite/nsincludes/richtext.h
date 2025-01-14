#if !defined(AFX_RICHTEXT_H__C770E226_9E4D_11D2_A2AB_006008043EC4__INCLUDED_)
#define AFX_RICHTEXT_H__C770E226_9E4D_11D2_A2AB_006008043EC4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class COleFont;
class CPicture;
class COLEObjects;

/////////////////////////////////////////////////////////////////////////////
// CRichText wrapper class



#include "definitions.h"

class AFX_MFC_EXT_TYPE CRichText : public CWnd
{
protected:
	DECLARE_DYNCREATE(CRichText)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x3b7c8860, 0xd78f, 0x101b, { 0xb9, 0xb5, 0x4, 0x2, 0x1c, 0x0, 0x94, 0x2 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:

// Operations
public:
	long GetAppearance();
	void SetAppearance(long nNewValue);
	unsigned long GetBackColor();
	void SetBackColor(unsigned long newValue);
	long GetBorderStyle();
	void SetBorderStyle(long nNewValue);
	float GetBulletIndent();
	void SetBulletIndent(float newValue);
	BOOL GetDisableNoScroll();
	void SetDisableNoScroll(BOOL bNewValue);
	BOOL GetEnabled();
	void SetEnabled(BOOL bNewValue);
	CString GetFileName();
	void SetFileName(LPCTSTR lpszNewValue);
	COleFont GetFont();
	void SetRefFont(LPDISPATCH newValue);
	BOOL GetHideSelection();
	void SetHideSelection(BOOL bNewValue);
	long GetHwnd();
	void SetHwnd(long nNewValue);
	BOOL GetLocked();
	void SetLocked(BOOL bNewValue);
	long GetMaxLength();
	void SetMaxLength(long nNewValue);
	CPicture GetMouseIcon();
	void SetMouseIcon(LPDISPATCH newValue);
	void SetRefMouseIcon(LPDISPATCH newValue);
	long GetMousePointer();
	void SetMousePointer(long nNewValue);
	BOOL GetMultiLine();
	void SetMultiLine(BOOL bNewValue);
	float GetRightMargin();
	void SetRightMargin(float newValue);
	long GetScrollBars();
	void SetScrollBars(long nNewValue);
	VARIANT GetSelAlignment();
	void SetSelAlignment(const VARIANT& newValue);
	VARIANT GetSelBold();
	void SetSelBold(const VARIANT& newValue);
	VARIANT GetSelBullet();
	void SetSelBullet(const VARIANT& newValue);
	VARIANT GetSelCharOffset();
	void SetSelCharOffset(const VARIANT& newValue);
	VARIANT GetSelColor();
	void SetSelColor(const VARIANT& newValue);
	VARIANT GetSelFontName();
	void SetSelFontName(const VARIANT& newValue);
	VARIANT GetSelFontSize();
	void SetSelFontSize(const VARIANT& newValue);
	VARIANT GetSelHangingIndent();
	void SetSelHangingIndent(const VARIANT& newValue);
	VARIANT GetSelIndent();
	void SetSelIndent(const VARIANT& newValue);
	VARIANT GetSelItalic();
	void SetSelItalic(const VARIANT& newValue);
	long GetSelLength();
	void SetSelLength(long nNewValue);
	VARIANT GetSelProtected();
	void SetSelProtected(const VARIANT& newValue);
	VARIANT GetSelRightIndent();
	void SetSelRightIndent(const VARIANT& newValue);
	CString GetSelRTF();
	void SetSelRTF(LPCTSTR lpszNewValue);
	long GetSelStart();
	void SetSelStart(long nNewValue);
	VARIANT GetSelStrikeThru();
	void SetSelStrikeThru(const VARIANT& newValue);
	VARIANT GetSelTabCount();
	void SetSelTabCount(const VARIANT& newValue);
	CString GetSelText();
	void SetSelText(LPCTSTR lpszNewValue);
	VARIANT GetSelUnderline();
	void SetSelUnderline(const VARIANT& newValue);
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	CString GetTextRTF();
	void SetTextRTF(LPCTSTR lpszNewValue);
	COLEObjects GetOLEObjects();
	BOOL GetAutoVerbMenu();
	void SetAutoVerbMenu(BOOL bNewValue);
	long GetOLEDragMode();
	void SetOLEDragMode(long nNewValue);
	long GetOLEDropMode();
	void SetOLEDropMode(long nNewValue);
	long Find(LPCTSTR bstrString, const VARIANT& vStart, const VARIANT& vEnd, const VARIANT& vOptions);
	long GetLineFromChar(long lChar);
	void LoadFile(LPCTSTR bstrFilename, const VARIANT& vFileType);
	void Refresh();
	void SaveFile(LPCTSTR bstrFilename, const VARIANT& vFlags);
	void SelPrint(long lHDC);
	VARIANT GetSelTabs(short sElement);
	void SetSelTabs(short sElement, const VARIANT& newValue);
	void Span(LPCTSTR bstrCharacterSet, const VARIANT& vForward, const VARIANT& vNegate);
	void UpTo(LPCTSTR bstrCharacterSet, const VARIANT& vForward, const VARIANT& vNegate);
	void OLEDrag();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RICHTEXT_H__C770E226_9E4D_11D2_A2AB_006008043EC4__INCLUDED_)
