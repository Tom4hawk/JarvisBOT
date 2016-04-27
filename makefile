CC=gcc
CFLAGS=-Wall -std='gnu89' -pedantic

all: example

example: example.o jarvis.o
	$(CC) example.o jarvis.o -o jarvis

example.o: example.c
	$(CC) $(CFLAGS) -c example.c

jarvis.o: jarvis.c
	$(CC) $(CFLAGS) -c jarvis.c

clean:
	rm jarvis
