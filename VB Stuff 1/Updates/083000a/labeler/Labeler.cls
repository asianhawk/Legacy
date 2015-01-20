VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
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
'*        3-Axis Label Applicator
'*             Main Class
'*
'*
'*    Customer: Lucent Technologies
'*              Shreveport, LA
'*
'*
'*    Date of origin: 12/29/96
'*    Original author: Michael D. Reed
'*
'* Class purpose:
'*    This class is the main class which controls the labeler
'*    customized for Lucent Technologies Shreveport, LA.
'*
'************************************************************************
'******************************************************************
Option Explicit
'******************************************************************

'  Regestry constents
Private Const m_strWEEK_SET = "WeekSet"

'  class constetst
Private Const m_intFIRST_APPLY_POINT_INDEX = 21
Private Const m_strLABEL_COUNT_IAI_LINE = "0032"
Private Const m_strX_SCAN_0_OFFSET_IAI_LINE = "0022"
Private Const m_strY_SCAN_0_OFFSET_IAI_LINE = "0023"
Private Const m_strX_SCAN_90_OFFSET_IAI_LINE = "0024"
Private Const m_strY_SCAN_90_OFFSET_IAI_LINE = "0025"

'  Digital input bits
Private Const m_intQUEUE_READY = 8
Private Const m_intNEXT_LABEL = 9
Private Const m_intMANUAL_FEED = 10
Private Const m_intLOW_LABEL = 11
Private Const m_intCONVEYOR_ERROR = 12
Private Const m_intLABEL_APPLIED = 13
Private Const m_intPANEL_COMPLETE = 14
Private Const m_intAPPLACTOR_BYPASS = 15
Private Const m_intLABEL_PICKUP_ERROR = 16
Private Const m_intPANEL_READY = 17
Private Const m_intGARD_DOORS_OPEN = 18
Private Const m_intHOLD_SWITCH = 19
Private Const m_intAIR_PRESSUR_LOSS = 20

Private g_blnBadLabel As Boolean

'  my name and status
Private m_strName As String
Private m_blnInitStatus As Boolean

'  Define Machine
Private Type Configuration
   strName             As String
   lngXPanelOffset     As Long
   lngXDirection       As Long
   lngYPanelOffset     As Long
   lngYDirection       As Long
   txtScannerOffsetCodeStep As String
   lngXScanner0Offset  As Long
   lngYScanner0Offset  As Long
   lngXScanner90Offset As Long
   lngYScanner90Offset As Long
   lngNosePieceOffset As Long
   intPointDataTableOffset As Integer
   txtBoardCountCodeStep As String
   strBadScanFileName As String
   strBadlabelPickupFileName As String
End Type 'Configuration
Private m_udtConfig As Configuration

'  Define job data
Private Const m_intWEEK_CODE_OFFSET = 20
'Private Const m_fmtSERIAL_NUMBER = "000000"
Private Const m_fmtSERIAL_NUMBER = "00000" ' changed to allow for
                                          ' dash numbers - rfv
Private Const m_fmtWEEK_CODE = "00"
Private Type Job_Info
   strJobID As String
   strName As String
   strPartNumber As String
   intLabels As Integer
   strDescription As String
   lngQuantity As Long
   strLastSerialNumber  As String
   strPlantCode As String
   strYearCode As String
   strWeekCode As String
   strDBPath As String
   strTableName As String
   strPWBDesignator As String
End Type  'Job_Info
Private m_udtCurrentJob As Job_Info

Private Type LabelInfo
   JobName As String
   PrefixWidth As Integer
   YearCodeWidth As Integer
   WeekCodeWidth As Integer
   SerialNumberWidth As Integer
End Type

Private m_udtLabelDesc As LabelInfo

'  Last label printed data
Private m_strLastLabel As String
Private m_lngPanelQuintityCount As Long
Private m_lngLabelApplyedCount As Long
Private m_blnQtyCountUP As Boolean
Private m_strSerialNumber As String
Private m_blnUseGlobalSN As Boolean
Private m_dbLabelApplied As Database
Private m_tblLabelApplied As Recordset

'  Define point tabel
Private Type Data_Point
   lngXApply As Long
   lngYApply As Long
   strThataApply As String
   strName As String
End Type 'Data_Point
Private m_udtDataPoints() As Data_Point
Private m_intLabelPrinted As Integer

'  Define a printer template
Private Type Printer_Template
   strFormatName As String
   strTemplate As String
   strFieldCount As String
   strTemplatePath As String
End Type 'Printer_Template
Private m_udtCurrentPrinterTemplate As Printer_Template
'  print queue
Private m_objLabelsPrinted As clsQueue

'  digitial I/O stuff
'  Output bits
Private Const m_intCLEAR_Q = 0
Private Const m_intLABEL_PASS = 1
Private Const m_intLABEL_FAIL = 2
Private Const m_intPAUSE = 3
Private Const m_intROTATE_90 = 5
'  input bits need to check
Private Const m_intAPPLICATOR_BYPASS = 15
Private Const m_intGUARD_DOORS = 18
Private Const m_intAIR_PRESSURE = 20
Private Const m_intHOLD_MODE = 19
Private Type Dig_IO
   strName As String
   strDirection As String
   intBitNum As Integer
   strDescription As String
End Type 'Dig_IO
Private ma_udtDigitialIO() As Dig_IO
Private m_colDigitialIO As New Collection

'  the main form desplayed to the user
Private m_objMainForm As Object

'  Private data items
Private m_objPrinter As clsLabelPrint
Private m_objIAICtrl As clsMotionControl
Private m_objscanner As clsMicroscan
Private m_objDigIO As clsDigitalIO

'  Info to program the IAI
Private Const m_chrDLIMITER = ","
Private Const m_strPROGRAM_NUMBER = "1"

Public Function Version() As String

   #If ccShip_Ver Then
      On Error Resume Next
   #Else
      On Error GoTo 0
   #End If

   With App
      Version = .Major & "." & .Minor & "." & .Revision
   End With 'app
   
End Function 'Version


Public Function InitStatus() As Boolean
   
   #If ccShip_Ver Then
      On Error Resume Next
   #Else
      On Error GoTo 0
   #End If

   InitStatus = m_blnInitStatus
   
End Function 'InitStatus


Private Function LoadPrinterData( _
                        strTemplate As String, strFormatName As String, _
                        strFieldCount As String, strTemplatePath As String _
                 ) As Boolean

   #If ccShip_Ver Then
      On Error GoTo LoadPrinterData_Error
   #Else
      On Error GoTo 0
   #End If
    
   With m_udtCurrentPrinterTemplate
      .strTemplate = strTemplate
      .strFormatName = strFormatName
      .strFieldCount = strFieldCount
      .strTemplatePath = strTemplatePath
      
   End With 'a_vntPrinterTemplate
      
   LoadPrinterData = True
   
   Exit Function

LoadPrinterData_Error:

   ProccessError "LoadPrinterData", m_strName, Err.Number, Err.Description
   LoadPrinterData = False

End Function 'LoadPrinterData

