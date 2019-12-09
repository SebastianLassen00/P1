CC = gcc
CFILES = $(wildcard src/*.c)
HFILES = $(wildcard include/*.h)

INCLUDE = -Iinclude
BIN = bin
PROGRAM_NAME = prog

$(BIN)/$(PROGRAM_NAME):  $(HFILES)
	$(CC) $(INCLUDE) $(CFILES) -o $@

.PHONY: clean print

clean: 
	rm *.o *.exe *.out
