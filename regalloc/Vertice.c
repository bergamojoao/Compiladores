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
}VerticeImpl;

////// FUNCOES VERTICE //////
Vertice criaVertice(int id, Lista adjacentes){
    VerticeImpl* v = (VerticeImpl*)malloc(sizeof(VerticeImpl));
    v->id=id;
    v->adjacentes=adjacentes;
    return v;
}

////// FIM FUNCOES VERTICE //////