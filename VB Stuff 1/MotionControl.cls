VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsMotionControl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
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
'*          IAI control class
'*
'*    Date of origin: 12/29/96
'*    Original author: Michael D. Reed
'*
'* Class purpose:
'*    This class provides the interface between the
'*    IAI and the 3-Axis Label Applicator control program.
'*
'************************************************************************
'******************************************************************

Option Explicit

'******************************************************************
'  Constant
'******************************************************************
'  Common Constant
Private Const m_intMAX_AXIES = 2

'  Communication port settings
Private Const m_intPROT_ID = 5
Private Const m_strPORT_SETTINGS = "9600,n,8,1"
Private Const m_vbcHAND_SHAKING = comRTS
Private Const m_blnDTR_ENABLE = True
Private Const m_blnRTSENABLE = True
Private Const m_intR_THRESHOLD = 1
Private Const m_blnNULL_DISCARD = True
Private Const m_chrPARITY_REPLACE = ""
Private Const m_intS_THRESHOLD = 0
Private Const m_intCTS_TIMEOUT = 0
Private Const m_intDSR_TIMEOUT = 0
Private Const m_intOUT_BUFFER_SIZE = 1024
Private Const m_intIN_BUFFER_SIZE = 1024

Private Const m_strEND_TX_MARK = vbCrLf

Private Const m_intWATCH_DOG = 1000  'in millSeconds set to 1 second
Private Const m_intEXE_TIMEOUT = 200 ' in millseconds set to .2 sec

'Private Const m_intRESET_WAIT_SEC = 6
'Private Const m_intWRITE_CARD_WAIT_SEC = 6

Private Const m_intRESET_WAIT_SEC = 3
Private Const m_intWRITE_CARD_WAIT_SEC = 3

'******************************************************************
'  Command Constant
'******************************************************************
'  Communitations Constant
Private Const m_posCOMMAND_CHAR = 1   'IAI string position 0
Private Const m_chrCOMMAND_CHAR = "?"
Private Const m_chrEXE_COMMAND = "/"

Private Const m_posRSPONSE_CHAR = 1   'IAI string position 0
Private Const m_chrNORMAL_RESPONSE = "#"

Private Const m_chrERROR_RESPONSE = "%"
Private Const m_posERROR_CODE = 4   'IAI string position 3
Private Const m_lenERROR_CODE = 2

Private Const m_posCONTROLLER = 2 ' IAI string position 0
Private Const m_strMASTER_NUMBER = "99"

'  The string ends with a check sum and a CRLF
Private Const m_strNO_CHECK_SUM = "@@"

'******************************************************************
'   General commands section
'   Reset
Private Const m_strRESET = "!!"

'  ROM Version inquire
Private Const m_strVERSION = "IR"
'  ROM Version responce
Private Const m_posVERSION = 6 'IAI string position 5
Private Const m_lenVERSION = 5
Private Const m_lenDATE_INFO = 2
Private Const m_posYEAR = 11 'IAI string position = 10
Private Const m_posMONTH = 14 'IAI string position = 13
Private Const m_posDAY = 17 'IAI string position = 16

'  Write to card
Private Const m_strWRITE_CARD = "/C"
Private Const m_strWRITE_ALL = "0"
Private Const m_strWRITE_PARAMETER = "1"
Private Const m_strWRITE_PROGRAM = "2"
Private Const m_strWRITE_POINT = "3"
Private Const m_strWRITE_FORAMT = "4"
Private Const m_fmtWRITE_CARD = "0"

'******************************************************************
'  Points section
'  Set point data
Private Const m_strSET_POINT = "/0"
Private Const m_fmtPOINT_NUM = "0000"
Private Const m_strPOINT_EXISTS = "1"
Private Const m_strNO_POINT = "0"
Private Const m_fmtPOINT_DATA = "000000"  'in .01mm

