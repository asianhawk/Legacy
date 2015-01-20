VERSION 5.00
Object = "{0BA686C6-F7D3-101A-993E-0000C0EF6F5E}#1.0#0"; "THREED32.OCX"
Object = "{E57EC353-9C37-11CE-9638-0000C0F04C96}#1.0#0"; "SSCTA32.OCX"
Begin VB.Form frmDigitalIO 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "Digital I/O"
   ClientHeight    =   4275
   ClientLeft      =   1365
   ClientTop       =   4410
   ClientWidth     =   2985
   ControlBox      =   0   'False
   Icon            =   "DigitalIO.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   4275
   ScaleWidth      =   2985
   ShowInTaskbar   =   0   'False
   Begin VB.Timer tmrScanNow 
      Enabled         =   0   'False
      Interval        =   100
      Left            =   2565
      Top             =   0
   End
   Begin Threed.SSPanel sspIOControl 
      Height          =   465
      Index           =   0
      Left            =   105
      TabIndex        =   0
      Top             =   420
      Width           =   915
      _Version        =   65536
      _ExtentX        =   1614
      _ExtentY        =   820
      _StockProps     =   15
      Caption         =   "0"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   4
      Begin Threed.SSRibbon ssrIOSwitch 
         Height          =   330
         Index           =   0
         Left            =   510
         TabIndex        =   1
         Top             =   60
         Width           =   330
         _Version        =   65536
         _ExtentX        =   582
         _ExtentY        =   582
         _StockProps     =   65
         BackColor       =   12632256
         GroupNumber     =   0
         Autosize        =   2
         PictureUp       =   "DigitalIO.frx":0442
         PictureDn       =   "DigitalIO.frx":0554
      End
      Begin VB.Image imgOFFIOIndicator 
         Height          =   240
         Index           =   0
         Left            =   45
         Picture         =   "DigitalIO.frx":0666
         Top             =   90
         Width           =   240
      End
      Begin VB.Image imgONIOIndicator 
         Height          =   240
         Index           =   0
         Left            =   270
         Picture         =   "DigitalIO.frx":0768
         Top             =   90
         Width           =   240
      End
   End
   Begin Threed.SSPanel sspIOControl 
      Height          =   465
      Index           =   1
      Left            =   105
      TabIndex        =   2
      Top             =   900
      Width           =   915
      _Version        =   65536
      _ExtentX        =   1614
      _ExtentY        =   820
      _StockProps     =   15
      Caption         =   "0"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   4
      Begin Threed.SSRibbon ssrIOSwitch 
         Height          =   330
         Index           =   1
         Left            =   510
         TabIndex        =   3
         Top             =   60
         Width           =   330
         _Version        =   65536
         _ExtentX        =   582
         _ExtentY        =   582
         _StockProps     =   65
         BackColor       =   12632256
         GroupNumber     =   0
         Autosize        =   2
         PictureUp       =   "DigitalIO.frx":086A
         PictureDn       =   "DigitalIO.frx":097C
      End
      Begin VB.Image imgONIOIndicator 
         Height          =   240
         Index           =   1
         Left            =   270
         Picture         =   "DigitalIO.frx":0A8E
         Top             =   90
         Width           =   240
      End
      Begin VB.Image imgOFFIOIndicator 
         Height          =   240
         Index           =   1
         Left            =   45
         Picture         =   "DigitalIO.frx":0B90
         Top             =   90
         Width           =   240
      End
   End
   Begin Threed.SSPanel sspIOControl 
      Height          =   465
      Index           =   2
      Left            =   105
      TabIndex        =   4
      Top             =   1380
      Width           =   915
      _Version        =   65536
      _ExtentX        =   1614
      _ExtentY        =   820
      _StockProps     =   15
      Caption         =   "0"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   4
      Begin Threed.SSRibbon ssrIOSwitch 
         Height          =   330
         Index           =   2
         Left            =   510
         TabIndex        =   5
         Top             =   60
         Width           =   330
         _Version        =   65536
         _ExtentX        =   582
         _ExtentY        =   582
         _StockProps     =   65
         BackColor       =   12632256
         GroupNumber     =   0
         Autosize        =   2
         PictureUp       =   "DigitalIO.frx":0C92
         PictureDn       =   "DigitalIO.frx":0DA4
      End
      Begin VB.Image imgONIOIndicator 
         Height          =   240
         Index           =   2
         Left            =   270
         Picture         =   "DigitalIO.frx":0EB6
         Top             =   90
         Width           =   240
      End
      Begin VB.Image imgOFFIOIndicator 
         Height          =   240
         Index           =   2
         Left            =   45
         Picture         =   "DigitalIO.frx":0FB8
         Top             =   90
         Width           =   240
      End
   End
   Begin Threed.SSPanel sspIOControl 
      Height          =   465
      Index           =   3
      Left            =   105
      TabIndex        =   6
      Top             =   1860
      Width           =   900
      _Version        =   65536
      _ExtentX        =   1588
      _ExtentY        =   820
      _StockProps     =   15
      Caption         =   "0"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   4
      Begin Threed.SSRibbon ssrIOSwitch 
         Height          =   330
         Index           =   3
         Left            =   510
         TabIndex        =   7
         Top             =   60
         Width           =   330
         _Version        =   65536
         _ExtentX        =   582
         _ExtentY        =   582
         _StockProps     =   65
         BackColor       =   12632256
         GroupNumber     =   0
         Autosize        =   2
         PictureUp       =   "DigitalIO.frx":10BA
         PictureDn       =   "DigitalIO.frx":11CC
      End
      Begin VB.Image imgONIOIndicator 
         Height          =   240
         Index           =   3
         Left            =   270
         Picture         =   "DigitalIO.frx":12DE
         Top             =   90
         Width           =   240
      End
      Begin VB.Image imgOFFIOIndicator 
         Height          =   240
         Index           =   3
         Left            =   45
         Picture         =   "DigitalIO.frx":13E0
         Top             =   90
         Width           =   240
      End
   End
   Begin Threed.SSPanel sspIOControl 
      Height          =   465
      Index           =   4
      Left            =   105
      TabIndex        =   8
      Top             =   2340
      Width           =   900
      _Version        =   65536
      _ExtentX        =   1588
      _ExtentY        =   820
      _StockProps     =   15
      Caption         =   "0"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   4
      Begin Threed.SSRibbon ssrIOSwitch 
         Height          =   330
         Index           =   4
         Left            =   510
         TabIndex        =   9
         Top             =   60
         Width           =   330
         _Version        =   65536
         _ExtentX        =   582
         _ExtentY        =   582
         _StockProps     =   65
         BackColor       =   12632256
         GroupNumber     =   0
         Autosize        =   2
         PictureUp       =   "DigitalIO.frx":14E2
         PictureDn       =   "DigitalIO.frx":15F4
      End
      Begin VB.Image imgONIOIndicator 
         Height          =   240
         Index           =   4
         Left            =   270
         Picture         =   "DigitalIO.frx":1706
         Top             =   90
         Width           =   240
      End
      Begin VB.Image imgOFFIOIndicator 
         Height          =   240
         Index           =   4
         Left            =   45
         Picture         =   "DigitalIO.frx":1808
         Top             =   90
         Width           =   240
      End
   End
   Begin Threed.SSPanel sspIOControl 
      Height          =   465
      Index           =   5
      Left            =   105
      TabIndex        =   10
      Top             =   2820
      Width           =   900
      _Version        =   65536
      _ExtentX        =   1588
      _ExtentY        =   820
      _StockProps     =   15
      Caption         =   "0"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   4
      Begin Threed.SSRibbon ssrIOSwitch 
         Height          =   330
         Index           =   5
         Left            =   510
         TabIndex        =   11
         Top             =   60
         Width           =   330
         _Version        =   65536
         _ExtentX        =   582
         _ExtentY        =   582
         _StockProps     =   65
         BackColor       =   12632256
         GroupNumber     =   0
         Autosize        =   2
         PictureUp       =   "DigitalIO.frx":190A
         PictureDn       =   "DigitalIO.frx":1A1C
      End
      Begin VB.Image imgONIOIndicator 
         Height          =   240
         Index           =   5
         Left            =   270
         Picture         =   "DigitalIO.frx":1B2E
         Top             =   90
         Width           =   240
      End
      Begin VB.Image imgOFFIOIndicator 
         Height          =   240
         Index           =   5
         Left            =   45
         Picture         =   "DigitalIO.frx":1C30
         Top             =   90
         Width           =   240
      End
   End
   Begin Threed.SSPanel sspIOControl 
      Height          =   465
      Index           =   6
      Left            =   105
      TabIndex        =   12
      Top             =   3300
      Width           =   900
      _Version        =   65536
      _ExtentX        =   1588
      _ExtentY        =   820
      _StockProps     =   15
      Caption         =   "0"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   4
      Begin Threed.SSRibbon ssrIOSwitch 
         Height          =   330
         Index           =   6
         Left            =   510
         TabIndex        =   13
         Top             =   60
         Width           =   330
         _Version        =   65536
         _ExtentX        =   582
         _ExtentY        =   582
         _StockProps     =   65
         BackColor       =   12632256
         GroupNumber     =   0
         Autosize        =   2
         PictureUp       =   "DigitalIO.frx":1D32
         PictureDn       =   "DigitalIO.frx":1E44
      End
      Begin VB.Image imgONIOIndicator 
         Height          =   240
         Index           =   6
         Left            =   270
         Picture         =   "DigitalIO.frx":1F56
         Top             =   90
         Width           =   240
      End
      Begin VB.Image imgOFFIOIndicator 
         Height          =   240
         Index           =   6
         Left            =   45
         Picture         =   "DigitalIO.frx":2058
         Top             =   90
         Width           =   240
      End
   End
   Begin Threed.SSPanel sspIOControl 
      Height          =   465
      Index           =   7
      Left            =   105
      TabIndex        =   14
      Top             =   3780
      Width           =   915
      _Version        =   65536
      _ExtentX        =   1614
      _ExtentY        =   820
      _StockProps     =   15
      Caption         =   "0"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   4
      Begin Threed.SSRibbon ssrIOSwitch 
         Height          =   330
         Index           =   7
         Left            =   510
         TabIndex        =   15
         Top             =   60
         Width           =   330
         _Version        =   65536
         _ExtentX        =   582
         _ExtentY        =   582
         _StockProps     =   65
         BackColor       =   12632256
         GroupNumber     =   0
         Autosize        =   2
         PictureUp       =   "DigitalIO.frx":215A
         PictureDn       =   "DigitalIO.frx":226C
      End
      Begin VB.Image imgONIOIndicator 
         Height          =   240
         Index           =   7
         Left            =   270
         Picture         =   "DigitalIO.frx":237E
         Top             =   90
         Width           =   240
      End
      Begin VB.Image imgOFFIOIndicator 
         Height          =   240
         Index           =   7
         Left            =   45
         Picture         =   "DigitalIO.frx":2480
         Top             =   90
         Width           =   240
      End
   End
   Begin Threed.SSPanel sspIOControl 
      Height          =   465
      Index           =   9
      Left            =   1050
      TabIndex        =   16
      Top             =   900
      Width           =   915
      _Version        =   65536
      _ExtentX        =   1614
      _ExtentY        =   820
      _StockProps     =   15
      Caption         =   "0"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   4
      Begin Threed.SSRibbon ssrIOSwitch 
         Height          =   330
         Index           =   9
         Left            =   510
         TabIndex        =   17
         Top             =   60
         Width           =   330
         _Version        =   65536
         _ExtentX        =   582
         _ExtentY        =   582
         _StockProps     =   65
         BackColor       =   12632256
         GroupNumber     =   0
         Autosize        =   2
         PictureUp       =   "DigitalIO.frx":2582
         PictureDn       =   "DigitalIO.frx":2694
      End
      Begin VB.Image imgOFFIOIndicator 
         Height          =   240
         Index           =   9
         Left            =   45
         Picture         =   "DigitalIO.frx":27A6
         Top             =   90
         Width           =   240
      End
      Begin VB.Image imgONIOIndicator 
         Height          =   240
         Index           =   9
         Left            =   270
         Picture         =   "DigitalIO.frx":28A8
         Top             =   90
         Width           =   240
      End
   End
   Begin Threed.SSPanel sspIOControl 
      Height          =   465
      Index           =   10
      Left            =   1050
      TabIndex        =   18
      Top             =   1380
      Width           =   915
      _Version        =   65536
      _ExtentX        =   1614
      _ExtentY        =   820
      _StockProps     =   15
      Caption         =   "0"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   4
      Begin Threed.SSRibbon ssrIOSwitch 
         Height          =   330
         Index           =   10
         Left            =   510
         TabIndex        =   19
         Top             =   60
         Width           =   330
         _Version        =   65536
         _ExtentX        =   582
         _ExtentY        =   582
         _StockProps     =   65
         BackColor       =   12632256
         GroupNumber     =   0
         Autosize        =   2
         PictureUp       =   "DigitalIO.frx":29AA
         PictureDn       =   "DigitalIO.frx":2ABC
      End
      Begin VB.Image imgOFFIOIndicator 
         Height          =   240
         Index           =   10
         Left            =   45
         Picture         =   "DigitalIO.frx":2BCE
         Top             =   90
         Width           =   240
      End
      Begin VB.Image imgONIOIndicator 
         Height          =   240
         Index           =   10
         Left            =   270
         Picture         =   "DigitalIO.frx":2CD0
         Top             =   90
         Width           =   240
      End
   End
   Begin Threed.SSPanel sspIOControl 
      Height          =   465
      Index           =   11
      Left            =   1050
      TabIndex        =   20
      Top             =   1860
      Width           =   915
      _Version        =   65536
      _ExtentX        =   1614
      _ExtentY        =   820
      _StockProps     =   15
      Caption         =   "0"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   4
      Begin Threed.SSRibbon ssrIOSwitch 
         Height          =   330
         Index           =   11
         Left            =   510
         TabIndex        =   21
         Top             =   60
         Width           =   330
         _Version        =   65536
         _ExtentX        =   582
         _ExtentY        =   582
         _StockProps     =   65
         BackColor       =   12632256
         GroupNumber     =   0
         Autosize        =   2
         PictureUp       =   "DigitalIO.frx":2DD2
         PictureDn       =   "DigitalIO.frx":2EE4
      End
      Begin VB.Image imgOFFIOIndicator 
         Height          =   240
         Index           =   11
         Left            =   45
         Picture         =   "DigitalIO.frx":2FF6
         Top             =   90
         Width           =   240
      End
      Begin VB.Image imgONIOIndicator 
         Height          =   240
         Index           =   11
         Left            =   270
         Picture         =   "DigitalIO.frx":30F8
         Top             =   90
         Width           =   240
      End
   End
   Begin Threed.SSPanel sspIOControl 
      Height          =   465
      Index           =   12
      Left            =   1050
      TabIndex        =   22
      Top             =   2340
      Width           =   915
      _Version        =   65536
      _ExtentX        =   1614
      _ExtentY        =   820
      _StockProps     =   15
      Caption         =   "0"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   4
      Begin Threed.SSRibbon ssrIOSwitch 
         Height          =   330
         Index           =   12
         Left            =   510
         TabIndex        =   23
         Top             =   60
         Width           =   330
         _Version        =   65536
         _ExtentX        =   582
         _ExtentY        =   582
         _StockProps     =   65
         BackColor       =   12632256
         GroupNumber     =   0
         Autosize        =   2
         PictureUp       =   "DigitalIO.frx":31FA
         PictureDn       =   "DigitalIO.frx":330C
      End
      Begin VB.Image imgOFFIOIndicator 
         Height          =   240
         Index           =   12
         Left            =   45
         Picture         =   "DigitalIO.frx":341E
         Top             =   90
         Width           =   240
      End
      Begin VB.Image imgONIOIndicator 
         Height          =   240
         Index           =   12
         Left            =   270
         Picture         =   "DigitalIO.frx":3520
         Top             =   90
         Width           =   240
      End
   End
   Begin Threed.SSPanel sspIOControl 
      Height          =   465
      Index           =   13
      Left            =   1050
      TabIndex        =   24
      Top             =   2820
      Width           =   915
      _Version        =   65536
      _ExtentX        =   1614
      _ExtentY        =   820
      _StockProps     =   15
      Caption         =   "0"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   4
      Begin Threed.SSRibbon ssrIOSwitch 
         Height          =   330
         Index           =   13
         Left            =   510
         TabIndex        =   25
         Top             =   60
         Width           =   330
         _Version        =   65536
         _ExtentX        =   582
         _ExtentY        =   582
         _StockProps     =   65
         BackColor       =   12632256
         GroupNumber     =   0
         Autosize        =   2
         PictureUp       =   "DigitalIO.frx":3622
         PictureDn       =   "DigitalIO.frx":3734
      End
      Begin VB.Image imgOFFIOIndicator 
         Height          =   240
         Index           =   13
         Left            =   45
         Picture         =   "DigitalIO.frx":3846
         Top             =   90
         Width           =   240
      End
      Begin VB.Image imgONIOIndicator 
         Height          =   240
         Index           =   13
         Left            =   270
         Picture         =   "DigitalIO.frx":3948
         Top             =   90
         Width           =   240
      End
   End
   Begin Threed.SSPanel sspIOControl 
      Height          =   465
      Index           =   14
      Left            =   1050
      TabIndex        =   26
      Top             =   3300
      Width           =   915
      _Version        =   65536
      _ExtentX        =   1614
      _ExtentY        =   820
      _StockProps     =   15
      Caption         =   "0"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   4
      Begin Threed.SSRibbon ssrIOSwitch 
         Height          =   330
         Index           =   14
         Left            =   510
         TabIndex        =   27
         Top             =   60
         Width           =   330
         _Version        =   65536
         _ExtentX        =   582
         _ExtentY        =   582
         _StockProps     =   65
         BackColor       =   12632256
         GroupNumber     =   0
         Autosize        =   2
         PictureUp       =   "DigitalIO.frx":3A4A
         PictureDn       =   "DigitalIO.frx":3B5C
      End
      Begin VB.Image imgOFFIOIndicator 
         Height          =   240
         Index           =   14
         Left            =   45
         Picture         =   "DigitalIO.frx":3C6E
         Top             =   90
         Width           =   240
      End
      Begin VB.Image imgONIOIndicator 
         Height          =   240
         Index           =   14
         Left            =   270
         Picture         =   "DigitalIO.frx":3D70
         Top             =   90
         Width           =   240
      End
   End
   Begin Threed.SSPanel sspIOControl 
      Height          =   465
      Index           =   15
      Left            =   1050
      TabIndex        =   28
      Top             =   3795
      Width           =   915
      _Version        =   65536
      _ExtentX        =   1614
      _ExtentY        =   820
      _StockProps     =   15
      Caption         =   "0"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   4
      Begin Threed.SSRibbon ssrIOSwitch 
         Height          =   330
         Index           =   15
         Left            =   510
         TabIndex        =   29
         Top             =   60
         Width           =   330
         _Version        =   65536
         _ExtentX        =   582
         _ExtentY        =   582
         _StockProps     =   65
         BackColor       =   12632256
         GroupNumber     =   0
         Autosize        =   2
         PictureUp       =   "DigitalIO.frx":3E72
         PictureDn       =   "DigitalIO.frx":3F84
      End
      Begin VB.Image imgOFFIOIndicator 
         Height          =   240
         Index           =   15
         Left            =   45
         Picture         =   "DigitalIO.frx":4096
         Top             =   90
         Width           =   240
      End
      Begin VB.Image imgONIOIndicator 
         Height          =   240
         Index           =   15
         Left            =   270
         Picture         =   "DigitalIO.frx":4198
         Top             =   90
         Width           =   240
      End
   End
   Begin Threed.SSPanel sspIOControl 
      Height          =   465
      Index           =   16
      Left            =   1980
      TabIndex        =   30
      Top             =   420
      Width           =   915
      _Version        =   65536
      _ExtentX        =   1614
      _ExtentY        =   820
      _StockProps     =   15
      Caption         =   "0"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   4
      Begin Threed.SSRibbon ssrIOSwitch 
         Height          =   330
         Index           =   16
         Left            =   510
         TabIndex        =   31
         Top             =   60
         Width           =   330
         _Version        =   65536
         _ExtentX        =   582
         _ExtentY        =   582
         _StockProps     =   65
         BackColor       =   12632256
         GroupNumber     =   0
         Autosize        =   2
         PictureUp       =   "DigitalIO.frx":429A
         PictureDn       =   "DigitalIO.frx":43AC
      End
      Begin VB.Image imgONIOIndicator 
         Height          =   240
         Index           =   16
         Left            =   270
         Picture         =   "DigitalIO.frx":44BE
         Top             =   90
         Width           =   240
      End
      Begin VB.Image imgOFFIOIndicator 
         Height          =   240
         Index           =   16
         Left            =   45
         Picture         =   "DigitalIO.frx":45C0
         Top             =   90
         Width           =   240
      End
   End
   Begin Threed.SSPanel sspIOControl 
      Height          =   465
      Index           =   17
      Left            =   1980
      TabIndex        =   32
      Top             =   900
      Width           =   915
      _Version        =   65536
      _ExtentX        =   1614
      _ExtentY        =   820
      _StockProps     =   15
      Caption         =   "0"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   4
      Begin Threed.SSRibbon ssrIOSwitch 
         Height          =   330
         Index           =   17
         Left            =   510
         TabIndex        =   33
         Top             =   60
         Width           =   330
         _Version        =   65536
         _ExtentX        =   582
         _ExtentY        =   582
         _StockProps     =   65
         BackColor       =   12632256
         GroupNumber     =   0
         Autosize        =   2
         PictureUp       =   "DigitalIO.frx":46C2
         PictureDn       =   "DigitalIO.frx":47D4
      End
      Begin VB.Image imgOFFIOIndicator 
         Height          =   240
         Index           =   17
         Left            =   45
         Picture         =   "DigitalIO.frx":48E6
         Top             =   90
         Width           =   240
      End
      Begin VB.Image imgONIOIndicator 
         Height          =   240
         Index           =   17
         Left            =   270
         Picture         =   "DigitalIO.frx":49E8
         Top             =   105
         Width           =   240
      End
   End
   Begin Threed.SSPanel sspIOControl 
      Height          =   465
      Index           =   18
      Left            =   1980
      TabIndex        =   34
      Top             =   1380
      Width           =   915
      _Version        =   65536
      _ExtentX        =   1614
      _ExtentY        =   820
      _StockProps     =   15
      Caption         =   "0"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   4
      Begin Threed.SSRibbon ssrIOSwitch 
         Height          =   330
         Index           =   18
         Left            =   510
         TabIndex        =   35
         Top             =   60
         Width           =   330
         _Version        =   65536
         _ExtentX        =   582
         _ExtentY        =   582
         _StockProps     =   65
         BackColor       =   12632256
         GroupNumber     =   0
         Autosize        =   2
         PictureUp       =   "DigitalIO.frx":4AEA
         PictureDn       =   "DigitalIO.frx":4BFC
      End
      Begin VB.Image imgOFFIOIndicator 
         Height          =   240
         Index           =   18
         Left            =   45
         Picture         =   "DigitalIO.frx":4D0E
         Top             =   90
         Width           =   240
      End
      Begin VB.Image imgONIOIndicator 
         Height          =   240
         Index           =   18
         Left            =   270
         Picture         =   "DigitalIO.frx":4E10
         Top             =   90
         Width           =   240
      End
   End
   Begin Threed.SSPanel sspIOControl 
      Height          =   465
      Index           =   19
      Left            =   1980
      TabIndex        =   36
      Top             =   1860
      Width           =   915
      _Version        =   65536
      _ExtentX        =   1614
      _ExtentY        =   820
      _StockProps     =   15
      Caption         =   "0"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   4
      Begin Threed.SSRibbon ssrIOSwitch 
         Height          =   330
         Index           =   19
         Left            =   510
         TabIndex        =   37
         Top             =   60
         Width           =   330
         _Version        =   65536
         _ExtentX        =   582
         _ExtentY        =   582
         _StockProps     =   65
         BackColor       =   12632256
         GroupNumber     =   0
         Autosize        =   2
         PictureUp       =   "DigitalIO.frx":4F12
         PictureDn       =   "DigitalIO.frx":5024
      End
      Begin VB.Image imgOFFIOIndicator 
         Height          =   240
         Index           =   19
         Left            =   45
         Picture         =   "DigitalIO.frx":5136
         Top             =   90
         Width           =   240
      End
      Begin VB.Image imgONIOIndicator 
         Height          =   240
         Index           =   19
         Left            =   270
         Picture         =   "DigitalIO.frx":5238
         Top             =   90
         Width           =   240
      End
   End
   Begin Threed.SSPanel sspIOControl 
      Height          =   465
      Index           =   20
      Left            =   1980
      TabIndex        =   38
      Top             =   2340
      Width           =   915
      _Version        =   65536
      _ExtentX        =   1614
      _ExtentY        =   820
      _StockProps     =   15
      Caption         =   "0"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   4
      Begin Threed.SSRibbon ssrIOSwitch 
         Height          =   330
         Index           =   20
         Left            =   510
         TabIndex        =   39
         Top             =   60
         Width           =   330
         _Version        =   65536
         _ExtentX        =   582
         _ExtentY        =   582
         _StockProps     =   65
         BackColor       =   12632256
         GroupNumber     =   0
         Autosize        =   2
         PictureUp       =   "DigitalIO.frx":533A
         PictureDn       =   "DigitalIO.frx":544C
      End
      Begin VB.Image imgOFFIOIndicator 
         Height          =   240
         Index           =   20
         Left            =   45
         Picture         =   "DigitalIO.frx":555E
         Top             =   90
         Width           =   240
      End
      Begin VB.Image imgONIOIndicator 
         Height          =   240
         Index           =   20
         Left            =   270
         Picture         =   "DigitalIO.frx":5660
         Top             =   90
         Width           =   240
      End
   End
   Begin Threed.SSPanel sspIOControl 
      Height          =   465
      Index           =   21
      Left            =   1980
      TabIndex        =   40
      Top             =   2820
      Width           =   915
      _Version        =   65536
      _ExtentX        =   1614
      _ExtentY        =   820
      _StockProps     =   15
      Caption         =   "0"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   4
      Begin Threed.SSRibbon ssrIOSwitch 
         Height          =   330
         Index           =   21
         Left            =   510
         TabIndex        =   41
         Top             =   60
         Width           =   330
         _Version        =   65536
         _ExtentX        =   582
         _ExtentY        =   582
         _StockProps     =   65
         BackColor       =   12632256
         GroupNumber     =   0
         Autosize        =   2
         PictureUp       =   "DigitalIO.frx":5762
         PictureDn       =   "DigitalIO.frx":5874
      End
      Begin VB.Image imgOFFIOIndicator 
         Height          =   240
         Index           =   21
         Left            =   45
         Picture         =   "DigitalIO.frx":5986
         Top             =   90
         Width           =   240
      End
      Begin VB.Image imgONIOIndicator 
         Height          =   240
         Index           =   21
         Left            =   270
         Picture         =   "DigitalIO.frx":5A88
         Top             =   90
         Width           =   240
      End
   End
   Begin Threed.SSPanel sspIOControl 
      Height          =   465
      Index           =   22
      Left            =   1980
      TabIndex        =   42
      Top             =   3300
      Width           =   915
      _Version        =   65536
      _ExtentX        =   1614
      _ExtentY        =   820
      _StockProps     =   15
      Caption         =   "0"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   4
      Begin Threed.SSRibbon ssrIOSwitch 
         Height          =   330
         Index           =   22
         Left            =   510
         TabIndex        =   43
         Top             =   60
         Width           =   330
         _Version        =   65536
         _ExtentX        =   582
         _ExtentY        =   582
         _StockProps     =   65
         BackColor       =   12632256
         GroupNumber     =   0
         Autosize        =   2
         PictureUp       =   "DigitalIO.frx":5B8A
         PictureDn       =   "DigitalIO.frx":5C9C
      End
      Begin VB.Image imgOFFIOIndicator 
         Height          =   240
         Index           =   22
         Left            =   45
         Picture         =   "DigitalIO.frx":5DAE
         Top             =   90
         Width           =   240
      End
      Begin VB.Image imgONIOIndicator 
         Height          =   240
         Index           =   22
         Left            =   270
         Picture         =   "DigitalIO.frx":5EB0
         Top             =   90
         Width           =   240
      End
   End
   Begin Threed.SSPanel sspIOControl 
      Height          =   465
      Index           =   23
      Left            =   1980
      TabIndex        =   44
      Top             =   3780
      Width           =   915
      _Version        =   65536
      _ExtentX        =   1614
      _ExtentY        =   820
      _StockProps     =   15
      Caption         =   "0"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   4
      Begin Threed.SSRibbon ssrIOSwitch 
         Height          =   330
         Index           =   23
         Left            =   510
         TabIndex        =   45
         Top             =   60
         Width           =   330
         _Version        =   65536
         _ExtentX        =   582
         _ExtentY        =   582
         _StockProps     =   65
         BackColor       =   12632256
         GroupNumber     =   0
         Autosize        =   2
         PictureUp       =   "DigitalIO.frx":5FB2
         PictureDn       =   "DigitalIO.frx":60C4
      End
      Begin VB.Image imgOFFIOIndicator 
         Height          =   240
         Index           =   23
         Left            =   45
         Picture         =   "DigitalIO.frx":61D6
         Top             =   90
         Width           =   240
      End
      Begin VB.Image imgONIOIndicator 
         Height          =   240
         Index           =   23
         Left            =   270
         Picture         =   "DigitalIO.frx":62D8
         Top             =   90
         Width           =   240
      End
   End
   Begin SSCTA.Sheridan Sheridan1 
      Left            =   -10005
      Top             =   0
      _Version        =   65536
      _ExtentX        =   1
      _ExtentY        =   1
      _StockProps     =   0
   End
   Begin Threed.SSPanel sspIOControl 
      Height          =   465
      Index           =   8
      Left            =   1050
      TabIndex        =   47
      Top             =   420
      Width           =   915
      _Version        =   65536
      _ExtentX        =   1614
      _ExtentY        =   820
      _StockProps     =   15
      Caption         =   "0"
      BackColor       =   12632256
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BorderWidth     =   1
      BevelInner      =   1
      Alignment       =   4
      Begin Threed.SSRibbon ssrIOSwitch 
         Height          =   330
         Index           =   8
         Left            =   510
         TabIndex        =   48
         Top             =   60
         Width           =   330
         _Version        =   65536
         _ExtentX        =   582
         _ExtentY        =   582
         _StockProps     =   65
         BackColor       =   12632256
         GroupNumber     =   0
         Autosize        =   2
         PictureUp       =   "DigitalIO.frx":63DA
         PictureDn       =   "DigitalIO.frx":64EC
      End
      Begin VB.Image imgOFFIOIndicator 
         Height          =   240
         Index           =   8
         Left            =   45
         Picture         =   "DigitalIO.frx":65FE
         Top             =   90
         Width           =   240
      End
      Begin VB.Image imgONIOIndicator 
         Height          =   240
         Index           =   8
         Left            =   270
         Picture         =   "DigitalIO.frx":6700
         Top             =   90
         Width           =   240
      End
   End
   Begin SSCTA.Sheridan Sheridan2 
      Left            =   -10005
      Top             =   0
      _Version        =   65536
      _ExtentX        =   1
      _ExtentY        =   1
      _StockProps     =   0
   End
   Begin SSCTA.Sheridan Sheridan3 
      Left            =   -10005
      Top             =   0
      _Version        =   65536
      _ExtentX        =   1
      _ExtentY        =   1
      _StockProps     =   0
   End
   Begin VB.Image imgTimerON 
      Height          =   240
      Left            =   30
      Picture         =   "DigitalIO.frx":6802
      Top             =   45
      Visible         =   0   'False
      Width           =   240
   End
   Begin VB.Label labDigitalIO 
      Caption         =   "labDigitalIO"
      Height          =   270
      Left            =   330
      TabIndex        =   46
      Top             =   75
      Width           =   2415
   End
