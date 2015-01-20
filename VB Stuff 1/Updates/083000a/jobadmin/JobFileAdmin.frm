VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Object = "{00028C01-0000-0000-0000-000000000046}#1.0#0"; "DBGRID32.OCX"
Object = "{0BA686C6-F7D3-101A-993E-0000C0EF6F5E}#1.0#0"; "THREED32.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.1#0"; "COMDLG32.OCX"
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "COMCTL32.OCX"
Begin VB.Form frmJobFileAdmin 
   Caption         =   "Job File Administration"
   ClientHeight    =   7020
   ClientLeft      =   735
   ClientTop       =   630
   ClientWidth     =   7365
   Icon            =   "JobFileAdmin.frx":0000
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   7020
   ScaleWidth      =   7365
   Begin TabDlg.SSTab sstJobFile 
      Height          =   6255
      Left            =   30
      TabIndex        =   35
      Top             =   75
      Width           =   7335
      _ExtentX        =   12938
      _ExtentY        =   11033
      _Version        =   327681
      Tabs            =   2
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
      TabCaption(0)   =   "Jobs"
      TabPicture(0)   =   "JobFileAdmin.frx":0442
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "labTempate"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).Control(1)=   "labTemplatePath"
      Tab(0).Control(1).Enabled=   0   'False
      Tab(0).Control(2)=   "labTableName"
      Tab(0).Control(2).Enabled=   0   'False
      Tab(0).Control(3)=   "labTemplateName"
      Tab(0).Control(3).Enabled=   0   'False
      Tab(0).Control(4)=   "labDBpath"
      Tab(0).Control(4).Enabled=   0   'False
      Tab(0).Control(5)=   "labPlantCode"
      Tab(0).Control(5).Enabled=   0   'False
      Tab(0).Control(6)=   "labSerilNumberStart"
      Tab(0).Control(6).Enabled=   0   'False
      Tab(0).Control(7)=   "labJobsPartNumber"
      Tab(0).Control(7).Enabled=   0   'False
      Tab(0).Control(8)=   "labJobsName"
      Tab(0).Control(8).Enabled=   0   'False
      Tab(0).Control(9)=   "Label1"
      Tab(0).Control(9).Enabled=   0   'False
      Tab(0).Control(10)=   "sspDataPoints"
      Tab(0).Control(10).Enabled=   0   'False
      Tab(0).Control(11)=   "txbTempate"
      Tab(0).Control(11).Enabled=   0   'False
      Tab(0).Control(12)=   "txbTemplatePath"
      Tab(0).Control(12).Enabled=   0   'False
      Tab(0).Control(13)=   "txbTableName"
      Tab(0).Control(13).Enabled=   0   'False
      Tab(0).Control(14)=   "txbTemplateName"
      Tab(0).Control(14).Enabled=   0   'False
      Tab(0).Control(15)=   "dbcDataPointInfo"
      Tab(0).Control(15).Enabled=   0   'False
      Tab(0).Control(16)=   "txbDBpath"
      Tab(0).Control(16).Enabled=   0   'False
      Tab(0).Control(17)=   "txbPlantCode"
      Tab(0).Control(17).Enabled=   0   'False
      Tab(0).Control(18)=   "txbSerilNumberStart"
      Tab(0).Control(18).Enabled=   0   'False
      Tab(0).Control(19)=   "txbJobsPartNumber"
      Tab(0).Control(19).Enabled=   0   'False
      Tab(0).Control(20)=   "txbJobsName"
      Tab(0).Control(20).Enabled=   0   'False
      Tab(0).Control(21)=   "txbJobID"
      Tab(0).Control(21).Enabled=   0   'False
      Tab(0).Control(22)=   "dbcJobFile"
      Tab(0).Control(22).Enabled=   0   'False
      Tab(0).Control(23)=   "cmdSave"
      Tab(0).Control(23).Enabled=   0   'False
      Tab(0).Control(24)=   "cmdNew"
      Tab(0).Control(24).Enabled=   0   'False
      Tab(0).Control(25)=   "cmdDelete"
      Tab(0).Control(25).Enabled=   0   'False
      Tab(0).Control(26)=   "Text1"
      Tab(0).Control(26).Enabled=   0   'False
      Tab(0).ControlCount=   27
      TabCaption(1)   =   "Global"
      TabPicture(1)   =   "JobFileAdmin.frx":045E
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "txbInitialWeekCode"
      Tab(1).Control(1)=   "txbYearCode"
      Tab(1).Control(2)=   "txbWeekCode"
      Tab(1).Control(3)=   "cmdSaveGlobal"
      Tab(1).Control(4)=   "txbDefalutePlantCode"
      Tab(1).Control(5)=   "ckbUseGlobalPN"
      Tab(1).Control(6)=   "txbInitialSerialNumber"
      Tab(1).Control(7)=   "dbcConfiguration"
      Tab(1).Control(8)=   "labInitialWeekCode"
      Tab(1).Control(9)=   "labYearCode"
      Tab(1).Control(10)=   "labWeekCode"
      Tab(1).Control(11)=   "labDefalutePlantCode"
      Tab(1).Control(12)=   "labInitialSerialNumber"
      Tab(1).ControlCount=   13
      Begin VB.TextBox Text1 
         DataField       =   "PWBDesignator"
         DataSource      =   "dbcJobFile"
         Height          =   285
         Left            =   2400
         TabIndex        =   41
         Text            =   "Text1"
         Top             =   3720
         Width           =   4095
      End
      Begin VB.CommandButton cmdDelete 
         Caption         =   "&Delete"
         Height          =   390
         Left            =   5160
         TabIndex        =   21
         Top             =   4905
         Width           =   975
      End
      Begin VB.CommandButton cmdNew 
         Caption         =   "&New"
         Height          =   390
         Left            =   6225
         TabIndex        =   32
         Top             =   4905
         Width           =   975
      End
      Begin VB.TextBox txbInitialWeekCode 
         DataField       =   "InitialWeekCode"
         DataSource      =   "dbcConfiguration"
         Height          =   375
         Left            =   -71790
         MaxLength       =   2
         TabIndex        =   31
         Text            =   "In"
         Top             =   3315
         Width           =   495
      End
      Begin VB.TextBox txbYearCode 
         DataField       =   "YearCode"
         DataSource      =   "dbcConfiguration"
         Height          =   375
         Left            =   -71835
         MaxLength       =   2
         TabIndex        =   27
         Text            =   "Ye"
         Top             =   2265
         Width           =   495
      End
      Begin VB.TextBox txbWeekCode 
         DataField       =   "WeekCode"
         DataSource      =   "dbcConfiguration"
         Height          =   375
         Left            =   -71820
         MaxLength       =   2
         TabIndex        =   29
         Text            =   "We"
         Top             =   2790
         Width           =   495
      End
      Begin VB.CommandButton cmdSaveGlobal 
         Caption         =   "&Save"
         Height          =   390
         Left            =   -69480
         TabIndex        =   33
         Top             =   3840
         Width           =   1440
      End
      Begin VB.CommandButton cmdSave 
         Caption         =   "&Save"
         Enabled         =   0   'False
         Height          =   390
         Left            =   4080
         TabIndex        =   20
         Top             =   4905
         Width           =   975
      End
      Begin VB.TextBox txbDefalutePlantCode 
         DataField       =   "DefalutePlantCode"
         DataSource      =   "dbcConfiguration"
         Height          =   375
         Left            =   -71835
         MaxLength       =   2
         TabIndex        =   25
         Text            =   "De"
         Top             =   1680
         Width           =   495
      End
      Begin VB.CheckBox ckbUseGlobalPN 
         Alignment       =   1  'Right Justify
         Caption         =   "Use global serial numbers"
         DataField       =   "UseGlobalPN"
         DataSource      =   "dbcConfiguration"
         Height          =   375
         Left            =   -73755
         TabIndex        =   34
         Top             =   600
         Width           =   2175
      End
      Begin VB.TextBox txbInitialSerialNumber 
         DataField       =   "InitialSerialNumber"
         DataSource      =   "dbcConfiguration"
         Height          =   375
         Left            =   -71835
         MaxLength       =   6
         TabIndex        =   23
         Text            =   "InitialSerialNumber"
         Top             =   1200
         Width           =   1935
      End
      Begin VB.Data dbcConfiguration 
         Caption         =   "Configuration"
         Connect         =   "Access"
         DatabaseName    =   "C:\labeler\lucenttechSP.mdb"
         DefaultCursorType=   0  'DefaultCursor
         DefaultType     =   2  'UseODBC
         Exclusive       =   0   'False
         Height          =   375
         Left            =   -74385
         Options         =   0
         ReadOnly        =   0   'False
         RecordsetType   =   0  'Table
         RecordSource    =   "tblconfiguration"
         Top             =   4380
         Visible         =   0   'False
         Width           =   3975
      End
      Begin VB.Data dbcJobFile 
         Caption         =   "qurJobFile"
         Connect         =   "Access"
         DatabaseName    =   "C:\labeler\lucenttechSP.mdb"
         DefaultCursorType=   0  'DefaultCursor
         DefaultType     =   2  'UseODBC
         Exclusive       =   0   'False
         Height          =   405
         Left            =   4080
         Options         =   0
         ReadOnly        =   0   'False
         RecordsetType   =   1  'Dynaset
         RecordSource    =   "qurJobFile"
         Top             =   5400
         Width           =   3150
      End
      Begin VB.TextBox txbJobID 
         DataField       =   "JobsID"
         DataSource      =   "dbcJobFile"
         Height          =   285
         Left            =   6120
         TabIndex        =   36
         Text            =   "JobsID"
         Top             =   4560
         Visible         =   0   'False
         Width           =   1095
      End
      Begin VB.TextBox txbJobsName 
         DataField       =   "JobsName"
         DataSource      =   "dbcJobFile"
         Height          =   285
         Left            =   2385
         TabIndex        =   1
         Text            =   "JobsName"
         Top             =   480
         Width           =   1935
      End
      Begin VB.TextBox txbJobsPartNumber 
         DataField       =   "JobsPartNumber"
         DataSource      =   "dbcJobFile"
         Height          =   285
         Left            =   2400
         MaxLength       =   9
         TabIndex        =   3
         Text            =   "JobsPartNumber"
         Top             =   840
         Width           =   1935
      End
      Begin VB.TextBox txbSerilNumberStart 
         DataField       =   "SerilNumberStart"
         DataSource      =   "dbcJobFile"
         Height          =   285
         Left            =   2400
         MaxLength       =   6
         TabIndex        =   5
         Text            =   "SerilNumberStart"
         Top             =   1200
         Width           =   1935
      End
      Begin VB.TextBox txbPlantCode 
         DataField       =   "PlantCode"
         DataSource      =   "dbcJobFile"
         Height          =   285
         Left            =   2400
         MaxLength       =   2
         TabIndex        =   7
         Text            =   "PlantCode"
         Top             =   1560
         Width           =   615
      End
      Begin VB.TextBox txbDBpath 
         DataField       =   "DBpath"
         DataSource      =   "dbcJobFile"
         Height          =   285
         Left            =   2400
         TabIndex        =   9
         Text            =   "DBpath"
         Top             =   1920
         Width           =   4095
      End
      Begin VB.Data dbcDataPointInfo 
         Caption         =   "Data Point Info"
         Connect         =   "Access"
         DatabaseName    =   "C:\labeler\lucenttechSP.mdb"
         DefaultCursorType=   0  'DefaultCursor
         DefaultType     =   2  'UseODBC
         Exclusive       =   0   'False
         Height          =   420
         Left            =   4680
         Options         =   0
         ReadOnly        =   0   'False
         RecordsetType   =   1  'Dynaset
         RecordSource    =   "tbldatapoints"
         Top             =   4080
         Visible         =   0   'False
         Width           =   2415
      End
      Begin VB.TextBox txbTemplateName 
         DataField       =   "TemplateName"
         DataSource      =   "dbcJobFile"
         Height          =   285
         Left            =   2400
         TabIndex        =   13
         Text            =   "TemplateName"
         Top             =   2640
         Width           =   1935
      End
      Begin VB.TextBox txbTableName 
         DataField       =   "TableName"
         DataSource      =   "dbcJobFile"
         Height          =   285
         Left            =   2400
         TabIndex        =   11
         Text            =   "TableName"
         Top             =   2280
         Width           =   1935
      End
      Begin VB.TextBox txbTemplatePath 
         DataField       =   "TemplatePath"
         DataSource      =   "dbcJobFile"
         Height          =   285
         Left            =   2400
         TabIndex        =   15
         Text            =   "TemplatePath"
         Top             =   3000
         Width           =   4095
      End
      Begin VB.TextBox txbTempate 
         DataField       =   "Tempate"
         DataSource      =   "dbcJobFile"
         Height          =   285
         Left            =   2400
         MultiLine       =   -1  'True
         ScrollBars      =   2  'Vertical
         TabIndex        =   17
         Text            =   "JobFileAdmin.frx":047A
         Top             =   3360
         Width           =   4095
      End
      Begin Threed.SSPanel sspDataPoints 
         Height          =   1935
         Left            =   240
         TabIndex        =   37
         Top             =   4080
         Width           =   3735
         _Version        =   65536
         _ExtentX        =   6588
         _ExtentY        =   3413
         _StockProps     =   15
         Caption         =   "SSPanel1"
         BackColor       =   12632256
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Begin VB.CommandButton cmdNewDataPoint 
            Caption         =   "&New"
            Height          =   375
            Left            =   240
            TabIndex        =   19
            Top             =   1440
            Width           =   975
         End
         Begin MSDBGrid.DBGrid dbgDataPoints 
            Bindings        =   "JobFileAdmin.frx":0482
            Height          =   1215
            Left            =   120
            OleObjectBlob   =   "JobFileAdmin.frx":049D
            TabIndex        =   18
            Top             =   120
            Width           =   3390
         End
      End
      Begin VB.Label Label1 
         Alignment       =   1  'Right Justify
         Caption         =   "PWBDesignator:"
         Height          =   255
         Left            =   600
         TabIndex        =   40
         Top             =   3720
         Width           =   1695
      End
      Begin VB.Label labInitialWeekCode 
         Alignment       =   1  'Right Justify
         Caption         =   "Code used for Lucent first week"
         Height          =   375
         Left            =   -74610
         TabIndex        =   30
         Top             =   3330
         Width           =   2655
      End
      Begin VB.Label labYearCode 
         Alignment       =   1  'Right Justify
         Caption         =   "Lucent Year"
         Height          =   375
         Left            =   -74115
         TabIndex        =   26
         Top             =   2265
         Width           =   2055
      End
      Begin VB.Label labWeekCode 
         Alignment       =   1  'Right Justify
         Caption         =   "Lucent Week Code"
         Height          =   375
         Left            =   -74085
         TabIndex        =   28
         Top             =   2790
         Width           =   2055
      End
      Begin VB.Label labDefalutePlantCode 
         Alignment       =   1  'Right Justify
         Caption         =   "Default Plant Code"
         Height          =   375
         Left            =   -74115
         TabIndex        =   24
         Top             =   1680
         Width           =   2055
      End
      Begin VB.Label labInitialSerialNumber 
         Alignment       =   1  'Right Justify
         Caption         =   "Initial Serial Number"
         Height          =   375
         Left            =   -74115
         TabIndex        =   22
         Top             =   1200
         Width           =   2055
      End
      Begin VB.Label labJobsName 
         Alignment       =   1  'Right Justify
         Caption         =   "Name"
         Height          =   255
         Left            =   360
         TabIndex        =   0
         Top             =   480
         Width           =   1935
      End
      Begin VB.Label labJobsPartNumber 
         Alignment       =   1  'Right Justify
         Caption         =   "Comcode"
         Height          =   255
         Left            =   360
         TabIndex        =   2
         Top             =   840
         Width           =   1935
      End
      Begin VB.Label labSerilNumberStart 
         Alignment       =   1  'Right Justify
         Caption         =   "Starting Serial Number"
         Height          =   255
         Left            =   360
         TabIndex        =   4
         Top             =   1200
         Width           =   1935
      End
      Begin VB.Label labPlantCode 
         Alignment       =   1  'Right Justify
         Caption         =   "Plant Code"
         Height          =   255
         Left            =   360
         TabIndex        =   6
         Top             =   1560
         Width           =   1935
      End
      Begin VB.Label labDBpath 
         Alignment       =   1  'Right Justify
         Caption         =   "ComcodeDB Path"
         Height          =   255
         Left            =   360
         TabIndex        =   8
         Top             =   1920
         Width           =   1935
      End
      Begin VB.Label labTemplateName 
         Alignment       =   1  'Right Justify
         Caption         =   "Label Template Name"
         Height          =   255
         Left            =   360
         TabIndex        =   12
         Top             =   2640
         Width           =   1935
      End
      Begin VB.Label labTableName 
         Alignment       =   1  'Right Justify
         Caption         =   "Comcode table name"
         Height          =   255
         Left            =   360
         TabIndex        =   10
         Top             =   2280
         Width           =   1935
      End
      Begin VB.Label labTemplatePath 
         Alignment       =   1  'Right Justify
         Caption         =   "Label Template Path"
         Height          =   255
         Left            =   360
         TabIndex        =   14
         Top             =   3000
         Width           =   1935
      End
      Begin VB.Label labTempate 
         Alignment       =   1  'Right Justify
         Caption         =   "Label Template"
         Height          =   255
         Left            =   360
         TabIndex        =   16
         Top             =   3360
         Width           =   1935
      End
   End
   Begin VB.PictureBox Sheridan1 
      Height          =   480
      Left            =   -10005
      ScaleHeight     =   420
      ScaleWidth      =   1140
      TabIndex        =   39
      Top             =   0
      Width           =   1200
   End
   Begin MSComDlg.CommonDialog cdlOpenDB 
      Left            =   3090
      Top             =   6300
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327681
   End
   Begin MSComDlg.CommonDialog cdlHelp 
      Left            =   2505
      Top             =   6300
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327681
   End
   Begin ComctlLib.StatusBar stbHelp 
      Align           =   2  'Align Bottom
      Height          =   420
      Left            =   0
      TabIndex        =   38
      Top             =   6600
      Width           =   7365
      _ExtentX        =   12991
      _ExtentY        =   741
      Style           =   1
      SimpleText      =   "stbHelp"
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
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
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
   Begin VB.Menu mnuView 
      Caption         =   "&View"
      Enabled         =   0   'False
      Visible         =   0   'False
      Begin VB.Menu mnuViewJobs 
         Caption         =   "&Jobs"
         Enabled         =   0   'False
         Visible         =   0   'False
      End
      Begin VB.Menu mnuViewGlobal 
         Caption         =   "&Global"
         Enabled         =   0   'False
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
'*
'*    Customer: Lucent Technologies
'*              Shreveport, LA
'*
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
Private Const m_idxGLOBAL = 1

