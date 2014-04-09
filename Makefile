# Homer Makefile

CC     ?= gcc
PREFIX ?= /usr/local

SRC:=src

BIN:=homer

CFLAGS=-Wall -Wextra -Wundef -Wpointer-arith -std=c89 -I$(SRC)

.PHONY: all clean install uninstall

all: $(BIN)

$(BIN): $(SRC)/cli.o $(SRC)/daemon.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	find . -name '*.o' -delete
	rm -f $(BIN)

install: $(BIN)
	mkdir -p $(PREFIX)/bin
	cp -f $(BIN) $(PREFIX)/bin/$(BIN)

uninstall:
	rm -f $(PREFIX)/bin/$(BIN)
