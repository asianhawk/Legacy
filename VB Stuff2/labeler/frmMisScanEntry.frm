VERSION 5.00
Begin VB.Form frmMisScanManualEntry 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Bottom Scanner Miss Scan: Manual Data Entry"
   ClientHeight    =   2790
   ClientLeft      =   2400
   ClientTop       =   2130
   ClientWidth     =   6585
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2790
   ScaleWidth      =   6585
   ShowInTaskbar   =   0   'False
   Begin VB.TextBox txbNumber 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   3000
      TabIndex        =   0
      Text            =   "01230456789"
      Top             =   1320
      Width           =   1815
   End
   Begin VB.CommandButton cmdCancel 
      Caption         =   "Cancel"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   3480
      TabIndex        =   2
      Top             =   2160
      Width           =   1815
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   1320
      TabIndex        =   1
      Top             =   2160
      Width           =   1815
   End
   Begin VB.Label Label2 
      Alignment       =   1  'Right Justify
      Caption         =   "Enter Serial Number:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   0
      TabIndex        =   3
      Top             =   1440
      Width           =   2775
   End
   Begin VB.Label Label1 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "The  Bar Code was MisScanned From The Bottom Label. Correct Value Manually and Press OK, or Press Cancel to Pause the Job."
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1095
      Left            =   360
      TabIndex        =   4
      Top             =   120
      Width           =   5895
   End
End
Attribute VB_Name = "frmMisScanManualEntry"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public m_blnReturnState As Boolean
Public m_strNewScannedValue As String


Private Sub cmdCancel_Click()
   m_strNewScannedValue = ""
   m_blnReturnState = False
   Hide
End Sub

Private Sub cmdOK_Click()
   If (Len(txbNumber) <> 10) Then
      MsgBox ("Must Be 10 Digits Long")
      txbNumber.Text = ""
      txbNumber.SetFocus
      Exit Sub
   End If
   
   m_strNewScannedValue = txbNumber.Text
   m_blnReturnState = True
   Hide
End Sub

Private Sub Form_Load()
   txbNumber.Text = m_strNewScannedValue
   modUtilities.CenterForm Me
End Sub

