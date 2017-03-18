# Microsoft Developer Studio Generated NMAKE File, Based on IGMapper.dsp
!IF "$(CFG)" == ""
CFG=IGMapper - Win32 Debug
!MESSAGE No configuration specified. Defaulting to IGMapper - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "IGMapper - Win32 Release" && "$(CFG)" != "IGMapper - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IGMapper.mak" CFG="IGMapper - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IGMapper - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "IGMapper - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "IGMapper - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\IGMapper.exe"

!ELSE 

ALL : "GameLib_2 - Win32 Release" "BertsToolBoxLib - Win32 Release" "$(OUTDIR)\IGMapper.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"BertsToolBoxLib - Win32 ReleaseCLEAN" "GameLib_2 - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\CullFaces.obj"
	-@erase "$(INTDIR)\Entity.obj"
	-@erase "$(INTDIR)\Face.obj"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\IGMapper.obj"
	-@erase "$(INTDIR)\IGMapperChooseTileDlg.obj"
	-@erase "$(INTDIR)\IGMapperEntiry.obj"
	-@erase "$(INTDIR)\IGMapperGlobals.obj"
	-@erase "$(INTDIR)\IGMapperListeners.obj"
	-@erase "$(INTDIR)\IGMapperTile.obj"
	-@erase "$(INTDIR)\PropertiesDialog.obj"
	-@erase "$(INTDIR)\Tile.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\IGMapper.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /O2 /I "C:\PROJECTS\BERTSTOOLBOX" /I "c:\projects\gamelib_2\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\IGMapper.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\IGMapper.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\IGMapper.pdb" /machine:I386 /out:"$(OUTDIR)\IGMapper.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CullFaces.obj" \
	"$(INTDIR)\Entity.obj" \
	"$(INTDIR)\Face.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\IGMapper.obj" \
	"$(INTDIR)\IGMapperChooseTileDlg.obj" \
	"$(INTDIR)\IGMapperEntiry.obj" \
	"$(INTDIR)\IGMapperGlobals.obj" \
	"$(INTDIR)\IGMapperListeners.obj" \
	"$(INTDIR)\IGMapperTile.obj" \
	"$(INTDIR)\PropertiesDialog.obj" \
	"$(INTDIR)\Tile.obj" \
	"..\BertsToolBox\Release\BertsToolBoxLib.lib" \
	"..\GAMELIB_2\Release\GameLib_2.lib"

"$(OUTDIR)\IGMapper.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "IGMapper - Win32 Debug"

OUTDIR=.\IGMapper___Win32_Debug
INTDIR=.\IGMapper___Win32_Debug
# Begin Custom Macros
OutDir=.\IGMapper___Win32_Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\IGMapper.exe"

!ELSE 

ALL : "GameLib_2 - Win32 Debug" "BertsToolBoxLib - Win32 Debug" "$(OUTDIR)\IGMapper.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"BertsToolBoxLib - Win32 DebugCLEAN" "GameLib_2 - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\CullFaces.obj"
	-@erase "$(INTDIR)\Entity.obj"
	-@erase "$(INTDIR)\Face.obj"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\IGMapper.obj"
	-@erase "$(INTDIR)\IGMapperChooseTileDlg.obj"
	-@erase "$(INTDIR)\IGMapperEntiry.obj"
	-@erase "$(INTDIR)\IGMapperGlobals.obj"
	-@erase "$(INTDIR)\IGMapperListeners.obj"
	-@erase "$(INTDIR)\IGMapperTile.obj"
	-@erase "$(INTDIR)\PropertiesDialog.obj"
	-@erase "$(INTDIR)\Tile.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\IGMapper.exe"
	-@erase "$(OUTDIR)\IGMapper.ilk"
	-@erase "$(OUTDIR)\IGMapper.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /Zi /Od /Ob1 /I "C:\PROJECTS\BERTSTOOLBOX" /I "c:\projects\gamelib_2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\IGMapper.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\IGMapper.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\IGMapper.pdb" /debug /machine:I386 /out:"$(OUTDIR)\IGMapper.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\CullFaces.obj" \
	"$(INTDIR)\Entity.obj" \
	"$(INTDIR)\Face.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\IGMapper.obj" \
	"$(INTDIR)\IGMapperChooseTileDlg.obj" \
	"$(INTDIR)\IGMapperEntiry.obj" \
	"$(INTDIR)\IGMapperGlobals.obj" \
	"$(INTDIR)\IGMapperListeners.obj" \
	"$(INTDIR)\IGMapperTile.obj" \
	"$(INTDIR)\PropertiesDialog.obj" \
	"$(INTDIR)\Tile.obj" \
	"..\BertsToolBox\Debug\BertsToolBoxLib.lib" \
	"..\GAMELIB_2\Debug\GameLib_2.lib"