'  Get point data inquier
Private Const m_strGET_POINT = "QP"
'  format point number see set point data
Private Const m_lenPOINT_NUM = 4
Private Const m_posPOINT_NUM = 6    'IAI string position = 5
Private Const m_intPOINT_EXISTS_OFFSET = -1
Private Const m_lenAXIES_POINT = 6
Private Const m_posAXIES1_POINT = 11  'IAI string position = 10
Private Const m_posAXIES2_POINT = 18  'IAI string position = 17
Private Const m_posAXIES3_POINT = 25  'IAI string position = 24
Private Const m_posAXIES4_POINT = 32  'IAI string position = 31

'  Define a data point
Private Const m_idxPtNum = 0
Private Const m_idxX = 1
Private Const m_idxY = 2
Private Const m_idxZ = 3
Private Const m_idxTH = 4

'******************************************************************
'  Program section
Private Const m_strEDIT_PROGRAM_CHANGE = "/1"
Private Const m_fmtPROGRAM_NUM = "00"
Private Const m_fmtPROGRAM_STEP = "0000"
'  Run program
Private Const m_strRUN_PROGRAM = "/5"
'  Stop program
Private Const m_strSTOP_PROGRAM = "/6"


'******************************************************************

'******************************************************************
'  class specific data

Private m_strName As String

'  Vesion inofmration
Private m_strROMVersion As String

'  class initialization status
Private m_blnInitStatus As Boolean

'  declare the communications class
Private m_objIAIPort As clsSerialCommCtrl

Public Function InitStatus() As Boolean
   
   InitStatus = m_blnInitStatus
   
End Function 'InitStatus


Public Function SendLabelsPerPanel( _
                                    strPROGRAM_NUMBER As String, _
                                    txtBoardCountCodeStep As String, _
                                    intLabels As Integer) As Boolean

   '  Info for the board count
   Const strCOMMAND_CODE = "73" 'Compar equal
   Const strEXTEND = "00"
   Const strCONDITION_1 = "01F5"
   Const strCONDITION_2 = "0000"
   Const strCONDITION_3 = "0000"
   Const strOPERAND_1 = "0C00"
   Const StrPOST = "7105"
   Const fmtLINE_NUM = "00000000"
   
   Dim strTempBuffer As String
   
   '  Build string
   strTempBuffer = Format(strPROGRAM_NUMBER, m_fmtPROGRAM_NUM)
   strTempBuffer = strTempBuffer & Format(txtBoardCountCodeStep, m_fmtPROGRAM_STEP)
   strTempBuffer = strTempBuffer & strCOMMAND_CODE
   strTempBuffer = strTempBuffer & strEXTEND
   strTempBuffer = strTempBuffer & strCONDITION_1
   strTempBuffer = strTempBuffer & strCONDITION_2
   strTempBuffer = strTempBuffer & strCONDITION_3
   strTempBuffer = strTempBuffer & strOPERAND_1
   strTempBuffer = strTempBuffer & SwapChar(FormatHex(intLabels, fmtLINE_NUM), 2)
   strTempBuffer = strTempBuffer & StrPOST
   
   '  Now send it to the IAI
   SendLabelsPerPanel = ChangeCodeLine(strOutCode:=strTempBuffer)

   modUtilities.MessageDisplay LoadResString(resWRITING_CARD)
   SendLabelsPerPanel = WriteCardProgram()
   modUtilities.MessageRemove
   
End Function 'SendLabelsPerPanel

