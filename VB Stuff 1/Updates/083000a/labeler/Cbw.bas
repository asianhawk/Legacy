Attribute VB_Name = "modCBW32"
'*********************************************************************
'
'      Computer Boards Library
'
'  By: Computer Boards
'      125 High St.
'      Mansfield MA 02048
'      (508) 261_1123
'
'  File: CBW32.BAS
'
'  (c) Copyright 1996 by Computer Boards
'      All Rights Reserved
'
' This file contains the Visual BASIC declarations for all Computer
' Boards library commands.   This file should be included in the
' project as a 'Private Module
'
'***********************************************************************

' Current Revision Number
Private Const CURRENTREVNUM = 3.4

' Error Codes
Private Const NOERRORS = 0
Private Const BADBOARD = 1
Private Const DEADDIGITALDEV = 2
Private Const DEADCOUNTERDEV = 3
Private Const DEADDADEV = 4
Private Const DEADADDEV = 5
Private Const NOTDIGITALCONF = 6
Private Const NOTCOUNTERCONF = 7
Private Const NOTDACONF = 8
Private Const NOTADCONF = 9
Private Const NOTMUXCONF = 10
Private Const BADPORTNUM = 11
Private Const BADCOUNTERDEVNUM = 12
Private Const BADDADEVNUM = 13
Private Const BADSAMPLEMODE = 14
Private Const BADINT = 15
Private Const BADADCHAN = 16
Private Const BADCOUNT = 17
Private Const BADCNTRCONFIG = 18
Private Const BADDAVAL = 19
Private Const BADDACHAN = 20
Private Const ALREADYACTIVE = 22
Private Const BADRATE = 24
Private Const COMPATMODE = 25
Private Const TRIGSTATE = 26
Private Const ADSTATUSHUNG = 27
Private Const TOOFEW = 28
Private Const OVERRUN = 29
Private Const BADRANGE = 30
Private Const NOPROGGAIN = 31
Private Const BADFILENAME = 32
Private Const DISKISFULL = 33
Private Const COMPATWARN = 34
Private Const BADPOINTER = 35
Private Const RATEWARNING = 37
Private Const CONVERTDMA = 38
Private Const DTCONNECTERR = 39
Private Const FORECONTINUOUS = 40
Private Const BADBOARDTYPE = 41
Private Const WRONGDIGCONFIG = 42
Private Const NOTCONFIGURABLE = 43
Private Const BADPORTCONFIG = 44
Private Const BADFIRSTPOINT = 45
Private Const ENDOFFILE = 46
Private Const NOT8254CTR = 47
Private Const NOT9513CTR = 48
Private Const BADTRIGTYPE = 49
Private Const BADTRIGVALUE = 50
Private Const BADOPTION = 52
Private Const BADPRETRIGCOUNT = 53
Private Const BADDIVIDER = 55
Private Const BADSOURCE = 56
Private Const BADCOMPARE = 57
Private Const BADTIMEOFDAY = 58
Private Const BADGATEINTERVAL = 59
Private Const BADGATECNTRL = 60
Private Const BADCOUNTEREDGE = 61
Private Const BADSPCLGATE = 62
Private Const BADRELOAD = 63
Private Const BADRECYCLEFLAG = 64
Private Const BADBCDFLAG = 65
Private Const BADDIRECTION = 66
Private Const BADOUTCONTROL = 67
Private Const BADBITNUMBER = 68
Private Const NONEENABLED = 69
Private Const BADCTRCONTROL = 70
Private Const BADMUXCHAN = 71
Private Const WRONGADRANGE = 72
Private Const OUTOFRANGE = 73
Private Const BADTEMPSCALE = 74
Private Const BADERRCODE = 75
Private Const NOQUEUE = 76
Private Const CONTINUOUSCOUNT = 77
Private Const UNDERRUN = 78
Private Const BADMEMMODE = 79
Private Const FREQOVERRUN = 80
Private Const NOCJCCHAN = 81
Private Const BADCHIPNUM = 82
Private Const DIGNOTENABLED = 83
Private Const CONVERT16BITS = 84
Private Const NOMEMBOARD = 85
Private Const DTACTIVE = 86
Private Const NOTMEMCONF = 87
Private Const ODDCHAN = 88
Private Const CTRNOINIT = 89
Private Const NOT8536CTR = 90
Private Const FREERUNNING = 91
Private Const INTERRUPTED = 92
Private Const NOSELECTORS = 93
Private Const NOBURSTMODE = 94
Private Const NOTWINDOWSFUNC = 95
Private Const NOTSIMULCONF = 96
Private Const EVENODDMISMATCH = 97
Private Const M1RATEWARNING = 98
Private Const NOTRS485 = 99
Private Const NOTDOSFUNC = 100
Private Const RANGEMISMATCH = 101
Private Const CLOCKTOOSLOW = 102
Private Const BADCALFACTORS = 103
Private Const BADCONFIGTYPE = 104
Private Const BADCONFIGITEM = 105
Private Const NOPCMCIABOARD = 106
Private Const NOBACKGROUND = 107
Private Const STRINGTOOSHORT = 108
Private Const CONVERTEXTMEM = 109

