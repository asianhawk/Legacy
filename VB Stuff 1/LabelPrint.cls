VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsLabelPrint"
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
'*           Zebra Label Printer
'*
'*    Date of origin: 2/5/97
'*    Original author: Michael D. Reed
'*
'* Class purpose:
'*    This class is the main control class for the
'*    Label Print Subsystem and needes to be included into
'*    the project needing to print labels.  This class is
'*    intended for the Zebra printers.
'*
'************************************************************************
Option Explicit
'******************************************************************

'  Communication port constent settings
Private Const m_lngCD_TIMEOUT = 0
'Private Const m_intPROT_ID = 6
Private Const m_intPROT_ID = 6

Private Const m_intCTS_TIMEOUT = 0
Private Const m_intDSR_TIMEOUT = 0
Private Const m_blnDTR_ENABLE = False
Private Const m_vbcHAND_SHAKING = 1
Private Const m_intIN_BUFFER_SIZE = 1024
Private Const m_intINPUT_LENGTH = 0
Private Const m_blnNULL_DISCARD = True
Private Const m_intOUT_BUFFER_SIZE = 512
Private Const m_chrPARITY_REPLACE = "?"
Private Const m_intR_THRESHOLD = 1
Private Const m_blnRTSENABLE = False
Private Const m_strPORT_SETTINGS = "9600,e,7,1"
Private Const m_intS_THRESHOLD = 0

Private Const m_intWATCH_DOG = 0  'disable watch dog timer

Private Const m_intCOM_RESP_TIMEOUT = 2000 'in millsec set for 2 sec

Private Const m_chrEND_TX_MARK = vbCrLf
Private Const m_intRESET_WAIT_SEC = 25

'******************************************************************
'  Constents to talk to Zebra printer
Private Const m_strHOST_IDENTIFICATION = "~HI"
Private Const m_strPOWER_ON_RESET = "~JR"

Private Const m_strBEGIN = "^XA"       'Opening Bracket
Private Const m_srtEND = "^XZ"         'Closing Bracket
Private Const m_strFIELD = "^FS"       'Field seprator

Private Const m_strFIELD_ID = "^FN"    'Field number
Private Const m_strFIELD_DATA = "^FD"  'Field data

Private Const m_strFORMAT = "^XFR:"      'Format retrive
Private Const m_strPRINT_QTY_1 = "^FQ1"   'Print number of labels

Private Const m_strSER_NUM = "\d:"
Private Const m_strDATE = "$Date"


'Added 09/30/98 for adding concode to label

Private Const m_strCONCODE = "CONCODE"

Private Const m_strDATA_DLM = "\"
Private Const m_strFMT_DLM = ","



'******************************************************************
'  class specific data
'  class initialization status
Private m_blnInitStatus As Boolean

Private m_strName As String

Private m_strModel_Version As String

'  declare the communications class
Private m_objPrinterPort As clsSerialCommCtrl

'  Name of template and number of fields
Dim m_strTemplate_FName As String
Private m_strTplatName As String
'  Setup a place to store the template
Private ma_strTemplate0() As String  'added 05-27-98

Private m_intFieldCount As Integer

Private m_strTemplate As String


Public Function GetTemplate0d() As Boolean
 
   Dim strTemplateBuffer As String
   Dim hfile As Integer
   Dim idx As Integer
 
   #If ccShip_Ver Then
      On Error GoTo GetTemplate0d_Error
   #Else
      On Error GoTo 0
   #End If
 
   GetTemplate0d = False
 
   hfile = FreeFile
   If hfile = 0 Then
      Err.Raise g_errNO_FILE_HANDAL, , LoadResString(resERR_PRT_TPLATE_ON_HANDAL)
   Else
      Open m_strTemplate_FName For Input Access Read As #hfile
      If Not EOF(hfile) Then
         ReDim ma_strTemplate0(0)
         idx = 0
         Do Until EOF(hfile)
            Line Input #hfile, strTemplateBuffer
            If (InStr(strTemplateBuffer, "^FX") <> 0) Then
               strTemplateBuffer = Trim(Mid(strTemplateBuffer, 1, InStr(strTemplateBuffer, "^FX") - 1))
            Else
               strTemplateBuffer = Trim(strTemplateBuffer)
            End If
            If strTemplateBuffer <> "" Then
               ma_strTemplate0(idx) = strTemplateBuffer
               If Not EOF(hfile) Then
                 idx = idx + 1
                 ReDim Preserve ma_strTemplate0(idx)
               End If
            End If
         Loop
      End If
   End If
 
   GetTemplate0d = True
   Exit Function
 
GetTemplate0d_Error:
 
   Dim intErrNum As Integer
   GetTemplate0d = False
   intErrNum = Err.Number
   If (intErrNum = g_errFILE_NOT_FOUND) Then
     PrinterError "GetTemplate0d", m_strName, _
                    g_errFILE_NOT_FOUND, _
                    LoadResString(resERR_PTR_TPLATE_NO_FILE) & vbCrLf & m_strTemplate_FName
   ElseIf intErrNum = g_errPATH_NOT_FOUND Then
      PrinterError "GetTemplate0d", m_strName, _
                    g_errPATH_NOT_FOUND, _
                    LoadResString(resERR_PRT_TPLATE_ON_PATH) & vbCrLf & m_strTemplate_FName
   Else
      ProccessError "GetTemplate0d", m_strName, Err.Number, Err.Description
   End If
 
