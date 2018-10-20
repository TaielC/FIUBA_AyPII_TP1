CC 		= gcc
CFLAGS 	= -g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
VFLAGS 	= --leak-check=full --track-origins=yes --show-reachable=yes 

strutil: strutil_pruebas_alumno.c strutil.c
	$(CC)  $(CFLAGS) strutil_pruebas_alumno.c strutil.c -o strutil.exe

run: strutil
	./strutil.exe

val: strutil
	valgrind $(VFLAGS) ./strutil.exe

clean:
	rm -f *.o *.exe

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<
