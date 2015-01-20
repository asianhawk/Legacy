VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Object = "{00028C01-0000-0000-0000-000000000046}#1.0#0"; "DBGRID32.OCX"
Begin VB.Form frmMain 
   Caption         =   "Configuration Administration"
   ClientHeight    =   6120
   ClientLeft      =   2100
   ClientTop       =   1140
   ClientWidth     =   7470
   Icon            =   "ConfigAdmin.frx":0000
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   6120
   ScaleWidth      =   7470
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   375
      Left            =   5640
      TabIndex        =   10
      Top             =   4920
      Width           =   1815
   End
   Begin TabDlg.SSTab sstConfiguration 
      Height          =   4875
      Left            =   120
      TabIndex        =   0
      Top             =   0
      Width           =   7455
      _ExtentX        =   13150
      _ExtentY        =   8599
      _Version        =   393216
      TabHeight       =   529
      TabCaption(0)   =   "Configuration"
      TabPicture(0)   =   "ConfigAdmin.frx":0442
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "famXAxies"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).Control(1)=   "famYAxies"
      Tab(0).Control(1).Enabled=   0   'False
      Tab(0).Control(2)=   "cmdSaveConfig"
      Tab(0).Control(2).Enabled=   0   'False
      Tab(0).Control(3)=   "Frame3"
      Tab(0).Control(3).Enabled=   0   'False
      Tab(0).Control(4)=   "Frame4"
      Tab(0).Control(4).Enabled=   0   'False
      Tab(0).Control(5)=   "cmdEditConfig"
      Tab(0).Control(5).Enabled=   0   'False
      Tab(0).ControlCount=   6
      TabCaption(1)   =   "Data points"
      TabPicture(1)   =   "ConfigAdmin.frx":045E
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "dbgMachineDataPt"
      Tab(1).Control(1)=   "dbcMachineDataPt"
      Tab(1).Control(2)=   "cmdSaveDP"
      Tab(1).ControlCount=   3
      TabCaption(2)   =   "Scanner Offsets"
      TabPicture(2)   =   "ConfigAdmin.frx":047A
      Tab(2).ControlEnabled=   0   'False
      Tab(2).Control(0)=   "Frame1"
      Tab(2).Control(1)=   "Frame2"
      Tab(2).Control(2)=   "cmdSaveScannerOffsets"
      Tab(2).Control(3)=   "cmdEditScannerOffsets"
      Tab(2).Control(4)=   "cmdTestScannerOffset"
      Tab(2).ControlCount=   5
      Begin VB.CommandButton cmdTestScannerOffset 
         Caption         =   "Test"
         Height          =   375
         Left            =   -69360
         TabIndex        =   40
         Top             =   3420
         Width           =   1455
      End
      Begin VB.CommandButton cmdEditConfig 
         Caption         =   "Edit"
         Height          =   375
         Left            =   4320
         TabIndex        =   39
         Top             =   4020
         Width           =   1335
      End
      Begin VB.Frame Frame4 
         Caption         =   "Nosepiece Info"
         Height          =   855
         Left            =   240
         TabIndex        =   36
         Top             =   3540
         Width           =   3615
         Begin VB.TextBox txbIAINosePieceOffset 
            DataField       =   " "
            DataSource      =   " "
            Height          =   285
            Left            =   1920
            TabIndex        =   38
            Text            =   "Text1"
            Top             =   360
            Width           =   1215
         End
         Begin VB.Label Label5 
            Alignment       =   1  'Right Justify
            Caption         =   "Nosepiece Offset(mm):"
            Height          =   255
            Left            =   240
            TabIndex        =   37
            Top             =   360
            Width           =   1620
         End
      End
      Begin VB.Frame Frame3 
         Caption         =   "IAI Constants"
         Height          =   2175
         Left            =   210
         TabIndex        =   27
         Top             =   1320
         Width           =   6945
         Begin VB.TextBox txbIAILabelsPerBoard 
            DataField       =   " "
            DataSource      =   " "
            Height          =   285
            Left            =   4440
            TabIndex        =   35
            Text            =   "Text1"
            Top             =   1320
            Width           =   1215
         End
         Begin VB.TextBox txbIAIScannerCodeOffset 
            DataField       =   " "
            DataSource      =   " "
            Height          =   285
            Left            =   4440
            TabIndex        =   34
            Text            =   "Text1"
            Top             =   960
            Width           =   1215
         End
         Begin VB.TextBox txbIAIStartDataPoint 
            DataField       =   " "
            DataSource      =   " "
            Height          =   285
            Left            =   4440
            TabIndex        =   33
            Text            =   "Text1"
            Top             =   600
            Width           =   1215
         End
         Begin VB.TextBox txbIAIProgramNumber 
            DataField       =   " "
            DataSource      =   " "
            Height          =   285
            Left            =   4440
            TabIndex        =   32
            Text            =   "Text1"
            Top             =   240
            Width           =   1215
         End
         Begin VB.Label Label4 
            Alignment       =   1  'Right Justify
            Caption         =   "Line number in IAI code for the number of labels per board:"
            Height          =   255
            Left            =   120
            TabIndex        =   31
            Top             =   1320
            Width           =   4140
         End
         Begin VB.Label Label3 
            Alignment       =   1  'Right Justify
            Caption         =   "Line number in IAI code where the scanner offsets start:"
            Height          =   255
            Left            =   270
            TabIndex        =   30
            Top             =   930
            Width           =   3960
         End
         Begin VB.Label Label2 
            Alignment       =   1  'Right Justify
            Caption         =   "Start of label data point in IAI data point table:"
            Height          =   255
            Left            =   1080
            TabIndex        =   29
            Top             =   600
            Width           =   3225
         End
         Begin VB.Label Label6 
            Alignment       =   1  'Right Justify
            Caption         =   "IAI Program Number:"
            Height          =   255
            Left            =   2520
            TabIndex        =   28
            Top             =   240
            Width           =   1695
         End
      End
      Begin VB.CommandButton cmdEditScannerOffsets 
         Caption         =   "Edit"
         Height          =   375
         Left            =   -69360
         TabIndex        =   22
         Top             =   2940
         Width           =   1455
      End
      Begin VB.CommandButton cmdSaveScannerOffsets 
         Caption         =   "&Save"
         Height          =   375
         Left            =   -69360
         TabIndex        =   17
         Top             =   3900
         Width           =   1455
      End
      Begin VB.Frame Frame2 
         Caption         =   "Y-Axis"
         Height          =   1575
         Left            =   -74760
         TabIndex        =   14
         Top             =   2340
         Width           =   4095
         Begin VB.TextBox txbY_90Offset 
            Height          =   375
            Left            =   2520
            TabIndex        =   21
            Text            =   "Text2"
            Top             =   960
            Width           =   1455
         End
         Begin VB.TextBox txbY_0Offset 
            Height          =   375
            Left            =   2520
            TabIndex        =   20
            Text            =   "Text2"
            Top             =   360
            Width           =   1455
         End
         Begin VB.Label Scanner90 
            Alignment       =   1  'Right Justify
            Caption         =   "Scanner 90 deg"
            Height          =   255
            Left            =   1200
            TabIndex        =   16
            Top             =   1080
            Width           =   1215
         End
         Begin VB.Label labScanner0 
            Alignment       =   1  'Right Justify
            Caption         =   "Scanner 0 deg"
            Height          =   255
            Left            =   1200
            TabIndex        =   15
            Top             =   480
            Width           =   1215
         End
      End
      Begin VB.Frame Frame1 
         Caption         =   "X-Axis"
         Height          =   1575
         Left            =   -74760
         TabIndex        =   11
         Top             =   420
         Width           =   4095
         Begin VB.TextBox txbX_90Offset 
            Height          =   375
            Left            =   2520
            TabIndex        =   19
            Text            =   "Text2"
            Top             =   960
            Width           =   1455
         End
         Begin VB.TextBox txbX_0Offset 
            Height          =   405
            Left            =   2520
            TabIndex        =   18
            Text            =   "Text1"
            Top             =   240
            Width           =   1455
         End
         Begin VB.Label labScanner90 
            Alignment       =   1  'Right Justify
            Caption         =   "Scanner 90 deg"
            Height          =   255
            Left            =   1200
            TabIndex        =   13
            Top             =   960
            Width           =   1215
         End
         Begin VB.Label labScanneer0 
            Alignment       =   1  'Right Justify
            Caption         =   "Scanner 0 deg"
            Height          =   255
            Left            =   1200
            TabIndex        =   12
            Top             =   360
            Width           =   1215
         End
      End
      Begin VB.CommandButton cmdSaveDP 
         Caption         =   "&Save"
         Height          =   375
         Left            =   -69135
         TabIndex        =   9
         Top             =   3180
         Width           =   1455
      End
      Begin VB.Data dbcMachineDataPt 
         Caption         =   "Michine Data Points"
         Connect         =   "Access"
         DatabaseName    =   "C:\labeler\Labeler.mdb"
         DefaultCursorType=   0  'DefaultCursor
         DefaultType     =   2  'UseODBC
         Exclusive       =   0   'False
         Height          =   375
         Left            =   -74760
         Options         =   0
         ReadOnly        =   0   'False
         RecordsetType   =   0  'Table
         RecordSource    =   "tblMachineDataPoints"
         Top             =   3150
         Width           =   5445
      End
      Begin VB.CommandButton cmdSaveConfig 
         Caption         =   "&Save"
         Height          =   375
         Left            =   5760
         TabIndex        =   7
         Top             =   4020
         Width           =   1455
      End
      Begin VB.Frame famYAxies 
         Caption         =   "Y Axis"
         Height          =   855
         Left            =   3810
         TabIndex        =   3
         Top             =   450
         Width           =   3375
         Begin VB.TextBox txbYOperator 
            Alignment       =   1  'Right Justify
            Height          =   285
            Left            =   2760
            TabIndex        =   26
            Text            =   "Text2"
            Top             =   360
            Width           =   495
         End
         Begin VB.TextBox txbYPanelOffset 
            Height          =   285
            Left            =   1200
            TabIndex        =   24
            Text            =   "Text2"
            Top             =   360
            Width           =   1215
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
            TabIndex        =   6
            Top             =   240
            Width           =   195
         End
         Begin VB.Label labYPanelOffset 
            Alignment       =   1  'Right Justify
            Caption         =   "Panel Offset"
            Height          =   255
            Left            =   120
            TabIndex        =   4
            Top             =   360
            Width           =   975
         End
      End
      Begin VB.Frame famXAxies 
         Caption         =   "X Axis"
         Height          =   855
         Left            =   210
         TabIndex        =   1
         Top             =   390
         Width           =   3375
         Begin VB.TextBox txbXOperator 
            Alignment       =   1  'Right Justify
            Height          =   285
            Left            =   2760
            TabIndex        =   25
            Text            =   "Text1"
            Top             =   360
            Width           =   495
         End
         Begin VB.TextBox txbXPanelOffset 
            Height          =   285
            Left            =   1200
            TabIndex        =   23
            Text            =   "Text1"
            Top             =   360
            Width           =   1215
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
            TabIndex        =   5
            Top             =   240
            Width           =   195
         End
         Begin VB.Label labXPanelOffset 
            Alignment       =   1  'Right Justify
            Caption         =   "Panel Offset"
            Height          =   255
            Left            =   120
            TabIndex        =   2
            Top             =   360
            Width           =   975
         End
      End
      Begin MSDBGrid.DBGrid dbgMachineDataPt 
         Bindings        =   "ConfigAdmin.frx":0496
         Height          =   2715
         Left            =   -74760
         OleObjectBlob   =   "ConfigAdmin.frx":04B5
         TabIndex        =   8
         Top             =   420
         Width           =   6015
      End
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuFilePreferences 
         Caption         =   "&Preferences"
         Shortcut        =   {F3}
      End
      Begin VB.Menu mnuFileExit 
         Caption         =   "E&xit"
         Shortcut        =   {F4}
      End
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "&Edit"
      Begin VB.Menu mnuEditTestLabelPosition 
         Caption         =   "Edit Test Label Position"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&Help"
      Begin VB.Menu mnuHelpAbout 
         Caption         =   "About"
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

