#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define IF 3
#define THEN 7
#define BEGIN 12
#define PRINT 17
#define END 20
#define ELSE 23
#define SEMI 24
#define EQ 25
#define NUM 27

typedef struct elemento{
    int token;
    struct elemento *prox;
}No;

typedef struct Fila {
    int tamanho;
    No* primeiro;
    No* ultimo;
}Fila;

void iniciaFila(Fila* fila){
    fila->tamanho = 0;
    fila->primeiro = NULL;
    fila->ultimo = NULL;
}

void push(Fila* fila, int token) {
    if (fila->tamanho == 0) {
        fila->primeiro = (No*)malloc(sizeof(No));
        fila->primeiro->token = token;
        fila->ultimo = fila->primeiro;
        fila->tamanho++;
    }
    else {
        fila->ultimo->prox = (No*)malloc(sizeof(No));
        fila->ultimo->prox->token = token;
        fila->ultimo->prox->prox = NULL;
        fila->ultimo = fila->ultimo->prox;
        fila->tamanho++;
    }
}

int pull(Fila* fila) {
    int token;
    No* aux;
    
    token = -1;
    
    if (fila->tamanho == 0) {
        return -1;
    }
    else {
        token = fila->primeiro->token;
        aux = fila->primeiro;
        fila->primeiro = fila->primeiro->prox;
        free(aux);
        fila->tamanho--;
        return token;
    }
    return -1;
}


bool states[]={false,false,false,true,false,false,false,true,false,false,false,false,true,false,false,false,false,true,false,false,true,false,false,true,true,true,false,true};

char symbols[] = {'0','1','2','3','4','5','6',
                  '7','8','9','+','-','=',';',
                  'b','d','e','f','g','h','i',
                  'l','n','p','r','s','t'
                };            
int edges[28][28]={/* 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, +, -, =, ;, b, d, e, f, g, h, i, l, n, p, r, s, t, other*/
       /*state 0*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 1*/  {27,27,27,27,27,27,27,27,27,27,26,26,25,24, 8, 0,18, 0, 0, 0, 2, 0, 0,13, 0, 0, 4, 0},
       /*state 2*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 3*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 4*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 5*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 6*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0},
       /*state 7*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 8*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 9*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 10*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,11, 0, 0, 0, 0, 0, 0, 0},
       /*state 11*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,12, 0, 0, 0, 0, 0},
       /*state 12*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 13*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,14, 0, 0, 0},
       /*state 14*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,15, 0, 0, 0, 0, 0, 0, 0},
       /*state 15*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,16, 0, 0, 0, 0, 0},
       /*state 16*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,17, 0},
       /*state 17*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 18*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,21,19, 0, 0, 0, 0, 0},
       /*state 19*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 20*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 21*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,22, 0, 0},
       /*state 22*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 23*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 24*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 25*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 26*/ {27,27,27,27,27,27,27,27,27,27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 27*/ {27,27,27,27,27,27,27,27,27,27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    }; 

int TOKENS_IDENTIFICADOS=0;

int getIndex(char symbol){
    int i;
    for(i=0;i<sizeof(symbols);i++){
        if(symbol==symbols[i])
            return i;
    }
    return i;
}

int isFinalState(int state){
    return states[state];
}

int lexico(char * info,Fila* fila){
    int lastFinal = 0;
    int currentState = 1;
    int verticalCursor=0, bottomCursor=0, topCursor=0,indexToken=0;
    char token[100];
    char substr[100];
    int i;
    while(info[verticalCursor]!='\0'){
        topCursor=verticalCursor;
        currentState=1;
        strcpy(token,"");
        strcpy(substr,"");
        indexToken=0;
        i=0;
        while(info[bottomCursor]!='\0'){
            char nextSymbol = info[bottomCursor];
            int index =getIndex(nextSymbol);
            currentState = edges[currentState][index];
            if(isFinalState(currentState)){
                while(topCursor<=bottomCursor){
                    if(info[topCursor]!='\n'){
                        token[indexToken]=info[topCursor];
                        indexToken++;
                    }
                    topCursor++;
                    
                }
                lastFinal=currentState;
            }
            if(currentState==0){
                if(strlen(token)==0)
                    bottomCursor=topCursor;
                break;
            }
            substr[i]=info[bottomCursor];
            i++;
            bottomCursor++;
        }
        token[indexToken]='\0';
        substr[i]='\0';
        if(strlen(token)>0){
            if(strlen(substr)>strlen(token))bottomCursor=topCursor;
            push(fila,lastFinal);
            TOKENS_IDENTIFICADOS++;
        }else{
            if(info[bottomCursor]!=' ' && info[bottomCursor]!='\n'){
                if(TOKENS_IDENTIFICADOS!=0)printf("\n");
                printf("ERRO");
                bottomCursor++;
                TOKENS_IDENTIFICADOS++;
            }else bottomCursor++;
        } 
        verticalCursor=bottomCursor; 
    }
}

void error(){
    printf("ERRO SINTATICO");
    exit(1);
}

void S(int token, Fila* tokens);
void L(int token, Fila* tokens);
void E(int token, Fila* tokens);

void eat(int t,int token,Fila* tokens){
    if (token==t){
        printf("%d",t);
        token = pull(tokens);
    }else{
        error();
    }

}

void S(int token, Fila* tokens){
    switch(token) {
        case IF: eat(IF,token,tokens); E(token,tokens); eat(THEN,token,tokens); S(token,tokens); eat(ELSE,token,tokens); S(token,tokens); break;
        case BEGIN: eat(BEGIN,token,tokens); S(token,tokens); L(token,tokens); break;
        case PRINT: eat(PRINT,token,tokens); E(token,tokens); break;
        default: error(); 
    }
}

void L(int token, Fila* tokens){
    switch(token) {
        case END: eat(END,token,tokens); break;
        case SEMI: eat(SEMI,token,tokens); S(token,tokens); L(token,tokens); break;
        default: error(); 
    }
}

void E(int token, Fila* tokens){ eat(NUM,token,tokens); eat(EQ,token,tokens); eat(NUM,token,tokens); }


void sintatico(Fila* tokens){
    int token = pull(tokens);
    S(token,tokens);
}

int main(){
    char linha[2048];
    Fila* tokens;
    iniciaFila(tokens);
    while(fgets(linha,2048,stdin)!=NULL){
        lexico(linha,tokens);
        sintatico(tokens);
    }
}