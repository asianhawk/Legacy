VERSION 5.00
Begin VB.Form frmHistory 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "frmHistory"
   ClientHeight    =   5880
   ClientLeft      =   900
   ClientTop       =   1950
   ClientWidth     =   3165
   ControlBox      =   0   'False
   Icon            =   "History.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   0
   ScaleWidth      =   0
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton cmdClear 
      Caption         =   "Clear"
      Height          =   255
      Left            =   2235
      TabIndex        =   1
      Top             =   5625
      Width           =   735
   End
   Begin VB.TextBox txbHistroy 
      Height          =   5505
      Left            =   75
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   0
      Text            =   "History.frx":0442
      Top             =   60
      Width           =   2970
   End
End
Attribute VB_Name = "frmHistory"
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
'*              Histroy
'*
'*    Date of origin: 1/30/96
'*    Original author: Michael D. Reed
'*
'* Form purpose:
'*    This list a history of actions.
'*
'************************************************************************
Option Explicit


Private Sub cmdClear_Click()

   txbHistroy.Text = ""
   
End Sub 'cmdClear_Click


Private Sub Form_Load()

   txbHistroy.Text = LoadResString(resSTARTED_HISTORY) & Format(Now, "Short Date") & vbCrLf
   Caption = LoadResString(resFORM_HISTORY)
   
End Sub 'Form_Load


Public Sub Message(strMsg As String)

   
   If Len(txbHistroy.Text) > 1000 Then
      txbHistroy.Text = ""
   End If
   
  txbHistroy.Text = txbHistroy.Text & strMsg & vbCrLf
 '  txbHistroy.SelStart = Len(txbHistroy.Text)
   
   modUtilities.Log "History", strMsg
   
End Sub 'Message


