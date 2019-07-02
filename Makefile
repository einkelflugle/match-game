CC=gcc
CFLAGS=-std=c99 -Wall -Werror -pedantic

.DEFAULT_GOAL := all

.PHONY: all debug clean

all: match

debug: CFLAGS += -g -DDEBUG
debug: clean all

clean:
	rm *.o match

match.o: match.c
	$(CC) $(CFLAGS) -c match.c -o match.o

errorCodes.o: errorCodes.c
	$(CC) $(CFLAGS) -c errorCodes.c -o errorCodes.o

grid.o: grid.c
	$(CC) $(CFLAGS) -c grid.c -o grid.o

gridFile.o: gridFile.c
	$(CC) $(CFLAGS) -c gridFile.c -o gridFile.o

match: match.o errorCodes.o grid.o gridFile.o
	$(CC) $(CFLAGS) match.o errorCodes.o grid.o gridFile.o -o match
