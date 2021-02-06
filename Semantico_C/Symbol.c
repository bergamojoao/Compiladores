#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include<string.h>
#include"Symbol.h"

typedef struct{
    int symbolSpec;
    char name[150];
    char type[10];
    int linha;
    int coluna;
    int arraySize;
}SymbolImpl;

Symbol createSymbol(char* name, char* type, int symbolSpec, int arraySize, int linha, int coluna){

    SymbolImpl* symbol = malloc(sizeof(SymbolImpl));

    symbol->symbolSpec=symbolSpec;
    strcpy(symbol->name,name);
    strcpy(symbol->type,type);
    symbol->arraySize=arraySize;
    symbol->linha=linha;
    symbol->coluna=coluna;

    return symbol;
}

Symbol createVar(int symbolSpec, char* type){

    SymbolImpl* symbol = malloc(sizeof(SymbolImpl));

    symbol->symbolSpec=symbolSpec;
    strcpy(symbol->type,type);
    
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