Private Function InquireVersion() As Boolean

   Dim strBuffer As String
   Dim blnResp As Boolean
   
   blnResp = SendCommand(BuildCommand(m_strVERSION))
   blnResp = ReceiveResponce(strBuffer)
   If blnResp And (strBuffer <> "") Then
      InquireVersion = True
      m_strROMVersion = Mid(strBuffer, m_posVERSION, m_lenVERSION)
      m_strROMVersion = m_strROMVersion & "--"
      m_strROMVersion = m_strROMVersion & Mid(strBuffer, m_posMONTH, m_lenDATE_INFO)
      m_strROMVersion = m_strROMVersion & "/"
      m_strROMVersion = m_strROMVersion & Mid(strBuffer, m_posDAY, m_lenDATE_INFO)
      m_strROMVersion = m_strROMVersion & "/"
      m_strROMVersion = m_strROMVersion & Mid(strBuffer, m_posYEAR, m_lenDATE_INFO)
   Else
      m_strROMVersion = "Version error!"
      InquireVersion = False
   End If
   
End Function 'InquireVersion


Private Function BuildCommand(CommandData As String) As String

   BuildCommand = m_chrCOMMAND_CHAR & m_strMASTER_NUMBER & _
                  CommandData & m_strNO_CHECK_SUM & vbCrLf
   
End Function 'BuildCommand

