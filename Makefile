# Homer Makefile

CC     ?= gcc
PREFIX ?= /usr/local

SRC:=src
TESTS_RUNNER=./test/test.sh

BIN:=homer
TARGET_DIR=$(PREFIX)/bin
TARGET=$(TARGET_DIR)/$(BIN)

CFLAGS=-Wall -Wextra -Wundef -Wpointer-arith -std=gnu99 -I$(SRC)

.PHONY: all clean test ci install uninstall

all: $(BIN)

$(BIN): $(SRC)/cli.o $(SRC)/daemon.o
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

$(TARGET): $(BIN) $(TARGET_DIR)
	cp -f $(BIN) $(TARGET)

%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	find . -name '*.o' -delete
	rm -f $(BIN) *.tmp

test: $(BIN)
	@HOMER=$${PWD}/$(BIN) $(TESTS_RUNNER)

test-install:
	@# this is used on CI server. 'homer' has been installed just before so
	@# we don't have to depend on the 'install' target here.
	@HOMER=$(TARGET) $(TESTS_RUNNER)

install: $(TARGET)

uninstall:
	rm -f $(TARGET)