Public m_dbConfiguration As Database
Public m_rsConfiguration As Recordset
Public m_strDatabaseName As String

Public m_objIAICtrl As clsMotionControl

Private Sub cmdEditConfig_Click()
  Enabled_EditConfig True

  cmdSaveConfig.Enabled = True

End Sub

Private Sub cmdEditScannerOffsets_Click()
  Enabled_EditScannerOffsets True
  cmdEditScannerOffsets.Enabled = False
End Sub

Private Sub cmdExit_Click()

   End
   
End Sub 'cmdExit_Click


Private Sub cmdSaveConfig_Click()
Dim nRetValue As Integer
  nRetValue = MsgBox("Are You Certain?", vbYesNo, "Updating Configuration Database")
  
  If (nRetValue = vbYes) Then
    SetPanelOffsets
    SetScannerOffsets
    SetIAIConstants
  End If
  
  cmdSaveConfig.Enabled = False
  Enabled_EditConfig False
   
   
End Sub 'cmdSaveConfig_Click



Private Sub cmdSaveDP_Click()

   dbcMachineDataPt.UpdateRecord
   
   SaveMachineDataPoints
   
End Sub 'cmdSaveDP_Click


Private Sub cmdSaveScannerOffsets_Click()
Dim lngX_0Offset As Long
Dim lngX_90Offset As Long