'  Constents for data point grid
Private Const m_gclX_AXIS = 0
Private Const m_gclY_AXIS = 1
Private Const m_gclTHATA_AXIS = 2

'  Data base conestents
Private Const m_strDATA_POINT_INFO = "pqrDataPointInfo" 'Used by the point grid

'  data base for the job file
Private m_strJobFileName As String
Private m_dbJobFile As Database
Private m_rstJobFile As Recordset
Private m_qurDataPoints As QueryDef
Private m_rcsDataPoints As Recordset
Private m_dbConfiguration As Database
Private m_rstConfiguration As Recordset


Private Sub ckbUseGlobalPN_Click()

   cmdSaveGlobal.Enabled = True

End Sub 'ckbUseGlobalPN_Click

Private Sub cmdDelete_Click()

   dbcJobFile.Recordset.Delete
   dbcJobFile.Recordset.MoveFirst
   
End Sub 'cmdDelete_Click


Private Sub cmdNew_Click()

   dbcJobFile.Recordset.AddNew
   dbcJobFile.Recordset.Update
   dbcJobFile.Recordset.MoveLast
   
End Sub 'cmdNew_Click

Private Sub cmdNewDataPoint_Click()

   frmAddDataPoint.Show vbModal
   
End Sub 'cmdNewDataPoint_Click

