CC = gcc
CFLAGS = -g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes 

dc: dc.c pila.o ../strutil/strutil.o
	$(CC) $(CFLAGS) dc.c pila.o ../strutil/strutil.o -o dc.exe

run: dc
	./dc.exe

valgrind: dc
	valgrind $(VFLAGS) ./dc.exe

gdb:
	gdb -tui ./dc.exe

clean:
	rm -f *.o *.exe

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<
