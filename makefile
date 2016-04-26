CC=gcc
CFLAGS=-Wall -std='gnu89' -pedantic

all: jarvis

jarvis:
	$(CC) $(CFLAGS) main.c -o jarvis

clean:
	rm jarvis
