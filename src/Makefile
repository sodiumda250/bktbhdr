#!/usr/bin/make -f
# $Id: Makefile,v 1.2 2005/05/30 02:27:57 woods Exp $

MAJOR = 0
MINOR = 0
TEENY = 1

COPYRIGHT = '"Copyright (C) 2005 woods"'

RELEASE_VERSION = $(MAJOR).$(MINOR).$(TEENY)

TARGET = bktbhdr.dll
OBJS = bktbhdr.$(OBJ) PluginSDK/BeckyAPI.$(OBJ) \
	title.$(OBJ) \
	hookproc.$(OBJ) dialog.$(OBJ)
RESOBJS = bktbhdr_res.$(OBJ)
LIBS = 
SRCS = $(OBJS:.$(OBJ)=.cpp)
HDRS = bktbhdr.h hookproc.h dialog.h

# Suffix
OBJ = o
#OBJ= obj # for bcc/cl(?)

# Commands
MAKE = make
CC = g++
LD = g++
RM = rm -f
CP = cp -f
STRIP = strip
MKDIR = mkdir -p
ZIP = zip
LHA = lha
TOUCH = touch
FIND = find
INSTALL = install

# Compile and Link option
CFLAGS = -g -O -Wall -pipe -mno-cygwin -I/usr/inlcude/w32api \
 -DRELEASE_VERSION=\"$(RELEASE_VERSION)\" \
 -DMAJOR=$(MAJOR) -DMINOR=$(MINOR) -DTEENY=$(TEENY) \
 -DCOPYRIGHT=$(COPYRIGHT)
LDFLAGS = -pipe -Wl,--enable-stdcall-fixup -mno-cygwin -mwindows -mingw \
 -mdll -mshared \
 -L/usr/lib/w32api

INSTALLPATH = /cygdrive/c/Becky!/`whoami`/Plugins
INSTALLNAME = bktbhdr.dll

DOCDIR = doc

RELEASE_DIR = bktbhdr$(RELEASE_VERSION)

all: $(TARGET)

install: all
	$(MKDIR) $(INSTALLPATH)
	$(INSTALL) -s -p $(TARGET) $(INSTALLPATH)/$(INSTALLNAME)

deinstall:
	$(RM) -f $(INSTALLPATH)/$(INSTALLNAME)

clean:
	$(RM) $(OBJS) $(RESOBJS) exports.$(OBJ) bktbhdr.lib bktbhdr.res
	$(RM) -r $(RELEASE_DIR) release
	if [ -d test ]; then (cd test; $(MAKE) clean); fi
	if [ -d exe ]; then (cd exe; $(MAKE) clean); fi

test: all
	if [ -d test ]; then (cd test; $(MAKE) all); fi
	if [ -d exe ]; then (cd exe; $(MAKE) all); fi

testrun: test
	if [ -f exe/shhdr01.exe ]; then exe/shhdr01.exe; fi

tags: $(SRCS) $(HDRS)
	ctags $(SRCS) $(HDRS)

strip:
	$(STRIP) $(TARGET)

debug: install
	./b2.sh

cleanall: clean
	if [ -d test ]; then (cd test; $(MAKE) cleanall); fi
	if [ -d exe ]; then (cd exe; $(MAKE) cleanall); fi
	$(RM) $(TARGET) bktbhdr$(RELEASE_VERSION).lzh bktbhdr$(RELEASE_VERSION).zip tags release $(RELEASE_DIR)
	$(RM) -r $(DOCDIR)

release: $(TARGET)
	$(MKDIR) $(RELEASE_DIR)
	$(MKDIR) $(RELEASE_DIR)/src
	$(MKDIR) $(RELEASE_DIR)/src/PlugInSDK
	$(INSTALL) -p -s $(TARGET) $(RELEASE_DIR)
	$(CP) bktbhdr.txt $(RELEASE_DIR)
	$(CP) *.c* *.h *.def *.rc Makefile bktbhdr.doxygen $(RELEASE_DIR)/src
	$(CP) PlugInSDK/*.* $(RELEASE_DIR)/src/PlugInSDK
	$(FIND) $(RELEASE_DIR) -name '*.$(OBJ)' -exec rm -f {} \;
	$(ZIP) -9 -v -r bktbhdr$(RELEASE_VERSION).zip $(RELEASE_DIR)
	$(LHA) av bktbhdr$(RELEASE_VERSION).lzh $(RELEASE_DIR)
	$(RM) bktbhdr$(RELEASE_VERSION).bak
	$(TOUCH) release

docs:
	doxygen bktbhdr.doxygen

doc: docs

$(TARGET): $(OBJS) $(RESOBJS) bktbhdr.def
	dlltool -d bktbhdr.def -e exports.$(OBJ) -l bktbhdr.lib $(OBJS)
	$(LD) $(LDFLAGS) -o bktbhdr.dll exports.$(OBJ) $(OBJS) $(RESOBJS) $(LIBS)

PluginSDK/BeckyAPI.$(OBJ): PluginSDK/BeckyAPI.cpp PluginSDK/BeckyAPI.h
	$(CC) -c -o PluginSDK/BeckyAPI.$(OBJ) $(CFLAGS) PluginSDK/BeckyAPI.cpp

bktbhdr_res.$(OBJ): bktbhdr.res
	windres -v -i bktbhdr.res -o bktbhdr_res.$(OBJ) --language=00000411

bktbhdr.res: bktbhdr.rc Makefile
	rc /r /dMAJOR=$(MAJOR) /dMINOR=$(MINOR) /dTEENY=$(TEENY) /dRELEASE_VERSION='"$(RELEASE_VERSION)\0"' /dVERSION_STR='"bktbhdr version $(RELEASE_VERSION)"' /dCOPYRIGHT=$(COPYRIGHT) bktbhdr.rc
#windres -v -i shhdr01.rc -o shhdr01.res --language=00000411 -DMAJOR=$(MAJOR) -DMINOR=$(MINOR) -DTEENY=$(TEENY)
#nkf -S --utf16 shhdr01.rc | windres -v --input-format=rc -o shhdr01.res --language=00000411

.cpp.$(OBJ):
	$(CC) -c $(CFLAGS) $<

bktbhdr.h: PlugInSDK/BeckyAPI.h
	$(TOUCH) -c bktbhdr.h

bktbhdr.$(OBJ): bktbhdr.cpp bktbhdr.h resource.h hookproc.h

hookproc.$(OBJ): hookproc.cpp hookproc.h

dialog.$(OBJ): dialog.cpp dialog.h bktbhdr.h
