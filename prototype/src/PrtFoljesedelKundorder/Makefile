#############################################################################
# Makefile for building: ../../bin/FSORDW
# Generated by qmake (1.04a) (Qt 3.1.1) on: Tue Apr  5 07:02:31 2005
# Project:  PrtFoljesedel.pro
# Template: app
# Command: $(QMAKE) -o Makefile PrtFoljesedel.pro
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

HEADERS = prtfoljesedel.ui.h
SOURCES = main.cpp
OBJECTS = main.o \
		prtfoljesedel.o
FORMS = prtfoljesedel.ui
UICDECLS = prtfoljesedel.h
UICIMPLS = prtfoljesedel.cpp
SRCMOC   = moc_prtfoljesedel.cpp
OBJMOC = moc_prtfoljesedel.o
DIST	   = PrtFoljesedel.pro
QMAKE_TARGET = FSORDW
DESTDIR  = ../../bin/
TARGET   = ../../bin/FSORDW

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

Makefile: PrtFoljesedel.pro  $(QTDIR)/mkspecs/default/qmake.conf 
	$(QMAKE) -o Makefile PrtFoljesedel.pro
qmake: 
	@$(QMAKE) -o Makefile PrtFoljesedel.pro

dist: 
	@mkdir -p .tmp/FSORDW && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .tmp/FSORDW/ && $(COPY_FILE) --parents prtfoljesedel.ui.h .tmp/FSORDW/ && ( cd `dirname .tmp/FSORDW` && $(TAR) FSORDW.tar FSORDW && $(GZIP) FSORDW.tar ) && $(MOVE) `dirname .tmp/FSORDW`/FSORDW.tar.gz . && $(DEL_FILE) -r .tmp/FSORDW

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

prtfoljesedel.h: prtfoljesedel.ui 
	$(UIC) prtfoljesedel.ui -o prtfoljesedel.h

prtfoljesedel.cpp: prtfoljesedel.h prtfoljesedel.ui 
	$(UIC) prtfoljesedel.ui -i prtfoljesedel.h -o prtfoljesedel.cpp

prtfoljesedel.o: prtfoljesedel.cpp prtfoljesedel.ui.h \
		prtfoljesedel.h

moc_prtfoljesedel.o: moc_prtfoljesedel.cpp prtfoljesedel.h 

moc_prtfoljesedel.cpp: $(MOC) prtfoljesedel.h
	$(MOC) prtfoljesedel.h -o moc_prtfoljesedel.cpp

####### Install

install: all 

uninstall: 

