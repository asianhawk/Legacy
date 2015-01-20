Attribute VB_Name = "modMain"
'************************************************************************
'*           Computype, Inc.
'*       NextStep Automation Group
'*
'*     © Copywrite 1997 Computype, Inc.
'*
'*        2-Axis Label Applicator
'*           Control software
'*             Main module
'*
'*
'*    Customer: Ford Markham
'*
'*
'*
'*    Date of origin: 1/21/97
'*    Original author: Michael D. Reed
'*
'* Module purpose:
'*    This module porvides the entery point into the
'*    2-Axis label Applicator upon start up.  It also contains
'*    any global constants, variables.
'*
'************************************************************************
Option Explicit

'************************************************************************
'  Public stuff
'  global constents
'  Array of bit values
Public g_JRFlavor
Public Const m_intFIRST_LSB = 0
Public Const m_intLAST_LSB = 15
Public Const m_intFIRST_MSB = 16
Public Const m_intLAST_MSB = 31

Public ma_blnBitValue(m_intFIRST_LSB To m_intLAST_MSB) As Boolean
Public ma_intSignalType(m_intFIRST_LSB To m_intLAST_MSB) As Integer
Public ma_lngStrobe(m_intFIRST_LSB To m_intLAST_MSB) As Long

Public Const g_strJOB_STUFF = "JobStuff"
Public Const m_strJobsDBName = "Jobs.mdb"
'added filename for processing INI files
Public Const m_strLabelerINIFile = "Labeler.ini"




Public Const g_strDB_EXT = "mdb"


' added Dec 14/00 for bottom scanning
Public g_blnIs2Sided As Boolean
Public g_blnBottomLabelScanned As Boolean
Public g_strBottomLabelScanned As String
Public g_blnNotUseBottomScanner As Boolean
Public g_blnDisplayScannerData As Boolean
Public g_strFlavorConstant As Boolean




'  Used to indicate Labeler is ready to start
Public g_blnLabelerReady As Boolean


'Used to describe job properties
Public g_strRotateNosePiece As String
Public g_strDisable_Scanner As String

Public g_strStopPin_1 As String
Public g_strStopPin_2 As String

Public g_intFlavor As Integer
Public g_intHolePattern As Integer

'Need to verify user's login id
Public LoginSucceeded As Boolean

'  Used by the about form.
Public g_strLabelerVersion As String
Public g_strLabelPrintVersion As String
Public g_strMicroScanerVersion As String
Public g_strDigitalOutpusVersion As String
Public g_strDigitalInpusVersion As String
Public g_strMoveVersion  As String


Public g_blnBoardRemove As Boolean


'  cross module events.
Public Const g_evtMANUAL_FEED = 100
Public Const g_evtTEST_LABEL = 101
Public Const g_evtLABEL_PICKUP_TIMEOUT = 102
Public Const g_evtARM_MOVE_TIMEOUT = 103
Public Const g_evtARM_RETRACT_TIMEOUT = 104
Public Const g_evtLABELED_SCANNED = 105

'************************************************************************
'  Private stuff
Private m_strName As String

'  local constents
Private Const m_strJOB_DB_NAME = "JobDatabaseName"
Private Const m_strJOB_DB_FILE = "JobDatabaseFile"

'  need this refrence to reset the motion controller
Private m_objMove As Object
Public m_objLabeler As Object
Private m_objDigitalOutpus As Object

'need public pointers to key objects
Public m_objscanner As SICKScanner
Public m_objBottomScanner As SICKScanner

Public m_objDIO_Input As clsDigitalInput
Public m_objDIO_Output As clsDigitalOutput
Public m_objDIO_Common As clsDigitalCommon

'  local data
Private m_dbConfgurationDataBaseName As String

Private m_dbJobsDataBaseName As String
Private m_strJobDatabaseFile As String
Private m_dbJobFileDataBaseName As String
Private m_strGetSerialPortConfiguration As String

Private m_tblLabelerConfiguration As String
Private m_tblGetDigitalInputConfig As String
Private m_tblGetDigitalOutputConfig As String

