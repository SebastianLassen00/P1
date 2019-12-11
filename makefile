
CC = gcc
CFILES = $(wildcard src/*.c)
HFILES = $(wildcard include/*.h)
INCLUDE = -Iinclude
CFLAGS = -ansi -Wall -pedantic
BIN = bin

PROGRAM_NAME = PROG

$(BIN)/$(PROGRAM_NAME): $(CFILES) $(HFILES)
	$(CC) $(CFLAGS) $(INCLUDE) $(CFILES) -o $@

.PHONY: clean

clean: 
	rm bin/*.exe bin/*.out bin/*.o
