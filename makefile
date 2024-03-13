MAINPROG=k-means
DIR=${PWD}
ASST=$(notdir ${DIR})
CC=gcc
CXX=g++
##
# Adjust settings for different compilers
#
ifeq ($(OS),Windows_NT)
#
# Flags for Windows compilers
CPPFLAGS=-g -std=c++17 -MMD -pthread -D_GLIBCXX_DEBUG -Wall
LFLAGS=
RM=del /q
EXE=.exe
TIMELIMIT=
else
#
# Flags for Linux & MacOS
CPPFLAGS=-g -std=c++17 -fsanitize=address -MMD -pthread -D_GLIBCXX_DEBUG -Wall
LFLAGSx=
RM=/bin/rm -rf
EXE=
UNAME_S=$(shell uname -s)
ifeq ($(UNAME_S),Linux)
  TIMELIMIT=timeout 10s
else
  TIMELIMIT=
endif
endif
#
########################################################################
# Macro definitions for "standard" C and C++ compilations
#
CFLAGS=-g
TARGET=$(MAINPROG)$(EXE)
CPPS=$(wildcard *.cpp)
MAINCPPS=$(filter-out unittest.cpp test%.cpp, $(CPPS))
TESTCPPS=$(filter-out $(MAINPROG).cpp, $(CPPS))
 
.SECONDARY:

LINK=g++ $(CPPFLAGS)
#
########################################################################
#
#
#  In most cases, you should not change anything below this line.
#
#  The following is "boilerplate" to set up the standard compilation
#  commands:
#


MAINOBJS=$(MAINCPPS:%.cpp=%.o)
TESTOBJS=$(TESTCPPS:%.cpp=%.o)
DEPENDENCIES = $(CPPS:%.cpp=%.d)

%.d: %.cpp
	touch $@

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -o $@ -c $*.cpp

# 
# Targets:
# 

all: compile

compile: $(TARGET)

clean:
	-/bin/rm -rf *.d *.o $(TARGET) unittest$(EXE) docs grader/build

documentation:
	-mkdir docs
	doxygen Doxyfile

make.dep: $(DEPENDENCIES)
	-cat $(DEPENDENCIES) > $@

include make.dep
