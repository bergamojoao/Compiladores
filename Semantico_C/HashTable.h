#ifndef HASH_H
#define HASH_H
#include"ListaDinamica.h"

/**
 * Este header file contêm as funçôes necessarias para a implementação de tabela de espalhamentos(HashTable), 
 * O mesmo possui funções para criação de de tabelas de espalhamentos, para inserir elementos na Hashtable,
 * para remoção e getter para obter o elemento armazenado na hashtable.
*/

/**
 * O tipo "HashTable" refere-se a estrutura principal de uma tabela de espalhamento. 
 * Contêm ponteiros para uma outra estrutura do tipo "Item" que contem uma lista
 * que é responsável por armazenar os elementos de cada posição da tabela de espalhamento
 * Possui também um inteiro que indica o tamanho da tabela.
 * E também armazena uma função que é responsável de retornar a chave do elemento contido na tabela.
*/
typedef void * HashTable;

/*
 * Função responsável pela criação da tabela de espalhamento.
 * Tem como parametro um inteiro que representa a quantidade de posições que serão alocadas
 * E tambem como parametro uma função que é responsável por retornar a chave do elemento a ser inserido,removido ou buscado. 
*/
HashTable criaHashTable(int tamanho, char* (*getChave)(Elem));

/*
 * Função responsável por inserir um elemento na tabela de espalhamento.
 * Recebe como parametro uma HashTable h que representa a tabela de espalhamento desejada
 * e um Elemento e que representa o elemento a ser inserido
*/
void insertHashTable(HashTable h,Elem e);

/*
 * Função responsável por remover um elemento na tabela de espalhamento.
 * Recebe como parametro uma HashTable h que representa a tabela de espalhamento desejada
 * e uma string que representa a chave do elemento que irá ser removido da tabela.
*/
void removerHashTable(HashTable h,char* chave);

/*
 * Função responsável por retornar o elemento cuja a chave informada via parametro.
 * Recebe como parametro uma HashTable h que representa a tabela de espalhamento desejada
 * e uma string que representa a chave do Elemento a ser retornado.
*/
Elem getElemHash(HashTable H,char* chave);

/*
 * Função responsável por desalocar todos os elementos da tabela de espalhamento.
 * Recebe como parametro uma HashTable h que representa a tabela de espalhamento desejada.
 * Todas as listas dinamicas relacionadas a cada Posicao da hash será desalocada.
*/
void desalocaHash(HashTable h);

int getSizeHash(HashTable H);

Lista getLista(HashTable H, int index);

#endif