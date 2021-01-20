#ifndef Symbol_H
#define Symbol_H

typedef void * Symbol;

enum SymSpec {FUNCAO, CONSTANTE, VARIAVEL, ARRAY};

Symbol createSymbol(char* name, char* type, int symbolSpec, int arraySize);

char* getSymbolName(Symbol s);

#endif