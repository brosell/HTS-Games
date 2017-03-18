# Microsoft Developer Studio Generated NMAKE File, Based on GameLib_2.dsp
!IF "$(CFG)" == ""
CFG=GameLib_2 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to GameLib_2 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "GameLib_2 - Win32 Release" && "$(CFG)" != "GameLib_2 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GameLib_2.mak" CFG="GameLib_2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GameLib_2 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "GameLib_2 - Win32 Debug" (based on "Win32 (x86) Static Library")
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

!IF  "$(CFG)" == "GameLib_2 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\GameLib_2.lib"


CLEAN :
	-@erase "$(INTDIR)\2dVector.obj"
	-@erase "$(INTDIR)\AM.obj"
	-@erase "$(INTDIR)\AManager.obj"
	-@erase "$(INTDIR)\AssetManager.obj"
	-@erase "$(INTDIR)\BR_Game.obj"
	-@erase "$(INTDIR)\Button.obj"
	-@erase "$(INTDIR)\Canvas.obj"
	-@erase "$(INTDIR)\CollisionBitMask.obj"
	-@erase "$(INTDIR)\Console.obj"
	-@erase "$(INTDIR)\Container.obj"
	-@erase "$(INTDIR)\DialogBox.obj"
	-@erase "$(INTDIR)\Display.obj"
	-@erase "$(INTDIR)\dropdownlist.obj"
	-@erase "$(INTDIR)\Font.obj"
	-@erase "$(INTDIR)\FontLoader.obj"
	-@erase "$(INTDIR)\GameMath.obj"
	-@erase "$(INTDIR)\GameScheduler.obj"
	-@erase "$(INTDIR)\HighlightButton.obj"
	-@erase "$(INTDIR)\HSlider.obj"
	-@erase "$(INTDIR)\IniBasedDialog.obj"
	-@erase "$(INTDIR)\Keyboard.obj"
	-@erase "$(INTDIR)\Label.obj"
	-@erase "$(INTDIR)\LibrayTest.obj"
	-@erase "$(INTDIR)\List.obj"
	-@erase "$(INTDIR)\ListChooser.obj"
	-@erase "$(INTDIR)\MouseCursor.obj"
	-@erase "$(INTDIR)\Music.obj"
	-@erase "$(INTDIR)\OpenGLDisplay.obj"
	-@erase "$(INTDIR)\ParticleSystem.obj"
	-@erase "$(INTDIR)\ProgressBar.obj"
	-@erase "$(INTDIR)\PropertiesDialog.obj"
	-@erase "$(INTDIR)\pygame_alpha_blit.obj"
	-@erase "$(INTDIR)\RotateSkin.obj"
	-@erase "$(INTDIR)\RotateSkinLoader.obj"
	-@erase "$(INTDIR)\SDLDisplay.obj"
	-@erase "$(INTDIR)\SharedRotateSkin.obj"
	-@erase "$(INTDIR)\SharedSkin.obj"
	-@erase "$(INTDIR)\Skin.obj"
	-@erase "$(INTDIR)\SkinCanvas.obj"
	-@erase "$(INTDIR)\SkinLoader.obj"
	-@erase "$(INTDIR)\SoundEffect.obj"
	-@erase "$(INTDIR)\SoundEffectLoader.obj"
	-@erase "$(INTDIR)\SoundMixer.obj"
	-@erase "$(INTDIR)\TextArea.obj"
	-@erase "$(INTDIR)\TextBox.obj"
	-@erase "$(INTDIR)\Thing.obj"
	-@erase "$(INTDIR)\ToggleButton.obj"
	-@erase "$(INTDIR)\UISystem.obj"
	-@erase "$(INTDIR)\UIThing.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VScrollBar.obj"
	-@erase "$(INTDIR)\Wizard.obj"
	-@erase "$(INTDIR)\World.obj"
	-@erase "$(INTDIR)\WorldCanvas.obj"
	-@erase "$(OUTDIR)\GameLib_2.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GR /O2 /I "./include" /I "../include" /I "C:\PROJECTS\BERTSTOOLBOX" /D "NDEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /Fp"$(INTDIR)\GameLib_2.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\GameLib_2.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\GameLib_2.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Music.obj" \
	"$(INTDIR)\SoundEffect.obj" \
	"$(INTDIR)\SoundMixer.obj" \
	"$(INTDIR)\Keyboard.obj" \
	"$(INTDIR)\Thing.obj" \
	"$(INTDIR)\World.obj" \
	"$(INTDIR)\CollisionBitMask.obj" \
	"$(INTDIR)\Display.obj" \
	"$(INTDIR)\OpenGLDisplay.obj" \
	"$(INTDIR)\pygame_alpha_blit.obj" \
	"$(INTDIR)\RotateSkin.obj" \
	"$(INTDIR)\SDLDisplay.obj" \
	"$(INTDIR)\SharedRotateSkin.obj" \
	"$(INTDIR)\SharedSkin.obj" \
	"$(INTDIR)\Skin.obj" \
	"$(INTDIR)\FontLoader.obj" \
	"$(INTDIR)\RotateSkinLoader.obj" \
	"$(INTDIR)\SkinLoader.obj" \
	"$(INTDIR)\SoundEffectLoader.obj" \
	"$(INTDIR)\AM.obj" \
	"$(INTDIR)\AssetManager.obj" \
	"$(INTDIR)\2dVector.obj" \
	"$(INTDIR)\GameMath.obj" \
	"$(INTDIR)\Button.obj" \
	"$(INTDIR)\Canvas.obj" \
	"$(INTDIR)\dropdownlist.obj" \
	"$(INTDIR)\HighlightButton.obj" \
	"$(INTDIR)\HSlider.obj" \
	"$(INTDIR)\Label.obj" \
	"$(INTDIR)\List.obj" \
	"$(INTDIR)\ListChooser.obj" \
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
	"$(INTDIR)\PropertiesDialog.obj" \
	"$(INTDIR)\UISystem.obj" \
	"$(INTDIR)\Wizard.obj" \
	"$(INTDIR)\Font.obj" \
	"$(INTDIR)\MouseCursor.obj" \
	"$(INTDIR)\UIThing.obj" \
	"$(INTDIR)\ParticleSystem.obj" \
	"$(INTDIR)\BR_Game.obj" \
	"$(INTDIR)\AManager.obj" \
	"$(INTDIR)\GameScheduler.obj" \
	"$(INTDIR)\LibrayTest.obj" \
	"..\SDL_Dump\lib\SDLmain.lib" \
	"..\SDL_Dump\lib\SDL_gfx.lib" \
	"..\SDL_Dump\lib\SDL_image.lib" \
	"..\SDL_Dump\lib\SDL_mixer.lib" \
	"..\SDL_Dump\lib\SDL.lib" \
	"..\..\Program Files\Microsoft Visual Studio\VC98\Lib\OPENGL32.LIB" \
	"..\..\Program Files\Microsoft Visual Studio\VC98\Lib\GLU32.LIB" \
	"..\..\Program Files\Microsoft Visual Studio\VC98\Lib\GLAUX.LIB"

