VERSION 5.00
Object = "{0BA686C6-F7D3-101A-993E-0000C0EF6F5E}#1.0#0"; "THREED32.OCX"
Begin VB.Form frmSplash 
   BorderStyle     =   3  'Fixed Dialog
   ClientHeight    =   5010
   ClientLeft      =   1215
   ClientTop       =   1830
   ClientWidth     =   6660
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   5010
   ScaleWidth      =   6660
   ShowInTaskbar   =   0   'False
   Begin Threed.SSPanel sspLogo 
      Align           =   1  'Align Top
      Height          =   4575
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   6660
      _Version        =   65536
      _ExtentX        =   11748
      _ExtentY        =   8070
      _StockProps     =   15
      Caption         =   "sspLogo"
      ForeColor       =   0
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BevelWidth      =   2
      BorderWidth     =   2
      BevelInner      =   1
      FloodColor      =   16777215
      Alignment       =   2
      Begin VB.Image imgLogo 
         BorderStyle     =   1  'Fixed Single
         Height          =   3960
         Left            =   120
         Picture         =   "Splash.frx":0000
         Top             =   120
         Width           =   6405
      End
   End
   Begin VB.Label labCopywrite 
      AutoSize        =   -1  'True
      Caption         =   "labCopywrite"
      Height          =   195
      Left            =   45
      TabIndex        =   1
      Top             =   4680
      Width           =   900
   End
End
Attribute VB_Name = "frmSplash"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'************************************************************************
'*           Computype, Inc.
'*       NextStep Automation Group
'*
'*     © Copywrite 1997 Computype, Inc.
'*
'*        3-Axis Label Applicator
'*           Control software
'*             Splash form
'*
'*
'*
'*    Date of origin: 1/21/97
'*    Original author: Michael D. Reed
'*
'* Form purpose:
'*    This form gives the user somethingto look
'*    at and informed them of the initialization status.
'*
'************************************************************************
Option Explicit


Private Sub Form_Load()

   Me.MousePointer = vbHourglass
   CenterForm Me
   
   
   labCopywrite.Caption = App.LegalCopyright
   sspLogo.Caption = LoadResString(resLABEL_SPLASH_LOGO)
   
   Me.Refresh
   DoEvents

End Sub 'Form_Load







