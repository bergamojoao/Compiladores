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

void verificaExpressao(Expression e);

bool constante=false;
char* texto;

HashTable globalTableFixa, localTable;

int semantico(Program p){

    Function functions = getFunctions(p);
    while (functions != NULL){

        Symbol s = getElemHash(getGlobalSymbolTable(p),getFunctionName(functions));

        HashTable localSymbolTable = getFunctionSymbolTable(functions);

        if(s!=NULL){
            if(getSymbolSpec(s) == PROTOTIPO){

                if(strcmp(getFunctionType(functions),getSymbolType(s)) != 0){
                    printf("error:semantic:%d:%d: conflicting types for '%s'\n%s\n%*s"
                        ,getLinhaFunc(functions), getColunaFunc(functions), getFunctionName(functions), getFunctionMsg(functions), getColunaFunc(functions), "^");
                    exit(0); 
                }
                
                Lista parametrosProt = getListaParametros(s);
                Lista parametrosFunc = getListaParametrosFunc(functions);

                int sizeProt = getListaSize(parametrosProt);
                int sizeFunc = getListaSize(parametrosFunc);


                if(sizeProt < sizeFunc){
                    printf("error:semantic:%d:%d: prototype for '%s' declares fewer arguments\n%s\n%*s"
                        ,getLinhaFunc(functions), getColunaFunc(functions), getFunctionName(functions), getFunctionMsg(functions), getColunaFunc(functions), "^");
                    exit(0);    
                }
                

                while (parametrosProt != NULL && parametrosFunc != NULL){
                    Symbol sProt = get(parametrosProt), sFunc = get(parametrosFunc);
                    if(strcmp(getSymbolType(sProt),getSymbolType(sFunc)) != 0){
                        printf("error:semantic:%d:%d: argument '%s' does not match prototype\n%s\n%*s"
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

                if(e != NULL && getExpType(e) == EXP_STRING && (strcmp(getFunctionType(functions),"char") != 0 || getPonteiroFunc(functions) != 1) ){
                    char type[20];
                    strcpy(type,getFunctionType(functions));

                    int k = 0;
                    for(k=0; k<getPonteiroFunc(functions); k++) strcat(type, "*");

                    printf("error:semantic:%d:%d: incompatible types when returning type 'char*' but '%s' was expected\n%s\n%*s"
                            ,getCmdLinha(listaComandos), getCmdColuna(listaComandos), type, getCmdText(listaComandos), getCmdColuna(listaComandos), "^");
                    exit(0);
                }

                if(e != NULL && getExpType(e) == EXP_VARIAVEL && getElemHash(localSymbolTable, getExpVarName(e)) == NULL){
                    printf("error:semantic:%d:%d: '%s' undeclared\n%s\n%*s"
                            ,getExpLinha(e), getExpColuna(e), getExpVarName(e), getCmdText(listaComandos), getExpColuna(e), "^");
                    exit(0);
                }
            }else if(getCmdType(listaComandos) == EXPRESSAO){
                Expression e = getExp(listaComandos);
                verificaExpressao(e);
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
    globalTableFixa = globalTable;
    localTable = symbolTable;
    if(existente != NULL){
        if(strcmp(getSymbolType(symbol),getSymbolType(existente)) == 0){
            printf("error:semantic:%d:%d: variable '%s' already declared, previous declaration in line %d column %d\n%s\n%*s"
                        ,getSymbolLinha(symbol),getSymbolColuna(symbol), getSymbolName(symbol), getSymbolLinha(existente), getSymbolColuna(existente), str, getSymbolColuna(symbol),"^");
        }else{
            printf("error:semantic:%d:%d: redefinition of '%s' previous defined in line %d column %d\n%s\n%*s"
                        ,getSymbolLinha(symbol),getSymbolColuna(symbol), getSymbolName(symbol), getSymbolLinha(existente), getSymbolColuna(existente), str, getSymbolColuna(symbol),"^");            
        }
        exit(0);
    }

    if(getSymbolSpec(symbol) != PROTOTIPO && strcmp(getSymbolType(symbol),"void") == 0){
        printf("error:semantic:%d:%d: variable '%s' declared void\n%s\n%*s"
                    ,getSymbolLinha(symbol),getSymbolColuna(symbol), getSymbolName(symbol), str, getSymbolColuna(symbol),"^");
        exit(0);           
    }

    if(getSymbolSpec(symbol) == CONSTANTE){
        constante = true;
        texto = str;
        verificaExpressao(getExpConstante(symbol));
        constante =false;
    }

    Expression exp = getArraySize(symbol);
    if(exp != NULL){
        if(getExpType(exp) == EXP_NUMBER){
            if(getExpValue(exp) == 0){
                printf("error:semantic:%d:%d: size of array '%s' is zero\n%s\n%*s"
                    ,getSymbolLinha(symbol),getSymbolColuna(symbol), getSymbolName(symbol), str, getSymbolColuna(symbol),"^");
                exit(0);    
            }else if(getExpValue(exp) < 0){
                printf("error:semantic:%d:%d: size of array '%s' is negative\n%s\n%*s"
                    ,getSymbolLinha(symbol),getSymbolColuna(symbol), getSymbolName(symbol), str, getSymbolColuna(symbol),"^");
                exit(0);
            }
        }else if(percorreExpressionInt(exp,symbolTable, globalTable)<0){
            printf("error:semantic:%d:%d: size of array '%s' is negative\n%s\n%*s"
                    ,getSymbolLinha(symbol),getSymbolColuna(symbol), getSymbolName(symbol), str, getSymbolColuna(symbol),"^");
            exit(0);
        }else if(percorreExpressionInt(exp,symbolTable, globalTable)==0){
                printf("error:semantic:%d:%d: size of array '%s' is zero\n%s\n%*s"
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

void verificaExpressao(Expression e){
    if(e != NULL){
        if(getExpType(e) != EXP_VARIAVEL){
            Expression left = getLeftChild(e);
            if(left != NULL && getExpType(left) == EXP_INC){
                printf("error:semantic:%d:%d: lvalue required as increment operand\n%s\n%*s",
                    getExpLinha(left), getExpColuna(left), getExpText(e), getExpColuna(left), "^");
                exit(0);    
            }
        }else if(getExpType(e) == EXP_ASSIGN){
            Expression left = getLeftChild(e);
            if(getExpType(left) != EXP_VARIAVEL){
                printf("error:semantic:%d:%d: lvalue required as left operand of assignment\n%s\n%*s",
                    getExpLinha(e), getExpColuna(e), getExpText(e), getExpColuna(e), "^");
                exit(0); 
            }
        }else if(getExpType(e) == EXP_VARIAVEL && constante){
            Symbol var = getElemHash(globalTableFixa, getExpVarName(e));
            if(var == NULL)
                var = getElemHash(localTable, getExpVarName(e));
            if(var != NULL && getSymbolSpec(var) != CONSTANTE){
                printf("error:semantic:%d:%d: '%s' initializer element is not constant\n%s\n%*s",
                        getExpLinha(e), getExpColuna(e), getExpVarName(e),texto, getExpColuna(e), "^");
                exit(0);        
            }
            
        }

        Expression esq = getLeftChild(e);
        verificaExpressao(esq);
        Expression dir = getRightChild(e);
        verificaExpressao(dir);
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