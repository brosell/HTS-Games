# Microsoft Developer Studio Generated NMAKE File, Based on colorcubes.dsp
!IF "$(CFG)" == ""
CFG=colorcubes - Win32 Debug
!MESSAGE No configuration specified. Defaulting to colorcubes - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "colorcubes - Win32 Release" && "$(CFG)" != "colorcubes - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "colorcubes - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\BarrelDrop.exe"

!ELSE 

ALL : "Gamelib - Win32 Release" "BertsToolBoxLib - Win32 Release" "$(OUTDIR)\BarrelDrop.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"BertsToolBoxLib - Win32 ReleaseCLEAN" "Gamelib - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\Block.obj"
	-@erase "$(INTDIR)\Board.obj"
	-@erase "$(INTDIR)\BusyDialog.obj"
	-@erase "$(INTDIR)\FireworksDialog.obj"
	-@erase "$(INTDIR)\GameModeDialog.obj"
	-@erase "$(INTDIR)\GameUI.obj"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\HighScores.obj"
	-@erase "$(INTDIR)\Listeners.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\NextShapeCanvas.obj"
	-@erase "$(INTDIR)\OptionsDialog.obj"
	-@erase "$(INTDIR)\ParticleTraits.obj"
	-@erase "$(INTDIR)\Score.obj"
	-@erase "$(INTDIR)\Shape.obj"
	-@erase "$(INTDIR)\SpecialTextCanvas.obj"
	-@erase "$(INTDIR)\SplashScreen.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\BarrelDrop.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\colorcubes.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\colorcubes.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\BarrelDrop.pdb" /machine:I386 /out:"$(OUTDIR)\BarrelDrop.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Block.obj" \
	"$(INTDIR)\Board.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\HighScores.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\ParticleTraits.obj" \
	"$(INTDIR)\Score.obj" \
	"$(INTDIR)\Shape.obj" \
	"$(INTDIR)\BusyDialog.obj" \
	"$(INTDIR)\FireworksDialog.obj" \
	"$(INTDIR)\GameModeDialog.obj" \
	"$(INTDIR)\GameUI.obj" \
	"$(INTDIR)\Listeners.obj" \
	"$(INTDIR)\NextShapeCanvas.obj" \
	"$(INTDIR)\OptionsDialog.obj" \
	"$(INTDIR)\SpecialTextCanvas.obj" \
	"$(INTDIR)\SplashScreen.obj" \
	"..\BertsToolBox\Release\BertsToolBoxLib.lib" \
	"..\GAMELIB\Release\Gamelib.lib"

"$(OUTDIR)\BarrelDrop.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "colorcubes - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\BarrelDrop.exe"

!ELSE 

ALL : "Gamelib - Win32 Debug" "BertsToolBoxLib - Win32 Debug" "$(OUTDIR)\BarrelDrop.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"BertsToolBoxLib - Win32 DebugCLEAN" "Gamelib - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\Block.obj"
	-@erase "$(INTDIR)\Board.obj"
	-@erase "$(INTDIR)\BusyDialog.obj"
	-@erase "$(INTDIR)\FireworksDialog.obj"
	-@erase "$(INTDIR)\GameModeDialog.obj"
	-@erase "$(INTDIR)\GameUI.obj"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\HighScores.obj"
	-@erase "$(INTDIR)\Listeners.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\NextShapeCanvas.obj"
	-@erase "$(INTDIR)\OptionsDialog.obj"
	-@erase "$(INTDIR)\ParticleTraits.obj"
	-@erase "$(INTDIR)\Score.obj"
	-@erase "$(INTDIR)\Shape.obj"
	-@erase "$(INTDIR)\SpecialTextCanvas.obj"
	-@erase "$(INTDIR)\SplashScreen.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\BarrelDrop.exe"
	-@erase "$(OUTDIR)\BarrelDrop.ilk"
	-@erase "$(OUTDIR)\BarrelDrop.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\colorcubes.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\colorcubes.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\BarrelDrop.pdb" /debug /machine:I386 /out:"$(OUTDIR)\BarrelDrop.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Block.obj" \
	"$(INTDIR)\Board.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\HighScores.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\ParticleTraits.obj" \
	"$(INTDIR)\Score.obj" \
	"$(INTDIR)\Shape.obj" \
	"$(INTDIR)\BusyDialog.obj" \
	"$(INTDIR)\FireworksDialog.obj" \
	"$(INTDIR)\GameModeDialog.obj" \
	"$(INTDIR)\GameUI.obj" \
	"$(INTDIR)\Listeners.obj" \
	"$(INTDIR)\NextShapeCanvas.obj" \
	"$(INTDIR)\OptionsDialog.obj" \
	"$(INTDIR)\SpecialTextCanvas.obj" \
	"$(INTDIR)\SplashScreen.obj" \
	"..\BertsToolBox\Debug\BertsToolBoxLib.lib" \
	"..\GAMELIB\Debug\Gamelib.lib"

