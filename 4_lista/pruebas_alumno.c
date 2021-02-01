#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void crear_destruir_lista(){
    lista_t* lista = lista_crear();
    print_test("Lista creada", lista!=NULL);
    print_test("Lista esta vacia", lista_esta_vacia(lista));
    print_test("Lista tiene 0 elementos", lista_largo(lista) == 0);
    print_test("El primer elemento es NULL", lista_ver_primero(lista) == NULL);
    print_test("Borro el primer elemento", lista_borrar_primero(lista) == NULL);
    print_test("El ultimo elemento es NULL", lista_ver_ultimo(lista) == NULL);
    lista_destruir(lista, NULL);
    print_test("La lista ha sido destruida", true);
}

void prueba_null(){
    lista_t* lista = lista_crear();
    print_test("Lista esta vacia", lista_esta_vacia(lista));
    print_test("Agregamos el elemento NULL", lista_insertar_primero(lista, NULL));
    print_test("La lista NO esta vacia", !lista_esta_vacia(lista));
    print_test("La lista tiene un solo elemento", lista_largo(lista)==1);
    print_test("El primero es el elemento NULL", lista_ver_primero(lista)==NULL);
    print_test("Elimino y devuelve NULL", lista_borrar_primero(lista) == NULL);
    lista_destruir(lista, NULL);
    print_test("La lista ha sido destruida", true);
}

void prueba_algunos_elementos(){
    lista_t* lista = lista_crear();
    int n = 7;
    char y = 'p';
    print_test("Agregamos el primer elemento", lista_insertar_primero(lista, &y));
    print_test("Agregamos el segundo elemento", lista_insertar_ultimo(lista, &n));
  	print_test("El largo de la lista es 2", lista_largo(lista)==2);
    print_test("El primer elemento es el primero que agregué", (*((char*)lista_ver_primero(lista))) == y);
    print_test("El ultimo elemento es el ultimo que agregué", lista_ver_ultimo(lista) == &n);
    print_test("Elimino el primer elemento", lista_borrar_primero(lista) == &y);
    print_test("Elimino el primer elemento y ultimo que queda", lista_borrar_primero(lista) == &n);
    print_test("La lista esta vacia", lista_esta_vacia(lista));
    lista_destruir(lista, NULL);
    print_test("La lista ha sido destruida", true);


}

void prueba_de_volumen(){
    lista_t* lista = lista_crear();
    bool ok;
    size_t numero = 1000;
    int *vector = malloc(sizeof(int)*numero);
    for (int i = 0; i < numero; i++)
    {
        vector[i] = i;
    }
    for (size_t i = 0; i < numero; i++)
    {
        ok = lista_insertar_ultimo(lista,&vector[i]);

    }
    print_test("Lista con 1000 elementos", ok);
    print_test("La lista no esta vacia", !lista_esta_vacia(lista));
	print_test("El largo de la lista es 1000", lista_largo(lista)==1000);
    print_test("El primer elemento es el 0", (*((int*)lista_ver_primero(lista))) == 0);
    print_test("El ultimo elemento es el 999", (*((int*)lista_ver_ultimo(lista))) == 999);
    
    for (int i = 0; i < numero; i++)
    {   
        ok &= (lista_borrar_primero(lista) == &vector[i]);
    }
   	print_test("Los elementos fueron eliminados", ok);
    print_test("La lista esta vacia", lista_esta_vacia(lista));
    free(vector);
    lista_destruir(lista, NULL);
    print_test("La lista ha sido destruida", true);
}
void prueba_destruccion_lista_vacia(){
    lista_t* lista = lista_crear();
    print_test("Lista creada", lista!=NULL);
    print_test("Lista esta vacia", lista_esta_vacia(lista));
    print_test("Lista tiene 0 elementos", lista_largo(lista) == 0);
    lista_destruir(lista, NULL);
    print_test("La lista ha sido destruida", true);
}
void prueba_destruccion_lista_no_vacia(){
    lista_t* lista = lista_crear();
    int a = 90;
    char b = 'u';
    print_test("Lista creada", lista!=NULL);
    print_test("Lista esta vacia", lista_esta_vacia(lista));
    print_test("Agrego el primer elemento a la lista", lista_insertar_primero(lista,&a));
    print_test("Agrego el segundo elemento a la lista", lista_insertar_ultimo(lista,&b));
    print_test("Primer elemento correcto", lista_ver_primero(lista) == &a);
    print_test("Ultimo elemento correcto", lista_ver_ultimo(lista) == &b);
    print_test("Lista tiene 2 elementos", lista_largo(lista) == 2);
    lista_destruir(lista, NULL);
    print_test("La lista ha sido destruida", true);
}
void prueba_destruccion_no_null_lista_vacia(){
    lista_t* lista = lista_crear();
    print_test("Lista creada", lista!=NULL);
    print_test("Lista esta vacia", lista_esta_vacia(lista));
    print_test("Lista tiene 0 elementos", lista_largo(lista) == 0);
    lista_destruir(lista, free);
    print_test("La lista ha sido destruida", true);
}
void prueba_destruccion_no_null_lista_no_vacia(){
    lista_t* lista = lista_crear();
    print_test("Lista creada", lista!=NULL);
    print_test("Lista esta vacia", lista_esta_vacia(lista));
    int *vector = malloc(sizeof(int));
    vector[0] = 90;
    print_test("Agrego un elemento a la lista", lista_insertar_ultimo(lista,&vector[0]));
    print_test("Lista tiene 1 elemento", lista_largo(lista) == 1);
    print_test("Lista no esta vacia", !lista_esta_vacia(lista));
    lista_destruir(lista, free);
    print_test("La lista ha sido destruida", true);

}

