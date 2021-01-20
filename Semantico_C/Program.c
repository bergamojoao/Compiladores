#include <string.h>
#include <stdlib.h>
#include"Program.h"
#include"HashTable.h"
#include"ListaDinamica.h"
#include"Function.h"

typedef struct {
    char* name;

    HashTable globalSymbolTable;

    Lista functionList;

}ProgramImpl;

Program createProgram(Lista functionList){

    ProgramImpl* program = malloc(sizeof(ProgramImpl));

    program->globalSymbolTable = criaHashTable(107,getFunctionName);

    program->functionList = functionList;
    
    return program;
}
