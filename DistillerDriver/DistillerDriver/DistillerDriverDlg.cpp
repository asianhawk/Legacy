
// DistillerDriverDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DistillerDriver.h"
#include "DistillerDriverDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDistillerDriverDlg dialog


int CALLBACK BrowseCallBackProc( HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);

CDistillerDriverDlg::CDistillerDriverDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDistillerDriverDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDistillerDriverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDistillerDriverDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_EN_SETFOCUS(IDC_TXB_SOURCE_DIRECTORY, &CDistillerDriverDlg::OnEnSetfocusTxbSourceDirectory)
	ON_EN_SETFOCUS(IDC_TXB_TARGET_DIRECTORY, &CDistillerDriverDlg::OnEnSetfocusTxbTargetDirectory)
	ON_EN_SETFOCUS(IDC_TXB_OPTIONSFILE, &CDistillerDriverDlg::OnEnSetfocusTxbOptionsfile)
	ON_BN_CLICKED(IDOK, &CDistillerDriverDlg::OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_TXB_WORKORDER, &CDistillerDriverDlg::OnEnKillfocusTxbWorkorder)
END_MESSAGE_MAP()


// CDistillerDriverDlg message handlers

BOOL CDistillerDriverDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDistillerDriverDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDistillerDriverDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





BOOL CDistillerDriverDlg::GetDirectory(CString &csDirectory)
{
 BROWSEINFO      bi;
  LPMALLOC        pMalloc = NULL;    
  LPITEMIDLIST    pidl;
  char            acStr[MAX_PATH];
  CString initialDir("C:\\");
  CString resultsDir;

  if  ( SHGetMalloc ( &pMalloc) != NOERROR )  return FALSE; 

  ZeroMemory ( &bi, sizeof ( BROWSEINFO ));

  bi.pidlRoot = NULL; 
  bi.pszDisplayName = acStr;
  bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
  bi.lpszTitle = "Please Select Directory";
  bi.lParam = (long)(LPCTSTR)initialDir;
  bi.lpfn = BrowseCallBackProc;

  if  ( pidl = SHBrowseForFolder ( &bi ))
  {
    if  ( SHGetPathFromIDList ( pidl, acStr )) csDirectory.Format ( "%s", acStr );

    pMalloc->Free   (pidl);
  }
  if ( pMalloc ) pMalloc->Release();       
  //GetDlgItem(IDC_PROCESSFILE)->EnableWindow();
  //UpdateData (FALSE);

  return TRUE;
}

int CALLBACK BrowseCallBackProc( HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
  switch(uMsg)
  {
    case BFFM_INITIALIZED:
      ::SendMessage( hwnd, BFFM_SETSELECTION, TRUE, lpData );
       break;
  }
  return 0;
}

void CDistillerDriverDlg::OnEnSetfocusTxbSourceDirectory()
{
	GetDirectory(m_strSourceDir);
	CWnd* pWnd = GetDlgItem(IDC_TXB_SOURCE_DIRECTORY);
	pWnd->SetWindowText(m_strSourceDir); 

}


void CDistillerDriverDlg::OnEnSetfocusTxbTargetDirectory()
{
	GetDirectory(m_strTargetDir);
	CWnd* pWnd = GetDlgItem(IDC_TXB_TARGET_DIRECTORY);
	pWnd->SetWindowText(m_strTargetDir); 
}

void CDistillerDriverDlg::OnEnSetfocusTxbOptionsfile()
{
	SetFocus();
	char szFilters[]= "Adobe Job Option Files (*.joboptions)|*.joboptions|Text Files (*.txt)|*.txt|All Files (*.*)|*.*||";


	

	CFileDialog *dia = new CFileDialog(TRUE,"joboptions","Digitek.joboptions",OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);

	if(dia->DoModal()==IDOK)
	{
		m_strOptionsFile = dia->GetFolderPath()+"\\"+dia->GetFileName() ; 

	//	GetDirectory(m_strOptionsFile);
		CWnd* pWnd = GetDlgItem(IDC_TXB_OPTIONSFILE);
		pWnd->SetWindowText(m_strOptionsFile); 
	}
	GetDlgItem(IDOK)->SetFocus();
}


void CDistillerDriverDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	int nCount=0;
	CWnd *hDistillerCWnd = FindWindow("Distiller",NULL);

	if (hDistillerCWnd > 0)
    {
        // close the window using API        
        SendMessage((int)hDistillerCWnd, WM_SYSCOMMAND, SC_CLOSE);
		while (FindWindow("Distiller",NULL)!=0)
		{
			Sleep(1000);
			if (nCount>5)
			{
				// Should be a message
				return;
			}
			nCount++;
		}
    }  

	if(m_strSourceDir.IsEmpty())
	{
		MessageBox("Source Directory Not Defined","Error");
		return;
	}

	if(m_strTargetDir.IsEmpty())
	{
		MessageBox("Target Directory Not Defined","Error");
		return;
	}

	if(m_strOptionsFile.IsEmpty())
	{
		MessageBox("Options File Not Defined","Error");
		return;
	}

	CString strMessage = "C:\\DistillerCtrlVC\\Debug\\DistillerCtrlVC.exe ";
	strMessage += CString("  /s:") + m_strSourceDir;
	strMessage += CString("  /t:") + m_strTargetDir;
	strMessage += CString("  /o:") + m_strOptionsFile;
	strMessage += CString("  /w:") + m_strWorkOrder;




	//WinExec("C:\\DistillerCtrlVC\\Debug\\DistillerCtrlVC.exe /s:c:\\269949 /t:c\\269949 /o:c:\\penny\\Digitek.joboptions", SW_NORMAL);
	WinExec(strMessage, SW_NORMAL);
//	CDialogEx::OnOK();
}







void CDistillerDriverDlg::OnEnKillfocusTxbWorkorder()
{
	CWnd* pWnd = GetDlgItem(IDC_TXB_WORKORDER);
	pWnd->GetWindowTextA(m_strWorkOrder);
}
