VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.1#0"; "COMDLG32.OCX"
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "COMCTL32.OCX"
Object = "{0BA686C6-F7D3-101A-993E-0000C0EF6F5E}#1.0#0"; "THREED32.OCX"
Begin VB.Form frmMain 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "frmMain"
   ClientHeight    =   6180
   ClientLeft      =   1230
   ClientTop       =   1965
   ClientWidth     =   7275
   Icon            =   "Main.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   0
   ScaleWidth      =   0
   ShowInTaskbar   =   0   'False
   Begin Threed.SSPanel sspLabelingInfo 
      Align           =   4  'Align Right
      Height          =   5730
      Left            =   2250
      TabIndex        =   0
      Top             =   0
      Width           =   5025
      _Version        =   65536
      _ExtentX        =   8864
      _ExtentY        =   10107
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
      BorderWidth     =   1
      BevelInner      =   1
      Begin Threed.SSFrame ssfLables 
         Height          =   1575
         Left            =   390
         TabIndex        =   4
         Top             =   1995
         Width           =   4230
         _Version        =   65536
         _ExtentX        =   7461
         _ExtentY        =   2778
         _StockProps     =   14
         Caption         =   "ssfLables"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Begin VB.Label labTextScaned 
            BackColor       =   &H00FFFFFF&
            BorderStyle     =   1  'Fixed Single
            Caption         =   "labTextScaned"
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   345
            Left            =   1800
            TabIndex        =   18
            Top             =   945
            Width           =   2265
         End
         Begin VB.Label labTextPrinted 
            BackColor       =   &H00FFFFFF&
            BorderStyle     =   1  'Fixed Single
            Caption         =   "labTextPrinted"
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   345
            Left            =   1800
            TabIndex        =   17
            Top             =   435
            Width           =   2265
         End
         Begin VB.Label labScaned 
            Alignment       =   1  'Right Justify
            AutoSize        =   -1  'True
            Caption         =   "labScaned"
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
            Left            =   405
            TabIndex        =   6
            Top             =   945
            Width           =   1290
         End
         Begin VB.Label labPrinted 
            Alignment       =   1  'Right Justify
            AutoSize        =   -1  'True
            Caption         =   "labPrinted"
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
            Left            =   465
            TabIndex        =   5
            Top             =   420
            Width           =   1230
         End
      End
      Begin VB.Label labMessages 
         BackColor       =   &H00C0C0C0&
         Caption         =   "labMessages"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000000FF&
         Height          =   1785
         Left            =   330
         TabIndex        =   19
         Top             =   3810
         Width           =   4440
         WordWrap        =   -1  'True
      End
      Begin VB.Label labTextQuantity 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         Caption         =   "labTextQuantity"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   345
         Left            =   2100
         TabIndex        =   16
         Top             =   1380
         Width           =   2265
      End
      Begin VB.Label labTextPartNumber 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         Caption         =   "labTextPartNumber"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   345
         Left            =   2115
         TabIndex        =   15
         Top             =   900
         Width           =   2265
      End
      Begin VB.Label labTextJobName 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         Caption         =   "labTextJobName"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   360
         Left            =   2115
         TabIndex        =   14
         Top             =   375
         Width           =   2250
      End
      Begin VB.Label labJobName 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "labJobName"
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
         Left            =   525
         TabIndex        =   8
         Top             =   345
         Width           =   1500
      End
      Begin VB.Label labQuantity 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "labQuantity"
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
         Left            =   645
         TabIndex        =   3
         Top             =   1395
         Width           =   1380
      End
      Begin VB.Label labPartNumber 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "labPartNumber"
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
         Left            =   225
         TabIndex        =   1
         Top             =   870
         Width           =   1800
      End
   End
   Begin Threed.SSPanel sspToolBar 
      Align           =   3  'Align Left
      Height          =   5730
      Left            =   0
      TabIndex        =   7
      Top             =   0
      Width           =   1350
      _Version        =   65536
      _ExtentX        =   2381
      _ExtentY        =   10107
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
      BorderWidth     =   1
      BevelInner      =   1
      Begin Threed.SSPanel sspRunJob 
         Height          =   1095
         Left            =   45
         TabIndex        =   9
         Top             =   1365
         Width           =   1245
         _Version        =   65536
         _ExtentX        =   2196
         _ExtentY        =   1931
         _StockProps     =   15
         Caption         =   "sspRunJob"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Alignment       =   8
         Begin Threed.SSCommand sscRunJob 
            Height          =   1005
            Left            =   45
            TabIndex        =   20
            Top             =   30
            Width           =   1155
            _Version        =   65536
            _ExtentX        =   2037
            _ExtentY        =   1773
            _StockProps     =   78
            Caption         =   "sscRunJob"
            BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
               Name            =   "MS Sans Serif"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Enabled         =   0   'False
            Picture         =   "Main.frx":0442
         End
      End
      Begin Threed.SSPanel sspOpenJob 
         Height          =   1095
         Left            =   60
         TabIndex        =   10
         Top             =   75
         Width           =   1245
         _Version        =   65536
         _ExtentX        =   2196
         _ExtentY        =   1931
         _StockProps     =   15
         Caption         =   "sspOpenJob"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Autosize        =   3
         Begin Threed.SSCommand sscOpenJob 
            Height          =   1005
            Left            =   45
            TabIndex        =   11
            Top             =   45
            Width           =   1155
            _Version        =   65536
            _ExtentX        =   2037
            _ExtentY        =   1773
            _StockProps     =   78
            Caption         =   "sscOpenJob"
            BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
               Name            =   "MS Sans Serif"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Picture         =   "Main.frx":1034
         End
      End
      Begin Threed.SSPanel sspExit 
         Height          =   1095
         Left            =   60
         TabIndex        =   12
         Top             =   2730
         Width           =   1245
         _Version        =   65536
         _ExtentX        =   2196
         _ExtentY        =   1931
         _StockProps     =   15
         Caption         =   "sspExit"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Autosize        =   3
         Begin Threed.SSCommand sscExit 
            Height          =   1005
            Left            =   45
            TabIndex        =   13
            Top             =   45
            Width           =   1155
            _Version        =   65536
            _ExtentX        =   2037
            _ExtentY        =   1773
            _StockProps     =   78
            Caption         =   "sscExit"
            BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
               Name            =   "MS Sans Serif"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Picture         =   "Main.frx":16AE
         End
      End
   End
   Begin MSComDlg.CommonDialog cdlHelp 
      Left            =   1575
      Top             =   1140
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327681
      DialogTitle     =   "Labeler Help"
      HelpFile        =   "Labler.hlp"
   End
   Begin MSComDlg.CommonDialog cdlOpenJobDB 
      Left            =   1560
      Top             =   555
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327681
      DialogTitle     =   "cdbOpenJobDB"
   End
   Begin ComctlLib.StatusBar stbStatus 
      Align           =   2  'Align Bottom
      Height          =   450
      Left            =   0
      TabIndex        =   2
      Top             =   5730
      Width           =   7275
      _ExtentX        =   12832
      _ExtentY        =   794
      Style           =   1
      SimpleText      =   "stbStatus"
      _Version        =   327682
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   1
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
      EndProperty
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin VB.Image imgLablerRunning 
      Height          =   465
      Left            =   1545
      Picture         =   "Main.frx":1940
      Top             =   2340
      Visible         =   0   'False
      Width           =   480
   End
   Begin VB.Image imgLablerInterrupted 
      Height          =   510
      Left            =   1530
      Picture         =   "Main.frx":2522
      Top             =   4605
      Visible         =   0   'False
      Width           =   525
   End
   Begin VB.Image imgLablerIdle 
      Height          =   465
      Left            =   1530
      Picture         =   "Main.frx":33BC
      Top             =   4095
      Visible         =   0   'False
      Width           =   480
   End
   Begin VB.Image imgLablerDisabled 
      Height          =   510
      Left            =   1515
      Picture         =   "Main.frx":3F9E
      Top             =   3525
      Visible         =   0   'False
      Width           =   525
   End
   Begin VB.Image imgLablerComplete 
      Height          =   465
      Left            =   1545
      Picture         =   "Main.frx":4E38
      Top             =   2925
      Visible         =   0   'False
      Width           =   480
   End
   Begin VB.Menu mnuFile 
      Caption         =   "mnuFile"
      Begin VB.Menu mnuFileOpen 
         Caption         =   "mnuFileOpen"
         Shortcut        =   {F2}
      End
      Begin VB.Menu mnuFileOpenJobFile 
         Caption         =   "mnuOpenJobFile"
         Shortcut        =   {F4}
      End
      Begin VB.Menu mnuFileSep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFilePrint 
         Caption         =   "mnuFilePrint"
         Enabled         =   0   'False
         Shortcut        =   {F3}
      End
      Begin VB.Menu mnuFileReset 
         Caption         =   "mnuFileReset"
         Begin VB.Menu mnuFileResetPrinter 
            Caption         =   "mnuFileResetPrinter"
         End
         Begin VB.Menu mnuFileResetIAI 
            Caption         =   "mnuFileResetIAI"
         End
         Begin VB.Menu mnuFileResetScanner 
            Caption         =   "mnuFileResetScanner"
         End
      End
      Begin VB.Menu mnuFileSep2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileExit 
         Caption         =   "mnuFileExit"
      End
   End
   Begin VB.Menu mnuRun 
      Caption         =   "mnuRun"
      Enabled         =   0   'False
   End
   Begin VB.Menu mnuView 
      Caption         =   "mnuView"
      Begin VB.Menu mnuViewHistory 
         Caption         =   "mnuViewHistory"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuViewSep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuViewComPorts 
         Caption         =   "mnuViewComPorts"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuViewDigIO 
         Caption         =   "mnuViewDigIO"
         Checked         =   -1  'True
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "mnuHelp"
      Begin VB.Menu mnuHelpContents 
         Caption         =   "mnuHelpContents"
         Shortcut        =   {F1}
      End
      Begin VB.Menu mnuHelpSearch 
         Caption         =   "mnuHelpSearch"
         Enabled         =   0   'False
         Visible         =   0   'False
      End
      Begin VB.Menu mnuHelpSep 
         Caption         =   "-"
      End
      Begin VB.Menu mnuHelpAbout 
         Caption         =   "mnuHelpAbout"
      End
   End