"$(OUTDIR)\GameLib_2.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "GameLib_2 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\GameLib_2.lib"


CLEAN :
	-@erase "$(INTDIR)\2dVector.obj"
	-@erase "$(INTDIR)\AM.obj"
	-@erase "$(INTDIR)\AManager.obj"
	-@erase "$(INTDIR)\AssetManager.obj"
	-@erase "$(INTDIR)\BR_Game.obj"
	-@erase "$(INTDIR)\Button.obj"
	-@erase "$(INTDIR)\Canvas.obj"
	-@erase "$(INTDIR)\CollisionBitMask.obj"
	-@erase "$(INTDIR)\Console.obj"
	-@erase "$(INTDIR)\Container.obj"
	-@erase "$(INTDIR)\DialogBox.obj"
	-@erase "$(INTDIR)\Display.obj"
	-@erase "$(INTDIR)\dropdownlist.obj"
	-@erase "$(INTDIR)\Font.obj"
	-@erase "$(INTDIR)\FontLoader.obj"
	-@erase "$(INTDIR)\GameMath.obj"
	-@erase "$(INTDIR)\GameScheduler.obj"
	-@erase "$(INTDIR)\HighlightButton.obj"
	-@erase "$(INTDIR)\HSlider.obj"
	-@erase "$(INTDIR)\IniBasedDialog.obj"
	-@erase "$(INTDIR)\Keyboard.obj"
	-@erase "$(INTDIR)\Label.obj"
	-@erase "$(INTDIR)\LibrayTest.obj"
	-@erase "$(INTDIR)\List.obj"
	-@erase "$(INTDIR)\ListChooser.obj"
	-@erase "$(INTDIR)\MouseCursor.obj"
	-@erase "$(INTDIR)\Music.obj"
	-@erase "$(INTDIR)\OpenGLDisplay.obj"
	-@erase "$(INTDIR)\ParticleSystem.obj"
	-@erase "$(INTDIR)\ProgressBar.obj"
	-@erase "$(INTDIR)\PropertiesDialog.obj"
	-@erase "$(INTDIR)\pygame_alpha_blit.obj"
	-@erase "$(INTDIR)\RotateSkin.obj"
	-@erase "$(INTDIR)\RotateSkinLoader.obj"
	-@erase "$(INTDIR)\SDLDisplay.obj"
	-@erase "$(INTDIR)\SharedRotateSkin.obj"
	-@erase "$(INTDIR)\SharedSkin.obj"
	-@erase "$(INTDIR)\Skin.obj"
	-@erase "$(INTDIR)\SkinCanvas.obj"
	-@erase "$(INTDIR)\SkinLoader.obj"
	-@erase "$(INTDIR)\SoundEffect.obj"
	-@erase "$(INTDIR)\SoundEffectLoader.obj"
	-@erase "$(INTDIR)\SoundMixer.obj"
	-@erase "$(INTDIR)\TextArea.obj"
	-@erase "$(INTDIR)\TextBox.obj"
	-@erase "$(INTDIR)\Thing.obj"
	-@erase "$(INTDIR)\ToggleButton.obj"
	-@erase "$(INTDIR)\UISystem.obj"
	-@erase "$(INTDIR)\UIThing.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VScrollBar.obj"
	-@erase "$(INTDIR)\Wizard.obj"
	-@erase "$(INTDIR)\World.obj"
	-@erase "$(INTDIR)\WorldCanvas.obj"
	-@erase "$(OUTDIR)\GameLib_2.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GR /Zi /Od /Ob1 /I "./include" /I "../include" /I "C:\PROJECTS\BERTSTOOLBOX" /D "_DEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /Fp"$(INTDIR)\GameLib_2.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\GameLib_2.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\GameLib_2.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Music.obj" \
	"$(INTDIR)\SoundEffect.obj" \
	"$(INTDIR)\SoundMixer.obj" \
	"$(INTDIR)\Keyboard.obj" \
	"$(INTDIR)\Thing.obj" \
	"$(INTDIR)\World.obj" \
	"$(INTDIR)\CollisionBitMask.obj" \
	"$(INTDIR)\Display.obj" \
	"$(INTDIR)\OpenGLDisplay.obj" \
	"$(INTDIR)\pygame_alpha_blit.obj" \
	"$(INTDIR)\RotateSkin.obj" \
	"$(INTDIR)\SDLDisplay.obj" \
	"$(INTDIR)\SharedRotateSkin.obj" \
	"$(INTDIR)\SharedSkin.obj" \
	"$(INTDIR)\Skin.obj" \
	"$(INTDIR)\FontLoader.obj" \
	"$(INTDIR)\RotateSkinLoader.obj" \
	"$(INTDIR)\SkinLoader.obj" \
	"$(INTDIR)\SoundEffectLoader.obj" \
	"$(INTDIR)\AM.obj" \
	"$(INTDIR)\AssetManager.obj" \
	"$(INTDIR)\2dVector.obj" \
	"$(INTDIR)\GameMath.obj" \
	"$(INTDIR)\Button.obj" \
	"$(INTDIR)\Canvas.obj" \
	"$(INTDIR)\dropdownlist.obj" \
	"$(INTDIR)\HighlightButton.obj" \
	"$(INTDIR)\HSlider.obj" \
	"$(INTDIR)\Label.obj" \
	"$(INTDIR)\List.obj" \
	"$(INTDIR)\ListChooser.obj" \
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
	"$(INTDIR)\PropertiesDialog.obj" \
	"$(INTDIR)\UISystem.obj" \
	"$(INTDIR)\Wizard.obj" \
	"$(INTDIR)\Font.obj" \
	"$(INTDIR)\MouseCursor.obj" \
	"$(INTDIR)\UIThing.obj" \
	"$(INTDIR)\ParticleSystem.obj" \
	"$(INTDIR)\BR_Game.obj" \
	"$(INTDIR)\AManager.obj" \
	"$(INTDIR)\GameScheduler.obj" \
	"$(INTDIR)\LibrayTest.obj" \
	"..\SDL_Dump\lib\SDLmain.lib" \
	"..\SDL_Dump\lib\SDL_gfx.lib" \
	"..\SDL_Dump\lib\SDL_image.lib" \
	"..\SDL_Dump\lib\SDL_mixer.lib" \
	"..\SDL_Dump\lib\SDL.lib" \
	"..\..\Program Files\Microsoft Visual Studio\VC98\Lib\OPENGL32.LIB" \
	"..\..\Program Files\Microsoft Visual Studio\VC98\Lib\GLU32.LIB" \
	"..\..\Program Files\Microsoft Visual Studio\VC98\Lib\GLAUX.LIB"

