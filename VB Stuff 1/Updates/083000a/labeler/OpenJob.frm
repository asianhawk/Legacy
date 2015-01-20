VERSION 5.00
Object = "{0BA686C6-F7D3-101A-993E-0000C0EF6F5E}#1.0#0"; "THREED32.OCX"
Object = "{B16553C3-06DB-101B-85B2-0000C009BE81}#1.0#0"; "SPIN32.OCX"
Object = "{B9D22273-0C24-101B-AEBD-04021C009402}#1.0#0"; "KEYSTA32.OCX"
Object = "{00028C01-0000-0000-0000-000000000046}#1.0#0"; "DBGRID32.OCX"
Begin VB.Form frmOpenJob 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "frmOpenJob"
   ClientHeight    =   4935
   ClientLeft      =   2670
   ClientTop       =   1935
   ClientWidth     =   4950
   Icon            =   "OpenJob.frx":0000
   LinkTopic       =   "frmOpenJob"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   4935
   ScaleWidth      =   4950
   ShowInTaskbar   =   0   'False
   WhatsThisButton =   -1  'True
   WhatsThisHelp   =   -1  'True
   Begin VB.TextBox txbQuantity 
      Height          =   375
      Left            =   3480
      MaxLength       =   5
      TabIndex        =   3
      Text            =   "txbQuanity"
      Top             =   600
      Width           =   1095
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "cmdOK"
      Default         =   -1  'True
      Height          =   435
      Left            =   2340
      TabIndex        =   4
      Top             =   2145
      Width           =   1095
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "cmdCancel"
      Height          =   435
      Left            =   3600
      TabIndex        =   5
      Top             =   2160
      Width           =   1095
   End
   Begin Threed.SSPanel sspJobData 
      Height          =   2250
      Left            =   45
      TabIndex        =   8
      Top             =   2625
      Visible         =   0   'False
      Width           =   4740
      _Version        =   65536
      _ExtentX        =   8361
      _ExtentY        =   3969
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
      Begin VB.TextBox txbLastSerialNumber 
         DataField       =   "LastSerialNumber"
         DataSource      =   "dbcJobs"
         Height          =   300
         Left            =   2985
         TabIndex        =   20
         Text            =   "LastSerialNumber"
         Top             =   135
         Width           =   1335
      End
      Begin VB.TextBox txbTableName 
         DataField       =   "TableName"
         DataSource      =   "dbcJobs"
         Height          =   300
         Left            =   2985
         TabIndex        =   19
         Text            =   "TableName"
         Top             =   1095
         Width           =   1335
      End
      Begin VB.TextBox txbDBpath 
         DataField       =   "DBpath"
         DataSource      =   "dbcJobs"
         Height          =   300
         Left            =   2985
         TabIndex        =   18
         Text            =   "DBpath"
         Top             =   780
         Width           =   1320
      End
      Begin VB.TextBox txbPlantCode 
         DataField       =   "PlantCode"
         DataSource      =   "dbcJobs"
         Height          =   300
         Left            =   2985
         TabIndex        =   17
         Text            =   "PlantCode"
         Top             =   450
         Width           =   1335
      End
      Begin VB.Data dbcJobs 
         Caption         =   "dbcJobs"
         Connect         =   "Access"
         DatabaseName    =   "C:\Labeler\LucentTechSP.mdb"
         DefaultCursorType=   0  'DefaultCursor
         DefaultType     =   2  'UseODBC
         Exclusive       =   0   'False
         Height          =   300
         Left            =   120
         Options         =   0
         ReadOnly        =   0   'False
         RecordsetType   =   2  'Snapshot
         RecordSource    =   "qurJobFile"
         Top             =   1875
         Width           =   2505
      End
      Begin VB.TextBox txbJobsID 
         DataField       =   "JobsID"
         DataSource      =   "dbcJobs"
         Height          =   300
         Left            =   120
         TabIndex        =   16
         Text            =   "JobsID"
         Top             =   150
         Width           =   1350
      End
      Begin VB.TextBox txbTempate 
         DataField       =   "Tempate"
         DataSource      =   "dbcJobs"
         Height          =   300
         Left            =   1515
         TabIndex        =   15
         Text            =   "Tempate"
         Top             =   1095
         Width           =   1440
      End
      Begin VB.TextBox txbTemplateName 
         DataField       =   "TemplateName"
         DataSource      =   "dbcJobs"
         Height          =   300
         Left            =   1515
         TabIndex        =   14
         Text            =   "TemplateName"
         Top             =   780
         Width           =   1440
      End
      Begin VB.TextBox txbTemplateFields 
         DataField       =   "TemplateFields"
         DataSource      =   "dbcJobs"
         Height          =   300
         Left            =   1515
         TabIndex        =   13
         Text            =   "TemplateFields"
         Top             =   465
         Width           =   1440
      End
      Begin VB.TextBox txbTemplatePath 
         DataField       =   "TemplatePath"
         DataSource      =   "dbcJobs"
         Height          =   300
         Left            =   1515
         TabIndex        =   12
         Text            =   "TemplatePath"
         Top             =   150
         Width           =   1440
      End
      Begin VB.TextBox txbJobsDiscriptions 
         DataField       =   "JobsDiscriptions"
         DataSource      =   "dbcJobs"
         Height          =   300
         Left            =   120
         TabIndex        =   11
         Text            =   "JobsDiscriptions"
         Top             =   1080
         Width           =   1335
      End
      Begin VB.TextBox txbJobsPartNumber 
         DataField       =   "JobsPartNumber"
         DataSource      =   "dbcJobs"
         Height          =   285
         Left            =   135
         TabIndex        =   10
         Text            =   "JobsPartNumber"
         Top             =   780
         Width           =   1335
      End
      Begin VB.TextBox txbJobsName 
         DataField       =   "JobsName"
         DataSource      =   "dbcJobs"
         Height          =   300
         Left            =   135
         TabIndex        =   9
         Text            =   "JobsName"
         Top             =   465
         Width           =   1335
      End
   End
   Begin MSDBGrid.DBGrid dbgJobs 
      Bindings        =   "OpenJob.frx":0442
      Height          =   1815
      Left            =   150
      OleObjectBlob   =   "OpenJob.frx":0458
      TabIndex        =   1
      Top             =   255
      Width           =   3195
   End
   Begin KeyStatLib.MhState kstJobs 
      Height          =   375
      Left            =   1620
      TabIndex        =   7
      Top             =   2160
      Visible         =   0   'False
      Width           =   375
      _Version        =   65536
      _ExtentX        =   661
      _ExtentY        =   661
      _StockProps     =   65
      Value           =   -1  'True
      Style           =   1
      MouseIcon       =   "OpenJob.frx":0E4B
   End
   Begin Spin.SpinButton spbQuantity 
      Height          =   375
      Left            =   4560
      TabIndex        =   6
      Top             =   600
      Width           =   255
      _Version        =   65536
      _ExtentX        =   450
      _ExtentY        =   661
      _StockProps     =   73
      BackColor       =   -2147483633
      ShadowThickness =   1
      TdThickness     =   1
   End
   Begin VB.Label labJobs 
      AutoSize        =   -1  'True
      Caption         =   "labJobs"
      Height          =   195
      Left            =   105
      TabIndex        =   0
      Top             =   0
      Width           =   540
   End
   Begin VB.Label labQuantity 
      AutoSize        =   -1  'True
      Caption         =   "labQuanity"
      Height          =   195
      Left            =   3480
      TabIndex        =   2
      Top             =   360
      Width           =   750
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
'*     © Copywrite 1997 Computype, Inc.
'*
'*        3-Axis Label Applicator
'*           Control software
'*             Open job form
'*
'*
'*    Customer: Lucent Technologies
'*              Shreveport, LA
'*
'*
'*    Date of origin: 1/23/97
'*    Original author: Michael D. Reed
'*
'* Form purpose:
'*    This is the diloge box to get a job to run.
'*
'************************************************************************
Option Explicit

