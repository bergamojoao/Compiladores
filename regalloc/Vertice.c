#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"Vertice.h"
#include"ListaDinamica.h"

typedef void* InfoAdj;
typedef struct{
    int id;
    Lista adjacentes;
    int qtdAdjacentes;
    int cor;
}VerticeImpl;

////// FUNCOES VERTICE //////
Vertice criaVertice(int id, Lista adjacentes){
    VerticeImpl* v = (VerticeImpl*)malloc(sizeof(VerticeImpl));
    v->id=id;
    v->adjacentes=adjacentes;
    v->qtdAdjacentes =getListaSize(adjacentes);
    v->cor=-1;
    return v;
}

int getVerticeId(Vertice v){
    VerticeImpl* vertice = v;
    return vertice->id;
}

Lista getVerticeAdjacentes(Vertice v){
    VerticeImpl* vertice = v;
    return vertice->adjacentes;
}

int getVerticeQtdAdjacentes(Vertice v){
    VerticeImpl* vertice = v;
    return vertice->qtdAdjacentes;
}

void setVerticeQtdAdjacentes(Vertice v, int qtd){
    VerticeImpl* vertice = v;
    vertice->qtdAdjacentes = qtd;
}


int getVerticeCor(Vertice v){
    VerticeImpl* vertice = v;
    return vertice->cor;
}

void setVerticeCor(Vertice v, int cor){
    VerticeImpl* vertice = v;
    vertice->cor = cor;
}
////// FIM FUNCOES VERTICE //////