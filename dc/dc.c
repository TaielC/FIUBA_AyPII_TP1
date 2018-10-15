#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../strutil/strutil.h"
#include "pila.h"

#define CERO_ASCII 	48
#define NUEVE_ASCII	57
#define SEPARADOR 	' '
#define VEC_BINARIO 2
#define TAM_BUFFER  10000

#define STR_ERR		"ERROR"
#define STR_LOG		"log"
#define	STR_SQRT	"sqrt"

typedef enum op{
	SUMA 	= '+',
	RESTA	= '-',
	PROD 	= '*',
	DIV 	= '/',
	POT 	= '^',
	TERN	= '?',
	SQRT	= 's',
	LOG 	= 'l',
	ERR		= -1,
	NONE	= ' '
}op_t;

bool es_par( size_t numero ){
	return !(numero%2);
}

int potencia( int base , int exponente ){
	if( exponente == 0 ) return 1;
	if( exponente == 1 ) return base;
	int resultado = potencia( base , exponente /2);
	return resultado * resultado * (es_par(exponente)? 1 : base);
}

int _raiz_cuadrada( int numero , int min , int max ){
	if( min >= max ) return max;
	int medio = ( max + min )/2;
	if( medio*medio == numero ) return medio;
	if( medio*medio > numero ) return _raiz_cuadrada( numero , min , medio-1 );
	return _raiz_cuadrada( numero , medio+1 , max );
}

int raiz_cuadrada( int numero ){
	return _raiz_cuadrada( numero , 1 , numero );
}

int logaritmo( int numero , int base ){
	if( numero	== 0 ) return ERR;

	int exponente = 1;
	while( base < numero ){
		base *= base;
		exponente++;
	}
	return exponente;
}

bool es_numero( char caracter ){
	return caracter >= CERO_ASCII && caracter <= NUEVE_ASCII;
}

void pila_num_apilar( pila_t* pila_num , int num ){
	int* numero = malloc(sizeof(int));
	*numero = num;
	pila_apilar( pila_num , numero );
}

int pila_num_desapilar( pila_t* pila_num ){
	int numero = *(int*)pila_ver_tope( pila_num );
	free( pila_desapilar( pila_num ));
	return numero;
}

void pila_num_destruir( pila_t* pila_num ){
	while( !pila_esta_vacia( pila_num )){
		pila_num_desapilar( pila_num );
	}
	pila_destruir( pila_num );
}

op_t identificar_operacion( char* entrada ){

	if( strlen( entrada ) != 1 ){
		if( !strcmp( entrada , STR_SQRT ))
			return SQRT;
		if( !strcmp( entrada , STR_LOG )) 
			return LOG;
		return ERR;
	}

	switch(entrada[0]){
		case SUMA:
			return SUMA;
		case RESTA:
			return RESTA;
		case PROD:
			return PROD;
		case DIV:
			return DIV;
		case POT:
			return POT;
		case TERN:
			return TERN;
		case NONE:
			return NONE;
	}
	return ERR;
}

int aplicar_operacion( int* operacion , pila_t* pila_num ){
	if( pila_esta_vacia( pila_num )) return ERR;
	
	int numeros[VEC_BINARIO];
	numeros[0] = pila_num_desapilar( pila_num );

	bool ok_op_binaria = false;
	if( !pila_esta_vacia( pila_num )){
		numeros[1] = pila_num_desapilar( pila_num );
		ok_op_binaria = true;
	}

	switch(*operacion){
		case SUMA:
			if( !ok_op_binaria ) break;
			return ( numeros[0] + numeros[1] ); 

		case RESTA:
			if( !ok_op_binaria ) break;
			return ( numeros[0] - numeros[1] ); 

		case PROD:
			if( !ok_op_binaria ) break;
			return ( numeros[0] * numeros[1] ); 

		case DIV:
			if( !ok_op_binaria ) break;
			return ( numeros[0] / numeros[1] ); 

		case POT:
			if( !ok_op_binaria ) break;
			return potencia( numeros[0] , numeros[1] ); 

		case TERN:
			if( pila_esta_vacia( pila_num )) break;
			int numero = pila_num_desapilar( pila_num );

			return (numeros[0])? (numeros[1]) : numero;

		case SQRT:
			pila_num_apilar( pila_num , numeros[1] );
			return raiz_cuadrada( numeros[0] );

		case LOG:
			if( !ok_op_binaria ) break;
			return logaritmo( numeros[0] , numeros[1] );
		case NONE:
			return numeros[0];
	}
	*operacion = ERR;
	return ERR;
}

int main(){
	
	// char* linea = NULL;
	char linea[TAM_BUFFER];
	size_t nro_leidos = 0;

	// nro_leidos = getline( &linea , &nro_leidos , stdin );
	scanf( " %[^\n]" , linea );
	nro_leidos = strlen( linea );

	while( nro_leidos > 0 && !feof( stdin )){
		
		char** entrada = split( linea , SEPARADOR );
		pila_t* pila_num = pila_crear();

		op_t operacion = NONE;
		int resultado = 0;

		int i = 0;
		while( entrada[i] != NULL ){
			if( es_numero( entrada[i][0] ) ){
				pila_num_apilar( pila_num , atoi( entrada[i] ));
				i++;
				continue;
			}
			operacion = identificar_operacion( entrada[i] );

			resultado = aplicar_operacion( &operacion , pila_num );
			pila_num_apilar( pila_num , resultado );
			i++;
		}
		pila_num_destruir( pila_num );
		
		if( operacion == ERR )
			fprintf( stdout , "%s\n", STR_ERR );
		else
			fprintf( stdout , "%d\n", resultado );

		// nro_leidos = getline( &linea , &nro_leidos , stdin );
		scanf( " %[^\n]" , linea );
		nro_leidos = strlen( linea );

		free_strv( entrada );
	}

	// free(linea);
	return EXIT_SUCCESS;
}