Public Function SetScannerOffsets( _
                     strPROGRAM_NUMBER As String, _
                     txtScannerOffsetCodeStep As String, _
                     lngXScanner0Offset As Long, _
                     lngYScanner0Offset As Long, _
                     lngXScanner90Offset As Long, _
                     lngYScanner90Offset As Long) As Boolean

   '  Info for the board count
   Const strCOMMAND_CODE_PADD = "81"
   Const strCOMMAND_CODE_PSUB = "82"
   Const strEXTEND = "00"
   Const strCONDITION_1 = "01F5"
   Const strCONDITION_0_2 = "54F0"
   Const strCONDITION_90_2 = "5400"
   Const strCONDITION_3 = "0000"
   Const strOPERAND_1_X = "0100"
   Const strOPERAND_1_Y = "0200"
   Const StrPOST = "0000"
   Const fmtOFFSET = "00000000"
   Const fmtLINE_NUM = "0000"
   
   Dim strTempBuffer As String
   Dim blnStatus As Boolean
   Dim intCodeLine As Integer
      
   modUtilities.MessageDisplay LoadResString(resWRITING_SCANNER_OFFSETS_TO_IAI)
   SetScannerOffsets = True
   
   intCodeLine = CInt(txtScannerOffsetCodeStep)

   '  Build string for X at 0 deg
   strTempBuffer = Format(strPROGRAM_NUMBER, m_fmtPROGRAM_NUM)
   strTempBuffer = strTempBuffer & Format(intCodeLine, fmtLINE_NUM)
   If lngXScanner0Offset > 0 Then
    strTempBuffer = strTempBuffer & strCOMMAND_CODE_PADD
   Else
    strTempBuffer = strTempBuffer & strCOMMAND_CODE_PSUB
   End If
   strTempBuffer = strTempBuffer & strEXTEND
   strTempBuffer = strTempBuffer & strCONDITION_1
   strTempBuffer = strTempBuffer & strCONDITION_0_2
   strTempBuffer = strTempBuffer & strCONDITION_3
   strTempBuffer = strTempBuffer & strOPERAND_1_X
   strTempBuffer = strTempBuffer & _
         SwapChar(FormatHex(Abs(lngXScanner0Offset), fmtOFFSET), g_intSWAP_LEN_2)
   strTempBuffer = strTempBuffer & StrPOST

   '  Now send it to the IAI
   blnStatus = ChangeCodeLine(strOutCode:=strTempBuffer)

   If Not blnStatus Then
    SetScannerOffsets = False
    Exit Function
   End If

   '  Build string for Y at 0 deg
   strTempBuffer = Format(strPROGRAM_NUMBER, m_fmtPROGRAM_NUM)
   strTempBuffer = strTempBuffer & Format(intCodeLine + 1, fmtLINE_NUM)
   If lngXScanner0Offset > 0 Then
    strTempBuffer = strTempBuffer & strCOMMAND_CODE_PADD
   Else
    strTempBuffer = strTempBuffer & strCOMMAND_CODE_PSUB
   End If
   strTempBuffer = strTempBuffer & strEXTEND
   strTempBuffer = strTempBuffer & strCONDITION_1
   strTempBuffer = strTempBuffer & strCONDITION_0_2
   strTempBuffer = strTempBuffer & strCONDITION_3
   strTempBuffer = strTempBuffer & strOPERAND_1_Y
   strTempBuffer = strTempBuffer & _
         SwapChar(FormatHex(Abs(lngYScanner0Offset), fmtOFFSET), g_intSWAP_LEN_2)
   strTempBuffer = strTempBuffer & StrPOST

   '  Now send it to the IAI
   blnStatus = ChangeCodeLine(strOutCode:=strTempBuffer)

   If Not blnStatus Then
    SetScannerOffsets = False
    Exit Function
   End If

   '  Build string for X at 90 deg
   strTempBuffer = Format(strPROGRAM_NUMBER, m_fmtPROGRAM_NUM)
   strTempBuffer = strTempBuffer & Format(intCodeLine + 2, fmtLINE_NUM)
   If lngXScanner0Offset > 0 Then
    strTempBuffer = strTempBuffer & strCOMMAND_CODE_PADD
   Else
    strTempBuffer = strTempBuffer & strCOMMAND_CODE_PSUB
   End If
   strTempBuffer = strTempBuffer & strEXTEND
   strTempBuffer = strTempBuffer & strCONDITION_1
   strTempBuffer = strTempBuffer & strCONDITION_90_2
   strTempBuffer = strTempBuffer & strCONDITION_3
   strTempBuffer = strTempBuffer & strOPERAND_1_X
   strTempBuffer = strTempBuffer & _
         SwapChar(FormatHex(Abs(lngXScanner90Offset), fmtOFFSET), g_intSWAP_LEN_2)
   strTempBuffer = strTempBuffer & StrPOST

   '  Now send it to the IAI
   blnStatus = ChangeCodeLine(strOutCode:=strTempBuffer)

   If Not blnStatus Then
    SetScannerOffsets = False
    Exit Function
   End If

   '  Build string for Y at 0 deg
   strTempBuffer = Format(strPROGRAM_NUMBER, m_fmtPROGRAM_NUM)
   strTempBuffer = strTempBuffer & Format(intCodeLine + 3, fmtLINE_NUM)
   If lngXScanner0Offset > 0 Then
    strTempBuffer = strTempBuffer & strCOMMAND_CODE_PADD
   Else
    strTempBuffer = strTempBuffer & strCOMMAND_CODE_PSUB
   End If
   strTempBuffer = strTempBuffer & strEXTEND
   strTempBuffer = strTempBuffer & strCONDITION_1
   strTempBuffer = strTempBuffer & strCONDITION_90_2
   strTempBuffer = strTempBuffer & strCONDITION_3
   strTempBuffer = strTempBuffer & strOPERAND_1_Y
   strTempBuffer = strTempBuffer & _
         SwapChar(FormatHex(Abs(lngYScanner90Offset), fmtOFFSET), g_intSWAP_LEN_2)
   strTempBuffer = strTempBuffer & StrPOST

   '  Now send it to the IAI
   blnStatus = ChangeCodeLine(strOutCode:=strTempBuffer)

   If Not blnStatus Then
    SetScannerOffsets = False
    Exit Function
   End If
         
   modUtilities.MessageDisplay LoadResString(resWRITING_CARD)
   SetScannerOffsets = WriteCardProgram()
   modUtilities.MessageRemove
   
End Function 'SetScannerOffsets

Public Sub WriteDataPoint(vntPointValue As Variant)

   Dim strOutputs As String
   Dim strBuffer As String
   If Not g_blnSimulator Then
      strOutputs = DataPointSourceToCode(vntPointValue)
   
     If SendCommand(BuildCommand(m_strSET_POINT & strOutputs)) Then
      If ReceiveResponce(strBuffer) Then
         SendEXE m_strSET_POINT
      End If
     End If
   End If
   
