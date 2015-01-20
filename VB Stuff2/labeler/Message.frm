VERSION 5.00
Object = "{0BA686C6-F7D3-101A-993E-0000C0EF6F5E}#1.0#0"; "THREED32.OCX"
Begin VB.Form frmMessage 
   BorderStyle     =   3  'Fixed Dialog
   ClientHeight    =   915
   ClientLeft      =   1590
   ClientTop       =   3150
   ClientWidth     =   6825
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   915
   ScaleMode       =   0  'User
   ScaleWidth      =   6825
   ShowInTaskbar   =   0   'False
   Begin Threed.SSPanel sspMessage 
      Align           =   1  'Align Top
      Height          =   915
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   6825
      _Version        =   65536
      _ExtentX        =   12039
      _ExtentY        =   1614
      _StockProps     =   15
      Caption         =   "sspMessage"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   18
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Autosize        =   3
   End
End
Attribute VB_Name = "frmMessage"
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

Private m_intPanalMsgHight As Integer

Private m_intRtfMsgHight As Integer



Public Sub MessageDisplay(strMessage As String)

   sspMessage.Height = ScaleHeight
   sspMessage.Caption = strMessage
   sspMessage.Enabled = True
   Show
   Refresh
   DoEvents
   
End Sub 'MessageDisplay

Public Sub MessageRemove()

   If Visible Then
      Hide
      sspMessage.Enabled = True
      Refresh
      DoEvents
   End If
   
End Sub 'MessageRemove



Private Sub Form_Load()

   CenterForm Me
   sspMessage.Caption = ""
   m_intPanalMsgHight = 1380
   m_intRtfMsgHight = 3700
    
End Sub 'Form_Load


Private Sub Form_LostFocus()
   
   Me.ZOrder 0 'Keep on top
  
End Sub 'Form_LostFocus