End Function 'GetTemplate0d

Private Sub Class_Initialize()

   m_strName = "clsLabelPrint"
   
   m_blnInitStatus = True
   
   '  Open the communication port
   Set m_objPrinterPort = New clsSerialCommCtrl

   m_blnInitStatus = m_objPrinterPort.Initialize(intPortID:=m_intPROT_ID, strEndTXMark:=m_chrEND_TX_MARK, _
                           strPortSettings:=m_strPORT_SETTINGS, intTimerInterval:=m_intWATCH_DOG, _
                           vbHandShaking:=m_vbcHAND_SHAKING, blnDTREnable:=m_blnDTR_ENABLE, _
                           blnRTSEnable:=m_blnRTSENABLE, intRThreshold:=m_intR_THRESHOLD, _
                           blnNullDiscard:=m_blnNULL_DISCARD, chrParityReplace:=m_chrPARITY_REPLACE, _
                           intSThreshold:=m_intS_THRESHOLD, intCTSTimeout:=m_intCTS_TIMEOUT, _
                           intDSRTimeout:=m_intDSR_TIMEOUT, intOutBufferSize:=m_intOUT_BUFFER_SIZE, _
                           intInBufferSize:=m_intIN_BUFFER_SIZE, strName:=m_strName)
                           
'   m_blnInitStatus = SendReset()
   m_blnInitStatus = InquireVersion()

End Sub 'Class_Initialize

Private Function InquireVersion() As Boolean

   Dim strBuf As String
   Dim intTemp As Integer
   Dim blnTemp As Boolean
   
   '  Set up the watch dog timer for exicute
   With m_objPrinterPort
      intTemp = .TimeOut
      .TimeOut = m_intCOM_RESP_TIMEOUT
      blnTemp = .TimeOutOK
      .TimeOutOK = True
   End With 'm_objPrinterPort
   
   InquireVersion = False
   
   If SendData(m_strHOST_IDENTIFICATION) Then
      If ReceiveResponse(strBuf) Then
         m_strModel_Version = modUtilities.CleanString(strBuf)
         InquireVersion = True
      End If
   End If
   
   '  now reset watch dog timer the way it was
   With m_objPrinterPort
      .TimeOut = intTemp
      .TimeOutOK = blnTemp
   End With 'm_objPrinterPort
   
End Function 'InquireVersion

Public Function Version() As String

   Version = m_strModel_Version
   
End Function 'Version

Public Function SendReset() As Boolean

   SendData (m_strPOWER_ON_RESET)
   
   Call modAPI.SleepSec(m_intRESET_WAIT_SEC)
   
End Function 'SendReset

Public Function SendFieldData(strOut As String) As Boolean

   Dim i As Integer
   Dim strBuffer As String
   Dim strFrontBuf As String
   Dim strBackBuf As String
   Dim strDataField As String
   Dim strFmat As String
   Dim strSave As String ' temporary fix to parsing problem
 
   #If ccShip_Ver Then
      On Error GoTo SendData_Error
   #Else
      On Error GoTo 0
   #End If
 
   SendFieldData = False
 
   '  Build the template into a string
 
    For i = 0 To UBound(ma_strTemplate0)
       strSave = ma_strTemplate0(i)
       If InStr(ma_strTemplate0(i), m_strSER_NUM) <> 0 Then
           '  now brake it up
            strFrontBuf = modUtilities.NextToken(ma_strTemplate0(i), m_strDATA_DLM)
            strDataField = modUtilities.NextToken(ma_strTemplate0(i), m_strDATA_DLM)
            '  get the format field
            strFmat = modUtilities.NextToken(strDataField, m_strFMT_DLM)
            strFmat = strDataField
            strBackBuf = modUtilities.NextToken(ma_strTemplate0(i), m_strDATA_DLM)
            strBuffer = strBuffer & strFrontBuf & strOut & strBackBuf
        
        ElseIf InStr(UCase(ma_strTemplate0(i)), m_strCONCODE) <> 0 Then
           
           '  now brake it up
            strFrontBuf = modUtilities.NextToken(ma_strTemplate0(i), m_strDATA_DLM)
            strDataField = modUtilities.NextToken(ma_strTemplate0(i), m_strDATA_DLM)
            '  get the format field
            strFmat = modUtilities.NextToken(strDataField, m_strFMT_DLM)
            strFmat = strDataField
            strBackBuf = modUtilities.NextToken(ma_strTemplate0(i), m_strDATA_DLM)
            strBuffer = strBuffer & strFrontBuf & Mid(g_strCONCODE, 1, 3) + " " + _
                                                  Mid(g_strCONCODE, 4, 3) + " " + _
                                                  Mid(g_strCONCODE, 7, 3) + " " & strBackBuf
        
        
        ElseIf InStr(ma_strTemplate0(i), m_strDATE) <> 0 Then
               '  now brake it up
               strFrontBuf = modUtilities.NextToken(ma_strTemplate0(i), m_strDATA_DLM)
               strDataField = modUtilities.NextToken(ma_strTemplate0(i), m_strDATA_DLM)
               '  get the format field
               strFmat = modUtilities.NextToken(strDataField, m_strFMT_DLM)
               strFmat = strDataField
 
               strBackBuf = modUtilities.NextToken(ma_strTemplate0(i), m_strDATA_DLM)
               strBuffer = strBuffer & strFrontBuf & Format(Now, strFmat) & strBackBuf
         Else
               strBuffer = strBuffer & ma_strTemplate0(i)
         End If
         ma_strTemplate0(i) = strSave
     Next i
 
   m_objPrinterPort.Buffer = strBuffer
 
   SendFieldData = True
   Exit Function
 
