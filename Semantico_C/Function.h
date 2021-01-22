#ifndef Function_H
#define Function_H
#include"ListaDinamica.h"

typedef void * Function;

Function createFunction(Lista commandList);

void setNextFunction(Function f, Function next);

void setFunctionName(Function f, char* name);

char* getFunctionName(Function f);

#endif