End
Attribute VB_Name = "frmDigitalIO"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'************************************************************************
'*           Computype, Inc.
'*       NextStep Automation Group
'*
'*     © Copywrite 1996 Computype, Inc.
'*
'*        3-Axis Label Applicator
'*           Control Subsystem
'*
'*          Digital I/O VB Form
'*
'*    Date of origin: 1/30/96
'*    Original author: Michael D. Reed
'*
'* Form purpose:
'*    This form provides a display and
'*    timer for scanning the Digital IO ports.
'*
'************************************************************************
'******************************************************************
Option Explicit

'  Module constents
Private Const m_strBIT = "BIT"
Private Const m_fmtBIT = "00"

'  Defin the IO indicators
Private Type IO_Def
   objInputONIndicator As Object
   objInputOFFIndicator As Object
   objIOSwith As Object
   objIOContainer As Object
   strIOType As String
End Type

Private m_colIOPortIndices As New Collection
Private m_udfIOPorts() As IO_Def

Private m_intLastBit As Integer

'  Reference to the digital controller class
'  connected to bits resented on this form.
Private m_objDigitalControl As Object

Private Function IOControl(Key As Integer) As IO_Def

   IOControl = m_udfIOPorts(m_colIOPortIndices.Item(CStr(Key)))
   
