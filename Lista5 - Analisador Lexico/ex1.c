#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool states[]={false,false,true,true,true,true,false,false,true};

char symbols[38] = {'0','1','2','3','4','5','6','7','8',
                    '9','+','-','a','b','c','d','e','f',
                    'g','h','i','j','k','l','m','n','o',
                    'p','q','r','s','t','u','v','w','x','y','z'
                };               

int edges[8][38]={/*0,1,2,3,4,5,6,7,8,9,+,-,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z*/
       /*state 0*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
       /*state 1*/ {5,5,5,5,5,5,5,5,5,5,3,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
       /*state 2*/ {2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
       /*state 3*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
       /*state 4*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
       /*state 5*/ {5,5,5,5,5,5,5,5,5,5,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
       /*state 6*/ {8,8,8,8,8,8,8,8,8,8,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
       /*state 7*/ {8,8,8,8,8,8,8,8,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

int getIndex(char symbol){
    for(int i=0;i<sizeof(symbols);i++){
        if(symbol==symbols[i])
            return i;
    }
    return -1;
}

int isFinalState(int state){
    return states[state];
}

int analyze(char * info){
    int lastFinal = 0;
    int currentState = 1;
    int verticalCursor=0, bottomCursor=0, topCursor=0,indexToken=0;
    char token[100];
    while(info[verticalCursor]!='\0'){
        topCursor=verticalCursor;
        currentState=1;
        strcpy(token,"");
        indexToken=0;
        while(info[bottomCursor]!='\0'){
            char nextSymbol = info[bottomCursor];
            int index =getIndex(nextSymbol);
            if(index==-1)
                break;
            else{
                currentState = edges[currentState][index];
                if(isFinalState(currentState)){
                    while(topCursor<=bottomCursor){
                        token[indexToken]=info[topCursor];
                        topCursor++;
                        indexToken++;
                    }
                    lastFinal=currentState;
                }
                if(currentState==0)
                    break;
                bottomCursor++;
            }  
        }
        token[indexToken]='\0';
        if(strlen(token)>0)
            printf("%s\n",token);
        else{
            if(info[bottomCursor]!='\n')
                printf("ERRO\n");
            bottomCursor++;
        }       
        verticalCursor=bottomCursor; 
    }
}

int main(){
    analyze("+-abcabc@\nabc");
}

