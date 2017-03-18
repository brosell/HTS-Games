# Microsoft Developer Studio Generated NMAKE File, Based on IndustrialGolf.dsp
!IF "$(CFG)" == ""
CFG=IndustrialGolf - Win32 Debug
!MESSAGE No configuration specified. Defaulting to IndustrialGolf - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "IndustrialGolf - Win32 Release" && "$(CFG)" != "IndustrialGolf - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "IndustrialGolf - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\IndustrialGolf.exe"

!ELSE 

ALL : "GameLib_2 - Win32 Release" "BertsToolBoxLib - Win32 Release" "$(OUTDIR)\IndustrialGolf.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"BertsToolBoxLib - Win32 ReleaseCLEAN" "GameLib_2 - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\Club.obj"
	-@erase "$(INTDIR)\Entity.obj"
	-@erase "$(INTDIR)\Face.obj"
	-@erase "$(INTDIR)\Game.obj"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\Goal.obj"
	-@erase "$(INTDIR)\GolfBall.obj"
	-@erase "$(INTDIR)\Level.obj"
	-@erase "$(INTDIR)\Listeners.obj"
	-@erase "$(INTDIR)\StartUp.obj"
	-@erase "$(INTDIR)\Tee.obj"
	-@erase "$(INTDIR)\Tile.obj"
	-@erase "$(INTDIR)\UI.obj"
	-@erase "$(INTDIR)\UpWind.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\IndustrialGolf.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /O2 /I "C:\PROJECTS\BERTSTOOLBOX" /I "c:\projects\gamelib_2\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\IndustrialGolf.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\IndustrialGolf.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\IndustrialGolf.pdb" /machine:I386 /out:"$(OUTDIR)\IndustrialGolf.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Face.obj" \
	"$(INTDIR)\Game.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\Level.obj" \
	"$(INTDIR)\Listeners.obj" \
	"$(INTDIR)\StartUp.obj" \
	"$(INTDIR)\Tile.obj" \
	"$(INTDIR)\Club.obj" \
	"$(INTDIR)\Entity.obj" \
	"$(INTDIR)\Goal.obj" \
	"$(INTDIR)\GolfBall.obj" \
	"$(INTDIR)\Tee.obj" \
	"$(INTDIR)\UpWind.obj" \
	"$(INTDIR)\UI.obj" \
	"..\BertsToolBox\Release\BertsToolBoxLib.lib" \
	"..\GAMELIB_2\Release\GameLib_2.lib"

"$(OUTDIR)\IndustrialGolf.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "IndustrialGolf - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\IndustrialGolf.exe"

!ELSE 

ALL : "GameLib_2 - Win32 Debug" "BertsToolBoxLib - Win32 Debug" "$(OUTDIR)\IndustrialGolf.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"BertsToolBoxLib - Win32 DebugCLEAN" "GameLib_2 - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\Club.obj"
	-@erase "$(INTDIR)\Entity.obj"
	-@erase "$(INTDIR)\Face.obj"
	-@erase "$(INTDIR)\Game.obj"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\Goal.obj"
	-@erase "$(INTDIR)\GolfBall.obj"
	-@erase "$(INTDIR)\Level.obj"
	-@erase "$(INTDIR)\Listeners.obj"
	-@erase "$(INTDIR)\StartUp.obj"
	-@erase "$(INTDIR)\Tee.obj"
	-@erase "$(INTDIR)\Tile.obj"
	-@erase "$(INTDIR)\UI.obj"
	-@erase "$(INTDIR)\UpWind.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\IndustrialGolf.exe"
	-@erase "$(OUTDIR)\IndustrialGolf.ilk"
	-@erase "$(OUTDIR)\IndustrialGolf.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /Zi /Od /Ob1 /I "C:\PROJECTS\BERTSTOOLBOX" /I "c:\projects\gamelib_2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\IndustrialGolf.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\IndustrialGolf.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\IndustrialGolf.pdb" /debug /machine:I386 /out:"$(OUTDIR)\IndustrialGolf.exe" /pdbtype:sept /verbose:lib 
LINK32_OBJS= \
	"$(INTDIR)\Face.obj" \
	"$(INTDIR)\Game.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\Level.obj" \
	"$(INTDIR)\Listeners.obj" \
	"$(INTDIR)\StartUp.obj" \
	"$(INTDIR)\Tile.obj" \
	"$(INTDIR)\Club.obj" \
	"$(INTDIR)\Entity.obj" \
	"$(INTDIR)\Goal.obj" \
	"$(INTDIR)\GolfBall.obj" \
	"$(INTDIR)\Tee.obj" \
	"$(INTDIR)\UpWind.obj" \
	"$(INTDIR)\UI.obj" \
	"..\BertsToolBox\Debug\BertsToolBoxLib.lib" \
	"..\GAMELIB_2\Debug\GameLib_2.lib"

