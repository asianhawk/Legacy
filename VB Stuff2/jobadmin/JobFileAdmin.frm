VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.1#0"; "COMDLG32.OCX"
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "COMCTL32.OCX"
Begin VB.Form frmJobFileAdmin 
   Caption         =   "Job File Administration"
   ClientHeight    =   4125
   ClientLeft      =   5445
   ClientTop       =   8355
   ClientWidth     =   7365
   Icon            =   "JobFileAdmin.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   4125
   ScaleWidth      =   7365
   Begin TabDlg.SSTab sstJobFile 
      Height          =   3615
      Left            =   0
      TabIndex        =   11
      Top             =   120
      Width           =   7335
      _ExtentX        =   12938
      _ExtentY        =   6376
      _Version        =   327680
      Tabs            =   2
      Tab             =   1
      TabHeight       =   529
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      TabCaption(0)   =   "&Jobs"
      Tab(0).ControlCount=   16
      Tab(0).ControlEnabled=   0   'False
      Tab(0).Control(0)=   "labTemplatePath"
      Tab(0).Control(0).Enabled=   -1  'True
      Tab(0).Control(1)=   "labTemplateName"
      Tab(0).Control(1).Enabled=   -1  'True
      Tab(0).Control(2)=   "labPartNumber"
      Tab(0).Control(2).Enabled=   -1  'True
      Tab(0).Control(3)=   "labJobsName"
      Tab(0).Control(3).Enabled=   -1  'True
      Tab(0).Control(4)=   "labLocationCode"
      Tab(0).Control(4).Enabled=   -1  'True
      Tab(0).Control(5)=   "labLastSeqNumber"
      Tab(0).Control(5).Enabled=   -1  'True
      Tab(0).Control(6)=   "txbTemplatePath"
      Tab(0).Control(6).Enabled=   -1  'True
      Tab(0).Control(7)=   "txbTemplateName"
      Tab(0).Control(7).Enabled=   -1  'True
      Tab(0).Control(8)=   "txbPartNumber"
      Tab(0).Control(8).Enabled=   -1  'True
      Tab(0).Control(9)=   "txbJobsName"
      Tab(0).Control(9).Enabled=   -1  'True
      Tab(0).Control(10)=   "dbcJobFile"
      Tab(0).Control(10).Enabled=   -1  'True
      Tab(0).Control(11)=   "cmdSave"
      Tab(0).Control(11).Enabled=   -1  'True
      Tab(0).Control(12)=   "cmdNew"
      Tab(0).Control(12).Enabled=   -1  'True
      Tab(0).Control(13)=   "cmdDelete"
      Tab(0).Control(13).Enabled=   -1  'True
      Tab(0).Control(14)=   "txbLocationCode"
      Tab(0).Control(14).Enabled=   -1  'True
      Tab(0).Control(15)=   "txbLastSeqNumber"
      Tab(0).Control(15).Enabled=   -1  'True
      TabCaption(1)   =   "&Common"
      Tab(1).ControlCount=   14
      Tab(1).ControlEnabled=   -1  'True
      Tab(1).Control(0)=   "labCommonData(0)"
      Tab(1).Control(0).Enabled=   0   'False
      Tab(1).Control(1)=   "labCommonData(1)"
      Tab(1).Control(1).Enabled=   0   'False
      Tab(1).Control(2)=   "labCommonData(2)"
      Tab(1).Control(2).Enabled=   0   'False
      Tab(1).Control(3)=   "labCommonData(3)"
      Tab(1).Control(3).Enabled=   0   'False
      Tab(1).Control(4)=   "labCommonData(4)"
      Tab(1).Control(4).Enabled=   0   'False
      Tab(1).Control(5)=   "labCommonData(5)"
      Tab(1).Control(5).Enabled=   0   'False
      Tab(1).Control(6)=   "dbcCommon"
      Tab(1).Control(6).Enabled=   0   'False
      Tab(1).Control(7)=   "txbCommonData(0)"
      Tab(1).Control(7).Enabled=   0   'False
      Tab(1).Control(8)=   "txbCommonData(1)"
      Tab(1).Control(8).Enabled=   0   'False
      Tab(1).Control(9)=   "txbCommonData(2)"
      Tab(1).Control(9).Enabled=   0   'False
      Tab(1).Control(10)=   "txbCommonData(3)"
      Tab(1).Control(10).Enabled=   0   'False
      Tab(1).Control(11)=   "txbCommonData(4)"
      Tab(1).Control(11).Enabled=   0   'False
      Tab(1).Control(12)=   "txbCommonData(5)"
      Tab(1).Control(12).Enabled=   0   'False
      Tab(1).Control(13)=   "cmdSaveCommon"
      Tab(1).Control(13).Enabled=   0   'False
      Begin VB.TextBox txbLastSeqNumber 
         DataField       =   "lngLastSeqNumber"
         DataSource      =   "dbcJobFile"
         Height          =   300
         Left            =   -72615
         TabIndex        =   29
         Text            =   "LastSeqNumber"
         Top             =   2295
         Width           =   1290
      End
      Begin VB.CommandButton cmdSaveCommon 
         Caption         =   "&Save "
         Height          =   435
         Left            =   5220
         TabIndex        =   28
         Top             =   2940
         Width           =   1635
      End
      Begin VB.TextBox txbCommonData 
         DataField       =   "txtLogFilePath"
         DataSource      =   "dbcCommon"
         Height          =   315
         Index           =   5
         Left            =   1800
         TabIndex        =   26
         Text            =   "LogFilePath"
         Top             =   2520
         Width           =   5355
      End
      Begin VB.TextBox txbCommonData 
         DataField       =   "txtLogFileName"
         DataSource      =   "dbcCommon"
         Height          =   315
         Index           =   4
         Left            =   1800
         TabIndex        =   24
         Text            =   "LogFileName"
         Top             =   2160
         Width           =   1155
      End
      Begin VB.TextBox txbCommonData 
         DataField       =   "txtKitFilePath"
         DataSource      =   "dbcCommon"
         Height          =   315
         Index           =   3
         Left            =   1800
         TabIndex        =   22
         Text            =   "KitFilePath"
         Top             =   1800
         Width           =   5355
      End
      Begin VB.TextBox txbCommonData 
         DataField       =   "txtKitFileName"
         DataSource      =   "dbcCommon"
         Height          =   315
         Index           =   2
         Left            =   1800
         TabIndex        =   20
         Text            =   "KitFileName"
         Top             =   1440
         Width           =   1155
      End
      Begin VB.TextBox txbCommonData 
         DataField       =   "intScanTries"
         DataSource      =   "dbcCommon"
         Height          =   315
         Index           =   1
         Left            =   1800
         MaxLength       =   1
         TabIndex        =   18
         Text            =   "2"
         Top             =   1080
         Width           =   255
      End
      Begin VB.TextBox txbCommonData 
         DataField       =   "chrLineCode"
         DataSource      =   "dbcCommon"
         Height          =   315
         Index           =   0
         Left            =   1800
         MaxLength       =   1
         TabIndex        =   16
         Text            =   "t"
         Top             =   720
         Width           =   255
      End
      Begin VB.Data dbcCommon 
         Caption         =   "tblCommon"
         Connect         =   "Access"
         DatabaseName    =   "S:\SoftwareDevelopment\Projects\Motorola_FL\Jobs.mdb"
         DefaultCursorType=   0  'DefaultCursor
         DefaultType     =   2  'UseODBC
         Exclusive       =   0   'False
         Height          =   375
         Left            =   1740
         Options         =   0
         ReadOnly        =   0   'False
         RecordsetType   =   1  'Dynaset
         RecordSource    =   "tblCommon"
         Top             =   2940
         Visible         =   0   'False
         Width           =   3015
      End
      Begin VB.TextBox txbLocationCode 
         DataField       =   "txtLocationCode"
         DataSource      =   "dbcJobFile"
         Height          =   300
         Left            =   -72615
         MaxLength       =   2
         TabIndex        =   12
         Text            =   "Lo"
         Top             =   1935
         Width           =   390
      End
      Begin VB.CommandButton cmdDelete 
         Caption         =   "&Delete"
         Height          =   390
         Left            =   -70200
         TabIndex        =   9
         Top             =   2820
         Width           =   975
      End
      Begin VB.CommandButton cmdNew 
         Caption         =   "&New"
         Height          =   390
         Left            =   -69135
         TabIndex        =   10
         Top             =   2820
         Width           =   975
      End
      Begin VB.CommandButton cmdSave 
         Caption         =   "&Save"
         Enabled         =   0   'False
         Height          =   390
         Left            =   -71295
         TabIndex        =   8
         Top             =   2820
         Width           =   975
      End
      Begin VB.Data dbcJobFile 
         Caption         =   "qurJobFile"
         Connect         =   "Access"
         DatabaseName    =   "S:\SoftwareDevelopment\Projects\Motorola_FL\Jobs.mdb"
         DefaultCursorType=   0  'DefaultCursor
         DefaultType     =   2  'UseODBC
         Exclusive       =   0   'False
         Height          =   405
         Left            =   -74610
         Options         =   0
         ReadOnly        =   0   'False
         RecordsetType   =   1  'Dynaset
         RecordSource    =   "qurJobFile"
         Top             =   2805
         Width           =   3150
      End
      Begin VB.TextBox txbJobsName 
         DataField       =   "txtJobsName"
         DataSource      =   "dbcJobFile"
         Height          =   285
         Left            =   -72615
         TabIndex        =   1
         Text            =   "JobsName"
         Top             =   480
         Width           =   1935
      End
      Begin VB.TextBox txbPartNumber 
         DataField       =   "txtPartNumber"
         DataSource      =   "dbcJobFile"
         Height          =   285
         Left            =   -72615
         MaxLength       =   6
         TabIndex        =   3
         Text            =   "txbPartNumber"
         Top             =   840
         Width           =   810
      End
      Begin VB.TextBox txbTemplateName 
         DataField       =   "txtTemplateName"
         DataSource      =   "dbcJobFile"
         Height          =   285
         Left            =   -72615
         TabIndex        =   5
         Text            =   "TemplateName"
         Top             =   1185
         Width           =   1950
      End
      Begin VB.TextBox txbTemplatePath 
         DataField       =   "txtTemplatePath"
         DataSource      =   "dbcJobFile"
         Height          =   285
         Left            =   -72615
         TabIndex        =   7
         Text            =   "TemplatePath"
         Top             =   1560
         Width           =   4095
      End
      Begin VB.Label labLastSeqNumber 
         Alignment       =   1  'Right Justify
         Caption         =   "Last Seq Number"
         Height          =   255
         Left            =   -74650
         TabIndex        =   30
         Top             =   2280
         Width           =   2000
      End
      Begin VB.Label labCommonData 
         Alignment       =   1  'Right Justify
         Caption         =   "Log File Path"
         Height          =   255
         Index           =   5
         Left            =   120
         TabIndex        =   27
         Top             =   2520
         Width           =   1635
      End
      Begin VB.Label labCommonData 
         Alignment       =   1  'Right Justify
         Caption         =   "Log File Name"
         Height          =   255
         Index           =   4
         Left            =   120
         TabIndex        =   25
         Top             =   2160
         Width           =   1635
      End
      Begin VB.Label labCommonData 
         Alignment       =   1  'Right Justify
         Caption         =   "Kit File Path"
         Height          =   255
         Index           =   3
         Left            =   120
         TabIndex        =   23
         Top             =   1800
         Width           =   1635
      End
      Begin VB.Label labCommonData 
         Alignment       =   1  'Right Justify
         Caption         =   "Kit File Name"
         Height          =   255
         Index           =   2
         Left            =   120
         TabIndex        =   21
         Top             =   1440
         Width           =   1635
      End
      Begin VB.Label labCommonData 
         Alignment       =   1  'Right Justify
         Caption         =   "Scan Tries"
         Height          =   255
         Index           =   1
         Left            =   120
         TabIndex        =   19
         Top             =   1080
         Width           =   1635
      End
      Begin VB.Label labCommonData 
         Alignment       =   1  'Right Justify
         Caption         =   "Line Code"
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   17
         Top             =   720
         Width           =   1635
      End
      Begin VB.Label labLocationCode 
         Alignment       =   1  'Right Justify
         Caption         =   "Label Location"
         Height          =   255
         Left            =   -74650
         TabIndex        =   13
         Top             =   1920
         Width           =   2000
      End
      Begin VB.Label labJobsName 
         Alignment       =   1  'Right Justify
         Caption         =   "Name"
         Height          =   255
         Left            =   -74650
         TabIndex        =   0
         Top             =   480
         Width           =   2000
      End
      Begin VB.Label labPartNumber 
         Alignment       =   1  'Right Justify
         Caption         =   "Part Number"
         Height          =   255
         Left            =   -74650
         TabIndex        =   2
         Top             =   840
         Width           =   2000
      End
      Begin VB.Label labTemplateName 
         Alignment       =   1  'Right Justify
         Caption         =   "Label Template Name"
         Height          =   255
         Left            =   -74650
         TabIndex        =   4
         Top             =   1185
         Width           =   2000
      End
      Begin VB.Label labTemplatePath 
         Alignment       =   1  'Right Justify
         Caption         =   "Label Template Path"
         Height          =   255
         Left            =   -74650
         TabIndex        =   6
         Top             =   1560
         Width           =   2000
      End
   End
   Begin VB.PictureBox Sheridan1 
      Height          =   480
      Left            =   -10005
      ScaleHeight     =   420
      ScaleWidth      =   1140
      TabIndex        =   14
      Top             =   0
      Width           =   1200
   End
   Begin MSComDlg.CommonDialog cdlHelp 
      Left            =   0
      Top             =   0
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327681
   End
   Begin ComctlLib.StatusBar stbHelp 
      Align           =   2  'Align Bottom
      Height          =   345
      Left            =   0
      TabIndex        =   15
      Top             =   3780
      Width           =   7365
      _ExtentX        =   12991
      _ExtentY        =   609
      Style           =   1
      SimpleText      =   "stbHelp"
      _Version        =   327682
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   1
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Text            =   ""
            TextSave        =   ""
            Key             =   ""
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
   Begin MSComDlg.CommonDialog cdlOpenDB 
      Left            =   6420
      Top             =   -180
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327681
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuFileOpen 
         Caption         =   "&Open Job File ..."
         Shortcut        =   {F2}
      End
      Begin VB.Menu mnuSep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileExit 
         Caption         =   "E&xit"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&Help"
      Begin VB.Menu mnuHelpContents 
         Caption         =   "&Contents"
         Shortcut        =   {F1}
      End
      Begin VB.Menu mnuHelpAbout 
         Caption         =   "&About"
      End
   End
