VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form frmScanner 
   Caption         =   "SICK Scanner View Monitor"
   ClientHeight    =   4140
   ClientLeft      =   1650
   ClientTop       =   1935
   ClientWidth     =   7440
   LinkTopic       =   "Form1"
   ScaleHeight     =   4140
   ScaleWidth      =   7440
   Begin VB.Frame Frame1 
      Caption         =   "Disable Scanner"
      Height          =   855
      Left            =   120
      TabIndex        =   23
      Top             =   3240
      Width           =   3135
      Begin VB.TextBox txbDisableScannerPW 
         Height          =   375
         Left            =   1800
         TabIndex        =   25
         Top             =   240
         Visible         =   0   'False
         Width           =   1215
      End
      Begin VB.CheckBox chkDisableScanner 
         Caption         =   "Disable Scanner"
         Height          =   255
         Left            =   120
         TabIndex        =   24
         Top             =   360
         Width           =   1575
      End
   End
   Begin VB.Frame fraStatisTics 
      Caption         =   "Scaner Statistics"
      Height          =   3135
      Left            =   4080
      TabIndex        =   8
      Top             =   120
      Width           =   3135
      Begin VB.TextBox txtCodeContinuity 
         Height          =   285
         Left            =   2160
         TabIndex        =   22
         Top             =   2520
         Width           =   855
      End
      Begin VB.TextBox txtCodeReliability 
         Height          =   285
         Left            =   2160
         TabIndex        =   20
         Top             =   2160
         Width           =   855
      End
      Begin VB.TextBox txtRequiredScans 
         Height          =   285
         Left            =   2160
         TabIndex        =   18
         Top             =   1800
         Width           =   855
      End
      Begin VB.TextBox txtCodeLength 
         Height          =   285
         Left            =   2160
         TabIndex        =   16
         Top             =   1440
         Width           =   855
      End
      Begin VB.TextBox txtCodePosition 
         Height          =   285
         Left            =   2160
         TabIndex        =   14
         Top             =   1080
         Width           =   855
      End
      Begin VB.TextBox txtIDQuality 
         Height          =   285
         Left            =   2160
         TabIndex        =   12
         Top             =   720
         Width           =   855
      End
      Begin VB.TextBox txtDReadInterval 
         Height          =   285
         Left            =   2160
         TabIndex        =   10
         Top             =   360
         Width           =   855
      End
      Begin VB.Label lblCodeContinuity 
         Caption         =   "Code Continuity:"
         Height          =   255
         Left            =   840
         TabIndex        =   21
         Top             =   2520
         Width           =   1215
      End
      Begin VB.Label lblCodeReliability 
         Caption         =   "Code Reliability:"
         Height          =   255
         Left            =   840
         TabIndex        =   19
         Top             =   2160
         Width           =   1215
      End
      Begin VB.Label lblRequiredScans 
         Caption         =   "Required Scans:"
         Height          =   255
         Left            =   720
         TabIndex        =   17
         Top             =   1800
         Width           =   1335
      End
      Begin VB.Label lblCodeLength 
         Caption         =   "Code Length:"
         Height          =   255
         Left            =   960
         TabIndex        =   15
         Top             =   1440
         Width           =   1095
      End
      Begin VB.Label lblCodePosition 
         Caption         =   "Code Position:"
         Height          =   255
         Left            =   960
         TabIndex        =   13
         Top             =   1080
         Width           =   1095
      End
      Begin VB.Label lblIDQuality 
         Caption         =   "Identification Quality:"
         Height          =   255
         Left            =   480
         TabIndex        =   11
         Top             =   720
         Width           =   1575
      End
      Begin VB.Label lblDReadInterval 
         Caption         =   "Duration Of Read Interval:"
         Height          =   255
         Left            =   120
         TabIndex        =   9
         Top             =   360
         Width           =   1935
      End
   End
   Begin VB.CheckBox chkViewStatistics 
      Caption         =   "Vew Statistics"
      Height          =   255
      Left            =   1200
      TabIndex        =   7
      Top             =   2880
      Width           =   2055
   End
   Begin VB.Frame fraScannerOptions 
      Caption         =   "Scanner Monitor Options"
      Height          =   2535
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   3855
      Begin VB.CommandButton Command2 
         Caption         =   "Self Test"
         Height          =   495
         Left            =   2280
         TabIndex        =   6
         Top             =   1800
         Width           =   1335
      End
      Begin VB.CommandButton cmdXmit 
         Caption         =   "Trigger Scanner"
         Height          =   495
         Left            =   240
         TabIndex        =   5
         Top             =   1800
         Width           =   1815
      End
      Begin VB.TextBox txbScannerOutput 
         Height          =   765
         Left            =   240
         MultiLine       =   -1  'True
         TabIndex        =   4
         Top             =   960
         Width           =   3375
      End
      Begin VB.CheckBox chkDiagnostic 
         Caption         =   "Enable Diagnostics"
         Height          =   255
         Left            =   240
         TabIndex        =   3
         Top             =   720
         Width           =   2055
      End
      Begin VB.CheckBox chkViewBarCode 
         Caption         =   "View Scanned Bar Code"
         Height          =   255
         Left            =   240
         TabIndex        =   2
         Top             =   360
         Width           =   2295
      End
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Exit"
      Height          =   615
      Left            =   3360
      TabIndex        =   0
      Top             =   3480
      Width           =   735
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   4800
      Top             =   3480
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   327681
      DTREnable       =   -1  'True
      BaudRate        =   2400
      SThreshold      =   1
   End
   Begin MSCommLib.MSComm MSComm2 
      Left            =   5640
      Top             =   3480
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   327681
      CommPort        =   8
      DTREnable       =   -1  'True
      RThreshold      =   1
      BaudRate        =   2400
      SThreshold      =   1
   End
