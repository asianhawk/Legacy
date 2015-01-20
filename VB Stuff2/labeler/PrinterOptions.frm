VERSION 5.00
Object = "{0BA686C6-F7D3-101A-993E-0000C0EF6F5E}#1.0#0"; "THREED32.OCX"
Object = "{B16553C3-06DB-101B-85B2-0000C009BE81}#1.0#0"; "SPIN32.OCX"
Begin VB.Form frmPrinterOptions 
   Caption         =   "frmPrinterOptions"
   ClientHeight    =   3285
   ClientLeft      =   2640
   ClientTop       =   3255
   ClientWidth     =   5115
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   3285
   ScaleWidth      =   5115
   Begin VB.CommandButton cmdOK 
      Caption         =   "cmdOK"
      Default         =   -1  'True
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   510
      Left            =   1035
      TabIndex        =   6
      Top             =   2550
      Width           =   1080
   End
   Begin VB.CommandButton cmdCancel 
      Caption         =   "cmdCancel"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   510
      Left            =   2400
      TabIndex        =   7
      Top             =   2565
      Width           =   1080
   End
   Begin VB.TextBox txbPrinterOption 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   420
      Index           =   2
      Left            =   2805
      TabIndex        =   4
      Text            =   "txbPrinterOption"
      Top             =   1980
      Width           =   1530
   End
   Begin Threed.SSFrame ssfImageOffset 
      Height          =   1755
      Left            =   360
      TabIndex        =   8
      Top             =   120
      Width           =   4305
      _Version        =   65536
      _ExtentX        =   7594
      _ExtentY        =   3096
      _StockProps     =   14
      Caption         =   "ssfImageOffset"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Begin VB.TextBox txbPrinterOption 
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   420
         Index           =   1
         Left            =   1920
         TabIndex        =   2
         Text            =   "txbPrinterOption"
         Top             =   1020
         Width           =   1515
      End
      Begin VB.TextBox txbPrinterOption 
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   420
         Index           =   0
         Left            =   1905
         TabIndex        =   0
         Text            =   "txbPrinterOption"
         Top             =   480
         Width           =   1515
      End
      Begin Spin.SpinButton spnPrinterOption 
         Height          =   480
         Index           =   1
         Left            =   3435
         TabIndex        =   3
         Top             =   1020
         Width           =   345
         _Version        =   65536
         _ExtentX        =   609
         _ExtentY        =   847
         _StockProps     =   73
         ShadowThickness =   1
         TdThickness     =   2
      End
      Begin Spin.SpinButton spnPrinterOption 
         Height          =   480
         Index           =   0
         Left            =   3435
         TabIndex        =   1
         Top             =   480
         Width           =   345
         _Version        =   65536
         _ExtentX        =   609
         _ExtentY        =   847
         _StockProps     =   73
         ShadowThickness =   1
         TdThickness     =   2
      End
      Begin VB.Image imgLabXY 
         Height          =   960
         Left            =   240
         Picture         =   "PrinterOptions.frx":0000
         Top             =   450
         Width           =   960
      End
      Begin VB.Label labY 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Y:"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   18
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   435
         Left            =   1455
         TabIndex        =   10
         Top             =   960
         Width           =   450
      End
      Begin VB.Label labX 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "X:"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   18
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   435
         Left            =   1365
         TabIndex        =   9
         Top             =   435
         Width           =   555
      End
   End
   Begin Spin.SpinButton spnPrinterOption 
      Height          =   480
      Index           =   2
      Left            =   4335
      TabIndex        =   5
      Top             =   1965
      Width           =   345
      _Version        =   65536
      _ExtentX        =   609
      _ExtentY        =   847
      _StockProps     =   73
      ShadowThickness =   1
      TdThickness     =   2
   End
   Begin VB.Label labDarkAdjust 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "labDarkAdjust"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   300
      Left            =   1050
      TabIndex        =   11
      Top             =   2055
      Width           =   1710
   End
End
Attribute VB_Name = "frmPrinterOptions"
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

'  indexes into the control array
Private Const m_idxX_OFFSET = 0
Private Const m_idxY_OFFSET = 1
Private Const m_idxDARL_ADJUST = 2

'  The form who called me
Private m_objPrinter As Object

'  Max and Min values for each control
Private ma_intMin(0 To 2) As Integer
Private ma_intMax(0 To 2) As Integer

Private Sub Increment(objControl As Object, intMax As Integer)

   Dim intQuantity As Long
   
   #If ccShip_Ver Then
      On Error GoTo Increment_Error
   #Else
      On Error GoTo 0
   #End If

   With objControl
      If Not IsNumeric(.Text) Then
         .Text = 0
      End If
      intQuantity = CInt(.Text)
      If intQuantity < intMax Then
         .Text = CStr(intQuantity + 1)
      End If
   End With 'objControl
   
   Exit Sub

Increment_Error:

   ProccessError "Increment", Name, Err.Number, Err.Description

End Sub 'Increment


Private Sub Decrement(objControl As Object, intMin As Integer)

   Dim intQuantity As Long
   
   #If ccShip_Ver Then
      On Error GoTo Decrement_Error
   #Else
      On Error GoTo 0
   #End If
   
   With objControl
      If Not IsNumeric(.Text) Then
         .Text = 0
      End If
      intQuantity = CInt(.Text)
      If intQuantity > intMin Then
         .Text = CStr(intQuantity - 1)
      End If
   End With 'objControl
   Exit Sub

Decrement_Error:

   ProccessError "Decrement", Name, Err.Number, Err.Description

