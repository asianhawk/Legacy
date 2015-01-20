VERSION 4.00
Begin VB.Form frmDBtemp2 
   Caption         =   "tblLabelerConfiguration"
   ClientHeight    =   4875
   ClientLeft      =   8790
   ClientTop       =   8130
   ClientWidth     =   5520
   Height          =   5280
   Left            =   8730
   LinkTopic       =   "Form1"
   ScaleHeight     =   4875
   ScaleWidth      =   5520
   Top             =   7785
   Width           =   5640
   Begin VB.Data dbcLabelerConfiguration 
      Align           =   2  'Align Bottom
      Caption         =   "LabelerConfiguration"
      Connect         =   ""
      DatabaseName    =   "S:\SoftwareDevelopment\Projects\Motorola_FL\Labeler\Labeler.mdb"
      Exclusive       =   0   'False
      Height          =   300
      Left            =   0
      Options         =   0
      ReadOnly        =   0   'False
      RecordsetType   =   1  'Dynaset
      RecordSource    =   "tblLabelerConfiguration"
      Top             =   4575
      Width           =   5520
   End
   Begin VB.TextBox txtFields 
      DataField       =   "txtEERotateDelay"
      DataSource      =   "dbcLabelerConfiguration"
      Height          =   285
      Index           =   12
      Left            =   2040
      TabIndex        =   23
      Top             =   3880
      Width           =   1935
   End
   Begin VB.TextBox txtFields 
      DataField       =   "lngExtendTimeOut"
      DataSource      =   "dbcLabelerConfiguration"
      Height          =   285
      Index           =   11
      Left            =   2040
      TabIndex        =   21
      Top             =   3560
      Width           =   1935
   End
   Begin VB.TextBox txtFields 
      DataField       =   "lngRetractTimeOut"
      DataSource      =   "dbcLabelerConfiguration"
      Height          =   285
      Index           =   10
      Left            =   2040
      TabIndex        =   19
      Top             =   3240
      Width           =   1935
   End
   Begin VB.TextBox txtFields 
      DataField       =   "lngMoveTimeOut"
      DataSource      =   "dbcLabelerConfiguration"
      Height          =   285
      Index           =   9
      Left            =   2040
      TabIndex        =   17
      Top             =   2920
      Width           =   1935
   End
   Begin VB.TextBox txtFields 
      DataField       =   "lngPickupTimeOut"
      DataSource      =   "dbcLabelerConfiguration"
      Height          =   285
      Index           =   8
      Left            =   2040
      TabIndex        =   15
      Top             =   2600
      Width           =   1935
   End
   Begin VB.TextBox txtFields 
      DataField       =   "lngScanTime"
      DataSource      =   "dbcLabelerConfiguration"
      Height          =   285
      Index           =   7
      Left            =   2040
      TabIndex        =   13
      Top             =   2280
      Width           =   1935
   End
   Begin VB.TextBox txtFields 
      DataField       =   "lngExtendTime"
      DataSource      =   "dbcLabelerConfiguration"
      Height          =   285
      Index           =   6
      Left            =   2040
      TabIndex        =   11
      Top             =   1960
      Width           =   1935
   End
   Begin VB.TextBox txtFields 
      DataField       =   "lngApplyDwellTime"
      DataSource      =   "dbcLabelerConfiguration"
      Height          =   285
      Index           =   5
      Left            =   2040
      TabIndex        =   9
      Top             =   1640
      Width           =   1935
   End
   Begin VB.TextBox txtFields 
      DataField       =   "lngDigitalInputOffset"
      DataSource      =   "dbcLabelerConfiguration"
      Height          =   285
      Index           =   4
      Left            =   2040
      TabIndex        =   7
      Top             =   1320
      Width           =   1935
   End
   Begin VB.TextBox txtFields 
      DataField       =   "lngDigitalOutputOffset"
      DataSource      =   "dbcLabelerConfiguration"
      Height          =   285
      Index           =   3
      Left            =   2040
      TabIndex        =   5
      Top             =   1000
      Width           =   1935
   End
   Begin VB.TextBox txtFields 
      DataField       =   "intInputScanRate"
      DataSource      =   "dbcLabelerConfiguration"
      Height          =   285
      Index           =   2
      Left            =   2040
      TabIndex        =   3
      Top             =   680
      Width           =   1935
   End
   Begin VB.TextBox txtFields 
      DataField       =   "strName"
      DataSource      =   "dbcLabelerConfiguration"
      Height          =   285
      Index           =   1
      Left            =   2040
      MaxLength       =   50
      TabIndex        =   1
      Top             =   360
      Width           =   1935
   End
   Begin VB.Label lblLabels 
      Alignment       =   1  'Right Justify
      Caption         =   "txtEERotateDelay:"
      Height          =   255
      Index           =   12
      Left            =   120
      TabIndex        =   22
      Top             =   3900
      Width           =   1815
   End
   Begin VB.Label lblLabels 
      Alignment       =   1  'Right Justify
      Caption         =   "lngExtendTimeOut:"
      Height          =   255
      Index           =   11
      Left            =   120
      TabIndex        =   20
      Top             =   3580
      Width           =   1815
   End
   Begin VB.Label lblLabels 
      Alignment       =   1  'Right Justify
      Caption         =   "lngRetractTimeOut:"
      Height          =   255
      Index           =   10
      Left            =   120
      TabIndex        =   18
      Top             =   3260
      Width           =   1815
   End
   Begin VB.Label lblLabels 
      Alignment       =   1  'Right Justify
      Caption         =   "lngMoveTimeOut:"
      Height          =   255
      Index           =   9
      Left            =   120
      TabIndex        =   16
      Top             =   2940
      Width           =   1815
   End
   Begin VB.Label lblLabels 
      Alignment       =   1  'Right Justify
      Caption         =   "lngPickupTimeOut:"
      Height          =   255
      Index           =   8
      Left            =   120
      TabIndex        =   14
      Top             =   2620
      Width           =   1815
   End
   Begin VB.Label lblLabels 
      Alignment       =   1  'Right Justify
      Caption         =   "lngScanTime:"
      Height          =   255
      Index           =   7
      Left            =   120
      TabIndex        =   12
      Top             =   2300
      Width           =   1815
   End
   Begin VB.Label lblLabels 
      Alignment       =   1  'Right Justify
      Caption         =   "lngExtendTime:"
      Height          =   255
      Index           =   6
      Left            =   120
      TabIndex        =   10
      Top             =   1980
      Width           =   1815
   End
   Begin VB.Label lblLabels 
      Alignment       =   1  'Right Justify
      Caption         =   "lngApplyDwellTime:"
      Height          =   255
      Index           =   5
      Left            =   120
      TabIndex        =   8
      Top             =   1660
      Width           =   1815
   End
   Begin VB.Label lblLabels 
      Alignment       =   1  'Right Justify
      Caption         =   "lngDigitalInputOffset:"
      Height          =   255
      Index           =   4
      Left            =   120
      TabIndex        =   6
      Top             =   1340
      Width           =   1815
   End
   Begin VB.Label lblLabels 
      Alignment       =   1  'Right Justify
      Caption         =   "lngDigitalOutputOffset:"
      Height          =   255
      Index           =   3
      Left            =   120
      TabIndex        =   4
      Top             =   1020
      Width           =   1815
   End
   Begin VB.Label lblLabels 
      Alignment       =   1  'Right Justify
      Caption         =   "intInputScanRate:"
      Height          =   255
      Index           =   2
      Left            =   120
      TabIndex        =   2
      Top             =   700
      Width           =   1815
   End
   Begin VB.Label lblLabels 
      Alignment       =   1  'Right Justify
      Caption         =   "strName:"
      Height          =   255
      Index           =   1
      Left            =   120
      TabIndex        =   0
      Top             =   380
      Width           =   1815
   End
