// PlacementSchemaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pacs.h"
#include "PlacementSchemaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlacementSchemaDlg dialog


CPlacementSchemaDlg::CPlacementSchemaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlacementSchemaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlacementSchemaDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPlacementSchemaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlacementSchemaDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlacementSchemaDlg, CDialog)
	//{{AFX_MSG_MAP(CPlacementSchemaDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlacementSchemaDlg message handlers

BOOL CPlacementSchemaDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int nX = 83*2;
	int nY = 17*2;
	int nZ = 125*2;

	m_oA1.m_nXval = nX/2;
	m_oA1.m_nYval = nY/2;
	m_oA1.m_nZval = nZ/2;

	m_oA2marker1.m_nXval = nX/2;
	m_oA2marker1.m_nYval = -nY/2;
	m_oA2marker1.m_nZval = nZ/2-20;

	m_oA2marker2.m_nXval = nX/2-20;
	m_oA2marker2.m_nYval = -nY/2;
	m_oA2marker2.m_nZval = nZ/2;

	m_oA2.m_nXval = nX/2;
	m_oA2.m_nYval = -nY/2;
	m_oA2.m_nZval = nZ/2;

	m_oA3.m_nXval = -nX/2;
	m_oA3.m_nYval = -nY/2;
	m_oA3.m_nZval = nZ/2;
	
	m_oA4.m_nXval = -nX/2;
	m_oA4.m_nYval = nY/2;
	m_oA4.m_nZval = nZ/2;
		
	m_oB1.m_nXval = nX/2;
	m_oB1.m_nYval = nY/2;
	m_oB1.m_nZval = -nZ/2;

	m_oB2.m_nXval = nX/2;
	m_oB2.m_nYval = -nY/2;
	m_oB2.m_nZval = -nZ/2;

	m_oB3.m_nXval = -nX/2;
	m_oB3.m_nYval = -nY/2;
	m_oB3.m_nZval = -nZ/2;

	m_oB4.m_nXval = -nX/2;
	m_oB4.m_nYval = nY/2;
	m_oB4.m_nZval = -nZ/2;

	m_oLabelA1.m_nXval = m_oA3.m_nXval + m_nFrontAcross*2;
	m_oLabelA1.m_nYval = m_oA3.m_nYval + m_nFrontDown*2;
	m_oLabelA1.m_nZval = m_oA3.m_nZval;

	m_oLabelA2.m_nXval = m_oLabelA1.m_nXval;
	m_oLabelA2.m_nYval = m_oLabelA1.m_nYval + m_nSideWidth*2;
	m_oLabelA2.m_nZval = m_oLabelA1.m_nZval;

	m_oLabelA3.m_nXval = m_oLabelA1.m_nXval + 63*2;
	m_oLabelA3.m_nYval = m_oLabelA1.m_nYval;
	m_oLabelA3.m_nZval = m_oLabelA1.m_nZval;

	m_oLabelA4.m_nXval = m_oLabelA2.m_nXval + 63*2;
	m_oLabelA4.m_nYval = m_oLabelA2.m_nYval;
	m_oLabelA4.m_nZval = m_oLabelA2.m_nZval;

	m_oLabelB1.m_nXval = m_oA2.m_nXval;
	m_oLabelB1.m_nYval = m_oA2.m_nYval + m_nFrontDown*2;
	m_oLabelB1.m_nZval = m_oA2.m_nZval - m_nSideAcross*2;

	m_oLabelB2.m_nXval = m_oLabelB1.m_nXval;
	m_oLabelB2.m_nYval = m_oLabelB1.m_nYval + m_nSideWidth*2;
	m_oLabelB2.m_nZval = m_oLabelB1.m_nZval;

	m_oLabelB3.m_nXval = m_oLabelB1.m_nXval;
	m_oLabelB3.m_nYval = m_oLabelB1.m_nYval;
	m_oLabelB3.m_nZval = m_oLabelB1.m_nZval - 63*2;

	m_oLabelB4.m_nXval = m_oLabelB2.m_nXval;
	m_oLabelB4.m_nYval = m_oLabelB2.m_nYval;
	m_oLabelB4.m_nZval = m_oLabelB2.m_nZval - 63*2;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPlacementSchemaDlg::OnPaint() 
{
	CWnd *pWnd = GetDlgItem(IDC_SCHEMA_WINDOW);
	CDC *pSchemaDC = pWnd->GetDC();
	CRect crctWindowSize;
	pSchemaDC->GetClipBox(&crctWindowSize);
	int nWindowHeight = crctWindowSize.Height();
	int nWindowWidth = crctWindowSize.Width();
	int nYOffset = nWindowHeight/3;
	int nXOffset = nWindowWidth/2;

	pSchemaDC->MoveTo(m_oA1.GetScreenX()+nXOffset,m_oA1.GetScreenY()+nYOffset);
	pSchemaDC->LineTo(m_oA2.GetScreenX()+nXOffset,m_oA2.GetScreenY()+nYOffset);
	pSchemaDC->LineTo(m_oA3.GetScreenX()+nXOffset,m_oA3.GetScreenY()+nYOffset);
	pSchemaDC->LineTo(m_oA4.GetScreenX()+nXOffset,m_oA4.GetScreenY()+nYOffset);
	pSchemaDC->LineTo(m_oA1.GetScreenX()+nXOffset,m_oA1.GetScreenY()+nYOffset);

	pSchemaDC->MoveTo(m_oA1.GetScreenX()+nXOffset,m_oA1.GetScreenY()+nYOffset);
	pSchemaDC->LineTo(m_oB1.GetScreenX()+nXOffset,m_oB1.GetScreenY()+nYOffset);

	pSchemaDC->MoveTo(m_oA2.GetScreenX()+nXOffset,m_oA2.GetScreenY()+nYOffset);
	pSchemaDC->LineTo(m_oB2.GetScreenX()+nXOffset,m_oB2.GetScreenY()+nYOffset);

	pSchemaDC->MoveTo(m_oB2.GetScreenX()+nXOffset,m_oB2.GetScreenY()+nYOffset);
	pSchemaDC->LineTo(m_oB1.GetScreenX()+nXOffset,m_oB1.GetScreenY()+nYOffset);

//	pSchemaDC->MoveTo(m_oB1.GetScreenX()+nXOffset,m_oB1.GetScreenY()+nYOffset); //hidden line
//	pSchemaDC->LineTo(m_oB4.GetScreenX()+nXOffset,m_oB4.GetScreenY()+nYOffset);

	pSchemaDC->MoveTo(m_oB2.GetScreenX()+nXOffset,m_oB2.GetScreenY()+nYOffset);
	pSchemaDC->LineTo(m_oB3.GetScreenX()+nXOffset,m_oB3.GetScreenY()+nYOffset);

//	pSchemaDC->MoveTo(m_oB3.GetScreenX()+nXOffset,m_oB3.GetScreenY()+nYOffset);	//hidden line
//	pSchemaDC->LineTo(m_oB4.GetScreenX()+nXOffset,m_oB4.GetScreenY()+nYOffset);

	pSchemaDC->MoveTo(m_oB3.GetScreenX()+nXOffset,m_oB3.GetScreenY()+nYOffset);
	pSchemaDC->LineTo(m_oA3.GetScreenX()+nXOffset,m_oA3.GetScreenY()+nYOffset);

//	pSchemaDC->MoveTo(m_oB4.GetScreenX()+nXOffset,m_oB4.GetScreenY()+nYOffset);	//hidden line
//	pSchemaDC->LineTo(m_oA4.GetScreenX()+nXOffset,m_oA4.GetScreenY()+nYOffset);

	pSchemaDC->MoveTo(m_oA2marker1.GetScreenX()+nXOffset,m_oA2marker1.GetScreenY()+nYOffset);
	pSchemaDC->LineTo(m_oA2marker2.GetScreenX()+nXOffset,m_oA2marker2.GetScreenY()+nYOffset);

	pSchemaDC->MoveTo(m_oLabelA1.GetScreenX()+nXOffset,m_oLabelA1.GetScreenY()+nYOffset);
	pSchemaDC->LineTo(m_oLabelA2.GetScreenX()+nXOffset,m_oLabelA2.GetScreenY()+nYOffset);

	pSchemaDC->MoveTo(m_oLabelA2.GetScreenX()+nXOffset,m_oLabelA2.GetScreenY()+nYOffset);
	pSchemaDC->LineTo(m_oLabelA4.GetScreenX()+nXOffset,m_oLabelA4.GetScreenY()+nYOffset);
	
	pSchemaDC->MoveTo(m_oLabelA3.GetScreenX()+nXOffset,m_oLabelA3.GetScreenY()+nYOffset);
	pSchemaDC->LineTo(m_oLabelA4.GetScreenX()+nXOffset,m_oLabelA4.GetScreenY()+nYOffset);

	pSchemaDC->MoveTo(m_oLabelA3.GetScreenX()+nXOffset,m_oLabelA3.GetScreenY()+nYOffset);
	pSchemaDC->LineTo(m_oLabelA1.GetScreenX()+nXOffset,m_oLabelA1.GetScreenY()+nYOffset);
	

	pSchemaDC->MoveTo(m_oLabelB1.GetScreenX()+nXOffset,m_oLabelB1.GetScreenY()+nYOffset);
	pSchemaDC->LineTo(m_oLabelB2.GetScreenX()+nXOffset,m_oLabelB2.GetScreenY()+nYOffset);

	pSchemaDC->MoveTo(m_oLabelB2.GetScreenX()+nXOffset,m_oLabelB2.GetScreenY()+nYOffset);
	pSchemaDC->LineTo(m_oLabelB4.GetScreenX()+nXOffset,m_oLabelB4.GetScreenY()+nYOffset);
	
	pSchemaDC->MoveTo(m_oLabelB3.GetScreenX()+nXOffset,m_oLabelB3.GetScreenY()+nYOffset);
	pSchemaDC->LineTo(m_oLabelB4.GetScreenX()+nXOffset,m_oLabelB4.GetScreenY()+nYOffset);

	pSchemaDC->MoveTo(m_oLabelB3.GetScreenX()+nXOffset,m_oLabelB3.GetScreenY()+nYOffset);
	pSchemaDC->LineTo(m_oLabelB1.GetScreenX()+nXOffset,m_oLabelB1.GetScreenY()+nYOffset);

	
	CRect crctText(0,300,400,400);
	pSchemaDC->SetBkMode(TRANSPARENT);
	pSchemaDC->DrawText(m_csText,&crctText,DT_LEFT);
	
	pWnd->ReleaseDC(pSchemaDC);

	
	// Do not call CDialog::OnPaint() for painting messages
}
