VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsDigitalOutput"
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
'*          Digital Output
'*
'*    Date of origin: June 16,1997
'*    Original author: Michael D. Reed
'*
'*    Class purpose:
'*       This class contains the inter face to the outside world.
'*       The public functions are:
'*          Initialize: that provides the information needed by the
'*                      class to set its self up.
'*          Show and Hide: to show the digital input monitoring form.
'*          MyForm: to get a reference to the digital input monitoring form.
'*          SetBit (intBit as integer, blnValue as Boolean) ' Set the bit to
'*             the value given
'*          StrobeBit (intBit as integer, blnWaite as Boolean) ' Strobes
'*          the bit, and if wait is set true waits until strobe is complete.
'*       Bite type and strobe length are set up in the configuration DB.
'*
'*
'************************************************************************
Option Explicit
'******************************************************************

'  General name
Private m_strName As String
Private m_strVersion As String
Private m_blnInitStatus As Boolean


'  refrence to digital system interface
Private m_objDigital As Object

'  refrence to assoicated form
Private m_objMyForm As Object


Public Function Version() As String

   Version = m_strVersion
   
End Function 'Version

'
Public Sub SetBit(intbit As Integer, blnValue As Boolean)
'  This function sets the bit value to the value passed in.

   #If ccShip_Ver Then
      On Error GoTo Error_SetBit
   #Else
      On Error GoTo 0
   #End If
 
   If g_blnSimulator Then Exit Sub
   '  Set the this bit's logical value
   ma_blnBitValue(intbit) = blnValue
   
   '  Now write it to the prot
   m_objDigital.WritePort vntDataValue:=DataValue(ma_blnBitValue)
   
   Exit Sub

Error_SetBit:

   ProccessError "SetBit", m_strName, Err.Number, Err.Description

End Sub 'SetBit

Public Sub SetBits(intBits() As Integer, blnValues() As Boolean)
'  This function sets a renge of bit value to the values passed in.

   Dim i As Integer

   #If ccShip_Ver Then
      On Error GoTo Error_SetBit
   #Else
      On Error GoTo 0
   #End If
 
   For i = LBound(intBits) To UBound(intBits)
      '  Set the this bit's logical value
      ma_blnBitValue(intBits(i)) = blnValues(i)
   Next i

   '  Now write it to the prot
   m_objDigital.WritePort vntDataValue:=DataValue(a_blnBitValues:=ma_blnBitValue)
   
   Exit Sub

Error_SetBit:

   ProccessError "SetBit", m_strName, Err.Number, Err.Description

End Sub 'SetBits

Public Sub Reset()

   Dim i As Integer
   
   #If ccShip_Ver Then
      On Error GoTo Reset_Error
   #Else
      On Error GoTo 0
   #End If
   
   '  set all bits to false -- off
   For i = m_intFIRST_LSB To m_intLAST_MSB
         ma_blnBitValue(i) = False
   Next i
   
   '  Now write it to the prot
   m_objDigital.WritePort vntDataValue:=DataValue(ma_blnBitValue)
   
   Exit Sub

Reset_Error:

   ProccessError "Reset", m_strName, Err.Number, Err.Description

   
End Sub 'Reset

Public Sub StrobeBit(intbit As Integer, blnWait As Boolean)
'  This function strobes a bit for the tiem set in the strobe array.
'  The wait boolean determines if the procedure is to wait until
'  the strobe is complete before returning.
   
   Dim objDigInput As New clsDigitalInput

   Set objDigInput = modMain.m_objDIO_Input
   Dim blnStartValue As Boolean
   Dim btest As Boolean
   
   #If ccShip_Ver Then
      On Error GoTo Error_StrobeBit
   #Else
      On Error GoTo 0
   #End If
  
   '  set the bit to the correct value for the start of strobe
   Select Case ma_intSignalType(intbit)
      Case g_intSTROBE_ON
         ma_blnBitValue(intbit) = True
      Case g_intSTROBE_OFF
         ma_blnBitValue(intbit) = False
      Case Else ' not to be strobed so exit
         Exit Sub
   End Select 'ma_intSignalType(intBit)
   
   '  Now save the start value
   blnStartValue = ma_blnBitValue(intbit)
   
   '  Now write it to the prot
   If m_objDigital.WritePort(vntDataValue:=DataValue(ma_blnBitValue)) Then
      
      '  Fire the timer
      m_objMyForm.StartTimer intbit:=intbit, lngStrobe:=ma_lngStrobe(intbit)
      
      ' Now weight until strobe complet if requested
      If blnWait Then
         Do While blnStartValue <> ma_blnBitValue(intbit)
            objDigInput.CheckGuardDoor
         Loop
      End If
   End If
   objDigInput.CheckGuardDoor
   Set objDigInput = Nothing
   
   Exit Sub

Error_StrobeBit:

   ProccessError "StrobeBit", m_strName, Err.Number, Err.Description

End Sub