"$(OUTDIR)\GameLib_2.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
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
!IF EXISTS("GameLib_2.dep")
!INCLUDE "GameLib_2.dep"
!ELSE 
!MESSAGE Warning: cannot find "GameLib_2.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "GameLib_2 - Win32 Release" || "$(CFG)" == "GameLib_2 - Win32 Debug"
SOURCE=.\src\Audio\Music.cpp

"$(INTDIR)\Music.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Audio\SoundEffect.cpp

"$(INTDIR)\SoundEffect.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Audio\SoundMixer.cpp

"$(INTDIR)\SoundMixer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Event\Keyboard.cpp

"$(INTDIR)\Keyboard.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Game\Thing.cpp

"$(INTDIR)\Thing.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Game\World.cpp

"$(INTDIR)\World.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Graphics\CollisionBitMask.cpp

"$(INTDIR)\CollisionBitMask.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Graphics\Display.cpp

"$(INTDIR)\Display.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Graphics\OpenGLDisplay.cpp

"$(INTDIR)\OpenGLDisplay.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Graphics\pygame_alpha_blit.c

"$(INTDIR)\pygame_alpha_blit.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Graphics\RotateSkin.cpp

"$(INTDIR)\RotateSkin.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Graphics\SDLDisplay.cpp

"$(INTDIR)\SDLDisplay.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Graphics\SharedRotateSkin.cpp

