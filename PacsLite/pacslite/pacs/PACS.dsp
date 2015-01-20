# Microsoft Developer Studio Project File - Name="PACS" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PACS - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PACS.MAK".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PACS.MAK" CFG="PACS - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PACS - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PACS - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PACS - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fr /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 c:\NSLibs\logtrace.lib c:\NSLibs\NSInternalSetup.lib c:\NSLibs\NSDatabase.lib c:\NSLibs\NSUtility.lib c:\NSLibs\NSJobs.lib c:\NSLibs\NSDIODiagnostic.lib c:\NSLibs\nsdio.lib c:\NSLibs\NSSerializationDlg.lib c:\NSLibs\NSChangePasswordDlg.lib c:\NSLibs\NSPasswordDlg.lib c:\NSLibs\NSDeleteJobDlg.lib c:\NSLibs\NSHoldDlg.lib c:\NSLibs\NSEnterJobNameDlg.lib c:\NSLibs\NSLabelSelectDlg.lib c:\NSLibs\NSPointDlg.lib c:\NSLibs\NSLibrary.lib c:\NSLibs\NSPanelLabelDlg.lib c:\NSLibs\NSPrinterSelectDlg.lib c:\NSLibs\NSSetupScannerDlg.lib c:\NSLibs\NSTemplateNameDlg.lib c:\NSLibs\NSTemplateEditDlg.lib c:\NSLibs\NSTemplateSetupDlg.lib c:\NSlibs\NSAddEditJobDlg.lib c:\NSlibs\NSStatisticsDb.lib c:\NSLibs\nsmsflexgrid.lib c:\NSLibs\CheckDgt.lib /nologo /stack:0x3d0900 /subsystem:windows /debug /machine:I386 /out:"c:\computype\pacs\PACS.exe"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "PACS - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fr /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 c:\NSLibs\logtrace.lib c:\NSLibs\NSInternalSetup.lib c:\NSLibs\NSDatabase.lib c:\NSLibs\NSSystemDB.lib c:\NSLibs\NSUtility.lib c:\NSLibs\NSJobs.lib c:\NSLibs\NSDIODiagnostic.lib c:\NSLibs\nsdio.lib c:\NSLibs\nsmsflexgrid.lib c:\NSLibs\NSSerializationDlg.lib c:\NSLibs\NSChangePasswordDlg.lib c:\NSLibs\NSPasswordDlg.lib c:\NSLibs\NSDeleteJobDlg.lib c:\NSLibs\NSHoldDlg.lib c:\NSLibs\NSEnterJobNameDlg.lib c:\NSLibs\NSLabelSelectDlg.lib c:\NSLibs\NSPointDlg.lib c:\NSLibs\NSLibrary.lib c:\NSLibs\NSPanelLabelDlg.lib c:\NSLibs\NSPrinterSelectDlg.lib c:\NSLibs\NSSetupScannerDlg.lib c:\NSLibs\NSTemplateNameDlg.lib c:\NSLibs\NSTemplateEditDlg.lib c:\NSLibs\NSTemplateSetupDlg.lib c:\NSlibs\NSAddEditJobDlg.lib c:\NSlibs\NsUpdateIntervalDlg.lib c:\NSlibs\NSStatisticsDb.lib c:\NSLibs\CheckDgt.lib /nologo /subsystem:windows /debug /machine:I386 /out:"c:\computype\pacs\pacs.exe" /pdbtype:sept
# SUBTRACT LINK32 /profile

!ENDIF 

# Begin Target

# Name "PACS - Win32 Release"
# Name "PACS - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\3Dpoint.cpp
# End Source File
# Begin Source File

SOURCE=.\ApplicatorControl.cpp
# End Source File
# Begin Source File

SOURCE=.\comPort.cpp
# End Source File
# Begin Source File

SOURCE=.\DiagDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DioController.cpp
# End Source File
# Begin Source File

SOURCE=.\ErrorMsgDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\InitDlgMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\mscommctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\PACS.cpp
# End Source File
# Begin Source File

