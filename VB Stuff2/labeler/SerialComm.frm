VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "tabctl32.ocx"
Object = "{0BA686C6-F7D3-101A-993E-0000C0EF6F5E}#1.0#0"; "threed32.ocx"
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form frmSerialComm 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "Serial Comm Monitor"
   ClientHeight    =   4740
   ClientLeft      =   1455
   ClientTop       =   4125
   ClientWidth     =   4995
   ControlBox      =   0   'False
   Icon            =   "SerialComm.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   4740
   ScaleWidth      =   4995
   ShowInTaskbar   =   0   'False
   Begin VB.Timer tmrWatchDog 
      Enabled         =   0   'False
      Index           =   12
      Left            =   2310
      Top             =   4335
   End
   Begin VB.Timer tmrWatchDog 
      Enabled         =   0   'False
      Index           =   11
      Left            =   1755
      Top             =   4335
   End
   Begin VB.Timer tmrWatchDog 
      Enabled         =   0   'False
      Index           =   10
      Left            =   1185
      Top             =   4335
   End
   Begin VB.Timer tmrWatchDog 
      Enabled         =   0   'False
      Index           =   9
      Left            =   630
      Top             =   4335
   End
   Begin VB.Timer tmrWatchDog 
      Enabled         =   0   'False
      Index           =   8
      Left            =   3960
      Top             =   4335
   End
   Begin VB.Timer tmrWatchDog 
      Enabled         =   0   'False
      Index           =   7
      Left            =   3420
      Top             =   4335
   End
   Begin VB.Timer tmrWatchDog 
      Enabled         =   0   'False
      Index           =   6
      Left            =   2865
      Top             =   4335
   End
   Begin VB.Timer tmrWatchDog 
      Enabled         =   0   'False
      Index           =   5
      Left            =   75
      Top             =   4335
   End
   Begin Threed.SSFrame ssfViewPort 
      Height          =   615
      Left            =   60
      TabIndex        =   0
      Top             =   -30
      Width           =   4920
      _Version        =   65536
      _ExtentX        =   8678
      _ExtentY        =   1085
      _StockProps     =   14
      Caption         =   "View port:"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ShadowStyle     =   1
      Begin Threed.SSOption ssoViewPort 
         Height          =   255
         Index           =   8
         Left            =   2295
         TabIndex        =   9
         Top             =   225
         Width           =   495
         _Version        =   65536
         _ExtentX        =   873
         _ExtentY        =   450
         _StockProps     =   78
         Caption         =   "8"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
      End
      Begin Threed.SSOption ssoViewPort 
         Height          =   255
         Index           =   7
         Left            =   1770
         TabIndex        =   8
         Top             =   225
         Width           =   495
         _Version        =   65536
         _ExtentX        =   873
         _ExtentY        =   450
         _StockProps     =   78
         Caption         =   "7"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
      End
      Begin Threed.SSOption ssoViewPort 
         Height          =   255
         Index           =   6
         Left            =   1245
         TabIndex        =   7
         Top             =   225
         Width           =   495
         _Version        =   65536
         _ExtentX        =   873
         _ExtentY        =   450
         _StockProps     =   78
         Caption         =   "6"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
      End
      Begin Threed.SSOption ssoViewPort 
         Height          =   255
         Index           =   5
         Left            =   705
         TabIndex        =   6
         Top             =   225
         Width           =   495
         _Version        =   65536
         _ExtentX        =   873
         _ExtentY        =   450
         _StockProps     =   78
         Caption         =   "5"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
      End
      Begin Threed.SSOption ssoViewPort 
         Height          =   255
         Index           =   12
         Left            =   4350
         TabIndex        =   5
         Top             =   225
         Width           =   495
         _Version        =   65536
         _ExtentX        =   873
         _ExtentY        =   450
         _StockProps     =   78
         Caption         =   "12"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
      End
      Begin Threed.SSOption ssoViewPort 
         Height          =   255
         Index           =   11
         Left            =   3855
         TabIndex        =   4
         Top             =   225
         Width           =   495
         _Version        =   65536
         _ExtentX        =   873
         _ExtentY        =   450
         _StockProps     =   78
         Caption         =   "11"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
      End
      Begin Threed.SSOption ssoViewPort 
         Height          =   255
         Index           =   10
         Left            =   3330
         TabIndex        =   3
         Top             =   225
         Width           =   495
         _Version        =   65536
         _ExtentX        =   873
         _ExtentY        =   450
         _StockProps     =   78
         Caption         =   "10"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
      End
      Begin Threed.SSOption ssoViewPort 
         Height          =   255
         Index           =   9
         Left            =   2790
         TabIndex        =   2
         Top             =   225
         Width           =   495
         _Version        =   65536
         _ExtentX        =   873
         _ExtentY        =   450
         _StockProps     =   78
         Caption         =   "9"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
      End
      Begin Threed.SSOption ssoViewPort 
         Height          =   255
         Index           =   0
         Left            =   105
         TabIndex        =   1
         Top             =   210
         Width           =   495
         _Version        =   65536
         _ExtentX        =   873
         _ExtentY        =   450
         _StockProps     =   78
         Caption         =   "All"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Value           =   -1  'True
      End
   End
   Begin TabDlg.SSTab sstMonitor 
      Height          =   3165
      Left            =   75
      TabIndex        =   10
      Top             =   645
      Width           =   4845
      _ExtentX        =   8546
      _ExtentY        =   5583
      _Version        =   327681
      Tab             =   2
      TabHeight       =   529
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      TabCaption(0)   =   "Output"
      Tab(0).ControlEnabled=   0   'False
      Tab(0).Control(0)=   "cmdClearIOutputBuffer"
      Tab(0).Control(1)=   "txbOutputBuffer"
      Tab(0).ControlCount=   2
      TabCaption(1)   =   "Input"
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "txbInputBuffer"
      Tab(1).Control(1)=   "cmdClearInputBuffer"
      Tab(1).ControlCount=   2
      TabCaption(2)   =   "Event && Error"
      TabPicture(2)   =   "SerialComm.frx":0442
      Tab(2).ControlEnabled=   -1  'True
      Tab(2).Control(0)=   "txbMessage"
      Tab(2).Control(0).Enabled=   0   'False
      Tab(2).Control(1)=   "cmdClearMessage"
      Tab(2).Control(1).Enabled=   0   'False
      Tab(2).ControlCount=   2
      Begin VB.CommandButton cmdClearMessage 
         Caption         =   "Clear"
         Height          =   255
         Left            =   3990
         TabIndex        =   16
         Top             =   2805
         Width           =   735
      End
      Begin VB.TextBox txbMessage 
         Height          =   2295
         Left            =   105
         MultiLine       =   -1  'True
         ScrollBars      =   3  'Both
         TabIndex        =   15
         Text            =   "SerialComm.frx":045E
         Top             =   435
         Width           =   4590
      End
      Begin VB.CommandButton cmdClearInputBuffer 
         Caption         =   "Clear"
         Height          =   255
         Left            =   -71010
         TabIndex        =   14
         Top             =   2805
         Width           =   735
      End
      Begin VB.TextBox txbInputBuffer 
         Height          =   2310
         Left            =   -74865
         MultiLine       =   -1  'True
         ScrollBars      =   3  'Both
         TabIndex        =   13
         Text            =   "SerialComm.frx":0469
         Top             =   390
         Width           =   4575
      End
      Begin VB.CommandButton cmdClearIOutputBuffer 
         Caption         =   "Clear"
         Height          =   255
         Left            =   -71025
         TabIndex        =   12
         Top             =   2820
         Width           =   735
      End
      Begin VB.TextBox txbOutputBuffer 
         Height          =   2340
         Left            =   -74850
         MultiLine       =   -1  'True
         ScrollBars      =   3  'Both
         TabIndex        =   11
         Text            =   "SerialComm.frx":047A
         Top             =   405
         Width           =   4560
      End
   End
   Begin MSCommLib.MSComm comSerialComm 
      Index           =   12
      Left            =   2310
      Top             =   3855
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327681
      CommPort        =   12
      DTREnable       =   -1  'True
      Handshaking     =   2
      NullDiscard     =   -1  'True
      OutBufferSize   =   1024
      ParityReplace   =   0
      RThreshold      =   1
      SThreshold      =   1
   End
   Begin MSCommLib.MSComm comSerialComm 
      Index           =   11
      Left            =   1755
      Top             =   3855
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327681
      CommPort        =   11
      DTREnable       =   -1  'True
      Handshaking     =   2
      NullDiscard     =   -1  'True
      OutBufferSize   =   1024
      ParityReplace   =   0
      RThreshold      =   1
      SThreshold      =   1
   End
   Begin MSCommLib.MSComm comSerialComm 
      Index           =   10
      Left            =   1185
      Top             =   3855
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327681
      CommPort        =   10
      DTREnable       =   -1  'True
      Handshaking     =   2
      NullDiscard     =   -1  'True
      OutBufferSize   =   1024
      ParityReplace   =   0
      RThreshold      =   1
      SThreshold      =   1
   End
   Begin MSCommLib.MSComm comSerialComm 
      Index           =   9
      Left            =   630
      Top             =   3855
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327681
      CommPort        =   9
      DTREnable       =   -1  'True
      Handshaking     =   2
      NullDiscard     =   -1  'True
      OutBufferSize   =   1024
      ParityReplace   =   0
      RThreshold      =   1
      SThreshold      =   1
   End
   Begin MSCommLib.MSComm comSerialComm 
      Index           =   8
      Left            =   3960
      Top             =   3855
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327681
      CommPort        =   8
      DTREnable       =   -1  'True
      Handshaking     =   2
      NullDiscard     =   -1  'True
      OutBufferSize   =   1024
      ParityReplace   =   0
      RThreshold      =   1
      SThreshold      =   1
   End
   Begin MSCommLib.MSComm comSerialComm 
      Index           =   7
      Left            =   3420
      Top             =   3855
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327681
      CommPort        =   7
      DTREnable       =   -1  'True
      Handshaking     =   2
      NullDiscard     =   -1  'True
      OutBufferSize   =   1024
      ParityReplace   =   0
      RThreshold      =   1
      SThreshold      =   1
   End
   Begin MSCommLib.MSComm comSerialComm 
      Index           =   6
      Left            =   2865
      Top             =   3855
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327681
      CommPort        =   6
      DTREnable       =   -1  'True
      NullDiscard     =   -1  'True
      OutBufferSize   =   1024
      ParityReplace   =   0
      RThreshold      =   1
      ParitySetting   =   2
      DataBits        =   7
      SThreshold      =   1
   End
   Begin MSCommLib.MSComm comSerialComm 
      Index           =   5
      Left            =   75
      Top             =   3855
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327681
      CommPort        =   5
      DTREnable       =   -1  'True
      Handshaking     =   2
      NullDiscard     =   -1  'True
      OutBufferSize   =   1024
      ParityReplace   =   0
      RThreshold      =   1
      SThreshold      =   1
   End
