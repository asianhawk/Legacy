VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.1#0"; "COMDLG32.OCX"
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "COMCTL32.OCX"
Object = "{0BA686C6-F7D3-101A-993E-0000C0EF6F5E}#1.0#0"; "THREED32.OCX"
Begin VB.Form frmMain 
   AutoRedraw      =   -1  'True
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "frmMain"
   ClientHeight    =   6630
   ClientLeft      =   1035
   ClientTop       =   1425
   ClientWidth     =   9660
   Icon            =   "Main.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   6630
   ScaleWidth      =   9660
   ShowInTaskbar   =   0   'False
   Begin Threed.SSPanel sspLabelingInfo 
      Align           =   4  'Align Right
      Height          =   6180
      Left            =   4035
      TabIndex        =   0
      Top             =   0
      Width           =   5625
      _Version        =   65536
      _ExtentX        =   9922
      _ExtentY        =   10901
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
      BorderWidth     =   1
      BevelInner      =   1
      Begin Threed.SSFrame ssfLastlabel 
         Height          =   1335
         Left            =   360
         TabIndex        =   10
         Top             =   2880
         Width           =   5205
         _Version        =   65536
         _ExtentX        =   9181
         _ExtentY        =   2355
         _StockProps     =   14
         Caption         =   "ssfLastlabel"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Begin VB.Label labPrinted 
            Alignment       =   1  'Right Justify
            AutoSize        =   -1  'True
            Caption         =   "labPrinted"
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   300
            Left            =   1290
            TabIndex        =   14
            Top             =   420
            Width           =   1230
         End
         Begin VB.Label labTextPrinted 
            BackColor       =   &H00FFFFFF&
            BorderStyle     =   1  'Fixed Single
            Caption         =   "labTextPartNumber"
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   345
            Left            =   2580
            TabIndex        =   13
            Top             =   405
            Width           =   2310
         End
         Begin VB.Label labTextScanned 
            BackColor       =   &H00FFFFFF&
            BorderStyle     =   1  'Fixed Single
            Caption         =   "labTextSeqPrinted"
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   345
            Left            =   2580
            TabIndex        =   12
            Top             =   795
            Width           =   2310
         End
         Begin VB.Label labScaned 
            Alignment       =   1  'Right Justify
            AutoSize        =   -1  'True
            Caption         =   "labScaned"
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   300
            Left            =   1200
            TabIndex        =   11
            Top             =   780
            Width           =   1290
         End
      End
      Begin VB.Label lblRunTimeMode 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         Caption         =   "Normal"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   435
         Left            =   2880
         TabIndex        =   58
         Top             =   2520
         Width           =   2280
      End
      Begin VB.Label lblMode 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Mode:"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   300
         Left            =   1950
         TabIndex        =   56
         Top             =   2520
         Width           =   750
      End
      Begin VB.Label lblDHolePattern 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   2880
         TabIndex        =   54
         Top             =   1680
         Width           =   2295
      End
      Begin VB.Label lblHPattern 
         Caption         =   "Hole Pattern(Sensors):"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   120
         TabIndex        =   53
         Top             =   1680
         Width           =   2775
      End
      Begin VB.Label Label2 
         Caption         =   "Hole Pattern (Job):"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   600
         TabIndex        =   52
         Top             =   1320
         Width           =   2295
      End
      Begin VB.Label lblHolePattern 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   2880
         TabIndex        =   50
         Top             =   1320
         Width           =   2295
      End
      Begin VB.Label lblFlavor 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   345
         Left            =   2880
         TabIndex        =   49
         Top             =   960
         Width           =   2280
      End
      Begin VB.Label Label1 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "Flavor:"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   300
         Left            =   1995
         TabIndex        =   48
         Top             =   960
         Width           =   825
      End
      Begin VB.Label labMessages 
         BackColor       =   &H00C0C0C0&
         Caption         =   "labMessages(1)"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   13.5
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000000FF&
         Height          =   360
         Index           =   1
         Left            =   240
         TabIndex        =   20
         Top             =   4320
         Width           =   5265
      End
      Begin VB.Label labTextPartNumber 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         Caption         =   "labTextPartNumber"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   345
         Left            =   2895
         TabIndex        =   26
         Top             =   600
         Width           =   2280
      End
      Begin VB.Label labPartNumber 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "labPartNumber"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   300
         Left            =   1020
         TabIndex        =   25
         Top             =   645
         Width           =   1800
      End
      Begin VB.Label labMessages 
         BackColor       =   &H00C0C0C0&
         Caption         =   "labMessages(5)"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   13.5
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000000FF&
         Height          =   360
         Index           =   5
         Left            =   240
         TabIndex        =   24
         Top             =   5760
         Width           =   5265
      End
      Begin VB.Label labMessages 
         BackColor       =   &H00C0C0C0&
         Caption         =   "labMessages(4)"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   13.5
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000000FF&
         Height          =   360
         Index           =   4
         Left            =   240
         TabIndex        =   23
         Top             =   5400
         Width           =   5265
      End
      Begin VB.Label labMessages 
         BackColor       =   &H00C0C0C0&
         Caption         =   "labMessages(3)"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   13.5
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000000FF&
         Height          =   360
         Index           =   3
         Left            =   240
         TabIndex        =   22
         Top             =   5040
         Width           =   5265
      End
      Begin VB.Label labMessages 
         BackColor       =   &H00C0C0C0&
         Caption         =   "labMessages(2)"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   13.5
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000000FF&
         Height          =   360
         Index           =   2
         Left            =   240
         TabIndex        =   21
         Top             =   4680
         Width           =   5265
      End
      Begin VB.Label labQuantity 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "labQuantity"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   300
         Left            =   1320
         TabIndex        =   17
         Top             =   2160
         Width           =   1380
      End
      Begin VB.Label labTextQuantity 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         Caption         =   "labTextQuantity"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   435
         Left            =   2880
         TabIndex        =   16
         Top             =   2040
         Width           =   2280
      End
      Begin VB.Label labTextJobName 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
         Caption         =   "labTextJobName"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   360
         Left            =   2880
         TabIndex        =   8
         Top             =   240
         Width           =   2325
      End
      Begin VB.Label labJobName 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         Caption         =   "labJobName"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   300
         Left            =   1200
         TabIndex        =   3
         Top             =   240
         Width           =   1560
      End
   End
   Begin VB.Timer tmrRetractTimeOut 
      Left            =   3120
      Top             =   1200
   End
   Begin VB.Timer tmrPickupTimeOut 
      Left            =   2640
      Top             =   1200
   End
   Begin Threed.SSPanel sspToolBar 
      Align           =   3  'Align Left
      Height          =   6180
      Left            =   0
      TabIndex        =   2
      Top             =   0
      Width           =   2490
      _Version        =   65536
      _ExtentX        =   4392
      _ExtentY        =   10901
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
      BorderWidth     =   1
      BevelInner      =   1
      Begin VB.CommandButton cmdPartPresent 
         Caption         =   "Part Present"
         Height          =   375
         Left            =   600
         TabIndex        =   55
         Top             =   5400
         Visible         =   0   'False
         Width           =   1575
      End
      Begin Threed.SSPanel sspRunJob 
         Height          =   1275
         Left            =   60
         TabIndex        =   4
         Top             =   1305
         Width           =   2355
         _Version        =   65536
         _ExtentX        =   4154
         _ExtentY        =   2249
         _StockProps     =   15
         Caption         =   "sspRunJob"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Alignment       =   8
         Autosize        =   3
         Begin Threed.SSCommand sscRunJob 
            Height          =   1185
            Left            =   45
            TabIndex        =   9
            Top             =   45
            Width           =   2265
            _Version        =   65536
            _ExtentX        =   3995
            _ExtentY        =   2090
            _StockProps     =   78
            Caption         =   "sscRunJob"
            BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
               Name            =   "MS Sans Serif"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Enabled         =   0   'False
            Picture         =   "Main.frx":0442
         End
      End
      Begin Threed.SSPanel sspOpenJob 
         Height          =   1275
         Left            =   60
         TabIndex        =   5
         Top             =   60
         Width           =   2355
         _Version        =   65536
         _ExtentX        =   4154
         _ExtentY        =   2249
         _StockProps     =   15
         Caption         =   "sspOpenJob"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Autosize        =   3
         Begin Threed.SSCommand sscOpenJob 
            Height          =   1185
            Left            =   45
            TabIndex        =   51
            Top             =   45
            Width           =   2265
            _Version        =   65536
            _ExtentX        =   3995
            _ExtentY        =   2090
            _StockProps     =   78
            Caption         =   "sscOpenJob"
            BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
               Name            =   "MS Sans Serif"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Picture         =   "Main.frx":1034
         End
      End
      Begin Threed.SSPanel sspExit 
         Height          =   1275
         Left            =   60
         TabIndex        =   6
         Top             =   3840
         Width           =   2355
         _Version        =   65536
         _ExtentX        =   4154
         _ExtentY        =   2249
         _StockProps     =   15
         Caption         =   "sspExit"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Autosize        =   3
         Begin Threed.SSCommand sscExit 
            Height          =   1185
            Left            =   45
            TabIndex        =   7
            Top             =   45
            Width           =   2265
            _Version        =   65536
            _ExtentX        =   3995
            _ExtentY        =   2090
            _StockProps     =   78
            Caption         =   "sscExit"
            BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
               Name            =   "MS Sans Serif"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Picture         =   "Main.frx":16AE
         End
      End
      Begin Threed.SSPanel SSPanel1 
         Height          =   1275
         Left            =   60
         TabIndex        =   18
         Top             =   2580
         Width           =   2355
         _Version        =   65536
         _ExtentX        =   4154
         _ExtentY        =   2249
         _StockProps     =   15
         Caption         =   "sspRunJob"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Alignment       =   8
         Autosize        =   3
         Begin Threed.SSCommand sscManualFeed 
            Height          =   1185
            Left            =   45
            TabIndex        =   19
            Top             =   45
            Width           =   2265
            _Version        =   65536
            _ExtentX        =   3995
            _ExtentY        =   2090
            _StockProps     =   78
            Caption         =   "sscManualFeed"
            BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
               Name            =   "MS Sans Serif"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Enabled         =   0   'False
            Picture         =   "Main.frx":1940
         End
      End
      Begin VB.Label labInstructions 
         Caption         =   "labInstructions"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   855
         Left            =   120
         TabIndex        =   15
         Top             =   6480
         Width           =   2265
         WordWrap        =   -1  'True
      End
   End
   Begin Threed.SSPanel sspConfiguration 
      Height          =   4395
      Left            =   2640
      TabIndex        =   27
      Top             =   1740
      Visible         =   0   'False
      Width           =   2115
      _Version        =   65536
      _ExtentX        =   3731
      _ExtentY        =   7752
      _StockProps     =   15
      Caption         =   "sspConfiguration"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Alignment       =   0
      Begin VB.TextBox txbEERotateDelay 
         DataField       =   "txtEERotateDelay"
         DataSource      =   "dbcLabelerConfiguration"
         Height          =   285
         Left            =   180
         TabIndex        =   42
         Text            =   "txbEERotateDelay"
         Top             =   2940
         Width           =   1755
      End
      Begin VB.Data dbcLabelerConfiguration 
         Caption         =   "dbcLabelerConfiguration"
         Connect         =   "Access"
         DatabaseName    =   "C:\Ford Markam\labeler\Labeler.mdb"
         DefaultCursorType=   0  'DefaultCursor
         DefaultType     =   2  'UseODBC
         Exclusive       =   0   'False
         Height          =   345
         Left            =   120
         Options         =   0
         ReadOnly        =   0   'False
         RecordsetType   =   1  'Dynaset
         RecordSource    =   "tblLabelerConfiguration"
         Top             =   3840
         Width           =   1755
      End
      Begin VB.TextBox txbName 
         DataField       =   "strName"
         DataSource      =   "dbcLabelerConfiguration"
         Height          =   285
         Left            =   180
         TabIndex        =   36
         Text            =   "txbName"
         Top             =   240
         Width           =   1755
      End
      Begin VB.TextBox txbApplyDwellTime 
         DataField       =   "lngApplyDwellTime"
         DataSource      =   "dbcLabelerConfiguration"
         Height          =   285
         Left            =   180
         TabIndex        =   35
         Text            =   "txbApplyDwellTime"
         Top             =   840
         Width           =   1755
      End
      Begin VB.TextBox txbInputScanRate 
         DataField       =   "intInputScanRate"
         DataSource      =   "dbcLabelerConfiguration"
         Height          =   285
         Left            =   180
         TabIndex        =   34
         Text            =   "txbInputScanRate"
         Top             =   540
         Width           =   1755
      End
      Begin VB.TextBox txbExtendTime 
         DataField       =   "lngExtendTime"
         DataSource      =   "dbcLabelerConfiguration"
         Height          =   285
         Left            =   180
         TabIndex        =   33
         Text            =   "txbExtendTime"
         Top             =   1140
         Width           =   1755
      End
      Begin VB.TextBox txbScanTime 
         DataField       =   "lngScanTime"
         DataSource      =   "dbcLabelerConfiguration"
         Height          =   285
         Left            =   180
         TabIndex        =   32
         Text            =   "txbScanTime"
         Top             =   1440
         Width           =   1755
      End
      Begin VB.TextBox txbRetractTimeOut 
         DataField       =   "lngRetractTimeOut"
         DataSource      =   "dbcLabelerConfiguration"
         Height          =   285
         Left            =   180
         TabIndex        =   31
         Text            =   "txbRetractTimeOut"
         Top             =   2340
         Width           =   1755
      End
      Begin VB.TextBox txbPickupTimeOut 
         DataField       =   "lngPickupTimeOut"
         DataSource      =   "dbcLabelerConfiguration"
         Height          =   285
         Left            =   180
         TabIndex        =   30
         Text            =   "txbPickupTimeOut"
         Top             =   1740
         Width           =   1755
      End
      Begin VB.TextBox txbMoveTimeOut 
         DataField       =   "lngMoveTimeOut"
         DataSource      =   "dbcLabelerConfiguration"
         Height          =   285
         Left            =   180
         TabIndex        =   29
         Text            =   "txbMoveTimeOut"
         Top             =   2040
         Width           =   1755
      End
      Begin VB.TextBox txbExtendTimeOut 
         DataField       =   "lngExtendTimeOut"
         DataSource      =   "dbcLabelerConfiguration"
         Height          =   285
         Left            =   180
         TabIndex        =   28
         Text            =   "txbExtendTimeOut"
         Top             =   2640
         Width           =   1755
      End
   End
   Begin Threed.SSPanel sspJobCommon 
      Height          =   4035
      Left            =   4800
      TabIndex        =   37
      Top             =   1500
      Width           =   1875
      _Version        =   65536
      _ExtentX        =   3307
      _ExtentY        =   7117
      _StockProps     =   15
      Caption         =   "sspJobCommon"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Alignment       =   0
      Begin VB.TextBox txbLogFileDlim 
         DataField       =   "chrLogFileDlim"
         DataSource      =   "dbcCommon"
         Height          =   285
         Left            =   60
         TabIndex        =   47
         Text            =   "chrLogFileDlim"
         Top             =   2640
         Width           =   1755
      End
      Begin VB.TextBox txbKitFileDlim 
         DataField       =   "chrKitFileDlim"
         DataSource      =   "dbcCommon"
         Height          =   285
         Left            =   60
         TabIndex        =   46
         Text            =   "chrKitFileDlim"
         Top             =   2340
         Width           =   1755
      End
      Begin VB.TextBox txbLogFileName 
         DataField       =   "txtLogFileName"
         DataSource      =   "dbcCommon"
         Height          =   285
         Left            =   60
         TabIndex        =   45
         Text            =   "txtLogFileName"
         Top             =   1740
         Width           =   1755
      End
      Begin VB.TextBox txbKitFileName 
         DataField       =   "txtKitFileName"
         DataSource      =   "dbcCommon"
         Height          =   285
         Left            =   60
         TabIndex        =   44
         Text            =   "txtKitFileName"
         Top             =   1140
         Width           =   1755
      End
      Begin VB.TextBox txbKitFilePath 
         DataField       =   "txtKitFilePath"
         DataSource      =   "dbcCommon"
         Height          =   285
         Left            =   60
         TabIndex        =   43
         Text            =   "txtKitFilePath"
         Top             =   1440
         Width           =   1755
      End
      Begin VB.TextBox txbScanTries 
         DataField       =   "intScanTries"
         DataSource      =   "dbcCommon"
         Height          =   285
         Left            =   60
         TabIndex        =   41
         Text            =   "txbScanTries"
         Top             =   840
         Width           =   1755
      End
      Begin VB.TextBox txbLogFilePath 
         DataField       =   "txtLogFilePath"
         DataSource      =   "dbcCommon"
         Height          =   285
         Left            =   60
         TabIndex        =   40
         Text            =   "txtLogFilePath"
         Top             =   2040
         Width           =   1755
      End
      Begin VB.TextBox txtNameJobs 
         DataField       =   "txtName"
         DataSource      =   "dbcCommon"
         Height          =   285
         Left            =   60
         TabIndex        =   39
         Text            =   "txtNameJobs"
         Top             =   240
         Width           =   1755
      End
      Begin VB.TextBox txbLineCode 
         DataField       =   "chrLineCode"
         DataSource      =   "dbcCommon"
         Height          =   285
         Left            =   60
         TabIndex        =   38
         Text            =   "txbLineCode"
         Top             =   540
         Width           =   1755
      End
      Begin VB.Data dbcCommon 
         Caption         =   "dbcCommon"
         Connect         =   "Access"
         DatabaseName    =   "C:\Ford Markam\Labeler\Jobs.mdb"
         DefaultCursorType=   0  'DefaultCursor
         DefaultType     =   2  'UseODBC
         Exclusive       =   0   'False
         Height          =   345
         Left            =   120
         Options         =   0
         ReadOnly        =   0   'False
         RecordsetType   =   1  'Dynaset
         RecordSource    =   "tblCommon"
         Top             =   3240
         Width           =   1755
      End
   End
   Begin MSComDlg.CommonDialog cdlHelp 
      Left            =   2580
      Top             =   540
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327681
      DialogTitle     =   "Labeler Help"
      HelpFile        =   "Labler.hlp"
   End
   Begin MSComDlg.CommonDialog cdlOpenJobDB 
      Left            =   2520
      Top             =   60
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327681
      DialogTitle     =   "cdbOpenJobDB"
   End
   Begin ComctlLib.StatusBar stbStatus 
      Align           =   2  'Align Bottom
      Height          =   450
      Left            =   0
      TabIndex        =   1
      Top             =   6180
      Width           =   9660
      _ExtentX        =   17039
      _ExtentY        =   794
      Style           =   1
      SimpleText      =   "stbStatus"
      _Version        =   327682
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   1
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Object.Tag             =   ""
         EndProperty
      EndProperty
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin VB.Label Label3 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "labTextQuantity"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   435
      Left            =   0
      TabIndex        =   57
      Top             =   0
      Width           =   2280
   End
   Begin VB.Image imgLablerRunning 
      Height          =   465
      Left            =   3120
      Picture         =   "Main.frx":1FBA
      Top             =   60
      Visible         =   0   'False
      Width           =   480
   End
   Begin VB.Image imgLablerInterrupted 
      Height          =   510
      Left            =   4440
      Picture         =   "Main.frx":2B9C
      Top             =   0
      Visible         =   0   'False
      Width           =   525
   End
   Begin VB.Image imgLablerIdle 
      Height          =   465
      Left            =   3720
      Picture         =   "Main.frx":3A36
      Top             =   600
      Visible         =   0   'False
      Width           =   480
   End
   Begin VB.Image imgLablerDisabled 
      Height          =   510
      Left            =   3120
      Picture         =   "Main.frx":4618
      Top             =   540
      Visible         =   0   'False
      Width           =   525
   End
   Begin VB.Image imgLablerComplete 
      Height          =   465
      Left            =   3720
      Picture         =   "Main.frx":54B2
      Top             =   60
      Visible         =   0   'False
      Width           =   480
   End
   Begin VB.Menu mnuFile 
      Caption         =   "mnuFile"
      Begin VB.Menu mnuFileOpen 
         Caption         =   "mnuFileOpen"
         Shortcut        =   {F2}
      End
      Begin VB.Menu mnuFileOpenJobFile 
         Caption         =   "mnuOpenJobFile"
         Shortcut        =   {F4}
      End
      Begin VB.Menu mnuFileExit 
         Caption         =   "mnuFileExit"
      End
   End
   Begin VB.Menu mnuRun 
      Caption         =   "mnuRun"
      Enabled         =   0   'False
   End
   Begin VB.Menu mnuView 
      Caption         =   "mnuView"
      Begin VB.Menu mnuViewHistory 
         Caption         =   "mnuViewHistory"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuViewSep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuViewComPorts 
         Caption         =   "mnuViewComPorts"
      End
      Begin VB.Menu mnuScannerView 
         Caption         =   "Scanner Diagnostics"
         Shortcut        =   {F5}
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "mnuHelp"
      Begin VB.Menu mnuHelpContents 
         Caption         =   "mnuHelpContents"
         Enabled         =   0   'False
         Shortcut        =   {F1}
         Visible         =   0   'False
      End
      Begin VB.Menu mnuHelpSearch 
         Caption         =   "mnuHelpSearch"
         Enabled         =   0   'False
         Visible         =   0   'False
      End
      Begin VB.Menu mnuHelpSep 
         Caption         =   "-"
      End
      Begin VB.Menu mnuHelpAbout 
         Caption         =   "mnuHelpAbout"
      End
   End
