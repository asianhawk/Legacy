VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.1#0"; "COMDLG32.OCX"
Begin VB.Form frmMain 
   Caption         =   "Visteon 2-Axis Labeler Database Conversion Utility"
   ClientHeight    =   5715
   ClientLeft      =   3615
   ClientTop       =   1710
   ClientWidth     =   6585
   LinkTopic       =   "Form1"
   ScaleHeight     =   5715
   ScaleWidth      =   6585
   Begin VB.CommandButton cmdExit 
      Caption         =   "Exit"
      Height          =   855
      Left            =   3840
      TabIndex        =   19
      Top             =   4560
      Width           =   2535
   End
   Begin VB.Frame frmDefValue 
      Caption         =   "Default Value"
      Height          =   1095
      Left            =   3840
      TabIndex        =   15
      Top             =   3240
      Width           =   2415
      Begin VB.CommandButton cmdUpdate 
         Caption         =   "Shez Zam"
         Height          =   375
         Left            =   240
         TabIndex        =   18
         Top             =   600
         Width           =   1695
      End
      Begin VB.TextBox txbNewValue 
         Height          =   285
         Left            =   960
         TabIndex        =   17
         Top             =   240
         Width           =   1335
      End
      Begin VB.Label lblUpdateName 
         Alignment       =   1  'Right Justify
         Caption         =   "Value:"
         Height          =   285
         Left            =   240
         TabIndex        =   16
         Top             =   240
         Width           =   615
      End
   End
   Begin VB.CheckBox chkInitNewField 
      Caption         =   "Initialize New Field"
      Height          =   255
      Left            =   3720
      TabIndex        =   14
      Top             =   2880
      Width           =   2295
   End
   Begin VB.ComboBox cmbFieldName 
      Height          =   315
      Left            =   1680
      TabIndex        =   10
      Top             =   1080
      Width           =   3015
   End
   Begin VB.TextBox txbNumberOfFields 
      Height          =   405
      Left            =   4920
      TabIndex        =   9
      Top             =   480
      Width           =   1575
   End
   Begin VB.Frame frmConvert 
      Caption         =   "Update  Database"
      Height          =   2175
      Left            =   240
      TabIndex        =   6
      Top             =   3240
      Width           =   3375
      Begin VB.Frame Frame1 
         Caption         =   "Field Type"
         Height          =   975
         Left            =   120
         TabIndex        =   20
         Top             =   600
         Width           =   2895
         Begin VB.TextBox txbLength 
            Height          =   285
            Left            =   1560
            TabIndex        =   24
            Top             =   240
            Width           =   1095
         End
         Begin VB.OptionButton optIntegerDataType 
            Caption         =   "Integer"
            Height          =   255
            Left            =   1560
            TabIndex        =   23
            Top             =   600
            Width           =   1095
         End
         Begin VB.OptionButton optBooleanDataType 
            Caption         =   "Boolean"
            Height          =   255
            Left            =   120
            TabIndex        =   22
            Top             =   600
            Width           =   1095
         End
         Begin VB.OptionButton optTextDataType 
            Caption         =   "Text"
            Height          =   255
            Left            =   120
            TabIndex        =   21
            Top             =   240
            Width           =   735
         End
         Begin VB.Label lblLength 
            Alignment       =   1  'Right Justify
            Caption         =   "Length:"
            Height          =   285
            Left            =   840
            TabIndex        =   25
            Top             =   240
            Width           =   615
         End
      End
      Begin VB.TextBox txbNewFieldName 
         Height          =   285
         Left            =   1560
         TabIndex        =   12
         Top             =   240
         Width           =   1455
      End
      Begin VB.CommandButton cmdConvertDatabase 
         Caption         =   "Convert Database"
         Height          =   375
         Left            =   600
         TabIndex        =   7
         Top             =   1680
         Width           =   2175
      End
      Begin VB.Label Label5 
         Alignment       =   1  'Right Justify
         Caption         =   "New Field Name:"
         Height          =   285
         Left            =   120
         TabIndex        =   13
         Top             =   240
         Width           =   1335
      End
   End
   Begin VB.CheckBox chkAddField 
      Caption         =   "Add Field"
      Height          =   255
      Left            =   240
      TabIndex        =   5
      Top             =   2880
      Width           =   1215
   End
   Begin VB.TextBox txbNumberOfRecords 
      Height          =   405
      Left            =   1680
      TabIndex        =   4
      Top             =   480
      Width           =   1575
   End
   Begin VB.TextBox txbDatabaseName 
      Height          =   405
      Left            =   1680
      TabIndex        =   1
      Top             =   0
      Width           =   4815
   End
   Begin VB.CommandButton cmdSelectDatabase 
      Caption         =   "Select Database"
      Height          =   615
      Left            =   2280
      TabIndex        =   0
      Top             =   1680
      Width           =   2175
   End
   Begin MSComDlg.CommonDialog dlgCommon 
      Left            =   480
      Top             =   1560
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327681
      DialogTitle     =   "Open Jobs Database"
      FileName        =   "jobs.mdb"
      Filter          =   "Database (*.mdb)|*.mdb"
      InitDir         =   "c:\ford markam\labeler"
   End
   Begin VB.Label Label4 
      Alignment       =   1  'Right Justify
      Caption         =   "Field Names:"
      Height          =   255
      Left            =   120
      TabIndex        =   11
      Top             =   1080
      Width           =   1335
   End
   Begin VB.Label Label3 
      Alignment       =   1  'Right Justify
      Caption         =   "Database Name:"
      Height          =   255
      Left            =   0
      TabIndex        =   8
      Top             =   120
      Width           =   1455
   End
   Begin VB.Line Line1 
      BorderWidth     =   5
      X1              =   240
      X2              =   6240
      Y1              =   2640
      Y2              =   2640
   End
   Begin VB.Label Label2 
      Alignment       =   1  'Right Justify
      Caption         =   "Number Of Records:"
      Height          =   255
      Left            =   75
      TabIndex        =   3
      Top             =   600
      Width           =   1455
   End
   Begin VB.Label Label1 
      Alignment       =   1  'Right Justify
      Caption         =   "Number Of Fields:"
      Height          =   255
      Left            =   3360
      TabIndex        =   2
      Top             =   600
      Width           =   1455
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private m_strJobDatabase As String