End
Attribute VB_Name = "frmMain"
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
'*             Main form
'*
'*
'*    Customer: Lucent Technologies
'*              Shreveport, LA
'*
'*
'*    Date of origin: 1/21/97
'*    Original author: Michael D. Reed
'*
'* Form purpose:
'*    The main human interface and top level control
'*    for the 3-axies Label Applicator.
'*
'************************************************************************
Option Explicit

'  My name
Private m_strName As String

'  Labeler class this form interactes with
Private m_objLabeler As Object
Private m_objPrinter As Object  ' added 05-27-98

'  Need so both menu and switch work together
Private m_strRun As String

Private m_lngQuanity As Long
Private m_strSerialNumber As String

'  Message label message list
Private ma_strMsgList(1 To 5) As String

Public Function Initialize(objLabeler As Object, objPrinter As Object) As Boolean

   #If ccShip_Ver Then
      On Error GoTo Initialize_Error
   #Else
      On Error GoTo 0
   #End If

   Set m_objLabeler = objLabeler
   Set m_objPrinter = objPrinter
   m_objLabeler.SetMainForm Me
   
   Initialize = True
   
   stbStatus.SimpleText = LoadResString(resMSG_STAT_LABLER_READY)

   Exit Function

Initialize_Error:

   ProccessError "Initialize", m_strName, Err.Number, Err.Description
   Initialize = False