End
Attribute VB_Name = "frmSerialComm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'************************************************************************
'*           Computype, Inc.
'*       NextStep Automation Group
'*
'*     © Copyright 1997 Computype, Inc.
'*
'*        2-Axis Label Applicator
'*           Control software
'*             Main form
'*
'*
'*    Customer: Ford Markham
'*
'*
'*
'*    Date of origin: 05/01/98
'*    Original author: Michael D. Reed
'*     Version Author: David Petersen
'*
'* Form purpose:
'*
'*
'*
'************************************************************************
Option Explicit
'******************************************************************

Private Const m_intMAX_DISPLAY = 4000
Private m_intTestPort As Integer

Private m_colControler As New Collection
Private m_colPortName As New Collection
Private m_colDeviceName As New Collection

Private Sub cmdClearIOutputBuffer_Click()

   txbOutputBuffer.Text = ""
   
End Sub 'cmdClearIOutputBuffer_Click

Private Sub cmdClearMessage_Click()

   txbMessage.Text = ""
   
End Sub 'cmdClearMessage_Click


Private Sub cmdClearInputBuffer_Click()

   txbInputBuffer.Text = ""
   
End Sub 'cmdClearInputBuffer_Click



Private Sub comSerialComm_OnComm(Index As Integer)

   #If ccShip_Ver Then
      On Error GoTo comSerialComm_OnComm_Error
   #Else
      On Error GoTo 0
   #End If

   With comSerialComm(Index)
      DspEvent intPort:=Index, intCommEvent:=.CommEvent
      If .CommEvent = comEvReceive Then
         m_colControler.Item(CStr(Index)).TempBuffer strCharsIn:=.Input
      End If
   End With 'comSerialComm
   
   Exit Sub