Private m_strInitalJob As String

Private Sub SetDefaults()
      
   m_dbConfgurationDataBaseName = App.Path & "\Labeler.mdb"
   m_dbJobsDataBaseName = App.Path & "\" & m_strJobsDBName
   
   
   m_tblLabelerConfiguration = "tblLabelerConfiguration"
   m_tblGetDigitalInputConfig = "tblDigitalInput"
   m_tblGetDigitalOutputConfig = "tblDigitalOutput"

   m_strGetSerialPortConfiguration = "pqrSerialPortByDeviceName"
   
   g_blnTest = False
   g_blnLog = False
   
End Sub 'SetDefaults


Public Sub Main()

   Dim objDigitalInputs As clsDigitalInput
   Dim objDigitalOutpus As clsDigitalOutput
   Dim objLabelPrint As clsLabelPrint
'   Dim objMicroscanCtrl As clsMicroscan
   Dim objScanner As SICKScanner
   Dim objBottomScanner As SICKScanner
   
   Dim objLabeler As clsLabeler
   Dim objMove As clsMove
   Dim nResult As Integer
   nResult = 0
   #If ccShip_Ver Then  'Set up error handler for shiped version
      On Error GoTo Main_Error
   #Else
      On Error GoTo 0
   #End If
   
   m_strName = "modMain"
   
   '  Set the labeler not ready flage
   g_blnLabelerReady = False
   g_blnDisplayScannerData = False
   
   frmSplash.Show
   
   SetDefaults
   
   ProcessProfile
   
   ProcessCommanedLine
   
   If Not ProcessINI Then
     nResult = MsgBox("The Labeler INI File Is Corrupted. The System Will Use Default Values. Proceed ?", vbOKCancel, "Labeler Profile Initialization Error")
     If (nResult <> vbOK) Then
        End
     End If
   End If
   
   '  If log file is called for open it
   If g_blnLog Then
      Log "Main", "File open and program start"
   End If
   
   '  load the spiclized message box.
   frmMessage.Hide
   
   '  load instrunctions form
   frmInstructions.Hide
   
   '  load the history window
   modUtilities.SetHistoryMonitorForm frmHistory
   
   
   TraceLog ("Labeler App. Started")

      
   '  Initialize Digitial I/O
   '  Do the digitial I/O first needed for other subsystems
   frmSplash.PanelDigital LoadResString(resMSG_INIT_DIG_IO)
   frmHistory.Message LoadResString(resMSG_INIT_DIG_IO)
   '  This function initilize both the input and output classes.
   If InitDigitalIO(r_objOutput:=objDigitalOutpus, _
                    r_objInput:=objDigitalInputs) _
   Then
      g_strDigitalOutpusVersion = LoadResString(resLAB_DIG_OUT_VERSION) & objDigitalOutpus.Version
      g_strDigitalInpusVersion = LoadResString(resLAB_DIG_IN_VERSION) & objDigitalInputs.Version
      frmHistory.Message g_strDigitalOutpusVersion
      frmHistory.Message g_strDigitalInpusVersion
      frmSplash.PanelDigital LoadResString(resMSG_INIT_DIG_OK)
      frmHistory.Message LoadResString(resMSG_INIT_DIG_OK)
   Else
      frmSplash.InitError LoadResString(resERR_DIG_NO_INIT)
      frmHistory.Message LoadResString(resERR_DIG_NO_INIT)
      ExitEnd
   End If
   Set m_objDIO_Input = objDigitalInputs
   Set m_objDIO_Output = objDigitalOutpus
   
   
   
   '  Initialize the move subsystem
   If (g_blnOpenTraceLogFile) Then TraceLog ("Initializing Motion Contoller")
   
   frmSplash.PanelMotion LoadResString(resMSG_INIT_MOVE)
   frmHistory.Message LoadResString(resMSG_INIT_MOVE)
   Set objMove = New clsMove
   If objMove.Initialize(objDigitalInput:=objDigitalInputs, _
                      objDigitalOutput:=objDigitalOutpus) _
   Then
       g_strMoveVersion = LoadResString(resLAB_MICROSCAN_ROM) & objMove.Version
      frmHistory.Message g_strMoveVersion
      frmSplash.PanelMotion LoadResString(resMSG_INIT_MOVE_OK)
      frmHistory.Message LoadResString(resMSG_INIT_MOVE_OK)
   Else
      frmSplash.InitError LoadResString(resERR_MOVE_NO_INIT)
      frmHistory.Message LoadResString(resERR_MOVE_NO_INIT)
      ExitEnd
   End If
   
   '  Initialize TOP Scanner
  If (g_blnOpenTraceLogFile) Then TraceLog ("Initializing TOP Microscaner")
   
  frmSplash.PanelScanner " SICK Scanner Initializing", "Top"
  frmHistory.Message LoadResString(resMSG_INIT_SCANNER)
  Set objScanner = New SICKScanner
  objScanner.InitForm
        
    
  Set objScanner.objScannerPort = frmScanner.MSComm1
  objScanner.SetScannerPort_Settings "2400,n,8,1"
  objScanner.SetScannerPort_ComPortID 6
  objScanner.objScannerPort.InputMode = comInputModeText
  objScanner.InitScanner 9, 3, 1
  Set m_objscanner = objScanner
    
  objScanner.frmScannerView.Hide

  frmHistory.Message g_strMicroScanerVersion
  frmSplash.PanelScanner " SICK Scanner Initialized OK", "Top"
  frmHistory.Message LoadResString(resMSG_INIT_SCANNER_OK)
   
       
   '  Initialize BOTTOM Scanner
  If (Not g_blnNotUseBottomScanner) Then
  
    If (g_blnOpenTraceLogFile) Then TraceLog ("Initializing Bottom Microscaner")
     
    frmHistory.Message LoadResString(resMSG_INIT_SCANNER)
    Set objBottomScanner = New SICKScanner
         
      
    Set objBottomScanner.objScannerPort = frmScanner.MSComm2
    objBottomScanner.SetScannerPort_Settings "2400,n,8,1"
    If g_blnSimulator Then
       objBottomScanner.SetScannerPort_ComPortID 1
    Else
       objBottomScanner.SetScannerPort_ComPortID 8
    End If
    objBottomScanner.objScannerPort.InputMode = comInputModeText
    If (Not objBottomScanner.InitBottomScanner(9, 3, 1)) Then
        frmSplash.InitError "Error Opening Bottom Scanner"
        frmHistory.Message "Error Opening Bottom SCanner"
        
        ExitEnd
    End If
    
    
    Set m_objBottomScanner = objBottomScanner
      
  End If
  frmHistory.Message g_strMicroScanerVersion
  frmHistory.Message LoadResString(resMSG_INIT_SCANNER_OK)
   
   
   
   '  Initialize the Printer class
   If (g_blnOpenTraceLogFile) Then TraceLog ("Initializing Printer")
   
   frmSplash.PanelPrint LoadResString(resMSG_INIT_PRINT)
   frmHistory.Message LoadResString(resMSG_INIT_PRINT)
   Set objLabelPrint = New clsLabelPrint
   If objLabelPrint.InitStatus Then
      g_strLabelPrintVersion = LoadResString(resLAB_PRINT_VERSION) & objLabelPrint.Version
      frmHistory.Message g_strLabelPrintVersion
      frmSplash.PanelPrint LoadResString(resMSG_INIT_PRINT_OK)
      frmHistory.Message LoadResString(resMSG_INIT_PRINT_OK)
   Else
      frmSplash.InitError LoadResString(resERR_PRINTER_NO_INIT)
       frmHistory.Message LoadResString(resERR_PRINTER_NO_INIT)
      ExitEnd
   End If
   
   '  Init main labeler class
   If (g_blnOpenTraceLogFile) Then TraceLog ("Initializing Labeler Driver")
   frmSplash.PanelLabeler LoadResString(resMSG_INIT_LABELER)
   frmHistory.Message LoadResString(resMSG_INIT_LABELER)
   Set objLabeler = New clsLabeler
   objLabeler.Initialize objScanner:=objScanner, _
                         objBottomScanner:=objBottomScanner, _
                           objOutput:=objDigitalOutpus, _
                           objInput:=objDigitalInputs, _
                           objPrinter:=objLabelPrint, _
                           objMove:=objMove
                           
   If objLabeler.InitStatus Then
      g_strLabelerVersion = "3.00.00"
      frmHistory.Message g_strLabelerVersion
      frmSplash.PanelLabeler LoadResString(resMSG_INIT_LABELER_OK)
      frmHistory.Message LoadResString(resMSG_INIT_LABELER_OK)
   Else
      frmSplash.InitError LoadResString(resERR_LABELER_NO_INIT)
      frmHistory.Message LoadResString(resERR_LABELER_NO_INIT)
      ExitEnd
   End If
   
   '  Now load the main form
   frmMain.Hide
   
   TraceLog ("Initializing Main Screen")
   
   If frmMain.Initialize(objLabeler:=objLabeler, _
                         objOutput:=objDigitalOutpus, _
                         objInput:=objDigitalInputs, _
                         objPrinter:=objLabelPrint, _
                         objMotion:=objMove) _
   Then
      frmHistory.Message "------------------"
      frmMain.Show
      Unload frmSplash
      frmMain.InitTimers ' init timers on main form
      
      '  start the input scan
      If (g_blnOpenTraceLogFile) Then TraceLog ("Scan Input Ports")
      
      objDigitalInputs.ScanNow
      
      '  now check for error condigions
      With objLabeler
          If (g_blnOpenTraceLogFile) Then TraceLog ("Checking Air and Power")
         
         .CheckAirCtrlVolt  '  Now see if voltage and air are their
         '  are the guard doors open ...
          If (g_blnOpenTraceLogFile) Then TraceLog ("Checking Guard Doors")
         
         If Not .GuardDoorsClosed Then
            .On_Event g_ibitGuardDoor, False
         End If