End Function 'Initialize


Private Sub Form_KeyPress(KeyAscii As Integer)

   #If ccShip_Ver Then
      On Error GoTo Form_KeyPress_Error
   #Else
      On Error GoTo 0
   #End If

   If g_blnJobReady And ((UCase(Chr(KeyAscii)) = "R") And Not g_blnJobRunning) Then
      m_objLabeler.RunStopJob
      KeyAscii = 0
   ElseIf g_blnJobReady And ((UCase(Chr(KeyAscii)) = "S") And g_blnJobRunning) Then
      m_objLabeler.RunStopJob
      KeyAscii = 0
   End If
   
   Exit Sub

Form_KeyPress_Error:

   ProccessError "Form_KeyPress", m_strName, Err.Number, Err.Description

End Sub 'Form_KeyPress

Private Sub Form_Load()

   #If ccShip_Ver Then
      On Error GoTo Form_Load_Error
   #Else
      On Error GoTo 0
   #End If

   m_strName = Me.Name
   
   '  Lable the menues
   '  File
   mnuFile.Caption = LoadResString(resMNU_FILE)
   mnuFileOpen.Caption = LoadResString(resMNU_OPEN)
   mnuFileOpenJobFile.Caption = LoadResString(resMNU_OPEN_JOB_FILE)
   mnuFilePrint.Caption = LoadResString(resMNU_PRINT_LABEL)
   mnuFileReset.Caption = LoadResString(resMNU_RESET)
   mnuFileResetIAI.Caption = LoadResString(resMNU_RESET_IAI)
   mnuFileResetPrinter.Caption = LoadResString(resMNU_RESET_PRINTER)
   mnuFileResetScanner.Caption = LoadResString(resMNU_RESET_SCANNER)
   mnuFileExit.Caption = LoadResString(resMNU_EXIT)
   '  Run
   mnuRun.Caption = LoadResString(resMNU_RUN)
   m_strRun = LoadResString(resMNU_RUN)
   '  View
   mnuView.Caption = LoadResString(resMNU_VIEW)
   mnuViewHistory.Caption = LoadResString(resMNU_HISTORY)
   mnuViewComPorts.Caption = LoadResString(resMNU_COMPORTS)
   mnuViewDigIO.Caption = LoadResString(resMNU_DIGITAL_IO)
   '  Help
   mnuHelp.Caption = LoadResString(resMNU_HELP)
   mnuHelpContents.Caption = LoadResString(resMNU_CONTENTS)
   mnuHelpSearch.Caption = LoadResString(resMNU_SEARCH)
   mnuHelpAbout.Caption = LoadResString(resMNU_ABOUT)
   
   '  Set up the form
   Me.Caption = LoadResString(resFORM_MAIN) & LoadResString(resFORM_MAIN_NO_JOB)
   Me.Width = 6495
   modUtilities.CenterForm Me
   
   '  Label command buttons
   sscOpenJob.Caption = LoadResString(resCND_NEW_JOB)
   sscExit.Caption = LoadResString(resCMD_EXIT)
   
   '  job run / idle button labeled on panal
   sscRunJob.Caption = LoadResString(resLABEL_MAIN_DISABLED)
   sscRunJob.Picture = imgLablerDisabled.Picture
   sscRunJob.Enabled = False
   
   '  Label labels
   labJobName.Caption = LoadResString(resLABEL_MAIN_NAME)
   labPartNumber.Caption = LoadResString(resLABEL_MAIN_PARTNUMBER)
   labQuantity.Caption = LoadResString(resLABEL_MAIN_QUANTITY)
   ssfLables.Caption = LoadResString(resLABEL_MAIN_LAST_LABEL)
   labPrinted.Caption = "Placed:" 'LoadResString(resLABEL_MAIN_PRINTED)
   labScaned.Caption = LoadResString(resLABEL_MAIN_SCANED)
   
   '  Clear label boxes
   labTextJobName.Caption = ""
   labTextPartNumber.Caption = ""
   labTextQuantity.Caption = ""
   labTextPrinted.Caption = ""
   labTextScaned.Caption = ""
   labMessages.Caption = ""
   
   '  clear status bar
   stbStatus.SimpleText = ""
   
   '  are we test mode
   If g_blnTest Then
      frmDigitalIO.WindowState = vbNormal
      mnuViewDigIO.Checked = True
      frmSerialComm.WindowState = vbNormal
      mnuViewComPorts.Checked = True
      frmHistory.WindowState = vbNormal
      mnuViewHistory.Checked = True
   Else
      frmDigitalIO.WindowState = vbNormal
      mnuViewDigIO.Checked = False
      frmSerialComm.WindowState = vbNormal
      mnuViewComPorts.Checked = False
      frmHistory.WindowState = vbNormal
      mnuViewHistory.Checked = False
   End If
   
   Exit Sub

