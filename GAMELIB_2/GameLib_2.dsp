# Microsoft Developer Studio Project File - Name="GameLib_2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=GameLib_2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GameLib_2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GameLib_2.mak" CFG="GameLib_2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GameLib_2 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "GameLib_2 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "GameLib_2 - Win32 Demo" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "GameLib_2"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GameLib_2 - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GR /O2 /I "./include" /I "../include" /I "C:\PROJECTS\BERTSTOOLBOX" /D "NDEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "GameLib_2 - Win32 Debug"

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
# ADD CPP /nologo /MD /W3 /Gm /GR /Zi /Od /Ob1 /I "./include" /I "../include" /I "C:\PROJECTS\BERTSTOOLBOX" /D "_LIB" /D "WIN32" /D "HTS_DEBUG" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "GameLib_2 - Win32 Demo"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "GameLib_2___Win32_Demo"
# PROP BASE Intermediate_Dir "GameLib_2___Win32_Demo"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "GameLib_2___Win32_Demo"
# PROP Intermediate_Dir "GameLib_2___Win32_Demo"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GR /O2 /I "./include" /I "../include" /I "C:\PROJECTS\BERTSTOOLBOX" /D "NDEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /O2 /I "./include" /I "../include" /I "C:\PROJECTS\BERTSTOOLBOX" /D "NDEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "GameLib_2 - Win32 Release"
# Name "GameLib_2 - Win32 Debug"
# Name "GameLib_2 - Win32 Demo"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Audio"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Audio\Music.cpp
# End Source File
# Begin Source File

SOURCE=.\include\Music.h
# End Source File
# Begin Source File

SOURCE=.\src\Audio\SoundEffect.cpp
# End Source File
# Begin Source File

SOURCE=.\include\SoundEffect.h
# End Source File
# Begin Source File

SOURCE=.\src\Audio\SoundMixer.cpp
# End Source File
# Begin Source File

SOURCE=.\include\SoundMixer.h
# End Source File
# End Group
# Begin Group "Event"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\EventSys.h
# End Source File
# Begin Source File

SOURCE=".\include\Keyboard-utils.h"
# End Source File
# Begin Source File

SOURCE=.\src\Event\Keyboard.cpp
# End Source File
# Begin Source File

SOURCE=.\include\Keyboard.h
# End Source File
# Begin Source File

SOURCE=.\include\NewEventModel.h
# End Source File
# End Group
# Begin Group "Game"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Game\Thing.cpp
# End Source File
# Begin Source File

SOURCE=.\include\Thing.h
# End Source File
# Begin Source File

SOURCE=.\include\Tile.h
# End Source File
# Begin Source File

SOURCE=.\src\Game\World.cpp
# End Source File
# Begin Source File

SOURCE=.\include\World.h
# End Source File
# End Group
# Begin Group "Graphics"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Graphics\CollisionBitMask.cpp
# End Source File
# Begin Source File

SOURCE=.\include\CollisionBitMask.h
# End Source File
# Begin Source File

SOURCE=.\src\Graphics\Display.cpp
# End Source File
# Begin Source File

SOURCE=.\include\Display.h
# End Source File
# Begin Source File

SOURCE=.\src\Graphics\OpenGLDisplay.cpp
# End Source File
# Begin Source File

SOURCE=.\include\OpenGLDisplay.h
# End Source File
# Begin Source File

SOURCE=.\src\Graphics\pygame_alpha_blit.c
# End Source File
# Begin Source File

SOURCE=.\src\Graphics\RotateSkin.cpp
# End Source File
# Begin Source File

SOURCE=.\include\RotateSkin.h
# End Source File
# Begin Source File

SOURCE=.\src\Graphics\SDLDisplay.cpp
# End Source File
# Begin Source File

SOURCE=.\include\sdldisplay.h
# End Source File
# Begin Source File

SOURCE=.\src\Graphics\SharedRotateSkin.cpp
# End Source File
# Begin Source File

SOURCE=.\include\SharedRotateSkin.h
# End Source File
# Begin Source File

SOURCE=.\src\Graphics\SharedSkin.cpp
# End Source File
# Begin Source File

SOURCE=.\include\SharedSkin.h
# End Source File
# Begin Source File

SOURCE=.\src\Graphics\Skin.cpp
# End Source File
# Begin Source File

SOURCE=.\include\Skin.h
# End Source File
# End Group
# Begin Group "Assets"

