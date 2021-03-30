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
