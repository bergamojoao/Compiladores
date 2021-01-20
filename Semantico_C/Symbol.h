#ifndef Symbol_H
#define Symbol_H

typedef void * Symbol;

Symbol createSymbol(char* name, char* type, int symbolSpec);

char* getSymbolName(Symbol s);

#endif