End Function 'IOControl



Private Function InitIOGroups(intLastBit As Integer) As Boolean

   Dim i As Integer
   Dim strTemp As String
   
   InitIOGroups = False
   
   If intLastBit <= (sspIOControl.Count - 1) Then
      '  Make the user array large enough to contain all the indicators
      m_intLastBit = intLastBit
      ReDim m_udfIOPorts(0 To m_intLastBit)
   
      For i = 0 To m_intLastBit
         With m_udfIOPorts(i)
            Set .objInputONIndicator = imgONIOIndicator(i)
            Set .objInputOFFIndicator = imgOFFIOIndicator(i)
            Set .objIOSwith = ssrIOSwitch(i)
            Set .objIOContainer = sspIOControl(i)
         End With 'm_udfIOPorts(i)
         
         '  Add index to  the collection
         m_colIOPortIndices.Add Item:=i, Key:=CStr(i)
      Next i
      
      InitIOGroups = True
   End If
   
End Function 'InitIOGroups

Public Function InitIODisplay(a_strDirection() As String, _
                             a_strLabel() As String, _
                             a_strName() As String, _
                             intLastBit As Integer) As Boolean

   Dim idx As Integer
   Dim blnStatus As Boolean
   
   blnStatus = False
   
   '  set up the basic structure
   blnStatus = InitIOGroups(intLastBit)
   If Not blnStatus Then Exit Function
   
   For idx = 0 To intLastBit
      With m_udfIOPorts(idx)
      
         '  Line up the controls
         .objInputONIndicator.Left = .objInputOFFIndicator.Left
         .objIOSwith.Left = .objInputOFFIndicator.Left
         
         '  Set the type of control
         .strIOType = a_strDirection(idx)
         If .strIOType = g_strOUTPUT Then
            .objIOSwith.Visible = True
            .objInputONIndicator.Visible = False
            .objInputOFFIndicator.Visible = False
         Else
            .objIOSwith.Visible = False
            .objInputONIndicator.Visible = False
            .objInputOFFIndicator.Visible = True
         End If
      
         '  Set the IO label
         .objIOContainer.Caption = a_strLabel(idx)
         .objIOContainer.Tag = a_strName(idx)
         
      End With 'm_udfIOPorts(idx)
   Next idx
      
   InitIODisplay = True
   
