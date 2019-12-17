CC = gcc
CFILES = $(wildcard src/*.c)
HFILES = $(wildcard include/*.h)

INCLUDE = -Iinclude
<<<<<<< HEAD
OPTIONS = -ansi -pedantic -Wall -lm
=======
LIBS = -lm
>>>>>>> 0b309d22632c48b58920ef6ec1624aa3c134af5a
BIN = bin
PROGRAM_NAME = prog

$(BIN)/$(PROGRAM_NAME): $(CFILES) $(HFILES)
<<<<<<< HEAD
	$(CC) $(INCLUDE) $(CFILES) -o $@ $(OPTIONS) 
=======
	$(CC) $(INCLUDE) $(LIBS) $(CFILES) -o $@ 
>>>>>>> 0b309d22632c48b58920ef6ec1624aa3c134af5a

.PHONY: clean print

clean: 
	rm *.o *.exe *.out prog
