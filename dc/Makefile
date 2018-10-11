CC = gcc
CFLAGS = -g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes 

PATH = ../gitignore/

dc: dc.c $(PATH)pila.o
	$(CC) $(CFLAGS) dc.c $(PATH)pila.o -o $(PATH)dc.exe

run: dc
	$(PATH)dc.exe

val: dc
	valgrind $(VFLAGS) $(PATH)dc.exe

clean:
	rm -f $(PATH)*.o $(PATH)*.exe

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<
