#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For ssize_t in Linux.


/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/



//Funcion de compararcion 

int comparar_enteros(const void* a, const void* b) {
	int* a_temp = (int*)a;
	int* b_temp = (int*)b;
	if (*a_temp > *b_temp) return 1;
	else if (*a_temp == *b_temp) return 0;
    else return -1;
}



void prueba_crear_heap_vacio() {
    printf("Inicio de pruebas heap vacio\n");
    heap_t* heap = heap_crear(NULL);

    print_test("Prueba heap crear heap vacio", heap);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap obtener clave A, es NULL, no existe", heap_esta_vacio(heap));
    print_test("Prueba heap ver maximo es false", !heap_ver_max(heap));
    print_test("Prueba heap borrar clave A, es NULL, no existe", heap_desencolar(heap) == NULL);

    heap_destruir(heap, NULL);
}

void prueba_encolar_desencolar() {
    printf("\nInicio de pruebas heap encolar y desencolar\n");
    int a = 100;
    int b = 200;
    int c = 300;
    int d = 400;
    int e = 500;
    int f = 600;
    int g = 700;

    heap_t* heap = heap_crear((cmp_func_t)comparar_enteros);

    print_test("El heap fue creado", heap != NULL);
    print_test("Se encolo un 100", heap_encolar(heap, &a));
    print_test("Se encolo un 200", heap_encolar(heap, &b));
    print_test("Se encolo un 300", heap_encolar(heap, &c));
    print_test("Se encolo un 400", heap_encolar(heap, &d));
    print_test("Se encolo un 500", heap_encolar(heap, &e));
    print_test("Se encolo un 600", heap_encolar(heap, &f));
    print_test("Se encolo un 700", heap_encolar(heap, &g));

    print_test("El heap no esta vacio", !heap_esta_vacio(heap));
    print_test("Heap_cantidad es igual a la cantidad de elementos encolados", heap_cantidad(heap) == 7);
    print_test("Heap_ver_max es igual al valor maximo insertado", *(int*)heap_ver_max(heap) == g);
    print_test("Heap desencolar devuelve el maximo valor encolado", *(int*)heap_desencolar(heap) == g);
    print_test("Heap_ver_max es igual al valor maximo insertado", *(int*)heap_ver_max(heap) == f);
    print_test("Heap desencolar devuelve el maximo valor encolado", *(int*)heap_desencolar(heap) == f);
    print_test("Heap_ver_max es igual al valor maximo insertado", *(int*)heap_ver_max(heap) == e);
    print_test("Heap desencolar devuelve el maximo valor encolado", *(int*)heap_desencolar(heap) == e);
    print_test("Heap_ver_max es igual al valor maximo insertado", *(int*)heap_ver_max(heap) == d);
    print_test("Heap desencolar devuelve el maximo valor encolado", *(int*)heap_desencolar(heap) == d);
    print_test("Heap_ver_max es igual al valor maximo insertado", *(int*)heap_ver_max(heap) == c);
    print_test("Heap desencolar devuelve el maximo valor encolado", *(int*)heap_desencolar(heap) == c);
    print_test("Heap_ver_max es igual al valor maximo insertado", *(int*)heap_ver_max(heap) == b);
    print_test("Heap desencolar devuelve el maximo valor encolado", *(int*)heap_desencolar(heap) == b);
    print_test("Heap_ver_max es igual al valor maximo insertado", *(int*)heap_ver_max(heap) == a);
    print_test("Heap desencolar devuelve el maximo valor encolado", *(int*)heap_desencolar(heap) == a);

    print_test("El heap esta vacio luego de desencolar todo", heap_esta_vacio(heap));
    print_test("Heap cantidad es igual a 0 luego de desencolar todo", heap_cantidad(heap) == 0);
    print_test("Ver maximo es NULL luego de desencolar", heap_desencolar(heap) == NULL);

    heap_destruir(heap, NULL);

    print_test("El heap fue destruido", true);
}

