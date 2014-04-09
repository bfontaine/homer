# Homer Makefile

SRC:=src

TARGET:=homer

CC:=gcc
CFLAGS=-Wall -Wextra -Wundef -Wpointer-arith -std=c89 -I$(SRC)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)/cli.o $(SRC)/daemon.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ -c $<
