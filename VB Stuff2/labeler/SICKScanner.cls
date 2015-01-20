VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "SICKScanner"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Description = "This scanner class is used soly for SICK scanners. Users wishing to modify the class are encouraged to obtain the SICK's command language guide."
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
'             SICK Scanner Class
'Date Created: 06/22/98
'Desciption:
'           This class is used with SICK scanners. After creating the
'           object, the user must assign a MSCOMM type object.
'
'
'
'Liat Of Procedures:
'
'Public Function ReadBarCode(strPrinterString As String) As Boolean
'Private Sub ParseBarCode()
'Public Function ReadDiagnosticData() As String
'Public Function ResetScanner() As Boolean
'Public Function InitScanner(nMaxWordLength As Integer, _
                            Optional intNumberOfRetries As Integer, _
                            Optional intScannerDelay As Integer) As Boolean

'Public Sub SetScannerPort_Settings(strSettings As String)
'Public Sub SetScannerPort_ComPortID(ByVal nComPortID As Integer)
'Public Function OpenScannerPort() As Boolean
'Private Sub TriggerOn()
'Private Sub TriggerOff()
'Private Sub ScanLabel()
'Public Function ScannerDiagnostic() As Boolean
'
'
'
Option Explicit


' *************      Constants    *********************
Private m_StartScanning As String
Private m_StopScanning As String

'Runtime Data
Private m_strScanBuffer As String 'Unfiltered, unparsed input from
                                  'scanner
Public m_strBarCode As String     'parsed bar code from scanner
Public m_blnScannerDiagnostic As Boolean  ' if scan operation fails
                                          ' run diagnostic
Private m_strErrorBuffer As String  'contains results from
                                  'self test


Public strBarCode As String

Public m_strTT As String    'duration of read interval
Public m_strMG As String    'mean time value of identification quality
Public m_strN As String     'number of barcodes read
Public m_strCP As String    ' code position
Public m_strCL As String    ' code length

Public m_strCA As String    ' required scans
Public m_strCS As String    ' code reliability
Public m_strCK As String    'code continuity

'Initialized Data
Public m_MaxWordLength As Integer ' maximum length of character string
                                  ' note: character string = printed barcode
Public m_nNumberOfRetries As Integer
Public m_nScannerDelay As Long    ' scanner needs time to write data
Private mvarobjScannerPortID As MSComm  'local copy
Public objScannerPort As MSComm

Private Const m_strTerminateReadMode As String = "13" ' Terminate Read Mode
Private Const m_strQueryParameterSize As String = "3?AQ" ' Query the Parameter Size
Private Const m_strOperatingMode As String = "3?BT" 'Operating Mode of Terminal Interface
Private Const m_LoadBasicFactorySettings As String = "3DF" 'Load the basic factory settings

'Define variables used to display data
Public frmScannerView As frmScanner
Public m_blnViewForm As Boolean
Public m_blnViewBarCode As Boolean
Public m_blnViewStatistics As Boolean

Public Static Function ReadBarCode(strPrinterString As String) As Boolean
'strPrinterStringCode = expected result


Dim nMsgBoxResult As Integer

Dim n_Attempt_Cntr As Integer
  
On Error GoTo ReadBarCode_Error:
  
  
   If (g_blnOpenTraceLogFile) Then TraceLog ("Class=SICKScanner: ReadBarCode")
  
  
   If frmScanner.chkDisableScanner.Value = 1 Then
     ReadBarCode = True
     m_strBarCode = "Scanner Disabled"
     Exit Function
   End If
   objScannerPort.InputMode = comInputModeText
        
        
   
   n_Attempt_Cntr = n_Attempt_Cntr + 1
   ReadBarCode = True  ' assume success
   
   ScanLabel
   If (g_blnSimulator) Then
      m_strBarCode = strPrinterString
   Else
      If (m_strScanBuffer <> "") Then
         ParseBarCode
      End If
   End If
      
   
   
   
   If UCase(strPrinterString) <> UCase(m_strBarCode) Then
      If n_Attempt_Cntr >= m_nNumberOfRetries Then
           nMsgBoxResult = MsgBox("Scan Failed After " + Str(n_Attempt_Cntr) + _
                  "Attempts", vbExclamation, "Scanner Operation Failed")
           ReadBarCode = False
           If m_blnScannerDiagnostic Then
              ScannerDiagnostic
           End If
      Else
           ReadBarCode = ReadBarCode(strPrinterString)
      End If
   Else
     
   End If
   
   If (n_Attempt_Cntr >= m_nNumberOfRetries) Or _
      (ReadBarCode) Then
      
      n_Attempt_Cntr = 0
      
   End If
   objScannerPort.InputMode = comInputModeBinary
   
   DisplayData
   Exit Function
