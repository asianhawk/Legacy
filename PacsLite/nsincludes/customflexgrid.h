#ifndef __CUSTOMFLEXGRID_H_
#define __CUSTOMFLEXGRID_H_


#define	  MAXCOLUMNS	20	

#include "definitions.h"


class AFX_MFC_EXT_TYPE CMSFlexGrid : public CWnd
{
protected:
	DECLARE_DYNCREATE(CMSFlexGrid)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x6262d3a0, 0x531b, 0x11cf, { 0x91, 0xf6, 0xc2, 0x86, 0x3c, 0x38, 0x5e, 0x30 } };
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
	long GetRows();
	void SetRows(long nNewValue);
	long GetCols();
	void SetCols(long nNewValue);
	long GetFixedRows();
	void SetFixedRows(long nNewValue);
	long GetFixedCols();
	void SetFixedCols(long nNewValue);
	short GetVersion();
	CString GetFormatString();
	void SetFormatString(LPCTSTR lpszNewValue);
	long GetTopRow();
	void SetTopRow(long nNewValue);
	long GetLeftCol();
	void SetLeftCol(long nNewValue);
	long GetRow();
	void SetRow(long nNewValue);
	long GetCol();
	void SetCol(long nNewValue);
	long GetRowSel();
	void SetRowSel(long nNewValue);
	long GetColSel();
	void SetColSel(long nNewValue);
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	unsigned long GetBackColor();
	void SetBackColor(unsigned long newValue);
	unsigned long GetForeColor();
	void SetForeColor(unsigned long newValue);
	unsigned long GetBackColorFixed();
	void SetBackColorFixed(unsigned long newValue);
	unsigned long GetForeColorFixed();
	void SetForeColorFixed(unsigned long newValue);
	unsigned long GetBackColorSel();
	void SetBackColorSel(unsigned long newValue);
	unsigned long GetForeColorSel();
	void SetForeColorSel(unsigned long newValue);
	unsigned long GetBackColorBkg();
	void SetBackColorBkg(unsigned long newValue);
	BOOL GetWordWrap();
	void SetWordWrap(BOOL bNewValue);
	LPDISPATCH GetFont();
	void SetRefFont(LPDISPATCH newValue);
	float GetFontWidth();
	void SetFontWidth(float newValue);
	CString GetCellFontName();
	void SetCellFontName(LPCTSTR lpszNewValue);
	float GetCellFontSize();
	void SetCellFontSize(float newValue);
	BOOL GetCellFontBold();
	void SetCellFontBold(BOOL bNewValue);
	BOOL GetCellFontItalic();
	void SetCellFontItalic(BOOL bNewValue);
	BOOL GetCellFontUnderline();
	void SetCellFontUnderline(BOOL bNewValue);
	BOOL GetCellFontStrikeThrough();
	void SetCellFontStrikeThrough(BOOL bNewValue);
	float GetCellFontWidth();
	void SetCellFontWidth(float newValue);
	long GetTextStyle();
	void SetTextStyle(long nNewValue);
	long GetTextStyleFixed();
	void SetTextStyleFixed(long nNewValue);
	BOOL GetScrollTrack();
	void SetScrollTrack(BOOL bNewValue);
	long GetFocusRect();
	void SetFocusRect(long nNewValue);
	long GetHighLight();
	void SetHighLight(long nNewValue);
	BOOL GetRedraw();
	void SetRedraw(BOOL bNewValue);
	long GetScrollBars();
	void SetScrollBars(long nNewValue);
	long GetMouseRow();
	long GetMouseCol();
	long GetCellLeft();
	long GetCellTop();
	long GetCellWidth();
	long GetCellHeight();
	long GetRowHeightMin();
	void SetRowHeightMin(long nNewValue);
	long GetFillStyle();
	void SetFillStyle(long nNewValue);
	long GetGridLines();
	void SetGridLines(long nNewValue);
	long GetGridLinesFixed();
	void SetGridLinesFixed(long nNewValue);
	unsigned long GetGridColor();
	void SetGridColor(unsigned long newValue);
	unsigned long GetGridColorFixed();
	void SetGridColorFixed(unsigned long newValue);
	unsigned long GetCellBackColor();
	void SetCellBackColor(unsigned long newValue);
	unsigned long GetCellForeColor();
	void SetCellForeColor(unsigned long newValue);
	short GetCellAlignment();
	void SetCellAlignment(short nNewValue);
	long GetCellTextStyle();
	void SetCellTextStyle(long nNewValue);
	short GetCellPictureAlignment();
	void SetCellPictureAlignment(short nNewValue);
	CString GetClip();
	void SetClip(LPCTSTR lpszNewValue);
	void SetSort(short nNewValue);
	long GetSelectionMode();
	void SetSelectionMode(long nNewValue);
	long GetMergeCells();
	void SetMergeCells(long nNewValue);
	BOOL GetAllowBigSelection();
	void SetAllowBigSelection(BOOL bNewValue);
	long GetAllowUserResizing();
	void SetAllowUserResizing(long nNewValue);
	long GetBorderStyle();
	void SetBorderStyle(long nNewValue);
	long GetHWnd();
	BOOL GetEnabled();
	void SetEnabled(BOOL bNewValue);
	long GetAppearance();
	void SetAppearance(long nNewValue);
	long GetMousePointer();
	void SetMousePointer(long nNewValue);
	LPDISPATCH GetMouseIcon();
	void SetRefMouseIcon(LPDISPATCH newValue);
	long GetPictureType();
	void SetPictureType(long nNewValue);
	LPDISPATCH GetPicture();
	LPDISPATCH GetCellPicture();
	void SetRefCellPicture(LPDISPATCH newValue);
	CString GetTextArray(long index);
	void SetTextArray(long index, LPCTSTR lpszNewValue);
	short GetColAlignment(long index);
	void SetColAlignment(long index, short nNewValue);
	long GetColWidth(long index);
	void SetColWidth(long index, long nNewValue);
	long GetRowHeight(long index);
	void SetRowHeight(long index, long nNewValue);
	BOOL GetMergeRow(long index);
	void SetMergeRow(long index, BOOL bNewValue);
	BOOL GetMergeCol(long index);
	void SetMergeCol(long index, BOOL bNewValue);
	void SetRowPosition(long index, long nNewValue);
	void SetColPosition(long index, long nNewValue);
	long GetRowData(long index);
	void SetRowData(long index, long nNewValue);
	long GetColData(long index);
	void SetColData(long index, long nNewValue);
	CString GetTextMatrix(long Row, long Col);
	void SetTextMatrix(long Row, long Col, LPCTSTR lpszNewValue);
	void AddItem(LPCTSTR Item, const VARIANT& index);
	void RemoveItem(long index);
	void Clear();
	void Refresh();
	LPDISPATCH GetDataSource();
	void SetDataSource(LPDISPATCH newValue);
	BOOL GetRowIsVisible(long index);
	BOOL GetColIsVisible(long index);
	long GetRowPos(long index);
	long GetColPos(long index);
	short GetGridLineWidth();
	void SetGridLineWidth(short nNewValue);
	short GetFixedAlignment(long index);
	void SetFixedAlignment(long index, short nNewValue);
	BOOL GetRightToLeft();
	void SetRightToLeft(BOOL bNewValue);
	long GetOLEDropMode();
	void SetOLEDropMode(long nNewValue);
	void OLEDrag();
};




