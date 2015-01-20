VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsDigitalIO"
Attribute VB_Creatable = False
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
'*          CompuBoard Digital I/O Board CIO-DIO24 Control class
'*
'*    Date of origin: 1/30/96
'*    Original author: Michael D. Reed
'*
'* Class purpose:
'*    This class provides the interface between the
'*    CompuBoard Universal Library and VB programs.
'*    It interfaces with the CompuBoards Basic module supplied
'*    with the Universal Library and a VB Form that provides
'*    a visual display and a timer for scanning the input ports.
'*
'************************************************************************
Option Explicit
'******************************************************************

'  Scanning intervial
Private m_intScanIntervial As Integer

'  Error Codes
Private Const m_intNOT_INPUT = 0 + g_intDIG_IO_OFFSET
Private Const m_intNOT_OUTPUT = 1 + g_intDIG_IO_OFFSET

'  No error from CompuBoard
Private Const m_intCB_NOERRORS = 0

'  Class instance name and status
Private m_strName As String
Private m_blnInitialized As Boolean

'  Information on the digitial board
Private m_strDLLRevisionNumber As String
Private m_strVXDRevisionNumber As String

'  Port Definition and data space
Private Type Prot_Def
   a_intBits() As Integer
   a_blnValue() As Boolean
   strPortNum  As String
   strDirection  As String
End Type 'Prot_Def
Private m_udtPorts() As Prot_Def
Private m_intBoardNumber As Integer

'  Setup a refrence to the call back module
Private m_objCallBack As Object

Private Sub Class_Initialize()


   Dim intCBStat As Integer
   Dim blnStatus As Boolean
   Dim idx As Variant
   
   Dim sglDLLRevNum As Single
   Dim sglVDXRevNum As Single
   
   Dim a_strDirection() As String
   Dim a_strLabel() As String
   Dim a_strName() As String
   Dim intLastBit As Integer
                                                
   blnStatus = False
   
   m_blnInitialized = False
   m_strDLLRevisionNumber = "None"
   m_strVXDRevisionNumber = "None"
   
   '  Give it the name of the class until it is renamed
   m_strName = "clsDigitalIO"
   
   '  Declare revision level used
   intCBStat = modCBW32.DeclareCurrentRevesion
   If Not intCBStat = m_intCB_NOERRORS Then Exit Sub
   
   '  Now get and save the revision numbers
'   intCBStat = modCBW32.GetCurrentRevision(sglDLLRevNum, sglVDXRevNum)
   If intCBStat = m_intCB_NOERRORS Then
      m_strDLLRevisionNumber = CStr(sglDLLRevNum)
      m_strVXDRevisionNumber = CStr(sglVDXRevNum)
   Else
      Exit Sub
   End If
   
   '  Now set up error handle
   intCBStat = modCBW32.InitErrHandle
   If Not intCBStat = m_intCB_NOERRORS Then Exit Sub
   
   blnStatus = InitIOPorts(a_strDirection(), a_strLabel(), a_strName(), intLastBit)
   If Not blnStatus Then Exit Sub
   
   frmDigitalIO.Hide
   blnStatus = frmDigitalIO.Initialize(objDigCtrl:=Me)
   blnStatus = frmDigitalIO.InitIODisplay(a_strDirection(), a_strLabel(), a_strName(), intLastBit)
   
   '  Initialize the ports
   For idx = 0 To UBound(m_udtPorts)
      With m_udtPorts(idx)
         intCBStat = ConfigurPort(m_intBoardNumber, .strPortNum, .strDirection)
         blnStatus = (intCBStat = m_intCB_NOERRORS)
         If Not blnStatus Then Exit Sub
      End With 'm_udtPorts(idx)
   Next idx
   
   '  Set the scanning timer intervial
   m_intScanIntervial = 100
   
   '  made it to here so all is ok
   m_blnInitialized = True
   
End Sub 'Class_Initialize

