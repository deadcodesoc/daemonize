PREFIX=$(DESTDIR)/usr/local
BINDIR=$(PREFIX)/bin
MANDIR=$(PREFIX)/share/man

all: daemonize

daemonize: daemonize.c
	$(CC) daemonize.c -o daemonize

daemonize.ps: daemonize.1
	groff -mandoc $< > $@

install: daemonize daemonize.1
	install -m 755 daemonize $(BINDIR)
	install -m 644 daemonize.1 $(MANDIR)/man1

uninstall:
	rm -f $(BINDIR)/daemonize
	rm -f $(MANDIR)/man1/daemonize.1

clean:
	rm -f daemonize daemonize.pdf daemonize.ps *~
