VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsSerialComm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
'************************************************************************
'*           Computype, Inc.
'*       NextStep Automation Group
'*
'*     © Copywrite 1996 Computype, Inc.
'*
'*        2-Axis label Applicator
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

'  Class name for error checking
Private m_strName As String

'  refrence to assoicated form
Private m_objMyForm As Object


'  Set if class initialized ok
Private m_blnInitialized As Boolean

'  Port Identification stuff
Private m_strDeviceName As String
Private m_strPortName As String
Private m_intPortIndex As Integer

'  IO buffesr and control
Private m_strTxTerminatingChr As String
Private m_strTempBuffer As String
Private m_strInputBuffer As String
Private m_blnDataReady  As Boolean
Private m_blnWatchDogTimer As Boolean

'  used for exe functions to determan if an error happened
Private m_blnTimeoutOK As Boolean

Private m_blnCTS As Boolean

'  Who to call if have data ready
'  if empty then not used
Private m_blnCallBack As Boolean
Private m_objCallBackFunction As Object

Public Sub SetMyForm(objMyForm As Object)
'  Set the reference to the form associated to this class.

   Set m_objMyForm = objMyForm
   
End Sub 'SetMyForm


Public Sub Show()

   m_objMyForm.Show
   
End Sub 'Show
Public Sub Hide()

   m_objMyForm.Hide
   
End Sub 'Hide




Public Function GetMonitorReference() As Object

   Set GetMonitorReference = frmSerialComm
   
End Function 'ViewForm


Private Sub Class_Initialize()
   
   m_blnTimeoutOK = False
   
   m_strName = "clsSerialCommCtrl"
   
   m_blnInitialized = True
   
End Sub 'Class_Initialize



Public Property Get Buffer() As String

   #If ccShip_Ver Then
      On Error GoTo GetBuffer_Error
   #Else
      On Error GoTo 0
   #End If

   #If g_blnSimulator Then
      
      '  Send what is in the buffer to the monitor form
      frmSerialComm.DisplayIOMsg intPortID:=m_intPortIndex, vntInMsg:=" Get Buffer"
      Exit Property
   #End If

   '  Start WatchDog timer if needed
   If m_blnWatchDogTimer Then
      frmSerialComm.tmrWatchDog(m_intPortIndex).Enabled = True
   End If
   
   '  Waite untill the ready to send is set true
   Do While Not m_blnDataReady
      DoEvents
   Loop
   
   '  Send what is in the buffer to the monitor form
  ' frmSerialComm.DisplayIOMsg intPortID:=m_intPortIndex, vntInMsg:=m_strInputBuffer
   
   '  Set data ready to false get the data and clear the input buffer
   m_blnDataReady = False
   Buffer = m_strInputBuffer
   m_strInputBuffer = ""
   
   frmSerialComm.tmrWatchDog(m_intPortIndex).Enabled = False

   Exit Property

GetBuffer_Error:

   ProccessError "Get Buffer", m_strName, Err.Number, Err.Description
   Buffer = ""

End Property 'Get Buffer

Public Property Let Buffer(strOutput As String)

   #If ccShip_Ver Then
      On Error GoTo LetBuffer_Error
   #Else
      On Error GoTo 0
   #End If

   With frmSerialComm
   
      .DisplayIOMsg intPortID:=m_intPortIndex, vntOutMsg:=strOutput
      If g_blnSimulator Then Exit Property
      
      DoEvents
      
      #If Not g_blnSimulator Then
         '  Set ready to send to false and send data out
         .comSerialComm(m_intPortIndex).Output = strOutput
      #End If
      
   End With '.txtPortToIFBuffer.Text
   
   Exit Property

LetBuffer_Error:

   ProccessError "Let Buffer", m_strName, Err.Number, Err.Description

End Property 'Let Buffer


Public Function Initialize(strDeviceName As String, Optional vntCallBack As Variant) As Boolean
   
   #If ccShip_Ver Then
      On Error GoTo Initialize_Error
   #Else
      On Error GoTo 0
   #End If

   If m_blnInitialized Then
      m_blnInitialized = frmSerialComm.Initialize( _
                           objController:=Me, _
                           strDeviceName:=strDeviceName)
   End If
   'code???
   If m_blnInitialized And Not IsMissing(vntCallBack) Then
      Set m_objCallBackFunction = vntCallBack
      m_blnCallBack = True
   Else
      m_blnCallBack = False
   End If
   Initialize = m_blnInitialized

   Exit Function

