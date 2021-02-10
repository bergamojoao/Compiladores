#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"Program.h"
#include"HashTable.h"
#include"Symbol.h"
#include"Command.h"

int percorreExpressionInt(Expression exp, HashTable symbolTable, HashTable globalTable);

int semantico(Program p){
    

    Function functions = getFunctions(p);
    while (functions != NULL){
        Symbol s = getElemHash(getGlobalSymbolTable(p),getFunctionName(functions));
        if(s!=NULL){
            if(getSymbolSpec(s) == PROTOTIPO){

                if(strcmp(getFunctionType(functions),getSymbolType(s)) != 0){
                    printf("error:semantic:%d:%d: conflicting types for ’%s’\n%s\n%*s"
                        ,getLinhaFunc(functions), getColunaFunc(functions), getFunctionName(functions), getFunctionMsg(functions), getColunaFunc(functions), "^");
                    exit(0); 
                }
                
                Lista parametrosProt = getListaParametros(s);
                Lista parametrosFunc = getListaParametrosFunc(functions);

                int sizeProt = getListaSize(parametrosProt);
                int sizeFunc = getListaSize(parametrosFunc);


                if(sizeProt < sizeFunc){
                    printf("error:semantic:%d:%d: prototype for ’%s’ declares fewer arguments\n%s\n%*s"
                        ,getLinhaFunc(functions), getColunaFunc(functions), getFunctionName(functions), getFunctionMsg(functions), getColunaFunc(functions), "^");
                    exit(0);    
                }
                

                while (parametrosProt != NULL && parametrosFunc != NULL){
                    Symbol sProt = get(parametrosProt), sFunc = get(parametrosFunc);
                    if(strcmp(getSymbolType(sProt),getSymbolType(sFunc)) != 0){
                        printf("error:semantic:%d:%d: argument ’%s’ does not match prototype\n%s\n%*s"
                            ,getSymbolLinha(sFunc), getSymbolColuna(sFunc), getSymbolName(sFunc), getFunctionMsg(functions), getSymbolColuna(sFunc), "^");
                        exit(0); 
                    }

                    parametrosProt = getProx(parametrosProt);
                    parametrosFunc = getProx(parametrosFunc);
                }
                
            }
        }

        Command listaComandos = getFunctionCommandList(functions);
        bool temReturn = false;
        while (listaComandos != NULL){
            if(getCmdType(listaComandos) == RETURN_CMD){
                temReturn = true;
                Expression e = getExp(listaComandos);

                if(strcmp(getFunctionType(functions),"void") == 0 && e != NULL){
                    printf("error:semantic:%d:%d: return with a value, in function returning void\n%s\n%*s"
                            ,getLinhaFunc(functions), getColunaFunc(functions), getFunctionMsg(functions), getColunaFunc(functions), "^");
                    exit(0);
                }else if(strcmp(getFunctionType(functions),"void") != 0 && e == NULL){
                    printf("error:semantic:%d:%d: return with no value, in function returning non-void\n%s\n%*s"
                            ,getCmdLinha(listaComandos), getCmdColuna(listaComandos), getCmdText(listaComandos), getCmdColuna(listaComandos), "^");
                    exit(0);
                }
            }
            listaComandos = getNextCommand(listaComandos);
        }

        if(!temReturn && strcmp(getFunctionType(functions),"void") != 0){
            printf("error:semantic:%d:%d: no return statement in function returning non-void\n%s\n%*s"
                            ,getLinhaFunc(functions), getColunaFunc(functions), getFunctionMsg(functions), getColunaFunc(functions), "^");
            exit(0);
        }
        

        functions = getNextFunction(functions);
    }
    
}


void verificaVariaveisIguais(HashTable symbolTable, HashTable globalTable,Symbol symbol, char* str){
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

    if(getSymbolSpec(symbol) != PROTOTIPO && strcmp(getSymbolType(symbol),"void") == 0){
        printf("error:semantic:%d:%d: variable ’%s’ declared void\n%s\n%*s"
                    ,getSymbolLinha(symbol),getSymbolColuna(symbol), getSymbolName(symbol), str, getSymbolColuna(symbol),"^");
        exit(0);           
    }

    Expression exp = getArraySize(symbol);
    if(exp != NULL){
        if(getExpType(exp) == EXP_NUMBER){
            if(getExpValue(exp) == 0){
                printf("error:semantic:%d:%d: size of array ’%s’ is zero\n%s\n%*s"
                    ,getSymbolLinha(symbol),getSymbolColuna(symbol), getSymbolName(symbol), str, getSymbolColuna(symbol),"^");
                exit(0);    
            }else if(getExpValue(exp) < 0){
                printf("error:semantic:%d:%d: size of array ’%s’ is negative\n%s\n%*s"
                    ,getSymbolLinha(symbol),getSymbolColuna(symbol), getSymbolName(symbol), str, getSymbolColuna(symbol),"^");
                exit(0);
            }
        }else if(percorreExpressionInt(exp,symbolTable, globalTable)<0){
            printf("error:semantic:%d:%d: size of array ’%s’ is negative\n%s\n%*s"
                    ,getSymbolLinha(symbol),getSymbolColuna(symbol), getSymbolName(symbol), str, getSymbolColuna(symbol),"^");
            exit(0);
        }else if(percorreExpressionInt(exp,symbolTable, globalTable)==0){
                printf("error:semantic:%d:%d: size of array ’%s’ is zero\n%s\n%*s"
                    ,getSymbolLinha(symbol),getSymbolColuna(symbol), getSymbolName(symbol), str, getSymbolColuna(symbol),"^");
                exit(0); 
        }
    }

}

void verificaFuncao(HashTable symbolTable, Function f, char* msg){
    printf("aqui");
    char a[41];
    scanf("%s",a);
    Symbol s = getElemHash(symbolTable, getFunctionName(f));
    if(s!=NULL){
        if(getSymbolSpec(s) == PROTOTIPO){
            printf("tem prototipo");
        }
    }
}   


int percorreExpressionInt(Expression exp, HashTable symbolTable, HashTable globalTable){
    if(exp != NULL){
        if(getExpType(exp) == EXP_VARIAVEL){
            Symbol s = getElemHash(symbolTable, getExpVarName(exp));
            if(s ==  NULL)
                s = getElemHash(globalTable, getExpVarName(exp));
            
            return percorreExpressionInt(getExpConstante(s), symbolTable, globalTable);
        }
        else if(getExpType(exp) == EXP_NUMBER){
            return getExpValue(exp);
        }

        Expression esq = getLeftChild(exp);
        Expression dir = getRightChild(exp);
        if(esq != NULL){
            if(dir!=NULL){
                switch (getExpType(exp)){
                    case OPERADOR_MULT:
                        return percorreExpressionInt(esq, symbolTable, globalTable) * percorreExpressionInt(dir, symbolTable, globalTable);
                    case OPERADOR_DIV:
                        return percorreExpressionInt(esq, symbolTable, globalTable) * percorreExpressionInt(dir, symbolTable, globalTable);
                    case OPERADOR_PLUS:
                        return percorreExpressionInt(esq, symbolTable, globalTable) + percorreExpressionInt(dir, symbolTable, globalTable);
                    case OPERADOR_SUB:
                        return percorreExpressionInt(esq, symbolTable, globalTable) - percorreExpressionInt(dir, symbolTable, globalTable);    
                } 
            }
            else return percorreExpressionInt(esq, symbolTable, globalTable);    
        }else return percorreExpressionInt(dir, symbolTable, globalTable);
 
    }
    return 0;
}