End
Attribute VB_Name = "frmJobFileAdmin"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

'*******************************************************************
'*           Computype, Inc.
'*       NextStep Automation Group
'*
'*     © Copywrite 1996 Computype, Inc.
'*
'*        3-Axis Label Applicator
'*        Job File Administration
'*
'*    Date of origin: 3/10/97
'*    Original author: Michael D. Reed
'*
'* Form purpose:
'*    This form is for maintaning job file
'*
'******************************************************************
Option Explicit

'  My name
Private m_strName As String

'******************************************************************
'  Constents for tabs on tab control
Private Const m_inxJOB = 0

'  Constents for data point grid
Private Const m_gcLNAME = 0
Private Const m_gclX_AXIS = 1
Private Const m_gclY_AXIS = 2
Private Const m_gclTHATA_AXIS = 3

'  Data base conestents
Private Const m_strDATA_POINT_INFO = "pqrDataPointInfo" 'Used by the point grid

'  data base for the job file
Private m_strJobFileName As String
Private m_dbJobFile As Database
Private m_rstJobFile As Recordset
Private m_qurDataPoints As QueryDef
Private m_rcsDataPoints As Recordset
Private m_dbConfiguration As Database
'******************************************************************

Private Sub cmdDelete_Click()

   dbcJobFile.Recordset.Delete
   dbcJobFile.Recordset.MoveFirst
   