Form_Load_Error:

   ProccessError "Form_Load", m_strName, Err.Number, Err.Description

End Sub 'Form_Load

Private Sub Form_Unload(Cancel As Integer)

   modMain.ExitEnd
   
End Sub 'Form_Unload





Private Sub mnuFileExit_Click()

   modMain.ExitEnd
   
End Sub 'mnuFileExit_Click

Private Sub mnuFileOpen_Click()

   GetJobData
   
End Sub 'mnuFileOpen

Private Sub mnuFileOpenJobFile_Click()

   OpenJobDB
   
End Sub 'mnuFileOpenJobFile_Click

Private Sub mnuFilePrint_Click()

   
   m_objLabeler.PrintTestLabel
   g_blnQueueOK = False
   
End Sub 'mnuFilePrint_Click


Private Sub mnuFileResetIAI_Click()

   m_objLabeler.ResetIAI
   
End Sub 'mnuFileResetIAI_Click


Private Sub mnuFileResetPrinter_Click()

   m_objLabeler.ResetPrinter
   g_blnQueueOK = False
   
End Sub 'mnuFileResetPrinter_Click


Private Sub mnuFileResetScanner_Click()

   m_objLabeler.ResetScanner
   
End Sub 'mnuFileResetScanner_Click

Private Sub mnuHelpAbout_Click()

   frmAbout.Show vbModal
   