Private Sub cmdSave_Click()

   dbcDataPointInfo.UpdateRecord
   dbcJobFile.UpdateRecord
   cmdSave.Enabled = False
      
End Sub 'cmdSave_Click


Private Sub cmdSaveGlobal_Click()

   dbcConfiguration.UpdateRecord
   
   cmdSaveGlobal.Enabled = False

End Sub 'cmdSaveGlobal_Click





Private Sub dbcConfiguration_Reposition()

   cmdSaveGlobal.Enabled = False

End Sub 'dbcConfiguration_Reposition


Private Sub dbcJobFile_Reposition()

   cmdSave.Enabled = False
   
End Sub 'dbcJobFile_Reposition




Private Sub dbgDataPoints_Change()

   cmdSave.Enabled = True
   
End Sub 'dbgDataPoints_Change

Private Sub dbgDataPoints_KeyPress(KeyAscii As Integer)

   '  exit sub if back space or Esc
   If (Chr(KeyAscii) = vbBack) Or KeyAscii = 27 Then Exit Sub
   
   With dbgDataPoints
      If .Col = 2 Then 'theta
         If Not (Chr(KeyAscii) Like "[09]") Then
            KeyAscii = 0
         End If
         If Len(.Columns(.Col).Text) >= 2 Then
            KeyAscii = 0
         End If
      Else ' X or Y Axis
         If Not (Chr(KeyAscii) Like "[0-9]") Then
            KeyAscii = 0
         End If
         If Len(.Columns(.Col).Text) >= 6 Then
            KeyAscii = 0
         End If
      End If
   End With 'dbgDataPoints
   
