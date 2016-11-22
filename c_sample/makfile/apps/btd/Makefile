# $Id: Makefile,v 1.5 2000/12/14 16:40:31 pkj Exp $

ifdef APPS
USE_UCLIBC = 1
include $(APPS)/Rules.elinux
endif

PROGS     = btd

INSTDIR   = $(prefix)/bin/
INSTMODE  = 0755
INSTOWNER = root
INSTGROUP = root

SRCS      = btd.c

OBJS      = btd.o

LDLIBS += -lreadline -ltermcap
CFLAGS += -I$(prefix)/include

all:	$(PROGS)

install:	$(PROGS)
	$(INSTALL) -d $(INSTDIR)
	$(INSTALL) -m $(INSTMODE) -o $(INSTOWNER) -g $(INSTGROUP) $(PROGS) $(INSTDIR)

clean:
	rm -f $(PROGS) *.o core

depend:
	makedepend -Y $(SRCS) 2>/dev/null

# -------------------------------------------------------------------------
# The following is used to automatically generate dependencies.
# DO NOT DELETE

btd.o: btd.h