Public Sub RunStopJob()
   
   #If ccShip_Ver Then
      On Error GoTo RunStopJob_Error
   #Else
      On Error GoTo 0
   #End If

   If g_blnJobRunning Then
      ' Stop the job
      m_objDigIO.ScanPorts False
      g_blnJobRunning = False
      With m_objMainForm
         .JobEnd
         .mnuFile.Enabled = True
         .MessageClear
      '   .labTextJobName.Caption = ""
      '   .labTextPartNumber.Caption = ""
      '   .labTextQuantity.Caption = ""
         .labTextPrinted.Caption = ""
         .labTextScaned.Caption = ""
         .labMessages.Caption = ""

      End With ' m_objMainForm
      m_objIAICtrl.SendReset
      m_dbLabelApplied.Close
      SaveLastSerialNumber
      If m_blnUseGlobalSN Then
         If Not g_blnQueueOK Then
            QueueStop
         End If
      Else
         QueueStop
      End If
      frmHistory.Message "Job Stopped"
      InstructionsRemove 'Make sure that instruction box is removed
    Else 'Start the job
      frmHistory.Message "Job Started"
      InstructionsRemove 'Make sure that instruction box is removed
      '  Set label counter to 0
      If OpenLogingDB() Then
         '  set the fixed part of the serial number
         SetDateSN

         #If cc_Simulation <> 1 Then
           m_objIAICtrl.SendReset
         #End If
         
         '  clear output bits
         #If cc_Simulation <> 1 Then
           SetDigIOBits
         #End If
         
         '  Start the digital ports scaning
         #If cc_Simulation <> 1 Then
            m_objDigIO.ScanPorts True
            m_objDigIO.Bit(m_intPAUSE) = False
         
         #End If
         
         
         '  Setart que for thata position
         m_intLabelPrinted = 21

         ' disable the file mnu
         frmMain.mnuFile.Enabled = False
         
         '  Set up the queues for the printer and iai
         If m_blnUseGlobalSN Then
            If Not g_blnQueueOK Then
               QueueStart
            End If
         Else
            QueueStart
         End If
            
         '  Strat the IAI
         #If cc_Simulation <> 1 Then
           If m_objIAICtrl.RunProgram(1, 1) Then
            frmHistory.Message "Labeler started IAI program"
            g_blnJobRunning = True
            m_objMainForm.JobRun
            m_objMainForm.labTextQuantity.Caption = m_lngPanelQuintityCount
           Else '   IAI did not start so stop everthing
             m_objDigIO.ScanPorts False
            QueueStop
            m_objMainForm.JobEnd
            frmHistory.Message "IAI failed to start job ended"
           End If
        #Else
            frmHistory.Message "Labeler started IAI program"
            g_blnJobRunning = True
            m_objMainForm.JobRun
            m_objMainForm.labTextQuantity.Caption = m_lngPanelQuintityCount
        #End If
      End If
   End If
   
   Exit Sub

RunStopJob_Error:

   ProccessError "RunStopJob", m_strName, Err.Number, Err.Description

End Sub 'RunStopJob

Private Function CheckDoorsAirBypass() As Boolean

   #If ccShip_Ver Then
      On Error GoTo CheckDoorsAirBypass_Error
   #Else
      On Error GoTo 0
   #End If
    
   Do
      With m_objDigIO
         If .Bit(m_intAPPLICATOR_BYPASS) Then
            g_blnBypassMode = True
            OnBit_ApplactorBypass True
         Else
            g_blnBypassMode = False
            OnBit_ApplactorBypass False
         End If
         If .Bit(m_intGUARD_DOORS) Then
            g_blnGardDoorsOpen = True
            OnBit_GardDoorsOpen True
         Else
            g_blnGardDoorsOpen = False
            OnBit_GardDoorsOpen False
         End If
         If .Bit(m_intAIR_PRESSURE) Then
            g_blnAirLoss = True
            OnBit_AirPressurLoss True
         Else
            g_blnAirLoss = False
            OnBit_AirPressurLoss False
         End If
      End With 'm_objDigIO
      If g_blnBypassMode Or g_blnGardDoorsOpen Or g_blnAirLoss Then
         MsgBox LoadResString(resDOORS_AIR_BYPASS), vbCritical + vbOKOnly, LoadResString(resAPP_SUSPENDED_TITLE)
      End If
   Loop While g_blnBypassMode Or g_blnGardDoorsOpen Or g_blnAirLoss
      
   Exit Function

CheckDoorsAirBypass_Error:

   ProccessError "CheckDoorsAirBypass", m_strName, Err.Number, Err.Description
   CheckDoorsAirBypass = False

End Function 'CheckDoorsAirBypass

Public Function Initialize(objIAICtrl As Object, _
                           objScanner As Object, _
                           objDigIO As Object, _
                           objPrinter As Object) As Boolean

   #If ccShip_Ver Then
      On Error GoTo Initialize_Error
   #Else
      On Error GoTo 0
   #End If
    
   ' Set up refrences to the subsystems
   Set m_objPrinter = objPrinter
   Set m_objIAICtrl = objIAICtrl
   Set m_objscanner = objScanner
   Set m_objDigIO = objDigIO
   
   '  Tell the digital IO subsys where my call back is
   m_objDigIO.SetCallBack Me
   
   ' Now set the offset for the scanner
   With m_udtConfig
      m_blnInitStatus = m_objIAICtrl.SetScannerOffsets( _
                           strPROGRAM_NUMBER:=m_strPROGRAM_NUMBER, _
                           txtScannerOffsetCodeStep:=.txtScannerOffsetCodeStep, _
                           lngXScanner0Offset:=.lngXScanner0Offset, _
                           lngYScanner0Offset:=.lngYScanner0Offset, _
                           lngXScanner90Offset:=.lngXScanner90Offset, _
                           lngYScanner90Offset:=.lngYScanner90Offset)
   End With 'm_udtConfig
   
   m_blnInitStatus = True
   g_blnJobReady = False
   g_blnJobRunning = False
   
   Exit Function

Initialize_Error:

   ProccessError "Initialize", m_strName, Err.Number, Err.Description
   Initialize = False

End Function 'Initialize

Public Sub SetMainForm(objMainForm As Object)

   #If ccShip_Ver Then
      On Error Resume Next
   #Else
      On Error GoTo 0
   #End If

   Set m_objMainForm = objMainForm
   
End Sub 'SetMainForm

Public Sub SendPrinterTemplate(Optional a_vntPrinterTemplate As Variant)
                              
   #If ccShip_Ver Then
      On Error GoTo SendPrinterTemplate_Error
   #Else
      On Error GoTo 0
   #End If

   With m_udtCurrentPrinterTemplate
      If Not IsMissing(a_vntPrinterTemplate) Then
         .strTemplate = CStr(a_vntPrinterTemplate(0))
         .strFormatName = CStr(a_vntPrinterTemplate(1))
         .strFieldCount = CInt(a_vntPrinterTemplate(2))
      End If
      
      m_objPrinter.SendTemplate strTemplate:=.strTemplate, _
                strFormatName:=.strFormatName, _
                strTemplatePath:=.strTemplatePath
   End With 'a_vntPrinterTemplate
                
   Exit Sub

SendPrinterTemplate_Error:

   ProccessError "SendPrinterTemplate", m_strName, Err.Number, Err.Description

End Sub 'SendPrinterTemplate

Private Sub PrintLabel(strBuffer As String)
   
   Dim vntTemp As Variant
   Dim i As Integer
   
   #If ccShip_Ver Then
      On Error GoTo PrintLabel_Error
   #Else
      On Error GoTo 0
   #End If
    
   
   m_objPrinter.SendFieldData strBuffer
   
   Exit Sub

PrintLabel_Error:

   ProccessError "PrintLabel", m_strName, Err.Number, Err.Description

End Sub 'PrintLabel

Public Sub ResetIAI()

   #If ccShip_Ver Then
      On Error Resume Next
   #Else
      On Error GoTo 0
   #End If

   m_objIAICtrl.SendReset
   
End Sub 'ResetIAI

Public Sub ResetPrinter()

   #If ccShip_Ver Then
      On Error Resume Next
   #Else
      On Error GoTo 0
   #End If

   If m_objPrinter.SendReset Then
      SendPrinterTemplate
   Else
   End If
   
End Sub 'ResetPrinter

Public Sub ResetScanner()

   #If ccShip_Ver Then
      On Error Resume Next
   #Else
      On Error GoTo 0
   #End If

   m_objscanner.SendReset
   