End Sub 'dbgDataPoints_KeyPress



Private Sub dbgDataPoints_RowColChange(LastRow As Variant, ByVal LastCol As Integer)

   If LastCol = 2 Then
      With dbgDataPoints.Columns(2)
         If .Text <> "90" And .Text <> "0" Then
            MsgBox LoadResString(resMSG_THATA_BAD), vbOKOnly, LoadResString(resTITLE_BAD_ENTRY)
            dbgDataPoints.Col = LastCol
         End If
      End With 'dbgDataPoints
   End If
   
End Sub 'dbgDataPoints_RowColChange


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
   mnuView.Caption = LoadResString(resMNU_VIEW)
   mnuViewJobs.Caption = LoadResString(resMNU_JOBS)
   mnuViewGlobal.Caption = LoadResString(resMNU_GLOBAL)
   mnuHelp.Caption = LoadResString(resMNU_HELP)
   mnuHelpContents.Caption = LoadResString(resMNU_CONTENTS)
   mnuHelpAbout.Caption = LoadResString(resMNU_ABOUT)
   
   '  Tab Captions
   sstJobFile.TabCaption(m_inxJOB) = LoadResString(resTAB_JOBS)
   sstJobFile.TabCaption(m_idxGLOBAL) = LoadResString(resTAB_GLOBAL)
   
   '  Clear help status line
   stbHelp.SimpleText = ""
  
   '   Command buttons captions
   cmdSaveGlobal.Caption = LoadResString(resCMD_SAVE)
   cmdSave.Caption = LoadResString(resCMD_SAVE)
   cmdNew.Caption = LoadResString(resCMD_NEW)
   cmdNewDataPoint.Caption = LoadResString(resCMD_NEW)
   cmdDelete.Caption = LoadResString(resCMD_DELETE)
   
   '  Fill in the labels
   labJobsName.Caption = LoadResString(resLABEL_JOB_NAME)
   labJobsPartNumber.Caption = LoadResString(resLABEL_COMCODE)
   labSerilNumberStart.Caption = LoadResString(resLABEL_STARTING_SN)
   labPlantCode.Caption = LoadResString(resLABEL_PLANT_CODE)
   labDBpath.Caption = LoadResString(resLABEL_COMCODE_DB_PATH)
   labTableName.Caption = LoadResString(resLABEL_COMCODE_TABEL)
   labTemplateName.Caption = LoadResString(resLABEL_TEMPLATE_NAME)
   labTemplatePath.Caption = LoadResString(resLABEL_TEMPLATE_PATH)
   labTempate.Caption = LoadResString(resLABEL_TEMPLATE)
   
   '  Label the data point grid
   dbgDataPoints.Caption = LoadResString(resLABEL_LOCATIONS)
   With dbgDataPoints
      .Columns.Item(m_gclX_AXIS).Caption = LoadResString(resLABEL_X_AXIS)
      .Columns.Item(m_gclY_AXIS).Caption = LoadResString(resLABEL_Y_AXIS)
      .Columns.Item(m_gclTHATA_AXIS).Caption = LoadResString(resLABEL_THATA)
   End With 'dbgJobs
   
   '  label the stuf on the global tab
   ckbUseGlobalPN.Caption = LoadResString(resLABEL_USE_GLOBAL_SN)
   labInitialSerialNumber.Caption = LoadResString(resLABEL_GLOBAL_SN)
   labDefalutePlantCode.Caption = LoadResString(resLABEL_DEFLAT_PLANT_CODE)
   labYearCode.Caption = LoadResString(resLABEL_LUCENT_YEAR)
   labWeekCode.Caption = LoadResString(resLABEL_LUCENT_WEEK)
   labInitialWeekCode.Caption = LoadResString(resLABEL_FIRST_WEEK)
   
   '  Job file status help
   labJobsName.Tag = LoadResString(resSTMSG_JOB_NAME)
   txbJobsName.Tag = LoadResString(resSTMSG_JOB_NAME)
   labJobsPartNumber.Tag = LoadResString(resSTMSG_COMCODE)
   txbJobsPartNumber.Tag = LoadResString(resSTMSG_COMCODE)
   labSerilNumberStart.Tag = LoadResString(resSTMSG_SERIAL)
   txbSerilNumberStart.Tag = LoadResString(resSTMSG_SERIAL)
   labPlantCode.Tag = LoadResString(resSTMSG_PLANT_CODE)
   txbPlantCode.Tag = LoadResString(resSTMSG_PLANT_CODE)
   labDBpath.Tag = LoadResString(resSTMSG_DB_PATH)
   txbDBpath.Tag = LoadResString(resSTMSG_DB_PATH)
   labTableName.Tag = LoadResString(resSTMSG_TABLE_NAME)
   txbTableName.Tag = LoadResString(resSTMSG_TABLE_NAME)
   labTemplateName.Tag = LoadResString(resSTMSG_LABEL_NAME)
   txbTemplateName.Tag = LoadResString(resSTMSG_LABEL_NAME)
   labTemplatePath.Tag = LoadResString(resSTMSG_LABEL_PATH)
   txbTemplatePath.Tag = LoadResString(resSTMSG_LABEL_PATH)
   labTempate.Tag = LoadResString(resSTMSG_LABEL_TEMPLATE)
   txbTempate.Tag = LoadResString(resSTMSG_LABEL_TEMPLATE)
   dbgDataPoints.Tag = LoadResString(resSTMSG_LABEL_DATA)
   cmdNewDataPoint.Tag = LoadResString(resSTMSG_NEW_DP)
   cmdSave.Tag = LoadResString(resSTMSG_SAVE_JOB)
   cmdDelete.Tag = LoadResString(resSTMSG_DELETE)
   cmdNew.Tag = LoadResString(resSTMSG_NEW_JOB)
   dbcJobFile.Tag = LoadResString(resSTMSG_DB_CONTROL)

   '  Galobal status help
   ckbUseGlobalPN.Tag = LoadResString(resSTMSG_USE_GLOBAL)
   labInitialSerialNumber.Tag = LoadResString(resSTMSG_INIT_SN)
   txbInitialSerialNumber.Tag = LoadResString(resSTMSG_INIT_SN)
   labDefalutePlantCode.Tag = LoadResString(resSTMSG_PLANT_DEFALT)
   txbDefalutePlantCode.Tag = LoadResString(resSTMSG_PLANT_DEFALT)
   labYearCode.Tag = LoadResString(resSTMSG_YEAR_CODE)
   txbYearCode.Tag = LoadResString(resSTMSG_YEAR_CODE)
   labWeekCode.Tag = LoadResString(resSTMSG_CURRENT_WEEK)
   txbWeekCode.Tag = LoadResString(resSTMSG_CURRENT_WEEK)
   labInitialWeekCode.Tag = LoadResString(resSTMSG_WEEK_CODE)
   txbInitialWeekCode.Tag = LoadResString(resSTMSG_WEEK_CODE)
   cmdSaveGlobal.Tag = LoadResString(resSTMSG_SAVE_GLOBAL)
      
   '  Now load the data controls
   strDBName = GetDBName()
   frmSplash.MousePointer = vbHourglass
   frmSplash.Refresh
   DoEvents
   
   If strDBName = "" Then
      strDBName = App.Path & "\" & "LucentTechSP.mdb"
   End If
   
   OpenDB strDBName
   
   
