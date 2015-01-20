// InternalSetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InternalSetupDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




/////////////////////////////////////////////////////////////////////////////
// CInternalSetupDlg dialog


CInternalSetupDlg::CInternalSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInternalSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInternalSetupDlg)
	//}}AFX_DATA_INIT
}


void CInternalSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInternalSetupDlg)
	DDX_Control(pDX, IDC_SETTINGS, m_edtSettings);
	DDX_Control(pDX, IDC_TRIGGER_DELAY, m_edtTriggerDelay);
	DDX_Control(pDX, IDC_PORT_ID, m_edtPortID);
	DDX_Control(pDX, IDC_OUTPUT_ADDRESS, m_edtOutputAddress);
	DDX_Control(pDX, IDC_OUTBUFFER_SIZE, m_edtOutBufferSize);
	DDX_Control(pDX, IDC_INPUT_ADDRESS, m_edtInputAddress);
	DDX_Control(pDX, IDC_INBUFFER_SIZE, m_edtInBufferSize);
	DDX_Control(pDX, IDC_DEVICE_LIST, m_listDevice);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInternalSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CInternalSetupDlg)
	ON_CBN_SELCHANGE(IDC_DEVICE_LIST, OnSelChangeDeviceList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInternalSetupDlg message handlers

BEGIN_EVENTSINK_MAP(CInternalSetupDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CInternalSetupDlg)
	ON_EVENT(CInternalSetupDlg, IDOK, -600 /* Click */, OnClickOk, VTS_NONE)
	ON_EVENT(CInternalSetupDlg, IDCANCEL, -600 /* Click */, OnClickCancel, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnInitDialog
//
//	Description:
//		Initialize data.
//
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CInternalSetupDlg::OnInitDialog() 
{

	CDialog::OnInitDialog();
	
	CString csDevices;
	CString csTemp;
	CString csInput;
	CString csOutput;
	CString csSpeed;
	CString csAccel;

	int
		nLength,
		nIndex;


	// Get device names from database and build device list.
	GetDeviceNames ( &csDevices );

	// The devices are ";" delimited.
	nIndex = csDevices.Find ( ";" );

	while ( nIndex != -1 )
	{

		csTemp = csDevices.Left ( nIndex );

		m_listDevice.AddString ( csTemp );

		nLength = csDevices.GetLength();
		csDevices = csDevices.Right ( nLength - nIndex - 1 );

		nIndex = csDevices.Find ( ";" );

		BuildDeviceData ( csTemp );

	}

	m_listDevice.SetCurSel ( 0 );
	m_nLastSelected = 0;

	// Display data for the currently selected device.
	OnSelChangeDeviceList();

	// Get DIO base addresses.
	GetDIOAddress ( &csInput, &csOutput );

	m_edtInputAddress.SetWindowText ( csInput );
	m_edtOutputAddress.SetWindowText ( csOutput );




	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE

}

void CInternalSetupDlg::OnClickOk() 
{

	CString csInput;
	CString csOutput;
	CString csDevice;
	CString csTemp;
	CString csDeviceName;

	BOOL
		bBad;

	int 
		i,
		nSize;

	int
		nPorts[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	int
		nTemp,
		nLength,
		nIndex,
		nLastSelected;

	int
		nTriggerDelay,
		nPortID,
		nInputBufferSize,
		nOutputBufferSize;


	CString 
		csSettings;


	// Retrieve DIO addresses.

	m_edtInputAddress.GetWindowText ( csInput );
	m_edtOutputAddress.GetWindowText ( csOutput );

	if ( !IsValidHex ( csInput, 3, 3 ) || !IsValidHex ( csInput, 3, 3 ) )
	{
		csTemp.LoadString ( IDS_INVALID_DIO_ADDRESS );
		AfxMessageBox ( csTemp );
		return;
	}


	nLastSelected = m_nLastSelected;

	m_nLastSelected = m_listDevice.GetCurSel();

	SetDeviceData();

	// Loop through all the devices ensuring that the values are valid.

	nSize = m_csaDeviceInfo.GetSize();

	bBad = FALSE;
	i = 0;
	while ( i < nSize && !bBad )
	{

		// Get device info from the device info array and parse out information.
		
		csDevice = m_csaDeviceInfo.GetAt ( i );

		nIndex = csDevice.Find ( ";" );

		if ( nIndex != -1 )
		{

			// Get name.

			csTemp = csDevice.Left ( nIndex );
			nLength = csDevice.GetLength();

			csDeviceName = csTemp;
			csDevice = csDevice.Right ( nLength - nIndex - 1 );

			// Get Port ID.

			nIndex = csDevice.Find ( ";" );
			if ( nIndex != -1 )
			{
				csTemp = csDevice.Left ( nIndex );
				nLength = csDevice.GetLength();

				csDevice = csDevice.Right ( nLength - nIndex - 1 );

				nTemp = atoi ( csTemp );

				if ( nTemp < 1 || nTemp > 12 )
				{
					bBad = TRUE;
					break;
				}
				if ( nPorts[nTemp-1] == 1 )
				{
					bBad = TRUE;
					break;
				}
				nPorts[nTemp-1] = 1;

				// Get settings.

				nIndex = csDevice.Find ( ";" );
				if ( nIndex != -1 )
				{
					csTemp = csDevice.Left ( nIndex );
					nLength = csDevice.GetLength();

					csDevice = csDevice.Right ( nLength - nIndex - 1 );

					if ( !IsValidSettings ( csTemp ) )
					{
						bBad = TRUE;
						break;
					}

					// Get in buffer size.

					nIndex = csDevice.Find ( ";" );
					if ( nIndex != -1 )
					{
						csTemp = csDevice.Left ( nIndex );
						nLength = csDevice.GetLength();

						csDevice = csDevice.Right ( nLength - nIndex - 1 );
						nTemp = atoi ( csTemp );
						if ( nTemp <=0 )
						{
							bBad = TRUE;
							break;
						}

						// Get out buffer size.

						nIndex = csDevice.Find ( ";" );
						if ( nIndex != -1 )
						{
							csTemp = csDevice.Left ( nIndex );
							nLength = csDevice.GetLength();

							csDevice = csDevice.Right ( nLength - nIndex - 1 );

							nTemp = atoi ( csTemp );
							if ( nTemp <=0 )
							{
								bBad = TRUE;
								break;
							}

							// Get trigger delay.

							nIndex = csDevice.Find ( ";" );
							if ( nIndex != -1 )
							{
								csTemp = csDevice.Left ( nIndex );

								if ( atoi ( csTemp ) <= 0 )
								{
									bBad = TRUE;
									break;
								}
							}
							else
								bBad = TRUE;
						}
						else
							bBad = TRUE;
					}
					else
						bBad = TRUE;
				}
				else
					bBad = TRUE;
			}
			else
				bBad = TRUE;
		}
		else
			bBad = TRUE;

		i++;
	}	// End while.

	if ( bBad )
	{
		csTemp.LoadString ( IDS_INVALID_DEVICE );
		csTemp += csDeviceName;
		AfxMessageBox ( csTemp );
		return;
	}

	// Add data checks out so update the database.
	SetDIOAddress ( csInput, csOutput );

	// Loop through all the devices and get corresponding data.
	nSize = m_csaDeviceInfo.GetSize();

	bBad = FALSE;
	for ( i = 0; i < nSize; i++ )
	{

		csDevice = m_csaDeviceInfo.GetAt ( i );

		nIndex = csDevice.Find ( ";" );

		if ( nIndex != -1 )
		{

			// Get name.

			csTemp = csDevice.Left ( nIndex );
			nLength = csDevice.GetLength();

			csDeviceName = csTemp;
			csDevice = csDevice.Right ( nLength - nIndex - 1 );

			// Get Port ID.

			nIndex = csDevice.Find ( ";" );
			if ( nIndex != -1 )
			{
				csTemp = csDevice.Left ( nIndex );
				nLength = csDevice.GetLength();

				csDevice = csDevice.Right ( nLength - nIndex - 1 );

				nPortID =  atoi ( csTemp );

				// Get settings.

				nIndex = csDevice.Find ( ";" );
				if ( nIndex != -1 )
				{
					csTemp = csDevice.Left ( nIndex );
					nLength = csDevice.GetLength();

					csDevice = csDevice.Right ( nLength - nIndex - 1 );

					csSettings = csTemp;

					// Get in buffer size.

					nIndex = csDevice.Find ( ";" );
					if ( nIndex != -1 )
					{
						csTemp = csDevice.Left ( nIndex );
						nLength = csDevice.GetLength();

						csDevice = csDevice.Right ( nLength - nIndex - 1 );

						nInputBufferSize =  atoi ( csTemp );

						// Get out buffer size.

						nIndex = csDevice.Find ( ";" );
						if ( nIndex != -1 )
						{
							csTemp = csDevice.Left ( nIndex );
							nLength = csDevice.GetLength();

							csDevice = csDevice.Right ( nLength - nIndex - 1 );

							nOutputBufferSize =  atoi ( csTemp );

							// Get trigger delay.

							nIndex = csDevice.Find ( ";" );
							if ( nIndex != -1 )
							{
								csTemp = csDevice.Left ( nIndex );

								nTriggerDelay =  atoi ( csTemp );
							}
							else
								bBad = TRUE;
						}
						else
							bBad = TRUE;
					}
					else
						bBad = TRUE;
				}
				else
					bBad = TRUE;
			}
			else
				bBad = TRUE;
		}
		else
			bBad = TRUE;
	
		if ( bBad )
		{
			csTemp.LoadString ( IDS_INVALID_DEVICE );
			csTemp += csDeviceName;
			AfxMessageBox ( csTemp );
			return;
		}

		if ( !SetComPortAttributes ( csDeviceName,
																 nTriggerDelay,
																 nInputBufferSize,
																 nOutputBufferSize,
																 nPortID,
																 csSettings ) )
			return;

	}



//	AfxMessageBox ("Device Configuration Error" );
	CDialog::OnOK();
}



void CInternalSetupDlg::OnClickCancel() 
{
	
	CDialog::OnCancel();

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		OnSelChangeDeviceList
//
//	Description:
//		Determine what is the selected device and update the appropriate fields.
//
//	Arguments:
//
//	Return:
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

void CInternalSetupDlg::OnSelChangeDeviceList() 
{
	
	CString csDevice;
	CString csTemp;
	
	int
		nIndex,
		nLength,
		nSelected;



	// Get selected device.

	nSelected = m_listDevice.GetCurSel();

	if ( nSelected != m_nLastSelected )
	{

		// Get current values for the previously selected device.

		SetDeviceData ( );

	}



	// Get device info from the device info array and parse out information.
	
	csDevice = m_csaDeviceInfo.GetAt ( nSelected );

	nIndex = csDevice.Find ( ";" );

	if ( nIndex != -1 )
	{

		// Get name and ignore.

		csTemp = csDevice.Left ( nIndex );
		nLength = csDevice.GetLength();

		csDevice = csDevice.Right ( nLength - nIndex - 1 );

		// Get Port ID.

		nIndex = csDevice.Find ( ";" );
		if ( nIndex != -1 )
		{
			csTemp = csDevice.Left ( nIndex );
			nLength = csDevice.GetLength();

			csDevice = csDevice.Right ( nLength - nIndex - 1 );

			m_edtPortID.SetWindowText ( csTemp );

			// Get settings.

			nIndex = csDevice.Find ( ";" );
			if ( nIndex != -1 )
			{
				csTemp = csDevice.Left ( nIndex );
				nLength = csDevice.GetLength();

				csDevice = csDevice.Right ( nLength - nIndex - 1 );

				m_edtSettings.SetWindowText ( csTemp );

				// Get in buffer size.

				nIndex = csDevice.Find ( ";" );
				if ( nIndex != -1 )
				{
					csTemp = csDevice.Left ( nIndex );
					nLength = csDevice.GetLength();

					csDevice = csDevice.Right ( nLength - nIndex - 1 );

					m_edtInBufferSize.SetWindowText ( csTemp );

					// Get out buffer size.

					nIndex = csDevice.Find ( ";" );
					if ( nIndex != -1 )
					{
						csTemp = csDevice.Left ( nIndex );
						nLength = csDevice.GetLength();

						csDevice = csDevice.Right ( nLength - nIndex - 1 );

						m_edtOutBufferSize.SetWindowText ( csTemp );

						// Get trigger delay.

						nIndex = csDevice.Find ( ";" );
						if ( nIndex != -1 )
						{

							csTemp = csDevice.Left ( nIndex );
							m_edtTriggerDelay.SetWindowText ( csTemp );
						}
					}
				}
			}
		}
	}

	m_nLastSelected = nSelected;

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		BuildDeviceData
//
//	Description:
//		Build the device info array from the data in the database.
//
//	Arguments:
//		Name of the device.
//
//	Return:
//		None
//
//	Called by:
//		OnInitDialog
//
/////////////////////////////////////////////////////////////////////////////////////

void CInternalSetupDlg::BuildDeviceData ( CString csDevice ) 
{

	CString csTemp;
	CString csInfo;

	int
		nTriggerDelay,
		nInputBufferSize,
		nOutputBufferSize,
		nPortID;

	CString
		csPortSettings;


	// Get the port info for the device.

	GetComPortAttributes ( csDevice,
													 &nTriggerDelay,
													 &nInputBufferSize,
													 &nOutputBufferSize,
													 &nPortID,
													 &csPortSettings );


	// Build device info string for string array.

	csInfo = csDevice + ";";

	csTemp.Format ( "%s;%d;%s;%d;%d;%d;", csDevice,
													  nPortID,
												     csPortSettings,
												     nInputBufferSize,
												     nOutputBufferSize,
													  nTriggerDelay );

	m_csaDeviceInfo.Add ( csTemp );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetDeviceData
//
//	Description:
//		Build the device info array from the selected device in the dialog box.
//
//	Arguments:
//		Name of the device.
//
//	Return:
//		None
//
//	Called by:
//		OnInitDialog
//
/////////////////////////////////////////////////////////////////////////////////////

void CInternalSetupDlg::SetDeviceData ( void ) 
{

	CString csTemp;
	CString csInfo;
	CString csDevice;


	m_listDevice.GetLBText ( m_nLastSelected, csDevice );

	csInfo = csDevice + ";";

	// Get each piece of data and build data string.

	m_edtPortID.GetWindowText ( csTemp );
	csInfo += csTemp + ";";

	m_edtSettings.GetWindowText ( csTemp );
	csInfo += csTemp + ";";

	m_edtInBufferSize.GetWindowText ( csTemp );
	csInfo += csTemp + ";";

	m_edtOutBufferSize.GetWindowText ( csTemp );
	csInfo += csTemp + ";";

	m_edtTriggerDelay.GetWindowText ( csTemp );
	csInfo += csTemp + ";";

	m_csaDeviceInfo.SetAt ( m_nLastSelected, csInfo );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		Open
//
//	Description:
//		Open the job database.
//
//	Arguments:
//		None.
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CInternalSetupDlg::Open ( void )  
{
static int nRepeatCount=0;
	CString csTemp;


	TRY
	{
		if (m_dbJobDatabase.IsOpen())
			m_dbJobDatabase.Close(); 
		m_dbJobDatabase.Open ( "c:\\computype\\database\\JobAdmin.mdb" );
	} 
	CATCH_ALL(e)
	{
		nRepeatCount+=1;

		if (nRepeatCount>3)
		{
			TCHAR   szCause[255];

 			e->GetErrorMessage(szCause,255); 
			csTemp.LoadString ( IDS_NO_DATABASE );
			AfxMessageBox ( csTemp );
			return FALSE;

		}
		else
		{
			if (m_dbJobDatabase.IsOpen())
				m_dbJobDatabase.Close(); 

			m_dbJobDatabase.m_pWorkspace->RepairDatabase("c:\\computype\\database\\JobAdmin.mdb"); 
			Open();	
		}

	
	}
	END_CATCH_ALL

	return ( TRUE );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		Close
//
//	Description:
//		Close the job database.
//
//	Arguments:
//		None.
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

void CInternalSetupDlg::Close ( void ) 
{

	m_dbJobDatabase.Close ();

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetComPortAttributes
//
//	Description:
//		Get the port attributes for the appropriate device.
//
//	Arguments:
//		None
//
//	Return:
//		Status.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CInternalSetupDlg::GetComPortAttributes ( CString csName,
													int *nTriggerDelay,
													int *nInputBufferSize,
													int *nOutputBufferSize,
													int *nPortID,
													CString *csPortSettings )
{

	int nCount;
	COleVariant var;
	CString csTemp;
	BOOL bGoodFind;

	CString
		csPrinter;


	CDaoRecordset	*rcdComPort;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdComPort = new CDaoRecordset( &m_dbJobDatabase );
	
	csTemp = "Select * from tbl_com_ports" ;   // CDaoRecordset does not like one-record recordset ? 

	rcdComPort->Open(AFX_DAO_USE_DEFAULT_TYPE, csTemp);

	nCount = rcdComPort->GetRecordCount();

	if ( nCount > 0 ) 
	{
		rcdComPort->MoveFirst();

		bGoodFind = FALSE;
		while ( !rcdComPort->IsEOF() && !bGoodFind )
		{

			// Find printer match.

			rcdComPort->GetFieldValue ( "Device_Name", var );
			csTemp = var.pbVal;
	
			if ( csName.CompareNoCase ( csTemp ) == 0 )
			{

				// Device found. Get the rest of the attributes.

				rcdComPort->GetFieldValue ( "Port_ID", var );
				csTemp = var.pbVal;

				int nPort;

				nPort = atoi ( csTemp );

				if ( nPort < 1 || nPort > 12 )
				{
					csTemp.LoadString ( IDS_INVALID_PORTID );
					AfxMessageBox ( csTemp );
					break;				
				}

				*nPortID = nPort;

				rcdComPort->GetFieldValue ( "Settings", var );
				csTemp = var.pbVal;
				*csPortSettings = csTemp;				

				rcdComPort->GetFieldValue ( "Trigger_Delay", var );
				csTemp = var.pbVal;
				*nTriggerDelay = atoi ( csTemp );				

				rcdComPort->GetFieldValue ( "Input_Buffer_Size", var );
				csTemp = var.pbVal;
				*nInputBufferSize = atoi ( csTemp );				

				rcdComPort->GetFieldValue ( "Output_Buffer_Size", var );
				csTemp = var.pbVal;
				*nOutputBufferSize = atoi ( csTemp );				

				bGoodFind = TRUE;

			}

			rcdComPort->MoveNext();
		}	// End while
	}
	else
	{
		bGoodFind = FALSE;
	}

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_INVALID_COMPORT_DATABASE );
		AfxMessageBox ( csTemp );
	}


	rcdComPort->Close();
	delete rcdComPort;

	// Close the database.

	Close();

	return ( bGoodFind );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetDIOAddress
//
//	Description:
//		Get the DIO addresses for the system.
//
//	Arguments:
//		Pointer to input address.
//		Pointer to output address.
//
//	Return:
//		Status.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CInternalSetupDlg::GetDIOAddress ( CString * csInput, CString * csOutput )
{

	int nCount;
	COleVariant var;
	CString csTemp;
	BOOL bGoodFind;


	CDaoRecordset	*rcdDIO;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdDIO = new CDaoRecordset( &m_dbJobDatabase );    // all of same kind pointer
	rcdDIO->Open(AFX_DAO_USE_DEFAULT_TYPE, "Select * from tbl_dio_settings");

	nCount = rcdDIO->GetRecordCount();

	if ( nCount > 0  )
	{
		rcdDIO->MoveFirst();

		while ( !rcdDIO->IsEOF() )
		{
			rcdDIO->GetFieldValue( "Name", var );
			csTemp = var.pbVal;
			
			if ( csTemp == "System_Input" )
			{
				rcdDIO->GetFieldValue ( "Base_Address", var );
				csTemp = var.pbVal;
				*csInput = csTemp;
			}

			if ( csTemp == "System_Output" )
			{
				rcdDIO->GetFieldValue ( "Base_Address", var );
				csTemp = var.pbVal;
				*csOutput = csTemp;
			}

			rcdDIO->MoveNext();
		}
	
		bGoodFind = TRUE;
	}
	else
	{

		bGoodFind = FALSE;
	}

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_INVALID_SYSTEMIO_DATABASE );
		AfxMessageBox ( csTemp );
	}


	rcdDIO->Close();
	delete rcdDIO;

	// Close the database.

	Close();

	return ( bGoodFind );

}


/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		GetDeviceNames
//
//	Description:
//		Get a list of the com port devices from the database.
//
//	Arguments:
//		Pointer to device string.
//
//	Return:
//		Status.
//
//	Called by:
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CInternalSetupDlg::GetDeviceNames ( CString *csDevices )
{

	int nCount;
	COleVariant var;
	CString csTemp;
	BOOL bGoodFind;

	CString
		csName = "";


	CDaoRecordset	*rcdComPort;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdComPort = new CDaoRecordset( &m_dbJobDatabase );
	
	csTemp = "Select * from tbl_com_ports" ;   // CDaoRecordset does not like one-record recordset ? 

	rcdComPort->Open(AFX_DAO_USE_DEFAULT_TYPE, csTemp);

	nCount = rcdComPort->GetRecordCount();

	if ( nCount > 0 ) 
	{
		rcdComPort->MoveFirst();

		bGoodFind = FALSE;
		while ( !rcdComPort->IsEOF() && !bGoodFind )
		{

			// Find device name.

			rcdComPort->GetFieldValue ( "Device_Name", var );
			csName += var.pbVal;
			
			csName += ";";

			rcdComPort->MoveNext();
		}	// End while

		bGoodFind = TRUE;

	}
	else
	{
		bGoodFind = FALSE;
	}

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_INVALID_COMPORT_DATABASE );
		AfxMessageBox ( csTemp );
	}

	rcdComPort->Close();
	delete rcdComPort;

	// Close the database.

	Close();

	*csDevices = csName;

	return ( bGoodFind );

}




/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetDIOAddress
//
//	Description:
//		Set the system DIO address information.
//
//	Arguments:
//		Input string.
//		Output string.
//
//	Return:
//		Status.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CInternalSetupDlg::SetDIOAddress ( CString csInput, CString csOutput )
{

	int nCount;
	COleVariant var;
	CString csTemp = " ";
	BOOL bGoodFind;

	char *p_chr_temp;

	CDaoRecordset	*rcdDIO;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdDIO = new CDaoRecordset( &m_dbJobDatabase );
	
	csTemp = "Select * from tbl_dio_settings" ;    

	rcdDIO->Open(AFX_DAO_USE_DEFAULT_TYPE, csTemp);

	nCount = rcdDIO->GetRecordCount();

	if ( nCount > 0 )
	{
		rcdDIO->MoveFirst();

		while ( !rcdDIO->IsEOF() )
		{
			rcdDIO->GetFieldValue( "Name", var);
			csTemp = var.pbVal;
			
			if ( csTemp == "System_Input" )
			{

				rcdDIO->Edit();
				p_chr_temp = csInput.GetBuffer ( csInput.GetLength() );
				rcdDIO->SetFieldValue ( "Base_Address", p_chr_temp );
				rcdDIO->Update();

			}
			if ( csTemp =="System_Output" )
			{

				rcdDIO->Edit();
				p_chr_temp = csOutput.GetBuffer ( csOutput.GetLength() );
				rcdDIO->SetFieldValue ( "Base_Address", p_chr_temp );
				rcdDIO->Update();

			}
			rcdDIO->MoveNext();
		}
	
		bGoodFind = TRUE;
	}
	else
	{

		bGoodFind = FALSE;
	}

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_INVALID_SYSTEMIO_DATABASE );
		AfxMessageBox ( csTemp );
	}


	rcdDIO->Close();
	delete rcdDIO;

	// Close the database.

	Close();

	return ( bGoodFind );

}



/////////////////////////////////////////////////////////////////////////////////////
//
//	Name: 
//		SetComPortAttributes
//
//	Description:
//		Set the port attributes for the appropriate device.
//
//	Arguments:
//		
//
//	Return:
//		Status.
//
//	Called by:
//		
//
/////////////////////////////////////////////////////////////////////////////////////

BOOL CInternalSetupDlg::SetComPortAttributes ( CString csName,
													int nTriggerDelay,
													int nInputBufferSize,
													int nOutputBufferSize,
													int nPortID,
													CString csPortSettings )
{

	int nCount;
	COleVariant var;
	CString csTemp = " ";
	BOOL bGoodFind;

	char *p_chr_temp;

	CDaoRecordset	*rcdComPort;


	// Open the database.

	if ( !Open() )
		return ( FALSE );

	rcdComPort = new CDaoRecordset( &m_dbJobDatabase );
	
	csTemp = "Select * from tbl_com_ports" ;    

	rcdComPort->Open(AFX_DAO_USE_DEFAULT_TYPE, csTemp);

	nCount =rcdComPort->GetRecordCount();

	if ( nCount > 0 )
	{
		rcdComPort->MoveFirst();

		while ( !rcdComPort->IsEOF() )
		{
			
			rcdComPort->GetFieldValue ( "Device_Name", var );
			csTemp = var.pbVal;
	
			if ( csName.CompareNoCase ( csTemp ) == 0 )
			{

				// Device found. Update the record.

				csTemp.Format ( "%d", nPortID );
				rcdComPort->Edit();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdComPort->SetFieldValue ( "Port_ID", p_chr_temp );
				rcdComPort->Update();

				csTemp = csPortSettings;
				rcdComPort->Edit();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdComPort->SetFieldValue ( "Settings", p_chr_temp );
				rcdComPort->Update();

				csTemp.Format ( "%d", nTriggerDelay );
				rcdComPort->Edit();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdComPort->SetFieldValue ( "Trigger_Delay", p_chr_temp );
				rcdComPort->Update();

				csTemp.Format ( "%d", nInputBufferSize );
				rcdComPort->Edit();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdComPort->SetFieldValue ( "Input_Buffer_Size", p_chr_temp );
				rcdComPort->Update();

				csTemp.Format ( "%d", nOutputBufferSize );
				rcdComPort->Edit();
				p_chr_temp = csTemp.GetBuffer ( csTemp.GetLength() );
				rcdComPort->SetFieldValue ( "Output_Buffer_Size", p_chr_temp );
				rcdComPort->Update();

			}
			rcdComPort->MoveNext();
		}
	
		bGoodFind = TRUE;
	}
	else
	{

		bGoodFind = FALSE;
	}

	if ( !bGoodFind )
	{
		csTemp.LoadString ( IDS_INVALID_SYSTEMIO_DATABASE );
		AfxMessageBox ( csTemp );
	}


	rcdComPort->Close();
	delete rcdComPort;

	// Close the database.

	Close();

	return ( bGoodFind );

}



BOOL CInternalSetupDlg::IsNumeric ( CString csNumber )
{

	int int_len = csNumber.GetLength();
	int i;
	char chr_temp;


	if (int_len < 1 )
		return FALSE;

	for (i = 0; i < int_len; i++)
	{
			chr_temp = csNumber[i];
			
			if (((int(chr_temp) < 48) || (int(chr_temp) > 57 )))
			{
				if(!((int(chr_temp) == 43)|| (int(chr_temp) == 45)))
						return FALSE;
			}
	}

	return TRUE;

}






/////////////////////////////////////////////////////////////////////////////
//
//	Name:
//		IsValidHex
//
//
//	Description:		
//		Determine if the string is a valid hex number.
//
//	Arguments:
//		Hex string.
//		Minimum size in characters.
//		Maximum size in characters.
//	
//	Returns:
//		Status
//
//	Called By:
//
//////////////////////////////////////////////////////////////////////////////

BOOL CInternalSetupDlg::IsValidHex ( CString csNumber, int nMinSize, int nMaxSize )
{

	int
		i,
		nLength;

	CString
		csTemp;


	// Check for correct length.

	nLength = csNumber.GetLength();

	if ( nLength < nMinSize || nLength > nMaxSize )
		return ( FALSE );

	// Check for correct characters.

	for ( i = 0; i < nLength; i++ )
	{
		csTemp = csNumber.Mid ( i, 1 );
		if ( csTemp != "0" && csTemp != "1" && csTemp != "2" && csTemp != "3" &&
			  csTemp != "4" && csTemp != "5" && csTemp != "6" && csTemp != "7" &&
			  csTemp != "8" && csTemp != "9" && csTemp != "a" && csTemp != "A" &&
			  csTemp != "b" && csTemp != "B" && csTemp != "c" && csTemp != "C" &&
			  csTemp != "d" && csTemp != "D" && csTemp != "e" && csTemp != "E" &&
			  csTemp != "f" && csTemp != "F" )
			return ( FALSE );
	}

	return ( TRUE );

}


BOOL CInternalSetupDlg::IsValidSettings ( CString csSettings )
{

	CString csTemp;

	int
		nIndex,
		nLength;


	// Settings string should have the format of :
	//   baudrate,parity,databits,stopbit
	//
	//  Ex. 9600,N,8,1

	nIndex = csSettings.Find ( "," );
	nLength = csSettings.GetLength();
	if ( nIndex < 1 )
		return ( FALSE );

	csTemp = csSettings.Left ( nIndex );

	if (csTemp != "38400" &&
		csTemp != "19200" &&
		  csTemp != "9600" &&
		  csTemp != "4800" &&
		  csTemp != "2400" &&
		  csTemp != "1200" &&
		  csTemp != "600" &&
		  csTemp != "300" )
		return ( FALSE );

	csSettings = csSettings.Right ( nLength - nIndex - 1 );

	nIndex = csSettings.Find ( "," );
	nLength = csSettings.GetLength();
	if ( nIndex < 1 )
		return ( FALSE );

	csTemp = csSettings.Left ( nIndex );

	if ( csTemp != "N" &&
		  csTemp != "E" &&
		  csTemp != "O" )
		return ( FALSE );

	csSettings = csSettings.Right ( nLength - nIndex - 1 );

	nIndex = csSettings.Find ( "," );
	nLength = csSettings.GetLength();
	if ( nIndex < 1 )
		return ( FALSE );

	csTemp = csSettings.Left ( nIndex );

	if ( csTemp != "7" &&
		  csTemp != "8" )
		return ( FALSE );

	csSettings = csSettings.Right ( nLength - nIndex - 1 );

	if ( csSettings != "1" &&
		  csSettings != "0" )
		return ( FALSE );

	return ( TRUE );

}


BOOL CInternalSetupDlg::CheckPositionFormat ( CString csPosition )
{

	int
		nLength;

	CString
		csRot;


	// The position must have the format of x,y;rot
	//		where:
	//			x = 6 digits,
	//			y = 6 digits,
	//			rot = 0 or 90.

	nLength = csPosition.GetLength();

	if ( csPosition[6] != ',' || csPosition[13] != ';' )
		return ( FALSE );

	csRot = csPosition.Right ( nLength - 14 );

	if ( !IsNumeric ( csPosition.Left ( 6 ) ) || !IsNumeric ( csPosition.Mid ( 7, 6 ) ) ||
		  !IsNumeric ( csRot )  || ( csRot != "0" && csRot != "00" && csRot != "90" ) )
		return ( FALSE );

	return ( TRUE );

}