comSerialComm_OnComm_Error:

   ProccessError "comSerialComm_OnComm", Name, Err.Number, Err.Description

End Sub    'comSerialComm_OnComm


Private Sub Form_Load()

   #If ccShip_Ver Then
      On Error GoTo Form_Load_Error
   #Else
      On Error GoTo 0
   #End If

   txbInputBuffer.Text = ""
   txbOutputBuffer.Text = ""
   txbMessage.Text = ""
   
   Me.Height = 4380
   Me.Left = 10
   Me.Top = 10
   m_intTestPort = 0
   
   ssoViewPort(0).Value = True

   modUtilities.SetSerialMonitorForm Me

   Exit Sub

Form_Load_Error:

   ProccessError "Form_Load", Name, Err.Number, Err.Description

End Sub 'Form_Load

Private Sub Form_Unload(Cancel As Integer)
'  Stop the program when the form is closed
   
   Dim i As Integer
   
   #If ccShip_Ver Then
      On Error GoTo Form_Unload_Error
   #Else
      On Error GoTo 0
   #End If

   For i = 5 To 12
      If comSerialComm(i).PortOpen Then
         comSerialComm(i).PortOpen = False
      End If
   Next i
   
   Exit Sub

Form_Unload_Error:

   ProccessError "Form_Unload", Name, Err.Number, Err.Description