End Sub 'WriteDataPoint

Private Function DataPointSourceToCode(vntPointData As Variant) As String

   Dim strBuffer As String
   
   #If ccShip_Ver Then
      On Error GoTo DataPointSourceToCode_Error
   #Else
      On Error GoTo 0
   #End If
   
   DataPointSourceToCode = ""
   
   'Add the point number and put in name index
   strBuffer = Format(vntPointData(m_idxPtNum), m_fmtPOINT_NUM)
   
   'Add the first axies "X" and put in X index
   If vntPointData(m_idxX) = g_lngNOT_USED Then
      strBuffer = strBuffer & m_strNO_POINT & m_fmtPOINT_NUM
   ElseIf vntPointData(m_idxX) < 0 Then
      Err.Raise g_errX_DATA_NEG, , LoadResString(resERR_X_DATA_NEG) & vntPointData(m_idxX)
   Else
      strBuffer = strBuffer & m_strPOINT_EXISTS & Format(vntPointData(m_idxX), m_fmtPOINT_DATA)
   End If
   
   'if two or more axies...
   If m_intMAX_AXIES >= 2 Then
      'Add the first axies "Y" and put in Y index
      If vntPointData(m_idxY) = g_lngNOT_USED Then
         strBuffer = strBuffer & m_strNO_POINT & m_fmtPOINT_NUM
      ElseIf vntPointData(m_idxY) < 0 Then
         Err.Raise g_errY_DATA_NEG, , LoadResString(resERR_Y_DATA_NEG) & vntPointData(m_idxY)
      Else
         strBuffer = strBuffer & m_strPOINT_EXISTS & Format(vntPointData(m_idxY), m_fmtPOINT_DATA)
      End If
   Else
      strBuffer = strBuffer & m_strNO_POINT & m_fmtPOINT_NUM
   End If
   
   'if three or more axies...
   If m_intMAX_AXIES >= 3 Then
      'Add the first axies "Z" and put in Z index
      If vntPointData(m_idxZ) = g_lngNOT_USED Then
         strBuffer = strBuffer & m_strNO_POINT & m_fmtPOINT_NUM
      ElseIf vntPointData(m_idxZ) < 0 Then
         Err.Raise g_errZ_DATA_NEG, , LoadResString(resERR_Z_DATA_NEG) & vntPointData(m_idxZ)
      Else
         strBuffer = strBuffer & m_strPOINT_EXISTS & Format(vntPointData(m_idxZ), m_fmtPOINT_DATA)
      End If
   Else
      strBuffer = strBuffer & m_strNO_POINT & m_fmtPOINT_NUM
   End If
   
   'if four or more axies...
   If m_intMAX_AXIES >= 4 Then
      'Add the first axies "Thata" and put in TH index
      If vntPointData(m_idxTH) = g_lngNOT_USED Then
         strBuffer = strBuffer & m_strNO_POINT & m_fmtPOINT_NUM
      ElseIf vntPointData(m_idxTH) < 0 Then
         Err.Raise g_errTH_DATA_NEG, , LoadResString(resERR_TH_DATA_NEG) & vntPointData(m_idxTH)
      Else
         strBuffer = strBuffer & m_strPOINT_EXISTS & Format(vntPointData(m_idxTH), m_fmtPOINT_DATA)
      End If
   Else
      strBuffer = strBuffer & m_strNO_POINT & m_fmtPOINT_NUM
   End If
   
   ' Now return the variant array
   DataPointSourceToCode = strBuffer

   Exit Function
   
DataPointSourceToCode_Error:

   Dim ErrNumber  As Long
   Dim ErrText As String
   
   ErrNumber = Err.Number
   ErrText = Err.Description
   
   ProccessError "DataPointSourceToCode", m_strName, ErrNumber, ErrText
   DataPointSourceToCode = ""
   