End Sub 'Decrement


Private Sub cmdCancel_Click()

   Unload Me
   
End Sub 'cmdCancel_Click


Private Sub cmdOK_Click()

   m_objPrinter.DarkAdjust = txbPrinterOption(m_idxDARL_ADJUST).Text
   m_objPrinter.XHome = txbPrinterOption(m_idxX_OFFSET).Text
   m_objPrinter.YHome = txbPrinterOption(m_idxY_OFFSET).Text
   m_objPrinter.SaveOptions
   
   Unload Me
   
End Sub 'cmdOK_Click

Private Sub Form_Load()

   modUtilities.CenterForm Me
   Me.Caption = LoadResString(resFORM_PTRSETUP)
   ssfImageOffset.Caption = LoadResString(resFORM_PTRSETUP_IMAGE)
   labDarkAdjust.Caption = LoadResString(resFORM_PTRSETUP_DENSTY)

   SetupOkButton cmdOK
   SetupCancelButton cmdCancel
   
End Sub 'Form_Load

Public Sub Initialize(objPrinter As Object)

   '  Set the printer object
   Set m_objPrinter = objPrinter
   
   '  Now fill the text boxes
   With objPrinter
      If IsNumeric(.DarkAdjust) Then
         txbPrinterOption(m_idxDARL_ADJUST).Text = .DarkAdjust
      Else
         txbPrinterOption(m_idxDARL_ADJUST).Text = "0"
      End If
      If IsNumeric(.XHome) Then
         txbPrinterOption(m_idxX_OFFSET).Text = .XHome
      Else
         txbPrinterOption(m_idxDARL_ADJUST).Text = "0"
      End If
      If IsNumeric(.YHome) Then
         txbPrinterOption(m_idxY_OFFSET).Text = .YHome
      Else
         txbPrinterOption(m_idxDARL_ADJUST).Text = "0"
      End If
   
      '  Set the max and min's
      ma_intMax(m_idxDARL_ADJUST) = .MaxDarkAdjust()
      ma_intMin(m_idxDARL_ADJUST) = .MinDarkAdjust()
      ma_intMax(m_idxY_OFFSET) = .MaxHome()
      ma_intMin(m_idxY_OFFSET) = .MinHome()
      ma_intMax(m_idxX_OFFSET) = .MaxHome()
      ma_intMin(m_idxX_OFFSET) = .MinHome()
   End With 'objPrinter
   
End Sub 'Initialize

Private Sub spnPrinterOption_SpinDown(Index As Integer)

   txbPrinterOption(Index).SetFocus
   Decrement txbPrinterOption(Index), ma_intMin(Index)
   
End Sub 'spnPrinterOption_SpinDown

Private Sub spnPrinterOption_SpinUp(Index As Integer)

   txbPrinterOption(Index).SetFocus
   Increment txbPrinterOption(Index), ma_intMax(Index)
   
End Sub 'spnPrinterOption_SpinUp


Private Sub txbPrinterOption_KeyPress(Index As Integer, KeyAscii As Integer)

   #If ccShip_Ver Then
      On Error GoTo txbPrinterOption_KeyPress_Error
   #Else
      On Error GoTo 0
   #End If
      
   If KeyAscii = 43 Then ' chr - so decrement value
      Increment txbPrinterOption(Index), ma_intMax(Index)
   ElseIf KeyAscii = 45 Then ' chr + so increment value
      Decrement txbPrinterOption(Index), ma_intMin(Index)
   ElseIf (48 <= KeyAscii) And (KeyAscii <= 57) Then
      With txbPrinterOption(Index)
         If (.Text = "") Or (.Text = "-") Then
            Exit Sub
         ElseIf Not IsNumeric(.Text) Then
            .Text = 0
            Exit Sub
         ElseIf CInt(.Text) < ma_intMax(Index) Then
            '  number pressed and quantity is not to big so exit sub
            Exit Sub
         End If
      End With 'txbPrinterOption(Index)
   ElseIf KeyAscii = 8 Then
      '  backspace so exit sub
      Exit Sub
   End If
   
   '  Clear the key so it will not print
   KeyAscii = 0

   Exit Sub 'txbQuantity_KeyPress

txbPrinterOption_KeyPress_Error:

   ProccessError "txbPrinterOption_KeyPress", "frmOpenJob", Err.Number, Err.Description

End Sub 'txbPrinterOption_KeyPress

Private Sub txbPrinterOption_LostFocus(Index As Integer)

   Dim strErrMessage As String
     
     
   With txbPrinterOption(Index)
      If Not IsNumeric(.Text) Then
         .Text = 0
      End If
      If CInt(.Text) > ma_intMax(Index) _
         Or _
            CInt(txbPrinterOption(Index).Text) < ma_intMin(Index) _
      Then
         Select Case Index
            Case m_idxX_OFFSET
               strErrMessage = LoadResString(resMSG_X_HOME)
            Case m_idxY_OFFSET
               strErrMessage = LoadResString(resMSG_Y_HOME)
            Case m_idxDARL_ADJUST
               strErrMessage = LoadResString(resMSG_DARKNESS)
         End Select
         strErrMessage = strErrMessage & ma_intMax(Index) & " and " & ma_intMin(Index)
         MsgBox strErrMessage, vbExclamation + vbOKOnly, LoadResString(resTITLE_PTR_OPTIONS)
         txbPrinterOption(Index).SetFocus
      End If
   End With 'txbPrinterOption(Index)

   
End Sub 'txbPrinterOption_LostFocus


