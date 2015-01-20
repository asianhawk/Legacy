VERSION 5.00
Object = "{00028C01-0000-0000-0000-000000000046}#1.0#0"; "DBGRID32.OCX"
Begin VB.Form frmOpenJob 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "frmOpenJob"
   ClientHeight    =   5790
   ClientLeft      =   1500
   ClientTop       =   1935
   ClientWidth     =   8715
   Icon            =   "OpenJob.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "frmOpenJob"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   5790
   ScaleWidth      =   8715
   ShowInTaskbar   =   0   'False
   WhatsThisButton =   -1  'True
   WhatsThisHelp   =   -1  'True
   Begin VB.Frame frEdit 
      Height          =   975
      Left            =   2160
      TabIndex        =   20
      Top             =   3480
      Width           =   4455
      Begin VB.CommandButton cmdPost 
         Cancel          =   -1  'True
         Caption         =   "Post Changes"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   540
         Left            =   2160
         TabIndex        =   22
         Top             =   240
         Width           =   1995
      End
      Begin VB.CommandButton Command1 
         Caption         =   "Edit Job Info"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   540
         Left            =   360
         TabIndex        =   21
         Top             =   240
         Width           =   1755
      End
   End
   Begin VB.Frame frOK 
      Height          =   1095
      Left            =   2160
      TabIndex        =   16
      Top             =   4560
      Width           =   4455
      Begin VB.CommandButton cmdRun 
         Caption         =   "cmdRun"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   780
         Left            =   3000
         TabIndex        =   19
         Top             =   240
         Width           =   1400
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
         Height          =   780
         Left            =   1560
         TabIndex        =   18
         Top             =   240
         Width           =   1400
      End
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
         Height          =   780
         Left            =   120
         TabIndex        =   17
         Top             =   240
         Width           =   1400
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Frame1"
      Height          =   2415
      Left            =   720
      TabIndex        =   1
      Top             =   5760
      Visible         =   0   'False
      Width           =   7215
      Begin VB.TextBox txbBBoardFlavor 
         DataField       =   "BBoardFlavor"
         DataSource      =   "dbcJobs"
         Height          =   285
         Left            =   1560
         TabIndex        =   24
         Text            =   "BBFlavor"
         Top             =   1680
         Width           =   1455
      End
      Begin VB.TextBox txb2Sided 
         DataField       =   "2Sided"
         DataSource      =   "dbcJobs"
         Height          =   285
         Left            =   4440
         TabIndex        =   23
         Text            =   "txb2Sided"
         Top             =   1320
         Width           =   1815
      End
      Begin VB.TextBox txtStopPin_1 
         DataField       =   "Stop Pin 1"
         DataSource      =   "dbcJobs"
         Height          =   285
         Left            =   5280
         TabIndex        =   15
         Text            =   "txtStopPin1"
         Top             =   240
         Visible         =   0   'False
         Width           =   1815
      End
      Begin VB.TextBox txbTemplatePath 
         DataField       =   "txtTemplatePath"
         DataSource      =   "dbcJobs"
         Height          =   300
         Left            =   1560
         TabIndex        =   14
         Text            =   "TemplatePath"
         Top             =   960
         Width           =   1440
      End
      Begin VB.TextBox txbHPEnabled 
         DataField       =   "HP Enabled"
         DataSource      =   "dbcJobs"
         Height          =   285
         Left            =   5280
         TabIndex        =   13
         Text            =   "txbHPEnabled"
         Top             =   600
         Width           =   1815
      End
      Begin VB.TextBox txbHolePattern 
         DataField       =   "Hole Pattern (HP)"
         DataSource      =   "dbcJobs"
         Height          =   285
         Left            =   3360
         TabIndex        =   12
         Text            =   "txbHolePattern"
         Top             =   600
         Width           =   1815
      End
      Begin VB.TextBox txtStopPin_2 
         DataField       =   "Stop Pin 2"
         DataSource      =   "dbcJobs"
         Height          =   285
         Left            =   3360
         TabIndex        =   11
         Text            =   "txtStopPin2"
         Top             =   240
         Visible         =   0   'False
         Width           =   1815
      End
      Begin VB.TextBox txbDisable_Scanner 
         DataField       =   "txtScannerDisabled"
         DataSource      =   "dbcJobs"
         Height          =   285
         Left            =   5280
         TabIndex        =   10
         Text            =   "Disable Scanner"
         Top             =   960
         Visible         =   0   'False
         Width           =   1815
      End
      Begin VB.TextBox txbRotate_NosePiece 
         DataField       =   "txtRotateLabels"
         DataSource      =   "dbcJobs"
         Height          =   285
         Left            =   3360
         TabIndex        =   9
         Text            =   "txbRotateNosePiece"
         Top             =   960
         Visible         =   0   'False
         Width           =   1815
      End
      Begin VB.TextBox txbLocationCode 
         DataField       =   "txtLocationCode"
         DataSource      =   "dbcJobs"
         Height          =   285
         Left            =   1560
         TabIndex        =   8
         Text            =   "LocationCode"
         Top             =   1320
         Width           =   1455
      End
      Begin VB.TextBox txbTemplateName 
         DataField       =   "txtTemplateName"
         DataSource      =   "dbcJobs"
         Height          =   300
         Left            =   1560
         TabIndex        =   7
         Text            =   "TemplateName"
         Top             =   600
         Width           =   1440
      End
      Begin VB.Data dbcJobs 
         Caption         =   "dbcJobs"
         Connect         =   "Access"
         DatabaseName    =   "C:\Ford Markam\Labeler\Jobs.mdb"
         DefaultCursorType=   0  'DefaultCursor
         DefaultType     =   2  'UseODBC
         Exclusive       =   0   'False
         Height          =   345
         Left            =   4080
         Options         =   0
         ReadOnly        =   0   'False
         RecordsetType   =   1  'Dynaset
         RecordSource    =   "qurJobFile"
         Top             =   1800
         Width           =   2505
      End
      Begin VB.TextBox txbPartNumber 
         DataField       =   "txtPartNumber"
         DataSource      =   "dbcJobs"
         Height          =   285
         Left            =   120
         TabIndex        =   6
         Text            =   "PartNumber"
         Top             =   960
         Width           =   1335
      End
      Begin VB.TextBox txbJobsName 
         DataField       =   "txtJobsName"
         DataSource      =   "dbcJobs"
         Height          =   300
         Left            =   120
         TabIndex        =   5
         Text            =   "JobsName"
         Top             =   600
         Width           =   1335
      End
      Begin VB.TextBox txbJobsID 
         DataField       =   "idJobs"
         DataSource      =   "dbcJobs"
         Height          =   300
         Left            =   120
         TabIndex        =   4
         Text            =   "JobsID"
         Top             =   240
         Width           =   1350
      End
      Begin VB.TextBox txbFlavor 
         DataField       =   "txtFlavor"
         DataSource      =   "dbcJobs"
         Height          =   285
         Left            =   1560
         TabIndex        =   3
         Text            =   "txbflavor"
         Top             =   240
         Width           =   1455
      End
      Begin VB.TextBox txbLastSeqNumber 
         DataField       =   "lngLastSeqNumber"
         DataSource      =   "dbcJobs"
         Height          =   285
         Left            =   120
         TabIndex        =   2
         Text            =   "LastSeqNumber"
         Top             =   1320
         Width           =   1455
      End
   End
   Begin MSDBGrid.DBGrid dbgJobs 
      Bindings        =   "OpenJob.frx":0442
      Height          =   3300
      Left            =   480
      OleObjectBlob   =   "OpenJob.frx":0454
      TabIndex        =   0
      Top             =   120
      Width           =   7860
   End
