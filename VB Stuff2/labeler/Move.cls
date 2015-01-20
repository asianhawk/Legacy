VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsMove"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'************************************************************************
'*           Computype, Inc.
'*       NextStep Automation Group
'*
'*     © Copywrite 1997 Computype, Inc.
'*
'*        2-Axis label Applicator
'*           Control Subsystem
'*
'*        IA inatelligent Actuator
'*          SA Controller
'*
'*    Date of origin: August 6,1997
'*    Original author: Michael D. Reed
'*
'* Class purpose:
'*    This class controls the SA Controller.  This is a single axis subsystem.
'*    The Public items are:
'*       Functions:
'*          Initialize - Used to pass items needed to initialize class,
'*                       such as reference for call back for HomeComplete
'*                       and MoveComplete events.
'*          Ready - Read only and is true when subsystem is ready for use.
'*       Properties:
'*          Position - Set or reads a number between 1 and 97 relating
'*                     to a pre loaded distance form the home position.
'*          Name - Sets or gets the name given to this instance of the class.
'*       Events:
'*          MoveComplete - Last move operation is complete.
'*       Methods:
'*          Home - sets the initial 0 position.
'*          Move - moves to the position in the position property.
'*
'*       Note:
'*          This class uses the digital subsystem to communicate
'*          with the SA Controller.
'************************************************************************
'******************************************************************
Option Explicit

'  My name
Private m_strName As String

'  All initilized and redy to go
Private m_blnStatus As Boolean

'  Refrence to the digitial IO
Private m_objDigitalInput As Object
Private m_objDigitalOutput As Object

'  Call back refrences
Private m_objMoveComplete As Object '  who to informe for move complete

'  Position bit array
Private ma_intMoveBitNumber(1 To 8) As Integer

'  Current or move to position
Private m_strPosition As String

'  Used to indicate that the subsystem is bussey
'  and can not accept new thing to do
Private m_blnBussey As Boolean

'  used to determin if call back is used
Private m_blnWaiting As Boolean

'  refrence to assoicated form
Private m_objMyForm As Object


Public Sub Hide()

   m_objMyForm.Hide
   
End Sub 'Hide

Public Sub Show()

   m_objMyForm.Show
   
End Sub 'Show

Public Sub SetCallBack(objCallBack As Object)

   '  Save call back reference
   Set m_objMoveComplete = objCallBack
   
End Sub 'SetCallBack


'
Private Sub Class_Initialize()

   '  set my name
   m_strName = "clsMove"
   
   '  set status to false Untill initialized
   m_blnStatus = False
   
   '  Set bussy to true untill initialized
   m_blnBussey = False
   
   '  Set position to -1 bad position until homed
   m_strPosition = g_strINVALIDE_POSITION
   
   '  Now set the bit numbers needed for movement
   SetBitNumbers
   
   'set up the move form
   With frmMove
      .Hide
      .Initialize Me
   End With 'frmMove
   
End Sub 'Class_Initialize


Public Sub SetMyForm(objMyForm As Object)
'  Set the reference to the form associated to this class.

   Set m_objMyForm = objMyForm
   
   m_objMyForm.tmrMoveTimeOut.Enabled = False
   
End Sub 'SetMyForm

Public Property Get Name() As String

   Name = m_strName
   
End Property 'Get Name

Public Property Let Name(vNewValue As String)

   m_strName = vNewValue
   
End Property 'Let Name

Public Function Ready() As Boolean
Dim btest As Boolean

btest = m_objDigitalInput.Value(intbit:=g_ibitSAReady)
btest = (Not m_objDigitalInput.Value(intbit:=g_ibitSA_Alarm))

   Ready = _
      (m_objDigitalInput.Value(intbit:=g_ibitSAReady) _
         And _
      (Not m_objDigitalInput.Value(intbit:=g_ibitSA_Alarm)))
   
End Function 'Get Ready

Public Property Get Position() As String

   Position = m_strPosition
   
End Property 'Get Position

Public Property Let Position(vNewValue As String)

   m_strPosition = Format(vNewValue, "00")
   
End Property 'Let Position

Public Sub Home(blnWait As Boolean)

   #If ccShip_Ver Then
      On Error GoTo Home_Error
   #Else
      On Error GoTo 0
   #End If
      
   If (g_blnOpenTraceLogFile) Then TraceLog ("Class=Move: Homing Actuator")
      
      
   '  Display message initializing motion
   frmMessage.MessageDisplay strMessage:=LoadResString(resHOMING_MOTION)
   
   Position = 0 ' position zero is home position
   
   Move blnWait:=blnWait '   now move to the home position
   
   frmMessage.MessageRemove

   Exit Sub