End Sub 'Form_Load

Private Sub ckbUseGlobalPN_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = ckbUseGlobalPN.Tag
End Sub 'ckbUseGlobalPN_MouseMove


Private Sub Form_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = frmJobFileAdmin.Tag
End Sub 'Form_MouseMove

Private Sub labInitialSerialNumber_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = labInitialSerialNumber.Tag
End Sub 'labInitialSerialNumber_MouseMove


Private Sub SSPanel1_Click()

End Sub

Private Sub mnuHelpContents_Click()

   With cdlHelp
      .HelpFile = App.HelpFile
      .HelpCommand = cdlHelpContents
      .ShowHelp
   End With 'cdlHelp
   
End Sub 'mnuHelpContents_Click

Private Sub sspDataPoints_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = dbgDataPoints.Tag
End Sub 'sspDataPoints_MouseMove

Private Sub sstJobFile_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = sstJobFile.Tag
End Sub 'sstJobFile_MouseMove


Private Sub txbInitialSerialNumber_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = txbInitialSerialNumber.Tag
End Sub 'txbInitialSerialNumber_MouseMove


Private Sub labDefalutePlantCode_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = labDefalutePlantCode.Tag
End Sub 'labDefalutePlantCode_MouseMove


Private Sub txbDefalutePlantCode_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = txbDefalutePlantCode.Tag
End Sub 'txbDefalutePlantCode_MouseMove


