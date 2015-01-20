VERSION 5.00
Object = "{0BA686C6-F7D3-101A-993E-0000C0EF6F5E}#1.0#0"; "THREED32.OCX"
Begin VB.Form frmAbout 
   Caption         =   "frmAbout"
   ClientHeight    =   3930
   ClientLeft      =   3180
   ClientTop       =   2370
   ClientWidth     =   4140
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   3930
   ScaleWidth      =   4140
   Begin Threed.SSPanel sspLogo 
      Align           =   1  'Align Top
      Height          =   2655
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   4140
      _Version        =   65536
      _ExtentX        =   7302
      _ExtentY        =   4683
      _StockProps     =   15
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BevelWidth      =   2
      BorderWidth     =   2
      BevelInner      =   1
      Alignment       =   8
      Autosize        =   3
      Begin VB.PictureBox picLogo 
         AutoSize        =   -1  'True
         Height          =   2430
         Left            =   120
         Picture         =   "About.frx":0000
         ScaleHeight     =   2370
         ScaleWidth      =   3810
         TabIndex        =   1
         Top             =   120
         Width           =   3870
      End
   End
   Begin Threed.SSPanel SSPanel2 
      Align           =   2  'Align Bottom
      Height          =   1290
      Left            =   0
      TabIndex        =   2
      Top             =   2640
      Width           =   4140
      _Version        =   65536
      _ExtentX        =   7303
      _ExtentY        =   2275
      _StockProps     =   15
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BevelWidth      =   2
      BorderWidth     =   2
      BevelInner      =   1
      Autosize        =   3
      Begin VB.CommandButton cmdOK 
         Caption         =   "cmdOK"
         Height          =   375
         Left            =   1320
         TabIndex        =   4
         Top             =   720
         Width           =   1095
      End
      Begin VB.Label labAbout 
         Alignment       =   2  'Center
         BackStyle       =   0  'Transparent
         Caption         =   "labAbout"
         Height          =   495
         Left            =   120
         TabIndex        =   3
         Top             =   120
         Width           =   3855
         WordWrap        =   -1  'True
      End
   End
End
Attribute VB_Name = "frmAbout"
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
'*             About form
'*
'*
'*    Date of origin: 1/21/97
'*    Original author: Michael D. Reed
'*
'* Form purpose:
'*    This is the about form.
'*
'************************************************************************
Option Explicit




Private Sub cmdOK_Click()

   Unload Me
   
End Sub 'cmdOK_Click



Private Sub Form_Load()

   Caption = "3-Axis Label Applactor"
   labAbout.Caption = App.LegalCopyright & vbCrLf
   labAbout.Caption = labAbout.Caption & App.CompanyName & vbCrLf
   
   '  Setup the  ok buttons
   modUtilities.SetupOkButton cmdOK
   
   '  setup form
   modUtilities.CenterForm Me
   
End Sub 'Form_Load

