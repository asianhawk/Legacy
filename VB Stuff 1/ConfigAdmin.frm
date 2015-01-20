VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Object = "{00028C01-0000-0000-0000-000000000046}#1.0#0"; "DBGRID32.OCX"
Begin VB.Form frmMain 
   Caption         =   "Configuration Administration"
   ClientHeight    =   4890
   ClientLeft      =   1020
   ClientTop       =   1110
   ClientWidth     =   7470
   Icon            =   "ConfigAdmin.frx":0000
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   4890
   ScaleWidth      =   7470
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   375
      Left            =   5640
      TabIndex        =   24
      Top             =   4440
      Width           =   1815
   End
   Begin TabDlg.SSTab sstConfiguration 
      Height          =   4395
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   7455
      _ExtentX        =   13150
      _ExtentY        =   7752
      _Version        =   327681
      Tabs            =   2
      Tab             =   1
      TabHeight       =   529
      TabCaption(0)   =   "Configuration"
      TabPicture(0)   =   "ConfigAdmin.frx":0442
      Tab(0).ControlEnabled=   0   'False
      Tab(0).Control(0)=   "txtbOffSet"
      Tab(0).Control(1)=   "txbBoardCountCodeLine"
      Tab(0).Control(2)=   "txbScannerOffsetLine"
      Tab(0).Control(3)=   "txbPointDataTableOffset"
      Tab(0).Control(4)=   "cmdSaveConfig"
      Tab(0).Control(5)=   "dbcConfiguration"
      Tab(0).Control(6)=   "famYAxies"
      Tab(0).Control(7)=   "famXAxies"
      Tab(0).Control(8)=   "Label5"
      Tab(0).Control(9)=   "Label4"
      Tab(0).Control(10)=   "Label3"
      Tab(0).Control(11)=   "Label2"
      Tab(0).ControlCount=   12
      TabCaption(1)   =   "Data points"
      TabPicture(1)   =   "ConfigAdmin.frx":045E
      Tab(1).ControlEnabled=   -1  'True
      Tab(1).Control(0)=   "dbgMachineDataPt"
      Tab(1).Control(0).Enabled=   0   'False
      Tab(1).Control(1)=   "dbcMachineDataPt"
      Tab(1).Control(1).Enabled=   0   'False
      Tab(1).Control(2)=   "cmdSaveDP"
      Tab(1).Control(2).Enabled=   0   'False
      Tab(1).ControlCount=   3
      Begin VB.TextBox txtbOffSet 
         DataField       =   "NosePieceOffset"
         DataSource      =   "dbcConfiguration"
         Height          =   285
         Left            =   -70440
         TabIndex        =   30
         Text            =   "OffSet"
         Top             =   3360
         Width           =   615
      End
      Begin VB.TextBox txbBoardCountCodeLine 
         DataField       =   "BoardCountCodeLine"
         DataSource      =   "dbcConfiguration"
         Height          =   285
         Left            =   -70440
         TabIndex        =   27
         Text            =   "BoardCountCodeLine"
         Top             =   3045
         Width           =   645
      End
      Begin VB.TextBox txbScannerOffsetLine 
         DataField       =   "ScannerOffsetLine"
         DataSource      =   "dbcConfiguration"
         Height          =   285
         Left            =   -70440
         TabIndex        =   25
         Text            =   "ScannerOffsetLine"
         Top             =   2685
         Width           =   615
      End
      Begin VB.CommandButton cmdSaveDP 
         Caption         =   "&Save"
         Height          =   375
         Left            =   5865
         TabIndex        =   23
         Top             =   3510
         Width           =   1455
      End
      Begin VB.Data dbcMachineDataPt 
         Caption         =   "Michine Data Points"
         Connect         =   "Access"
         DatabaseName    =   "C:\lucent\Labeler.mdb"
         DefaultCursorType=   0  'DefaultCursor
         DefaultType     =   2  'UseODBC
         Exclusive       =   0   'False
         Height          =   375
         Left            =   240
         Options         =   0
         ReadOnly        =   0   'False
         RecordsetType   =   0  'Table
         RecordSource    =   "tblMachineDataPoints"
         Top             =   3450
         Width           =   5445
      End
      Begin VB.TextBox txbPointDataTableOffset 
         DataField       =   "PointDataTableOffset"
         DataSource      =   "dbcConfiguration"
         Height          =   285
         Left            =   -70440
         TabIndex        =   21
         Text            =   "PointDataTableOffset"
         Top             =   2280
         Width           =   600
      End
      Begin VB.CommandButton cmdSaveConfig 
         Caption         =   "&Save"
         Height          =   375
         Left            =   -69120
         TabIndex        =   19
         Top             =   3840
         Width           =   1455
      End
      Begin VB.Data dbcConfiguration 
         Caption         =   "Configuration"
         Connect         =   "Access"
         DatabaseName    =   "C:\Lucent\Labeler.mdb"
         DefaultCursorType=   0  'DefaultCursor
         DefaultType     =   2  'UseODBC
         Exclusive       =   0   'False
         Height          =   375
         Left            =   -74760
         Options         =   0
         ReadOnly        =   0   'False
         RecordsetType   =   1  'Dynaset
         RecordSource    =   "tblConfiguration"
         Top             =   3840
         Visible         =   0   'False
         Width           =   5775
      End
      Begin VB.Frame famYAxies 
         Caption         =   "Y Axies"
         Height          =   1575
         Left            =   -71160
         TabIndex        =   5
         Top             =   600
         Width           =   3375
         Begin VB.TextBox txbConfiguration 
            DataField       =   "YScanner90Offset"
            DataSource      =   "dbcConfiguration"
            Height          =   285
            Index           =   7
            Left            =   1440
            MaxLength       =   6
            TabIndex        =   18
            Text            =   "YScanner90Offset"
            Top             =   1080
            Width           =   1095
         End
         Begin VB.TextBox txbConfiguration 
            DataField       =   "YScanner0Offset"
            DataSource      =   "dbcConfiguration"
            Height          =   285
            Index           =   6
            Left            =   1440
            MaxLength       =   6
            TabIndex        =   17
            Text            =   "YScanner0Offset"
            Top             =   720
            Width           =   1095
         End
         Begin VB.TextBox txbConfigOpand 
            DataField       =   "YOperator"
            DataSource      =   "dbcConfiguration"
            Height          =   285
            Index           =   1
            Left            =   2760
            MaxLength       =   2
            TabIndex        =   15
            Text            =   "YOperator"
            Top             =   360
            Width           =   270
         End
         Begin VB.TextBox txbConfiguration 
            DataField       =   "YPanelOffset"
            DataSource      =   "dbcConfiguration"
            Height          =   285
            Index           =   4
            Left            =   1320
            MaxLength       =   6
            TabIndex        =   14
            Text            =   "YPanelOffset"
            Top             =   360
            Width           =   1095
         End
         Begin VB.Label Label1 
            AutoSize        =   -1  'True
            Caption         =   "x"
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
            Index           =   1
            Left            =   2520
            TabIndex        =   16
            Top             =   240
            Width           =   195
         End
         Begin VB.Label Scanner90 
            Alignment       =   1  'Right Justify
            Caption         =   "Scanner 90 dgg"
            Height          =   255
            Left            =   120
            TabIndex        =   8
            Top             =   1080
            Width           =   1215
         End
         Begin VB.Label labScanner0 
            Alignment       =   1  'Right Justify
            Caption         =   "Scanner 0 deg"
            Height          =   255
            Left            =   120
            TabIndex        =   7
            Top             =   720
            Width           =   1215
         End
         Begin VB.Label labYPanelOffset 
            Alignment       =   1  'Right Justify
            Caption         =   "Panel Offset"
            Height          =   255
            Left            =   120
            TabIndex        =   6
            Top             =   360
            Width           =   975
         End
      End
      Begin VB.Frame famXAxies 
         Caption         =   "X Axies"
         Height          =   1575
         Left            =   -74760
         TabIndex        =   1
         Top             =   600
         Width           =   3375
         Begin VB.TextBox txbConfiguration 
            DataField       =   "XScanner90Offset"
            DataSource      =   "dbcConfiguration"
            Height          =   285
            Index           =   3
            Left            =   1440
            MaxLength       =   6
            TabIndex        =   13
            Text            =   "XScanner90Offset"
            Top             =   1080
            Width           =   1095
         End
         Begin VB.TextBox txbConfiguration 
            DataField       =   "XScanner0Offset"
            DataSource      =   "dbcConfiguration"
            Height          =   285
            Index           =   2
            Left            =   1440
            MaxLength       =   6
            TabIndex        =   12
            Text            =   "XScanner0Offset"
            Top             =   720
            Width           =   1095
         End
         Begin VB.TextBox txbConfigOpand 
            DataField       =   "XOperator"
            DataSource      =   "dbcConfiguration"
            Height          =   285
            Index           =   0
            Left            =   2760
            MaxLength       =   2
            TabIndex        =   10
            Text            =   "XOperator"
            Top             =   360
            Width           =   270
         End
         Begin VB.TextBox txbConfiguration 
            DataField       =   "XPanelOffset"
            DataSource      =   "dbcConfiguration"
            Height          =   285
            Index           =   0
            Left            =   1320
            MaxLength       =   6
            TabIndex        =   9
            Text            =   "XPanelOffset"
            Top             =   360
            Width           =   1095
         End
         Begin VB.Label Label1 
            AutoSize        =   -1  'True
            Caption         =   "x"
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
            Index           =   0
            Left            =   2520
            TabIndex        =   11
            Top             =   240
            Width           =   195
         End
         Begin VB.Label labXPanelOffset 
            Alignment       =   1  'Right Justify
            Caption         =   "Panel Offset"
            Height          =   255
            Left            =   120
            TabIndex        =   4
            Top             =   360
            Width           =   975
         End
         Begin VB.Label labScanneer0 
            Alignment       =   1  'Right Justify
            Caption         =   "Scanner 0 deg"
            Height          =   255
            Left            =   120
            TabIndex        =   3
            Top             =   720
            Width           =   1215
         End
         Begin VB.Label labScanner90 
            Alignment       =   1  'Right Justify
            Caption         =   "Scanner 90 dgg"
            Height          =   255
            Left            =   120
            TabIndex        =   2
            Top             =   1080
            Width           =   1215
         End
      End
      Begin MSDBGrid.DBGrid dbgMachineDataPt 
         Bindings        =   "ConfigAdmin.frx":047A
         Height          =   2715
         Left            =   240
         OleObjectBlob   =   "ConfigAdmin.frx":0495
         TabIndex        =   22
         Top             =   720
         Width           =   6015
      End
      Begin VB.Label Label5 
         Alignment       =   1  'Right Justify
         Caption         =   "Nosepiece Offset(mm):"
         Height          =   255
         Left            =   -72120
         TabIndex        =   29
         Top             =   3360
         Width           =   1620
      End
      Begin VB.Label Label4 
         Alignment       =   1  'Right Justify
         Caption         =   "Line number in IAI code for the number of labels per board:"
         Height          =   255
         Left            =   -74640
         TabIndex        =   28
         Top             =   3075
         Width           =   4140
      End
      Begin VB.Label Label3 
         Alignment       =   1  'Right Justify
         Caption         =   "Line number in IAI code where the scanner offsets start:"
         Height          =   255
         Left            =   -74400
         TabIndex        =   26
         Top             =   2700
         Width           =   3960
      End
      Begin VB.Label Label2 
         Alignment       =   1  'Right Justify
         Caption         =   "Start of label data point in IAI data point table:"
         Height          =   255
         Left            =   -73680
         TabIndex        =   20
         Top             =   2280
         Width           =   3225
      End
   End
