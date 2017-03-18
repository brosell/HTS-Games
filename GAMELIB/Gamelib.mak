# Microsoft Developer Studio Generated NMAKE File, Based on Gamelib.dsp
!IF "$(CFG)" == ""
CFG=Gamelib - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Gamelib - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Gamelib - Win32 Release" && "$(CFG)" != "Gamelib - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Gamelib - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Gamelib.lib"

!ELSE 

ALL : "BertsToolBoxLib - Win32 Release" "$(OUTDIR)\Gamelib.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"BertsToolBoxLib - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\2dVector.obj"
	-@erase "$(INTDIR)\AssetManager.obj"
	-@erase "$(INTDIR)\BR_Game.obj"
	-@erase "$(INTDIR)\Button.obj"
	-@erase "$(INTDIR)\Canvas.obj"
	-@erase "$(INTDIR)\Collision.obj"
	-@erase "$(INTDIR)\CollisionBitMask.obj"
	-@erase "$(INTDIR)\Console.obj"
	-@erase "$(INTDIR)\ConsoleCommand.obj"
	-@erase "$(INTDIR)\Container.obj"
	-@erase "$(INTDIR)\DialogBox.obj"
	-@erase "$(INTDIR)\Display.obj"
	-@erase "$(INTDIR)\DropDownList.obj"
	-@erase "$(INTDIR)\Font.obj"
	-@erase "$(INTDIR)\GameMath.obj"
	-@erase "$(INTDIR)\GameScheduler.obj"
	-@erase "$(INTDIR)\HighlightButton.obj"
	-@erase "$(INTDIR)\HSlider.obj"
	-@erase "$(INTDIR)\IniBasedDialog.obj"
	-@erase "$(INTDIR)\Keyboard.obj"
	-@erase "$(INTDIR)\Label.obj"
	-@erase "$(INTDIR)\List.obj"
	-@erase "$(INTDIR)\Motion.obj"
	-@erase "$(INTDIR)\MouseMotion.obj"
	-@erase "$(INTDIR)\Music.obj"
	-@erase "$(INTDIR)\OpenGLDisplay.obj"
	-@erase "$(INTDIR)\ParticleSystem.obj"
	-@erase "$(INTDIR)\ProgressBar.obj"
	-@erase "$(INTDIR)\SDLDisplay.obj"
	-@erase "$(INTDIR)\SharedRotateSkin.obj"
	-@erase "$(INTDIR)\SharedSkin.obj"
	-@erase "$(INTDIR)\Skin.obj"
	-@erase "$(INTDIR)\SkinCanvas.obj"
	-@erase "$(INTDIR)\SoundEffect.obj"
	-@erase "$(INTDIR)\SoundMixer.obj"
	-@erase "$(INTDIR)\StraitLineMotion.obj"
	-@erase "$(INTDIR)\tests.obj"
	-@erase "$(INTDIR)\TextArea.obj"
	-@erase "$(INTDIR)\TextBox.obj"
	-@erase "$(INTDIR)\Thing.obj"
	-@erase "$(INTDIR)\ThingCollection.obj"
	-@erase "$(INTDIR)\ToggleButton.obj"
	-@erase "$(INTDIR)\UISystem.obj"
	-@erase "$(INTDIR)\UIThing.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VScrollBar.obj"
	-@erase "$(INTDIR)\Wizard.obj"
	-@erase "$(INTDIR)\World.obj"
	-@erase "$(INTDIR)\WorldCanvas.obj"
	-@erase "$(OUTDIR)\Gamelib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W4 /Ob1 /I "..\gamelib" /I "..\SDL_gfx-2.0.3" /I "..\glSDL" /D "NDEBUG" /D "_LIB" /D "HAVE_OPENGL" /D "WIN32" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Gamelib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\Gamelib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Font.obj" \
	"$(INTDIR)\UIThing.obj" \
	"$(INTDIR)\Keyboard.obj" \
	"$(INTDIR)\Button.obj" \
	"$(INTDIR)\Canvas.obj" \
	"$(INTDIR)\DropDownList.obj" \
	"$(INTDIR)\HighlightButton.obj" \
	"$(INTDIR)\HSlider.obj" \
	"$(INTDIR)\Label.obj" \
	"$(INTDIR)\List.obj" \
	"$(INTDIR)\ProgressBar.obj" \
	"$(INTDIR)\SkinCanvas.obj" \
	"$(INTDIR)\TextArea.obj" \
	"$(INTDIR)\TextBox.obj" \
	"$(INTDIR)\ToggleButton.obj" \
	"$(INTDIR)\VScrollBar.obj" \
	"$(INTDIR)\WorldCanvas.obj" \
	"$(INTDIR)\Console.obj" \
	"$(INTDIR)\Container.obj" \
	"$(INTDIR)\DialogBox.obj" \
	"$(INTDIR)\IniBasedDialog.obj" \
	"$(INTDIR)\UISystem.obj" \
	"$(INTDIR)\Wizard.obj" \
	"$(INTDIR)\ConsoleCommand.obj" \
	"$(INTDIR)\tests.obj" \
	"$(INTDIR)\BR_Game.obj" \
	"$(INTDIR)\CollisionBitMask.obj" \
	"$(INTDIR)\SharedRotateSkin.obj" \
	"$(INTDIR)\SharedSkin.obj" \
	"$(INTDIR)\Skin.obj" \
	"$(INTDIR)\Display.obj" \
	"$(INTDIR)\OpenGLDisplay.obj" \
	"$(INTDIR)\SDLDisplay.obj" \
	"$(INTDIR)\Collision.obj" \
	"$(INTDIR)\Motion.obj" \
	"$(INTDIR)\MouseMotion.obj" \
	"$(INTDIR)\StraitLineMotion.obj" \
	"$(INTDIR)\Thing.obj" \
	"$(INTDIR)\ThingCollection.obj" \
	"$(INTDIR)\World.obj" \
	"$(INTDIR)\Music.obj" \
	"$(INTDIR)\SoundEffect.obj" \
	"$(INTDIR)\SoundMixer.obj" \
	"$(INTDIR)\2dVector.obj" \
	"$(INTDIR)\GameMath.obj" \
	"$(INTDIR)\ParticleSystem.obj" \
	"$(INTDIR)\AssetManager.obj" \
	"$(INTDIR)\GameScheduler.obj" \
	"..\SDL_Dump\lib\SDL.lib" \
	"..\SDL_Dump\lib\SDL_image.lib" \
	"..\SDL_Dump\lib\SDL_mixer.lib" \
	"..\SDL_Dump\lib\SDLmain.lib" \
	"..\SDL_Dump\lib\SDL_gfx.lib" \
	"..\SDL_Dump\lib\SFont.lib" \
	"..\..\Program Files\Microsoft Visual Studio\VC98\Lib\GLU32.LIB" \
	"..\..\Program Files\Microsoft Visual Studio\VC98\Lib\OPENGL32.LIB" \
	"..\..\Program Files\Microsoft Visual Studio\VC98\Lib\WINMM.LIB" \
	"..\..\Program Files\Microsoft Visual Studio\VC98\Lib\GLAUX.LIB" \
	"..\BertsToolBox\Release\BertsToolBoxLib.lib"