End
Attribute VB_Name = "frmMain"
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
'*    The main human interface and top level control
'*    for the 2-axies Label Applicator.
'*
'************************************************************************
Option Explicit

'  My name
Private m_strName As String

'  Labeler class this form interactes with
Public m_objLabeler As Object
Private m_objPrinter As Object
Private m_objOutputs As Object
Private m_objInputs As Object
Private m_objMotion As Object

'  Need so both menu and switch work together
Private m_strRun As String

Private m_lngQuanity As Long
Private m_strSerialNumber As String

'  Message label message list
Private ma_strMsgList(1 To 5) As String

'  Refrence to serial form
Private m_objSerialForm As Object

Private m_blnRunNow As Boolean
Public m_blnLastError As Boolean
Public m_strlastErrorMessage As String


'    Jr. added this command
' Public g_JRFlavor
' Jr added this command

'  job open status
Private m_blnJobReady As Boolean

Public Function Initialize(objLabeler As Object, objPrinter As Object, _
                           objOutput As Object, objInput As Object, _
                           objMotion As Object _
                           ) As Boolean

   #If ccShip_Ver Then
      On Error GoTo Initialize_Error
   #Else
      On Error GoTo 0
   #End If

   Set m_objLabeler = objLabeler
   Set m_objInputs = objInput
   Set m_objOutputs = objOutput
   Set m_objPrinter = objPrinter
   Set m_objMotion = objMotion
   m_objLabeler.SetMainForm Me
   
   '  now load and init job open form
   With frmOpenJob
      '  Load the the job open form
      .Hide
   
      ' Init it
      .Initialize Me
                        
   End With 'frmOpenJob
   ClearLabelFields
   Initialize = True
   
   stbStatus.SimpleText = LoadResString(resMSG_STAT_LABLER_READY)

   Exit Function

