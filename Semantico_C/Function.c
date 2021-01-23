#include <string.h>
#include <stdlib.h>
#include"Function.h"
#include"HashTable.h"
#include"Symbol.h"
#include"Command.h"

typedef struct func{
    char* name;

    HashTable symbolTable;

    Command commandList;

    struct func* next;

}FunctionImpl;

Function createFunction(Command commandList){

    FunctionImpl* function = malloc(sizeof(FunctionImpl));

    function->name=NULL;
    function->symbolTable= NULL;
    function->commandList=commandList;
    function->next=NULL;
    
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
    function->name = name;
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
