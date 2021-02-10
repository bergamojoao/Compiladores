#ifndef Function_H
#define Function_H
#include"ListaDinamica.h"
#include"HashTable.h"
#include"Command.h"

typedef void * Function;

Function createFunction(Lista commandList);

Function getNextFunction(Function f);

void setNextFunction(Function f, Function next);

void setFunctionName(Function f, char* name);

char* getFunctionName(Function f);

void setFunctionSymbolTable(Function f, HashTable symbolTable);

HashTable getFunctionSymbolTable(Function f);

void setListaParametrosFunc(Function f, Lista l);

Lista getListaParametrosFunc(Function f);

void setLinhaColunaFunc(Function f, int linha, int coluna);

int getLinhaFunc(Function f);

int getColunaFunc(Function f);

void setFunctionMsg(Function f, char* msg);

char* getFunctionMsg(Function f);

void setFunctionType(Function f, char* name);

char* getFunctionType(Function f);

void setReturnMsg(Function f, char* msg);

char* getReturnMsg(Function f);

Command getFunctionCommandList(Function f);

void setPonteiroFunc(Function f, int ponteiros);

int getPonteiroFunc(Function f);

#endif