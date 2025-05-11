KDIR := /usr/src/linux-source-5.15.0
PWD := $(shell pwd)

obj-m += cdev_driver.o

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean

