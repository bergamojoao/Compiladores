#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include<string.h>
#include"Program.h"
#include"HashTable.h"
#include"Symbol.h"

int semantico(Program p){

    Function f = getFunctions(p);
    while(f!=NULL){
        printf("Funcao: %s\n",getFunctionName(f));
        f=getNextFunction(f);
    }
    //HashTable local = getFunctionSymbolTable(f);

    //printf("%s", getSymbolType(getElemHash(local,"a")));
}