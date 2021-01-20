#ifndef Function_H
#define Function_H
#include"ListaDinamica.h"

typedef void * Function;

Function createFunction(char* name, Lista commandList);

char* getFunctionName(Function f);

#endif