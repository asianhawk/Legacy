VERSION 5.00
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.1#0"; "richtx32.ocx"
Begin VB.Form frmInstructions 
   BorderStyle     =   3  'Fixed Dialog
   ClientHeight    =   5835
   ClientLeft      =   2955
   ClientTop       =   2250
   ClientWidth     =   6570
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   5835
   ScaleWidth      =   6570
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton cmdOption 
      Caption         =   "cmdOption"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1395
      Index           =   3
      Left            =   3360
      TabIndex        =   4
      Top             =   4380
      Width           =   3135
   End
   Begin VB.CommandButton cmdOption 
      Caption         =   "cmdOption"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1395
      Index           =   2
      Left            =   120
      TabIndex        =   3
      Top             =   4380
      Width           =   3135
   End
   Begin VB.CommandButton cmdOption 
      Caption         =   "cmdOption"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1395
      Index           =   1
      Left            =   3360
      TabIndex        =   2
      Top             =   2940
      Width           =   3135
   End
   Begin VB.CommandButton cmdOption 
      Caption         =   "cmdOption"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1395
      Index           =   0
      Left            =   120
      TabIndex        =   1
      Top             =   2940
      Width           =   3135
   End
   Begin RichTextLib.RichTextBox rtfInstructions 
      Height          =   2835
      Left            =   60
      TabIndex        =   0
      Top             =   0
      Width           =   6435
      _ExtentX        =   11351
      _ExtentY        =   5001
      _Version        =   327681
      TextRTF         =   $"Instructions.frx":0000
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
End
Attribute VB_Name = "frmInstructions"
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

'  Myname
Private m_strName As String

Private Const m_int2BUTTON_HIGHT = 4830
Private Const m_int4BUTTON_HIGHT = 6240

Private Const m_strOK_BUTTON = "OK"
Private Const m_strCANCEL_BUTTON = "Cancel"

Private m_intButtonClicked As Integer

Private m_blnDialog As Boolean

Private ma_strButtons(3) As String

Public Sub InstructionsDisplay(strFileName As String)

   #If ccShip_Ver Then
      On Error GoTo InstructionsDisplay_Error
   #Else
      On Error GoTo 0
   #End If
   
   m_blnDialog = False
   
   '  save off the buttons, name, and display them
   cmdOption(0).Caption = m_strOK_BUTTON
   cmdOption(0).Visible = True
   cmdOption(1).Caption = m_strCANCEL_BUTTON
   cmdOption(1).Visible = True
   
   With Me
      .Height = m_int2BUTTON_HIGHT
      rtfInstructions.LoadFile strFileName, rtfRTF
      rtfInstructions.Visible = True
      .Show IIf(g_blnTest, vbModeless, vbModal)
      .Refresh
   End With 'me
   
   DoEvents
   
   Exit Sub

InstructionsDisplay_Error:

   ProccessError "InstructionsDisplay", Name, Err.Number, Err.Description
   
End Sub 'InstructionsDisplay

Public Function InstructionsDialog(strFileName As String, a_strButtons() As String) As String

   Dim i As Integer
   
   #If ccShip_Ver Then
      On Error GoTo InstructionsDialog_Error
   #Else
      On Error GoTo 0
   #End If
   
   m_blnDialog = True
   
   '  save off the buttons, name, and display them
   For i = 0 To UBound(a_strButtons)
      cmdOption(i).Caption = a_strButtons(i)
      cmdOption(i).Visible = True
      ma_strButtons(i) = a_strButtons(i)
   Next i
   
   With Me
      If i <= 2 Then
         .Height = m_int2BUTTON_HIGHT
      Else
         .Height = m_int4BUTTON_HIGHT
      End If
      
      rtfInstructions.LoadFile strFileName, rtfRTF
   
      .Show IIf(g_blnTest, vbModeless, vbModal)
   
   End With 'Me
   
   '  return the button clicked
   InstructionsDialog = ma_strButtons(m_intButtonClicked)
   
   ' Hide the buttons
'   For i = 0 To 3
'      cmdOption(i).Visible = False
'   Next i
   
   Exit Function

InstructionsDialog_Error:

   ProccessError "InstructionsDialog", Name, Err.Number, Err.Description
   InstructionsDialog = ""
   
End Function 'InstructionsDialog


Public Sub InstructionsRemove()

   Dim i As Integer
   
   #If ccShip_Ver Then
      On Error GoTo cmdOption_Click_Error
   #Else
      On Error GoTo 0
   #End If
   
   
   ' Hide the buttons
   For i = 0 To 3
      cmdOption(i).Visible = False
   Next i
   
   With Me
      If .Visible Then
         rtfInstructions.Visible = False
         .Hide
         .Refresh
      End If
   End With 'Me
   DoEvents
   
   Exit Sub

cmdOption_Click_Error:

   ProccessError "InstructionsRemove", Name, Err.Number, Err.Description
   
End Sub 'InstructionsRemove





Private Sub cmdOption_Click(Index As Integer)

   #If ccShip_Ver Then
      On Error GoTo cmdOption_Click_Error
   #Else
      On Error GoTo 0
   #End If
   
   With Me
      If m_blnDialog Then
         m_intButtonClicked = Index
         .Hide
      Else
         If cmdOption(Index).Caption = m_strCANCEL_BUTTON Then
            .Hide
            modMain.ExitEnd
         Else
            .Hide
         End If
      End If
   End With 'Me
   
   Exit Sub

cmdOption_Click_Error:

   ProccessError "", m_strName, Err.Number, Err.Description
   
End Sub 'cmdOption_Click

Private Sub Form_Load()

   Dim i As Integer
   
   CenterForm Me
   
   rtfInstructions.Text = ""
   
   ' Hide the buttons
   For i = 0 To 3
      cmdOption(i).Visible = False
   Next i
   
End Sub 'Form_Load




