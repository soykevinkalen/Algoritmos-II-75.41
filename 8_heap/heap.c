#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

/*Nota: B
Los principales errores que tienen son E01 y E03.
E05 es menos importante pero estaria bueno que entendieran la idea mas que nada.
Lo demas son mas que nada detalles.
*/

#define FACTOR_REDIMENSION 4/5
#define FACTOR_CARGA 16
#define TAMANIO_INICIAL 4

struct heap{
    void** datos;
    cmp_func_t cmp;
    size_t tam;
    size_t cant;
};

heap_t *heap_crear(cmp_func_t cmp){
    heap_t* heap = malloc(sizeof(heap_t));
    if(!heap) return NULL;
    heap->datos = malloc(sizeof(void*)*TAMANIO_INICIAL);
    if(!heap->datos){ 
        free(heap);
        return NULL;
    }
    heap->cmp = cmp;
    heap->cant = 0;
    heap->tam = TAMANIO_INICIAL;
    return heap;
}

bool heap_esta_vacio(const heap_t *heap){
    return heap->cant == 0;
}

void *heap_ver_max(const heap_t *heap){
    if(!heap->cant) return NULL;
    return heap->datos[0];
}

size_t heap_cantidad(const heap_t *heap){
    return heap->cant;
}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)){
    if(destruir_elemento){
        for (size_t i = 0; i < heap->cant; i++){
            destruir_elemento(heap->datos[i]);
        }
    }
    free(heap->datos);
    free(heap);
}

//Intercambia dos punteros genericos dentro de un arreglo.
void swap(void* arreglo[], size_t posicion_1, size_t posicion_2){
	void* aux = arreglo[posicion_1];
	arreglo[posicion_1] = arreglo[posicion_2];
	arreglo[posicion_2] = aux;
}

//Busca la posicion del padre.
size_t obtener_padre(size_t posicion){
    return (posicion-1) / 2;
}

//Busca la posicion del hijo izquierdo.
size_t hijo_izquierdo(size_t posicion){
    return ((2 * posicion) + 1);
}

//Busca la posicion del hijo derecho.
size_t hijo_derecho(size_t posicion){
    return hijo_izquierdo(posicion)+1;
}

//Mueve el elemento en la posicion "pos" del arreglo
//hacia posiciones menores en el arreglo, hasta que se cumpla
//la invariante del heap.
void upheap(void* arreglo[], size_t pos, cmp_func_t cmp){
	if (pos == 0) return;
	size_t padre = obtener_padre(pos);
	if (cmp(arreglo[pos], arreglo[padre]) > 0){
		swap(arreglo,pos,padre);
		upheap(arreglo, padre, cmp);
    }
}

//Mueve un elemento hacia posiciones mayores del arreglo hasta
//que se cumpla la invariante del heap.
void downheap(void* A[], size_t tam, size_t pos, cmp_func_t cmp){
    if (pos >= tam) return;
    size_t padre = pos; 
    size_t izq = hijo_izquierdo(pos); 
    size_t der = hijo_derecho(pos); 
    if (izq < tam && cmp(A[izq], A[padre]) > 0)
        padre = izq;
    if (der < tam && cmp(A[der], A[padre]) > 0)
        padre = der;
    if (padre != pos){
        swap(A, pos, padre);
        downheap(A, tam, padre, cmp);
    }
}

//Convierte el arreglo en un heap de maximos.
void heapify(void* arreglo[], size_t tam, cmp_func_t cmp){
    for (size_t pos = tam/2; pos > 0; pos--){
        downheap(arreglo, tam, pos-1, cmp);
    }
}

//Redimensiona el heap.
//Recibe un heap y un tamanio nuevo.
//Redimensiona con Realloc.
bool heap_redimensionar(heap_t* heap, size_t new_size){
    if(heap->cant <= heap->tam/2 && heap->tam/2 >= TAMANIO_INICIAL){
        new_size /= 2;
    }
    void** datos_nuevos = realloc(heap->datos, sizeof(void*)*new_size);
    if(!datos_nuevos) return false;
    heap->datos = datos_nuevos;
    heap->tam = new_size;
    return true;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp) {
    heap_t* heap = heap_crear(cmp);
    if(!heap) return NULL;
    if(!heap_redimensionar(heap, n)) return NULL;
    for (size_t i = 0; i < n; i ++) {
        heap->datos[i] = arreglo[i];
        heap->cant ++;
    }
    heap->cmp = cmp;
    heap->tam = n;
    heapify(heap->datos, heap->tam, heap->cmp);
    return heap;
}

//Funcion que ordena un arreglo de punteros.
//Recibe una funcion de comparacion.
//Modifica el arreglo in-situ.
void heap_sort(void *elementos[], size_t tam, cmp_func_t cmp){
    heapify(elementos, tam, cmp);
    for (size_t i = tam-1; i > 0; i--){
        swap(elementos,0,i);
        tam--;
        downheap(elementos, tam, 0, cmp);
    }   
}

bool heap_encolar(heap_t *heap, void *elem){
    if(elem == NULL) return false;
    if(heap->cant >= heap->tam*FACTOR_REDIMENSION){
        if(!heap_redimensionar(heap, heap->tam*FACTOR_CARGA)) return false;
    }
    if(heap_esta_vacio(heap)) heap->datos[0] = elem;
    else{
        heap->datos[heap->cant] = elem;
        upheap(heap->datos, heap->cant, heap->cmp);
    }
    heap->cant ++;
    return true;
}

void *heap_desencolar(heap_t *heap){
    if(heap_esta_vacio(heap)) return NULL;
    void* devolver = heap->datos[0];
    heap->datos[0] = heap->datos[heap->cant-1];
    downheap(heap->datos,heap->cant-1,0,heap->cmp);
    if(!heap_redimensionar(heap, heap->tam)) return false;
    heap->cant --;
    return devolver;
}