'         .PrinterEngage '  is printer ready ...
         .InitMotion ' init motion
      End With 'objLabeler
      
      '  Save some refrences to use on exit
      Set m_objLabeler = objLabeler '  save refrence to labeler
      Set m_objMove = objMove '  Save the refrence to move subsystem
      Set m_objDigitalOutpus = objDigitalOutpus '  save the reference to digital oputputs
      '  force the current dir to app dir
      
      If (g_blnOpenTraceLogFile) Then TraceLog ("Change Systen Path to App Path")
      
      ChDir App.Path
      
      If (g_blnOpenTraceLogFile) Then TraceLog ("Get Job Data")
      
      If m_strInitalJob <> "" Then
         frmMain.GetJobData varInitalJob:=m_strInitalJob
      End If
   Else
      frmSplash.InitError "Main form failed to initialize."
      If (g_blnOpenTraceLogFile) Then TraceLog ("Main form failed to initialize.")
      
      ExitEnd
   End If
   
   '  Set the labeler not ready flage
   g_blnLabelerReady = True
   g_blnBoardRemove = False
   Exit Sub
   
Main_Error:

   ProccessError "Main", "modMain", Err.Number, Err.Description
   ExitEnd
   
End Sub 'Main

Public Function InitDigitalIO(ByRef r_objOutput As Object, ByRef r_objInput As Object) As Boolean

   Dim dbLabelerDataBase As Database
   Dim snpDigitalIO As Recordset
   Dim objCommonDriver As Object
   Dim a_strNames(0 To 31) As String
   Dim a_intSignalType(0 To 31) As Integer
   Dim a_lngStrobe(0 To 31) As Long
   Dim a_blnInitialValue(0 To 31) As Boolean
   Dim strSignal As String
   Dim intbit As Integer

   #If ccShip_Ver Then
      On Error GoTo InitDigitalIO_Error
   #Else
      On Error GoTo 0
   #End If
   
   InitDigitalIO = False
   
   ' ******************************
   '  get data on digitial IO prots
   Set dbLabelerDataBase = Workspaces(0).OpenDatabase(m_dbConfgurationDataBaseName)
   
   ' ******************************
   '  Now set up the dirver interface
   Set objCommonDriver = New clsDigitalCommon
   If objCommonDriver.Initialize( _
                     objConfgDB:=dbLabelerDataBase, _
                     strConfigTable:=m_tblLabelerConfiguration) _
   Then
      '  Now Initilize the input and outputs
      
      ' ******************************
      ' ******************************
      '  Now get the input bit definitions
      Set snpDigitalIO = dbLabelerDataBase.OpenRecordset(m_tblGetDigitalInputConfig, dbOpenSnapshot)
      
      '  Now process each input bits
      Do While Not snpDigitalIO.EOF
         intbit = snpDigitalIO![keyBit]
            
         strSignal = snpDigitalIO![txtSoftwareLabel]
         a_strNames(intbit) = snpDigitalIO![txtSignalName]
         a_intSignalType(intbit) = snpDigitalIO![intSignalType]
         
              
         Select Case strSignal
               Case g_inpGUARD_DOOR:         g_ibitGuardDoor = intbit
               Case g_inpLOW_LABEL:          g_ibitLowLabel = intbit
               Case g_inpPART_PRESENT:       g_ibitPartPresent = intbit
               Case g_inpPRINTER_ENGAGED:    g_ibitPrinterEngaged = intbit
               Case g_inpVACUUM_SENSE:       g_ibitVacuumSense = intbit
               Case g_inpAIR_PRESSER:        g_ibitAirPresser = intbit
               Case g_inpRETRACTED:          g_ibitRetracted = intbit
               Case g_inpEND_ROTATE_0_DEG:   g_ibitRotate0 = intbit
               Case g_inpEND_ROTATE_90_DEG:  g_ibitRotate90 = intbit
               Case g_inpSA_ALARM:           g_ibitSA_Alarm = intbit
               Case g_inpSA_READY:           g_ibitSAReady = intbit
               Case g_inpPOSITIONING_END:    g_ibitPositioningEnd = intbit
               Case g_intCONTROL_VOLTAGE:    g_ibitControlVolts = intbit
               Case g_intE_STOP:             g_ibitEStop = intbit
               Case Else
                  Err.Raise g_errINPUT_BIT_NOT_FOUND, , LoadResString(resERR_INPUT_BIT_NOT_FOUND)
         End Select 'strSignal
         
         snpDigitalIO.MoveNext
      Loop 'While Not snpDigitalIO.EOF
      
      '  Start a new instence of Digital input class
      Set r_objInput = New clsDigitalInput
      
      '  Initilize digital inputs
      r_objInput.Initialize objDigital:=objCommonDriver, _
                          a_strNames:=a_strNames, _
                          a_intSignalType:=a_intSignalType
                          
      ' ******************************
      '  Now get the scanning rate
      Set snpDigitalIO = dbLabelerDataBase.OpenRecordset(m_tblLabelerConfiguration, dbOpenSnapshot)
      r_objInput.ScanRate intValue:=snpDigitalIO![intInputScanRate]
      
      ' ******************************
      ' ******************************
      '  clean out the name array
      For intbit = 0 To 15
         a_strNames(intbit) = ""
         a_intSignalType(intbit) = 0
      Next intbit
      
      ' ******************************
      ' ******************************
      '  Now get the output bit definitions
      Set snpDigitalIO = dbLabelerDataBase.OpenRecordset(m_tblGetDigitalOutputConfig, dbOpenSnapshot)
      
      '  Now process each output bits
      Do While Not snpDigitalIO.EOF
         intbit = snpDigitalIO![keyBit]
            
         strSignal = snpDigitalIO![txtSoftwareLabel]
         a_strNames(intbit) = snpDigitalIO![txtSingalName]
         a_lngStrobe(intbit) = snpDigitalIO![lngStrobe]
         a_intSignalType(intbit) = snpDigitalIO![intType]
         a_blnInitialValue(intbit) = snpDigitalIO![binInitialValue]
            
         Select Case strSignal
               Case g_outAIR_BLAST:         g_obitAirBlast = intbit
               Case g_outROTATE_SOLENOID:   g_obitRotate = intbit
               Case g_outPRINTER_RELESE:    g_obitPtrRelese = intbit
               Case g_outEE_ACTUATOR:       g_obitActuator = intbit
               Case g_outEERTOATE:           g_obitEERotate = intbit
               Case g_outVACUME_SOLENOID:   g_obitVacuum = intbit
               Case g_outBLOW_OFF:          g_obitBlowOff = intbit
               Case g_outSCANNER_TRIGGER:   g_obitScannerTrig = intbit
               Case g_outLABELING_COMPLETE: g_obitLabelingComplete = intbit
               Case g_outBUZZER:            g_obitBuzzer = intbit
               Case g_outBECON_RED:         g_obitRedBeckon = intbit
               Case g_outBECKON_YELLOW:     g_obitYellowBeckon = intbit
               Case g_outBECKON_GREEN:      g_obitGreenBeckon = intbit
               Case g_outSA_EMERGENCY_STOP: g_obitSAEmergencyStop = intbit
               Case g_outSA_EXTERNAL_START: g_obitSAExternalStart = intbit
               Case g_outSA_HOLD:           g_obitSAHold = intbit
               Case g_outSA_POSITION_1:     g_obitSAPosition1 = intbit
               Case g_outSA_POSITION_2:     g_obitSAPosition2 = intbit
               Case g_outSA_POSITION_4:     g_obitSAPosition4 = intbit
               Case g_outSA_POSITION_8:     g_obitSAPosition8 = intbit
               Case g_outSA_POSITION_10:    g_obitSAPosition10 = intbit
               Case g_outSA_POSITION_20:    g_obitSAPosition20 = intbit
               Case g_outSA_POSITION_40:    g_obitSAPosition40 = intbit
               Case g_outSA_POSITION_80:    g_obitSAPosition80 = intbit
               Case g_outSA_RESET:          g_obitSAReset = intbit
               Case Else
                  Err.Raise g_errOUTPUT_BIT_NOT_FOUND, , LoadResString(resERR_OUTPUT_BIT_NOT_FOUND)
         End Select 'strNames
         
         snpDigitalIO.MoveNext
         
      Loop 'While Not snpDigitalIO.EOF
      
      '  Start a new instence of Digital input class
      Set r_objOutput = New clsDigitalOutput
      
      '  Initilize digital inputs
      r_objOutput.Initialize objDigital:=objCommonDriver, _
                             a_strNames:=a_strNames, _
                             a_intSignalType:=a_intSignalType, _
                             a_lngStrobe:=a_lngStrobe, _
                             a_blnInitialValue:=a_blnInitialValue
                            
      InitDigitalIO = True
   Else '   the common driver interface did not initilize.
      InitDigitalIO = False
   End If
   
   ' ******************************
   '  Done so leave
   dbLabelerDataBase.Close
      
   Exit Function
   