Private Function InitIOPorts(a_strDirection() As String, _
                             a_strLabel() As String, _
                             a_strName() As String, _
                             intLastBit As Integer) As Boolean

   '  Labeler database
   Dim idxBit As Integer
   Dim idxPort As Integer
   Dim strDir As String
   Dim strTemp As String
   
   Dim dbLabelerDataBase As Database
   Dim snpLabelerIOPorts As Recordset
   
   #If ccShip_Ver Then
      On Error GoTo InitIOPorts_Error
   #Else
      On Error GoTo 0
   #End If
   
   '  Set up Labeler data
   '  Open the data base and get the command lines
   Set dbLabelerDataBase = Workspaces(0).OpenDatabase(modMain.GetConfigurationDataBaseName)
   Set snpLabelerIOPorts = dbLabelerDataBase.OpenRecordset(modMain.GetLabelerIOPorts, dbOpenSnapshot)
      
   '  Set up the arrays for the dispaly
   ReDim a_strDirection(1)
   ReDim a_strLabel(1)
   ReDim a_strName(1)
   
   '  Do the first one
   ReDim m_udtPorts(1)
   idxPort = 0
   '  First get the board number this should stay the same for all ports and bites
   m_intBoardNumber = snpLabelerIOPorts![BoardNumber]
   
   With m_udtPorts(idxPort)
      .strPortNum = snpLabelerIOPorts![PortNumber]
      .strDirection = snpLabelerIOPorts![Direction]
      
      '  Save bit information
      idxBit = 0
      ReDim .a_intBits(0)
      .a_intBits(idxBit) = snpLabelerIOPorts![BitNumber]
      ReDim .a_blnValue(0)
     
      '  save bit data to pass back to the form
      intLastBit = 0
      ReDim a_strDirection(1)
      ReDim a_strLabel(1)
      ReDim a_strName(1)
      a_strDirection(intLastBit) = .strDirection
      a_strLabel(intLastBit) = snpLabelerIOPorts![BitNumber]
      a_strName(intLastBit) = "(" & snpLabelerIOPorts![BoardSignalName] & ") " & snpLabelerIOPorts![Name]
   End With
   
   snpLabelerIOPorts.MoveNext
                     
   '  Now do the rest
   Do Until snpLabelerIOPorts.EOF
   
      '  Check if port number changes ...
      If m_udtPorts(idxPort).strPortNum = snpLabelerIOPorts![PortNumber] Then
         '  It did not change so add bit number to current port
         With m_udtPorts(idxPort)
            ReDim Preserve .a_intBits(UBound(.a_intBits) + 1)
            ReDim Preserve .a_blnValue(UBound(.a_blnValue) + 1)
            idxBit = idxBit + 1
            .a_intBits(idxBit) = snpLabelerIOPorts![BitNumber]
            
            '  save bit data to pass back to the form
            intLastBit = intLastBit + 1
            ReDim Preserve a_strDirection(intLastBit)
            ReDim Preserve a_strLabel(intLastBit)
            ReDim Preserve a_strName(intLastBit)
            a_strDirection(intLastBit) = .strDirection
            a_strLabel(intLastBit) = snpLabelerIOPorts![BitNumber]
            a_strName(intLastBit) = "(" & snpLabelerIOPorts![BoardSignalName] & ") " & snpLabelerIOPorts![Name]
         End With 'm_udtPorts(idxPort)
      Else  'It did change so add new port
         '  and gen a new prot definition
         idxPort = idxPort + 1
         ReDim Preserve m_udtPorts(idxPort)
         
         With m_udtPorts(idxPort)
            .strPortNum = snpLabelerIOPorts![PortNumber]
            .strDirection = snpLabelerIOPorts![Direction]
      
            ReDim .a_intBits(0)
            idxBit = 0
            .a_intBits(idxBit) = snpLabelerIOPorts![BitNumber]
            ReDim .a_blnValue(0)

            '  save bit data to pass back to the form
            intLastBit = intLastBit + 1
            ReDim Preserve a_strDirection(intLastBit)
            ReDim Preserve a_strLabel(intLastBit)
            ReDim Preserve a_strName(intLastBit)
            a_strDirection(intLastBit) = .strDirection
            a_strLabel(intLastBit) = snpLabelerIOPorts![BitNumber]
            a_strName(intLastBit) = "(" & snpLabelerIOPorts![BoardSignalName] & ") " & snpLabelerIOPorts![Name]
         End With
      End If
      
      snpLabelerIOPorts.MoveNext
   
   Loop 'Until snpLabelerIOPorts.EOF
   
   dbLabelerDataBase.Close
   
   InitIOPorts = True
   
   Exit Function

InitIOPorts_Error:

   ProccessError "InitIOPorts", m_strName, Err.Number, Err.Description
   InitIOPorts = False
   
End Function 'InitIOPorts