"$(OUTDIR)\Gamelib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Gamelib - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Gamelib.lib"

!ELSE 

ALL : "BertsToolBoxLib - Win32 Debug" "$(OUTDIR)\Gamelib.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"BertsToolBoxLib - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\2dVector.obj"
	-@erase "$(INTDIR)\AssetManager.obj"
	-@erase "$(INTDIR)\BR_Game.obj"
	-@erase "$(INTDIR)\Button.obj"
	-@erase "$(INTDIR)\Canvas.obj"
	-@erase "$(INTDIR)\Collision.obj"
	-@erase "$(INTDIR)\CollisionBitMask.obj"
	-@erase "$(INTDIR)\Console.obj"
	-@erase "$(INTDIR)\ConsoleCommand.obj"
	-@erase "$(INTDIR)\Container.obj"
	-@erase "$(INTDIR)\DialogBox.obj"
	-@erase "$(INTDIR)\Display.obj"
	-@erase "$(INTDIR)\DropDownList.obj"
	-@erase "$(INTDIR)\Font.obj"
	-@erase "$(INTDIR)\GameMath.obj"
	-@erase "$(INTDIR)\GameScheduler.obj"
	-@erase "$(INTDIR)\HighlightButton.obj"
	-@erase "$(INTDIR)\HSlider.obj"
	-@erase "$(INTDIR)\IniBasedDialog.obj"
	-@erase "$(INTDIR)\Keyboard.obj"
	-@erase "$(INTDIR)\Label.obj"
	-@erase "$(INTDIR)\List.obj"
	-@erase "$(INTDIR)\Motion.obj"
	-@erase "$(INTDIR)\MouseMotion.obj"
	-@erase "$(INTDIR)\Music.obj"
	-@erase "$(INTDIR)\OpenGLDisplay.obj"
	-@erase "$(INTDIR)\ParticleSystem.obj"
	-@erase "$(INTDIR)\ProgressBar.obj"
	-@erase "$(INTDIR)\SDLDisplay.obj"
	-@erase "$(INTDIR)\SharedRotateSkin.obj"
	-@erase "$(INTDIR)\SharedSkin.obj"
	-@erase "$(INTDIR)\Skin.obj"
	-@erase "$(INTDIR)\SkinCanvas.obj"
	-@erase "$(INTDIR)\SoundEffect.obj"
	-@erase "$(INTDIR)\SoundMixer.obj"
	-@erase "$(INTDIR)\StraitLineMotion.obj"
	-@erase "$(INTDIR)\tests.obj"
	-@erase "$(INTDIR)\TextArea.obj"
	-@erase "$(INTDIR)\TextBox.obj"
	-@erase "$(INTDIR)\Thing.obj"
	-@erase "$(INTDIR)\ThingCollection.obj"
	-@erase "$(INTDIR)\ToggleButton.obj"
	-@erase "$(INTDIR)\UISystem.obj"
	-@erase "$(INTDIR)\UIThing.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VScrollBar.obj"
	-@erase "$(INTDIR)\Wizard.obj"
	-@erase "$(INTDIR)\World.obj"
	-@erase "$(INTDIR)\WorldCanvas.obj"
	-@erase "$(OUTDIR)\Gamelib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /Gm /Zi /Od /I "..\gamelib" /I "..\SDL_gfx-2.0.3" /I "..\glSDL" /D "_DEBUG" /D "_LIB" /D "HAVE_OPENGL" /D "WIN32" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Gamelib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\Gamelib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Font.obj" \
	"$(INTDIR)\UIThing.obj" \
	"$(INTDIR)\Keyboard.obj" \
	"$(INTDIR)\Button.obj" \
	"$(INTDIR)\Canvas.obj" \
	"$(INTDIR)\DropDownList.obj" \
	"$(INTDIR)\HighlightButton.obj" \
	"$(INTDIR)\HSlider.obj" \
	"$(INTDIR)\Label.obj" \
	"$(INTDIR)\List.obj" \
	"$(INTDIR)\ProgressBar.obj" \
	"$(INTDIR)\SkinCanvas.obj" \
	"$(INTDIR)\TextArea.obj" \
	"$(INTDIR)\TextBox.obj" \
	"$(INTDIR)\ToggleButton.obj" \
	"$(INTDIR)\VScrollBar.obj" \
	"$(INTDIR)\WorldCanvas.obj" \
	"$(INTDIR)\Console.obj" \
	"$(INTDIR)\Container.obj" \
	"$(INTDIR)\DialogBox.obj" \
	"$(INTDIR)\IniBasedDialog.obj" \
	"$(INTDIR)\UISystem.obj" \
	"$(INTDIR)\Wizard.obj" \
	"$(INTDIR)\ConsoleCommand.obj" \
	"$(INTDIR)\tests.obj" \
	"$(INTDIR)\BR_Game.obj" \
	"$(INTDIR)\CollisionBitMask.obj" \
	"$(INTDIR)\SharedRotateSkin.obj" \
	"$(INTDIR)\SharedSkin.obj" \
	"$(INTDIR)\Skin.obj" \
	"$(INTDIR)\Display.obj" \
	"$(INTDIR)\OpenGLDisplay.obj" \
	"$(INTDIR)\SDLDisplay.obj" \
	"$(INTDIR)\Collision.obj" \
	"$(INTDIR)\Motion.obj" \
	"$(INTDIR)\MouseMotion.obj" \
	"$(INTDIR)\StraitLineMotion.obj" \
	"$(INTDIR)\Thing.obj" \
	"$(INTDIR)\ThingCollection.obj" \
	"$(INTDIR)\World.obj" \
	"$(INTDIR)\Music.obj" \
	"$(INTDIR)\SoundEffect.obj" \
	"$(INTDIR)\SoundMixer.obj" \
	"$(INTDIR)\2dVector.obj" \
	"$(INTDIR)\GameMath.obj" \
	"$(INTDIR)\ParticleSystem.obj" \
	"$(INTDIR)\AssetManager.obj" \
	"$(INTDIR)\GameScheduler.obj" \
	"..\SDL_Dump\lib\SDL.lib" \
	"..\SDL_Dump\lib\SDL_image.lib" \
	"..\SDL_Dump\lib\SDL_mixer.lib" \
	"..\SDL_Dump\lib\SDLmain.lib" \
	"..\SDL_Dump\lib\SDL_gfx.lib" \
	"..\SDL_Dump\lib\SFont.lib" \
	"..\..\Program Files\Microsoft Visual Studio\VC98\Lib\GLU32.LIB" \
	"..\..\Program Files\Microsoft Visual Studio\VC98\Lib\OPENGL32.LIB" \
	"..\..\Program Files\Microsoft Visual Studio\VC98\Lib\WINMM.LIB" \
	"..\..\Program Files\Microsoft Visual Studio\VC98\Lib\GLAUX.LIB" \
	"..\BertsToolBox\Debug\BertsToolBoxLib.lib"

