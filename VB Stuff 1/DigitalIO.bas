Attribute VB_Name = "modDigitalIO"
'************************************************************************
'*           Computype, Inc.
'*       NextStep Automation Group
'*
'*     © Copywrite 1996 Computype, Inc.
'*
'*        3-Axis Label Applicator
'*           Control Subsystem
'*
'*          CompuBoard Digital I/O Board CIO-DIO24
'*          Control Global Module
'*
'*    Date of origin: 1/30/96
'*    Original author: Michael D. Reed
'*
'* Class purpose:
'*    This module contains the global constant delectations.
'*
'************************************************************************
'******************************************************************
Option Explicit

'  Direction strings should match the database direction strings.
Public Const g_strINPUT = "Input"
Public Const g_strOUTPUT = "Output"

'  Port numbers should match the database strings.
Public Const g_strPORT_A = "A"
Public Const g_strPORT_B = "B"
Public Const g_strPORT_CL = "CL"
Public Const g_strPORT_CH = "CH"

Public Const g_idxBIT_NUM = 0
Public Const g_idxBIT_VAL = 1

'  Bit indicators
Public Const g_chrBIT_0 = "0"
Public Const g_chrBIT_1 = "1"


Public Sub DigIOError(ProcName As String, _
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
   
   MsgBox strMessage, vbOKOnly + vbCritical, "Error in Digital SubSystem"
   
End Sub 'ProccessError



