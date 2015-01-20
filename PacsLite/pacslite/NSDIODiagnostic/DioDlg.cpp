// DioDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DioDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// global used to communicate between main and worker threads
threadCom	g_sThreadCommunication;

/////////////////////////////////////////////////////////////////////////////
// CDioDlg dialog


CDioDlg::CDioDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDioDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDioDlg)
	m_inputAddress = _T("");
	m_outputAddress = _T("");
	m_csInputBit_10 = _T("");
	m_csInputBit_11 = _T("");
	m_csInputBit_12 = _T("");
	m_csInputBit_13 = _T("");
	m_csInputBit_14 = _T("");
	m_csInputBit_15 = _T("");
	m_csInputBit_16 = _T("");
	m_csInputBit_17 = _T("");
	m_csInputBit_18 = _T("");
	m_csInputBit_19 = _T("");
	m_csInputBit_00 = _T("");
	m_csInputBit_01 = _T("");
	m_csInputBit_02 = _T("");
	m_csInputBit_20 = _T("");
	m_csInputBit_21 = _T("");
	m_csInputBit_22 = _T("");
	m_csInputBit_23 = _T("");
	m_csInputBit_24 = _T("");
	m_csInputBit_25 = _T("");
	m_csInputBit_26 = _T("");
	m_csInputBit_27 = _T("");
	m_csInputBit_28 = _T("");
	m_csInputBit_29 = _T("");
	m_csInputBit_30 = _T("");
	m_csInputBit_31 = _T("");
	m_csInputBit_03 = _T("");
	m_csInputBit_04 = _T("");
	m_csInputBit_05 = _T("");
	m_csInputBit_06 = _T("");
	m_csInputBit_07 = _T("");
	m_csInputBit_08 = _T("");
	m_csInputBit_09 = _T("");
	m_csOutputBit_00 = _T("");
	m_csOutputBit_01 = _T("");
	m_csOutputBit_10 = _T("");
	m_csOutputBit_11 = _T("");
	m_csOutputBit_12 = _T("");
	m_csOutputBit_13 = _T("");
	m_csOutputBit_14 = _T("");
	m_csOutputBit_15 = _T("");
	m_csOutputBit_16 = _T("");
	m_csOutputBit_17 = _T("");
	m_csOutputBit_18 = _T("");
	m_csOutputBit_19 = _T("");
	m_csOutputBit_02 = _T("");
	m_csOutputBit_20 = _T("");
	m_csOutputBit_21 = _T("");
	m_csOutputBit_22 = _T("");
	m_csOutputBit_23 = _T("");
	m_csOutputBit_24 = _T("");
	m_csOutputBit_25 = _T("");
	m_csOutputBit_26 = _T("");
	m_csOutputBit_27 = _T("");
	m_csOutputBit_28 = _T("");
	m_csOutputBit_29 = _T("");
	m_csOutputBit_03 = _T("");
	m_csOutputBit_30 = _T("");
	m_csOutputBit_31 = _T("");
	m_csOutputBit_04 = _T("");
	m_csOutputBit_05 = _T("");
	m_csOutputBit_06 = _T("");
	m_csOutputBit_07 = _T("");
	m_csOutputBit_08 = _T("");
	m_csOutputBit_09 = _T("");
	//}}AFX_DATA_INIT
}


void CDioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDioDlg)
	DDX_Control(pDX, IDC_CHECK9, m_output9);
	DDX_Control(pDX, IDC_CHECK8, m_output8);
	DDX_Control(pDX, IDC_CHECK7, m_output7);
	DDX_Control(pDX, IDC_CHECK6, m_output6);
	DDX_Control(pDX, IDC_CHECK5, m_output5);
	DDX_Control(pDX, IDC_CHECK4, m_output4);
	DDX_Control(pDX, IDC_CHECK31, m_output31);
	DDX_Control(pDX, IDC_CHECK30, m_output30);
	DDX_Control(pDX, IDC_CHECK3, m_output3);
	DDX_Control(pDX, IDC_CHECK29, m_output29);
	DDX_Control(pDX, IDC_CHECK28, m_output28);
	DDX_Control(pDX, IDC_CHECK26, m_output26);
	DDX_Control(pDX, IDC_CHECK27, m_output27);
	DDX_Control(pDX, IDC_CHECK25, m_output25);
	DDX_Control(pDX, IDC_CHECK24, m_output24);
	DDX_Control(pDX, IDC_CHECK23, m_output23);
	DDX_Control(pDX, IDC_CHECK22, m_output22);
	DDX_Control(pDX, IDC_CHECK21, m_output21);
	DDX_Control(pDX, IDC_CHECK20, m_output20);
	DDX_Control(pDX, IDC_CHECK2, m_output2);
	DDX_Control(pDX, IDC_CHECK19, m_output19);
	DDX_Control(pDX, IDC_CHECK18, m_output18);
	DDX_Control(pDX, IDC_CHECK17, m_output17);
	DDX_Control(pDX, IDC_CHECK16, m_output16);
	DDX_Control(pDX, IDC_CHECK15, m_output15);
	DDX_Control(pDX, IDC_CHECK14, m_output14);
	DDX_Control(pDX, IDC_CHECK13, m_output13);
	DDX_Control(pDX, IDC_CHECK12, m_output12);
	DDX_Control(pDX, IDC_CHECK11, m_output11);
	DDX_Control(pDX, IDC_CHECK10, m_output10);
	DDX_Control(pDX, IDC_CHECK0, m_output0);
	DDX_Control(pDX, IDC_CHECK1, m_output1);
	DDX_Text(pDX, IDC_INPUT_ADDRESS, m_inputAddress);
	DDX_Text(pDX, IDC_OUTPUT_ADDRESS, m_outputAddress);
	DDX_Control(pDX, IDC_INPUT0, m_input0);
	DDX_Control(pDX, IDC_INPUT1, m_input1);
	DDX_Control(pDX, IDC_INPUT10, m_input10);
	DDX_Control(pDX, IDC_INPUT11, m_input11);
	DDX_Control(pDX, IDC_INPUT12, m_input12);
	DDX_Control(pDX, IDC_INPUT13, m_input13);
	DDX_Control(pDX, IDC_INPUT14, m_input14);
	DDX_Control(pDX, IDC_INPUT15, m_input15);
	DDX_Control(pDX, IDC_INPUT16, m_input16);
	DDX_Control(pDX, IDC_INPUT17, m_input17);
	DDX_Control(pDX, IDC_INPUT18, m_input18);
	DDX_Control(pDX, IDC_INPUT19, m_input19);
	DDX_Control(pDX, IDC_INPUT2, m_input2);
	DDX_Control(pDX, IDC_INPUT20, m_input20);
	DDX_Control(pDX, IDC_INPUT21, m_input21);
	DDX_Control(pDX, IDC_INPUT22, m_input22);
	DDX_Control(pDX, IDC_INPUT23, m_input23);
	DDX_Control(pDX, IDC_INPUT24, m_input24);
	DDX_Control(pDX, IDC_INPUT25, m_input25);
	DDX_Control(pDX, IDC_INPUT26, m_input26);
	DDX_Control(pDX, IDC_INPUT27, m_input27);
	DDX_Control(pDX, IDC_INPUT28, m_input28);
	DDX_Control(pDX, IDC_INPUT29, m_input29);
	DDX_Control(pDX, IDC_INPUT3, m_input3);
	DDX_Control(pDX, IDC_INPUT30, m_input30);
	DDX_Control(pDX, IDC_INPUT31, m_input31);
	DDX_Control(pDX, IDC_INPUT4, m_input4);
	DDX_Control(pDX, IDC_INPUT5, m_input5);
	DDX_Control(pDX, IDC_INPUT6, m_input6);
	DDX_Control(pDX, IDC_INPUT7, m_input7);
	DDX_Control(pDX, IDC_INPUT8, m_input8);
	DDX_Control(pDX, IDC_INPUT9, m_input9);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_10, m_csInputBit_10);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_11, m_csInputBit_11);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_12, m_csInputBit_12);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_13, m_csInputBit_13);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_14, m_csInputBit_14);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_15, m_csInputBit_15);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_16, m_csInputBit_16);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_17, m_csInputBit_17);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_18, m_csInputBit_18);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_19, m_csInputBit_19);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_0, m_csInputBit_00);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_1, m_csInputBit_01);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_2, m_csInputBit_02);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_20, m_csInputBit_20);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_21, m_csInputBit_21);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_22, m_csInputBit_22);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_23, m_csInputBit_23);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_24, m_csInputBit_24);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_25, m_csInputBit_25);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_26, m_csInputBit_26);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_27, m_csInputBit_27);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_28, m_csInputBit_28);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_29, m_csInputBit_29);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_30, m_csInputBit_30);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_31, m_csInputBit_31);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_3, m_csInputBit_03);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_4, m_csInputBit_04);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_5, m_csInputBit_05);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_6, m_csInputBit_06);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_7, m_csInputBit_07);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_8, m_csInputBit_08);
	DDX_Text(pDX, IDC_STATIC_INPUT_BIT_9, m_csInputBit_09);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_0, m_csOutputBit_00);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_1, m_csOutputBit_01);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_10, m_csOutputBit_10);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_11, m_csOutputBit_11);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_12, m_csOutputBit_12);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_13, m_csOutputBit_13);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_14, m_csOutputBit_14);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_15, m_csOutputBit_15);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_16, m_csOutputBit_16);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_17, m_csOutputBit_17);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_18, m_csOutputBit_18);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_19, m_csOutputBit_19);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_2, m_csOutputBit_02);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_20, m_csOutputBit_20);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_21, m_csOutputBit_21);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_22, m_csOutputBit_22);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_23, m_csOutputBit_23);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_24, m_csOutputBit_24);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_25, m_csOutputBit_25);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_26, m_csOutputBit_26);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_27, m_csOutputBit_27);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_28, m_csOutputBit_28);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_29, m_csOutputBit_29);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_3, m_csOutputBit_03);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_30, m_csOutputBit_30);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_31, m_csOutputBit_31);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_4, m_csOutputBit_04);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_5, m_csOutputBit_05);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_6, m_csOutputBit_06);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_7, m_csOutputBit_07);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_8, m_csOutputBit_08);
	DDX_Text(pDX, IDC_STATIC_OUTPUT_BIT_9, m_csOutputBit_09);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDioDlg, CDialog)
	//{{AFX_MSG_MAP(CDioDlg)
	ON_BN_CLICKED(IDC_CHECK0, OnCheck0)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK10, OnCheck10)
	ON_BN_CLICKED(IDC_CHECK11, OnCheck11)
	ON_BN_CLICKED(IDC_CHECK12, OnCheck12)
	ON_BN_CLICKED(IDC_CHECK13, OnCheck13)
	ON_BN_CLICKED(IDC_CHECK14, OnCheck14)
	ON_BN_CLICKED(IDC_CHECK15, OnCheck15)
	ON_BN_CLICKED(IDC_CHECK16, OnCheck16)
	ON_BN_CLICKED(IDC_CHECK17, OnCheck17)
	ON_BN_CLICKED(IDC_CHECK18, OnCheck18)
	ON_BN_CLICKED(IDC_CHECK19, OnCheck19)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK20, OnCheck20)
	ON_BN_CLICKED(IDC_CHECK21, OnCheck21)
	ON_BN_CLICKED(IDC_CHECK22, OnCheck22)
	ON_BN_CLICKED(IDC_CHECK23, OnCheck23)
	ON_BN_CLICKED(IDC_CHECK24, OnCheck24)
	ON_BN_CLICKED(IDC_CHECK25, OnCheck25)
	ON_BN_CLICKED(IDC_CHECK26, OnCheck26)
	ON_BN_CLICKED(IDC_CHECK27, OnCheck27)
	ON_BN_CLICKED(IDC_CHECK28, OnCheck28)
	ON_BN_CLICKED(IDC_CHECK29, OnCheck29)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK30, OnCheck30)
	ON_BN_CLICKED(IDC_CHECK31, OnCheck31)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck6)
	ON_BN_CLICKED(IDC_CHECK7, OnCheck7)
	ON_BN_CLICKED(IDC_CHECK8, OnCheck8)
	ON_BN_CLICKED(IDC_CHECK9, OnCheck9)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_DIODLGTHREADMESSAGE,OnThreadMessage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDioDlg message handlers

