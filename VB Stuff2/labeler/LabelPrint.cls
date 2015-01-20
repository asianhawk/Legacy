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
'*        2-Axis label Applicator
'*           Control Subsystem
'*
'*           DataMax Podigy Max Label Printer
'*
'*    Date of origin: 2/5/97
'*    Original author: Michael D. Reed
'*
'* Class purpose:
'*    This class is the main control class for the
'*    Label Print Subsystem and needes to be included into
'*    the project needing to print labels.  This class is
'*    intended for the Intermec printers.
'*
'*    Sequence for printing labels:
'*       GetTemplate
'*       SenData
'*       PrintLabel
'*
'*       Properties
'*          DarkAdjust: get or sets label darkness setting,
'*                      usually the heat setting.
'*          XHome:      Gets or sets the x value for the label
'*                      symbology location.
'*          YHome:      Gets or sets the y value for the label
'*                      symbology location.
'*       Functions:
'*          InitStatus:    Returns the initialization status
'*          MaxDarkAdjust: Returns the maxim dark adjustment.
'*          MinDarkAdjust: Returns the minimum dark adjustment.
'*          MaxHome:       Returns the maxim for the x or y for
'*                         changing label placement.
'*          MinHome: :     Returns the minimum for the x or y for
'*                         changing label placement.
'*          PrintLabel:    Prints the current label in the buffer.
'*                         Returns true if successful.
'*          SaveOptions:   Save the current printer options.
'*          SendData:      Addes new data to the template.
'*                         Returns true if successful
'*          SendTemplate:  Gets a new template. Returns true if successful.
'*          Version:       Returns the subsystem version.
'*
'************************************************************************
Option Explicit
'******************************************************************
Private Const m_intRESET_WAIT_SEC = 2

'******************************************************************
'  Constents to talk to Intermec printer
'  Some printer codes have control codes in them
'  use the Termainal font to see them.
Private Const m_posFIELD_DATA = 16 'This is a line position
Private Const m_posFIELD_COL = 12
Private Const m_posFIELD_ROW = 8
Private Const m_lenFIELD_POS = 4
Private Const m_strFIELD_FMT = "0000"
Private Const m_strSTART_OF_LINE = "[1-4]" 'this is 1 through 4 to be used by like operator
Private Const m_strDARK_ADJUST_MARKER = "H"
Private Const m_strDARK_ADJUST_FMT = "00"
Private Const m_strEOL = vbCrLf

'  Max and Min's for printer pramaters
Private Const m_intMAX_DARK_ADJUST = 30
Private Const m_intMIN_DARK_ADJUST = 0
Private Const m_intMAX_HOME = 100
Private Const m_intMIN_HOME = 0

'  Internal field markers for template
Private Const m_strX_POS = "\xxx" ' x Position for the data line
Private Const m_strY_POS = "\yyy" ' y Position for the data line
Private Const m_strDATA = "\d:" ' Data marker
Private Const m_strDARKNESS_ADJUST = "\a" ' Darkness adjust marker
Private Const m_strFIELD_NAME = "SNUM"

'  THE TEMPLATE
Private ma_strCodeLines() As String

'  Dark adjust setting in the template
Private m_strDarkAdjust  As String

'  Template path
Private m_strTemplatePath  As String

'  contasins the label to be printed
Private m_strLabelBuffer As String

'******************************************************************
'  class specific data
'  class initialization status
Private m_blnInitStatus As Boolean

Private m_strName As String
Private m_strDeviceName As String

Private m_strModel_Version As String

'  declare the communications class
Private m_objPrinterPort As clsSerialComm

Public Function MaxHome() As Integer

   MaxHome = m_intMAX_HOME
   
End Function ' MaxHome

Public Function MinHome() As Integer

   MinHome = m_intMIN_HOME
   
End Function ' MaxHome


Private Sub Class_Initialize()

   #If ccShip_Ver Then
      On Error GoTo Class_Initialize_Error
   #Else
      On Error GoTo 0
   #End If

   m_strName = "clsLabelPrint"
   m_strDeviceName = "PRINTER"
   
   m_blnInitStatus = True
   
   '  Open the communication port
   Set m_objPrinterPort = New clsSerialComm
   m_blnInitStatus = Not (m_objPrinterPort Is Nothing)
   '  now initialize the port
   If m_blnInitStatus Then
      m_blnInitStatus = m_objPrinterPort.Initialize(strDeviceName:=m_strDeviceName)
   End If
                       
   Exit Sub
   
Class_Initialize_Error:
      
   m_blnInitStatus = False
   ProccessError "Class_Initialize", m_strName, Err.Number, Err.Description
   
End Sub 'Class_Initialize


Public Function Version() As String

   Version = m_strModel_Version
   
End Function 'Version



Public Function InitStatus() As Boolean
   
   InitStatus = m_blnInitStatus
   
End Function 'InitStatus




Public Function GetTemplate(strPathFileName As String) As Boolean

   
 If (g_blnOpenTraceLogFile) Then TraceLog ("Class=LabelPrint: GetTemplate")
   
   
   Dim strTemplateBuffer As String
   Dim hFile As Integer
   Dim i As Integer
   

   #If ccShip_Ver Then
      On Error GoTo GetTemplate_Error
   #Else
      On Error GoTo 0
   #End If
 
   GetTemplate = False
    
   hFile = FreeFile
   If hFile = 0 Then
      Err.Raise g_errNO_FILE_HANDAL, , LoadResString(resERR_PRT_TPLATE_NO_HANDAL)
   Else
      If (Dir(strPathFileName, vbNormal) = "") Then
         
         MsgBox ("Template File: " + strPathFileName + " Does Not Exist!")
         Exit Function
      End If
      
      Open strPathFileName For Input Access Read As #hFile
      ReDim ma_strCodeLines(0)
      Do While Not EOF(hFile)
         Line Input #hFile, strTemplateBuffer
         
         '  Save the line in the buffer
         ma_strCodeLines(i) = strTemplateBuffer
         
         '  if not at end of file add another string to the array
         If Not EOF(hFile) Then
            ReDim Preserve ma_strCodeLines(UBound(ma_strCodeLines) + 1)
            i = i + 1
         End If
      Loop
   End If
   
   Close hFile
   
   GetTemplate = True
   
   Exit Function