End Sub 'Form_Unload









Private Sub DspEvent(intPort As Integer, intCommEvent As Integer)

   Dim strMessage As String
   
   #If ccShip_Ver Then
      On Error GoTo DspEvent_Error
   #Else
      On Error GoTo 0
   #End If

    Select Case intCommEvent
        Case comEvReceive
            strMessage = Format(Now, "Long time") & "  v->" & "Receive"
        Case comEvSend
             strMessage = Format(Now, "Long time") & " v->" & "Send"
        Case comEvCTS
            strMessage = Format(Now, "Long time") & " v->" & "Change in CTS Detected"
        Case comEvDSR
            strMessage = Format(Now, "Long time") & " v->" & "Change in DSR Detected"
        Case comEvCD
            strMessage = Format(Now, "Long time") & " v->" & "Change in CD Detected"
        Case comEvRing
            strMessage = Format(Now, "Long time") & " v->" & "The Phone is Ringing"
        Case comEvEOF
            strMessage = Format(Now, "Long time") & " v->" & "End of File Detected"
        Case comBreak
            strMessage = Format(Now, "Long time") & " v->" & "Break Received"
        Case comCTSTO
            strMessage = Format(Now, "Long time") & " e->" & "CTS Timeout"
        Case comDSRTO
            strMessage = Format(Now, "Long time") & " e->" & "DSR Timeout"
        Case comFrame
            strMessage = Format(Now, "Long time") & " v->" & "Framing Error"
        Case comOverrun
            strMessage = Format(Now, "Long time") & " e->" & "Overrun Error"
        Case comCDTO
            strMessage = Format(Now, "Long time") & " e->" & "Carrier Detect Timeout"
        Case comRxOver
            strMessage = Format(Now, "Long time") & " e->" & "Receive Buffer Overflow"
        Case comRxParity
            strMessage = Format(Now, "Long time") & " v->" & "Parity Error"
        Case comTxFull
            strMessage = Format(Now, "Long time") & " e->" & "Transmit Buffer Full"
        Case Else
            strMessage = Format(Now, "Long time") & " e->" & intCommEvent & "--Unknown error or event"
    End Select

    DisplayIOMsg intPortID:=intPort, vntMsg:=strMessage & vbCrLf

   Exit Sub

DspEvent_Error:

   ProccessError "DspEvent", Name, Err.Number, Err.Description

End Sub 'RecEvnet

Public Function Initialize(objController As Object, strDeviceName As String) As Boolean
   
   Dim dbLabelerDataBase As Database
   Dim qdfSerialPort As QueryDef
   Dim snpSerialPort As Recordset
   Dim intPortIndex As Integer
   Dim intWatchDogTimer As Integer
   
   #If ccShip_Ver Then
      On Error GoTo Initialize_Error
   #Else
      On Error GoTo 0
   #End If
   
      '  Set Lucent point data
   '  Open the data base, define the quire and get the data points using the JobID
   Set dbLabelerDataBase = Workspaces(0).OpenDatabase(modMain.GetConfigurationDataBaseName)
   Set qdfSerialPort = dbLabelerDataBase.QueryDefs(modMain.GetSerialPortConfiguration)
   qdfSerialPort.Parameters![strDeviceName] = strDeviceName
   Set snpSerialPort = qdfSerialPort.OpenRecordset(dbOpenSnapshot)
   

   intPortIndex = snpSerialPort![PortIndex]
   
   m_colControler.Add Key:=CStr(intPortIndex), Item:=objController
   m_colPortName.Add Key:=CStr(intPortIndex), Item:=snpSerialPort![PortName]
   m_colDeviceName.Add Key:=CStr(intPortIndex), Item:=strDeviceName
   Dim ntest As Integer
   With comSerialComm(intPortIndex)
      .CDTimeout = snpSerialPort![CDTimeout]
      .CTSTimeout = snpSerialPort![CTSTimeout]
      .DSRTimeout = snpSerialPort![DSRTimeout]
      .DTREnable = snpSerialPort![DTREnable]
      .Handshaking = snpSerialPort![Handshaking]
      .InBufferSize = snpSerialPort![InBufferSize]
      .InputLen = snpSerialPort![InputLen]
      .NullDiscard = snpSerialPort![NullDiscard]
      .OutBufferSize = snpSerialPort![OutBufferSize]
      .ParityReplace = Left(snpSerialPort![ParityReplace], 1) ' Just get the first char
      .RThreshold = snpSerialPort![RThreshold]
      .RTSEnable = snpSerialPort![RTSEnable]
      .Settings = snpSerialPort![PortSettings]
      .SThreshold = snpSerialPort![SThreshold]
      If Not g_blnSimulator Then
         '  Now open the port
         .PortOpen = True
      End If
   End With 'frmSerialComm

   intWatchDogTimer = snpSerialPort![WatchDogTimer]
   tmrWatchDog(intPortIndex).Interval = intWatchDogTimer
   
   With objController
      .DeviceName = strDeviceName
      .PortName = snpSerialPort![PortName]
      .PortIndex = intPortIndex
