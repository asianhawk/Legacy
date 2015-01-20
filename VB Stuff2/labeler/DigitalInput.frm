VERSION 5.00
Object = "{0BA686C6-F7D3-101A-993E-0000C0EF6F5E}#1.0#0"; "threed32.ocx"
Begin VB.Form frmDigitalInput 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Digital Inputs"
   ClientHeight    =   6465
   ClientLeft      =   1725
   ClientTop       =   3180
   ClientWidth     =   2970
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   6465
   ScaleWidth      =   2970
   Begin Threed.SSPanel sspInputs 
      Height          =   5775
      Left            =   60
      TabIndex        =   0
      Top             =   600
      Width           =   2835
      _Version        =   65536
      _ExtentX        =   5001
      _ExtentY        =   10186
      _StockProps     =   15
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   6
      Begin Threed.SSPanel sspInputControl 
         Height          =   345
         Index           =   0
         Left            =   120
         TabIndex        =   1
         Top             =   120
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "0"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin VB.Image imgOFFIOIndicator 
            Height          =   240
            Index           =   0
            Left            =   45
            Picture         =   "DigitalInput.frx":0000
            Top             =   45
            Width           =   240
         End
         Begin VB.Image imgONIOIndicator 
            Height          =   240
            Index           =   0
            Left            =   255
            Picture         =   "DigitalInput.frx":0102
            Top             =   45
            Width           =   240
         End
      End
      Begin Threed.SSPanel sspInputControl 
         Height          =   345
         Index           =   1
         Left            =   120
         TabIndex        =   2
         Top             =   480
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "1"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin VB.Image imgONIOIndicator 
            Height          =   240
            Index           =   1
            Left            =   270
            Picture         =   "DigitalInput.frx":0204
            Top             =   45
            Width           =   240
         End
         Begin VB.Image imgOFFIOIndicator 
            Height          =   240
            Index           =   1
            Left            =   45
            Picture         =   "DigitalInput.frx":0306
            Top             =   45
            Width           =   240
         End
      End
      Begin Threed.SSPanel sspInputControl 
         Height          =   345
         Index           =   2
         Left            =   120
         TabIndex        =   3
         Top             =   825
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "2"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin VB.Image imgONIOIndicator 
            Height          =   240
            Index           =   2
            Left            =   285
            Picture         =   "DigitalInput.frx":0408
            Top             =   45
            Width           =   240
         End
         Begin VB.Image imgOFFIOIndicator 
            Height          =   240
            Index           =   2
            Left            =   45
            Picture         =   "DigitalInput.frx":050A
            Top             =   45
            Width           =   240
         End
      End
      Begin Threed.SSPanel sspInputControl 
         Height          =   345
         Index           =   3
         Left            =   120
         TabIndex        =   4
         Top             =   1170
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "3"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin VB.Image imgONIOIndicator 
            Height          =   240
            Index           =   3
            Left            =   285
            Picture         =   "DigitalInput.frx":060C
            Top             =   45
            Width           =   240
         End
         Begin VB.Image imgOFFIOIndicator 
            Height          =   240
            Index           =   3
            Left            =   45
            Picture         =   "DigitalInput.frx":070E
            Top             =   45
            Width           =   240
         End
      End
      Begin Threed.SSPanel sspInputControl 
         Height          =   345
         Index           =   4
         Left            =   120
         TabIndex        =   5
         Top             =   1515
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "4"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin VB.Image imgONIOIndicator 
            Height          =   240
            Index           =   4
            Left            =   270
            Picture         =   "DigitalInput.frx":0810
            Top             =   45
            Width           =   240
         End
         Begin VB.Image imgOFFIOIndicator 
            Height          =   240
            Index           =   4
            Left            =   30
            Picture         =   "DigitalInput.frx":0912
            Top             =   45
            Width           =   240
         End
      End
      Begin Threed.SSPanel sspInputControl 
         Height          =   345
         Index           =   5
         Left            =   120
         TabIndex        =   6
         Top             =   1860
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "5"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin VB.Image imgONIOIndicator 
            Height          =   240
            Index           =   5
            Left            =   270
            Picture         =   "DigitalInput.frx":0A14
            Top             =   45
            Width           =   240
         End
         Begin VB.Image imgOFFIOIndicator 
            Height          =   240
            Index           =   5
            Left            =   45
            Picture         =   "DigitalInput.frx":0B16
            Top             =   45
            Width           =   240
         End
      End
      Begin Threed.SSPanel sspInputControl 
         Height          =   345
         Index           =   6
         Left            =   120
         TabIndex        =   7
         Top             =   2205
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "6"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin VB.Image imgONIOIndicator 
            Height          =   240
            Index           =   6
            Left            =   270
            Picture         =   "DigitalInput.frx":0C18
            Top             =   45
            Width           =   240
         End
         Begin VB.Image imgOFFIOIndicator 
            Height          =   240
            Index           =   6
            Left            =   30
            Picture         =   "DigitalInput.frx":0D1A
            Top             =   45
            Width           =   240
         End
      End
      Begin Threed.SSPanel sspInputControl 
         Height          =   345
         Index           =   7
         Left            =   120
         TabIndex        =   8
         Top             =   2550
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "7"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin VB.Image imgONIOIndicator 
            Height          =   240
            Index           =   7
            Left            =   270
            Picture         =   "DigitalInput.frx":0E1C
            Top             =   45
            Width           =   240
         End
         Begin VB.Image imgOFFIOIndicator 
            Height          =   240
            Index           =   7
            Left            =   45
            Picture         =   "DigitalInput.frx":0F1E
            Top             =   45
            Width           =   240
         End
      End
      Begin Threed.SSPanel sspInputControl 
         Height          =   345
         Index           =   8
         Left            =   120
         TabIndex        =   9
         Top             =   2895
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "8"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin VB.Image imgONIOIndicator 
            Height          =   240
            Index           =   8
            Left            =   270
            Picture         =   "DigitalInput.frx":1020
            Top             =   45
            Width           =   240
         End
         Begin VB.Image imgOFFIOIndicator 
            Height          =   240
            Index           =   8
            Left            =   45
            Picture         =   "DigitalInput.frx":1122
            Top             =   45
            Width           =   240
         End
      End
      Begin Threed.SSPanel sspInputControl 
         Height          =   345
         Index           =   9
         Left            =   120
         TabIndex        =   10
         Top             =   3240
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "9"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin VB.Image imgOFFIOIndicator 
            Height          =   240
            Index           =   9
            Left            =   45
            Picture         =   "DigitalInput.frx":1224
            Top             =   45
            Width           =   240
         End
         Begin VB.Image imgONIOIndicator 
            Height          =   240
            Index           =   9
            Left            =   270
            Picture         =   "DigitalInput.frx":1326
            Top             =   45
            Width           =   240
         End
      End
      Begin Threed.SSPanel sspInputControl 
         Height          =   345
         Index           =   10
         Left            =   120
         TabIndex        =   11
         Top             =   3585
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "10"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin VB.Image imgOFFIOIndicator 
            Height          =   240
            Index           =   10
            Left            =   60
            Picture         =   "DigitalInput.frx":1428
            Top             =   60
            Width           =   240
         End
         Begin VB.Image imgONIOIndicator 
            Height          =   240
            Index           =   10
            Left            =   270
            Picture         =   "DigitalInput.frx":152A
            Top             =   60
            Width           =   240
         End
      End
      Begin Threed.SSPanel sspInputControl 
         Height          =   345
         Index           =   11
         Left            =   120
         TabIndex        =   12
         Top             =   3930
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "11"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin VB.Image imgOFFIOIndicator 
            Height          =   240
            Index           =   11
            Left            =   45
            Picture         =   "DigitalInput.frx":162C
            Top             =   45
            Width           =   240
         End
         Begin VB.Image imgONIOIndicator 
            Height          =   240
            Index           =   11
            Left            =   270
            Picture         =   "DigitalInput.frx":172E
            Top             =   45
            Width           =   240
         End
      End
      Begin Threed.SSPanel sspInputControl 
         Height          =   345
         Index           =   12
         Left            =   120
         TabIndex        =   13
         Top             =   4275
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "12"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin VB.Image imgOFFIOIndicator 
            Height          =   240
            Index           =   12
            Left            =   45
            Picture         =   "DigitalInput.frx":1830
            Top             =   45
            Width           =   240
         End
         Begin VB.Image imgONIOIndicator 
            Height          =   240
            Index           =   12
            Left            =   270
            Picture         =   "DigitalInput.frx":1932
            Top             =   45
            Width           =   240
         End
      End
      Begin Threed.SSPanel sspInputControl 
         Height          =   345
         Index           =   13
         Left            =   120
         TabIndex        =   14
         Top             =   4620
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "13"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin VB.Image imgOFFIOIndicator 
            Height          =   240
            Index           =   13
            Left            =   45
            Picture         =   "DigitalInput.frx":1A34
            Top             =   45
            Width           =   240
         End
         Begin VB.Image imgONIOIndicator 
            Height          =   240
            Index           =   13
            Left            =   270
            Picture         =   "DigitalInput.frx":1B36
            Top             =   45
            Width           =   240
         End
      End
      Begin Threed.SSPanel sspInputControl 
         Height          =   345
         Index           =   14
         Left            =   120
         TabIndex        =   15
         Top             =   4965
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "14"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin VB.Image imgOFFIOIndicator 
            Height          =   240
            Index           =   14
            Left            =   45
            Picture         =   "DigitalInput.frx":1C38
            Top             =   45
            Width           =   240
         End
         Begin VB.Image imgONIOIndicator 
            Height          =   240
            Index           =   14
            Left            =   270
            Picture         =   "DigitalInput.frx":1D3A
            Top             =   45
            Width           =   240
         End
      End
      Begin Threed.SSPanel sspInputControl 
         Height          =   345
         Index           =   15
         Left            =   120
         TabIndex        =   16
         Top             =   5310
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "15"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin VB.Image imgOFFIOIndicator 
            Height          =   240
            Index           =   15
            Left            =   45
            Picture         =   "DigitalInput.frx":1E3C
            Top             =   45
            Width           =   240
         End
         Begin VB.Image imgONIOIndicator 
            Height          =   240
            Index           =   15
            Left            =   270
            Picture         =   "DigitalInput.frx":1F3E
            Top             =   45
            Width           =   240
         End
      End
   End
   Begin Threed.SSPanel sspStatus 
      Align           =   1  'Align Top
      Height          =   555
      Left            =   0
      TabIndex        =   17
      Top             =   0
      Width           =   2970
      _Version        =   65536
      _ExtentX        =   5239
      _ExtentY        =   979
      _StockProps     =   15
      Caption         =   "Version:"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   1
      Begin VB.Timer tmrScan 
         Left            =   1380
         Top             =   60
      End
      Begin VB.Image imgScanOFF 
         Height          =   240
         Left            =   2400
         Picture         =   "DigitalInput.frx":2040
         Top             =   120
         Visible         =   0   'False
         Width           =   240
      End
      Begin VB.Image imgScanON 
         Height          =   240
         Left            =   2640
         Picture         =   "DigitalInput.frx":2142
         Top             =   120
         Width           =   240
      End
   End