End Function 'DataPointSourceToCode

Private Function ReceiveResponce(ByRef InString As String) As Boolean
   
   '  Waite a while to let the IAI respond
   modAPI.SleepSec 1
   
   
   
   
   
   '  Get data from the communications port.
   InString = m_objIAIPort.Buffer
   
   If InString = "" And m_objIAIPort.TimeOutOK Then
      ReceiveResponce = True
   ElseIf Mid(InString, m_posRSPONSE_CHAR, 1) = m_chrNORMAL_RESPONSE Then
      ReceiveResponce = True
   ElseIf Mid(InString, m_posRSPONSE_CHAR, 1) = m_chrERROR_RESPONSE Then
      ProcessIAIError Mid(InString, m_posERROR_CODE, m_lenERROR_CODE)
      ReceiveResponce = False
   Else
      ReceiveResponce = False
   End If
   
End Function 'ReceiveResponce


Private Sub ProcessIAIError(strErrorCode As String)

   Dim strMessage As String
   Dim strTital As String
   
   strTital = "IAI Error"
   strMessage = "Error code returned = " & strErrorCode & vbCrLf
   strMessage = strMessage & "See help."
   
   strMessage = strMessage & vbCrLf & "from: clsMotionControl"
   
   MsgBox strMessage, vbExclamation + vbOKOnly, strTital
   modUtilities.Log "Motion Controler", strMessage
   
End Sub 'ProcessIAIError

