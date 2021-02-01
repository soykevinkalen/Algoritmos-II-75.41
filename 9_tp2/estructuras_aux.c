#include "estructuras_aux.h"

struct hospital{
	hash_t* pacientes;
	hash_t* doctores;
    hash_t* cant_pacientes_esp; //Cant de pacientes por especialidad
    hash_t* turnos_pedidos; //Hash de colas/abbs por especialidad
    abb_t* abb_doctore;
};

struct doctores {
    char* nombre;
    char* especialidad;
    size_t cant_atendidos;
};

struct pacientes {
    char* nombre;
    char* inscripcion;
};

struct prioridades {
    cola_t* urgentes;
    abb_t* regulares;
};

// --------------------- Funcion auxiliar ---------------------

int es_digito(char* string) {
    if(!strlen(string)) return 0;
    for (int i = 0; string[i]; i++) {
        if (isdigit(string[i]) || string[i] == '-') {
            continue;
        } else {
            return 0;
        }
    }
    return 1;
} 

// --------------------- CREADORES ---------------------

hospital_t* crear_hospital(hash_t* pacientes, hash_t* doctores, hash_t* cant_pacientes_esp, hash_t* turnos_pedidos, abb_t* abb_doctore) {
    hospital_t* hospital = malloc(sizeof(hospital_t));
	if (!hospital) return NULL;
	hospital->pacientes = pacientes;
	hospital->doctores = doctores;
	hospital->cant_pacientes_esp = cant_pacientes_esp;
    hospital->turnos_pedidos = turnos_pedidos;
    hospital->abb_doctore = abb_doctore;
    return hospital;
}

doctor_t* crear_doctor(char* nombre, char* especialidad) {
    doctor_t* doctor = malloc(sizeof(doctor_t));
    if (!doctor) return NULL;
    doctor->nombre = nombre;
    doctor->especialidad = especialidad;
    doctor->cant_atendidos = 0;
    return doctor;
}

paciente_t* crear_paciente(char* nombre, char* inscripcion) {
    paciente_t* paciente = malloc(sizeof(paciente_t));
    if (!paciente) return NULL;
    paciente->nombre = nombre;
    paciente->inscripcion = inscripcion;
    return paciente;
}

