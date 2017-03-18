# Microsoft Developer Studio Generated NMAKE File, Based on BertsToolBoxLib.dsp
!IF "$(CFG)" == ""
CFG=BertsToolBoxLib - Win32 Debug
!MESSAGE No configuration specified. Defaulting to BertsToolBoxLib - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "BertsToolBoxLib - Win32 Release" && "$(CFG)" != "BertsToolBoxLib - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BertsToolBoxLib.mak" CFG="BertsToolBoxLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BertsToolBoxLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "BertsToolBoxLib - Win32 Debug" (based on "Win32 (x86) Static Library")
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

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\BertsToolBoxLib.lib" "$(OUTDIR)\BertsToolBoxLib.bsc"


CLEAN :
	-@erase "$(INTDIR)\AutoBuffer.obj"
	-@erase "$(INTDIR)\BSocket.obj"
	-@erase "$(INTDIR)\CommandLineParser.obj"
	-@erase "$(INTDIR)\Convert.obj"
	-@erase "$(INTDIR)\Coroutine.obj"
	-@erase "$(INTDIR)\FileManager.obj"
	-@erase "$(INTDIR)\FileUtils.obj"
	-@erase "$(INTDIR)\IniFile.obj"
	-@erase "$(INTDIR)\Link.obj"
	-@erase "$(INTDIR)\Log.obj"
	-@erase "$(INTDIR)\Message.obj"
	-@erase "$(INTDIR)\MessageCenter.obj"
	-@erase "$(INTDIR)\MessageTesters.obj"
	-@erase "$(INTDIR)\ObjectCache.obj"
	-@erase "$(INTDIR)\PackFunctions.obj"
	-@erase "$(INTDIR)\PakFile.obj"
	-@erase "$(INTDIR)\pcl.obj"
	-@erase "$(INTDIR)\pcl.sbr"
	-@erase "$(INTDIR)\SoftwareLink.obj"
	-@erase "$(INTDIR)\StateMachine.obj"
	-@erase "$(INTDIR)\StdString.obj"
	-@erase "$(INTDIR)\stlcompile.obj"
	-@erase "$(INTDIR)\STLFunctorDelegate.obj"
	-@erase "$(INTDIR)\StringTokenizer.obj"
	-@erase "$(INTDIR)\TCPLink.obj"
	-@erase "$(INTDIR)\TestSuite.obj"
	-@erase "$(INTDIR)\Thread.obj"
	-@erase "$(INTDIR)\ThreadSafeList.obj"
	-@erase "$(INTDIR)\Timer.obj"
	-@erase "$(INTDIR)\ToolBoxTests.obj"
	-@erase "$(INTDIR)\UnitTest.obj"
	-@erase "$(INTDIR)\Utils.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\BertsToolBoxLib.bsc"
	-@erase "$(OUTDIR)\BertsToolBoxLib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W4 /GR /O2 /I "C:\PROJECTS\BERTSTOOLBOX" /D "NDEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\BertsToolBoxLib.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\pcl.sbr"

"$(OUTDIR)\BertsToolBoxLib.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\BertsToolBoxLib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\BSocket.obj" \
	"$(INTDIR)\Link.obj" \
	"$(INTDIR)\Message.obj" \
	"$(INTDIR)\MessageCenter.obj" \
	"$(INTDIR)\MessageTesters.obj" \
	"$(INTDIR)\PackFunctions.obj" \
	"$(INTDIR)\SoftwareLink.obj" \
	"$(INTDIR)\TCPLink.obj" \
	"$(INTDIR)\AutoBuffer.obj" \
	"$(INTDIR)\CommandLineParser.obj" \
	"$(INTDIR)\ObjectCache.obj" \
	"$(INTDIR)\StdString.obj" \
	"$(INTDIR)\StringTokenizer.obj" \
	"$(INTDIR)\ThreadSafeList.obj" \
	"$(INTDIR)\Convert.obj" \
	"$(INTDIR)\Utils.obj" \
	"$(INTDIR)\StateMachine.obj" \
	"$(INTDIR)\Coroutine.obj" \
	"$(INTDIR)\pcl.obj" \
	"$(INTDIR)\Thread.obj" \
	"$(INTDIR)\Timer.obj" \
	"$(INTDIR)\FileManager.obj" \
	"$(INTDIR)\FileUtils.obj" \
	"$(INTDIR)\IniFile.obj" \
	"$(INTDIR)\Log.obj" \
	"$(INTDIR)\PakFile.obj" \
	"$(INTDIR)\TestSuite.obj" \
	"$(INTDIR)\stlcompile.obj" \
	"$(INTDIR)\STLFunctorDelegate.obj" \
	"$(INTDIR)\ToolBoxTests.obj" \
	"$(INTDIR)\UnitTest.obj" \
	"..\..\Program Files\Microsoft Visual Studio\VC98\Lib\WSOCK32.LIB" \
	"..\..\Program Files\Microsoft Visual Studio\VC98\Lib\WINMM.LIB"