Public Property Get Bit(intBit As Integer) As Boolean

   Dim intResp As Integer
   Dim intValue As Integer
   Dim blnTimerStatus As Boolean
    
   #If ccShip_Ver Then
      On Error GoTo Get_Bit_Error
   #Else
      On Error GoTo 0
   #End If
 
   blnTimerStatus = frmDigitalIO.TimerStatus()
   frmDigitalIO.TimerEnable False
   
   If IsInput(intBit) Then
      intResp = modCBW32.BitIn(m_intBoardNumber, intBit, intValue)
   Else
      Err.Raise m_intNOT_INPUT, , "Bit " & intBit & " is not an input."
   End If
      
   If (intResp = m_intCB_NOERRORS) Then
      frmDigitalIO.ShowBit Index:=intBit, blnValue:=CBool(intValue)
      SaveBitValue intBit:=intBit, blnValue:=CBool(intValue)
      Bit = CBool(intValue)
   Else
         DigIOError "Got Bit", m_strName, intResp, modCBW32.GetErrorMsg(intResp)
   End If
   
   frmDigitalIO.TimerEnable blnTimerStatus
   
   '  done so exit sub befor the error handler
   Exit Property

Get_Bit_Error:

   ProccessError "Get Bit", m_strName, Err.Number, Err.Description
   
End Property 'Get Bit

Public Property Let Bit(intBit As Integer, blnValue As Boolean)

   Dim intResp As Integer
   
   #If ccShip_Ver Then
      On Error GoTo Let_Bit_Error
   #Else
      On Error GoTo 0
   #End If
 
   frmDigitalIO.TimerEnable False
   If IsOutput(intBit) Then
      intResp = modCBW32.BitOut(m_intBoardNumber, intBit, Abs(CInt(blnValue)))
   Else
      Err.Raise m_intNOT_OUTPUT, , "Bit " & intBit & " is not an output."
   End If
   
   If (intResp = m_intCB_NOERRORS) Then
      SaveBitValue intBit:=intBit, blnValue:=blnValue
      frmDigitalIO.ShowBit Index:=intBit, blnValue:=blnValue
   Else
      DigIOError "Let Bit", m_strName, intResp, modCBW32.GetErrorMsg(intResp)
   End If
   
   frmDigitalIO.TimerEnable True
   '  done so exit sub before the error handler
   Exit Property

Let_Bit_Error:

   ProccessError "Let Bit", m_strName, Err.Number, Err.Description
   
End Property 'Let Bit






Public Sub ForceBit(intBitNumber As Integer, blnBitValue As Boolean)
'  This function is used by the display form for
'  forcing a bit by the operator.  Changing or reading a bit
'  under program control should use the bit property.

   #If ccShip_Ver Then
      On Error GoTo ForceBit_Error
   #Else
      On Error GoTo 0
   #End If
 
   Dim intRet As Integer
   
   If IsOutput(intBitNumber) Then
      intRet = modCBW32.BitOut(m_intBoardNumber, intBitNumber, Abs(CInt(blnBitValue)))
   Else
      Err.Raise m_intNOT_OUTPUT, , "Bit " & intBitNumber & " is not output."
   End If
   
   '  done so exit sub before the error handler
   Exit Sub

ForceBit_Error:

   ProccessError "<SubName>", m_strName, Err.Number, Err.Description
   
End Sub 'ForceBit

Public Function InitStatus()

   InitStatus = m_blnInitialized
   
End Function 'InitStatus

Public Sub Scan(ByRef vntBuffer() As Variant)
'  This function is used by the display form for
'  scanning the input bits.  Changing or reading a bit
'  under program control should use the bit property.

   Dim idx As Integer
   Dim intWidth As Integer
   Dim intBits As Integer
   Dim intNBits As Integer
   Dim i As Integer
   Dim blnTemp  As Boolean
   
   Dim vntTemp(g_idxBIT_NUM To g_idxBIT_VAL) As Variant
   
    #If ccShip_Ver Then
      On Error GoTo Scan_Error
   #Else
      On Error GoTo 0
   #End If
  
   intNBits = 0
   
   For idx = 1 To UBound(m_udtPorts)
      With m_udtPorts(idx)
         If .strDirection = g_strINPUT Then
            '  get the bits from the input port
            intBits = modCBW32.InputPort(m_intBoardNumber, .strPortNum)
            
            '  Now make room for it in the buffer
            intWidth = UBound(.a_intBits)
            ReDim Preserve vntBuffer(intNBits + intWidth)

            '  adjust the width to count from zero "0"
            For i = 0 To intWidth
               blnTemp = (intBits And (2 ^ i)) <> 0
               '  did the bit value change
               If blnTemp <> .a_blnValue(i) Then
                  .a_blnValue(i) = blnTemp
                  '  Call the call back function and tell them what happened
                  If Not (m_objCallBack Is Nothing) Then
                     m_objCallBack.OnBit_Trans intBit:=.a_intBits(i), blnValue:=.a_blnValue(i)
                  End If
