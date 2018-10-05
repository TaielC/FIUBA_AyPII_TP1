#include <stdio.h>

#include "testing.h"
#include "strutil.h"

int main(void){

	char** str_separadas = split( "hola,que,tal" , ',' );

	for( int i = 0 ; i < 3 ; i++ ){
		printf("%s\n", str_separadas[i] );
	}

	free_strv( str_separadas );
}