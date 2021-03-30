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
Grafo criaGrafo(int size, int id){
    GrafoImpl* g = malloc(sizeof(GrafoImpl));
    g->id=id;
    g->size=size;
    g->vertices=NULL;
    return g;
}