ReadBarCode_Error:
  ReadBarCode = False
  MsgBox ("Error In Read Bar Code Error Msg [" + Err.Description + "]")
End Function
Public Function ReadBottomBarCode() As Boolean

'strPrinterStringCode = expected r esult
Dim nMsgBoxResult As Integer
Static n_Attempt_Cntr As Integer
  
   If (g_blnOpenTraceLogFile) Then TraceLog ("Class=SICKScanner: ReadBarCode")
  
  
   objScannerPort.InputMode = comInputModeText
        
        
   
   n_Attempt_Cntr = n_Attempt_Cntr + 1
   ReadBottomBarCode = True  ' assume success
   
   ScanBottomLabel
   ParseBarCode
   
      
   If m_strBarCode = "" Then
      If n_Attempt_Cntr >= m_nNumberOfRetries Then
'           nMsgBoxResult = MsgBox("Scan Failed After " + Str(n_Attempt_Cntr) + _
'                  "Attempts", vbExclamation, "Scanner Operation Failed")
           ReadBottomBarCode = False
'           If m_blnScannerDiagnostic Then
'              ScannerDiagnostic
'           End If
      Else
           ReadBottomBarCode = ReadBottomBarCode
      End If
   Else
     
   End If
   
   If (n_Attempt_Cntr >= m_nNumberOfRetries) Or _
      (ReadBottomBarCode) Then
      
      n_Attempt_Cntr = 0
      
   End If
   objScannerPort.InputMode = comInputModeBinary
   
End Function



Public Function ScanBarCode() As Boolean
'this function does not verify the scanned code
'it is meant to be used for diagnostic purposes
  
   objScannerPort.InputMode = comInputModeText
   ScanBarCode = True  ' assume success
   
   ScanLabel
   ParseBarCode
   DisplayData
      
   If m_blnScannerDiagnostic Then
       ScannerDiagnostic
   End If
   objScannerPort.InputMode = comInputModeBinary
   
   
End Function


Private Sub ParseBarCode()
    
On Error GoTo ParseBarCode_Error:
    
    
    m_strBarCode = Mid(m_strScanBuffer, InStr(1, m_strScanBuffer, "n=_") + 6 _
                    , m_MaxWordLength)
                    
'read duration
    m_strTT = Mid(m_strScanBuffer, InStr(1, m_strScanBuffer, "TT=_") + 5 _
                    , 6)
    If Mid(m_strTT, 1, 1) = "_" Then
      m_strTT = Mid(m_strTT, 2)
    End If
    
'identification quality
    m_strMG = Mid(m_strScanBuffer, InStr(1, m_strScanBuffer, "MG=_") + 3 _
                    , 3)
    If Mid(m_strMG, 1, 1) = "_" Then
      m_strMG = Mid(m_strMG, 2)
    End If
    
'code position
    m_strCP = Mid(m_strScanBuffer, InStr(1, m_strScanBuffer, "CP=_") + 4 _
                    , 2)
    If Mid(m_strCP, 1, 1) = "_" Then
      m_strCP = Mid(m_strCP, 2)
    End If
    
'code length
    m_strCL = Mid(m_strScanBuffer, InStr(1, m_strScanBuffer, "CL=_") + 4 _
                    , 2)
    If Mid(m_strCL, 1, 1) = "_" Then
      m_strCL = Mid(m_strCL, 2)
    End If

'required scans
    m_strCA = Mid(m_strScanBuffer, InStr(1, m_strScanBuffer, "CA=_") + 4 _
                    , 2)
    If Mid(m_strCA, 1, 1) = "_" Then
      m_strCA = Mid(m_strCA, 2)
    End If
    
'code reliability
    m_strCS = Mid(m_strScanBuffer, InStr(1, m_strScanBuffer, "CS=_") + 4 _
                    , 3)
    If Mid(m_strCS, 1, 1) = "_" Then
      m_strCS = Mid(m_strCS, 2)
    End If
    