# PROP Default_Filter ""
# Begin Group "Loaders"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Asset\FontLoader.cpp
# End Source File
# Begin Source File

SOURCE=.\include\FontLoader.h
# End Source File
# Begin Source File

SOURCE=.\src\Asset\RotateSkinLoader.cpp
# End Source File
# Begin Source File

SOURCE=.\include\RotateSkinLoader.h
# End Source File
# Begin Source File

SOURCE=.\src\Asset\SkinLoader.cpp
# End Source File
# Begin Source File

SOURCE=.\include\SkinLoader.h
# End Source File
# Begin Source File

SOURCE=.\src\Asset\SoundEffectLoader.cpp
# End Source File
# Begin Source File

SOURCE=.\include\SoundEffectLoader.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\Asset\AM.cpp
# End Source File
# Begin Source File

SOURCE=.\include\AM.h
# End Source File
# Begin Source File

SOURCE=.\src\Misc\AssetManager.cpp
# End Source File
# Begin Source File

SOURCE=.\include\AssetManager.h
# End Source File
# Begin Source File

SOURCE=.\include\Cache.h
# End Source File
# End Group
# Begin Group "Math"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Misc\2dVector.cpp
# End Source File
# Begin Source File

SOURCE=.\include\2dVector.h
# End Source File
# Begin Source File

SOURCE=.\src\Misc\GameMath.cpp
# End Source File
# Begin Source File

SOURCE=.\include\GameMath.h
# End Source File
# End Group
# Begin Group "Scripting"

# PROP Default_Filter ""
# End Group
# Begin Group "UI"

# PROP Default_Filter ""
# Begin Group "Widgets"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\UI\Button.cpp
# End Source File
# Begin Source File

SOURCE=.\include\Button.h
# End Source File
# Begin Source File

SOURCE=.\src\UI\Canvas.cpp
# End Source File
# Begin Source File

SOURCE=.\include\Canvas.h
# End Source File
# Begin Source File

SOURCE=.\src\UI\dropdownlist.cpp
# End Source File
# Begin Source File

SOURCE=.\include\DropDownList.h
# End Source File
# Begin Source File

SOURCE=.\src\UI\HighlightButton.cpp
# End Source File
# Begin Source File

SOURCE=.\include\HighlightButton.h
# End Source File
# Begin Source File

SOURCE=.\src\UI\HSlider.cpp
# End Source File
# Begin Source File

SOURCE=.\include\HSlider.h
# End Source File
# Begin Source File

SOURCE=.\src\UI\Label.cpp
# End Source File
# Begin Source File

SOURCE=.\include\Label.h
# End Source File
# Begin Source File

SOURCE=.\src\UI\List.cpp
# End Source File
# Begin Source File

SOURCE=.\include\List.h
# End Source File
# Begin Source File

SOURCE=.\src\UI\ListChooser.cpp
# End Source File
# Begin Source File

SOURCE=.\include\listchooser.h
# End Source File
# Begin Source File

SOURCE=.\src\UI\ProgressBar.cpp
# End Source File
# Begin Source File

SOURCE=.\include\ProgressBar.h
# End Source File
# Begin Source File

SOURCE=.\src\UI\RadioButton.cpp
# End Source File
# Begin Source File

SOURCE=.\include\RadioButton.h
# End Source File
# Begin Source File

SOURCE=.\src\UI\SkinCanvas.cpp
# End Source File
# Begin Source File

SOURCE=.\include\SkinCanvas.h
# End Source File
# Begin Source File

SOURCE=.\src\UI\TextArea.cpp
# End Source File
# Begin Source File

SOURCE=.\include\TextArea.h
# End Source File
# Begin Source File

SOURCE=.\src\UI\TextBox.cpp
# End Source File
# Begin Source File

SOURCE=.\include\TextBox.h
# End Source File
# Begin Source File

SOURCE=.\src\UI\ToggleButton.cpp
# End Source File
# Begin Source File

SOURCE=.\include\ToggleButton.h
# End Source File
# Begin Source File

SOURCE=.\src\UI\VScrollBar.cpp
# End Source File
# Begin Source File

SOURCE=.\include\VScrollBar.h
# End Source File
# Begin Source File

SOURCE=.\src\UI\WorldCanvas.cpp
# End Source File
# Begin Source File

