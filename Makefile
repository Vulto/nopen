VERSION = 0.8
 PREFIX = /usr/local
 
NOPENLDLIBS =
NOPENOBJ = nopen.o spawn.c 
BIN = nopen

all: $(BIN)

nopen: $(NOPENOBJ)
	$(CC) $(CFLAGS) -o $@ $(NOPENOBJ) $(LDFLAGS) $(NOPENLDLIBS)

dprintf.o: util.h
nopen.o: arg.h config.h util.h

install: all
	cp -p nopen $(DESTDIR)$(PREFIX)/bin