'code continuity
    m_strCK = Mid(m_strScanBuffer, InStr(1, m_strScanBuffer, "CK=_") + 4 _
                    , 2)
    If Mid(m_strCK, 1, 1) = "_" Then
      m_strCK = Mid(m_strCK, 2)
    End If
    
Exit Sub
ParseBarCode_Error:
MsgBox ("Error In ParseBarCode Error Msg [" + Err.Description + "]")

    
End Sub



Public Function ReadDiagnosticData() As String
End Function

Public Function ResetScanner() As Boolean
End Function

Public Function InitScanner(nMaxWordLength As Integer, _
                            Optional intNumberOfRetries As Variant, _
                            Optional intScannerDelay As Variant, _
                            Optional frmView As Variant) As Boolean

Dim strBuffer As String
   
On Error GoTo Error_Handle:
   
   m_StartScanning = Chr("2") + "21" + Chr("3")
   m_StopScanning = Chr("2") + "22" + Chr("3")
   OpenScannerPort                     'Open scanner port
      
   If IsMissing(intNumberOfRetries) Then
     m_nNumberOfRetries = 3
   Else
     m_nNumberOfRetries = intNumberOfRetries
   End If
   
   If IsMissing(intScannerDelay) Then
     m_nScannerDelay = 1
   Else
     m_nScannerDelay = intScannerDelay
   
   End If

   m_MaxWordLength = nMaxWordLength
   strBuffer = Chr("2") + "11" + Chr("3") 'put scanner in Read mode
   If (Not g_blnSimulator) Then
      objScannerPort.Output = strBuffer
   End If
 Exit Function
Error_Handle:
   
   MsgBox ("Scanner Init Error: " + Err.Description)
   End

End Function

Public Sub SetScannerPort_Settings(strSettings As String)
   objScannerPort.Settings = strSettings
End Sub


Public Sub SetScannerPort_ComPortID(ByVal nComPortID As Integer)
   objScannerPort.CommPort = nComPortID
End Sub

Public Function OpenScannerPort() As Boolean
   On Error GoTo Error_h
   OpenScannerPort = True
   objScannerPort.PortOpen = True
   Exit Function
Error_h:
   OpenScannerPort = False
End Function

Public Sub TriggerOn()
Dim l_Timer As Long
   objScannerPort.Output = Chr(2) + "11" + Chr(3)
   objScannerPort.Output = m_StartScanning
   l_Timer = Timer
   'added 07/28/99 for midnight rollover problem
   SleepSec (m_nScannerDelay)
   
'   Do While (Timer - l_Timer) < m_nScannerDelay
      ' give scannner time to dump data into
      ' the PC's serial port
'   Loop

End Sub

Public Sub TriggerOff()
   If (Not g_blnSimulator) Then
      objScannerPort.Output = m_StopScanning
   End If

End Sub
Public Sub BottomTriggerOn()
   If (Not g_blnSimulator) Then
      objScannerPort.Output = m_StopScanning
   End If
End Sub

Private Sub ScanLabel()
On Error GoTo ScanLabel_Error:
   
   If (g_blnOpenTraceLogFile) Then TraceLog ("Class=SICKScanner: ScanLabel")
   
   If (Not g_blnSimulator) Then
   
        TriggerOn
        m_strScanBuffer = objScannerPort.Input
        TriggerOff

    End If
    
Exit Sub

ScanLabel_Error:
MsgBox ("Error In Scan Label Error Msg [" + Err.Description + "]")
    
End Sub
Private Sub ScanBottomLabel()
On Error GoTo ScanError:
   
   If (g_blnOpenTraceLogFile) Then TraceLog ("Class=SICKScanner: ScanLabel")
   
   If (Not g_blnSimulator) Then
   
        BottomTriggerOn
        m_strScanBuffer = objScannerPort.Input
        TriggerOff

    End If
    
Exit Sub

ScanError:
MsgBox ("Error In Scan Label Error Msg [" + Err.Description + "]")
    
    
End Sub



Public Function ScannerDiagnostic() As Boolean
'Only when m_blnScannerDiagnostic is enabled will the
'code access this module.

