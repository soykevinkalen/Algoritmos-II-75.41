from grafo import Grafo
from queue import *
from heapq import *
from math import inf, log
from collections import deque
import random
from operator import itemgetter


def BFS(grafo, origen, destino = None, nivel = inf):
    visitados = set()
    orden = {}
    padres = {}
    cola = Queue()

    visitados.add(origen)
    orden[origen] = 0
    padres[origen] = None
    cola.put(origen)

    while not cola.empty():
        actual = cola.get()
        if orden[actual] > nivel: break
        if actual == destino: break
        """Esta podria ser una funcion auxiliar"""
        for ady in grafo.obtener_adyacentes(actual):
            if ady not in visitados:
                visitados.add(ady)
                orden[ady] = orden[actual] + 1
                padres[ady] = actual
                cola.put(ady)
                if ady == destino:
                    return padres, orden
                if orden[ady] == nivel: break
    return padres, orden


def pagerank_grafo(grafo):
    sinks = 0
    k = 20
    d = 0.85
    n = len(grafo)
    sumat = {}
    grado = {}
    old_pr = {}
    new_pr = {}

    """Estas podrian ser funciones auxiliares."""
    for vert in grafo:
        grado[vert] = 0
        old_pr[vert] = 1 / n
    for vert in grafo:
        for ady in grafo.obtener_adyacentes(vert):
            grado[vert] += 1

    for _ in range(0, k):
        
        sinks = 0
        for vert in grafo:
            if grado[vert] == 0: sinks += old_pr[vert]
            sumat[vert] = 0 # 
       
        for vert in grafo:
            for ady in grafo.obtener_adyacentes(vert):
                sumat[ady] += (old_pr[vert] / grado[vert])

        
        for vert in grafo:
            new_pr[vert] = ((1 - d + d * sinks) / n) + (d * sumat[vert])
        old_pr = new_pr
    return old_pr


def _encontrar_ciclo(grafo, camino_parcial, largo_actual, largo_final, deadend):

    if largo_actual == largo_final and camino_parcial[0] == camino_parcial[-1]:
        return camino_parcial
    
    """Aca conviene usar el if opuesto para no tener todo el codigo adentro del if"""
    if largo_actual < largo_final:
        ultimo = camino_parcial[-1]

        camino_copia = camino_parcial[:]
        """Esta podria ser una funcion auxiliar"""
        for ady in grafo.obtener_adyacentes(ultimo):
            if ady in deadend.get(largo_actual, ()): continue
            
            if ady in camino_parcial and largo_actual < largo_final - 1: continue
            
            camino_copia.append(ady)
            ciclo = _encontrar_ciclo(grafo, camino_copia, largo_actual + 1, largo_final, deadend)
            if ciclo:

                return ciclo

    if largo_actual not in deadend:

        deadend[largo_actual] = set()

    deadend[largo_actual].add(camino_parcial.pop())
    
    return []

def encontrar_ciclo(grafo, origen, largo):
    deadend = {}
    return _encontrar_ciclo(grafo, [origen], 1, largo + 1, deadend)


def n_links(grafo, origen, lista, n):
    if len(lista) == n or len(grafo.obtener_adyacentes(origen)) == 0: 
        return lista
    for w in grafo.obtener_adyacentes(origen):
        solucion = n_links(grafo, w, lista + [w], n)
        if solucion is not None:
            return solucion

def clustering_coef(grafo, v):
    ady = grafo.obtener_adyacentes(v)
    if len(ady) <= 1: return 0.0
    links = 0
    for w in ady:
        for u in ady:
            if u in grafo.obtener_adyacentes(w) and u != w: links += 1.0
    return (links/(len(ady)*(len(ady)-1)))

def clustering_coefficient(grafo,v=None):
    if v:
        return clustering_coef(grafo, v)
    else:
        c = 0
        for i in grafo:
            c += clustering_coef(grafo, i)        
        n = len(grafo)
        return (c / n)
    
# def clustering_coefficient(grafo,v):
#     ady = grafo.obtener_adyacentes(v)
#     if len(ady) <= 1: return 0.0
#     links = 0
#     for w in ady:
#         for u in ady:
#             if u in grafo.obtener_adyacentes(w) and u != w: links += 1.0
#     return (links/(len(ady)*(len(ady)-1)))