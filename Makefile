PREFIX = /usr/local

all:
	$(CC) -O3 -Wall -Wextra -Wpedantic -o imeigen imeigen.c

install:
	install -D -m 0755 imeigen $(DESTDIR)$(PREFIX)/bin/imeigen
	install -D -m 0755 ig-crack $(DESTDIR)$(PREFIX)/sbin/ig-crack

clean:
	-rm -f imeigen

distclean: clean

uninstall:
	-rm -f $(DESTDIR)$(PREFIX)/bin/imeigen
	-rm -f $(DESTDIR)$(PREFIX)/sbin/ig-crack

.PHONY: all install clean distclean uninstall
