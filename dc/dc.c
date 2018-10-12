#define _GNU_SOURCE
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "pila.h"

#define SUMA 		'+'
#define RESTA 		'-'
#define PRODUCTO 	'*'
#define DIVISION 	'/'
#define POTENCIA	'^'
#define TERNARIO	'?'
#define RAIZ		"sqrt"
#define LOGARITMO 	"log"

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

int main(){
	
	char *linea = NULL;
	size_t nro_leidos = 0;

	nro_leidos = getline( &linea , &nro_leidos , stdin );

	pila_t* pila_numeros = pila_crear();

	printf("%lu %lu\n", nro_leidos , strlen( linea ) );

	// while( nro_leidos > 0 ){


	// }


	free(linea);
	pila_destruir( pila_numeros );
	return EXIT_SUCCESS;
}