
all: kiki.ko


%.ko: $(shell find src -name "*.c")
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd)/src modules && cp src/$@ $@


install: kiki.ko
	install -m 644 $< /lib/modules/$(shell uname -r)/kernel/drivers/
	install -m 644 conf/kiki.conf /etc/modules-load.d/
	install -m 644 src/kiki.h /usr/include
	depmod

uninstall:
	rm -f /usr/include/kiki.h
	rm -f /etc/modules-load.d/kiki.conf
	rm -f /lib/modules/$(shell uname -r)/kernel/drivers/char/kiki.ko.gz
	depmod


load: kiki.ko
	sudo insmod $<

unload:
	sudo rmmod kiki

.PHONY reload:
	make unload
	make load


clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd)/src clean
	rm -f kiki.ko
