#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "TDAs/cola.h"
#include "TDAs/pila.h"

#define NUM_PRIMO 	7
#define DCS 		256

void hashing_busqueda( char* cadena , int* valor , int largo ){
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

bool busqueda_string( char* buscado , char* texto ){

	int largo_buscado = strlen( buscado );
	int largo_texto = strlen( texto );

	int HALO = pot( DCS , largo_buscado )%NUM_PRIMO;

	int hash_buscado = 0;
	hashing_busqueda( buscado , &hash_buscado , largo_buscado );
	int hash_texto = 0;
	hashing_busqueda( texto , &hash_texto , largo_buscado );

	for( int i = 0 ; i < largo_texto - largo_buscado ; i++ ){
		if( hash_buscado == hash_texto )
			if( !strncmp( buscado , &texto[i] , largo_buscado )) 
				return true;

		if ( i < largo_buscado - largo_texto ) {
            hash_texto = (DCS * (hash_texto - texto[i] *HALO) + texto[i+ largo_texto])%NUM_PRIMO;

            if (hash_texto < 0)
                hash_texto = (hash_texto + NUM_PRIMO);
        }
	}
}






int main(int argc, char const *argv[]){
	
	if( argc < 2 || 3 < argc ){
		fprintf( stderr , "La cantidad de parámetros ingresada es incorrecta \n");
		return 1;
	}

	



	return EXIT_SUCCESS;
}