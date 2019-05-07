/*
 * prueba_hash.c
 * Pruebas para el tipo de dato abstracto Tabla de Hash
 * Copyright: (2011) Margarita Manterola, Maximiliano Curia
 * Licencia: CC-BY-SA 2.5 (ar) ó CC-BY-SA 3.0
 */

#include "hash.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For ssize_t in Linux.


/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

static void prueba_crear_hash_vacio()
{
   printf("\nPRUEBA CREAR HASH VACIO\n");

    hash_t* hash = hash_crear(NULL);

    print_test("Prueba hash crear hash vacio", hash);
    print_test("Prueba hash la cantidad de elementos es 0", hash_cantidad(hash) == 0);
    print_test("Prueba hash obtener clave A, es NULL, no existe", !hash_obtener(hash, "A"));
    print_test("Prueba hash pertenece clave A, es false, no existe", !hash_pertenece(hash, "A"));
    print_test("Prueba hash borrar clave A, es NULL, no existe", !hash_borrar(hash, "A"));

    hash_destruir(hash);
}

static void prueba_iterar_hash_vacio()
{
    printf("\nPRUEBA ITERAR HASH VACIO\n");

    hash_t* hash = hash_crear(NULL);
    hash_iter_t* iter = hash_iter_crear(hash);
    print_test("Prueba hash iter crear iterador hash vacio", iter);
    print_test("Prueba hash iter esta al final", hash_iter_al_final(iter));
    print_test("Prueba hash iter avanzar es false", !hash_iter_avanzar(iter));
    print_test("Prueba hash iter ver actual es NULL", !hash_iter_ver_actual(iter));

    hash_iter_destruir(iter);
    hash_destruir(hash);
}

