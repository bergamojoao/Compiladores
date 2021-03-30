#ifndef _GRAFO_H
#define _GRAFO_H


/**
 *  Este header file contêm as funçôes necessárias para a implementação de
 * um grafo direcionado e também para o algoritmo de dijkstra.
 *  O mesmo possui funções para inserção e remoção de vértices e arestas,
 * bem como para a obtenção de seu adjacentes.
 *  Para o algoritmo de dijkstra, são encontradas as funções para inicialização
 * e realização do mesmo, bem como para comparar a prioridade entre vértices
 * na fila, sendo esta necessária para a implementação deste.
*/

/**
 * Um grafo direcionado G é constituído por um conjunto
 * de vértices V e um conjunto de arestas E, denotado por
 * G = (V,E). Uma aresta e=(u,v) é ordenada, isto é,
 * (u,v)!=(v,u). Os nomes dos vértices são strings chamadas 
 * de "ID". O mesmo possui uma lista de vértices cujos mesmos
 * possuem uma lista de adjacentes que guarda as informações
 * das arestas.
*/
typedef void * Grafo;

/**
 *  Uma estrutura do tipo "InfoAdj" armazena outras duas 
 * do tipo "Aresta" e "Vertice", referente a um vértice
 * adjacente a outro e uma aresta que os conecta.
*/
typedef void * InfoAdj;

/**
 * Cria um grafo contendo n vértices e nenhuma aresta.
*/
Grafo criaGrafo(int id, int size, Lista vertices);

#endif