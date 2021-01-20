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

Function createFunction(char* name, Command commandList){

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