Home_Error:

   ProccessError "Home", m_strName, Err.Number, Err.Description
   
End Sub 'Home

Public Function Initialize(objDigitalInput As Object, objDigitalOutput As Object) As Boolean

   Dim blnStatus As Boolean
   
   #If ccShip_Ver Then
      On Error GoTo Initialize_Error
   #Else
      On Error GoTo 0
   #End If
      
   blnStatus = True
   
   Set m_objDigitalInput = objDigitalInput
   Set m_objDigitalOutput = objDigitalOutput
   
   '  Set up call back for my bits
   With m_objDigitalInput
      If .InitStatus Then
         .SetCallBack Me, g_ibitSA_Alarm, g_ibitPositioningEnd
         blnStatus = blnStatus And True
      Else
         blnStatus = False
      End If
   End With 'm_objDigitalInput

   blnStatus = blnStatus And m_objDigitalOutput.InitStatus
   m_blnStatus = blnStatus
   Initialize = blnStatus
   
   m_blnBussey = False
   
   Exit Function

Initialize_Error:
   Initialize = False
   ProccessError "Initialize", m_strName, Err.Number, Err.Description

End Function 'Initialize

Public Sub Move(blnWait As Boolean)
   Dim ltimer As Single
   
   #If ccTrace Then
      Debug.Print m_strName & ".Move (IN) to: " & m_strPosition & " -- WT:" & blnWait & "-- WTing:" & m_blnWaiting & " -- BZY:" & m_blnBussey
   #End If
   #If ccShip_Ver Then
      On Error GoTo Move_Error
   #Else
      On Error GoTo 0
   #End If
   
   TraceLog ("Class=Move: Moving Actuator")
   
   If Ready And (Not m_blnBussey) Then
      m_blnBussey = True
      m_blnWaiting = blnWait
      SetMoveBits strPosition:=m_strPosition
      m_objDigitalOutput.StrobeBit intbit:=g_obitSAExternalStart, blnWait:=blnWait
      m_objMyForm.tmrMoveTimeOut.Enabled = True
      m_blnWaiting = True
      
      If blnWait Then
        ltimer = Timer
             
 '       Do While (Timer - ltimer) < 2
 '           If (Timer - ltimer) < 0 Then
                ' we have gone over midnight
 '               ltimer = 0
 '           End If
 '       Loop
        SleepSec 2
        Do While m_blnWaiting
           DoEvents
           m_objDigitalInput.ScanNow
           m_blnWaiting = Not (m_objDigitalInput.Value(g_ibitPositioningEnd))
        Loop
      End If
      
      m_objMyForm.tmrMoveTimeOut.Enabled = False
      m_blnBussey = False
   End If
   
   #If ccTrace Then
      Debug.Print m_strName & ".Move (EX) -- WTing:" & m_blnWaiting & " -- BZY:" & m_blnBussey
   #End If
   Exit Sub

Move_Error:

   ProccessError "Move", m_strName, Err.Number, Err.Description
   
End Sub 'Move

Private Sub SetMoveBits(strPosition As String)
   
   Dim strBits As String
   Dim a_blnValues(1 To 8) As Boolean
   Dim i As Integer
   
   #If ccShip_Ver Then
      On Error GoTo SetMoveBits_Error
   #Else
      On Error GoTo 0
   #End If
   
   ' Do the MSB's frist
   strBits = GetBNCBits(Mid(strPosition, 1, 1))
   For i = 1 To 4
      a_blnValues(i + 4) = (Mid(strBits, i, 1) = "1")
   Next i
   
   ' Now do the LSB's
   strBits = GetBNCBits(Mid(strPosition, 2, 1))
   For i = 1 To 4
      a_blnValues(i) = (Mid(strBits, i, 1) = "1")
   Next i
   
   '  Now set the bits
   m_objDigitalOutput.SetBits intBits:=ma_intMoveBitNumber, blnValues:=a_blnValues
   
   Exit Sub

SetMoveBits_Error:

   ProccessError "SetMoveBits", m_strName, Err.Number, Err.Description

End Sub 'SetMoveBits

Private Sub SetBitNumbers()

   ma_intMoveBitNumber(4) = g_obitSAPosition1
   ma_intMoveBitNumber(3) = g_obitSAPosition2
   ma_intMoveBitNumber(2) = g_obitSAPosition4
   ma_intMoveBitNumber(1) = g_obitSAPosition8
   ma_intMoveBitNumber(8) = g_obitSAPosition10
   ma_intMoveBitNumber(7) = g_obitSAPosition20
   ma_intMoveBitNumber(6) = g_obitSAPosition40
   ma_intMoveBitNumber(5) = g_obitSAPosition80

