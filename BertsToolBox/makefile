# tool box makefile

ifeq ($(TOOLSET),dmc)

	CCC = dmc.exe
	CC = dmc.exe
	
	CPPFLAGS = -c -Jm -w -w- -w6 -v0  -o-all $(INCLUDE_DIRS) -D_STLP_NO_OWN_IOSTREAMSxxx -DWIN32 -DNDEBUG -D_MBCS -D_LIB -o$(INTDIR)\ /c -mn
	CFLAGS = -c -Jm -w -w- -w6 -v0  -o-all $(INCLUDE_DIRS) -D_STLP_NO_OWN_IOSTREAMSxxx -DWIN32 -DNDEBUG -D_MBCS -D_LIB -o$(INTDIR)\ /c -mn
	
	OBJ_DIR = dmc_obj
	LIB_DIR = dmc_lib
			
	LIB = lib.exe
	LINK = dmc.exe
	INCLUDE_DIRS = "-I.;c:\dm\stlport\stlport;c:\dm\stl;c:\dm\include;c:\projects\GAMELIB"
	
	LINK_LINE = $(LINK) "-oToolBox.lib" $(cppobjs) $(cobjs) $(LIBS) -mn /PAGESIZE:32
	LINK_LINE = lib -p32 -c ToolBox.lib  $(cppobjs) $(cobjs) $(libs)
else
ifeq ($(TOOLSET),vc)
	CCC = cl
	CC = cl
	CPPFLAGS = /nologo /MD /W3 /Od /Ox /Ob1 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB"  /c 
	CFLAGS = /nologo /MD /W3 /Od /Ob1 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB"  /c 

	OBJ_DIR = vc_obj
	LIB_DIR = vc_lib
		
	LINK_LINE = link.exe -lib "/out:ToolBox.lib" $(cppobjs) $(cobjs) $(LIBS)
	Link = link
else
		
endif
endif

OUTFILE = -o$@
	
LIBS = wsock32.lib winmm.lib OLEAUT32.LIB

depricated = AutoBuffer.obj OutputIteratorAdaptors.obj

cppobjslll = \
				BSocket.obj \
				Link.obj \
				Message.obj \
				MessageCenter.obj \
			 	MessageTesters.obj \
			 	PackFunctions.obj \
			 	SoftwareLink.obj \
			 	TCPLink.obj \
			 	StdString.obj \
			 	CommandLineParser.obj \
			 	StringTokenizer.obj \
			 	Stub.obj \
       	ThreadSafeList.obj \
       	ObjectCache.obj \
       	Timer.obj \
       	StateMachine.obj \
       	Coroutine.obj \
       	Thread.obj \
       	FileManager.obj \
       	FileUtils.obj \
       	Log.obj \
       	PakFile.obj \
       	Convert.obj


cppobjs = \
				BSocket.obj \
				Link.obj \
				Message.obj \
				MessageCenter.obj \
			 	MessageTesters.obj \
			 	PackFunctions.obj \
			 	SoftwareLink.obj \
			 	TCPLink.obj \
			 	StdString.obj \
			 	CommandLineParser.obj \
			 	StringTokenizer.obj \
			 	Stub.obj \
       	ThreadSafeList.obj \
       	ObjectCache.obj \
       	Timer.obj \
       	StateMachine.obj \
       	Coroutine.obj \
       	Thread.obj \
       	FileManager.obj \
       	FileUtils.obj \
       	IniFile.obj \
       	Log.obj \
       	PakFile.obj \
       	Convert.obj
              
cobjs = pcl.obj


ToolBox.lib: $(cppobjs) $(cobjs)
	$(LINK_LINE)

$(cppobjs): %.obj: %.cpp
	-$(CCC)  $(CPPFLAGS) $< $(OUTFILE)

$(cobjs):%.obj: %.c
	-$(CC)  $(CFLAGS) $< $(OUTFILE)
  

	