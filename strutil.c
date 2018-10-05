#include <stdlib.h>
#include <string.h>

#include "strutil.h"

int split_identificar_cantidad( const char* cadena , char separador ){
	int cant_separar = 1;
	int contador = 0;
	while( cadena[contador] != '\0' ){
		if( cadena[contador] == separador )
			cant_separar++;
		contador++;
	}
	//En caso de que el separador sea '\0' se verá en la posición final de la cadena
	if( cadena[contador] == separador )
			cant_separar++;

	return cant_separar;
}

int* split_identificar_posiciones( const char* cadena , char separador , int cant_separar){

	int* posiciones = malloc( sizeof(int) * cant_separar );
	int contador = 0;
	int pos_encontradas = 0;
	while( pos_encontradas <= cant_separar ){
		if( cadena[contador] == separador ){
			posiciones[pos_encontradas] = contador;
			pos_encontradas++;
		}
		contador++;
	}

	return posiciones;
}

char** split( const char* cadena , char separador ){

	int cant_separar = split_identificar_cantidad( cadena , separador );
	char** separados = malloc( sizeof(char*) * cant_separar +1 );

	int* pos_separar = split_identificar_posiciones( cadena , separador , cant_separar);

	for( size_t i = 0 ; i < cant_separar ; i++ ){
		separados[i] = malloc( sizeof(char) * pos_separar[i] +1 );
		strncpy( separados[i] , &cadena[pos_separar[i]] , pos_separar[i] );
		separados[i][pos_separar[i]+1] = '\0';
	}

	separados[cant_separar+1] = NULL;

	return separados;
}

void free_strv( char** arr_cadenas ){
	int contador = 0;
	while( arr_cadenas[contador] != NULL ){
		free( arr_cadenas[contador] );
		contador++;
	}
	free( arr_cadenas );
}


char* join( const char** arr_cadenas , char separador ); 
