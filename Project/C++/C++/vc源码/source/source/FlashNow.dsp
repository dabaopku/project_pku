# Microsoft Developer Studio Project File - Name="FlashNow" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=FlashNow - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "FlashNow.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FlashNow.mak" CFG="FlashNow - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FlashNow - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "FlashNow - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/FlashNow", GFAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FlashNow - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /NODEFAULTLIB:libc.lib /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "FlashNow - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "FlashNow - Win32 Release"
# Name "FlashNow - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\2HtmlDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BrowserFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\BrowserFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\BrowserList.cpp
# End Source File
# Begin Source File

SOURCE=.\DropDownToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\FileOpenDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FlashNow.cpp
# End Source File
# Begin Source File

SOURCE=.\FlashNow.rc
# End Source File
# Begin Source File

SOURCE=.\FlashOCX.cpp
# End Source File
# Begin Source File

SOURCE=.\FlashToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\FlashWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\FormBar.cpp
# End Source File
# Begin Source File

SOURCE=.\History.cpp
# End Source File
# Begin Source File

SOURCE=.\LogoBar.cpp
# End Source File
# Begin Source File

SOURCE=.\NavigatorToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SetUpDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Shell.cpp
# End Source File
# Begin Source File

SOURCE=.\ShellList.cpp
# End Source File
# Begin Source File

SOURCE=.\ShellTree.cpp
# End Source File
# Begin Source File

SOURCE=.\ShockwaveFlash.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewerClient.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewerFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewerToolBar.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\2HtmlDlg.h
# End Source File
# Begin Source File

SOURCE=.\BrowserFolder.h
# End Source File
# Begin Source File

SOURCE=.\BrowserFrame.h
# End Source File
# Begin Source File

SOURCE=.\BrowserList.h
# End Source File
# Begin Source File

SOURCE=.\DropDownToolBar.h
# End Source File
# Begin Source File

SOURCE=.\FileOpenDlg.h
# End Source File
# Begin Source File

SOURCE=.\FlashNow.h
# End Source File
# Begin Source File

SOURCE=.\FlashOCX.h
# End Source File
# Begin Source File

SOURCE=.\FlashToolBar.h
# End Source File
# Begin Source File

SOURCE=.\FlashWnd.h
# End Source File
# Begin Source File

SOURCE=.\FormBar.h
# End Source File
# Begin Source File

SOURCE=.\History.h
# End Source File
# Begin Source File

SOURCE=.\LogoBar.h
# End Source File
# Begin Source File

SOURCE=.\NavigatorToolBar.h
# End Source File
# Begin Source File

SOURCE=.\ProgressStatusBar.h
# End Source File
# Begin Source File

SOURCE=.\PropertyDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SetUpDlg.h
# End Source File
# Begin Source File

SOURCE=.\Shell.h
# End Source File
# Begin Source File

SOURCE=.\ShellList.h
# End Source File
# Begin Source File

SOURCE=.\ShellTree.h
# End Source File
# Begin Source File

SOURCE=.\ShockwaveFlash.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ViewerClient.h
# End Source File
# Begin Source File

SOURCE=.\ViewerFrame.h
# End Source File
# Begin Source File

SOURCE=.\ViewerToolBar.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\browser.bmp
# End Source File
# Begin Source File

SOURCE=..\source\ToolKit\cj60libsrc\CJ60Lib\res\btn_arro.bmp
# End Source File
# Begin Source File

SOURCE=.\res\flash.bmp
# End Source File
# Begin Source File

SOURCE=.\res\FlashNow.ico
# End Source File
# Begin Source File

SOURCE=.\res\FlashNow.rc2
# End Source File
# Begin Source File

SOURCE=..\source\ToolKit\cj60libsrc\CJ60Lib\res\hsplitba.cur
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\uninstal.ico
# End Source File
# Begin Source File

SOURCE=..\source\ToolKit\cj60libsrc\CJ60Lib\res\vsplitba.cur
# End Source File
# End Group
# End Target
# End Project
# Section FlashNow : {F1DB5255-FDFC-418D-8CE4-23AFF526291E}
# 	2:19:CLASS: CBrowserTree:CBrowserTree
# 	2:15:BrowserTree.cpp:BrowserTree.cpp
# 	2:13:BrowserTree.h:BrowserTree.h
# 	2:19:Application Include:flashnow.h
# End Section