Private Sub labYearCode_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = labYearCode.Tag
End Sub 'labYearCode_MouseMove


Private Sub txbJobsName_Change()

   dbcJobFile.Caption = LoadResString(resLABEL_DATA_CONTROL) & txbJobsName.Text
   cmdSave.Enabled = True
   
End Sub 'txbJobsName_Change

Private Sub txbYearCode_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = txbYearCode.Tag
End Sub 'txbYearCode_MouseMove


Private Sub labWeekCode_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = labWeekCode.Tag
End Sub 'labWeekCode_MouseMove


Private Sub txbWeekCode_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = txbWeekCode.Tag
End Sub 'txbWeekCode_MouseMove


Private Sub labInitialWeekCode_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = labInitialWeekCode.Tag
End Sub 'labInitialWeekCode_MouseMove


Private Sub txbInitialWeekCode_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = txbInitialWeekCode.Tag
End Sub 'txbInitialWeekCode_MouseMove


Private Sub cmdSaveGlobal_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = cmdSaveGlobal.Tag
End Sub 'cmdSaveGlobal_MouseMove



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
   
   If cmdSaveGlobal.Enabled Then
      intResponce = MsgBox(LoadResString(resMSG_GLOBAL_SAVE), vbQuestion + vbYesNoCancel, LoadResString(resMSG_TITEL))
      If intResponce = vbCancel Then
         Cancel = 1 'cancel the cancel
         Exit Sub
      ElseIf intResponce = vbYes Then
         cmdSaveGlobal_Click
      End If
   End If
   
