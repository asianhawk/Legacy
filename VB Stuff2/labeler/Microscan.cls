VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsMicroscan"
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
'*        2-Axis label Applicator
'*           Control Subsystem
'*
'*        Microscanner Series 3000
'*
'*    Date of origin: 12/29/96
'*    Original author: Michael D. Reed
'*
'* Class purpose:
'*    This class provides the interface between the
'*    IAI and the 2-Axis label Applicator control program.
'*
'************************************************************************
'******************************************************************
Option Explicit

'******************************************************************
'  Constant
'******************************************************************

'  Command strings
Private Const m_chrSTART = "<"
Private Const m_chrSTOP = ">"

'  Program management
Private Const m_chrSOFTWARE_RESET = "A" 'Initializes the scaner
Private Const m_chrSAVE_NVRAM = "Z" '  Save to nonvolatile RAM

'  Device control
Private Const m_chrLASER_ON = "H"
Private Const m_chrLASER_OFF = "I"

'  Code Types
Private Const m_chrAUTO_ALL = "P"
Private Const m_chrCODE_39 = "Q"
Private Const m_chrCODABAR = "R"
Private Const m_chrI2OF5 = "S"

'  Test
Private Const m_chrDECODE_RATE_TEST = "C"
Private Const m_chrSTOP_DECODE_RATE_TEST = "J"

'  Version inquire
'  ROM software part number
Private Const m_chrSW_PART_NUMBER = "#"
Private Const m_chrEPROM_CHECK_SUM = "!"

'  K codes for setup
Private Const m_strSERIAL_TRIGGER_CHAR = "Ki"
Private Const m_strTRIGGER_MODE_SERIAL = "Kg4"
Private Const m_strEND_READ_CYCLE_TIMEOUT = "Kh0,200"

' Read label
Private Const m_chrREAD_LABEL_TRIGER = "b"

'  Reset delay time
Private Const m_intRESET_WAIT_SEC = 1

'******************************************************************
'  Device connected to communication port
Private m_strDeviceName As String

'  class specific data
'  class initialization status
Private m_blnInitStatus As Boolean

' my name
Private m_strName As String

'  used for version control
Private m_strROM_SW_Part_Number As String

'  declare the communications class
Private m_objMicroscanPort As clsSerialComm

'  who called me
Private m_objCallBack As Object

'******************************************************************

Public Function InitStatus() As Boolean
   
   InitStatus = m_blnInitStatus
   
End Function 'InitStatus


Public Function ReadlBarCode() As String

   Dim strBuf As String
   Dim strBuf1 As String
   Dim ltimer As Long
   #If ccShip_Ver Then
      On Error GoTo ReadlBarCode_Error
   #Else
      On Error GoTo 0
   #End If
   strBuf = ""
   strBuf = frmSerialComm.comSerialComm(6).Input
   SendReset
   strBuf = frmSerialComm.comSerialComm(6).Input
   'clear port
   
   
   Do While frmSerialComm.comSerialComm(6).InBufferCount > 0
     strBuf = frmSerialComm.comSerialComm(6).Input
   Loop
   
   If SendCommand(m_chrREAD_LABEL_TRIGER) Then
     ltimer = Timer
     Do While (Timer - ltimer) < 1
       ' overkill
     Loop
     
     Do While (frmSerialComm.comSerialComm(6).InBufferCount < 9) And ((Timer - ltimer) < 2)
      ' DoEvents
        If frmSerialComm.comSerialComm(6).Input = "NOREAD" Then Exit Do
   '     If frmSerialComm.comSerialComm(6).Input = "" Then Exit Do
     Loop
     
     strBuf = frmSerialComm.comSerialComm(6).Input
      
   '   If ReceiveResponse(strBuf1) Then
         ReadlBarCode = strBuf
   '   End If
   End If
   
   Exit Function

ReadlBarCode_Error:

   ProccessError "ReadlBarCode", m_strName, Err.Number, Err.Description
   ReadlBarCode = ""

End Function 'ReadlBarCode

Private Sub Class_Initialize()
   
   #If ccShip_Ver Then
      On Error GoTo Class_Initialize_Error
   #Else
      On Error GoTo 0
   #End If

   m_strName = "clsMicroscan"
   m_strDeviceName = "SCANNER"
   
   m_blnInitStatus = False
   
   '  Open the communication port
   Set m_objMicroscanPort = New clsSerialComm
    
   m_blnInitStatus = Not (m_objMicroscanPort Is Nothing)
   
   '  Now init the divece port
   If m_blnInitStatus Then
      m_blnInitStatus = m_objMicroscanPort.Initialize(strDeviceName:=m_strDeviceName)
   End If
   
   '  if simulator then exit sub at this time
   If g_blnSimulator Then Exit Sub
   
   '  Now send reset and check version
   'code????
