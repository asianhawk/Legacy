VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsQueue"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
'************************************************************************
'*           Computype, Inc.
'*       NextStep Automation Group
'*
'*     © Copywrite 1996 Computype, Inc.
'*
'*        3-Axis Label Applicator
'*           Software Subsystem
'*
'*          Queue managment
'*
'*    Date of origin: <Date>
'*    Original author: Michael D. Reed
'*
'* Class purpose:
'*    This class provides the tools necessary to manage
'*    a queue (FIFO).   An empty queue setup when the class
'*    initializes. A method Push to add items to the end of
'*    the queue and a method Pull to remove an item from the
'*    front of the queue. A Look method is provided to look
'*    at the queue contents.  A QSize method returning the
'*    number of items in  the queue.  The queue is implemented
'*    using the VB Collection Object.
'*
'************************************************************************
Option Explicit
'******************************************************************

Private m_colQueue As Collection

Private Sub Class_Initialize()

   Set m_colQueue = New Collection
   If g_blnTest Then
      frmQueue.Show
   End If
   
End Sub 'Class_Initialize



Public Sub Push(vntMember As Variant)

   If m_colQueue.Count = 0 Then
      m_colQueue.Add Item:=vntMember
   Else
      m_colQueue.Add Item:=vntMember, After:=m_colQueue.Count
   End If
   
   If g_blnTest Then
      frmQueue.lstQueue.AddItem vntMember
      frmQueue.labQueue.Caption = "Q size = " & m_colQueue.Count
   End If
   
End Sub 'Push

Public Function Pull() As Variant

   If m_colQueue.Count > 0 Then
      Pull = m_colQueue.Item(1)
      m_colQueue.Remove 1
      If g_blnTest Then
         frmQueue.lstQueue.RemoveItem 0
      End If
   Else
      Pull = Empty
   End If
   
   If g_blnTest Then
      frmQueue.labQueue.Caption = "Q size = " & m_colQueue.Count
   End If
   
End Function 'Pull

Public Function Look(Optional vntIndex As Variant) As Variant

   If m_colQueue.Count > 0 Then
      If IsMissing(vntIndex) Then
         Look = m_colQueue.Item(1)
      ElseIf IsMember(CInt(vntIndex)) Then
         Look = m_colQueue.Item(CInt(vntIndex))
      Else
         Look = Null
      End If
   Else
      Look = Empty
   End If
End Function 'Look

Public Function IsMember(intKey As Integer)

   Dim vntTemp As Variant
   
   On Error Resume Next
   
   vntTemp = m_colQueue.Item(intKey)
   IsMember = (Err.Number = 0)
   
   On Error GoTo 0
   
End Function 'IsMember

Private Sub Class_Terminate()

   Set m_colQueue = Nothing
   If g_blnTest Then
      Unload frmQueue
   End If
   
End Sub 'Class_Terminate



Public Function QSize() As Long

   QSize = m_colQueue.Count

End Function 'QSize

Public Sub Clear()

   Set m_colQueue = Nothing
   Set m_colQueue = New Collection
   If g_blnTest Then
      frmQueue.lstQueue.Clear
      frmQueue.labQueue.Caption = "Q size = " & m_colQueue.Count
   End If

End Sub 'Clear

Public Sub ReSync(strScannedLabel As String)
Dim intQueueLength As Integer
Dim intScannedLabel As Integer
Dim intQueuedLabel As Integer
Dim intCntr As Integer
Dim strQueue As String
  
  intQueueLength = 6

strQueue = Look
strQueue = Mid(strQueue, Len(strQueue) - 3, 2)
 intQueuedLabel = Val(strQueue)
 intScannedLabel = Val(Mid(strScannedLabel, Len(strScannedLabel) - 3, 2))

 If (Abs(intQueuedLabel - intScannedLabel) <= intQueueLength) Then
  
 Pull  ' delete one from queue
 strQueue = Look
 strQueue = Mid(strQueue, Len(strQueue) - 3, 2)
 intQueuedLabel = Val(strQueue)
 
 Do While intCntr < 6
      If (Abs(intQueuedLabel - intScannedLabel) <> 0) Then
          Pull
          intCntr = intCntr + 1
      Else
         Exit Sub
      End If
   strQueue = Look
   strQueue = Mid(strQueue, Len(strQueue) - 3, 2)
   intQueuedLabel = Val(strQueue)
   intCntr = intCntr + 1
   
 Loop
End If
End Sub

Public Function StrCompare(strScannedLabel As String, strLastPrinted) As Boolean
Dim intQueueLength As Integer
Dim intScannedLabel As Integer
Dim intQueuedLabel As Integer
Dim intCntr As Integer
Dim strQueue As String
  
  intQueueLength = 7

strQueue = strLastPrinted
strQueue = Mid(strQueue, Len(strQueue) - 2, 3)
 intQueuedLabel = Val(strQueue)
 intScannedLabel = Val(Mid(strScannedLabel, Len(strScannedLabel) - 2, 3))

If (Abs(intQueuedLabel - intScannedLabel) = intQueueLength) Then
   StrCompare = True
Else
   'code???
   StrCompare = True
End If
End Function