End Sub 'SetBitNumbers

Public Sub On_Event(intbit As Integer, Optional blnValue As Variant)

   #If ccTrace Then
      Debug.Print m_strName & ".On_Event (IN) -- BZY:" & m_blnBussey;
      If IsMissing(blnValue) Then
         Debug.Print " -- Bit = " & intbit; "-- Value = NA"
      Else
         Debug.Print " -- Bit = " & intbit & "-- Value =" & blnValue
      End If
   #End If
   #If ccShip_Ver Then
      On Error GoTo On_Event_Error
   #Else
      On Error GoTo 0
   #End If
   
   m_blnBussey = False
   
   Select Case intbit
      Case g_ibitSA_Alarm
            m_objMoveComplete.On_Event intbit
      Case g_ibitPositioningEnd
         If m_blnWaiting Then
            m_blnWaiting = False
         Else
            m_objMoveComplete.On_Event intbit
         End If
   End Select 'intBit
   
   #If ccTrace Then
      Debug.Print m_strName & ".On_Event (EX) -- BZY:" & m_blnBussey
   #End If
   Exit Sub

On_Event_Error:

   ProccessError "On_Event", m_strName, Err.Number, Err.Description
   
End Sub 'On_Event

Private Function GetBNCBits(strNumber As String) As String

   Select Case strNumber
      Case "0": GetBNCBits = "0000"
      Case "1": GetBNCBits = "0001"
      Case "2": GetBNCBits = "0010"
      Case "3": GetBNCBits = "0011"
      Case "4": GetBNCBits = "0100"
      Case "5": GetBNCBits = "0101"
      Case "6": GetBNCBits = "0110"
      Case "7": GetBNCBits = "0111"
      Case "8": GetBNCBits = "1000"
      Case "9": GetBNCBits = "1001"
   End Select 'strNumber

End Function 'GetBNCBits

Public Function Version() As String

   Version = "1.0"

End Function 'Version

Public Sub Reset(blnForce As Boolean)
Dim btest As Boolean
Dim m_objDigital As clsDigitalCommon
   Set m_objDigital = New clsDigitalCommon
   #If ccShip_Ver Then
      On Error GoTo Reset_Error
   #Else
      On Error GoTo 0
   #End If
   
   If (g_blnOpenTraceLogFile) Then TraceLog ("Class=Move: Reseting Actuator")
   
   If blnForce Or Not Ready Then
      '  Alarm is on so desplay message and cycle power relay
      frmMessage.MessageDisplay LoadResString(resRESETTING_MOTION)
      
      
      m_objDigitalOutput.SetBit g_obitSAReset, False
      
      modAPI.SleepMSec g_lngSA_RESET_WAIT
      
     '  Set the this bit's logical value
 '     m_objDigitalOutput.SetBit g_obitSAEmergencyStop, False
      m_objDigitalOutput.SetBit g_obitSAReset, True
      
      modAPI.SleepMSec g_lngSA_RESET_WAIT
          
      frmMessage.MessageRemove
      '  if alarm is still on then fatel error
    
      If m_objDigitalInput.Value(g_ibitSA_Alarm) And Not g_blnSimulator Then
'         Err.Raise g_errSA_NOT_RESET, , LoadResString(resERR_MOTION_NOT_RESET)
          MsgBox ("Motion Controller In Error: Program will Exit")
                    
          End
 
      End If
   End If
   
   Exit Sub

Reset_Error:

   ProccessError "Reset", m_strName, Err.Number, Err.Description

End Sub 'reset

Public Sub SetMoveTimeOut(lngValue As Long)
   
   frmMove.tmrMoveTimeOut.Interval = lngValue
   
End Sub 'SetMoveTimeOut

Public Sub MoveTimeOut()

   If (g_blnOpenTraceLogFile) Then TraceLog ("Class=Move: MoveTimeOut")


   m_objMyForm.tmrMoveTimeOut.Enabled = False
   m_objMoveComplete.On_Event g_evtARM_MOVE_TIMEOUT
   
End Sub 'MoveTimeOut



Public Sub EStop()

   If (g_blnOpenTraceLogFile) Then TraceLog ("Class=Move: EStop")


   m_objDigitalOutput.StrobeBit intbit:=g_obitSAEmergencyStop, blnWait:=True

End Sub 'EStop
