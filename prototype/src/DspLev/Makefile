#############################################################################
# Makefile for building: ../../bin/DSPLEVW
# Generated by qmake (1.04a) (Qt 3.1.1) on: Sat Nov 13 17:06:40 2004
# Project:  DspLev.pro
# Template: app
# Command: $(QMAKE) -o Makefile DspLev.pro
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

HEADERS = frmdsplev.ui.h
SOURCES = main.cpp
OBJECTS = main.o \
		frmdsplev.o
FORMS = frmdsplev.ui
UICDECLS = frmdsplev.h
UICIMPLS = frmdsplev.cpp
SRCMOC   = moc_frmdsplev.cpp
OBJMOC = moc_frmdsplev.o
DIST	   = DspLev.pro
QMAKE_TARGET = DSPLEVW
DESTDIR  = ../../bin/
TARGET   = ../../bin/DSPLEVW

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

Makefile: DspLev.pro  $(QTDIR)/mkspecs/default/qmake.conf 
	$(QMAKE) -o Makefile DspLev.pro
qmake: 
	@$(QMAKE) -o Makefile DspLev.pro

dist: 
	@mkdir -p .tmp/DSPLEVW && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .tmp/DSPLEVW/ && $(COPY_FILE) --parents frmdsplev.ui.h .tmp/DSPLEVW/ && ( cd `dirname .tmp/DSPLEVW` && $(TAR) DSPLEVW.tar DSPLEVW && $(GZIP) DSPLEVW.tar ) && $(MOVE) `dirname .tmp/DSPLEVW`/DSPLEVW.tar.gz . && $(DEL_FILE) -r .tmp/DSPLEVW

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

main.o: main.cpp frmdsplev.h

frmdsplev.h: frmdsplev.ui 
	$(UIC) frmdsplev.ui -o frmdsplev.h

frmdsplev.cpp: frmdsplev.h frmdsplev.ui 
	$(UIC) frmdsplev.ui -i frmdsplev.h -o frmdsplev.cpp

frmdsplev.o: frmdsplev.cpp frmdsplev.ui.h \
		frmdsplev.h

moc_frmdsplev.o: moc_frmdsplev.cpp frmdsplev.h 

moc_frmdsplev.cpp: $(MOC) frmdsplev.h
	$(MOC) frmdsplev.h -o moc_frmdsplev.cpp

####### Install

install: all 

uninstall: 