End Sub 'mnuHelpAbout_Click






Private Sub mnuHelpContents_Click()

   With cdlHelp
      .HelpFile = App.HelpFile
      .HelpCommand = cdlHelpContents
      .ShowHelp
   End With 'cdlHelp
   
End Sub 'mnuHelpContents_Click

Private Sub mnuHelpSearch_Click()

   With cdlHelp
      .HelpFile = App.HelpFile
      .HelpCommand = cdlHelpIndex
      .ShowHelp
   End With 'cdlHelp
   
End Sub


Private Sub mnuRun_Click()

   m_objLabeler.RunStopJob
            
End Sub 'mnuRun_Click

Private Sub mnuViewComPorts_Click()

   With mnuViewComPorts
      If .Checked Then
         frmSerialComm.Hide
         .Checked = False
      Else
         frmSerialComm.Show
         .Checked = True
      End If
   End With 'mnuViewComPorts

End Sub 'mnuViewComPorts_Click

Private Sub mnuViewDigIO_Click()

   With mnuViewDigIO
      If .Checked Then
         frmDigitalIO.Hide
         .Checked = False
      Else
         frmDigitalIO.Show
         .Checked = True
      End If
   End With 'mnuViewDigIO

End Sub 'mnuViewDigIO_Click


Private Sub mnuViewHistory_Click()

   With mnuViewHistory
      If .Checked Then
         frmHistory.Hide
         .Checked = False
      Else
         frmHistory.Show
         .Checked = True
      End If
   End With 'mnuViewHistory
   
End Sub 'mnuViewHistory_Click


Private Sub sscExit_Click()

   modMain.ExitEnd

End Sub 'sscExit_Click

Private Sub sscOpenJob_Click()

   GetJobData
   
End Sub 'sscOpenJob_Click





Public Sub JobRun()

   sscOpenJob.Enabled = False
   sscRunJob.Picture = imgLablerRunning.Picture
   mnuRun.Caption = LoadResString(resMNU_STOP)
   sscRunJob.Caption = LoadResString(resLABEL_MAIN_RUNNING)
   stbStatus.SimpleText = LoadResString(resMSG_STAT_JOB_RUNNING)
   Me.Caption = LoadResString(resFORM_MAIN) & LoadResString(resFORM_MAIN_RUNNING)

End Sub 'JobRun

Public Sub JobEnd()


   mnuRun.Caption = LoadResString(resMNU_RUN)
   sscRunJob.Caption = LoadResString(resLABEL_MAIN_IDEL)
   sscRunJob.Picture = imgLablerComplete.Picture
   stbStatus.SimpleText = LoadResString(resMSG_STAT_JOB_COMPLETE)
   Me.Caption = LoadResString(resFORM_MAIN) & LoadResString(resFORM_MAIN_IDLE)
   sscOpenJob.Enabled = True

End Sub 'JobEnd


Public Sub GetJobData()

   #If ccShip_Ver Then
      On Error GoTo GetJobData_Error
   #Else
      On Error GoTo 0
   #End If

   
   frmOpenJob.Hide
   frmOpenJob.Initialize Me
   frmOpenJob.Show vbModal
   
   ProcessPrinterTemplate
   
   If g_blnJobReady Then
      JobRunEnable
      stbStatus.SimpleText = LoadResString(resMSG_STAT_JOB_LOADED_READY)
   End If

   modUtilities.MessageRemove
   
   Exit Sub

GetJobData_Error:

   ProccessError "GetJobData", m_strName, Err.Number, Err.Description

End Sub 'GetJobData

Public Sub InfoJob(strJobID As String, strName As String, strLastSerialNumber As String, _
                   strPartNumber As String, strPlantCode As String, _
                   strDescription As String, strQuanity As String, _
                   strTableName As String, strDBPath As String, _
                   strTemplate As String, strFormatName As String, _
                   strFieldCount As String, strTemplatePath As String)
                   
