#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "strutil.h"
#include "cola.h"
#include "pila.h"

void terminos_sum_rest(char* operador, pila_t* pila, cola_t* cola){
    if(!pila_esta_vacia(pila)){
        char* dato = pila_desapilar(pila);
        if(strcmp(dato, "-") == 0){
            cola_encolar(cola, " ");
            cola_encolar(cola, dato);
            pila_apilar(pila, operador);
        }
        else if(strcmp(dato, "+") == 0){
            cola_encolar(cola, " ");
            cola_encolar(cola, dato);
            pila_apilar(pila, operador);
        }
        else if(strcmp(dato, "*") == 0){
            if(pila_esta_vacia(pila)){
                cola_encolar(cola, " ");
                cola_encolar(cola, dato);
                pila_apilar(pila, operador);
            }else if(!pila_esta_vacia(pila)){
                char* dato2 = pila_desapilar(pila);
                if(strcmp(dato2, "(") == 0){
                    cola_encolar(cola, " ");
                    cola_encolar(cola, dato);
                    pila_apilar(pila, dato2);
                    pila_apilar(pila, operador);
                }else{
                    pila_apilar(pila, dato2);
                    pila_apilar(pila, dato);
                    pila_apilar(pila, operador);
                }
            }
            else{
                pila_apilar(pila, operador);
                pila_apilar(pila, dato);
            }
        }else if(strcmp(dato, "^") == 0){
            if(pila_esta_vacia(pila)){
                pila_apilar(pila, operador);
                cola_encolar(cola, " ");
                cola_encolar(cola, dato);
            }else{
                pila_apilar(pila, dato);
                pila_apilar(pila, operador);
            }
        }else if(strcmp(dato, "/") == 0){
            if(pila_esta_vacia(pila)){
                pila_apilar(pila, operador);
                cola_encolar(cola, " ");
                cola_encolar(cola, dato);
            }           
            else{
                char* dato2 = pila_desapilar(pila);
                if(strcmp(dato2, "-") == 0 && pila_esta_vacia(pila)){
                    cola_encolar(cola, " ");
                    cola_encolar(cola, dato);
                    cola_encolar(cola, " ");
                    cola_encolar(cola, dato2);
                    pila_apilar(pila, operador);
                }else{
                    pila_apilar(pila, dato2);
                    pila_apilar(pila, dato);
                    pila_apilar(pila, operador);
                }
            }
        }
        else if(strcmp(dato, "(") == 0){
            if(!pila_esta_vacia(pila)){
                char* dato2 = pila_desapilar(pila);
                if(strcmp(dato2, "/") == 0 && pila_esta_vacia(pila)){
                    cola_encolar(cola, " ");
                    cola_encolar(cola, dato2);
                    pila_apilar(pila, operador);
                }else if(strcmp(dato2, "(") == 0){
                    if(pila_esta_vacia(pila)){
                        pila_apilar(pila, dato);
                        pila_apilar(pila, dato2);
                        pila_apilar(pila, operador);
                    }else{
                        pila_apilar(pila, dato);
                        pila_apilar(pila, dato2);
                        pila_apilar(pila, operador);
                    }
                }else if(strcmp(dato2, "*") == 0 && pila_esta_vacia(pila)){
                    pila_apilar(pila, dato2);
                    pila_apilar(pila,dato);
                    pila_apilar(pila, operador);
                }else if(strcmp(dato2, "+") == 0 && pila_esta_vacia(pila)){
                    pila_apilar(pila, dato2);
                    pila_apilar(pila, operador);
                    free(dato);
                }else if(strcmp(dato2, "*") == 0 && !pila_esta_vacia(pila)){
                    char* dato3 = pila_desapilar(pila);
                    if(strcmp(dato3, "-") == 0){
                        pila_apilar(pila, operador);
                        pila_apilar(pila, dato2);
                        pila_apilar(pila, dato3);
                        pila_apilar(pila, dato);
                    }else{
                        pila_apilar(pila, dato3);
                        pila_apilar(pila, dato2);
                        pila_apilar(pila, dato);
                        pila_apilar(pila, operador);
                    }
                }
                else{
                    pila_apilar(pila, dato2);
                    pila_apilar(pila, operador);
                    free(dato);
                }
            }else{
                pila_apilar(pila, dato);
                pila_apilar(pila, operador);
            }
        }
        else{
            pila_apilar(pila, dato);
            pila_apilar(pila, operador);
        }
    }
    else{
        pila_apilar(pila, operador);
    }
}

