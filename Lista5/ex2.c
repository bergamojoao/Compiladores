#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool states[]={false,false,true,true,true,true,true,true,true,true,false,true,true,true};

char symbols[] = {'0','1','2','3','4','5','6','7','8',
                  '9','a','b','c','d','e','f','g','h',
                  'i','j','k','l','m','n','o','p','q',
                  'r','s','t','u','v','w','x','y','z',
                  '.',' ','-','\n'
                };               

int edges[14][41]={/*0,1,2,3,4,5,6,7,8,9,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,., ,-,\n,other*/
       /*state 0*/  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
       /*state 1*/  {7,7,7,7,7,7,7,7,7,7,4,4,4,4,4,4,4,4,2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,12,9,0,13},
       /*state 2*/  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0},
       /*state 3*/  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0},
       /*state 4*/  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0},
       /*state 5*/  {6,6,6,6,6,6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
       /*state 6*/  {6,6,6,6,6,6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
       /*state 7*/  {7,7,7,7,7,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0},
       /*state 8*/  {8,8,8,8,8,8,8,8,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
       /*state 9*/  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,0,0},
       /*state 10*/ {0,0,0,0,0,0,0,0,0,0,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,0,0,0,11,0},
       /*state 11*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
       /*state 12*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,0,0},
       /*state 13*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

int getIndex(char symbol){
    for(int i=0;i<sizeof(symbols);i++){
        if(symbol==symbols[i])
            return i;
    }
    return 40;
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
                        if(info[topCursor]!='\n'){
                            token[indexToken]=info[topCursor];
                            indexToken++;
                        }
                        topCursor++;
                        
                    }
                    lastFinal=currentState;
                }
                if(currentState==0)
                    break;
                bottomCursor++;
            }  
        }
        token[indexToken]='\0';
        if(strlen(token)>0){
            switch (lastFinal){
                case 2:
                    printf("%s ID\n",token);
                    break;
                case 3:
                    printf("%s IF\n",token);
                    break;
                case 4:
                    printf("%s ID\n",token);
                    break;
                case 5:
                    printf("%s error\n",token);
                    break;
                case 6:
                    printf("%s REAL\n",token);
                    break;
                case 7:
                    printf("%s NUM\n",token);
                    break;
                case 8:
                    printf("%s REAL\n",token);
                    break;
                case 9:
                    printf("%s error\n",token);
                    break;
                case 11:
                    printf("%s comment\n",token);
                    break;
                case 12:
                    printf("white space\n");
                    break;
                case 13:
                    printf("%s error\n",token);
                    break;
            }
        
        }else bottomCursor++;
        verticalCursor=bottomCursor; 
    }
}

int main(){
    analyze("@josodsaso if abc teste 64548 58.8\n--commenttest\n");
}

