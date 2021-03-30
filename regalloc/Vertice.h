#ifndef VERTICE_H
#define VERTICE_H
#include"ListaDinamica.h"

typedef void * Vertice;

/**
 *  Este header file contêm as funções necessárias para a criação e atribuição 
 * de valores de uma estrutura do tipo "Vertice", referente a um vértice de um
 * grafo direcionado.
*/

/**
 *  Retorna uma estrutura do tipo "Vertice" contendo as informações especificadas.
*/
Vertice criaVertice(int id);


#endif