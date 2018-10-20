#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "strutil.h"
#include "pila.h"

#define CERO_ASCII 		'0'
#define NUEVE_ASCII		'9'
#define NEGATIVO_ASCII	'-'

#define FIN_STR		'\0'
#define SEPARADOR 	' '
#define VEC_BINARIO 2
#define TAM_BUFFER  10000

#define STR_ERR		"ERROR"
#define STR_LOG		"log"
#define	STR_SQRT	"sqrt"


/* ------------ Definición de Operaciones ------------ */

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
	NONE	= '\0'
}op_t;

bool es_par( size_t numero ){
	return !(numero%2);
}

// Función de potencia, en O(log n)
int potencia( int base , int exponente ){
	if( exponente == 0 ) return 1;
	else if( exponente == 1 ) return base;
	int resultado = potencia( base , exponente /2);
	return resultado * resultado * (es_par(exponente)? 1 : base);
}

// Función de raiz cuadrada, en O(log n)
int _raiz_cuadrada( int numero , int min , int max ){
	int medio = ( max + min )/2;
	if( medio*medio == numero ) return medio;
	if( medio*medio > numero ) return _raiz_cuadrada( numero , min , medio-1 );
	if( (medio+1)*(medio+1) > numero ) return medio;
	return _raiz_cuadrada( numero , medio+1 , max );
}
// Wrapper de raiz cuadrada
int raiz_cuadrada( int numero ){
	if( numero < 0 ) return ERR;
	return _raiz_cuadrada( numero , 1 , numero );
}

// Función de logaritmo
int logaritmo( int argumento , int base ){
	if( argumento <= 0 || base <= 0 ) return ERR;
	if( base == 1  && argumento != 1 ) return ERR;

	int exponente = 0;
	int resultado = 1;
	while( resultado*(base) <= argumento ){
		resultado *= base;
		exponente++;
	}
	return exponente;
}


/* ------------ Funciones que adaptan la pila  ------------- */

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
		free( pila_desapilar( pila_num ));
	}
	pila_destruir( pila_num );
}


/* ----------- Funciones auxiliares a la calculadora ---------- */

// Recibe una cadena de caracteres para identificar, a partir de la tabla ascii
// si son caracteres numéricos (devuelve true) o no (devuelve false)
bool es_numero( char* entrada ){
	
	int cont = 0;

	if( strlen(entrada) > 1 && entrada[cont] == NEGATIVO_ASCII )
		cont++;

	while( entrada[cont] != FIN_STR ){
		if( entrada[cont] < CERO_ASCII || entrada[cont] > NUEVE_ASCII )
			return false;
		cont++;
	}

	return true;
}

// Aplica la operación de la entrada
// Recibe la entrada, un op_t para verificacion de errores y la pila con números
// Devuelve el resultado de la operación, y la operación que fue ejecutada,
// en caso de que la entrada no fuera una operación válida o surja 
// un error de ejecucion asigna a operacion el dato ERR.
int aplicar_operacion( char* entrada , op_t* operacion , pila_t* pila_num ){
	if( pila_esta_vacia( pila_num )){
		*operacion = ERR;
		return ERR;	
	} 
	
	int numeros[VEC_BINARIO];
	numeros[0] = pila_num_desapilar( pila_num );

	bool ok_op_binaria = false;
	if( !pila_esta_vacia( pila_num )){
		numeros[1] = pila_num_desapilar( pila_num );
		ok_op_binaria = true;
	}

	if( strlen( entrada ) != 1 ){
		int resultado = ERR;
		if( !strcmp( entrada , STR_SQRT )){
			*operacion = SQRT;
			if( ok_op_binaria )
				pila_num_apilar( pila_num , numeros[1] );
			resultado = raiz_cuadrada( numeros[0] );
		}
		else if( !strcmp( entrada , STR_LOG )){
			*operacion = LOG;
			if( ok_op_binaria )
				resultado = logaritmo( numeros[0] , numeros[1] );
		}
		if( resultado == ERR )
			*operacion = ERR;
		return resultado;
	}

	switch(entrada[0]){
		case SUMA:
			*operacion = SUMA;
			if( ok_op_binaria )
				return ( numeros[0] + numeros[1] ); 

		case RESTA:
			*operacion = RESTA;
			if( ok_op_binaria )
				return ( numeros[0] - numeros[1] ); 

		case PROD:
			*operacion = PROD;
			if( ok_op_binaria )
				return ( numeros[0] * numeros[1] ); 

		case DIV:
			*operacion = DIV;
			if( ok_op_binaria ){
				if( numeros[1] == 0 ) break;
				return ( numeros[0] / numeros[1] ); 
			}

		case POT:
			*operacion = POT;
			if( !ok_op_binaria || numeros[1] < 0 ) break;
			return potencia( numeros[0] , numeros[1] ); 

		case TERN:
			*operacion = TERN;
			if( pila_esta_vacia( pila_num )) break;
			int numero = pila_num_desapilar( pila_num );

			return (numeros[0])? (numeros[1]) : numero;
	}
	*operacion = ERR;
	return ERR;
}

/* ------------- PROGRAMA PRINCIPAL -------------- */

int main(){
	
	char linea[TAM_BUFFER];
	size_t nro_leidos = 0;

	scanf( " %[^\n]" , linea );
	nro_leidos = strlen( linea );

	while( nro_leidos > 0 ){
		
		char** entrada = split( linea , SEPARADOR );
		pila_t* pila_num = pila_crear();

		op_t operacion = NONE;
		int resultado = 0;

		int i = 0;
		while( entrada[i] != NULL && operacion != ERR ){
			if( entrada[i][0] == FIN_STR ){}
			else if( es_numero( entrada[i] ) ){
				pila_num_apilar( pila_num , atoi( entrada[i] ));
				operacion = NONE;
			}
			else{
				resultado = aplicar_operacion( entrada[i] , &operacion , pila_num );
				pila_num_apilar( pila_num , resultado );
			}
			i++;
		}
		resultado = pila_num_desapilar( pila_num );
		
		if( operacion == ERR || !pila_esta_vacia( pila_num ))
			fprintf( stdout , "%s\n", STR_ERR );
		else 
			fprintf( stdout , "%d\n", resultado );

		scanf( " %[^\n]" , linea );
		nro_leidos = strlen( linea );

		pila_num_destruir( pila_num );
		free_strv( entrada );
		if( feof(stdin) ) break;
	}

	return EXIT_SUCCESS;
}