Private Const INTERNALERR = 200

' Windows error codes
Private Const CANTLOCKDMABUF = 301
Private Const DMAINUSE = 302
Private Const BADMEMHANDLE = 303
Private Const NOENHANCEDMODE = 304
Private Const NOVDDINSTALLED = 305
Private Const NOWINDOWSMEMORY = 306

' These are the commonly occurring remapped DOS error codes
Private Const DOSBADFUNC = 501
Private Const DOSFILENOTFOUND = 502
Private Const DOSPATHNOTFOUND = 503
Private Const DOSNOHANDLES = 504
Private Const DOSACCESSDENIED = 505
Private Const DOSINVALIDHANDLE = 506
Private Const DOSNOMEMORY = 507
Private Const DOSBADDRIVE = 515
Private Const DOSTOOMANYFILES = 518
Private Const DOSWRITEPROTECT = 519
Private Const DOSDRIVENOTREADY = 521
Private Const DOSSEEKERROR = 525
Private Const DOSWRITEFAULT = 529
Private Const DOSREADFAULT = 530
Private Const DOSGENERALFAULT = 531

Private Const WIN_UNK_INT = 607
Private Const WIN_CANNOT_SET_INT = 608
Private Const WIN_CANNOT_ENABLE_INT = 609
Private Const WIN_CANNOT_RESET_INT = 610
Private Const WIN_CANNOT_DISABLE_INT = 611

Private Const NOTUSED = -1

' Maximum length of error string
Private Const ERRSTRLEN = 80

' Maximum length of board name string
Private Const BOARDNAMELEN = 25


' Status values
Private Const Idle = 0
Private Const RUNNING = 1

' Option Flags
Private Const FOREGROUND = &H0
Private Const BACKGROUND = &H1

Private Const SINGLEEXEC = &H0
Private Const CONTINUOUS = &H2

Private Const TIMED = &H0
Private Const EXTCLOCK = &H4

Private Const NOCONVERTDATA = &H0
Private Const CONVERTDATA = &H8

Private Const NODTCONNECT = &H0
Private Const DTCONNECT = &H10

Private Const DEFAULTIO = &H0
Private Const SINGLEIO = &H20
Private Const DMAIO = &H40
Private Const BLOCKIO = &H60

Private Const BYTEXFER = &H0
Private Const WORDXFER = &H100

Private Const INDIVIDUAL = &H0
Private Const SIMULTANEOUS = &H200

Private Const Filter = &H0
Private Const NOFILTER = &H400

Private Const NORMMEMORY = &H0
Private Const EXTMEMORY = &H800

Private Const BURSTMODE = &H1000

Private Const NOTODINTS = &H2000

Private Const EXTTRIG = &H4000

Private Const NOCALIBRATEDATA = &H8000
Private Const CALIBRATEDATA = &H0

Private Const Enabled = 1
Private Const DISABLED = 0


' Types of error reporting
Private Const DONTPRINT = 0
Private Const PRINTWARNINGS = 1
Private Const PRINTFATAL = 2
Private Const PRINTALL = 3

' Types of error handling
Private Const DONTSTOP = 0
Private Const STOPFATAL = 1
Private Const STOPALL = 2

' Types of digital input ports
Private Const DIGITALOUT = 1
Private Const DIGITALIN = 2

' DT Modes for cbSetDTMode ()
Private Const DTIN = 0
Private Const DTOUT = 2

Private Const FROMHERE = -1
Private Const GETFIRST = -2
Private Const GETNEXT = -3

