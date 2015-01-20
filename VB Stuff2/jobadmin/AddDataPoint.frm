VERSION 4.00
Begin VB.Form frmAddDataPoint 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "frmAddDataPoint"
   ClientHeight    =   2745
   ClientLeft      =   3630
   ClientTop       =   5865
   ClientWidth     =   4665
   ControlBox      =   0   'False
   Height          =   3150
   Left            =   3570
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2745
   ScaleWidth      =   4665
   ShowInTaskbar   =   0   'False
   Top             =   5520
   Width           =   4785
   Begin VB.TextBox txbName 
      Height          =   345
      Left            =   2160
      TabIndex        =   8
      Text            =   "txbName"
      Top             =   120
      Width           =   1215
   End
   Begin VB.ComboBox ddlThata 
      Height          =   315
      ItemData        =   "AddDataPoint.frx":0000
      Left            =   2205
      List            =   "AddDataPoint.frx":000A
      Style           =   2  'Dropdown List
      TabIndex        =   5
      Top             =   1530
      Width           =   945
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   495
      Left            =   2520
      TabIndex        =   7
      Top             =   2025
      Width           =   1335
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   495
      Left            =   705
      TabIndex        =   6
      Top             =   2025
      Width           =   1335
   End
   Begin VB.TextBox txbYAxis 
      Height          =   345
      Left            =   2160
      MaxLength       =   6
      TabIndex        =   3
      Text            =   "txbYAxis"
      Top             =   1050
      Width           =   1215
   End
   Begin VB.TextBox txbXAxis 
      Height          =   345
      Left            =   2160
      MaxLength       =   6
      TabIndex        =   1
      Text            =   "txbXAxis"
      Top             =   585
      Width           =   1215
   End
   Begin VB.Label labName 
      Alignment       =   1  'Right Justify
      Caption         =   "labName"
      Height          =   255
      Left            =   600
      TabIndex        =   9
      Top             =   120
      Width           =   1455
   End
   Begin VB.Label labThata 
      Alignment       =   1  'Right Justify
      Caption         =   "labThata"
      Height          =   255
      Left            =   600
      TabIndex        =   4
      Top             =   1530
      Width           =   1455
   End
   Begin VB.Label labYAxis 
      Alignment       =   1  'Right Justify
      Caption         =   "labYAxis"
      Height          =   255
      Left            =   600
      TabIndex        =   2
      Top             =   1050
      Width           =   1455
   End
   Begin VB.Label labXAxis 
      Alignment       =   1  'Right Justify
      Caption         =   "labXAxis"
      Height          =   255
      Left            =   600
      TabIndex        =   0
      Top             =   570
      Width           =   1455
   End
End
Attribute VB_Name = "frmAddDataPoint"
Attribute VB_Creatable = False
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

Private Sub cmdCancel_Click()

   Unload Me
   
End Sub 'cmdCancel_Click

Private Sub cmdOK_Click()

   'Send the data to the JobAdmin form
   
   frmJobFileAdmin.AddDataPoint _
            strName:=txbName.Text, _
            strXAxis:=txbXAxis.Text, _
            strYaxis:=txbYAxis.Text, _
            strThata:=ddlThata.Text
   
   Unload Me

End Sub 'cmdOK_Click

Private Sub Form_Load()

   ' Set up form
   m_strName = Me.Name
   CenterForm Me
   Me.Caption = LoadResString(resFORM_ADD_DATA_POINT)
   
   '  label the command buttons
   cmdOK.Caption = LoadResString(resCMD_OK)
   cmdCancel.Caption = LoadResString(resCMD_CANCEL)
   
   '  get captions for the labels
   labName.Caption = LoadResString(resLABEL_DATA_POINT_NAME)
   labXAxis.Caption = LoadResString(resLABEL_X_AXIS)
   labYAxis.Caption = LoadResString(resLABEL_Y_AXIS)
   labThata.Caption = LoadResString(resLABEL_THATA)
   
   '  Clear text boxes.
   txbName.Text = ""
   txbXAxis.Text = "0"
   txbYAxis.Text = "0"
   ddlThata.Text = "0"
   
   '  Status help text
   frmAddDataPoint.Tag = LoadResString(resSTMSG_ADD_DP)
   labName.Tag = LoadResString(resSTMSG_LABEL_NAME)
   txbName.Tag = LoadResString(resSTMSG_LABEL_NAME)
   labXAxis.Tag = LoadResString(resSTMSG_LABEL_X_AXIS)
   txbXAxis.Tag = LoadResString(resSTMSG_LABEL_X_AXIS)
   labYAxis.Tag = LoadResString(resSTMSG_LABEL_Y_AXIS)
   txbYAxis.Tag = LoadResString(resSTMSG_LABEL_Y_AXIS)
   labThata.Tag = LoadResString(resSTMSG_LABEL_THETA)
   ddlThata.Tag = LoadResString(resSTMSG_LABEL_THETA)
   cmdOK.Tag = LoadResString(resSTMSG_DP_OK)
   cmdCancel.Tag = LoadResString(resSTMSG_DP_CANCEL)
   
End Sub 'Form_Load


Private Sub Form_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   frmJobFileAdmin.stbHelp.SimpleText = frmAddDataPoint.Tag
End Sub 'Form_MouseMove


Private Sub labName_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   frmJobFileAdmin.stbHelp.SimpleText = labName.Tag
End Sub


Private Sub labXAxis_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   frmJobFileAdmin.stbHelp.SimpleText = labXAxis.Tag
End Sub 'labXAxis_MouseMove



Private Sub txbName_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   frmJobFileAdmin.stbHelp.SimpleText = txbName.Tag
End Sub 'txbName_MouseMove


Private Sub txbXAxis_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   frmJobFileAdmin.stbHelp.SimpleText = txbXAxis.Tag
End Sub 'txbXAxis_MouseMove


Private Sub labYAxis_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   frmJobFileAdmin.stbHelp.SimpleText = labYAxis.Tag
End Sub 'labYAxis_MouseMove


Private Sub txbYAxis_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   frmJobFileAdmin.stbHelp.SimpleText = txbYAxis.Tag
End Sub 'txbYAxis_MouseMove


Private Sub labThata_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   frmJobFileAdmin.stbHelp.SimpleText = labThata.Tag
End Sub 'labThata_MouseMove



Private Sub cmdOK_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   frmJobFileAdmin.stbHelp.SimpleText = cmdOK.Tag
End Sub 'cmdOK_MouseMove


Private Sub cmdCancel_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
   frmJobFileAdmin.stbHelp.SimpleText = cmdCancel.Tag
End Sub 'cmdCancel_MouseMove

Private Sub txbXAxis_KeyPress(KeyAscii As Integer)

   If Not (Chr(KeyAscii) Like "[0-9]") And _
      Not (Chr(KeyAscii) = vbBack) Then
      KeyAscii = 0
   End If

End Sub 'txbXAxis_KeyPress


Private Sub txbYAxis_KeyPress(KeyAscii As Integer)

   If Not (Chr(KeyAscii) Like "[0-9]") And _
      Not (Chr(KeyAscii) = vbBack) Then
      KeyAscii = 0
   End If

End Sub 'txbYAxis_KeyPress