End Sub 'ResetScanner



Public Function LoadPointTable(strJobID As String, ByRef r_intLabels As Integer) As Boolean

   Dim dbLucentDataBase As Database
   Dim qdfDataPoints As QueryDef
   Dim snpDataPoints As Recordset
   Dim vntDataPoints(0 To 2) As Variant
   Dim idx As Integer
   Dim lngXOffset As Long
   Dim lngYOffset As Long
   Dim lngThetaRotate As Long
   Dim lngNosePieceOffset As Long
   Dim lngXSign As Long
   Dim lngYSign As Long
   Dim lngTemp As Long
   
   #If ccShip_Ver Then
      On Error GoTo LoadPointTable_Error
   #Else
      On Error GoTo 0
   #End If
   
   modUtilities.MessageDisplay LoadResString(resLOADING_LABEL_POINT_TABEL)
   LoadPointTable = False
   
    '  Set up offsets
   With m_udtConfig
      lngXOffset = .lngXPanelOffset
      lngXSign = .lngXDirection
      lngYOffset = .lngYPanelOffset
      lngYSign = .lngYDirection
      lngNosePieceOffset = .lngNosePieceOffset
   End With 'Configuration
  
   '  Set Lucent point data
   '  Open the data base, define the quire and get the data points using the JobID
   Set dbLucentDataBase = Workspaces(0).OpenDatabase(modMain.JobDatabaseName)
   Set qdfDataPoints = dbLucentDataBase.QueryDefs(modMain.GetDataPoints)
   qdfDataPoints.Parameters![JobsName] = strJobID
   Set snpDataPoints = qdfDataPoints.OpenRecordset(dbOpenSnapshot)
   
   '  setup the table
   '  init the index counter
   idx = m_intFIRST_APPLY_POINT_INDEX
   r_intLabels = 0
   '  file the table
   Do While Not snpDataPoints.EOF
      ReDim Preserve m_udtDataPoints(m_intFIRST_APPLY_POINT_INDEX To idx)
      With m_udtDataPoints(idx)
         If IsNull(snpDataPoints![XApplyPt]) Then
            .lngXApply = g_lngNOT_USED
         Else
            lngTemp = snpDataPoints![XApplyPt]
            If snpDataPoints![thataapply] = 0 Then
              .lngXApply = lngXOffset + (lngXSign * lngTemp)
            Else
               .lngXApply = lngXOffset + (lngXSign * lngTemp) - lngNosePieceOffset * 100
            End If
         End If
         If IsNull(snpDataPoints![YApplyPt]) Then
            .lngYApply = g_lngNOT_USED
         Else
            lngTemp = snpDataPoints![YApplyPt]
            
            If snpDataPoints![thataapply] = 0 Then
              .lngYApply = lngYOffset + (lngYSign * lngTemp) - lngNosePieceOffset * 100
            Else
            
              .lngYApply = lngYOffset + (lngYSign * lngTemp)
            End If
         End If
         If IsNull(snpDataPoints![thataapply]) Then
            .strThataApply = ""
         Else
            .strThataApply = snpDataPoints![thataapply]
         End If
         If IsNull(snpDataPoints![DataPtName]) Then
            .strName = ""
         Else
            .strName = snpDataPoints![DataPtName]
         End If
         modUtilities.Log "Labeler", "Points from table:: " & .strName & ": " & "; X=" & .lngXApply & "; Y=" & .lngYApply & "; Th=" & .strThataApply
      End With 'm_udtDataPoints(idx)
      snpDataPoints.MoveNext
      idx = idx + 1
      r_intLabels = r_intLabels + 1
   Loop 'While Not snpDataPoints.EOF
      
   '  Now send the points to the IAI
   For idx = LBound(m_udtDataPoints) To UBound(m_udtDataPoints)
      With m_udtDataPoints(idx)
         vntDataPoints(0) = CStr(idx)
         Debug.Print CStr(idx)
         vntDataPoints(1) = .lngXApply
         Debug.Print .lngXApply
         
         vntDataPoints(2) = .lngYApply
         Debug.Print .lngYApply
         
         modUtilities.Log "Labeler", "Points to IAI::" & vntDataPoints(0) & ") x=" & vntDataPoints(1) & "; Y=" & vntDataPoints(2)
         m_objIAICtrl.WriteDataPoint vntPointValue:=vntDataPoints
      End With 'm_udtDataPoints(idx)
   Next idx
   
   dbLucentDataBase.Close
   modUtilities.MessageDisplay LoadResString(resWRITING_CARD)
   LoadPointTable = m_objIAICtrl.WriteCardDataPoints()
   modUtilities.Log "Labeler", "Points writen to card"
   
   Exit Function 'LoadPointTable

LoadPointTable_Error:

   ProccessError "LoadPointTable", m_strName, Err.Number, Err.Description
   LoadPointTable = False
   

End Function 'LoadPointTable


Private Sub Class_Initialize()
   
   #If ccShip_Ver Then
      On Error GoTo Class_Initialize_Error
   #Else
      On Error GoTo 0
   #End If
   
   m_blnInitStatus = True
   
   ' give me a name
   m_strName = "clsLabeler"
   
   g_blnQueueOK = False
   'comment out BadLabel *** llj 1/7/98
   'g_blnBadLabel = False
   
   '  Setup Labeler configuration data
   m_blnInitStatus = m_blnInitStatus And InitConfiguration()
   
   '  setup the digital IO data
   m_blnInitStatus = m_blnInitStatus And InitDigitalIO()
       
   Exit Sub
   
Class_Initialize_Error:

   ProccessError "Class_Initialize", m_strName, Err.Number, Err.Description
   m_blnInitStatus = False
   
End Sub 'Class_Initialize




Public Function InfoJob(strJobID As String, strName As String, strLastSerialNumber As String, _
                        strPartNumber As String, strPlantCode As String, _
                        strDescription As String, strQuanity As String, _
                        strTemplate As String, strFormatName As String, _
                        strFieldCount As String, strTemplatePath As String, _
                        strTableName As String, strDBPath As String _
                ) As Boolean

   Dim blnStatus
   
   #If ccShip_Ver Then
      On Error GoTo InfoJob_Error
   #Else
      On Error GoTo 0
   #End If
    
   blnStatus = True
   
   '  Set up job info
   blnStatus = blnStatus And LoadJobData(strJobID:=strJobID, strPlantCode:=strPlantCode, _
                       strName:=strName, strPartNumber:=strPartNumber, strLastSerialNumber:=strLastSerialNumber, _
                       strDescription:=strDescription, strQuanity:=strQuanity, _
                       strTableName:=strTableName, strDBPath:=strDBPath)
                       
   '  set up printer data
   blnStatus = blnStatus And LoadPrinterData(strTemplate:=strTemplate, _
                strFormatName:=strFormatName, _
                strFieldCount:=strFieldCount, _
                strTemplatePath:=strTemplatePath)
       
   '  Everything loaded from DB now init the IAI and printer
   blnStatus = blnStatus And InitJob()
   
   InfoJob = blnStatus
   
   frmHistory.Message "Job PN: " & strPartNumber
   
   Exit Function

InfoJob_Error:

   ProccessError "InfoJob", m_strName, Err.Number, Err.Description
   InfoJob = False

End Function 'InfoJob