SOURCE=.\hlp\PACS.hpj

!IF  "$(CFG)" == "PACS - Win32 Release"

# Begin Custom Build - Making help file...
OutDir=.\Release
ProjDir=.
TargetName=PACS
InputPath=.\hlp\PACS.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call "$(ProjDir)\makehelp.bat"

# End Custom Build

!ELSEIF  "$(CFG)" == "PACS - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PACS.odl
# End Source File
# Begin Source File

SOURCE=.\PACS.rc
# End Source File
# Begin Source File

SOURCE=.\PACSDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Password.cpp
# End Source File
# Begin Source File

SOURCE=.\Printer.cpp
# End Source File
# Begin Source File

SOURCE=.\PrinterControl.cpp
# End Source File
# Begin Source File

SOURCE=.\PrinterDiagDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RescanDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ReSyncDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RunDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RunProcesses.cpp
# End Source File
# Begin Source File

SOURCE=.\ScanDiagDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Scanner.cpp
# End Source File
# Begin Source File

SOURCE=.\ScannerControl.cpp
# End Source File
# Begin Source File

SOURCE=.\SetupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\simulator.cpp
# End Source File
# Begin Source File

SOURCE=.\SNManager.cpp
# End Source File
# Begin Source File

SOURCE=.\StartupErrorsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Sxbutton.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\3Dpoint.h
# End Source File
# Begin Source File

SOURCE=.\ApplicatorControl.h
# End Source File
# Begin Source File

SOURCE=.\comPort.h
# End Source File
# Begin Source File

SOURCE=.\customflexgrid.h
# End Source File
# Begin Source File

SOURCE=.\DiagDlg.h
# End Source File
# Begin Source File

SOURCE=.\Dio.h
# End Source File
# Begin Source File

SOURCE=.\DioController.h
# End Source File
# Begin Source File

SOURCE=.\DioDlg.h
# End Source File
# Begin Source File

SOURCE=.\ErrorMsgDlg.h
# End Source File
# Begin Source File

SOURCE=.\InitDlgMessage.h
# End Source File
# Begin Source File

SOURCE=.\mscommctrl.h
# End Source File
# Begin Source File

SOURCE=.\PACS.h
# End Source File
# Begin Source File

SOURCE=.\PACSDlg.h
# End Source File
# Begin Source File

SOURCE=.\Password.h
# End Source File
# Begin Source File

SOURCE=.\printer.h
# End Source File
# Begin Source File

SOURCE=.\PrinterControl.h
# End Source File
# Begin Source File

SOURCE=.\PrinterDiagDlg.h
# End Source File
# Begin Source File

SOURCE=.\RescanDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ReSyncDlg.h
# End Source File
# Begin Source File

SOURCE=.\RunDialog.h
# End Source File
# Begin Source File

SOURCE=.\RunProcesses.h
# End Source File
# Begin Source File

SOURCE=.\ScanDiagDlg.h
# End Source File
# Begin Source File

SOURCE=.\Scanner.h
# End Source File
# Begin Source File

SOURCE=.\ScannerControl.h
# End Source File
# Begin Source File

SOURCE=.\SetupDlg.h
# End Source File
# Begin Source File

SOURCE=.\SetupSerializationDlg.h
# End Source File
# Begin Source File

SOURCE=.\simulationconstants.h
# End Source File
# Begin Source File

SOURCE=.\simulator.h
# End Source File
# Begin Source File

SOURCE=.\SNManager.h
# End Source File
# Begin Source File

SOURCE=.\StartupErrorsDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Sxbutton.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Computype.ico
# End Source File
# Begin Source File

SOURCE=.\res\dn_arrow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\help.bmp
# End Source File
# Begin Source File

SOURCE=.\res\left_arrow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PACS.ico
# End Source File
# Begin Source File

SOURCE=.\res\PACS.rc2
# End Source File
# Begin Source File

SOURCE=.\res\rt_arrow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\up_arrow.bmp
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\hlp\AfxDlg.rtf

!IF  "$(CFG)" == "PACS - Win32 Release"

