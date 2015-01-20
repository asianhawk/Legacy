VERSION 5.00
Begin VB.Form frmQueue 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "frmQueue"
   ClientHeight    =   2010
   ClientLeft      =   885
   ClientTop       =   8355
   ClientWidth     =   3045
   ControlBox      =   0   'False
   Icon            =   "Queue.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   2010
   ScaleWidth      =   3045
   ShowInTaskbar   =   0   'False
   Begin VB.ListBox lstQueue 
      Height          =   1620
      ItemData        =   "Queue.frx":0442
      Left            =   45
      List            =   "Queue.frx":0444
      TabIndex        =   0
      Top             =   225
      Width           =   2880
   End
   Begin VB.Label labQueue 
      AutoSize        =   -1  'True
      Caption         =   "Print Q:"
      Height          =   195
      Left            =   45
      TabIndex        =   1
      Top             =   0
      Width           =   525
   End
End
Attribute VB_Name = "frmQueue"
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
'*           Software Subsystem
'*
'*          Queue managment
'*
'*    Date of origin: <Date>
'*    Original author: Michael D. Reed
'*
'* Class purpose:
'*    Used by the Q class to display it contents.
'*
'************************************************************************
Option Explicit

Private Sub Form_Load()

   labQueue.Caption = ""
   
End Sub 'Form_Load


Private Sub Form_Unload(Cancel As Integer)

   lstQueue.Clear
   
End Sub 'Form_Unload



