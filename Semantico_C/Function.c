#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include"Function.h"
#include"HashTable.h"
#include"Symbol.h"
#include"Command.h"

typedef struct func{
    char name[150];
    char type[10];

    int linha;
    int coluna;

    char msg[180];

    HashTable symbolTable;

    Command commandList;

    struct func* next;

    Lista parametros;

}FunctionImpl;

Function createFunction(Command commandList){

    FunctionImpl* function = malloc(sizeof(FunctionImpl));

    function->symbolTable= NULL;
    function->commandList=commandList;
    function->next=NULL;
    function->parametros=NULL;
    
    return function;
}

void setNextFunction(Function f, Function next){
    FunctionImpl* function = f;
    function->next = next;
}

Function getNextFunction(Function f){
    FunctionImpl* function = f;
    return function->next;
}

void setFunctionName(Function f, char* name){
    FunctionImpl* function = f;
    strcpy(function->name, name);
}

char* getFunctionName(Function f){
    FunctionImpl* function = f;
    return function->name;
}

void setFunctionSymbolTable(Function f, HashTable symbolTable){
    FunctionImpl* function = f;
    function->symbolTable = symbolTable;
}

HashTable getFunctionSymbolTable(Function f){
    FunctionImpl* function = f;
    return function->symbolTable;
}

void setListaParametrosFunc(Function f, Lista l){
    FunctionImpl* function = f;
    function->parametros = l;
}

Lista getListaParametrosFunc(Function f){
    FunctionImpl* function = f;
    return function->parametros;
}

void setLinhaColunaFunc(Function f, int linha, int coluna){
    FunctionImpl* function = f;
    function->linha = linha;
    function->coluna = coluna;
}

int getLinhaFunc(Function f){
    FunctionImpl* function = f;
    return function->linha;
}

int getColunaFunc(Function f){
    FunctionImpl* function = f;
    return function->coluna;
}

void setFunctionMsg(Function f, char* msg){
    FunctionImpl* function = f;
    strcpy(function->msg, msg);
}

char* getFunctionMsg(Function f){
    FunctionImpl* function = f;
    return function->msg;
}

void setFunctionType(Function f, char* type){
    FunctionImpl* function = f;
    strcpy(function->type, type);
}

char* getFunctionType(Function f){
    FunctionImpl* function = f;
    return function->type;
}