Initialize_Error:

   ProccessError "Initialize", m_strName, Err.Number, Err.Description
   Initialize = False

End Function 'Initialize




Private Sub cmdPartPresent_Click()
   If g_blnSimulator Then
      m_objLabeler.OnBit_PartReady
      m_objLabeler.OnBit_VacuumSense
'      OnEvent_LabelApplied
   End If

End Sub

Private Sub Form_KeyPress(KeyAscii As Integer)

   #If ccShip_Ver Then
      On Error GoTo Form_KeyPress_Error
   #Else
      On Error GoTo 0
   #End If
   
   With m_objLabeler
      If m_blnJobReady And ((UCase(Chr(KeyAscii)) = "R") And Not .JobRunning) Then
         m_objLabeler.RunStopJob
         KeyAscii = 0
      ElseIf m_blnJobReady And ((UCase(Chr(KeyAscii)) = "S") And .JobRunning) Then
         m_objLabeler.RunStopJob
         KeyAscii = 0
      End If
   End With 'm_objLabeler
   
   Exit Sub

Form_KeyPress_Error:

   ProccessError "Form_KeyPress", m_strName, Err.Number, Err.Description

End Sub 'Form_KeyPress

Private Sub Form_Load()

   Dim i As Integer
   
   #If ccShip_Ver Then
      On Error GoTo Form_Load_Error
   #Else
      On Error GoTo 0
   #End If

   '  Set up the form
   m_strName = Me.Name
   Me.Caption = LoadResString(resFORM_MAIN) & LoadResString(resFORM_MAIN_NO_JOB)
   Me.Width = 8235
   modUtilities.CenterForm Me
   
   '  Lable the menues
   '  File
   mnuFile.Caption = LoadResString(resMNU_FILE)
   mnuFileOpen.Caption = LoadResString(resMNU_OPEN)
   mnuFileOpenJobFile.Caption = LoadResString(resMNU_OPEN_JOB_FILE)
   mnuFileExit.Caption = LoadResString(resMNU_EXIT)
   '  Run
   mnuRun.Caption = LoadResString(resMNU_RUN)
   m_strRun = LoadResString(resMNU_RUN)
   '  View
   mnuView.Caption = LoadResString(resMNU_VIEW)
   mnuViewHistory.Caption = LoadResString(resMNU_HISTORY)
   mnuViewComPorts.Caption = LoadResString(resMNU_COMPORTS)
   
   '  Help
   mnuHelp.Caption = LoadResString(resMNU_HELP)
   mnuHelpContents.Caption = LoadResString(resMNU_CONTENTS)
   mnuHelpSearch.Caption = LoadResString(resMNU_SEARCH)
   mnuHelpAbout.Caption = LoadResString(resMNU_ABOUT)
   
   '  Label command buttons
   sscOpenJob.Caption = LoadResString(resCND_NEW_JOB)
   sscExit.Caption = LoadResString(resCMD_EXIT)
   labInstructions.Caption = LoadResString(resLABEL_INSTRUCTIONS_RUN)
   sscManualFeed.Caption = LoadResString(resCMD_MANUAL_FEED)
   
   '  job run / idle button labeled on panal
   sscRunJob.Caption = LoadResString(resLABEL_MAIN_DISABLED)
   sscRunJob.Picture = imgLablerDisabled.Picture
   sscRunJob.Enabled = False
   
   '  Label labels
   labJobName.Caption = LoadResString(resLABEL_MAIN_NAME)
   labPartNumber.Caption = "Part Number: " 'LoadResString(resLABEL_MAIN_PARTNUMBER)
   labQuantity.Caption = LoadResString(resLABEL_MAIN_QUANTITY)
   ssfLastlabel.Caption = LoadResString(resLABEL_MAIN_LAST_PRINTED)
   labScaned.Caption = LoadResString(resLABEL_MAIN_SCANED)
   labPrinted.Caption = LoadResString(resLABEL_MAIN_SEQ_PRINTED)
 
   '  Clear label boxes
   labTextJobName.Caption = ""
   labTextPartNumber.Caption = ""
   labTextQuantity.Caption = ""
   labTextPrinted.Caption = ""
   labTextScanned.Caption = ""
   
   '  Clear message area
   MessageClear
   '  clear status bar
   stbStatus.SimpleText = ""
      
   '   Setup monitring forms
   If g_blnTest Then
      frmSerialComm.Show
      mnuViewComPorts.Checked = True
      frmHistory.WindowState = vbNormal
      mnuViewHistory.Checked = True
   Else
      frmSerialComm.Hide
      mnuViewComPorts.Checked = False
      frmHistory.WindowState = vbNormal
      mnuViewHistory.Checked = False
   End If
   
   '   Conect to the configuration data base
   dbcLabelerConfiguration.DatabaseName = modMain.GetConfigurationDataBaseName
   dbcLabelerConfiguration.ReadOnly = True
   
   '  Now connect to the job common stuff
   dbcCommon.DatabaseName = modMain.JobDatabaseName

   '  set the run now flage to false to initialize
   m_blnRunNow = False
   
   If (g_blnSimulator) Then
     cmdPartPresent.Visible = True
   Else
     cmdPartPresent.Visible = False
   
   End If
   
   Exit Sub

