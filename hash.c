#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "lista.h"

// Definicion de constantes

#define CAPACIDAD_INICIAL 31

// Definicion de la estructura nodo_hash_t

typedef struct nodo_hash {
    const char* clave;
    void* dato;
} nodo_hash_t;

// Definicion de la estructura hash abierto

struct hash {
    lista_t** tabla;
    unsigned long (*funcion_hash)(const char*);
    size_t cantidad;
    size_t capacidad;
    hash_destruir_dato_t destruir_dato;
};

// Definicion de la estructura hash_iter

struct hash_iter {
    lista_t** tabla;
    size_t pos;
    lista_t* act;
    size_t tabla_largo;
};

// Funcion de Hash
// Fuente: http://profesores.elo.utfsm.cl/~agv/elo320/miscellaneous/hashFunction/hashFunction.html

unsigned long f_hash(const char *str) {
    unsigned long f_hash = 5381;
    int c;

    while ( (c = *str++) )
        f_hash = ((f_hash << 5) + f_hash) + (unsigned long)c; /* hash * 33 + c */

    return f_hash;
}

// Funciones auxiliares

nodo_hash_t* nodo_hash_crear(const char* clave, void* dato) {
    nodo_hash_t* nodo = malloc( sizeof(nodo_hash_t) );
    if ( !nodo )
        return NULL;

    nodo->clave = clave;
    nodo->dato = dato;
    return nodo;
}

void inicializar_tabla(hash_t* hash) {
    for (size_t i=0; i < hash->capacidad; i++)
        hash->tabla[i] = NULL;
}


// Primitivas del hash

hash_t* hash_crear(hash_destruir_dato_t destruir_dato) {
    hash_t* hash = malloc( sizeof(hash_t) );
    if ( !hash )
        return NULL;

    lista_t** tabla = malloc( CAPACIDAD_INICIAL * sizeof(lista_t*) );
    if ( !tabla ) {
        free(hash);
        return NULL;
    }

    hash->tabla = tabla;
    hash->funcion_hash = f_hash;
    hash->capacidad = CAPACIDAD_INICIAL;
    hash->cantidad = 0;
    hash->destruir_dato = destruir_dato;
    inicializar_tabla(hash);
    return hash;
}

size_t hash_cantidad(const hash_t* hash) {
    return hash->cantidad;
}

bool hash_pertenece(const hash_t* hash, const char* clave) {
    size_t indice = hash->funcion_hash(clave) % hash->capacidad;
    return hash->tabla[indice];
}

bool hash_guardar(hash_t* hash, const char* clave, void* dato) {
    size_t indice = hash->funcion_hash(clave) % hash->capacidad;
    nodo_hash_t* nodo_hash = nodo_hash_crear(clave, dato);
    if ( !nodo_hash )
        return false;

    bool existe = false;
    if ( !hash_pertenece(hash, clave) ) {
        hash->tabla[indice] = lista_crear();
        existe = true;
    }

    bool ok = lista_insertar_ultimo(hash->tabla[indice], nodo_hash);
    if ( ok && existe )
        hash->cantidad++;
    return ok;
}

void* hash_borrar(hash_t* hash, const char* clave) {
    size_t indice = hash->funcion_hash(clave) % hash->capacidad;
    if ( !hash_pertenece(hash, clave) )
        return NULL;

    void* valor = NULL;
    nodo_hash_t* actual = NULL;
    bool existe = false;

    lista_iter_t* iter = lista_iter_crear(hash->tabla[indice]);
    while ( !( existe || lista_iter_al_final(iter) ) ) {
        actual = lista_iter_ver_actual(iter);
        if ( actual->clave == clave ) {
            valor = actual->dato;
            lista_iter_borrar(iter);
            existe = true;
        }
        lista_iter_avanzar(iter);
    }
    free(iter);

    if ( existe )
        free(actual);

    if ( lista_esta_vacia(hash->tabla[indice]) ) {
        free(hash->tabla[indice]);
        hash->tabla[indice] = NULL;
    }

    hash->cantidad--;
    return valor;
}

void* hash_obtener(const hash_t* hash, const char* clave) {
    if ( !hash_pertenece(hash, clave) )
        return NULL;
    size_t indice = hash->funcion_hash(clave) % hash->capacidad;
    nodo_hash_t* ultimo = lista_ver_ultimo(hash->tabla[indice]);
    return ultimo->dato;
}

void hash_destruir(hash_t* hash) {
    for (size_t i=0; i < hash->capacidad; i++) {
        if ( hash->tabla[i] ) {
            while ( !lista_esta_vacia(hash->tabla[i]) ) {
                nodo_hash_t* primero = lista_borrar_primero(hash->tabla[i]);
                if ( hash->destruir_dato )
                    hash->destruir_dato(primero->dato);
                free(primero);
            }
            free(hash->tabla[i]);
        }
    }
    free(hash->tabla);
    free(hash);
}

// Primitivas del iterador

hash_iter_t* hash_iter_crear(const hash_t* hash) {
    hash_iter_t* iter = malloc( sizeof(hash_iter_t) );
    if ( !iter )
        return NULL;
    iter->tabla = hash->tabla;
    iter->pos = 0;
    iter->act = iter->tabla[iter->pos];
    iter->tabla_largo = hash->capacidad;
    return iter;
}

bool hash_iter_al_final(const hash_iter_t* iter) {
    return ( iter->pos != iter->tabla_largo );
}

bool hash_iter_avanzar(hash_iter_t* iter) {
    if ( hash_iter_al_final(iter) )
        return false;
    iter->pos++;
    iter->act = iter->tabla[iter->pos];
    return true;
}

const char* hash_iter_ver_actual(const hash_iter_t* iter) {
    if ( hash_iter_al_final(iter) )
        return NULL;
    nodo_hash_t* ultimo = lista_ver_ultimo(iter->act);
    char clave_caracter[strlen(ultimo->clave)];
    strcpy(clave_caracter, ultimo->clave);
    const char* clave = clave_caracter;
    return clave;
}

void hash_iter_destruir(hash_iter_t* iter) {
    free(iter);
}
