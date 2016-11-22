#
# Makefile for the Bluetooth device driver.
#

O_TARGET := bt.o
O_OBJS   =  bluetooth.o btdebug.o btmem.o hci.o l2cap.o rfcomm.o sdp.o tcs.o bt_proc.o hci_vendor.o l2cap_con.o sec_client.o l2cap_sec.o rfcomm_sec.o
M_OBJS   = $(O_TARGET)

ifeq ($(TOPDIR)/Rules.make,$(wildcard $(TOPDIR)/Rules.make))

include $(TOPDIR)/Rules.make

else

MODFLAGS = -DMODVERSIONS -include /usr/include/linux/modversions.h
CFLAGS   = -D__KERNEL__ -DMODULE -I../include -Wall -Wstrict-prototypes -O2 -fomit-frame-pointer -fno-strength-reduce $(MODFLAGS)

all:	$(O_TARGET)

$(O_TARGET):	$(O_OBJS)
	ld -r -o $@ $^

install:	all

clean:
	rm -f *.o core

endif