"$(OUTDIR)\IGMapper.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("IGMapper.dep")
!INCLUDE "IGMapper.dep"
!ELSE 
!MESSAGE Warning: cannot find "IGMapper.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "IGMapper - Win32 Release" || "$(CFG)" == "IGMapper - Win32 Debug"
SOURCE=.\CullFaces.cpp

"$(INTDIR)\CullFaces.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Entity.cpp

"$(INTDIR)\Entity.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Face.cpp

"$(INTDIR)\Face.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Globals.cpp

"$(INTDIR)\Globals.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\IGMapper.cpp

"$(INTDIR)\IGMapper.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\IGMapperChooseTileDlg.cpp

"$(INTDIR)\IGMapperChooseTileDlg.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\IGMapperEntiry.cpp

"$(INTDIR)\IGMapperEntiry.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\IGMapperGlobals.cpp

"$(INTDIR)\IGMapperGlobals.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\IGMapperListeners.cpp

"$(INTDIR)\IGMapperListeners.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\IGMapperTile.cpp

"$(INTDIR)\IGMapperTile.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PropertiesDialog.cpp

"$(INTDIR)\PropertiesDialog.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Tile.cpp

"$(INTDIR)\Tile.obj" : $(SOURCE) "$(INTDIR)"


!IF  "$(CFG)" == "IGMapper - Win32 Release"

"BertsToolBoxLib - Win32 Release" : 
   cd "\projects\BertsToolBox"
   $(MAKE) /$(MAKEFLAGS) /F .\BertsToolBoxLib.mak CFG="BertsToolBoxLib - Win32 Release" 
   cd "..\IndustrialGolf"

"BertsToolBoxLib - Win32 ReleaseCLEAN" : 
   cd "\projects\BertsToolBox"
   $(MAKE) /$(MAKEFLAGS) /F .\BertsToolBoxLib.mak CFG="BertsToolBoxLib - Win32 Release" RECURSE=1 CLEAN 
   cd "..\IndustrialGolf"

!ELSEIF  "$(CFG)" == "IGMapper - Win32 Debug"

"BertsToolBoxLib - Win32 Debug" : 
   cd "\projects\BertsToolBox"
   $(MAKE) /$(MAKEFLAGS) /F .\BertsToolBoxLib.mak CFG="BertsToolBoxLib - Win32 Debug" 
   cd "..\IndustrialGolf"

"BertsToolBoxLib - Win32 DebugCLEAN" : 
   cd "\projects\BertsToolBox"
   $(MAKE) /$(MAKEFLAGS) /F .\BertsToolBoxLib.mak CFG="BertsToolBoxLib - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\IndustrialGolf"

!ENDIF 

!IF  "$(CFG)" == "IGMapper - Win32 Release"

"GameLib_2 - Win32 Release" : 
   cd "\projects\GAMELIB_2"
   $(MAKE) /$(MAKEFLAGS) /F .\GameLib_2.mak CFG="GameLib_2 - Win32 Release" 
   cd "..\IndustrialGolf"

"GameLib_2 - Win32 ReleaseCLEAN" : 
   cd "\projects\GAMELIB_2"
   $(MAKE) /$(MAKEFLAGS) /F .\GameLib_2.mak CFG="GameLib_2 - Win32 Release" RECURSE=1 CLEAN 
   cd "..\IndustrialGolf"

!ELSEIF  "$(CFG)" == "IGMapper - Win32 Debug"

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

