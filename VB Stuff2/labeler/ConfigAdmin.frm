VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "tabctl32.ocx"
Object = "{00028C01-0000-0000-0000-000000000046}#1.0#0"; "DBGRID32.OCX"
Object = "{0BA686C6-F7D3-101A-993E-0000C0EF6F5E}#1.0#0"; "threed32.ocx"
Object = "{FAEEE763-117E-101B-8933-08002B2F4F5A}#1.1#0"; "dblist32.ocx"
Begin VB.Form frmMain 
   Caption         =   "Configuration Administration"
   ClientHeight    =   5010
   ClientLeft      =   3750
   ClientTop       =   8580
   ClientWidth     =   8265
   Icon            =   "ConfigAdmin.frx":0000
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   5010
   ScaleWidth      =   8265
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   375
      Left            =   6360
      TabIndex        =   1
      Top             =   4560
      Width           =   1815
   End
   Begin TabDlg.SSTab sstConfiguration 
      Height          =   4455
      Left            =   0
      TabIndex        =   2
      Top             =   0
      Width           =   8235
      _ExtentX        =   14526
      _ExtentY        =   7858
      _Version        =   327681
      Style           =   1
      Tabs            =   4
      TabsPerRow      =   4
      TabHeight       =   529
      TabCaption(0)   =   "Configuration"
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "lblLabels(2)"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).Control(1)=   "lblLabels(3)"
      Tab(0).Control(1).Enabled=   0   'False
      Tab(0).Control(2)=   "lblLabels(4)"
      Tab(0).Control(2).Enabled=   0   'False
      Tab(0).Control(3)=   "lblLabels(5)"
      Tab(0).Control(3).Enabled=   0   'False
      Tab(0).Control(4)=   "lblLabels(6)"
      Tab(0).Control(4).Enabled=   0   'False
      Tab(0).Control(5)=   "lblLabels(7)"
      Tab(0).Control(5).Enabled=   0   'False
      Tab(0).Control(6)=   "lblLabels(8)"
      Tab(0).Control(6).Enabled=   0   'False
      Tab(0).Control(7)=   "lblLabels(9)"
      Tab(0).Control(7).Enabled=   0   'False
      Tab(0).Control(8)=   "lblLabels(10)"
      Tab(0).Control(8).Enabled=   0   'False
      Tab(0).Control(9)=   "lblLabels(11)"
      Tab(0).Control(9).Enabled=   0   'False
      Tab(0).Control(10)=   "lblLabels(12)"
      Tab(0).Control(10).Enabled=   0   'False
      Tab(0).Control(11)=   "cmdSaveConfig"
      Tab(0).Control(11).Enabled=   0   'False
      Tab(0).Control(12)=   "txtNameField"
      Tab(0).Control(12).Enabled=   0   'False
      Tab(0).Control(13)=   "txtFields(2)"
      Tab(0).Control(13).Enabled=   0   'False
      Tab(0).Control(14)=   "txtFields(3)"
      Tab(0).Control(14).Enabled=   0   'False
      Tab(0).Control(15)=   "txtFields(4)"
      Tab(0).Control(15).Enabled=   0   'False
      Tab(0).Control(16)=   "txtFields(5)"
      Tab(0).Control(16).Enabled=   0   'False
      Tab(0).Control(17)=   "txtFields(6)"
      Tab(0).Control(17).Enabled=   0   'False
      Tab(0).Control(18)=   "txtFields(7)"
      Tab(0).Control(18).Enabled=   0   'False
      Tab(0).Control(19)=   "txtFields(8)"
      Tab(0).Control(19).Enabled=   0   'False
      Tab(0).Control(20)=   "txtFields(9)"
      Tab(0).Control(20).Enabled=   0   'False
      Tab(0).Control(21)=   "txtFields(10)"
      Tab(0).Control(21).Enabled=   0   'False
      Tab(0).Control(22)=   "txtFields(11)"
      Tab(0).Control(22).Enabled=   0   'False
      Tab(0).Control(23)=   "txtFields(12)"
      Tab(0).Control(23).Enabled=   0   'False
      Tab(0).Control(24)=   "dbcLabelerConfiguration"
      Tab(0).Control(24).Enabled=   0   'False
      Tab(0).ControlCount=   25
      TabCaption(1)   =   "Serial Ports"
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "dbcSerialPortNames"
      Tab(1).Control(1)=   "cmdSavePortStuff"
      Tab(1).Control(2)=   "txbTxTerminatingChr"
      Tab(1).Control(3)=   "txbWatchDogTimer"
      Tab(1).Control(4)=   "txbDeviceName"
      Tab(1).Control(5)=   "dbcSerailPorts"
      Tab(1).Control(6)=   "SSFrame1"
      Tab(1).Control(7)=   "labSerialPortNames"
      Tab(1).Control(8)=   "dblSerialPortNames"
      Tab(1).Control(9)=   "Label3"
      Tab(1).Control(10)=   "labTxTerminatingChr"
      Tab(1).Control(11)=   "labWatchDogTimer"
      Tab(1).ControlCount=   12
      TabCaption(2)   =   "Digital Input"
      Tab(2).ControlEnabled=   0   'False
      Tab(2).Control(0)=   "cmdSaveInputs"
      Tab(2).Control(1)=   "dbc_quirDigitalInputsByBits"
      Tab(2).Control(2)=   "grd_quirDigitalInputsByBits"
      Tab(2).ControlCount=   3
      TabCaption(3)   =   "Digaital Output"
      Tab(3).ControlEnabled=   0   'False
      Tab(3).Control(0)=   "cmdSaveOutpus"
      Tab(3).Control(1)=   "dbc_qurDigitalOutputsByBits"
      Tab(3).Control(2)=   "grd_qurDigitalOutputsByBits"
      Tab(3).ControlCount=   3
      Begin VB.Data dbcLabelerConfiguration 
         Caption         =   "LabelerConfiguration"
         Connect         =   "Access"
         DatabaseName    =   "S:\SoftwareDevelopment\Projects\Motorola_FL\Labeler\Labeler.mdb"
         DefaultCursorType=   0  'DefaultCursor
         DefaultType     =   2  'UseODBC
         Exclusive       =   0   'False
         Height          =   360
         Left            =   2640
         Options         =   0
         ReadOnly        =   0   'False
         RecordsetType   =   1  'Dynaset
         RecordSource    =   "tblLabelerConfiguration"
         Top             =   2415
         Visible         =   0   'False
         Width           =   3855
      End
      Begin VB.TextBox txtFields 
         DataField       =   "txtEERotateDelay"
         DataSource      =   "dbcLabelerConfiguration"
         Height          =   285
         Index           =   12
         Left            =   6000
         TabIndex        =   47
         Top             =   1725
         Width           =   1935
      End
      Begin VB.TextBox txtFields 
         DataField       =   "lngExtendTimeOut"
         DataSource      =   "dbcLabelerConfiguration"
         Height          =   285
         Index           =   11
         Left            =   6000
         TabIndex        =   45
         Top             =   1395
         Width           =   1935
      End
      Begin VB.TextBox txtFields 
         DataField       =   "lngRetractTimeOut"
         DataSource      =   "dbcLabelerConfiguration"
         Height          =   285
         Index           =   10
         Left            =   6000
         TabIndex        =   43
         Top             =   1080
         Width           =   1935
      End
      Begin VB.TextBox txtFields 
         DataField       =   "lngMoveTimeOut"
         DataSource      =   "dbcLabelerConfiguration"
         Height          =   285
         Index           =   9
         Left            =   6000
         TabIndex        =   41
         Top             =   765
         Width           =   1935
      End
      Begin VB.TextBox txtFields 
         DataField       =   "lngPickupTimeOut"
         DataSource      =   "dbcLabelerConfiguration"
         Height          =   285
         Index           =   8
         Left            =   6000
         TabIndex        =   39
         Top             =   435
         Width           =   1935
      End
      Begin VB.TextBox txtFields 
         DataField       =   "lngScanTime"
         DataSource      =   "dbcLabelerConfiguration"
         Height          =   285
         Index           =   7
         Left            =   2040
         TabIndex        =   37
         Top             =   2040
         Width           =   1935
      End
      Begin VB.TextBox txtFields 
         DataField       =   "lngExtendTime"
         DataSource      =   "dbcLabelerConfiguration"
         Height          =   285
         Index           =   6
         Left            =   2040
         TabIndex        =   35
         Top             =   1725
         Width           =   1935
      End
      Begin VB.TextBox txtFields 
         DataField       =   "lngApplyDwellTime"
         DataSource      =   "dbcLabelerConfiguration"
         Height          =   285
         Index           =   5
         Left            =   2040
         TabIndex        =   33
         Top             =   1395
         Width           =   1935
      End
      Begin VB.TextBox txtFields 
         DataField       =   "lngDigitalInputOffset"
         DataSource      =   "dbcLabelerConfiguration"
         Height          =   285
         Index           =   4
         Left            =   2040
         TabIndex        =   31
         Top             =   1080
         Width           =   1935
      End
      Begin VB.TextBox txtFields 
         DataField       =   "lngDigitalOutputOffset"
         DataSource      =   "dbcLabelerConfiguration"
         Height          =   285
         Index           =   3
         Left            =   2040
         TabIndex        =   29
         Top             =   765
         Width           =   1935
      End
      Begin VB.TextBox txtFields 
         DataField       =   "intInputScanRate"
         DataSource      =   "dbcLabelerConfiguration"
         Height          =   285
         Index           =   2
         Left            =   2040
         TabIndex        =   27
         Top             =   435
         Width           =   1935
      End
      Begin VB.TextBox txtNameField 
         DataField       =   "strName"
         DataSource      =   "dbcLabelerConfiguration"
         Height          =   285
         Left            =   4860
         MaxLength       =   50
         TabIndex        =   25
         Top             =   2820
         Visible         =   0   'False
         Width           =   1935
      End
      Begin VB.CommandButton cmdSaveOutpus 
         Caption         =   "&Save"
         Height          =   375
         Left            =   -68340
         TabIndex        =   24
         Top             =   4020
         Width           =   1455
      End
      Begin VB.CommandButton cmdSaveInputs 
         Caption         =   "&Save"
         Height          =   375
         Left            =   -68340
         TabIndex        =   23
         Top             =   4020
         Width           =   1455
      End
      Begin VB.Data dbc_qurDigitalOutputsByBits 
         Caption         =   "DigitalOutputsByBits"
         Connect         =   "Access"
         DatabaseName    =   "S:\SoftwareDevelopment\Projects\Vitex\Labeler\Labeler.mdb"
         DefaultCursorType=   0  'DefaultCursor
         DefaultType     =   2  'UseODBC
         Exclusive       =   0   'False
         Height          =   375
         Left            =   -72960
         Options         =   0
         ReadOnly        =   0   'False
         RecordsetType   =   1  'Dynaset
         RecordSource    =   "qurDigitalOutputsByBits"
         Top             =   4020
         Visible         =   0   'False
         Width           =   4215
      End
      Begin VB.Data dbc_quirDigitalInputsByBits 
         Caption         =   "Digital Inputs By Bits"
         Connect         =   "Access"
         DatabaseName    =   "S:\SoftwareDevelopment\Projects\Vitex\Labeler\Labeler.mdb"
         DefaultCursorType=   0  'DefaultCursor
         DefaultType     =   2  'UseODBC
         Exclusive       =   0   'False
         Height          =   375
         Left            =   -72900
         Options         =   0
         ReadOnly        =   0   'False
         RecordsetType   =   1  'Dynaset
         RecordSource    =   "quirDigitalInputsByBits"
         Top             =   4020
         Visible         =   0   'False
         Width           =   4335
      End
      Begin VB.Data dbcSerialPortNames 
         Caption         =   "dbcSerialPortNames"
         Connect         =   "Access"
         DatabaseName    =   "C:\Projects\LucentTechnologiesMY\Labeler\Labeler.mdb"
         DefaultCursorType=   0  'DefaultCursor
         DefaultType     =   2  'UseODBC
         Exclusive       =   0   'False
         Height          =   345
         Left            =   -70575
         Options         =   3
         ReadOnly        =   0   'False
         RecordsetType   =   1  'Dynaset
         RecordSource    =   "tblSerialPortNames"
         Top             =   3000
         Visible         =   0   'False
         Width           =   1695
      End
      Begin VB.CommandButton cmdSavePortStuff 
         Caption         =   "&Save"
         Height          =   375
         Left            =   -68280
         TabIndex        =   18
         Top             =   3960
         Width           =   1455
      End
      Begin VB.TextBox txbTxTerminatingChr 
         DataField       =   "TxTerminatingChr"
         DataSource      =   "dbcSerailPorts"
         Height          =   285
         Left            =   -69765
         TabIndex        =   15
         Text            =   "TxTerminatingChr"
         Top             =   1350
         Width           =   750
      End
      Begin VB.TextBox txbWatchDogTimer 
         DataField       =   "WatchDogTimer"
         DataSource      =   "dbcSerailPorts"
         Height          =   285
         Left            =   -69765
         TabIndex        =   4
         Text            =   "WatchDogTimer"
         Top             =   795
         Width           =   750
      End
      Begin VB.TextBox txbDeviceName 
         DataField       =   "DeviceName"
         DataSource      =   "dbcSerailPorts"
         Height          =   300
         Left            =   -71775
         TabIndex        =   3
         Text            =   "txbDeviceName"
         Top             =   3000
         Visible         =   0   'False
         Width           =   1080
      End
      Begin VB.Data dbcSerailPorts 
         Caption         =   "dbcSerailPorts"
         Connect         =   "Access"
         DatabaseName    =   "C:\Projects\LucentTechnologiesMY\Labeler\Labeler.mdb"
         DefaultCursorType=   0  'DefaultCursor
         DefaultType     =   2  'UseODBC
         Exclusive       =   0   'False
         Height          =   360
         Left            =   -74895
         Options         =   3
         ReadOnly        =   0   'False
         RecordsetType   =   1  'Dynaset
         RecordSource    =   "tblSerialPortConfiguration"
         Top             =   3480
         Width           =   4200
      End
      Begin VB.CommandButton cmdSaveConfig 
         Caption         =   "&Save"
         Height          =   375
         Left            =   6720
         TabIndex        =   0
         Top             =   4020
         Width           =   1455
      End
      Begin Threed.SSFrame SSFrame1 
         Height          =   2055
         Left            =   -74790
         TabIndex        =   5
         Top             =   1215
         Width           =   2820
         _Version        =   65536
         _ExtentX        =   4974
         _ExtentY        =   3625
         _StockProps     =   14
         Caption         =   "Communications Parameters"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Begin VB.ComboBox ddlBaudRate 
            DataField       =   "BaudRate"
            DataSource      =   "dbcSerailPorts"
            Height          =   315
            ItemData        =   "ConfigAdmin.frx":0442
            Left            =   1080
            List            =   "ConfigAdmin.frx":044F
            Style           =   2  'Dropdown List
            TabIndex        =   9
            Top             =   300
            Width           =   1290
         End
         Begin VB.ComboBox ddlParity 
            DataField       =   "Parity"
            DataSource      =   "dbcSerailPorts"
            Height          =   315
            ItemData        =   "ConfigAdmin.frx":0465
            Left            =   1080
            List            =   "ConfigAdmin.frx":0472
            Style           =   2  'Dropdown List
            TabIndex        =   8
            Top             =   720
            Width           =   750
         End
         Begin VB.ComboBox ddlDataBits 
            DataField       =   "DataBits"
            DataSource      =   "dbcSerailPorts"
            Height          =   315
            ItemData        =   "ConfigAdmin.frx":047F
            Left            =   1080
            List            =   "ConfigAdmin.frx":0489
            Style           =   2  'Dropdown List
            TabIndex        =   7
            Top             =   1110
            Width           =   750
         End
         Begin VB.ComboBox ddlStopBits 
            DataField       =   "StopBits"
            DataSource      =   "dbcSerailPorts"
            Height          =   315
            ItemData        =   "ConfigAdmin.frx":0493
            Left            =   1080
            List            =   "ConfigAdmin.frx":049D
            Style           =   2  'Dropdown List
            TabIndex        =   6
            Top             =   1500
            Width           =   735
         End
         Begin VB.Label lsbBaudRate 
            Alignment       =   1  'Right Justify
            AutoSize        =   -1  'True
            Caption         =   "Baud Rate:"
            Height          =   195
            Left            =   225
            TabIndex        =   13
            Top             =   300
            Width           =   810
         End
         Begin VB.Label labParity 
            Alignment       =   1  'Right Justify
            AutoSize        =   -1  'True
            Caption         =   "Parity:"
            Height          =   195
            Left            =   570
            TabIndex        =   12
            Top             =   720
            Width           =   435
         End
         Begin VB.Label labDataBits 
            Alignment       =   1  'Right Justify
            AutoSize        =   -1  'True
            Caption         =   "Data Bits:"
            Height          =   195
            Left            =   315
            TabIndex        =   11
            Top             =   1110
            Width           =   690
         End
         Begin VB.Label labStopBits 
            Alignment       =   1  'Right Justify
            AutoSize        =   -1  'True
            Caption         =   "Stop Bits:"
            Height          =   195
            Left            =   315
            TabIndex        =   10
            Top             =   1500
            Width           =   675
         End
      End
      Begin MSDBGrid.DBGrid grd_qurDigitalOutputsByBits 
         Bindings        =   "ConfigAdmin.frx":04A7
         Height          =   3555
         Left            =   -74940
         OleObjectBlob   =   "ConfigAdmin.frx":04CD
         TabIndex        =   22
         Top             =   420
         Width           =   8175
      End
      Begin MSDBGrid.DBGrid grd_quirDigitalInputsByBits 
         Bindings        =   "ConfigAdmin.frx":1730
         Height          =   3555
         Left            =   -74940
         OleObjectBlob   =   "ConfigAdmin.frx":1756
         TabIndex        =   21
         Top             =   420
         Width           =   8055
      End
      Begin MSDBCtls.DBCombo dblSerialPortNames 
         Bindings        =   "ConfigAdmin.frx":265D
         DataField       =   "PortNameID"
         DataSource      =   "dbcSerailPorts"
         Height          =   315
         Left            =   -74265
         TabIndex        =   19
         Top             =   750
         Width           =   2295
         _ExtentX        =   4048
         _ExtentY        =   556
         _Version        =   327681
         Style           =   2
         BackColor       =   16777215
         ForeColor       =   0
         ListField       =   "PortName"
         BoundColumn     =   "PortNameID"
         Text            =   "dblSerialPortNames"
      End
      Begin VB.Label lblLabels 
         Alignment       =   1  'Right Justify
         Caption         =   "txtEERotateDelay:"
         Height          =   255
         Index           =   12
         Left            =   4080
         TabIndex        =   46
         Top             =   1740
         Width           =   1815
      End
      Begin VB.Label lblLabels 
         Alignment       =   1  'Right Justify
         Caption         =   "lngExtendTimeOut:"
         Height          =   255
         Index           =   11
         Left            =   4080
         TabIndex        =   44
         Top             =   1425
         Width           =   1815
      End
      Begin VB.Label lblLabels 
         Alignment       =   1  'Right Justify
         Caption         =   "lngRetractTimeOut:"
         Height          =   255
         Index           =   10
         Left            =   4080
         TabIndex        =   42
         Top             =   1095
         Width           =   1815
      End
      Begin VB.Label lblLabels 
         Alignment       =   1  'Right Justify
         Caption         =   "lngMoveTimeOut:"
         Height          =   255
         Index           =   9
         Left            =   4080
         TabIndex        =   40
         Top             =   780
         Width           =   1815
      End
      Begin VB.Label lblLabels 
         Alignment       =   1  'Right Justify
         Caption         =   "lngPickupTimeOut:"
         Height          =   255
         Index           =   8
         Left            =   4080
         TabIndex        =   38
         Top             =   465
         Width           =   1815
      End
      Begin VB.Label lblLabels 
         Alignment       =   1  'Right Justify
         Caption         =   "lngScanTime:"
         Height          =   255
         Index           =   7
         Left            =   120
         TabIndex        =   36
         Top             =   2055
         Width           =   1815
      End
      Begin VB.Label lblLabels 
         Alignment       =   1  'Right Justify
         Caption         =   "lngExtendTime:"
         Height          =   255
         Index           =   6
         Left            =   120
         TabIndex        =   34
         Top             =   1740
         Width           =   1815
      End
      Begin VB.Label lblLabels 
         Alignment       =   1  'Right Justify
         Caption         =   "lngApplyDwellTime:"
         Height          =   255
         Index           =   5
         Left            =   120
         TabIndex        =   32
         Top             =   1425
         Width           =   1815
      End
      Begin VB.Label lblLabels 
         Alignment       =   1  'Right Justify
         Caption         =   "lngDigitalInputOffset:"
         Height          =   255
         Index           =   4
         Left            =   120
         TabIndex        =   30
         Top             =   1095
         Width           =   1815
      End
      Begin VB.Label lblLabels 
         Alignment       =   1  'Right Justify
         Caption         =   "lngDigitalOutputOffset:"
         Height          =   255
         Index           =   3
         Left            =   120
         TabIndex        =   28
         Top             =   780
         Width           =   1815
      End
      Begin VB.Label lblLabels 
         Alignment       =   1  'Right Justify
         Caption         =   "intInputScanRate:"
         Height          =   255
         Index           =   2
         Left            =   120
         TabIndex        =   26
         Top             =   465
         Width           =   1815
      End
      Begin VB.Label labSerialPortNames 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Name:"
         Height          =   195
         Left            =   -74730
         TabIndex        =   20
         Top             =   750
         Width           =   465
      End
      Begin VB.Label Label3 
         Caption         =   "[ASCII character used to terminate a incoming string on this port.  Use \n for CRLF, \h### for hex number for a control code.]"
         Height          =   870
         Left            =   -71670
         TabIndex        =   17
         Top             =   1665
         Width           =   2610
      End
      Begin VB.Label labTxTerminatingChr 
         Alignment       =   1  'Right Justify
         Caption         =   "Received string terminating character: "
         Height          =   510
         Left            =   -71910
         MousePointer    =   1  'Arrow
         TabIndex        =   16
         Top             =   1305
         Width           =   2145
         WordWrap        =   -1  'True
      End
      Begin VB.Label labWatchDogTimer 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Watch Dog Timer (sec):"
         Height          =   195
         Left            =   -71475
         MousePointer    =   1  'Arrow
         TabIndex        =   14
         Top             =   795
         Width           =   1695
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


