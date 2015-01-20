Attribute VB_Name = "TraceUtilities"
Public g_strTraceLog As String
Public g_blnOpenTraceLogFile As Boolean

Public g_blnErrorTraceLogHandle As Long
Public g_lngTraceLogHandle As Long

Public g_lngSequenceNumber As Long
Public g_lngMaxSequenceNumber As Long

Public g_blnLogError As Boolean
Public g_nMaxDefSequence As Integer


Public Sub TraceLog(strBuffer As String)
Dim strTime As String
Dim strDate As String
Static strOutput As String
Static blnInit As Boolean
    
    If Not blnInit Then
       InitTrackingFile
       blnInit = True
    End If

    If (Not g_blnOpenTraceLogFile) And (Not g_blnLogError) Then
    
       If g_nMaxDefSequence > 15 Then 'must limit the size of the strOutput var

          strOutput = ""
          g_nMaxDefSequence = 0
       
       End If
       strOutput = strOutput + "[" + Format(Date, "ddmmyy") + "] " + _
                "[" + Format(Time, "hh:mm:ss") + "] " + strBuffer + vbCrLf
       
       
       
       
       Exit Sub
    
    
    End If

    
    
    If (Not g_blnLogError) Then
      
      strOutput = strOutput + "[" + Format(Date, "ddmmyy") + "] " + _
                "[" + Format(Time, "hh:mm:ss") + "] " + strBuffer + vbCrLf
      
      
      
      If (g_lngSequenceNumber = g_lngMaxSequenceNumber) Then
        OpenTraceLog
        Print #g_lngTraceLogHandle, strOutput
        CloseTraceLog
        strOutput = ""
        g_lngSequenceNumber = 0
      End If
   Else
      
      OpenErrorTraceLog
      
      Print #g_blnErrorTraceLogHandle, strBuffer + vbCrLf
      Print #g_blnErrorTraceLogHandle, strOutput
      
      CloseErrorTraceLog
      
     
   End If
End Sub

Public Sub OpenTraceLog()
Dim strDate As String
Dim strFileName As String
  On Error GoTo OpenTraceLog_error
  g_lngTraceLogHandle = FreeFile(0)
  
  strDate = Date
  
  
  strFileName = "c:\Labeler" + "_TraceLog.txt"
  
  
  If (Dir(strFileName, vbNormal) <> "") And (g_lngSequenceNumber = g_lngMaxSequenceNumber) Then
     Kill strFileName
  End If
  
  Open strFileName For Output As #g_lngTraceLogHandle

Exit Sub
OpenTraceLog_error:
  Close #g_lngTraceLogHandle
 
End Sub


Public Sub CloseTraceLog()
  If (g_blnOpenTraceLogFile) Then
     Close g_lngTraceLogHandle
  End If

End Sub

Public Sub OpenErrorTraceLog()
Dim strDate As String
Dim strFileName As String
  On Error GoTo OpenErrorTraceLog_error
  
  g_blnErrorTraceLogHandle = FreeFile(0)
  
  strDate = Date
  
  strFileName = "c:\Labeler_Error" + Format(strDate, "mmddyy") + "_TraceLog.txt"
  
  
  If (Dir(strFileName, vbNormal) <> "") Then
     Kill strFileName
  End If
  Open strFileName For Output As #g_blnErrorTraceLogHandle

Exit Sub


OpenErrorTraceLog_error:
  Close #g_blnErrorTraceLogHandle
 
End Sub

Public Sub CloseErrorTraceLog()
  
  If (g_blnLogError) Then
     Close g_blnErrorTraceLogHandle
  End If

End Sub

Private Sub InitTrackingFile()

  
  
  If (Dir("c:\Labeler_TraceLog.txt", vbNormal) <> "") Then
     Kill "c:\Labeler_TraceLog.txt"
  End If

End Sub