void prueba_casos_bordes(){
    lista_t* lista = lista_crear();
    int n0 = 78, n1 = 89;
    print_test("Agrego un elemento al final", lista_insertar_ultimo(lista, &n0));
    print_test("El primer elemento es un 78", (*((int*)lista_ver_primero(lista))) == n0);
    print_test("El ultimo elemento también es un 78", (*((int*)lista_ver_ultimo(lista))) == n0);
    print_test("Agrego un elemento al final", lista_insertar_ultimo(lista, &n1));
    print_test("El ultimo elemento ahora es 89", (*((int*)lista_ver_ultimo(lista))) == n1);
  	print_test("El largo de la lista es 2", lista_largo(lista)==2);
    lista_destruir(lista, NULL);
    print_test("La lista ha sido destruida", true);
}

void prueba_iterador_externo(){
    lista_t* lista = lista_crear();
    lista_iter_t* iterador = lista_iter_crear(lista);
    print_test("Iterador creado", iterador != NULL);
    int n0 = 34;
    char a = 'a';
    print_test("Agrego un elemento con el iterador", lista_iter_insertar(iterador, &a));
    print_test("El elemento agregado está al principio de la lista", (*((char*)lista_ver_primero(lista))) == a);
    print_test("El iterador está en el principio", (*((char*)lista_iter_ver_actual(iterador))) == a);
    print_test("Avanzo el iterador", lista_iter_avanzar(iterador));
    print_test("El iterador está al final de la lista", lista_iter_al_final(iterador));
    print_test("Agrego un elemento con el iterador", lista_iter_insertar(iterador, &n0));
    print_test("El elemento agregado está al final de la lista", (*((int*)lista_ver_ultimo(lista))) == n0);
    print_test("Borro el ultimo elemento con el iterador", (*((int*)lista_iter_borrar(iterador))) == n0);
    print_test("El iterador está al final de la lista", lista_iter_al_final(iterador));
    lista_iter_destruir(iterador);
    print_test("El iterador ha sido destruido", true);
    print_test("Borro el primer elemento agregado 'a'", (*((char*)lista_borrar_primero(lista))) == a);
    print_test("Lista vacia", lista_esta_vacia(lista));
    lista_destruir(lista, NULL);
    print_test("La lista ha sido destruida", true);
}