Initialize_Error:

   ProccessError "Initialize", m_strName, Err.Number, Err.Description
   Initialize = False

End Function 'Initialize



Public Sub TempBuffer(strCharsIn As String)

   #If ccShip_Ver Then
      On Error GoTo TempBuffer_Error
   #Else
      On Error GoTo 0
   #End If

   Static s_strTemp As String
   
   If strCharsIn = "" Then Exit Sub
   
   s_strTemp = s_strTemp & strCharsIn
   '  See if theer is enough char to compair
   If Len(s_strTemp) < Len(m_strTxTerminatingChr) Then Exit Sub
   If Right(s_strTemp, Len(m_strTxTerminatingChr)) = m_strTxTerminatingChr Then
      '  has the end of string come in if so store it in the input buffer
      '  and clear the static temp buffer
      m_strInputBuffer = Left((s_strTemp), Len(s_strTemp) - Len(m_strTxTerminatingChr))
      s_strTemp = ""
      m_blnDataReady = True
      If m_blnCallBack Then
         m_objCallBackFunction.DataReady
      End If
   End If
   
   Exit Sub

TempBuffer_Error:

   ProccessError "TempBuffer", m_strName, Err.Number, Err.Description

End Sub 'TempBuffer

Public Sub TimeUp()

   Dim strMsg As String
   
   #If ccShip_Ver Then
      On Error GoTo TimeUp_Error
   #Else
      On Error GoTo 0
   #End If

   If Not m_blnTimeoutOK Then
      strMsg = m_strName & " port " & m_intPortIndex & " timed out." & vbCrLf
      strMsg = strMsg & "Text=>" & m_strInputBuffer & "<-was in the input buffer." & vbCrLf
      strMsg = strMsg & "Buffer cleared."
      
      MsgBox strMsg, vbOKOnly + vbExclamation, "Serial Comm"
   
      m_strInputBuffer = ""
   End If
   
   m_blnDataReady = True
   
   Exit Sub

TimeUp_Error:

   ProccessError "TimeUp", m_strName, Err.Number, Err.Description

End Sub 'TimeUp

Public Property Get TimeOutOK() As Boolean

   TimeOutOK = m_blnTimeoutOK
   
End Property 'TimeoutOK

Public Property Let TimeOutOK(vNewValue As Boolean)

   m_blnTimeoutOK = vNewValue
   
End Property 'TimeoutOK

Public Property Get TimeOut() As Integer
   
   TimeOut = frmSerialComm.tmrWatchDog(m_intPortIndex).Interval
   
End Property 'Get TimeOut

Public Property Let TimeOut(vNewValue As Integer)

   m_blnWatchDogTimer = (vNewValue <> 0)
   frmSerialComm.tmrWatchDog(m_intPortIndex).Interval = vNewValue
   
End Property 'Let TimeOut




Public Property Get DeviceName() As String
   
   DeviceName = m_strDeviceName
   
End Property 'DeviceName

Public Property Let DeviceName(vNewValue As String)

   m_strDeviceName = vNewValue
   
End Property 'DeviceName

Public Property Get PortName() As String

   PortName = m_strPortName

End Property 'PortName

Public Property Let PortName(vNewValue As String)

   m_strPortName = vNewValue
   
End Property 'PortName

Public Property Get PortIndex() As Integer

   PortIndex = m_intPortIndex
   
End Property   'PortIndex

Public Property Let PortIndex(vNewValue As Integer)

   m_intPortIndex = vNewValue

End Property 'PortIndex

Public Property Get TxTerminatingChr() As String

   TxTerminatingChr = m_strTxTerminatingChr
   
End Property 'TxTerminatingChr

Public Property Let TxTerminatingChr(vNewValue As String)
   
   m_strTxTerminatingChr = vNewValue
   
End Property 'TxTerminatingChr

Public Property Get WatchDogTimer() As Boolean
   
   WatchDogTimer = m_blnWatchDogTimer

End Property 'WatchDogTimer

Public Property Let WatchDogTimer(vNewValue As Boolean)

   m_blnWatchDogTimer = vNewValue
   
End Property 'WatchDogTimer
