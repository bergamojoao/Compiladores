#ifndef PESSOA_H
#define PESSOA_H

/**
 * Neste Header File encontra-se o tipo abstrato de dado (TAD) "PESSOA",
 * bem como os procedimentos necessários para a atribuição 
 * ou obtenção de suas informações e a pessoa a quem representa.
*/

/**
 * Uma pessoa possui os atributos CPF, NOME, SOBRENOME,SEXO e DATA DE NASCIMENTO
*/
typedef void * PESSOA;

/*
 * Recebe todos os atributos necessários para uma pessoa, aloca e retorna uma
 * estrutura do tipo "PESSOA".
*/
PESSOA* createPessoa(char * cpf, char * nome,char * sobrenome, char sexo,char * datanasc);

/*
 * Função responsavel por retornar o CPF de uma pessoa
 * Recebe como parametro o PESSOA* e cujo sera retornado o CNPJ
*/
char * getCPFPessoa(PESSOA* p);

/*
 * Função responsavel por retornar o NOME de uma pessoa
 * Recebe como parametro o PESSOA* e cujo sera retornado o NOME
*/
char * getNomePessoa(PESSOA* p);

/*
 * Função responsavel por retornar o SOBRENOME de uma pessoa
 * Recebe como parametro o PESSOA* e cujo sera retornado o SOBRENOMEs
*/
char * getSobrenomePessoa(PESSOA* p);

/*
 * Função responsavel por retornar a DATA DE NASCIMENTO de uma pessoa
 * Recebe como parametro o PESSOA* e cujo sera retornado a DATA DE NASCIMENTO
*/
char * getDataNascPessoa(PESSOA* p);

/*
 * Função responsavel por retornar o SEXO de uma pessoa
 * Recebe como parametro o PESSOA* e cujo sera retornado o SEXO
*/
char getSexoPessoa(PESSOA* p);

#endif