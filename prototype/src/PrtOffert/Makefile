#############################################################################
# Makefile for building: ../../bin/PRTOFFW
# Generated by qmake (1.07a) (Qt 3.3.4) on: Sun Nov 19 11:55:35 2006
# Project:  PrtOffert.pro
# Template: app
# Command: $(QMAKE) -o Makefile PrtOffert.pro
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

HEADERS = frmprtoffert.ui.h
SOURCES = main.cpp
OBJECTS = main.o \
		frmprtoffert.o
FORMS = frmprtoffert.ui
UICDECLS = frmprtoffert.h
UICIMPLS = frmprtoffert.cpp
SRCMOC   = moc_frmprtoffert.cpp
OBJMOC = moc_frmprtoffert.o
DIST	   = PrtOffert.pro
QMAKE_TARGET = PRTOFFW
DESTDIR  = ../../bin/
TARGET   = ../../bin/PRTOFFW

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

Makefile: PrtOffert.pro  /usr/lib/qt3/mkspecs/default/qmake.conf /usr/lib/qt3/lib/libqt-mt.prl
	$(QMAKE) -o Makefile PrtOffert.pro
qmake: 
	@$(QMAKE) -o Makefile PrtOffert.pro

dist: 
	@mkdir -p .tmp/PRTOFFW && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .tmp/PRTOFFW/ && $(COPY_FILE) --parents frmprtoffert.ui.h .tmp/PRTOFFW/ && ( cd `dirname .tmp/PRTOFFW` && $(TAR) PRTOFFW.tar PRTOFFW && $(GZIP) PRTOFFW.tar ) && $(MOVE) `dirname .tmp/PRTOFFW`/PRTOFFW.tar.gz . && $(DEL_FILE) -r .tmp/PRTOFFW

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

main.o: main.cpp frmprtoffert.h

frmprtoffert.h: frmprtoffert.ui 
	$(UIC) frmprtoffert.ui -o frmprtoffert.h

frmprtoffert.cpp: frmprtoffert.h frmprtoffert.ui frmprtoffert.ui.h 
	$(UIC) frmprtoffert.ui -i frmprtoffert.h -o frmprtoffert.cpp

frmprtoffert.o: frmprtoffert.cpp frmprtoffert.h

moc_frmprtoffert.o: moc_frmprtoffert.cpp  frmprtoffert.h 

moc_frmprtoffert.cpp: $(MOC) frmprtoffert.h
	$(MOC) frmprtoffert.h -o moc_frmprtoffert.cpp

####### Install

install:  

uninstall:  

