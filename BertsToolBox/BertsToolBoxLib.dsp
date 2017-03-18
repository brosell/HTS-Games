# Microsoft Developer Studio Project File - Name="BertsToolBoxLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=BertsToolBoxLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BertsToolBoxLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BertsToolBoxLib.mak" CFG="BertsToolBoxLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BertsToolBoxLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "BertsToolBoxLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "BertsToolBoxLib - Win32 Demo" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "BertsToolBoxLib"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

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
# ADD CPP /nologo /MD /W4 /GR /O2 /I "C:\PROJECTS\BERTSTOOLBOX" /D "NDEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

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
# ADD CPP /nologo /MD /Gm /GR /Zi /Od /Ob1 /I "C:\PROJECTS\BERTSTOOLBOX" /D "_LIB" /D "WIN32" /D "HTS_DEBUG" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BertsToolBoxLib___Win32_Demo"
# PROP BASE Intermediate_Dir "BertsToolBoxLib___Win32_Demo"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BertsToolBoxLib___Win32_Demo"
# PROP Intermediate_Dir "BertsToolBoxLib___Win32_Demo"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W4 /GR /O2 /I "C:\PROJECTS\BERTSTOOLBOX" /D "NDEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /FD /c
# ADD CPP /nologo /MD /W4 /GR /O2 /I "C:\PROJECTS\BERTSTOOLBOX" /D "NDEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /FD /c
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

# Name "BertsToolBoxLib - Win32 Release"
# Name "BertsToolBoxLib - Win32 Debug"
# Name "BertsToolBoxLib - Win32 Demo"
# Begin Group "ipc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BSocket.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\BSocket.h
# End Source File
# Begin Source File

SOURCE=.\ipc.h
# End Source File
# Begin Source File

SOURCE=.\Link.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Link.h
# End Source File
# Begin Source File

SOURCE=.\Message.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Message.h
# End Source File
# Begin Source File

SOURCE=.\MessageCenter.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MessageCenter.h
# End Source File
# Begin Source File

SOURCE=.\MessageTesters.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MessageTesters.h
# End Source File
# Begin Source File

SOURCE=.\PackFunctions.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\packFunctions.h
# End Source File
# Begin Source File

SOURCE=.\SoftwareLink.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SoftwareLink.h
# End Source File
# Begin Source File

SOURCE=.\TCPLink.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TCPLink.h
# End Source File
# End Group
# Begin Group "Container"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AutoBuffer.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AutoBuffer.h
# End Source File
# Begin Source File

SOURCE=.\CommandLineParser.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CommandLineParser.h
# End Source File
# Begin Source File

SOURCE=.\ObjectCache.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ObjectCache.h
# End Source File
# Begin Source File

SOURCE=.\OutputIteratorAdapters.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OutputIteratorAdapters.h
# End Source File
# Begin Source File

SOURCE=.\StdString.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdString.h
# End Source File
# Begin Source File

SOURCE=.\StringTokenizer.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StringTokenizer.h
# End Source File
# Begin Source File

SOURCE=.\ThreadSafeList.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ThreadSafeList.h
# End Source File
# End Group
# Begin Group "Misc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Convert.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

# ADD CPP /Ob0

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

# ADD BASE CPP /Ob0
# ADD CPP /Ob0

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Convert.h
# End Source File
# Begin Source File

SOURCE=.\Delegate.h
# End Source File
# Begin Source File

SOURCE=.\Types.h
# End Source File
# Begin Source File

SOURCE=.\Utils.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Utils.h
# End Source File
# End Group
# Begin Group "StateMachine"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\StateMachine.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StateMachine.h
# End Source File
# End Group
# Begin Group "Multitask"

# PROP Default_Filter ""
# Begin Group "Coroutine"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Coroutine.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

# ADD CPP /Od /Ob1

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /GX- /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

# ADD BASE CPP /Od /Ob1
# ADD CPP /Od /Ob1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Coroutine.h
# End Source File
# Begin Source File

SOURCE=.\CoroutineDelegates.h
# End Source File
# Begin Source File

SOURCE=.\pcl.c

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

# ADD CPP /Od /Ob1 /FR

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

# ADD BASE CPP /Od /Ob1 /FR
# ADD CPP /Od /Ob1 /FR

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\pcl.h
# End Source File
# Begin Source File

SOURCE=.\pcl_config.h
# End Source File
# Begin Source File

SOURCE=.\pcl_version.c

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "Thread"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Mutex.h
# End Source File
# Begin Source File

SOURCE=.\Thread.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Thread.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Timer.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Timer.h
# End Source File
# End Group
# Begin Group "FileStuff"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\enumeration.hpp
# End Source File
# Begin Source File

SOURCE=.\FileManager.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FileManager.h
# End Source File
# Begin Source File

SOURCE=.\FileUtils.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FileUtils.h
# End Source File
# Begin Source File

SOURCE=.\IniFile.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\IniFile.h
# End Source File
# Begin Source File

SOURCE=.\Log.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Log.h
# End Source File
# Begin Source File

SOURCE=.\NDirIt.hpp
# End Source File
# Begin Source File

SOURCE=.\PakFile.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PakFile.h
# End Source File
# End Group
# Begin Group "external libs"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\..\..\..\Program Files\Microsoft Visual Studio\VC98\Lib\WSOCK32.LIB"
# End Source File
# Begin Source File

SOURCE="..\..\Program Files\Microsoft Visual Studio\VC98\Lib\WINMM.LIB"
# End Source File
# End Group
# Begin Group "Deprecated"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ErrorCode.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ErrorCode.h

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Event.h
# End Source File
# Begin Source File

SOURCE=.\execute.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\execute.h

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MemLeakDetector.h
# End Source File
# Begin Source File

SOURCE=.\mmgr.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mmgr.h
# End Source File
# Begin Source File

SOURCE=.\nommgr.h
# End Source File
# Begin Source File

SOURCE=.\SafeSet.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SafeSet.h
# End Source File
# End Group
# Begin Group "Testing"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TestSuite.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TestSuite.h
# End Source File
# End Group
# Begin Group "STL"

# PROP Default_Filter ""
# Begin Group "tests"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\nocase_compare_tests.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\nocase_compare.h
# End Source File
# Begin Source File

SOURCE=.\null_ostreambuf.h
# End Source File
# Begin Source File

SOURCE=.\stlcompile.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\STLFunctorDelegate.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\STLFunctorDelegate.h
# End Source File
# End Group
# Begin Group "UnitTests"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UnitTests\test_suite_tests.h
# End Source File
# Begin Source File

SOURCE=.\ToolBoxTests.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\UnitTests\UnitTest.cpp

!IF  "$(CFG)" == "BertsToolBoxLib - Win32 Release"

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Debug"

# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "BertsToolBoxLib - Win32 Demo"

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\CommentMacro.h
# End Source File
# Begin Source File

SOURCE=.\lunar.h
# End Source File
# Begin Source File

SOURCE=.\ToolBoxTests.h
# End Source File
# End Target
# End Project
