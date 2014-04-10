# Homer Makefile

CC     ?= gcc
PREFIX ?= /usr/local

SRC:=src
TESTS_RUNNER=./test/test.sh

BIN:=homer
TARGET_DIR=$(PREFIX)/bin
TARGET=$(TARGET_DIR)/$(BIN)

CFLAGS=-Wall -Wextra -Wundef -Wpointer-arith -std=gnu99 -I$(SRC)

CPPCHECK_VER:=$(shell cppcheck --version 2>/dev/null)
ifdef CPPCHECK_VER
CPPCHECK=cppcheck \
	--enable=warning,style \
	--language=c -q
else
CPPCHECK=\#
endif

.PHONY: all clean test test-install install uninstall

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
	@# avoid a failed build because cppcheck doesn't exist or is a wrong
	@# version
	$(CPPCHECK) $(SRC) || true
	@HOMER=$${PWD}/$(BIN) $(TESTS_RUNNER)

test-install:
	@# this is used on CI server. 'homer' has been installed just before so
	@# we don't have to depend on the 'install' target here.
	@HOMER=$(TARGET) $(TESTS_RUNNER)

install: $(TARGET)

uninstall:
	rm -f $(TARGET)
