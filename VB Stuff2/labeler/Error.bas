Attribute VB_Name = "modError"
'************************************************************************
'*           Computype, Inc.
'*       NextStep Automation Group
'*
'*     © Copywrite 1996 Computype, Inc.
'*
'*        2-Axis Label Applicator
'*           Control Subsystem
'*
'*          Error reporting and handling subsystem.
'*
'*    Date of origin: 2/3/97
'*    Original author: Michael D. Reed
'*
'* Module purpose:
'*    This module contains the code for the error reporting
'*    and handling as well as the error codes used in this application.
'*
'************************************************************************
'  Options section
Option Explicit

'******************************************************************
'  Trapable errors
Public Const g_errFILE_NOT_FOUND = 53
Public Const g_errPATH_NOT_FOUND = 76

'  Application constants
Private Const m_intAppOffset = 63000
Private Const m_intINIT_OFFSET = 0 + m_intAppOffset
Private Const m_intPRINTER_OFFSET = 100 + m_intAppOffset
Private Const m_intDIG_IO_OFFSET = 200 + m_intAppOffset
Private Const m_intDB_OFFSET = 300 + m_intAppOffset
Private Const m_intDIGITAL_OFFSET = 400 + m_intAppOffset
Public Const g_intMOTION_ERROR_OFFSET = 500 + m_intAppOffset
Private Const m_intCONTROL_ERROR_OFFSET = 600 + m_intAppOffset
Private Const m_intOTHER_ERRORS_OFFSET = 900 + m_intAppOffset

'  Initilization errors
Public Const g_intINIT_PTR_OBJ = m_intINIT_OFFSET + 1
Public Const g_intINIT_INPUT_OBJ = m_intINIT_OFFSET + 2
Public Const g_intINIT_OUTPUT_OBJ = m_intINIT_OFFSET + 3
Public Const g_intINIT_SCANNER_OBJ = m_intINIT_OFFSET + 4
Public Const g_intINIT_MOVE_OBJ = m_intINIT_OFFSET + 5
Public Const g_intINIT_BECKON_OBJ = m_intINIT_OFFSET + 6

'  Printer errors
Public Const g_errNO_FILE_HANDAL = m_intPRINTER_OFFSET + 1
Public Const g_errDARKNESS_SETTING = m_intPRINTER_OFFSET + 2
Public Const g_errPRINTER_OPTIONS = m_intPRINTER_OFFSET + 3

'  DB errors
Public Const g_errERR_NULL_CONFIG_DATA = m_intDB_OFFSET + 1
Public Const g_errNO_JOB_MATCH = m_intDB_OFFSET + 2

'  Ditital errors
Public Const g_errOUT_OF_TIMERS = m_intDIGITAL_OFFSET + 1

'  Control errors
Public Const g_errINPUT_BIT_NOT_FOUND = m_intCONTROL_ERROR_OFFSET + 1
Public Const g_errOUTPUT_BIT_NOT_FOUND = m_intCONTROL_ERROR_OFFSET + 2
Public Const g_errNO_AIR = m_intCONTROL_ERROR_OFFSET + 3
Public Const g_errNO_CTRL_VOLTS = m_intCONTROL_ERROR_OFFSET + 4

'  other errors
Public Const g_errBASE36_CONVERSION_ERROR = m_intOTHER_ERRORS_OFFSET + 0


'******************************************************************

Public Sub ProccessError(ProcName As String, _
                         ModName As String, _
                         ErrorNumber As Long, _
                         ErrorText As String)
            
   Dim strMessage As String
   Dim intResp As Integer
   
   strMessage = "An error occured in: " & vbCrLf
   strMessage = strMessage & "Proc: " & ProcName & vbCrLf
   strMessage = strMessage & "Module: " & ModName & vbCrLf
   strMessage = strMessage & "Error number = " & ErrorNumber & vbCrLf
   strMessage = strMessage & "Msg: " & ErrorText & vbCrLf
   strMessage = strMessage & "Program will abort."
   
   g_blnLogError = True
   TraceLog ("Class=Labeler: OnEvent_LabelingComplete. If State<>(Manual Feed) panel count-> quantity+=1")

   MsgBox strMessage, vbOKOnly + vbCritical, "Error in " & App.Title
   
   modUtilities.Log "Error", strMessage
   #If cc_Labeler Then
      modMain.ExitEnd
   #Else
      End
   #End If

End Sub 'ProccessError

Public Sub ReportError(ProcName As String, _
                         ModName As String, _
                         ErrorNumber As Long, _
                         ErrorText As String)
            
   Dim strMessage As String
   Dim intResp As Integer
   
   strMessage = "An error occured in: " & vbCrLf
   strMessage = strMessage & "Proc: " & ProcName & vbCrLf
   strMessage = strMessage & "Module: " & ModName & vbCrLf
   strMessage = strMessage & "Error number = " & ErrorNumber & vbCrLf
   strMessage = strMessage & "Msg: " & ErrorText
   
   MsgBox strMessage, vbOKOnly + vbCritical, "Error in " & App.Title
   
   modUtilities.Log "Error", strMessage
   
End Sub 'ReportError


Public Sub Assert(ProcName As String, _
                         ModName As String, _
                         AssertText As String)

#If Not ccShip_Ver Then
   Dim strMessage As String
   
   strMessage = "Assert in: " & vbCrLf
   strMessage = strMessage & "Proc: " & ProcName & vbCrLf
   strMessage = strMessage & "Module: " & ModName & vbCrLf
   strMessage = strMessage & "Assertion: " & AssertText
   strMessage = strMessage & "Program will abort."
   
   MsgBox strMessage, vbOKOnly + vbCritical, "Assert rasied in " & App.Title
   
   Stop
#End If
End Sub 'Assert