End
Attribute VB_Name = "frmScanner"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public m_strScannedBottomLabel As String
Dim m_strScannerPassWord As String
Private Sub chkDiagnostic_Click()
   If chkDiagnostic.Value = 1 Then
      modMain.m_objscanner.m_blnScannerDiagnostic = True
   Else
      modMain.m_objscanner.m_blnScannerDiagnostic = False
   End If
End Sub

Private Sub chkViewBarCode_Click()
  If chkViewBarCode.Value = 1 Then
     modMain.m_objscanner.m_blnViewBarCode = True
  Else
     modMain.m_objscanner.m_blnViewBarCode = False
  End If
End Sub

Private Sub chkViewStatistics_Click()
  If chkViewStatistics.Value = 1 Then
     fraStatisTics.Enabled = True
     modMain.m_objscanner.m_blnViewStatistics = True
  Else
     fraStatisTics.Enabled = False
     modMain.m_objscanner.m_blnViewStatistics = False
  End If
     
  
End Sub

Private Sub cmdXmit_Click()
  
  modMain.m_objscanner.ScanBarCode
  
'  MSComm1.PortOpen = False

End Sub

Private Sub Command1_Click()
   Me.Hide
   
End Sub

Private Sub Command2_Click()
  modMain.m_objscanner.SelfTest
  Me.txbScannerOutput.Refresh
  Me.Refresh
  
End Sub

Private Sub Form_Load()
  fraStatisTics.Enabled = False
 
End Sub

Private Sub fraScannerOptions_DragDrop(Source As Control, x As Single, Y As Single)
   modMain.m_objscanner.m_blnViewForm = True

End Sub

Private Sub MSComm2_OnComm()