InitDigitalIO_Error:

   ProccessError "InitDigitalIO", m_strName, Err.Number, Err.Description
   InitDigitalIO = False
   
End Function 'InitDigitalIO


   
Public Sub ProcessCommanedLine()

   Dim intP1 As Integer
   Dim nRetCode As Integer
   #If ccShip_Ver Then
      On Error Resume Next
   #Else
      On Error GoTo 0
   #End If
   
   #If ccSimulation = 1 Then
      g_blnSimulator = True
   #End If
   
   '  No command line arguments leave.
   If Command = "" Then Exit Sub
   
   '  Look for and set log or test mode if wanted ...
   If Not g_blnSimulator Then
      g_blnSimulator = (Command Like "*[/+-][sS]*")
   End If
   
   
   g_blnDisplayScannerData = (Command Like "*[/][dD]*")
   
   
   g_blnNotUseBottomScanner = (Command Like "*[/+-][bB]*")
   
   
   
   g_blnOpenTraceLogFile = (Command Like "*[/][aA]*")
   
   If g_blnOpenTraceLogFile Then
     g_lngMaxSequenceNumber = Val(Mid(Command, InStr(UCase(Command), "/MAXSEQ=") + Len("/MAXSEQ="), 3))
     
     If (g_lngMaxSequenceNumber < 1) Or (g_lngMaxSequenceNumber > 99) Then
     
        nRetCode = MsgBox("Invalid Maximum Sequence Number To Record = " + Str(g_lngMaxSequenceNumber) + ". Press OK When Ready", vbOKOnly, _
                          "Invalid Command Line Argument")
        End
     End If
     
   End If
   
   g_lngSequenceNumber = 0
   g_nMaxDefSequence = 0
   g_blnLogError = False
   
   
   
   '  Do they want to run a job immediately.
   intP1 = InStr(UCase(Command), "/J:")
   If intP1 <> 0 Then
      '  indicat an intial job so look for name
      m_strInitalJob = Mid(Command, intP1 + 3)
      '  clean up the string
      m_strInitalJob = Trim(m_strInitalJob)
   End If
   
