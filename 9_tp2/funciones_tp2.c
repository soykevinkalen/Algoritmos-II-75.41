#include "funciones_tp2.h"

//-----------------------------------------------------------------

bool existe_paciente(hash_t* pacientes, char* paciente) {
    if(!pacientes) return false;
    return hash_pertenece(pacientes, paciente);
}

bool existe_doctor(hash_t* doctores, char* doctor) {
    if(!doctores) return false;
    return hash_pertenece(doctores, doctor);
}

bool existe_especialidad(hash_t* cant_pacientes_esp, char* especialidad) {
    if(!cant_pacientes_esp) return false;
    return hash_pertenece(cant_pacientes_esp, especialidad);
}

bool existe_urgencia(char* urgencia) {
    return ((strcmp(urgencia, "URGENTE") == 0) || (strcmp(urgencia, "REGULAR") == 0));
}

void pedir_turno(hospital_t* hospital, char** turno) { 
    //Aca en los errores les conviene poner un return en el if y asi evitas los else.
    if (!existe_paciente(hospital_pacientes(hospital), turno[0])) {
        printf(ENOENT_PACIENTE, turno[0]);
    }else if (!existe_especialidad(hospital_cantidad(hospital), turno[1])) {
        printf(ENOENT_ESPECIALIDAD, turno[1]);
    }else if (!existe_urgencia(turno[2])) {
        printf(ENOENT_URGENCIA, turno[2]);
    } else {
        hash_t* hash_turnos = hospital_turnos(hospital); //Aca podrian usar directmante hospital->turnos_pedidos
        prioridades_t* prioridades = (prioridades_t*)hash_obtener(hash_turnos, turno[1]);
        //Esto deberia estar en el if correspondiente a la prioridad que tenes.
        cola_t* urgentes = obtener_cola_prioridad(prioridades);
        /*No me queda claro porque usan una cola para los urgentes y un abb para los regulares.*/
        abb_t* regulares = obtener_abb_prioridad(prioridades);
        paciente_t* paciente = hash_obtener(hospital_pacientes(hospital), turno[0]);
        if(strcmp(turno[2], "URGENTE") == 0){
            cola_encolar(urgentes,paciente);
        }else {
            abb_guardar(regulares, obtener_inscripcion_paciente(paciente), paciente);
        }
        /*Esto no hace falta que lo hagan porque modifican un puntero a las estructuras y no una copia*/
        prioridades_agregar(prioridades, urgentes, regulares);
        /*Aca se ve que la cantidad es el tamano de la cola y el abb? Lo mas correcto aca seria modificar la
        cola para que tuviera una funcion que devuelva la cantidad de elementos y asi la cantidad seria:
        abb_cantidad + cola_cantidad y evitas tener una estructura distinta para eso.*/
        size_t* cantidad = (size_t*)hash_obtener(hospital_cantidad(hospital), turno[1]);
        *cantidad = *cantidad + 1;
        printf(PACIENTE_ENCOLADO, turno[0]);
        printf(CANT_PACIENTES_ENCOLADOS,*cantidad, turno[1]);
    }
}

char* abb_eliminar_paciente(abb_t* abb) {
    abb_iter_t* iter = abb_iter_in_crear(abb);
    paciente_t* paciente = (paciente_t*)abb_borrar(abb ,abb_iter_in_ver_actual(iter));
    char* resultado = obtener_nombre_paciente(paciente);
    abb_iter_in_destruir(iter);
    return resultado;
}

