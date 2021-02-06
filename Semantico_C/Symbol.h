#ifndef Symbol_H
#define Symbol_H

typedef void * Symbol;

enum SymSpec {FUNCAO, CONSTANTE, VARIAVEL, ARRAY};

Symbol createSymbol(char* name, char* type, int symbolSpec, int arraySize, int linha, int coluna);

Symbol createVar(int symbolSpec, char* type);

char* getSymbolName(Symbol s);

void setSymbolName(Symbol s, char* name);

char* getSymbolType(Symbol s);

int getSymbolLinha(Symbol s);

int getSymbolColuna(Symbol s);

void setSymbolLinha(Symbol s, int linha);

void setSymbolColuna(Symbol s, int coluna);

#endif