End Sub 'Form_QueryUnload


Private Sub labJobsName_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = labJobsName.Tag
End Sub 'labJobsName_MouseMove


Private Sub txbJobsName_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = txbJobsName.Tag
End Sub 'txbJobsName_MouseMove


Private Sub labJobsPartNumber_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = labJobsPartNumber.Tag
End Sub 'labJobsPartNumber_MouseMove


Private Sub txbJobsPartNumber_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = txbJobsPartNumber.Tag
End Sub 'txbJobsPartNumber_MouseMove


Private Sub labSerilNumberStart_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = labSerilNumberStart.Tag
End Sub 'labSerilNumberStart_MouseMove


Private Sub txbSerilNumberStart_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = txbSerilNumberStart.Tag
End Sub 'txbSerilNumberStart_MouseMove


Private Sub labPlantCode_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = labPlantCode.Tag
End Sub 'labPlantCode_MouseMove


Private Sub txbPlantCode_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = txbPlantCode.Tag
End Sub 'txbPlantCode_MouseMove


Private Sub labDBpath_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = labDBpath.Tag
End Sub 'labDBpath_MouseMove


Private Sub txbDBpath_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = txbDBpath.Tag
End Sub 'txbDBpath_MouseMove


Private Sub labTableName_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = labTableName.Tag
End Sub 'labTableName_MouseMove


Private Sub txbTableName_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = txbTableName.Tag
End Sub 'txbTableName_MouseMove


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


Private Sub labTempate_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = labTempate.Tag
End Sub 'labTempate_MouseMove


Private Sub txbTempate_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = txbTempate.Tag
End Sub 'txbTempate_MouseMove


Private Sub dbgDataPoints_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = dbgDataPoints.Tag
End Sub 'dbgDataPoints_MouseMove


Private Sub cmdNewDataPoint_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   stbHelp.SimpleText = cmdNewDataPoint.Tag
End Sub 'cmdNewDataPoint_MouseMove


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
   dbcConfiguration.Refresh
   
End Sub 'mnuFileOpen_Click

Private Sub mnuHelpAbout_Click()

   frmAbout.Show vbModal
   
End Sub  'mnuHelpAbout_Click

Private Sub mnuViewGlobal_Click()

'   sstJobFile.Tabs(m_idxGLOBAL) = True

End Sub 'mnuViewGlobal_Click

Private Sub mnuViewJobs_Click()

 '  sstJobFile.Tabs(m_inxJOB) = True
   
End Sub 'mnuViewJobs_Click


Private Sub txbDBpath_Change()

   cmdSave.Enabled = True
   
End Sub 'txbDBpath_Change

Private Sub txbDefalutePlantCode_Change()

   cmdSaveGlobal.Enabled = True

End Sub 'txbDefalutePlantCode_Change

Private Sub txbInitialSerialNumber_Change()

   cmdSaveGlobal.Enabled = True

End Sub 'txbInitialSerialNumber_Change

Private Sub txbInitialSerialNumber_KeyPress(KeyAscii As Integer)

   If Not (Chr(KeyAscii) Like "[0-9]") And Not (Chr(KeyAscii) = vbBack) Then
      KeyAscii = 0
   End If

End Sub 'txbInitialSerialNumber_KeyPress



Private Sub txbInitialWeekCode_Change()

   cmdSaveGlobal.Enabled = True