BEGIN_EVENTSINK_MAP(CDioDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CDioDlg)
	ON_EVENT(CDioDlg, IDC_CLOSE_DIO_DIAGNOSTICS, -600 /* Click */, OnClickCloseDioDiagnostics, VTS_NONE)
	ON_EVENT(CDioDlg, IDC_SET_INPUT_ADDRESS, -600 /* Click */, OnClickSetInputAddress, VTS_NONE)
	ON_EVENT(CDioDlg, IDC_SET_OUTPUT_ADDRESS, -600 /* Click */, OnClickSetOutputAddress, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnInitDialog
//
//	Description:
//		Set up the dialog for initial display
//
//	Arguments:
//		none
//
//	Return:
//		void
//
//	Called by:
//		MFC framework
/////////////////////////////////////////////////////////////////////////////////////

BOOL CDioDlg::OnInitDialog() 
{
	// run base class method
	CDialog::OnInitDialog();

	// declare and initialize the database
	CDatabase	oDatabase;
	oDatabase.Initialize();
	
	// retrieve the input and output addresses
	CString		csInputAddress,csOutputAddress;
	oDatabase.GetDIOAddress(&csInputAddress,&csOutputAddress);

	// refresh the edit controls	
	m_inputAddress = csInputAddress;
	m_outputAddress = csOutputAddress;
	InitInputBitDescription();
	InitOutputBitDescription();

	UpdateData(FALSE);

	// a utility object to use for conversions
	CUtilities oUtility;

	// convert the input address to an integer
	int nInputAddress = oUtility.AsciiHexToUINT(csInputAddress);
	
	// convert the output address to an integer
	int nOutputAddress = oUtility.AsciiHexToUINT(csOutputAddress);
	
	// declare and initialize DioInput object
	m_oDioInput  = new CDIODriver();	
	m_oDioInput->Initialize((unsigned long)nInputAddress);

	// declare and initialize DioOutput object
	m_oDioOutput = new CDIODriver();
	m_oDioOutput->Initialize((unsigned long)nOutputAddress);

	// reset output array
	m_oDioOutput->WriteOutputLong(0);

	// get initial input array values
	unsigned long	ulInitialInputArray;
	m_oDioInput->ReadInputLong(&ulInitialInputArray);

	// display initial input array values
	SetInputDisplay(ulInitialInputArray);

	// cache initial input array in global structure
	g_sThreadCommunication.ulInputArray = ulInitialInputArray;
	
	// set the thread lives flag
	g_sThreadCommunication.bThreadLives = TRUE;

	// spawn the thread to update the display
	m_myThread = AfxBeginThread(DioThreadFunction,this,THREAD_PRIORITY_BELOW_NORMAL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickCloseDioDiagnostics
//
//	Description:
//		Closes and cleans up the dialog
//
//	Arguments:
//		none
//
//	Return:
//		void
//
//	Called by:
//		MFC framework
/////////////////////////////////////////////////////////////////////////////////////

void CDioDlg::OnClickCloseDioDiagnostics() 
{
	// reset output array
	m_oDioOutput->WriteOutputLong(0);
	
	// turn off all the buttons
	m_output0.SetCheck(FALSE);
	m_output1.SetCheck(FALSE);
	m_output2.SetCheck(FALSE);
	m_output3.SetCheck(FALSE);
	m_output4.SetCheck(FALSE);
	m_output5.SetCheck(FALSE);
	m_output6.SetCheck(FALSE);
	m_output7.SetCheck(FALSE);
	m_output8.SetCheck(FALSE);
	m_output9.SetCheck(FALSE);
	m_output10.SetCheck(FALSE);
	m_output11.SetCheck(FALSE);
	m_output12.SetCheck(FALSE);
	m_output13.SetCheck(FALSE);
	m_output14.SetCheck(FALSE);
	m_output15.SetCheck(FALSE);
	m_output16.SetCheck(FALSE);
	m_output17.SetCheck(FALSE);
	m_output18.SetCheck(FALSE);
	m_output19.SetCheck(FALSE);
	m_output20.SetCheck(FALSE);
	m_output21.SetCheck(FALSE);
	m_output22.SetCheck(FALSE);
	m_output23.SetCheck(FALSE);
	m_output24.SetCheck(FALSE);
	m_output25.SetCheck(FALSE);
	m_output26.SetCheck(FALSE);
	m_output27.SetCheck(FALSE);
	m_output28.SetCheck(FALSE);
	m_output29.SetCheck(FALSE);
	m_output30.SetCheck(FALSE);
	m_output31.SetCheck(FALSE);
	
	// toggle the global to kill the thread
	g_sThreadCommunication.bThreadLives = FALSE;

	// wait for thread to die
	WaitForSingleObject(m_myThread->m_hThread,INFINITE);

	// set the thread to nothing
	m_myThread = NULL;

	// delete the driver objects
	delete m_oDioInput;
	delete m_oDioOutput;

	// call base class end
	CDialog::EndDialog(0);	
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetSingleBit
//
//	Description:
//		Turns one output display bit on or off
//
//	Arguments:
//		BOOL bState:    TRUE = ON, FALSE = OFF
//		int  nPosition: Bit number to turn on or off
//	Return:
//		void
//
//	Called by:
//		CDioDlg::SetInputDisplay()
/////////////////////////////////////////////////////////////////////////////////////

void CDioDlg::SetSingleBit(BOOL bState, int nPosition)
{
	COLORREF buttonColor;

	if (bState)
		// color is green, bit is on
		buttonColor = 0x00008000;
	else
		// color is red, bit is off
		buttonColor = 0x000000FF;

	// set the correct button to the chosen color
	switch (nPosition)
	{
		case 0:
		{
			m_input0.SetBackColor(buttonColor);
			break;
		}
		case 1:
		{
			m_input1.SetBackColor(buttonColor);
			break;
		}
		case 2:
		{
			m_input2.SetBackColor(buttonColor);
			break;
		}
		case 3:
		{
			m_input3.SetBackColor(buttonColor);
			break;
		}
		case 4:
		{
			m_input4.SetBackColor(buttonColor);
			break;
		}
		case 5:
		{
			m_input5.SetBackColor(buttonColor);
			break;
		}
		case 6:
		{
			m_input6.SetBackColor(buttonColor);
			break;
		}
		case 7:
		{
			m_input7.SetBackColor(buttonColor);
			break;
		}
		case 8:
		{
			m_input8.SetBackColor(buttonColor);
			break;
		}
		case 9:
		{
			m_input9.SetBackColor(buttonColor);
			break;
		}
		case 10:
		{
			m_input10.SetBackColor(buttonColor);
			break;
		}
		case 11:
		{
			m_input11.SetBackColor(buttonColor);
			break;
		}
		case 12:
		{
			m_input12.SetBackColor(buttonColor);
			break;
		}
		case 13:
		{
			m_input13.SetBackColor(buttonColor);
			break;
		}
		case 14:
		{
			m_input14.SetBackColor(buttonColor);
			break;
		}
		case 15:
		{
			m_input15.SetBackColor(buttonColor);
			break;
		}
		case 16:
		{
			m_input16.SetBackColor(buttonColor);
			break;
		}
		case 17:
		{
			m_input17.SetBackColor(buttonColor);
			break;
		}
		case 18:
		{
			m_input18.SetBackColor(buttonColor);
			break;
		}
		case 19:
		{
			m_input19.SetBackColor(buttonColor);
			break;
		}
		case 20:
		{
			m_input20.SetBackColor(buttonColor);
			break;
		}
		case 21:
		{
			m_input21.SetBackColor(buttonColor);
			break;
		}
		case 22:
		{
			m_input22.SetBackColor(buttonColor);
			break;
		}
		case 23:
		{
			m_input23.SetBackColor(buttonColor);
			break;
		}
		case 24:
		{
			m_input24.SetBackColor(buttonColor);
			break;
		}
		case 25:
		{
			m_input25.SetBackColor(buttonColor);
			break;
		}
		case 26:
		{
			m_input26.SetBackColor(buttonColor);
			break;
		}
		case 27:
		{	
			m_input27.SetBackColor(buttonColor);
			break;
		}
		case 28:
		{
			m_input28.SetBackColor(buttonColor);
			break;
		}
		case 29:
		{
			m_input29.SetBackColor(buttonColor);
			break;
		}
		case 30:
		{
			m_input30.SetBackColor(buttonColor);
			break;
		}
		case 31:
		{
			m_input31.SetBackColor(buttonColor);
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetInputDisplay
//
//	Description:
//		Maps the input array to the dialog display
//
//	Arguments:
//		unsigned long bitField:  number representing state of input array
//
//	Return:
//		void
//
//	Called by:
//		CDioDlg::OnInitDlg()
/////////////////////////////////////////////////////////////////////////////////////

void CDioDlg::SetInputDisplay(unsigned long bitField)
{
	int digit;
	unsigned int powerOfTwo=1;

	for(digit=0;digit<31;digit++)
	{
		// if digit is turned on
		if ((bitField&powerOfTwo)==powerOfTwo)
			SetSingleBit(TRUE,digit);
		else
			SetSingleBit(FALSE,digit);
		powerOfTwo*=2;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnCheckX where X = 0 through 31
//
//	Description:
//		These functions toggle the corresponding output bit
//
//	Arguments:
//		none
//
//	Return:
//		void
//
//	Called by:
//		MFC framework
/////////////////////////////////////////////////////////////////////////////////////

void CDioDlg::OnCheck0() 
{
	setOutputBits();
}

void CDioDlg::OnCheck1() 
{
	setOutputBits();
}

void CDioDlg::OnCheck2() 
{
	setOutputBits();
}

void CDioDlg::OnCheck3() 
{
	setOutputBits();
}

void CDioDlg::OnCheck4() 
{
	setOutputBits();
}

void CDioDlg::OnCheck5() 
{
	setOutputBits();
}

void CDioDlg::OnCheck6() 
{
	setOutputBits();
}

void CDioDlg::OnCheck7() 
{
	setOutputBits();
}

void CDioDlg::OnCheck8() 
{
	setOutputBits();
}

void CDioDlg::OnCheck9() 
{
	setOutputBits();
}

void CDioDlg::OnCheck10() 
{
	setOutputBits();
}

void CDioDlg::OnCheck11() 
{
	setOutputBits();
}

void CDioDlg::OnCheck12() 
{
	setOutputBits();
}

void CDioDlg::OnCheck13() 
{
	setOutputBits();
}

void CDioDlg::OnCheck14() 
{
	setOutputBits();
}

void CDioDlg::OnCheck15() 
{
	setOutputBits();
}

void CDioDlg::OnCheck16() 
{
	setOutputBits();
}

void CDioDlg::OnCheck17() 
{
	setOutputBits();
}

void CDioDlg::OnCheck18() 
{
	setOutputBits();
}

void CDioDlg::OnCheck19() 
{
	setOutputBits();
}

void CDioDlg::OnCheck20() 
{
	setOutputBits();
}

void CDioDlg::OnCheck21() 
{
	setOutputBits();
}

void CDioDlg::OnCheck22() 
{
	setOutputBits();
}

void CDioDlg::OnCheck23() 
{
	setOutputBits();
}

void CDioDlg::OnCheck24() 
{
	setOutputBits();
}

void CDioDlg::OnCheck25() 
{
	setOutputBits();
}

void CDioDlg::OnCheck26() 
{
	setOutputBits();
}

void CDioDlg::OnCheck27() 
{
	setOutputBits();
}

void CDioDlg::OnCheck28() 
{
	setOutputBits();
}

void CDioDlg::OnCheck29() 
{
	setOutputBits();
}

void CDioDlg::OnCheck30() 
{
	setOutputBits();
}

void CDioDlg::OnCheck31() 
{
	setOutputBits();
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		setOutputBits
//
//	Description:
//		Makes the output array match the output check box states
//
//	Arguments:
//		none
//
//	Return:
//		void
//
//	Called by:
//		OnCheckX where X = 0 through 31, for each output check box
/////////////////////////////////////////////////////////////////////////////////////

void CDioDlg::setOutputBits()
{
	unsigned long ulOutputArray[32];

	// make the array match the button states
	ulOutputArray[0]  = m_output0.GetCheck();
	ulOutputArray[1]  = m_output1.GetCheck();
	ulOutputArray[2]  = m_output2.GetCheck();
	ulOutputArray[3]  = m_output3.GetCheck();
	ulOutputArray[4]  = m_output4.GetCheck();
	ulOutputArray[5]  = m_output5.GetCheck();
	ulOutputArray[6]  = m_output6.GetCheck();
	ulOutputArray[7]  = m_output7.GetCheck();
	ulOutputArray[8]  = m_output8.GetCheck();
	ulOutputArray[9]  = m_output9.GetCheck();
	ulOutputArray[10] = m_output10.GetCheck();
	ulOutputArray[11] = m_output11.GetCheck();
	ulOutputArray[12] = m_output12.GetCheck();
	ulOutputArray[13] = m_output13.GetCheck();
	ulOutputArray[14] = m_output14.GetCheck();
	ulOutputArray[15] = m_output15.GetCheck();
	ulOutputArray[16] = m_output16.GetCheck();
	ulOutputArray[17] = m_output17.GetCheck();
	ulOutputArray[18] = m_output18.GetCheck();
	ulOutputArray[19] = m_output19.GetCheck();
	ulOutputArray[20] = m_output20.GetCheck();
	ulOutputArray[21] = m_output21.GetCheck();
	ulOutputArray[22] = m_output22.GetCheck();
	ulOutputArray[23] = m_output23.GetCheck();
	ulOutputArray[24] = m_output24.GetCheck();
	ulOutputArray[25] = m_output25.GetCheck();
	ulOutputArray[26] = m_output26.GetCheck();
	ulOutputArray[27] = m_output27.GetCheck();
	ulOutputArray[28] = m_output28.GetCheck();
	ulOutputArray[29] = m_output29.GetCheck();
	ulOutputArray[30] = m_output30.GetCheck();
	ulOutputArray[31] = m_output31.GetCheck();

	// write back the result
	m_oDioOutput->WriteOutputArray(ulOutputArray);
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickSetInputAddress
//
//	Description:
//		Sets a new input address
//
//	Arguments:
//		none
//	Return:
//		void
//
//	Called by:
//		MFC framework
/////////////////////////////////////////////////////////////////////////////////////

void CDioDlg::OnClickSetInputAddress() 
{
	// suspend the thread updating the display
	m_myThread->SuspendThread();

	// cache the old address
	CString	csOldAddress = m_inputAddress;
	
	// update member variables from controls
	UpdateData(TRUE);

	// get text from edit box, format it
	CString csInputAddress = m_inputAddress;
	csInputAddress.MakeUpper();
	csInputAddress.TrimRight();
	csInputAddress.TrimLeft();

	// utility object for conversions
	CUtilities oUtility;

	// if the hex number is valid, use it; else retrieve old value
	if (oUtility.IsValidHex(csInputAddress,3,3))
		m_oDioInput->Initialize(oUtility.AsciiHexToUINT(csInputAddress));
	else
	{
		m_inputAddress = csOldAddress;
		UpdateData(FALSE);
	}

	// resume the worker thread updating the display
	m_myThread->ResumeThread();
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnClickSetOutputAddress
//
//	Description:
//		Set a new output address
//
//	Arguments:
//		none
//	Return:
//		void
//
//	Called by:
//		MFC framework
/////////////////////////////////////////////////////////////////////////////////////

void CDioDlg::OnClickSetOutputAddress() 
{
	// reset output array
	m_oDioOutput->WriteOutputLong(0);
	
	// turn off all the buttons
	m_output0.SetCheck(FALSE);
	m_output1.SetCheck(FALSE);
	m_output2.SetCheck(FALSE);
	m_output3.SetCheck(FALSE);
	m_output4.SetCheck(FALSE);
	m_output5.SetCheck(FALSE);
	m_output6.SetCheck(FALSE);
	m_output7.SetCheck(FALSE);
	m_output8.SetCheck(FALSE);
	m_output9.SetCheck(FALSE);
	m_output10.SetCheck(FALSE);
	m_output11.SetCheck(FALSE);
	m_output12.SetCheck(FALSE);
	m_output13.SetCheck(FALSE);
	m_output14.SetCheck(FALSE);
	m_output15.SetCheck(FALSE);
	m_output16.SetCheck(FALSE);
	m_output17.SetCheck(FALSE);
	m_output18.SetCheck(FALSE);
	m_output19.SetCheck(FALSE);
	m_output20.SetCheck(FALSE);
	m_output21.SetCheck(FALSE);
	m_output22.SetCheck(FALSE);
	m_output23.SetCheck(FALSE);
	m_output24.SetCheck(FALSE);
	m_output25.SetCheck(FALSE);
	m_output26.SetCheck(FALSE);
	m_output27.SetCheck(FALSE);
	m_output28.SetCheck(FALSE);
	m_output29.SetCheck(FALSE);
	m_output30.SetCheck(FALSE);
	m_output31.SetCheck(FALSE);

	// cache the old address
	CString	csOldAddress = m_outputAddress;
	
	// update member variables from controls
	UpdateData(TRUE);

	// get text from edit box, format it
	CString csOutputAddress = m_outputAddress;
	csOutputAddress.MakeUpper();
	csOutputAddress.TrimRight();
	csOutputAddress.TrimLeft();

	// utility object for conversions
	CUtilities oUtility;

	// if the hex number is valid, use it; else retrieve old value
	if (oUtility.IsValidHex(csOutputAddress,3,3))
		m_oDioOutput->Initialize(oUtility.AsciiHexToUINT(csOutputAddress));
	else
	{
		m_outputAddress = csOldAddress;
		UpdateData(FALSE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnThreadMessage
//
//	Description:
//		Dialog response to thread telling it to update
//
//	Arguments:
//		wParam, lParam unused
//	Return:
//		void
//
//	Called by:
//		DioThreadFunction via ::PostMessage
/////////////////////////////////////////////////////////////////////////////////////

void CDioDlg::OnThreadMessage(WPARAM wParam, LPARAM lParam)
{
	SetInputDisplay(g_sThreadCommunication.ulInputArray);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		DioThreadFunction
//
//	Description:
//		worker thread to continuously update input display
//
//	Arguments:
//		LPVOID *p_dialog: cast thread owner
//	Return:
//		UINT always zero
//
//	Called by:
//		CDioDiagnosticsDlg::OnInitDialog via AfxBeginThread
/////////////////////////////////////////////////////////////////////////////////////

UINT DioThreadFunction (LPVOID pParam)
{
	unsigned long ulNewArray;
	CDioDlg *theDialog;

	// correctly cast the parameter
	theDialog = (CDioDlg *) pParam;

	// get safe handle to post the message to
	HWND MessageTarget = theDialog->GetSafeHwnd();

	// while the dialog hasn't killed us
	while (g_sThreadCommunication.bThreadLives)
	{
		// check the array
		theDialog->m_oDioInput->ReadInputLong(&ulNewArray);
		// if the array has changed, update display and save new value
		if (ulNewArray!=g_sThreadCommunication.ulInputArray)
		{
			g_sThreadCommunication.ulInputArray = ulNewArray;			
			::PostMessage(MessageTarget,WM_DIODLGTHREADMESSAGE,0,0);
		}
	}

	// we've been killed time to leave
	return (0);
}

void CDioDlg::InitInputBitDescription()
{
CDatabase	oDatabase;
CStringArray csInputBits;

	oDatabase.Initialize();
	if (oDatabase.GetInputBits(&csInputBits))
	{

		m_csInputBit_00 = CString ("[0] ") + csInputBits[0];
		m_csInputBit_01 = CString ("[1] ") + csInputBits[1];
		m_csInputBit_02 = CString ("[2] ") +  csInputBits[2];
		m_csInputBit_03 = CString ("[3] ") +  csInputBits[3];
		m_csInputBit_04 = CString ("[4] ") +  csInputBits[4];
		m_csInputBit_05 = CString ("[5] ") +  csInputBits[5];
		m_csInputBit_06 = CString ("[6] ") +  csInputBits[6];
		m_csInputBit_07 = CString ("[7] ") +  csInputBits[7];
		m_csInputBit_08 = CString ("[8] ") +  csInputBits[8];
		m_csInputBit_09 = CString ("[9] ") +  csInputBits[9];
		m_csInputBit_10 = CString ("[10] ") +  csInputBits[10];
		m_csInputBit_11 = CString ("[11] ") +  csInputBits[11];
		m_csInputBit_12 = CString ("[12] ") +  csInputBits[12];
		m_csInputBit_13 = CString ("[13] ") +  csInputBits[13];
		m_csInputBit_14 = CString ("[14] ") +  csInputBits[14];
		m_csInputBit_15 = CString ("[15] ") +  csInputBits[15];
		m_csInputBit_16 = CString ("[16] ") +  csInputBits[16];
		m_csInputBit_17 = CString ("[17] ") +  csInputBits[17];
		m_csInputBit_18 = CString ("[18] ") +  csInputBits[18];
		m_csInputBit_19 = CString ("[19] ") +  csInputBits[19];
		m_csInputBit_20 = CString ("[20] ") +  csInputBits[20];
		m_csInputBit_21 = CString ("[21] ") +  csInputBits[21];
		m_csInputBit_22 = CString ("[22] ") +  csInputBits[22];
		m_csInputBit_23 = CString ("[23] ") +  csInputBits[23];
		m_csInputBit_24 = CString ("[24] ") +  csInputBits[24];
		m_csInputBit_25 = CString ("[25] ") +  csInputBits[25];
		m_csInputBit_26 = CString ("[26] ") +  csInputBits[26];
		m_csInputBit_27 = CString ("[27] ") +  csInputBits[27];
		m_csInputBit_28 = CString ("[28] ") +  csInputBits[28];
		m_csInputBit_29 = CString ("[29] ") +  csInputBits[29];
		m_csInputBit_30 = CString ("[30] ") +  csInputBits[30];
		m_csInputBit_31 = CString ("[31] ") +  csInputBits[31];
	}

	

}


void CDioDlg::InitOutputBitDescription()
{
CDatabase	oDatabase;
CStringArray csOutputBits;

	oDatabase.Initialize();
	if (oDatabase.GetOutputBits(&csOutputBits))
	{

		m_csOutputBit_00 = CString ("[0] ") +  csOutputBits[0];
		m_csOutputBit_01 = CString ("[1] ") +  csOutputBits[1];
		m_csOutputBit_02 = CString ("[2] ") +  csOutputBits[2];
		m_csOutputBit_03 = CString ("[3] ") +  csOutputBits[3];
		m_csOutputBit_04 = CString ("[4] ") +  csOutputBits[4];
		m_csOutputBit_05 = CString ("[5] ") +  csOutputBits[5];
		m_csOutputBit_06 = CString ("[6] ") +  csOutputBits[6];
		m_csOutputBit_07 = CString ("[7] ") +  csOutputBits[7];
		m_csOutputBit_08 = CString ("[8] ") +  csOutputBits[8];
		m_csOutputBit_09 = CString ("[9] ") +  csOutputBits[9];
		m_csOutputBit_10 = CString ("[10] ") +  csOutputBits[10];
		m_csOutputBit_11 = CString ("[11] ") +  csOutputBits[11];
		m_csOutputBit_12 = CString ("[12] ") +  csOutputBits[12];
		m_csOutputBit_13 = CString ("[13] ") +  csOutputBits[13];
		m_csOutputBit_14 = CString ("[14] ") +  csOutputBits[14];
		m_csOutputBit_15 = CString ("[15] ") +  csOutputBits[15];
		m_csOutputBit_16 = CString ("[16] ") +  csOutputBits[16];
		m_csOutputBit_17 = CString ("[17] ") +  csOutputBits[17];
		m_csOutputBit_18 = CString ("[18] ") +  csOutputBits[18];
		m_csOutputBit_19 = CString ("[19] ") +  csOutputBits[19];
		m_csOutputBit_20 = CString ("[20] ") +  csOutputBits[20];
		m_csOutputBit_21 = CString ("[21] ") +  csOutputBits[21];
		m_csOutputBit_22 = CString ("[22] ") +  csOutputBits[22];
		m_csOutputBit_23 = CString ("[23] ") +  csOutputBits[23];
		m_csOutputBit_24 = CString ("[24] ") +  csOutputBits[24];
		m_csOutputBit_25 = CString ("[25] ") +  csOutputBits[25];
		m_csOutputBit_26 = CString ("[26] ") +  csOutputBits[26];
		m_csOutputBit_27 = CString ("[27] ") +  csOutputBits[27];
		m_csOutputBit_28 = CString ("[28] ") +  csOutputBits[28];
		m_csOutputBit_29 = CString ("[29] ") +  csOutputBits[29];
		m_csOutputBit_30 = CString ("[30] ") +  csOutputBits[30];
		m_csOutputBit_31 = CString ("[31] ") +  csOutputBits[31];
	}

	

}
