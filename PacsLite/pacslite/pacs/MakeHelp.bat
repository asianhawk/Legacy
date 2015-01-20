@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by PACS.HPJ. >"hlp\PACS.hm"
echo. >>"hlp\PACS.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\PACS.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\PACS.hm"
echo. >>"hlp\PACS.hm"
echo // Prompts (IDP_*) >>"hlp\PACS.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\PACS.hm"
echo. >>"hlp\PACS.hm"
echo // Resources (IDR_*) >>"hlp\PACS.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\PACS.hm"
echo. >>"hlp\PACS.hm"
echo // Dialogs (IDD_*) >>"hlp\PACS.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\PACS.hm"
echo. >>"hlp\PACS.hm"
echo // Frame Controls (IDW_*) >>"hlp\PACS.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\PACS.hm"
REM -- Make help for Project PACS


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\PACS.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\PACS.hlp" goto :Error
if not exist "hlp\PACS.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\PACS.hlp" Debug
if exist Debug\nul copy "hlp\PACS.cnt" Debug
if exist Release\nul copy "hlp\PACS.hlp" Release
if exist Release\nul copy "hlp\PACS.cnt" Release
echo.
goto :done

:Error
echo hlp\PACS.hpj(1) : error: Problem encountered creating help file

:done
echo.
