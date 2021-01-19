#include <string.h>
#include <stdlib.h>

typedef struct{
    char cpf[20];
    char nome[30];
    char sobrenome[60];
    char sexo;
    char dataNasc[10];
}PESSOA;

PESSOA* createPessoa(char * cpf, char * nome,char * sobrenome, char sexo,char * datanasc){
    PESSOA* pessoa = malloc(sizeof(PESSOA));
    strcpy(pessoa->cpf,cpf);
    strcpy(pessoa->nome,nome);
    strcpy(pessoa->sobrenome,sobrenome);
    pessoa->sexo=sexo;
    strcpy(pessoa->dataNasc,datanasc);
    return pessoa;
}

char * getCPFPessoa(PESSOA* p){
    return p->cpf;
}

char * getNomePessoa(PESSOA* p){
    return p->nome;
}

char * getSobrenomePessoa(PESSOA* p){
    return p->sobrenome;
}

char * getDataNascPessoa(PESSOA* p){
    return p->dataNasc;
}

char getSexoPessoa(PESSOA* p){
    return p->sexo;
}