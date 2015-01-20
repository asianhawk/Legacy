VERSION 5.00
Object = "{0BA686C6-F7D3-101A-993E-0000C0EF6F5E}#1.0#0"; "threed32.ocx"
Begin VB.Form frmDigitalOutput 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Digital Outputs"
   ClientHeight    =   6510
   ClientLeft      =   2790
   ClientTop       =   2475
   ClientWidth     =   5745
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   6510
   ScaleWidth      =   5745
   Begin VB.Timer tmrStrobe 
      Index           =   15
      Left            =   2880
      Top             =   6000
   End
   Begin VB.Timer tmrStrobe 
      Index           =   14
      Left            =   2880
      Top             =   5640
   End
   Begin VB.Timer tmrStrobe 
      Index           =   13
      Left            =   2880
      Top             =   5280
   End
   Begin VB.Timer tmrStrobe 
      Index           =   12
      Left            =   2880
      Top             =   4920
   End
   Begin VB.Timer tmrStrobe 
      Index           =   11
      Left            =   2880
      Top             =   4560
   End
   Begin VB.Timer tmrStrobe 
      Index           =   10
      Left            =   2880
      Top             =   4200
   End
   Begin VB.Timer tmrStrobe 
      Index           =   9
      Left            =   2880
      Top             =   3840
   End
   Begin VB.Timer tmrStrobe 
      Index           =   8
      Left            =   2880
      Top             =   3480
   End
   Begin VB.Timer tmrStrobe 
      Index           =   7
      Left            =   2880
      Top             =   3120
   End
   Begin VB.Timer tmrStrobe 
      Index           =   6
      Left            =   2880
      Top             =   2760
   End
   Begin VB.Timer tmrStrobe 
      Index           =   5
      Left            =   2880
      Top             =   2400
   End
   Begin VB.Timer tmrStrobe 
      Index           =   4
      Left            =   2880
      Top             =   2040
   End
   Begin VB.Timer tmrStrobe 
      Index           =   3
      Left            =   2880
      Top             =   1680
   End
   Begin VB.Timer tmrStrobe 
      Index           =   2
      Left            =   2880
      Top             =   1320
   End
   Begin VB.Timer tmrStrobe 
      Index           =   1
      Left            =   2880
      Top             =   960
   End
   Begin VB.Timer tmrStrobe 
      Index           =   0
      Left            =   2880
      Top             =   540
   End
   Begin Threed.SSPanel sspOutputs 
      Height          =   5775
      Index           =   0
      Left            =   0
      TabIndex        =   0
      Top             =   600
      Width           =   2835
      _Version        =   65536
      _ExtentX        =   5001
      _ExtentY        =   10186
      _StockProps     =   15
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
      Alignment       =   6
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   0
         Left            =   120
         TabIndex        =   1
         Top             =   135
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "0"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   0
            Left            =   45
            TabIndex        =   2
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":0000
            PictureDn       =   "DigitalOutput.frx":0112
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   1
         Left            =   120
         TabIndex        =   3
         Top             =   480
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "1"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   1
            Left            =   45
            TabIndex        =   4
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":0224
            PictureDn       =   "DigitalOutput.frx":0336
            PictureDisabled =   "DigitalOutput.frx":0448
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   2
         Left            =   120
         TabIndex        =   5
         Top             =   825
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "2"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   2
            Left            =   45
            TabIndex        =   6
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":0464
            PictureDn       =   "DigitalOutput.frx":0576
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   3
         Left            =   120
         TabIndex        =   7
         Top             =   1170
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "3"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   3
            Left            =   45
            TabIndex        =   8
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":0688
            PictureDn       =   "DigitalOutput.frx":079A
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   4
         Left            =   120
         TabIndex        =   9
         Top             =   1515
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "4"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   4
            Left            =   45
            TabIndex        =   10
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":08AC
            PictureDn       =   "DigitalOutput.frx":09BE
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   5
         Left            =   120
         TabIndex        =   11
         Top             =   1860
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "5"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   5
            Left            =   45
            TabIndex        =   12
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":0AD0
            PictureDn       =   "DigitalOutput.frx":0BE2
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   6
         Left            =   120
         TabIndex        =   13
         Top             =   2205
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "6"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   6
            Left            =   45
            TabIndex        =   14
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":0CF4
            PictureDn       =   "DigitalOutput.frx":0E06
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   7
         Left            =   120
         TabIndex        =   15
         Top             =   2550
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "7"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   7
            Left            =   45
            TabIndex        =   16
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":0F18
            PictureDn       =   "DigitalOutput.frx":102A
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   8
         Left            =   120
         TabIndex        =   17
         Top             =   2895
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "8"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   8
            Left            =   45
            TabIndex        =   18
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":113C
            PictureDn       =   "DigitalOutput.frx":124E
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   9
         Left            =   120
         TabIndex        =   19
         Top             =   3240
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "9"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   9
            Left            =   45
            TabIndex        =   20
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":1360
            PictureDn       =   "DigitalOutput.frx":1472
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   10
         Left            =   120
         TabIndex        =   21
         Top             =   3585
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "10"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   10
            Left            =   45
            TabIndex        =   22
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":1584
            PictureDn       =   "DigitalOutput.frx":1696
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   11
         Left            =   120
         TabIndex        =   23
         Top             =   3930
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "11"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   11
            Left            =   45
            TabIndex        =   24
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":17A8
            PictureDn       =   "DigitalOutput.frx":18BA
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   12
         Left            =   120
         TabIndex        =   25
         Top             =   4275
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "12"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   12
            Left            =   45
            TabIndex        =   26
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            MouseIcon       =   "DigitalOutput.frx":19CC
            PictureUp       =   "DigitalOutput.frx":19E8
            PictureDn       =   "DigitalOutput.frx":1AFA
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   13
         Left            =   120
         TabIndex        =   27
         Top             =   4620
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "13"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   13
            Left            =   45
            TabIndex        =   28
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":1C0C
            PictureDn       =   "DigitalOutput.frx":1D1E
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   14
         Left            =   120
         TabIndex        =   29
         Top             =   4965
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "14"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   14
            Left            =   45
            TabIndex        =   30
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":1E30
            PictureDn       =   "DigitalOutput.frx":1F42
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   15
         Left            =   120
         TabIndex        =   31
         Top             =   5310
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "15"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   15
            Left            =   45
            TabIndex        =   32
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":2054
            PictureDn       =   "DigitalOutput.frx":2166
         End
      End
   End
   Begin Threed.SSPanel sspStatus 
      Align           =   1  'Align Top
      Height          =   555
      Left            =   0
      TabIndex        =   33
      Top             =   0
      Width           =   5745
      _Version        =   65536
      _ExtentX        =   10134
      _ExtentY        =   979
      _StockProps     =   15
      Caption         =   "Version:"
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
      Alignment       =   1
   End
   Begin Threed.SSPanel sspOutputs 
      Height          =   5775
      Index           =   1
      Left            =   2880
      TabIndex        =   34
      Top             =   600
      Width           =   2835
      _Version        =   65536
      _ExtentX        =   5001
      _ExtentY        =   10186
      _StockProps     =   15
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
      Alignment       =   6
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   16
         Left            =   120
         TabIndex        =   35
         Top             =   135
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "16"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   16
            Left            =   45
            TabIndex        =   36
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":2278
            PictureDn       =   "DigitalOutput.frx":238A
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   17
         Left            =   120
         TabIndex        =   37
         Top             =   480
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "17"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   17
            Left            =   45
            TabIndex        =   38
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":249C
            PictureDn       =   "DigitalOutput.frx":25AE
            PictureDisabled =   "DigitalOutput.frx":26C0
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   18
         Left            =   120
         TabIndex        =   39
         Top             =   825
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "18"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   18
            Left            =   45
            TabIndex        =   40
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":26DC
            PictureDn       =   "DigitalOutput.frx":27EE
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   19
         Left            =   120
         TabIndex        =   41
         Top             =   1170
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "19"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   19
            Left            =   45
            TabIndex        =   42
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":2900
            PictureDn       =   "DigitalOutput.frx":2A12
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   20
         Left            =   120
         TabIndex        =   43
         Top             =   1515
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "20"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   20
            Left            =   45
            TabIndex        =   44
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":2B24
            PictureDn       =   "DigitalOutput.frx":2C36
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   21
         Left            =   120
         TabIndex        =   45
         Top             =   1860
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "21"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   21
            Left            =   45
            TabIndex        =   46
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":2D48
            PictureDn       =   "DigitalOutput.frx":2E5A
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   22
         Left            =   120
         TabIndex        =   47
         Top             =   2205
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "22"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   22
            Left            =   45
            TabIndex        =   48
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":2F6C
            PictureDn       =   "DigitalOutput.frx":307E
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   23
         Left            =   120
         TabIndex        =   49
         Top             =   2550
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "23"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   23
            Left            =   45
            TabIndex        =   50
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":3190
            PictureDn       =   "DigitalOutput.frx":32A2
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   24
         Left            =   120
         TabIndex        =   51
         Top             =   2895
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "24"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   24
            Left            =   45
            TabIndex        =   52
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":33B4
            PictureDn       =   "DigitalOutput.frx":34C6
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   25
         Left            =   120
         TabIndex        =   53
         Top             =   3240
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "25"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   25
            Left            =   45
            TabIndex        =   54
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":35D8
            PictureDn       =   "DigitalOutput.frx":36EA
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   26
         Left            =   120
         TabIndex        =   55
         Top             =   3585
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "26"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   26
            Left            =   45
            TabIndex        =   56
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":37FC
            PictureDn       =   "DigitalOutput.frx":390E
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   27
         Left            =   120
         TabIndex        =   57
         Top             =   3930
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "27"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.26
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   27
            Left            =   45
            TabIndex        =   58
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":3A20
            PictureDn       =   "DigitalOutput.frx":3B32
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   28
         Left            =   120
         TabIndex        =   59
         Top             =   4275
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "28"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   28
            Left            =   45
            TabIndex        =   60
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            MouseIcon       =   "DigitalOutput.frx":3C44
            PictureUp       =   "DigitalOutput.frx":3C60
            PictureDn       =   "DigitalOutput.frx":3D72
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   29
         Left            =   120
         TabIndex        =   61
         Top             =   4620
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "29"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   29
            Left            =   45
            TabIndex        =   62
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":3E84
            PictureDn       =   "DigitalOutput.frx":3F96
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   30
         Left            =   120
         TabIndex        =   63
         Top             =   4965
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "30"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   30
            Left            =   45
            TabIndex        =   64
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":40A8
            PictureDn       =   "DigitalOutput.frx":41BA
         End
      End
      Begin Threed.SSPanel sspOutputControl 
         Height          =   345
         Index           =   31
         Left            =   120
         TabIndex        =   65
         Top             =   5310
         Width           =   2565
         _Version        =   65536
         _ExtentX        =   4524
         _ExtentY        =   609
         _StockProps     =   15
         Caption         =   "31"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BorderWidth     =   1
         BevelInner      =   1
         Begin Threed.SSRibbon ssrIOSwitch 
            Height          =   240
            Index           =   31
            Left            =   45
            TabIndex        =   66
            Top             =   45
            Width           =   255
            _Version        =   65536
            _ExtentX        =   450
            _ExtentY        =   423
            _StockProps     =   65
            BackColor       =   255
            GroupNumber     =   0
            Autosize        =   1
            PictureUp       =   "DigitalOutput.frx":42CC
            PictureDn       =   "DigitalOutput.frx":43DE
         End
      End
   End
