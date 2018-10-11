#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[]){
	
	if( argc < 2 || 3 < argc ){
		printf("La cantidad de parámetros ingresada es incorrecta \n");
		return 1;
	}

	return EXIT_SUCCESS;
}