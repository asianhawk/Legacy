VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsMicroscan"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

'******************************************************************
'  Constant
'******************************************************************
'  Communication port settings
Private Const m_intPROT_ID = 6
Private Const m_strPORT_SETTINGS = "9600,E,7,1"
Private Const m_vbcHAND_SHAKING = comNone 'vb constent
Private Const m_blnDTR_ENABLE = True
Private Const m_blnRTSENABLE = False
Private Const m_intR_THRESHOLD = 1
Private Const m_blnNULL_DISCARD = True
Private Const m_chrPARITY_REPLACE = ""
Private Const m_intS_THRESHOLD = 0
Private Const m_intCTS_TIMEOUT = 0
Private Const m_intDSR_TIMEOUT = 0
Private Const m_intOUT_BUFFER_SIZE = 1024
Private Const m_intIN_BUFFER_SIZE = 1024
Private Const m_chrEND_TX_MARK = vbCrLf
Private Const m_intWATCH_DOG = 2000  'in millSeconds set to 1 seconds

Private Const m_intRESET_WAIT_SEC = 1

'******************************************************************
'  Command strings
Private Const m_chrSTART = "<"
Private Const m_chrSTOP = ">"

'  Program management
Private Const m_chrSOFTWARE_RESET = "A" 'Initializes the scaner
Private Const m_chrRESTORE_ROM = "Ad" 'Restores defaults from ROM
Private Const m_chrRESTROE_NVRAM = "An" ' Restores nonvolatile RAM
Private Const m_chrSAVE_NVRAM = "Z" '  Save to nonvolatile RAM

'  Device control
Private Const m_chrLASER_ON = "H"
Private Const m_chrLASER_OFF = "I"
Private Const m_chrMOTER_ON = "KE"
Private Const m_chrMOTER_OFF = "KF"
Private Const m_chrREALY1_PULSE = "L1"
Private Const m_chrREALY2_PLUSE = "L2"

'  Code Types
Private Const m_chrAUTO_ALL = "P"
Private Const m_chrCODE_39 = "Q"
Private Const m_chrCODABAR = "R"
Private Const m_chrI2OF5 = "S"

'  Test
Private Const m_chrDECODE_RATE_TEST = "C"
Private Const m_chrDECODE_EXTENDED_RATE_TEST = "Ce"
Private Const m_chrSTOP_DECODE_RATE_TEST = "J"

'  Version inquire
'  ROM software part number
Private Const m_chrSW_PART_NUMBER = "#"
Private Const m_chrEPROM_CHECK_SUM = "!"
Private Const m_chrSTATUS = "?"

' Read label
Private Const m_chrREAD_LABEL_TRIGER = "b"

'******************************************************************
'  class specific data
'  class initialization status
Private m_blnInitStatus As Boolean

Private m_strName As String


Private m_strROM_SW_Part_Number As String

'  declare the communications class
Private m_objMicroscanPort As clsSerialCommCtrl

Public Function InitStatus() As Boolean
   
   InitStatus = m_blnInitStatus
   
End Function 'InitStatus


Public Function ReadlBarCode() As String

   Dim strBuf As String
   
   If SendCommand(m_chrREAD_LABEL_TRIGER) Then
      If ReceiveResponse(strBuf) Then
         ReadlBarCode = strBuf
      End If
   End If
   
End Function 'ReadlBarCode

Private Sub Class_Initialize()
   
   m_strName = "clsMicroscan"
   
   m_blnInitStatus = True
   
   '  Open the communication port
   Set m_objMicroscanPort = New clsSerialCommCtrl
   m_blnInitStatus = m_objMicroscanPort.Initialize(intPortID:=m_intPROT_ID, strEndTXMark:=m_chrEND_TX_MARK, _
                           strPortSettings:=m_strPORT_SETTINGS, intTimerInterval:=m_intWATCH_DOG, _
                           vbHandShaking:=m_vbcHAND_SHAKING, blnDTREnable:=m_blnDTR_ENABLE, _
                           blnRTSEnable:=m_blnRTSENABLE, intRThreshold:=m_intR_THRESHOLD, _
                           blnNullDiscard:=m_blnNULL_DISCARD, chrParityReplace:=m_chrPARITY_REPLACE, _
                           intSThreshold:=m_intS_THRESHOLD, intCTSTimeout:=m_intCTS_TIMEOUT, _
                           intDSRTimeout:=m_intDSR_TIMEOUT, intOutBufferSize:=m_intOUT_BUFFER_SIZE, _
                           intInBufferSize:=m_intIN_BUFFER_SIZE, strName:=m_strName)
   m_blnInitStatus = SendReset()
   m_blnInitStatus = InquireVersion()

End Sub 'Class_Initialize



Private Function InquireVersion() As Boolean

   Dim strBuf As String
   
   If g_blnSimulator Then
      InquireVersion = True
      Exit Function
   Else
   
     InquireVersion = False
   End If
   
   If SendCommand(m_chrSW_PART_NUMBER) Then
      If ReceiveResponse(strBuf) Then
         m_strROM_SW_Part_Number = strBuf
         InquireVersion = True
      End If
   End If
   
End Function 'InquireVersion

Private Function SendCommand(strOut As String) As Boolean

     If Not g_blnSimulator Then
         m_objMicroscanPort.Buffer = m_chrSTART & strOut & m_chrSTOP
     End If
     
     SendCommand = True
     
End Function 'SendCommand

Private Function ReceiveResponse(ByRef r_strIN As String) As Boolean

   Dim strBuf As String
   
   strBuf = m_objMicroscanPort.Buffer
   If strBuf = "" Then
      ReceiveResponse = False
   Else
      r_strIN = Left((strBuf), Len(strBuf) - Len(m_chrEND_TX_MARK))
      ReceiveResponse = True
   End If
   
End Function 'ReceiveResponse

Public Function Version() As String

   Version = m_strROM_SW_Part_Number
   
End Function 'Version

Public Function SendReset() As Boolean
   
   SendCommand (m_chrRESTROE_NVRAM)
   
   Call modAPI.SleepSec(m_intRESET_WAIT_SEC)
   
End Function 'SendReset