End Sub 'cmdDelete_Click


Private Sub cmdNew_Click()

   dbcJobFile.Recordset.AddNew
   dbcJobFile.Recordset.Update
   dbcJobFile.Recordset.MoveLast
   
End Sub 'cmdNew_Click


Private Sub cmdSave_Click()

   dbcJobFile.UpdateRecord
   cmdSave.Enabled = False
      
End Sub 'cmdSave_Click

Private Sub cmdSaveCommon_Click()

   dbcCommon.UpdateRecord
   cmdSaveCommon.Enabled = False
   
End Sub 'cmdSaveCommon_Click

Private Sub dbcJobFile_Reposition()

   cmdSave.Enabled = False
   
End Sub 'dbcJobFile_Reposition



Private Sub Form_Load()

   Dim strDBName As String
   
   '  Set up form
   m_strName = Me.Name
   CenterForm Me
   Me.Caption = LoadResString(resFORM_MAIN_CAPTION) & m_strJobFileName
   
   '  Build the captions
   mnuFile.Caption = LoadResString(resMNU_FILE)
   mnuFileOpen.Caption = LoadResString(resMNU_OPEN)
   mnuFileExit.Caption = LoadResString(resMNU_EXIT)
   mnuHelp.Caption = LoadResString(resMNU_HELP)
   mnuHelpContents.Caption = LoadResString(resMNU_CONTENTS)
   mnuHelpAbout.Caption = LoadResString(resMNU_ABOUT)
   
   '  Tab Captions
   sstJobFile.TabCaption(m_inxJOB) = LoadResString(resTAB_JOBS)
   
   '  Clear help status line
   stbHelp.SimpleText = ""
  
   '   Command buttons captions
   cmdSave.Caption = LoadResString(resCMD_SAVE)
   cmdNew.Caption = LoadResString(resCMD_NEW)
   cmdDelete.Caption = LoadResString(resCMD_DELETE)
   'cmdNewDataPoint.Caption = LoadResString(resCMD_NEW)
   
   '  Fill in the labels
   labJobsName.Caption = LoadResString(resLABEL_JOB_NAME)
   labPartNumber.Caption = LoadResString(resLABEL_PART_NUMBER)
   labLocationCode.Caption = LoadResString(resLABEL_LOCATION_CODE)
   labTemplateName.Caption = LoadResString(resLABEL_TEMPLATE_NAME)
   labTemplatePath.Caption = LoadResString(resLABEL_TEMPLATE_PATH)
   labLocationCode.Caption = LoadResString(resLABEL_LABEL_LOCATION)
   labLastSeqNumber.Caption = LoadResString(resLABEL_LAST_SEQ_NUMBER)
   labCommonData(0).Caption = LoadResString(resLABEL_LINE_CODE)
   labCommonData(1).Caption = LoadResString(resLABEL_SCAN_TRIES)
   labCommonData(2).Caption = LoadResString(resLABEL_KIT_FILE_NAME)
   labCommonData(3).Caption = LoadResString(resLABEL_KIT_FILE_PATH)
   labCommonData(4).Caption = LoadResString(resLABEL_LOG_FILE_NAME)
   labCommonData(5).Caption = LoadResString(resLABEL_LOG_FILE_PATH)
   
   '  Job file status help
   labJobsName.Tag = LoadResString(resSTMSG_JOB_NAME)
   txbJobsName.Tag = LoadResString(resSTMSG_JOB_NAME)
   labPartNumber.Tag = LoadResString(resSTMSG_PART_NUMBER)
   txbPartNumber.Tag = LoadResString(resSTMSG_LOCATION_CODE)
   labLocationCode.Tag = LoadResString(resSTMSG_LOCATION_CODE)
   txbLocationCode.Tag = LoadResString(resSTMSG_PART_NUMBER)
   labTemplateName.Tag = LoadResString(resLABEL_TEMPLATE_NAME)
   txbTemplateName.Tag = LoadResString(resLABEL_TEMPLATE_NAME)
   labTemplatePath.Tag = LoadResString(resSTMSG_TEMPLATE_PATH)
   txbTemplatePath.Tag = LoadResString(resSTMSG_TEMPLATE_PATH)
   labLocationCode.Tag = LoadResString(resSTMSG_LOCATION_CODE)
   txbLocationCode.Tag = LoadResString(resSTMSG_LOCATION_CODE)
   labLastSeqNumber.Tag = LoadResString(resSTMSG_LAST_SEQ_NUMBER)
   txbLastSeqNumber.Tag = LoadResString(resSTMSG_LAST_SEQ_NUMBER)
   labCommonData(0).Tag = LoadResString(resSTMSG_LINE_CODE)
   txbCommonData(0).Tag = LoadResString(resSTMSG_LINE_CODE)
   labCommonData(1).Tag = LoadResString(resSTMSG_SCAN_TRIES)
   txbCommonData(1).Tag = LoadResString(resSTMSG_SCAN_TRIES)
   labCommonData(2).Tag = LoadResString(resSTMSG_KIT_FILE_NAME)
   txbCommonData(2).Tag = LoadResString(resSTMSG_KIT_FILE_NAME)
   labCommonData(3).Tag = LoadResString(resSTMSG_KIT_FILE_PATH)
   txbCommonData(3).Tag = LoadResString(resSTMSG_KIT_FILE_PATH)
   labCommonData(4).Tag = LoadResString(resSTMSG_LOG_FILE_NAME)
   txbCommonData(4).Tag = LoadResString(resSTMSG_LOG_FILE_NAME)
   labCommonData(5).Tag = LoadResString(resSTMSG_LOG_FILE_PATH)
   txbCommonData(5).Tag = LoadResString(resSTMSG_LOG_FILE_PATH)
   
   cmdSave.Tag = LoadResString(resSTMSG_SAVE_JOB)
   cmdDelete.Tag = LoadResString(resSTMSG_DELETE)
   cmdNew.Tag = LoadResString(resSTMSG_NEW_JOB)
   dbcJobFile.Tag = LoadResString(resSTMSG_DB_CONTROL)
      
   '  Now load the data controls
   strDBName = GetDBName()
   frmSplash.MousePointer = vbHourglass
   frmSplash.Refresh
   DoEvents
   
   OpenDB strDBName
   
   