"$(OUTDIR)\Gamelib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Gamelib.dep")
!INCLUDE "Gamelib.dep"
!ELSE 
!MESSAGE Warning: cannot find "Gamelib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Gamelib - Win32 Release" || "$(CFG)" == "Gamelib - Win32 Debug"
SOURCE=.\UI\Font.cpp

"$(INTDIR)\Font.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\UI\UIThing.cpp

"$(INTDIR)\UIThing.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Event\Keyboard.cpp

"$(INTDIR)\Keyboard.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\UI\Button.cpp

"$(INTDIR)\Button.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\UI\Canvas.cpp

"$(INTDIR)\Canvas.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\UI\DropDownList.cpp

"$(INTDIR)\DropDownList.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\UI\HighlightButton.cpp

"$(INTDIR)\HighlightButton.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\UI\HSlider.cpp

"$(INTDIR)\HSlider.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\UI\Label.cpp

"$(INTDIR)\Label.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\UI\List.cpp

"$(INTDIR)\List.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\UI\ProgressBar.cpp

"$(INTDIR)\ProgressBar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\UI\SkinCanvas.cpp

"$(INTDIR)\SkinCanvas.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\UI\TextArea.cpp

"$(INTDIR)\TextArea.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\UI\TextBox.cpp

"$(INTDIR)\TextBox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\UI\ToggleButton.cpp

