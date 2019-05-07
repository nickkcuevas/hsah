#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * ******************************************************************/

typedef struct lista lista_t;

typedef struct lista_iter lista_iter_t;

/* ******************************************************************
 *                PRIMITIVAS DE LA LISTA ENLAZADA
 * ******************************************************************/

// Crea una lista enlazada.
// Post: Devuelve una nueva lista enlazada vacia.
lista_t* lista_crear(void);

// Devuelve verdadero si la lista enlazada no tiene elementos (si el largo es igual a 0) false en caso contrario.
// Pre: la lista enlazada fue creada.
bool lista_esta_vacia(const lista_t* lista);

// Agrega un nuevo elemento en la primer posicion de la lista. Devuelve falso en caso de error.
// Pre: la lista enlazada fue creada.
// Post: se agrego un nuevo elemento a la lista en la primer posicion.
// Se incremento en uno el largo de la lista.
bool lista_insertar_primero(lista_t* lista, void* dato);

// Agrega un nuevo elemento en la ultima posicion de la lista. Devuelve falso en caso de error.
// Pre: la lista enlazada fue creada.
// Post: se agrego un nuevo elemento a la lista en la ultima posicion.
// Se incremento en uno el largo de la lista.
bool lista_insertar_ultimo(lista_t* lista, void* dato);

// Elimina el primer elemento de la lista. Si la lista tiene elementos se quita el primero de la lista, 
// y se devuelve su valor, si esta vacia, devuelve NULL.
// Pre: la lista enlazada fue creada.
// Post: se elimino el elemento correspondiente a la primer posicion de la lista. 
// Se decremento en uno el largo de la lista.
void* lista_borrar_primero(lista_t* lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene elementos, se devuelve el valor del primero.
// Si la lista esta vacia, devuelve NULL.
// Pre: la lista enlazada fue creada.
// Post: se devolvio el primer elemento de la lista, cuando no esta vacia.
void* lista_ver_primero(const lista_t* lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene elementos, se devuelve el valor del ultimo.
// Si la lista esta vacia, devuelve NULL.
// Pre: la lista enlazada fue creada.
// Post: se devolvio el ultimo elemento de la lista, cuando no esta vacia.
void* lista_ver_ultimo(const lista_t* lista);

// Devuelve el largo de la lista, correspondiente a la cantidad de elementos en la lista.
// Si la lista esta vacia el largo es igual a 0.
// Pre: la lista enlazada fue creada.
// Post: se devolvio el largo de la lista.
size_t lista_largo(const lista_t* lista);

// Destruye la lista. Si se recibe la funcion destruir por parametro,
// para cada uno de los elementos de la lista llama a destruir.
// Pre: la lista enlazada fue creada.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t* lista, void destruir(void*));

/* ******************************************************************
 *                PRIMITIVAS DEL ITERADOR EXTERNO
 * ******************************************************************/

// Crea un iterador externo.
// Pre: la lista enlazada fue creada.
// Post: devuelve un nuevo iterador externo. En la posicion del primer elemento de la lista.
lista_iter_t* lista_iter_crear(lista_t* lista);

// Avanza el iterador a la siguiente posicion. Si la lista tiene elementos apunta 
// al siguiente elemento de la lista.
// Si la lista esta vacia o el iterador se encuentra en la ultima posicion devuelve falso.
// Pre: el iterador fue creado.
// Post: el iterador avanzo a la siguiente posicion. Apunta al siguiente elemento de la lista.
bool lista_iter_avanzar(lista_iter_t* iter);

// Obtiene el valor del elemento de la lista al cual el iterador esta apuntando.
// Si la lista tiene elementos y el iterador no se encuentra al final, se devuelve el valor 
// del elemento al que apunta el iterador, false en caso contrario.
// Pre: el iterador fue creado.
// Post: se devolvio el valor del elemento que apunta el iterador, cuando la lista no esta vacia
// y el iterador no apunta al final.
void* lista_iter_ver_actual(const lista_iter_t* iter);

// Devuelve verdadero si el iterador esta apuntando al final de la lista, si la lista esta vacia 
// o el iterador esta apuntando al final de la lista entonces devuelve false.
// Pre: el iterador fue creado.
// Post: se devolvio si el iterador se encuentra al final de la lista.
bool lista_iter_al_final(const lista_iter_t* iter);

// Destruye solo el iterador externo.
// Pre: el iterador fue creado.
// Post: se elimino el iterador.
void lista_iter_destruir(lista_iter_t* iter);

// Agrega un nuevo elemento a la lista en la posicion actual que se encuentra el iterador.
// Devuelve false en caso de error.
// Pre: el iterador fue creado.
// Post: se agrego un nuevo elemento a la lista en la posicion actual del iterador.
// Se incremento en uno el largo de la lista.
bool lista_iter_insertar(lista_iter_t* iter, void* dato);

// Elimina el primer elemento de la lista. Si la lista tiene elementos se quita el primero de la lista, 
// y se devuelve su valor, si esta vacia, devuelve NULL.
// Pre: la lista enlazada fue creada.
// Post: se elimino el elemento correspondiente a la primer posicion de la lista. 
// Se decremento en uno el largo de la lista.

// Elimina el elemento de la lista que se encuentra en la posicion actual del iterador. 
// Si la lista tiene elementos se quita el elemento que se encuentra en la posicion actual 
// del iterador, y se devuelve su valor, si la lista esta vacia o el iterador se encuentra 
// al final, devuelve NULL.
// Pre: el iterador fue creado.
// Post: se elimino el elemento en la posicion actual del iterador.
// Se decremento en uno el largo de la lista.
void* lista_iter_borrar(lista_iter_t* iter);

/* ******************************************************************
 *                PRIMITIVAS DEL ITERADOR INTERNO
 * ******************************************************************/

// Itera sobre los elementos de la lista si la funcion que recibe como parametro 
// visitar devuelve verdadero.
// En el caso que la funcion visitar devuelve falso entonces se termina la iteracion.
// Pre: la lista enlazada fue creada.
// Post: se itero sobre la lista.
void lista_iterar(lista_t* lista, bool visitar(void* dato, void* extra), void* extra);

/* ******************************************************************
 *                      PRUEBAS UNITARIAS
 * ******************************************************************/

void pruebas_lista_alumno(void);

#endif // LISTA_H