Dim lngY_0Offset As Long
Dim lngY_90Offset As Long
    
   SetScannerOffsets
   lngX_0Offset = Val(txbX_0Offset)
   lngX_90Offset = Val(txbX_90Offset)
    
   lngY_0Offset = Val(txbY_0Offset)
   lngY_90Offset = Val(txbY_90Offset)
   Enabled_EditConfig False
   cmdEditScannerOffsets.Enabled = True
   
   If g_blnSimulator Then Exit Sub
    
   If (Not m_objIAICtrl.SetScannerOffsets(txbIAIProgramNumber, _
                                   txbIAIScannerCodeOffset, _
                                   lngX_0Offset, _
                                   lngY_0Offset, _
                                   lngX_90Offset, _
                                   lngY_90Offset)) Then
     MsgBox ("Error")
   End If
   
  

End Sub

Private Sub cmdTestScannerOffset_Click()
  frmScannerOffsetTest.Show 1
End Sub

Private Sub dbgMachineDataPt_RowColChange(LastRow As Variant, ByVal LastCol As Integer)

   dbcMachineDataPt.Caption = dbgMachineDataPt.Columns(0).Text
   
End Sub 'dbgMachineDataPt_RowColChange


Private Sub Form_Load()
   
   frmMessage.Hide
   
   g_blnTest = False
   
   #If cc_Labeler Then
      g_blnSimulator = True
   #Else
      g_blnSimulator = False
   #End If
   
   CenterForm Me
 ' Take out the stuff on the data points for now
   Set m_objIAICtrl = New clsMotionControl
   sstConfiguration.TabEnabled(1) = True
   
   
    
   dbcMachineDataPt.DatabaseName = App.Path & "\Labeler.mdb"
   
   m_strDatabaseName = App.Path + "\labeler.mdb"
   
   GetPanelOffsets
   GetScannerOffsets
   GetIAIConstants
   Enabled_EditConfig False
   cmdSaveConfig.Enabled = False
   
   