"$(INTDIR)\ToggleButton.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\UI\VScrollBar.cpp

"$(INTDIR)\VScrollBar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\UI\WorldCanvas.cpp

"$(INTDIR)\WorldCanvas.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\UI\Console.cpp

"$(INTDIR)\Console.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\UI\Container.cpp

"$(INTDIR)\Container.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\UI\DialogBox.cpp

"$(INTDIR)\DialogBox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\UI\IniBasedDialog.cpp

"$(INTDIR)\IniBasedDialog.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\UI\UISystem.cpp

"$(INTDIR)\UISystem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\UI\Wizard.cpp

"$(INTDIR)\Wizard.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\UI\ConsoleCommand.cpp

"$(INTDIR)\ConsoleCommand.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\tests.cpp

"$(INTDIR)\tests.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\BR_Game.cpp

!IF  "$(CFG)" == "Gamelib - Win32 Release"

CPP_SWITCHES=/nologo /MD /W4 /Ob1 /I "..\gamelib" /I "..\SDL_gfx-2.0.3" /I "..\glSDL" /D "NDEBUG" /D "_LIB" /D "HAVE_OPENGL" /D "WIN32" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\BR_Game.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Gamelib - Win32 Debug"

CPP_SWITCHES=/nologo /MD /Gm /GX- /Zi /Od /I "..\gamelib" /I "..\SDL_gfx-2.0.3" /I "..\glSDL" /D "_DEBUG" /D "_LIB" /D "HAVE_OPENGL" /D "WIN32" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\BR_Game.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Graphics\RotateSkin.cpp
SOURCE=.\Graphics\CollisionBitMask.cpp

