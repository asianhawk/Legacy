VERSION 5.00
Begin VB.Form frmScannerOffsetTest 
   Caption         =   "Scanner Offset Test"
   ClientHeight    =   5940
   ClientLeft      =   1965
   ClientTop       =   1485
   ClientWidth     =   9630
   LinkTopic       =   "Form1"
   ScaleHeight     =   5940
   ScaleWidth      =   9630
   Begin VB.Timer tmrReadActuator 
      Left            =   4860
      Top             =   4950
   End
   Begin VB.Frame Frame10 
      Caption         =   "Actuator Position"
      Height          =   1125
      Left            =   150
      TabIndex        =   8
      Top             =   4650
      Width           =   5295
      Begin VB.Frame Frame12 
         Height          =   735
         Left            =   2760
         TabIndex        =   12
         Top             =   240
         Width           =   1785
         Begin VB.TextBox txbYPos 
            Height          =   405
            Left            =   630
            TabIndex        =   13
            Top             =   240
            Width           =   975
         End
         Begin VB.Label Label9 
            Alignment       =   1  'Right Justify
            Caption         =   "Y-Pos:"
            Height          =   255
            Left            =   90
            TabIndex        =   14
            Top             =   330
            Width           =   465
         End
      End
      Begin VB.Frame Frame11 
         Height          =   735
         Left            =   240
         TabIndex        =   9
         Top             =   240
         Width           =   2085
         Begin VB.TextBox txbXPos 
            Height          =   405
            Left            =   720
            TabIndex        =   10
            Top             =   240
            Width           =   945
         End
         Begin VB.Label Label8 
            Alignment       =   1  'Right Justify
            Caption         =   "X-Pos:"
            Height          =   255
            Left            =   120
            TabIndex        =   11
            Top             =   330
            Width           =   525
         End
      End
   End
   Begin VB.Frame Frame9 
      Height          =   1125
      Left            =   5490
      TabIndex        =   5
      Top             =   4650
      Width           =   4065
      Begin VB.CommandButton Command1 
         Caption         =   "TBA"
         Height          =   495
         Left            =   2190
         TabIndex        =   38
         Top             =   360
         Width           =   1155
      End
      Begin VB.CommandButton cmdOk 
         Caption         =   "OK"
         Height          =   465
         Left            =   540
         TabIndex        =   6
         Top             =   390
         Width           =   1455
      End
   End
   Begin VB.Frame framScanner 
      Height          =   4515
      Left            =   5460
      TabIndex        =   2
      Top             =   30
      Width           =   4095
      Begin VB.Frame Frame4 
         Caption         =   "Read Rate"
         Height          =   615
         Left            =   120
         TabIndex        =   25
         Top             =   1080
         Width           =   3735
         Begin VB.OptionButton optDecodeRate 
            Caption         =   "Decode Rate"
            Height          =   255
            Left            =   1980
            TabIndex        =   27
            Top             =   240
            Width           =   1575
         End
         Begin VB.OptionButton optScannerPercent 
            Caption         =   "Percent %"
            Height          =   255
            Left            =   120
            TabIndex        =   26
            Top             =   240
            Width           =   1575
         End
      End
      Begin VB.Frame Frame3 
         Height          =   2565
         Left            =   150
         TabIndex        =   24
         Top             =   1800
         Width           =   3855
         Begin VB.Line shpYAxis 
            X1              =   360
            X2              =   360
            Y1              =   2370
            Y2              =   300
         End
         Begin VB.Line shpXAxis 
            X1              =   360
            X2              =   3480
            Y1              =   2370
            Y2              =   2370
         End
         Begin VB.Shape shpCurrentDecodeRate 
            Height          =   1830
            Left            =   1530
            Top             =   540
            Width           =   435
         End
      End
      Begin VB.CommandButton cmdTriggerScanner 
         Caption         =   "Trigger Scanner"
         Height          =   405
         Left            =   120
         TabIndex        =   16
         Top             =   600
         Width           =   1905
      End
      Begin VB.CommandButton cmdDecode 
         Caption         =   "View Decode Rate On"
         Height          =   405
         Left            =   2130
         TabIndex        =   15
         Top             =   600
         Width           =   1905
      End
      Begin VB.TextBox txbScannerOutput 
         Height          =   375
         Left            =   1320
         TabIndex        =   4
         Top             =   180
         Width           =   2685
      End
      Begin VB.Label Label7 
         Alignment       =   2  'Center
         Caption         =   "Scanner Output"
         Height          =   255
         Left            =   90
         TabIndex        =   3
         Top             =   240
         Width           =   1215
      End
   End
   Begin VB.Frame Frame1 
      Height          =   4515
      Left            =   90
      TabIndex        =   0
      Top             =   30
      Width           =   5325
      Begin VB.Frame Frame5 
         Caption         =   "Label Position"
         Height          =   2925
         Left            =   150
         TabIndex        =   17
         Top             =   1470
         Width           =   5115
         Begin VB.Frame Frame14 
            Caption         =   "Y-Axis Scanner Offset"
            Height          =   765
            Left            =   450
            TabIndex        =   35
            Top             =   1920
            Width           =   4125
            Begin VB.CommandButton Command3 
               Caption         =   "Verify Y-Axis Scanner Offset"
               Height          =   405
               Left            =   150
               TabIndex        =   37
               Top             =   210
               Width           =   2625
            End
            Begin VB.CommandButton cmdSaveYAxisScannerOffset 
               Caption         =   "Save"
               Height          =   405
               Left            =   2880
               TabIndex        =   36
               Top             =   210
               Width           =   1125
            End
         End
         Begin VB.Frame Frame13 
            Caption         =   "X-Axis Scanner Offset"
            Height          =   765
            Left            =   450
            TabIndex        =   32
            Top             =   1110
            Width           =   4125
            Begin VB.CommandButton cmdSaveXAxisScannerOffset 
               Caption         =   "Save"
               Height          =   405
               Left            =   2880
               TabIndex        =   34
               Top             =   210
               Width           =   1125
            End
            Begin VB.CommandButton cmdXAxisScannerOffset 
               Caption         =   "Verify X-Axis Scanner Offset"
               Height          =   405
               Left            =   180
               TabIndex        =   33
               Top             =   210
               Width           =   2625
            End
         End
         Begin VB.Frame Frame8 
            Height          =   735
            Left            =   3480
            TabIndex        =   28
            Top             =   240
            Width           =   1515
            Begin VB.TextBox txbTPTheta 
               Height          =   405
               Left            =   600
               TabIndex        =   29
               Top             =   240
               Width           =   735
            End
            Begin VB.Label Label3 
               Alignment       =   1  'Right Justify
               Caption         =   "Theta:"
               Height          =   255
               Left            =   60
               TabIndex        =   30
               Top             =   330
               Width           =   465
            End
         End
         Begin VB.Frame Frame6 
            Height          =   735
            Left            =   1800
            TabIndex        =   21
            Top             =   240
            Width           =   1515
            Begin VB.TextBox txbMoveToYPos 
               Height          =   405
               Left            =   600
               TabIndex        =   22
               Top             =   240
               Width           =   735
            End
            Begin VB.Label Label1 
               Alignment       =   1  'Right Justify
               Caption         =   "Y-Pos:"
               Height          =   255
               Left            =   60
               TabIndex        =   23
               Top             =   330
               Width           =   525
            End
         End
         Begin VB.Frame Frame7 
            Height          =   735
            Left            =   120
            TabIndex        =   18
            Top             =   240
            Width           =   1575
            Begin VB.TextBox txbMoveToXPos 
               Height          =   405
               Left            =   630
               TabIndex        =   19
               Top             =   240
               Width           =   735
            End
            Begin VB.Label Label2 
               Alignment       =   1  'Right Justify
               Caption         =   "X-Pos:"
               Height          =   255
               Left            =   90
               TabIndex        =   20
               Top             =   360
               Width           =   525
            End
         End
      End
      Begin VB.Frame Frame2 
         Caption         =   "IAI Controller Options"
         Height          =   1155
         Left            =   150
         TabIndex        =   1
         Top             =   240
         Width           =   5085
         Begin VB.CommandButton cmdServoOff 
            Caption         =   "Servo Off"
            Height          =   495
            Left            =   1800
            TabIndex        =   39
            Top             =   360
            Width           =   1155
         End
         Begin VB.CommandButton cmdThetaRotate 
            Caption         =   "Theta Rotate"
            Height          =   495
            Left            =   3030
            TabIndex        =   31
            Top             =   360
            Width           =   1155
         End
         Begin VB.CommandButton cmdHome 
            Caption         =   "Home"
            Height          =   495
            Left            =   870
            TabIndex        =   7
            Top             =   360
            Width           =   855
         End
      End
   End