class DllExport CCHKBUTTON : public CButton
{
// Construction
public:
	CCHKBUTTON();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCHKBUTTON)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCHKBUTTON();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCHKBUTTON)
	afx_msg void OnClicked();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

class DllExport CEditWnd : public CEdit
{
// Construction
public:
	CEditWnd();
 


// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditWnd)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};



class DllExport CFlexGrid : public CMSFlexGrid
{
public:	
	CFlexGrid();	
	CString GetData(int nAtRow, int nAtCol);
	CString GetTextData(int nAtRow, int nAtCol);
	void SetTextData(int nAtRow, int nAtCol, CString csTextData);
	void InitFlexGrid(int nNoOfRows, int nNoOfCols);
	void InitFlexGrid(int nNoOfFixedRows,
		 			  int nNoOfFixedColumns,
					  int nNoOfRows, int nNoOfCols);

	int     GetColumnHeadersCount();
	void	AddColumnHeaders(CString csHeader);
	void	AddFixedRowHeaders(CString csHeader);
	void	ResetHeaderColumnsCount();
	void	ResetFixedRowsCount();
	int		FindString(CString csSearch, int nColumn);
	void	SetDataCursor(int nAtRow);

	BOOL	GetAllowEditing();
	void	SetAllowEditing(BOOL blnPermission);
	void	Sort(int nCriteria, int nType);
	void	Sort();
	void	AppendString(CString csBuffer);
	long	GetActiveRowCount();

	// Experimental
		virtual void PreSubclassWindow();
      CEditWnd m_edit;
	  CCHKBUTTON m_btnData1;
	  CCHKBUTTON	m_btnUsedChkBox[5];
	  CCHKBUTTON	m_btnPrintedChkBox[5];
	  CCHKBUTTON	m_btnLoggedChkBox[5];
	  CCHKBUTTON	m_btnScanChkBox[100];
	  BOOL GetFixedColumnStatus();	
	  void SetFixedColumnStatus(BOOL blnStatus);

	  BOOL GetFixedRowStatus();	
	  void SetFixedRowStatus(BOOL blnStatus);

      long	m_lCHKBorderWidth;
      long	m_lCHKBorderHeight;
	  int m_nCHKLogY;
	  int m_nCHKLogX;
	  int m_nScanChkBoxCount;
	  void CreateChkBoxes(int nRow, int nCol);
	  void CreateUsedChkBoxes(int nIndex, int nRow, int nCol);
	  void CreatePrintedChkBoxes(int nIndex, int nRow, int nCol);
	  void CreateLoggedChkBoxes(int nIndex, int nRow, int nCol);
	  void AddScanCheckBox(int nIndex, int nRow, int nCol);
	  void SetEditBkgColor();
	  void RestoreBkgColor();
	  void TabRight();



	  void UpdateRow(int nRow, CString csBuffer);
	  
	  
	  long m_lBorderWidth; 
      long m_lBorderHeight;

	  long m_lGridWidth;

	  int m_nLogY;
	  int m_nLogX;
	
	  BOOL m_blnSortData;	
	  long m_nSortOnColumn;
	  long m_nSortType;


      afx_msg void OnKeyPressGrid(short FAR* KeyAscii);
      afx_msg void OnDblClickGrid();
      afx_msg void OnUpdateGrid();

      DECLARE_EVENTSINK_MAP()

	//{{AFX_MSG(CFlexGrid)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	int		m_nColumnHeaderCount;
	int		m_nRowHeaderCount;
	BOOL	m_blnAllowEditing;
	BOOL	m_blnFixedColumnsAreDefined;
	BOOL	m_blnFixedRowsAreDefined;

	unsigned long m_lBackGrdColor;
	unsigned long m_lHighLightColor;

};


#endif
