CC = gcc
CFILES = $(wildcard src/*.c)
HFILES = $(wildcard include/*.h)

INCLUDE = -Iinclude
LIBS = -lm
BIN = bin
PROGRAM_NAME = prog

$(BIN)/$(PROGRAM_NAME): $(CFILES) $(HFILES)
	$(CC) $(INCLUDE) $(LIBS) $(CFILES) -o $@ 

.PHONY: clean print

clean: 
	rm *.o *.exe *.out prog