End
Attribute VB_Name = "frmScannerOffsetTest"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim m_objScanner As clsMicroscan
'  Test Scanner
Private Const m_chrDECODE_RATE_TEST_Cp = "Cp"
Private Const m_chrDECODE_RATE_TEST_C = "C"

Private Const m_chrDECODE_EXTENDED_RATE_TEST = "Ce"
Private Const m_chrSTOP_DECODE_RATE_TEST = "J"
Private m_blnScannerDecodeOn As Boolean
Private m_blnReadScanner As Boolean
' Read label
Private Const m_chrREAD_LABEL_TRIGER = "b"
Private m_nScanReadRate As Integer

Private Sub cmdDecode_Click()
Dim strBuffer As String
tmrReadActuator.Enabled = True
strBuffer = cmdDecode.Caption
If (strBuffer = "View Decode Rate Off") Then
  cmdDecode.Caption = "View Decode Rate On"
  If (Not g_blnSimulator) Then
      If optScannerPercent.Value = True Then
         m_objScanner.SendCommand (m_chrDECODE_RATE_TEST_Cp)
       Else
         m_objScanner.SendCommand (m_chrDECODE_RATE_TEST_C)
       
       End If
  End If
  
  m_blnScannerDecodeOn = True
  
Else
  cmdDecode.Caption = "View Decode Rate Off"
  If (Not g_blnSimulator) Then
     m_objScanner.SendCommand (m_chrSTOP_DECODE_RATE_TEST)
  End If
  m_blnScannerDecodeOn = False
