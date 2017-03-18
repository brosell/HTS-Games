
ifeq ($(TOOLSET),dmc)

	CCC = dmc.exe
	CC = dmc.exe
	
	INCLUDE_DIRS = "-Ic:\projects\SDL_dump\include;c:\projects\BertsToolBox;..;."

	CPPFLAGS = -c -Jm -w -w- -w6 -v0  -o-all $(INCLUDE_DIRS) -D_STLP_NO_OWN_IOSTREAMSxxx -DWIN32 -DNDEBUG -D_MBCS -D_LIB -o$(INTDIR)\ /c -mn  -WD 
	CFLAGS = -c -Jm -w -w- -w6 -v0  -o-all $(INCLUDE_DIRS) -D_STLP_NO_OWN_IOSTREAMSxxx -DWIN32 -DNDEBUG -D_MBCS -D_LIB -o$(INTDIR)\ /c -mn  -WD 
	
	LIB = lib.exe
	LINK = dmc.exe

	LIBS = "c:\projects\BertsToolBox\ToolBox.lib"
	
	LINK_LINE = $(LINK) /lib "-oGameLib.lib" $(cppobjs) $(cobjs) $(LIBS) -mn
else
ifeq ($(TOOLSET),vc)
	CCC = cl
	CC = cl
	
	INCLUDE_DIRS = "/I c:\projects\SDL_dump\include /I c:\projects\BertsToolBox; /I .. /I ."
	
	CPPFLAGS = /nologo /MD /W3 /Od /Ox /Ob1 $(INCLUDE_DIRS) /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB"  /c 
	CFLAGS = /nologo /MD /W3 /Od /Ob1 $(INCLUDE_DIRS) /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB"  /c 

	LINK_LINE = link.exe -lib "/out:GameLib.lib" $(cppobjs) $(cobjs) $(LIBS)
	Link = link
else
		
endif
endif

OUTFILE = -o$@
	
LIBS = "c:\projects\BertsToolBox\ToolBox.lib"
#wsock32.lib winmm.lib OLEAUT32.LIB

depricated = AutoBuffer.obj OutputIteratorAdaptors.obj

cppobjs = \
BR_Game.obj \
tests.obj \
Wizard.obj \
Audio/Music.obj \
Audio/SoundEffect.obj \
Audio/SoundMixer.obj \
Event/Keyboard.obj \
Game/Collision.obj \
Game/Motion.obj \
Game/MouseMotion.obj \
Game/StraitLineMotion.obj \
Game/Thing.obj \
Game/ThingCollection.obj \
Game/World.obj \
Graphics/CollisionBitMask.obj \
Graphics/Display.obj \
Graphics/OpenGLDisplay.obj \
Graphics/RotateSkin.obj \
Graphics/SDLDisplay.obj \
Graphics/SharedRotateSkin.obj \
Graphics/SharedSkin.obj \
Graphics/Skin.obj \
Misc/2dVector.obj \
Misc/AssetManager.obj \
Misc/GameMath.obj \
Misc/ParticleSystem.obj \
Tasking/GameScheduler.obj \
UI/Button.obj \
UI/Canvas.obj \
UI/Console.obj \
UI/ConsoleCommand.obj \
UI/Container.obj \
UI/DialogBox.obj \
UI/DropDownList.obj \
UI/Font.obj \
UI/HighlightButton.obj \
UI/HSlider.obj \
UI/IniBasedDialog.obj \
UI/Label.obj \
UI/List.obj \
UI/ProgressBar.obj \
UI/SkinCanvas.obj \
UI/TextArea.obj \
UI/TextBox.obj \
UI/ToggleButton.obj \
UI/UISystem.obj \
UI/UIThing.obj \
UI/VScrollBar.obj \
UI/Wizard.obj \
UI/WorldCanvas.obj 

GameLib.lib: $(cppobjs)
	$(LINK_LINE)

$(cppobjs): %.obj: %.cpp
	-$(CCC)  $(CPPFLAGS) $< $(OUTFILE)

