#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "strutil.h"
#include "pila.h"

int* valor(pila_t* pila){
    if(pila_esta_vacia(pila)) return NULL;
    int* valor = pila_desapilar(pila);
    return valor;
}

void limpia_valores(int* valor1, int* valor2){
    if(valor1)free(valor1);
    if(valor2)free(valor2);
}

void limpia(pila_t* pila, char** lista){
    free_strv(lista);
    while(!pila_esta_vacia(pila)){
		limpia_valores(pila_desapilar(pila), NULL);
	}
	pila_destruir(pila);
}

bool suma(pila_t* pila){
    if(pila_esta_vacia(pila)){
        return false;
    }
    int* valor2 = valor(pila);

    if(pila_esta_vacia(pila)){ 
        free(valor2);
        return false;}
    int* valor1 = valor(pila);
    int* suma = malloc(sizeof(int));
    if(!suma) {
        limpia_valores(valor1, valor2);
        return false;}
    *suma = *valor1 + *valor2;
    pila_apilar(pila, suma);
    limpia_valores(valor1, valor2);
    return true;
}

bool resta(pila_t* pila){
    if(pila_esta_vacia(pila)){
        return false;
    }
    int* valor2 = valor(pila);
    int* valor1 = valor(pila);
    int* resta = malloc(sizeof(int));
    if(!resta){
        limpia_valores(valor1, valor2);
        return false;}
    *resta = *valor1 - *valor2;
    pila_apilar(pila, resta);
    limpia_valores(valor1, valor2);
    return true;
}

bool multiplica(pila_t* pila){
    if(pila_esta_vacia(pila)){
        return false;
    }
    int* valor2 = valor(pila);
    int* valor1 = valor(pila);
    int* multiplicacion = malloc(sizeof(int));
    if(!multiplicacion) return false;
    *multiplicacion = *valor1 * *valor2;
    pila_apilar(pila, multiplicacion);
    limpia_valores(valor1, valor2);
    return true;
}

bool exponenciacion(pila_t* pila){
    if(pila_esta_vacia(pila)){
        return false;
    }
    int* valor2 = valor(pila);
    int* valor1 = valor(pila);
    if(*valor2 < 0){
        limpia_valores(valor1, valor2);
        return false;}
    int* resultado = malloc(sizeof(int));
    if(!resultado) return false;
    *resultado = pow(*valor1, *valor2);
    pila_apilar(pila, resultado);
    limpia_valores(valor1, valor2);
    return true;
}

bool division(pila_t* pila){
    if(pila_esta_vacia(pila)){
        return false;
    }
    int* valor2 = valor(pila);
    int* valor1 = valor(pila);
    if(*valor2 == 0){
        limpia_valores(valor1, valor2);
        
        return false;}
    int* division = malloc(sizeof(int));
    if(!division) return false;
    *division = (*valor1 / *valor2);
    pila_apilar(pila, division);
    limpia_valores(valor1, valor2);
    return true;
}

bool logaritmo(pila_t* pila){
    if(pila_esta_vacia(pila)){
        return false;
    }
    int* valor2 = valor(pila);
    int* valor1 = valor(pila);
    if(*valor2 < 2){ 
        limpia_valores(valor1, valor2);
        return false;}
    int* resultado = malloc(sizeof(int));
    if(!resultado) return false;
    *resultado = (log(*valor1) / log(*valor2));
    pila_apilar(pila, resultado);
    limpia_valores(valor1, valor2);
    return true;
}

bool ternario(pila_t* pila){
    if(pila_esta_vacia(pila)){
        return false;
    }
    int* falso = valor(pila);
    int* verdadero = valor(pila);
    if(pila_esta_vacia(pila)){
        limpia_valores(falso, verdadero);
        return false;
    }
    int* condicion = valor(pila);
    pila_apilar(pila, *condicion ? verdadero : falso);
    limpia_valores(condicion, *condicion ? falso : verdadero);
    return true;
}

bool raiz(pila_t* pila){
    if(pila_esta_vacia(pila)){
        return false;
    }
    int* valor1 = valor(pila);
    if(*valor1 < 0) {
        limpia_valores(valor1, NULL);
        return false;}
    int* raiz = malloc(sizeof(int));
    *raiz = sqrt(*valor1);
    pila_apilar(pila, raiz);
    limpia_valores(valor1, NULL);
    return true;
}

void operando(pila_t* pila, char* dato, bool* ok){
    if(strcmp(dato, "+") == 0){ *ok = suma(pila);}
    else if(strcmp(dato, "-") == 0) *ok = resta(pila);
    else if(strcmp(dato, "*") == 0) *ok = multiplica(pila);
    else if(strcmp(dato, "^") == 0) *ok = exponenciacion(pila);
    else if(strcmp(dato, "/") == 0) *ok = division(pila);
    else if(strcmp(dato, "log") == 0) *ok = logaritmo(pila);
    else if(strcmp(dato, "?") == 0) *ok = ternario(pila);
    else if(strcmp(dato, "sqrt") == 0) *ok = raiz(pila);
    else *ok = false;
}

void calculadora(char* datos){
    pila_t* pila = pila_crear();

    char** lista_datos = split(datos,' ');
    
    bool ok = true;

    for (size_t i = 0; lista_datos[i]; i++){
        int* numero = malloc(sizeof(int));
        *numero = atoi(lista_datos[i]);
        if(*numero || strcmp(lista_datos[i],"0") == 0){ 
            int len = strlen(lista_datos[i]);
            char* p = lista_datos[i];
            for (size_t j = 0; j < len; j++){
                if(!isdigit(p[j])){
                    if(p[j] == '-'){
                    }
                    else{
                        ok = false;
                        break;
                    }
                }
            }
            if(!ok){
                free(numero);
                break;
            }else{
                pila_apilar(pila,numero);
            }
        }
        else{
            free(numero);
            operando(pila, lista_datos[i],&ok);
            if(!ok){
                break;
            }
        }
    }
    if(!ok) fprintf(stdout,"%s\n","ERROR");
    else{
        int* resp = pila_desapilar(pila);
        if(pila_esta_vacia(pila)) fprintf(stdout,"%d\n",*resp);
        else{ fprintf(stdout,"%s\n","ERROR");}
        free(resp);
    }
    limpia(pila, lista_datos);
}

void lee_archivo(){
    size_t cont = 0;
    char* linea = NULL;
    while(getline(&linea, &cont, stdin) != -1){
        if(linea[strlen(linea)-1] == '\n'){
            linea[strlen(linea)-1] = '\0';}
        calculadora(linea);
    }
    free(linea);
}

int main(){

    lee_archivo();

    return 0;
}