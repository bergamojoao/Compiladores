#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include<string.h>
#include"Program.h"
#include"HashTable.h"
#include"Symbol.h"

int semantico(Program p){
    printf("chegou");
}

void verificaVariaveisIguais(HashTable symbolTable, Symbol symbol, char* str){
    Symbol existente = getElemHash(symbolTable,getSymbolName(symbol));

    if(existente != NULL){
        if(strcmp(getSymbolType(symbol),getSymbolType(existente)) == 0){
            printf("error:semantic:%d:%d: variable ’%s’ already declared, previous declaration in line %d column %d\n%s\n%*s"
                        ,getSymbolLinha(symbol),getSymbolColuna(symbol), getSymbolName(symbol), getSymbolLinha(existente), getSymbolColuna(existente), str, getSymbolColuna(symbol),"^");
        }else{
            printf("error:semantic:%d:%d: redefinition of ’%s’ previous defined in line %d column %d\n%s\n%*s"
                        ,getSymbolLinha(symbol),getSymbolColuna(symbol), getSymbolName(symbol), getSymbolLinha(existente), getSymbolColuna(existente), str, getSymbolColuna(symbol),"^");            
        }
        exit(0);
    }

    if(strcmp(getSymbolType(symbol),"VOID") == 0){
        printf("error:semantic:%d:%d: variable ’%s’ declared void\n%s\n%*s"
                    ,getSymbolLinha(symbol),getSymbolColuna(symbol), getSymbolName(symbol), str, getSymbolColuna(symbol),"^");
        exit(0);           
    }
}