"$(OUTDIR)\BarrelDrop.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
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
!IF EXISTS("colorcubes.dep")
!INCLUDE "colorcubes.dep"
!ELSE 
!MESSAGE Warning: cannot find "colorcubes.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "colorcubes - Win32 Release" || "$(CFG)" == "colorcubes - Win32 Debug"
SOURCE=.\Block.cpp

"$(INTDIR)\Block.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Board.cpp

"$(INTDIR)\Board.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Globals.cpp

"$(INTDIR)\Globals.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\HighScores.cpp

"$(INTDIR)\HighScores.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\main.cpp

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ParticleTraits.cpp

"$(INTDIR)\ParticleTraits.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Score.cpp

"$(INTDIR)\Score.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Shape.cpp

"$(INTDIR)\Shape.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\BusyDialog.cpp

"$(INTDIR)\BusyDialog.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\FireworksDialog.cpp

"$(INTDIR)\FireworksDialog.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\GameModeDialog.cpp

"$(INTDIR)\GameModeDialog.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\GameUI.cpp

"$(INTDIR)\GameUI.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Listeners.cpp

"$(INTDIR)\Listeners.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\NextShapeCanvas.cpp

"$(INTDIR)\NextShapeCanvas.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\OptionsDialog.cpp

"$(INTDIR)\OptionsDialog.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SpecialTextCanvas.cpp

"$(INTDIR)\SpecialTextCanvas.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SplashScreen.cpp

"$(INTDIR)\SplashScreen.obj" : $(SOURCE) "$(INTDIR)"


!IF  "$(CFG)" == "colorcubes - Win32 Release"

"BertsToolBoxLib - Win32 Release" : 
   cd "\projects\BertsToolBox"
   $(MAKE) /$(MAKEFLAGS) /F .\BertsToolBoxLib.mak CFG="BertsToolBoxLib - Win32 Release" 
   cd "..\BarrelDrop"

"BertsToolBoxLib - Win32 ReleaseCLEAN" : 
   cd "\projects\BertsToolBox"
   $(MAKE) /$(MAKEFLAGS) /F .\BertsToolBoxLib.mak CFG="BertsToolBoxLib - Win32 Release" RECURSE=1 CLEAN 
   cd "..\BarrelDrop"

!ELSEIF  "$(CFG)" == "colorcubes - Win32 Debug"

"BertsToolBoxLib - Win32 Debug" : 
   cd "\projects\BertsToolBox"
   $(MAKE) /$(MAKEFLAGS) /F .\BertsToolBoxLib.mak CFG="BertsToolBoxLib - Win32 Debug" 
   cd "..\BarrelDrop"

"BertsToolBoxLib - Win32 DebugCLEAN" : 
   cd "\projects\BertsToolBox"
   $(MAKE) /$(MAKEFLAGS) /F .\BertsToolBoxLib.mak CFG="BertsToolBoxLib - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\BarrelDrop"

!ENDIF 

!IF  "$(CFG)" == "colorcubes - Win32 Release"

"Gamelib - Win32 Release" : 
   cd "\projects\GAMELIB"
   $(MAKE) /$(MAKEFLAGS) /F .\Gamelib.mak CFG="Gamelib - Win32 Release" 
   cd "..\BarrelDrop"

"Gamelib - Win32 ReleaseCLEAN" : 
   cd "\projects\GAMELIB"
   $(MAKE) /$(MAKEFLAGS) /F .\Gamelib.mak CFG="Gamelib - Win32 Release" RECURSE=1 CLEAN 
   cd "..\BarrelDrop"

!ELSEIF  "$(CFG)" == "colorcubes - Win32 Debug"

"Gamelib - Win32 Debug" : 
   cd "\projects\GAMELIB"
   $(MAKE) /$(MAKEFLAGS) /F .\Gamelib.mak CFG="Gamelib - Win32 Debug" 
   cd "..\BarrelDrop"

"Gamelib - Win32 DebugCLEAN" : 
   cd "\projects\GAMELIB"
   $(MAKE) /$(MAKEFLAGS) /F .\Gamelib.mak CFG="Gamelib - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\BarrelDrop"

!ENDIF 


!ENDIF 