End Sub 'Form_Load


Private Sub Form_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = frmJobFileAdmin.Tag
End Sub 'Form_MouseMove



Private Sub labCommonData_MouseMove(Index As Integer, Button As Integer, Shift As Integer, X As Single, Y As Single)

   stbHelp.SimpleText = labCommonData(Index).Tag
   
End Sub 'labCommonData_MouseMove


Private Sub labLastSeqNumber_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = labLastSeqNumber.Tag
End Sub 'labLastSeqNumber_MouseMove


Private Sub labLocationCode_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = labLocationCode.Tag
End Sub 'labLocationCode_MouseMove


Private Sub mnuHelpContents_Click()

   With cdlHelp
      .HelpFile = App.HelpFile
      .HelpCommand = cdlHelpContents
      .ShowHelp
   End With 'cdlHelp
   
End Sub 'mnuHelpContents_Click


Private Sub sstJobFile_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = sstJobFile.Tag
End Sub 'sstJobFile_MouseMove

Private Sub txbCommonData_Change(Index As Integer)

   cmdSaveCommon.Enabled = True
   
End Sub 'txbCommonData_Change


Private Sub txbCommonData_KeyPress(Index As Integer, KeyAscii As Integer)

   If Index <> 1 Then Exit Sub
   
   If Not ((Chr$(KeyAscii) Like "[0-9]") Or (Chr$(KeyAscii) = vbBack)) Then
      KeyAscii = 0
   End If
   
