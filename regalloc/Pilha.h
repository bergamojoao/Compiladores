#ifndef PILHA_H
#define PILHA_H


typedef void * Pilha;


typedef void * Elem;

Pilha iniciarPilha();

void push(Pilha P,Elem elemento);

Elem pop(Pilha P);

#endif