End
Attribute VB_Name = "frmOpenJob"
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

Public m_blnJobCancel As Boolean    'added 05/11/01


'    Collums for job grid
Private Const m_gclPARTNUMBER = 0
Private Const m_gclNAME = 1

'  my name
Private m_strName As String
'Public g_JRFlavor As Integer


'  form or class which called this form
Private m_objCaller As Object

'  Flage to indicate that a new job was chosen
'  Set to true if operator selected
Private m_blnNewJob As Boolean

Private Sub cmdCancel_Click()
   dbgJobs.AllowUpdate = False
   m_blnJobCancel = True   'added 05/11/01
   Me.Hide
   
End Sub 'cmdCancel



Private Sub cmdOK_Click()
Dim intRow As Integer
   '  Send false to wait for
   '  operator action to start the job
   g_strStopPin_1 = txtStopPin_1
   g_strStopPin_2 = txtStopPin_2
   Me.Hide
   dbgJobs.AllowUpdate = False
   m_blnJobCancel = False   ' added 05/11/01
   JobInfo False
   
End Sub 'cmdOK_Click


Private Sub cmdPost_Click()
  Dim intRow As Integer
  Dim strBuffer As String
  Dim i As Integer
  
   intRow = dbgJobs.Row + 1
   dbgJobs.Col = 2
   strBuffer = dbgJobs.Text
   dbgJobs.Refresh

   SetJobCmds True
   dbgJobs.AllowUpdate = False
   cmdPost.Enabled = False
   dbgJobs.Row = intRow
   dbgJobs.Col = 2
        
  For i = 0 To dbgJobs.VisibleRows - 1
    dbgJobs.Row = i
    If dbgJobs.Text = strBuffer Then
       
       Exit For
    End If
  Next i
  Command1.Enabled = True