Private Function ChangeCodeLine(strOutCode As String) As Boolean

   #If Not ccShip_Ver Then
      If strOutCode = "" Then Assert "CleanString", m_strName, "strKey = """""
   #End If
 
   ChangeCodeLine = WriteCodeLine(m_strEDIT_PROGRAM_CHANGE, strOutCode)
   
End Function 'ChangeCodeLine



Private Function BuildEXE(CmmndCode As String) As String

  BuildEXE = m_chrEXE_COMMAND & m_strMASTER_NUMBER & _
             CmmndCode & m_strNO_CHECK_SUM & vbCrLf
   
End Function 'BuildEXE

Private Function SendCommand(OutString As String) As Boolean

'   m_blnUseCTS = True
   If Not g_blnSimulator Then
       m_objIAIPort.Buffer = OutString
   End If
'   m_blnUseCTS = False
   SendCommand = True
   
End Function 'SendCommand

Public Function SendReset() As Boolean

'   modUtilities.MessageDisplay LoadResString(resRESETTING_IAI)
   
   SendReset = SendCommand(BuildCommand(m_strRESET))
   modAPI.SleepSec (m_intRESET_WAIT_SEC) ' Give the IAI a chance to rset
   
   modUtilities.MessageRemove

End Function 'SendReset


Public Function StopProgram(intProgID As Integer) As Boolean

   Dim strTemp As String
   
   StopProgram = False

   If SendCommand(BuildCommand(m_strSTOP_PROGRAM)) Then
      StopProgram = SendEXE(m_strSTOP_PROGRAM)
   End If
   
End Function 'RStopProgram

Public Function RunProgram(intProgID As Integer, intStartStep As Integer) As Boolean

   Dim strTemp As String
   
   RunProgram = False

   If SendCommand( _
      BuildCommand(m_strRUN_PROGRAM & _
      Format(intProgID, m_fmtPROGRAM_NUM) & _
      Format(intStartStep, m_fmtPROGRAM_STEP))) _
   Then
      If ReceiveResponce(strTemp) Then
         RunProgram = SendEXE(m_strRUN_PROGRAM & Format(intProgID, m_fmtPROGRAM_NUM))
      End If
   End If
   
End Function 'RunProgram

Public Function Version() As String

   Version = m_strROMVersion

End Function 'Get Version

Private Function WriteCard(intAction As Integer) As Boolean

   Dim strTemp As String
      
   WriteCard = False
   
   If Not g_blnSimulator Then
   
      If SendCommand(BuildCommand(m_strWRITE_CARD & Format(intAction, m_fmtWRITE_CARD))) Then
        If ReceiveResponce(strTemp) Then
         WriteCard = SendEXE(m_strWRITE_CARD & Format(intAction, m_fmtWRITE_CARD))
        End If
      End If
   Else
      WriteCard = True
   End If
   
'   modAPI.SleepMSec 500
   modAPI.SleepSec (m_intWRITE_CARD_WAIT_SEC) ' Give the IAI a chance to rset
   
End Function 'WriteCard

Public Function WriteCardAll() As Boolean

   WriteCardAll = WriteCard(m_strWRITE_ALL)
   
End Function 'WriteCardAll

Public Function WriteCardDataPoints() As Boolean

   WriteCardDataPoints = WriteCard(m_strWRITE_POINT)
   
End Function 'WriteCardDataPoints


Public Function WriteCardProgram() As Boolean

   WriteCardProgram = WriteCard(m_strWRITE_PROGRAM)
   
End Function 'WriteCardProgram


Private Function WriteCodeLine(strEditCode As String, strOutCode As String) As Boolean

   Dim strBuffer As String
   Dim blnResp As Boolean
   
   If Not g_blnSimulator Then
      blnResp = SendCommand(BuildCommand(strEditCode & strOutCode))
      blnResp = ReceiveResponce(strBuffer)
   
      If blnResp Then
        blnResp = SendEXE(strEditCode)
      End If
   Else
      blnResp = True
   End If
   
   WriteCodeLine = blnResp
   
End Function 'WriteCodeLine



   Private Sub Class_Initialize()

   m_strName = "clsMotionControl"
   
   m_blnInitStatus = True
   
   '  Open the communication port
   Set m_objIAIPort = New clsSerialCommCtrl
      
   m_blnInitStatus = m_objIAIPort.Initialize(intPortID:=m_intPROT_ID, strEndTXMark:=m_strEND_TX_MARK, _
                           strPortSettings:=m_strPORT_SETTINGS, intTimerInterval:=m_intWATCH_DOG, _
                           vbHandShaking:=m_vbcHAND_SHAKING, blnDTREnable:=m_blnDTR_ENABLE, _
                           blnRTSEnable:=m_blnRTSENABLE, intRThreshold:=m_intR_THRESHOLD, _
                           blnNullDiscard:=m_blnNULL_DISCARD, chrParityReplace:=m_chrPARITY_REPLACE, _
                           intSThreshold:=m_intS_THRESHOLD, intCTSTimeout:=m_intCTS_TIMEOUT, _
                           intDSRTimeout:=m_intDSR_TIMEOUT, intOutBufferSize:=m_intOUT_BUFFER_SIZE, _
                           intInBufferSize:=m_intIN_BUFFER_SIZE, strName:=m_strName)
                           
                          
   m_blnInitStatus = m_blnInitStatus And SendReset()
'   m_blnInitStatus = m_blnInitStatus And InquireVersion()
      
End Sub 'Class_Initialize



Private Function SendEXE(strEditCode As String)

   Dim strBuffer As String
   Dim intTemp As Integer
   Dim blnTemp As Boolean
   
   SendEXE = False
   
   '  Set up the watch dog timer for exicute
   With m_objIAIPort
      intTemp = .TimeOut
      .TimeOut = m_intEXE_TIMEOUT
      blnTemp = .TimeOutOK
      .TimeOutOK = True
   End With 'm_objIAIPort
   
   If SendCommand(BuildEXE(strEditCode)) Then
      SendEXE = ReceiveResponce(strBuffer)
   End If
   
   '  now reset watch dog timer the way it was
   With m_objIAIPort
      .TimeOut = intTemp
      .TimeOutOK = blnTemp
   End With 'm_objIAIPort
   
End Function 'SendEXE

