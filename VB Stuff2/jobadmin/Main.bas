Attribute VB_Name = "modMain"
'*******************************************************************
'*           Computype, Inc.
'*       NextStep Automation Group
'*
'*     © Copywrite 1996 Computype, Inc.
'*
'*        3-Axis Label Applicator
'*        Job File Administration
'*
'*
'*    Date of origin: 12/29/96
'*    Original author: Michael D. Reed
'*
'* Form purpose:
'*    This form is for maintaning job file
'*
'******************************************************************
Option Explicit

Public Sub Main()

   frmSplash.Show
   DoEvents
   With App
      .HelpFile = .Path & "\" & .EXEName & ".hlp"
   End With ' app
   
   frmJobFileAdmin.Hide
   DoEvents
   frmJobFileAdmin.Show
   
   Unload frmSplash
   
End Sub 'Main

