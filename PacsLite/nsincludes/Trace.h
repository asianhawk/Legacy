#ifndef __TRACE_H_
#define __TRACE_H_


/*

_NO_TRACE - Use this precompiler option to minimize compiler application size.

TraceReadINI - From the applications ini file reads control values.
I.E.
[TRACE]
;Specific log name and path
PathAndFileName=C:\A_TEST\mylog.txt

[TRACE]
;Use the default path and name
PathAndFileName=C:\A_TEST\mylog.txt

If you use TraceReadINI then you do not have to use TraceStart.

TraceStart - Tracing defaults to TraceStop.  A call to TraceStart will start tracing
until end of execution or TraceStop.  The log will default to the directory of the application 
that called it.  You can over ride the default behavior by passing in your own path, file name and
file name extension.  The existing log is always numerically archived.  If more than one
instance of an application is executing, then susequent applications will have the post fix
'HMODULE' in the log entries.

Trace -  Works just like TRACE or printf.  The first parameter can be any length, the sum
of the additional parameters is limited to 1024 characters.

TraceSuspend - Default is false.  When true logging is suspended until set back to false.

TraceStop - The current log is closed.  To continue logging, explicitly call TraceStart.
In the event of multiple programs writing to the same log, the log will not be closed.  The next
call to TraceStart will append to the existing log.

TraceClockCapture - Captures the current clock value.

TraceClockDuration - Writes the number of seconds passed since the last TraceClockCapture.

TraceFlush - Default is true.  You can turn it off to increase performance, but if the 
application fails you may not get the last several dozen statements logged written to the 
log file.

TraceWithTime - Default is true.  Causes the Trace statement to output the time of each
trace statement.  The year value is not output.


*/


#ifdef _NO_TRACE
	#pragma message("Trace.  Tracing to a log will not be available in the exe.\n")
#else
	#pragma message("Trace.  Tracing to a log will be available in the exe.\n")
	#pragma message("Make sure you turn it on in the applications ini file with TraceReadINI\n")
	#pragma message("or a direct call to TraceStart.\n")
#ifdef _UNICODE
	#pragma message("..\n")
	#pragma message("_UNICODE option is defined.\n")
#endif
#endif

CString GetLogFileName(CString csFileName);
BOOL IsArchiveLastLog(CString csFileName);
void ArchiveCurrentSession(CString csFileName);
void RemoteTCP(CString csFileName);
void SendInfoDataPackets(CString csFileName);
void SendErrorDataPackets(CString csFileName);
void SendStatusDataPackets(CString csFileName);
BOOL CheckForReceivedMsgs();


/* Functions that are exposed */
__declspec( dllexport ) void  TraceStart(char *pszPathName  = NULL);
__declspec( dllexport ) void  Trace(const char *pszFormat, ...);
__declspec( dllexport ) void  TraceWithTime(bool bValue);
__declspec( dllexport ) void  TraceSuspend(bool bTrueToSuspend);
__declspec( dllexport ) void  TraceStop();
__declspec( dllexport ) void  TraceClockCapture(char* pszComment = NULL);
__declspec( dllexport ) void  TraceClockDuration (char* pszComment = NULL);
__declspec( dllexport ) void  TraceFlush(bool bForceFlush);
__declspec( dllexport ) void  TraceReadINI();
__declspec( dllexport ) BOOL  IsTraceOn();


/*Private functions */
__declspec( dllexport ) void ArchiveLastLog(CString strLogPathName);

#endif
