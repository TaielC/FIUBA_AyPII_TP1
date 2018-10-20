#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "strutil.h"

#define FIN_STRING '\0'

/* ------------ Funciónes auxiliares a split ------------ */

// Función auxiliar para el cálculo del largo de un cadenas
// Recibe un cadenas y devuelve su largo sin contar el caracter
// de fin de cadena ('\0')
int str_largo( const char* cadenas ){
	int contador = 0;
	while( cadenas[contador] != FIN_STRING )
		contador++;
	return contador;
}

// Función auxiliar de copia de un cadenas
// Recibe un cadenas destino, donde se copiará una cantidad largo
// del cadenas que se reciba de origen 
void str_copy( char* destino , const char* origen , int largo ){
	for( int i = 0 ; i < largo ; i++ )
		destino[i] = origen[i];
}

// Devuelve la cantidad de separadores en la cadena a separar,
// si la cadena no debe ser separada devuelve 1.
int split_identificar_cantidad( const char* cadena , char separador ){
	int cant_separar = 1;
	int contador = 0;
	while( cadena[contador] != FIN_STRING ){
		if( cadena[contador] == separador )
			cant_separar++;
		contador++;
	}

	return cant_separar;
}

// Devuelve un vector dinámico con la posición de cada
// separador de una cadena a separar
int* split_identificar_posiciones( const char* cadena , char separador , int cant_separar){

	int* posiciones = malloc( sizeof(int) * (cant_separar +1) );
	int contador = 0;
	int pos_encontradas = 1;

	posiciones[0] = 0;
	while( cadena[contador] != FIN_STRING ){
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

// Recibe una cadena y un caracter separador
// Devuelve un array de cadenas cada una formada por cada parte 
// de la cadena principal recibida que estuviera separada del resto 
// de la cadena por el caracter separador
char** split( const char* cadena , char separador ){
	if( !cadena ) return NULL;

	int cant_separar = split_identificar_cantidad( cadena , separador );
	int* posiciones_separar = split_identificar_posiciones( cadena , separador , cant_separar);

	char** arr_cadenas = malloc( sizeof(char*)* (cant_separar +1) );
	
	int largo_actual;
	for( size_t i = 0 ; i < cant_separar ; i++ ){

		largo_actual = posiciones_separar[i+1] - posiciones_separar[i];
		arr_cadenas[i] = malloc( sizeof(char) * largo_actual );

		str_copy( arr_cadenas[i] , &cadena[posiciones_separar[i]] , largo_actual );
		arr_cadenas[i][largo_actual-1] = FIN_STRING;
	}

	arr_cadenas[cant_separar] = NULL;

	free( posiciones_separar );
	return arr_cadenas;
}

/* ============ Función join ============ */

// Recibe un array de cadenas y un caracter separador
// Devuelve una cadena alocada en memoria dinámica con las cadenas
// del array concatenadas separadas por el caracter separador
char* join( char** arr_cadenas , char separador ){
	if( !arr_cadenas ) return NULL;

	int cont = 0;
	while( arr_cadenas[cont] != NULL )
		cont++;
	int* largo_cadenas = malloc( sizeof(int) * (cont+1) );

	int largo_total = 0;
	cont = 0;
	largo_cadenas[0] = 0;
	while( arr_cadenas[cont] != NULL ){
		largo_cadenas[cont+1] = str_largo( arr_cadenas[cont] )+1;
		largo_total += largo_cadenas[cont+1];
		cont++;
	}

	char* cadena = malloc( sizeof(char) * (largo_total+1) );

	cont = 0;
	int pos_actual = 0;
	while( arr_cadenas[cont] != NULL ){
		pos_actual += largo_cadenas[cont];
		str_copy( &cadena[pos_actual] , arr_cadenas[cont] , largo_cadenas[cont+1] );
		cadena[pos_actual+largo_cadenas[cont+1]-1] = separador;	
		cont++;
	}
	if( largo_total > 0 )
		cadena[largo_total-1] = FIN_STRING;
	else
		cadena[0] = FIN_STRING; 

	free( largo_cadenas );
	return cadena;
}

/* ============ Función free_strv ============ */

// Libera el espacio de memoria asignado a un array de strings char**
void free_strv( char** arr_cadenas ){
	if( !arr_cadenas ) return;

	int contador = 0;
	while( arr_cadenas[contador] != NULL ){
		free( arr_cadenas[contador] );
		contador++;
	}
	free( arr_cadenas );
}