Form_Load_Error:

   ProccessError "Form_Load", m_strName, Err.Number, Err.Description

End Sub 'Form_Load

Private Sub Form_Unload(Cancel As Integer)

   modMain.ExitEnd
   
End Sub 'Form_Unload








Private Sub mnuFileExit_Click()

   modMain.ExitEnd
   
End Sub 'mnuFileExit_Click

Private Sub mnuFileOpen_Click()

   GetJobData
   
End Sub 'mnuFileOpen

Private Sub mnuFileOpenJobFile_Click()

   OpenJobDB
   
End Sub 'mnuFileOpenJobFile_Click

Private Sub mnuFilePrint_Click()

   m_objLabeler.On_Event g_evtTEST_LABEL, True
   
End Sub 'mnuFilePrint_Click






Private Sub mnuFilePrinterRelease_Click()

   m_objOutputs.SetBit intbit:=g_obitPtrRelese, blnValue:=False

End Sub 'mnuFilePrinterRelease_Click

Private Sub mnuHelpAbout_Click()

   frmAbout.Show vbModal
   
End Sub 'mnuHelpAbout_Click






Private Sub mnuHelpContents_Click()

   With cdlHelp
      .HelpFile = App.HelpFile
      .HelpCommand = cdlHelpContents
      .ShowHelp
   End With 'cdlHelp
   
