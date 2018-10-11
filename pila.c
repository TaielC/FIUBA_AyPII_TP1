#include "pila.h"
#include <stdlib.h>

#define CAPACIDAD_INICIAL 	10
#define PORCENTAJE_AMPLIAR	200
#define PORCENTAJE_REDUCIR 	50
#define PORCENTAJE_REDUCTOR	25

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t* pila_crear(void){

	pila_t* pila = malloc( sizeof(pila_t) );
	if( pila == NULL ){
		return NULL;
	}
	pila->datos = malloc( CAPACIDAD_INICIAL*sizeof(void*) );
	if( pila->datos == NULL ){
		free(pila);
		return NULL;
	}
	pila->cantidad 	= 0;
	pila->capacidad = CAPACIDAD_INICIAL;

	return pila;
}

void pila_destruir(pila_t *pila){

	free(pila->datos);
	free(pila);
}

bool pila_esta_vacia(const pila_t *pila){

	return ( pila->cantidad == 0 );
}

// Redimensiona por el porcentaje pasado por parámetro
bool pila_redimensionar( pila_t* pila , int porcentaje_redimension ){

	void* datos_aux = realloc( pila->datos , pila->capacidad * sizeof(void*) * porcentaje_redimension /100 );
	if( datos_aux == NULL ){
		//en caso de que realloc falle, se devuelve que no se pudo completar 
		return false;
	}
	pila->datos = datos_aux;
	pila->capacidad = pila->capacidad* porcentaje_redimension /100;
	return true;	
}

bool pila_apilar(pila_t *pila, void* valor){

	if( pila->capacidad == pila->cantidad ){
		//segun de la funcion pila_ampliar se devuelve si se pudo completar la accion de apilar o no
		if( !pila_redimensionar( pila , PORCENTAJE_AMPLIAR ) )	return false; 
	}
	
	pila->datos[pila->cantidad] = valor; 
	pila->cantidad++;

	return true;
}

void* pila_ver_tope(const pila_t *pila){

	if( pila_esta_vacia( pila ) ){
		return NULL;
	}

	return pila->datos[pila->cantidad -1];
}

void* pila_desapilar(pila_t *pila){

	if( pila_esta_vacia( pila ) ){
		return NULL;
	}

	// Si la cantidad de datos de la pila es menor a un 25 porciento de la capacidad y 
	// al reducirse a la mitad la capacidad se obtiene mayor o igual a la capacidad inicial:
	if( (pila->capacidad * PORCENTAJE_REDUCTOR /100 ) > pila->cantidad && ( pila->capacidad * PORCENTAJE_REDUCIR /100 ) >= CAPACIDAD_INICIAL ){
		pila_redimensionar( pila  , PORCENTAJE_REDUCIR );
	}

	pila->cantidad--;
	return pila->datos[pila->cantidad];
}