"$(INTDIR)\CollisionBitMask.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Graphics\SharedRotateSkin.cpp

"$(INTDIR)\SharedRotateSkin.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Graphics\SharedSkin.cpp

"$(INTDIR)\SharedSkin.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Graphics\Skin.cpp

"$(INTDIR)\Skin.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Graphics\Display.cpp

"$(INTDIR)\Display.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Graphics\OpenGLDisplay.cpp

"$(INTDIR)\OpenGLDisplay.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Graphics\SDLDisplay.cpp

"$(INTDIR)\SDLDisplay.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Game\Collision.cpp

"$(INTDIR)\Collision.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Game\Motion.cpp

"$(INTDIR)\Motion.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Game\MouseMotion.cpp

"$(INTDIR)\MouseMotion.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Game\StraitLineMotion.cpp

"$(INTDIR)\StraitLineMotion.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Game\Thing.cpp

"$(INTDIR)\Thing.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Game\ThingCollection.cpp

"$(INTDIR)\ThingCollection.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Game\World.cpp

"$(INTDIR)\World.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Audio\Music.cpp

"$(INTDIR)\Music.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Audio\SoundEffect.cpp

"$(INTDIR)\SoundEffect.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Audio\SoundMixer.cpp

"$(INTDIR)\SoundMixer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Misc\2dVector.cpp

"$(INTDIR)\2dVector.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Misc\GameMath.cpp

"$(INTDIR)\GameMath.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Misc\ParticleSystem.cpp

"$(INTDIR)\ParticleSystem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "Gamelib - Win32 Release"

"BertsToolBoxLib - Win32 Release" : 
   cd "\projects\BertsToolBox"
   $(MAKE) /$(MAKEFLAGS) /F .\BertsToolBoxLib.mak CFG="BertsToolBoxLib - Win32 Release" 
   cd "..\GAMELIB"

"BertsToolBoxLib - Win32 ReleaseCLEAN" : 
   cd "\projects\BertsToolBox"
   $(MAKE) /$(MAKEFLAGS) /F .\BertsToolBoxLib.mak CFG="BertsToolBoxLib - Win32 Release" RECURSE=1 CLEAN 
   cd "..\GAMELIB"

!ELSEIF  "$(CFG)" == "Gamelib - Win32 Debug"

"BertsToolBoxLib - Win32 Debug" : 
   cd "\projects\BertsToolBox"
   $(MAKE) /$(MAKEFLAGS) /F .\BertsToolBoxLib.mak CFG="BertsToolBoxLib - Win32 Debug" 
   cd "..\GAMELIB"

"BertsToolBoxLib - Win32 DebugCLEAN" : 
   cd "\projects\BertsToolBox"
   $(MAKE) /$(MAKEFLAGS) /F .\BertsToolBoxLib.mak CFG="BertsToolBoxLib - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\GAMELIB"

!ENDIF 

SOURCE=.\Misc\AssetManager.cpp

"$(INTDIR)\AssetManager.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Tasking\GameScheduler.cpp

!IF  "$(CFG)" == "Gamelib - Win32 Release"

CPP_SWITCHES=/nologo /MD /W4 /Ob1 /I "..\gamelib" /I "..\SDL_gfx-2.0.3" /I "..\glSDL" /D "NDEBUG" /D "_LIB" /D "HAVE_OPENGL" /D "WIN32" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\GameScheduler.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Gamelib - Win32 Debug"

CPP_SWITCHES=/nologo /MD /Gm /GX- /Zi /Od /I "..\gamelib" /I "..\SDL_gfx-2.0.3" /I "..\glSDL" /D "_DEBUG" /D "_LIB" /D "HAVE_OPENGL" /D "WIN32" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\GameScheduler.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

