#include"Pilha.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct elemento{
    Elem e;
    struct elemento *anterior;
}ElemImpl;


typedef struct pilha{
    struct elemento *last;
}PilhaImpl;

Pilha iniciarPilha(){
    PilhaImpl *novo=(PilhaImpl *)malloc(sizeof(PilhaImpl));
    novo->last=NULL;
    return novo;
}

void push(Pilha P,Elem elemento){
    PilhaImpl *pilha = P;
    if(elemento == NULL) return;
    ElemImpl *novo=(ElemImpl *)malloc(sizeof(ElemImpl));
    novo->e = elemento;
    novo->anterior = pilha->last;
    pilha->last = novo;
}

Elem pop(Pilha P){
    PilhaImpl *pilha = P;
    if(pilha->last == NULL) return NULL;
    Elem ret = pilha->last->e;
    pilha->last = pilha->last->anterior;
    return ret;
}
