Attribute VB_Name = "modMain"
'************************************************************************
'*           Computype, Inc.
'*       NextStep Automation Group
'*
'*     © Copywrite 1997 Computype, Inc.
'*
'*        3-Axis Label Applicator
'*           Control software
'*             Main module
'*
'*
'*    Customer: Lucent Technologies
'*              Shreveport, LA
'*
'*
'*    Date of origin: 1/21/97
'*    Original author: Michael D. Reed
'*
'* Module purpose:
'*    This module porvides the entery point into the
'*    3-Axis Label Applicator upon start up.  It also contains
'*    any global constants, variables.
'*
'************************************************************************
Option Explicit

'************************************************************************
'  Public stuff
'added 09/30/98
Public g_blnSimulator As Boolean
Public g_strCONCODE As String

'  global constents



Public Const g_strJOB_STUFF = "JobStuff"
Public Const g_strLUCENT_DB_NAME = "LucentTechSP.mdb"
Public Const g_strDB_EXT = "mdb"

'  Labeler run flags
Public g_blnJobRunning As Boolean
Public g_blnJobReady As Boolean
Public g_blnManualFeed As Boolean
Public g_blnPrintingLabel As Boolean
Public g_blnClearingQue As Boolean
Public g_blnBypassMode As Boolean
Public g_blnGardDoorsOpen As Boolean
Public g_blnConveyorError As Boolean
Public g_blnHoldSwitch As Boolean
Public g_blnAirLoss As Boolean
'comment out BadLabel *** llj 1/7/98
'Public g_blnBadLabel As Boolean
Public g_blnQueueOK As Boolean

Public g_intMaxPCBRunQuantity As Integer

Public g_strLabelerVersion As String
Public g_strLabelPrintVersion As String
Public g_strMicroScanerVersion As String
Public g_strIAIControlerVersion As String
Public g_strCompuBoardVersion As String

'************************************************************************
'  Private stuff
'  Private refrences items
Private m_objLabeler As clsLabeler
Private m_objLabelPrint As clsLabelPrint
Private m_objIAICtrl As clsMotionControl
Private m_objMicroscanCtrl As clsMicroscan
Private m_strLabelerIOPorts As String
Private m_objDigitalIO As clsDigitalIO

'  local constents
Private Const m_strJOB_DB_NAME = "JobDatabaseName"
Private Const m_strJOB_DB_FILE = "JobDatabaseFile"
'  local data
Private m_dbConfgurationDataBaseName As String
Private m_dbLucentDataBaseName As String
Private m_strJobDatabaseFile As String
Private m_dbJobFileDataBaseName As String
Private m_strDigitalIO As String
Private m_strDataPoints As String
Private m_tblConfiguration As String
Private m_strGetDateData As String
Private m_strJobSerNumData As String
Private m_strAllJobsSerNumData As String

Public Function GetDateData() As String
   
   GetDateData = m_strGetDateData
   
End Function 'GetDateData

Public Function GetLabelerIOPorts() As String

   GetLabelerIOPorts = m_strLabelerIOPorts
   
End Function 'GetLabelerIOPorts


Private Sub SetDefaults()

   g_intMaxPCBRunQuantity = 16000
   
   
   m_dbConfgurationDataBaseName = App.Path & "\Labeler.mdb"
   m_dbLucentDataBaseName = App.Path & "\" & g_strLUCENT_DB_NAME
   
   m_strLabelerIOPorts = "qurDigitalSignal"
   m_strDataPoints = "qurJADataPointInfo"
   m_tblConfiguration = "tblConfiguration"
   m_strDigitalIO = "qurDigitalIO"
   m_strGetDateData = "qurDateData"
   m_strJobSerNumData = "pqrJobSerNumData"
   m_strAllJobsSerNumData = "qurAllJobSerNumData"
   
   g_blnTest = False
   g_blnLog = False
   
End Sub 'SetDefaults


