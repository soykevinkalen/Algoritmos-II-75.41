#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include "funciones_tp2.h"
#include "strutil.h"
#include "mensajes.h"
#include "cola.h"

#define COMANDO_PEDIR_TURNO "PEDIR_TURNO"
#define COMANDO_ATENDER "ATENDER_SIGUIENTE"
#define COMANDO_INFORME "INFORME"

/*Nota: 8
Esta muy bien la entrega, principalmente la utilizacion de funciones auxiliares y de varios archivos .c y .h
que ayudan a que el codigo sea facil de leer.
Las estructuras que usaron estan bien, la que mas me hace ruido igual es la de las prioridades
no esta mal pero creo que se podria haber simplificado utilizando caracteres o numeros que indiquen si es una urgencia
o no. Por otro lado, creo que tienen una estructura demas para los pacientes, podrian haberlo hecho usando solo
pacientes_por_prioridad.
Les fui agregando comentarios en el codigo asi que leanlos para ver otras cosas que les marque pero como eran detalles
preferi no ponerlos aca tambien.
*/

void procesar_comando(hospital_t* hospital , char* comando, char** parametros) {
	if (strcmp(comando, COMANDO_PEDIR_TURNO) == 0) {
		pedir_turno(hospital, parametros);
	} else if (strcmp(comando, COMANDO_ATENDER) == 0) {
		atender_sgte_paciente(hospital, parametros);
	} else if (strcmp(comando, COMANDO_INFORME) == 0) {
		//Aca la validacion de los parametros la tendria que hacer la funcion informe_doctores.
		if(!parametros[0] || !parametros[1]){
			printf(ENOENT_PARAMS, comando);
		}else{
			informe_doctores(hospital, parametros[0], parametros[1]);
		}
	}
	else{
		if(comando && !parametros) printf(ENOENT_FORMATO, comando);
		if(comando && parametros) printf(ENOENT_CMD, comando);
	}
}

void eliminar_fin_linea(char* linea) {
	size_t len = strlen(linea);
	if (linea[len - 1] == '\n') {
		linea[len - 1] = '\0';
	}
}

void procesar_entrada(hospital_t* hospital) {
	char* linea = NULL;
	size_t c = 0;
	while (getline(&linea, &c, stdin) > 0) {
		eliminar_fin_linea(linea);
		char** campos = split(linea, ':');
		if (campos[1] == NULL) {
			printf(ENOENT_FORMATO, linea);
			free_strv(campos);
			continue;	
		}
		char** parametros = split(campos[1], ',');
		procesar_comando(hospital ,campos[0], parametros);
		free_strv(parametros);
		free_strv(campos);
	}
	free(linea);
}

void* wraper_doctor(char** datos, void* extra){
	char* nombre = strdup(datos[0]);
	char* especialidad = strdup(datos[1]);
    void* doc = crear_doctor(nombre, especialidad);
    return doc;
}

void* wraper_pacientes(char** datos, void* extra){
	char* nombre = strdup(datos[0]);
	char* inscripcion = strdup(datos[1]);
    void* paciente = crear_paciente(nombre, inscripcion);
    return paciente;
}

int main(int argc, char** argv) {
	lista_t* lista_doctores = csv_crear_estructura(argv[1], wraper_doctor, NULL);
	lista_t* lista_pacientes = csv_crear_estructura(argv[2], wraper_pacientes, NULL);
	hash_t* hash_pacientes = crear_hash_pacientes(lista_pacientes);
	hash_t* hash_doctores = crear_hash_doctores(lista_doctores);
	hash_t* pacientes_a_atender = crear_hash_cant_x_especialidad(lista_doctores); //El nombre de esta funcion es medio raro.
	hash_t* pacientes_por_prioridad = crear_hash_a_atender(lista_doctores);
	abb_t* abb_doctores = crear_abb_doctores(lista_doctores);
	hospital_t* hospital = crear_hospital(hash_pacientes, hash_doctores, pacientes_a_atender, pacientes_por_prioridad, abb_doctores);
	procesar_entrada(hospital);
	hospital_destruir_listas(lista_doctores, lista_pacientes);
	hospital_destruir(hospital);
	
	return 0;
}