'      .TxTerminatingChr = modUtilities.ConvertTerminatingChr(snpSerialPort![TxTerminatingChr])
      .WatchDogTimer = (intWatchDogTimer <> 0)
   End With 'objController
   
   Initialize = True
   
   Exit Function
   
Initialize_Error:

   ProccessError "Initialize", Name, Err.Number, Err.Description
   Initialize = False
  
End Function 'Initialize

Public Sub DisplayIOMsg(intPortID As Integer, _
                        Optional vntInMsg As Variant, _
                        Optional vntOutMsg As Variant, _
                        Optional vntMsg As Variant)
                        
   Dim strTempBuf As String
   
   #If ccShip_Ver Then
      On Error GoTo DisplayIOMsg_Error
   #Else
      On Error GoTo 0
   #End If

   If (intPortID = m_intTestPort) Or (m_intTestPort = 0) Then
      If m_intTestPort = 0 Then
         strTempBuf = Format(intPortID, "00") & ":"
     End If
      If Not IsMissing(vntInMsg) Then
         DisplayMsg txbInputBuffer, strTempBuf & CStr(vntInMsg)
         modUtilities.Log "Input serial port: " & intPortID, CStr(vntInMsg)
      End If
      If Not IsMissing(vntOutMsg) Then
         DisplayMsg txbOutputBuffer, strTempBuf & CStr(vntOutMsg)
         modUtilities.Log "Serial Port: " & intPortID, CStr(vntOutMsg)
      End If
      If Not IsMissing(vntMsg) Then
         DisplayMsg txbMessage, strTempBuf & CStr(vntMsg)
         modUtilities.Log "Serial Port: " & intPortID, CStr(vntMsg)
      End If
   End If
   
   Exit Sub

DisplayIOMsg_Error:

   ProccessError "DisplayIOMsg", Name, Err.Number, Err.Description

End Sub 'DisplayIOMsg

Private Sub DisplayMsg(txbControl As Control, strMsg As String)
   
   #If ccShip_Ver Then
      On Error GoTo DisplayMsg_Error
   #Else
      On Error GoTo 0
   #End If

   If Len(txbControl.Text) > m_intMAX_DISPLAY Then
      txbControl.Text = ""
   End If
   
   If Right(strMsg, 2) <> vbCrLf Then
      strMsg = strMsg & vbCrLf
   End If
   
   txbControl.Text = txbControl.Text & strMsg
   txbControl.SelStart = Len(txbControl)
   
   Exit Sub

DisplayMsg_Error:

   ProccessError "DisplayMsg", Name, Err.Number, Err.Description

End Sub 'DisplayMsg

Private Sub ssoViewPort_Click(Index As Integer, Value As Integer)

   m_intTestPort = Index
   
End Sub 'ssoViewPort_Click



Private Sub tmrWatchDog_Timer(Index As Integer)
   
   #If ccShip_Ver Then
      On Error GoTo tmrWatchDog_Timer_Error
   #Else
      On Error GoTo 0
   #End If

   DisplayIOMsg intPortID:=Index, vntMsg:="Time Out" & vbCrLf
   
   m_colControler.Item(CStr(Index)).TimeUp
   
   Exit Sub

tmrWatchDog_Timer_Error:

   ProccessError "tmrWatchDog_Timer", Name, Err.Number, Err.Description

End Sub 'tmrWatchDog_Timer


