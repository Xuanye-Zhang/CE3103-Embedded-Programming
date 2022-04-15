obj-m := gpio_lkm.o

all:
	make -C /usr/src/linux-headers-`uname -r` M=`pwd` modules

clean:
	rm -f *.ko
	rm -f *.mod*
	rm -f *.o
	rm -f modules.order
	rm -f Module.symvers