static void prueba_hash_insertar()
{
    printf("\nPRUEBA HASH INSERTAR\n");

    hash_t* hash = hash_crear(NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba hash insertar clave1", hash_guardar(hash, clave1, valor1));
    print_test("Prueba hash la cantidad de elementos es 1", hash_cantidad(hash) == 1);
    print_test("Prueba hash obtener clave1 es valor1", hash_obtener(hash, clave1) == valor1);
    print_test("Prueba hash obtener clave1 es valor1", hash_obtener(hash, clave1) == valor1);
    print_test("Prueba hash pertenece clave1, es true", hash_pertenece(hash, clave1));
    print_test("Prueba hash borrar clave1, es valor1", hash_borrar(hash, clave1) == valor1);
    print_test("Prueba hash la cantidad de elementos es 0", hash_cantidad(hash) == 0);

    /* Inserta otros 2 valores y no los borra (se destruyen con el hash) */
    print_test("Prueba hash insertar clave2", hash_guardar(hash, clave2, valor2));
    print_test("Prueba hash la cantidad de elementos es 1", hash_cantidad(hash) == 1);
    print_test("Prueba hash obtener clave2 es valor2", hash_obtener(hash, clave2) == valor2);
    print_test("Prueba hash obtener clave2 es valor2", hash_obtener(hash, clave2) == valor2);
    print_test("Prueba hash pertenece clave2, es true", hash_pertenece(hash, clave2));

    print_test("Prueba hash insertar clave3", hash_guardar(hash, clave3, valor3));
    print_test("Prueba hash la cantidad de elementos es 2", hash_cantidad(hash) == 2);
    print_test("Prueba hash obtener clave3 es valor3", hash_obtener(hash, clave3) == valor3);
    print_test("Prueba hash obtener clave3 es valor3", hash_obtener(hash, clave3) == valor3);
    print_test("Prueba hash pertenece clave3, es true", hash_pertenece(hash, clave3));

    hash_destruir(hash);
}



static void prueba_hash_reemplazar()
{
    printf("\nPRUEBA HASH REEMPLAZAR\n");

    hash_t* hash = hash_crear(NULL);

    char *clave1 = "perro", *valor1a = "guau", *valor1b = "warf";
    char *clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";

    // Inserta 2 valores y luego los reemplaza
    print_test("Prueba hash insertar clave1", hash_guardar(hash, clave1, valor1a));
    print_test("Prueba hash obtener clave1 es valor1a", hash_obtener(hash, clave1) == valor1a);
    print_test("Prueba hash obtener clave1 es valor1a", hash_obtener(hash, clave1) == valor1a);
    print_test("Prueba hash insertar clave2", hash_guardar(hash, clave2, valor2a));
    print_test("Prueba hash obtener clave2 es valor2a", hash_obtener(hash, clave2) == valor2a);
    print_test("Prueba hash obtener clave2 es valor2a", hash_obtener(hash, clave2) == valor2a);
    print_test("Prueba hash la cantidad de elementos es 2", hash_cantidad(hash) == 2);

    print_test("Prueba hash insertar clave1 con otro valor", hash_guardar(hash, clave1, valor1b));
    print_test("Prueba hash obtener clave1 es valor1b", hash_obtener(hash, clave1) == valor1b);
    print_test("Prueba hash obtener clave1 es valor1b", hash_obtener(hash, clave1) == valor1b);
    print_test("Prueba hash insertar clave2 con otro valor", hash_guardar(hash, clave2, valor2b));
    print_test("Prueba hash obtener clave2 es valor2b", hash_obtener(hash, clave2) == valor2b);
    print_test("Prueba hash obtener clave2 es valor2b", hash_obtener(hash, clave2) == valor2b);
    print_test("Prueba hash la cantidad de elementos es 2", hash_cantidad(hash) == 2);

    hash_destruir(hash);
}


static void prueba_hash_borrar()
{
    printf("\nPRUEBA HASH BORRAR\n");

    hash_t* hash = hash_crear(NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    // Inserta 3 valores y luego los borra 
    print_test("Prueba hash insertar clave1", hash_guardar(hash, clave1, valor1));
    print_test("Prueba hash insertar clave2", hash_guardar(hash, clave2, valor2));
    print_test("Prueba hash insertar clave3", hash_guardar(hash, clave3, valor3));

    // Al borrar cada elemento comprueba que ya no está pero los otros sí.
    print_test("Prueba hash pertenece clave3, es verdadero", hash_pertenece(hash, clave3));
    print_test("Prueba hash borrar clave3, es valor3", hash_borrar(hash, clave3) == valor3);
    print_test("Prueba hash borrar clave3, es NULL", !hash_borrar(hash, clave3));
    print_test("Prueba hash pertenece clave3, es falso", !hash_pertenece(hash, clave3));
    print_test("Prueba hash obtener clave3, es NULL", !hash_obtener(hash, clave3));
    print_test("Prueba hash la cantidad de elementos es 2", hash_cantidad(hash) == 2);

    print_test("Prueba hash pertenece clave1, es verdadero", hash_pertenece(hash, clave1));
    print_test("Prueba hash borrar clave1, es valor1", hash_borrar(hash, clave1) == valor1);
    print_test("Prueba hash borrar clave1, es NULL", !hash_borrar(hash, clave1));
    print_test("Prueba hash pertenece clave1, es falso", !hash_pertenece(hash, clave1));
    print_test("Prueba hash obtener clave1, es NULL", !hash_obtener(hash, clave1));
    print_test("Prueba hash la cantidad de elementos es 1", hash_cantidad(hash) == 1);

    print_test("Prueba hash pertenece clave2, es verdadero", hash_pertenece(hash, clave2));
    print_test("Prueba hash borrar clave2, es valor2", hash_borrar(hash, clave2) == valor2);
    print_test("Prueba hash borrar clave2, es NULL", !hash_borrar(hash, clave2));
    print_test("Prueba hash pertenece clave2, es falso", !hash_pertenece(hash, clave2));
    print_test("Prueba hash obtener clave2, es NULL", !hash_obtener(hash, clave2));
    print_test("Prueba hash la cantidad de elementos es 0", hash_cantidad(hash) == 0);

    hash_destruir(hash);
}


static void prueba_hash_clave_vacia()
{
    printf("\nPRUEBA HASH CLAVE VACIA\n");
    hash_t* hash = hash_crear(NULL);

    char *clave = "", *valor = "";

    print_test("Prueba hash insertar clave vacia", hash_guardar(hash, clave, valor));
    print_test("Prueba hash la cantidad de elementos es 1", hash_cantidad(hash) == 1);
    print_test("Prueba hash obtener clave vacia es valor", hash_obtener(hash, clave) == valor);
    print_test("Prueba hash pertenece clave vacia, es true", hash_pertenece(hash, clave));
    print_test("Prueba hash borrar clave vacia, es valor", hash_borrar(hash, clave) == valor);
    print_test("Prueba hash la cantidad de elementos es 0", hash_cantidad(hash) == 0);

    hash_destruir(hash);
}

static void prueba_hash_valor_null()
{
    printf("\nPRUEBA HASH VALOR NULL\n");

    hash_t* hash = hash_crear(NULL);

    char *clave = "", *valor = NULL;

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba hash insertar clave vacia valor NULL", hash_guardar(hash, clave, valor));
    print_test("Prueba hash la cantidad de elementos es 1", hash_cantidad(hash) == 1);
    print_test("Prueba hash obtener clave vacia es valor NULL", hash_obtener(hash, clave) == valor);
    print_test("Prueba hash pertenece clave vacia, es true", hash_pertenece(hash, clave));
    print_test("Prueba hash borrar clave vacia, es valor NULL", hash_borrar(hash, clave) == valor);
    print_test("Prueba hash la cantidad de elementos es 0", hash_cantidad(hash) == 0);

    hash_destruir(hash);
}


/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/


void pruebas_hash_catedra()
{
    /* Ejecuta todas las pruebas unitarias. */
    prueba_crear_hash_vacio();
    prueba_iterar_hash_vacio();
    prueba_hash_insertar();
    prueba_hash_reemplazar();
    prueba_hash_borrar();
    prueba_hash_clave_vacia();
    prueba_hash_valor_null();
}

int main() {
    pruebas_hash_catedra();
    return 0;
}



