'   If m_blnInitStatus Then
'      m_blnInitStatus = SendReset()
'   End If
'   If m_blnInitStatus Then
'      m_blnInitStatus = InquireVersion()
'   End If
   
'   If m_blnInitStatus Then '  send trigger mode and char
'      m_blnInitStatus = m_blnInitStatus And SendCommand(strOut:=m_strTRIGGER_MODE_SERIAL)
'      m_blnInitStatus = m_blnInitStatus And SendCommand(strOut:=m_strSERIAL_TRIGGER_CHAR & m_chrREAD_LABEL_TRIGER)
'      m_blnInitStatus = m_blnInitStatus And SendCommand(strOut:=m_strEND_READ_CYCLE_TIMEOUT)
'   End If
   
   Exit Sub

Class_Initialize_Error:

   m_blnInitStatus = False
   ProccessError "Class_Initialize", m_strName, Err.Number, Err.Description

End Sub 'Class_Initialize



Private Function InquireVersion() As Boolean

   Dim strBuf As String
   
   #If ccShip_Ver Then
      On Error GoTo InquireVersion_Error
   #Else
      On Error GoTo 0
   #End If

   InquireVersion = False

   If SendCommand(m_chrSW_PART_NUMBER) Then
      If ReceiveResponse(strBuf) Then
         m_strROM_SW_Part_Number = strBuf
         InquireVersion = True
      End If
   End If
   
   Exit Function

InquireVersion_Error:

   ProccessError "InquireVersion", m_strName, Err.Number, Err.Description
   InquireVersion = False

End Function 'InquireVersion

Private Function SendCommand(strOut As String) As Boolean
  
   #If ccShip_Ver Then
      On Error GoTo SendCommand_Error
   #Else
      On Error GoTo 0
   #End If
     
     m_objMicroscanPort.Buffer = m_chrSTART & strOut & m_chrSTOP
    
     SendCommand = True
     
   Exit Function

SendCommand_Error:

   ProccessError "SendCommand", m_strName, Err.Number, Err.Description
   SendCommand = False

End Function 'SendCommand

Private Function ReceiveResponse(ByRef r_strIN As String) As Boolean

   Dim strBuf As String
   
   #If ccShip_Ver Then
      On Error GoTo ReceiveResponse_Error
   #Else
      On Error GoTo 0
   #End If

   strBuf = ""
   r_strIN = ""
   strBuf = m_objMicroscanPort.Buffer
   If strBuf = "" Then
      ReceiveResponse = False
   Else
      r_strIN = strBuf
      ReceiveResponse = True
   End If
   
   Exit Function

ReceiveResponse_Error:

   ProccessError "ReceiveResponse", m_strName, Err.Number, Err.Description
   ReceiveResponse = False

End Function 'ReceiveResponse

Public Function Version() As String

   Version = m_strROM_SW_Part_Number
   
End Function 'Version

Public Function SendReset() As Boolean
   
   #If ccShip_Ver Then
      On Error GoTo SendReset_Error
   #Else
      On Error GoTo 0
   #End If

'   SendReset = False
   
'   SendCommand (m_chrSOFTWARE_RESET)
   
'   Call modAPI.SleepSec(m_intRESET_WAIT_SEC)
   
   SendReset = True
   Exit Function

SendReset_Error:

   ProccessError "SendReset", m_strName, Err.Number, Err.Description
   SendReset = False

End Function 'SendReset

Public Sub DataReady()

   Dim strTempBuffer As String
   
   If ReceiveResponse(strTempBuffer) Then
       m_objCallBack.ScanedData = strTempBuffer
   End If
   
End Sub 'DataReady

Public Function Initialize(objCallBack As Object) As Boolean

   #If ccShip_Ver Then
      On Error GoTo Initialize_Error
   #Else
      On Error GoTo 0
   #End If

   Set m_objCallBack = objCallBack
   
   Exit Function

Initialize_Error:

   ProccessError "Initialize", m_strName, Err.Number, Err.Description
   Initialize = False

End Function 'Initialize


