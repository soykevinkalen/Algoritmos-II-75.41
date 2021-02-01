#include "cola.h"
#include "vector.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>

void crear_y_destruir_cola(){
    
    /* Declaro las variables a utilizar */
    cola_t* cola = cola_crear();

    /* Inicio las pruebas */
    print_test("Crear cola", cola != NULL);
    print_test("Cola vacia", cola_esta_vacia(cola));
    print_test("Ver primero en cola recién creada", cola_ver_primero(cola) == NULL);
    print_test("Desencolar una cola recién creada", cola_desencolar(cola) == NULL);

    /* Destruyo la cola */
    cola_destruir(cola,NULL);
    print_test("La cola ha sido destruida", true);
}

void encolo_y_desencolo_un_elemento(){
    
    /* Declaro las variables a utilizar */
    cola_t* cola = cola_crear();
    char a = 'o';
    print_test("Crear una cola", cola!=NULL);
    /* Encolo elemento */
    print_test("Encolo un elemento",cola_encolar(cola, &a));

    /* Verifico que la cola no este vacia */
    print_test("La cola no esta vacia", !cola_esta_vacia(cola));

    /* Verifico que el elemento encolado sea el correcto*/
    print_test("Ver primero", (*((char*)cola_ver_primero(cola))) == a);

    /* Desencolo el elemento */
    print_test("Elemento desencolado",(*((char*)cola_desencolar(cola))) == a);

    /* Verifico que la cola este vacia */
    print_test("La cola esta vacia", cola_esta_vacia(cola));

    /* Destruyo la cola y paso como parametro NULL*/
    cola_destruir(cola, NULL);

    print_test("Fin de la prueba", true);

}

void pruebas_null(){
    cola_t* cola = cola_crear();
    print_test("Cola creada", cola!= NULL);
    print_test("Encolar un elemento NULL", cola_encolar(cola,NULL));
    print_test("La cola no esta vacia", !cola_esta_vacia(cola));
    print_test("El primero de la cola es NULL", cola_ver_primero(cola)==NULL);
    print_test("Desencolar devuelve NULL", cola_desencolar(cola)==NULL);
	print_test("Se vacio la cola", cola_esta_vacia(cola));
	cola_destruir(cola,NULL);
	print_test("La cola ha sido destruida", true);
}

void vector_destruir_wrapper(void* dato){
    vector_destruir(dato);
}

void pruebas_con_vector(){
    vector_t* vector = vector_crear(10);
    print_test("Vector creado", vector!=NULL);
    bool guardado = true;
    for(size_t i = 0; i < 10; i++){
        guardado &= vector_guardar(vector,i,((int)i + 1));
    }
    print_test("Vector lleno", guardado);
    cola_t* cola = cola_crear();
    print_test("Cola creada", cola!=NULL);
    print_test("Encolar vector", cola_encolar(cola,vector));
    print_test("El primero es el vector", cola_ver_primero(cola) == vector);
    print_test("Cola no vacia", !cola_esta_vacia(cola));
    cola_destruir(cola,vector_destruir_wrapper);
    print_test("La cola ha sido destruida", true);
}

void pruebas_volumen(){
    cola_t* cola = cola_crear();
    bool ok;
    size_t n = 1000;
    int* vector = malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++){
        vector[i] = i;
    }
    for (size_t i = 0; i < n; i++){
        ok = cola_encolar(cola,&vector[i]);
    }
    print_test("1000 elementos encolados", ok);
    print_test("La cola no esta vacia", !cola_esta_vacia(cola));
    print_test("El primer elemento es el 0", (*((int*)cola_ver_primero(cola))) == 0);
    for (int i = 0; i < n; i++){
        ok &= (cola_desencolar(cola) == &vector[i]);
    }
    print_test("Se desencolaron todos los elementos", ok);
    print_test("Cola vacia", cola_esta_vacia(cola));
    free(vector);
    cola_destruir(cola, NULL);
    print_test("La cola ha sido destruido", ok);     
}

