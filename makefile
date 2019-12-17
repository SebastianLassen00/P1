CC = gcc
CFILES = $(wildcard src/*.c)
HFILES = $(wildcard include/*.h)

INCLUDE = -Iinclude -lm 
BIN = bin
PROGRAM_NAME = prog

$(BIN)/$(PROGRAM_NAME): $(CFILES) $(HFILES)
	$(CC) $(INCLUDE) $(CFILES) -o $@ 

.PHONY: clean print

clean: 
	rm *.o *.exe *.out prog
