#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include<string.h>
#include"Symbol.h"
#include"Expression.h"
#include"ListaDinamica.h"

typedef struct{
    int symbolSpec;
    char name[150];
    char type[10];
    int linha;
    int coluna;
    Expression arraySize;
    Expression constante;
    Lista parametros;
}SymbolImpl;

Symbol createSymbol(char* name, char* type, int symbolSpec, Expression arraySize, int linha, int coluna){

    SymbolImpl* symbol = malloc(sizeof(SymbolImpl));

    symbol->symbolSpec=symbolSpec;
    strcpy(symbol->name,name);
    strcpy(symbol->type,type);
    symbol->arraySize=arraySize;
    symbol->linha=linha;
    symbol->coluna=coluna;
    symbol->constante=NULL;
    symbol->parametros=NULL;

    return symbol;
}

Symbol createVar(int symbolSpec, char* type){

    SymbolImpl* symbol = malloc(sizeof(SymbolImpl));

    symbol->symbolSpec=symbolSpec;
    strcpy(symbol->type,type);
    symbol->arraySize=NULL;
    symbol->constante=NULL;
    symbol->parametros=NULL;
    
    return symbol;
}

void setSymbolName(Symbol s, char* name){
    SymbolImpl* symbol=s;
    strcpy(symbol->name,name);
}

char* getSymbolName(Symbol s){
    SymbolImpl* symbol=s;
    return symbol->name;
}

char* getSymbolType(Symbol s){
    SymbolImpl* symbol=s;
    return symbol->type;
}

int getSymbolLinha(Symbol s){
    SymbolImpl* symbol=s;
    return symbol->linha;
}

int getSymbolColuna(Symbol s){
    SymbolImpl* symbol=s;
    return symbol->coluna;
}

void setSymbolLinha(Symbol s, int linha){
    SymbolImpl* symbol=s;
    symbol->linha = linha;
}

void setSymbolColuna(Symbol s, int coluna){
    SymbolImpl* symbol=s;
    symbol->coluna = coluna;
}

void setArraySize(Symbol s, Expression arraySize){
    SymbolImpl* symbol=s;
    symbol->arraySize = arraySize;
}

Expression getArraySize(Symbol s){
    SymbolImpl* symbol=s;
    return symbol->arraySize;
}

void setExpConstante(Symbol s, Expression constante){
    SymbolImpl* symbol=s;
    symbol->constante = constante;
}

Expression getExpConstante(Symbol s){
    SymbolImpl* symbol=s;
    return symbol->constante;
}

void setListaParametros(Symbol s, Lista l){
    SymbolImpl* symbol=s;
    symbol->parametros = l;
}

Lista getListaParametros(Symbol s){
    SymbolImpl* symbol=s;
    return symbol->parametros;
}

int getSymbolSpec(Symbol s){
    SymbolImpl* symbol=s;
    return symbol->symbolSpec;
}

void setSymbolType(Symbol s, char* type){
    SymbolImpl* symbol=s;
    strcpy(symbol->type,type);
}
