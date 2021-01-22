#include <string.h>
#include <stdlib.h>
#include"Program.h"
#include"HashTable.h"
#include"Function.h"
#include"Symbol.h"

typedef struct {
    char* name;

    HashTable globalSymbolTable;

    Function functionList;

}ProgramImpl;

Program createProgram(){

    ProgramImpl* program = malloc(sizeof(ProgramImpl));

    program->globalSymbolTable = criaHashTable(108,getSymbolName);

    program->functionList = NULL;
    
    return program;
}

void setFunctionList(Program p, Function functionList){
    ProgramImpl* program = p;
    program->functionList=functionList;
}
