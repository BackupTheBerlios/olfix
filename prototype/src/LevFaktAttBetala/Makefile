#############################################################################
# Makefile for building: ../../bin/ATTBETW
# Generated by qmake (1.04a) (Qt 3.1.1) on: Sun Nov 14 05:31:52 2004
# Project:  LevFaktAttBetala.pro
# Template: app
# Command: $(QMAKE) -o Makefile LevFaktAttBetala.pro
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

HEADERS = frmlevfaktattbetala.ui.h
SOURCES = main.cpp
OBJECTS = main.o \
		frmlevfaktattbetala.o
FORMS = frmlevfaktattbetala.ui
UICDECLS = frmlevfaktattbetala.h
UICIMPLS = frmlevfaktattbetala.cpp
SRCMOC   = moc_frmlevfaktattbetala.cpp
OBJMOC = moc_frmlevfaktattbetala.o
DIST	   = LevFaktAttBetala.pro
QMAKE_TARGET = ATTBETW
DESTDIR  = ../../bin/
TARGET   = ../../bin/ATTBETW

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

Makefile: LevFaktAttBetala.pro  $(QTDIR)/mkspecs/default/qmake.conf 
	$(QMAKE) -o Makefile LevFaktAttBetala.pro
qmake: 
	@$(QMAKE) -o Makefile LevFaktAttBetala.pro

dist: 
	@mkdir -p .tmp/ATTBETW && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .tmp/ATTBETW/ && $(COPY_FILE) --parents frmlevfaktattbetala.ui.h .tmp/ATTBETW/ && ( cd `dirname .tmp/ATTBETW` && $(TAR) ATTBETW.tar ATTBETW && $(GZIP) ATTBETW.tar ) && $(MOVE) `dirname .tmp/ATTBETW`/ATTBETW.tar.gz . && $(DEL_FILE) -r .tmp/ATTBETW

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

main.o: main.cpp frmlevfaktattbetala.h

frmlevfaktattbetala.h: frmlevfaktattbetala.ui 
	$(UIC) frmlevfaktattbetala.ui -o frmlevfaktattbetala.h

frmlevfaktattbetala.cpp: frmlevfaktattbetala.h frmlevfaktattbetala.ui 
	$(UIC) frmlevfaktattbetala.ui -i frmlevfaktattbetala.h -o frmlevfaktattbetala.cpp

frmlevfaktattbetala.o: frmlevfaktattbetala.cpp frmlevfaktattbetala.ui.h \
		frmlevfaktattbetala.h

moc_frmlevfaktattbetala.o: moc_frmlevfaktattbetala.cpp frmlevfaktattbetala.h 

moc_frmlevfaktattbetala.cpp: $(MOC) frmlevfaktattbetala.h
	$(MOC) frmlevfaktattbetala.h -o moc_frmlevfaktattbetala.cpp

####### Install

install: all 

uninstall: 