End Sub 'ProcessCommanedLine

Public Function ProcessProfile()

   #If ccShip_Ver Then
      On Error Resume Next
   #Else
      On Error GoTo 0
   #End If

   ProcessProfile = True
   
   ' check to see if file exist
   If Dir(m_dbJobsDataBaseName, vbNormal) = "" Then
      m_dbJobsDataBaseName = GetSetting(App.EXEName, g_strJOB_STUFF, m_strJOB_DB_NAME, m_dbJobsDataBaseName)
      m_strJobDatabaseFile = GetSetting(App.EXEName, g_strJOB_STUFF, m_strJOB_DB_FILE, m_strJobDatabaseFile)
   Else
   
   
   End If
End Function 'ProcessProfile

Public Sub SetupOkButton(objButton As Object)

   objButton.Caption = LoadResString(resCMD_OK)

End Sub 'SetupOkButton

Public Sub SetupCancelButton(objButton As Object)

   objButton.Caption = LoadResString(resCMD_CANCEL)
   
End Sub 'SetupCancelButton

Public Function GetConfigurationDataBaseName() As String

   GetConfigurationDataBaseName = m_dbConfgurationDataBaseName
   
End Function 'GetConfigurationDataBaseName


Public Sub ExitEnd()

   '  disengage printer
   If Not (m_objLabeler Is Nothing) Then
      m_objLabeler.PrinterRelease
   End If
   
   '  Force the reset of the SA
   If Not (m_objMove Is Nothing) Then
      m_objMove.Reset blnForce:=True
   End If
   
   '  Now reset the outputs
   If Not (m_objDigitalOutpus Is Nothing) Then
      m_objDigitalOutpus.Reset
   End If
   
   Close ' close any files which may be open
   If g_blnTest Then
      Stop
   Else
      End
   End If
   CloseTraceLog
   