Dim instring As String
Dim strBuffer As String
Dim strTemp As String
Dim nOffset As Integer
    On Error GoTo Comm_Error:

    Select Case MSComm2.CommEvent
        ' Handle each event or error by placing
        ' code below each case statement
    
        ' Errors
            Case comEventBreak  ' A Break was received.
            Case comEventCDTO   ' CD (RLSD) Timeout.
            Case comEventCTSTO  ' CTS Timeout.
            Case comEventDSRTO  ' DSR Timeout.
            Case comEventFrame  ' Framing Error
            Case comEventOverrun    ' Data Lost.
            Case comEventRxOver ' Receive buffer overflow.
            Case comEventRxParity   ' Parity Error.
    
            Case comEventTxFull ' Transmit buffer full.
            Case comEventDCB    ' Unexpected error retrieving DCB]
    
        ' Events
            Case comEvCD    ' Change in the CD line.
            Case comEvCTS   ' Change in the CTS line.
            Case comEvDSR   ' Change in the DSR line.
            Case comEvRing  ' Change in the Ring Indicator.
            Case comEvReceive   ' Received RThreshold # of chars.
                 'purge input buffer
            Case comEvSend  ' There are SThreshold number of
                                ' characters in the transmit
                                ' buffer.
    
    Case comEvEOF   ' An EOF charater was found in                              ' the input stream
        End Select
    instring = ""
    If MSComm2.InBufferCount > 5 Then
        ' Read data.
        While MSComm2.InBufferCount > 0
           instring = instring + MSComm2.Input
           Sleep (5)
        Wend
        instring = Mid(instring, 1, 80)
        
        nOffset = 0
        Do While Asc(Mid(instring, nOffset + 1, 1)) > 20
            nOffset = nOffset + 1
        Loop
        strTemp = Mid(instring, nOffset + 1)
        nOffset = 0
        Do While Asc(Mid(strTemp, nOffset + 1, 1)) < 48
            nOffset = nOffset + 1
        Loop
        strTemp = Mid(strTemp, nOffset + 1)
        nOffset = 1
        strBuffer = ""
        Do While Asc(Mid(strTemp, nOffset, 1)) > 20
            If IsNumeric(Mid(strTemp, nOffset, 1)) Then
                strBuffer = strBuffer + Mid(strTemp, nOffset, 1)
            End If
            nOffset = nOffset + 1
        Loop
    
    End If
      
    If (Not g_blnIs2Sided) Then
       Exit Sub
    End If
     
      
    If strBuffer <> "" And _
     ((frmMain.m_objLabeler.m_staLabelerState <> "Idle") And _
      (frmMain.m_objLabeler.m_staLabelerState <> "NoJob") And _
      (frmMain.m_objLabeler.m_staLabelerState <> "Init")) Then
       If (Len(m_strScannedBottomLabel) > 10) Then
          m_strScannedBottomLabel = Mid(strBuffer, 1, 10)
       Else
          m_strScannedBottomLabel = Mid(strBuffer, 1, 10)
       End If
       
       If (Len(m_strScannedBottomLabel) <> 10) Then
          frmMisScanManualEntry.m_blnReturnState = False
          frmMisScanManualEntry.m_strNewScannedValue = m_strScannedBottomLabel
          frmMisScanManualEntry.Show vbModal
            
                           
          If (frmMisScanManualEntry.m_blnReturnState) Then
              m_strScannedBottomLabel = frmMisScanManualEntry.m_strNewScannedValue
              Unload frmMisScanManualEntry
          Else
              Unload frmMisScanManualEntry
              frmMain.JobEnd
              m_strScannedBottomLabel = ""
              Exit Sub
          End If
       End If
    Else
       m_strScannedBottomLabel = ""
    End If
    
    If g_blnDisplayScannerData Then
        MsgBox ("Scanned Data Direct From The Bottom Scanner = " + m_strScannedBottomLabel)
    End If
    
    Exit Sub
Comm_Error:
    'hopefully this will catch power spikes and emi noise.
    m_strScannedBottomLabel = ""
    'purge buffer
    While MSComm2.InBufferCount > 0
       instring = instring + MSComm2.Input
       Sleep (5)
    Wend
    

End Sub

Private Sub txbDisableScannerPW_KeyPress(KeyAscii As Integer)
'future work
   
   m_strScannerPassWord = m_strScannerPassWord + Chr(KeyAscii)
   txbDisableScannerPW.Text = txbDisableScannerPW.Text + "X"
   KeyAscii = 0
End Sub