Private Function LoadJobData(strJobID As String, strName As String, strLastSerialNumber As String, _
                        strPartNumber As String, strPlantCode As String, _
                        strDescription As String, strQuanity As String, _
                        strTableName As String, strDBPath As String) As Boolean

   #If ccShip_Ver Then
      On Error GoTo LoadJobData_Error
   #Else
      On Error GoTo 0
   #End If
 
   
   '  Set current job info
   With m_udtCurrentJob
      .strJobID = strJobID
      .strName = strName
      .strPartNumber = strPartNumber
      .strDescription = strDescription
      .lngQuantity = CLng(strQuanity)
      m_blnQtyCountUP = (.lngQuantity = 0)
      m_lngPanelQuintityCount = .lngQuantity
      .strLastSerialNumber = strLastSerialNumber
      .strPlantCode = strPlantCode
      .strDBPath = strDBPath
      .strTableName = strTableName
   End With 'm_udtCurrentJob
   
   With m_objMainForm
      .labTextJobName.Caption = m_udtCurrentJob.strName
      .labTextPartNumber.Caption = m_udtCurrentJob.strPartNumber
       g_strCONCODE = m_udtCurrentJob.strPartNumber
      .labTextQuantity.Caption = CStr(m_udtCurrentJob.lngQuantity)
   End With 'm_objMainForm
      
   LoadJobData = True
   
   Exit Function

LoadJobData_Error:

   ProccessError "LoadJobData", m_strName, Err.Number, Err.Description
   LoadJobData = False
   
End Function 'LoadJobData

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
   Set snpConfiguration = dbLabelerDataBase.OpenRecordset(modMain.GetConfiguration, dbOpenSnapshot)
   With m_udtConfig
      .strName = snpConfiguration![Name]
      .lngXPanelOffset = snpConfiguration![XPanelOffset]
      .lngXDirection = snpConfiguration![XOperator]
      .lngYPanelOffset = snpConfiguration![YPanelOffset]
      .lngYDirection = snpConfiguration![YOperator]
      .txtScannerOffsetCodeStep = snpConfiguration![ScannerOffsetLine]
      .lngXScanner0Offset = snpConfiguration![XScanner0Offset]
      .lngYScanner0Offset = snpConfiguration![YScanner0Offset]
      .lngXScanner90Offset = snpConfiguration![XScanner90Offset]
      .lngYScanner90Offset = snpConfiguration![YScanner90Offset]
      .intPointDataTableOffset = snpConfiguration![PointDataTableOffset]
      .txtBoardCountCodeStep = snpConfiguration![BoardCountCodeLine]
      .strBadScanFileName = snpConfiguration![BadScanFile]
      .strBadlabelPickupFileName = snpConfiguration![BadLabelFile]
      .lngNosePieceOffset = snpConfiguration![NosePieceOffset]
   End With 'Configuration
   
   dbLabelerDataBase.Close
      
   Exit Function
   
InitConfiguration_Error:

   ProccessError "InitConfiguration", m_strName, Err.Number, Err.Description
   InitConfiguration = False

End Function 'InitConfiguration

Public Function InitDigitalIO() As Boolean

   Dim dbLabelerDataBase As Database
   Dim snpDigitalIO As Recordset
   Dim udtTempDigIO As Dig_IO
   Dim idx As Integer

   #If ccShip_Ver Then
      On Error GoTo InitDigitalIO_Error
   #Else
      On Error GoTo 0
   #End If
   
   InitDigitalIO = False
   
   '  get data on digitial IO prots
   Set dbLabelerDataBase = Workspaces(0).OpenDatabase(modMain.GetConfigurationDataBaseName)
   Set snpDigitalIO = dbLabelerDataBase.OpenRecordset(modMain.GetDigitalIO, dbOpenSnapshot)
   
   idx = 0
   
   '  file the table
   Do While Not snpDigitalIO.EOF
      With udtTempDigIO
         .strName = snpDigitalIO![Name]
         .strDirection = snpDigitalIO![Direction]
         .intBitNum = snpDigitalIO![BitNumber]
         .strDescription = snpDigitalIO![Description]
      End With 'udtTempDigIO
      
      ReDim Preserve ma_udtDigitialIO(idx)
      ma_udtDigitialIO(idx) = udtTempDigIO
      m_colDigitialIO.Add Item:=idx, Key:=CStr(ma_udtDigitialIO(idx).intBitNum)
      
      snpDigitalIO.MoveNext
      idx = idx + 1
   Loop 'While Not snpDataPoints.EOF
      
   dbLabelerDataBase.Close
   
   InitDigitalIO = True
   
   Exit Function
   
InitDigitalIO_Error:

   ProccessError "InitDigitalIO", m_strName, Err.Number, Err.Description
   InitDigitalIO = False
   
End Function 'InitDigitalIO
Private Function DigitalIO(Key As Integer) As Dig_IO
   
   #If ccShip_Ver Then
      On Error Resume Next
   #Else
      On Error GoTo 0
   #End If

   DigitalIO = ma_udtDigitialIO(m_colDigitialIO.Item(CStr(Key)))
   
End Function 'DigitalIO

Public Sub OnBit_Trans(intBit As Integer, blnValue As Boolean)
 
   #If ccShip_Ver Then
      On Error GoTo OnBit_Trans_Error
   #Else
      On Error GoTo 0
   #End If
    
   If IsMember(m_colDigitialIO, CStr(intBit)) Then
   '   frmHistory.Message intBit & ">" & DigitalIO(intBit).strName & "=" & blnValue
      Select Case DigitalIO(intBit).intBitNum
        Case m_intQUEUE_READY:        OnBit_QueueReady blnValue
        Case m_intNEXT_LABEL:         OnBit_NextLabel blnValue
        Case m_intMANUAL_FEED:        OnBit_ManualFeed blnValue
        Case m_intLOW_LABEL:          OnBit_LowLabel blnValue
        Case m_intCONVEYOR_ERROR:     OnBit_ConveyorError blnValue
        Case m_intLABEL_APPLIED:      OnBit_LabelApplied blnValue
        Case m_intPANEL_COMPLETE:     OnBit_PanelComplete blnValue
        Case m_intAPPLACTOR_BYPASS:   OnBit_ApplactorBypass blnValue
        Case m_intLABEL_PICKUP_ERROR: OnBit_LabelPickupError blnValue
        Case m_intPANEL_READY:        OnBit_PanelReady blnValue
        Case m_intGARD_DOORS_OPEN:    OnBit_GardDoorsOpen blnValue
        Case m_intHOLD_SWITCH:        OnBit_HoldSwitch blnValue
        Case m_intAIR_PRESSUR_LOSS:   OnBit_AirPressurLoss blnValue
      End Select
   End If

   Exit Sub

OnBit_Trans_Error:

   ProccessError "OnBit_Trans", m_strName, Err.Number, Err.Description

End Sub 'OnBit_Trans

Private Sub OnBit_LowLabel(blnValue As Boolean)

   Static intMesgNumber As Integer
   
   #If ccShip_Ver Then
      On Error GoTo OnBit_LowLabel_Error
   #Else
      On Error GoTo 0
   #End If
    
   If blnValue Then
      intMesgNumber = m_objMainForm.MessageDisplay(LoadResString(resLOW_LABEL))
   Else
      m_objMainForm.MessageRemove intMesgNumber
   End If
   
   Exit Sub

OnBit_LowLabel_Error:

   ProccessError "OnBit_LowLabel", m_strName, Err.Number, Err.Description

End Sub 'LowLabel

Private Sub OnBit_QueueReady(blnValue As Boolean)

   #If ccShip_Ver Then
      On Error GoTo OnBit_QueueReady_Error
   #Else
      On Error GoTo 0
   #End If
 
   If blnValue Then
      '  Set clearing Q to flase
      g_blnClearingQue = False
      
   End If
   
   Exit Sub

OnBit_QueueReady_Error:

   ProccessError "OnBit_QueueReady", m_strName, Err.Number, Err.Description

End Sub 'QueueReady