End Function 'InitIODisplay




Private Sub ToggleIOIndicators(udtIOCtrl As IO_Def, Value As Boolean)

   With udtIOCtrl
      If .strIOType = g_strOUTPUT Then
         .objIOSwith.Value = Value
      Else
         If Value Then
            .objInputONIndicator.Visible = True
            .objInputOFFIndicator.Visible = False
         Else
            .objInputONIndicator.Visible = False
            .objInputOFFIndicator.Visible = True
         End If
      End If
      'modUtilities.Log "DigIO Bit " & .objIOContainer.Caption, .objIOContainer.Tag & "; Value=" & CStr(Value)
      
   End With 'udtIOCtrl
   
End Sub 'ToggleIOIndicators

Private Sub Form_Load()

   '  disable the timer until ready to run
   tmrScanNow.Enabled = False
         
End Sub 'Form_Load





Private Sub Form_Unload(Cancel As Integer)

   '  disable the timer so it does not mess up the ide
   tmrScanNow.Enabled = False

End Sub 'Form_Unload


Private Sub sspIOControl_Click(Index As Integer)

   If ssrIOSwitch(Index).Visible Then
      ssrIOSwitch(Index).Value = Not ssrIOSwitch(Index).Value
   End If

End Sub 'sspIOControl_Click

