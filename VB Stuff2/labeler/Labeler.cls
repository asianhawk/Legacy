VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsLabeler"
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
'*             Main Class
'*
'*
'*    Customer: Motorla FL
'*
'*
'*    Date of origin: 12/29/96
'*    Original author: Michael D. Reed
'*
'* Class purpose:
'*    This class is the main class which controls the labeler
'*    customized for Ford Markham   .
'*
'************************************************************************
'******************************************************************
Option Explicit
'******************************************************************

'  used to determane if seq num to be incermented

Private m_blnPreCheckSerialNumbers As Boolean
Private m_blnNextLabel As Boolean
Dim sBadNumbers(500, 2)  As String
Dim m_nNoOfBadSerialNumbers As Long
Dim m_blnBAD_SerialDB_Found As Boolean


'  RTF messages
Private Const m_strNO_LABEL = "NoLabel.rtf"
Private Const m_strBAD_SCAN = "NoScan.rtf"
Private Const m_strNO_PRITNER = "NoPrinter.rtf"
Private Const m_strNO_AIR = "NoAir.rtf"
Private Const m_strGUARDS_OPEN = "GuardsOpen.rtf"
Private Const m_strMOTION_ERR = "MotionErr.rtf"
Private Const m_strNO_MOVE = "NoMove.rtf"
Private Const m_strNO_RECTRACT = "NoRectract.rtf"

'  FOR  THE BECKON
Private Const m_intNO_LIGHT = -1

'  MAX BASE 36 NUMBER
'  1679615 = ZZZZ
Private Const m_strMAX_BASE36_NUMBER = "ZZZZ"
Private Const m_fmtSEQ_NUMBER = "0000"

'  my name and status
Private m_strName As String
Private m_blnInitStatus As Boolean

'******************************************************************
'  Refrences
'******************************************************************
'  the main form desplayed to the user
Private m_objMainForm As Object

'  Outputs
Private m_objOutputs As clsDigitalOutput

'  Inputs
Private m_objInputs As clsDigitalInput

'  Printer
Private m_objPrinter As clsLabelPrint

'  Scanner
Private m_objscanner As SICKScanner
'added 12/14/00
Private m_objBottomScanner As SICKScanner
Private m_strBottomScannedLabel As String


'  Motion
Private m_objMove As clsMove

'  Beckon
Private m_objBeckon As clsBeckon

'******************************************************************
'  Configuration
'******************************************************************
Private m_strConfigName As String

'  Timing
Private m_lngAcuatorExtendTime As Long 'Time needed to extend actuator
Private m_lngApplyDwellTime As Long 'Time needed to push label on

'  Instructions buttons
Private Const m_strRESCAN = "Re-Scan"
Private Const m_strRELABEL = "Re-Label"
Private Const m_strCONTINUE = "Continue"
Private Const m_strCANCEL = "Cancel"

'  Auto run flage
Private m_blnAutoRun As Boolean

'******************************************************************
'  Job data
'******************************************************************
'  Define job data
Private Type Job_Info
   strJobID As String
   strName As String
   strLocationCode As String
   strPartNumber As String
   strFormatName As String
   strTemplatePath As String
End Type  'Job_Info
Private m_udtCurrentJob As Job_Info

'  Last label printed data
Private m_lngPanelQuintityCount As Long
Private m_lngLabelApplyedCount As Long

'  Label items
Private m_lngSequenceNumber As Long
Private m_strLabelDataPrinted As String

'  Manual print flage
Private m_blnManualFeed As Boolean

'  Kit file for next job
Private m_strKitPathFileName As String
Private m_strLogPathFileName As String
Private m_chrKeyFileDelim As String
Private m_chrLogFileDelim As String

'******************************************************************
' State defintitions
'******************************************************************
'  Local events
Private Const m_evtNEXT_LABEL = 200
Private Const m_evtLABEL_APPLIED = 201
Private Const m_evtLABELING_COMPLETE = 202
Private Const m_evtSCAN = 203
Private Const m_evtAPPLY_LABEL = 204

'  Labeler states
Public m_staLabelerState As String
Private m_staReturnState  As String
Private Const m_staSUSPENDED = "Supend"
Private Const m_staIDLE = "Idle"
Private Const m_staRUNNING = "Run"
Private Const m_staNO_JOB = "NoJob"
Private Const m_staLABELING = "Label"
Private Const m_staSCANNING = "Scan"
Private Const m_staMOVING = "Move"
Private Const m_staAPPLYING = "Apply"
Private Const m_staRELABEL = "ReLabel"
Private Const m_staINIT = "Init"
Private Const m_staNO_PRINTER = "No Printer"

'  Spended states
Private m_staSpendState As Integer
Private Const m_staNOT_SPENDED = 0
Private Const m_staNO_VACUUM = 1
Private Const m_staNO_MOVE = 2
Private Const m_staNO_RETRACE = 3

'  Fault conditions
Private Const m_intRESET = 0


Public Function Version() As String

   With App
      Version = .Major & "." & .Minor & "." & .Revision
   End With 'app
   
End Function 'Version


Public Function InitStatus() As Boolean
   
   InitStatus = m_blnInitStatus
   
End Function 'InitStatus


Private Function LoadPrinterData(strFormatName As String, strTemplatePath As String) As Boolean

   #If ccShip_Ver Then
      On Error GoTo LoadPrinterData_Error
   #Else
      On Error GoTo 0
   #End If
   Exit Function

LoadPrinterData_Error:

   LoadPrinterData = False
   ProccessError "LoadPrinterData", m_strName, Err.Number, Err.Description

End Function 'LoadPrinterData

Public Sub RunStopJob()
   
   
   TraceLog ("Class=Labeler: RunStopJob")
   
   #If ccTrace Then
      Debug.Print m_strName & ".RunStopJob (IN) -- " & "labST=" & m_staLabelerState & " -- retST=" & m_staReturnState
   #End If
   #If ccShip_Ver Then
      On Error GoTo RunStopJob_Error
   #Else
      On Error GoTo 0
   #End If

   If m_staLabelerState = m_staRUNNING Then
      TraceLog ("Class=Labeler: RunStopJob State was Running")
      
      m_blnNextLabel = False
      '   Set to idle
      m_staLabelerState = m_staIDLE
      If (g_blnOpenTraceLogFile) Then TraceLog ("Class=Labeler: RunStopJob State now Idle")
      
      With m_objMainForm
          If (g_blnOpenTraceLogFile) Then
              TraceLog ("Class=Labeler: RunStopJob->MainJobEnd")
          End If
              
         
         .JobEnd
         .MessageClear
      End With ' m_objMainForm
      frmHistory.Message "Job Stopped"
      frmInstructions.InstructionsRemove 'Make sure that instruction box is removed
      m_objBeckon.TurnOnBeckon intLight:=m_intNO_LIGHT
      
      TraceLog ("Class=Labeler: RunStopJob Display Job Stopped Message ")
      
   
   ElseIf m_staLabelerState = m_staIDLE Then
      TraceLog ("Class=Labeler: RunStopJob State was Idle")
      
      TraceLog ("Class=Labeler: RunStopJob->CheckAirCtrlVolt")
       
      
      CheckAirCtrlVolt
      m_staLabelerState = m_staRUNNING
      TraceLog ("Class=Labeler: RunStopJob State = Running")
      
      If Not GuardDoorsClosed Then
         TraceLog ("Class=Labeler: Guard Door Open")
         
         OnBit_GardDoorsClosed False
         Exit Sub
      End If
     
      
      m_blnNextLabel = True
      '   set to run
      frmHistory.Message "Job Started"
      frmInstructions.InstructionsRemove 'Make sure that instruction box is removed
      
      frmHistory.Message "Labeler started"
      
      With m_objMainForm
         TraceLog ("Class=Labeler: Start JobRun")
         
         .JobRun
         .labTextQuantity.Caption = m_lngPanelQuintityCount
         m_lngSequenceNumber = .CurrentSeqNumber
      End With 'm_objMainForm
      
      m_objBeckon.TurnOnBeckon intLight:=g_intGREEN
      TraceLog ("Class=Labeler: Set beacon light = green")


'   ElseIf m_staLabelerState = m_staSUSPENDED Or _
'          m_staLabelerState = m_staRELABEL Then
   ElseIf m_staLabelerState = m_staSUSPENDED Then
      TraceLog ("Class=Labeler: State was Suspended")
     
      '  Restart the job
      m_blnNextLabel = False
      '   Set to idle
      m_staLabelerState = m_staIDLE
      TraceLog ("Class=Labeler: State now Idle")
      
      With m_objMainForm
         .JobEnd
         .MessageClear
      End With ' m_objMainForm
      m_staLabelerState = m_staIDLE
      
      m_objBeckon.TurnOnBeckon intLight:=m_intNO_LIGHT
      
      
      Select Case m_staSpendState
         Case m_staNO_VACUUM: OnEvent_NoVacuum False
         Case m_staNO_MOVE: OnEvent_NoMove False
      End Select
      m_staLabelerState = m_staIDLE
   
   End If
       
  
   
 Exit Sub

   
   

   #If ccTrace Then
      Debug.Print m_strName & ".RunStopJob (EX) -- " & "labST=" & m_staLabelerState & " -- retST=" & m_staReturnState
   #End If
RunStopJob_Error:

   ProccessError "RunStopJob", m_strName, Err.Number, Err.Description

End Sub 'RunStopJob


Public Function Initialize(objScanner As Object, _
                           objBottomScanner As Object, _
                           objOutput As Object, _
                           objInput As Object, _
                           objPrinter As Object, _
                           objMove As Object) As Boolean

   #If ccShip_Ver Then
      On Error GoTo Initialize_Error
   #Else
      On Error GoTo 0
   #End If
