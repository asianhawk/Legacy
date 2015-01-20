VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsDigitalCommon"
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
'*          Digital Driver Interface
'*
'*    Date of origin: July 20,1997
'*    Original author: Michael D. Reed
'*
'*    Module purpose:
'*       This is the driver interface for both the digital input and output.
'*       The Base address and width of the digital space is set in registration DB.
'*       The offsets for the digital output and the digital input are set in the Labeler
'*       configuration DB.
'*
'************************************************************************
Option Explicit

'  name and version
Private m_strName As String
Private m_strVersion  As String

Private Type Write_Buffer
   lngPortOffset As Long
   lngDataValue As Long
End Type


'constants
'  Define card definition

Private Type Port_Def
   lngBaseAddress As Long
   lngPortCount As Long
End Type

'  Offsets form the base address for each one
Private m_lngOutputPortOffset(0 To 1) As Long
Private m_lngInputPortOffset As Long


Const MaxEntries = 9        ' This version under windows can use 9 device only

Private DeviceHandle As Long
Private ptDevGetFeatures As PT_DeviceGetFeatures
Private devicelist(0 To MaxEntries) As PT_DEVLIST
Private ErrCde As Integer
Private szErrMsg As String * 80
Private bRun As Boolean

Private gwPort As Integer
Private Const g_nInPortDevice_Num = 0
Private Const g_nOutputPortDevice_Num = 1
Private Const g_strInputPortCard_ID = "PCL-733 I/O=300H"
Private Const g_strOutputPortCard_ID = "PCL-734 I/O=304H"

Private g_nInportPort_ID As Integer
Private g_nOutPutPort_ID As Integer

Private dwDeviceNum As Long

Private Type PT_DEVLIST
    dwDeviceNum  As Long
    szDeviceName(0 To 49) As Byte
    nNumOfSubdevices As Integer
End Type

Private Type PT_DeviceGetFeatures
    Buffer As Long        ' LPDEVFEATURES
    size   As Integer
End Type

'****************************************************************************
'    Constant Definition
'****************************************************************************
Private Const MaxDev = 255 ' max. # of devices
Private Const MaxDevNameLen = 49           ' original is 64; max lenght of device name


'**************************************************************************
'    Function Declaration for ADAPI32
'**************************************************************************
Private Declare Function DRV_DeviceGetNumOfList Lib "adsapi32.dll" (NumOfDevices As Integer) As Long
Private Declare Function DRV_DeviceGetList Lib "adsapi32.dll" (ByVal devicelist As Long, ByVal MaxEntries As Integer, nOutEntries As Integer) As Long
Private Declare Sub DRV_GetErrorMessage Lib "adsapi32.dll" (ByVal lError As Long, ByVal lpszszErrMsg As String)

' Direct I/O Functions List
Private Declare Function DRV_outp Lib "adsapi32.dll" (ByVal DeviceNum As Long, ByVal port As Integer, ByVal ByteData As Long) As Long
Private Declare Function DRV_outpw Lib "adsapi32.dll" (ByVal DeviceNum As Long, ByVal port As Integer, ByVal ByteData As Long) As Long
Private Declare Function DRV_inp Lib "adsapi32.dll" (ByVal DeviceNum As Long, ByVal port As Integer, ByteData As Long) As Long
Private Declare Function DRV_inpw Lib "adsapi32.dll" (ByVal DeviceNum As Long, ByVal port As Integer, ByteData As Long) As Long

Private Declare Function DRV_GetAddress Lib "adsapi32.dll" (lpVoid As Any) As Long


Public Function Version() As String

   Version = m_strVersion
   
End Function 'Version


Public Function WritePort(vntDataValue() As Variant) As Boolean

   Dim lngLength As Long
   Dim i As Integer
   Dim nResponse As Integer
   
   #If ccShip_Ver Then
      On Error GoTo Error_WritePort
   #Else
      On Error GoTo 0
   #End If
   
   If g_blnSimulator Then
      WritePort = True
      Exit Function
   Else
      WritePort = False
   End If
   
   
   For i = 0 To UBound(vntDataValue)
      ' set up our data buffer to pass to the driver
      
      lngLength = 0
      'code????
      ErrCde = DRV_outpw(g_nOutputPortDevice_Num, g_nOutPutPort_ID + 2 * i, vntDataValue(i))
      
      If (ErrCde <> 0 And (Not g_blnSimulator)) Then
          DRV_GetErrorMessage ErrCde, szErrMsg
          nResponse = MsgBox(szErrMsg, vbOKOnly, "Error!!")
          WritePort = False
          Exit Function
      Else
          WritePort = True
      End If
      
   
   Next i
   
   
   Exit Function
   
