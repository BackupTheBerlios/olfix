#############################################################################
# Makefile for building: ../../bin/BALRPTW
# Generated by qmake (1.04a) (Qt 3.1.1) on: Fri Nov 12 20:25:21 2004
# Project:  Balansrapport.pro
# Template: app
# Command: $(QMAKE) -o Makefile Balansrapport.pro
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

HEADERS = frmbalansrapport.ui.h
SOURCES = main.cpp
OBJECTS = main.o \
		frmbalansrapport.o
FORMS = frmbalansrapport.ui
UICDECLS = frmbalansrapport.h
UICIMPLS = frmbalansrapport.cpp
SRCMOC   = moc_frmbalansrapport.cpp
OBJMOC = moc_frmbalansrapport.o
DIST	   = Balansrapport.pro
QMAKE_TARGET = BALRPTW
DESTDIR  = ../../bin/
TARGET   = ../../bin/BALRPTW

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

Makefile: Balansrapport.pro  $(QTDIR)/mkspecs/default/qmake.conf 
	$(QMAKE) -o Makefile Balansrapport.pro
qmake: 
	@$(QMAKE) -o Makefile Balansrapport.pro

dist: 
	@mkdir -p .tmp/BALRPTW && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .tmp/BALRPTW/ && $(COPY_FILE) --parents frmbalansrapport.ui.h .tmp/BALRPTW/ && ( cd `dirname .tmp/BALRPTW` && $(TAR) BALRPTW.tar BALRPTW && $(GZIP) BALRPTW.tar ) && $(MOVE) `dirname .tmp/BALRPTW`/BALRPTW.tar.gz . && $(DEL_FILE) -r .tmp/BALRPTW

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

main.o: main.cpp frmbalansrapport.h

frmbalansrapport.h: frmbalansrapport.ui 
	$(UIC) frmbalansrapport.ui -o frmbalansrapport.h

frmbalansrapport.cpp: frmbalansrapport.h frmbalansrapport.ui 
	$(UIC) frmbalansrapport.ui -i frmbalansrapport.h -o frmbalansrapport.cpp

frmbalansrapport.o: frmbalansrapport.cpp frmbalansrapport.ui.h \
		frmbalansrapport.h

moc_frmbalansrapport.o: moc_frmbalansrapport.cpp frmbalansrapport.h 

moc_frmbalansrapport.cpp: $(MOC) frmbalansrapport.h
	$(MOC) frmbalansrapport.h -o moc_frmbalansrapport.cpp

####### Install

install: all 

uninstall: 

