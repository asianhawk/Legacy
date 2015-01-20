Attribute VB_Name = "modAPI"
Option Explicit

Private Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)


Public Sub SleepSec(intTimeSec As Integer)
   
   Call Sleep(CLng(intTimeSec * 1000))

End Sub 'SleepSec
Public Sub SleepMSec(lngTimeMSec As Long)
   
   Call Sleep(CLng(lngTimeMSec))

End Sub 'SleepSec

