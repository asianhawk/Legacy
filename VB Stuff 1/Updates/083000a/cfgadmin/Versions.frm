VERSION 4.00
Begin VB.Form frmVersions 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "frmVersions"
   ClientHeight    =   2985
   ClientLeft      =   6720
   ClientTop       =   3750
   ClientWidth     =   4110
   Height          =   3390
   Left            =   6660
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2985
   ScaleWidth      =   4110
   ShowInTaskbar   =   0   'False
   Top             =   3405
   Width           =   4230
   Begin VB.CommandButton cmdOK 
      Caption         =   "cmdOK"
      Default         =   -1  'True
      Height          =   435
      Left            =   1440
      TabIndex        =   1
      Top             =   2520
      Width           =   1095
   End
   Begin VB.PictureBox picVersions 
      Align           =   1  'Align Top
      Height          =   2415
      Left            =   0
      ScaleHeight     =   2355
      ScaleWidth      =   4050
      TabIndex        =   0
      Top             =   0
      Width           =   4110
   End
End
Attribute VB_Name = "frmVersions"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdOK_Click()

   Unload Me
   
End Sub 'cmdOK_Click

Private Sub Form_Activate()


End Sub 'Form_Activate

Private Sub Form_Load()

   Dim strAppVersion As String
   
   frmVersions.Caption = "Versions"
   
   
End Sub 'Form_Load


