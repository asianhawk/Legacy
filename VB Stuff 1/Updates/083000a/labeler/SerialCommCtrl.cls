VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsSerialCommCtrl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
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
'*          Serial Communications
'*
'*    Date of origin: <Date>
'*    Original author: Michael D. Reed
'*
'* Class purpose:
'*    This class provides the interface between the labeler
'*    program and the serial communications form.  The serial
'*    communications form contains the interface to the system
'*    serial communications software. This works with the frmSerialComm.
'*    There is an instants of this class for each port used.
'*
'************************************************************************
Option Explicit
'******************************************************************

Private m_strName As String

Private m_blnInitialized As Boolean

Private m_intPortID As Integer

Private m_strEndTXMark As String

Private m_strTempBuffer As String

Private m_strInputBuffer As String

Private m_blnDataReady  As Boolean

Private m_blnWatchDogTimer As Boolean

'  used for exe functions to determan if an error happened
Private m_blnTimeoutOK As Boolean

Private m_blnCTS As Boolean
Private Sub Class_Initialize()
   
   m_blnInitialized = True
   
   m_blnTimeoutOK = False
   
End Sub 'Class_Initialize



Private Property Get LocalBuffer() As String

   '  Start WatchDog timer if needed
   If m_blnWatchDogTimer Then
      frmSerialComm.tmrWatchDog(m_intPortID).Enabled = True
   End If
   
   '  Waite untill the ready to send is set true
   Do While Not m_blnDataReady
      DoEvents
   Loop
   
   '  Send what is in the buffer to the monitor form
   frmSerialComm.DisplayIOMsg intPortID:=m_intPortID, vntInMsg:=m_strInputBuffer
   
   '  Set data ready to false get the data and clear the input buffer
   m_blnDataReady = False
   LocalBuffer = m_strInputBuffer
   m_strInputBuffer = ""
   
   frmSerialComm.tmrWatchDog(m_intPortID).Enabled = False

End Property 'Get LocalBuffer

Public Property Let LocalBuffer(strOutput As String)

   With frmSerialComm
   
'      .DisplayIOMsg intPortID:=m_intPortID, vntOutMsg:=strOutput
      
      DoEvents
      
      '  Set ready to send to false and send data out
      
      If Not g_blnSimulator Then
         
          .comSerialComm(m_intPortID).Output = strOutput
      ElseIf g_blnSimulator And m_intPortID = 6 Then
          .comSerialComm(m_intPortID).Output = strOutput
      End If
      
   End With '.txtPortToIFBuffer.Text
   
End Property 'Let LocalBuffer


Public Function Initialize(intPortID As Integer, strPortSettings As String, _
                           vbHandShaking As Integer, blnDTREnable As Boolean, _
                           blnRTSEnable As Boolean, intRThreshold As Integer, _
                           blnNullDiscard As Boolean, chrParityReplace As String, _
                           intSThreshold As Integer, intTimerInterval As Integer, _
                           intCTSTimeout As Integer, intDSRTimeout As Integer, _
                           intOutBufferSize As Integer, intInBufferSize As Integer, _
                           strEndTXMark As String, strName As String) As Boolean
   
   If m_blnInitialized Then
      ' Initialize the port used by the IAI Controller.
      m_blnInitialized = frmSerialComm.Initialize(objController:=Me, _
                           intPortID:=intPortID, strPortSettings:=strPortSettings, _
                           vbHandShaking:=vbHandShaking, blnDTREnable:=blnDTREnable, _
                           blnRTSEnable:=blnRTSEnable, intRThreshold:=intRThreshold, _
                           blnNullDiscard:=blnNullDiscard, chrParityReplace:=chrParityReplace, _
                           intSThreshold:=intSThreshold, intCTSTimeout:=intCTSTimeout, _
                           intDSRTimeout:=intDSRTimeout, intOutBufferSize:=intOutBufferSize, _
                           intInBufferSize:=intInBufferSize, intTimerInterval:=intTimerInterval)
   End If
   
   If m_blnInitialized Then
      m_strName = strName
      m_intPortID = intPortID
      m_strEndTXMark = strEndTXMark
      m_blnWatchDogTimer = (intTimerInterval <> 0)
   Else
      m_intPortID = 0
   End If
   
   Initialize = m_blnInitialized

End Function 'Initialize


Public Property Get Buffer() As String

   Buffer = LocalBuffer
   
End Property 'Get Buffer

Public Property Let Buffer(vNewValue As String)

   LocalBuffer = vNewValue

End Property 'Let Buffer

Public Sub TempBuffer(strCharsIn As String)

   Static s_strTemp As String
   
   If strCharsIn = "" Then Exit Sub
   
   s_strTemp = s_strTemp & strCharsIn
   '  See if theer is enough char to compair
   If Len(s_strTemp) < Len(m_strEndTXMark) Then Exit Sub
   If Right(s_strTemp, Len(m_strEndTXMark)) = m_strEndTXMark Then
      '  has the end of string come in if so store it in the input buffer
      '  and clear the static temp buffer
      m_strInputBuffer = s_strTemp
      s_strTemp = ""
      m_blnDataReady = True
   End If
   
End Sub 'TempBuffer

Public Sub TimeUp()

   Dim strMsg As String
   
   If Not m_blnTimeoutOK Then
      If m_intPortID = 5 Then
         strMsg = "IAI Controller Not Responding." & vbCrLf
         strMsg = strMsg + "Possible Reasons:" & vbCrLf
         strMsg = strMsg + "   1. Comm. Cable Not Plugged In" + vbCrLf
         strMsg = strMsg + "   2. Air Hose Disconnected "
       Else
                  
         strMsg = m_strName & " port " & m_intPortID & " timed out." & vbCrLf
         strMsg = strMsg & "Text=>" & m_strInputBuffer & "<-was in the input buffer." & vbCrLf
         strMsg = strMsg & "Buffer cleared."
       End If
      MsgBox strMsg, vbOKOnly + vbExclamation, "Serial Comm"
   
      m_strInputBuffer = ""
   End If
   
   m_blnDataReady = True
   
End Sub 'TimeUp

Public Property Get TimeOutOK() As Boolean

   TimeOutOK = m_blnTimeoutOK
   
End Property 'TimeoutOK

Public Property Let TimeOutOK(vNewValue As Boolean)

   m_blnTimeoutOK = vNewValue
   
End Property 'TimeoutOK

Public Property Get TimeOut() As Integer
   If Not g_blnSimulator Then
      TimeOut = frmSerialComm.tmrWatchDog(m_intPortID).Interval
   End If
End Property 'Get TimeOut

Public Property Let TimeOut(vNewValue As Integer)
   If Not g_blnSimulator Then

     m_blnWatchDogTimer = (vNewValue <> 0)
     frmSerialComm.tmrWatchDog(m_intPortID).Interval = vNewValue
   End If
End Property 'Let TimeOut



