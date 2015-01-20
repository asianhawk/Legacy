Attribute VB_Name = "modMoveConstants"
'************************************************************************
'*           Computype, Inc.
'*       NextStep Automation Group
'*
'*     © Copywrite 1997 Computype, Inc.
'*
'*        2-Axis label Applicator
'*           Control Subsystem
'*
'*          Digital Constents
'*
'*    Date of origin: August 6,1997
'*    Original author: Michael D. Reed
'*
'*    Module purpose:
'*       This module contains the constants used by the motion subsystem.
'*
'************************************************************************
Option Explicit

'  invalded position indicator used in position poroperty
Public Const g_strINVALIDE_POSITION = "-1'"

'  Built in posiitons
Public Const g_strPRINTER_POSITION = "99"
Public Const g_strQUEUE_STACK = "98"

'  Timing constests
Public Const g_lngSA_RESET_WAIT  As Long = 4000

'  Errors
Public Const g_errSA_NOT_RESET = g_intMOTION_ERROR_OFFSET + 1