'                  modUtilities.Log "DigIO Bit " & .objIOContainer.Caption, .objIOContainer.Tag & "; Value=" & CStr(Value)
               End If
               '  save the bit number and value
               intNBits = intNBits + 1
               ReDim Preserve vntBuffer(intNBits)
               '  Set bit number
               vntTemp(g_idxBIT_NUM) = .a_intBits(i)
               '  Set bit value
               vntTemp(g_idxBIT_VAL) = blnTemp
               '  now add to variant array
               vntBuffer(intNBits - 1) = vntTemp()
            Next i
            
         End If
      End With 'm_udtPorts(idx)
   Next idx

   Exit Sub

Scan_Error:

   ProccessError "Scan", m_strName, Err.Number, Err.Description
        
End Sub 'Scan


Public Function Version() As String

   Version = "DLL=" & m_strDLLRevisionNumber & " VXD=" & m_strVXDRevisionNumber

End Function 'Version




Public Function Initialize(strName As String)

   m_strName = "strName"
   
   '  now check if any bits are set.
   frmDigitalIO.ScanPorts
   
End Function 'Initialize

Public Function IsOutput(intBitNumber As Integer)

   Dim intFloor As Integer
   Dim intCeiling As Integer
   
   #If ccShip_Ver Then
      On Error GoTo IsOutput_Error
   #Else
      On Error GoTo 0
   #End If
 
   Dim i As Integer
   
   '  look through the port array for bit location
   For i = LBound(m_udtPorts) To UBound(m_udtPorts)
      With m_udtPorts(i)
         intFloor = .a_intBits(LBound(.a_intBits))
         intCeiling = .a_intBits(UBound(.a_intBits))
         '   if the bit is in this port ...
         If (intFloor <= intBitNumber) And (intBitNumber <= intCeiling) Then
            '  See if its direction is an output
            IsOutput = (.strDirection = g_strOUTPUT)
            Exit Function
         End If
      End With
   Next i
   
   '  Got here so must not be an output or
   '  in collection so send back a faluse
   IsOutput = False
   
   Exit Function

IsOutput_Error:

   ProccessError "IsOutput", m_strName, Err.Number, Err.Description
   IsOutput = False
   
End Function 'IsOutput

Public Function IsInput(intBitNumber As Integer)

   Dim intFloor As Integer
   Dim intCeiling As Integer
   
   #If ccShip_Ver Then
      On Error GoTo IsInput_Error
   #Else
      On Error GoTo 0
   #End If
 
    Dim i As Integer
  
  '  look through the port array for bit location
   For i = LBound(m_udtPorts) To UBound(m_udtPorts)
      With m_udtPorts(i)
         intFloor = .a_intBits(LBound(.a_intBits))
         intCeiling = .a_intBits(UBound(.a_intBits))
         '   if the bit is in this port ...
         If (intFloor <= intBitNumber) And (intBitNumber <= intCeiling) Then
            '  See if its direction is an input
            IsInput = (.strDirection = g_strINPUT)
            Exit Function
         End If
      End With
   Next i
   
   '  Got here so must not be an input or
   '  in collection so send back a faluse
   IsInput = False
   
   Exit Function

IsInput_Error:

   ProccessError "IsInput", m_strName, Err.Number, Err.Description
   IsInput = False
   
End Function 'IsInput



Public Function SetCallBack(objCallBack As Object)

  Set m_objCallBack = objCallBack
  
End Function 'SetCallBack

Public Sub ScanPorts(blnScan As Boolean)

   frmDigitalIO.TimerEnable blnScan, m_intScanIntervial

End Sub 'ScanPorts

Private Sub SaveBitValue(intBit As Integer, blnValue As Boolean)

   Dim iP As Integer
   Dim iB As Integer
   
   For iP = LBound(m_udtPorts) To UBound(m_udtPorts)
      With m_udtPorts(iP)
         For iB = LBound(.a_intBits) To UBound(.a_intBits)
            If intBit = .a_intBits(iB) Then
               .a_blnValue(iB) = blnValue
               Exit Sub
            End If
         Next iB
      End With 'm_udtPorts(iP)
   Next iP
   
End Sub 'SaveBitValue
