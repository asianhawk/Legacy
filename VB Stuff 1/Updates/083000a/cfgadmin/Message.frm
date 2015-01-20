VERSION 5.00
Object = "{0BA686C6-F7D3-101A-993E-0000C0EF6F5E}#1.0#0"; "THREED32.OCX"
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.1#0"; "RICHTX32.OCX"
Begin VB.Form frmMessage 
   BorderStyle     =   3  'Fixed Dialog
   ClientHeight    =   3240
   ClientLeft      =   300
   ClientTop       =   1770
   ClientWidth     =   6825
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   3240
   ScaleMode       =   0  'User
   ScaleWidth      =   6825
   ShowInTaskbar   =   0   'False
   Begin Threed.SSPanel sspMessage 
      Align           =   1  'Align Top
      Height          =   3240
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   6825
      _Version        =   65536
      _ExtentX        =   12039
      _ExtentY        =   5715
      _StockProps     =   15
      Caption         =   "sspMessage"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Begin RichTextLib.RichTextBox rtfInstructions 
         Height          =   3105
         Left            =   60
         TabIndex        =   1
         Top             =   60
         Visible         =   0   'False
         Width           =   6720
         _ExtentX        =   11853
         _ExtentY        =   5477
         _Version        =   327681
         Enabled         =   -1  'True
         HideSelection   =   0   'False
         ScrollBars      =   2
         Appearance      =   0
         RightMargin     =   10000
         TextRTF         =   $"Message.frx":0000
      End
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
'*     © Copywrite 1996 Computype, Inc.
'*
'*        3-Axis Label Applicator
'*           Control Subsystem
'*
'*              Messaging
'*
'*    Date of origin: 1/30/96
'*    Original author: Michael D. Reed
'*
'* Form purpose:
'*    This form provides a modle form to pervent
'*    action to be taken by the operator on the
'*    form until it is ready.
'*
'************************************************************************
Option Explicit

Private m_intPanalMsgHight As Integer

Private m_intRtfMsgHight As Integer

Private Sub Form_Click()
   Unload Me
End Sub

Private Sub Form_Load()

   CenterForm Me
   sspMessage.Caption = ""
   rtfInstructions.Visible = False
'   rtfInstructions.Text = ""
   m_intPanalMsgHight = 1380
   m_intRtfMsgHight = 3700
    
End Sub 'Form_Load


Private Sub Form_LostFocus()
   
   Me.ZOrder 0 'Keep on top
  
End Sub 'Form_LostFocus



Public Property Get PanalMsgHight() As Integer

   PanalMsgHight = m_intPanalMsgHight

End Property 'PanalMsgHight

Public Property Let PanalMsgHight(vNewValue As Integer)

   m_intPanalMsgHight = vNewValue
   
End Property 'PanalMsgHight

Public Property Get RtfMsgHight() As Integer

   RtfMsgHight = m_intRtfMsgHight
   
End Property 'RtfMsgHight

Public Property Let RtfMsgHight(vNewValue As Integer)

   m_intRtfMsgHight = vNewValue
   
End Property 'RtfMsgHight