End Sub 'ExitEnd


Public Function GetLabelerConfiguration() As String

   GetLabelerConfiguration = m_tblLabelerConfiguration
   
End Function 'GetLabelerConfiguration




Public Property Get JobDatabaseName() As String

   JobDatabaseName = m_dbJobsDataBaseName

End Property 'Get JobDatabaseName

Public Property Let JobDatabaseName(vNewValue As String)

   m_dbJobsDataBaseName = vNewValue
   SaveSetting App.EXEName, g_strJOB_STUFF, m_strJOB_DB_NAME, vNewValue

End Property 'Let JobDatabaseName

Public Property Get JobDatabaseFile() As String

   JobDatabaseFile = m_strJobDatabaseFile
   
End Property ' Get JobDatabaseFile

Public Property Let JobDatabaseFile(vNewValue As String)

   m_strJobDatabaseFile = vNewValue
   SaveSetting App.EXEName, g_strJOB_STUFF, m_strJOB_DB_FILE, vNewValue
   
End Property ' Let JobDatabaseFile


Public Function GetSerialPortConfiguration()

   GetSerialPortConfiguration = m_strGetSerialPortConfiguration
   
End Function 'GetSerialPortConfiguration

Public Sub DataValues(a_blnBitValues() As Boolean)

'  This function processes the array of bit values, builds a
'  long number containing all the values, and passes back.
'  This function also updates the indicators on the
'  associated digital output.

   Dim lngBuffer As Long
   Dim i As Integer
   Dim a_vntDataOut(1) As Variant
   g_lDataValue = 0
   #If ccShip_Ver Then
      On Error GoTo Error_DataValues
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
   

   Exit Sub
   