Dim DBase As Database
Dim Table As Recordset
Dim nCount As Integer
Dim strDBPath As String
    
   m_blnBAD_SerialDB_Found = False
   strDBPath = App.Path + Trim("\BadSN.mdb")
   
   If (Dir(strDBPath, vbNormal) <> "") Then
      Set DBase = OpenDatabase(strDBPath)
      Set Table = DBase.OpenRecordset("Table", dbOpenTable)
   
      Table.MoveFirst
    
      m_nNoOfBadSerialNumbers = Table.RecordCount
        
      For nCount = 1 To m_nNoOfBadSerialNumbers
          sBadNumbers(nCount, 1) = Table("First")
          sBadNumbers(nCount, 2) = Table("Second")
          Table.MoveNext
      Next
   
      Table.Close
      DBase.Close
      m_blnBAD_SerialDB_Found = True
  End If
   
  '  set job state
   m_blnInitStatus = True
    
   ' Set up refrences to the subsystems
   Set m_objPrinter = objPrinter
   Set m_objscanner = objScanner
   Set m_objBottomScanner = objBottomScanner
   Set m_objOutputs = objOutput
   Set m_objInputs = objInput
   Set m_objMove = objMove
   
   '  Now chech that all nessary objects are present
   '  pritner object
   If m_objPrinter Is Nothing Then
      If m_objPrinter.InitStatus Then
         Err.Raise g_intINIT_PTR_OBJ, "clsLabeler.Initialize", LoadResString(resERR_INIT_PTR_OBJ)
         m_blnInitStatus = False
      End If
   End If
   '  scanner object
   If m_objscanner Is Nothing Then
      If m_objscanner.SelfTest Then
         Err.Raise g_intINIT_SCANNER_OBJ, "clsLabeler.Initialize", LoadResString(resERR_INIT_SCANNER_OBJ)
         m_blnInitStatus = False
      End If
   End If
   
   If (m_objBottomScanner Is Nothing) And (Not g_blnNotUseBottomScanner) Then
'      If m_objBottomScanner.SelfTest Then
         Err.Raise g_intINIT_SCANNER_OBJ, "clsLabeler.Initialize", LoadResString(resERR_INIT_SCANNER_OBJ)
         m_blnInitStatus = False
'      End If
   End If
   
   
   
   
   '  Move object
   If m_objMove Is Nothing Then
      Err.Raise g_intINIT_OUTPUT_OBJ, "clsLabeler.Initialize", LoadResString(resERR_INIT_OUTPUT_OBJ)
      m_blnInitStatus = False
   Else
      m_objMove.SetCallBack Me
   End If
   '  Digital output objects
   If m_objOutputs Is Nothing Then
      Err.Raise g_intINIT_OUTPUT_OBJ, "clsLabeler.Initialize", LoadResString(resERR_INIT_OUTPUT_OBJ)
      m_blnInitStatus = False
   End If
   '  Inputs object
   If m_objInputs Is Nothing Then
      Err.Raise g_intINIT_MOVE_OBJ, "clsLabeler.Initialize", LoadResString(resERR_INIT_MOVE_OBJ)
      m_blnInitStatus = False
   Else
      '  Tell the digital IO subsys where my call back is
      '  and start the input scanning
      With m_objInputs
         .SetCallBack Me, g_ibitGuardDoor, g_ibitLowLabel, g_ibitPartPresent, g_ibitPrinterEngaged, _
                                 g_ibitVacuumSense, g_ibitAirPresser, g_ibitRetracted, g_ibitRotate0, _
                                 g_ibitRotate90
         .ScanInputs blnEnable:=True
      End With 'm_objInputs
   End If
   
   '  Initilzie the beckon class
   Set m_objBeckon = New clsBeckon
   If m_objBeckon Is Nothing Then
      Err.Raise g_intINIT_BECKON_OBJ, "clsLabeler.Initialize", LoadResString(resERR_INIT_BECKON_OBJ)
      m_blnInitStatus = False
   Else
      m_blnInitStatus = m_blnInitStatus And m_objBeckon.Initialize(objOutput:=m_objOutputs)
   End If
    
   '  Now set the job state
   m_staLabelerState = m_staINIT
   m_blnAutoRun = False
   
   Exit Function

Initialize_Error:

   Initialize = False
   ProccessError "Initialize", m_strName, Err.Number, Err.Description

End Function 'Initialize

Public Sub SetMainForm(objMainForm As Object)
'  This module is called by the main form to pass the refrence to it
'  and to initialize the motion now that all is here

   Dim dbLabelerDataBase As Database
   Dim snpConfiguration As Recordset
   
   #If ccShip_Ver Then
      On Error GoTo SetMainForm_Error
   #Else
      On Error GoTo 0
   #End If
   
   Set m_objMainForm = objMainForm
   
   With m_objMainForm
      m_objMove.SetMoveTimeOut lngValue:=CLng(.txbMoveTimeOut.Text)
      If .txbKitFilePath.Text = "" Then
         m_strKitPathFileName = App.Path & "\" & .txbKitFileName.Text
      Else
         m_strKitPathFileName = .txbKitFilePath.Text & "\" & .txbKitFileName.Text
      End If
      If .txbLogFilePath.Text = "" Then
         m_strLogPathFileName = App.Path & "\" & .txbLogFileName.Text
      Else
         m_strLogPathFileName = .txbLogFilePath.Text & "\" & .txbLogFileName.Text
      End If
      m_chrKeyFileDelim = .txbKitFileDlim.Text
      m_chrLogFileDelim = .txbLogFileDlim.Text
   End With 'm_objMainForm
   
   Exit Sub
   
SetMainForm_Error:

   ProccessError "SetMainForm", m_strName, Err.Number, Err.Description
   
End Sub 'SetMainForm

Private Sub Class_Initialize()
   
   #If ccShip_Ver Then
      On Error GoTo Class_Initialize_Error
   #Else
      On Error GoTo 0
   #End If
   
   m_blnInitStatus = True
   
   ' give me a name
   m_strName = "clsLabeler"
   
   '  Setup Labeler configuration data
   m_blnInitStatus = m_blnInitStatus And InitConfiguration()
   
   Exit Sub
   
Class_Initialize_Error:

   ProccessError "Class_Initialize", m_strName, Err.Number, Err.Description
   m_blnInitStatus = False
   
End Sub 'Class_Initialize




Public Function InfoJob(strJobID As String, strName As String, _
                        strPartNumber As String, strLocationCode As String, _
                        strFormatName As String, strTemplatePath As String, _
                        blnAutoRun As Boolean, blnNewJob As Boolean) As Boolean
'  This function sets the labeler to run the first job

   Dim blnStatus As Boolean
   Dim strTempBuff As String
   Dim a_strBuffer(2) As String
   
   #If ccShip_Ver Then
      On Error GoTo InfoJob_Error
   #Else
      On Error GoTo 0
   #End If
    
   blnStatus = True
   
   '  initilize the job
   blnStatus = blnStatus And InitJob(strJobID:=strJobID, strName:=strName, _
                                 strPartNumber:=strPartNumber, _
                                 strFormatName:=strFormatName, _
                                 strLocationCode:=strLocationCode, _
                                 strTemplatePath:=strTemplatePath)
                        
   
   If blnNewJob Then
      '  Set auto run flage
      m_blnAutoRun = blnAutoRun
      
      '  Set job state to idle
      m_staLabelerState = m_staIDLE
      
      '  Rotate blowoff to pickup position
      m_objOutputs.SetBit intbit:=g_obitRotate, blnValue:=True
      
'      m_blnManualFeed = False
      
   End If
   
   InfoJob = blnStatus
   
   strTempBuff = "Job: " & strName & vbCrLf
   strTempBuff = strTempBuff & "PN: " & strPartNumber & vbCrLf
   strTempBuff = strTempBuff & "Loc: " & strLocationCode
   
   frmHistory.Message strTempBuff
   
   Exit Function

InfoJob_Error:

   ProccessError "InfoJob", m_strName, Err.Number, Err.Description
   InfoJob = False

End Function 'InfoJob




Public Function InitConfiguration() As Boolean

   Dim dbLabelerDataBase As Database
   Dim snpConfiguration As Recordset
   Dim blnStatus As Boolean
   
   #If ccShip_Ver Then
      On Error GoTo InitConfiguration_Error
   #Else
      On Error GoTo 0
   #End If
   
   InitConfiguration = False
   blnStatus = True
   
   '  Set up Labeler data
   Set dbLabelerDataBase = Workspaces(0).OpenDatabase(modMain.GetConfigurationDataBaseName)
   Set snpConfiguration = dbLabelerDataBase.OpenRecordset(modMain.GetLabelerConfiguration, dbOpenSnapshot)
   m_strConfigName = snpConfiguration![strName]
   m_lngAcuatorExtendTime = snpConfiguration![lngExtendtime]
   m_lngApplyDwellTime = snpConfiguration![lngApplyDwellTime]
   
   dbLabelerDataBase.Close
      
   Exit Function
   
InitConfiguration_Error:

   ProccessError "InitConfiguration", m_strName, Err.Number, Err.Description
   InitConfiguration = False

End Function 'InitConfiguration


Public Sub On_Event(intbit As Integer, Optional blnValue As Variant)
 
   #If ccTrace Then
      If IsMissing(blnValue) Then
         Debug.Print m_strName & ".On_Event -- Bit = " & intbit; "-- Value = NA"
      Else
         Debug.Print m_strName & ".On_Event -- Bit = " & intbit & "-- Value =" & blnValue
      End If
   #End If
   #If ccShip_Ver Then
      On Error GoTo On_Event_Error
   #Else
      On Error GoTo 0
   #End If
'   m_objInputs.CheckGuardDoor
   Select Case intbit
      'Digital input events
      Case g_ibitPartPresent:          OnBit_PartReady
      Case g_ibitVacuumSense:          OnBit_VacuumSense
      Case g_ibitPositioningEnd:       OnBit_MoveComplete
      Case g_ibitRetracted:            OnBit_Retracted
      Case g_ibitLowLabel:             OnBit_LowLabel CBool(blnValue)
      Case g_ibitGuardDoor:            OnBit_GardDoorsClosed CBool(blnValue)
      Case g_ibitAirPresser:           OnBit_AirPressurLoss CBool(blnValue)
      Case g_ibitSA_Alarm:             OnBit_MotionError
      Case g_ibitPrinterEngaged:       OnBit_EngagePrinter CBool(blnValue)
      Case g_ibitEStop:                 OnBit_EmergStop
      '  Internal events
      Case m_evtNEXT_LABEL:            OnEvent_NextLabel
      Case m_evtLABEL_APPLIED:         OnEvent_LabelApplied
      Case m_evtLABELING_COMPLETE:     OnEvent_LabelingComplete
      Case m_evtAPPLY_LABEL:           OnEvent_ApplyLabel
      
      '  Events from the main form
      Case g_evtLABEL_PICKUP_TIMEOUT:  OnEvent_NoVacuum CBool(blnValue)
      Case g_evtARM_MOVE_TIMEOUT:      OnEvent_NoMove CBool(blnValue)
      Case g_evtARM_RETRACT_TIMEOUT:   OnEvent_NoRetract CBool(blnValue)
      Case g_evtMANUAL_FEED:           OnEvent_ManualFeed
      Case g_evtTEST_LABEL:            OnEvnet_PrintTestLabel
   End Select

   Exit Sub