End Sub 'Form_Load
Public Sub Enabled_EditScannerOffsets(blnEnable As Boolean)
  
 If blnEnable Then
   ' Enable editing of scanner offsets.
   txbX_0Offset.Enabled = True
   txbX_90Offset.Enabled = True
   txbY_0Offset.Enabled = True
   txbY_90Offset.Enabled = True
 Else
   ' Default to disable editing of scanner offsets.
   txbX_0Offset.Enabled = False
   txbX_90Offset.Enabled = False
   txbY_0Offset.Enabled = False
   txbY_90Offset.Enabled = False
 
 End If
  
  
End Sub
Public Sub Enabled_EditIAIConstants(blnEnable As Boolean)
  
 If blnEnable Then
   ' Enable editing of scanner offsets.
   txbIAIProgramNumber.Enabled = True
   txbIAIStartDataPoint.Enabled = True
   txbIAIScannerCodeOffset.Enabled = True
   txbIAILabelsPerBoard.Enabled = True
 Else
   ' Default to disable editing of scanner offsets.
   txbIAIProgramNumber.Enabled = False
   txbIAIProgramNumber.Font.Bold = True
   
   txbIAIStartDataPoint.Enabled = False
   txbIAIStartDataPoint.Font.Bold = True
   
   txbIAIScannerCodeOffset.Enabled = False
   txbIAIScannerCodeOffset.Font.Bold = True
    
   txbIAILabelsPerBoard.Enabled = False
   txbIAILabelsPerBoard.Font.Bold = True
 
 End If
  
  