Error_DataValues:

   ProccessError "DataValue", m_strName, Err.Number, Err.Description
   
End Sub      'DataValue



Private Function ProcessINI() As Boolean
Dim blnResult As Boolean
Dim strFlavorConstant As String
Dim strSimulationMode As String
Dim strUseBottomScanner As String


On Error GoTo Error_Control:
   'declare default values
   
   ProcessINI = True
   g_strFlavorConstant = True
   blnResult = True
   
   strFlavorConstant = GetProfile("Two Sided Boards", "FlavorIsStatic", m_strLabelerINIFile, blnResult)
   If blnResult Then
      If (UCase(strFlavorConstant) = "NO") Then
         g_strFlavorConstant = False
      End If
          
   Else
     ProcessINI = False
   End If
   
   ' now check for simulation mode
   If (Not g_blnSimulator) Then
        strSimulationMode = GetProfile("Defaults", "SimulationMode", m_strLabelerINIFile, blnResult)
        If blnResult Then
           If (UCase(strSimulationMode) = "TRUE") Then
              g_blnSimulator = True
           End If
        Else
          ProcessINI = False
        End If
   End If
   
   ' now check to enable bottom scanner
   If (Not g_blnNotUseBottomScanner) Then
        strUseBottomScanner = GetProfile("Defaults", "UseBottomScanner", m_strLabelerINIFile, blnResult)
        If blnResult Then
           If (UCase(strUseBottomScanner) = "FALSE") Then
              g_blnNotUseBottomScanner = True
           End If
        Else
          ProcessINI = False
        End If
   End If
   
   
   
   
