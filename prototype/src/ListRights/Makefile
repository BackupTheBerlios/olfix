#############################################################################
# Makefile for building: ../../bin/LSTRGTW
# Generated by qmake (1.04a) (Qt 3.1.1) on: Mon Nov 15 05:23:00 2004
# Project:  ListRights.pro
# Template: app
# Command: $(QMAKE) -o Makefile ListRights.pro
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

HEADERS = getuser.h
SOURCES = main.cpp
OBJECTS = main.o \
		frmlistrights.o
FORMS = frmlistrights.ui
UICDECLS = frmlistrights.h
UICIMPLS = frmlistrights.cpp
SRCMOC   = moc_frmlistrights.cpp
OBJMOC = moc_frmlistrights.o
DIST	   = ListRights.pro
QMAKE_TARGET = LSTRGTW
DESTDIR  = ../../bin/
TARGET   = ../../bin/LSTRGTW

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

Makefile: ListRights.pro  $(QTDIR)/mkspecs/default/qmake.conf 
	$(QMAKE) -o Makefile ListRights.pro
qmake: 
	@$(QMAKE) -o Makefile ListRights.pro

dist: 
	@mkdir -p .tmp/LSTRGTW && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .tmp/LSTRGTW/ && $(COPY_FILE) --parents frmlistrights.ui.h .tmp/LSTRGTW/ && ( cd `dirname .tmp/LSTRGTW` && $(TAR) LSTRGTW.tar LSTRGTW && $(GZIP) LSTRGTW.tar ) && $(MOVE) `dirname .tmp/LSTRGTW`/LSTRGTW.tar.gz . && $(DEL_FILE) -r .tmp/LSTRGTW

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

main.o: main.cpp frmlistrights.h

frmlistrights.h: frmlistrights.ui 
	$(UIC) frmlistrights.ui -o frmlistrights.h

frmlistrights.cpp: frmlistrights.h frmlistrights.ui 
	$(UIC) frmlistrights.ui -i frmlistrights.h -o frmlistrights.cpp

frmlistrights.o: frmlistrights.cpp frmlistrights.ui.h \
		frmlistrights.h

moc_frmlistrights.o: moc_frmlistrights.cpp frmlistrights.h 

moc_frmlistrights.cpp: $(MOC) frmlistrights.h
	$(MOC) frmlistrights.h -o moc_frmlistrights.cpp

####### Install

install: all 

uninstall: 