'    Collums for job grid
Private Const m_gclPART_NUM = 0
Private Const m_gclNAME = 1

'  my name
Private m_strName As String

'  to  save old numlock keystate
Private m_blnOldNumLockKeyState As Boolean

'  form or class which called this form
Private m_objCaller As Object

Private Sub cmdCancel_Click()

   Unload Me
   
End Sub 'cmdCancel

Private Sub cmdOK_Click()

   #If ccShip_Ver Then
      On Error GoTo cmdOK_Click_Error
   #Else
      On Error GoTo 0
   #End If

   Me.Hide
   modUtilities.MessageDisplay LoadResString(resINITIALIZING_JOB)
   
   '  Send job info back
   m_objCaller.InfoJob strJobID:=txbJobsID.Text, strName:=txbJobsName.Text, strLastSerialNumber:=txbLastSerialNumber.Text, _
                        strPartNumber:=txbJobsPartNumber.Text, strPlantCode:=txbPlantCode.Text, _
                        strDescription:=txbJobsDiscriptions.Text, strQuanity:=txbQuantity.Text, _
                        strTemplate:=txbTempate.Text, strFormatName:=txbTemplateName.Text, _
                        strFieldCount:=txbTemplateFields.Text, strTemplatePath:=txbTemplatePath.Text, _
                        strTableName:=txbTableName.Text, strDBPath:=txbDBpath.Text _

   Unload Me
   
   Exit Sub

