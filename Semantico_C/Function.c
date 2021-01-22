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
    function->symbolTable= criaHashTable(108,getSymbolName);
    function->commandList=commandList;
    function->next=NULL;
    
    return function;
}

void setNextFunction(Function f, Function next){
    FunctionImpl* function = f;
    function->next = next;
}

void setFunctionName(Function f, char* name){
    FunctionImpl* function = f;
    function->name = name;
}

char* getFunctionName(Function f){
    FunctionImpl* function = f;
    return function->name;
}