SendData_Error:
 
   ProccessError "SendfieldData", m_strName, Err.Number, Err.Description
   SendFieldData = False

End Function 'SendData

Private Function ReceiveResponse(ByRef r_strIN As String) As Boolean

   Dim strBuf As String
   
   If g_blnSimulator Then
      strBuf = "sim"
   Else
     strBuf = m_objPrinterPort.Buffer
   End If
   
   
   
   If strBuf = "" Then
     ReceiveResponse = False
     Exit Function
   End If
   
   r_strIN = Trim(strBuf)
   ReceiveResponse = True
   
End Function 'ReceiveResponse

Public Function InitStatus() As Boolean
   
   InitStatus = m_blnInitStatus
   
End Function 'InitStatus



Public Function SendTemplate(strTemplate As String, strFormatName As String, _
                               strTemplatePath As String _
                              ) As Boolean

   Dim blnStatus As Boolean
   blnStatus = True
   
   m_strTplatName = strFormatName
'   m_intFieldCount = intFieldCount
   If strTemplate = "" Then
      m_objPrinterPort.Buffer = GetTemplate( _
                                    strFileName:=strTemplatePath, _
                                    blnStatus:=blnStatus)
   Else
      m_objPrinterPort.Buffer = strTemplate
      blnStatus = True
   End If
   
   SendTemplate = blnStatus
   
End Function 'SendTemplate

Private Function GetTemplate(strFileName As String, _
                            ByRef blnStatus As Boolean) As String

   Dim strTemplateBuffer As String
   Dim hfile As Integer

   #If ccShip_Ver Then
      On Error GoTo GetTemplate_Error
   #Else
      On Error GoTo 0
   #End If
 
   blnStatus = False
    
   hfile = FreeFile
   If hfile = 0 Then
      Err.Raise g_errNO_FILE_HANDAL, , LoadResString(resERR_PRT_TPLATE_ON_HANDAL)
   Else
      Open App.Path & "\" & strFileName For Binary Access Read As #hfile
      If Not EOF(hfile) Then
         strTemplateBuffer = Input(LOF(hfile), #hfile)
      End If
   End If
   
   GetTemplate = strTemplateBuffer
   blnStatus = True
   Exit Function

GetTemplate_Error:

   Dim intErrNum As Integer
   
   intErrNum = Err.Number
   If (intErrNum = g_errFILE_NOT_FOUND) Then
     PrinterError "GetTemplate", m_strName, _
                    g_errFILE_NOT_FOUND, _
                    LoadResString(resERR_PTR_TPLATE_NO_FILE) & vbCrLf & strFileName
   ElseIf intErrNum = g_errPATH_NOT_FOUND Then
      PrinterError "GetTemplate", m_strName, _
                    g_errPATH_NOT_FOUND, _
                    LoadResString(resERR_PRT_TPLATE_ON_PATH) & vbCrLf & strFileName
   Else
      ProccessError "GetTemplate", m_strName, Err.Number, Err.Description
   End If
   
End Function 'GetTemplate

Public Sub PrinterError(ProcName As String, _
                         ModName As String, _
                         ErrorNumber As Integer, _
                         ErrorText As String)
            
   Dim strMessage As String
   
   strMessage = "An error occured in: " & vbCrLf
   strMessage = strMessage & "Proc: " & ProcName & vbCrLf
   strMessage = strMessage & "Module: " & ModName & vbCrLf
   strMessage = strMessage & "Error number = " & ErrorNumber & vbCrLf
   strMessage = strMessage & "Msg: " & ErrorText
   strMessage = strMessage & "Program will abort."
   
   MsgBox strMessage, vbOKOnly + vbCritical, "Error in Printer SubSystem"
   
End Sub 'PrinterError




Public Function SendData(strBuffer As String) As Boolean

   
   If Not g_blnSimulator Then
      m_objPrinterPort.Buffer = strBuffer
   End If
   
   SendData = True
   
End Function 'SendData

Public Property Get m_strTemplate_FileName() As String
  m_strTemplate_FileName = m_strTemplate_FName
End Property

Public Property Let m_strTemplate_FileName(vNewValue As String)
  m_strTemplate_FName = vNewValue
End Property
