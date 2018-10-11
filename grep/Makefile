CC = gcc
CFLAGS = -g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes= ../gitignore/

grep: grep.c cola.o
	gcc $(CFLAGS) grep.c cola.o -o grep.exe

run: grep
	./grep.exe

valgrind: grep
	valgrind $(VFLAGS) grep.exe

clean:
	rm -f *.o *.exe

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<
