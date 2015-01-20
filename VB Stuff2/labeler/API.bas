Attribute VB_Name = "modAPI"
'************************************************************************
'*           Computype, Inc.
'*       NextStep Automation Group
'*
'*     © Copywrite 1996 Computype, Inc.
'*
'*        2-Axis Label Applicator
'*           Control Subsystem
'*       Win and general API module
'*
'*
'*    Date of origin:
'*    Original author: Michael D. Reed
'*
'* Module purpose:
'*    This module contains the references to the Windows API
'*    as well as a place to store general DLL references.  It
'*    also contains a VB wrapper for each call to a DLL.
'*
'************************************************************************
Option Explicit


Public Declare Function GetPrivateProfileSection Lib "kernel32" Alias "GetPrivateProfileSectionA" (ByVal lpAppName As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long
Public Declare Function GetPrivateProfileString Lib "kernel32" Alias "GetPrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long

Public Const ENUM_BUF_SIZE = 255


Public Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)

Private Declare Function ConvBase36 Lib "CompUtil.dll" (ByVal lConvert As Long, ByVal strConvert As String) As Integer

Public Sub SleepSec(intTimeSec As Integer)
   
   Call Sleep(CLng(intTimeSec * 1000))

End Sub 'SleepSec
Public Sub SleepMSec(lngTimeMSec As Long)
   
   Call Sleep(CLng(lngTimeMSec))

End Sub 'SleepSec



Public Function Cbase36(lngNewValue As Long, strFormat As String) As String
'  This function converts a long integer to a base 36 number.
'  The format string is similar to the format statement format string.

   Dim strBuffer As String
   Dim intRetVal As Integer
   
   #If ccShip_Ver Then
      On Error GoTo Cbase36_Error
   #Else
      On Error GoTo 0
   #End If
   
   ' Provide a destination string.
   strBuffer = Space(Len(strFormat))
    
   ' Convert number to a Base 36 string. The
   ' string IS NULL terminated! Return value
   ' is 0 for success, negative for failure.
   intRetVal = ConvBase36(lngNewValue, strBuffer)
   
   If intRetVal = 0 Then
      strBuffer = Trim(strBuffer)
      If InStr(strBuffer, Chr(0)) <> 0 Then
         strBuffer = Left(strBuffer, InStr(strBuffer, Chr(0)) - 1)
      End If
      If Len(strBuffer) < Len(strFormat) Then
         strBuffer = Left(strFormat, Len(strFormat) - Len(strBuffer)) & UCase(strBuffer)
      End If
       ' Display converted number.
      Cbase36 = strBuffer
   Else
      Err.Raise g_errBASE36_CONVERSION_ERROR, , LoadResString(resERR_BASE36_CONVERSION_ERROR)
   End If
   
   Exit Function

Cbase36_Error:

   ProccessError "Cbase36", "modAPI", Err.Number, Err.Description

End Function 'Cbase36

'---------------------------------------------------------------------------
'
'   GetProfile() - Get a value or enumerate keys in Labeler INI file
'
' Get a value given the section and key, or enumerate keys given the
' section name and "" for the key. If enumerating, the list of keys for
' the given section is returned as a null-separated string, with a
' double null at the end.
'
'---------------------------------------------------------------------------
Public Function GetProfile(sSection As String, sKey As String, strSource, ByRef blnResult As Boolean) As String
On Error GoTo Error_Control:
    
    Dim retLen As Long
    Dim buf As String * ENUM_BUF_SIZE
   
    blnResult = True

    If sKey <> "" Then
        retLen = GetPrivateProfileString(sSection, sKey, "", buf, ENUM_BUF_SIZE, strSource)
    Else
        retLen = GetPrivateProfileString(sSection, 0&, "", buf, ENUM_BUF_SIZE, strSource)
    End If
    If retLen = 0 Then
        GetProfile = ""
    Else
        GetProfile = Left$(buf, retLen)
    End If

Exit Function

Error_Control:
   blnResult = False


End Function




