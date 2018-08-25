@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by HELPAPP.HPJ. >"hlp\HelpApp.hm"
echo. >>"hlp\HelpApp.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\HelpApp.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\HelpApp.hm"
echo. >>"hlp\HelpApp.hm"
echo // Prompts (IDP_*) >>"hlp\HelpApp.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\HelpApp.hm"
echo. >>"hlp\HelpApp.hm"
echo // Resources (IDR_*) >>"hlp\HelpApp.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\HelpApp.hm"
echo. >>"hlp\HelpApp.hm"
echo // Dialogs (IDD_*) >>"hlp\HelpApp.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\HelpApp.hm"
echo. >>"hlp\HelpApp.hm"
echo // Frame Controls (IDW_*) >>"hlp\HelpApp.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\HelpApp.hm"
REM -- Make help for Project HELPAPP


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\HelpApp.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\HelpApp.hlp" goto :Error
if not exist "hlp\HelpApp.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\HelpApp.hlp" Debug
if exist Debug\nul copy "hlp\HelpApp.cnt" Debug
if exist Release\nul copy "hlp\HelpApp.hlp" Release
if exist Release\nul copy "hlp\HelpApp.cnt" Release
echo.
goto :done

:Error
echo hlp\HelpApp.hpj(1) : error: Problem encountered creating help file

:done
echo.