'  Temperature scales
'Private Const CELSIUS = 0
'Private Const FAHRENHEIT = 1
'Private Const KELVIN = 2

                          
' Types of digital I/O Ports
Private Const AUXPORT = 1
Private Const FIRSTPORTA = 10
Private Const FIRSTPORTB = 11
Private Const FIRSTPORTCL = 12
Private Const FIRSTPORTCH = 13
Private Const SECONDPORTA = 14
Private Const SECONDPORTB = 15
Private Const SECONDPORTCL = 16
Private Const SECONDPORTCH = 17
Private Const THIRDPORTA = 18
Private Const THIRDPORTB = 19
Private Const THIRDPORTCL = 20
Private Const THIRDPORTCH = 21
Private Const FOURTHPORTA = 22
Private Const FOURTHPORTB = 23
Private Const FOURTHPORTCL = 24
Private Const FOURTHPORTCH = 25
Private Const FIFTHPORTA = 26
Private Const FIFTHPORTB = 27
Private Const FIFTHPORTCL = 28
Private Const FIFTHPORTCH = 29
Private Const SIXTHPORTA = 30
Private Const SIXTHPORTB = 31
Private Const SIXTHPORTCL = 32
Private Const SIXTHPORTCH = 33
Private Const SEVENTHPORTA = 34
Private Const SEVENTHPORTB = 35
Private Const SEVENTHPORTCL = 36
Private Const SEVENTHPORTCH = 37
Private Const EIGHTHPORTA = 38
Private Const EIGHTHPORTB = 39
Private Const EIGHTHPORTCL = 40
Private Const EIGHTHPORTCH = 41

            
' Selectable A/D Ranges codes
'Private Const BIP10VOLTS = 1                    ' Bipolar Ranges (-10 to +10 Volts)
'Private Const BIP5VOLTS = 0
'Private Const BIP2PT5VOLTS = 2
'Private Const BIP1PT25VOLTS = 3
'Private Const BIP1VOLTS = 4
'Private Const BIPPT625VOLTS = 5
'Private Const BIPPT5VOLTS = 6
'Private Const BIPPT1VOLTS = 7
'Private Const BIPPT05VOLTS = 8
'Private Const BIPPT01VOLTS = 9
'Private Const BIPPT005VOLTS = 10
'Private Const BIP1PT67VOLTS = 11

'Private Const UNI10VOLTS = 100                  ' Unipolar Ranges (0 to 10 Volts)
'Private Const UNI5VOLTS = 101
'Private Const UNI2PT5VOLTS = 102
'Private Const UNI2VOLTS = 103
'Private Const UNI1PT25VOLTS = 104
'Private Const UNI1VOLTS = 105
'Private Const UNIPT1VOLTS = 106
'Private Const UNIPT01VOLTS = 107
'Private Const UNIPT02VOLTS = 108
'Private Const UNI1PT67VOLTS = 109

'Private Const MA4TO20 = 200                     ' Current Ranges (4 to 20 ma )
'Private Const MA2to10 = 201
'Private Const MA1TO5 = 202
'Private Const MAPT5TO2PT5 = 203


' Types of D/A
'Private Const ADDA1 = 0
'Private Const ADDA2 = 1

' 8536 counter output 1 control
'Private Const NOTLINKED = 0
'Private Const GATECTR2 = 1
'Private Const TRIGCTR2 = 2
'Private Const INCTR2 = 3

' Types of 8254 Counter configurations
'Private Const HIGHONLASTCOUNT = 0
'Private Const ONESHOT = 1
'Private Const RATEGENERATOR = 2
'Private Const SQUAREWAVE = 3
'Private Const SOFTWARESTROBE = 4
'Private Const HARDWARESTROBE = 5

' Where to reload from for 9513 counters
'Private Const LOADREG = 0
'Private Const LOADANDHOLDREG = 1

' Counter recycle modes
'Private Const ONETIME = 0
'Private Const RECYCLE = 1

' Direction of counting for 9513 counters
'Private Const COUNTDOWN = 0
'Private Const COUNTUP = 1

' Types of count detection for 9513 counters
'Private Const POSITIVEEDGE = 0
'Private Const NEGATIVEEDGE = 1

' Counter output control
'Private Const ALWAYSLOW = 0
'Private Const HIGHPULSEONTC = 1
'Private Const TOGGLEONTC = 2
'Private Const DISCONNECTED = 4
'Private Const LOWPULSEONTC = 5
'Private Const HIGHUNTILTC = 6