End
Attribute VB_Name = "frmDBtemp2"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdAdd_Click()
  Data1.Recordset.AddNew
End Sub

Private Sub cmdDelete_Click()
  'this may produce an error if you delete the last
  'record or the only record in the recordset
  Data1.Recordset.Delete
  Data1.Recordset.MoveNext
End Sub

Private Sub cmdRefresh_Click()
  'this is really only needed for multi user apps
  Data1.Refresh
End Sub

Private Sub cmdUpdate_Click()
  Data1.UpdateRecord
  Data1.Recordset.Bookmark = Data1.Recordset.LastModified
End Sub

Private Sub cmdClose_Click()
  Unload Me
End Sub

Private Sub Data1_Error(DataErr As Integer, Response As Integer)
  'This is where you would put error handling code
  'If you want to ignore errors, comment out the next line
  'If you want to trap them, add code here to handle them
  MsgBox "Data error event hit err:" & Error$(DataErr)
  Response = 0  'throw away the error
End Sub

Private Sub Data1_Reposition()
  Screen.MousePointer = vbDefault
  On Error Resume Next
  'This will display the current record position
  'for dynasets and snapshots
  Data1.Caption = "Record: " & (Data1.Recordset.AbsolutePosition + 1)
  'for the table object you must set the index property when
  'the recordset gets created and use the following line
  'Data1.Caption = "Record: " & (Data1.Recordset.RecordCount * (Data1.Recordset.PercentPosition * 0.01)) + 1
End Sub

Private Sub Data1_Validate(Action As Integer, Save As Integer)
  'This is where you put validation code
  'This event gets called when the following actions occur
  Select Case Action
    Case vbDataActionMoveFirst
    Case vbDataActionMovePrevious
    Case vbDataActionMoveNext
    Case vbDataActionMoveLast
    Case vbDataActionAddNew
    Case vbDataActionUpdate
    Case vbDataActionDelete
    Case vbDataActionFind
    Case vbDataActionBookmark
    Case vbDataActionClose
  End Select
  Screen.MousePointer = vbHourglass
End Sub

