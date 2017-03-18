# Microsoft Developer Studio Project File - Name="colorcubes" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=colorcubes - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "colorcubes.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "colorcubes.mak" CFG="colorcubes - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "colorcubes - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "colorcubes - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "colorcubes"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "colorcubes - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GR /O2 /I "C:\PROJECTS\BERTSTOOLBOX" /I "c:\projects\gamelib_2\include" /D "NDEBUG" /D "_CONSOLE" /D "WIN32" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"Release/BarrelDrop.exe"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "colorcubes - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GR /Zi /Od /I "C:\PROJECTS\BERTSTOOLBOX" /I "c:\projects\gamelib_2\include" /D "_DEBUG" /D "_CONSOLE" /D "WIN32" /D "_MBCS" /YX /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"Debug/BarrelDrop.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "colorcubes - Win32 Release"
# Name "colorcubes - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Block.cpp
# End Source File
# Begin Source File

SOURCE=.\Board.cpp
# End Source File
# Begin Source File

SOURCE=.\Globals.cpp
# End Source File
# Begin Source File

SOURCE=.\HighScores.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\ParticleTraits.cpp
# End Source File
# Begin Source File

SOURCE=.\Score.cpp
# End Source File
# Begin Source File

SOURCE=.\Shape.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Block.h
# End Source File
# Begin Source File

SOURCE=.\Board.h
# End Source File
# Begin Source File

SOURCE=.\ColorCode.h
# End Source File
# Begin Source File

SOURCE=.\Globals.h
# End Source File
# Begin Source File

SOURCE=.\HighScores.h
# End Source File
# Begin Source File

SOURCE=.\ParticleTraits.h
# End Source File
# Begin Source File

SOURCE=.\Score.h
# End Source File
# Begin Source File

SOURCE=.\Shape.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\BarrelDrop.ico
# End Source File
# End Group
# Begin Group "UI"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BusyDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\BusyDialog.h
# End Source File
# Begin Source File

SOURCE=.\FireworksDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\FireworksDialog.h
# End Source File
# Begin Source File

SOURCE=.\GameDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GameDialog.h
# End Source File
# Begin Source File

SOURCE=.\GameModeDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GameModeDialog.h
# End Source File
# Begin Source File

SOURCE=.\GameUI.cpp
# End Source File
# Begin Source File

SOURCE=.\GameUI.h
# End Source File
# Begin Source File

SOURCE=.\HighScoresDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\HighScoresDialog.h
# End Source File
# Begin Source File

SOURCE=.\Listeners.cpp
# End Source File
# Begin Source File

SOURCE=.\Listeners.h
# End Source File
# Begin Source File

SOURCE=.\NextShapeCanvas.cpp
# End Source File
# Begin Source File

SOURCE=.\NextShapeCanvas.h
# End Source File
# Begin Source File

SOURCE=.\OptionsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsDialog.h
# End Source File
# Begin Source File

SOURCE=.\SpecialTextCanvas.cpp
# End Source File
# Begin Source File

SOURCE=.\SpecialTextCanvas.h
# End Source File
# Begin Source File

SOURCE=.\SplashScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\SplashScreen.h
# End Source File
# End Group
# Begin Group "Assets"

# PROP Default_Filter ""
# Begin Group "Game Modes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Easy.ini
# End Source File
# Begin Source File

SOURCE=.\Hard.ini
# End Source File
# Begin Source File

SOURCE=.\Medium.ini
# End Source File
# Begin Source File

SOURCE=.\Survivor.ini
# End Source File
# End Group
# Begin Group "dialogs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ui\Buttons.ini
# End Source File
# Begin Source File

SOURCE=.\ui\ChooseGameMode.ini
# End Source File
# Begin Source File

SOURCE=.\ui\Credits.ini
# End Source File
# Begin Source File

SOURCE=.\UI\Dialogs.ini
# End Source File
# Begin Source File

SOURCE=.\ui\Fonts.ini
# End Source File
# Begin Source File

SOURCE=.\ui\Game.ini
# End Source File
# Begin Source File

SOURCE=.\ui\GameOver.ini
# End Source File
# Begin Source File

SOURCE=.\UI\HighScoresScreen.ini
# End Source File
# Begin Source File

SOURCE=.\InstructionsWizard.ini
# End Source File
# Begin Source File

SOURCE=.\ui\MainMenu.ini
# End Source File
# Begin Source File

SOURCE=.\ui\Mouse.ini
# End Source File
# Begin Source File

SOURCE=.\ui\Options.ini
# End Source File
# Begin Source File

SOURCE=.\QuickStart.ini
# End Source File
# End Group
# Begin Source File

SOURCE=.\Assets.ini
# End Source File
# Begin Source File

SOURCE=.\docAssets.ini
# End Source File
# Begin Source File

SOURCE=.\Misc.ini
# End Source File
# Begin Source File

SOURCE=.\Options.ini
# End Source File
# Begin Source File

SOURCE=.\Scoring.ini
# End Source File
# Begin Source File

SOURCE=.\Sounds.ini
# End Source File
# Begin Source File

SOURCE=.\Text.ini
# End Source File
# Begin Source File

SOURCE=.\UIAssets.ini
# End Source File
# End Group
# Begin Source File

SOURCE=.\demoAssets.ini
# End Source File
# Begin Source File

SOURCE=.\noDemoAssets.ini
# End Source File
# Begin Source File

SOURCE=.\Unlocker.txt
# End Source File
# End Target
# End Project
