import random 

class Grafo:
    
    def __init__(self):
        """Inicializador del grafo"""
        self.vertices = {}
    
    def __len__(self):
        """Tamaño del grafo"""
        return len(self.vertices)
    
    def __iter__(self):
        """Iterador del grafo"""
        return iter(self.vertices)
    
    def __str__(self):
        """Metodo str del grafo"""
        return str(self.vertices)
    
    def __repr__(self):
        """Metodo repr"""
        return str(self.vertices)

    def __contains__(self, item):
        return item in self.vertices

    def agregar_vertice(self, vertice):
        """Agrega vertices al grafo, en caso de estar devuelve False"""
        if vertice not in self.vertices: 
            self.vertices[vertice] = {}
            return True
        return False
    
    
    def sacar_vertice(self, vertice):
        """Elimina el vertice del grafo en caso de encontrarse sino devuelve False"""
        if vertice in self.vertices:
            for aristas in self.vertices.values():
                if vertice in aristas: aristas.pop(vertice)
            self.vertices.pop(vertice)
            return True
        return False
    
    def obtener_vertices(self):
        """Devuelve una lista de los vertices que se encuentran en el grafo"""
        return list(self.vertices.keys())

    def agregar_arista(self, desde, hasta, peso = 1):
        """Agrega una arista al grafo y le asigna el peso = 1, en caso de no encontrarse
        la arista (no serian los vertices??) devuelve False"""
        if desde in self.vertices and hasta in self.vertices:
            self.vertices[desde][hasta] = peso
            return True
        return False
    
    def sacar_arista(self, desde, hasta):
        """Elimina una arista dentro del grafo en caso de no encontrarse devuelve False"""
        if desde in self.vertices and hasta in self.vertices:
            self.vertices[desde].pop(hasta)    
            return True
        return False

    def estan_conectados(self, u, v):
        """Devuelve True en caso de que dos vertices se encuentren conectados"""
        if u in self.vertices and v in self.vertices:
            return v in self.vertices[u] or u in self.vertices[v]
        return False

    def existe_vertice(self, v):
        """Devuelve True en caso de que el vertice exista"""
        return v in self.vertices
    
    def vertice_aleatorio(self):
        """Devuelve un vertice aleatorio"""
        return random.choice(list(self.vertices.keys()))
    
    def obtener_adyacentes(self, vertice):
        """Devuelve una lista de todos los adyacentes en caso de no tenerlos devuelve None"""
        if vertice in self.vertices:
            return list(self.vertices[vertice].keys())
        return None
