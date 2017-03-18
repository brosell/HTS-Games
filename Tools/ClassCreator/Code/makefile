#########################################################################
# makefile
# Created by John F. Hubbard on Mon Jul 31 10:30:34 PDT 2000
#
#
#  Copyright (c) 2000, ATD Azad Technology Development Corporation
#
#            The Reliable Software Outsource Resource
#        You hire us, we do it for you, and we do it right.
#
#                       www.azadtech.com
#
#  Permission is granted to use this code without restriction,
#  as long as this copyright notice appears in all source files.
#
#
#  File Contents: makefile for the ClassCreator project.
#
#  IMPORTANT: Usage: You must set three variables correctly:
#			  TARGET, CPP_LINK_LIBRARY, and CPP_INCLUDE_DIRECTORY.
#
#			See below for details as to how this is done.
#
# %version: 2.33 %
# %date_modified: Fri Jun 29 18:31:25 2001 %
# %created_by: jhubbard %
#
#########################################################################

# Uncomment the target that you are building for. Alternatively, you can use
# the command: make TARGET=LINUX_X86 .

#TARGET=SOLARIS_SPARC
#TARGET=SOLARIS_X86
#TARGET=LINUX_X86
#TARGET=LYNXOS_X86

# Change the value of these two directories to point to a standards-compliant C++
# Library.  If you are using STL Port (free, from http://www.stlport.org), then no
# changes are necessary.  If you are using Dinkumware ($50, from http://www.dinkumware.com)
# I have supplied a commented-out section that will work.

CPP_LINK_LIBRARY=${HOME}/cvs_wa/atc/thirdparty/STLport-4.0/lib/$(TARGET)/libstlport_gcc.a
CPP_INCLUDE_DIRECTORY=${HOME}/cvs_wa/atc/thirdparty/STLport-4.0/stlport

#CPP_LINK_LIBRARY=${HOME}/cvs_wa/atc/thirdparty/sxl/lib/$(TARGET)/sxl.a
#CPP_INCLUDE_DIRECTORY=${HOME}/cvs_wa/atc/thirdparty/sxl/include

INCLUDE_DIRECTORIES=${CPP_INCLUDE_DIRECTORY}
LIBS:=$(CPP_LINK_LIBRARY)

LOCAL_CXX:=gcc
LINK:=gcc
CXX_FLAGS:=-D$(TARGET) -c -O2 -fno-builtin -static -D_REENTRANT -Wall -Wno-unknown-pragmas -Wno-unused

ifeq ($(TARGET),SOLARIS_SPARC)
	LINK_FLAGS= -lgcc -lm -fno-builtin
endif

ifeq ($(TARGET),LINUX_X86)
	LINK_FLAGS= -lgcc -lm -fno-builtin
endif

ifeq ($(TARGET),LYNXOS_X86)
	LINK_FLAGS= -lgcc -lm
endif

OBJECTS		:= 	$(TARGET)/ClassCreator.o 		\
				$(TARGET)/WriteSentry.o 		\
				$(TARGET)/HeaderFileGen.o 		\
			   	$(TARGET)/CodeGenerator.o   	\
               	$(TARGET)/ImplFileGen.o 		\
				$(TARGET)/InlineFileGen.o 		\
				$(TARGET)/UnitTestFileGen.o 	\
				$(TARGET)/MakefileGen.o  		\
               	$(TARGET)/DigestedCommands.o 	\
               	$(TARGET)/CommandLine.o 		\
				$(TARGET)/PackedString.o 		\
				$(TARGET)/main.o

PROGRAM=fcc

all: setup $(TARGET)/$(PROGRAM)
	@echo "Building for the $(TARGET) platform..."

setup:
	@if [ ! -d $(TARGET) ];then mkdir $(TARGET);fi

html: ${HEADERS}
	doc++ -d html ${HEADERS}
	touch html

clean:
	@-rm -r $(TARGET)
#	@-rm -r html

$(TARGET)/$(PROGRAM): $(OBJECTS)
	$(LINK) $(LINK_FLAGS) $(OBJECTS) $(LIBS) -o $(TARGET)/$(PROGRAM)

$(TARGET)/%.o:%.cpp *.h *.icc
	$(LOCAL_CXX) $(CXX_FLAGS) $< -o $@ -I $(INCLUDE_DIRECTORIES)

clean_for_checkin:
	@-rm *.o utCommandLine
	@-rm -r  html
	@-rm -r Debug
	@-rm *.plg *.opt *.ncb *.dsw