Private Sub OnBit_NextLabel(blnValue As Boolean)
   
   #If ccShip_Ver Then
      On Error GoTo OnBit_NextLabel_Error
   #Else
      On Error GoTo 0
   #End If
    
   g_blnPrintingLabel = blnValue
      
   '  set scanned pass / fail bits to false
   m_objDigIO.Bit(m_intLABEL_PASS) = False
   m_objDigIO.Bit(m_intLABEL_FAIL) = False
      
  If Not blnValue Then
      If g_blnManualFeed Then
         PrintLabel LoadResString(resMANUAL_FEED_LABEL)
         g_blnQueueOK = False
      ElseIf g_blnJobRunning Then
         
         InstructionsRemove ' make instructios message box is not desplayed
         
         '  Get a new label
         m_strLastLabel = GetNextLabel()
    '     Dim x As Long
    '     x = Timer
    '     While Timer - x < 1
            m_objDigIO.Bit(m_intROTATE_90) = (m_udtDataPoints(m_intLabelPrinted).strThataApply = "90")
    '     Wend
         '  Set the thata bit
         
         '  Print the label
         PrintLabel m_strLastLabel
         
         '  Display what was printed
    '     m_objMainForm.labTextPrinted.Caption = m_strLastLabel
         
         '  Now store it into the que
       '  m_objLabelsPrinted.Push m_strLastLabel
         '  pull out the next label in que if was bad...
         ' code commented out *** llj 1/7/98
         
'         If g_blnBadLabel Then
'            m_objLabelsPrinted.Pull
'         End If
'         m_objLabelsPrinted.Push m_strLastLabel
         frmHistory.Message "Printed: " & m_strLastLabel
      
      End If
   End If

   Exit Sub

OnBit_NextLabel_Error:

   ProccessError "OnBit_NextLabel", m_strName, Err.Number, Err.Description

End Sub 'NextLabel

Public Sub PrintTestLabel()

   #If ccShip_Ver Then
      On Error Resume Next
   #Else
      On Error GoTo 0
   #End If
   
   PrintLabel LoadResString(resTEST_LABEL)

End Sub 'PrintTestLabel

Private Sub OnBit_ManualFeed(blnValue)
   
   Static intMesgNumber As Integer
   
   #If ccShip_Ver Then
      On Error GoTo OnBit_ManualFeed_Error
   #Else
      On Error GoTo 0
   #End If
    
   g_blnManualFeed = blnValue
   g_blnQueueOK = False
   
   If g_blnManualFeed Then
      '  display message
      intMesgNumber = m_objMainForm.MessageDisplay(LoadResString(resMANUAL_FEED_MSG))
       g_blnManualFeed = True
    '  m_objMainForm.MessageRemove intMesgNumber
   Else
      '  Remove message
      g_blnManualFeed = False
      
      m_objMainForm.MessageRemove intMesgNumber
        
   End If

   Exit Sub

OnBit_ManualFeed_Error:

   ProccessError "OnBit_ManualFeed", m_strName, Err.Number, Err.Description

End Sub 'ManualFeed

Private Function GetNextLabel() As String
'  bulid label of
'  yywwSPsnsnsn
'  aywwnnnnn - new format for board handler - rfv
   #If ccShip_Ver Then
      On Error GoTo GetNextLabel_Error
   #Else
      On Error GoTo 0
   #End If
    
   Dim strTmpBuff As String
   Dim strTmpHandler As String ' added to hold board handler character - rfv
   GetLabelInfo
   GetPWBDesignator

  With m_udtCurrentJob
      strTmpHandler = Left(.strPWBDesignator, m_udtLabelDesc.PrefixWidth)  ' get first character of
                                               ' JobsDiscription field for handler - rf
      strTmpBuff = strTmpHandler & Right(.strYearCode, m_udtLabelDesc.YearCodeWidth) & Right(.strWeekCode, m_udtLabelDesc.WeekCodeWidth)
      ' get the right 5 digits only to allow for dash numbers - rfv
      m_strSerialNumber = Format(CLng(Right(m_strSerialNumber, m_udtLabelDesc.SerialNumberWidth)) + 1, m_fmtSERIAL_NUMBER)
      ' end of changed code - rfv
      strTmpBuff = strTmpBuff & m_strSerialNumber
   End With 'm_udtCurrentJob
     
   'Added savelastserialnumber 11/13/97 llj
   SaveLastSerialNumber
   GetNextLabel = strTmpBuff
   
   Exit Function

GetNextLabel_Error:

   ProccessError "GetNextLabel", m_strName, Err.Number, Err.Description
   GetNextLabel = False

End Function 'GetNextLabel

Public Sub OnBit_LabelApplied(blnValue As Boolean)
Dim objQueue As Object
Static nCounter As Integer
   Static s_blnScanning As Boolean
   Set objQueue = New clsQueue
   Dim strTemp As String
   Dim strScannedLabel As String
   #If ccShip_Ver Then
      On Error GoTo OnBit_LabelApplied_Error
   #Else
      On Error GoTo 0
   #End If
   nCounter = 0
   If Not g_blnJobRunning Then Exit Sub
   
   '  set scanned pass / fail bits to false
   m_objDigIO.Bit(m_intLABEL_PASS) = False
   m_objDigIO.Bit(m_intLABEL_FAIL) = False
 '  m_objDigIO.Bit(m_intROTATE_90) = False '(m_udtDataPoints(m_intLabelPrinted).strThataApply = "90")
      
   If blnValue And (Not s_blnScanning) Then
      s_blnScanning = True
      
      '  scan label
      frmMain.MessageClear
      'code????
      strTemp = m_objscanner.ReadlBarCode
      strScannedLabel = strTemp
      frmHistory.Message "Scaned: " & strTemp
      modUtilities.InstructionsRemove ' make sure the instruction box is removed
    '  m_objLabelsPrinted.ReSync (strTemp)
      With m_objDigIO
         '  if scanned ok...
         frmHistory.Message "In Q: " & strTemp
'         If objQueue.StrCompare(strTemp, m_strLastLabel) Then
         'code????
         'If objQueue.StrCompare(m_strLastLabel, m_strLastLabel) Then
          If (strTemp = m_strLastLabel) Then
            '  Labeled passed
            .Bit(m_intLABEL_PASS) = True
            '  Display th label scaned
            nCounter = nCounter + 1
            m_objMainForm.labTextScaned.Caption = strTemp
            m_objMainForm.labTextPrinted.Caption = m_strLastLabel
            '  Add to DB and pull it form the Q
            UpdateSerialNumberDB strTemp
                     
            m_intLabelPrinted = m_intLabelPrinted + 1
            Debug.Print "OnBit_LabelApplied ", m_intLabelPrinted
            ' comment out BadLabel *** llj 1/7/98
            g_blnBadLabel = False
         Else 'Label failed to scan so ...
            If (strTemp = "NOREAD") Then
                .Bit(m_intLABEL_FAIL) = True
                modUtilities.InstructionsDisplay m_udtConfig.strBadScanFileName
                m_objMainForm.labTextScaned.Caption = strScannedLabel
                m_objMainForm.labTextPrinted.Caption = strTemp
                  
            Else
              .Bit(m_intLABEL_FAIL) = True
'removed for project
                modUtilities.InstructionsDisplay m_udtConfig.strBadScanFileName
                m_objMainForm.labTextScaned.Caption = strScannedLabel
                m_objMainForm.labTextPrinted.Caption = strTemp
            End If
            
            
            ' code replaced with following stmt *** llj 1/7/98
            g_blnBadLabel = True
            
'       m_objLabelsPrinted.Pull
     
         End If
      End With 'm_objDigIO
      s_blnScanning = False
   End If
   Set objQueue = Nothing
   Exit Sub

OnBit_LabelApplied_Error:

   ProccessError "OnBit_LabelApplied", m_strName, Err.Number, Err.Description

End Sub 'LabelApplied

