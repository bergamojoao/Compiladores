#ifndef Program_H
#define Program_H
#include"ListaDinamica.h"
#include"Function.h"

typedef void * Program;

Program createProgram();

void setFunctionList(Program p, Function functionList);

#endif