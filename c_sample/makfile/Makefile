include $(APPS)/Rules.elinux

#SUBDIRS = src libs apps

INSTDIR = /usr/local/bin
CONFDIR = /etc

all:
	make -C src
	make -C libs install
	make -C apps
	make -C apps/sdp_server sdp_user

install:
	install apps/btd/btd $(INSTDIR)
	install apps/userstack/btduser $(INSTDIR)
	install apps/sdp_server/sdp_server $(INSTDIR)
	install apps/sdp_server/sdp_user $(INSTDIR)
	install apps/sdp_server/sdp.xml $(CONFDIR)

devs:
	mknod -m 0666 /dev/ttyBT0 c 124 0
	mknod -m 0666 /dev/ttyBT1 c 124 1
	mknod -m 0666 /dev/ttyBT2 c 124 2
	mknod -m 0666 /dev/ttyBT3 c 124 3
	mknod -m 0666 /dev/ttyBT4 c 124 4
	mknod -m 0666 /dev/ttyBT5 c 124 5
	mknod -m 0666 /dev/ttyBT6 c 124 6
	mknod -m 0666 /dev/ttyBTC c 124 7
	chgrp tty /dev/ttyBT*