' Counter input sources
'Private Const TCPREVCTR = 0
'Private Const CTRINPUT1 = 1
'Private Const CTRINPUT2 = 2
'Private Const CTRINPUT3 = 3
'Private Const CTRINPUT4 = 4
'Private Const CTRINPUT5 = 5
'Private Const GATE1 = 6
'Private Const GATE2 = 7
'Private Const GATE3 = 8
'Private Const GATE4 = 9
'Private Const GATE5 = 10
'Private Const FREQ1 = 11
'Private Const FREQ2 = 12
'Private Const FREQ3 = 13
'Private Const FREQ4 = 14
'Private Const FREQ5 = 15
'Private Const CTRINPUT6 = 101
'Private Const CTRINPUT7 = 102
'Private Const CTRINPUT8 = 103
'Private Const CTRINPUT9 = 104
'Private Const CTRINPUT10 = 105
'Private Const GATE6 = 106
'Private Const GATE7 = 107
'Private Const GATE8 = 108
'Private Const GATE9 = 109
'Private Const GATE10 = 110
'Private Const FREQ6 = 111
'Private Const FREQ7 = 112
'Private Const FREQ8 = 113
'Private Const FREQ9 = 114
'Private Const FREQ10 = 115
'Private Const CTRINPUT11 = 201
'Private Const CTRINPUT12 = 202
'Private Const CTRINPUT13 = 203
'Private Const CTRINPUT14 = 204
'Private Const CTRINPUT15 = 205
'Private Const GATE11 = 206
'Private Const GATE12 = 207
'Private Const GATE13 = 208
'Private Const GATE14 = 209
'Private Const GATE15 = 210
'Private Const FREQ11 = 211
'Private Const FREQ12 = 212
'Private Const FREQ13 = 213
'Private Const FREQ14 = 214
'Private Const FREQ15 = 215
'Private Const CTRINPUT16 = 301
'Private Const CTRINPUT17 = 302
'Private Const CTRINPUT18 = 303
'Private Const CTRINPUT19 = 304
'Private Const CTRINPUT20 = 305
'Private Const GATE16 = 306
'Private Const GATE17 = 307
'Private Const GATE18 = 308
'Private Const GATE19 = 309
'Private Const GATE20 = 310
'Private Const FREQ16 = 311
'Private Const FREQ17 = 312
'Private Const FREQ18 = 313
'Private Const FREQ19 = 314
'Private Const FREQ20 = 315

' Counter registers
'Private Const LOADREG1 = 1
'Private Const LOADREG2 = 2
'Private Const LOADREG3 = 3
'Private Const LOADREG4 = 4
'Private Const LOADREG5 = 5
'Private Const LOADREG6 = 6
'Private Const LOADREG7 = 7
'Private Const LOADREG8 = 8
'Private Const LOADREG9 = 9
'Private Const LOADREG10 = 10
'Private Const LOADREG11 = 11
'Private Const LOADREG12 = 12
'Private Const LOADREG13 = 13
'Private Const LOADREG14 = 14
'Private Const LOADREG15 = 15
'Private Const LOADREG16 = 16
'Private Const LOADREG17 = 17
'Private Const LOADREG18 = 18
'Private Const LOADREG19 = 19
'Private Const LOADREG20 = 20
'Private Const HOLDREG1 = 101
'Private Const HOLDREG2 = 102
'Private Const HOLDREG3 = 103
'Private Const HOLDREG4 = 104
'Private Const HOLDREG5 = 105
'Private Const HOLDREG6 = 106
'Private Const HOLDREG7 = 107
'Private Const HOLDREG8 = 108
'Private Const HOLDREG9 = 109
'Private Const HOLDREG10 = 110
'Private Const HOLDREG11 = 111
'Private Const HOLDREG12 = 112
'Private Const HOLDREG13 = 113
'Private Const HOLDREG14 = 114
'Private Const HOLDREG15 = 115
'Private Const HOLDREG16 = 116
'Private Const HOLDREG17 = 117
'Private Const HOLDREG18 = 118
'Private Const HOLDREG19 = 119
'Private Const HOLDREG20 = 120

'Private Const ALARM1CHIP1 = 201
'Private Const ALARM2CHIP1 = 202
'Private Const ALARM1CHIP2 = 301
'Private Const ALARM2CHIP2 = 302
'Private Const ALARM1CHIP3 = 401
'Private Const ALARM2CHIP3 = 402
'Private Const ALARM1CHIP4 = 501
'Private Const ALARM2CHIP4 = 502

