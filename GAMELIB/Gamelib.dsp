# Microsoft Developer Studio Project File - Name="Gamelib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Gamelib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Gamelib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Gamelib.mak" CFG="Gamelib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Gamelib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Gamelib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "Gamelib"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Gamelib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W4 /GR /O2 /I "..\gamelib" /I "..\SDL_gfx-2.0.3" /I "..\glSDL" /D "NDEBUG" /D "_LIB" /D "HAVE_OPENGL" /D "WIN32" /D "_MBCS" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Gamelib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /ML /Gm /GR /Zi /Od /I "..\gamelib" /I "..\SDL_gfx-2.0.3" /I "..\glSDL" /D "_DEBUG" /D "_LIB" /D "HAVE_OPENGL" /D "WIN32" /D "_MBCS" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "Gamelib - Win32 Release"
# Name "Gamelib - Win32 Debug"
# Begin Group "Header Files"

# PROP Default_Filter ""
# End Group
# Begin Group "UI"

# PROP Default_Filter ""
# Begin Group "Base"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UI\Font.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\Font.h
# End Source File
# Begin Source File

SOURCE=.\UI\UIThing.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\UIThing.h
# End Source File
# End Group
# Begin Group "Event and Input"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Event\Event.h
# End Source File
# Begin Source File

SOURCE=.\EventSys.h
# End Source File
# Begin Source File

SOURCE=".\Event\Keyboard-utils.h"
# End Source File
# Begin Source File

SOURCE=.\Event\Keyboard.cpp
# End Source File
# Begin Source File

SOURCE=.\Event\Keyboard.h
# End Source File
# End Group
# Begin Group "Widgets"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UI\Button.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\Button.h
# End Source File
# Begin Source File

SOURCE=.\UI\Canvas.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\Canvas.h
# End Source File
# Begin Source File

SOURCE=.\UI\DropDownList.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\DropDownList.h
# End Source File
# Begin Source File

SOURCE=.\UI\HighlightButton.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\HighlightButton.h
# End Source File
# Begin Source File

SOURCE=.\UI\HSlider.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\HSlider.h
# End Source File
# Begin Source File

SOURCE=.\UI\Label.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\Label.h
# End Source File
# Begin Source File

SOURCE=.\UI\List.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\List.h
# End Source File
# Begin Source File

SOURCE=.\UI\ListChooser.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\ListChooser.h
# End Source File
# Begin Source File

SOURCE=.\UI\ProgressBar.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\ProgressBar.h
# End Source File
# Begin Source File

SOURCE=.\UI\SkinCanvas.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\SkinCanvas.h
# End Source File
# Begin Source File

SOURCE=.\UI\TextArea.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\TextArea.h
# End Source File
# Begin Source File

SOURCE=.\UI\TextBox.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\TextBox.h
# End Source File
# Begin Source File

SOURCE=.\UI\ToggleButton.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\ToggleButton.h
# End Source File
# Begin Source File

SOURCE=.\UI\VScrollBar.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\VScrollBar.h
# End Source File
# Begin Source File

SOURCE=.\UI\WorldCanvas.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\WorldCanvas.h
# End Source File
# End Group
# Begin Group "Containers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UI\Console.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\Console.h
# End Source File
# Begin Source File

SOURCE=.\UI\Container.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\Container.h
# End Source File
# Begin Source File

SOURCE=.\UI\DialogBox.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\DialogBox.h
# End Source File
# Begin Source File

SOURCE=.\UI\IniBasedDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\IniBasedDialog.h
# End Source File
# Begin Source File

SOURCE=.\UI\PropertiesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\PropertiesDialog.h
# End Source File
# Begin Source File

SOURCE=.\UI\UISystem.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\UISystem.h
# End Source File
# Begin Source File

SOURCE=.\UI\Wizard.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\Wizard.h
# End Source File
# End Group
# Begin Group "Misc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UI\ConsoleCommand.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\ConsoleCommand.h
# End Source File
# Begin Source File

SOURCE=.\tests.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\UI\NewEventModel.h
# End Source File
# Begin Source File

SOURCE=.\UI.h
# End Source File
# End Group
# Begin Group "NewGameInterface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BR_Game.cpp

!IF  "$(CFG)" == "Gamelib - Win32 Release"

!ELSEIF  "$(CFG)" == "Gamelib - Win32 Debug"

# ADD CPP /GX-

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\BR_Game.h
# End Source File
# End Group
# Begin Group "Display And Textures"

# PROP Default_Filter ""
# Begin Group "Skins"

# PROP Default_Filter ""
# Begin Group "Deprecated"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Graphics\RotateSkin.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Graphics\RotateSkin.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Graphics\CollisionBitMask.cpp
# End Source File
# Begin Source File

SOURCE=.\Graphics\CollisionBitMask.h
# End Source File
# Begin Source File

SOURCE=.\Graphics\SharedRotateSkin.cpp
# End Source File
# Begin Source File

SOURCE=.\Graphics\SharedRotateSkin.h
# End Source File
# Begin Source File

SOURCE=.\Graphics\SharedSkin.cpp
# End Source File
# Begin Source File