Private Sub ssrIOSwitch_Click(Index As Integer, Value As Integer)

   m_objDigitalControl.ForceBit intBitNumber:=Index, blnBitValue:=CBool(Value)
   
End Sub 'ssrIOSwitch_Click



Public Function Initialize(objDigCtrl As Object) As Boolean

   Dim blnStatus As Boolean
   
   Initialize = False
   
   Set m_objDigitalControl = objDigCtrl
   
   labDigitalIO.Caption = "CompuBoard: " & m_objDigitalControl.Version
   
   Caption = "CompuBoard Digital"
   
   SetMonitorForm Me
   
   Initialize = blnStatus
   
End Function 'Initialize
Public Sub ShowBit(Index As Integer, blnValue As Boolean)

   ToggleIOIndicators udtIOCtrl:=IOControl(Index), Value:=blnValue
   
End Sub 'ShowBit

Public Sub ScanPorts()

   Dim vntBuffer() As Variant
   Dim i As Integer
   
   m_objDigitalControl.Scan vntBuffer
   
'   For i = 0 To UBound(vntBuffer) - 1
'      ToggleIOIndicators IOControl(vntBuffer(i)(g_idxBIT_NUM)), vntBuffer(i)(g_idxBIT_VAL)
'   Next i

End Sub 'ScanPorts

Public Sub TimerEnable(blnValue As Boolean, Optional intInterval As Variant)

   tmrScanNow.Enabled = blnValue
   
   If Not IsMissing(intInterval) Then
      tmrScanNow.Interval = intInterval
   End If
   
End Sub 'TimerEnable

Private Sub tmrScanNow_Timer()

   '  disable the timer events while scanning
   tmrScanNow.Enabled = False
   imgTimerON.Visible = True
   imgTimerON.Refresh
   ScanPorts
   imgTimerON.Visible = False
   imgTimerON.Refresh
   tmrScanNow.Enabled = True
   
End Sub 'tmrScanNow_Timer



Public Sub UnloadMe()

   Unload Me
   
End Sub 'Unload

Public Function TimerStatus() As Boolean

   TimerStatus = tmrScanNow.Enabled
   
End Function 'TimerStatus