End If


End Sub
Private Sub DecodeOff()
  
  cmdDecode.Caption = "View Decode Rate Off"
  If (Not g_blnSimulator) Then
     m_objScanner.SendCommand (m_chrSTOP_DECODE_RATE_TEST)
  End If
  m_blnScannerDecodeOn = False

End Sub

Private Sub cmdHome_Click()
tmrReadActuator.Enabled = False
If Not g_blnSimulator Then
   frmMain.m_objIAICtrl.HomeController
   
  Do
    
    GetActuatorPosition
  Loop Until ((Val(txbXPos) = 0) And (Val(txbYPos) = 0))
End If
cmdHome.Enabled = False
End Sub

Private Sub cmdMoveTo_Click()
 tmrReadActuator.Enabled = True
 
 If frmMain.m_objIAICtrl.MoveTo(txbMoveToXPos, txbMoveToYPos) Then
 
 End If
 
End Sub

Private Sub cmdOk_Click()
  Unload Me
End Sub

Private Sub cmdServoOff_Click()
  Do
  Loop While Not (frmMain.m_objIAICtrl.ServoOff)
End Sub

Private Sub cmdTriggerScanner_Click()

  DecodeOff

  If (Not g_blnSimulator) Then

     m_objScanner.SendCommand (m_chrREAD_LABEL_TRIGER)
     m_blnReadScanner = True
     
  End If
  
End Sub

Private Sub cmdXAxisScannerOffset_Click()
 tmrReadActuator.Enabled = True
 
 If frmMain.m_objIAICtrl.MoveTo(txbMoveToXPos, txbMoveToYPos) Then
 
 End If

End Sub

Private Sub Command1_Click()
   DecodeRateBarGraph
End Sub


Private Sub GetActuatorPosition()
  frmMain.m_objIAICtrl.ActuatorPosition
  txbXPos = frmMain.m_objIAICtrl.m_strXPos
  txbYPos = frmMain.m_objIAICtrl.m_strYPos
End Sub


Private Sub Command2_Click()

End Sub

Private Sub Form_Load()
  Set m_objScanner = New clsMicroscan
   m_blnReadScanner = False
  optScannerPercent.Value = True
   InitBarGraph
  CenterForm Me
  cmdDecode.Caption = "View Decode Rate Off"
  If (Not g_blnSimulator) Then
     frmMain.m_objIAICtrl.ResetController
     frmMain.m_objIAICtrl.HomeController
  End If
  tmrReadActuator.Enabled = False
  tmrReadActuator.Interval = 1000
End Sub

Private Sub tmrReadActuator_Timer()
Dim strBuffer As String
      
   If (Not g_blnSimulator) Then
    GetActuatorPosition
  
   
     If m_blnScannerDecodeOn Then
       Do
       Loop Until (m_objScanner.ReceiveResponse(strBuffer))
       m_nScanReadRate = Val(Mid(strBuffer, 83, 2))
       If optDecodeRate.Value = True Then
          txbScannerOutput = Mid(strBuffer, 82)
       Else
         txbScannerOutput = Mid(strBuffer, 83, 2)
       End If
       DecodeRateBarGraph
     
     ElseIf m_blnReadScanner Then
       
       strBuffer = m_objScanner.ReadlBarCode()
       
       m_blnReadScanner = False
     
     End If
     
   End If
   tmrReadActuator.Enabled = True
End Sub


Public Sub InitBarGraph()
  Dim nXOrgin As Integer
  Dim nYOrgin As Integer

 nXOrgin = shpXAxis.Y1
 shpCurrentDecodeRate.Top = nXOrgin
 shpCurrentDecodeRate.Height = 0
 shpCurrentDecodeRate.FillColor = QBColor(2)
 shpCurrentDecodeRate.FillStyle = vbFSSolid

End Sub

Public Sub DecodeRateBarGraph()

Dim nConvertScannerDecodeRate As Integer
 
 If m_nScanReadRate > 0 Then
    nConvertScannerDecodeRate = m_nScanReadRate / 100 * _
                            (shpYAxis.Y1 - shpYAxis.Y2)
 Else
    nConvertScannerDecodeRate = 0
 End If
 
 shpCurrentDecodeRate.Height = nConvertScannerDecodeRate '- nYAxisOffset
 shpCurrentDecodeRate.Top = shpXAxis.Y1 - nConvertScannerDecodeRate
 shpCurrentDecodeRate.FillColor = QBColor(2)
 shpCurrentDecodeRate.FillStyle = vbFSSolid

End Sub