End Sub 'txbCommonData_KeyPress

Private Sub txbCommonData_MouseMove(Index As Integer, Button As Integer, Shift As Integer, X As Single, Y As Single)

   stbHelp.SimpleText = txbCommonData(Index).Tag
   
End Sub 'txbCommonData_MouseMove


Private Sub txbJobsName_Change()

   dbcJobFile.Caption = LoadResString(resLABEL_DATA_CONTROL) & txbJobsName.Text
   cmdSave.Enabled = True
   
End Sub 'txbJobsName_Change


Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)

   Dim strTital As String
   Dim strMessage As String
   Dim intResponce
   
   
   If cmdSave.Enabled Then
      intResponce = MsgBox(LoadResString(resMSG_JOB_SAVE), vbQuestion + vbYesNoCancel, LoadResString(resMSG_TITEL))
      If intResponce = vbCancel Then
         Cancel = 1  'cancel the cancel
         Exit Sub
      ElseIf intResponce = vbYes Then
         cmdSave_Click
      End If
   End If
   
End Sub 'Form_QueryUnload


Private Sub labJobsName_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = labJobsName.Tag
End Sub 'labJobsName_MouseMove


Private Sub txbJobsName_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = txbJobsName.Tag
End Sub 'txbJobsName_MouseMove


Private Sub labPartNumber_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = labPartNumber.Tag
End Sub 'labJobsPartNumber_MouseMove