cmdOK_Click_Error:

   ProccessError "cmdOK_Click", m_strName, Err.Number, Err.Description

End Sub 'cmdOK_Click






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
   
   '  Set form height
   Me.Height = 3160
   
   '  Set database location
   dbcJobs.DatabaseName = modMain.JobDatabaseName
   dbcJobs.ReadOnly = True
   
   '  Setup controls on form
   labJobs.Caption = LoadResString(resLABEL_OPEN_JOBES)
   With dbgJobs
      .Columns.Item(m_gclPART_NUM).Caption = LoadResString(resLABEL_OPEN_GRID_PN)
      .Columns.Item(m_gclNAME).Caption = LoadResString(resLABEL_OPEN_GRID_NAME)
      .Columns.Item(m_gclPART_NUM).Width = 1000
   End With 'dbgJobs
   labQuantity.Caption = LoadResString(resLABEL_OPEN_QUANTITY)
   txbQuantity.Text = "0"
   
   '  Set up the form
   Me.Caption = modMain.JobDatabaseName & " - " & LoadResString(resFORM_OPEN_JOB)
   modUtilities.CenterForm Me
   
   m_blnOldNumLockKeyState = kstJobs.Value
   kstJobs.Value = True
   
   Exit Sub

Form_Load_Error:

   ProccessError "Form_Load", m_strName, Err.Number, Err.Description

End Sub 'Form_Load



Private Sub Form_Unload(Cancel As Integer)

   kstJobs.Value = m_blnOldNumLockKeyState
   
End Sub 'Form_Unload


Private Sub spbQuantity_SpinDown()

   DecrementQuantity
   
End Sub 'spbQuantity_SpinDown


Private Sub spbQuantity_SpinUp()

   IncrementQuantity

End Sub 'spbQuantity_SpinUp


Private Sub IncrementQuantity()

   Dim intQuantity As Long
   
   #If ccShip_Ver Then
      On Error GoTo IncrementQuantity_Error
   #Else
      On Error GoTo 0
   #End If

   intQuantity = CLng(txbQuantity.Text)
   If intQuantity < g_intMaxPCBRunQuantity Then
      txbQuantity.Text = CStr(intQuantity + 1)
   End If

   Exit Sub

IncrementQuantity_Error:

   ProccessError "IncrementQuantity", m_strName, Err.Number, Err.Description

End Sub 'IncrementQuantity


Private Sub DecrementQuantity()

   Dim intQuantity As Long
   
   #If ccShip_Ver Then
      On Error GoTo DecrementQuantity_Error
   #Else
      On Error GoTo 0
   #End If

   intQuantity = CLng(txbQuantity.Text)
   If intQuantity > 0 Then
      txbQuantity.Text = CStr(intQuantity - 1)
   End If
   
   Exit Sub

DecrementQuantity_Error:

   ProccessError "DecrementQuantity", m_strName, Err.Number, Err.Description

End Sub 'DecrementQuantity


Private Sub txbQuantity_GotFocus()

   SelectAll txbQuantity
   
End Sub 'txbQuantity_GotFocus

Private Sub txbQuantity_KeyPress(KeyAscii As Integer)

   #If ccShip_Ver Then
      On Error GoTo txbQuantity_KeyPress_Error
   #Else
      On Error GoTo 0
   #End If
      
   If KeyAscii = 45 Then ' chr - so decrement value
         DecrementQuantity
   ElseIf KeyAscii = 43 Then ' chr + so increment value
      IncrementQuantity
   ElseIf (48 <= KeyAscii) And (KeyAscii <= 57) Then
      If txbQuantity.Text = "" Then
         Exit Sub
      ElseIf CLng(txbQuantity.Text) < g_intMaxPCBRunQuantity Then
         '  number pressed and quantity is not to big so exit sub
         Exit Sub
      End If
   ElseIf KeyAscii = 8 Then
      '  backspace so exit sub
      Exit Sub
   End If
   
   '  Clear the key so it will not print
   KeyAscii = 0

   Exit Sub 'txbQuantity_KeyPress

txbQuantity_KeyPress_Error:

   ProccessError "txbQuantity_KeyPress", "frmOpenJob", Err.Number, Err.Description

End Sub 'txbQuantity_KeyPress


Public Sub SelectAll(objTextBox As Control)

   #If ccShip_Ver Then
      On Error Resume Next
   #Else
      On Error GoTo 0
   #End If

   With objTextBox
      .SelStart = 0
      .SelLength = Len(.Text)
   End With 'objTextBox
   
End Sub 'SelectAll





Public Sub Initialize(objCaller As Object)
   
   #If ccShip_Ver Then
      On Error Resume Next
   #Else
      On Error GoTo 0
   #End If

   Set m_objCaller = objCaller

End Sub 'Initialize