End
Attribute VB_Name = "frmDigitalOutput"
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
'******************************************************************

'  assoiated digit out class
Private m_objMyClass As Object
Private m_blnInitStatus As Boolean

Private Const m_intTIMER_NOT_USED = 0
Private Const m_intLAST_TIMER = 15

Private m_intTimeUsed(0 To 15) As Integer


Private Sub Form_Load()

   Me.Width = 5865
   
   sspStatus.Caption = "Vrsion: " & App.Major & "." & App.Minor & "." & App.Revision
   
   m_blnInitStatus = True
   
End Sub 'Form_Load


Private Sub sspOutputControl_Click(Index As Integer)

   m_objMyClass.SetBit Index, IIf(ssrIOSwitch(Index).Value = 0, True, False)

End Sub 'sspOutputControl_Click



'
Private Sub tmrStrobe_Timer(Index As Integer)

   tmrStrobe(Index).Enabled = False
   m_objMyClass.StrobeTimeOut m_intTimeUsed(Index)
   m_intTimeUsed(Index) = m_intTIMER_NOT_USED
   
End Sub 'tmrStrobe_Timer



Public Sub Initialize(objMyClass As Object)

   Set m_objMyClass = objMyClass
   If m_objMyClass Is Nothing Then
      m_blnInitStatus = False
   Else
      m_objMyClass.SetMyForm Me
      m_blnInitStatus = m_blnInitStatus And True
   End If

End Sub 'Initialize

Public Function InitStatus()

   InitStatus = m_blnInitStatus
   
End Function 'InitStatus


Private Function GetNextTimer() As Integer

   #If ccShip_Ver Then
      On Error GoTo GetNextTimer_Error
   #Else
      On Error GoTo 0
   #End If
   
   Dim i
   
   i = 0
   Do Until m_intTimeUsed(i) = m_intTIMER_NOT_USED
      i = i + 1
      If i > m_intLAST_TIMER Then
         Call Err.Raise(g_errOUT_OF_TIMERS, , LoadResString(resERR_OUT_OF_TIMERS))
      End If
   Loop
   
   GetNextTimer = i
   
   Exit Function

GetNextTimer_Error:

   ProccessError "GetNextTimer", Name, Err.Number, Err.Description

End Function 'GetNextTimer


Public Sub StartTimer(intbit As Integer, lngStrobe As Long)

   Dim intTimer As Integer
   
   intTimer = GetNextTimer
   m_intTimeUsed(intTimer) = intbit

   With tmrStrobe(intTimer)
      .Interval = lngStrobe
      .Enabled = True
   End With 'm_objMyForm.tmrStrobe (ingBit)
      
End Sub 'StartTimer
