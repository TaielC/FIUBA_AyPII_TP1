#include <stdio.h>
#include <stdlib.h>

#include "testing.h"
#include "strutil.h"

int main(void){

	char** str_separadas = split( NULL , ',' );

	for( int i = 0 ; i < 0 ; i++ ){
		printf("%s\n", str_separadas[i] );
	}

	char* cadena =  join( (const char**)str_separadas , ',' );

	printf("%p\n", cadena );

	// free(cadena);
	free_strv( str_separadas );
}