void atender_sgte_paciente(hospital_t* hospital, char** linea) {
    char* paciente = NULL;
    
    if (!existe_doctor(hospital_doctores(hospital), linea[0]) || !hospital) {
        printf(ENOENT_DOCTOR, linea[0]);
        //Aca pongan un return, asi evitan tener todo el resto del codigo indentado por el else.
    } else {

        doctor_t* doctor = hash_obtener(hospital_doctores(hospital), linea[0]);
        char* especialidad = obtener_especialidad_doctor(doctor);
        size_t* cant = (size_t*)hash_obtener(hospital_cantidad(hospital), especialidad);

        if(!*cant){
            printf(SIN_PACIENTES);
            return;
        }
        
        prioridades_t* prioridad = (prioridades_t*)hash_obtener(hospital_turnos(hospital),especialidad);

        cola_t* urgentes = obtener_cola_prioridad(prioridad);
        abb_t* regulares = obtener_abb_prioridad(prioridad);

        size_t cantidad_abb = abb_cantidad(regulares);
        if (!cola_esta_vacia(urgentes)) {
            paciente = desencolar_nombre(urgentes);
            printf(PACIENTE_ATENDIDO, paciente);
        } else if ( cantidad_abb > 0)  {            
            paciente = abb_eliminar_paciente(regulares);
            printf(PACIENTE_ATENDIDO, paciente);
        } else {
            //Esto no deberia ser necesario porque ya verificaste antes si habia pacientes o no.
            printf(SIN_PACIENTES);
            return;
        }
        
        if (*cant > 0) {
            *cant = *cant - 1;
            printf(CANT_PACIENTES_ENCOLADOS, *cant, especialidad);
            //Como estas usando punteros no hace falta que vuelvan a guardar los datos.
            incrementar_atendidos(hospital,doctor);
        }   
    }  
}

void informe_doctores(hospital_t* hospital, char* inicio, char* fin) {
    hash_t* hash_doc = hospital_doctores(hospital);
    size_t contador_1 = 0, cant_atendidos = 0, contador_2 = 0;
    //Podrian haber puesto un or en el if en vez de usar dos.
    if(!hash_doc){
        printf(DOCTORES_SISTEMA, contador_1);
        return;
    }
    if(!hash_cantidad(hash_doc)){
        printf(DOCTORES_SISTEMA, contador_1);
        return;
    }
    
    cola_t* cola = cola_crear();
    abb_t* abb_doctores = hospital_abb_doctore(hospital);
    abb_iter_t* iter = abb_iter_in_crear(abb_doctores);
    char* nombre = NULL, *especialidad = NULL;

    /*Aca siento que se complicaron de mas por intentar hacerlo con un solo while, podrian haber hecho dos uno
    en el que encolan elementosy otro en el que no. En el primer while avanzan el iterador hasta el inicio y en
    el segundo encolan hasta el fin. Tambien pueden asumir que inicio <= fin o verificar eso al principio y tirar
    un error en caso contrario.*/
    while (!abb_iter_in_al_final(iter)) {
        if (strcmp(abb_iter_in_ver_actual(iter), fin) <= 0 &&
            strcmp(abb_iter_in_ver_actual(iter), inicio) >= 0) {
            contador_1 ++;
            cola_encolar(cola, abb_obtener(abb_doctores, abb_iter_in_ver_actual(iter)));
        }
        else if(strcmp("", inicio) == 0 && strcmp("", fin) == 0){
            contador_1 ++;
            cola_encolar(cola, abb_obtener(abb_doctores, abb_iter_in_ver_actual(iter)));
        }
        else if(strcmp("", inicio) == 0 && strcmp(abb_iter_in_ver_actual(iter), fin) < 0){
            contador_1 ++;
            cola_encolar(cola, abb_obtener(abb_doctores, abb_iter_in_ver_actual(iter)));
        }
        else if(strcmp("", fin) == 0 && strcmp(abb_iter_in_ver_actual(iter), inicio) > 0){
            contador_1 ++;
            cola_encolar(cola, abb_obtener(abb_doctores, abb_iter_in_ver_actual(iter)));
        }
        if(!obtener_cant_atendidos_doctor(abb_obtener(abb_doctores, abb_iter_in_ver_actual(iter)))){
            contador_2 ++;
        }
        abb_iter_in_avanzar(iter);
    }
    if(contador_1 == contador_2 && abb_cantidad(abb_doctores) != 1){
        abb_iter_in_destruir(iter);
        cola_destruir(cola, NULL);
        printf(DOCTORES_SISTEMA, contador_1 - contador_2);
        return;
    }
    printf(DOCTORES_SISTEMA, contador_1);
    for (size_t i = 1; !cola_esta_vacia(cola); i++) {
        doctor_t* doctor = (doctor_t*)cola_desencolar(cola);
        nombre = obtener_nombre_doctor(doctor);
        especialidad = obtener_especialidad_doctor(doctor);
        cant_atendidos = obtener_cant_atendidos_doctor(doctor);
        printf(INFORME_DOCTOR ,i, nombre, especialidad, cant_atendidos);
    }
    abb_iter_in_destruir(iter);
    cola_destruir(cola, free);
}

