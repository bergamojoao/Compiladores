#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool states[]={false,false,false,true,false,false,true,false,true,false,true,false,false,true,true,true,true,true,true,true,false,false,true};

char symbols[] = {'0','1','2','3','4','5','6',
                  '7','8','9','+','-','a','c',
                  'e','h','i','r','s','t'
                };            
int edges[23][21]={/* 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, +, -, a, c, e, h, i, r, s, t,other*/
       /*state 0*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 1*/  {19,19,19,19,19,19,19,19,19,19,17,18, 0,11, 0, 2, 0, 0, 4, 0, 0},
       /*state 2*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 7, 0, 0, 0, 0},
       /*state 3*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0},
       /*state 4*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0},
       /*state 5*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0},
       /*state 6*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 7*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0},
       /*state 8*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 9*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10, 0, 0},
       /*state 10*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 11*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,12, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 12*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,14, 0,13, 0},
       /*state 13*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,15, 0, 0},
       /*state 14*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,16, 0, 0},
       /*state 15*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 16*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 17*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 18*/ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 19*/ {19,19,19,19,19,19,19,19,19,19, 0, 0, 0, 0,20, 0, 0, 0, 0, 0, 0},
       /*state 20*/ {22,22,22,22,22,22,22,22,22,22,21,21, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 21*/ {22,22,22,22,22,22,22,22,22,22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       /*state 22*/ {22,22,22,22,22,22,22,22,22,22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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

int analyze(char * info){
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
            if(TOKENS_IDENTIFICADOS!=0)printf("\n");
            switch (lastFinal){
                case 3:
                    printf("ELE");
                    break;
                case 6:
                    printf("ELA");
                    break;
                case 8:
                    printf("DELE");
                    break;
                case 10:
                    printf("DELA");
                    break;
                case 13:
                    printf("GATO");
                    break;
                case 14:
                    printf("CARRO");
                    break;
                case 15:
                    printf("GATOS");
                    break;
                case 16:
                    printf("CARROS");
                    break;
                case 17:
                    printf("MAIS");
                    break;
                case 18:
                    printf("MENOS");
                    break;
                case 19:
                    printf("INTEIRO %s",token);
                    break;
                case 22:
                    printf("REAL %s",token);
                    break;
            }
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

int main(){
    char linha[2048];
    while(fgets(linha,2048,stdin)!=NULL)
        analyze(linha);
}