"$(INTDIR)\SharedRotateSkin.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Graphics\SharedSkin.cpp

"$(INTDIR)\SharedSkin.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Graphics\Skin.cpp

"$(INTDIR)\Skin.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Asset\FontLoader.cpp

"$(INTDIR)\FontLoader.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Asset\RotateSkinLoader.cpp

"$(INTDIR)\RotateSkinLoader.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Asset\SkinLoader.cpp

"$(INTDIR)\SkinLoader.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Asset\SoundEffectLoader.cpp

"$(INTDIR)\SoundEffectLoader.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Asset\AM.cpp

"$(INTDIR)\AM.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Misc\AssetManager.cpp

"$(INTDIR)\AssetManager.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Misc\2dVector.cpp

"$(INTDIR)\2dVector.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Misc\GameMath.cpp

"$(INTDIR)\GameMath.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\Button.cpp

"$(INTDIR)\Button.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\Canvas.cpp

"$(INTDIR)\Canvas.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\dropdownlist.cpp

"$(INTDIR)\dropdownlist.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\HighlightButton.cpp

"$(INTDIR)\HighlightButton.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\HSlider.cpp

"$(INTDIR)\HSlider.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\Label.cpp

"$(INTDIR)\Label.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\List.cpp

"$(INTDIR)\List.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\ListChooser.cpp

"$(INTDIR)\ListChooser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\ProgressBar.cpp

"$(INTDIR)\ProgressBar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\SkinCanvas.cpp

"$(INTDIR)\SkinCanvas.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\TextArea.cpp

"$(INTDIR)\TextArea.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\TextBox.cpp

"$(INTDIR)\TextBox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\ToggleButton.cpp

"$(INTDIR)\ToggleButton.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\VScrollBar.cpp

"$(INTDIR)\VScrollBar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\WorldCanvas.cpp

"$(INTDIR)\WorldCanvas.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\Console.cpp

"$(INTDIR)\Console.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\Container.cpp

"$(INTDIR)\Container.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\DialogBox.cpp

"$(INTDIR)\DialogBox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\IniBasedDialog.cpp

"$(INTDIR)\IniBasedDialog.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\PropertiesDialog.cpp

"$(INTDIR)\PropertiesDialog.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\UISystem.cpp

"$(INTDIR)\UISystem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\Wizard.cpp

"$(INTDIR)\Wizard.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\Font.cpp

"$(INTDIR)\Font.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\MouseCursor.cpp

"$(INTDIR)\MouseCursor.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\UI\UIThing.cpp

"$(INTDIR)\UIThing.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Misc\ParticleSystem.cpp

"$(INTDIR)\ParticleSystem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Core\BR_Game.cpp

"$(INTDIR)\BR_Game.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Misc\AManager.cpp

"$(INTDIR)\AManager.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\GameScheduler.cpp

"$(INTDIR)\GameScheduler.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\UnitTests\LibrayTest.cpp

"$(INTDIR)\LibrayTest.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

