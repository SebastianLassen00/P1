
CC = gcc
CFILES = $(wildcard src/*.c)
HFILES = $(wildcard include/*.h)
INCLUDE = -Iinclude
BIN = BIN

PROGRAM_NAME = PROG

$(BIN)/$(PROGRAM_NAME): $(CFILES) $(HFILES)
	$(CC) $(INCLUDE) $(CFILES) -o $@

.PHONY: clean

clean: 
	rm bin/*