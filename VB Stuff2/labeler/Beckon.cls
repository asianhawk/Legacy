VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsBeckon"
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
'*          Beckon control subsystem.
'*
'*
'*    Date of origin: 9/8/97
'*    Original author: Michael D. Reed
'*
'* Class purpose:
'*    This provides the necessary procedures to control the beckon.
'*
'************************************************************************
Option Explicit

'  Outputs
Private m_objOutputs As clsDigitalOutput

'  my name and status
Private m_strName As String
Private m_blnInitStatus As Boolean


Public Function Initialize(objOutput As Object) As Boolean

   #If ccShip_Ver Then
      On Error GoTo Initialize_Error
   #Else
      On Error GoTo 0
   #End If
    
   '  set job state
   m_blnInitStatus = True
   
   ' Set up refrences to the subsystems
   Set m_objOutputs = objOutput
   
   '  Digital output objects
   If m_objOutputs Is Nothing Then
      Err.Raise g_intINIT_OUTPUT_OBJ, "clsBeckon.Initialize", LoadResString(resERR_INIT_OUTPUT_OBJ)
      m_blnInitStatus = False
   End If
   
   Initialize = m_blnInitStatus

   Exit Function

Initialize_Error:

   Initialize = False
   ProccessError "Initialize", m_strName, Err.Number, Err.Description

End Function 'Initialize


Public Sub TurnOnBeckon(intLight As Integer)
' This procudure turns on a light an all others off

   #If ccShip_Ver Then
      On Error GoTo TurnOnBeckon_Error
   #Else
      On Error GoTo 0
   #End If
   
   Select Case intLight
      Case g_intRED
         Red blnOn:=True
         Green blnOn:=False
      Case g_intGREEN
         Red blnOn:=False
         Green blnOn:=True
      Case Else
         Red blnOn:=False
         Green blnOn:=False
   End Select 'intLight
   
   Exit Sub

TurnOnBeckon_Error:

   ProccessError "TurnOnBeckon", m_strName, Err.Number, Err.Description

End Sub 'TurnOnBeckon




Public Sub Yellow(blnOn As Boolean)

   #If ccShip_Ver Then
      On Error GoTo Yellow_Error
   #Else
      On Error GoTo 0
   #End If
   
   With m_objOutputs
      If blnOn Then
         .SetBit intBit:=g_obitYellowBeckon, blnValue:=True
      Else
         .SetBit intBit:=g_obitYellowBeckon, blnValue:=False
      End If
   End With 'm_objOutputs
   
   Exit Sub

Yellow_Error:

   ProccessError "Yellow", m_strName, Err.Number, Err.Description
   
End Sub 'Yellow

Public Sub Red(blnOn As Boolean)

   #If ccShip_Ver Then
      On Error GoTo Red_Error
   #Else
      On Error GoTo 0
   #End If
   
   With m_objOutputs
      If blnOn Then
         .SetBit intBit:=g_obitRedBeckon, blnValue:=True
      Else
         .SetBit intBit:=g_obitRedBeckon, blnValue:=False
      End If
   End With 'm_objOutputs
   
   Exit Sub

Red_Error:

   ProccessError "Red", m_strName, Err.Number, Err.Description
   
End Sub 'Red


Public Sub Buzzer(blnOn As Boolean)

   #If ccShip_Ver Then
      On Error GoTo Buzzer_Error
   #Else
      On Error GoTo 0
   #End If
   
   With m_objOutputs
      If blnOn Then
         .SetBit intBit:=g_obitBuzzer, blnValue:=True
      Else
         .SetBit intBit:=g_obitBuzzer, blnValue:=False
      End If
   End With 'm_objOutputs
   
   Exit Sub

Buzzer_Error:

   ProccessError "Buzzer", m_strName, Err.Number, Err.Description
   
End Sub 'Buzzer

Public Sub Green(blnOn As Boolean)

   #If ccShip_Ver Then
      On Error GoTo Green_Error
   #Else
      On Error GoTo 0
   #End If
   
   With m_objOutputs
      If blnOn Then
         .SetBit intBit:=g_obitGreenBeckon, blnValue:=True
      Else
         .SetBit intBit:=g_obitGreenBeckon, blnValue:=False
      End If
   End With 'm_objOutputs
   
   Exit Sub

Green_Error:

   ProccessError "Green", m_strName, Err.Number, Err.Description
   
End Sub 'Green


Public Sub BuzzerAcknowledge(strMessage As String)
'  This procedure turns the buzzer on and then off
'  when the operator acknowledges the dialogue box.

   #If ccShip_Ver Then
      On Error GoTo BuzzerAcknowledge_Error
   #Else
      On Error GoTo 0
   #End If
   
   Buzzer blnOn:=True
   MsgBox "Label Pickup Error. Press OK to Continue", vbOKOnly + vbCritical, "Label Pickup Error! Press OK to Continue."
   Buzzer blnOn:=False
   
   Exit Sub

BuzzerAcknowledge_Error:

   ProccessError "BuzzerAcknowledge", m_strName, Err.Number, Err.Description
   
End Sub 'BuzzerAcknowledge

Private Sub Class_Initialize()
   
   #If ccShip_Ver Then
      On Error GoTo Class_Initialize_Error
   #Else
      On Error GoTo 0
   #End If
   
   m_blnInitStatus = True
   
   ' give me a name
   m_strName = "clsBeckon"
   
   Exit Sub
   
Class_Initialize_Error:

   ProccessError "Class_Initialize", m_strName, Err.Number, Err.Description
   m_blnInitStatus = False
   

End Sub 'Class_Initialize