hash_t* crear_hash_doctores(lista_t* doctores) {
    if (!doctores) return NULL;
    if(lista_esta_vacia(doctores)) return NULL;
    hash_t* hash = hash_crear(NULL);
    if (!hash) return NULL;
    lista_iter_t* iter = lista_iter_crear(doctores);
    while (!lista_iter_al_final(iter)) {
        char* nombre = obtener_nombre_doctor((doctor_t*)lista_iter_ver_actual(iter));
        doctor_t* doc = (doctor_t*)lista_iter_ver_actual(iter);
        hash_guardar(hash,nombre ,doc);
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return hash;
}

hash_t* crear_hash_pacientes(lista_t* pacientes) {
    if (!pacientes) return NULL;
    if(lista_esta_vacia(pacientes)) return NULL;
    hash_t* hash = hash_crear(NULL);
    if (!hash) return NULL;
    lista_iter_t* iter = lista_iter_crear(pacientes);
    if(!iter) {
        hash_destruir(hash);
        return NULL;
    }
    while (!lista_iter_al_final(iter)) {
        if(!es_digito(((paciente_t*)lista_iter_ver_actual(iter))->inscripcion)){
            printf(ENOENT_ANIO,((paciente_t*)lista_iter_ver_actual(iter))->inscripcion);
            return NULL;
        }
        hash_guardar(hash, ((paciente_t*)lista_iter_ver_actual(iter))->nombre, (paciente_t*)lista_iter_ver_actual(iter));
        
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return hash;
}

void eliminar_campos(void* campo) {
    if (campo != NULL) free(campo);
}

hash_t* crear_hash_cant_x_especialidad(lista_t* doctores) {
    if (!doctores){ 
        return NULL;
    }
    if(lista_esta_vacia(doctores)) return NULL;
    hash_t* hash = hash_crear(eliminar_campos);
    if (!hash) return NULL;
    lista_iter_t* iter = lista_iter_crear(doctores);
    while (!lista_iter_al_final(iter)) {
        size_t* cantidad = malloc(sizeof(size_t));
        *cantidad = 0;
        char* especialidad = ((doctor_t*)lista_iter_ver_actual(iter))->especialidad;
        if (!hash_pertenece(hash, especialidad)) hash_guardar(hash, especialidad, cantidad);
        else {
            free(cantidad);
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return hash;
}

prioridades_t* crear_prioridades(abb_t* abb, cola_t* cola) {
    prioridades_t* prioridades = malloc(sizeof(prioridades_t));
    if (!prioridades) return NULL;
    prioridades->regulares = abb;
    if (!prioridades->regulares) return NULL;
    prioridades->urgentes = cola;
    if (!prioridades->urgentes) return NULL;
    return prioridades;
}

void destruir_todo(void* prioridades) {
    wrraper_destruir_prioridades((prioridades_t*) prioridades);
}

hash_t* crear_hash_a_atender(lista_t* doctores) {
    if (!doctores) return NULL;
    if(lista_esta_vacia(doctores)) return NULL;
    hash_t* hash = hash_crear(destruir_todo);
    if (!hash) return NULL;
    lista_iter_t* iter = lista_iter_crear(doctores);
    while (!lista_iter_al_final(iter)) {
        prioridades_t* prioridades = crear_prioridades(abb_crear(strcmp, NULL), cola_crear());
        hash_guardar(hash, ((doctor_t*)lista_iter_ver_actual(iter))->especialidad, prioridades);
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return hash;
}

abb_t* crear_abb_doctores(lista_t* doctores) {
    if (!doctores) return NULL;
    abb_t* abb = abb_crear(strcmp,NULL);
    if (!abb) return NULL;
    lista_iter_t* iter = lista_iter_crear(doctores);
    if(lista_iter_al_final(iter)){ 
        lista_iter_destruir(iter);
        abb_destruir(abb);
        return NULL;
    }
    while (!lista_iter_al_final(iter)) {
        abb_guardar(abb, ((doctor_t*)lista_iter_ver_actual(iter))->nombre, (doctor_t*)lista_iter_ver_actual(iter));
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return abb;
}

// --------------------- DESTRUCTORES ---------------------

void destruir_doctor(doctor_t* doctor){
    free(doctor->especialidad);
    free(doctor->nombre);
    free(doctor);
}

void destruir_paciente(paciente_t* paciente){
    if(paciente->inscripcion) free(paciente->inscripcion);
    if(paciente->nombre) free(paciente->nombre);
    if(paciente) free(paciente);
}

void destruir_hash_atender(hash_t* hash){
    hash_destruir(hash);
}

void hospital_destruir(hospital_t* hospital){
    if(!hospital) return;
    if(hospital->abb_doctore) abb_destruir(hospital->abb_doctore);
    if(hospital->cant_pacientes_esp) hash_destruir(hospital->cant_pacientes_esp);
    if(hospital->doctores) hash_destruir(hospital->doctores);
    if(hospital->pacientes) hash_destruir(hospital->pacientes);
    if(hospital->turnos_pedidos) destruir_hash_atender(hospital->turnos_pedidos);
    free(hospital);
}

void wrraper_destruir_doctor(void* doctor){
    doctor_t* doc = doctor;
    destruir_doctor(doc);
}


void wrraper_destruir_paciente(void* _paciente){
    if(!_paciente) return;
    paciente_t* paciente = _paciente;
    destruir_paciente(paciente);
}

void hospital_destruir_listas(lista_t* lista_doctores, lista_t* lista_pacientes){
    if(lista_doctores) lista_destruir(lista_doctores, wrraper_destruir_doctor);
    if(lista_pacientes) lista_destruir(lista_pacientes, wrraper_destruir_paciente);
}

void wrraper_destruir_cola(cola_t* cola){
    cola_destruir(cola, NULL);
}

void wrraper_destruir_abb(abb_t* abb){
    abb_destruir(abb);
}

void wrraper_destruir_prioridades(prioridades_t* prioridades){
    cola_destruir(prioridades->urgentes, wrraper_destruir_paciente);

    abb_destruir(prioridades->regulares);
    free(prioridades);
}

void wrraper_destruir_cantidad(size_t* cantidad){
    free(cantidad);
}

// --------------------- PRIMITIVAS ---------------------

hash_t* hospital_cantidad(hospital_t* hospital){
    if(!hospital) return NULL;
    return hospital->cant_pacientes_esp;
}

abb_t* hospital_abb_doctore(hospital_t* hospital){
    if(!hospital) return NULL;
    return hospital->abb_doctore;
}

hash_t* hospital_turnos(hospital_t* hospital){
    if(!hospital) return NULL;
    return hospital->turnos_pedidos;
}

hash_t* hospital_doctores(hospital_t* hospital){
    if(!hospital) return NULL;
    return hospital->doctores;
}

hash_t* hospital_pacientes(hospital_t* hospital){
    if(!hospital) return NULL;
    return hospital->pacientes;
}

char* obtener_inscripcion_paciente(paciente_t* paciente){
    return paciente->inscripcion;
}

char* obtener_nombre_paciente(paciente_t* paciente){
    return paciente->nombre;
}

cola_t* obtener_cola_prioridad(prioridades_t* prioridad){
    return prioridad->urgentes;
}

abb_t* obtener_abb_prioridad(prioridades_t* prioridad){
    return prioridad->regulares;
}

char* desencolar_nombre(cola_t* cola) {
    paciente_t* paciente = (paciente_t*)cola_desencolar(cola);
    return paciente->nombre;
}

char* obtener_especialidad_doctor(doctor_t* doctor){
    return doctor->especialidad;
}

char* obtener_nombre_doctor(doctor_t* doctor){
    return doctor->nombre;
}

size_t obtener_cant_atendidos_doctor(doctor_t* doctor){
    return doctor->cant_atendidos;
}

void incrementar_atendidos(hospital_t* hospital, doctor_t* doctor){
    doctor->cant_atendidos ++;
    hash_guardar(hospital->doctores, doctor->nombre, doctor);
    abb_guardar(hospital->abb_doctore, doctor->nombre, doctor);
}

void prioridades_agregar(prioridades_t* prioridades, cola_t* cola, abb_t* abb) {
    prioridades->regulares = abb;
    prioridades->urgentes = cola;
}