"$(OUTDIR)\BertsToolBoxLib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\BertsToolBoxLib.lib"


CLEAN :
	-@erase "$(INTDIR)\AutoBuffer.obj"
	-@erase "$(INTDIR)\BSocket.obj"
	-@erase "$(INTDIR)\CommandLineParser.obj"
	-@erase "$(INTDIR)\Convert.obj"
	-@erase "$(INTDIR)\Coroutine.obj"
	-@erase "$(INTDIR)\FileManager.obj"
	-@erase "$(INTDIR)\FileUtils.obj"
	-@erase "$(INTDIR)\IniFile.obj"
	-@erase "$(INTDIR)\Link.obj"
	-@erase "$(INTDIR)\Log.obj"
	-@erase "$(INTDIR)\Message.obj"
	-@erase "$(INTDIR)\MessageCenter.obj"
	-@erase "$(INTDIR)\MessageTesters.obj"
	-@erase "$(INTDIR)\ObjectCache.obj"
	-@erase "$(INTDIR)\PackFunctions.obj"
	-@erase "$(INTDIR)\PakFile.obj"
	-@erase "$(INTDIR)\pcl.obj"
	-@erase "$(INTDIR)\SoftwareLink.obj"
	-@erase "$(INTDIR)\StateMachine.obj"
	-@erase "$(INTDIR)\StdString.obj"
	-@erase "$(INTDIR)\stlcompile.obj"
	-@erase "$(INTDIR)\STLFunctorDelegate.obj"
	-@erase "$(INTDIR)\StringTokenizer.obj"
	-@erase "$(INTDIR)\TCPLink.obj"
	-@erase "$(INTDIR)\TestSuite.obj"
	-@erase "$(INTDIR)\Thread.obj"
	-@erase "$(INTDIR)\ThreadSafeList.obj"
	-@erase "$(INTDIR)\Timer.obj"
	-@erase "$(INTDIR)\ToolBoxTests.obj"
	-@erase "$(INTDIR)\UnitTest.obj"
	-@erase "$(INTDIR)\Utils.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\BertsToolBoxLib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /Gm /GR /Zi /Od /Ob1 /I "C:\PROJECTS\BERTSTOOLBOX" /D "_DEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\BertsToolBoxLib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\BertsToolBoxLib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\BSocket.obj" \
	"$(INTDIR)\Link.obj" \
	"$(INTDIR)\Message.obj" \
	"$(INTDIR)\MessageCenter.obj" \
	"$(INTDIR)\MessageTesters.obj" \
	"$(INTDIR)\PackFunctions.obj" \
	"$(INTDIR)\SoftwareLink.obj" \
	"$(INTDIR)\TCPLink.obj" \
	"$(INTDIR)\AutoBuffer.obj" \
	"$(INTDIR)\CommandLineParser.obj" \
	"$(INTDIR)\ObjectCache.obj" \
	"$(INTDIR)\StdString.obj" \
	"$(INTDIR)\StringTokenizer.obj" \
	"$(INTDIR)\ThreadSafeList.obj" \
	"$(INTDIR)\Convert.obj" \
	"$(INTDIR)\Utils.obj" \
	"$(INTDIR)\StateMachine.obj" \
	"$(INTDIR)\Coroutine.obj" \
	"$(INTDIR)\pcl.obj" \
	"$(INTDIR)\Thread.obj" \
	"$(INTDIR)\Timer.obj" \
	"$(INTDIR)\FileManager.obj" \
	"$(INTDIR)\FileUtils.obj" \
	"$(INTDIR)\IniFile.obj" \
	"$(INTDIR)\Log.obj" \
	"$(INTDIR)\PakFile.obj" \
	"$(INTDIR)\TestSuite.obj" \
	"$(INTDIR)\stlcompile.obj" \
	"$(INTDIR)\STLFunctorDelegate.obj" \
	"$(INTDIR)\ToolBoxTests.obj" \
	"$(INTDIR)\UnitTest.obj" \
	"..\..\Program Files\Microsoft Visual Studio\VC98\Lib\WSOCK32.LIB" \
	"..\..\Program Files\Microsoft Visual Studio\VC98\Lib\WINMM.LIB"