'  Counter Gate Control
'Private Const NOGATE = 0
'Private Const AHLTCPREVCTR = 1
'Private Const AHLNEXTGATE = 2
'Private Const AHLPREVGATE = 3
'Private Const AHLGATE = 4
'Private Const ALLGATE = 5
'Private Const AHEGATE = 6
'Private Const ALEGATE = 7


' Types of triggers
'Private Const TRIGABOVE = 0
'Private Const TRIGBELOW = 1

' Types of configuration information
Private Const GLOBALINFO = 1
Private Const BOARDINFO = 2
Private Const DIGITALINFO = 3
Private Const COUNTERINFO = 4
Private Const EXPANSIONINFO = 5
Private Const MISCINFO = 6


' Types of global configuration information
Private Const GIVERSION = 36        ' Config file format version number
Private Const GINUMBOARDS = 38      ' Maximum number of boards
Private Const GINUMEXPBOARDS = 40   ' Maximum number of expansion boards

' Types of board configuration information
Private Const BIBASEADR = 0         ' Base Address
Private Const BIBOARDTYPE = 1       ' Board Type (0x101 - 0x7FFF)
Private Const BIINTLEVEL = 2        ' Interrupt level
Private Const BIDMACHAN = 3         ' DMA channel
Private Const BIINITIALIZED = 4     ' TRUE or FALSE
Private Const BICLOCK = 5           ' Clock freq (1, 10 or bus)
Private Const BIRANGE = 6           ' Switch selectable range
Private Const BINUMADCHANS = 7      ' Number of A/D channels
Private Const BIUSESEXPS = 8        ' Supports expansion boards TRUE/FALSE
Private Const BIDINUMDEVS = 9       ' Number of digital devices
Private Const BIDIDEVNUM = 10       ' Index into digital information
Private Const BICINUMDEVS = 11      ' Number of counter devices
Private Const BICIDEVNUM = 12       ' Index into counter information
Private Const BINUMDACHANS = 13     ' Number of D/A channels
Private Const BIWAITSTATE = 14      ' Wait state enabled TRUE/FALSE
Private Const BINUMIOPORTS = 15     ' I/O address space used by board
Private Const BIPARENTBOARD = 16    ' Board number of parent board
Private Const BIDTBOARD = 17        ' Board number of connected DT board

' Types of digital device information
Private Const DIBASEADR = 0         ' Base address
Private Const DIINITIALIZED = 1     ' TRUE or FALSE
Private Const DIDEVTYPE = 2         ' AUXPORT or xPORTA - CH
Private Const DIMASK = 3            ' Bit mask for this port
Private Const DIREADWRITE = 4       ' Read required before write
Private Const DICONFIG = 5          ' Current configuration
Private Const DINUMBITS = 6         ' Number of bits in port
Private Const DICURVAL = 7          ' Current value of outputs

' Types of counter device information
'Private Const CIBASEADR = 0         ' Base address
'Private Const CIINITIALIZED = 1     ' TRUE or FALSE
'Private Const CICTRTYPE = 2         ' Counter type 8254, 9513 or 8536
'Private Const CICTRNUM = 3          ' Which counter on chip
'Private Const CICONFIGBYTE = 4      ' Configuration byte

' Types of expansion board information
'Private Const XIBOARDTYPE = 0       ' Expansion board type
'Private Const XIMUXADCHAN1 = 1      ' 0 - 15
'Private Const XIMUXADCHAN2 = 2      ' 0 - 15 or NOTUSED
'Private Const XIRANGE1 = 3          ' Range (gain) of low 16 chans
'Private Const XIRANGE2 = 4          ' Range (gain) of high 16 chans
'Private Const XICJCCHAN = 5         ' 0 - 15 or NOTUSED
'Private Const XITHERMTYPE = 6       ' TYPEJ, TYPEK, TYPEB, TYPET, TYPEE, TYPER, or TYPES
'Private Const XINUMEXPCHANS = 7     ' Number of expansion channels on board
'Private Const XIPARENTBOARD = 8     ' Board number of parent A/D board
'Private Const XISPARE0 = 9          ' 16 words of misc options

'  Digital I/O functions used
Private Declare Function cbDBitIn% Lib "cbw32.dll" (ByVal BoardNum%, ByVal PortType%, ByVal BitNum%, BitValue%)
Private Declare Function cbDBitOut% Lib "cbw32.dll" (ByVal BoardNum%, ByVal PortType%, ByVal BitNum%, ByVal BitValue%)
Private Declare Function cbDIn% Lib "cbw32.dll" (ByVal BoardNum%, ByVal PortNum%, DataValue%)