On_Event_Error:

   ProccessError "On_Event", m_strName, Err.Number, Err.Description

End Sub 'On_Event
Public Sub OnBit_EmergStop()
  
  TraceLog ("Class=Labeler: OnBit_EmergStop")
  
End Sub
Private Sub OnBit_EngagePrinter(blnValue As Boolean)

   Static intMesgNumber As Integer
   
   TraceLog ("Class=Labeler: OnBit_EngagePrinter")
   
   
   #If ccShip_Ver Then
      On Error GoTo OnBit_EngagePrinter_Error
   #Else
      On Error GoTo 0
   #End If
   
   If Not blnValue Then
      If intMesgNumber = 0 Then
         intMesgNumber = m_objMainForm.MessageDisplay(LoadResString(resPRINTER_NOT_ENGUAGED))
      End If
   Else
      PrinterEngage
      intMesgNumber = m_objMainForm.MessageRemove(intMesgNumber)
   End If
   
   Exit Sub

OnBit_EngagePrinter_Error:

   ProccessError "OnBit_EngagePrinter", m_strName, Err.Number, Err.Description
   

End Sub 'OnBit_EngagePrinter

Private Sub OnBit_LowLabel(blnValue As Boolean)

   #If ccShip_Ver Then
      On Error GoTo OnBit_LowLabel_Error
   #Else
      On Error GoTo 0
   #End If
    
   TraceLog ("Class=Labeler: OnBit_LowLabel")
    
    
   Static s_intMesgNumber As Integer
   
   If blnValue Then
      If s_intMesgNumber = 0 Then
         s_intMesgNumber = m_objMainForm.MessageDisplay(LoadResString(resLOW_LABEL))
      End If
      m_objBeckon.Yellow blnOn:=True
   Else
      s_intMesgNumber = m_objMainForm.MessageRemove(s_intMesgNumber)
      m_objBeckon.Yellow blnOn:=False
   End If
   
   Exit Sub

OnBit_LowLabel_Error:

   ProccessError "OnBit_LowLabel", m_strName, Err.Number, Err.Description

End Sub 'LowLabel


Public Sub OnEvent_NextLabel()
Dim strLastLabelPrinted As String
Dim strBuffer As String


   #If ccTrace Then
      Debug.Print m_strName & ".OnEvent_NextLabel -- " & "labST=" & m_staLabelerState & " -- retST=" & m_staReturnState
   #End If
   #If ccShip_Ver Then
      On Error GoTo OnEvent_NextLabel_Error
   #Else
      On Error GoTo 0
   #End If
    
   TraceLog ("Class=Labeler: OnEvent_NextLabel")
    
    
   If m_staLabelerState = m_staRUNNING _
      Or m_staLabelerState = m_staIDLE _
      Or m_staLabelerState = m_staRELABEL _
   Then
 '     If m_objInputs.Value(g_ibitRetracted) Then
         '  Seve the current state then set new state
         m_staReturnState = m_staLabelerState
         m_staLabelerState = m_staLABELING
         
         '  Start labeling process
         With m_objOutputs
                        
            '  Print label
'            If m_staReturnState <> m_staRELABEL Then
'               m_objPrinter.PrintLabel strOut:=GetNextlabel()
'            Else
'              m_objPrinter.PrintLabel m_strLabelDataPrinted
'            End If
            
            'Change requested by Ford Markham 06/29/30
            'Each time a bar code label is printed,
            'the serial number is incremented.
             TraceLog ("Class=Labeler: OnEvent_NextLabel->PrintLabel")
             
            strBuffer = ""
            If (Not g_blnIs2Sided) Then
                m_objPrinter.PrintLabel strOut:=GetNextlabel()
            Else
                
                strBuffer = GetBottomScannedLabel()
                If (strBuffer = "") Then
                    With m_objBeckon
                       .TurnOnBeckon intLight:=g_intRED
                    End With 'm_objBeckon
                    m_staLabelerState = m_staIDLE
                    m_objMainForm.JobEnd
                    Exit Sub

                End If
                m_objPrinter.PrintLabel strOut:=strBuffer
            
            End If
            
            
             
            
            
            '  Now desplay it
            m_objMainForm.labTextPrinted.Caption = CStr(m_strLabelDataPrinted)
           ' m_objMainForm.labTextScanned.Caption = " " 'CStr(m_strLabelDataPrinted)

            '  Enalbe Blow off
            
             TraceLog ("Class=Labeler: OnEvent_NextLabel >> Turn On Air Blast")
            
            .SetBit g_obitAirBlast, True
          
            '  Enable vacuum
            
             TraceLog ("Class=Labeler: OnEvent_NextLabel >> Turn On NosePiece Vacuum")
            
            
            .SetBit g_obitVacuum, True
      
      
            TraceLog ("Class=Labeler: OnEvent_NextLabel >> Turn On Timer for Label Pickup")
      
            If Not g_blnSimulator Then
              TraceLog ("Class=Labeler: OnEvent_NextLabel >>Time On Pickup TimeOut Timer")
              m_objMainForm.tmrPickupTimeOut.Enabled = True
            End If
      
         End With 'm_objOutputs
   End If
        
   Exit Sub

OnEvent_NextLabel_Error:

   ProccessError "OnEvent_NextLabel", m_strName, Err.Number, Err.Description

End Sub 'OnEvent_NextLabel


Public Sub OnEvnet_PrintTestLabel()
   
   If m_staLabelerState = m_staIDLE Then
      '  Print label
      m_objPrinter.PrintLabel "TestLabel"
   End If
   
End Sub 'OnEvnet_PrintTestLabel


Private Sub OnEvent_ManualFeed()
   
   #If ccShip_Ver Then
      On Error GoTo OnEvent_ManualFeed_Error
   #Else
      On Error GoTo 0
   #End If
   
  TraceLog ("Class=Labeler: OnEvent_ManualFeed >> Set beacon light = red")
   
   
   m_objBeckon.Red (True)
   
'   If m_staLabelerState = m_staIDLE Then
      m_blnManualFeed = True
      TraceLog ("Class=Labeler: OnEvent_ManualFeed >> Set Job State = manual feed")
      TraceLog ("Class=Labeler: OnEvent_ManualFeed >> Calling m_evtNEXT_LABEL")
      
      On_Event m_evtNEXT_LABEL
'   End If
'   m_staLabelerState = m_staIDLE
   
   Exit Sub
OnEvent_ManualFeed_Error:

   ProccessError "OnEvent_ManualFeed", m_strName, Err.Number, Err.Description

End Sub 'OnEvent_ManualFeed


Public Sub OnEvent_LabelApplied()
'  This function scans the label and compares it to the label printed.
'  It provides a method from recovering from miss-scanned labels.

   Dim strScanData As String
   Dim blnGoodScan As Boolean
   Dim intAttempts As Integer
   Dim strResponse As String
   Dim a_strButtons(3) As String
   Dim s_intMesgNumber As Integer
   
   TraceLog ("Class=Labeler: Entered OnEvent_LabelApplied ")
   
   
   #If ccTrace Then
      Debug.Print m_strName & ".OnEvent_LabelApplied -- " & "labST=" & m_staLabelerState & " -- retST=" & m_staReturnState
   #End If
   #If ccShip_Ver Then
      On Error GoTo OnEvent_LabelApplied_Error
   #Else
      On Error GoTo 0
   #End If
   
   If m_staLabelerState = m_staAPPLYING Then
   
      '  Set the state to scanning
      m_staLabelerState = m_staSCANNING
       
      'Scann the label
      frmInstructions.InstructionsRemove ' make sure the instruction box is removed
      
      '  Look at data from que
      frmHistory.Message "Queued: " & m_strLabelDataPrinted
      
      '  rotate the actuator for scanning
       'code????
 '     m_objOutputs.SetBit intBit:=g_obitEERotate, blnValue:=False
            
OnEvent_LabelApplied_Try_Agen: ' This allows to keep rescanning the label
                               '  with little effect on the state machine.
      '  Check bar code
      intAttempts = 0
      If g_strDisable_Scanner = "Y" Then
         blnGoodScan = True
      Else
 '       Do '  scan the label and compar
         '  How did it scan ?
         TraceLog ("Class=Labeler: OnEvent_LabelApplied->ReadBarCode ")
          If Not g_blnSimulator Then
                blnGoodScan = m_objscanner.ReadBarCode(m_strLabelDataPrinted)
          
          Else
              blnGoodScan = True
          End If
      
      End If
      '  if scanned ok...
      If blnGoodScan Or m_blnManualFeed Then
         
         
         
         If m_blnManualFeed Then
           m_objBeckon.TurnOnBeckon intLight:=g_intRED
          TraceLog ("Class=Labeler: OnEvent_LabelApplied. State=Manual Feed, Beacon = Red  ")
         
         Else
          TraceLog ("Class=Labeler: OnEvent_LabelApplied. State=Good Scan, Beacon = Green  ")
           
           m_objBeckon.TurnOnBeckon intLight:=g_intGREEN
         End If
         
         '  now display the last label scanned
         If (g_blnSimulator) Then
         
            m_objMainForm.labTextScanned.Caption = m_strLabelDataPrinted
            
          Else
            m_objMainForm.labTextScanned.Caption = m_objscanner.m_strBarCode
          
          End If
         
         TraceLog ("Class=Labeler: OnEvent_LabelApplied->OnEvent_LabelingComplete")
         
         
         OnEvent_LabelingComplete
         
         ' Now move back to the printer to complete the labeling tasks
         
         TraceLog ("Class=Labeler: OnEvent_LabelApplied->MovetoPrinter")
         
         MoveToPrinter