void prueba_eliminar_elementos_heap() {
    printf("\nInicio prueba heap con algunos elementos\n");
    int a = 1, b = 2, c = 3;
    
    heap_t* heap = heap_crear((cmp_func_t)comparar_enteros);

    print_test("Inserto 1", heap_encolar(heap, &a));
    print_test("Chequeo que sea el mismo", *(int*)heap_ver_max(heap) == a);
    print_test("Inserto 2", heap_encolar(heap, &b));
    print_test("Chequeo que sea el mismo", *(int*)heap_ver_max(heap) == b);
    print_test("Inserto 3", heap_encolar(heap, &c));
    print_test("Chequeo que sea el mismo", *(int*)heap_ver_max(heap) == c);

    print_test("Desencolo 1", *(int*)heap_desencolar(heap) == c);
    print_test("Desencolo 2", *(int*)heap_desencolar(heap) == b);
    print_test("Desencolo 3", *(int*)heap_desencolar(heap) == a);

    print_test("Esta vacio, el desencolar devolvio NULL", heap_desencolar(heap) == NULL);
    print_test("El heap esta vacio", heap_esta_vacio(heap));
    print_test("La cantidad es 0", heap_cantidad(heap) == 0);        
    
    heap_destruir(heap, NULL);
}


void prueba_volumen() {
    printf("\nInicio de prueba de volumen\n");
    heap_t* heap = heap_crear((cmp_func_t)comparar_enteros);
    int array[2000];
    int cantidad_desencolados = 0;
    int cantidad_encolados = 0;
    
    for (int i = 0; i < 2000; i++) {
        array[i] = i;
    }

    for (int i = 0; i < 2000; i++) {
        heap_encolar(heap, &array[i]);
        cantidad_encolados ++;
    }
    
    print_test("La cantidad de encolados es 2000", cantidad_encolados == 2000);
    print_test("El max es 2000", *(int*)heap_ver_max(heap) == 1999);
    print_test("El heap no se encuenta vacio", !heap_esta_vacio(heap));
    
    for (int i = 0; i < 2000; i++) {
        heap_desencolar(heap);
        cantidad_desencolados ++;
    }
    
    print_test("La cantidad de desencolados es 2000", cantidad_desencolados == 2000);
    print_test("Chequeo que el heap esta vacio", heap_esta_vacio(heap));
    heap_destruir(heap, NULL);
}

void pruebas_func_arreglo(){
    printf("\nInicio de pruebas heap con arreglo\n");
	size_t len = 7;
	int vector[]= { 7, 10, 15, 25, 8, 13, 35 };
	void* array[len];
	
	for(size_t i= 0; i < len; i++) {
		array[i]= vector+i;
	}
	
	heap_t* heap= heap_crear_arr(array, len, (cmp_func_t)comparar_enteros);
	
	print_test("Creo el heap", heap != NULL);
	
	print_test("Prueba heap no esta vacio, TRUE", !heap_esta_vacio(heap));
	print_test("Prueba heap cantidad de elementos 7", heap_cantidad(heap) == len);
	print_test("Prueba heap el maximo es 35", heap_ver_max(heap) == &vector[6]);

	heap_destruir(heap, NULL);
}

void pruebas_heapsort(){
	size_t len = 7;
    bool ok = true;
    int vector[] = {8, 11, 17, 27, 9, 13, 33};
	void* array[len];
	printf("\nPrueba HeapSort\n");
	for(size_t i=0; i < len; i++){
		array[i]= vector+i;
		printf("%i ", *(int*)array[i]);
	}
    print_test(", array desordenado", ok);
	heap_sort(array, len, (cmp_func_t)comparar_enteros);
	for(size_t i = 0; i < len; i++){
		printf("%i ", *(int*)array[i]);
	}
    print_test(", array ordenado", ok);
	heap_t* heap= heap_crear_arr(array, len, (cmp_func_t)comparar_enteros);
	while(!heap_esta_vacio(heap)){
		printf("%i ", *(int*)heap_desencolar(heap));
	}
    print_test(", array desencolado", ok);

    heap_destruir(heap, NULL);
}

/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/


void pruebas_heap_alumno()
{
    prueba_crear_heap_vacio();
    prueba_encolar_desencolar();
    prueba_eliminar_elementos_heap();
    prueba_volumen();
    pruebas_func_arreglo();
    pruebas_heapsort();
}

