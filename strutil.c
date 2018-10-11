#include <stdlib.h>
#include <string.h>

#include "strutil.h"


/* ------------ Funciónes auxiliares a split ------------ */

// Devuelve la cantidad de separadores en la cadena a separar,
// si la cadena no debe ser separada devuelve 1.
int split_identificar_cantidad( const char* cadena , char separador ){
	int cant_separar = 1;
	int contador = 0;
	while( cadena[contador] != '\0' ){
		if( cadena[contador] == separador )
			cant_separar++;
		contador++;
	}

	return cant_separar;
}

// Devuelve un vector dinámico con la posición de cada separador en la cadena a separar
int* split_identificar_posiciones( const char* cadena , char separador , int cant_separar){

	int* posiciones = malloc( sizeof(int) * (cant_separar +1) );
	int contador = 0;
	int pos_encontradas = 1;

	posiciones[0] = 0;
	while( cadena[contador] != '\0' ){
		if( cadena[contador] == separador ){
			posiciones[pos_encontradas] = contador+1;
			pos_encontradas++;
		}
		contador++;
	}
	posiciones[cant_separar] = contador+1;

	return posiciones;
}

/* ============ Función split ============ */

char** split( const char* cadena , char separador ){
	if( !cadena ) return NULL;

	int cant_separar = split_identificar_cantidad( cadena , separador );
	int* posiciones_separar = split_identificar_posiciones( cadena , separador , cant_separar);

	char** arr_cadenas = malloc( sizeof(char*)* (cant_separar +1) );
	
	int largo_actual;
	for( size_t i = 0 ; i < cant_separar ; i++ ){
		largo_actual = posiciones_separar[i+1] - posiciones_separar[i];
		arr_cadenas[i] = malloc( sizeof(char) * largo_actual );
		strncpy( arr_cadenas[i] , &cadena[posiciones_separar[i]] , largo_actual );
		arr_cadenas[i][largo_actual-1] = '\0';
	}

	arr_cadenas[cant_separar] = NULL;

	free( posiciones_separar );
	return arr_cadenas;
}

/* ============ Función join ============ */

char* join( const char** arr_cadenas , char separador ){
	if( !arr_cadenas ) return NULL;

	int largo_total = 0;
	int cont = 0;
	while( arr_cadenas[cont] != NULL){
		largo_total += ( (int)strlen( arr_cadenas[cont] ) +1);
		cont++;
	}

	char* cadena = malloc( sizeof(char) * largo_total );
	cadena[0] = '\0';

	int cant_cadenas = cont;
	cont = 0;
	while( arr_cadenas[cont] != NULL){
		strncat( cadena , arr_cadenas[cont] , strlen( arr_cadenas[cont] ) );
		if( cont != cant_cadenas-1 )
			strncat( cadena , &separador , 1 );	
		cont++;
	}

	return cadena;
}

void free_strv( char** arr_cadenas ){
	if( !arr_cadenas ) return
		;

	int contador = 0;
	while( arr_cadenas[contador] != NULL ){
		free( arr_cadenas[contador] );
		contador++;
	}
	free( arr_cadenas );
}
