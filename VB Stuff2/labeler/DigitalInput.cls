VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsDigitalInput"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
'************************************************************************
'*           Computype, Inc.
'*       NextStep Automation Group
'*
'*     © Copywrite 1997 Computype, Inc.
'*
'*        2-Axis label Applicator
'*           Control Subsystem
'*
'*          Digital Input
'*
'*    Date of origin: June 19,1997
'*    Original author: Michael D. Reed
'*
'*    Class purpose:
'*       This class contains the interface to the outside world.
'*       The public functions are:
'*          Initialize: that provides the information needed by the
'*                      class to set its self up.
'*          Value: a boolean function that returns the value of an input.
'*          Show and Hide: to show the digital input monitoring form.
'*          MyForm: to get a reference to the digital input monitoring form.
'*          ScanNow: This is used by the timer on the monitoring form to
'*                   start the input scanning process.
'*          ScanRate: Sets scan rate for the scanner timer
'*          ScanInputs: Starts scanning of the digital inputs.
'*          CallBack: Sets a refrence to the function to be called
'*                    back when an event happens.
'*       This function expects the calling object to have a subroutine
'*       called On_Transition to be called upon the change of the input line.
'*       On_Transition has two arguments, an integer representing the bit number,
'*       and a boolean representing its value.
'*
'************************************************************************
Option Explicit
'******************************************************************

'  General name
Private m_strName As String
Private m_strVersion As String
Private m_blnInitStatus As Boolean

'  Array of bit values
Private Const m_intFIRST_BIT = 0
Private Const m_intLAST_BIT = 15
Private Type InBit_def
   blnValue As Boolean
   intSignalType As Integer
   objCallBack As Object
End Type 'InBit_def
Private ma_udtBits(m_intFIRST_BIT To m_intLAST_BIT) As InBit_def
Private m_queCallBack As New clsQueue

'  refrence to digital system interface
Private m_objDigital As Object

'  refrence to assoicated form
Private m_objMyForm As Object

'  Refrence to the call back
Private m_objCallBack As Object

Public Function InitStatus()

   InitStatus = m_blnInitStatus
   
End Function 'InitStatus

'
Private Sub Class_Initialize()

   #If ccShip_Ver Then
      On Error GoTo Class_Initialize_Error
   #Else
      On Error GoTo 0
   #End If
    
   m_strName = "clsDigitalinput"
   m_strVersion = "1.0.0"
   
   '  now set up the form
   With frmDigitalInput
      .Hide
      .Initialize Me
      m_blnInitStatus = .InitStatus
   End With 'frmDigitalOutput
   
   Exit Sub
   
Class_Initialize_Error:

   ProccessError "Class_Initialize", m_strName, Err.Number, Err.Description

End Sub 'Class_Initialize




Public Sub Initialize(objDigital As Object, a_strNames() As String, _
                      a_intSignalType() As Integer)
'   Set the reference to the common driver Interface class
'   Adds names to monitor form.
'   Saves the type of signals:
'     Event on true
'     Event on false
'     Event on transition
'     Value only

   Dim i As Integer
   
   #If ccShip_Ver Then
      On Error GoTo Error_Initialize
   #Else
      On Error GoTo 0
   #End If
   
   '  Save the refrence to the digital system interface
   Set m_objDigital = objDigital
   
   '  Save the input types
   For i = m_intFIRST_BIT To m_intLAST_BIT
      ma_udtBits(i).intSignalType = a_intSignalType(i)
   Next i
   
   '  Now setup montering form.
   With m_objMyForm
      For i = m_intFIRST_BIT To m_intLAST_BIT
         .sspInputControl(i).Caption = a_strNames(i)
      Next i
   End With 'm_objMyForm
   
   '  Scann the input once to get initial values.
   ScanNow
   
   m_blnInitStatus = m_blnInitStatus And True
   
   Exit Sub

Error_Initialize:

   ProccessError "Initialize", m_strName, Err.Number, Err.Description

End Sub ' Initialize

Public Sub SetMyForm(objMyForm As Object)
'  Set the reference to the form associated to this class.

   Set m_objMyForm = objMyForm
   
End Sub 'SetMyForm



Public Sub Hide()

   m_objMyForm.Hide
   
End Sub 'Hide

Public Sub Show()

   m_objMyForm.Show
   
End Sub 'Show
Public Sub ScanNow()
'   Gets data from port, sends off for processing if
'   data different form previous read.

   Static lngLastReading As Long
   Dim lngNewReading As Long
   Dim blnStatus As Boolean
   
   #If ccShip_Ver Then
      On Error GoTo Error_ScanNow
   #Else
      On Error GoTo 0
   #End If
 
   '  Read the input card
   If m_objDigital.ReadPort(r_lngValue:=lngNewReading) Then
      '  if there is no change do not process
      If lngNewReading <> lngLastReading Then
         ProcessInputs lngInputValue:=lngNewReading
         lngLastReading = lngNewReading
   
         '  Now process the call backs
'         CheckGuardDoor
         CallBack
      End If
   End If
   
   Exit Sub

Error_ScanNow:

   ProccessError "ScanNow", m_strName, Err.Number, Err.Description

