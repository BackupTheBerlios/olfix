#############################################################################
# Makefile for building: ../../bin/DSPINKW
# Generated by qmake (1.04a) (Qt 3.1.1) on: Sat Nov 13 15:04:26 2004
# Project:  DspBestellning.pro
# Template: app
# Command: $(QMAKE) -o Makefile DspBestellning.pro
#############################################################################

####### Compiler, tools and options

CC       = gcc
CXX      = g++
LEX      = flex
YACC     = yacc
CFLAGS   = -pipe -Wall -W -O2 -fomit-frame-pointer -pipe -march=i586 -mcpu=pentiumpro  -DQT_NO_DEBUG
CXXFLAGS = -pipe -Wall -W -O2 -fomit-frame-pointer -pipe -march=i586 -mcpu=pentiumpro  -DQT_NO_DEBUG
LEXFLAGS = 
YACCFLAGS= -d
INCPATH  = -I$(QTDIR)/mkspecs/default -I. -I. -I$(QTDIR)/include
LINK     = g++
LFLAGS   = 
LIBS     = $(SUBLIBS) -L$(QTDIR)/lib -L/usr/X11R6/lib -lqt -lXext -lX11 -lm
AR       = ar cqs
RANLIB   = 
MOC      = $(QTDIR)/bin/moc
UIC      = $(QTDIR)/bin/uic
QMAKE    = qmake
TAR      = tar -cf
GZIP     = gzip -9f
COPY     = cp -f
COPY_FILE= $(COPY) -p
COPY_DIR = $(COPY) -pR
DEL_FILE = rm -f
SYMLINK  = ln -sf
DEL_DIR  = rmdir
MOVE     = mv -f
CHK_DIR_EXISTS= test -d
MKDIR    = mkdir -p

####### Output directory

OBJECTS_DIR = ./

####### Files

HEADERS = frmdspbest.ui.h
SOURCES = main.cpp
OBJECTS = main.o \
		frmdspbest.o
FORMS = frmdspbest.ui
UICDECLS = frmdspbest.h
UICIMPLS = frmdspbest.cpp
SRCMOC   = moc_frmdspbest.cpp
OBJMOC = moc_frmdspbest.o
DIST	   = DspBestellning.pro
QMAKE_TARGET = DSPINKW
DESTDIR  = ../../bin/
TARGET   = ../../bin/DSPINKW

first: all
####### Implicit rules

.SUFFIXES: .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

####### Build rules

all: Makefile $(TARGET)

$(TARGET): $(UICDECLS) $(OBJECTS) $(OBJMOC) 
	test -d ../../bin/ || mkdir -p ../../bin/
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJMOC) $(LIBS)

mocables: $(SRCMOC)

$(MOC): 
	( cd $(QTDIR)/src/moc ; $(MAKE) )

Makefile: DspBestellning.pro  $(QTDIR)/mkspecs/default/qmake.conf 
	$(QMAKE) -o Makefile DspBestellning.pro
qmake: 
	@$(QMAKE) -o Makefile DspBestellning.pro

dist: 
	@mkdir -p .tmp/DSPINKW && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .tmp/DSPINKW/ && $(COPY_FILE) --parents frmdspbest.ui.h .tmp/DSPINKW/ && ( cd `dirname .tmp/DSPINKW` && $(TAR) DSPINKW.tar DSPINKW && $(GZIP) DSPINKW.tar ) && $(MOVE) `dirname .tmp/DSPINKW`/DSPINKW.tar.gz . && $(DEL_FILE) -r .tmp/DSPINKW

mocclean:
	-$(DEL_FILE) $(OBJMOC)
	-$(DEL_FILE) $(SRCMOC)

uiclean:
	-$(DEL_FILE) $(UICIMPLS) $(UICDECLS)

yaccclean:
lexclean:
clean: mocclean uiclean
	-$(DEL_FILE) $(OBJECTS) 
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) ../../bin/$(TARGET) $(TARGET)


FORCE:

####### Compile

main.o: main.cpp frmdspbest.h

frmdspbest.h: frmdspbest.ui 
	$(UIC) frmdspbest.ui -o frmdspbest.h

frmdspbest.cpp: frmdspbest.h frmdspbest.ui 
	$(UIC) frmdspbest.ui -i frmdspbest.h -o frmdspbest.cpp

frmdspbest.o: frmdspbest.cpp frmdspbest.ui.h \
		frmdspbest.h

moc_frmdspbest.o: moc_frmdspbest.cpp frmdspbest.h 

moc_frmdspbest.cpp: $(MOC) frmdspbest.h
	$(MOC) frmdspbest.h -o moc_frmdspbest.cpp

####### Install

install: all 

uninstall: 

