CC = gcc
CFLAGS = -g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes 

PATH = ../gitignore/

strutil: strutil_pruebas_alumno.c $(PATH)strutil.o
	$(CC) $(CFLAGS) strutil.c $(PATH)strutil.o -o $(PATH)strutil.exe

run: strutil
	$(PATH)strutil.exe

val: strutil
	valgrind $(VFLAGS) $(PATH)strutil.exe

clean:
	rm -f $(PATH)*.o $(PATH)*.exe

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<
