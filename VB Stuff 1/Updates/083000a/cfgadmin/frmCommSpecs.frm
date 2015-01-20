VERSION 5.00
Begin VB.Form frmCommSpecs 
   Caption         =   "Settings"
   ClientHeight    =   5355
   ClientLeft      =   2655
   ClientTop       =   1095
   ClientWidth     =   6585
   LinkTopic       =   "Form1"
   ScaleHeight     =   5355
   ScaleWidth      =   6585
   Begin VB.Frame Frame6 
      Height          =   525
      Left            =   240
      TabIndex        =   11
      Top             =   1140
      Width           =   2325
      Begin VB.TextBox txbScannerWordLength 
         Height          =   315
         Left            =   1170
         TabIndex        =   12
         Top             =   150
         Width           =   465
      End
      Begin VB.Label Label4 
         Caption         =   "Bits"
         Height          =   285
         Left            =   1710
         TabIndex        =   14
         Top             =   180
         Width           =   435
      End
      Begin VB.Label Label3 
         Alignment       =   1  'Right Justify
         Caption         =   "Word Length:"
         Height          =   255
         Left            =   90
         TabIndex        =   13
         Top             =   210
         Width           =   975
      End
   End
   Begin VB.Frame Frame3 
      Caption         =   "Frame3"
      Height          =   975
      Left            =   2970
      TabIndex        =   1
      Top             =   4350
      Width           =   3495
      Begin VB.CommandButton cmdExit 
         Caption         =   "Exit"
         Height          =   375
         Left            =   2280
         TabIndex        =   4
         Top             =   360
         Width           =   975
      End
      Begin VB.CommandButton cmdCancel 
         Caption         =   "Cancel"
         Height          =   375
         Left            =   1200
         TabIndex        =   3
         Top             =   360
         Width           =   975
      End
      Begin VB.CommandButton cmdSave 
         Caption         =   "Save"
         Height          =   375
         Left            =   120
         TabIndex        =   2
         Top             =   360
         Width           =   975
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Scanner Port Settings"
      Height          =   2085
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   5745
      Begin VB.Frame Frame8 
         Height          =   555
         Left            =   120
         TabIndex        =   18
         Top             =   1470
         Width           =   2685
         Begin VB.ComboBox cmbScannerParity 
            Height          =   315
            ItemData        =   "frmCommSpecs.frx":0000
            Left            =   1170
            List            =   "frmCommSpecs.frx":000A
            TabIndex        =   20
            Text            =   "Combo1"
            Top             =   180
            Width           =   1455
         End
         Begin VB.Label Label5 
            Alignment       =   1  'Right Justify
            Caption         =   "Parity:"
            Height          =   255
            Left            =   90
            TabIndex        =   19
            Top             =   210
            Width           =   975
         End
      End
      Begin VB.Frame Frame7 
         Height          =   525
         Left            =   2460
         TabIndex        =   15
         Top             =   900
         Width           =   1755
         Begin VB.TextBox txbScannerStopBits 
            Height          =   315
            Left            =   1170
            TabIndex        =   16
            Top             =   150
            Width           =   465
         End
         Begin VB.Label Label6 
            Alignment       =   1  'Right Justify
            Caption         =   "Stop Bits:"
            Height          =   255
            Left            =   90
            TabIndex        =   17
            Top             =   210
            Width           =   975
         End
      End
      Begin VB.Frame Frame5 
         Height          =   555
         Left            =   2850
         TabIndex        =   8
         Top             =   300
         Width           =   2685
         Begin VB.TextBox txbScannerBaudRate 
            Height          =   315
            Left            =   1170
            TabIndex        =   10
            Top             =   150
            Width           =   1425
         End
         Begin VB.Label Label2 
            Alignment       =   1  'Right Justify
            Caption         =   "Baud Rate:"
            Height          =   255
            Left            =   90
            TabIndex        =   9
            Top             =   210
            Width           =   975
         End
      End
      Begin VB.Frame Frame4 
         Height          =   555
         Left            =   120
         TabIndex        =   5
         Top             =   300
         Width           =   2685
         Begin VB.ComboBox cmbScannerPort 
            Height          =   315
            Left            =   1140
            TabIndex        =   7
            Text            =   "Combo1"
            Top             =   180
            Width           =   1455
         End
         Begin VB.Label Label1 
            Alignment       =   1  'Right Justify
            Caption         =   "Com Port #:"
            Height          =   255
            Left            =   90
            TabIndex        =   6
            Top             =   210
            Width           =   975
         End
      End
   End
End
Attribute VB_Name = "frmCommSpecs"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'  Communication port settings
Private Const m_intScannerPORT_ID = 6
Private Const m_strScannerBaudRate = "9600"
Private Const m_strScannerParity = "Even"
Private Const m_strScannerWordLength = "7"
Private Const m_strScannerStopBit = "1"

Private Sub cmdExit_Click()
  Unload Me
End Sub

Private Sub Form_Load()

Dim strINIPath As String



  strINIPath = App.Path + "\config.ini"
  
  If (Dir(strINIPath, vbNormal) = "") Then
    UseDefaultSettings True
  Else
    UseDefaultSettings False

  End If
  
  
  
  

End Sub

Public Sub UseDefaultSettings(blnInitDefault As Boolean)

  InitiateScannerInfo blnInitDefault

End Sub

Public Sub InitiateScannerInfo(blnInitType As Boolean)
Dim hFile As Long
Dim strINIPath As String
Dim strBuffer As String
Dim strParity As String
Dim strComport As String
Dim strBaudRate As String
Dim strWordLength As String
Dim strStopBits As String

  hFile = FreeFile(0)
  strINIPath = App.Path + "\config.ini"


  If (blnInitType) Then  ' noINI file found or
     
     cmbScannerPort.Text = m_intScannerPORT_ID
     txbScannerBaudRate = m_strScannerBaudRate
     txbScannerWordLength = m_strScannerWordLength
     txbScannerStopBits = m_strScannerStopBit
     cmbScannerParity.Text = m_strScannerParity
  Else
     Open strINIPath For Input As #hFile
     
     Do
     Line Input #hFile, strBuffer  'read header line
     Loop Until (UCase(Mid(strBuffer, 1, 7)) = "SCANNER")
     Input #hFile, strComport, _
                  strBaudRate, _
                  strWordLength, _
                  strParity, _
                  strStopBits

     
     cmbScannerPort.Text = strComport
     txbScannerBaudRate = strBaudRate
     txbScannerWordLength = strWordLength
     txbScannerStopBits = strStopBits
     cmbScannerParity.Text = strParity

  
  
  End If
  
  
  
  Close (hFile)
End Sub