Error_WritePort:

   ProccessError "WritePort", m_strName, Err.Number, Err.Description

End Function 'WritePort

Public Function CheckDIOAcces(lngProtAddr As Long, lngProtCount As Long) As Boolean
   '  This function checks to see if the Acces cards have been in installed and
   '  the address and port count matches what is in the Labeler DB.
   
  Dim gnNumOfDevices As Integer
  Dim nOutEntries As Integer
  Dim i, ii As Integer
  Dim tt As Long
  Dim tempStr As String
  Dim strBuffer As String
  Dim nResponse     As Integer
  
  CheckDIOAcces = False
  ' Add type of PC Laboratory Card
  tt = DRV_GetAddress(devicelist(0))
  ErrCde = DRV_DeviceGetList(tt, MaxEntries, nOutEntries)
  If (ErrCde <> 0) Then
    DRV_GetErrorMessage ErrCde, szErrMsg
    nResponse = MsgBox(szErrMsg, vbOKOnly, "Error!!")
    
    Exit Function
  End If
  
  ErrCde = DRV_DeviceGetNumOfList(gnNumOfDevices)
  If (ErrCde <> 0) Then
    DRV_GetErrorMessage ErrCde, szErrMsg
    nResponse = MsgBox(szErrMsg, vbOKOnly, "Error!!")
    Exit Function
  End If
  
  For i = 0 To (gnNumOfDevices - 1)
    tempStr = ""
    For ii = 0 To MaxDevNameLen
    
     tempStr = tempStr + Chr(devicelist(i).szDeviceName(ii))
    Next ii
      
      strBuffer = Mid(tempStr, 1, InStr(tempStr, "=") + 4)
      If strBuffer = g_strInputPortCard_ID Then
           g_nInportPort_ID = Val("&H300")
      ElseIf strBuffer = g_strOutputPortCard_ID Then
           g_nOutPutPort_ID = Val("&H304")
      End If
      
      
  Next i
  CheckDIOAcces = True
   
   
 Exit Function
   
Error_CheckDIOAcces:

   CheckDIOAcces = False
   
   ProccessError "CheckDIOAcces", m_strName, Err.Number, Err.Description

End Function 'CheckDIOAcces

Public Function ReadPort(ByRef r_lngValue As Long) As Boolean

   Dim lngLength As Long
   Dim lngDataBuffer As Long
   Dim nResponse As Integer
   
   #If ccShip_Ver Then
      On Error GoTo Error_ReadPort
   #Else
      On Error GoTo 0
   #End If
   
   #If g_blnSimulator Then
      r_lngValue = 0
      ReadPort = True
      Exit Function
   #Else
      ReadPort = False
   #End If
   

'   lngLength = 0
   
   
   ErrCde = DRV_inpw(g_nInPortDevice_Num, g_nInportPort_ID, lngDataBuffer)
   
   If (ErrCde <> 0) And (Not g_blnSimulator) Then
        DRV_GetErrorMessage ErrCde, szErrMsg
        nResponse = MsgBox(szErrMsg, vbOKOnly, "Error!!")
        ReadPort = False
        Exit Function
   End If
   
   ' show status
   r_lngValue = lngDataBuffer
   ReadPort = True
   
   Exit Function
   
Error_ReadPort:

   ProccessError "ReadPort", m_strName, Err.Number, Err.Description

