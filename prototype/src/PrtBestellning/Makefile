#############################################################################
# Makefile for building: ../../bin/PRTINKW
# Generated by qmake (1.04a) (Qt 3.1.1) on: Mon Nov 15 05:40:53 2004
# Project:  PrtBestellning.pro
# Template: app
# Command: $(QMAKE) -o Makefile PrtBestellning.pro
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

HEADERS = prtink.ui.h
SOURCES = main.cpp
OBJECTS = main.o \
		prtink.o
FORMS = prtink.ui
UICDECLS = prtink.h
UICIMPLS = prtink.cpp
SRCMOC   = moc_prtink.cpp
OBJMOC = moc_prtink.o
DIST	   = PrtBestellning.pro
QMAKE_TARGET = PRTINKW
DESTDIR  = ../../bin/
TARGET   = ../../bin/PRTINKW

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

Makefile: PrtBestellning.pro  $(QTDIR)/mkspecs/default/qmake.conf 
	$(QMAKE) -o Makefile PrtBestellning.pro
qmake: 
	@$(QMAKE) -o Makefile PrtBestellning.pro

dist: 
	@mkdir -p .tmp/PRTINKW && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .tmp/PRTINKW/ && $(COPY_FILE) --parents prtink.ui.h .tmp/PRTINKW/ && ( cd `dirname .tmp/PRTINKW` && $(TAR) PRTINKW.tar PRTINKW && $(GZIP) PRTINKW.tar ) && $(MOVE) `dirname .tmp/PRTINKW`/PRTINKW.tar.gz . && $(DEL_FILE) -r .tmp/PRTINKW

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

main.o: main.cpp prtink.h

prtink.h: prtink.ui 
	$(UIC) prtink.ui -o prtink.h

prtink.cpp: prtink.h prtink.ui 
	$(UIC) prtink.ui -i prtink.h -o prtink.cpp

prtink.o: prtink.cpp prtink.ui.h \
		prtink.h

moc_prtink.o: moc_prtink.cpp prtink.h 

moc_prtink.cpp: $(MOC) prtink.h
	$(MOC) prtink.h -o moc_prtink.cpp

####### Install

install: all 

uninstall: 