End Sub 'mnuHelpContents_Click

Private Sub mnuHelpSearch_Click()

   With cdlHelp
      .HelpFile = App.HelpFile
      .HelpCommand = cdlHelpIndex
      .ShowHelp
   End With 'cdlHelp
   
End Sub


Private Sub mnuRun_Click()

   m_objLabeler.RunStopJob
            
End Sub 'mnuRun_Click

Private Sub mnuScannerView_Click()
   frmScanner.Show
End Sub

Private Sub mnuViewComPorts_Click()
'  Use the printer class to get to the serial form

   With mnuViewComPorts
      If .Checked Then
         modUtilities.HideSerialMonitorForm
         .Checked = False
      Else
         modUtilities.ShowSerialMonitorForm
         .Checked = True
      End If
   End With 'mnuViewComPorts

End Sub 'mnuViewComPorts_Click


Private Sub mnuViewDigitalInputs_Click()
   
 '  With mnuViewDigitalInputs
 '     If .Checked Then
 '        m_objInputs.Hide
 '        .Checked = False
 '     Else
 '        m_objInputs.Show
 '        .Checked = True
 '     End If
 '  End With 'mnuViewDigIO

End Sub 'mnuViewDigitalInputs_Click

Private Sub mnuViewDigitalOutputs_Click()

'   With mnuViewDigitalOutputs
'      If .Checked Then
'         m_objOutputs.Hide
'         .Checked = False
'      Else
'         m_objOutputs.Show
'         .Checked = True
'      End If
'   End With 'mnuViewDigIO

End Sub 'mnuViewDigitalOutputs_Click


Private Sub mnuViewHistory_Click()

   With mnuViewHistory
      If .Checked Then
         modUtilities.HideHistoryMonitorForm
         .Checked = False
      Else
         modUtilities.ShowHistoryMonitorForm
         .Checked = True
      End If
   End With 'mnuViewHistory
   