Private Sub cmdExit_Click()

   End
   
End Sub 'cmdExit_Click


Private Sub cmdSaveConfig_Click()

   dbcLabelerConfiguration.UpdateRecord
   
End Sub 'cmdSaveConfig_Click


Private Sub cmdSaveInputs_Click()

   dbc_quirDigitalInputsByBits.UpdateRecord
   
End Sub 'cmdSaveInputs_Click

Private Sub cmdSaveOutpus_Click()

   dbc_qurDigitalOutputsByBits.UpdateRecord
   
End Sub 'cmdSaveOutpus_Click


Private Sub cmdSavePortStuff_Click()

   
   '  turn off error trapping
   On Error Resume Next
   dbcSerailPorts.UpdateRecord
   '  Is there a duplicate field value
   '  where one should not be ...
   If Err.Number = 524 Then
     modError.ReportError "cmdSavePortStuff_Click", Name, Err.Number, Err.Description
   ElseIf Err.Number <> 0 Then
     modError.ProccessError "cmdSavePortStuff_Click", Name, Err.Number, Err.Description
   End If
   On Error GoTo 0

End Sub 'cmdSavePortStuff_Click


Private Sub dbcConfiguration_Validate(Action As Integer, Save As Integer)

End Sub

Private Sub dbcSerailPorts_Reposition()

   dbcSerailPorts.Caption = txbDeviceName.Text
   
End Sub 'dbcSerailPorts_Reposition




Private Sub DBGrid1_Click()

End Sub


Private Sub Form_Load()

   frmMessage.Hide
   
   g_blnTest = False
   
   CenterForm Me
      
   dbcLabelerConfiguration.DatabaseName = App.Path & "\Labeler.mdb"
   dbcSerailPorts.DatabaseName = App.Path & "\Labeler.mdb"
   dbcSerialPortNames.DatabaseName = App.Path & "\Labeler.mdb"
   dbc_quirDigitalInputsByBits.DatabaseName = App.Path & "\Labeler.mdb"
   dbc_qurDigitalOutputsByBits.DatabaseName = App.Path & "\Labeler.mdb"
   
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




Private Sub txbWatchDogTimer_KeyPress(KeyAscii As Integer)

   If Not (Chr(KeyAscii) Like "[0-9]") And Not (Chr(KeyAscii) = vbBack) Then
      KeyAscii = 0
   End If

End Sub 'txbWatchDogTimer_KeyPress




Private Sub txtNameField_Change()

      With frmMain
      .Caption = .Caption & " [" & txtNameField.Text & "]"
   End With 'frmMain
   
End Sub 'txtNameField_Change


