# Cross compilation Makefile for ARM
KERN_SRC= /home/raj/linux-3.14.56
obj-m = memory.o
 
all: 
	make -C $(KERN_SRC) ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-  M=$(PWD) modules

clean:
	make -C $(KERN_SRC) ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-  M=$(PWD) clean