Private Sub chkAddField_Click()
  If (chkAddField.Value) Then
     frmConvert.Enabled = True
     cmdConvertDatabase.Enabled = True
     EnableConvertFrame
     optIntegerDataType.SetFocus
     
     
  Else
     DisableConvertFrame
     DisableInitFrame
  
  End If
  
End Sub

Private Sub chkInitNewField_Click()
Dim strDataType As String

    EnableInitFrame
    
    If (optTextDataType.Value) Then
       txbNewValue = "Sample"
    ElseIf (optBooleanDataType.Value) Then
       txbNewValue = "True"
    ElseIf (optIntegerDataType.Value) Then
       txbNewValue = "0"
    End If
    
End Sub

Private Sub cmdConvertDatabase_Click()
Dim strDataType As String
    If (txbNewFieldName = "") Then
      MsgBox ("New Field Name Must Not Be Blanked")
      Exit Sub
    ElseIf (Not IsNumeric(txbLength)) Then
      MsgBox ("Field Length Must Be A Number")
      Exit Sub
    End If

    If (optTextDataType.Value) Then
       If txbLength = "" Then
         MsgBox ("Text Field Length Not Defined")
         Exit Sub
       End If
       strDataType = "Text"
    ElseIf (optBooleanDataType.Value) Then
       strDataType = "Boolean"
    ElseIf (optIntegerDataType.Value) Then
       strDataType = "Integer"
    Else
       MsgBox ("Must Define Data Type")
       Exit Sub
    End If
    
    If (dbCalls.AddDatabaseField(m_strJobDatabase, txbNewFieldName, strDataType, txbLength)) Then
         chkInitNewField.Enabled = True
         dbCalls.UpdateQueries m_strJobDatabase
    End If
    
    
End Sub

Private Sub cmdExit_Click()
  End
End Sub

Private Sub cmdSelectDatabase_Click()
Dim nIndex As Integer
DisableInitFrame
Dim strBuffer As String
  nIndex = 1
  dlgCommon.ShowOpen
  chkInitNewField.Enabled = False
  
  If (dlgCommon.filename <> "") Then
     m_strJobDatabase = dlgCommon.filename
     txbDatabaseName = m_strJobDatabase
     chkAddField.Enabled = True
     chkAddField.Value = False
     txbNewFieldName = ""
     txbNewValue = ""
     
  End If
  
  For nIndex = 1 To cmbFieldName.ListCount
     cmbFieldName.RemoveItem (0)
  Next
  nIndex = 1
  If m_strJobDatabase <> "" Then
    dbCalls.CollectDatabaseInfo m_strJobDatabase
    txbNumberOfRecords = dbCalls.GetNumberOfRecords
    txbNumberOfFields = Str(dbCalls.GetNumberOfFields(m_strJobDatabase))
    If (GetFieldNames(m_strJobDatabase)) Then
      nIndex = 1
      strBuffer = dbCalls.m_strFieldNames(nIndex)
      Do While (strBuffer <> "")
        cmbFieldName.AddItem strBuffer, nIndex - 1
        nIndex = nIndex + 1
        strBuffer = dbCalls.m_strFieldNames(nIndex)
      Loop
      cmbFieldName.Text = cmbFieldName.List(0)
    End If
  Else
    txbNumberOfRecords = ""
    txbNumberOfFields = ""
    txbDatabaseName = ""
  End If
  
End Sub

Private Sub cmdUpdate_Click()
  
  If optTextDataType Then
    If (Len(txbNewValue) <> Val(txbLength)) Then
       MsgBox ("Value has more characters than allowed")
       Exit Sub
    End If
  
  If txbNewValue <> "" Then
    If txbNewFieldName <> "" Then
       dbCalls.InitNewField m_strJobDatabase, txbNewFieldName, txbNewValue
    End If
  End If
 End If
End Sub

Private Sub Form_Load()
     DisableConvertFrame
     DisableInitFrame
     txbDatabaseName = ""
     chkAddField.Enabled = False
     chkInitNewField.Enabled = False
End Sub

Private Sub DisableConvertFrame()
    
    cmdConvertDatabase.Enabled = False
    frmConvert.Enabled = False
    optBooleanDataType.Enabled = False
    optTextDataType.Enabled = False
    optIntegerDataType.Enabled = False
    txbNewFieldName.Enabled = False
    lblLength.Enabled = False
    txbLength.Enabled = False

End Sub

Private Sub EnableConvertFrame()
    
    cmdConvertDatabase.Enabled = True
    frmConvert.Enabled = True
    optBooleanDataType.Enabled = True
    optTextDataType.Enabled = True
    optIntegerDataType.Enabled = True
    txbNewFieldName.Enabled = True
    
End Sub


Private Sub DisableInitFrame()
    
    cmdUpdate.Enabled = False
    frmDefValue.Enabled = False
    txbNewValue.Enabled = False
    lblUpdateName.Enabled = False

End Sub

Private Sub EnableInitFrame()
    
    cmdUpdate.Enabled = True
    frmDefValue.Enabled = True
    txbNewValue.Enabled = True
    lblUpdateName.Enabled = True

End Sub

Private Sub optTextDataType_Click()
    
  If optTextDataType Then
    lblLength.Enabled = True
    txbLength.Enabled = True
  Else
    lblLength.Enabled = False
    txbLength.Enabled = False
  End If
End Sub
