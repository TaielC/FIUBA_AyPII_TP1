#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "cola.h"

#define NUM_PRIMO 	17
#define DCS 		256
#define TAM_BUFFER  10000

void hashing_busqueda( const char* cadena , int* valor , size_t largo ){
	for ( size_t i = 0; i < largo ; i++ ){
		*valor = ( DCS * (*valor) + cadena[i])%NUM_PRIMO;
	}
}

int pot(int a , size_t b ){
	for (int i = 0; i < b; i++ ){
		a*=a;
	}
	return a;
}

bool busqueda_string( const char* buscado , const char* texto ){

	size_t len_buscado = strlen( buscado );
	size_t len_texto = strlen( texto );

	int nro = pot( DCS , len_buscado )%NUM_PRIMO;

	int h_buscado = 0;
	hashing_busqueda( buscado , &h_buscado , len_buscado );
	int h_texto = 0;
	hashing_busqueda( texto , &h_texto , len_buscado );

	for( int i = 0 ; i < len_texto - len_buscado ; i++ ){

		if( h_buscado == h_texto )
			if( !strncmp( buscado , &texto[i] , len_buscado )) 
				return true;

		if ( i < len_texto - len_buscado ) {
            h_texto = (DCS * (h_texto - texto[i] *nro) + texto[i+len_texto])%NUM_PRIMO;
			
			if (h_texto < 0) h_texto += NUM_PRIMO;
        }
	}
	return false;
}

int main(int argc, char const *argv[]){
	
	if( argc < 3 || 4 < argc ){
		fprintf( stderr , "Cantidad de parametros erronea\n");
		return 1;
	}

	FILE* entrada;
	if( argc == 4 ){
		entrada = fopen( argv[3] , "r" );
		if( !entrada ){
			fprintf(stderr, "No se pudo leer el archivo indicado\n");
			return 1;
		}
	}else
		entrada = stdin;

	const char* buscado = argv[1];
	size_t largo_buscado = strlen( buscado );

	int cant_lineas = atoi( argv[2] );
	int lineas_guardadas = 0;
	cola_t* cola_lineas = cola_crear();

	char* linea[TAM_BUFFER];
	size_t largo_linea = TAM_BUFFER;

	while( !feof( entrada ) && getline( linea , &largo_linea , entrada ) >= 0){
		largo_linea = strlen( *linea );
		if( largo_linea < largo_buscado )
			continue;

		if( busqueda_string( buscado , *linea )){
			while( !cola_esta_vacia( cola_lineas )){
				fprintf( stdout , "%s", (char*)cola_ver_primero( cola_lineas ) );
				free( cola_desencolar( cola_lineas ) );
			}
			fprintf( stdout , "%s", *linea );
			lineas_guardadas = 0;
		}
		else{
			if( cant_lineas > 0 ){
				char* linea_aux = malloc( sizeof(char) * (largo_linea +1) );
				strcpy( linea_aux , *linea );
				cola_encolar( cola_lineas , linea_aux );
				lineas_guardadas++;
			}
			if( lineas_guardadas > cant_lineas )
				free( cola_desencolar( cola_lineas ));
		}
		largo_linea = TAM_BUFFER;
	}

	free(*linea);
	cola_destruir( cola_lineas , free );
	fclose( entrada );
	return EXIT_SUCCESS;
}