"$(OUTDIR)\IndustrialGolf.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("IndustrialGolf.dep")
!INCLUDE "IndustrialGolf.dep"
!ELSE 
!MESSAGE Warning: cannot find "IndustrialGolf.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "IndustrialGolf - Win32 Release" || "$(CFG)" == "IndustrialGolf - Win32 Debug"
SOURCE=.\Face.cpp

"$(INTDIR)\Face.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Game.cpp

"$(INTDIR)\Game.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Globals.cpp

"$(INTDIR)\Globals.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Level.cpp

"$(INTDIR)\Level.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Listeners.cpp

"$(INTDIR)\Listeners.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\LoadLevel.cpp
SOURCE=.\StartUp.cpp

"$(INTDIR)\StartUp.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Tile.cpp

"$(INTDIR)\Tile.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Club.cpp

"$(INTDIR)\Club.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Entity.cpp

"$(INTDIR)\Entity.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Goal.cpp

"$(INTDIR)\Goal.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\GolfBall.cpp

"$(INTDIR)\GolfBall.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Tee.cpp

"$(INTDIR)\Tee.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\UpWind.cpp

"$(INTDIR)\UpWind.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\NewThing.cpp
SOURCE=.\UI.cpp

"$(INTDIR)\UI.obj" : $(SOURCE) "$(INTDIR)"


!IF  "$(CFG)" == "IndustrialGolf - Win32 Release"

"BertsToolBoxLib - Win32 Release" : 
   cd "\projects\BertsToolBox"
   $(MAKE) /$(MAKEFLAGS) /F .\BertsToolBoxLib.mak CFG="BertsToolBoxLib - Win32 Release" 
   cd "..\IndustrialGolf"

"BertsToolBoxLib - Win32 ReleaseCLEAN" : 
   cd "\projects\BertsToolBox"
   $(MAKE) /$(MAKEFLAGS) /F .\BertsToolBoxLib.mak CFG="BertsToolBoxLib - Win32 Release" RECURSE=1 CLEAN 
   cd "..\IndustrialGolf"

!ELSEIF  "$(CFG)" == "IndustrialGolf - Win32 Debug"

"BertsToolBoxLib - Win32 Debug" : 
   cd "\projects\BertsToolBox"
   $(MAKE) /$(MAKEFLAGS) /F .\BertsToolBoxLib.mak CFG="BertsToolBoxLib - Win32 Debug" 
   cd "..\IndustrialGolf"

"BertsToolBoxLib - Win32 DebugCLEAN" : 
   cd "\projects\BertsToolBox"
   $(MAKE) /$(MAKEFLAGS) /F .\BertsToolBoxLib.mak CFG="BertsToolBoxLib - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\IndustrialGolf"

!ENDIF 

!IF  "$(CFG)" == "IndustrialGolf - Win32 Release"

"GameLib_2 - Win32 Release" : 
   cd "\projects\GAMELIB_2"
   $(MAKE) /$(MAKEFLAGS) /F .\GameLib_2.mak CFG="GameLib_2 - Win32 Release" 
   cd "..\IndustrialGolf"

"GameLib_2 - Win32 ReleaseCLEAN" : 
   cd "\projects\GAMELIB_2"
   $(MAKE) /$(MAKEFLAGS) /F .\GameLib_2.mak CFG="GameLib_2 - Win32 Release" RECURSE=1 CLEAN 
   cd "..\IndustrialGolf"

!ELSEIF  "$(CFG)" == "IndustrialGolf - Win32 Debug"

"GameLib_2 - Win32 Debug" : 
   cd "\projects\GAMELIB_2"
   $(MAKE) /$(MAKEFLAGS) /F .\GameLib_2.mak CFG="GameLib_2 - Win32 Debug" 
   cd "..\IndustrialGolf"

"GameLib_2 - Win32 DebugCLEAN" : 
   cd "\projects\GAMELIB_2"
   $(MAKE) /$(MAKEFLAGS) /F .\GameLib_2.mak CFG="GameLib_2 - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\IndustrialGolf"

!ENDIF 


!ENDIF 