void prueba_iter_elemento_en_el_medio(){
    lista_t* lista = lista_crear();
    lista_iter_t* iterador = lista_iter_crear(lista);
    print_test("Iterador creado", iterador != NULL);
    int n0 = 34, n1 = 90;
    char a = 'a';
    print_test("Agrego el primer elemento con el iterador", lista_iter_insertar(iterador, &n0));
    print_test("Agrego el segundo elemento con el iterador", lista_iter_insertar(iterador, &n1));
    print_test("El largo de la lista es 2", lista_largo(lista)==2);
    print_test("El primer elemento es el 90", (*((int*)lista_ver_primero(lista))) == n1);
    print_test("El ultimo elemento es el 34", (*((int*)lista_ver_ultimo(lista))) == n0);
    print_test("El iterador está en el 90", (*((int*)lista_iter_ver_actual(iterador))) == n1);
    print_test("Avanzo el iterador", lista_iter_avanzar(iterador));
    print_test("El iterador está en el 34", (*((int*)lista_iter_ver_actual(iterador))) == n0);
    print_test("Agrego el elemento en el medio con el iterador", lista_iter_insertar(iterador, &a));
    print_test("El largo de la lista es 3", lista_largo(lista)==3);
    print_test("El iterador está en el elemento a", (*((char*)lista_iter_ver_actual(iterador))) == a);
    print_test("El primer elemento sigue siendo el 90", (*((int*)lista_ver_primero(lista))) == n1);
    print_test("El ultimo elemento sigue siendo el 34", (*((int*)lista_ver_ultimo(lista))) == n0);
    print_test("Avanzo el iterador", lista_iter_avanzar(iterador));
    print_test("El iterador no está al final de la lista", !lista_iter_al_final(iterador));
    print_test("Avanzo el iterador", lista_iter_avanzar(iterador));
    print_test("El iterador está al final de la lista", lista_iter_al_final(iterador));
    lista_iter_destruir(iterador);
    print_test("El iterador ha sido destruido", true);
    lista_destruir(lista, NULL);
    print_test("La lista ha sido destruida", true);
}

void prueba_iter_remover_primer_elemento(){
    lista_t* lista = lista_crear();
    bool ok;
    int i = 0, j = 5, k = 89;
    ok = lista_insertar_ultimo(lista,&i);
    ok = lista_insertar_ultimo(lista,&j);
    ok = lista_insertar_ultimo(lista,&k);
    print_test("Se agregaron 3 elementos a la lista", ok);
    print_test("El largo de la lista es 3", lista_largo(lista)==3);
    print_test("El primer elemento es el 0", (*((int*)lista_ver_primero(lista))) == 0);
    print_test("El ultimo elemento es el 89", (*((int*)lista_ver_ultimo(lista))) == 89);
    lista_iter_t* iterador = lista_iter_crear(lista);
    print_test("Iterador creado", iterador != NULL);
    print_test("Elimino el elemento de un iterador recién creado", (*((int*)lista_iter_borrar(iterador))) == i);
    print_test("El largo de la lista es 2", lista_largo(lista)==2);
    print_test("El primer elemento es el 5", (*((int*)lista_ver_primero(lista))) == 5);
    lista_iter_destruir(iterador);
    print_test("El iterador ha sido destruido", true);
    lista_destruir(lista, NULL);
    print_test("La lista ha sido destruida", true);
}

void prueba_iter_remover_ultimo_elemento(){
    lista_t* lista = lista_crear();
    bool ok;
    int i = 0, j = 5, k = 89;
    ok = lista_insertar_ultimo(lista,&i);
    ok = lista_insertar_ultimo(lista,&j);
    ok = lista_insertar_ultimo(lista,&k);
    print_test("Se agregaron 3 elementos a la lista", ok);
    print_test("El largo de la lista es 3", lista_largo(lista)==3);
    print_test("El primer elemento es el 0", (*((int*)lista_ver_primero(lista))) == i);
    print_test("El ultimo elemento es el 89", (*((int*)lista_ver_ultimo(lista))) == k);
    lista_iter_t* iterador = lista_iter_crear(lista);
    print_test("Iterador creado", iterador != NULL);
    print_test("El iterador está en el 0", (*((int*)lista_iter_ver_actual(iterador))) == i);
    print_test("Avanzo el iterador", lista_iter_avanzar(iterador));
    print_test("El iterador está en el 5", (*((int*)lista_iter_ver_actual(iterador))) == j);
    print_test("Avanzo el iterador", lista_iter_avanzar(iterador));
    print_test("El iterador está en el 89", (*((int*)lista_iter_ver_actual(iterador))) == k);
    print_test("Elimino el ultimo elemento", (*((int*)lista_iter_borrar(iterador))) == k);
    print_test("El largo de la lista es 2", lista_largo(lista)==2);
    print_test("El ultimo elemento es el 5", (*((int*)lista_ver_ultimo(lista))) == j);
    lista_iter_destruir(iterador);
    print_test("El iterador ha sido destruido", true);
    lista_destruir(lista, NULL);
    print_test("La lista ha sido destruida", true);
}

