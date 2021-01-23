#ifndef Program_H
#define Program_H
#include"ListaDinamica.h"
#include"Function.h"
#include"HashTable.h"

typedef void * Program;

Program createProgram();

void setFunctionList(Program p, Function functionList);

HashTable getGlobalSymbolTable(Program p);

Function getFunctions(Program p);

#endif