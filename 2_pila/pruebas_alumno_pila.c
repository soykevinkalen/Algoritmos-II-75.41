#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void crear_y_destruir_pila(){
    /* Declaro las variables a utilizar*/
    pila_t* pila = pila_crear();

    /* Inicio de pruebas */
    print_test("Crear pila", pila != NULL);
    print_test("Pila vacia", pila_esta_vacia(pila) == true);
    print_test("Ver tope en pila recién creada", pila_ver_tope(pila) == NULL);
    print_test("Desapilar una pila recién creada", pila_desapilar(pila) == NULL);

    /* Destruyo la pila*/
    pila_destruir(pila);
    print_test("La pila fue destruida", true);
}

void apilo_y_desapilo_distintos_elementos(){

    /* Declaro las variables a utilizar*/
    pila_t* pila = pila_crear();
    int n0 = 4;
    char a0 = 'A';
    double d0 = 3.78;

    /* Apilo los elementos */
    pila_apilar(pila, &n0);
    pila_apilar(pila, &a0);
    pila_apilar(pila, &d0);

    /* Verifico que la pila no este vacia*/
    print_test("Pila cargada", !pila_esta_vacia(pila));

    /* Verifico que el tope sea correcto y desapilo*/
    print_test("Tope correcto de tipo double", (*((double*)pila_ver_tope(pila))) == d0);
    pila_desapilar(pila);
    print_test("Tope correcto de tipo char", (*((char*)pila_ver_tope(pila))) == a0);
    pila_desapilar(pila);
    print_test("Tope correcto de tipo int", (*((int*)pila_ver_tope(pila))) == n0);
    pila_desapilar(pila);

    /* Verifico que la pila este vacia*/
    print_test("Pila vacia", pila_esta_vacia(pila));

    /* Destruyo la pila*/
    pila_destruir(pila);
    print_test("La pila fue destruida", true);
}
void apilo_y_desapilo_x2(){
    /* Declaro las variables a utilizar */
    pila_t* pila = pila_crear();
    char a = 'e', b = 'j';
    int n = 89;
    
    /* Apilo un elemento */
    pila_apilar(pila, &a);

    /* Verifico que la pila no este vacia */
    print_test("Pila cargada", !pila_esta_vacia(pila));

    /* Verifico tope y desapilo*/
    print_test("Tope correcto de tipo char", (*((char*)pila_ver_tope(pila))) == a);
    pila_desapilar(pila);

    /* Verifico que la pila este vacia */
    print_test("Pila vacia", pila_esta_vacia(pila));

    /* Apilo elementos en una pila recién desapilada*/
    pila_apilar(pila, &b);
    pila_apilar(pila, &n);

    /* Verifico que la pila no este vacia */
    print_test("Pila cargada", !pila_esta_vacia(pila));

    /* Verifico tope y desapilo*/
    print_test("Tope correcto de tipo int", (*((int*)pila_ver_tope(pila))) == n);
    pila_desapilar(pila);
    print_test("Tope correcto de tipo char", (*((char*)pila_ver_tope(pila))) == b);
    pila_desapilar(pila);

    /* Verifico que la pila este vacia */
    print_test("Pila vacia", pila_esta_vacia(pila));

    /* Destruyo la pila*/
    pila_destruir(pila);
    print_test("La pila fue destruida", true);


}
void apilo_y_desapilo_muchos_elementos(){

    /* Declaro las variables a utilizar */
    pila_t* pila = pila_crear();
    bool ok;
    size_t n = 1000;
    int* vector = malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++){
        vector[i] = i;
    }
    for (size_t i = 0; i < n; i++){
        ok = pila_apilar(pila,&vector[i]);
    }   
    
    print_test("Apilar 1000 elementos", ok);
    /* Verifico si la pila no esta vacia */
    print_test("La pila no esta vacia", !pila_esta_vacia(pila)); 

    /* Verifico si el tope es 999 */
    print_test("Tope correcto, el tope es 999", (*((int*)pila_ver_tope(pila))) == 999);
    
    /* Desapilo */

    for (int i = 999; 0 <= i; i--){
        printf("%d",i);
        print_test(" desapilado", (*((int*)pila_desapilar(pila))) == i);
    }
    print_test("La pila esta vacia", pila_esta_vacia(pila));
    /* Verifico que ver tope y desapilar son invalidos */
    print_test("Ver tope en pila recién desapilada", pila_ver_tope(pila) == NULL);
    print_test("Desapilar una pila recién desapilada", pila_desapilar(pila) == NULL);

    /* Verifico si la pila esta vacia */
    print_test("La pila esta vacia", pila_esta_vacia(pila) == true ); 

    /* Destruyo la pila */
    free(vector);
    pila_destruir(pila);
    print_test("La pila fue destruida", true);

}

void pruebas_pila_alumno() {
    crear_y_destruir_pila();
    apilo_y_desapilo_distintos_elementos();
    apilo_y_desapilo_x2();
    apilo_y_desapilo_muchos_elementos();
}