End Sub

Public Sub Enabled_EditConfig(blnEnable As Boolean)
  
  Enabled_EditScannerOffsets blnEnable
  Enabled_EditIAIConstants blnEnable
 
 If blnEnable Then
   ' Enable editing of Panel offsets.
   txbXPanelOffset.Enabled = True
   txbXOperator.Enabled = True
   txbYPanelOffset.Enabled = True
   txbYOperator.Enabled = True
   txbIAINosePieceOffset.Enabled = True
 Else
   ' Default to disable editing of panel offsets.
   txbXPanelOffset.Enabled = False
   txbXOperator.Enabled = False
   txbYPanelOffset.Enabled = False
   txbYOperator.Enabled = False
   txbIAINosePieceOffset.Enabled = False
 End If
  
  
End Sub


Public Sub GetIAIConstants()
   Set m_dbConfiguration = OpenDatabase(m_strDatabaseName)
   Set m_rsConfiguration = m_dbConfiguration.OpenRecordset("Select * from tblConfiguration")
   
   With m_rsConfiguration
   
     If (Not .EOF) Then
'       If (IsNull(.Fields("IAIScannerOffsetProgramN"))) Then
         'if first time
         txbIAIProgramNumber = "1"
'       Else
         ' if record exists (should be only 1)
 '        txbIAIProgramNumber = .Fields("IAIScannerOffsetProgramN")
'       End If
       
       If (IsNull(.Fields("PointDataTableOffset"))) Then
         'if first time
         txbIAIStartDataPoint = ""
       Else
         ' if record exists (should be only 1)
         txbIAIStartDataPoint = .Fields("PointDataTableOffset")
       End If
       
       If (IsNull(.Fields("ScannerOffsetLine"))) Then
         'if first time
         txbIAIScannerCodeOffset = ""
       Else
         ' if record exists (should be only 1)
         txbIAIScannerCodeOffset = .Fields("ScannerOffsetLine")
       End If
     
       If (IsNull(.Fields("BoardCountCodeLine"))) Then
         'if first time
         txbIAILabelsPerBoard = ""
       Else
         ' if record exists (should be only 1)
         txbIAILabelsPerBoard = .Fields("BoardCountCodeLine")
       End If
       
       
       If (IsNull(.Fields("NosePieceOffset"))) Then
         'if first time
         txbIAINosePieceOffset = ""
       Else
         ' if record exists (should be only 1)
         txbIAINosePieceOffset = .Fields("NosePieceOffset")
       End If
     End If
     
   
     .Close
   
   End With
   m_dbConfiguration.Close
   Set m_rsConfiguration = Nothing
   Set m_dbConfiguration = Nothing
   
   
   


End Sub
Public Sub SetIAIConstants()
   Set m_dbConfiguration = OpenDatabase(m_strDatabaseName)
   Set m_rsConfiguration = m_dbConfiguration.OpenRecordset("Select * from tblConfiguration")
   
   With m_rsConfiguration
   
     If (Not .EOF) Then
        .Edit
'       .Fields("IAIScannerOffsetProgramN") = txbIAIProgramNumber
       .Fields("PointDataTableOffset") = Val(txbIAIStartDataPoint)
       
       .Fields("ScannerOffsetLine") = txbIAIScannerCodeOffset
       .Fields("BoardCountCodeLine") = txbIAILabelsPerBoard
       .Fields("NosePieceOffset") = Val(txbIAINosePieceOffset)
       .Update
     Else
        .AddNew
 '      .Fields("IAIScannerOffsetProgramN") = txbIAIProgramNumber
       .Fields("PointDataTableOffset") = Val(txbIAIStartDataPoint)
       
       .Fields("ScannerOffsetLine") = txbIAIScannerCodeOffset
       .Fields("BoardCountCodeLine") = txbIAILabelsPerBoard
       .Fields("NosePieceOffset") = Val(txbIAINosePieceOffset)
       .Update
     
     
     
     End If
     
   
        .Close
   
   End With
   m_dbConfiguration.Close
   Set m_rsConfiguration = Nothing
   Set m_dbConfiguration = Nothing
   
   
   