End Sub 'mnuViewHistory_Click


Private Sub mnuViewMotion_Click()

'   With mnuViewMotion
'      If .Checked Then
'         m_objMotion.Hide
'         .Checked = False
'      Else
'         m_objMotion.Show
'         .Checked = True
'      End If
'   End With 'mnuViewMotion

End Sub 'mnuViewMotion_Click

Private Sub mnuViewPrinterOptions_Click()

   #If ccShip_Ver Then
      On Error GoTo mnuViewPrinterOptions_Click_Error
   #Else
      On Error GoTo 0
   #End If

   '  Open the the job open form
   frmPrinterOptions.Hide
   
   '  fill the text boxes
   frmPrinterOptions.Initialize m_objPrinter
                         
   frmPrinterOptions.Show vbModal
   
   Exit Sub

mnuViewPrinterOptions_Click_Error:

   ProccessError "mnuViewPrinterOptions_Click", m_strName, Err.Number, Err.Description

   
End Sub 'mnuViewPrinterOptions_Click


Private Sub sscExit_Click()

   modMain.ExitEnd

End Sub 'sscExit_Click

Private Sub sscManualFeed_Click()
   m_objLabeler.On_Event g_evtMANUAL_FEED, True
   
End Sub 'sscManualFeed_Click

Private Sub sscOpenJob_Click()
' added flag to determine if job is 2 sided 12/14/00
   
   If (g_blnOpenTraceLogFile) Then TraceLog ("Open Job Selected")
   
   GetJobData varInitalJob:=labTextJobName.Caption
   labTextQuantity.Caption = ""
   labTextPrinted.Caption = ""
   labTextScanned.Caption = ""
      
   If frmOpenJob.m_blnJobCancel Then
     Exit Sub
   End If
   
   frmOpenJob.dbgJobs.Refresh
   frmOpenJob.Refresh
   DoEvents
   If (frmOpenJob.txb2Sided = "Y") Then
      g_blnIs2Sided = True
       If (Not frmScanner.MSComm2.PortOpen) Then
          frmScanner.MSComm2.PortOpen = True
       End If
   Else
       If (frmScanner.MSComm2.PortOpen) Then
          frmScanner.MSComm2.PortOpen = False
       End If
      g_blnIs2Sided = False
   End If
   If Not m_blnLastError Then
   
     lblFlavor.Caption = frmOpenJob.txbFlavor.Text
     lblHolePattern.Caption = Trim(frmOpenJob.txbHolePattern)
     lblDHolePattern.Caption = ""
      m_blnLastError = False
   End If
   If g_strStopPin_1 = "Y" Then
      If (g_blnOpenTraceLogFile) Then TraceLog ("Enable Stop Pin 1")
      
      m_objLabeler.StopPin_1
   Else
      If (g_blnOpenTraceLogFile) Then TraceLog ("Enable Stop Pin 2")
      
      m_objLabeler.StopPin_2
   End If
    
   If (g_blnIs2Sided) Then
     lblRunTimeMode.Caption = "2 Sided"
   Else
     lblRunTimeMode.Caption = "Normal"
   End If
   
   
End Sub 'sscOpenJob_Click





Public Sub JobRun()
   If (g_blnOpenTraceLogFile) Then TraceLog ("Entering Job Run")


   '  Change the menu for a running job
   With mnuRun
      .Caption = LoadResString(resMNU_STOP)
      .Enabled = True
   End With 'mnuRun
   mnuFile.Enabled = False
   
   '  Disable the job open while the job is running.
   sscOpenJob.Enabled = False
   sscManualFeed.Enabled = False
   
   '  Change job run button for running job
   With sscRunJob
      .Picture = imgLablerRunning.Picture
      .Caption = LoadResString(resLABEL_MAIN_RUNNING)
      .Enabled = True
   End With 'sscRunJob
   
   labInstructions.Caption = LoadResString(resLABEL_INSTRUCTIONS_STOP)
   
   '  Change the status line a form caption for a running job.
   '  Refresh the form and  give the system some time.
   stbStatus.SimpleText = LoadResString(resMSG_STAT_JOB_RUNNING)
   Me.Caption = LoadResString(resFORM_MAIN) & LoadResString(resFORM_MAIN_RUNNING)
   
   '  Refresh the form and
   '  give the system some time.
   Refresh
   DoEvents
   
   If (g_blnOpenTraceLogFile) Then TraceLog ("Exiting Job Run")

End Sub 'JobRun

Public Sub JobEnd()
   TraceLog ("Entering JobEnd")

   '  Reset menu and the job open button for end of job
   With mnuRun
      .Caption = LoadResString(resMNU_RUN)
      .Enabled = True
   End With 'mnuRun
   lblRunTimeMode.Caption = ""
   
   mnuFile.Enabled = True
   
   sscOpenJob.Enabled = True
   sscManualFeed.Enabled = True
   
   labInstructions.Caption = LoadResString(resLABEL_INSTRUCTIONS_RUN)
   
   With sscRunJob
      .Caption = LoadResString(resLABEL_MAIN_IDEL)
      .Picture = imgLablerComplete.Picture
      .Enabled = True
   End With 'sscRunJob
   
   '  Change the status  and caption for end of job.
   stbStatus.SimpleText = LoadResString(resMSG_STAT_JOB_COMPLETE)
   Me.Caption = LoadResString(resFORM_MAIN) & LoadResString(resFORM_MAIN_IDLE)
   
   '  Refresh the form and
   '  give the system some time
   Refresh
   DoEvents
   TraceLog ("Exiting JobEnd")
   
End Sub 'JobEnd