End Sub 'txbInitialWeekCode_Change

Private Sub txbInitialWeekCode_KeyPress(KeyAscii As Integer)

   If Not (Chr(KeyAscii) Like "[0-9]") And Not (Chr(KeyAscii) = vbBack) Then
      KeyAscii = 0
   End If

End Sub 'txbInitialWeekCode_KeyPress


Private Sub txbJobID_Change()

   m_qurDataPoints.Parameters("JobID") = CLng(txbJobID.Text)
   Set m_rcsDataPoints = m_qurDataPoints.OpenRecordset()
   Set dbcDataPointInfo.Recordset = m_rcsDataPoints
   
End Sub 'txbJobID_Change



Private Function GetDBName() As String

   cdlOpenDB.DialogTitle = LoadResString(resFORM_OPEN_JOB_FILE)
   cdlOpenDB.Filter = LoadResString(resJOB_FILE_FILTER)
   cdlOpenDB.filename = "lucenttechSP.mdb"
   On Error Resume Next 'no error handling because test form
   cdlOpenDB.ShowOpen
   
   GetDBName = cdlOpenDB.filename
   m_strJobFileName = cdlOpenDB.FileTitle
   
   On Error GoTo 0

End Function 'GetDBName



Private Sub txbJobsPartNumber_Change()

   cmdSave.Enabled = True
   
End Sub 'txbJobsPartNumber_Change


Private Sub txbPlantCode_Change()

   cmdSave.Enabled = True
   
End Sub 'txbPlantCode_Change

Private Sub txbSerilNumberStart_Change()

   cmdSave.Enabled = True
   
End Sub 'txbSerilNumberStart_Change

Private Sub txbSerilNumberStart_KeyPress(KeyAscii As Integer)

   If Not (Chr(KeyAscii) Like "[0-9]") And Not (Chr(KeyAscii) = vbBack) Then
      KeyAscii = 0
   End If

End Sub 'txbSerilNumberStart_KeyPress



Private Sub txbTableName_Change()

   cmdSave.Enabled = True
   
End Sub 'txbTableName_Change

Private Sub txbTempate_Change()

   cmdSave.Enabled = True
   
End Sub 'txbTempate_Change

Private Sub txbTemplateName_Change()

   cmdSave.Enabled = True
   
End Sub 'txbTemplateName_Change


Private Sub txbTemplatePath_Change()

   cmdSave.Enabled = True
   
End Sub 'txbTemplatePath_Change


Private Sub txbWeekCode_Change()

   cmdSaveGlobal.Enabled = True

End Sub 'txbWeekCode_Change

Private Sub txbWeekCode_KeyPress(KeyAscii As Integer)

   If Not (Chr(KeyAscii) Like "[0-9]") And Not (Chr(KeyAscii) = vbBack) Then
      KeyAscii = 0
   End If

End Sub 'txbWeekCode_KeyPress


Private Sub txbYearCode_Change()

   cmdSaveGlobal.Enabled = True

End Sub 'txbYearCode_Change

Private Sub txbYearCode_KeyPress(KeyAscii As Integer)

   If Not (Chr(KeyAscii) Like "[0-9]") And Not (Chr(KeyAscii) = vbBack) Then
      KeyAscii = 0
   End If

End Sub 'txbYearCode_KeyPress



Private Sub OpenDB(strDBName As String)

   #If ccShip_Ver Then
      On Error GoTo OpenDB_Error
   #Else
      On Error GoTo 0
   #End If

   If strDBName <> "" Then
      dbcConfiguration.DatabaseName = strDBName
      dbcJobFile.DatabaseName = strDBName

      Set m_dbJobFile = Workspaces(0).OpenDatabase(strDBName)
      Set m_qurDataPoints = m_dbJobFile.QueryDefs(m_strDATA_POINT_INFO)
   End If
   
   Me.Caption = LoadResString(resFORM_MAIN_CAPTION) & m_strJobFileName
   
   Me.Refresh
   DoEvents
   
   Exit Sub

OpenDB_Error:

   ProccessError "OpenDB", m_strName, Err.Number, Err.Description

End Sub 'OpenDB

Public Sub AddDataPoint(strXAxis As String, strYaxis As String, strThata As String)

   #If ccShip_Ver Then
      On Error GoTo AddDataPoint_Error
   #Else
      On Error GoTo 0
   #End If

   '  Add a new record to the table
   m_rcsDataPoints.AddNew
   
   '  Add the key from the job file tabel
   m_rcsDataPoints![JobsID] = txbJobID.Text
   
   '  Add the data points
   m_rcsDataPoints![XApplyPt] = CLng(strXAxis)
   m_rcsDataPoints![YApplyPt] = CLng(strYaxis)
   m_rcsDataPoints![ThataApply] = strThata
   
   '  now save the reocrd
   m_rcsDataPoints.Update

   '  now update the grid by forcing the
   '  change event of the jobID text box
   txbJobID_Change

   Exit Sub

AddDataPoint_Error:

   ProccessError "AddDataPoint", m_strName, Err.Number, Err.Description

End Sub 'AddDataPoint