'  Used in the Initialization process
Private Declare Function cbDeclareRevision% Lib "cbw32.dll" (RevNum!)
Private Declare Function cbDConfigPort% Lib "cbw32.dll" (ByVal BoardNum%, ByVal PortNum%, ByVal Direction%)
Private Declare Function cbErrHandling% Lib "cbw32.dll" (ByVal ErrReporting%, ByVal ErrHandling%)
Private Declare Function cbGetRevision% Lib "cbw32.dll" (DLLRevNum!, VXDRevNum!)

'  Status and error handling
Private Declare Function cbGetErrMsg% Lib "cbw32.dll" (ByVal ErrCode%, ByVal ErrMsg$)
Private Declare Function cbGetStatus% Lib "cbw32.dll" (ByVal BoardNum%, Status%, CurCount&, CurIndex&)
      
'  These are not used as of yet
'Private Declare Function cbAConvertData% Lib "cbw32.dll" (ByVal BoardNum%, ByVal NumPoints&, ADData%, ChanTags%)
'Private Declare Function cbACalibrateData% Lib "cbw32.dll" (ByVal BoardNum%, ByVal NumPoints&, ByVal Gain%, ADData%)
'Private Declare Function cbAConvertPretrigData% Lib "cbw32.dll" (ByVal BoardNum%, ByVal PretrigCount&, ByVal TotalCount&, ADData%, ChanTags%)
'Private Declare Function cbAIn% Lib "cbw32.dll" (ByVal BoardNum%, ByVal Chan%, ByVal Gain%, DataValue%)
'Private Declare Function cbAInScan% Lib "cbw32.dll" (ByVal BoardNum%, ByVal LowChan%, ByVal HighChan%, ByVal CBCount&, CBRate&, ByVal Gain%, ByVal MemHandle%, ByVal Options%)
'Private Declare Function cbALoadQueue% Lib "cbw32.dll" (ByVal BoardNum%, ChanArray%, GainArray%, ByVal NumChans%)
'Private Declare Function cbAOut% Lib "cbw32.dll" (ByVal BoardNum%, ByVal Chan%, ByVal Gain%, ByVal DataValue%)
'Private Declare Function cbAOutScan% Lib "cbw32.dll" (ByVal BoardNum%, ByVal LowChan%, ByVal HighChan%, ByVal CBCount&, CBRate&, ByVal Gain%, ByVal MemHandle%, ByVal Options%)
'Private Declare Function cbAPretrig% Lib "cbw32.dll" (ByVal BoardNum%, ByVal LowChan%, ByVal HighChan%, PretrigCount&, CBCount&, CBRate&, ByVal Gain%, ByVal MemHandle%, ByVal Options%)
'Private Declare Function cbATrig% Lib "cbw32.dll" (ByVal BoardNum%, ByVal Chan%, ByVal TrigType%, ByVal TrigValue%, ByVal Gain%, DataValue%)
'Private Declare Function cbC8254Config% Lib "cbw32.dll" (ByVal BoardNum%, ByVal CounterNum%, ByVal Config%)
'Private Declare Function cbC8536Config% Lib "cbw32.dll" (ByVal BoardNum%, ByVal CounterNum%, ByVal OutputControl%, ByVal RecycleMode%, ByVal Retrigger%)
'Private Declare Function cbC9513Config% Lib "cbw32.dll" (ByVal BoardNum%, ByVal CounterNum%, ByVal GateControl%, ByVal CounterEdge%, ByVal CountSource%, ByVal SpecialGate%, ByVal Reload%, ByVal RecycleMode%, ByVal BCDMode%, ByVal CountDirec%, ByVal OutputCtrl%)
'Private Declare Function cbC8536Init% Lib "cbw32.dll" (ByVal BoardNum%, ByVal ChipNum%, ByVal Ctr1Output%)
'Private Declare Function cbC9513Init% Lib "cbw32.dll" (ByVal BoardNum%, ByVal ChipNum%, ByVal FOutDivider%, ByVal FOutSource%, ByVal Compare1%, ByVal Compare2%, ByVal TimeOfDay%)
'Private Declare Function cbCStoreOnInt% Lib "cbw32.dll" (ByVal BoardNum%, ByVal IntCount%, CntrControl%, ByVal DataBuffer%)
'Private Declare Function cbCFreqIn% Lib "cbw32.dll" (ByVal BoardNum%, ByVal SigSource%, ByVal GateInterval%, CBCount%, Freq&)
'Private Declare Function cbCIn% Lib "cbw32.dll" (ByVal BoardNum%, ByVal CounterNum%, CBCount%)
'Private Declare Function cbCLoad% Lib "cbw32.dll" (ByVal BoardNum%, ByVal RegNum%, ByVal LoadValue%)
'Private Declare Function cbDConfigPort% Lib "cbw32.dll" (ByVal BoardNum%, ByVal PortNum%, ByVal Direction%)
'Private Declare Function cbDIn% Lib "cbw32.dll" (ByVal BoardNum%, ByVal PortNum%, DataValue%)
'Private Declare Function cbDInScan% Lib "cbw32.dll" (ByVal BoardNum%, ByVal PortNum%, ByVal CBCount&, CBRate&, ByVal MemHandle%, ByVal Options%)
'Private Declare Function cbDOut% Lib "cbw32.dll" (ByVal BoardNum%, ByVal PortNum%, ByVal DataValue%)
'Private Declare Function cbDOutScan% Lib "cbw32.dll" (ByVal BoardNum%, ByVal PortNum%, ByVal CBCount&, CBRate&, ByVal MemHandle%, ByVal Options%)
'Private Declare Function cbFileAInScan% Lib "cbw32.dll" (ByVal BoardNum%, ByVal LowChan%, ByVal HighChan%, ByVal CBCount&, CBRate&, ByVal Gain%, ByVal FileName$, ByVal Options%)
'Private Declare Function cbFileGetInfo% Lib "cbw32.dll" (ByVal FileName$, LowChan%, HighChan%, PretrigCount&, TotalCount&, CBRate&, Gain%)
'Private Declare Function cbFilePretrig% Lib "cbw32.dll" (ByVal BoardNum%, ByVal LowChan%, ByVal HighChan%, PretrigCount&, CBCount&, CBRate&, ByVal Gain%, ByVal FileName$, ByVal Options%)
'Private Declare Function cbFileRead% Lib "cbw32.dll" (ByVal FileName$, ByVal FirstPoint&, NumPoints&, DataBuffer%)
'Private Declare Function cbStopBackground% Lib "cbw32.dll" (ByVal BoardNum%)
'Private Declare Function cbMemSetDTMode% Lib "cbw32.dll" (ByVal BoardNum%, ByVal Mode%)
'Private Declare Function cbMemReset% Lib "cbw32.dll" (ByVal BoardNum%)
'Private Declare Function cbMemRead% Lib "cbw32.dll" (ByVal BoardNum%, DataBuffer%, ByVal FirstPoint&, ByVal CBCount&)
'Private Declare Function cbMemWrite% Lib "cbw32.dll" (ByVal BoardNum%, DataBuffer%, ByVal FirstPoint&, ByVal CBCount&)
'Private Declare Function cbMemReadPretrig% Lib "cbw32.dll" (ByVal BoardNum%, DataBuffer%, ByVal FirstPoint&, ByVal CBCount&)
'Private Declare Function cbRS485% Lib "cbw32.dll" (ByVal BoardNum%, ByVal Transmit%, ByVal Receive%)
'Private Declare Function cbTIn% Lib "cbw32.dll" (ByVal BoardNum%, ByVal Chan%, ByVal CBScale%, TempValue!, ByVal Options%)
'Private Declare Function cbTInScan% Lib "cbw32.dll" (ByVal BoardNum%, ByVal LowChan%, ByVal HighChan%, ByVal CBScale%, DataBuffer!, ByVal Options%)
'Private Declare Function cbWinBufToArray% Lib "cbw32.dll" (ByVal MemHandle%, DataBuffer%, ByVal FirstPoint&, ByVal CBCount&)
'Private Declare Function cbWinArrayToBuf% Lib "cbw32.dll" (DataBuffer%, ByVal MemHandle%, ByVal FirstPoint&, ByVal CBCount&)
'Private Declare Function cbWinBufAlloc% Lib "cbw32.dll" (ByVal NumPoints&)
'Private Declare Function cbWinBufFree% Lib "cbw32.dll" (ByVal MemHandle%)
'Private Declare Function cbInByte% Lib "cbw32.dll" (ByVal BoardNum%, ByVal PortNum%)
'Private Declare Function cbOutByte% Lib "cbw32.dll" (ByVal BoardNum%, ByVal PortNum%, ByVal PortVal%)
'Private Declare Function cbInWord% Lib "cbw32.dll" (ByVal BoardNum%, ByVal PortNum%)
'Private Declare Function cbOutWord% Lib "cbw32.dll" (ByVal BoardNum%, ByVal PortNum%, ByVal PortVal%)
'Private Declare Function cbGetConfig% Lib "cbw32.dll" (ByVal InfoType%, ByVal BoardNum%, ByVal DevNum%, ByVal ConfigItem%, ConfigVal%)
'Private Declare Function cbSetConfig% Lib "cbw32.dll" (ByVal InfoType%, ByVal BoardNum%, ByVal DevNum%, ByVal ConfigItem%, ByVal ConfigVal%)
'Private Declare Function cbToEngUnits% Lib "cbw32.dll" (ByVal BoardNum%, ByVal Range%, ByVal DataVal%, EngUnits!)
'Private Declare Function cbFromEngUnits% Lib "cbw32.dll" (ByVal BoardNum%, ByVal Range%, ByVal EngUnits!, DataVal%)
'Private Declare Function cbGetBoardName% Lib "cbw32.dll" (ByVal BoardNum%, ByVal BoardName$)