Public Sub GetJobData(Optional varInitalJob As Variant)

   #If ccShip_Ver Then
      On Error GoTo GetJobData_Error
   #Else
      On Error GoTo 0
   #End If

   TraceLog ("Entered GetJobData")

   '  move the actuator to the Q stack position
   '  This allow the unit to in and out of open job
   '  and know it is at the printer when a job is ready
   
   TraceLog ("GetJobData->MovetoQueueStack")
   
   m_objLabeler.MoveToQueueStack
   
   With frmOpenJob
      If (g_blnOpenTraceLogFile) Then TraceLog ("GetJobData->frmMainJobOpen")
      
      If IsMissing(varInitalJob) Then
         .JobOpen strInitalJob:=""
      Else
         .JobOpen strInitalJob:=CStr(varInitalJob)
      End If
   End With 'frmOpenJob
   
   '  Did a leagel job get chosen...
   If m_blnJobReady Then
      TraceLog ("GetJobData->JobRunEnable ")
      
      JobRunEnable
      stbStatus.SimpleText = LoadResString(resMSG_STAT_JOB_LOADED_READY)
   End If

   If frmOpenJob.m_blnJobCancel Then
     JobInterrupted
     ClearLabelFields
     m_blnJobReady = False
     sscOpenJob.Enabled = True
    
     Exit Sub
   End If

   
   '  Remove job initialization message
   frmMessage.MessageRemove
   If (frmOpenJob.txb2Sided = "Y") Then
      g_blnIs2Sided = True
      lblRunTimeMode.Caption = "2 Sided"

   Else
      g_blnIs2Sided = False
     lblRunTimeMode.Caption = "Normal"
      
   End If
   
   
   '  Does he want to run the job imedeatly
   If m_blnRunNow Then
      If (g_blnOpenTraceLogFile) Then TraceLog ("GetJobData: Good Job Found")
      If (g_blnOpenTraceLogFile) Then TraceLog ("GetJobData->RunStopJob ")
      m_objLabeler.RunStopJob
      m_blnRunNow = False
   End If
   
   '  now move back to the printer
   TraceLog ("GetJobData: Move Actuator to Printer")
   
   m_objLabeler.MoveToPrinter
   
   Exit Sub

GetJobData_Error:

   ProccessError "GetJobData", m_strName, Err.Number, Err.Description

End Sub 'GetJobData

Public Sub InfoJob(strJobID As String, strName As String, strPartNumber As String, _
                   strLocationCode As String, strFormatName As String, _
                   strTemplatePath As String, blnRunNow As Boolean, blnNewJob As Boolean)
                   
   #If ccShip_Ver Then
      On Error GoTo InfoJob_Error
   #Else
      On Error GoTo 0
   #End If


   If strPartNumber = "" Then
      Log "Main Form", "No job loaded"
      m_blnJobReady = False
   Else
      m_blnJobReady = m_objLabeler.InfoJob(strJobID:=strJobID, strName:=strName, _
                           strPartNumber:=strPartNumber, _
                           strFormatName:=strFormatName, strLocationCode:=strLocationCode, _
                           strTemplatePath:=strTemplatePath, blnAutoRun:=blnRunNow, blnNewJob:=blnNewJob)
                           
      m_blnRunNow = blnRunNow
      
   End If
   
   Exit Sub

InfoJob_Error:

   ProccessError "InfoJob", m_strName, Err.Number, Err.Description

                    
End Sub 'InfoJob


Public Sub JobUpdate(ByVal v_strName As String, _
                     ByRef r_strPartNumber As String, _
                     ByRef r_strLocationCode As String, _
                     ByRef r_strFormatName As String, _
                     ByRef r_strTemplatePath As String)
'  This function passes the data through to the job open form to
'  update a record in the jobs database.

   TraceLog ("JobUpdate: Updating Job Data")


   #If ccShip_Ver Then
      On Error GoTo JobUpdate_Error
   #Else
      On Error GoTo 0
   #End If

   frmOpenJob.JobUpdate v_strName:=v_strName, _
                        r_strPartNumber:=r_strPartNumber, _
                        r_strLocationCode:=r_strLocationCode, _
                        r_strFormatName:=r_strFormatName, _
                        r_strTemplatePath:=r_strTemplatePath
   Exit Sub

JobUpdate_Error:

   ProccessError "JobUpdate", m_strName, Err.Number, Err.Description

End Sub 'JobUpdate




Public Sub JobRunEnable()

   '  Now set up menu items
   TraceLog ("JobRunEnable: Initializing Main Screen Buttons")
   
   With mnuRun
      .Caption = LoadResString(resMNU_RUN)
      .Enabled = True
   End With 'mnuRun
   
   sscOpenJob.Enabled = True
   sscManualFeed.Enabled = True

   '  Setup the run job button
   With sscRunJob
      .Caption = LoadResString(resLABEL_MAIN_IDEL)
      .Picture = imgLablerIdle.Picture
      .Enabled = True
  '    .SetFocus
   End With 'sscRunJob
   
   '  Setup the status and caption
   Me.Caption = LoadResString(resFORM_MAIN) & LoadResString(resFORM_MAIN_IDLE)
   stbStatus.SimpleText = LoadResString(resMSG_STAT_JOB_READY)
   
   '  Refresh the form and
   '  give the system time to complete tasks
   Refresh
   DoEvents

End Sub 'JobRunEnable




Public Function MessageRemove(intMsg As Integer)

   Dim i As Integer
   
   #If ccShip_Ver Then
      On Error GoTo MessageRemove_Error
   #Else
      On Error GoTo 0
   #End If
   
   If intMsg >= 1 And intMsg <= 5 Then
      With labMessages(intMsg)
         .Visible = False
         .Caption = ""
         .Refresh
      End With 'labMessages (intMsg)
      MessageRemove = 0
   End If

   Exit Function
   
MessageRemove_Error:

   ProccessError "MessageRemove", m_strName, Err.Number, Err.Description

End Function 'RemoveMessage

Public Function MessageDisplay(strMsg As String) As Integer

   Dim i As Integer
   
   #If ccShip_Ver Then
      On Error GoTo MessageDisplay_Error
   #Else
      On Error GoTo 0
   #End If
   
   '  Find the first blank message
   i = 1
   Do While labMessages(i).Visible And i <= 5
      i = i + 1
   Loop
   
   If i <= 5 Then
      With labMessages(i)
         .Visible = True
         .Caption = strMsg
         .Refresh
      End With 'labMessages (i)
      MessageDisplay = i
   Else
      MessageDisplay = 0
   End If

   Exit Function

MessageDisplay_Error:

   MessageDisplay = 0
   ProccessError "MessageDisplay", m_strName, Err.Number, Err.Description

End Function 'MessageDisplay


Public Sub PanelComplete(strQuantity As String)

   #If ccShip_Ver Then
      On Error Resume Next
   #Else
      On Error GoTo 0
   #End If

   If (g_blnOpenTraceLogFile) Then TraceLog ("PanelComplete")

   stbStatus.SimpleText = LoadResString(resMSG_STAT_PANEL_COMPLETE)
   labTextQuantity.Caption = strQuantity
   
End Sub 'PanelComplete

Public Sub PartReady()

   #If ccShip_Ver Then
      On Error Resume Next
   #Else
      On Error GoTo 0
   #End If

   stbStatus.SimpleText = LoadResString(resMSG_STAT_PANEL_LABELING)
   
