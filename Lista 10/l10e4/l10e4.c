#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define PLUS 2
#define MULT 3
#define L_PAREN 4
#define R_PAREN 5
#define DOLAR 6
#define ID 7





typedef struct elemento{
    int token;
    int linha;
	char str[100];
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

void push(Fila* fila, int token,int linha,char* str) {
    if (fila->tamanho == 0) {
        fila->primeiro = (No*)malloc(sizeof(No));
        fila->primeiro->token = token;
        fila->primeiro->linha = linha; 
		strcpy(fila->primeiro->str,str);
        fila->ultimo = fila->primeiro;
        fila->tamanho++;
    }
    else {
        fila->ultimo->prox = (No*)malloc(sizeof(No));
        fila->ultimo->prox->token = token;
        fila->ultimo->prox->linha = linha;
		strcpy(fila->ultimo->prox->str,str);
        fila->ultimo->prox->prox = NULL;
        fila->ultimo = fila->ultimo->prox;
        fila->tamanho++;
    }
}

No* pull(Fila* fila) {
    int token;
    No* aux;
    
    
    if (fila->tamanho == 0) {
        return NULL;
    }
    else {
        aux = fila->primeiro;
        fila->primeiro = fila->primeiro->prox;
        fila->tamanho--;
        return aux;
    }
    return NULL;
}

int getToken(No* no){
    return no->token;
}

int getLinha(No* no){
    return no->linha;
}

char* getStr(No* no){
	return no->str;
}

No* token;

bool states[]={false,false,true,true,true,true,true,true};

char symbols[] = {'0','1','2','3','4','5','6','7','8','9',
                  '(',')','+','*','$','a','b','c','d','e',
				  'f','g','h','i','j','k','l','m','n','o',
				  'p','q','r','s','t','u','v','w','x','y','z'};

int edges[90][42]={/* 0  1  2  3  4  5  6  7  8  9  (  )  +  *  $  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z  other*/
       /*state 0*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	   /*state 1*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 2, 3, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0},
	   /*state 2*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	   /*state 3*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	   /*state 4*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	   /*state 5*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	   /*state 6*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	   /*state 7*/  { 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0},
    }; 

int TOKENS_IDENTIFICADOS=0;
bool ERRO_SINTATICO=false;

int getIndex(char symbol){
    int i;
    if(symbol>='A' && symbol<='Z')
        symbol+=32;
    for(i=0;i<sizeof(symbols);i++){
        if(symbol==symbols[i])
            return i;
    }
    return i;
}

int isFinalState(int state){
    return states[state];
}

int lexico(char * info,Fila* fila,int count){
    int lastFinal = 0;
    int currentState = 1;
    int verticalCursor=0, bottomCursor=0, topCursor=0,indexToken=0;
    char token[1000];
    char substr[1000];
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
            if(strcmp(token," ")!=0){
                switch (lastFinal){
                    case PLUS:
                        push(fila,lastFinal,count,"+");
                        break;
                    case MULT:
                        push(fila,lastFinal,count,"*");
                        break;
                    case L_PAREN:
                        push(fila,lastFinal,count,"(");
                        break;
                    case R_PAREN:
                        push(fila,lastFinal,count,")");
                        break;
                    case DOLAR:
                        push(fila,lastFinal,count,"$");
                        break;
                    case ID:
                        push(fila,lastFinal,count,"id");
                        break;
                    default:
                        break;
                }
            }
            
            TOKENS_IDENTIFICADOS++;
        }else{
            if(info[bottomCursor]!=' ' && info[bottomCursor]!='\n'){
				printf("ERRO LEXICO: %c",info[bottomCursor]);
				return -1;
            }else bottomCursor++;
        } 
        verticalCursor=bottomCursor; 
    }
    return 0;
}


void eat(Fila* tokens, int validation, int* err){
    if(*err==1)
        return;
    
    if(getToken(token)==validation){
        int ant = getToken(token);
        token=pull(tokens);
        if(token==NULL && ant!=DOLAR){
            *err = 1;
            printf("ERRO SINTATICO EM: ESPERADO: +, *, ), $");
        }
    }
    else{
        *err = 1;
        printf("ERRO SINTATICO EM: %s ESPERADO: +, *, ), $" ,getStr(token));
    }
}


void S(Fila* tokens, int *err);
void E(Fila* tokens, int *err);
void EL(Fila* tokens, int *err);
void T(Fila* tokens, int *err);
void TL(Fila* tokens, int *err);
void F(Fila* tokens, int *err);



void S(Fila* tokens, int *err){

	if(*err == 1)
		return;

	E(tokens,err);
    eat(tokens,DOLAR,err);
}

void E(Fila* tokens, int *err){

	if(*err == 1)
		return;

	T(tokens,err);
    EL(tokens,err);
}

void EL(Fila* tokens, int *err){

	if(*err == 1)
		return;

	switch (getToken(token)){
        case PLUS:
            eat(tokens,PLUS,err);
            T(tokens,err);
            EL(tokens,err);
            break;
        default:
            break;
    }
}

void T(Fila* tokens, int *err){

	if(*err == 1)
		return;

	F(tokens,err);
    TL(tokens,err);
}

void TL(Fila* tokens, int *err){

	if(*err == 1)
		return;

	switch (getToken(token)){
        case MULT:
            eat(tokens,MULT,err);
            F(tokens,err);
            TL(tokens,err);
            break;
        default:
            break;
    }
}

void F(Fila* tokens, int *err){

	if(*err == 1)
		return;

	switch (getToken(token)){
        case L_PAREN:
            eat(tokens,L_PAREN,err);
            E(tokens,err);
            eat(tokens,R_PAREN,err);
            break;
        case ID:
            eat(tokens,ID,err);
            break;
        default:
            break;
    }
}




void sintatico(Fila *tokens){
    int err = 0;
	token = pull(tokens);
	S(tokens,&err);
	if(err==0)
		printf("CADEIA ACEITA");
}

int main(){
    char linha[8000];
	
    Fila* tokens = malloc(sizeof(Fila));
    iniciaFila(tokens);
    int count = 1;
    while(fgets(linha,8000,stdin)!=NULL){
        if(count!=1)printf("\n");
        int status = lexico(linha,tokens,count);
        if(status>=0){
            sintatico(tokens);
        }
        while(pull(tokens)!=NULL);

        count++;
    }
	
}