#############################################################################
# Makefile for building: ../../bin/LSTPGMW
# Generated by qmake (1.07a) (Qt 3.3.4) on: Wed Mar 22 06:10:49 2006
# Project:  ListProgram.pro
# Template: app
# Command: $(QMAKE) -o Makefile ListProgram.pro
#############################################################################

####### Compiler, tools and options

CC       = gcc
CXX      = g++
LEX      = flex
YACC     = yacc
CFLAGS   = -pipe -Wall -W -O2 -pipe -Wp,-D_FORTIFY_SOURCE=2 -fomit-frame-pointer -march=i586 -mtune=pentiumpro  -DQT_NO_DEBUG -DQT_SHARED -DQT_THREAD_SUPPORT
CXXFLAGS = -pipe -Wall -W -O2 -pipe -Wp,-D_FORTIFY_SOURCE=2 -fomit-frame-pointer -march=i586 -mtune=pentiumpro  -DQT_NO_DEBUG -DQT_SHARED -DQT_THREAD_SUPPORT
LEXFLAGS = 
YACCFLAGS= -d
INCPATH  = -I/usr/lib/qt3/mkspecs/default -I. -I. -I$(QTDIR)/include
LINK     = g++
LFLAGS   = 
LIBS     = $(SUBLIBS) -L$(QTDIR)/lib -L/usr/X11R6/lib -lqt-mt -lXext -lX11 -lm
AR       = ar cqs
RANLIB   = 
MOC      = $(QTDIR)/bin/moc
UIC      = $(QTDIR)/bin/uic
QMAKE    = qmake
TAR      = tar -cf
GZIP     = gzip -9f
COPY     = cp -f
COPY_FILE= $(COPY)
COPY_DIR = $(COPY) -r
INSTALL_FILE= $(COPY_FILE)
INSTALL_DIR = $(COPY_DIR)
DEL_FILE = rm -f
SYMLINK  = ln -sf
DEL_DIR  = rmdir
MOVE     = mv -f
CHK_DIR_EXISTS= test -d
MKDIR    = mkdir -p

####### Output directory

OBJECTS_DIR = ./

####### Files

HEADERS = frmlistprogram.ui.h
SOURCES = main.cpp
OBJECTS = main.o \
		frmlistprogram.o
FORMS = frmlistprogram.ui
UICDECLS = frmlistprogram.h
UICIMPLS = frmlistprogram.cpp
SRCMOC   = moc_frmlistprogram.cpp
OBJMOC = moc_frmlistprogram.o
DIST	   = ListProgram.pro
QMAKE_TARGET = LSTPGMW
DESTDIR  = ../../bin/
TARGET   = ../../bin/LSTPGMW

first: all
####### Implicit rules

.SUFFIXES: .c .o .cpp .cc .cxx .C

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

$(TARGET):  $(UICDECLS) $(OBJECTS) $(OBJMOC)  
	test -d ../../bin/ || mkdir -p ../../bin/
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJMOC) $(OBJCOMP) $(LIBS)

mocables: $(SRCMOC)
uicables: $(UICDECLS) $(UICIMPLS)

$(MOC): 
	( cd $(QTDIR)/src/moc && $(MAKE) )

Makefile: ListProgram.pro  /usr/lib/qt3/mkspecs/default/qmake.conf /usr/lib/qt3/lib/libqt-mt.prl
	$(QMAKE) -o Makefile ListProgram.pro
qmake: 
	@$(QMAKE) -o Makefile ListProgram.pro

dist: 
	@mkdir -p .tmp/LSTPGMW && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .tmp/LSTPGMW/ && $(COPY_FILE) --parents frmlistprogram.ui.h .tmp/LSTPGMW/ && ( cd `dirname .tmp/LSTPGMW` && $(TAR) LSTPGMW.tar LSTPGMW && $(GZIP) LSTPGMW.tar ) && $(MOVE) `dirname .tmp/LSTPGMW`/LSTPGMW.tar.gz . && $(DEL_FILE) -r .tmp/LSTPGMW

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

frmlistprogram.h: frmlistprogram.ui 
	$(UIC) frmlistprogram.ui -o frmlistprogram.h

frmlistprogram.cpp: frmlistprogram.h frmlistprogram.ui frmlistprogram.ui.h 
	$(UIC) frmlistprogram.ui -i frmlistprogram.h -o frmlistprogram.cpp

frmlistprogram.o: frmlistprogram.cpp frmlistprogram.h

moc_frmlistprogram.o: moc_frmlistprogram.cpp  frmlistprogram.h 

moc_frmlistprogram.cpp: $(MOC) frmlistprogram.h
	$(MOC) frmlistprogram.h -o moc_frmlistprogram.cpp

####### Install

install:  

uninstall:  

