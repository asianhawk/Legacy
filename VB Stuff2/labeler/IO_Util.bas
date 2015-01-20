Attribute VB_Name = "Module1"
'**************************************************************************
'    Function Declaration for ADAPI32
'**************************************************************************
Private Declare Function DRV_DeviceGetNumOfList Lib "adapi32.dll" (NumOfDevices As Integer) As Long
Private Declare Function DRV_DeviceGetList Lib "adapi32.dll" (ByVal devicelist As Long, ByVal MaxEntries As Integer, nOutEntries As Integer) As Long
Private Declare Sub DRV_GetErrorMessage Lib "adapi32.dll" (ByVal lError As Long, ByVal lpszszErrMsg As String)

' Direct I/O Functions List
Private Declare Function DRV_outp Lib "adapi32.dll" (ByVal DeviceNum As Long, ByVal port As Integer, ByVal ByteData As Long) As Long
Private Declare Function DRV_outpw Lib "adapi32.dll" (ByVal DeviceNum As Long, ByVal port As Integer, ByVal ByteData As Long) As Long
Private Declare Function DRV_inp Lib "adapi32.dll" (ByVal DeviceNum As Long, ByVal port As Integer, ByteData As Long) As Long
Private Declare Function DRV_inpw Lib "adapi32.dll" (ByVal DeviceNum As Long, ByVal port As Integer, ByteData As Long) As Long

Private Declare Function DRV_GetAddress Lib "adapi32.dll" (lpVoid As Any) As Long

Public Function WriteBitPort(intbit As Integer, bitvalue As Boolean) As Boolean
   Dim lngLength As Long
   Dim lngReadWord As Long
   Dim i As Integer
   Dim intNewValue As Integer
   Dim newvalue As Long
   Dim nResponse As Integer
   
   #If ccShip_Ver Then
      On Error GoTo Error_WriteBitPort
   #Else
      On Error GoTo 0
   #End If
   
   lngReadWord = ReadWordPort
   
   intNewValue = 0
   For i = 0 To 15
      If lngReadWord And 2 ^ i = 1 Then
        
        If i = intbit Then
          If bitvalue Then
             newvalue = newvalue + 2 ^ i
          End If
          
          
           
        Else
          newvalue = newvalue + 2 ^ i
        End If
        
      End If
      
   
   Next i
   
   ErrCde = DRV_outpw(g_nOutputPortDevice_Num, g_nOutPutPort_ID, newvalue)
      
   If (ErrCde <> 0) Then
       DRV_GetErrorMessage ErrCde, szErrMsg
       nResponse = MsgBox(szErrMsg, vbOKOnly, "Error!!")
       WriteBitPort = False
       Exit Function
      Else
          WriteBitPort = True
      End If
      
   
   Exit Function
   
Error_WriteBitPort:

   ProccessError "WritebitPort", m_strName, Err.Number, Err.Description

End Function 'WritePort
Public Function ReadWordPort() As Long

   Dim lngLength As Long
   Dim lngDataBuffer As Long
   Dim nResponse As Integer
   
   #If ccShip_Ver Then
      On Error GoTo Error_ReadPort
   #Else
      On Error GoTo 0
   #End If
   

   lngLength = 0
   
   ErrCde = DRV_inpw(g_nInPortDevice_Num, g_nInportPort_ID, lngDataBuffer)
   If (ErrCde <> 0) Then
        DRV_GetErrorMessage ErrCde, szErrMsg
        nResponse = MsgBox(szErrMsg, vbOKOnly, "Error!!")
        ReadPort = False
        Exit Function
   End If
   
   ' show status
   ReadWordPort = lngDataBuffer
   
   
   Exit Function
   
Error_ReadWordPort:

   ProccessError "ReadWordPort", m_strName, Err.Number, Err.Description

End Function 'ReadWordPort
