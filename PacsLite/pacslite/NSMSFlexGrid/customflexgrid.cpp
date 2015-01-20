#include "stdafx.h"
#include "customflexgrid.h"

#define MINROWNUMBER	4
#define MAXLABELPERBRDNUMBER	300

CFlexGrid::CFlexGrid()
{
	ResetHeaderColumnsCount();
	ResetFixedRowsCount();
	SetAllowEditing(FALSE);
    m_blnSortData=FALSE;	
    m_nSortOnColumn=0;		//default to col 1
	m_nSortType=1;			//default to Ascending
	m_nScanChkBoxCount=0;

	m_lBackGrdColor=0x00FFFF80;
	m_lHighLightColor=0x0080FF80;
	m_lGridWidth=0;
	
}


BEGIN_MESSAGE_MAP(CFlexGrid, CMSFlexGrid)
	//{{AFX_MSG_MAP(CEditGrid)
//	ON_WM_GETDLGCODE()
//	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



BEGIN_EVENTSINK_MAP(CFlexGrid, CMSFlexGrid)
    //{{AFX_EVENTSINK_MAP(CEditGrid)
	//}}AFX_EVENTSINK_MAP
	ON_EVENT_REFLECT(CFlexGrid, DISPID_KEYPRESS /* KeyPress */, OnKeyPressGrid, VTS_PI2)
	ON_EVENT_REFLECT(CFlexGrid, DISPID_DBLCLICK /* DblClick */, OnDblClickGrid, VTS_NONE)
	ON_EVENT_REFLECT(CFlexGrid, 72 /* LeaveCell */, OnUpdateGrid, VTS_NONE)

END_EVENTSINK_MAP()

void CFlexGrid::PreSubclassWindow() 
{
	//Calculate border size
int nCount;
CString csBuffer,
	    csCount;

	SetRow(0);
	SetCol(0);

	m_lBorderWidth = GetCellLeft();
	m_lBorderHeight = GetCellTop();

	// To convert grid rect from twips to DC units
	// We need pixels per inch
	CDC* pDC = GetDC();
	m_nLogX = pDC->GetDeviceCaps(LOGPIXELSX);
	m_nLogY = pDC->GetDeviceCaps(LOGPIXELSY);
	ReleaseDC(pDC);
	
	//Create invisible edit control
	m_edit.Create(WS_CHILD|ES_AUTOHSCROLL , 
		CRect(0,0,0,0), this, GetDlgCtrlID());	



	for (nCount=0;nCount<5;nCount++)
	{
  	   
	
		m_btnUsedChkBox[nCount].Create(" ", BS_CHECKBOX|WS_CHILD, 
	  	  CRect(0,0,0,0), this, GetDlgCtrlID());

		m_btnPrintedChkBox[nCount].Create(" ", BS_CHECKBOX|WS_CHILD, 
			CRect(0,0,0,0), this, GetDlgCtrlID());

		m_btnLoggedChkBox[nCount].Create(" ", BS_CHECKBOX|WS_CHILD, 
	  	  CRect(0,0,0,0), this, GetDlgCtrlID());


	}

}



CString CFlexGrid::GetData(int nAtRow, int nAtCol)
{
CString csTemp;

	int nRow;
	int nCol=1;

	for (nRow=1;nRow<GetRows();nRow++)
	{
		
		SetRow(nRow);
		if (GetCellBackColor()==m_lHighLightColor)
		{
			for (nCol=1;nCol<GetCols();nCol++)
			{
				SetCol(nCol);
				SetCellBackColor(m_lBackGrdColor); // set background;
			}

		}
	}
	
	SetRow(nAtRow);
    SetCol(nAtCol);

	csTemp= GetText();

	for (nCol=1;nCol<GetCols();nCol++)
	{
		SetCol(nCol);
		SetCellBackColor(m_lHighLightColor);  //Highlight cell
	}
	return csTemp;

}


