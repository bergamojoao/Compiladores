#ifndef Symbol_H
#define Symbol_H
#include"Expression.h"
#include"ListaDinamica.h"

typedef void * Symbol;

enum SymSpec {FUNCAO, CONSTANTE, VARIAVEL, ARRAY, PARAMETRO, PROTOTIPO};

Symbol createSymbol(char* name, char* type, int symbolSpec, Expression arraySize, int linha, int coluna);

Symbol createVar(int symbolSpec, char* type);

char* getSymbolName(Symbol s);

void setSymbolName(Symbol s, char* name);

char* getSymbolType(Symbol s);

int getSymbolLinha(Symbol s);

int getSymbolColuna(Symbol s);

void setSymbolLinha(Symbol s, int linha);

void setSymbolColuna(Symbol s, int coluna);

void setArraySize(Symbol s, Expression arraySize);

Expression getArraySize(Symbol s);

void setExpConstante(Symbol s, Expression constante);

Expression getExpConstante(Symbol s);

void setListaParametros(Symbol s, Lista l);

Lista getListaParametros(Symbol s);

int getSymbolSpec(Symbol s);

void setSymbolType(Symbol s, char* type);

#endif