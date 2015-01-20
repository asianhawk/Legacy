Attribute VB_Name = "modDigitalConstants"
'************************************************************************
'*           Computype, Inc.
'*       NextStep Automation Group
'*
'*     © Copywrite 1997 Computype, Inc.
'*
'*        2-Axis Label Applicator
'*           Control Subsystem
'*
'*          Digital Constents
'*
'*    Date of origin: June 24,1997
'*    Original author: Michael D. Reed
'*
'*    Module purpose:
'*       This module contains the constants variables used by the digital subsystem.
'*
'************************************************************************
Option Explicit
Public g_lDataValue As Long

' Signal types
Public Const NotUsed = 0
Public Const g_intVALUE = 1       'Value only
'  Inputs
Public Const g_intTRANSITION = 3    'On transition
Public Const g_intTRANS_TRUE = 4    'On positive transition
Public Const g_intTRANS_FALSE = 2   'On negative transition
'  ouputs
Public Const g_intSTROBE_ON = 3     'Strobe bit on
Public Const g_intSTROBE_OFF = 2    'Strobe bit off

'  Input Siginal names
Public Const g_inpGUARD_DOOR = "inpGuardDoor"
Public Const g_inpLOW_LABEL = "inpLowLabel"
Public Const g_inpPART_PRESENT = "inpPartPresent"
Public Const g_inpPRINTER_ENGAGED = "inpPrinterEngaged"
Public Const g_inpVACUUM_SENSE = "inpVacuumSense"
Public Const g_inpAIR_PRESSER = "inpAirPresserLoss"
Public Const g_inpRETRACTED = "inpRetracted"
Public Const g_inpEND_ROTATE_0_DEG = "inpRotate0"
Public Const g_inpEND_ROTATE_90_DEG = "inpRotate90"
Public Const g_inpSA_ALARM = "inpSAAlarem"
Public Const g_inpSA_READY = "inpSAReady"
Public Const g_inpPOSITIONING_END = "inpPositioningEnd"
Public Const g_intCONTROL_VOLTAGE = "inpControl24Volts"
Public Const g_intE_STOP = "inpEStop"
Public g_ibitGuardDoor      As Integer
Public g_ibitLowLabel       As Integer
Public g_ibitPartPresent    As Integer
Public g_ibitPrinterEngaged As Integer
Public g_ibitVacuumSense    As Integer
Public g_ibitAirPresser     As Integer
Public g_ibitRetracted      As Integer
Public g_ibitRotate0        As Integer
Public g_ibitRotate90       As Integer
Public g_ibitSA_Alarm       As Integer
Public g_ibitSAReady        As Integer
Public g_ibitPositioningEnd As Integer
Public g_ibitControlVolts   As Integer
Public g_ibitEStop          As Integer
Public Const g_ibitRemovedBoard = 15  'added 06/01/01


'  Output Siginal Names
Public Const g_outAIR_BLAST = "outAirBlast"
Public Const g_outROTATE_SOLENOID = "outRotate"
Public Const g_outPRINTER_RELESE = "outPtrRelese"
Public Const g_outEE_ACTUATOR = "outEEactuator"
Public Const g_outEERTOATE = "outEERotate"
Public Const g_outVACUME_SOLENOID = "outVacuum"
Public Const g_outBLOW_OFF = "outBlowOff"
Public Const g_outSCANNER_TRIGGER = "outScannerTrig"
Public Const g_outLABELING_COMPLETE = "outLabelingComplete"
Public Const g_outBUZZER = "outBuzzer"
Public Const g_outBECON_RED = "outReadBeckon"
Public Const g_outBECKON_YELLOW = "outYellowBeckon"
Public Const g_outBECKON_GREEN = "outGreenBeckon"
Public Const g_outSA_EMERGENCY_STOP = "outSAEmergencyStop"
Public Const g_outSA_EXTERNAL_START = "outSAExternalStart"
Public Const g_outSA_HOLD = "outSAHold"
Public Const g_outSA_POSITION_1 = "outSAPosition1"
Public Const g_outSA_POSITION_2 = "outSAPosition2"
Public Const g_outSA_POSITION_4 = "outSAPosition4"
Public Const g_outSA_POSITION_8 = "outSAPosition8"
Public Const g_outSA_POSITION_10 = "outSAPosition10"
Public Const g_outSA_POSITION_20 = "outSAPosition20"
Public Const g_outSA_POSITION_40 = "outSAPosition40"
Public Const g_outSA_POSITION_80 = "outSAPosition80"
Public Const g_outSA_RESET = "outSAReset"
Public g_obitAirBlast         As Integer
Public g_obitRotate           As Integer
Public g_obitPtrRelese        As Integer
Public g_obitActuator         As Integer
Public g_obitEERotate          As Integer
Public g_obitVacuum           As Integer
Public g_obitBlowOff          As Integer
Public g_obitScannerTrig      As Integer
Public g_obitLabelingComplete As Integer
Public g_obitBuzzer           As Integer
Public g_obitRedBeckon       As Integer
Public g_obitYellowBeckon     As Integer
Public g_obitGreenBeckon      As Integer
Public g_obitSAEmergencyStop  As Integer
Public g_obitSAExternalStart  As Integer
Public g_obitSAHold           As Integer
Public g_obitSAPosition1      As Integer
Public g_obitSAPosition2      As Integer
Public g_obitSAPosition4      As Integer
Public g_obitSAPosition8      As Integer
Public g_obitSAPosition10     As Integer
Public g_obitSAPosition20     As Integer
Public g_obitSAPosition40     As Integer
Public g_obitSAPosition80     As Integer
Public g_obitSAReset          As Integer

