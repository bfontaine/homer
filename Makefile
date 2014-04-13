# Homer Makefile

CC        ?= gcc
PREFIX    ?= /usr/local
BINPREFIX ?= $(PREFIX)/bin
MANPREFIX ?= $(PREFIX)/share/man/man1

SRC:=src
TESTS_RUNNER=./test/test.sh

SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:.c=.o)

MANS=$(wildcard man/*.md)
MAN_PAGES=$(MANS:.md=.1)

BIN:=homer

CFLAGS=-Wall -Wextra -Wundef -Wpointer-arith -std=gnu99
LDFLAGS=-lm

CPPCHECK_VER:=$(shell cppcheck --version 2>/dev/null)
ifdef CPPCHECK_VER
CPPCHECK=cppcheck \
	--enable=warning,style \
	--language=c -q
else
CPPCHECK=\#
endif

.PHONY: all clean docs test test-install install uninstall

all: $(BIN) docs

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ -c $<

docs: $(MAN_PAGES)

man/%.1: man/%.md
	ronn -rw --manual "Homer Manual" --pipe $< > $@

clean:
	find . -name '*.o' -delete
	rm -f $(BIN)
	rm -rf *.tmp
	rm -f man/*.1

test: $(BIN)
	@# avoid a failed build because cppcheck doesn't exist or is a wrong
	@# version
	$(CPPCHECK) $(SRC) || true
	@HOMER=$${PWD}/$(BIN) $(TESTS_RUNNER)

test-install:
	@# this is used on CI server. 'homer' has been installed just before so
	@# we don't have to depend on the 'install' target here.
	@HOMER=$(BINPREFIX)/$(BIN) $(TESTS_RUNNER)

install: $(BIN) docs
	@mkdir -p $(BINPREFIX)
	@mkdir -p $(MANPREFIX)
	cp -f $(BIN) $(BINPREFIX)/$(BIN)
	cp -f man/*.1 $(MANPREFIX)/

uninstall:
	rm -f $(BINPREFIX)/$(BIN)
	$(foreach MAN, $(MAN_PAGES), \
		rm -f $(MANPREFIX)/$(notdir $(MAN)))
