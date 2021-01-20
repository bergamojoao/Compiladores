#include <string.h>
#include <stdlib.h>
#include"Program.h"
#include"HashTable.h"
#include"ListaDinamica.h"
#include"Symbol.h"

typedef struct {
    char* name;

    HashTable globalSymbolTable;

    Lista functionList;

}ProgramImpl;

Program createProgram(Lista functionList){

    ProgramImpl* program = malloc(sizeof(ProgramImpl));

    program->globalSymbolTable = criaHashTable(108,getSymbolName);

    program->functionList = functionList;
    
    return program;
}
