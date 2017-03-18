#########################################################################
#  makefile
#  Created by Bert Rosell on Mon Nov 24 2003, 14:07:36 Eastern Standard Time
#
#  Copyright (c) 2001, ATD Azad Technology Development Corporation
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
# BASIC USAGE:  This is easy!  As long as you set the TARGET variable
#               (either in your environmental variables, or by un-commenting
#               one of the "TARGET=xxx" lines below), the makefile will
#               work for you (just type "make" or "make all").
#               In addition, here are a few refinements:
#
# ADVANCED USAGE:
#    1. You can add new class files by adding the associated object file
#    name to the list of object files in the CPP_OBJS variable, below.
#    That is, if you add a new class Blue, add "${TARGET}/Blue.o" to the list.
#
#    2. Similarly, you can add additional unit tests by adding to the list of
#    object files in the UNIT_TEST_OBJS variable.
#
#    3. If you need to change any of the compile or link flags, they are
#    subdivided into groups, in order to make this easy.  For example,
#    you could type "make TARGET=SOLARIS_SPARC DEBUG_FLAGS= " in order
#    to turn off the -g option (which adds debug symbols).
#
#    4. You can use a different C++ library by changing just two
#    variables: CPP_LINK_LIBRARY and CPP_INCLUDE_DIRECTORY.  Currently,
#    these are pointing to a typical location for the STLport Standard
#    C++ Library.  I recommend that you stick with this, as it is free,
#    portable, thread-safe, and highly standards-compliant (as of July, 2001);
#    you can download STLport from http://www.stlport.org . The
#    C/C++ Users Journal also has an article on libraries that shows STLport
#    in a good light; see http://www.cuj.com .
#    -- John F. Hubbard, 27 July 2001.
#
#  $Version: 1.0 $
#  $Date: Mon Nov 24 2003, 14:07:36 Eastern Standard Time $ 
#  $Author: Bert Rosell $
#
#########################################################################


PROGRAM=utRadioButton

CPP_OBJS=            ${TARGET}/RadioButton.o   

UNIT_TEST_OBJS=      ${TARGET}/utRadioButton.o

# Uncomment the target that you are building for. Alternatively, you can use
# the command: make TARGET=LINUX_X86 .

#TARGET=SOLARIS_SPARC
#TARGET=SOLARIS_X86
#TARGET=LINUX_X86
#TARGET=LYNXOS_X86
#TARGET=LYNXOS_PPC
#TARGET=WIN32_GCC

# Change the value of these two directories to point to a standards-compliant C++
# Library.  If you are using STL Port (free, from http://www.stlport.org), then no
# changes are necessary.

CPP_LINK_LIBRARY=${HOME}/cvs_wa/atc/thirdparty/STLport-4.0/lib/${TARGET}/libstlport_gcc.a
CPP_INCLUDE_DIRECTORY=${HOME}/cvs_wa/atc/thirdparty/STLport-4.0/stlport

INCLUDES=-I${CPP_INCLUDE_DIRECTORY} -I.
LIBS:=  ${CPP_LINK_LIBRARY}

LOCAL_CXX:=gcc
LINK:=gcc

LINK_FLAGS= -lgcc -lm -fno-builtin

OPTIMIZE_FLAGS=           -O2
DEBUG_FLAGS=              -g
WARNING_LEVEL_FLAGS=      -Wall -Wno-unknown-pragmas -Wno-unused
THIRD_PARTY_STL_FLAGS=    -fno-builtin -static
PLATFORM_SPECIFIC_FLAGS=

ifeq (${TARGET},SOLARIS_SPARC)
	# Change or add any Solaris-specific flags here
endif

ifeq (${TARGET},LINUX_X86)
	# Change or add any Linux-specific flags here
endif

ifeq (${TARGET},LYNXOS_X86)
	# Change or add any LynxOS-specific flags here
	LINK_FLAGS= -lgcc -lm
	PLATFORM_SPECIFIC_FLAGS=-D__Lynx__
endif

ifeq (${TARGET},LYNXOS_PPC)
	# Change or add any LynxOS-specific flags here
	LINK_FLAGS= -lgcc -lm
	PLATFORM_SPECIFIC_FLAGS=-D__Lynx__
endif

CXX_FLAGS:=-D${TARGET}                \
           -D_REENTRANT               \
           ${OPTIMIZE_FLAGS}          \
           ${DEBUG_FLAGS}             \
           ${THIRD_PARTY_STL_FLAGS}   \
           ${WARNING_LEVEL_FLAGS}     \
           ${PLATFORM_SPECIFIC_FLAGS}

default: ${TARGET}/${PROGRAM}

all: ${TARGET}/${PROGRAM} doc

doc:
	@if [ ! -d html ];then mkdir html;fi
	-@ doc++ -d html -H -u *.h

cleandoc:
	-@if [ -d html ];then rm -r html;fi

setup:
	@echo "Building the ${PROGRAM} program..."
	@if [ ! -d ${TARGET} ];then mkdir ${TARGET};fi

${TARGET}/${PROGRAM}: setup ${CPP_OBJS} ${UNIT_TEST_OBJS}
	${LINK} ${CPP_OBJS} ${UNIT_TEST_OBJS} ${LIBS} ${LINK_FLAGS} -o ${TARGET}/${PROGRAM}

${UNIT_TEST_OBJS}: ${TARGET}/%.o: %.cpp
	${LOCAL_CXX} -c ${CXX_FLAGS} $< -o $@ ${INCLUDES}

${CPP_OBJS}: ${TARGET}/%.o: %.cpp %.h %.icc
	${LOCAL_CXX} -c ${CXX_FLAGS} $< -o $@ ${INCLUDES}

cleanall: cleandoc clean

clean:
	-@if [ -d html ];then rm html/*;fi
	-@if [ -d ${TARGET} ];then rm -r ${TARGET} ;fi

test: all
	@$(TARGET)/$(PROGRAM) > $(PROGRAM).out

	@if cmp -s $(PROGRAM).sig $(PROGRAM).out; then                          	        \
		echo "UnitTest $(PROGRAM):	SUCCESS";                                       \
	else                                                                    	        \
		if [ -x $(PROGRAM).sig ]; then                                      	        \
			echo "UnitTest $(PROGRAM):	FAILED";                                \
			diff $(PROGRAM).sig $(PROGRAM).out;                                     \
		else                                                                	        \
			echo "UnitTest $(PROGRAM):	UNKNOWN (no signature file exists)"; 	\
		fi                                                                              \
	fi