Dim blnResult As Boolean
Dim intContinue As Integer
Dim strTitle As String
Dim blnScannerTargeting As Boolean

 blnResult = True
 strTitle = "Scanner Diagnostics"
 
 ScannerDiagnostic = False    ' only a successful read of a bar
                              ' code is satisfactory. Note
                              ' the user can still exit if routine
                              ' be indicating that there was a
                              ' successful read of the program.
 
 Do While blnResult
    blnScannerTargeting = True
    ScanLabel
    ParseBarCode
    intContinue = MsgBox("Scanned BarCode = " + _
                  m_strBarCode + Chr(13) + Chr(10) + _
                  "Is the problem fixed?", vbYesNo, strTitle)
           
    If intContinue = 6 Then
       ScannerDiagnostic = True
       blnResult = False
    Else
       Do While blnScannerTargeting
         TriggerOn
         intContinue = MsgBox("Is Scanner Targeting Correctly?" _
                     , vbYesNo, strTitle)
                     
         If intContinue = 6 Then
            blnScannerTargeting = False
            TriggerOff
         End If
       Loop
    End If
 Loop

End Function


Public Function SelfTest() As Boolean

Dim strBuffer() As Byte
Dim ii As Variant
Dim intPrevBufferCount As Integer
Dim i As Integer

   SelfTest = False
   m_strScanBuffer = ""
   
   QuitReadMode
   StartReadMode
   objScannerPort.InBufferCount = 0
   objScannerPort.Output = Chr(2) + "15" + Chr(3)
   ScannerWaitTime 200
   
   intPrevBufferCount = objScannerPort.InBufferCount
   
   Do While objScannerPort.InBufferCount <> intPrevBufferCount
     intPrevBufferCount = objScannerPort.InBufferCount
   Loop
   strBuffer = objScannerPort.Input
   For Each ii In strBuffer()
    If ii >= 48 Then
       m_strScanBuffer = m_strScanBuffer + Chr(ii)
    End If
   Next
   If m_strScanBuffer = "ERR" Then
      MsgBox ("Scanner In Read Mode")
      SelfTest = False
      Exit Function
   End If
   m_strErrorBuffer = SelfTestErrorCheck(m_strScanBuffer)
   If m_blnScannerDiagnostic Then
      DisplayData
   End If
   If m_strErrorBuffer <> "OK" Then
     MsgBox ("Scanner Failure: " + m_strErrorBuffer)
   End If
   

End Function
Private Function QuitReadMode() As Boolean
Dim strBuffer() As Byte
Dim strErrorBuffer As String
Dim strQuitModeReadBuffer As String
Dim ii As Variant
Dim intPrevBufferCount As Integer
Dim i As Integer

   m_strScanBuffer = ""
   objScannerPort.InBufferCount = 0
   objScannerPort.Output = Chr(2) + "13" + Chr(3)
   ScannerWaitTime 10
   
   intPrevBufferCount = objScannerPort.InBufferCount
   
   Do While objScannerPort.InBufferCount <> intPrevBufferCount
     intPrevBufferCount = objScannerPort.InBufferCount
   Loop
   strBuffer = objScannerPort.Input
   For Each ii In strBuffer()
    If ii >= 48 Then
       strQuitModeReadBuffer = strQuitModeReadBuffer + Chr(ii)
    End If
   Next
   
End Function
Private Function StartReadMode() As Boolean
Dim strBuffer() As Byte
Dim strErrorBuffer As String
Dim strQuitModeReadBuffer As String
Dim ii As Variant
Dim intPrevBufferCount As Integer
Dim i As Integer
   
   m_strScanBuffer = ""
   objScannerPort.InBufferCount = 0
   objScannerPort.Output = Chr(2) + "11" + Chr(3)
   ScannerWaitTime 10
   
   intPrevBufferCount = objScannerPort.InBufferCount
   
   Do While objScannerPort.InBufferCount <> intPrevBufferCount
     intPrevBufferCount = objScannerPort.InBufferCount
   Loop
   strBuffer = objScannerPort.Input
   For Each ii In strBuffer()
    If ii >= 48 Then
       strQuitModeReadBuffer = strQuitModeReadBuffer + Chr(ii)
    End If
   Next
   
End Function

