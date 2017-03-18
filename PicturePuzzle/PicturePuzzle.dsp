# Microsoft Developer Studio Project File - Name="PicturePuzzle" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PicturePuzzle - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PicturePuzzle.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PicturePuzzle.mak" CFG="PicturePuzzle - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PicturePuzzle - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PicturePuzzle - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "PicturePuzzle - Win32 Demo" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "PicturePuzzle"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PicturePuzzle - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "c:\projects\gamelib_2\include" /I "C:\PROJECTS\BERTSTOOLBOX" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
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
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "PicturePuzzle - Win32 Debug"

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
# ADD CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "c:\projects\gamelib_2\include" /I "C:\PROJECTS\BERTSTOOLBOX" /D "_WINDOWS" /D "WIN32" /D "HTS_DEBUG" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "PicturePuzzle - Win32 Demo"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "PicturePuzzle___Win32_Demo"
# PROP BASE Intermediate_Dir "PicturePuzzle___Win32_Demo"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "PicturePuzzle___Win32_Demo"
# PROP Intermediate_Dir "PicturePuzzle___Win32_Demo"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GR /GX /O2 /I "c:\projects\gamelib_2\include" /I "C:\PROJECTS\BERTSTOOLBOX" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "c:\projects\gamelib_2\include" /I "C:\PROJECTS\BERTSTOOLBOX" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_DEMO" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "PicturePuzzle - Win32 Release"
# Name "PicturePuzzle - Win32 Debug"
# Name "PicturePuzzle - Win32 Demo"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Picture.cpp
# End Source File
# Begin Source File

SOURCE=.\Playfield.cpp
# End Source File
# Begin Source File

SOURCE=.\StartUp.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Picture.h
# End Source File
# Begin Source File

SOURCE=.\Playfield.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Icon.ico
# End Source File
# End Group
# Begin Group "UI"

# PROP Default_Filter ""
# Begin Group "modes"

# PROP Default_Filter ""
# Begin Group "Obsolite"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LayoutSwapper.cpp
# End Source File
# Begin Source File

SOURCE=.\LayoutSwapper.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\LayoutPuzzle.cpp
# End Source File
# Begin Source File

SOURCE=.\LayoutPuzzle.h
# End Source File
# Begin Source File

SOURCE=.\LayoutSlider.cpp
# End Source File
# Begin Source File

SOURCE=.\LayoutSlider.h
# End Source File
# Begin Source File

SOURCE=.\LayoutSwapper2.cpp
# End Source File
# Begin Source File

SOURCE=.\LayoutSwapper2.h
# End Source File
# End Group
# Begin Group "GamePlay"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GameDialog.h
# End Source File
# Begin Source File

SOURCE=.\Layout.cpp
# End Source File
# Begin Source File

SOURCE=.\Layout.h
# End Source File
# Begin Source File

SOURCE=.\PieceBucket.cpp
# End Source File
# Begin Source File

SOURCE=.\PieceBucket.h
# End Source File
# End Group
# Begin Group "ui-ini"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UI\Dialogs.ini
# End Source File
# Begin Source File

SOURCE=.\UI\Game_dlg.ini
# End Source File
# Begin Source File

SOURCE=.\Options_assets.ini
# End Source File
# Begin Source File

SOURCE=.\UI\Options_dlg.ini
# End Source File
# Begin Source File

SOURCE=.\UI\Preview_dlg.ini
# End Source File
# End Group
# Begin Group "Pieces"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Piece.cpp
# End Source File
# Begin Source File

SOURCE=.\Piece.h
# End Source File
# Begin Source File

SOURCE=.\StrechablePiece.cpp
# End Source File
# Begin Source File

SOURCE=.\StretchablePiece.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\BrowserItem.cpp
# End Source File
# Begin Source File

SOURCE=.\BrowserItem.h
# End Source File
# Begin Source File

SOURCE=.\ChooseModeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChooseModeDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainMenuDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainMenuDlg.h
# End Source File
# Begin Source File

SOURCE=.\OptionsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsDialog.h
# End Source File
# Begin Source File

SOURCE=.\PictureBrowser.cpp
# End Source File
# Begin Source File

SOURCE=.\PictureBrowser.h
# End Source File
# Begin Source File

SOURCE=.\SplashScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\SplashScreen.h
# End Source File
# End Group
# Begin Group "Obsolite No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OnDeck.cpp
# End Source File
# Begin Source File

SOURCE=.\OnDeck.h
# End Source File
# End Group
# Begin Group "tests"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DShow8.cpp

!IF  "$(CFG)" == "PicturePuzzle - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "PicturePuzzle - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "PicturePuzzle - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DShow8.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Assets.ini
# End Source File
# Begin Source File

SOURCE=.\Assets_Common.ini
# End Source File
# Begin Source File

SOURCE=.\Assets_Demo.ini
# End Source File
# Begin Source File

SOURCE=.\Assets_Full.ini
# End Source File
# Begin Source File

SOURCE=.\assets\assets_ui.ini
# End Source File
# Begin Source File

SOURCE=.\AudioAssets.ini
# End Source File
# Begin Source File

SOURCE=.\assets\dlg\dlg_MainMenu.ini
# End Source File
# Begin Source File

SOURCE=.\assets\dlg\dlg_PlayScreen.ini
# End Source File
# Begin Source File

SOURCE=.\assets\dlg\dlg_Preview.ini
# End Source File
# Begin Source File

SOURCE=".\Old Dialogs.txt"
# End Source File
# Begin Source File

SOURCE=.\Options.ini
# End Source File
# Begin Source File

SOURCE=.\pictures.ini
# End Source File
# Begin Source File

SOURCE=..\SDL_Dump\lib\SDL_Mixer_static.lib
# PROP Exclude_From_Build 1
# End Source File
# End Target
# End Project
