#ifndef Symbol_H
#define Symbol_H

typedef void * Symbol;

enum SymSpec {FUNCAO, CONSTANTE, VARIAVEL, ARRAY};

Symbol createSymbol(char* name, char* type, int symbolSpec, int arraySize);

Symbol createVar(int symbolSpec, char* type);

char* getSymbolName(Symbol s);

void setSymbolName(Symbol s, char* name);

char* getSymbolType(Symbol s);

#endif