void pruebas_operaciones_intercaladas(){
    cola_t* cola = cola_crear();
    bool ok;
    size_t n = 10;
    int* vector = malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++){
        vector[i] = i;
    }
    for (size_t i = 0; i < n; i++){
        ok = cola_encolar(cola,&vector[i]);
    }
    print_test("10 elementos encolados", ok);
    print_test("La cola no esta vacia", !cola_esta_vacia(cola));
    print_test("El primer elemento es el 0", (*((int*)cola_ver_primero(cola))) == 0);
    for (int i = 0; i < n; i++){
        printf("%d",i);
        print_test(" desencolado", (*((int*)cola_desencolar(cola))) == i);
    }
    print_test("La cola está vacia", cola_esta_vacia(cola));
    char a = 't', b = 'u';
    int o = 90;
    for (size_t i = 0; i < n; i++){
        ok = cola_encolar(cola, &a);
        ok = cola_encolar(cola, &b);
        ok = cola_encolar(cola, &o);
    }
    print_test("30 elementos encolados", ok);
    print_test("La cola no esta vacia", !cola_esta_vacia(cola));
    print_test("El primer elemento correcto", (*((char*)cola_ver_primero(cola))) == a);
    for (int i = 0; i < n; i++){
        printf("%c",a);
        print_test(" desencolado", (*((char*)cola_desencolar(cola))) == a);
        printf("%c",b);
        print_test(" desencolado", (*((char*)cola_desencolar(cola))) == b);
        printf("%d",o);
        print_test(" desencolado", (*((int*)cola_desencolar(cola))) == o);

    }
    print_test("La cola está vacia", cola_esta_vacia(cola));
    free(vector);
    cola_destruir(cola, NULL);
    print_test("La cola ha sido destruido", ok); 
}

void pruebas_destruccion_cola_vacia(){
    cola_t* cola = cola_crear();
    print_test("Cola creada", cola!= NULL);
    print_test("La cola esta vacia", cola_esta_vacia(cola));
    cola_destruir(cola, NULL);
    print_test("La cola ha sido destruida", true); 
}

void pruebas_destruccion_cola_no_vacia(){
    cola_t* cola = cola_crear();
    bool ok = true;
    print_test("Cola creada", cola!= NULL);
    print_test("Encolo un elemento", cola_encolar(cola, &ok));
    print_test("La cola no esta vacia", !cola_esta_vacia(cola));
    print_test("El elemento es el recién agregado", cola_ver_primero(cola) == &ok);   
    cola_destruir(cola, NULL);
    print_test("La cola ha sido destruida", true);
}

void pruebas_destruccion_no_null_cola_vacia(){
    cola_t* cola = cola_crear();
    print_test("Cola creada", cola!= NULL);
    print_test("La cola esta vacia", cola_esta_vacia(cola));
    cola_destruir(cola, free);
    print_test("La cola ha sido destruida", true); 
}

void pruebas_destruccion_no_null_cola_no_vacia(){
    cola_t* cola = cola_crear();
    int* vector = malloc(sizeof(int));
    vector[0] = 78;
    print_test("Cola creada", cola!= NULL);
    print_test("Encolo un elemento", cola_encolar(cola, &vector[0]));
    print_test("La cola no esta vacia", !cola_esta_vacia(cola));
    print_test("El elemento es el recién agregado", cola_ver_primero(cola) == &vector[0]);   
    cola_destruir(cola, free);
    print_test("La cola ha sido destruida", true);
}
void pruebas_cola_alumno(void){
    crear_y_destruir_cola();
    encolo_y_desencolo_un_elemento();
    pruebas_null();
    pruebas_con_vector();
    pruebas_volumen();
    pruebas_operaciones_intercaladas();
    pruebas_destruccion_cola_vacia();
    pruebas_destruccion_cola_no_vacia();
    pruebas_destruccion_no_null_cola_vacia();
    pruebas_destruccion_no_null_cola_no_vacia();
}