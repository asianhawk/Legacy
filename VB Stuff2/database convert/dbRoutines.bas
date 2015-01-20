Attribute VB_Name = "dbCalls"
Option Explicit
Dim m_nNumberOfJobRecords As Integer
Public m_strFieldNames(1 To 100) As String



Public Sub CollectDatabaseInfo(strDBName As String)
Dim dbJob As Database
Dim rsJob As Recordset
Dim nCount As Integer
On Error GoTo Error_Handler:
Set dbJob = OpenDatabase(strDBName)

Set rsJob = dbJob.OpenRecordset("select * from tblJobFIle")
nCount = 0
With rsJob
    
    If (Not .EOF) Then
        .MoveFirst
    End If
    Do While (Not .EOF)
      nCount = nCount + 1
      .MoveNext
    Loop
End With

rsJob.Close
dbJob.Close


SetNumberOfJobRecords nCount
Exit Sub

Error_Handler:
   MsgBox ("Error = " + Err.Description)
   
End Sub


Private Sub SetNumberOfJobRecords(nCount As Integer)
  m_nNumberOfJobRecords = nCount
  
End Sub

Public Function GetNumberOfRecords() As Integer
  GetNumberOfRecords = m_nNumberOfJobRecords
End Function


Public Function GetNumberOfFields(strDBName As String) As Integer

Dim dbJob As Database
Dim rsJob As Recordset
Dim nCount As Integer
On Error GoTo Error_Handler:
Set dbJob = OpenDatabase(strDBName)

Set rsJob = dbJob.OpenRecordset("select * from tblJobFIle")
nCount = 0
With rsJob
    
    If (Not .EOF) Then
        .MoveFirst
        nCount = .Fields.Count
    
    End If
    
End With

rsJob.Close
dbJob.Close


GetNumberOfFields = nCount
Exit Function

Error_Handler:
   MsgBox ("Error = " + Err.Description)


End Function


Public Function GetFieldNames(strDBName As String) As Boolean
Dim dbJob As Database
Dim rsJob As Recordset
Dim nCount As Integer
Dim nIndex As Integer

On Error GoTo Error_Handler:
Set dbJob = OpenDatabase(strDBName)

Set rsJob = dbJob.OpenRecordset("select * from tblJobFIle")
nCount = 0
With rsJob
    
    If (Not .EOF) Then
        .MoveFirst
        nCount = .Fields.Count
        For nIndex = 1 To nCount
           m_strFieldNames(nIndex) = .Fields(nIndex - 1).Name
        Next
        GetFieldNames = True
    Else
      GetFieldNames = False
    End If
    
    
End With

rsJob.Close
dbJob.Close

Exit Function

Error_Handler:
   MsgBox ("Error = " + Err.Description)
   GetFieldNames = False

End Function



Public Function AddDatabaseField(strDBName As String, strFieldName As String, strDataType As String, strFLength As String) As Boolean
Dim dbJob As Database
Dim tblJob As TableDef
    
Dim nCount As Integer
Dim nIndex As Integer

On Error GoTo Error_Handler:
Set dbJob = OpenDatabase(strDBName)
Set tblJob = dbJob.TableDefs("tblJobFIle")
nCount = 0
AddDatabaseField = True
With tblJob
    
    
    If (strDataType = "Text") Then
        .Fields.Append .CreateField(strFieldName, _
                    dbText, Val(strFLength))
    
    ElseIf (strDataType = "Boolean") Then
        .Fields.Append .CreateField(strFieldName, _
                    dbBoolean)
    
    ElseIf (strDataType = "Integer") Then
        .Fields.Append .CreateField(strFieldName, _
                    dbInteger)
    
    End If
End With

Set tblJob = Nothing
dbJob.Close

Exit Function

Error_Handler:
   MsgBox ("Error = " + Err.Description)
   AddDatabaseField = False


End Function


Public Sub InitNewField(strDBName As String, strFieldName As String, strNewValue As String)
Dim dbJob As Database
Dim rsJob As Recordset
Dim nCount As Integer
On Error GoTo Error_Handler:
Set dbJob = OpenDatabase(strDBName)

Set rsJob = dbJob.OpenRecordset("select * from tblJobFIle")
nCount = 0
With rsJob
    
    If (Not .EOF) Then
        .MoveFirst
    End If
    Do While (Not .EOF)
      .Edit
      If (strNewValue = "True") Then
        .Fields(strFieldName).Value = True
      ElseIf (strNewValue = "False") Then
        .Fields(strFieldName).Value = False
      Else
        .Fields(strFieldName).Value = strNewValue
      End If
      .Update
      .MoveNext
    Loop
End With

rsJob.Close
dbJob.Close


SetNumberOfJobRecords nCount
Exit Sub

Error_Handler:
   MsgBox ("Error = " + Err.Description)
   

End Sub

Public Function UpdateQueries(strDBName As String) As Boolean
Dim dbJob As Database
Dim qurJob As QueryDef
Dim strSQLCmd As String

On Error GoTo Error_Handler:

    UpdateQueries = True
    strSQLCmd = "select * from tblJobFile ORDER BY txtJobsName ASC"
    Set dbJob = OpenDatabase(strDBName)
    dbJob.QueryDefs.Delete "qurJobFIle"
    
    Set qurJob = dbJob.CreateQueryDef("qurJobFile", strSQLCmd)
    dbJob.QueryDefs("qurJobFIle").Close

Set qurJob = Nothing
dbJob.Close

Exit Function

Error_Handler:
   MsgBox ("Error = " + Err.Description)
   UpdateQueries = False


End Function


