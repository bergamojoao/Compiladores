#include <string.h>
#include <stdlib.h>
#include<string.h>
#include"Symbol.h"

typedef struct{
    int symbolSpec;
    char *name;
    char type[10];
    int arraySize;
}SymbolImpl;

Symbol createSymbol(char* name, char* type, int symbolSpec, int arraySize){

    SymbolImpl* symbol = malloc(sizeof(SymbolImpl));

    symbol->symbolSpec=symbolSpec;
    symbol->name=name;
    strcpy(symbol->type,type);
    symbol->arraySize=arraySize;
    
    return symbol;
}

char* getSymbolName(Symbol s){
    SymbolImpl* symbol=s;
    return symbol->name;
}