Private Sub UpdateSerialNumberDB(strLastLabel As String)

   #If ccShip_Ver Then
      On Error GoTo UpdateSerialNumberDB_Error
   #Else
      On Error GoTo 0
   #End If
 
   m_tblLabelApplied.AddNew
   'code????
   m_tblLabelApplied![SerialNumber] = "test" 'strLastLabel
   m_tblLabelApplied![Comcode] = m_udtCurrentJob.strPartNumber
   m_tblLabelApplied![TimeStamp] = Now
   m_tblLabelApplied.Update
   
   Exit Sub

UpdateSerialNumberDB_Error:

   ProccessError "UpdateSerialNumberDB", m_strName, Err.Number, Err.Description
  
End Sub 'UpdateSerialNumberDB

   
Private Sub OnBit_PanelComplete(blnValue As Boolean)
   
   #If ccShip_Ver Then
      On Error GoTo OnBit_PanelComplete_Error
   #Else
      On Error GoTo 0
   #End If
    
   If blnValue Then
      m_intLabelPrinted = 21
      m_objDigIO.Bit(m_intPAUSE) = True
      
      If m_blnQtyCountUP Then
         m_lngPanelQuintityCount = m_lngPanelQuintityCount + 1
      Debug.Print "New Panel"
      Else
         m_lngPanelQuintityCount = m_lngPanelQuintityCount - 1
         Debug.Print "Job Complete"
         If m_lngPanelQuintityCount = 0 Then
            MsgBox LoadResString(resJOB_COMPLETE_MSG), vbOKOnly + vbInformation, LoadResString(resJOB_COMPLETE_TITLE)
            m_blnQtyCountUP = True '   reset the panal count up flag
            RunStopJob
         End If
      End If
      m_objMainForm.PanelComplete CStr(m_lngPanelQuintityCount)
   
   Else
         m_objDigIO.Bit(m_intPAUSE) = False

   End If
   
   Exit Sub

OnBit_PanelComplete_Error:

   ProccessError "OnBit_PanelComplete", m_strName, Err.Number, Err.Description

End Sub 'PanelComplete

Private Sub OnBit_ApplactorBypass(blnValue As Boolean)

   Static intMesgNumber As Integer
   
   #If ccShip_Ver Then
      On Error GoTo OnBit_ApplactorBypass_Error
   #Else
      On Error GoTo 0
   #End If
    
   If blnValue And (Not g_blnBypassMode) Then
      intMesgNumber = m_objMainForm.MessageDisplay(LoadResString(resAPPLICATOR_BYPASS))
      m_objMainForm.JobInterrupted True
      g_blnBypassMode = True
   ElseIf g_blnBypassMode And (Not blnValue) Then
      m_objMainForm.MessageRemove intMesgNumber
      g_blnBypassMode = False
      m_objMainForm.JobInterrupted _
                     (g_blnBypassMode And _
                      g_blnGardDoorsOpen And _
                      g_blnAirLoss)
   End If
   
   Exit Sub

OnBit_ApplactorBypass_Error:

   ProccessError "OnBit_ApplactorBypass", m_strName, Err.Number, Err.Description

End Sub 'ApplactorBypass

Private Sub OnBit_LabelPickupError(blnValue As Boolean)

   Static intMesgNumber As Integer

   #If ccShip_Ver Then
      On Error GoTo OnBit_LabelPickupError_Error
   #Else
      On Error GoTo 0
   #End If
    If blnValue Then
      intMesgNumber = m_objMainForm.MessageDisplay(LoadResString(resLABEL_PICKUP_ERROR))
      m_objMainForm.JobInterrupted True
      modUtilities.InstructionsDisplay m_udtConfig.strBadlabelPickupFileName
      'If g_blnClearingQue Then changed code 03-18-98
      If g_blnClearingQue Then
         m_objLabelsPrinted.Pull
      End If
   Else
      
  '    m_objLabelsPrinted.Pull  '03-18-98
      
      m_objMainForm.MessageRemove intMesgNumber
      m_objMainForm.JobInterrupted _
                     (g_blnBypassMode And _
                      g_blnGardDoorsOpen And _
                      g_blnAirLoss)
   End If
   
   Exit Sub

OnBit_LabelPickupError_Error:

   ProccessError "OnBit_LabelPickupError", m_strName, Err.Number, Err.Description

End Sub 'LabelPickupError

Private Sub OnBit_PanelReady(blnValue As Boolean)

   #If ccShip_Ver Then
      On Error GoTo OnBit_PanelReady_Error
   #Else
      On Error GoTo 0
   #End If
    
   If blnValue Then
      m_objMainForm.PanelReady
   End If
   
   Exit Sub

OnBit_PanelReady_Error:

   ProccessError "OnBit_PanelReady", m_strName, Err.Number, Err.Description

End Sub 'Panelready

Private Sub OnBit_GardDoorsOpen(blnValue As Boolean)

   Static intMesgNumber As Integer
   
   #If ccShip_Ver Then
      On Error GoTo OnBit_GardDoorsOpen_Error
   #Else
      On Error GoTo 0
   #End If
    
   If blnValue Then
      intMesgNumber = m_objMainForm.MessageDisplay(LoadResString(resGUARD_DOOR_OPEN))
      m_objMainForm.JobInterrupted True
      frmHistory.Message "Gard doors open!"
      MsgBox LoadResString(resGUARD_DOOR_OPEN_MSG), vbOKOnly + vbCritical, LoadResString(resOPERATION_ERROR_TITLE)
      RunStopJob
   End If
   
   Exit Sub

OnBit_GardDoorsOpen_Error:

   ProccessError "OnBit_GardDoorsOpen", m_strName, Err.Number, Err.Description

End Sub 'GardDoorsOpen

Private Sub OnBit_HoldSwitch(blnValue As Boolean)

   Static intMesgNumber As Integer
   
   #If ccShip_Ver Then
      On Error GoTo OnBit_HoldSwitch_Error
   #Else
      On Error GoTo 0
   #End If
    
   g_blnHoldSwitch = blnValue
   
   With m_objMainForm
      If g_blnHoldSwitch Then
         intMesgNumber = .MessageDisplay(LoadResString(resHOLD_MODE))
         .JobHolding True
      Else
         
         g_blnManualFeed = False
         
         .MessageRemove intMesgNumber
         .JobHolding False
      End If
   End With 'm_objMainForm
   
   Exit Sub

OnBit_HoldSwitch_Error:

   ProccessError "OnBit_HoldSwitch", m_strName, Err.Number, Err.Description

End Sub 'HoldSwitch

Private Sub OnBit_AirPressurLoss(blnValue As Boolean)

   #If ccShip_Ver Then
      On Error GoTo OnBit_AirPressurLoss_Error
   #Else
      On Error GoTo 0
   #End If
 
   Static intMesgNumber As Integer
   
   If Not blnValue Then
      intMesgNumber = m_objMainForm.MessageDisplay(LoadResString(resAIR_PRESSURE_LOSS))
      m_objMainForm.JobInterrupted True
      frmHistory.Message "Air pressure lost!"
      MsgBox LoadResString(resAIR_LOSS_MSG), vbOKOnly + vbCritical, LoadResString(resOPERATION_ERROR_TITLE)
      RunStopJob
   End If
   
   Exit Sub

OnBit_AirPressurLoss_Error:

   ProccessError "OnBit_AirPressurLoss", m_strName, Err.Number, Err.Description

End Sub 'AirPressurLoss





Private Function OpenLogingDB()

   #If ccShip_Ver Then
      On Error GoTo OpenLogingDB_Error
   #Else
      On Error GoTo 0
   #End If
 
   With m_udtCurrentJob
      '  Open the Serinal number database for loging
      
      ChDir App.Path
      Set m_dbLabelApplied = Workspaces(0).OpenDatabase(.strDBPath)
      Set m_tblLabelApplied = m_dbLabelApplied.OpenRecordset(.strTableName, dbOpenTable)
   End With 'm_udtCurrentJob
      
      OpenLogingDB = True
   
      Exit Function
      