End Sub

Private Sub cmdRun_Click()
    dbgJobs.AllowUpdate = False

   '  Send true to run the job immediately
   Me.Hide
   JobInfo True
   
End Sub 'cmdRun_Click

Private Sub Command1_Click()
  SetJobCmds False
  
  frmLogin.Show 1
  If LoginSucceeded Then
    dbgJobs.AllowUpdate = True
'    dbcJobs.Refresh
    dbgJobs.Refresh
    cmdPost.Enabled = True
    Command1.Enabled = False
  Else
    SetJobCmds True
    cmdPost.Enabled = False
    dbgJobs.AllowUpdate = False
    Command1.Enabled = True
  End If
  DoEvents
  
End Sub
Private Sub SetJobCmds(blnCmd As Boolean)
  cmdCancel.Enabled = False
  cmdOK.Enabled = blnCmd
  cmdRun.Enabled = blnCmd
End Sub

Private Sub Form_Load()

   #If ccShip_Ver Then
      On Error GoTo Form_Load_Error
   #Else
      On Error GoTo 0
   #End If

   m_strName = Me.Name
   
   '  Setup the cancel and ok buttons
   modMain.SetupOkButton cmdOK
   modMain.SetupCancelButton cmdCancel
   cmdRun.Caption = LoadResString(resCMD_AUTO_RUN)
   
   '  Set form height
   Me.Height = 6435
   SetJobCmds True
   cmdPost.Enabled = False
   
   '  Set database location
   dbcJobs.DatabaseName = modMain.JobDatabaseName
   
   '  Setup controls on form
   With dbgJobs
      .Caption = LoadResString(resLABEL_OPEN_JOBES)
'      .Columns.Item(m_gclPARTNUMBER).Caption = LoadResString(resLABEL_OPEN_PARTNUMBER)
'      .Columns.Item(m_gclNAME).Caption = LoadResString(resLABEL_OPEN_GRID_NAME)
'      .Columns.Item(m_gclPARTNUMBER).Width = 2000
   End With 'dbgJobs
   
   '  Set up the form
   Me.Caption = modMain.JobDatabaseFile & " - " & LoadResString(resFORM_OPEN_JOB)
   modUtilities.CenterForm Me
   dbgJobs.AllowUpdate = False
   cmdCancel.Enabled = True
   
   
   Exit Sub

Form_Load_Error:

   ProccessError "Form_Load", m_strName, Err.Number, Err.Description

End Sub 'Form_Load

Public Sub SelectAll(objTextBox As Control)

   With objTextBox
      .SelStart = 0
      .SelLength = Len(.Text)
   End With 'objTextBox
   
End Sub 'SelectAll

Public Sub Initialize(objCaller As Object)
   
   Set m_objCaller = objCaller

End Sub 'Initialize

Private Sub JobInfo(blnRunImmediate As Boolean)

   #If ccShip_Ver Then
      On Error GoTo cmdOK_Click_Error
   #Else
      On Error GoTo 0
   #End If

'   frmMessage.MessageDisplay LoadResString(resINITIALIZING_JOB)
   g_strRotateNosePiece = txbRotate_NosePiece
   '  Send job info back
   m_objCaller.InfoJob strJobID:=txbJobsID.Text, strName:=txbJobsName.Text, _
                        strPartNumber:=txbPartNumber.Text, strLocationCode:=txbLocationCode.Text, _
                        strFormatName:=txbTemplateName.Text, strTemplatePath:=txbTemplatePath.Text, _
                        blnRunNow:=blnRunImmediate, blnNewJob:=m_blnNewJob
    
   
   Me.Hide
   
   Exit Sub