GetTemplate_Error:

   Dim intErrNum As Integer
   
   intErrNum = Err.Number
   If (intErrNum = g_errFILE_NOT_FOUND) Then
     PrinterError "GetTemplate", m_strName, _
                    g_errFILE_NOT_FOUND, _
                    LoadResString(resERR_PTR_TPLATE_NO_FILE) & vbCrLf & strPathFileName
   ElseIf intErrNum = g_errPATH_NOT_FOUND Then
      PrinterError "GetTemplate", m_strName, _
                    g_errPATH_NOT_FOUND, _
                    LoadResString(resERR_PRT_TPLATE_NO_PATH) & vbCrLf & strPathFileName
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






Public Property Get DarkAdjust() As String

   DarkAdjust = m_strDarkAdjust
   
End Property 'Get DarkAdjust

Public Property Let DarkAdjust(vNewValue As String)

   m_strDarkAdjust = vNewValue
   
End Property 'Let DarkAdjust

Public Property Get XHome() As String

'   XHome = ma_udtDataLines(0).intXloc
   
End Property 'Get strXHome

Public Property Let XHome(vNewValue As String)

   Dim i As Integer
   
'   ma_udtDataLines(i).intXloc = vNewValue
   
End Property 'Let strXHome
 
 

Public Property Get YHome() As String

'   YHome = ma_udtDataLines(0).intYloc
   
End Property 'Get strYHome

Public Property Let YHome(vNewValue As String)

   Dim i As Integer
   
'   For i = 0 To UBound(ma_udtDataLines)
'      With ma_udtDataLines(i)
'         .intYloc = vNewValue + .intOffSet
'      End With 'ma_udtDataLines(i)
'   Next i
      
End Property 'Let strYHome

Public Function MaxDarkAdjust() As Integer

   MaxDarkAdjust = m_intMAX_DARK_ADJUST
   
End Function 'MaxDarkAdjust
Public Function MinDarkAdjust() As Integer

   MinDarkAdjust = m_intMIN_DARK_ADJUST
   
End Function 'MinDarkAdjust





Public Sub SaveOptions()

   Dim strTemplateBuffer As String
   Dim hFile As Integer
   Dim idxDataLine As Integer
   Dim idxCodeLine As Integer
   Dim a_strTempBuff() As String
   Dim i As Integer
   
   #If ccShip_Ver Then
      On Error GoTo SaveOptions_Error
   #Else
      On Error GoTo 0
   #End If
 
'   BuildTemplate a_strTempBuff()
    
   hFile = FreeFile
   If hFile = 0 Then
      Err.Raise g_errNO_FILE_HANDAL, , LoadResString(resERR_PRT_TPLATE_NO_HANDAL)
   Else
      Open m_strTemplatePath For Output Access Write As #hFile
      For i = 0 To UBound(a_strTempBuff)
         Print #hFile, a_strTempBuff(i)
      Next
   End If
   
   Close hFile
   
   Exit Sub

SaveOptions_Error:

   Dim intErrNum As Integer
   
   If intErrNum = g_errPATH_NOT_FOUND Then
      PrinterError "SaveOptions", m_strName, _
                    g_errPATH_NOT_FOUND, _
                    LoadResString(resERR_PRT_TPLATE_NO_PATH) & vbCrLf & m_strTemplatePath
   Else
      ProccessError "GetTemplate", m_strName, Err.Number, Err.Description
   End If
   
End Sub 'SaveOptions



Public Function PrintLabel(strOut As String) As Boolean
'  This builds a output string from the template and string sent in
'  then send the string to the printer

   TraceLog ("Class=LabelPrint: PrintLabel = " + strOut)


   Dim i As Integer
   Dim strBuffer As String
   
   #If ccShip_Ver Then
      On Error GoTo PrintLabel_Error
   #Else
      On Error GoTo 0
   #End If

   PrintLabel = False
   If g_blnSimulator Then
      PrintLabel = True
      Exit Function
   End If
      
   For i = 0 To UBound(ma_strCodeLines)
      If InStr(ma_strCodeLines(i), m_strDATA & m_strFIELD_NAME) <> 0 Then
         '  prep the line for the data
         strBuffer = strBuffer & Left(ma_strCodeLines(i), InStr(ma_strCodeLines(i), m_strDATA & m_strFIELD_NAME) - 1)
         '  put data into the data line
         strBuffer = strBuffer & strOut
         '  Put end of line back on
         strBuffer = strBuffer & Mid(ma_strCodeLines(i), InStr(ma_strCodeLines(i), m_strDATA & m_strFIELD_NAME) + Len(m_strDATA & m_strFIELD_NAME))
      Else ' copy code to buffer
         strBuffer = strBuffer & ma_strCodeLines(i)
      End If
   Next i
      
   '  Send data to the output port
   m_objPrinterPort.Buffer = strBuffer
   
   PrintLabel = True
     
   Exit Function

PrintLabel_Error:

   ProccessError "PrintLabel", m_strName, Err.Number, Err.Description
   PrintLabel False

End Function 'PrintLabel



