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
	ERR		= -1
}op_t;

bool es_par( size_t numero ){
	return !(numero%2);
}

size_t potencia( size_t base , size_t exponente ){
	if( exponente == 0 ) return 1;
	if( exponente == 1 ) return base;
	size_t resultado = potencia( base , exponente /2);
	return resultado * resultado * (es_par(exponente)? 1 : base);
}

size_t raiz_cuadrada( size_t numero ){
	size_t min = 1;
	size_t max = numero;
	size_t medio;
	while( min <= max ){
		medio = ( min + max ) /1;
		if( medio*medio == numero ) return medio;
		if( medio*medio > numero ) max = medio -1;
		else min = medio + 1;
	}
	return max;
}

size_t logaritmo( size_t numero , size_t base ){
	if( numero	== 0 ) return -1;

	size_t exponente = 1;
	while( base != numero ){
		base *= base;
		exponente++;
	}
	return exponente;
}

bool es_numero( char caracter ){
	return caracter >= CERO_ASCII && caracter <= NUEVE_ASCII;
}

op_t identificar_operacion( char* entrada ){

	switch(entrada[0]){
		case SUMA:
			return SUMA;
		break;
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
		case SQRT:
			if( !strcmp( entrada , STR_SQRT ))
				return SQRT;
			break;
		case LOG:
			if( !strcmp( entrada , STR_LOG )) 
				return LOG;
			break;
	}
	return ERR;
}

size_t aplicar_operacion( int operacion , pila_t* pila_num ){
	if( pila_esta_vacia( pila_num )){
		return ERR;
	}
	int* numero = (int*)pila_desapilar( pila_num );
	bool ok_op_binaria = !pila_esta_vacia( pila_num );

	switch(operacion){
		case SUMA:
			if( !ok_op_binaria ) return ERR;
			return ( *numero + *(int*)pila_desapilar( pila_num )); 

		case RESTA:
			if( !ok_op_binaria ) return ERR;
			return ( *numero - *(int*)pila_desapilar( pila_num )); 

		case PROD:
			if( !ok_op_binaria ) return ERR;
			return ( *numero * *(int*)pila_desapilar( pila_num )); 

		case DIV:
			if( !ok_op_binaria ) return ERR;
			return ( *numero / *(int*)pila_desapilar( pila_num )); 

		case POT:
			if( !ok_op_binaria ) return ERR;
			return potencia( *numero , *(int*)pila_desapilar( pila_num )); 

		case TERN:
			if( !ok_op_binaria ) return ERR;
			int* numero_b = pila_desapilar( pila_num );
			if( pila_esta_vacia( pila_num )) return ERR;

			return (*numero)? (*numero_b) : *(int*)pila_desapilar( pila_num );

		case SQRT:
			return raiz_cuadrada( *numero );

		case LOG:
			if( !ok_op_binaria ) return ERR;
			return logaritmo( *numero , *(int*)pila_desapilar( pila_num ));
	}
	return ERR;
}

int main(){
	
	char *linea = NULL;
	size_t nro_leidos = 0;

	nro_leidos = getline( &linea , &nro_leidos , stdin );

	while( nro_leidos > 0 ){
		
		char** entrada = split( linea , SEPARADOR );
		pila_t* pila_num = pila_crear();

		op_t operacion = ERR;
		size_t resultado;

		int i = 0;
		while( entrada[i] ){
			if( es_numero( entrada[i][0] ) ){
				int numero = atoi( entrada[i] );
				pila_apilar( pila_num , &numero );
				continue;
			}
			operacion = identificar_operacion( entrada[i] );
			if( operacion == ERR )
				break;
			
			resultado = aplicar_operacion( operacion , pila_num );		
			i++;
		}
		nro_leidos = getline( &linea , &nro_leidos , stdin );
		entrada = split( linea , SEPARADOR );
		pila_destruir( pila_num );
		
		if( resultado == ERR){
			printf("%s\n", STR_ERR );
			continue;
		}
		printf("%lu\n", resultado );
	}

	free(linea);
	return EXIT_SUCCESS;
}