
ARCHIVOS = deps.mk dc.c strutil.c strutil.h grep.c pila.c pila.h cola.c cola.h 

dc.c: ../../dc/dc.c
	cp ../../dc/dc.c ./

strutil.c: ../../strutil/strutil.c
	cp ../../strutil/strutil.c ./

strutil.h: ../../strutil/strutil.h
	cp ../../strutil/strutil.h ./

grep.c: ../../grep/grep.c
	cp ../../grep/grep.c ./

zip: $(ARCHIVOS)
	zip 102510-TP1.zip $(ARCHIVOS) 