Private Sub txbLastSeqNumber_Change()

   cmdSave.Enabled = True
   
End Sub 'txbLastSeqNumber_Change

Private Sub txbLastSeqNumber_KeyPress(KeyAscii As Integer)

   If Not ((Chr$(KeyAscii) Like "[0-9]") Or (Chr$(KeyAscii) = vbBack)) Then
      KeyAscii = 0
   End If
   
End Sub 'txbLastSeqNumber_KeyPress


Private Sub txbLastSeqNumber_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = txbLastSeqNumber.Tag
End Sub 'txbLastSeqNumber_MouseMove


Private Sub txbLocationCode_Change()

   cmdSave.Enabled = True
   
End Sub 'txbLocationCode_Change

Private Sub txbLocationCode_KeyPress(KeyAscii As Integer)

   If Not ((Chr$(KeyAscii) Like "[0-9]") Or (Chr$(KeyAscii) = vbBack)) Then
      KeyAscii = 0
   End If
   
End Sub 'txbLocationCode_KeyPress


Private Sub txbLocationCode_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = txbLocationCode.Tag
End Sub 'txbLocationCode_MouseMove


Private Sub txbPartNumber_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = txbPartNumber.Tag
End Sub 'txbJobsPartNumber_MouseMove




Private Sub labTemplateName_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = labTemplateName.Tag
End Sub 'labTemplateName_MouseMove


