#############################################################################
# Makefile for building: ../../bin/LSTKSTW
# Generated by qmake (1.04a) (Qt 3.1.1) on: Sun Nov 14 08:54:49 2004
# Project:  ListKst.pro
# Template: app
# Command: $(QMAKE) -o Makefile ListKst.pro
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

HEADERS = frmlistkst.ui.h
SOURCES = main.cpp
OBJECTS = main.o \
		frmlistkst.o
FORMS = frmlistkst.ui
UICDECLS = frmlistkst.h
UICIMPLS = frmlistkst.cpp
SRCMOC   = moc_frmlistkst.cpp
OBJMOC = moc_frmlistkst.o
DIST	   = ListKst.pro
QMAKE_TARGET = LSTKSTW
DESTDIR  = ../../bin/
TARGET   = ../../bin/LSTKSTW

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

Makefile: ListKst.pro  $(QTDIR)/mkspecs/default/qmake.conf 
	$(QMAKE) -o Makefile ListKst.pro
qmake: 
	@$(QMAKE) -o Makefile ListKst.pro

dist: 
	@mkdir -p .tmp/LSTKSTW && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .tmp/LSTKSTW/ && $(COPY_FILE) --parents frmlistkst.ui.h .tmp/LSTKSTW/ && ( cd `dirname .tmp/LSTKSTW` && $(TAR) LSTKSTW.tar LSTKSTW && $(GZIP) LSTKSTW.tar ) && $(MOVE) `dirname .tmp/LSTKSTW`/LSTKSTW.tar.gz . && $(DEL_FILE) -r .tmp/LSTKSTW

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

main.o: main.cpp frmlistkst.h

frmlistkst.h: frmlistkst.ui 
	$(UIC) frmlistkst.ui -o frmlistkst.h

frmlistkst.cpp: frmlistkst.h frmlistkst.ui 
	$(UIC) frmlistkst.ui -i frmlistkst.h -o frmlistkst.cpp

frmlistkst.o: frmlistkst.cpp frmlistkst.ui.h \
		frmlistkst.h

moc_frmlistkst.o: moc_frmlistkst.cpp frmlistkst.h 

moc_frmlistkst.cpp: $(MOC) frmlistkst.h
	$(MOC) frmlistkst.h -o moc_frmlistkst.cpp

####### Install

install: all 

uninstall: 