End Function 'ReadPort
Public Function ReadHolePatternPort(ByRef r_lngValue As Long) As Boolean

   Dim lngLength As Long
   Dim lngDataBuffer As Long
   Dim nResponse As Integer
   
   #If ccShip_Ver Then
      On Error GoTo Error_ReadPort
   #Else
      On Error GoTo 0
   #End If
   
   #If g_blnSimulator Then
      r_lngValue = 0
      ReadHolePatternPort = True
      Exit Function
   #Else
      ReadHolePatternPort = False
   #End If
   

   lngLength = 0
   
   ErrCde = DRV_inpw(g_nInPortDevice_Num, g_nInportPort_ID + 2, lngDataBuffer)
   If (ErrCde <> 0) Then
        DRV_GetErrorMessage ErrCde, szErrMsg
        nResponse = MsgBox(szErrMsg, vbOKOnly, "Error!!")
        ReadHolePatternPort = False
        Exit Function
   End If
   
   ' show status
   r_lngValue = lngDataBuffer
   
   ReadHolePatternPort = True
   
   Exit Function
   
Error_ReadPort:

   ProccessError "ReadHolePatternPort", m_strName, Err.Number, Err.Description

End Function 'ReadPort



Private Sub Class_Initialize()

   m_strName = "modDigitalCommon"
   m_strVersion = "1.1.0"
  Dim gnNumOfDevices As Integer
  Dim nOutEntries As Integer
  Dim i, ii As Integer
  Dim tt As Long
  Dim tempStr As String
  Dim strBuffer As String
  Dim nResponse     As Integer
  
  ' Add type of PC Laboratory Card
  tt = DRV_GetAddress(devicelist(0))
  ErrCde = DRV_DeviceGetList(tt, MaxEntries, nOutEntries)
  If (ErrCde <> 0) Then
    DRV_GetErrorMessage ErrCde, szErrMsg
    nResponse = MsgBox(szErrMsg, vbOKOnly, "Error!!")
    
    Exit Sub
  End If
  
  ErrCde = DRV_DeviceGetNumOfList(gnNumOfDevices)
  If (ErrCde <> 0) Then
    DRV_GetErrorMessage ErrCde, szErrMsg
    nResponse = MsgBox(szErrMsg, vbOKOnly, "Error!!")
    Exit Sub
  End If
  
  For i = 0 To (gnNumOfDevices - 1)
    tempStr = ""
    For ii = 0 To MaxDevNameLen
    
     tempStr = tempStr + Chr(devicelist(i).szDeviceName(ii))
    Next ii
      
      strBuffer = Mid(tempStr, 1, InStr(tempStr, "=") + 4)
      If strBuffer = g_strInputPortCard_ID Then
           g_nInportPort_ID = Val("&H300")
      ElseIf strBuffer = g_strOutputPortCard_ID Then
           g_nOutPutPort_ID = Val("&H304")
      End If
      
      
  Next i
   
   

End Sub 'Class_Initialize



Public Function Initialize(objConfgDB As Object, strConfigTable As String) As Boolean

   Dim snpConfiguration As Recordset
   Dim blnStatus As Boolean
   
   #If ccShip_Ver Then
      On Error GoTo InitConfiguration_Error
   #Else
      On Error GoTo 0
   #End If
   
   Initialize = False
   
   '  Set up Labeler data
   Set snpConfiguration = objConfgDB.OpenRecordset(strConfigTable, dbOpenSnapshot)
   
   m_lngOutputPortOffset(0) = snpConfiguration![lngDigitalOutputOffset]
   m_lngOutputPortOffset(1) = m_lngOutputPortOffset(0) + CLng(2)
   m_lngInputPortOffset = snpConfiguration![lngDigitalInputOffset]
         
   Initialize = True
      
   Exit Function
   
InitConfiguration_Error:

   ProccessError "Initialize", m_strName, Err.Number, Err.Description
   
End Function 'Initialize

Public Sub WPort()
Dim nResponse As Integer
Dim ErrCode As Integer

   #If ccShip_Ver Then
      On Error GoTo Error_WPort
   #Else
      On Error GoTo 0
   #End If
   
   ErrCde = DRV_outpw(g_nOutputPortDevice_Num, g_nOutPutPort_ID, g_lDataValue)
      
   If (ErrCde <> 0) Then
       DRV_GetErrorMessage ErrCde, szErrMsg
          nResponse = MsgBox(szErrMsg, vbOKOnly, "Error!!")
   End If
   
   Exit Sub
   
Error_WPort:

   ProccessError "WPort", m_strName, Err.Number, Err.Description

End Sub      'WritePort

