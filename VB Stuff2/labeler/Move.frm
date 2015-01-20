VERSION 5.00
Begin VB.Form frmMove 
   Caption         =   "SA Motion Control"
   ClientHeight    =   1440
   ClientLeft      =   14850
   ClientTop       =   12870
   ClientWidth     =   3075
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   1440
   ScaleWidth      =   3075
   Begin VB.Timer tmrMoveTimeOut 
      Left            =   0
      Top             =   0
   End
   Begin VB.CommandButton cmdMove 
      Caption         =   "Move"
      Height          =   435
      Left            =   1680
      TabIndex        =   3
      Top             =   840
      Width           =   975
   End
   Begin VB.TextBox txbMoveTo 
      Height          =   375
      Left            =   2040
      MaxLength       =   2
      TabIndex        =   2
      Text            =   "txbMoveTo"
      Top             =   360
      Width           =   555
   End
   Begin VB.CommandButton cmdHome 
      Caption         =   "Home"
      Height          =   435
      Left            =   660
      TabIndex        =   0
      Top             =   840
      Width           =   975
   End
   Begin VB.Label labMove 
      Caption         =   "Current Position"
      Height          =   255
      Left            =   180
      TabIndex        =   1
      Top             =   420
      Width           =   1695
   End
End
Attribute VB_Name = "frmMove"
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

Private m_objMove As Object
Private Sub cmdHome_Click()

   m_objMove.Home blnWait:=False
   
End Sub 'cmdHome_Click



Private Sub cmdMove_Click()

   With m_objMove
      .Postion = txbMoveTo.Text
      .Move blnWait:=False
   End With 'm_objMove
   
End Sub 'cmdMiove_Click


Private Sub Form_Load()

   txbMoveTo.Text = ""
   
   tmrMoveTimeOut.Enabled = False
   
End Sub 'Form_Load

Private Sub tmrMoveTimeOut_Timer()

   m_objMove.MoveTimeOut
   
End Sub 'tmrMoveTimeOut_Timer

Private Sub txbMoveTo_GotFocus()

   txbMoveTo.Text = m_objMove.Postion
   
End Sub 'txbMoveTo_GotFocus

Private Sub txbMoveTo_LostFocus()

   With txbMoveTo
      If (Len(.Text) <> 2) And _
         (Int(.Text) < 1) And _
         (Int(.Text) > 99) _
      Then
         MsgBox "The positional value must two digits between 01 and 99.", , "SA Motion Control"
         .SetFocus
      End If
   End With 'txbMoveTo
   
End Sub 'txbMoveTo_LostFocus



Public Sub Initialize(objMove As Object)

   Set m_objMove = objMove
   
   m_objMove.SetMyForm Me
   
End Sub 'Initialize
