CC = gcc
CFLAGS = -g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes 

PADRON = 102510

strutil: strutil_pruebas_alumno.c strutil.o
	$(CC) $(CFLAGS) strutil_pruebas_alumno.c strutil.o -o strutil.exe

run_strutil: strutil
	./strutil.exe

val_strutil: strutil
	valgrind $(VFLAGS) ./strutil.exe

grep: grep.c cola.o
	$(CC) $(CFLAGS) grep.c cola.o -o grep.exe

run_strutil: grep
	./grep.exe

val_strutil: grep
	valgrind $(VFLAGS) ./grep.exe

clean:
	rm -f *.o *.exe

zip:
	zip $(PADRON)-TP1.zip 

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<
