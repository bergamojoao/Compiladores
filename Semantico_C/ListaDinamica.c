#include"ListaDinamica.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct elemento{
    Elem e;
    struct elemento *prox;
}ListaImpl;

ListaD inserir(ListaD L,Elem elemento){
    ListaImpl *inicio = L;

    ListaImpl *novo=(ListaImpl *)malloc(sizeof(ListaImpl));
    novo->e=elemento;
    novo->prox=NULL;

    if(inicio==NULL){
        inicio=novo;
        inicio->prox=NULL;
    }else{
        ListaImpl *aux,*ant;
        aux=inicio;
        while(aux!=NULL){
            ant=aux;
            aux=aux->prox;
        }
        ant->prox=novo;
        aux=novo;
    }
    return inicio;
}

ListaD remover(ListaD L,Elem elemento){
    ListaImpl *inicio = L;
    ListaImpl *aux,*ant;

    if(inicio!=NULL){
        if(inicio->e==elemento){
            aux=inicio;
            inicio=inicio->prox;
            free(aux);
        }else{
            ant=inicio;
            aux=inicio->prox;
            while(aux!=NULL){
                if(aux->e==elemento){
                    ant->prox=aux->prox;
                    free(aux);
                    break;
                }
                ant=aux;
                aux=aux->prox;
            }
        }
    }
    return inicio;
}

ListaD removerSemFree(ListaD L,Elem elemento){
    ListaImpl *inicio = L;
    ListaImpl *aux,*ant;

    if(inicio!=NULL){
        if(inicio->e==elemento){
            aux=inicio;
            inicio=inicio->prox;
        }else{
            ant=inicio;
            aux=inicio->prox;
            while(aux!=NULL){
                if(aux->e==elemento){
                    ant->prox=aux->prox;
                    break;
                }
                ant=aux;
                aux=aux->prox;
            }
        }
    }
    return inicio;
}

ListaD getProx(ListaD L){
    ListaImpl *l = L;
    return l->prox;
}

Elem getD(ListaD L){
    ListaImpl *l = L;
    return l->e;
}

int getListaDSize(ListaD lista){
    ListaImpl* L = lista;
    int cont = 0;
    while(L != NULL){
        cont++;
        L = L->prox;
    }
    return cont;
}

void finalizar(ListaD L){
    ListaImpl *inicio=L;
    ListaImpl *aux;
    aux=inicio;
    while(aux!=NULL){
        inicio=inicio->prox;
        free(aux);
        aux=inicio;
    }
}