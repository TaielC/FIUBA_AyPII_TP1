#include <stdlib.h>

#include "cola.h"


/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct nodo{
	void* dato;
	struct nodo* siguiente;
}nodo_t;

struct cola{
	nodo_t* primero;
	nodo_t* ultimo;
};


/* ******************************************************************
 *                       FUNCIONES AUXILIARES
 * *****************************************************************/

// Post: devuelve un nodo, si falla devuelve NULL
nodo_t* nodo_crear( nodo_t* siguiente , void* valor ){
	nodo_t* nodo = malloc( sizeof(nodo_t) );
	if(nodo == NULL) return NULL;

	nodo->dato = valor;
	nodo->siguiente = siguiente;
	return nodo;
}

// Pre: el nodo fue creado
// Post: destruye el nodo y devuelve el valor guardado
void* nodo_destruir( nodo_t * nodo ){ 
	void* valor = nodo->dato;
	free( nodo );
	return valor;
}

/* ******************************************************************
 *            IMPLEMENTACIÓN DE PRIMITIVAS DE LA COLA
 * *****************************************************************/

cola_t* cola_crear(void){

	cola_t* cola = malloc( sizeof(cola_t) );

	if(!cola) return NULL;

	cola->primero = NULL;
	cola->ultimo = NULL;
	return cola;
}

void cola_destruir(cola_t *cola, void(*destruir_dato)(void*) ){

	while(!cola_esta_vacia( cola )){

		void* dato_aux = cola_desencolar( cola );
		if( destruir_dato != NULL )
			destruir_dato( dato_aux );
	}
	free(cola);
}

bool cola_esta_vacia(const cola_t *cola){

	return ( !cola->primero && !cola->ultimo );
}

bool cola_encolar(cola_t *cola, void* valor){

	nodo_t* nodo = nodo_crear( NULL , valor );
	if( nodo == NULL ) return false;

	if(cola_esta_vacia( cola ))
		cola->primero = nodo;
	else
		cola->ultimo->siguiente = nodo;
	cola->ultimo = nodo;

	return true;
}

void* cola_ver_primero(const cola_t *cola){

	if(cola_esta_vacia( cola ))	return NULL;

	return cola->primero->dato;
}

void* cola_desencolar(cola_t *cola){

	if(cola_esta_vacia( cola )){
		return NULL;
	}

	void* nodo_siguiente = cola->primero->siguiente;
	void* dato_aux = nodo_destruir( cola->primero );
	cola->primero = nodo_siguiente;
	if( cola->primero == NULL ){
		cola->ultimo = NULL;
	}

	return dato_aux;
}
