# Microsoft Developer Studio Project File - Name="IndustrialGolf" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=IndustrialGolf - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "IndustrialGolf.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IndustrialGolf.mak" CFG="IndustrialGolf - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IndustrialGolf - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "IndustrialGolf - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "IndustrialGolf"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "IndustrialGolf - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GR /GX /O2 /I "C:\PROJECTS\BERTSTOOLBOX" /I "c:\projects\gamelib_2\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "IndustrialGolf - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GR /GX /Zi /Od /Ob1 /I "C:\PROJECTS\BERTSTOOLBOX" /I "c:\projects\gamelib_2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /verbose:lib
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "IndustrialGolf - Win32 Release"
# Name "IndustrialGolf - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\EventGenerator.cpp
# End Source File
# Begin Source File

SOURCE=.\Face.cpp
# End Source File
# Begin Source File

SOURCE=.\Game.cpp
# End Source File
# Begin Source File

SOURCE=.\Globals.cpp
# End Source File
# Begin Source File

SOURCE=.\Level.cpp
# End Source File
# Begin Source File

SOURCE=.\Listeners.cpp
# End Source File
# Begin Source File

SOURCE=.\LoadLevel.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\LocalEventGenerator.cpp
# End Source File
# Begin Source File

SOURCE=.\Player.cpp
# End Source File
# Begin Source File

SOURCE=.\RemoteEventGenerator.cpp
# End Source File
# Begin Source File

SOURCE=.\StartUp.cpp
# End Source File
# Begin Source File

SOURCE=.\Tile.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\EventGenerator.h
# End Source File
# Begin Source File

SOURCE=.\Face.h
# End Source File
# Begin Source File

SOURCE=.\Game.h
# End Source File
# Begin Source File

SOURCE=.\Globals.h
# End Source File
# Begin Source File

SOURCE=.\Level.h
# End Source File
# Begin Source File

SOURCE=.\Listeners.h
# End Source File
# Begin Source File

SOURCE=.\LocalEventGenerator.h
# End Source File
# Begin Source File

SOURCE=.\Player.h
# End Source File
# Begin Source File

SOURCE=.\RemoteEventGenerator.h
# End Source File
# Begin Source File

SOURCE=.\Tile.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Defs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Defaults.ini
# End Source File
# Begin Source File

SOURCE=.\EntityDef.ini
# End Source File
# Begin Source File

SOURCE=.\FaceDef.ini
# End Source File
# Begin Source File

SOURCE=.\TileDef.ini
# End Source File
# End Group
# Begin Group "assets"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Assets.ini
# End Source File
# Begin Source File

SOURCE=.\BackgroundAssets.ini
# End Source File
# Begin Source File

SOURCE=.\EntityAssets.ini
# End Source File
# Begin Source File

SOURCE=.\MiscAssets.ini
# End Source File
# Begin Source File

SOURCE=.\TileAssets.ini
# End Source File
# End Group
# Begin Group "Entities"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Club.cpp
# End Source File
# Begin Source File

SOURCE=.\Club.h
# End Source File
# Begin Source File

SOURCE=.\Door.cpp
# End Source File
# Begin Source File

SOURCE=.\Door.h
# End Source File
# Begin Source File

SOURCE=.\Entity.cpp
# End Source File
# Begin Source File

SOURCE=.\Entity.h
# End Source File
# Begin Source File

SOURCE=.\Goal.cpp
# End Source File
# Begin Source File

SOURCE=.\Goal.h
# End Source File
# Begin Source File

SOURCE=.\GolfBall.cpp
# End Source File
# Begin Source File

SOURCE=.\GolfBall.h
# End Source File
# Begin Source File

SOURCE=.\OscillatingFan.cpp
# End Source File
# Begin Source File

SOURCE=.\OscillatingFan.h
# End Source File
# Begin Source File

SOURCE=.\Star.cpp
# End Source File
# Begin Source File

SOURCE=.\Star.h
# End Source File
# Begin Source File

SOURCE=.\Switch.cpp
# End Source File
# Begin Source File

SOURCE=.\Switch.h
# End Source File
# Begin Source File

SOURCE=.\Tee.cpp
# End Source File
# Begin Source File

SOURCE=.\Tee.h
# End Source File
# Begin Source File

SOURCE=.\Teleporter.cpp
# End Source File
# Begin Source File

SOURCE=.\Teleporter.h
# End Source File
# Begin Source File

SOURCE=.\UpWind.cpp
# End Source File
# Begin Source File

SOURCE=.\UpWind.h
# End Source File
# End Group
# Begin Group "Depricated"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\NewThing.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\NewThing.h
# End Source File
# End Group
# Begin Group "UI"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UI\dialogs.ini
# End Source File
# Begin Source File

SOURCE=.\UI.cpp
# End Source File
# Begin Source File

SOURCE=.\UI.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Games.ini
# End Source File
# Begin Source File

SOURCE=".\Posable Sequence of events.txt"
# End Source File
# End Target
# End Project
