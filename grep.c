#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "cola.h"

#define NUM_PRIMO 	7
#define DCS 		256
#define TAM_BUFFER  10000

void hashing_busqueda( const char* cadena , int* valor , int largo ){
	for ( size_t i = 0; i < largo ; i++ ){
		*valor = ( DCS * (*valor) + cadena[i])%NUM_PRIMO;
	}
}

int pot(int a , int b ){
	for (int i = 0; i < b; i++ ){
		a*=a;
	}
	return a;
}

bool busqueda_string( const char* buscado , char* texto ){

	int len_buscado = strlen( buscado );
	int len_texto = strlen( texto );

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
            h_texto = (DCS * (h_texto - texto[i] *nro) + texto[i+ len_texto])%NUM_PRIMO;

            if (h_texto < 0)
                h_texto = (h_texto + NUM_PRIMO);
        }
	}
	return false;
}

int main(int argc, char const *argv[]){
	
	if( argc < 3 || 4 < argc ){
		fprintf( stderr , "Cantidad de parametros erronea");
		return 1;
	}

	FILE* entrada;
	if( argc == 4 ){
		entrada = fopen( argv[4] , "r" );
		if( !entrada ){
			fprintf(stderr, "No se pudo leer el archivo indicado");
		}
	}else
		entrada = stdin;

	const char* buscado = argv[1];
	int largo_buscado = strlen( buscado );

	int cant_lineas = atoi( argv[2] );
	int lineas_guardadas = 0;
	cola_t* cola_lineas = cola_crear();

	char* linea = NULL;
	size_t largo_linea = 0;

	while( !feof( entrada ) && getline( &linea , &largo_linea , entrada ) >= 0){

		if( largo_linea < largo_buscado )
			continue;

		if( busqueda_string( buscado , linea )){
			while( !cola_esta_vacia( cola_lineas )){
				char* linea_aux = cola_desencolar( cola_lineas );		
				fprintf( stdout , "%s\n", linea_aux );
				free( linea_aux );
			}
			fprintf( stdout , "%s\n", linea );
			lineas_guardadas = 0;
		}
		else{
			if( lineas_guardadas >= cant_lineas )
				free( cola_desencolar( cola_lineas ));
			if( cant_lineas > 0 )
				cola_encolar( cola_lineas , linea );
		}
	}

	return EXIT_SUCCESS;
}