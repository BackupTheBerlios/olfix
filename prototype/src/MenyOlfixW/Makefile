#############################################################################
# Makefile for building: ../../bin/OLFIXW
# Generated by qmake (1.07a) (Qt 3.3.4) on: Wed Jan  4 08:38:41 2006
# Project:  MenyOlfixW.pro
# Template: app
# Command: $(QMAKE) -o Makefile MenyOlfixW.pro
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

HEADERS = frmolfix.ui.h
SOURCES = main.cpp
OBJECTS = main.o \
		frmolfix.o
FORMS = frmolfix.ui
UICDECLS = frmolfix.h
UICIMPLS = frmolfix.cpp
SRCMOC   = moc_frmolfix.cpp
OBJMOC = moc_frmolfix.o
DIST	   = MenyOlfixW.pro
QMAKE_TARGET = OLFIXW
DESTDIR  = ../../bin/
TARGET   = ../../bin/OLFIXW

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

Makefile: MenyOlfixW.pro  /usr/lib/qt3/mkspecs/default/qmake.conf /usr/lib/qt3/lib/libqt-mt.prl
	$(QMAKE) -o Makefile MenyOlfixW.pro
qmake: 
	@$(QMAKE) -o Makefile MenyOlfixW.pro

dist: 
	@mkdir -p .tmp/OLFIXW && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .tmp/OLFIXW/ && $(COPY_FILE) --parents frmolfix.ui.h .tmp/OLFIXW/ && ( cd `dirname .tmp/OLFIXW` && $(TAR) OLFIXW.tar OLFIXW && $(GZIP) OLFIXW.tar ) && $(MOVE) `dirname .tmp/OLFIXW`/OLFIXW.tar.gz . && $(DEL_FILE) -r .tmp/OLFIXW

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

frmolfix.cpp: frmolfix.h frmolfix.ui frmolfix.ui.h 
	$(UIC) frmolfix.ui -i frmolfix.h -o frmolfix.cpp

frmolfix.o: frmolfix.cpp frmolfix.ui.h \
		frmolfix.h

moc_frmolfix.o: moc_frmolfix.cpp  frmolfix.h 

moc_frmolfix.cpp: $(MOC) frmolfix.h
	$(MOC) frmolfix.h -o moc_frmolfix.cpp

####### Install

install:  

uninstall:  

