CC = gcc
CFLAGS = -g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes 

PATH = ../gitignore/

grep: grep.c $(PATH)cola.o
	$(CC) $(CFLAGS) grep.c $(PATH)cola.o -o $(PATH)grep.exe

run: grep
	$(PATH)grep.exe

valgrind: grep
	valgrind $(VFLAGS) $(PATH)grep.exe

clean:
	rm -f $(PATH)*.o $(PATH)*.exe

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<
