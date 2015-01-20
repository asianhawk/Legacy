Attribute VB_Name = "modError"
'************************************************************************
'*           Computype, Inc.
'*       NextStep Automation Group
'*
'*     © Copywrite 1996 Computype, Inc.
'*
'*        3-Axis Label Applicator
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
Private Const m_intAppOffset = 64000
Public Const g_intDIG_IO_OFFSET = 0 + m_intAppOffset
Public Const g_intPRINTER_OFFSET = 100 + m_intAppOffset
Public Const g_intIAI_OFFSET = 200 + m_intAppOffset
Public Const g_intDB_OFFSET = 300 + m_intAppOffset

'  Printer errors
Public Const g_errNO_FILE_HANDAL = g_intPRINTER_OFFSET + 1

'  IAI errors
Public Const g_errX_DATA_NEG = g_intIAI_OFFSET + 1
Public Const g_errY_DATA_NEG = g_intIAI_OFFSET + 2
Public Const g_errZ_DATA_NEG = g_intIAI_OFFSET + 3
Public Const g_errTH_DATA_NEG = g_intIAI_OFFSET + 4

'  DB errors
Public Const g_errERR_NULL_CONFIG_DATA = g_intDB_OFFSET + 1

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
   strMessage = strMessage & "Msg: " & ErrorText
   strMessage = strMessage & "Program will abort."
   
   MsgBox strMessage, vbOKOnly + vbCritical, "Error in " & App.Title
   
   
End Sub 'ProccessError

#If Not ccShip_Ver Then
Public Sub Assert(ProcName As String, _
                         ModName As String, _
                         AssertText As String)

   Dim strMessage As String
   
   strMessage = "Assert in: " & vbCrLf
   strMessage = strMessage & "Proc: " & ProcName & vbCrLf
   strMessage = strMessage & "Module: " & ModName & vbCrLf
   strMessage = strMessage & "Assertion: " & AssertText
   strMessage = strMessage & "Program will abort."
   
   MsgBox strMessage, vbOKOnly + vbCritical, "Assert rasied in " & App.Title
   
End Sub 'Assert
#End If