OpenLogingDB_Error:

   ProccessError "OpenLogingDB", m_strName, Err.Number, Err.Description
   OpenLogingDB = False
   
End Function 'OpenLogingDB

Private Function SetDigIOBits() As Boolean

   Dim idx As Integer
   Dim blnValue As Boolean
   
   #If ccShip_Ver Then
      On Error GoTo SetDigIOBits_Error
   #Else
      On Error GoTo 0
   #End If
   
   '  go through the bits to see how setup
   For idx = 1 To UBound(ma_udtDigitialIO)
      With ma_udtDigitialIO(idx)
         If .strDirection = g_strOUTPUT Then
            ' and set to false if an output
            m_objDigIO.Bit(.intBitNum) = False
         End If
      End With 'ma_udtDigitialIO(idx)
   Next idx
   
   SetDigIOBits = True
   
   Exit Function

SetDigIOBits_Error:

   ProccessError "SetDigIOBits", m_strName, Err.Number, Err.Description
   SetDigIOBits = False
   
End Function 'SetDigIOBits


Private Function InitJob()
 
   Dim blnStatus As Boolean
   Dim intLabels As Integer

   #If ccShip_Ver Then
      On Error GoTo InitJob_Error
   #Else
      On Error GoTo 0
   #End If
    
   blnStatus = True
      
   With m_udtCurrentJob
      'load point table
      blnStatus = blnStatus And LoadPointTable(strJobID:=.strName, r_intLabels:=intLabels)
      
      '  Send number of labels per panel to IAI
      blnStatus = blnStatus And m_objIAICtrl.SendLabelsPerPanel( _
                                 strPROGRAM_NUMBER:=m_strPROGRAM_NUMBER, _
                                 txtBoardCountCodeStep:=m_udtConfig.txtBoardCountCodeStep, _
                                 intLabels:=intLabels + m_udtConfig.intPointDataTableOffset)
   End With 'm_udtCurrentJob
   
   modUtilities.MessageDisplay LoadResString(resLOADING_PRINTER_DATA)
   With m_udtCurrentPrinterTemplate
      blnStatus = blnStatus And m_objPrinter.SendTemplate( _
                              strTemplate:=.strTemplate, _
                              strFormatName:=.strFormatName, _
                              strTemplatePath:=.strTemplatePath)
   End With 'a_vntPrinterTemplate
   
   InitJob = blnStatus
   
   Exit Function

InitJob_Error:

   ProccessError "InitJob", m_strName, Err.Number, Err.Description
   InitJob = False

End Function 'InitJob

Private Function ProcessNewWeek() As Boolean

   Dim dbLabelerDataBase As Database
   Dim dynDateData As Recordset
   Dim qdfJobPNSN As QueryDef
   Dim dynJobPNSN  As Recordset
   Dim strTmpWeek As String
   Dim strTmpYear As String
   Dim strTitle As String
   Dim strMessage As String
   Dim intResp As Integer
   Dim strTemp As String
   
   #If ccShip_Ver Then
      On Error GoTo ProcessNewWeek_Error
   #Else
      On Error GoTo 0
   #End If
 
   ProcessNewWeek = False
   
   
   '  Open up the database
   Set dbLabelerDataBase = Workspaces(0).OpenDatabase(modMain.JobDatabaseName)

   '  get the configuration data
   Set dynDateData = dbLabelerDataBase.OpenRecordset(modMain.GetDateData, dbOpenDynaset)
      
   If IsNull(dynDateData![YearCode]) Or IsNull(dynDateData![WeekCode]) Then
      Err.Raise g_errERR_NULL_CONFIG_DATA, , LoadResString(resERR_NULL_CONFIG_DATA)
   End If
   
   '  Get the current year and week form the PC
   strTmpWeek = dynDateData![WeekCode]
   strTmpYear = dynDateData![YearCode]
   
   '  move the week
   strTmpWeek = Format(CInt(strTmpWeek) + 1, "00")
   
   
   '  start the edit process
   dynDateData.Edit
   
   '  is it the 53 week and The year is the same then
   If strTmpWeek = "73" Then
      
      strTitle = LoadResString(resEND_OF_YEAR_TITLE)
      strMessage = LoadResString(resEND_OF_YEAR_MESSAGE)
      intResp = MsgBox(strMessage, vbYesNo + vbQuestion, strTitle)
      '  if now start next year...
      If intResp = vbNo Then
         
         dynDateData![WeekCode] = dynDateData![InitialWeekCode]
         strTemp = Format(Str(CInt(strTmpYear) + 1), "00")

         If Len(strTemp) > 2 Then
            
            strTemp = Mid(strTemp, 2, 2)
         End If
         dynDateData![YearCode] = strTemp 'Format(CInt(strTmpYear) + 1, "00")
      
      Else
         
         dynDateData![WeekCode] = strTmpWeek
      
      End If
   ElseIf strTmpWeek = "74" Then
      
      dynDateData![WeekCode] = dynDateData![InitialWeekCode]
      strTemp = Format(Str(CInt(strTmpYear) + 1), "00")
      
      If Len(strTemp) > 2 Then
         strTemp = Mid(strTemp, 2, 2)
      End If
      
     
      dynDateData![YearCode] = strTemp 'Format(CInt(strTmpYear) + 1, "00")
   
   Else
      dynDateData![WeekCode] = strTmpWeek
   
   End If

   '  need to reset global serial numbers
   
   dynDateData![LastSerialNumber] = dynDateData![InitialSerialNumber]
   
   '  now update the global db
   dynDateData.Update
   
   '  reset set each job serial number for each job
   Set dynJobPNSN = dbLabelerDataBase.OpenRecordset(modMain.AllJobsSerNumData, dbOpenDynaset)
   Do '  the part number serial number is not null so init
      
      dynJobPNSN.Edit
      dynJobPNSN![LastSerialNumber] = dynJobPNSN![SerilNumberStart]
      
      dynJobPNSN.Update
  
      dynJobPNSN.MoveNext
   Loop Until dynJobPNSN.EOF
   
   '  done so close the db and leave
   dbLabelerDataBase.Close

   g_blnQueueOK = False
   
   ProcessNewWeek = True
   
   Exit Function

ProcessNewWeek_Error:
   Close #23
   ProccessError "ProcessNewWeek", m_strName, Err.Number, Err.Description
   
End Function 'ProcessNewWeek

Private Sub SaveLastSerialNumber()

   Dim dbLabelerDataBase As Database
   Dim dynDateData As Recordset
   Dim qdfJobPNSN As QueryDef
   Dim dynJobPNSN  As Recordset

   #If ccShip_Ver Then
      On Error GoTo SaveLastSerialNumber_Error
   #Else
      On Error GoTo 0
   #End If

   '  Open up the database
   Set dbLabelerDataBase = Workspaces(0).OpenDatabase(modMain.JobDatabaseName)
   
   '  get the configuration data
   Set dynDateData = dbLabelerDataBase.OpenRecordset(modMain.GetDateData, dbOpenDynaset)
      
   '  Now save the last serial numbers
      
   If dynDateData![UseGlobalPN] Then
      dynDateData.Edit
      dynDateData![LastSerialNumber] = m_strSerialNumber
      dynDateData.Update
   Else
      '  Get the job data data
      Set qdfJobPNSN = dbLabelerDataBase.QueryDefs(modMain.JobSerNumData)
      qdfJobPNSN.Parameters![JobsName] = m_udtCurrentJob.strName
      Set dynJobPNSN = qdfJobPNSN.OpenRecordset(dbOpenDynaset)
      '  save the latest serial number
      dynJobPNSN.Edit
      dynJobPNSN![LastSerialNumber] = m_strSerialNumber
      dynJobPNSN.Update
      '  Save it in current job if needed agen
      m_udtCurrentJob.strLastSerialNumber = m_strSerialNumber
   End If
   
   dbLabelerDataBase.Close
   
   Exit Sub