SOURCE=.\include\WorldCanvas.h
# End Source File
# End Group
# Begin Group "Container"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\UI\Console.cpp
# End Source File
# Begin Source File

SOURCE=.\include\Console.h
# End Source File
# Begin Source File

SOURCE=.\src\UI\Container.cpp
# End Source File
# Begin Source File

SOURCE=.\include\Container.h
# End Source File
# Begin Source File

SOURCE=.\src\UI\DialogBox.cpp
# End Source File
# Begin Source File

SOURCE=.\include\DialogBox.h
# End Source File
# Begin Source File

SOURCE=.\src\UI\IniBasedDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\include\IniBasedDialog.h
# End Source File
# Begin Source File

SOURCE=.\src\UI\PropertiesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\include\PropertiesDialog.h
# End Source File
# Begin Source File

SOURCE=.\src\UI\UISystem.cpp
# End Source File
# Begin Source File

SOURCE=.\include\UISystem.h
# End Source File
# Begin Source File

SOURCE=.\src\UI\Wizard.cpp
# End Source File
# Begin Source File

SOURCE=.\include\Wizard.h
# End Source File
# End Group
# Begin Group "Font"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\UI\Font.cpp
# End Source File
# Begin Source File

SOURCE=.\include\Font.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\UI\MouseCursor.cpp
# End Source File
# Begin Source File

SOURCE=.\include\MouseCursor.h
# End Source File
# Begin Source File

SOURCE=.\include\ui.h
# End Source File
# Begin Source File

SOURCE=.\src\UI\UIThing.cpp
# End Source File
# Begin Source File

SOURCE=.\include\UIThing.h
# End Source File
# End Group
# Begin Group "Particle"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Misc\ParticleSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\include\ParticleSystem.h
# End Source File
# End Group
# Begin Group "Core"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Core\BR_Game.cpp
# End Source File
# Begin Source File

SOURCE=.\include\BR_Game.h
# End Source File
# End Group
# Begin Group "tasking"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\GameScheduler.cpp
# End Source File
# Begin Source File

SOURCE=.\include\ThinkScheduler.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\Misc\AManager.cpp
# End Source File
# Begin Source File

SOURCE=.\include\AManager.h
# End Source File
# Begin Source File

SOURCE=.\src\Tasking\ThinkDelegate.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Tasking\ThinkScheduler.cpp
# End Source File
# End Group
# Begin Group "UnitTests"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\UnitTest\AM_tests.h
# End Source File
# Begin Source File

SOURCE=.\include\UnitTest\AManager_tests.h
# End Source File
# Begin Source File

SOURCE=.\include\UnitTest\Cache_Skin_tests.h
# End Source File
# Begin Source File

SOURCE=.\include\UnitTest\Cache_test.h
# End Source File
# Begin Source File

SOURCE=.\include\UnitTest\LibraryTest.h
# End Source File
# Begin Source File

SOURCE=.\UnitTests\LibrayTest.cpp
# End Source File
# Begin Source File

SOURCE=.\include\UnitTest\TextBox_tests.h
# End Source File
# Begin Source File

SOURCE=.\include\UnitTest\ToggleButtonGroup_tests.h
# End Source File
# End Group
# Begin Group "external libs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SDL_Dump\lib\SDLmain.lib
# End Source File
# Begin Source File

SOURCE=..\SDL_Dump\lib\SDL_gfx.lib
# End Source File
# Begin Source File

SOURCE=..\SDL_Dump\lib\SDL_image.lib
# End Source File
# Begin Source File

SOURCE=..\SDL_Dump\lib\SDL.lib
# End Source File
# Begin Source File

SOURCE="..\..\Program Files\Microsoft Visual Studio\VC98\Lib\OPENGL32.LIB"
# End Source File
# Begin Source File

SOURCE="..\..\Program Files\Microsoft Visual Studio\VC98\Lib\GLU32.LIB"
# End Source File
# Begin Source File

SOURCE="..\..\Program Files\Microsoft Visual Studio\VC98\Lib\GLAUX.LIB"
# End Source File
# End Group
# Begin Source File

SOURCE=.\include\GameScheduler.h
# End Source File
# Begin Source File

SOURCE=.\include\ThinkDelegate.h
# End Source File
# Begin Source File

SOURCE=..\SDL_Dump\lib\SDL_Mixer_static.lib
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\SDL_Dump\lib\SDL_mixer.lib
# End Source File
# End Target
# End Project
