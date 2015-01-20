VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "COMCTL32.OCX"
Object = "{0BA686C6-F7D3-101A-993E-0000C0EF6F5E}#1.0#0"; "THREED32.OCX"
Begin VB.Form frmSplash 
   BorderStyle     =   3  'Fixed Dialog
   ClientHeight    =   5955
   ClientLeft      =   2310
   ClientTop       =   1965
   ClientWidth     =   8775
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   5955
   ScaleWidth      =   8775
   ShowInTaskbar   =   0   'False
   Begin Threed.SSPanel sspLogo 
      Align           =   1  'Align Top
      Height          =   5370
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   8775
      _Version        =   65536
      _ExtentX        =   15478
      _ExtentY        =   9472
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
         Left            =   1110
         Picture         =   "Splash.frx":0000
         Top             =   510
         Width           =   6405
      End
   End
   Begin ComctlLib.StatusBar stbStatus 
      Align           =   2  'Align Bottom
      Height          =   300
      Left            =   0
      TabIndex        =   1
      Top             =   5655
      Width           =   8775
      _ExtentX        =   15478
      _ExtentY        =   529
      SimpleText      =   ""
      _Version        =   327682
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   5
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            AutoSize        =   1
            Bevel           =   0
            Object.Width           =   3059
            MinWidth        =   254
            Text            =   "Digital"
            TextSave        =   "Digital"
            Key             =   "Digital"
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel2 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Bevel           =   0
            Text            =   "Motion"
            TextSave        =   "Motion"
            Key             =   "Motion"
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel3 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            AutoSize        =   1
            Bevel           =   0
            Object.Width           =   3059
            MinWidth        =   254
            Text            =   "Scanner"
            TextSave        =   "Scanner"
            Key             =   "Scanner"
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel4 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            AutoSize        =   1
            Bevel           =   0
            Object.Width           =   3059
            MinWidth        =   254
            Text            =   "Printer"
            TextSave        =   "Printer"
            Key             =   "Printer"
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel5 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            AutoSize        =   1
            Bevel           =   0
            Object.Width           =   3059
            MinWidth        =   254
            Text            =   "Labeler"
            TextSave        =   "Labeler"
            Key             =   "Labeler"
            Object.Tag             =   ""
         EndProperty
      EndProperty
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
   Begin VB.Label labCopywrite 
      AutoSize        =   -1  'True
      Caption         =   "labCopywrite"
      Height          =   195
      Left            =   45
      TabIndex        =   2
      Top             =   5370
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


Private Sub Form_Load()

   CenterForm Me
   
   stbStatus.Panels("Scanner").Text = ""
   stbStatus.Panels("Printer").Text = ""
   stbStatus.Panels("Digital").Text = ""
   stbStatus.Panels("Labeler").Text = ""
   stbStatus.Panels("Motion").Text = ""
   
   labCopywrite.Caption = App.LegalCopyright
   sspLogo.Caption = LoadResString(resLABEL_SPLASH_LOGO)
   
   Me.Refresh
   frmSplash.stbStatus.Refresh
   DoEvents

End Sub 'Form_Load



Public Sub PanelMotion(strShow As String)

   With stbStatus
      .Panels("Motion").Text = strShow
      .Panels("Motion").Bevel = .Panels("Motion").Bevel + 1
      .Refresh
   End With 'stbStatus
   
   modUtilities.Log "Splash", strShow
   
   DoEvents

End Sub 'PanelMotion

Public Sub PanelScanner(strShow As String, strPosition As String)

   With stbStatus
      .Panels("Scanner").Text = strPosition + " " + strShow
      .Panels("Scanner").Bevel = .Panels("Scanner").Bevel + 1
      .Refresh
   End With 'stbStatus
   
   modUtilities.Log "Splash", strShow
   
   DoEvents

End Sub 'PanelScanner


Public Sub InitError(strErrMsg As String)

   Dim strTital As String
   Dim strMsg As String
   
   strTital = "Initialization Error"
   
   strMsg = "3-Axis Laber failed to initializ because"
   strMsg = strMsg & vbCrLf & vbCrLf
   strMsg = strMsg & strErrMsg
   
   MsgBox strMsg, vbOKOnly + vbCritical, strTital
  
End Sub 'InitError


Public Sub PanelDigital(strShow As String)

   With stbStatus
      .Panels("Digital").Text = strShow
      .Panels("Digital").Bevel = .Panels("Digital").Bevel + 1
      .Refresh
   End With 'stbStatus
   
   modUtilities.Log "Splash", strShow
   
   DoEvents

End Sub 'PanelDigital

Public Sub PanelLabeler(strShow As String)

   With stbStatus
      .Panels("Labeler").Text = strShow
      .Panels("Labeler").Bevel = .Panels("Labeler").Bevel + 1
      .Refresh
   End With 'stbStatus
   
   modUtilities.Log "Splash", strShow
   
   DoEvents

End Sub 'PanelLabeler

Public Sub PanelPrint(strShow As String)

   With stbStatus
      .Panels("Printer").Text = strShow
      .Panels("Printer").Bevel = .Panels("Printer").Bevel + 1
      .Refresh
   End With 'stbStatus
   
   modUtilities.Log "Splash", strShow
   
   DoEvents

End Sub 'PanelPrint