'         m_staLabelerState = m_staRUNNING
         s_intMesgNumber = m_objMainForm.MessageRemove(s_intMesgNumber)
         
     Else 'Label failed to scan so ...
         With m_objBeckon
            .TurnOnBeckon intLight:=g_intRED
           ' .BuzzerAcknowledge LoadResString(resMSG_MISS_SCAN_BUZZER)
         End With 'm_objBeckon
          TraceLog ("Class=Labeler: OnEvent_LabelApplied. State=Bad Scan, Beacon = Red  ")
         
         With m_objMainForm
            .JobHolding True
            '  Display a message on the main form
            If s_intMesgNumber = 0 Then
               s_intMesgNumber = .MessageDisplay(strMsg:=LoadResString(resLABEL_SCAN_ERROR))
            End If
         End With 'm_objMainForm
         
         a_strButtons(0) = m_strRESCAN
         a_strButtons(1) = m_strRELABEL
         a_strButtons(2) = m_strCONTINUE
         a_strButtons(3) = m_strCANCEL
         
         TraceLog ("Class=Labeler: OnEvent_LabelApplied. State=Bad Scan, Show Relabel, rescan dialog box ")
         
         
         '  Show instructions
         strResponse = frmInstructions.InstructionsDialog(strFileName:=App.Path & "\" & m_strBAD_SCAN, a_strButtons:=a_strButtons)
         If strResponse = m_strRESCAN Then
            '  Go back up and rescan the label
             TraceLog ("Class=Labeler: OnEvent_LabelApplied. State=Bad Scan, Operator chose Rescan ")
            
            GoTo OnEvent_LabelApplied_Try_Agen
         ElseIf strResponse = m_strRELABEL Then
            m_objBeckon.TurnOnBeckon intLight:=g_intGREEN
             TraceLog ("Class=Labeler: OnEvent_LabelApplied. State=Bad Scan, Operator chose Relabel ")
            
            With m_objMainForm
               .JobHolding False
               '  Display a message on the main form
               s_intMesgNumber = .MessageRemove(s_intMesgNumber)
            End With 'm_objMainForm
            '  Do a relabel
            m_staLabelerState = m_staRELABEL
            MoveToPrinter
            OnEvent_NextLabel
            m_staLabelerState = m_staLABELING

           ' m_staLabelerState = m_staRUNNING
         ElseIf strResponse = m_strCONTINUE Then
            TraceLog ("Class=Labeler: OnEvent_LabelApplied. State=Bad Scan, Operator chose Skip ")
            
            '  skip this one so move to printer
            MoveToPrinter
            m_staLabelerState = m_staRUNNING
            m_objBeckon.TurnOnBeckon intLight:=g_intGREEN
            With m_objMainForm
               .JobHolding False
               '  Display a message on the main form
               s_intMesgNumber = .MessageRemove(s_intMesgNumber)
            End With 'm_objMainForm
         Else ' m_strCANCEL
            TraceLog ("Class=Labeler: OnEvent_LabelApplied. State=Bad Scan, Operator chose Cancel ")
            
            MoveToPrinter
            m_staLabelerState = m_staRUNNING
            m_objBeckon.TurnOnBeckon intLight:=g_intGREEN
            With m_objMainForm
               .JobHolding False
               '  Display a message on the main form
               s_intMesgNumber = .MessageRemove(s_intMesgNumber)
            End With 'm_objMainForm
            RunStopJob
         End If ' Continue
      End If
         
   End If
   
   TraceLog ("Class=Labeler: Exiting OnEvent_LabelApplied. Normal Exit")
   
   Exit Sub
   
OnEvent_LabelApplied_Error:

   ProccessError "OnEvent_LabelApplied", m_strName, Err.Number, Err.Description

End Sub 'OnEvent_LabelApplied


Private Sub OnEvent_LabelingComplete()
   
   #If ccTrace Then
      Debug.Print m_strName & ".OnEvent_LabelingComplete -- " & "labST=" & m_staLabelerState & " -- retST=" & m_staReturnState
   #End If
   #If ccShip_Ver Then
      On Error GoTo OnEvent_LabelingComplete_Error
   #Else
      On Error GoTo 0
   #End If
   
   TraceLog ("Class=Labeler: Entered OnEvent_LabelingComplete.")
   
   
   If m_staLabelerState = m_staSCANNING Then
       
      If m_staReturnState = m_staRELABEL Then
        m_staLabelerState = m_staRUNNING
      Else
      
        m_staLabelerState = m_staReturnState
      End If
      
      
      If m_blnManualFeed Then
         m_blnManualFeed = False
         m_staLabelerState = m_staIDLE

      Else
        TraceLog ("Class=Labeler: OnEvent_LabelingComplete. If State<>(Manual Feed) panel count-> quantity+=1")
         
         
         m_lngPanelQuintityCount = m_lngPanelQuintityCount + 1

         UpdateLabelLog
         With m_objMainForm
            .PanelComplete CStr(m_lngPanelQuintityCount)
            If m_lngSequenceNumber = Val("9999999") Then
               g_blnLogError = True
               TraceLog ("Class=Labeler: OnEvent_LabelingComplete. Board Serialization Is Wrong")
                
               MsgBox ("Warning Check Trace Log File Board Serialization Is Wrong")
               frmMain.JobEnd
               Exit Sub
            End If
            .CurrentSeqNumber = m_lngSequenceNumber
         End With 'm_objMainForm
         TraceLog ("Class=Labeler: OnEvent_LabelingComplete. Sequence Number = " + Str(g_lngSequenceNumber))
         g_lngSequenceNumber = g_lngSequenceNumber + 1
         g_nMaxDefSequence = g_nMaxDefSequence + 1
        
        ' m_objOutputs.StrobeBit intBit:=g_obitLabelingComplete, blnWait:=True
        TraceLog ("Class=Labeler: Entered OnEvent_LabelingComplete>>SetOutput Bit 10 = true")
        m_objOutputs.StrobeBit intbit:=10, blnWait:=True
      End If
   End If
   
   Exit Sub

OnEvent_LabelingComplete_Error:

   ProccessError "OnEvent_LabelingComplete", m_strName, Err.Number, Err.Description

End Sub 'OnEvent_LabelingComplete



Public Sub OnBit_PartReady()
'  This procedure is executed when the part ready bit is set to true.
Dim ltimer As Long
Dim nCount As Integer

   #If ccTrace Then
      Debug.Print m_strName & ".OnBit_PartReady -- " & "labST=" & m_staLabelerState & " -- retST=" & m_staReturnState
   #End If
   #If ccShip_Ver Then
      On Error GoTo OnBit_PartReady_Error
   #Else
      On Error GoTo 0
   #End If
   TraceLog ("Class=Labeler: OnBit_PartReady.")
   
   ltimer = Timer
   If UCase(frmOpenJob.txbHPEnabled = "Y") Then
     If (Not g_blnSimulator) Then
          m_objInputs.GetHolePattern
          frmMain.lblDHolePattern.Caption = Trim(Str(g_intHolePattern))
          nCount = 1
          Do While g_intHolePattern <> Val(frmOpenJob.txbHolePattern.Text)
            m_objInputs.GetHolePattern
            
            SleepSec (1)
            If nCount > 5 Then
            
              With m_objBeckon
                 .TurnOnBeckon intLight:=g_intRED
              End With 'm_objBeckon
              m_staLabelerState = m_staIDLE
              m_objMainForm.JobEnd
        '      RunStopJob
              MsgBox ("Job File Flavor <> Digital I/O Flavor")
              
              Exit Sub
            End If
            nCount = nCount + 1
          Loop
     End If
     
     frmMain.lblDHolePattern.Caption = Trim(Str(g_intHolePattern))
   
   Else
      frmMain.lblDHolePattern.Caption = "Disabled"
   End If
   
   
   
   If m_staLabelerState = m_staRUNNING Then
      m_objMainForm.PartReady
      If m_blnAutoRun Then
         GetNextJob m_strKitPathFileName
      End If
      
      If (g_blnIs2Sided) Then
        If frmScanner.m_strScannedBottomLabel = "" Then
            
              With m_objBeckon
                 .TurnOnBeckon intLight:=g_intRED
              End With 'm_objBeckon
              
              frmManualEntry.m_blnReturnState = False
              frmManualEntry.m_strNewScannedValue = ""
              frmManualEntry.Show vbModal
              While g_blnBoardRemove
                MsgBox ("Board Switch Has Not Been Closed")
                
              Wend
                             
              If (frmManualEntry.m_blnReturnState) Then
                m_strBottomScannedLabel = frmManualEntry.m_strNewScannedValue
                Unload frmManualEntry
              Else
                Unload frmManualEntry
                m_staLabelerState = m_staIDLE
                m_objMainForm.JobEnd
                Exit Sub
              End If
         Else
            m_strBottomScannedLabel = frmScanner.m_strScannedBottomLabel
            frmScanner.m_strScannedBottomLabel = ""
        End If
      End If
      On_Event m_evtNEXT_LABEL
   End If
   
   
   
   Exit Sub

OnBit_PartReady_Error:

   ProccessError "OnBit_PartReady", m_strName, Err.Number, Err.Description

End Sub 'OnBit_PartReady

Public Sub GetNextJob(strPathFileName As String)
'  This procure tries to open a file and read the first and only line it the file.
'     If the file does not exist, just exit and uses the current job.
'     If the file does exists then use the first field to look up a job.
'     If other fields exist then update the job or add it to the jobs DB.

   Dim strTemplateBuffer As String
   Dim hFile As Integer
   Dim udtJob As Job_Info

'   #If ccShip_Ver Then
      On Error GoTo GetNextJob_Error
'   #Else
'      On Error GoTo 0
'   #End If
   
   '  No file to open and check.
   
   TraceLog ("Class=Labeler: GetNextJob.")
   
   If strPathFileName = "" Then Exit Sub
   
   hFile = FreeFile
   If hFile = 0 Then
      Err.Raise g_errNO_FILE_HANDAL, , LoadResString(resERR_PRT_TPLATE_NO_HANDAL)
   Else  ' open the file and read the first line and only line
      Open strPathFileName For Input Access Read As #hFile
      Line Input #hFile, strTemplateBuffer
   End If
   
   Close hFile
   
   '  Now delete the file so will not read it agen.
   Kill strPathFileName
   
   If strTemplateBuffer = "" Then Exit Sub ' nothing there so get out
   
   '  Something there so process it
   '  Note NextToken is in modUtilities
   With udtJob
      .strName = NextToken(r_strText:=strTemplateBuffer, v_strDelmList:=m_chrKeyFileDelim)
      If strTemplateBuffer <> "" Then
         .strPartNumber = NextToken(r_strText:=strTemplateBuffer, v_strDelmList:=m_chrKeyFileDelim)
         .strLocationCode = NextToken(r_strText:=strTemplateBuffer, v_strDelmList:=m_chrKeyFileDelim)
         .strFormatName = NextToken(r_strText:=strTemplateBuffer, v_strDelmList:=m_chrKeyFileDelim)
         .strTemplatePath = NextToken(r_strText:=strTemplateBuffer, v_strDelmList:=m_chrKeyFileDelim)
      End If
   End With 'udtJob
   
   '  now send it off to be updated
   With udtJob
      m_objMainForm.JobUpdate v_strName:=.strName, _
                           r_strPartNumber:=.strPartNumber, _
                           r_strLocationCode:=.strLocationCode, _
                           r_strFormatName:=.strFormatName, _
                           r_strTemplatePath:=.strTemplatePath
   End With 'udtJob
      
   Exit Sub

GetNextJob_Error:

   Dim intErrNum As Integer
   
   intErrNum = Err.Number
   If (intErrNum = g_errFILE_NOT_FOUND) Or (intErrNum = g_errPATH_NOT_FOUND) Then
      Exit Sub       ' not found so continue with the current job
   Else
      ProccessError "GetNextJob", m_strName, Err.Number, Err.Description
   End If
   
End Sub 'GetNextJob


Private Sub OnBit_GardDoorsClosed(blnValue As Boolean)
'  This function reacts to open guard door bit displays a message
'  and then and stop the job if not stopped.
      
   Dim objInstructions As Object
   #If ccShip_Ver Then
      On Error GoTo OnBit_GardDoorsClosed_Error
   #Else
      On Error GoTo 0
   #End If
       
   Static s_intMesgNumber As Integer
   
   TraceLog ("Class=Labeler: OnBit_GardDoorsClosed.")
   
   
   If Not blnValue Then
      If s_intMesgNumber = 0 Then
         s_intMesgNumber = m_objMainForm.MessageDisplay("Guard Doors Open!")
      End If
      
      frmHistory.Message "Guard doors open!"
      m_staLabelerState = m_staIDLE

      If (m_staLabelerState = m_staIDLE) Or (m_staReturnState = m_staIDLE) Then
         
         
         With m_objBeckon
            .TurnOnBeckon intLight:=g_intRED
'            .BuzzerAcknowledge LoadResString(resMSG_GUARD_DOORS_OPEN_BUZZER)
         End With 'm_objBeckon
         
         m_objMainForm.JobInterrupted
      
      ElseIf (m_staLabelerState = m_staRUNNING) Or ((m_staReturnState = m_staRUNNING) And (m_staLabelerState <> m_staSUSPENDED)) Then
         m_objMainForm.JobInterrupted
         
         With m_objBeckon
            .TurnOnBeckon intLight:=g_intRED
            .BuzzerAcknowledge LoadResString(resMSG_GUARD_DOORS_OPEN_BUZZER)
         End With 'm_objBeckon
            
         frmInstructions.InstructionsDisplay strFileName:=App.Path & "\" & m_strGUARDS_OPEN
         'modMain.ExitEnd commented out KERRY 5/19/98 - cancel button will do this
      ElseIf m_staLabelerState = m_staINIT Then
         Do Until GuardDoorsClosed()
            frmInstructions.InstructionsDisplay strFileName:=App.Path & "\" & m_strGUARDS_OPEN
         Loop
      End If
   Else

   With m_objMove

       
   End With 'm_objMove
 


     
      m_objOutputs.SetBit 27, False

      frmMessage.MessageDisplay LoadResString(resRESETTING_MOTION)
      
      modAPI.SleepMSec g_lngSA_RESET_WAIT
      frmMessage.MessageRemove
      
      m_objInputs.ScanNow
      modAPI.SleepMSec g_lngSA_RESET_WAIT
      
      m_objMove.Home True
      
      
      

         
         With m_objBeckon
            .Red False
            .Yellow False
            
            .Green True  ' intLight:=g_intGREEN
         End With 'm_objBeckon

      
      If m_staLabelerState = m_staIDLE Then
         m_objMainForm.JobRunEnable
      End If
      s_intMesgNumber = m_objMainForm.MessageRemove(s_intMesgNumber)
   End If

   Exit Sub 'm_staLabelerState

OnBit_GardDoorsClosed_Error:

   ProccessError "OnBit_GardDoorsClosed", m_strName, Err.Number, Err.Description

End Sub 'GardDoorsOpen


Private Sub OnBit_AirPressurLoss(blnValue As Boolean)

   #If ccShip_Ver Then
      On Error GoTo OnBit_AirPressurLoss_Error
   #Else
      On Error GoTo 0
   #End If
 
   Static s_intMesgNumber As Integer
   
   g_blnLogError = True
   TraceLog ("Class=Labeler: OnBit_AirPressurLoss.")
   g_blnLogError = False
   
   
   If Not blnValue Then

   
      m_objMove.EStop
      s_intMesgNumber = m_objMainForm.MessageDisplay(LoadResString(resAIR_PRESSURE_LOSS))
      frmHistory.Message "Air pressure lost!"
      m_objMainForm.JobInterrupted
      With m_objBeckon
         .TurnOnBeckon intLight:=g_intRED

      End With 'm_objBeckon
         
      Do Until HaveAir()

         frmInstructions.InstructionsDisplay strFileName:=App.Path & "\" & m_strNO_AIR
      Loop
      
      ' air restored so restart the job in idel mode
      InitMotion
      s_intMesgNumber = m_objMainForm.MessageRemove(s_intMesgNumber)
      m_staLabelerState = m_staRUNNING
    
      RunStopJob
   End If
   
   Exit Sub

OnBit_AirPressurLoss_Error:

   ProccessError "OnBit_AirPressurLoss", m_strName, Err.Number, Err.Description

End Sub 'AirPressurLoss

Private Sub OnBit_MotionError()
'  This function reacts to an error "Alarm to SA" displays a message
'  and then tries to reset the SA and stop the job.

   
   #If ccShip_Ver Then
      On Error GoTo OnBit_MotionError_Error
   #Else
      On Error GoTo 0
   #End If
      
   Static s_intMesgNumber As Integer
   
   g_blnLogError = True
   TraceLog ("Class=Labeler: OnBit_MotionError.")
   g_blnLogError = False
   
   
   s_intMesgNumber = m_objMainForm.MessageDisplay(LoadResString(resMOTION_ERROR))
   frmHistory.Message "Motion Error!"
   m_objMainForm.JobInterrupted
   With m_objBeckon
      .TurnOnBeckon intLight:=g_intRED

   End With 'm_objBeckon
      
   Do
      frmInstructions.InstructionsDisplay strFileName:=App.Path & "\" & m_strMOTION_ERR
      InitMotion
   Loop Until m_objMove.Ready
   
   ' air restored so restart the job in idel mode
   s_intMesgNumber = m_objMainForm.MessageRemove(s_intMesgNumber)
   m_staLabelerState = m_staRUNNING
   RunStopJob
   
   Exit Sub

OnBit_MotionError_Error:

   ProccessError "OnBit_MotionError", m_strName, Err.Number, Err.Description

End Sub 'OnBit_MotionError

Public Sub OnBit_VacuumSense()
'  This procedure is executed when the vacuum scenes bit goes true
'  The assumption is that a label is on the end of the actuator.

   #If ccTrace Then
      Debug.Print m_strName & ".OnBit_VacuumSense -- " & "labST=" & m_staLabelerState & " -- retST=" & m_staReturnState
   #End If
   #If ccShip_Ver Then
      On Error GoTo OnBit_VacuumSense_Error
   #Else
      On Error GoTo 0
   #End If
   
   TraceLog ("Class=Labeler: OnBit_VacuumSense.")
   
   
   If m_staLabelerState = m_staLABELING Then
      '  disable the pickup timer
      If Not g_blnSimulator Then
        TraceLog ("Class=Labeler:OnBit_VacuumSense=true disable pickup timer")
        m_objMainForm.tmrPickupTimeOut.Enabled = False
      End If
      '  NOW SET TO THE MOVING STATE
      
      m_staLabelerState = m_staMOVING
      
      '  Disable Blow Off
      TraceLog ("Class=Labeler:OnBit_VacuumSense Disable Air Blast")
      
      m_objOutputs.SetBit g_obitAirBlast, False

      ' Now move to the label position
      
      If m_blnManualFeed Then
         TraceLog ("Class=Labeler: OnBit_VacuumSense. State = Manual feed. Move to Stack Position")
         
         MoveToQueueStack
        OnEvent_ApplyLabel
      
      Else
         TraceLog ("Class=Labeler: OnBit_VacuumSense. Move to Print Position =" + m_udtCurrentJob.strLocationCode)
         
         With m_objMove
           .Position = m_udtCurrentJob.strLocationCode
           .Move blnWait:=True
         End With 'm_objMove
         '  rotate the actuator but waite for a bit
         '  to allow the actuatro to clear the printer
'         modAPI.SleepMSec 2000 ' CLng(m_objMainForm.txbEERotateDelay.Text)
         
         
         If UCase(g_strRotateNosePiece) = "Y" Then
           TraceLog ("Class=Labeler: OnBit_VacuumSense. Rotate Nosepiece=Y")
           
           m_objOutputs.SetBit intbit:=g_obitEERotate, blnValue:=True
           modAPI.SleepMSec 450
         End If
         TraceLog ("Class=Labeler: OnBit_VacuumSense. Check Guard Door")
        
        TraceLog ("Class=Labeler: OnBit_VacuumSense. Check Guard Door")
        m_objInputs.CheckGuardDoor
           
        TraceLog ("Class=Labeler: OnBit_VacuumSense->OnEvent_ApplyLabel")
           
        OnEvent_ApplyLabel
      End If
   End If
  TraceLog ("Class=Labeler: OnBit_VacuumSense: Normal Exit")
     
   Exit Sub
   
OnBit_VacuumSense_Error:

   ProccessError "OnBit_VacuumSense", m_strName, Err.Number, Err.Description

End Sub 'OnBit_VacuumSense

Private Sub OnEvent_ApplyLabel()
'This procedure performs the sequence of events that applies the label.

   TraceLog ("Class=Labeler: OnEvent_ApplyLabel")


   #If ccTrace Then
      Debug.Print m_strName & ".OnEvent_ApplyLabel -- " & "labST=" & m_staLabelerState & " -- retST=" & m_staReturnState
   #End If
   #If ccShip_Ver Then
      On Error GoTo OnEvent_ApplyLabele_Error
   #Else
      On Error GoTo 0
   #End If

   If m_staLabelerState = m_staMOVING Then
      
      m_staLabelerState = m_staAPPLYING
      
      With m_objOutputs
          TraceLog ("Class=Labeler: OnEvent_ApplyLabel->Extend Actuator")

         '  extend the Actuator
         .SetBit intbit:=g_obitActuator, blnValue:=True
         DoEvents

         '      Wait for actuator to fully extend
         TraceLog ("Class=Labeler: OnEvent_ApplyLabel: Wait for actuator to fully extend (time)=" + Str(m_lngAcuatorExtendTime) + "msec")
         modAPI.SleepMSec m_lngAcuatorExtendTime

         '  Disable vacuum
          TraceLog ("Class=Labeler: OnEvent_ApplyLabel->Turn Off Nose Piece Vacuum")
         
         .SetBit intbit:=g_obitVacuum, blnValue:=False
               
         '  turn on blow off
          TraceLog ("Class=Labeler: OnEvent_ApplyLabel->Turn On Blow off")
         
         .SetBit intbit:=g_obitBlowOff, blnValue:=True
         DoEvents
         
         '  Give a  little dwell time for the label to be placed.
         modAPI.SleepMSec m_lngApplyDwellTime
         
          '  turn off blow off
          TraceLog ("Class=Labeler: OnEvent_ApplyLabel->Turn Off Blow off")
         
         .SetBit intbit:=g_obitBlowOff, blnValue:=False
         
        '  Retract Actuator
          TraceLog ("Class=Labeler: OnEvent_ApplyLabel->Retract Actuator")
        
        .SetBit g_obitActuator, False
         
         If UCase(g_strRotateNosePiece) = "Y" And _
           Not (m_blnManualFeed) Then
            TraceLog ("Class=Labeler: OnEvent_ApplyLabel NosePiece Rotate Back to 0 theta")
           .SetBit intbit:=g_obitEERotate, blnValue:=True
         End If
        '   now issue the label complete event
        
        
           TraceLog ("Class=Labeler: OnEvent_ApplyLabel->m_evtLABEL_APPLIED")
        
        On_Event m_evtLABEL_APPLIED

      End With 'm_objOutputs
   End If
   TraceLog ("Class=Labeler: OnEvent_ApplyLabel: Normal Exit")

   Exit Sub
   
OnEvent_ApplyLabele_Error:

   ProccessError "OnEvent_ApplyLabel", m_strName, Err.Number, Err.Description

End Sub   'OnEvent_ApplyLabel


Private Sub OnEvent_NoVacuum(blnValue As Boolean)
'  This function processes the miss pickup of a label.
'  This show up when vacuum is not sensed.

   Static s_intMesgNumber As Integer
   TraceLog ("Class=Labeler: OnEvent_NoVacuum")
   
   
   #If ccShip_Ver Then
      On Error GoTo OnEvent_NoVacuum_Error
   #Else
      On Error GoTo 0
   #End If
   '    Turn off the timer
   m_objMainForm.tmrPickupTimeOut.Enabled = False
   
   ' Stop labeling process
   With m_objOutputs
      '  Disabale Blow off
      .SetBit g_obitAirBlast, False
    
      '  disable vacuum
      .SetBit g_obitVacuum, False
   End With 'm_objOutputs
   
   '  Label pick error so display messages and wait for it to go away.
   If blnValue Then
       If s_intMesgNumber = 0 Then
          s_intMesgNumber = m_objMainForm.MessageDisplay(strMsg:=LoadResString(resLABEL_PICKUP_ERROR))
       End If
       With m_objBeckon
          .TurnOnBeckon intLight:=g_intRED
        ' .BuzzerAcknowledge LoadResString(resMSG_NO_PICKUP_BUZZER)
       End With 'm_objBeckon
          
       MoveToQueueStack
       
       m_objMainForm.JobHolding True
       m_staLabelerState = m_staSUSPENDED
       m_staSpendState = m_staNO_VACUUM
   
   '    Do
          '  Releas the printer
   '       PrinterRelease
          '  now desplay and process instructions
          frmInstructions.InstructionsDisplay strFileName:=App.Path & "\" & m_strNO_LABEL
  '     Loop Until PrinterEngaged
       
       '  Now try to relabel the board
       m_staLabelerState = m_staRELABEL
      
   
       MoveToPrinter
       m_objBeckon.TurnOnBeckon intLight:=g_intGREEN
       s_intMesgNumber = m_objMainForm.MessageRemove(s_intMesgNumber)
       m_objMainForm.JobHolding True
       OnEvent_NextLabel
         
   Else
      s_intMesgNumber = m_objMainForm.MessageRemove(s_intMesgNumber)
      m_objBeckon.TurnOnBeckon intLight:=g_intGREEN
      MoveToPrinter
      m_objMainForm.JobHolding True
      m_staSpendState = m_staNOT_SPENDED
      m_staLabelerState = m_staReturnState
      frmInstructions.InstructionsRemove
   End If
    
   Exit Sub

OnEvent_NoVacuum_Error:

   ProccessError "OnEvent_NoVacuum", m_strName, Err.Number, Err.Description

End Sub 'OnEvent_NoVacuum

Private Sub OnEvent_NoMove(blnValue As Boolean)
   
   #If ccShip_Ver Then
      On Error GoTo OnEvent_NoMove_Error
   #Else
      On Error GoTo 0
   #End If
       
   Static s_intMesgNumber As Integer
   
   TraceLog ("Class=Labeler: OnEvent_NoMove")
   
   If Not blnValue Then
      s_intMesgNumber = m_objMainForm.MessageDisplay(LoadResString(resNO_MOVE))
      frmHistory.Message "Motion Error!"
      m_objMainForm.JobInterrupted True
      With m_objBeckon
         .TurnOnBeckon intLight:=g_intRED
        ' .BuzzerAcknowledge LoadResString(resMSG_NO_MOVE_BUZZER)
      End With 'm_objBeckon
      frmInstructions.InstructionsDisplay strFileName:=App.Path & "\" & m_strNO_MOVE
      ' air restored so restart the job in idel mode
      InitMotion
      s_intMesgNumber = m_objMainForm.MessageRemove(s_intMesgNumber)
      m_staLabelerState = m_staRUNNING
      RunStopJob
   End If
   
   Exit Sub

OnEvent_NoMove_Error:

   ProccessError "OnEvent_NoMove", m_strName, Err.Number, Err.Description
      
End Sub 'OnEvent_NoMove


Public Sub JobFaultCondition(intAction As Integer, strMsg As String)

   Dim strMessage As String
   Dim intResp As Integer
   
   
   strMessage = LoadResString(resJOB_FAULT_MESSAGE) & vbCrLf
   strMessage = strMessage & strMsg
   Select Case intAction
      Case m_intRESET
         strMessage = strMessage & LoadResString(resJOB_FALUT_JOB_ABORT) & vbCrLf
   End Select ' intAction
   
   If m_staLabelerState = m_staRUNNING Then
      MsgBox strMessage, vbOKOnly + vbCritical, LoadResString(resJOB_FAULT_CAPTION)
   End If
   
   modUtilities.Log "Fault", strMessage
   
   Select Case intAction
      Case m_intRESET
         RunStopJob
   End Select ' intAction

End Sub 'JobFaultCondition

Private Sub OnBit_Retracted()

   #If ccTrace Then
      Debug.Print m_strName & ".OnBit_Retracted -- " & "labST=" & m_staLabelerState & " -- retST=" & m_staReturnState
   #End If
   #If ccShip_Ver Then
      On Error GoTo OnBit_Retracted_Error
   #Else
      On Error GoTo 0
   #End If
   
   TraceLog ("Class=Labeler: OnBit_Retracted")
   
   If m_staLabelerState = m_staAPPLYING Then
      '  Assume label applyed
   End If
   
   Exit Sub

OnBit_Retracted_Error:

   ProccessError "OnBit_Retracted", m_strName, Err.Number, Err.Description
      
End Sub 'OnBit_Retracted



Private Sub OnEvent_NoRetract(blnValue As Boolean)
   
   #If ccShip_Ver Then
      On Error GoTo OnEvent_NoRetract_Error
   #Else
      On Error GoTo 0
   #End If
    
   m_objMainForm.tmrLabelApply.Enabled = False
      
   Static s_intMesgNumber As Integer
   
   TraceLog ("Class=Labeler: OnEvent_NoRetract")
   
   If Not blnValue Then
      s_intMesgNumber = m_objMainForm.MessageDisplay(LoadResString(resNO_RECTRACT))
      frmHistory.Message "Motion Error!"
      m_objMainForm.JobInterrupted True
      With m_objBeckon
         .TurnOnBeckon intLight:=g_intRED
        ' .BuzzerAcknowledge LoadResString(resMSG_NO_RECTRACT_BUZZER)
      End With 'm_objBeckon
      frmInstructions.InstructionsDisplay strFileName:=App.Path & "\" & m_strNO_RECTRACT
      ' air restored so restart the job in idel mode
      s_intMesgNumber = m_objMainForm.MessageRemove(s_intMesgNumber)
      m_staLabelerState = m_staRUNNING
      RunStopJob
   End If
   
   Exit Sub

OnEvent_NoRetract_Error:

   ProccessError "OnEvent_NoRetract", m_strName, Err.Number, Err.Description
      
End Sub 'OnEvent_NoRetract

Public Function JobRunning() As Boolean

   JobRunning = (m_staLabelerState = m_staRUNNING)
   
End Function 'JobRunning

Public Function JobIdle() As Boolean

   JobIdle = (m_staLabelerState = m_staIDLE)
   
End Function 'JobIdle

Public Function JobSuspended() As Boolean

   JobSuspended = (m_staLabelerState = m_staSUSPENDED)
   
End Function 'JobSuspended

Public Function JobNone() As Boolean

   JobNone = (m_staLabelerState = m_staNO_JOB)
   
End Function 'JobNone







Public Sub InitMotion()

   #If ccShip_Ver Then
      On Error GoTo InitMotion_Error
   #Else
      On Error GoTo 0
   #End If
   
   TraceLog ("Class=Labeler: InitMotion")
   
   If g_blnSimulator Then Exit Sub
   
   '  now init the move
   With m_objMove
      '  reset motion controller
      .Reset blnForce:=False
      DoEvents
      '  Home actuator
      .Home blnWait:=True
   End With 'm_objMove

   'now set the state to get ready for a job
   m_staLabelerState = m_staNO_JOB

   Exit Sub
   
InitMotion_Error:

   ProccessError "InitMotion", m_strName, Err.Number, Err.Description
   
End Sub 'InitMotion

Public Sub MoveToPrinter()

   #If ccShip_Ver Then
      On Error GoTo MoveToPrinter_Error
   #Else
      On Error GoTo 0
   #End If
   TraceLog ("Class=Labeler: MoveToPrinter")
   
   '  make sure the actuator is in piclkup position
   m_objOutputs.SetBit intbit:=g_obitEERotate, blnValue:=False
            
   ' Move to the printer location
   With m_objMove
     .Position = g_strPRINTER_POSITION
     .Move blnWait:=True
   End With 'm_objOutputs
   Exit Sub

MoveToPrinter_Error:

   ProccessError "MoveToPrinter", m_strName, Err.Number, Err.Description

End Sub 'MoveToPrinter

Public Sub MoveToQueueStack()

   #If ccShip_Ver Then
      On Error GoTo MoveToQueueStack_Error
   #Else
      On Error GoTo 0
   #End If
   TraceLog ("Class=Labeler: MoveToQueueStack")
   
   ' Move to the printer location
   With m_objMove
     .Position = g_strQUEUE_STACK
     .Move blnWait:=True
   End With 'g_strQUEUE_STACK
      
   Exit Sub

MoveToQueueStack_Error:

   ProccessError "MoveToQueueStack", m_strName, Err.Number, Err.Description

End Sub 'MoveToQueueStack


Public Sub CheckAirCtrlVolt()

   #If ccShip_Ver Then
      On Error GoTo CheckAirCtrlVolt_Error
   #Else
      On Error GoTo 0
   #End If
   TraceLog ("Class=Labeler: CheckAirCtrlVolt")
   
   With m_objInputs
   
       '  Check volts
      If Not (.Value(intbit:=g_ibitControlVolts)) Then
         
         g_blnLogError = True
         TraceLog ("Class=Labeler: CheckAirCtrlVolt Power Failed Check")
         
         Err.Raise g_errNO_CTRL_VOLTS, , LoadResString(resERR_NO_CTRL_VOLTS)
         End
      End If
      
      '  Check air
      If Not (.Value(intbit:=g_ibitAirPresser)) Then
         g_blnLogError = True
         TraceLog ("Class=Labeler: CheckAirCtrlVolt Power Failed Check")
         g_blnLogError = False
         
         Err.Raise g_errNO_AIR, , LoadResString(resERR_NO_AIR)
      End If
      
   End With 'm_objInputs
   
   Exit Sub

CheckAirCtrlVolt_Error:

   ProccessError "CheckAirCtrlVolt", m_strName, Err.Number, Err.Description

End Sub 'CheckAirCtrlVolt

Private Sub OnBit_MoveComplete()

   #If ccShip_Ver Then
      On Error GoTo OnBit_MoveComplete_Error
   #Else
      On Error GoTo 0
   #End If
   #If ccTrace Then
      Debug.Print m_strName & ".OnBit_MoveComplete -- " & "labST=" & m_staLabelerState & " -- retST=" & m_staReturnState
   #End If
   
   TraceLog ("Class=Labeler: OnBit_MoveComplete")
   
   If m_staLabelerState = m_staMOVING Then
      On_Event m_evtAPPLY_LABEL
   ElseIf m_staLabelerState = m_staSCANNING Then
      m_blnNextLabel = True
      On_Event m_evtLABELING_COMPLETE
   ElseIf m_staLabelerState = m_staRELABEL Then
      m_blnNextLabel = False
      m_staLabelerState = m_staReturnState
      On_Event m_evtNEXT_LABEL
   End If
   
   Exit Sub

OnBit_MoveComplete_Error:

   ProccessError "OnBit_MoveComplete", m_strName, Err.Number, Err.Description


End Sub 'OnBit_MoveComplete

Private Function GetNextlabel() As String
'  this procedure gets the next label and stores
'  it for comparison to scaned label
'  then passes it back

Dim clsStopWatch As CStopWatch
Dim FNum As Integer
Dim blnCheck As Boolean
Dim strPass As String

   Set clsStopWatch = New CStopWatch
   strPass = "True"
   blnCheck = False

   #If ccShip_Ver Then
      On Error GoTo GetNextlabel_Error
   #Else
      On Error GoTo 0
   #End If
   TraceLog ("Class=Labeler: GetNextlabel")
   
   If m_blnNextLabel And (Not m_blnManualFeed) Then
      m_lngSequenceNumber = m_lngSequenceNumber + 1
          
        TraceLog ("Class=GetNextlabel: NextLabel=true, Manual Feed= false")
        TraceLog ("Class=GetNextlabel: Next Sequence Number = " + Str(m_lngSequenceNumber))
          
       If g_intFlavor <> Val(frmOpenJob.txbFlavor.Text) Then
       
       
       End If
       
       
       m_strLabelDataPrinted = _
         Trim(Str(m_lngSequenceNumber)) + Trim(Format(frmOpenJob.txbFlavor.Text, "00"))
   ElseIf (m_blnManualFeed) Then
      With m_objMainForm
'         m_lngSequenceNumber = .CurrentSeqNumber
 '         m_lngSequenceNumber = "9999999"
      End With 'm_objMainForm
       
       
        TraceLog ("Class=GetNextlabel: Manual Feed= True")
        TraceLog ("Class=GetNextlabel: Sequence Number = " + Str(m_lngSequenceNumber))
       
       
       m_strLabelDataPrinted = _
         "9999999" & _
         Format(frmOpenJob.txbFlavor.Text, "00")
   
   Else
   
       m_lngSequenceNumber = m_lngSequenceNumber + 1
       TraceLog ("Class=GetNextlabel: NextLabel=false, Manual Feed= false")
       TraceLog ("Class=GetNextlabel: Sequence Number = " + Str(m_lngSequenceNumber))
          
          
       If g_intFlavor <> Val(frmOpenJob.txbFlavor.Text) Then
       
       
       End If
       
       
       m_strLabelDataPrinted = _
         Trim(Str(m_lngSequenceNumber)) + Trim(Format(frmOpenJob.txbFlavor.Text, "00"))
   
   
   
   
   End If
    
   TraceLog ("Class=GetNextlabel= " + Str(m_strLabelDataPrinted))
   
   If m_blnBAD_SerialDB_Found Then
        If (IsPreSerialNumberChk And (Not m_blnManualFeed)) Then
            
            clsStopWatch.Reset
            
            If Not PreScanCheck(m_strLabelDataPrinted) Then
               blnCheck = True
               strPass = "Fail"
            End If
        
            If g_blnSimulator Then
              FNum = FreeFile
              Open "c:\testres.txt" For Append As FNum
              Print #FNum, m_strLabelDataPrinted & "," & "PreCheck = " + strPass, "Process Time = " + Str(clsStopWatch.Elapsed)
              Close FNum
            End If
               
            If blnCheck Then
              GetNextlabel
            End If
          End If
   End If
   
   
   
   
   If (Not m_blnManualFeed) Then
      UpdateSerialNumber
   End If
   
   GetNextlabel = m_strLabelDataPrinted
   
   Exit Function

GetNextlabel_Error:

   ProccessError "GetNextlabel", m_strName, Err.Number, Err.Description

End Function 'GetNextlabel
Private Function GetBottomScannedLabel() As String

Dim strBuffer As String
Dim strFlavorChk As String
   
   
   
   If m_blnNextLabel And (Not m_blnManualFeed) Then
          
        TraceLog ("CGetBottomScannedLabel: GetBottomScannedLabel=true, Manual Feed= false")
        TraceLog ("GetBottomScannedLabel: Scanned Value = " + m_strBottomScannedLabel)
          
         ' retrieve line number + serial number
         If (m_strBottomScannedLabel <> "") Then
            strBuffer = Mid(m_strBottomScannedLabel, 1, 7)
           ' add board flavor
            'Perform Flavor Check
            If g_strFlavorConstant Then
               strFlavorChk = Mid(m_strBottomScannedLabel, 8, 2)
               If (strFlavorChk <> Trim(Format(frmOpenJob.txbBBoardFlavor.Text, "00"))) Then
                   
                   m_objMainForm.JobInterrupted
                   With m_objBeckon
                    .TurnOnBeckon intLight:=g_intRED
                    ' .BuzzerAcknowledge LoadResString(resMSG_MISS_SCAN_BUZZER)
                   End With 'm_objBeckon
        
                   MsgBox ("Bottom Board Flavor [" + strFlavorChk + "]" + _
                           "Does Not Match With Expected Bottom Board's Flavor[" + _
                           Format(frmOpenJob.txbBBoardFlavor.Text, "00") + "]")
                   Exit Function
               End If
               strBuffer = strBuffer + Trim(Format(frmOpenJob.txbFlavor.Text, "00"))
               
            Else
               strBuffer = strBuffer + Trim(Format(frmOpenJob.txbBBoardFlavor.Text, "00"))
            
            End If
            
            
         Else
            MsgBox ("No Bottom Code Read Value")
            GetBottomScannedLabel = ""
            Exit Function
         End If
   ElseIf (m_blnManualFeed) Then
        TraceLog ("Class=GetNextlabel: Manual Feed= True")
        TraceLog ("Class=GetNextlabel: Sequence Number = " + Str(m_lngSequenceNumber))
        strBuffer = "9999999" + Format(frmOpenJob.txbFlavor.Text, "00")
   
   Else
        ' retrieve line number + serial number
        strBuffer = Mid(m_strBottomScannedLabel, 1, 7)
        ' add board flavor
        strBuffer = strBuffer + Trim(Format(frmOpenJob.txbFlavor.Text, "00"))
   
   End If
   
  TraceLog ("GetBottomScannedLabel: Scanned Value = " + strBuffer)
   
   GetBottomScannedLabel = strBuffer
   m_strLabelDataPrinted = strBuffer  ' save to verify the scan value

End Function

Public Sub PrinterRelease()

   m_objOutputs.SetBit intbit:=g_obitPtrRelese, blnValue:=False
   
End Sub 'PrinterRelease

Public Function PrinterEngaged() As Boolean

    PrinterEngaged = m_objInputs.Value(intbit:=g_ibitPrinterEngaged)
   
End Function 'PrinterEngaged

Public Sub PrinterEngage()

   #If ccShip_Ver Then
      On Error GoTo PrinterEngageCheck_Error
   #Else
      On Error GoTo 0
   #End If

   Dim staSaveState As String
   
   staSaveState = m_staLabelerState
   m_staLabelerState = m_staNO_PRINTER
   
   Do Until PrinterEngaged()
      frmInstructions.InstructionsDisplay strFileName:=App.Path & "\" & m_strNO_PRITNER
   Loop
   
   m_objOutputs.SetBit intbit:=g_obitPtrRelese, blnValue:=True
   
   m_staLabelerState = staSaveState
   
   Exit Sub

PrinterEngageCheck_Error:

   ProccessError "PrinterEngageCheck", m_strName, Err.Number, Err.Description
   
End Sub 'PrinterEngageCheck


Public Function InitJob(strJobID As String, strName As String, _
                        strPartNumber As String, strLocationCode As String, _
                        strFormatName As String, strTemplatePath As String _
                        ) As Boolean
'  This function initializes the job data and the printer date.

   Dim blnStatus As Boolean
   
   #If ccShip_Ver Then
      On Error GoTo InitJob_Error
   #Else
      On Error GoTo 0
   #End If
   
   blnStatus = True
   
   '  Set current job info
   With m_udtCurrentJob
      .strJobID = strJobID
      .strName = strName
      .strPartNumber = strPartNumber
      .strLocationCode = strLocationCode
      .strFormatName = strFormatName
      .strTemplatePath = strTemplatePath
   End With 'm_udtCurrentJob
   
  
   '  set up printer
   frmMessage.MessageDisplay LoadResString(resLOADING_PRINTER_DATA)
   With m_objPrinter
      If strTemplatePath = "" Then
         blnStatus = blnStatus And .GetTemplate(strPathFileName:=App.Path & "\" & strFormatName)
      Else
         blnStatus = blnStatus And .GetTemplate(strPathFileName:=strTemplatePath & "\" & strFormatName)
      End If
   End With 'm_objPrinter
   frmMessage.MessageRemove
       
   With m_objMainForm
       If blnStatus Then
          
         .labTextJobName.Caption = m_udtCurrentJob.strName
         .labTextPartNumber.Caption = m_udtCurrentJob.strPartNumber
       Else
         .m_blnLastError = True
         .ClearLabelFields
       End If
   End With 'm_objMainForm
        
       
   '  Set panel count to 0 assume new job
   m_lngPanelQuintityCount = 0
   
   InitJob = blnStatus
   
   Exit Function

InitJob_Error:

   ProccessError "InitJob", m_strName, Err.Number, Err.Description

End Function 'InitJob

Private Sub UpdateLabelLog()
   
   Dim strBuffer As String
   Dim hFile As Integer
   Dim intNumTrys As Integer
   
   #If ccShip_Ver Then
      On Error GoTo UpdateLabelLog_Error
   #Else
      On Error GoTo 0
   #End If
   
   
   If m_strLogPathFileName <> "" Then
   
      hFile = FreeFile
      If hFile = 0 Then
         Err.Raise g_errNO_FILE_HANDAL, , LoadResString(resERR_PRT_TPLATE_NO_HANDAL)
      Else
         Open m_strLogPathFileName For Append Access Write As #hFile
         With m_udtCurrentJob
            strBuffer = .strName & m_chrLogFileDelim
            strBuffer = strBuffer & .strPartNumber & m_chrLogFileDelim
            strBuffer = strBuffer & m_objMainForm.labTextScanned.Caption & m_chrLogFileDelim
            strBuffer = strBuffer & Format(Now, "General Date")
         End With 'm_udtCurrentJob
         Print #hFile, strBuffer
      End If
      
      Close #hFile
      
      Exit Sub
         
   End If
         
UpdateLabelLog_Error:
   
   Dim intErrNum As Integer
   
   '  Check to see if some one is read it.
   intErrNum = Err.Number
   If (intErrNum = 55) And intNumTrys <= 5 Then
      modAPI.SleepMSec (250)
      intNumTrys = intNumTrys + 1
      Resume
   End If
      
   ProccessError "UpdateLabelLog", m_strName, Err.Number, Err.Description
   
End Sub 'UpdateLabelLog

Public Function GuardDoorsClosed() As Boolean
   
   #If ccShip_Ver Then
      On Error GoTo GuardDoorsClosed_Error
   #Else
      On Error GoTo 0
   #End If
   
   TraceLog ("Class=Labeler: GuardDoorsClosed")
   
'   m_staLabelerState = m_staIDLE
   With m_objInputs
      .ScanNow
      GuardDoorsClosed = .Value(intbit:=g_ibitGuardDoor)
   End With 'm_objInputs
   
   Exit Function

GuardDoorsClosed_Error:

   ProccessError "GuardDoorsClosed", m_strName, Err.Number, Err.Description
   
End Function 'GuardDoorsClosed

Public Function HaveAir() As Boolean
   m_objInputs.ScanNow
   HaveAir = m_objInputs.Value(intbit:=g_ibitAirPresser)
   
End Function 'HaveAir
Public Sub StopPin_1()
   #If ccShip_Ver Then
      On Error GoTo StopPin_1
   #Else
      On Error GoTo 0
   #End If
   
   TraceLog ("Class=Labeler: StopPin_1")
   
   m_objOutputs.SetBit intbit:=28, blnValue:=True
   m_objOutputs.SetBit intbit:=29, blnValue:=False
   Exit Sub

StopPin_1:

   ProccessError "StopPin_1", m_strName, Err.Number, Err.Description

End Sub

Public Sub StopPin_2()
   #If ccShip_Ver Then
      On Error GoTo StopPin_2
   #Else
      On Error GoTo 0
   #End If
   TraceLog ("Class=Labeler: StopPin_2")
   
   m_objOutputs.SetBit intbit:=28, blnValue:=False
   m_objOutputs.SetBit intbit:=29, blnValue:=True
   
   Exit Sub

StopPin_2:

   ProccessError "StopPin_2", m_strName, Err.Number, Err.Description

End Sub


Public Sub UpdateSerialNumber()
Dim db As Database
Dim rs As Recordset
Dim strSQLCmd As String
Dim strJobName As String
 


On Error GoTo UpDateSerialNumber_Error:
 
  strJobName = frmMain.labTextJobName
  strSQLCmd = "select * from tblJobFile where txtJobsName = '" + strJobName + "'"
 
 Set db = OpenDatabase(modMain.JobDatabaseName)
 Set rs = db.OpenRecordset(strSQLCmd)
 
 
 If (Not rs.EOF) Then
   rs.Edit
 
   rs.Fields("lngLastSeqNumber") = m_lngSequenceNumber
   rs.Update
 End If

 rs.Close
 db.Close
 
Exit Sub

UpDateSerialNumber_Error:

   ProccessError "UpdateSerialNumber", m_strName, Err.Number, Err.Description


End Sub


Public Sub ActivateBottomScanner()

      
'      blnGoodScan =
   ScannedBottomLabel = ""
    While (Not m_objBottomScanner.ReadBottomBarCode)
     g_blnBottomLabelScanned = False
     DoEvents
   Wend
   If (g_blnSimulator) Then
     m_objBottomScanner.m_strBarCode = "1234567890"
   End If
   
   If (m_objBottomScanner.m_strBarCode <> "") Then
      ScannedBottomLabel = m_objBottomScanner.m_strBarCode
   End If
   
   
End Sub


Property Let ScannedBottomLabel(strScannedLabel As String)
    
    m_strBottomScannedLabel = strScannedLabel
   
    
    If g_blnSimulator Then
       m_strBottomScannedLabel = "1234567890"
    End If
    
End Property

Property Get ScannedBottomLabel() As String
      ScannedBottomLabel = m_strBottomScannedLabel
End Property

Public Function IsBottomLabelRead() As Boolean
   
   IsBottomLabelRead = False
   If (ScannedBottomLabel <> "") Then
     IsBottomLabelRead = True
   End If
   
   
End Function


Public Sub DeActivateBottomScanner()
      
    m_objBottomScanner.TriggerOff
   
End Sub

Private Function PreScanCheck(strNewSerialNumber As String) As Boolean
 
    
    Dim iSeed As Long
    Dim iBoard As Integer
    Dim hSeed As String
    Dim bBoard As String
    Dim hBoard As String
    Dim iZeros As Integer
    Dim hNumber As String
    Dim FirstBad As String
    Dim SecondBad As String
    Dim i As Integer
    Dim j As Integer
    Dim iMB As Long
    Dim iDB As Integer
    Dim sSecond As String
    Dim sFirst As String
    Dim iChecksum As Integer
    Dim sChecksum As String
    Dim FNum As Integer
    Dim iNewSeed As Long
    Dim iCount As Long
    Dim nMaxCount As Long
    
    On Error GoTo Process_Error
                
    
    iCount = 0
    
    
    
     For iDB = 1 To 20
         
         iSeed = Val(strNewSerialNumber) * 2
         iBoard = iDB
 
         If iBoard > 15 Then
              iSeed = iSeed + 1
              iBoard = iBoard - 16
        End If

         
         hSeed = Hex(iSeed)
         hBoard = Hex(iBoard)
         
         hNumber = hSeed & hBoard
         
         iZeros = 10 - Len(hNumber)
         
         For i = 1 To iZeros
             hNumber = 0 & hNumber
         Next i
             
         sFirst = Mid(hNumber, 1, 2)
         sSecond = Mid(hNumber, 3, 2)
         sChecksum = Hex(Val("&H" & sFirst) Xor Val("&H" & sSecond))
         
         For i = 1 To 3
             sSecond = Mid(hNumber, (i * 2) + 3, 2)
             sChecksum = Hex(Val("&H" & sChecksum) Xor Val("&H" & sSecond))
         Next i
         
         sChecksum = Hex(Val("&H55") Xor Val("&H" & sChecksum))
         
         hNumber = hNumber & sChecksum
             
         For i = 0 To 4
             sFirst = Mid(hNumber, (i * 2) + 1, 2)
             sSecond = Mid(hNumber, (i * 2) + 3, 2)
             For j = 1 To m_nNoOfBadSerialNumbers
                 FirstBad = sBadNumbers(j, 1)
                 SecondBad = sBadNumbers(j, 2)
                 If ((sFirst = FirstBad) And (sSecond = SecondBad)) Then
                    
                    If g_blnSimulator Then
                      FNum = FreeFile
                      Open "c:\BadSN4.txt" For Append As FNum
                      Print #FNum, strNewSerialNumber, hNumber & "," & Str$(iNewSeed + iMB) & "," & Str$(iDB) & "," & sFirst & sSecond
                      Close FNum
                    End If
                    
                    PreScanCheck = False
                    Exit Function
                 End If
             Next j
         Next i
     Next iDB
    
    PreScanCheck = True
    
    Exit Function
    
Process_Error:

   ProccessError "PreScanCheck", "Error=", Err.Number, Err.Description

    
End Function


Public Property Get IsPreSerialNumberChk() As Boolean

 IsPreSerialNumberChk = m_blnPreCheckSerialNumbers

End Property

Public Property Let IsPreSerialNumberChk(blnCheckSerialNumber As Boolean)

   m_blnPreCheckSerialNumbers = blnCheckSerialNumber

End Property

