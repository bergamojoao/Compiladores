#include <string.h>
#include <stdlib.h>
#include"Function.h"
#include"HashTable.h"
#include"ListaDinamica.h"
#include"Symbol.h"

typedef struct func{
    char* name;

    HashTable symbolTable;

    Lista commandList;

    struct func* next;

}FunctionImpl;

Function createFunction(char* name, Lista commandList){

    FunctionImpl* function = malloc(sizeof(FunctionImpl));

    function->name=name;
    function->symbolTable= criaHashTable(108,getSymbolName);
    function->commandList=commandList;
    function->next=NULL;
    
    return function;
}

char* getFunctionName(Function f){
    FunctionImpl* function = f;
    return function->name;
}
