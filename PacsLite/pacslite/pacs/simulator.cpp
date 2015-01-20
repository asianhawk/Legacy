#include "stdafx.h"
#include "simulator.h"

char* pFileName = "c:\\pacs.log";
CStdioFile f1;

void OpenLogFile()
{
	if( !f1.Open( pFileName,CFile::modeCreate| 
       CFile::modeWrite | CFile::typeText ) ) 
	{
      #ifdef _DEBUG
        afxDump << "Unable to open file" << "\n";
      #endif
    }
}

void CloseLogFile()
{
	f1.Close();
}

void LogInfo(CString strBuffer)
{
  f1.WriteString(strBuffer + CString("\n"));
}