!ELSEIF  "$(CFG)" == "PACS - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MakeHelp.bat

!IF  "$(CFG)" == "PACS - Win32 Release"

!ELSEIF  "$(CFG)" == "PACS - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\PACS.cnt

!IF  "$(CFG)" == "PACS - Win32 Release"

!ELSEIF  "$(CFG)" == "PACS - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\PACS.reg
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\Dio.lib
# End Source File
# End Target
# End Project
# Section PACS : {04598FC4-866C-11CF-AB7C-00AA00C08FCF}
# 	2:5:Class:CCommandButton
# 	2:10:HeaderFile:commandbutton.h
# 	2:8:ImplFile:commandbutton.cpp
# End Section
# Section PACS : {8BD21D13-EC42-11CE-9E0D-00AA006002F3}
# 	2:5:Class:CMdcText
# 	2:10:HeaderFile:mdctext.h
# 	2:8:ImplFile:mdctext.cpp
# End Section
# Section PACS : {978C9E23-D4B0-11CE-BF2D-00AA003F40D0}
# 	2:21:DefaultSinkHeaderFile:labelcontrol.h
# 	2:16:DefaultSinkClass:CLabelControl
# End Section
# Section PACS : {859321D0-3FD1-11CF-8981-00AA00688B10}
# 	2:5:Class:COLEObjects
# 	2:10:HeaderFile:oleobjects.h
# 	2:8:ImplFile:oleobjects.cpp
# End Section
# Section PACS : {8BD21D53-EC42-11CE-9E0D-00AA006002F3}
# 	2:5:Class:CMdcOptionButton
# 	2:10:HeaderFile:mdcoptionbutton.h
# 	2:8:ImplFile:mdcoptionbutton.cpp
# End Section
# Section PACS : {5F4DF280-531B-11CF-91F6-C2863C385E30}
# 	2:5:Class:CMSFlexGrid
# 	2:10:HeaderFile:msflexgrid.h
# 	2:8:ImplFile:msflexgrid.cpp
# End Section
# Section PACS : {6262D3A0-531B-11CF-91F6-C2863C385E30}
# 	2:21:DefaultSinkHeaderFile:msflexgrid.h
# 	2:16:DefaultSinkClass:CMSFlexGrid
# End Section
# Section PACS : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section PACS : {3B7C8860-D78F-101B-B9B5-04021C009402}
# 	2:21:DefaultSinkHeaderFile:richtext.h
# 	2:16:DefaultSinkClass:CRichText
# End Section
# Section PACS : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section PACS : {D92641A0-DF79-11CF-8E74-00A0C90F26F8}
# 	2:5:Class:CRichText
# 	2:10:HeaderFile:richtext.h
# 	2:8:ImplFile:richtext.cpp
# End Section
# Section PACS : {D7053240-CE69-11CD-A777-00DD01143C57}
# 	2:21:DefaultSinkHeaderFile:commandbutton.h
# 	2:16:DefaultSinkClass:CCommandButton
# End Section
# Section PACS : {04598FC1-866C-11CF-AB7C-00AA00C08FCF}
# 	2:5:Class:CLabelControl
# 	2:10:HeaderFile:labelcontrol.h
# 	2:8:ImplFile:labelcontrol.cpp
# End Section
# Section PACS : {8BD21D10-EC42-11CE-9E0D-00AA006002F3}
# 	2:21:DefaultSinkHeaderFile:mdctext.h
# 	2:16:DefaultSinkClass:CMdcText
# End Section
# Section PACS : {ED117630-4090-11CF-8981-00AA00688B10}
# 	2:5:Class:COLEObject
# 	2:10:HeaderFile:oleobject.h
# 	2:8:ImplFile:oleobject.cpp
# End Section
# Section PACS : {8BD21D50-EC42-11CE-9E0D-00AA006002F3}
# 	2:21:DefaultSinkHeaderFile:mdcoptionbutton.h
# 	2:16:DefaultSinkClass:CMdcOptionButton
# End Section