CString CFlexGrid::GetTextData(int nAtRow, int nAtCol)
{
CString csTemp;


	SetRow(nAtRow);
    SetCol(nAtCol);

	if (GetText().IsEmpty())
	{
		csTemp="";
	}
	else 
		csTemp= GetText();

	if ((csTemp==" ")||(csTemp==""))
		csTemp = "Not Defined ";

	return csTemp;

}

void CFlexGrid::SetTextData(int nAtRow, int nAtCol, CString csTextData)
{
int nRowSave,
	nColSave;

	nRowSave=GetRow();
	nColSave=GetCol();

	SetRow(nAtRow);
    SetCol(nAtCol);

	SetText(csTextData);

	SetRow(nRowSave);
    SetCol(nRowSave);

}


void CFlexGrid::SetDataCursor(int nAtRow)
{

int nRowSave,
	nColSave;

	int nRow;
	int nCol=1;

	nRowSave=GetRow();
	nColSave=GetCol();

	
	

	for (nRow=GetFixedRows();nRow<GetRows();nRow++)
	{
		
		SetRow(nRow);
		if (GetCellBackColor()==m_lHighLightColor)
		{
			for (nCol=GetFixedCols();nCol<GetCols();nCol++)
			{
				SetCol(nCol);
				SetCellBackColor(m_lBackGrdColor);
			}

		}
	}
	
	SetRow(nAtRow);
	for (nCol=GetFixedCols();nCol<GetCols();nCol++)
	{
		SetCol(nCol);
		SetCellBackColor(m_lHighLightColor);
	}

	SetRow(nRowSave);
	SetCol(nColSave);

}



void CFlexGrid::InitFlexGrid(int nNoOfRows, int nNoOfCols)
{

	Clear();
	ResetHeaderColumnsCount();
	if (nNoOfRows< MINROWNUMBER)
	{
		SetRows(MINROWNUMBER);  // for cosmetic purposes
	}
	else
	{
		SetRows(nNoOfRows); 

	}
	
	SetCols(nNoOfCols);


}


void CFlexGrid::InitFlexGrid(int nNoOfFixedRows,
							 int nNoOfFixedColumns,
							 int nNoOfRows, int nNoOfCols)
{
	// For grids that require both one fixed col, and one
	// fixed row.

//	Clear();
	ResetHeaderColumnsCount();
	ResetFixedRowsCount();
	SetFixedRows(nNoOfFixedRows);
	SetFixedCols(nNoOfFixedColumns);

	SetRows(nNoOfRows); 
	SetCols(nNoOfCols);


}




void CFlexGrid::AddColumnHeaders(CString csHeader)
{
int nSaveRow,
	nTemp;

	nSaveRow=GetRow();
	SetRow(0);
	if (csHeader!="")
	{

		SetCol(m_nColumnHeaderCount);
		SetText(csHeader);

		nTemp=(long) GetCellFontSize()*15*csHeader.GetLength();
		SetColWidth(m_nColumnHeaderCount,(long) GetCellFontSize()
				*15*csHeader.GetLength());

		m_lGridWidth+=GetColWidth(m_nColumnHeaderCount);
		SetColAlignment(m_nColumnHeaderCount,2);
		m_nColumnHeaderCount+=1;

	}
	SetRow(nSaveRow);
}


void CFlexGrid::AddFixedRowHeaders(CString csHeader)
{
int nSaveRow,
    nSaveCol;
	

	nSaveRow=GetRow();
	nSaveCol=GetCol();
	SetCol(0);
	if (csHeader!="")
	{

		SetRow(m_nRowHeaderCount);
		SetText(csHeader);

		SetColWidth(0,(long) GetCellFontSize()
				*16*csHeader.GetLength());

		SetColAlignment(0,2);
		m_nRowHeaderCount+=1;

	}
	SetRow(nSaveRow);
	SetCol(nSaveCol);
}


int CFlexGrid::GetColumnHeadersCount()
{
	return m_nColumnHeaderCount;

}

void CFlexGrid::ResetHeaderColumnsCount()
{
	m_nColumnHeaderCount=0;
}


