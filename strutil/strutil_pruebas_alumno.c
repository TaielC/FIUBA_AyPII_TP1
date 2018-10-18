#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "strutil.h"

int main(void){

	// char caden[1000];

	// scanf(" %[^\n]" , caden );

	char** str_separadas = split( "" , ' ' );

	int i = 0;
	while( str_separadas[i] ){
		printf("%s\n", str_separadas[i] );
		i++;
	}

	char* cadena =  join( str_separadas , ' ' );

	free(cadena);
	free_strv( str_separadas );
}