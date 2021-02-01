#include "tp0.h"

/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap (int *x, int *y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}


int maximo(int vector[], int n) {
    int posicion = 0; 
    if(n == 0){
        return -1;
    }
    for(int i = 0; i < n; i++){
        if(vector[i] > vector[posicion]){
            posicion = i;
        }
    }
    return posicion;
}



int comparar(int vector1[], int n1, int vector2[], int n2){
    
    for (int i = 0; i < n1 && i < n2; i++)
    {
        if(vector1[i] < vector2[i]){
            return -1;
        }else if(vector1[i] > vector2[i]){
            return 1;
        }
    }
    if(n1 < n2){
        return -1;
    }else if( n1 > n2){
        return 1;
    }else{
        return 0;
    }
}


void seleccion(int vector[], int n) {
    for(int contador = 0; contador < n; contador ++){
        int posicion_del_maximo = maximo(vector, n - contador);
        swap(&vector[posicion_del_maximo], &vector[n - contador -1]);
    }
}
