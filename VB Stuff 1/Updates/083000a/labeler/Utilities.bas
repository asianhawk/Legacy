Attribute VB_Name = "modUtilities"
'************************************************************************
'*           Computype, Inc.
'*       NextStep Automation Group
'*
'*     � Copywrite 1996 Computype, Inc.
'*
'*        3-Axis Label Applicator
'*           Control Common
'*
'*            Utilities
'*
'*    Date of origin: <Date>
'*    Original author: Michael D. Reed
'*
'* Module purpose:
'*    This module contains procedures used through
'*    out the several subsystems and programs.
'*
'************************************************************************
Option Explicit
'******************************************************************

'  some constents usefull for the utilities
Public Const g_intSWAP_LEN_2 = 2

'  global flags
Public g_blnTest As Boolean
Public g_blnLog As Boolean

Private Const m_strName = "modUtilities"


Public Sub MessageDisplay(strMessage As String)

   With frmMessage
      .rtfInstructions.Visible = False
      .Height = .PanalMsgHight
      .sspMessage.Height = .ScaleHeight
      .sspMessage.Caption = strMessage
      .sspMessage.Enabled = True
      .Show
      .Refresh
   End With 'frmMessage
   DoEvents
   
End Sub 'MessageDisplay

Public Sub InstructionsDisplay(strFileName As String)

   With frmMessage
      .Height = .RtfMsgHight
      .sspMessage.Height = .ScaleHeight
      .sspMessage.Enabled = False
      .rtfInstructions.Visible = True
      .rtfInstructions.LoadFile strFileName, rtfRTF
      .Show
      .Refresh
       
   End With 'frmMessage
   DoEvents
   
End Sub 'InstructionsDisplay

Public Sub InstructionsRemove()

   With frmMessage
      If Not .Visible Then Exit Sub
      .Height = .RtfMsgHight
      .rtfInstructions.Visible = False
      .Hide
      .Refresh
   End With 'frmMessage
   DoEvents

End Sub 'InstructionsRemove


Public Sub Log(strWho As String, strMeg As String)

   Static fhLog As Integer
   
   #If ccShip_Ver Then
      On Error GoTo Log_Error
   #Else
      On Error GoTo 0
   #End If
   Exit Sub
   If Not g_blnLog Then Exit Sub
   
   If fhLog = 0 Then
      fhLog = FreeFile
      On Error Resume Next
      Open App.Path & "\" & App.EXEName & ".log" For Output Access Write As #fhLog
      If Err.Number <> 0 Then
         g_blnLog = False
      Else
         Print #fhLog, "[" & Format(Now, "Long Time") & "] " & strWho & " -> " & strMeg
      End If
      On Error GoTo 0
   Else
      Print #fhLog, "[" & Format(Now, "Long Time") & "] " & strWho & " -> " & strMeg
   End If

   Exit Sub

Log_Error:

   ProccessError "Log", m_strName, Err.Number, Err.Description

End Sub 'Log

Public Sub MessageRemove()

   With frmMessage
      If Not .Visible Then Exit Sub
      .Hide
      .sspMessage.Enabled = True
      .Refresh
   End With 'frmMessage
   DoEvents

End Sub 'MessageRemove

Public Sub SetMonitorForm(frmMonitor As Form)

   With frmMonitor
      .Hide
      If g_blnTest Then
         .WindowState = vbNormal
         .Refresh
         .Show
      Else
         .WindowState = vbNormal
      End If
   End With
   
End Sub 'SetMonitorForm


Public Function FormatHex(intVal As Integer, strFormat As String) As String

   Dim strTemp As String
   
   '  Convert the value to a hex number
   strTemp = Hex(intVal)
   If Left(strFormat, 1) = "0" Then
      '  Assume all 0 so fixed string is wanted to
      '  add 0 in front of the number to fill out the length.
      While Len(strTemp) < Len(strFormat)
         strTemp = "0" & strTemp
      Wend
   End If
   
   FormatHex = strTemp
      
End Function 'FormatHex

Public Function FillString(strShort As String, intLen As Integer, chrFill) As String
 
   FillString = String(intLen, chrFill) & strShort
   
End Function 'FillString



Public Function NextToken(ByRef r_strText As String, ByVal v_strDelmList As String) As String

'<t>#If ShipVer Then
'<t>   On Error GoTo GetNextToken_Error
'<t>#End If
      
   Dim lngDelmPos As Long
   Dim i As Integer

'<t>   #If DB_DEV Then
'<t>      If v_strDelmList = "" Then Assert "Get NextToken", m_strName, "DlimiterList = """""
'<t>   #End If
   
   If r_strText = "" Then 'String sent in is empty so send back a null
      NextToken = ""
      Exit Function
   End If
   
   For i = 1 To Len(v_strDelmList)
      lngDelmPos = InStr(r_strText, Mid(v_strDelmList, i, 1))
      If lngDelmPos <> 0 Then 'A delmiter found so send back the token
         NextToken = Left(r_strText, lngDelmPos - 1)
         r_strText = Mid(r_strText, lngDelmPos + 1)
         Exit Function
      End If
   Next i
   
   ' no delimiters were found so send back rest of string and set to null
   NextToken = r_strText
   r_strText = ""
   
   Exit Function
   
'<t>GetNextToken_Error:

'<t>   ProccessError "NextToken", m_strName, Err.Number, Err.Description

End Function 'NextToken

Public Function SwapChar(strIn As String, intWidth As Integer) As String

   Dim strBuffTemp As String
   Dim idx As Integer
   
   strBuffTemp = ""
   idx = 1
   Do
      strBuffTemp = Mid(strIn, idx, intWidth) & strBuffTemp
      idx = idx + intWidth
   Loop Until idx >= Len(strIn)
   
   SwapChar = strBuffTemp
   
End Function 'SwapChar



Public Sub CenterForm(objForm As Form)

   With objForm
      .Move (Screen.Width - .Width) \ 2, (Screen.Height - .Height) \ 2
   End With 'objForm
   
End Sub 'CenterForm

Public Function IsMember(colCollection As Collection, strKey As String)

   Dim vntTemp As Variant
   
   On Error Resume Next
   
   vntTemp = colCollection.Item(strKey)
   IsMember = (Err.Number = 0)
   
   On Error GoTo 0
   
End Function 'IsMember

Public Function CleanString(strDirty As String) As String

   Dim strTemp As String
   Dim i As Integer
   
   For i = 1 To Len(strDirty)
      If " " <= Mid(strDirty, i, 1) Then ' GT then a space
         strTemp = strTemp & Mid(strDirty, i, 1)
      End If
   Next i
   
   strTemp = Trim(strTemp)
   
   CleanString = strTemp
   
End Function 'CleanString