End
Attribute VB_Name = "frmMain"
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
'*      Configuration Administration
'*
'*
'*    Customer: Lucent Technologies
'*              Shreveport, LA
'*
'*
'*    Date of origin: 12/29/96
'*    Original author: Michael D. Reed
'*
'* Form purpose:
'*    This form is for maintaning the configuration of the 3-Axis
'     Configuration Database.
'*
'******************************************************************
'******************************************************************
Option Explicit

Private m_objIAICtrl As clsMotionControl

Private Sub cmdExit_Click()

   End
   
End Sub 'cmdExit_Click


Private Sub cmdSaveConfig_Click()

   dbcConfiguration.UpdateRecord
   
End Sub 'cmdSaveConfig_Click



Private Sub cmdSaveDP_Click()

   dbcMachineDataPt.UpdateRecord
   
   SaveMachineDataPoints
   
End Sub 'cmdSaveDP_Click

Private Sub dbgMachineDataPt_RowColChange(LastRow As Variant, ByVal LastCol As Integer)

   dbcMachineDataPt.Caption = dbgMachineDataPt.Columns(0).Text
   
End Sub 'dbgMachineDataPt_RowColChange


Private Sub Form_Load()

   frmMessage.Hide
   
   g_blnTest = False
   
   CenterForm Me
   
 ' Take out the stuff on the data points for now
   Set m_objIAICtrl = New clsMotionControl
   sstConfiguration.TabEnabled(1) = True
   
   dbcConfiguration.DatabaseName = App.Path & "\Labeler.mdb"
   dbcMachineDataPt.DatabaseName = App.Path & "\Labeler.mdb"
   