End Sub

Public Sub GetScannerOffsets()
   Set m_dbConfiguration = OpenDatabase(m_strDatabaseName)
   Set m_rsConfiguration = m_dbConfiguration.OpenRecordset("Select * from tblConfiguration")
   
   With m_rsConfiguration
   
     If (Not .EOF) Then
     
       txbX_0Offset = .Fields("XScanner0Offset")
       txbY_0Offset = .Fields("YScanner0Offset")
       
       txbX_90Offset = .Fields("XScanner90Offset")
       txbY_90Offset = .Fields("YScanner90Offset")
       
     
     Else
     
        MsgBox ("Missing Scanner Offset")
     
     End If
     
   
        .Close
   
   End With
   m_dbConfiguration.Close
   Set m_rsConfiguration = Nothing
   Set m_dbConfiguration = Nothing
   
   
   
End Sub
Public Sub SetScannerOffsets()
   Set m_dbConfiguration = OpenDatabase(m_strDatabaseName)
   Set m_rsConfiguration = m_dbConfiguration.OpenRecordset("Select * from tblConfiguration")
   
   With m_rsConfiguration
   
     If (Not .EOF) Then
       .Edit    'not 1st time edit existing record
       .Fields("XScanner0Offset") = txbX_0Offset
       .Fields("YScanner0Offset") = txbY_0Offset
       
       .Fields("XScanner90Offset") = txbX_90Offset
       .Fields("YScanner90Offset") = txbY_90Offset
       .Update
       
     
     Else
     
       .AddNew    '1st time add record
       .Fields("XScanner0Offset") = Val(txbX_0Offset)
       .Fields("YScanner0Offset") = Val(txbY_0Offset)
       
       .Fields("XScanner90Offset") = Val(txbX_90Offset)
       .Fields("YScanner90Offset") = Val(txbY_90Offset)
       .Update
             
     End If
     
   
        .Close
   
   End With
   m_dbConfiguration.Close
   Set m_rsConfiguration = Nothing
   Set m_dbConfiguration = Nothing
   
   
   
End Sub
Public Sub GetPanelOffsets()
   Set m_dbConfiguration = OpenDatabase(m_strDatabaseName)
   Set m_rsConfiguration = m_dbConfiguration.OpenRecordset("Select * from tblConfiguration")
   
   With m_rsConfiguration
   
     If (Not .EOF) Then
     
       txbXPanelOffset = .Fields("XPanelOffset")
       txbYPanelOffset = .Fields("YPanelOffset")
       txbXOperator = .Fields("XOperator")
       txbYOperator = .Fields("YOperator")
     
     Else
     
        MsgBox ("Missing Panel Offsets")
     
     End If
     
   
        .Close
   
   End With
   m_dbConfiguration.Close
   Set m_rsConfiguration = Nothing
   Set m_dbConfiguration = Nothing
   
   
   
End Sub
Public Sub SetPanelOffsets()
   Set m_dbConfiguration = OpenDatabase(m_strDatabaseName)
   Set m_rsConfiguration = m_dbConfiguration.OpenRecordset("Select * from tblConfiguration")
   
   With m_rsConfiguration
   
     If (Not .EOF) Then
       .Edit
       .Fields("XPanelOffset") = Val(txbXPanelOffset)
       .Fields("YPanelOffset") = Val(txbYPanelOffset)
       .Fields("XOperator") = Val(txbXOperator)
       .Fields("YOperator") = Val(txbYOperator)
       .Update
     Else
       .AddNew
       .Fields("XPanelOffset") = Val(txbXPanelOffset)
       .Fields("YPanelOffset") = Val(txbYPanelOffset)
       .Fields("XPanelOffset") = Val(txbXOperator)
       .Fields("YPanelOffset") = Val(txbYOperator)
       .Update
     
     
     End If
     
   
        .Close
   
   End With
   m_dbConfiguration.Close
   Set m_rsConfiguration = Nothing
   Set m_dbConfiguration = Nothing
   
   
   
End Sub





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


Private Sub mnuFileExit_Click()
  Unload Me
  End
End Sub

Private Sub mnuFilePreferences_Click()
  frmCommSpecs.Show 1
End Sub