Dim strBuffer As String ' added 05-27-98
                   
   #If ccShip_Ver Then
      On Error GoTo InfoJob_Error
   #Else
      On Error GoTo 0
   #End If
  
   If g_blnTest Then Exit Sub

   If strPartNumber = "" Then
      Log "Main Form", "No job loaded"
      g_blnJobReady = False
   Else
      ' code added to clear queue *** llj 1/7/98
      g_blnQueueOK = (labTextJobName.Caption = strName)
      g_blnJobReady = m_objLabeler.InfoJob(strJobID:=strJobID, strName:=strName, strLastSerialNumber:=strLastSerialNumber, _
                         strPartNumber:=strPartNumber, strPlantCode:=strPlantCode, _
                        strDescription:=strDescription, strQuanity:=strQuanity, _
                        strTableName:=strTableName, strDBPath:=strDBPath, _
                        strTemplate:=strTemplate, strFormatName:=strFormatName, _
                        strFieldCount:=strFieldCount, strTemplatePath:=strTemplatePath)
         
         
      m_objPrinter.m_strTemplate_FileName = strTemplatePath + "\" + strTemplate
      modUtilities.Log "Main Form", "Job Loaded" & vbCrLf & Space(3) & _
          "strJobID:=" & strJobID & vbCrLf & Space(3) & "strName:=" & strName & vbCrLf & Space(3) & _
          "strPartNumber:=" & strPartNumber & vbCrLf & Space(3) & "LastSerialNumber:=" & strLastSerialNumber & vbCrLf & Space(3) & _
          "strDescription:=" & strDescription & vbCrLf & Space(3) & "strQuanity:=" & strQuanity & vbCrLf & Space(3) & _
          "strPlantCode:=" & strPlantCode & vbCrLf & Space(3) & _
          "strTableName:=" & strTableName & vbCrLf & Space(3) & "strDBPath:=" & strDBPath & vbCrLf & Space(3) & _
          "strTemplate:=" & strTemplate & vbCrLf & Space(3) & "strFormatName:=" & strFormatName & vbCrLf & Space(3) & _
          "strFieldCount:=" & strFieldCount & vbCrLf & Space(3) & "strTemplatePath:=" & strTemplatePath & vbCrLf
   End If
   Exit Sub

InfoJob_Error:

   ProccessError "InfoJob", m_strName, Err.Number, Err.Description

                    
End Sub 'InfoJob



Public Sub JobRunEnable()

   sscRunJob.Caption = LoadResString(resLABEL_MAIN_IDEL)
   sscRunJob.Picture = imgLablerIdle.Picture
   sscRunJob.Enabled = True
   mnuRun.Enabled = True
   mnuFilePrint.Enabled = True
   Me.Caption = LoadResString(resFORM_MAIN) & LoadResString(resFORM_MAIN_IDLE)
   stbStatus.SimpleText = LoadResString(resMSG_STAT_JOB_READY)

End Sub 'JobRunEnable




Public Sub MessageRemove(intMsg As Integer)

   Dim i As Integer
   
   #If ccShip_Ver Then
      On Error GoTo MessageRemove_Error
   #Else
      On Error GoTo 0
   #End If

   For i = intMsg To UBound(ma_strMsgList) - 1
      ma_strMsgList(i) = ma_strMsgList(i + 1)
   Next i
   
   ma_strMsgList(UBound(ma_strMsgList)) = ""
   
   MessageShow
   
   Exit Sub

MessageRemove_Error:

   ProccessError "MessageRemove", m_strName, Err.Number, Err.Description

End Sub 'RemoveMessage

Public Function MessageDisplay(strMsg As String) As Integer

   Dim i As Integer
   
   #If ccShip_Ver Then
      On Error GoTo MessageDisplay_Error
   #Else
      On Error GoTo 0
   #End If
   
   For i = 1 To UBound(ma_strMsgList)
      If ma_strMsgList(i) = "" Then
         ma_strMsgList(i) = strMsg
         MessageDisplay = i
         Exit For
      End If
   Next i
   
   MessageShow
   
   Exit Function

MessageDisplay_Error:

   ProccessError "MessageDisplay", m_strName, Err.Number, Err.Description
   MessageDisplay = -1

End Function 'MessageDisplay