void terminos_exp_mult(char* operador, pila_t* pila, cola_t* cola){
    if(!pila_esta_vacia(pila)){
        char* dato = pila_desapilar(pila);
        if(strcmp(dato, "^") == 0){
            if(!pila_esta_vacia(pila)){
                char* dato2 = pila_desapilar(pila);
                if(strcmp(dato2, "(") == 0){
                    pila_apilar(pila, dato);
                    pila_apilar(pila, operador);
                    free(dato2);
                }else if(strcmp(dato2, "^") == 0 && pila_esta_vacia(pila) && strcmp(operador, "*") == 0){
                    cola_encolar(cola, " ");
                    cola_encolar(cola, dato);
                    cola_encolar(cola, " ");
                    cola_encolar(cola, dato2);
                    pila_apilar(pila, operador);
                }else if(strcmp(dato2, "/") == 0 && pila_esta_vacia(pila) && strcmp(operador, "^") == 0){
                    
                    pila_apilar(pila, dato2);
                    pila_apilar(pila, dato);
                    pila_apilar(pila, operador);
                }
                else if(strcmp(dato2, "^") == 0){
                    pila_apilar(pila, dato);
                    pila_apilar(pila, operador);
                    pila_apilar(pila, dato2);
                }else{
                    pila_apilar(pila, dato2);
                    pila_apilar(pila, dato);
                    pila_apilar(pila, operador);
                }
            }else if(pila_esta_vacia(pila)){
                if(strcmp(operador, "*") == 0){
                    cola_encolar(cola, " ");
                    cola_encolar(cola, dato);
                    pila_apilar(pila, operador);
                }else if(strcmp(operador, "/") == 0){
                    cola_encolar(cola, " ");
                    cola_encolar(cola, dato);
                    pila_apilar(pila, operador);
                }
                else{
                    pila_apilar(pila, operador);
                    pila_apilar(pila, dato);
                }
            }
            else{
                cola_encolar(cola, " ");
                cola_encolar(cola, dato);
                pila_apilar(pila, operador);
            }    
        }else if(strcmp(dato, "*") == 0){
            if(pila_esta_vacia(pila) && strcmp(operador, "^") != 0){
                cola_encolar(cola, " ");
                cola_encolar(cola, dato);
                pila_apilar(pila, operador);
            }else if(pila_esta_vacia(pila) && strcmp(operador, "^") == 0){
                pila_apilar(pila, dato);
                pila_apilar(pila, operador);
            }
            
            else{
                char* dato2 = pila_desapilar(pila);
                if(strcmp(dato2, "/") == 0){
                    cola_encolar(cola, " ");
                    cola_encolar(cola, dato2);
                    cola_encolar(cola, " ");
                    cola_encolar(cola, dato);
                    pila_apilar(pila, operador);
                }else if(strcmp(operador, "/") == 0 && strcmp(dato2, "+") == 0){
                    cola_encolar(cola, " ");
                    cola_encolar(cola, dato);
                    pila_apilar(pila, dato2);
                    pila_apilar(pila, operador);
                }
                else if(strcmp(dato2, "+") == 0){
                    cola_encolar(cola, " ");
                    cola_encolar(cola, dato2);
                    cola_encolar(cola, " ");
                    cola_encolar(cola, dato);
                    pila_apilar(pila, operador);
                }else if(strcmp(dato2, "(") == 0){
                    cola_encolar(cola, " ");
                    cola_encolar(cola, dato);
                    pila_apilar(pila, operador);
                    free(dato2);
                }
                else{
                    pila_apilar(pila,dato2);
                    pila_apilar(pila, operador);
                }
            }
        }else if(strcmp(dato, "/") == 0){
            if(strcmp(operador, "^") == 0 && pila_esta_vacia(pila)){
                pila_apilar(pila, dato);
            }
            else if(strcmp(operador, "^") == 0 && !pila_esta_vacia(pila)){
                char* dato2 = pila_desapilar(pila);
                if(strcmp(dato2, "+") == 0 || strcmp(dato2, "-") == 0){
                    cola_encolar(cola, " ");
                    cola_encolar(cola, dato2);
                }else{
                    free(dato2);
                    cola_encolar(cola, " ");
                    cola_encolar(cola, dato);
                }
            }else if(strcmp(operador, "/") == 0){
                cola_encolar(cola, " ");
                cola_encolar(cola, dato);
            }else if(strcmp(operador, "*") == 0 && pila_esta_vacia(pila)){
                cola_encolar(cola, " ");
                cola_encolar(cola, dato);
            }else if(strcmp(operador,"*") == 0 && !pila_esta_vacia(pila)){
                char* dato2 = pila_desapilar(pila);
                if(strcmp(dato2, "(") == 0){
                    cola_encolar(cola, " ");
                    cola_encolar(cola, dato);
                    pila_apilar(pila, dato2);
                }else{
                    pila_apilar(pila, dato2);
                    pila_apilar(pila, dato);
                }
            }
            else{
                pila_apilar(pila,dato);
            }
            pila_apilar(pila, operador);
        }

        else if(strcmp(dato, "(") == 0 && strcmp(operador, "/") == 0 && !pila_esta_vacia(pila)){
            char* dato2 = pila_desapilar(pila);
            if(strcmp(dato2, "-") == 0){
                cola_encolar(cola, " ");
                cola_encolar(cola, dato2);
                pila_apilar(pila, dato);
                pila_apilar(pila, operador);
            }else{
                pila_apilar(pila, dato2);
                pila_apilar(pila, operador);
                free(dato);
            }
        }
        else if(strcmp(dato, "-") == 0 && strcmp(operador, "/") == 0){
            if(!pila_esta_vacia(pila)){
                cola_encolar(cola, " ");
                cola_encolar(cola, dato);
                pila_apilar(pila, operador);
            }
            else{
                pila_apilar(pila,dato);
                pila_apilar(pila, operador);
            }
        }else if(strcmp(dato, "+") == 0 && strcmp(operador, "/") == 0 && !pila_esta_vacia(pila)){
            char *dato2 = pila_desapilar(pila);
            if(strcmp(dato2, "(") == 0 && !pila_esta_vacia(pila)){
                char* dato3 = pila_desapilar(pila);
                if(strcmp(dato3, "*") == 0 && pila_esta_vacia(pila)){
                    cola_encolar(cola, " ");
                    cola_encolar(cola, dato);
                    cola_encolar(cola, " ");
                    cola_encolar(cola, dato3);
                    pila_apilar(pila, dato2);
                    pila_apilar(pila, operador);
                }
            }else{
                cola_encolar(cola, " ");
                cola_encolar(cola, dato);
                pila_apilar(pila, dato2);
                pila_apilar(pila, operador);
            }
        }
        else if(strcmp(dato, "-") == 0 && strcmp(operador, "^") == 0 && !pila_esta_vacia(pila)){
            cola_encolar(cola, " ");
            cola_encolar(cola, dato);
            pila_apilar(pila, operador);
        }
        else if(strcmp(dato, "+") == 0 && strcmp(operador, "*") == 0 && !pila_esta_vacia(pila)){
            cola_encolar(cola, " ");
            cola_encolar(cola, dato);
            pila_apilar(pila, operador);
        }
        else if(strcmp(dato, "+") == 0 && strcmp(operador, "^") == 0 && !pila_esta_vacia(pila)){
            cola_encolar(cola, " ");
            cola_encolar(cola, dato);
            pila_apilar(pila, operador);
        }
        else{
            pila_apilar(pila,dato);
            pila_apilar(pila, operador);
        }
    }
    else{
        pila_apilar(pila, operador);
    }
}