Public Function InputPort(intBoardNum As Integer, strPortNum As String) As Integer
   
   Dim intDataValue As Integer
   Dim intCBRet As Integer
   
   intCBRet = cbDIn%(intBoardNum, PortNum(strPortNum, intBoardNum), intDataValue)
   InputPort = intDataValue
   
End Function 'InputPort

Public Function BitOut(intBoardNum As Integer, _
                        intBitNum As Integer, intValue As Integer) As Integer
   
   BitOut = cbDBitOut%(intBoardNum, FIRSTPORTA, intBitNum, intValue)

End Function 'BitOut

Public Function BitIn(intBoardNum As Integer, _
                                 intBitNum As Integer, intValue As Integer) As Integer
                                 
   BitIn = cbDBitIn%(intBoardNum, FIRSTPORTA, intBitNum, intValue)

End Function 'BitIn



Public Function DeclareCurrentRevesion() As Integer

   ' declare revision level of Universal Library
   If g_blnSimulator Then
      DeclareCurrentRevesion = intCBStat
   Else
   
       DeclareCurrentRevesion = cbDeclareRevision(CURRENTREVNUM)
   End If

End Function 'DeclareCurrentRevesion

Public Function GetCurrentRevision(sglDLLRevNum As Single, _
                                   sglVDXRevNum As Single) As Integer

   GetCurrentRevision = cbGetRevision(sglDLLRevNum, sglVDXRevNum)
   
