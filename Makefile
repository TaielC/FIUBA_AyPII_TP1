CC = gcc
CFLAGS = -g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes 

PADRON = 102510

strutil: strutil_pruebas_alumno.c strutil.o
	$(CC) $(CFLAGS) strutil_pruebas_alumno.c strutil.o -o strutil

run_strutil: strutil
	./strutil

val_strutil: strutil
	valgrind $(VFLAGS) ./strutil

clean:
	rm -f *.o $(EXEC_S)

zip:
	zip $(PADRON).zip 

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<