void CFlexGrid::ResetFixedRowsCount()
{
	m_nRowHeaderCount=0;
}

int	CFlexGrid::FindString(CString csSearch, int nColumn)
{
int nRowSave,
	nColSave;

int nIndex,
	nRecordNumber;

	nRowSave=GetRow();
	nColSave=GetCol();
	nRecordNumber=-1;
	SetCol(nColumn);
	for (nIndex=1;nIndex<GetRows();nIndex++)
	{
		SetRow(nIndex);
		if (GetText()=="") return -1;

		if (GetText()==csSearch)
		{
			
			nRecordNumber=nIndex;
			break;
		}

	}
	


	SetRow(nRowSave);
	SetCol(nColSave);


	return nRecordNumber;


}


void CFlexGrid::OnDblClickGrid() 
{
	if (!GetAllowEditing()) return;
	short i = 13;
	
	OnKeyPressGrid(&i); //Simulate a return
}



void CFlexGrid::OnKeyPressGrid(short FAR* KeyAscii) 
{	
	
	if (!GetAllowEditing()) return;

	ASSERT (KeyAscii != NULL);
		
	m_edit.SetWindowText(GetText());

	if (*KeyAscii == 13)
	{
		m_edit.SetSel(0,-1);
	}
	else if (*KeyAscii==9)
	{
		TabRight();
	}
	else
	{
		char buf[] = " ";
		buf[0] = (char)*KeyAscii;
		m_edit.SetSel(-1,-1);
		m_edit.ReplaceSel(buf);
	}
		
	//Adjust for border heigth and
	//Convert from twips to screen units
	m_edit.MoveWindow(((GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
		((GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
		(GetCellWidth()* m_nLogX)/1440, 
		(GetCellHeight()* m_nLogY)/1440, FALSE);

	m_edit.ShowWindow(SW_SHOW);
	m_edit.SetFocus();	
}

void CFlexGrid::OnUpdateGrid() 
{
	//Check to see if edit is visible
	if (!GetAllowEditing()) return;

	BOOL bVisible = ::GetWindowLong(m_edit.GetSafeHwnd(), GWL_STYLE) & WS_VISIBLE;

	if (bVisible)
	{
		CString cStr;
		m_edit.GetWindowText(cStr);
		SetText(cStr);
		m_edit.SetWindowText("");
		m_edit.ShowWindow(SW_HIDE);
	}	
}

UINT CFlexGrid::OnGetDlgCode() 
{	

	return DLGC_WANTALLKEYS;
}

void CFlexGrid::OnSetFocus(CWnd* pOldWnd) 
{
	if (!GetAllowEditing()) return;

	CMSFlexGrid::OnSetFocus(pOldWnd);
	
	OnUpdateGrid();	
}


BOOL CFlexGrid::GetAllowEditing()
{
	return m_blnAllowEditing;

}

void CFlexGrid::SetAllowEditing(BOOL blnPermission)
{
	m_blnAllowEditing=blnPermission;


}

void CFlexGrid::CreateChkBoxes(int nRow, int nCol)
{
int nRowSave,
	nColSave;

	nRowSave=GetRow();
	nColSave=GetCol();

	SetRow(nRow);
	SetCol(nCol);


	m_btnData1.MoveWindow(((GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
		((GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
		(GetCellWidth()* m_nLogX)/1440, 
		(GetCellHeight()* m_nLogY)/1440, FALSE);

	m_btnData1.ShowWindow(SW_SHOW);


	SetRow(nRowSave);
	SetCol(nColSave);

}



void CFlexGrid::CreateUsedChkBoxes(int nIndex, int nRow, int nCol)
{
int nRowSave,
	nColSave;

	nRowSave=GetRow();
	nColSave=GetCol();

	SetRow(nRow);
	SetCol(nCol);


	m_btnUsedChkBox[nIndex].MoveWindow(((GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
		((GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
		(GetCellWidth()* m_nLogX)/1440, 
		(GetCellHeight()* m_nLogY)/1440, FALSE);

	m_btnUsedChkBox[nIndex].ShowWindow(SW_SHOW);
	m_btnUsedChkBox[nIndex].SetCheck(0);


	SetRow(nRowSave);
	SetCol(nColSave);

}


void CFlexGrid::CreatePrintedChkBoxes(int nIndex, int nRow, int nCol)
{
int nRowSave,
	nColSave;

	nRowSave=GetRow();
	nColSave=GetCol();

	SetRow(nRow);
	SetCol(nCol);


	m_btnPrintedChkBox[nIndex].MoveWindow(((GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
		((GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
		(GetCellWidth()* m_nLogX)/1440, 
		(GetCellHeight()* m_nLogY)/1440, FALSE);

	m_btnPrintedChkBox[nIndex].ShowWindow(SW_SHOW);
	m_btnPrintedChkBox[nIndex].SetCheck(0);

	SetRow(nRowSave);
	SetCol(nColSave);

}

void CFlexGrid::CreateLoggedChkBoxes(int nIndex, int nRow, int nCol)
{
int nRowSave,
	nColSave;

	nRowSave=GetRow();
	nColSave=GetCol();

	SetRow(nRow);
	SetCol(nCol);


	m_btnLoggedChkBox[nIndex].MoveWindow(((GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
		((GetCellTop() - m_lBorderHeight) * m_nLogY)/1440,
		(GetCellWidth()* m_nLogX)/1440, 
		(GetCellHeight()* m_nLogY)/1440, FALSE);

	m_btnLoggedChkBox[nIndex].ShowWindow(SW_SHOW);
	m_btnLoggedChkBox[nIndex].SetCheck(0);


	SetRow(nRowSave);
	SetCol(nColSave);

}

void CFlexGrid::Sort(int nCriteria, int nType)
{
	
    
	if (m_blnSortData)
	{
	
		SetCol(nCriteria);
		SetSort(nType);

	}
	
	SetRow(1);
	SetCol(1);

}

void CFlexGrid::Sort()
{

    
	if (m_blnSortData)
	{
	
		SetCol(m_nSortOnColumn);
		SetSort((short)m_nSortType);

	}
	

}



long CFlexGrid::GetActiveRowCount()
{
int nRowSave,
	nColSave,
	nIndex,
	nFixedRow,
	nFixedCol;


long nActiveRowCount;
CString csBuffer;	

	nRowSave=GetRow();
	nColSave=GetCol();


	nFixedRow=GetFixedRows();
	nFixedCol=GetFixedCols();

	nActiveRowCount=0;
	for (nIndex=nFixedRow;nIndex<GetRows();nIndex++)
	{
		if (GetTextData(nIndex, nFixedCol).IsEmpty())
		{
			break;
		}
		else
		{
			nActiveRowCount+=1;
		}

	}

	SetRow(nRowSave);
	SetCol(nColSave);

	return nActiveRowCount;

}

void CFlexGrid::AppendString(CString csBuffer)
{
COleVariant nVar;
long nOffset;
	nOffset= GetActiveRowCount()+GetFixedRows();
	nVar=nOffset;
	AddItem(csBuffer,nVar);

	if (m_blnSortData)
		Sort();
}

void CFlexGrid::UpdateRow(int nRow, CString csBuffer)
{
COleVariant nVar;
long nOffset;
//int nRowSave,
//	nColSave;

//	nRowSave=GetRow();
//	nColSave=GetCol();

//	nOffset= nRow+GetFixedRows();
//	nVar=nOffset;

	
//	AddItem(csBuffer,nVar);

//	SetRow(nRowSave);
//	SetCol(nColSave);

int nRowSave,
	nColSave;

CString	csTemp;

	nRowSave=GetRow();
	nColSave=GetCol();

	if (csBuffer=="") return;
    SetCol(0);

	if (GetFixedCols()>0) 
	{
		SetRow(nRow);

		csTemp=GetText();
		
	
	}
	
	if (csTemp=="") return;
	RemoveItem(nRow);
	nOffset= nRow-1+GetFixedRows();
	nVar=nOffset;

	
	AddItem(csTemp+"\t"+csBuffer,nVar);
//	csBuffer=csTemp+"\t"+csBuffer;
//	SetText(csBuffer);

	SetRow(nRowSave);
    SetCol(nColSave);

}



void CFlexGrid::AddScanCheckBox(int nIndex, int nRow, int nCol)
{

int nRowSave,
	nColSave,
	x;
static int nCellTop;

	nRowSave=GetRow();
	nColSave=GetCol();

	SetRow(nRow);
	SetCol(nCol);
	
	if (nIndex==0)
	{
		nCellTop=330;
	}
	else
	{
		nCellTop=nCellTop+285;
	}
	x=GetCellLeft();
	x=GetCellTop();
	x=GetCellWidth();
	x=GetCellHeight();

	m_btnScanChkBox[nIndex].MoveWindow(((GetCellLeft() - m_lBorderWidth) * m_nLogX)/1440, 
		((nCellTop - m_lBorderHeight) * m_nLogY)/1440,
		(GetCellWidth()* m_nLogX)/1440, 
		(GetCellHeight()* m_nLogY)/1440, FALSE);

	m_btnScanChkBox[nIndex].ShowWindow(SW_SHOW);
	m_btnScanChkBox[nIndex].SetCheck(0);
	
	
	
	m_nScanChkBoxCount+=1;

	SetRow(nRowSave);
	SetCol(nColSave);


}

void CFlexGrid::SetEditBkgColor()
{
	m_lBackGrdColor=GetBackColor();
	SetBackColor(0x00FFFFFF);

}

void CFlexGrid::RestoreBkgColor()
{
	SetBackColor(m_lBackGrdColor);

}
void CFlexGrid::TabRight()
{
	if (GetCol()<GetCols()-1)
	{
		SetCol(GetCol()+1);
		 
	}
	else
	{
		if (GetFixedCols()>0)
			SetCol(1);
		else
			SetCol(0);
		if (GetRow()==(GetRows()-GetFixedRows()))
		{
			if (GetFixedRows()==1)
				SetRow(1);
			else
				SetRow(0);
		}
		else
			SetRow(GetRow()+1);
	}

}



BOOL CFlexGrid::GetFixedColumnStatus()
{
	
	return m_blnFixedColumnsAreDefined;
}

void CFlexGrid::SetFixedColumnStatus(BOOL blnStatus)
{
	m_blnFixedColumnsAreDefined=blnStatus;

}

BOOL CFlexGrid::GetFixedRowStatus()
{
	
	return m_blnFixedRowsAreDefined;
}

void CFlexGrid::SetFixedRowStatus(BOOL blnStatus)
{
	m_blnFixedRowsAreDefined=blnStatus;

}

CCHKBUTTON::CCHKBUTTON()
{
}

CCHKBUTTON::~CCHKBUTTON()
{
}


BEGIN_MESSAGE_MAP(CCHKBUTTON, CButton)
	//{{AFX_MSG_MAP(CCHKBUTTON)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCHKBUTTON message handlers

void CCHKBUTTON::OnClicked() 
{
	if (GetCheck()!=0)
		SetCheck(0);
	else
		SetCheck(1);

}

void CCHKBUTTON::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	

	CButton::OnLButtonDblClk(nFlags, point);

	if (GetCheck()!=0)
		SetCheck(0);
	else
		SetCheck(1);

}


CEditWnd::CEditWnd()
{

}



CEditWnd::~CEditWnd()
{
}


BEGIN_MESSAGE_MAP(CEditWnd, CEdit)
	//{{AFX_MSG_MAP(CEditWnd)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditWnd message handlers

void CEditWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar != 13)
		CEdit::OnChar(nChar, nRepCnt, nFlags);
}

void CEditWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar == 27) //Esc
	{
		SetWindowText("");
		ShowWindow(SW_HIDE);		
		GetParent()->SetFocus();
	}
	else if (nChar==9)
	{
		GetParent()->SendMessage(9,0,0);
	}
	else if (nChar == 13)  //Return 
		GetParent()->SetFocus();
              
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);


}


/////////////////////////////////////////////////////////////////////////////
// CMSFlexGrid

IMPLEMENT_DYNCREATE(CMSFlexGrid, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CMSFlexGrid properties

/////////////////////////////////////////////////////////////////////////////
// CMSFlexGrid operations

long CMSFlexGrid::GetRows()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetRows(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMSFlexGrid::GetCols()
{
	long result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetCols(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMSFlexGrid::GetFixedRows()
{
	long result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetFixedRows(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMSFlexGrid::GetFixedCols()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetFixedCols(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

short CMSFlexGrid::GetVersion()
{
	short result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

CString CMSFlexGrid::GetFormatString()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetFormatString(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CMSFlexGrid::GetTopRow()
{
	long result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetTopRow(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMSFlexGrid::GetLeftCol()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetLeftCol(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMSFlexGrid::GetRow()
{
	long result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetRow(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMSFlexGrid::GetCol()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetCol(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMSFlexGrid::GetRowSel()
{
	long result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetRowSel(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMSFlexGrid::GetColSel()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetColSel(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CMSFlexGrid::GetText()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

unsigned long CMSFlexGrid::GetBackColor()
{
	unsigned long result;
	InvokeHelper(DISPID_BACKCOLOR, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetBackColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(DISPID_BACKCOLOR, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CMSFlexGrid::GetForeColor()
{
	unsigned long result;
	InvokeHelper(DISPID_FORECOLOR, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetForeColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(DISPID_FORECOLOR, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CMSFlexGrid::GetBackColorFixed()
{
	unsigned long result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetBackColorFixed(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CMSFlexGrid::GetForeColorFixed()
{
	unsigned long result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetForeColorFixed(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CMSFlexGrid::GetBackColorSel()
{
	unsigned long result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetBackColorSel(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CMSFlexGrid::GetForeColorSel()
{
	unsigned long result;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetForeColorSel(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CMSFlexGrid::GetBackColorBkg()
{
	unsigned long result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetBackColorBkg(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL CMSFlexGrid::GetWordWrap()
{
	BOOL result;
	InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetWordWrap(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x13, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH CMSFlexGrid::GetFont()
{
	LPDISPATCH result;
	InvokeHelper(DISPID_FONT, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetRefFont(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(DISPID_FONT, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

float CMSFlexGrid::GetFontWidth()
{
	float result;
	InvokeHelper(0x54, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetFontWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x54, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString CMSFlexGrid::GetCellFontName()
{
	CString result;
	InvokeHelper(0x4d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetCellFontName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

float CMSFlexGrid::GetCellFontSize()
{
	float result;
	InvokeHelper(0x4e, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetCellFontSize(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x4e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL CMSFlexGrid::GetCellFontBold()
{
	BOOL result;
	InvokeHelper(0x4f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetCellFontBold(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x4f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CMSFlexGrid::GetCellFontItalic()
{
	BOOL result;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetCellFontItalic(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x50, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CMSFlexGrid::GetCellFontUnderline()
{
	BOOL result;
	InvokeHelper(0x51, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetCellFontUnderline(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x51, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CMSFlexGrid::GetCellFontStrikeThrough()
{
	BOOL result;
	InvokeHelper(0x52, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetCellFontStrikeThrough(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x52, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

float CMSFlexGrid::GetCellFontWidth()
{
	float result;
	InvokeHelper(0x53, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetCellFontWidth(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x53, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long CMSFlexGrid::GetTextStyle()
{
	long result;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetTextStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x14, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMSFlexGrid::GetTextStyleFixed()
{
	long result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetTextStyleFixed(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x15, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CMSFlexGrid::GetScrollTrack()
{
	BOOL result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetScrollTrack(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x16, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CMSFlexGrid::GetFocusRect()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetFocusRect(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMSFlexGrid::GetHighLight()
{
	long result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetHighLight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CMSFlexGrid::GetRedraw()
{
	BOOL result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetRedraw(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CMSFlexGrid::GetScrollBars()
{
	long result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetScrollBars(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMSFlexGrid::GetMouseRow()
{
	long result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CMSFlexGrid::GetMouseCol()
{
	long result;
	InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CMSFlexGrid::GetCellLeft()
{
	long result;
	InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CMSFlexGrid::GetCellTop()
{
	long result;
	InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CMSFlexGrid::GetCellWidth()
{
	long result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CMSFlexGrid::GetCellHeight()
{
	long result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CMSFlexGrid::GetRowHeightMin()
{
	long result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetRowHeightMin(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x21, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMSFlexGrid::GetFillStyle()
{
	long result;
	InvokeHelper(0xfffffe01, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetFillStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xfffffe01, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMSFlexGrid::GetGridLines()
{
	long result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetGridLines(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x22, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMSFlexGrid::GetGridLinesFixed()
{
	long result;
	InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetGridLinesFixed(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

unsigned long CMSFlexGrid::GetGridColor()
{
	unsigned long result;
	InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetGridColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x24, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CMSFlexGrid::GetGridColorFixed()
{
	unsigned long result;
	InvokeHelper(0x25, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetGridColorFixed(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x25, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CMSFlexGrid::GetCellBackColor()
{
	unsigned long result;
	InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetCellBackColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x26, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CMSFlexGrid::GetCellForeColor()
{
	unsigned long result;
	InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetCellForeColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x27, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

short CMSFlexGrid::GetCellAlignment()
{
	short result;
	InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetCellAlignment(short nNewValue)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x28, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMSFlexGrid::GetCellTextStyle()
{
	long result;
	InvokeHelper(0x29, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetCellTextStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x29, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

short CMSFlexGrid::GetCellPictureAlignment()
{
	short result;
	InvokeHelper(0x2b, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetCellPictureAlignment(short nNewValue)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x2b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CMSFlexGrid::GetClip()
{
	CString result;
	InvokeHelper(0x2d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetClip(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void CMSFlexGrid::SetSort(short nNewValue)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x2e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMSFlexGrid::GetSelectionMode()
{
	long result;
	InvokeHelper(0x2f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetSelectionMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMSFlexGrid::GetMergeCells()
{
	long result;
	InvokeHelper(0x30, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetMergeCells(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x30, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CMSFlexGrid::GetAllowBigSelection()
{
	BOOL result;
	InvokeHelper(0x33, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetAllowBigSelection(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x33, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CMSFlexGrid::GetAllowUserResizing()
{
	long result;
	InvokeHelper(0x34, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetAllowUserResizing(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x34, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMSFlexGrid::GetBorderStyle()
{
	long result;
	InvokeHelper(DISPID_BORDERSTYLE, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetBorderStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(DISPID_BORDERSTYLE, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMSFlexGrid::GetHWnd()
{
	long result;
	InvokeHelper(DISPID_HWND, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CMSFlexGrid::GetEnabled()
{
	BOOL result;
	InvokeHelper(DISPID_ENABLED, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(DISPID_ENABLED, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CMSFlexGrid::GetAppearance()
{
	long result;
	InvokeHelper(DISPID_APPEARANCE, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetAppearance(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(DISPID_APPEARANCE, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CMSFlexGrid::GetMousePointer()
{
	long result;
	InvokeHelper(0x35, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetMousePointer(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x35, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH CMSFlexGrid::GetMouseIcon()
{
	LPDISPATCH result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetRefMouseIcon(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x36, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

long CMSFlexGrid::GetPictureType()
{
	long result;
	InvokeHelper(0x32, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetPictureType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x32, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH CMSFlexGrid::GetPicture()
{
	LPDISPATCH result;
	InvokeHelper(0x31, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH CMSFlexGrid::GetCellPicture()
{
	LPDISPATCH result;
	InvokeHelper(0x2a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetRefCellPicture(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x2a, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

CString CMSFlexGrid::GetTextArray(long index)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		index);
	return result;
}

void CMSFlexGrid::SetTextArray(long index, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 index, lpszNewValue);
}

short CMSFlexGrid::GetColAlignment(long index)
{
	short result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms,
		index);
	return result;
}

void CMSFlexGrid::SetColAlignment(long index, short nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I2;
	InvokeHelper(0x38, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 index, nNewValue);
}

long CMSFlexGrid::GetColWidth(long index)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x39, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		index);
	return result;
}

void CMSFlexGrid::SetColWidth(long index, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x39, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 index, nNewValue);
}

long CMSFlexGrid::GetRowHeight(long index)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		index);
	return result;
}

void CMSFlexGrid::SetRowHeight(long index, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x3a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 index, nNewValue);
}

BOOL CMSFlexGrid::GetMergeRow(long index)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		index);
	return result;
}

void CMSFlexGrid::SetMergeRow(long index, BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL;
	InvokeHelper(0x3b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 index, bNewValue);
}

BOOL CMSFlexGrid::GetMergeCol(long index)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		index);
	return result;
}

void CMSFlexGrid::SetMergeCol(long index, BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL;
	InvokeHelper(0x3c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 index, bNewValue);
}

void CMSFlexGrid::SetRowPosition(long index, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x3d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 index, nNewValue);
}

void CMSFlexGrid::SetColPosition(long index, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x3e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 index, nNewValue);
}

long CMSFlexGrid::GetRowData(long index)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		index);
	return result;
}

void CMSFlexGrid::SetRowData(long index, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x3f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 index, nNewValue);
}

long CMSFlexGrid::GetColData(long index)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x40, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		index);
	return result;
}

void CMSFlexGrid::SetColData(long index, long nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x40, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 index, nNewValue);
}

CString CMSFlexGrid::GetTextMatrix(long Row, long Col)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		Row, Col);
	return result;
}

void CMSFlexGrid::SetTextMatrix(long Row, long Col, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_BSTR;
	InvokeHelper(0x41, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Row, Col, lpszNewValue);
}

void CMSFlexGrid::AddItem(LPCTSTR Item, const VARIANT& index)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x42, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Item, &index);
}

void CMSFlexGrid::RemoveItem(long index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x43, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 index);
}

void CMSFlexGrid::Clear()
{
	InvokeHelper(0x44, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMSFlexGrid::Refresh()
{
	InvokeHelper(DISPID_REFRESH, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH CMSFlexGrid::GetDataSource()
{
	LPDISPATCH result;
	InvokeHelper(0x4c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetDataSource(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x4c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL CMSFlexGrid::GetRowIsVisible(long index)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x55, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		index);
	return result;
}

BOOL CMSFlexGrid::GetColIsVisible(long index)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x56, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		index);
	return result;
}

long CMSFlexGrid::GetRowPos(long index)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x57, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		index);
	return result;
}

long CMSFlexGrid::GetColPos(long index)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x58, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		index);
	return result;
}

short CMSFlexGrid::GetGridLineWidth()
{
	short result;
	InvokeHelper(0x59, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetGridLineWidth(short nNewValue)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x59, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

short CMSFlexGrid::GetFixedAlignment(long index)
{
	short result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5a, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms,
		index);
	return result;
}

void CMSFlexGrid::SetFixedAlignment(long index, short nNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I2;
	InvokeHelper(0x5a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 index, nNewValue);
}

BOOL CMSFlexGrid::GetRightToLeft()
{
	BOOL result;
	InvokeHelper(0xfffffd9d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetRightToLeft(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xfffffd9d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CMSFlexGrid::GetOLEDropMode()
{
	long result;
	InvokeHelper(0x60f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMSFlexGrid::SetOLEDropMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void CMSFlexGrid::OLEDrag()
{
	InvokeHelper(0x610, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
