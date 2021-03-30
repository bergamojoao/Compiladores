#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"ListaDinamica.h"
#include"Vertice.h"
#include"Grafo.h"

typedef struct{
    int id;
    int size;
    Lista vertices;
}GrafoImpl;


////// FUNCOES GRAFO //////
Grafo criaGrafo(int id, int size, Lista vertices){
    GrafoImpl* g = malloc(sizeof(GrafoImpl));
    g->id=id;
    g->size=size;
    g->vertices=vertices;
    return g;
}

int getGrafoId(Grafo g){
    GrafoImpl *grafo = g;
    return grafo->id;
}

int getGrafoSize(Grafo g){
    GrafoImpl *grafo = g;
    return grafo->size;
}

Lista getGrafoVertices(Grafo g){
    GrafoImpl *grafo = g;
    Lista copiaVertices = NULL;
    Lista vertices = grafo->vertices;
    while (vertices != NULL){
        Vertice v = get(vertices);
        setVerticeCor(v, -1);
        setVerticeQtdAdjacentes(v, getListaSize(getVerticeAdjacentes(v)));
        copiaVertices = inserir(copiaVertices, v);
        vertices = getProx(vertices);
    }

    return copiaVertices;
}

