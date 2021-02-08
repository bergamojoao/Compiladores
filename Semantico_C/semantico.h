#ifndef SEMANTICO_H
#define SEMANTICO_H
#include"Program.h"

void semantico(Program p);

void verificaVariaveisIguais(HashTable symbolTable, HashTable globalTable,Symbol symbol, char* str);

#endif