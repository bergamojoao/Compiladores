#ifndef Function_H
#define Function_H
#include"ListaDinamica.h"
#include"HashTable.h"

typedef void * Function;

Function createFunction(Lista commandList);

Function getNextFunction(Function f);

void setNextFunction(Function f, Function next);

void setFunctionName(Function f, char* name);

char* getFunctionName(Function f);

void setFunctionSymbolTable(Function f, HashTable symbolTable);

HashTable getFunctionSymbolTable(Function f);

#endif