Private Function SelfTestErrorCheck(strBuffer As String) As String

  strBuffer = Mid(strBuffer, 3, 3)
  If strBuffer = "000" Then
     SelfTestErrorCheck = "OK"
  ElseIf strBuffer = "011" Then
     
     SelfTestErrorCheck = "Data Error(external RAM)"
  ElseIf strBuffer = "012" Then
     SelfTestErrorCheck = "Address Error(external RAM)"
  ElseIf strBuffer = "012" Then
     SelfTestErrorCheck = "RAM too small(external RAM)"
  ElseIf strBuffer = "013" Then
     SelfTestErrorCheck = "Error 013"
  ElseIf strBuffer = "021" Then
     SelfTestErrorCheck = "Error 021"
  ElseIf strBuffer = "022" Then
     SelfTestErrorCheck = "Error 022"
  ElseIf strBuffer = "031" Then
     SelfTestErrorCheck = "Error 031"
  ElseIf strBuffer = "032" Then
     SelfTestErrorCheck = "Error 032"
  ElseIf strBuffer = "041" Then
     SelfTestErrorCheck = "Error 041"
  ElseIf strBuffer = "051" Then
     SelfTestErrorCheck = "Error 051"
  ElseIf strBuffer = "055" Then
     SelfTestErrorCheck = "Error 055"
  ElseIf strBuffer = "061" Then
     SelfTestErrorCheck = "Error 061"
  ElseIf strBuffer = "071" Then
     SelfTestErrorCheck = "Error 071"
  ElseIf strBuffer = "072" Then
     SelfTestErrorCheck = "Error 072"
  ElseIf strBuffer = "091" Then
     SelfTestErrorCheck = "Error 091"
  ElseIf strBuffer = "092" Then
     SelfTestErrorCheck = "Error 092"
  ElseIf strBuffer = "093" Then
     SelfTestErrorCheck = "Error 093"
  ElseIf strBuffer = "094" Then
     SelfTestErrorCheck = "Error 094"
  ElseIf strBuffer = "095" Then
     SelfTestErrorCheck = "Error 095"
  End If
End Function


Private Sub ScannerWaitTime(lngWaitTime As Long)
'must be in milliseconds
Dim lngTimer As Single

  lngTimer = Timer
  
   'added 07/28/99 for midnight rollover problem.
   SleepSec (lngWaitTime / 100)
  
'  Do While (Timer - lngTimer) < lngWaitTime / 100
  
'  Loop

End Sub
Public Sub InitForm()
   Set frmScannerView = New frmScanner
   frmScannerView.Show
   frmScannerView.WindowState = 0
   frmScanner.fraStatisTics.Enabled = False
   m_blnViewForm = True
End Sub

Private Sub DisplayData()
 
 If (g_blnOpenTraceLogFile) Then TraceLog ("Class=SICKScanner: DisplayData")
 
 
 If m_blnViewForm = False Then Exit Sub
   
   If Len(frmScanner.txbScannerOutput.Text) > 100 Then
       frmScanner.txbScannerOutput.Text = ""
   End If
 
     
   With frmScanner.txbScannerOutput
     If m_blnViewBarCode Then
       .Text = .Text + Format(Now, "hh:mm:ss") + "::" + "Scanned Bar Code:" + m_strBarCode + vbCrLf
     End If
     
     If m_blnScannerDiagnostic Then
       .Text = .Text + Format(Now, "hh:mm:ss") + "::" + "Scanner Status Code:" + m_strErrorBuffer + vbCrLf
     End If
'       .Refresh
'       frmScanner.txbScannerOutput.Text = "test"
    End With
    If m_blnViewStatistics = True Then
       frmScanner.txtDReadInterval = m_strTT
       frmScanner.txtIDQuality = m_strMG
       frmScanner.txtCodePosition = m_strCP
       frmScanner.txtCodeLength = m_strCL
       frmScanner.txtRequiredScans = m_strCA
       frmScanner.txtCodeReliability = m_strCL
       frmScanner.txtCodeContinuity = m_strCK
    
    End If
End Sub


Public Function InitBottomScanner(nMaxWordLength As Integer, _
                            Optional intNumberOfRetries As Variant, _
                            Optional intScannerDelay As Variant, _
                            Optional frmView As Variant) As Boolean

Dim strBuffer As String
   InitBottomScanner = True
   
   If (Not OpenScannerPort) Then 'Open scanner port
      InitBottomScanner = False
      Exit Function
   End If
      
   If IsMissing(intNumberOfRetries) Then
     m_nNumberOfRetries = 3
   Else
     m_nNumberOfRetries = intNumberOfRetries
   End If
   
   If IsMissing(intScannerDelay) Then
     m_nScannerDelay = 1
   Else
     m_nScannerDelay = intScannerDelay
   
   End If

   m_MaxWordLength = nMaxWordLength

End Function


