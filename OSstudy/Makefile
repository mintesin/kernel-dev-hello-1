obj-m += intro_module.o
obj-m += info_timer.o
obj-m += hello_procs.o 
obj-m += assignment_one.o

PWD := $(CURDIR)
all:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