"$(OUTDIR)\BertsToolBoxLib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
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
!IF EXISTS("BertsToolBoxLib.dep")
!INCLUDE "BertsToolBoxLib.dep"
!ELSE 
!MESSAGE Warning: cannot find "BertsToolBoxLib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "BertsToolBoxLib - Win32 Release" || "$(CFG)" == "BertsToolBoxLib - Win32 Debug"
SOURCE=.\BSocket.cpp

"$(INTDIR)\BSocket.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Link.cpp

"$(INTDIR)\Link.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Message.cpp

"$(INTDIR)\Message.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\MessageCenter.cpp

"$(INTDIR)\MessageCenter.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\MessageTesters.cpp

"$(INTDIR)\MessageTesters.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PackFunctions.cpp

"$(INTDIR)\PackFunctions.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SoftwareLink.cpp

"$(INTDIR)\SoftwareLink.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\TCPLink.cpp

"$(INTDIR)\TCPLink.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\AutoBuffer.cpp

"$(INTDIR)\AutoBuffer.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\CommandLineParser.cpp

"$(INTDIR)\CommandLineParser.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ObjectCache.cpp

"$(INTDIR)\ObjectCache.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\OutputIteratorAdapters.cpp
SOURCE=.\StdString.cpp

"$(INTDIR)\StdString.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StringTokenizer.cpp

"$(INTDIR)\StringTokenizer.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ThreadSafeList.cpp

"$(INTDIR)\ThreadSafeList.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Convert.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

CPP_SWITCHES=/nologo /ML /W4 /GR /O2 /Ob0 /I "C:\PROJECTS\BERTSTOOLBOX" /D "NDEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Convert.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

CPP_SWITCHES=/nologo /ML /Gm /GR /Zi /Od /Ob1 /I "C:\PROJECTS\BERTSTOOLBOX" /D "_DEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\Convert.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Utils.cpp

"$(INTDIR)\Utils.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StateMachine.cpp

"$(INTDIR)\StateMachine.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Coroutine.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

CPP_SWITCHES=/nologo /ML /W4 /GR /Od /Ob1 /I "C:\PROJECTS\BERTSTOOLBOX" /D "NDEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Coroutine.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

CPP_SWITCHES=/nologo /ML /Gm /GR /GX- /ZI /Od /Ob1 /I "C:\PROJECTS\BERTSTOOLBOX" /D "_DEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\Coroutine.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\pcl.c

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

CPP_SWITCHES=/nologo /ML /W4 /GR /Od /Ob1 /I "C:\PROJECTS\BERTSTOOLBOX" /D "NDEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\pcl.obj"	"$(INTDIR)\pcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

CPP_SWITCHES=/nologo /ML /Gm /GR /Zi /Od /Ob1 /I "C:\PROJECTS\BERTSTOOLBOX" /D "_DEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\pcl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\pcl_version.c
SOURCE=.\Thread.cpp

"$(INTDIR)\Thread.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Timer.cpp

"$(INTDIR)\Timer.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\FileManager.cpp

"$(INTDIR)\FileManager.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\FileUtils.cpp

"$(INTDIR)\FileUtils.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\IniFile.cpp

"$(INTDIR)\IniFile.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Log.cpp

"$(INTDIR)\Log.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PakFile.cpp

"$(INTDIR)\PakFile.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ErrorCode.cpp
SOURCE=.\execute.cpp
SOURCE=.\mmgr.cpp
SOURCE=.\SafeSet.cpp
SOURCE=.\TestSuite.cpp

"$(INTDIR)\TestSuite.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\stlcompile.cpp

"$(INTDIR)\stlcompile.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\STLFunctorDelegate.cpp

"$(INTDIR)\STLFunctorDelegate.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ToolBoxTests.cpp

"$(INTDIR)\ToolBoxTests.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\UnitTests\UnitTest.cpp

"$(INTDIR)\UnitTest.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