Public Sub Main()

   #If ccShip_Ver Then  'Set up error handler for shiped version
      On Error GoTo Main_Error
   #Else
      On Error GoTo 0
   #End If
   
   
   #If cc_Simulation Then   'Set up for simulation mode
       g_blnSimulator = True
   #End If
   

   frmSplash.Show
   
   SetDefaults
   
   ProcessProfile
   
   ProcessCommanedLine
   
   
   '  load the spiclized message box.
   frmMessage.Hide
   
   '  load the history window
   SetMonitorForm frmHistory
   
   '  Initialize the IAI class and contrler
   frmSplash.PanelMotion LoadResString(resMSG_INIT_IAI)
   frmHistory.Message LoadResString(resMSG_INIT_IAI)
   Set m_objIAICtrl = New clsMotionControl
   If m_objIAICtrl.InitStatus Then
      frmSplash.PanelMotion LoadResString(resMSG_INIT_IAI_OK)
   Else
      frmSplash.InitError LoadResString(resERR_IAI_NO_INIT)
      ExitEnd
   End If
   
   '  Initialize Microscaner
   frmSplash.PanelScanner LoadResString(resMSG_INIT_SCANNER)
   Set m_objMicroscanCtrl = New clsMicroscan
   If m_objMicroscanCtrl.InitStatus Then
      frmSplash.PanelScanner LoadResString(resMSG_INIT_SCANNER_OK)
   Else
      frmSplash.InitError LoadResString(resERR_SCANNER_NO_INIT)
      ExitEnd
   End If
   
   '  Initialize CompuBoard Digitial I/O
   frmSplash.PanelDigital LoadResString(resMSG_INIT_DIG_IO)
   Set m_objDigitalIO = New clsDigitalIO
   If m_objDigitalIO.InitStatus Then
      frmSplash.PanelDigital LoadResString(resMSG_INIT_DIG_OK)
   Else
      frmSplash.InitError LoadResString(resERR_DIG_NO_INIT)
      ExitEnd
   End If
   
   '  Initialize the Printer class
   frmSplash.PanelPrint LoadResString(resMSG_INIT_PRINT)
   Set m_objLabelPrint = New clsLabelPrint
   If m_objLabelPrint.InitStatus Then
      frmSplash.PanelPrint LoadResString(resMSG_INIT_PRINT_OK)
   Else
      frmSplash.InitError LoadResString(resERR_PRINTER_NO_INIT)
      ExitEnd
   End If
   
   '  Init main labeler class
   frmSplash.PanelLabeler LoadResString(resMSG_INIT_LABELER)
   Set m_objLabeler = New clsLabeler
   m_objLabeler.Initialize objIAICtrl:=m_objIAICtrl, _
                           objScanner:=m_objMicroscanCtrl, _
                           objDigIO:=m_objDigitalIO, _
                           objPrinter:=m_objLabelPrint
   If m_objLabeler.InitStatus Then
      frmSplash.PanelLabeler LoadResString(resMSG_INIT_LABELER_OK)
   Else
      frmSplash.InitError LoadResString(resERR_IAI_NO_INIT)
      ExitEnd
   End If
   
   '  Now load the main form
   frmMain.Hide
   
   If frmMain.Initialize(objLabeler:=m_objLabeler, objPrinter:=m_objLabelPrint) Then
      frmMain.Show
      Unload frmSplash
   Else
      frmSplash.InitError "Main form failed to initialize."
      ExitEnd
   End If
   
   Exit Sub
   
Main_Error:

   ProccessError "Main", "modMain", Err.Number, Err.Description
   ExitEnd
   
End Sub 'Main


Public Sub ProcessCommanedLine()

   #If ccShip_Ver Then
      On Error Resume Next
   #Else
      On Error GoTo 0
   #End If

   If Command = "" Then Exit Sub
   
   g_blnTest = (Command Like "*[/+-][tT]*")
   g_blnLog = (Command Like "*[/+-][lL]*")
   
End Sub 'ProcessCommanedLine

Public Function ProcessProfile()

   #If ccShip_Ver Then
      On Error Resume Next
   #Else
      On Error GoTo 0
   #End If

   ProcessProfile = True
   
'   m_dbLucentDataBaseName = GetSetting(App.EXEName, g_strJOB_STUFF, m_strJOB_DB_NAME, m_dbLucentDataBaseName)
'   m_strJobDatabaseFile = GetSetting(App.EXEName, g_strJOB_STUFF, m_strJOB_DB_FILE, m_strJobDatabaseFile)
   
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

   Close ' close any files which may be open
   If g_blnTest Then
      End
   Else
      m_objIAICtrl.SendReset
      End
   
   End If
   
End Sub 'ExitEnd

Public Function GetDataPoints()

   GetDataPoints = m_strDataPoints
   
End Function 'GetDataPoints

Public Function GetConfiguration() As String

   GetConfiguration = m_tblConfiguration
   
End Function 'GetConfiguration

Public Function GetDigitalIO() As String

   GetDigitalIO = m_strDigitalIO

End Function 'GetDigitalIO

Public Function JobSerNumData()

   JobSerNumData = m_strJobSerNumData

End Function 'JobSerNumData

Public Function AllJobsSerNumData() As String
   
   AllJobsSerNumData = m_strAllJobsSerNumData
   
End Function 'AllJobsSerNumData


Public Property Get JobDatabaseName() As String

   JobDatabaseName = m_dbLucentDataBaseName

End Property 'Get JobDatabaseName

Public Property Let JobDatabaseName(vNewValue As String)

   m_dbLucentDataBaseName = vNewValue
   SaveSetting App.EXEName, g_strJOB_STUFF, m_strJOB_DB_NAME, vNewValue

End Property 'Let JobDatabaseName

Public Property Get JobDatabaseFile() As String

   JobDatabaseFile = m_strJobDatabaseFile
   
End Property ' Get JobDatabaseFile

Public Property Let JobDatabaseFile(vNewValue As String)

   m_strJobDatabaseFile = vNewValue
   SaveSetting App.EXEName, g_strJOB_STUFF, m_strJOB_DB_FILE, vNewValue
   
End Property ' Let JobDatabaseFile
