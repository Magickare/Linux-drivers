obj-m += major_minor_driver.o

KDIR = /lib/modules/$(shell uname -r)/build
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