End Sub 'Form_Load


Private Sub txbConfigOpand_KeyPress(Index As Integer, KeyAscii As Integer)

   If Not (Chr(KeyAscii) Like "[1-]") And Not (Chr(KeyAscii) = vbBack) Then
      KeyAscii = 0
   End If
      
End Sub 'txbConfigOpand_KeyPress


Private Sub txbConfiguration_KeyPress(Index As Integer, KeyAscii As Integer)

   If Not (Chr(KeyAscii) Like "[0-9]") And Not (Chr(KeyAscii) = vbBack) Then
      KeyAscii = 0
   End If
   
End Sub 'txbConfiguration_KeyPress



Private Sub SaveMachineDataPoints()
   
   Const intColPointIndex = 1
   Const intColXAxis = 2
   Const intColYaxise = 3
   Const intIdxPointIndex = 0
   Const intIdxXAxis = 1
   Const intIdxYaxise = 2
   
   Dim vntDataPoints(0 To 2) As Variant
      
   MessageDisplay "Writing data points to IAI"
   
   '  make shure that we are at the first row
   dbcMachineDataPt.Recordset.MoveFirst
   Do Until dbcMachineDataPt.Recordset.EOF
      '  now get the points and send them to the iai
      vntDataPoints(intIdxPointIndex) = CInt(dbgMachineDataPt.Columns(intColPointIndex).Text)
      vntDataPoints(intIdxXAxis) = CLng(dbgMachineDataPt.Columns(intColXAxis).Text)
      vntDataPoints(intIdxYaxise) = CLng(dbgMachineDataPt.Columns(intColYaxise).Text)
      m_objIAICtrl.WriteDataPoint vntPointValue:=vntDataPoints
      dbcMachineDataPt.Recordset.MoveNext
   Loop
   
   '  now wright the mess to the card
   MessageDisplay "Writing IAI data to memory card" 'LoadResString(resWRITING_CARD)
   m_objIAICtrl.WriteCardAll
   MessageRemove
   
End Sub 'SaveMachineDataPoints

