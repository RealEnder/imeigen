PREFIX = /usr/local

all:
	$(CC) -O3 -Wall -o imeigen imeigen.c

install:
	install -D -m 0755 imeigen $(DESTDIR)$(PREFIX)/bin/imeigen

clean:
	-rm -f imeigen

distclean: clean

uninstall:
	-rm -f $(DESTDIR)$(PREFIX)/bin/imeigen

.PHONY: all install clean distclean uninstall
