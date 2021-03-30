#ifndef _GRAFO_H
#define _GRAFO_H

typedef void * Grafo;


Grafo criaGrafo(int id, int size, Lista vertices);

int getGrafoId(Grafo g);

int getGrafoSize(Grafo g);

Lista getGrafoVertices(Grafo g);


#endif