cmdOK_Click_Error:

   ProccessError "cmdOK_Click", m_strName, Err.Number, Err.Description

End Sub


Public Sub JobUpdate(ByVal v_strName As String, _
                     ByRef r_strPartNumber As String, _
                     ByRef r_strLocationCode As String, _
                     ByRef r_strFormatName As String, _
                     ByRef r_strTemplatePath As String)
'  This function updates a record in the jobs database.
'  Or add a new record if none exists for the part number.
'  If the part number is not found and no data is given for
'  it an error is raised.

   Dim blnRecordData As Boolean
   
   #If ccShip_Ver Then
      On Error GoTo JobUpdate_Error
   #Else
      On Error GoTo 0
   #End If
   
   m_blnNewJob = False
   
   '  if not name has been sent in then junk sent in ignore all.
   If v_strName = "" Then Exit Sub
   
   blnRecordData = r_strPartNumber <> "" _
               And r_strLocationCode <> ""
   
   With dbcJobs
      .ReadOnly = False
      .Recordset.FindFirst "txtJobsName=" & "'" & v_strName & "'"
      If blnRecordData Then
         '  No match add new record ...
         If .Recordset.NoMatch Then
            .Recordset.AddNew
         End If
         txbJobsName.Text = v_strName
         txbPartNumber.Text = r_strPartNumber
         txbLocationCode.Text = r_strLocationCode
         If r_strFormatName <> "" Then
            txbTemplateName.Text = r_strFormatName
         End If
         If r_strTemplatePath <> "" Then
            txbTemplatePath.Text = r_strTemplatePath
         End If
         .UpdateRecord
      Else '   update an existing record
         If .Recordset.NoMatch Then
            Err.Raise g_errNO_JOB_MATCH, , LoadResString(resERR_NO_JOB_MATCH) & v_strName
         End If
         If r_strPartNumber <> "" Then
            r_strPartNumber = txbPartNumber.Text
         End If
         If r_strLocationCode <> "" Then
            r_strLocationCode = txbLocationCode.Text
         End If
         If r_strFormatName <> "" Then
            r_strFormatName = txbTemplateName.Text
         End If
         If r_strTemplatePath <> "" Then
            r_strTemplatePath = txbTemplatePath.Text
         End If
         .UpdateRecord
      End If
      .ReadOnly = True
      .Recordset.FindFirst "txtJobsName=" & "'" & v_strName & "'"
   End With 'dbcJobs
   
   '  now send back the data to the labeler through the main form.
   JobInfo True
   
   Exit Sub

JobUpdate_Error:

   ProccessError "JobUpdate", m_strName, Err.Number, Err.Description

End Sub 'JobUpdate


Public Sub JobOpen(strInitalJob As String)

   Dim strMessage As String
   
   #If ccShip_Ver Then
      On Error GoTo JobOpen_Error
   #Else
      On Error GoTo 0
   #End If
   
   m_blnNewJob = True
   If strInitalJob = "" Then
      Me.Show vbModal
   Else
      With dbcJobs
         .ReadOnly = True
         .Recordset.FindFirst "txtJobsName=" & "'" & strInitalJob & "'"
         If .Recordset.NoMatch Then
            strMessage = """" & strInitalJob & """ "
            strMessage = strMessage & LoadResString(resJOB_NOT_IN_DB) & vbCrLf
            strMessage = strMessage & LoadResString(resPRESS_OK)
            MsgBox strMessage, vbOKOnly + vbExclamation, LoadResString(resTITLE_DB_ERROR)
            Me.Show vbModal
         ElseIf g_blnLabelerReady Then
            Me.Show vbModal
         Else
            Me.Width = 5000
            dbgJobs.Visible = False
            Me.Show vbModal
         End If
         .ReadOnly = False
      End With
   End If
   Exit Sub

JobOpen_Error:

   ProccessError "JobOpen", m_strName, Err.Number, Err.Description
   
End Sub 'JobOpen

Private Sub Form_Unload(Cancel As Integer)
 m_blnJobCancel = True
End Sub
