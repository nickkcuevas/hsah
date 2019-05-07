#include "lista.h"
#include <stdlib.h>


// Defincion de la estructura nodo_t

typedef struct nodo {
    struct nodo* prox;
    void* dato;
}nodo_t;

// Definicion de la estructura lista

struct lista {
    nodo_t* primero;
    nodo_t* ultimo;
    size_t largo;
};

// Definicion de la estructura lista_iter

struct lista_iter {
    lista_t* lista;
    nodo_t* act;
    nodo_t* ant;
};


// Funciones auxiliares

nodo_t* nodo_crear(void* dato) {
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if ( !nodo )
        return NULL;

    nodo->dato = dato;
    nodo->prox = NULL;
    return nodo;
}

// Primitivas de la lista enlazada

lista_t* lista_crear(void) {
    lista_t* lista = malloc(sizeof(lista_t));
    if ( !lista )
        return NULL;

    lista->primero = NULL;
    lista->ultimo = NULL;
    lista->largo = 0;
    return lista;
}

bool lista_esta_vacia(const lista_t* lista) {
    return !lista->largo;
}

bool lista_insertar_primero(lista_t* lista, void* dato) {
    nodo_t* nodo = nodo_crear(dato);
    if ( !nodo )
        return false;

    if ( lista_esta_vacia(lista) )
        lista->ultimo = nodo;
    else
        nodo->prox = lista->primero;

    lista->primero = nodo;
    lista->largo++;
    return true;
}

bool lista_insertar_ultimo(lista_t* lista, void* dato) {
    nodo_t* nodo = nodo_crear(dato);
    if ( !nodo )
        return false;

    if ( lista_esta_vacia(lista) )
        lista->primero = nodo;
    else
        lista->ultimo->prox = nodo;

    lista->ultimo = nodo;
    lista->largo++;
    return true;
}

void* lista_borrar_primero(lista_t* lista) {
    if ( lista_esta_vacia(lista) )
        return NULL;

    void* dato = lista->primero->dato;
    nodo_t* nodo = lista->primero;
    lista->primero = lista->primero->prox;

    if ( lista_esta_vacia(lista) )
        lista->ultimo = NULL;

    free(nodo);
    lista->largo--;
    return dato;
}

void* lista_ver_primero(const lista_t* lista) {
    if ( lista_esta_vacia(lista) )
        return NULL;
    return lista->primero->dato;
}

void* lista_ver_ultimo(const lista_t* lista) {
    if ( lista_esta_vacia(lista) )
        return NULL;
    return lista->ultimo->dato;
}

size_t lista_largo(const lista_t* lista) {
    return lista->largo;
}

void lista_destruir(lista_t* lista, void destruir(void*)) {
    while ( !lista_esta_vacia(lista) ) {
        if ( destruir )
            destruir(lista_borrar_primero(lista));
        else
            lista_borrar_primero(lista);
    }
    free(lista);
}

// Primitivas del iterador externo

lista_iter_t* lista_iter_crear(lista_t* lista) {
    lista_iter_t* iter = malloc(sizeof(lista_iter_t));
    if ( !iter )
        return NULL;
    iter->lista = lista;
    iter->ant = NULL;
    iter->act = lista->primero;
    return iter;
}

bool lista_iter_al_final(const lista_iter_t* iter) {
    return !iter->act;
}

bool lista_iter_avanzar(lista_iter_t* iter) {
    if ( lista_iter_al_final(iter) )
        return false;
    iter->ant = iter->act;
    iter->act = iter->act->prox;
    return true;
}

void* lista_iter_ver_actual(const lista_iter_t* iter) {
    if ( lista_iter_al_final(iter) )
        return NULL;
    return iter->act->dato;
}

void lista_iter_destruir(lista_iter_t* iter) {
    free(iter);
}

bool lista_iter_insertar(lista_iter_t* iter, void* dato) {
    bool ok;
    if ( !iter->ant ) {
        ok = lista_insertar_primero(iter->lista, dato);
        iter->act = iter->lista->primero;
        return ok;
    }
    if ( lista_iter_al_final(iter) ) {
        ok = lista_insertar_ultimo(iter->lista, dato);
        iter->act = iter->lista->ultimo;
        iter->ant->prox = iter->act;
        return ok;
    }
    nodo_t* nodo = nodo_crear(dato);
    if ( !nodo )
        return false;
    nodo->prox = iter->act;
    iter->ant->prox = nodo;
    iter->act = nodo;
    iter->lista->largo++;
    return true;
}

void* lista_iter_borrar(lista_iter_t* iter) {
    if ( lista_iter_al_final(iter) )
        return NULL;
    void* dato = iter->act->dato;
    nodo_t* nodo = iter->act;
    iter->act = iter->act->prox;
    // actualizar primero de la lista
    if ( !iter->ant )
        iter->lista->primero = iter->act;
    else
        iter->ant->prox = iter->act;
    // actualizar ultimo de la lista
    if ( lista_iter_al_final(iter) )
        iter->lista->ultimo = iter->ant;
    iter->lista->largo--;
    free(nodo);
    return dato;
}

// Primitivas del iterador interno

void lista_iterar(lista_t* lista, bool visitar(void* dato, void* extra), void* extra) {
    nodo_t* actual = lista->primero;
    while ( actual ) {
        if ( !visitar(actual->dato, extra) )
            break;
        actual = actual->prox;
    }
}