Exit Function
Error_Control:
  ProcessINI = False

End Function

Public Function PreCheckSerialNumbers(strJobName As String) As Boolean

Dim strFileName As String
Dim nFH As Long
Dim strBuffer As String
Dim blnFound As Boolean
Dim nJobNameCount As Integer
Dim nIndex As Integer

   On Error GoTo Error_DataValues
   
   
   PreCheckSerialNumbers = False
   
   nFH = FreeFile
   strFileName = App.Path + "\" + "precheck_params.txt"
   
   If (Dir(strFileName, vbNormal) <> "") Then
   
      Open strFileName For Input As nFH
      
      While (Not EOF(nFH))
         Line Input #nFH, strBuffer
         
         
         If (InStr(UCase(strBuffer), "PRECHECKALLJOBS")) Then
            If ((InStr(UCase(strBuffer), "TRUE"))) Then
                PreCheckSerialNumbers = True
                Close (nFH)
                Exit Function
            End If
         End If
      
         
         If (InStr(UCase(strBuffer), "PRECHECKSOMEJOBS")) Then
            If (InStr(UCase(strBuffer), "TRUE") > 0) Then
               While (Not EOF(nFH))
                Line Input #nFH, strBuffer
                If (InStr(strBuffer, "JobNames") > 0) Then
                   While (Not EOF(nFH))
                     Line Input #nFH, strBuffer
                     If (InStr(UCase(strBuffer), UCase(strJobName)) > 0) Then
                         PreCheckSerialNumbers = True
                         Close (nFH)
                         Exit Function
                     End If
                  Wend
                End If
              Wend
           Else
             PreCheckSerialNumbers = False
             Close (nFH)
             Exit Function
           End If
        End If
        
        
      Wend
   End If
   
   Close (nFH)

Exit Function

Error_DataValues:
   
   PreCheckSerialNumbers = False

   ProccessError "DataValue", m_strName, Err.Number, Err.Description


End Function




