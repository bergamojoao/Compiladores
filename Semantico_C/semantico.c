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
bool array=false;
bool showText=false;
char* texto;

HashTable globalTableFixa, localTable;

void verificarAssign(Expression e, char* str){
    showText=true;
    texto=str;
    verificaExpressao(e);
    showText=false;
}

int semantico(Program p){

    globalTableFixa = getGlobalSymbolTable(p);

    Function functions = getFunctions(p);
    while (functions != NULL){

        Symbol s = getElemHash(getGlobalSymbolTable(p),getFunctionName(functions));

        HashTable localSymbolTable = getFunctionSymbolTable(functions);

        localTable = getFunctionSymbolTable(functions);

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
        }else{
            Symbol func = createSymbol(getFunctionName(functions), getFunctionType(functions), FUNCAO, NULL, getLinhaFunc(functions), getColunaFunc(functions));
            insertHashTable(globalTableFixa, func);
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
            }else if(getCmdType(listaComandos) == IF_CMD){
                Expression e = getExp(listaComandos);
                if(getExpType(e) == EXP_VARIAVEL){
                    Expression func1 = getLeftChild(e);
                    if(func1 != NULL && getExpType(func1) == EXP_FUNC){
                        Symbol func = getElemHash(globalTableFixa, getExpVarName(e));
                        if(func == NULL)
                            func = getElemHash(localTable, getExpVarName(e));

                        if(strcmp(getSymbolType(func),"void") == 0){
                            printf("error:semantic:%d:%d: void value not ignored as it ought to be\n%s\n%*s",
                                getExpLinha(e), getExpColuna(e), getExpText(e), getExpColuna(e), "^");
                            exit(0); 
                        }
                    }
                }
            }
            else if(getCmdType(listaComandos) == EXPRESSAO){
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


void verificaVariaveisIguais(HashTable symbolTable, HashTable globalTable,Symbol symbol, char* str, char* erro){
    Symbol existente = getElemHash(symbolTable,getSymbolName(symbol));
    globalTableFixa = globalTable;
    localTable = symbolTable;
    if(existente != NULL){
        if(strcmp(getSymbolType(symbol),getSymbolType(existente)) == 0){
            sprintf(erro, "error:semantic:%d:%d: variable '%s' already declared, previous declaration in line %d column %d\n%s\n%*s"
                        ,getSymbolLinha(symbol),getSymbolColuna(symbol), getSymbolName(symbol), getSymbolLinha(existente), getSymbolColuna(existente), str, getSymbolColuna(symbol),"^");
        }else{
            sprintf(erro,"error:semantic:%d:%d: redefinition of '%s' previous defined in line %d column %d\n%s\n%*s"
                        ,getSymbolLinha(symbol),getSymbolColuna(symbol), getSymbolName(symbol), getSymbolLinha(existente), getSymbolColuna(existente), str, getSymbolColuna(symbol),"^");            
        }
    }

    if(getSymbolSpec(symbol) != PROTOTIPO && strcmp(getSymbolType(symbol),"void") == 0){
        sprintf(erro, "error:semantic:%d:%d: variable '%s' declared void\n%s\n%*s"
                    ,getSymbolLinha(symbol),getSymbolColuna(symbol), getSymbolName(symbol), str, getSymbolColuna(symbol),"^");         
    }

    if(getSymbolSpec(symbol) == CONSTANTE){
        constante = true;
        texto = str;
        verificaExpressao(getExpConstante(symbol));
        constante =false;
    }

    Expression assign = getExpAssign(symbol);
    if(assign != NULL){
        if(getExpType(assign) == OPERADOR_BITWISE){
            Expression sub = getLeftChild(assign);
            if(getExpType(sub) != EXP_VARIAVEL){
                printf("error:semantic:%d:%d: lvalue required as unary '&' operand\n%s\n%*s",
                        getExpLinha(assign), getExpColuna(assign), str, getExpColuna(assign), "^");
                exit(0); 
            }
        }
    }

    Expression exp = getArraySize(symbol);
    if(exp != NULL){
        array=true;
        texto = str;
        verificaExpressao(exp);
        array = false;
        if(getExpType(exp) == EXP_NUMBER){
            if(getExpValue(exp) == 0){
                sprintf(erro, "error:semantic:%d:%d: size of array '%s' is zero\n%s\n%*s"
                    ,getSymbolLinha(symbol),getSymbolColuna(symbol), getSymbolName(symbol), str, getSymbolColuna(symbol),"^");   
            }else if(getExpValue(exp) < 0){
                sprintf(erro, "error:semantic:%d:%d: size of array '%s' is negative\n%s\n%*s"
                    ,getSymbolLinha(symbol),getSymbolColuna(symbol), getSymbolName(symbol), str, getSymbolColuna(symbol),"^");
            }
        }else{
            setExpValue(exp, percorreExpressionInt(exp,symbolTable, globalTable));
            if(getExpValue(exp) == 0){
                sprintf(erro, "error:semantic:%d:%d: size of array '%s' is zero\n%s\n%*s"
                    ,getSymbolLinha(symbol),getSymbolColuna(symbol), getSymbolName(symbol), str, getSymbolColuna(symbol),"^");   
            }else if(getExpValue(exp) < 0){
                sprintf(erro, "error:semantic:%d:%d: size of array '%s' is negative\n%s\n%*s"
                    ,getSymbolLinha(symbol),getSymbolColuna(symbol), getSymbolName(symbol), str, getSymbolColuna(symbol),"^");
            }
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
        }
        if(getExpType(e) == PLUS_EXP){
            Expression left = getLeftChild(e);
            Symbol var = getElemHash(globalTableFixa, getExpVarName(left));
            if(var == NULL)
                var = getElemHash(localTable, getExpVarName(left));
            if(left != NULL && getExpType(left) == EXP_VARIAVEL && getSymbolPonteiro(var) != 0){
                printf("error:semantic:%d:%d: wrong type argument to unary plus\n%s\n%*s",
                    getExpLinha(e), getExpColuna(e), getExpText(e), getExpColuna(e), "^");
                exit(0);    
            }
        }
        if(getExpType(e) == POINTER_EXP){
            Expression left = getLeftChild(e);
            Symbol var = getElemHash(globalTableFixa, getExpVarName(left));
            if(var == NULL)
                var = getElemHash(localTable, getExpVarName(left));
            if(left != NULL && getExpType(left) == EXP_VARIAVEL && getSymbolPonteiro(var) == 0){
                printf("error:semantic:%d:%d: invalid type argument of unary '*' (have '%s')\n%s\n%*s",
                    getExpLinha(e), getExpColuna(e), getSymbolType(var), getExpText(e), getExpColuna(e), "^");
                exit(0);    
            }
        }
        if(getExpType(e) == EXP_ASSIGN){
            
            Expression left = getLeftChild(e);
            if(getExpType(left) == EXP_STRING){
                printf("error:semantic:%d:%d: assignment of read-only location %s\n%s\n%*s",
                    getExpLinha(e), getExpColuna(e), getExpVarName(left),getExpText(e), getExpColuna(e), "^");
                exit(0); 
            }
            if(getExpType(left) != EXP_VARIAVEL){
                printf("error:semantic:%d:%d: lvalue required as left operand of assignment\n%s\n%*s",
                    getExpLinha(e), getExpColuna(e), getExpText(e), getExpColuna(e), "^");
                exit(0); 
            }

            Expression right = getRightChild(e);
            if(getExpType(right) == EXP_VARIAVEL){
                Expression left1 = getLeftChild(right);
                if(left1 != NULL && getExpType(left1) == ARRAY_EXP){
                    Expression sub = getLeftChild(left1);
                    if(getExpPonteiro(right)>1){
                        printf("error:semantic:%d:%d: subscripted value is neither array nor pointer\n%s\n%*s"
                                ,getExpLinha(left1),getExpColuna(left1), getExpText(e), getExpColuna(left1),"^");
                        exit(0); 
                    }
                }
                Expression func = getLeftChild(right);
                if(func != NULL && getExpType(func) == EXP_FUNC){

                    Symbol var = getElemHash(globalTableFixa, getExpVarName(left));
                    if(var == NULL)
                        var = getElemHash(localTable, getExpVarName(left));
                    Symbol func = getElemHash(globalTableFixa, getExpVarName(right));
                    if(func == NULL)
                        func = getElemHash(localTable, getExpVarName(right));
                    
                    if(getSymbolSpec(func) != PROTOTIPO && getSymbolSpec(func) != FUNCAO){
                        printf("error:semantic:%d:%d: called object '%s' is not a function or function pointer\n%s\n%*s"
                                ,getExpLinha(right),getExpColuna(right), getSymbolName(func), getExpText(e), getExpColuna(right),"^");
                        exit(0); 
                    }

                    if(strcmp(getSymbolType(func),"void") == 0){
                        printf("error:semantic:%d:%d: void value not ignored as it ought to be\n%s\n%*s",
                            getExpLinha(e), getExpColuna(e), getExpText(e), getExpColuna(e), "^");
                        exit(0); 
                    }    
                    
                }
                Symbol var1 = getElemHash(globalTableFixa, getExpVarName(left));
                if(var1 == NULL)
                    var1 = getElemHash(localTable, getExpVarName(left));
                Symbol var2 = getElemHash(globalTableFixa, getExpVarName(right));
                if(var2 == NULL)
                    var2 = getElemHash(localTable, getExpVarName(right));

                if(getSymbolPonteiro(var1) != getSymbolPonteiro(var2)){
                    char type1[20];
                    strcpy(type1, getSymbolType(var1));
                    int n;
                    for(n=0; n<getSymbolPonteiro(var1); n++) strcat(type1, "*");
                    char type2[20];
                    strcpy(type2, getSymbolType(var2));
                    for(n=0; n<getSymbolPonteiro(var2); n++) strcat(type2, "*");
                    printf("error:semantic:%d:%d: incompatible types when assigning to type '%s' from type '%s'\n%s\n%*s"
                        ,getExpLinha(e),getExpColuna(e), type1, type2, getExpText(e), getExpColuna(e),"^");
                    exit(0);   
                }
            }
            if(getExpType(right) == OPERADOR_BITWISE){
                Expression sub = getLeftChild(right);
                if(getExpType(sub) != EXP_VARIAVEL){
                    printf("error:semantic:%d:%d: lvalue required as unary '&' operand\n%s\n%*s",
                            getExpLinha(right), getExpColuna(right), getExpText(e), getExpColuna(right), "^");
                    exit(0); 
                }
            }
        }
        if(getExpType(e) == OPERADOR_PLUS || getExpType(e) == OPERADOR_SUB){
            Expression left = getLeftChild(e);
            Expression right = getRightChild(e);
            if(getExpType(left) == EXP_VARIAVEL && getExpType(right) == EXP_VARIAVEL){
                Symbol var1 = getElemHash(globalTableFixa, getExpVarName(left));
                if(var1 == NULL)
                    var1 = getElemHash(localTable, getExpVarName(left));
                Symbol var2 = getElemHash(globalTableFixa, getExpVarName(right));
                if(var2 == NULL)
                    var2 = getElemHash(localTable, getExpVarName(right));
                if(getSymbolPonteiro(var1) != 0 || getSymbolPonteiro(var2) != 0){
                    char type1[20];
                    strcpy(type1, getSymbolType(var1));
                    int n;
                    for(n=0; n<getSymbolPonteiro(var1); n++) strcat(type1, "*");
                    char type2[20];
                    strcpy(type2, getSymbolType(var2));
                    for(n=0; n<getSymbolPonteiro(var2); n++) strcat(type2, "*");   
                    printf("error:semantic:%d:%d: invalid operands to binary '%c' (have '%s' and '%s')\n%s\n%*s",
                            getExpLinha(e), getExpColuna(e),getExpType(e) == OPERADOR_PLUS ? '+' : '-', type1, type2,getExpText(e), getExpColuna(e), "^");
                    exit(0); 
                }
            }

        }
        if(getExpType(e) == EXP_VARIAVEL && constante){
            Symbol var = getElemHash(globalTableFixa, getExpVarName(e));
            if(var == NULL)
                var = getElemHash(localTable, getExpVarName(e));
            if(var != NULL && getSymbolSpec(var) != CONSTANTE){
                printf("error:semantic:%d:%d: '%s' initializer element is not constant\n%s\n%*s",
                        getExpLinha(e), getExpColuna(e), getExpVarName(e),texto, getExpColuna(e), "^");
                exit(0);        
            }    
        }
        if(getExpType(e) == EXP_STRING && constante){
            printf("error:semantic:%d:%d: string type is not compatible with define\n%s\n%*s",
                    getExpLinha(e), getExpColuna(e),texto, getExpColuna(e), "^");
            exit(0); 
        }
        if(getExpType(e) == EXP_VARIAVEL && array){
            Symbol var = getElemHash(globalTableFixa, getExpVarName(e));
            if(var == NULL)
                var = getElemHash(localTable, getExpVarName(e));
            if(var != NULL && getSymbolSpec(var) != CONSTANTE){
                printf("error:semantic:%d:%d: '%s' initializer element is not constant\n%s\n%*s"
                    ,getExpLinha(e),getExpColuna(e), getExpVarName(e), texto, getExpColuna(e),"^");
                exit(0);        
            }    
        }
        if(getExpType(e) == EXP_LSHIFT || getExpType(e) == EXP_RSHIFT){
            Expression left = getLeftChild(e);
            Expression right = getRightChild(e);
            if(getExpType(right) == EXP_VARIAVEL){
                Symbol var = getElemHash(globalTableFixa, getExpVarName(right));
                if(var == NULL)
                    var = getElemHash(localTable, getExpVarName(right));
                if(strcmp(getSymbolName(var),"int") != 0 || getSymbolPonteiro(var) != 0){
                    char type[20];
                    strcpy(type, getSymbolType(var));
                    int n;
                    for(n=0; n<getSymbolPonteiro(var); n++) strcat(type, "*");
                    printf("error:semantic:%d:%d: cannot convert from '%s' to int\n%s\n%*s"
                        ,getExpLinha(e),getExpColuna(e), type, getExpText(e), getExpColuna(e),"^");
                    exit(0);   
                }
            }
            int vL = percorreExpressionInt(left, localTable, globalTableFixa);
            int vR = percorreExpressionInt(right, localTable, globalTableFixa);
            if(vR>4){
                printf("warning:%d:%d: %s shift count >= width of type\n%s\n%*s\n"
                    ,getExpLinha(e),getExpColuna(e), getExpType(e) == EXP_LSHIFT ? "left" : "right", getExpText(e), getExpColuna(e),"^");
            }
            if(vR<0){
                printf("error:semantic:%d:%d: %s shift count is negative\n%s\n%*s"
                    ,getExpLinha(e),getExpColuna(e), getExpType(e) == EXP_LSHIFT ? "left" : "right",getExpText(e), getExpColuna(e),"^");
                exit(0);  
            }

        }
        if(getExpType(e) == CMP_LESST || getExpType(e) == CMP_LESSEQ || getExpType(e) == CMP_GREATERT || getExpType(e) == CMP_GREATEREQ){
            Expression left = getLeftChild(e);
            Expression right = getRightChild(e);
            Symbol var1=NULL, var2=NULL;
            int bitwiseLeft = 0, bitwiseRight = 0;
            if(getExpType(left) == OPERADOR_BITWISE){
                left = getLeftChild(left);
                bitwiseLeft=1;
            }
            if(getExpType(right) == OPERADOR_BITWISE){
                right = getLeftChild(right);
                bitwiseRight=1;
            }
            if(getExpType(left) == EXP_STRING){
                var1 = createSymbol("aa","char",VARIAVEL,NULL,0,0);
                setSymbolPonteiro(var1,1);
                setExpType(left,EXP_VARIAVEL);
            }
            if(getExpType(right) == EXP_STRING){
                var2 = createSymbol("aa","char",VARIAVEL,NULL,0,0);
                setSymbolPonteiro(var2,1);
                setExpType(right,EXP_VARIAVEL);
            }
            if(getExpType(left) == EXP_VARIAVEL && getExpType(right) == EXP_VARIAVEL){
                if(var1 == NULL)
                    var1 = getElemHash(globalTableFixa, getExpVarName(left));
                if(var1 == NULL)
                    var1 = getElemHash(localTable, getExpVarName(left));
                if(var2 == NULL)
                    var2 = getElemHash(globalTableFixa, getExpVarName(right));
                if(var2 == NULL)
                    var2 = getElemHash(localTable, getExpVarName(right));
                if(getSymbolPonteiro(var1)+bitwiseLeft != 0 || getSymbolPonteiro(var2)+bitwiseRight != 0){
                    char type1[20];
                    strcpy(type1, getSymbolType(var1));
                    int n;
                    for(n=0; n<getSymbolPonteiro(var1)+bitwiseLeft; n++) strcat(type1, "*");
                    char type2[20];
                    strcpy(type2, getSymbolType(var2));
                    for(n=0; n<getSymbolPonteiro(var2)+bitwiseRight; n++) strcat(type2, "*");
                    char op[3];
                    switch (getExpType(e)){
                    case CMP_LESST:
                        strcpy(op,"<");
                        break;
                    case CMP_LESSEQ:
                        strcpy(op,"<=");
                        break;
                    case CMP_GREATERT:
                        strcpy(op,">");
                        break;
                    case CMP_GREATEREQ:
                        strcpy(op,">=");
                        break;
                    }
                    if(strcmp(getSymbolType(var1), getSymbolType(var2)) != 0){
                        printf("error:semantic:%d:%d: comparison between '%s' and '%s' operator '%s'\n%s\n%*s",
                                getExpLinha(e), getExpColuna(e),type1, type2, op, showText?texto:getExpText(e), getExpColuna(e), "^");
                        exit(0);
                    }else{
                        printf("warning:%d:%d: comparison between '%s' and '%s' operator '%s'\n%s\n%*s\n",
                                getExpLinha(e), getExpColuna(e),type1, type2, op, showText?texto:getExpText(e), getExpColuna(e), "^");
                    }
                }
            }
        }
        if(constante){
            int value = percorreExpressionInt(e,localTable, globalTableFixa);
        }

        if(getExpType(e) == EXP_VARIAVEL){
            Expression left = getLeftChild(e);
            if(left != NULL && getExpType(left) == ARRAY_EXP){
                Expression sub = getLeftChild(left);
                if(getExpPonteiro(e)>1){
                    printf("error:semantic:%d:%d: subscripted value is neither array nor pointer\n%s\n%*s"
                            ,getExpLinha(left),getExpColuna(left),  showText?texto:getExpText(e), getExpColuna(left),"^");
                    exit(0); 
                }
                if(getExpType(sub) == EXP_VARIAVEL){
                    Symbol var = getElemHash(globalTableFixa, getExpVarName(sub));
                    if(var == NULL)
                        var = getElemHash(localTable, getExpVarName(sub));

                    if(getSymbolPonteiro(var) != 0 || strcmp(getSymbolType(var),"void") == 0){
                        printf("error:semantic:%d:%d: array subscript is not an integer\n%s\n%*s"
                            ,getExpLinha(left),getExpColuna(left),  showText?texto:getExpText(e), getExpColuna(left),"^");
                        exit(0); 
                    }
                }
                int valor = percorreExpressionInt(sub, localTable, globalTableFixa);
                if(valor>getExpValue(sub)){
                    printf("warning:%d:%d: array index out of bounds\n%s\n%*s\n",
                                getExpLinha(left), getExpColuna(left), showText?texto:getExpText(left), getExpColuna(left), "^");
                }
            }
            Expression func = getLeftChild(e);
            if(func != NULL && getExpType(func) == EXP_FUNC){

                Symbol var = getElemHash(globalTableFixa, getExpVarName(e));
                if(var == NULL)
                    var = getElemHash(localTable, getExpVarName(e));

                if(getSymbolSpec(var) == PROTOTIPO){
                    Lista parametrosVar = getListaParametros(var);
                    Lista parametrosFunc = getExpParametros(func);
                    int sizeVar = getListaSize(parametrosVar), sizeFunc = getListaSize(parametrosFunc);
                    if(sizeVar>sizeFunc){
                        printf("error:semantic:%d:%d: too few arguments to function '%s'\n%s\n%*s"
                            ,getExpLinha(e),getExpColuna(e), getExpVarName(e), getExpText(e), getExpColuna(e),"^");
                        exit(0); 
                    }else if(sizeVar<sizeFunc){
                        printf("error:semantic:%d:%d: too many arguments to function '%s'\n%s\n%*s"
                            ,getExpLinha(e),getExpColuna(e), getExpVarName(e), getExpText(e), getExpColuna(e),"^");
                        exit(0); 
                    }else{
                        int k=sizeFunc;
                        while (parametrosVar != NULL && parametrosFunc != NULL){
                            Symbol pVar = get(parametrosVar);
                            Expression pExp = get(parametrosFunc);

                            Symbol pFunc;

                            int bitwise = 0;
                            if(getExpType(pExp)== OPERADOR_BITWISE){
                                bitwise++;
                                pExp = getLeftChild(pExp);
                            }

                            if(getExpType(pExp) == EXP_VARIAVEL){
                                pFunc = getElemHash(globalTableFixa, getExpVarName(pExp));
                                if(pFunc == NULL)
                                    pFunc = getElemHash(localTable, getExpVarName(pExp));
                                
                                char type1[20];
                                strcpy(type1, getSymbolType(pFunc));
                                int n = 0;
                                for(n=0; n<getSymbolPonteiro(pFunc)+bitwise; n++) strcat(type1, "*");

                                char type2[20];
                                strcpy(type2, getSymbolType(pVar));
                                for(n=0; n<getSymbolPonteiro(pVar); n++) strcat(type2, "*");

                                if((getSymbolType(pVar) != getSymbolType(pFunc)) || (getSymbolPonteiro(pVar) != getSymbolPonteiro(pFunc)+bitwise) ){
                                    printf("error:semantic:%d:%d: incompatible type for argument '%d' of '%s' expected '%s' but argument is of type '%s'\n%s\n%*s"
                                        ,getExpLinha(e),getExpColuna(e), k,getExpVarName(e), type2, type1, getExpText(e), getExpColuna(e),"^");
                                    exit(0); 
                                }
                            }

                            k--;
                            parametrosVar = getProx(parametrosVar);
                            parametrosFunc = getProx(parametrosFunc);
                        }
                        
                    }
                }
                
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
        int a,b;
        Expression esq = getLeftChild(exp);
        Expression dir = getRightChild(exp);
        if(esq != NULL){
            if(dir!=NULL){
                switch (getExpType(exp)){
                    case OPERADOR_MULT:
                        return percorreExpressionInt(esq, symbolTable, globalTable) * percorreExpressionInt(dir, symbolTable, globalTable);
                    case OPERADOR_DIV:
                        a = percorreExpressionInt(esq, symbolTable, globalTable);
                        b = percorreExpressionInt(dir, symbolTable, globalTable);
                        if(b == 0){
                            printf("error:semantic:%d:%d: division by zero\n%s\n%*s"
                                ,getExpLinha(exp),getExpColuna(exp), getExpText(exp), getExpColuna(exp),"^");
                            exit(0); 
                        }
                        return  a/b ;
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