#############################################################################
# Makefile for building: ../../bin/LSTPKDW
# Generated by qmake (1.04a) (Qt 3.1.1) on: Wed Dec  1 05:45:10 2004
# Project:  ListProdkod.pro
# Template: app
# Command: $(QMAKE) -o Makefile ListProdkod.pro
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

HEADERS = frmlistprodkod.ui.h
SOURCES = main.cpp
OBJECTS = main.o \
		frmlistprodkod.o
FORMS = frmlistprodkod.ui
UICDECLS = frmlistprodkod.h
UICIMPLS = frmlistprodkod.cpp
SRCMOC   = moc_frmlistprodkod.cpp
OBJMOC = moc_frmlistprodkod.o
DIST	   = ListProdkod.pro
QMAKE_TARGET = LSTPKDW
DESTDIR  = ../../bin/
TARGET   = ../../bin/LSTPKDW

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

Makefile: ListProdkod.pro  $(QTDIR)/mkspecs/default/qmake.conf 
	$(QMAKE) -o Makefile ListProdkod.pro
qmake: 
	@$(QMAKE) -o Makefile ListProdkod.pro

dist: 
	@mkdir -p .tmp/LSTPKDW && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .tmp/LSTPKDW/ && $(COPY_FILE) --parents frmlistprodkod.ui.h .tmp/LSTPKDW/ && ( cd `dirname .tmp/LSTPKDW` && $(TAR) LSTPKDW.tar LSTPKDW && $(GZIP) LSTPKDW.tar ) && $(MOVE) `dirname .tmp/LSTPKDW`/LSTPKDW.tar.gz . && $(DEL_FILE) -r .tmp/LSTPKDW

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

main.o: main.cpp 

frmlistprodkod.h: frmlistprodkod.ui 
	$(UIC) frmlistprodkod.ui -o frmlistprodkod.h

frmlistprodkod.cpp: frmlistprodkod.h frmlistprodkod.ui 
	$(UIC) frmlistprodkod.ui -i frmlistprodkod.h -o frmlistprodkod.cpp

frmlistprodkod.o: frmlistprodkod.cpp frmlistprodkod.ui.h \
		frmlistprodkod.h

moc_frmlistprodkod.o: moc_frmlistprodkod.cpp frmlistprodkod.h 

moc_frmlistprodkod.cpp: $(MOC) frmlistprodkod.h
	$(MOC) frmlistprodkod.h -o moc_frmlistprodkod.cpp

####### Install

install: all 

uninstall: 

