CC = gcc
CFILES = $(wildcard src/*.c)
HFILES = $(wildcard include/*.h)

INCLUDE = -Iinclude
BIN = bin
PROGRAM_NAME = prog

$(BIN)/$(PROGRAM_NAME): $(CFILES) $(HFILES)
	$(CC) $(INCLUDE) $(CFILES) -o $@ -lm 

.PHONY: clean print

clean: 
	rm *.o *.exe *.out prog