void compara_operadores(char* operador, pila_t* pila, cola_t* cola){
    if(strcmp(operador, "+") == 0) terminos_sum_rest(operador, pila, cola);
    else if(strcmp(operador, "-") == 0) terminos_sum_rest(operador, pila, cola);
    else if(strcmp(operador, "*") == 0) terminos_exp_mult(operador, pila, cola);
    else if(strcmp(operador, "^") == 0) terminos_exp_mult(operador, pila, cola);
    else if(strcmp(operador, "/") == 0) terminos_exp_mult(operador, pila, cola);
    else free(operador);
}

void compara(pila_t* pila, cola_t* cola, char* caracter){
    size_t len = strlen(caracter);
    bool ok = true;
    for (size_t i = 0; i < len; i++){
        char* num = malloc(sizeof(char)*2);
        *num = caracter[i];
        num[1] = '\0';
        if(isdigit(caracter[i])){
            if(!ok){
                cola_encolar(cola, " ");
                ok = true;
            }
            cola_encolar(cola, num);
        }else{
            if(strcmp(num,"(") == 0){
                pila_apilar(pila, num);
            }else if(strcmp(num,")") == 0){
                if(!pila_esta_vacia(pila)){
                    char* dato = pila_desapilar(pila);
                    if(strcmp(dato, "*") == 0 || strcmp(dato, "+") == 0 || strcmp(dato, "^") == 0 || strcmp(dato,"/") == 0){
                        if(strcmp(dato, "+") == 0 && !pila_esta_vacia(pila)){
                            compara_operadores(dato, pila, cola);
                        }else{
                            cola_encolar(cola, " ");
                            cola_encolar(cola, dato);
                        }
                    }else{
                        compara_operadores(dato, pila, cola);
                    }
                }
                free(num);
            }
            else{
                if(caracter[i] != ' '){
                    compara_operadores(num, pila, cola);
                    ok = false;
                }else{
                    free(num);                                                    
                }
            }               
        }
    }
}

void ordena(char* linea){
    cola_t* cola = cola_crear();
    pila_t* pila = pila_crear();
    compara(pila, cola,linea);
    while (!pila_esta_vacia(pila)){
        char* p = pila_desapilar(pila);
        if(strcmp(p,"(") != 0){
            cola_encolar(cola, " ");
            cola_encolar(cola,p);
        }else{
            free(p);
        }
    }
    cola_encolar(cola,"\n");

    while(!cola_esta_vacia(cola)){
        char* a = cola_desencolar(cola);
        fprintf(stdout,"%s",a);
    }
    
    cola_destruir(cola,NULL);
    pila_destruir(pila);
}

void lee_archivo(){
    size_t cont = 0;
    char* linea = NULL;
    while(getline(&linea, &cont, stdin) != -1){
        if(linea[strlen(linea)-1] == '\n'){
            linea[strlen(linea)-1] = '\0';}
        ordena(linea);
    }
    free(linea); 
}

int main(){

    lee_archivo();
    
    return 0;
}