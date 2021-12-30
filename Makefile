ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m   := my_module.o
ccflags-y += -g
else
# normal makefile
KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD
	cp ./my_module.ko /home/yevhenii/Desktop/lab4/busybox/_install/
	cp my_module.ko my_module.ko.unstripped
	$(CROSS_COMPILE)strip -g my_module.ko
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
endif