End Sub 'ScanNow

Public Function Value(intbit As Integer) As Boolean

   Value = ma_udtBits(intbit).blnValue
   If g_blnSimulator Then
      Value = 1
   End If
End Function ' Value

Public Sub ScanRate(intValue As Integer)

   frmDigitalInput.tmrScan.Interval = 100 ' 5000intValue
   
End Sub 'ScanRate
 

Public Sub ScanInputs(blnEnable As Boolean)
   
   frmDigitalInput.tmrScan.Enabled = blnEnable

End Sub 'ScanInputs

Private Sub ProcessInputs(lngInputValue As Long)
'* Looks at each bit setting the Boolean array appropriately.
   Dim i As Integer

   #If ccShip_Ver Then
      On Error GoTo Error_ProcessInputs
   #Else
      On Error GoTo 0
   #End If
 
   If ((lngInputValue And 2 ^ g_ibitRemovedBoard) = 2 ^ g_ibitRemovedBoard) Then
     g_blnBoardRemove = True
   Else
     g_blnBoardRemove = False
   End If
 
   '  Process each bit
   For i = m_intFIRST_BIT To m_intLAST_BIT
      With ma_udtBits(i)
         If .blnValue <> ((lngInputValue And 2 ^ i) = (2 ^ i)) Then
            ProcessTransition intbit:=i, blnOldValue:=.blnValue
            .blnValue = ((lngInputValue And 2 ^ i) = (2 ^ i))
            m_objMyForm.UpDateDsp intIndex:=i, blnValue:=.blnValue
         End If
      End With 'ma_udtBits(i)
   Next i
   
   Exit Sub
   
Error_ProcessInputs:

   ProccessError "ProcessInputs", m_strName, Err.Number, Err.Description
   
End Sub 'ProcessInputs

Private Sub ProcessTransition(intbit As Integer, blnOldValue As Boolean)

   #If ccShip_Ver Then
      On Error GoTo Error_ProcessTransition
   #Else
      On Error GoTo 0
   #End If
 
   With ma_udtBits(intbit)
      Select Case .intSignalType
         Case g_intTRANSITION
            m_queCallBack.Push intbit
         Case g_intTRANS_TRUE
            If blnOldValue = False Then
               m_queCallBack.Push intbit
            End If
         Case g_intTRANS_FALSE
            If blnOldValue = True Then
               m_queCallBack.Push intbit
            End If
      End Select
   End With 'ma_udtBits
   
   Exit Sub
   
Error_ProcessTransition:

   ProccessError "ProcessTransition", m_strName, Err.Number, Err.Description
   
End Sub 'ProcessTransition

Private Sub CallBack()

   Dim intbit As Integer
   
   #If ccShip_Ver Then
      On Error GoTo Error_CallBack
   #Else
      On Error GoTo 0
   #End If
   
   '  If no reference to call back
   '  Clear que and leave
   If m_objCallBack Is Nothing Then
      m_queCallBack.Clear
      Exit Sub
   End If
   
   Do While m_queCallBack.QSize > 0
      CheckGuardDoor
      intbit = CInt(m_queCallBack.Pull)
      With ma_udtBits(intbit)
         .objCallBack.On_Event intbit:=intbit, blnValue:=.blnValue
      End With
   Loop
   
   Exit Sub
   
Error_CallBack:

   ProccessError "CallBack", m_strName, Err.Number, Err.Description
   
End Sub 'CallBack

Public Sub SetCallBack(objCallBack As Object, ParamArray a_Bits() As Variant)

   Dim i As Variant
   
   '  Save call back reference
   Set m_objCallBack = objCallBack
   
   For Each i In a_Bits
      Set ma_udtBits(CInt(i)).objCallBack = objCallBack
   Next
   
End Sub 'SetCallBack

Public Function Version() As String

   Version = m_strVersion
   
End Function 'Version

Public Function CheckGuardDoor() As Boolean
  Dim objOutputs As clsDigitalOutput
  Dim lngNewReading As Long
  Dim blnEStop As Boolean
    
  Exit Function
  Set objOutputs = modMain.m_objDIO_Output
  
     If (m_objDigital.ReadPort(r_lngValue:=lngNewReading)) Then
        If ((lngNewReading And 2 ^ 0) = 0) Then  '0= door closed
          
          objOutputs.SetBit intbit:=16, blnValue:=True
          MsgBox ("GuardDoorOpen")
          
'          modMain.m_objLabeler.RunStopJob
          
        End If
        
   
   End If
 Set objOutputs = Nothing
End Function

Public Sub GetHolePattern()
  
  Static lngLastReading As Long
  Dim lngNewReading As Long
  Dim blnStatus As Boolean
  Dim i As Integer
  g_intHolePattern = 0
   
   '  Read the input card
   If m_objDigital.ReadHolePatternPort(r_lngValue:=lngNewReading) Then
      '  if there is no change do not process
         For i = 8 To 12
          If ((lngNewReading And 2 ^ i) = (2 ^ i)) Then
            g_intHolePattern = g_intHolePattern + 2 ^ (i - 8)
          End If
         
         Next
      
     
   End If

End Sub
