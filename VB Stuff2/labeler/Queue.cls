VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "clsQueue"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'************************************************************************
'*          DANA-REED & Co.
'*                      © Copywrite 1997
'*
'*          Queue managment
'*
'*    Date of origin: 2/18/97
'*    Original author: Michael D. Reed
'*
'* Class purpose:
'*    This class provides the tools necessary to manage
'*    a queue (FIFO).   An empty queue setup when the class
'*    initializes. A method Push to add items to the end of
'*    the queue and a method Pull to remove an item from the
'*    front of the queue. This a Queue property where the Get
'*    is the same as Pull and the Let is the same as Push.
'*    A Look method is provided to look at the queue contents.
'*    A QSize method returning the number of items in  the queue.
'*    The queue is implemented using the VB Collection Object.
'*
'*    The queue is initialized upon class initialization and
'*    destroyed on class termination.  The following formats are
'*    for the public procedures are provided:
'*       Push (Let Queue)  [takes a Variant argument]
'*       Pull (Get Queue)  [returns: a Variant if there is an item
'*                                      in the queue
'*                                   Empty if the queue there
'*                                      is on items in the queue]
'*       Look  [Takes an optional index (integer) Variant argument
'*                 into the queue
'*              Returns: with no index the first item in the queue
'*                       with an index the item at the index location
'*                       the following values are returned:
'*                          Variant item in the queue
'*                          Empty if the queue there is on items
'*                             in the queue
'*                          Null if an index is given and the
'*                             index does not exists
'*
'************************************************************************
Option Explicit
'******************************************************************

Private m_colQueue As Collection

Private Sub Class_Initialize()

      Set m_colQueue = New Collection

End Sub 'Class_Initialize



Public Sub Push(vntMember As Variant)

   If m_colQueue.Count = 0 Then
      m_colQueue.Add Item:=vntMember
   Else
      m_colQueue.Add Item:=vntMember, After:=m_colQueue.Count
   End If

End Sub 'Push

Public Function Pull() As Variant

   If m_colQueue.Count > 0 Then
      
'      Pull = m_colQueue.Item(1)
      Pull = m_colQueue.Item(m_colQueue.Count)
      m_colQueue.Remove m_colQueue.Count
   Else
      Pull = Empty
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
      
End Sub 'Class_Terminate



Public Function QSize() As Long

   QSize = m_colQueue.Count

End Function 'QSize

Public Property Get Queue() As Variant

   Queue = Pull
   
End Property  'Get Queue

Public Property Let Queue(vNewValue As Variant)

   Push vNewValue

End Property 'Let Queue

Public Sub Clear()

   Do While m_colQueue.Count > 0
      m_colQueue.Remove 1
   Loop
   
End Sub 'ClearQue