SOURCE=.\Graphics\SharedSkin.h
# End Source File
# Begin Source File

SOURCE=.\Graphics\Skin.cpp
# End Source File
# Begin Source File

SOURCE=.\Graphics\Skin.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Graphics\Display.cpp
# End Source File
# Begin Source File

SOURCE=.\Graphics\Display.h
# End Source File
# Begin Source File

SOURCE=.\Graphics\OpenGLDisplay.cpp
# End Source File
# Begin Source File

SOURCE=.\Graphics\OpenGLDisplay.h
# End Source File
# Begin Source File

SOURCE=.\Graphics\SDLDisplay.cpp
# End Source File
# Begin Source File

SOURCE=.\Graphics\SDLDisplay.h
# End Source File
# End Group
# Begin Group "Game"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Game\Collision.cpp
# End Source File
# Begin Source File

SOURCE=.\Game\Collision.h
# End Source File
# Begin Source File

SOURCE=.\Game\Motion.cpp
# End Source File
# Begin Source File

SOURCE=.\Game\Motion.h
# End Source File
# Begin Source File

SOURCE=.\Game\MouseMotion.cpp
# End Source File
# Begin Source File

SOURCE=.\Game\MouseMotion.h
# End Source File
# Begin Source File

SOURCE=.\Game\StraitLineMotion.cpp
# End Source File
# Begin Source File

SOURCE=.\Game\StraitLineMotion.h
# End Source File
# Begin Source File

SOURCE=.\Game\Thing.cpp
# End Source File
# Begin Source File

SOURCE=.\Game\Thing.h
# End Source File
# Begin Source File

SOURCE=.\Game\ThingCollection.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Game\ThingCollection.h
# End Source File
# Begin Source File

SOURCE=.\Game\Tile.h
# End Source File
# Begin Source File

SOURCE=.\Game\World.cpp
# End Source File
# Begin Source File

SOURCE=.\Game\World.h
# End Source File
# End Group
# Begin Group "Sound"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Audio\Music.cpp
# End Source File
# Begin Source File

SOURCE=.\Audio\Music.h
# End Source File
# Begin Source File

SOURCE=.\Audio\SoundEffect.cpp
# End Source File
# Begin Source File

SOURCE=.\Audio\SoundEffect.h
# End Source File
# Begin Source File

SOURCE=.\Audio\SoundMixer.cpp
# End Source File
# Begin Source File

SOURCE=.\Audio\SoundMixer.h
# End Source File
# End Group
# Begin Group "Math"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Misc\2dVector.cpp
# End Source File
# Begin Source File

SOURCE=.\Misc\2dVector.h
# End Source File
# Begin Source File

SOURCE=.\Misc\GameMath.cpp
# End Source File
# Begin Source File

SOURCE=.\Misc\GameMath.h
# End Source File
# End Group
# Begin Group "Special"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Misc\ParticleSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\Misc\ParticleSystem.h
# End Source File
# End Group
# Begin Group "external libs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SDL_Dump\lib\SDL.lib
# End Source File
# Begin Source File

SOURCE=..\SDL_Dump\lib\SDL_image.lib
# End Source File
# Begin Source File

SOURCE=..\SDL_Dump\lib\SDL_mixer.lib
# End Source File
# Begin Source File

SOURCE=..\SDL_Dump\lib\SDLmain.lib
# End Source File
# Begin Source File

SOURCE=..\SDL_Dump\lib\SDL_gfx.lib
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\Program Files\Microsoft Visual Studio\VC98\Lib\GLU32.LIB"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\Program Files\Microsoft Visual Studio\VC98\Lib\OPENGL32.LIB"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\Program Files\Microsoft Visual Studio\VC98\Lib\GLAUX.LIB"
# End Source File
# End Group
# Begin Group "UnitTests"

# PROP Default_Filter ""
# Begin Group "UI tests"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UnitTests\TextBox_tests.h
# End Source File
# Begin Source File

SOURCE=.\UnitTests\ToggleButtonGroup_tests.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\UnitTests\LibraryTest.h
# End Source File
# Begin Source File

SOURCE=.\UnitTests\LibrayTest.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Misc\AssetManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Misc\AssetManager.h
# End Source File
# Begin Source File

SOURCE=.\Tasking\GameScheduler.cpp

!IF  "$(CFG)" == "Gamelib - Win32 Release"

!ELSEIF  "$(CFG)" == "Gamelib - Win32 Debug"

# ADD CPP /GX-

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Tasking\GameScheduler.h
# End Source File
# Begin Source File

SOURCE=.\MouseCursor.h
# End Source File
# Begin Source File

SOURCE=".\pygame alpha blit src.txt"
# End Source File
# Begin Source File

SOURCE=.\SampleGUIXMLFile.txt
# End Source File
# Begin Source File

SOURCE=.\UI\ToggleButtonGroup.cpp
# End Source File
# Begin Source File

SOURCE=.\UI\ToggleButtonGroup.h
# End Source File
# Begin Source File

SOURCE=.\Types.h
# End Source File
# Begin Source File

SOURCE=.\Graphics\VideoMode.h
# End Source File
# End Target
# End Project
