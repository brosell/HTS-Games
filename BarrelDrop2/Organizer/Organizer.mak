# Microsoft Developer Studio Generated NMAKE File, Based on Organizer.dsp
!IF "$(CFG)" == ""
CFG=Organizer - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Organizer - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Organizer - Win32 Release" && "$(CFG)" != "Organizer - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Organizer.mak" CFG="Organizer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Organizer - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Organizer - Win32 Debug" (based on "Win32 (x86) Static Library")
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

!IF  "$(CFG)" == "Organizer - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : ".\l" ".\f" 

!ELSE 

ALL : "colorcubes - Win32 Release" ".\l" ".\f" 

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"colorcubes - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase 
	-@erase "f"
	-@erase "l"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\Organizer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Organizer.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\Organizer.lib" 
LIB32_OBJS= \
	

!ELSEIF  "$(CFG)" == "Organizer - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : ".\f" 

!ELSE 

ALL : "colorcubes - Win32 Debug" ".\f" 

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"colorcubes - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase 
	-@erase "f"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\Organizer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Organizer.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\Organizer.lib" 
LIB32_OBJS= \
	

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
!IF EXISTS("Organizer.dep")
!INCLUDE "Organizer.dep"
!ELSE 
!MESSAGE Warning: cannot find "Organizer.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Organizer - Win32 Release" || "$(CFG)" == "Organizer - Win32 Debug"
SOURCE=..\debugOrganize.bat

!IF  "$(CFG)" == "Organizer - Win32 Release"

!ELSEIF  "$(CFG)" == "Organizer - Win32 Debug"

InputPath=..\debugOrganize.bat
InputName=debugOrganize

".\f" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	cd .. 
	$(InputName) 
<< 
	

!ENDIF 

SOURCE=..\releaseOrganize.bat

!IF  "$(CFG)" == "Organizer - Win32 Release"

InputPath=..\releaseOrganize.bat
InputName=releaseOrganize

".\f" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	cd .. 
	$(InputName) 
<< 
	

!ELSEIF  "$(CFG)" == "Organizer - Win32 Debug"

!ENDIF 

SOURCE=..\Version.ini

!IF  "$(CFG)" == "Organizer - Win32 Release"

InputPath=..\Version.ini

".\l" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	c:\tools\versioner.exe -major=0 -minor=9 $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "Organizer - Win32 Debug"

!ENDIF 

!IF  "$(CFG)" == "Organizer - Win32 Release"

"colorcubes - Win32 Release" : 
   cd "\projects\BarrelDrop"
   $(MAKE) /$(MAKEFLAGS) /F .\colorcubes.mak CFG="colorcubes - Win32 Release" 
   cd ".\Organizer"

"colorcubes - Win32 ReleaseCLEAN" : 
   cd "\projects\BarrelDrop"
   $(MAKE) /$(MAKEFLAGS) /F .\colorcubes.mak CFG="colorcubes - Win32 Release" RECURSE=1 CLEAN 
   cd ".\Organizer"

!ELSEIF  "$(CFG)" == "Organizer - Win32 Debug"

"colorcubes - Win32 Debug" : 
   cd "\projects\BarrelDrop"
   $(MAKE) /$(MAKEFLAGS) /F .\colorcubes.mak CFG="colorcubes - Win32 Debug" 
   cd ".\Organizer"

"colorcubes - Win32 DebugCLEAN" : 
   cd "\projects\BarrelDrop"
   $(MAKE) /$(MAKEFLAGS) /F .\colorcubes.mak CFG="colorcubes - Win32 Debug" RECURSE=1 CLEAN 
   cd ".\Organizer"

!ENDIF 


!ENDIF 