Private Sub Class_Initialize()

   #If ccShip_Ver Then
      On Error GoTo Class_Initialize_Error
   #Else
      On Error GoTo 0
   #End If
    
   m_strName = "clsDigitalOutput"
   m_strVersion = "1.0.0"
   
   '  now set up the form
   With frmDigitalOutput
      .Hide
      .Initialize Me
      m_blnInitStatus = .InitStatus
   End With 'frmDigitalOutput
   
   Exit Sub
   
Class_Initialize_Error:

   ProccessError "Class_Initialize", m_strName, Err.Number, Err.Description

End Sub 'Class_Initialize




Public Sub Initialize(objDigital As Object, a_strNames() As String, _
                      a_intSignalType() As Integer, a_lngStrobe() As Long, _
                      a_blnInitialValue() As Boolean)
                      
'   Set the reference to the common driver Interface class
'   Adds names to monitor form.
   
   Dim i As Integer
   
   #If ccShip_Ver Then
      On Error GoTo Error_Initialize
   #Else
      On Error GoTo 0
   #End If
   
   '  Save the refrence to the digital system interface
   Set m_objDigital = objDigital
   With m_objMyForm
      For i = m_intFIRST_LSB To m_intLAST_MSB
         .sspOutputControl(i).Caption = a_strNames(i)
         ma_blnBitValue(i) = a_blnInitialValue(i)
         ma_intSignalType(i) = a_intSignalType(i)
         ma_lngStrobe(i) = a_lngStrobe(i)
      Next i
   End With 'm_objMyForm
   
   '  Now write the initial settings to the prot
   m_objDigital.WritePort DataValue(ma_blnBitValue)
   
   m_blnInitStatus = m_blnInitStatus And True
   
   Exit Sub

Error_Initialize:

   ProccessError "Initialize", m_strName, Err.Number, Err.Description

End Sub ' Initialize

Public Sub SetMyForm(objMyForm As Object)
'  Set the reference to the form associated to this class.

   Set m_objMyForm = objMyForm
   
End Sub 'SetMyForm

Public Sub StrobeTimeOut(intIndex As Integer)
'This function toggles the bit when the strobe time is up.

   #If ccShip_Ver Then
      On Error GoTo Error_StrobeTimeOut
   #Else
      On Error GoTo 0
   #End If
   
   '  Set the this bit's logical value
   ma_blnBitValue(intIndex) = Not ma_blnBitValue(intIndex)
   
   '  Now write it to the prot
   m_objDigital.WritePort vntDataValue:=DataValue(ma_blnBitValue)
   
   Exit Sub

Error_StrobeTimeOut:

   ProccessError "StrobeTimeOut", m_strName, Err.Number, Err.Description

End Sub 'StrobeTimeOut
Private Function DataValue(a_blnBitValues() As Boolean) As Variant
'  This function processes the array of bit values, builds a
'  long number containing all the values, and passes back.
'  This function also updates the indicators on the
'  associated digital output.

   Dim lngBuffer As Long
   Dim i As Integer
   Dim a_vntDataOut(1) As Variant
   g_lDataValue = 0
   #If ccShip_Ver Then
      On Error GoTo Error_DataValue
   #Else
      On Error GoTo 0
   #End If
   
   lngBuffer = CLng(0)
   For i = m_intFIRST_LSB To m_intLAST_MSB
    
    '  Build the word to send out the prot
      If a_blnBitValues(i) Then
         g_lDataValue = g_lDataValue + (2 ^ (i))
      End If
   
   
   Next i
   
   
   With m_objMyForm
      '  Process the first word
      For i = m_intFIRST_LSB To m_intLAST_LSB
         '  Build the word to send out the prot
         If a_blnBitValues(i) Then
            lngBuffer = lngBuffer + (2 ^ i)
         End If
         '  Set the switchs on monitor form
         .ssrIOSwitch(i).Value = a_blnBitValues(i)
      Next i
      '  Save it to the array to send back
      a_vntDataOut(0) = lngBuffer
      ' Now zero out the buffer and process the second word
      lngBuffer = CLng(0)
      For i = m_intFIRST_MSB To m_intLAST_MSB
         '  Build the word to send out the prot
         If a_blnBitValues(i) Then
            '   Need to use 10 to 15 for bit
            lngBuffer = lngBuffer + (2 ^ (i - 16))
         End If
         '  Set the switchs on monitor form
         .ssrIOSwitch(i).Value = a_blnBitValues(i)
      Next i
      '  Save it to the array to send back
      a_vntDataOut(1) = lngBuffer
   End With 'm_objMyForm
   
   DataValue = a_vntDataOut

   Exit Function
   
Error_DataValue:

   ProccessError "DataValue", m_strName, Err.Number, Err.Description
   
End Function 'DataValue


Public Sub Hide()

   m_objMyForm.Hide
   
End Sub 'Hide

Public Sub Show()

   m_objMyForm.Show
   
End Sub 'Show


Public Function InitStatus()

   InitStatus = m_blnInitStatus
   
End Function 'InitStatus
