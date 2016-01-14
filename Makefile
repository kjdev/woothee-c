CFLAGS := -g -O3 -Wall -Wextra -Wno-unused-parameter
PREFIX := /usr/local
BINDIR := $(PREFIX)/bin
INCLUDEDIR := $(PREFIX)/include
LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
  LIBDIR := $(PREFIX)/lib64
else
  LIBDIR := $(PREFIX)/lib
endif


CFLAGS := $(CFLAGS) -Isrc -fPIC
LDFLAGS := $(LDFLAGS) -lpcre
SRCS := \
	src/woothee.c \
	src/util.c \
	src/crawler.c \
	src/browser.c \
	src/os.c \
	src/mobilephone.c \
	src/appliance.c \
	src/misc.c
OBJS := $(SRCS:%.c=%.o)

ifdef COVERAGE
CFLAGS := $(CFLAGS) -coverage
LDFLAGS := $(LDFLAGS) -lgcov
endif

.PHONY: all test clean


all: libwoothee.so libwoothee.a woothee

libwoothee.so: libwoothee.so.1.0.0
	ln -f -s $^ $@

libwoothee.so.1.0.0: $(OBJS)
	$(CC) -Wl,-soname,$(@F) -shared $^ $(LDFLAGS) -o $@

libwoothee.a: $(OBJS)
	$(AR) rcs libwoothee.a $^


woothee: bin/woothee.o $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@


install:
	install -m755 -d $(DESTDIR)$(LIBDIR)
	install -m755 -d $(DESTDIR)$(BINDIR)
	install -m755 -d $(DESTDIR)$(INCLUDEDIR)

	install -m644 libwoothee.a $(DESTDIR)$(LIBDIR)
	install -m755 libwoothee.so.1.0.0 $(DESTDIR)$(LIBDIR)
	ln -f -s libwoothee.so.1.0.0 $(DESTDIR)$(LIBDIR)/libwoothee.so.1
	ln -f -s libwoothee.so.1.0.0 $(DESTDIR)$(LIBDIR)/libwoothee.so

	install -m755 woothee $(DESTDIR)$(BINDIR)

	install -m755 -d $(DESTDIR)$(INCLUDEDIR)/woothee
	install -m644 src/*.h $(DESTDIR)$(INCLUDEDIR)/woothee

	sed -e "s#@prefix@#$(PREFIX)#" -e "s#@libdir@#$(LIBDIR)#" woothee.pc > $(DESTDIR)$(LIBDIR)/pkgconfig/woothee.pc

test: woothee
	python test/runner.py

clean:
	-rm -f bin/*.o $(OBJS)
	-rm -f libwoothee.so* libwoothee.a
	-rm -f woothee
	-rm -f bin/*.gc* src/*.gc* *.gcov


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
