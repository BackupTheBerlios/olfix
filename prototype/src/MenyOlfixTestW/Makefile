#############################################################################
# Makefile for building: ../../bin/OLFIXTW
# Generated by qmake (1.04a) (Qt 3.1.1) on: Tue Nov 29 14:20:26 2005
# Project:  MenyOlfixTestW.pro
# Template: app
# Command: $(QMAKE) -o Makefile MenyOlfixTestW.pro
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

HEADERS = frmolfix.ui.h
SOURCES = main.cpp
OBJECTS = main.o \
		frmolfix.o
FORMS = frmolfix.ui
UICDECLS = frmolfix.h
UICIMPLS = frmolfix.cpp
SRCMOC   = moc_frmolfix.cpp
OBJMOC = moc_frmolfix.o
DIST	   = MenyOlfixTestW.pro
QMAKE_TARGET = OLFIXTW
DESTDIR  = ../../bin/
TARGET   = ../../bin/OLFIXTW

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

Makefile: MenyOlfixTestW.pro  $(QTDIR)/mkspecs/default/qmake.conf 
	$(QMAKE) -o Makefile MenyOlfixTestW.pro
qmake: 
	@$(QMAKE) -o Makefile MenyOlfixTestW.pro

dist: 
	@mkdir -p .tmp/OLFIXTW && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .tmp/OLFIXTW/ && $(COPY_FILE) --parents frmolfix.ui.h .tmp/OLFIXTW/ && ( cd `dirname .tmp/OLFIXTW` && $(TAR) OLFIXTW.tar OLFIXTW && $(GZIP) OLFIXTW.tar ) && $(MOVE) `dirname .tmp/OLFIXTW`/OLFIXTW.tar.gz . && $(DEL_FILE) -r .tmp/OLFIXTW

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

main.o: main.cpp frmolfix.h

frmolfix.h: frmolfix.ui 
	$(UIC) frmolfix.ui -o frmolfix.h

frmolfix.cpp: frmolfix.h frmolfix.ui 
	$(UIC) frmolfix.ui -i frmolfix.h -o frmolfix.cpp

frmolfix.o: frmolfix.cpp frmolfix.ui.h \
		frmolfix.h

moc_frmolfix.o: moc_frmolfix.cpp frmolfix.h 

moc_frmolfix.cpp: $(MOC) frmolfix.h
	$(MOC) frmolfix.h -o moc_frmolfix.cpp

####### Install

install: all 

uninstall: 

