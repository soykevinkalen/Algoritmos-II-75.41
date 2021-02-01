#!/usr/bin/python3

from grafo import Grafo
from biblioteca import *
import sys
import csv


#-------------------------------------------------------------------------------------------


def leer_linea(linea):
    if linea == "":
        operacion = ""
        parametros = None
    
    else:
        linea = linea.rstrip().split(' ', 1)

        operacion = linea[0]
        parametros = linea[1].split(',') if len(linea) == 2 else None

    return operacion, parametros


def agregar_vertices(grafo, datos):
    """Funcion auxiliar para agregar vertices y aristas al grafo"""
    for i in range(len(datos)):
        grafo.agregar_vertice(datos[i])


def agregar_aristas(grafo, datos):
    cabeza = datos[0]
    for i in range(len(datos)):
        if i != 0:
            grafo.agregar_arista(cabeza, datos[i])


def procesar_datos(grafo, archivo_paginas):
    """Procesa los archivos y los manda a un grafo"""
    with open(archivo_paginas, newline="") as csvfile:
        csvreader = csv.reader(csvfile, delimiter="\t")
        for datos in csvreader:
            agregar_vertices(grafo, datos)

    with open(archivo_paginas, newline="") as csvfile:
        csvreader = csv.reader(csvfile, delimiter="\t")
        for datos in csvreader:
            agregar_aristas(grafo, datos)


def obtener_operaciones():
    """Devuelve un diccionario que contiene por clave el nombre de la operacion implementada
    y como valor una tupla con la cantidad de parametros y la funcion a ejecutarse"""
    operaciones = {}
    operaciones["camino"] = (2, camino_mas_corto)
    operaciones["navegacion"] = (1, navegacion_primer_link)
    operaciones["mas_importantes"] = (1, pagerank)
    operaciones["ciclo"] = (2, ciclo)
    operaciones["clustering"] = (1, clustering)
    return operaciones


def listar_operaciones():
    """Devuelve una linea de las operaciones disponibles"""
    return [print(i) for i in obtener_operaciones()]


def operaciones(grafo, operacion, parametros):
    """Recibe el grafo principal, la operacion y los parametros ingresados por el usuario.
    Efectua las operaciones correspondientes sobre dichos parametros."""

    if operacion == "listar_operaciones":
        listar_operaciones()
    elif operacion == "camino":
        camino_mas_corto(grafo, *parametros)
    elif operacion == "navegacion":
        navegacion_primer_link(grafo, *parametros)
    elif operacion == "mas_importantes":
        pagerank(grafo, *parametros)
    elif operacion == "ciclo":
        ciclo(grafo, *parametros)
    elif operacion == "clustering":
    	"""Aca estan validando dos veces lo de los parametros
    	afuera y adentro de la funcion, lo mejor seria hacerlo en la funcion
    	clustering no mas."""
        if parametros is None:
            clustering(grafo)
        else:
            clustering(grafo, *parametros)


def imprimir_lista(lista):
    """Imprime la lista al reves"""
    cont_aux = 0
    for i in reversed(lista):
        cont_aux += 1 
        if i is None: continue
        if cont_aux == len(lista):
            print(f"{i} ", end="")
        else:
            print(f"{i} -> ", end="")


def imprimir_orden(orden, destino):
    """Imprime el costo de llegar a un destino"""
    print(f"\nCosto: {orden[destino]}")


def imprimir_resultado(padres, orden, origen, destino):
    """Imprime el resultado para camino_mas_corto"""
    try:
        lista = []
        lista.append(destino)
        actual = ""
        actual = padres[destino]
        
        while actual != origen:
            lista.append(actual)
            actual = padres[actual]  
        if actual == origen:
            lista.append(origen)
        imprimir_lista(lista)  
        imprimir_orden(orden, destino)
    except: 
        print("No se encontro recorrido")
    
        
def obtener_orden_mayor(orden):
    mayor_actual = 0
    clave_res = ""
    clave_de_none = None
    for clave, valor in orden.items():  
        if valor == None:
            clave_de_none = clave
        if valor > mayor_actual:
            mayor_actual = valor
            clave_res = clave
    return clave_res, clave_de_none


def imprimir_lista2(lista):
    if len(lista) == 0:
        print("No se encontro recorrido")
    else:
        i = 0
        for v in lista:
            if i == len(lista) - 1:
                print(f"{v} \n",end="")
            else:
                print(f"{v} -> ",end="")
            i += 1

#----------------------------------------------------------------------------------------

def camino_mas_corto(grafo ,origen, destino):
    """Implementado con bfs ya que es un grafo dirigido y no pesado"""
    padres, orden = BFS(grafo, origen, destino)
    imprimir_resultado(padres, orden, origen, destino)

def navegacion_primer_link(grafo, origen):
    lista_ = n_links(grafo, origen, [origen], 21)
    imprimir_lista2(lista_)

def pagerank(grafo, cantidad):
    pr = pagerank_grafo(grafo)
    result_pagerank = nlargest(int(cantidad), pr, key=pr.get)
    print(', '.join(str(paginas) for paginas in result_pagerank))

def ciclo(grafo, pagina, cantidad):
    camino = encontrar_ciclo(grafo, pagina, int(cantidad))
    imprimir_lista2(camino)

def clustering(grafo, pagina=None):
    if pagina is None:
        clus = clustering_coefficient(grafo)
    else:
        clus = clustering_coefficient(grafo,pagina)
    print("{:.3f}".format(clus))

#-------------------------------------------------------------------

def netstats(archivo_paginas, entrada_estandar):
    grafo = Grafo()
    procesar_datos(grafo, archivo_paginas)

    for linea in entrada_estandar:

        operacion, parametros = leer_linea(linea)

        operaciones(grafo, operacion, parametros)

if __name__ == "__main__":

    if len(sys.argv) == 2:
        netstats(sys.argv[1], sys.stdin)
    else:
        print("Error archivos erroneos")
        sys.exit()