Private Sub MessageShow()

   Dim i As Integer
   Dim strTmp As String
   
   #If ccShip_Ver Then
      On Error GoTo MessageShow_Error
   #Else
      On Error GoTo 0
   #End If

   labMessages.Caption = ""
   
   For i = 1 To UBound(ma_strMsgList)
      If ma_strMsgList(i) <> "" Then
         strTmp = strTmp & ma_strMsgList(i) & vbCrLf
      End If
   Next i
   
   labMessages.Caption = strTmp
   labMessages.Refresh
   
   Exit Sub

MessageShow_Error:

   ProccessError "MessageShow", m_strName, Err.Number, Err.Description

End Sub 'MessageShow

Public Sub PanelComplete(strQuantity As String)

   #If ccShip_Ver Then
      On Error Resume Next
   #Else
      On Error GoTo 0
   #End If

   stbStatus.SimpleText = LoadResString(resMSG_STAT_PANEL_COMPLETE)
   labTextQuantity.Caption = strQuantity
   
End Sub 'PanelComplete

Public Sub PanelReady()

   #If ccShip_Ver Then
      On Error Resume Next
   #Else
      On Error GoTo 0
   #End If

   stbStatus.SimpleText = LoadResString(resMSG_STAT_PANEL_LABELING)
   
End Sub 'PanelReady

Public Sub JobInterrupted(blnStatus As Boolean)

   If blnStatus Then
      sscOpenJob.Enabled = False
      If Not g_blnJobReady Then
         stbStatus.SimpleText = LoadResString(resMSG_STAT_LABELING_INTERRUPTED)
         sscRunJob.Picture = imgLablerInterrupted.Picture
         sscRunJob.Caption = LoadResString(resLABEL_MAIN_INTERRUPTED)
         Me.Caption = LoadResString(resFORM_MAIN) & LoadResString(resFORM_MAIN_INTERRUPTED)
      End If
   Else
      If Not g_blnJobReady Then
         sscOpenJob.Enabled = True
      ElseIf g_blnJobRunning Then
         JobRun
      Else
         sscRunJob.Picture = imgLablerIdle.Picture
         Me.Caption = LoadResString(resFORM_MAIN) & LoadResString(resFORM_MAIN_IDLE)
         sscRunJob.Enabled = True
      End If
   End If
   
End Sub 'JobInterrupted

Public Sub JobHolding(blnStatus As Boolean)

   If g_blnJobRunning Then
      If blnStatus Then
         stbStatus.SimpleText = LoadResString(resMSG_STAT_LABELING_HOLDING)
         sscRunJob.Picture = imgLablerInterrupted.Picture
         sscRunJob.Caption = LoadResString(resLABEL_MAIN_HOLDING)
         Me.Caption = LoadResString(resFORM_MAIN) & LoadResString(resFORM_MAIN_HOLDING)
      Else
         stbStatus.SimpleText = LoadResString(resMSG_STAT_PANEL_LABELING)
         sscRunJob.Picture = imgLablerRunning.Picture
         sscRunJob.Caption = LoadResString(resLABEL_MAIN_RUNNING)
         Me.Caption = LoadResString(resFORM_MAIN) & LoadResString(resFORM_MAIN_RUNNING)
      End If
   End If
   
End Sub 'JobHolding

Private Sub sscRunJob_Click()

   m_objLabeler.RunStopJob
         
End Sub 'sscRunJob



Private Sub OpenJobDB()

   cdlOpenJobDB.DialogTitle = LoadResString(resFORM_OPEN_JOB_FILE)
   
   cdlOpenJobDB.Filter = LoadResString(resJOB_FILE_FILTER)
   
   On Error Resume Next
   cdlOpenJobDB.ShowOpen
   
   On Error GoTo 0
   If cdlOpenJobDB.filename <> "" Then
      ' set file name for job file
      modMain.JobDatabaseName = cdlOpenJobDB.filename
      modMain.JobDatabaseFile = cdlOpenJobDB.FileTitle
   End If

End Sub 'OpenJobDB

Public Sub MessageClear()

   Dim i As Integer

   #If ccShip_Ver Then
      On Error GoTo MessageClear_Error
   #Else
      On Error GoTo 0
   #End If

   labMessages.Caption = ""
   labMessages.Refresh
   For i = 1 To UBound(ma_strMsgList)
      ma_strMsgList(i) = ""
   Next i
   
   Exit Sub

MessageClear_Error:

   ProccessError "MessageClear", m_strName, Err.Number, Err.Description

End Sub 'MessageClear



Public Sub ProcessPrinterTemplate()
 
  m_objPrinter.GetTemplate0d
End Sub