Private Sub txbTemplateName_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = txbTemplateName.Tag
End Sub 'txbTemplateName_MouseMove


Private Sub labTemplatePath_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = labTemplatePath.Tag
End Sub 'labTemplatePath_MouseMove


Private Sub txbTemplatePath_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = txbTemplatePath.Tag
End Sub 'txbTemplatePath_MouseMove




Private Sub cmdSave_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = cmdSave.Tag
End Sub 'cmdSave_MouseMove


Private Sub cmdDelete_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = cmdDelete.Tag
End Sub 'cmdDelete_MouseMove


Private Sub cmdNew_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = cmdNew.Tag
End Sub 'cmdNew_MouseMove


Private Sub dbcJobFile_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = dbcJobFile.Tag
End Sub 'dbcJobFile_MouseMove


Private Sub mnuFileExit_Click()

   End
   
End Sub 'mnuFileexit_Click

Private Sub mnuFileOpen_Click()
   
   OpenDB GetDBName()
   dbcJobFile.Refresh
   
End Sub 'mnuFileOpen_Click

Private Sub mnuHelpAbout_Click()

   frmAbout.Show vbModal
   
End Sub  'mnuHelpAbout_Click


Private Function GetDBName() As String

   cdlOpenDB.DialogTitle = LoadResString(resFORM_OPEN_JOB_FILE)
   cdlOpenDB.Filter = LoadResString(resJOB_FILE_FILTER)
   
   On Error Resume Next 'no error handling because test form
   cdlOpenDB.ShowOpen
   
   GetDBName = cdlOpenDB.filename
   m_strJobFileName = cdlOpenDB.FileTitle
   
   On Error GoTo 0

End Function 'GetDBName



Private Sub txbPartNumber_Change()

   cmdSave.Enabled = True
   
End Sub 'txbJobsPartNumber_Change

Private Sub txbTemplateName_Change()

   cmdSave.Enabled = True
   
End Sub 'txbTemplateName_Change


Private Sub txbTemplatePath_Change()

   cmdSave.Enabled = True
   
End Sub 'txbTemplatePath_Change



Private Sub OpenDB(strDBName As String)

   #If ccShip_Ver Then
      On Error GoTo OpenDB_Error
   #Else
      On Error GoTo 0
   #End If

   If strDBName <> "" Then
      dbcJobFile.DatabaseName = strDBName
      dbcCommon.DatabaseName = strDBName

      Set m_dbJobFile = Workspaces(0).OpenDatabase(strDBName)
   
      Me.Caption = LoadResString(resFORM_MAIN_CAPTION) & m_strJobFileName
   
   End If
   
   Me.Refresh
   DoEvents
   
   Exit Sub

OpenDB_Error:

   ProccessError "OpenDB", m_strName, Err.Number, Err.Description

End Sub 'OpenDB