void prueba_iter_remover_elemento_del_medio(){
    lista_t* lista = lista_crear();
    bool ok;
    int i = 0, j = 5, k = 89;
    ok = lista_insertar_ultimo(lista,&i);
    ok = lista_insertar_ultimo(lista,&j);
    ok = lista_insertar_ultimo(lista,&k);
    print_test("Se agregaron 3 elementos a la lista", ok);
    print_test("El largo de la lista es 3", lista_largo(lista)==3);
    print_test("El primer elemento es el 0", (*((int*)lista_ver_primero(lista))) == i);
    print_test("El ultimo elemento es el 89", (*((int*)lista_ver_ultimo(lista))) == k);
    lista_iter_t* iterador = lista_iter_crear(lista);
    print_test("Iterador creado", iterador != NULL);
    print_test("El iterador está en el 0", (*((int*)lista_iter_ver_actual(iterador))) == i);
    print_test("Avanzo el iterador", lista_iter_avanzar(iterador));
    print_test("El iterador está en el 5", (*((int*)lista_iter_ver_actual(iterador))) == j);
    print_test("Elimino el elemento del medio", (*((int*)lista_iter_borrar(iterador))) == j);
    print_test("El largo de la lista es 2", lista_largo(lista)==2);
    print_test("El primer elemento es el 0", (*((int*)lista_ver_primero(lista))) == i);
    print_test("El ultimo elemento es el 89", (*((int*)lista_ver_ultimo(lista))) == k);
    lista_iter_destruir(iterador);
    print_test("El iterador ha sido destruido", true);
    lista_destruir(lista, NULL);
    print_test("La lista ha sido destruida", true);
}

bool sumar_datos(void* dato, void* extra){
	int* numero = dato;
	int* suma = extra;
	*suma += *numero;
	return true;
}


// Devuelve la posicion de la primer aparicion del elemento buscado 
bool busca_datos(void* dato, void* extra){

    if( (*((int*)dato)) == 4){

        (*((int*)extra)) ++;

        return false;
    }

    (*((int*)extra)) ++;

    return true;
}

void prueba_iter_interno_condicion_de_corte(){
    lista_t* lista = lista_crear();
    int posicion = -1;
    int vector[] = {0,1,2,3,4,5,6,4};
    for (size_t i = 0; i < 8; i++){
        lista_insertar_ultimo(lista, &vector[i]);
    }
    print_test("Se agregaron 8 elementos a la lista", lista_largo(lista) == 8);
    lista_iterar(lista, busca_datos, &posicion);
    print_test("Encontrado", posicion == 4);
    lista_destruir(lista,NULL);
 	print_test("Lista ha sido destruida", true);
}

void prueba_iter_interno(){
    lista_t* lista = lista_crear();
 	int suma = 0;
 	int arreglo [] = {1,2,3};
 	for(int i=0; i<3; i++){
 		lista_insertar_ultimo(lista,&arreglo[i]);
 	}
    print_test("Se agregaron 3 datos en la lista", lista_largo(lista)==3);
    lista_iterar(lista,sumar_datos,&suma);
 	print_test("La funcion iterar funciona correctamente",true);
 	print_test("El resultado de la funcion sumar es 6", suma==6);
 	lista_destruir(lista,NULL);
 	print_test("Lista ha sido destruida", true);
}

void pruebas_lista_alumno(void){
    // // Pruebas de la lista
    // crear_destruir_lista();
    // prueba_null();
    // prueba_algunos_elementos();
    // prueba_de_volumen();
    // prueba_destruccion_lista_vacia();
    // prueba_destruccion_lista_no_vacia();
    // prueba_destruccion_no_null_lista_vacia();
    // prueba_destruccion_no_null_lista_no_vacia();
    // prueba_casos_bordes();
    // // Pruebas iterador externo
    // prueba_iterador_externo();
    // prueba_iter_elemento_en_el_medio();
    // prueba_iter_remover_primer_elemento();
    // prueba_iter_remover_ultimo_elemento();
    // prueba_iter_remover_elemento_del_medio();
    // // Pruebas iterador interno
    // prueba_iter_interno();
    prueba_iter_interno_condicion_de_corte();
}