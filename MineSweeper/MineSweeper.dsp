# Microsoft Developer Studio Project File - Name="MineSweeper" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MineSweeper - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MineSweeper.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MineSweeper.mak" CFG="MineSweeper - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MineSweeper - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MineSweeper - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MineSweeper - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "HtmlHelp" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 htmlhelp.lib winmm.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "MineSweeper - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "HtmlHelp" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 HtmlHelp\htmlhelp.lib" winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MineSweeper - Win32 Release"
# Name "MineSweeper - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BestTimes.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildView.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomMines.cpp
# End Source File
# Begin Source File

SOURCE=.\FastestTime.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MineSweeper.cpp
# End Source File
# Begin Source File

SOURCE=.\MineSweeper.rc
# End Source File
# Begin Source File

SOURCE=.\Sound.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\BestTimes.h
# End Source File
# Begin Source File

SOURCE=.\ChildView.h
# End Source File
# Begin Source File

SOURCE=.\ColorsRGB.h
# End Source File
# Begin Source File

SOURCE=.\CustomMines.h
# End Source File
# Begin Source File

SOURCE=.\FastestTime.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MineSweeper.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Sound.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\FaceCool.ico
# End Source File
# Begin Source File

SOURCE=.\res\FaceDead.ico
# End Source File
# Begin Source File

SOURCE=.\res\FaceOooo.ico
# End Source File
# Begin Source File

SOURCE=.\res\FacePressed.ico
# End Source File
# Begin Source File

SOURCE=.\res\FaceSmile.ICO
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00005.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00006.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00007.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00008.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00009.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00010.ico
# End Source File
# Begin Source File

SOURCE=.\res\IcoFace_Mono.ico
# End Source File
# Begin Source File

SOURCE=.\res\icofacep.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\iSq_6.ico
# End Source File
# Begin Source File

SOURCE=.\res\led_0.ico
# End Source File
# Begin Source File

SOURCE=.\res\led_1.ico
# End Source File
# Begin Source File

SOURCE=.\res\led_2.ico
# End Source File
# Begin Source File

SOURCE=.\res\led_3.ico
# End Source File
# Begin Source File

SOURCE=.\res\led_4.ico
# End Source File
# Begin Source File

SOURCE=.\res\led_5.ico
# End Source File
# Begin Source File

SOURCE=.\res\led_6.ico
# End Source File
# Begin Source File

SOURCE=.\res\led_7.ico
# End Source File
# Begin Source File

SOURCE=.\res\led_8.ico
# End Source File
# Begin Source File

SOURCE=.\res\led_9.ico
# End Source File
# Begin Source File

SOURCE=.\res\LtGraySq.ico
# End Source File
# Begin Source File

SOURCE=.\res\MineSweeper.ico
# End Source File
# Begin Source File

SOURCE=.\res\MineSweeper.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Qq_Mine_Red.ico
# End Source File
# Begin Source File

SOURCE=.\Sounds.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Sq_0.ico
# End Source File
# Begin Source File

SOURCE=.\res\Sq_1.ico
# End Source File
# Begin Source File

SOURCE=.\res\Sq_2.ico
# End Source File
# Begin Source File

SOURCE=.\res\Sq_3.ico
# End Source File
# Begin Source File

SOURCE=.\res\Sq_4.ico
# End Source File
# Begin Source File

SOURCE=.\res\Sq_5.ico
# End Source File
# Begin Source File

SOURCE=.\res\Sq_6.ico
# End Source File
# Begin Source File

SOURCE=.\res\Sq_7.ico
# End Source File
# Begin Source File

SOURCE=.\res\Sq_8.ico
# End Source File
# Begin Source File

SOURCE=.\res\Sq_Flag.ico
# End Source File
# Begin Source File

SOURCE=.\res\Sq_Flag_Wrong.ico
# End Source File
# Begin Source File

SOURCE=.\res\Sq_Mine.ico
# End Source File
# Begin Source File

SOURCE=.\res\Sq_Mine_Red.ico
# End Source File
# Begin Source File

SOURCE=.\res\Sq_Mine_Red_Mono.ico
# End Source File
# Begin Source File

SOURCE=.\res\Sq_Mine_Wrong.ico
# End Source File
# Begin Source File

SOURCE=.\res\Sq_Mine_Wrong_Mono.ico
# End Source File
# Begin Source File

SOURCE=.\res\Sq_Mono.ico
# End Source File
# Begin Source File

SOURCE=.\res\Sq_Question.ico
# End Source File
# Begin Source File

SOURCE=.\res\SqMono.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