End Function 'GetCurrentRevision

Public Function InitErrHandle() As Integer

   If g_blnSimulator Then
      InitErrHandle = intCBStat
   Else
   
       InitErrHandle = cbErrHandling%(PRINTALL, DONTSTOP)
   End If
   
   
   
   
End Function 'InitErrHandle

Public Function ConfigurPort(intBoardNum As Integer, _
                             strProtName As String, strDirection As String) As Integer

   If g_blnSimulator Then
      ConfigurPort = intCBStat
   Else
   
       ConfigurPort = cbDConfigPort%(intBoardNum, PortNum(strProtName, intBoardNum), Direction(strDirection))
   End If
   
   
   
   

End Function 'ConfigurPort

Private Function PortNum(strProtName As String, intBoardNum As Integer) As Integer

   Select Case strProtName
      Case "A"
         Select Case intBoardNum
            Case 0
               PortNum = FIRSTPORTA
         End Select 'intBoardNum
      Case "B"
         Select Case intBoardNum
            Case 0
               PortNum = FIRSTPORTB
         End Select 'intBoardNum
      Case "CL"
         Select Case intBoardNum
            Case 0
               PortNum = FIRSTPORTCL
         End Select 'intBoardNum
      Case "CH"
         Select Case intBoardNum
            Case 0
               PortNum = FIRSTPORTCH
         End Select 'intBoardNum
   End Select 'strProtName
   
End Function 'PortNum

Private Function Direction(strTypes As String) As Integer

   If strTypes = g_strOUTPUT Then
      Direction = DIGITALOUT
   ElseIf strTypes = g_strINPUT Then
      Direction = DIGITALIN
   End If

End Function 'Direction

Public Function GetErrorMsg(intErr As Integer) As String

   Dim intRsp As Integer
   Dim strTemp As String * ERRSTRLEN
   
   intRsp = cbGetErrMsg%(intErr, strTemp)
   
   GetErrorMsg = Trim(strTemp)
   
End Function ' GetErrorMsg