End
Attribute VB_Name = "frmDigitalInput"
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
'******************************************************************

'  assoiated digit out class
Private m_objMyClass As Object
Private m_blnInitStatus As Boolean

Private m_strName As String

Private Sub Form_Load()

   Dim i As Integer
   
   #If ccShip_Ver Then
      On Error GoTo Form_Load_Error
   #Else
      On Error GoTo 0
   #End If
    
   m_strName = Me.Name
   
   sspStatus.Caption = "Vrsion: " & App.Major & "." & App.Minor & "." & App.Revision

   imgScanOFF.Top = imgScanON.Top
   imgScanOFF.Left = imgScanON.Left
   imgScanOFF.Enabled = True
   imgScanON.Enabled = False
   
   tmrScan.Interval = 50000
   tmrScan.Enabled = False
   
   For i = 0 To 15
      imgONIOIndicator(i).Top = imgOFFIOIndicator(i).Top
      imgONIOIndicator(i).Left = imgOFFIOIndicator(i).Left
      imgONIOIndicator(i).Visible = False
      imgOFFIOIndicator(i).Visible = True
   Next i
   
   m_blnInitStatus = True
   
   Exit Sub
   
Form_Load_Error:

   m_blnInitStatus = False
   ProccessError "Form_Load", m_strName, Err.Number, Err.Description

End Sub 'Form_Load



Public Sub Initialize(objMyClass As Object)

   Set m_objMyClass = objMyClass
   If m_objMyClass Is Nothing Then
      m_blnInitStatus = False
   Else
      m_objMyClass.SetMyForm Me
      m_blnInitStatus = m_blnInitStatus And True
   End If
   
End Sub 'Initialize

Private Sub tmrScan_Timer()

   '  disable the timer events while scanning
   tmrScan.Enabled = False
   imgScanON.Visible = True
   imgScanOFF.Visible = False
   imgScanON.Refresh
   m_objMyClass.ScanNow
   imgScanON.Visible = False
   imgScanOFF.Visible = True
   imgScanON.Refresh
   tmrScan.Enabled = True
   
End Sub 'tmrScan_Timer



Public Sub UpDateDsp(intIndex As Integer, blnValue As Boolean)

   imgONIOIndicator(intIndex).Visible = blnValue
   imgOFFIOIndicator(intIndex).Visible = Not blnValue
      
End Sub 'UpDateDsp

Public Function InitStatus() As Boolean
    
    InitStatus = m_blnInitStatus
    
End Function 'InitStatus