SaveLastSerialNumber_Error:

   ProccessError "SaveLastSerialNumber", m_strName, Err.Number, Err.Description

End Sub 'SaveLastSerialNumber

Private Function SetDateSN() As Boolean

   Dim dtNow As Date
   
   #If ccShip_Ver Then
      On Error GoTo SetDateSN_Error
   #Else
      On Error GoTo 0
   #End If
   
   '  use the vb data funciton to see if we went to a new week.
   dtNow = Now ' make sure using the same date
   'X = ProcessNewWeek()
   If Format(dtNow, "ww", vbMonday) = GetSetting(App.EXEName, g_strJOB_STUFF, m_strWEEK_SET, "00") Then
      SetDateSN = ProcessDateSN()
   Else
      If ProcessNewWeek() Then
         SetDateSN = ProcessDateSN()
         SaveSetting App.EXEName, g_strJOB_STUFF, m_strWEEK_SET, Format(dtNow, "ww", vbMonday)
      Else
         SetDateSN = False
      End If
      SaveSetting App.EXEName, g_strJOB_STUFF, m_strWEEK_SET, Format(dtNow, "ww", vbMonday)
   End If
   
   Exit Function

SetDateSN_Error:

   ProccessError "SetDateSN", m_strName, Err.Number, Err.Description
   SetDateSN = False

End Function 'SetDateSN

Private Function ProcessDateSN() As Boolean

   Dim dbLucentData As Database
   Dim snpDateSN As Recordset
   
   #If ccShip_Ver Then
      On Error GoTo ProcessDateSN_Error
   #Else
      On Error GoTo 0
   #End If
   
   ProcessDateSN = False
   
   '  Open up the database
   Set dbLucentData = Workspaces(0).OpenDatabase(modMain.JobDatabaseName)
   
   '  get the configuration data
   Set snpDateSN = dbLucentData.OpenRecordset(modMain.GetConfiguration, dbOpenSnapshot)
   
   '  get the week and year code, if the plant code is null get that also
   With m_udtCurrentJob
      .strYearCode = snpDateSN![YearCode]
      .strWeekCode = snpDateSN![WeekCode]
      ' comment out defaultplantcode - llj 12/02/97
     ' If .strPlantCode = "" Then
      '   .strPlantCode = snpDateSN![DefalutePlantCode]
     ' End If
     
   
      '  if the global pn is to be used...
      If snpDateSN![UseGlobalPN] Then
         m_blnUseGlobalSN = True
         m_strSerialNumber = snpDateSN![LastSerialNumber]
      Else '   each part number has its own
         m_strSerialNumber = .strLastSerialNumber
         m_blnUseGlobalSN = False
      End If
   End With 'm_udtCurrentJob
   
   dbLucentData.Close
   
   ProcessDateSN = True
   
   Exit Function

ProcessDateSN_Error:

   ProccessError "ProcessDateSN", m_strName, Err.Number, Err.Description
   ProcessDateSN = False
   
End Function 'ProcessDateSN

Private Sub QueueStart()

   #If ccShip_Ver Then
      On Error GoTo QueueStart_Error
   #Else
      On Error GoTo 0
   #End If
    
   '  Start queue for printer
   ' code added *** llj 1/7/98
   QueueStop
   Set m_objLabelsPrinted = New clsQueue
      
   '  Tell the IAI to start the que
 '  m_objDigIO.Bit(m_intCLEAR_Q) = True
   g_blnClearingQue = True
   
   '  Set the queue to ok
   g_blnQueueOK = True
      
   Exit Sub

QueueStart_Error:

   ProccessError "QueueStart", m_strName, Err.Number, Err.Description

End Sub 'QueueStart

Private Sub QueueStop()
   
   #If ccShip_Ver Then
      On Error Resume Next
   #Else
      On Error GoTo 0
   #End If
    
   Set m_objLabelsPrinted = Nothing
   g_blnQueueOK = False
   
End Sub 'QueueStop

Private Sub OnBit_ConveyorError(blnValue As Boolean)

   Static intMesgNumber As Integer
   
   #If ccShip_Ver Then
      On Error GoTo OnBit_ConveyorError_Error
   #Else
      On Error GoTo 0
   #End If
    
   If blnValue Then
      intMesgNumber = m_objMainForm.MessageDisplay(LoadResString(resCONVEYOR_ERROR))
      m_objMainForm.JobInterrupted True
      frmHistory.Message "Conveyro Error!"
      MsgBox LoadResString(resCONVEYOR_ERROR_MSG), vbOKOnly + vbCritical, LoadResString(resOPERATION_ERROR_TITLE)
      RunStopJob
   End If

   Exit Sub

OnBit_ConveyorError_Error:

   ProccessError "OnBit_ConveyorError", m_strName, Err.Number, Err.Description

End Sub 'OnBit_ConveyorError


Public Sub GetPWBDesignator()
   #If ccShip_Ver Then
      On Error GoTo GetPWBDesignator_Error
   #Else
      On Error GoTo 0
   #End If

Dim objDB As Database
Dim objRS As Recordset


Set objDB = Workspaces(0).OpenDatabase(modMain.JobDatabaseName)
Set objRS = objDB.OpenRecordset _
            ("Select PWBDesignator from tbljobfile " & _
             "where JobsName = " & "'" & m_udtCurrentJob.strName & "'")

m_udtCurrentJob.strPWBDesignator = objRS.Fields![PWBDesignator]


objRS.Close
objDB.Close
Set objDB = Nothing
Set objRS = Nothing


Exit Sub


GetPWBDesignator_Error:
    
    ProccessError "Error in clsLabeler", "GetPWBDesignator", 666, "Can not find PWBDesignator Field or Value in tblJobFile Table"
    objRS.Close
    objDB.Close
    Set objDB = Nothing
    Set objRS = Nothing


End Sub

Public Sub GetLabelInfo()

Dim objDB As Database
Dim objRS As Recordset
Dim strErrorMessage As String
On Error GoTo LabelInfoError

'm_udtCurrentJob.strJobID = "L1"

Set objDB = Workspaces(0).OpenDatabase(modMain.JobDatabaseName)
Set objRS = objDB.OpenRecordset _
            ("Select * from LabelDesign " & _
             "where JobName = " & "'" & "L1" & "'")

strErrorMessage = "Missing value for JobName in Labelinfo table. "
m_udtLabelDesc.JobName = objRS.Fields![JobName]

strErrorMessage = "Missing value for PrefixWidth in Labelinfo table. "
m_udtLabelDesc.PrefixWidth = objRS.Fields![PrefixWidth]

strErrorMessage = "Missing value for YearCodeWidth in Labelinfo table. "
m_udtLabelDesc.YearCodeWidth = objRS.Fields![YearCodeWidth]

strErrorMessage = "Missing value for WeekCodeWidth in Labelinfo table. "
m_udtLabelDesc.WeekCodeWidth = objRS.Fields![WeekCodeWidth]

strErrorMessage = "Missing value for SerialNumberWidth in Labelinfo table. "
m_udtLabelDesc.SerialNumberWidth = objRS.Fields![SerialNumberWidth]



objRS.Close
objDB.Close
Set objDB = Nothing
Set objRS = Nothing
Exit Sub
LabelInfoError:
    ProccessError "Error in clsLabeler", "GetLabelInfo", 666, strErrorMessage
    objRS.Close
    objDB.Close
    Set objDB = Nothing
    Set objRS = Nothing


End Sub