End Sub 'PartReady

Public Sub JobInterrupted()


   If (g_blnOpenTraceLogFile) Then TraceLog ("JobInterrupted")

   sscOpenJob.Enabled = False
   If m_blnJobReady Then
   
      mnuFile.Enabled = True
      mnuRun.Enabled = False
      
      With sscRunJob
         .Picture = imgLablerInterrupted.Picture
         .Caption = LoadResString(resLABEL_MAIN_INTERRUPTED)
         .Enabled = False
      End With 'sscRunJob
      
      sscOpenJob.Enabled = True
      sscManualFeed.Enabled = False
      
      stbStatus.SimpleText = LoadResString(resMSG_STAT_LABELING_INTERRUPTED)
      Me.Caption = LoadResString(resFORM_MAIN) & LoadResString(resFORM_MAIN_INTERRUPTED)
   End If
   Refresh
   DoEvents
   
End Sub 'JobInterrupted

Public Sub JobHolding(blnStatus As Boolean)

   TraceLog ("JobHolding")


   If m_objLabeler.JobRunning Then
      If blnStatus Then 'job is holding
         mnuRun.Enabled = False
         With sscRunJob
            .Picture = imgLablerInterrupted.Picture
            .Caption = LoadResString(resLABEL_MAIN_HOLDING)
            .Enabled = False
         End With 'sscRunJob
         Me.Caption = LoadResString(resFORM_MAIN) & LoadResString(resFORM_MAIN_HOLDING)
         stbStatus.SimpleText = LoadResString(resMSG_STAT_LABELING_HOLDING)
      Else
         mnuRun.Enabled = True
         With sscRunJob
            .Picture = imgLablerRunning.Picture
            .Caption = LoadResString(resLABEL_MAIN_RUNNING)
           ' .Enabled = False
         End With 'sscRunJob
         Me.Caption = LoadResString(resFORM_MAIN) & LoadResString(resFORM_MAIN_RUNNING)
         stbStatus.SimpleText = LoadResString(resMSG_STAT_PANEL_LABELING)
      End If
   End If
   Refresh
   DoEvents
   
End Sub 'JobHolding

Private Sub sscRunJob_Click()
Dim i As Integer
Dim strBuffer As String

   TraceLog ("Run Button Pressed")
   
   
   
   
   If (frmOpenJob.txb2Sided = "Y") Then
      If (g_blnNotUseBottomScanner) Then
        MsgBox ("Bottom Scanner Deactivated. Select Another Job")
        Exit Sub
      End If
      g_blnIs2Sided = True
      'clear input buffer
      Do While frmScanner.MSComm2.InBufferCount > 0
        strBuffer = frmScanner.MSComm2.Input
      Loop
      If Trim(frmOpenJob.txbBBoardFlavor.Text) = "" Then
        MsgBox ("Missing Bottom Board Flavor Not Defined")
        Exit Sub
      End If
   Else
   
       If labTextJobName.Caption <> "" Then
          m_objLabeler.IsPreSerialNumberChk = PreCheckSerialNumbers(labTextJobName.Caption)
       End If
       g_blnIs2Sided = False
   End If
   

   
   m_objLabeler.RunStopJob


End Sub 'sscRunJob



Private Sub OpenJobDB()

   
   TraceLog ("OpenJobDB Dialog Box is Displayed")
   
   cdlOpenJobDB.DialogTitle = LoadResString(resFORM_OPEN_JOB_FILE)
   
   cdlOpenJobDB.Filter = LoadResString(resJOB_FILE_FILTER)
   
   On Error Resume Next
   cdlOpenJobDB.ShowOpen
   
   On Error GoTo 0
   If cdlOpenJobDB.filename <> "" Then
      ' set file name for job file
      modMain.JobDatabaseName = cdlOpenJobDB.filename
      modMain.JobDatabaseFile = cdlOpenJobDB.FileTitle
      '  update the data control to the job common stuff
      dbcCommon.DatabaseName = modMain.JobDatabaseName
   End If

End Sub 'OpenJobDB

Public Sub MessageClear()

   Dim i As Integer

   #If ccShip_Ver Then
      On Error GoTo MessageClear_Error
   #Else
      On Error GoTo 0
   #End If

   For i = 1 To 5
      With labMessages(i)
         .Visible = False
         .Caption = ""
         .Refresh
      End With 'labMessages (i)
   Next i
   
   Exit Sub

MessageClear_Error:

   ProccessError "MessageClear", m_strName, Err.Number, Err.Description

End Sub 'MessageClear





Public Sub ScanData()

End Sub 'ScanData

Public Sub RunJob()

   TraceLog ("RunJob ->RunStopJob")

   m_objLabeler.RunStopJob
            
End Sub 'RunJob

Public Sub ClearLabelFields()
    labInstructions.Caption = ""
   
    labTextJobName.Caption = ""
    labTextPartNumber.Caption = ""
    labTextPrinted.Caption = ""
    labTextQuantity.Caption = ""
    labTextScanned.Caption = ""
    lblDHolePattern.Caption = ""
    lblFlavor.Caption = ""
    lblHolePattern.Caption = ""
    lblRunTimeMode.Caption = ""
    
    lblFlavor.Refresh
End Sub


Public Sub InitTimers()
' This has to be done after form is avtive

   tmrPickupTimeOut.Enabled = False
   tmrRetractTimeOut.Enabled = False
   tmrPickupTimeOut.Interval = CInt(txbPickupTimeOut.Text)
   tmrRetractTimeOut.Interval = CInt(txbRetractTimeOut.Text)
   
End Sub 'InitTimers



Private Sub tmrPickupTimeOut_Timer()

   m_objLabeler.On_Event g_evtLABEL_PICKUP_TIMEOUT, True
   
End Sub 'tmrPickupTimeOut_Timer




Public Property Get CurrentSeqNumber() As Long
   
   CurrentSeqNumber = CLng(frmOpenJob.txbLastSeqNumber)
   
End Property  'Get CurrentSeqNumber

Public Property Let CurrentSeqNumber(vNewValue As Long)

   With frmOpenJob
      TraceLog ("frmOpenJob SerialNumber Being Updated=" + CStr(vNewValue))
      .txbLastSeqNumber.Text = CStr(vNewValue)
      .dbcJobs.UpdateRecord
   End With 'frmOpenJob

End Property 'Let CurrentSeqNumber



