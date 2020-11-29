%{
typedef struct T{
	char tipo[10];
	double value;
	char f[10];
}Tipo;

#define YYSTYPE Tipo
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

extern int yylex();
extern void yyrestart(FILE *f);
extern char* yytext;
void yyerror(char *s);

double h_view_lo = -6.500000;
double h_view_hi = 6.500000;
double v_view_lo= -3.500000;
double v_view_hi= 3.500000;
int integral_steps= 1000;
bool draw_axis=true;
bool connect_dots=false;
int op=0;
char RPN[100] = "";
bool function=false;
bool integral=false;
bool num=false;
double resulF[10][3000];
int tam=80,auxInt=0;
double lInf,lSup;
int f=0;
char tela[25][80];
double matrix[10][10],aux[10][10];
int linha=0,coluna=0,auxColuna=0,auxLinha;




void configs();
void resetConfigs();
void about();
void montaFunc(int f,int s);
void montaNum(double value);
void calcFunc(char* op,int f);
void verificaOp(Tipo exp1, Tipo exp2,char* op);
void calcFuncLeft(char* op,int f,double value);
void calcFuncRight(char* op,int f,double value);
void integrate();
double min();
double max();
void preparaTela();
void plot();
void ajustaMatrix();
void showMatrix();
void solveDeterminant();

%}
%token EQUAL
%token ADD
%token SUB
%token MUL
%token DIV
%token POW
%token PORCENTAGEM
%token ABRE_PARENTESES
%token FECHA_PARENTESES
%token SEN
%token COS
%token TAN
%token ABS
%token VAR
%token NUM
%token EOL
%token SHOW;
%token RESET;
%token SETTINGS;
%token SET;
%token H_VIEW;
%token V_VIEW;
%token AXIS;
%token ON;
%token OFF;
%token PLOT;
%token INTEGRAL_STEPS;
%token INTEGRATE;
%token MATRIX;
%token SOLVE;
%token DET;
%token LINEAR_S;
%token ABOUT;
%token COLON;
%token SEMI_COLON;
%token COMMA;
%token L_SQUARE_BRACKET;
%token R_SQUARE_BRACKET;

%start S

%%

S:  COMANDOS EOL {printf(">");} S
	| error {} ;

COMANDOS: SHOW SETTINGS SEMI_COLON {configs();}
	| RESET SETTINGS SEMI_COLON {resetConfigs();}
	| SET H_VIEW NUM_FORM COLON NUM_FORM SEMI_COLON {h_view_lo=$3.value;h_view_hi=$5.value;}
	| SET V_VIEW NUM_FORM COLON NUM_FORM SEMI_COLON {v_view_lo=$3.value;v_view_hi=$5.value;}
	| SET AXIS ON SEMI_COLON {draw_axis=true;}
	| SET AXIS OFF SEMI_COLON {draw_axis=false;}
	| ABOUT SEMI_COLON {about();}
	| SET INTEGRAL_STEPS NUM_FORM SEMI_COLON {integral_steps=$3.value;}
	| INTEGRATE ABRE_PARENTESES NUM_FORM1 COLON NUM_FORM1 COMMA EXP1 FECHA_PARENTESES SEMI_COLON {integrate();auxInt=0;f=0;integral=false;}
	| PLOT SEMI_COLON {plot();}
	| PLOT ABRE_PARENTESES EXP FECHA_PARENTESES SEMI_COLON {f=0;function=false;strcpy(RPN,"");num=false;plot();}
	| MATRIX EQUAL L_SQUARE_BRACKET MATRIX1 R_SQUARE_BRACKET SEMI_COLON {ajustaMatrix();}
	| SHOW MATRIX SEMI_COLON {showMatrix();}
	| SOLVE DET SEMI_COLON {solveDeterminant();}
	| EXP {printf("\nFunction in RPN format:\n\n%s\n\n",RPN);strcpy(RPN,"");f=0;function=false;num=false;}
	| ;

MATRIX1: L_SQUARE_BRACKET MATRIX2 R_SQUARE_BRACKET 
	| L_SQUARE_BRACKET MATRIX2 R_SQUARE_BRACKET COMMA MATRIX1 ;

MATRIX2: NUM_FORM MAUX {aux[auxLinha-1][auxColuna]=$1.value;if(auxColuna>coluna)coluna=auxColuna;auxColuna++;};

MAUX : COMMA MATRIX2
	| {auxLinha++;auxColuna=0;} ;
		 

NUM_FORM: ADD NUM {$$.value=$2.value;strcpy($$.tipo,"D");integral=false;if(!function && !num){montaNum($2.value);num=true;}}
	| SUB NUM {$$.value=-$2.value;strcpy($$.tipo,"D");integral=false;if(!function && !num){montaNum($2.value);num=true;}}
	| NUM {$$.value=$1.value;strcpy($$.tipo,"D");integral=false;if(!function && !num){montaNum($1.value);num=true;}}

NUM_FORM1: ADD NUM {$$.value=$2.value;strcpy($$.tipo,"D");if(auxInt==0){lInf=$2.value;}else if(auxInt==1){lSup=$2.value;}auxInt++;integral=true;}
	| SUB NUM {$$.value=-$2.value;strcpy($$.tipo,"D");if(auxInt==0){lInf=-$2.value;}else if(auxInt==1){lSup=-$2.value;}auxInt++;integral=true;}
	| NUM {$$.value=$1.value;strcpy($$.tipo,"D");if(auxInt==0){lInf=$1.value;}else if(auxInt==1){lSup=$1.value;}auxInt++;integral=true;}
	
EXP: NUM_FORM {char aux[100];sprintf(aux,"%.6lf ",$$.value);strcat(RPN,aux);}
	| VAR {strcat(RPN,"x ");function=true;montaFunc(atoi($1.tipo),80);$$=$1;}
	| EXP ADD EXP {strcat(RPN,"+ ");verificaOp($1,$3,"+");}
	| EXP SUB EXP {strcat(RPN,"- ");verificaOp($1,$3,"-");}
	| EXP MUL EXP {strcat(RPN,"* ");verificaOp($1,$3,"*");}
	| EXP DIV EXP {strcat(RPN,"/ ");verificaOp($1,$3,"/");}
	| EXP POW EXP {strcat(RPN,"^ ");verificaOp($1,$3,"^");}
	| SEN ABRE_PARENTESES EXP FECHA_PARENTESES {strcat(RPN,"SEN ");if(function){calcFunc("SEN",atoi($3.tipo));strcpy($$.tipo,$3.tipo);}else{$$.value=sin($3.value);}}
	| COS ABRE_PARENTESES EXP FECHA_PARENTESES {strcat(RPN,"COS ");if(function){calcFunc("COS",atoi($3.tipo));strcpy($$.tipo,$3.tipo);}else{$$.value=cos($3.value);}}
	| TAN ABRE_PARENTESES EXP FECHA_PARENTESES {strcat(RPN,"TAN ");if(function){calcFunc("TAN",atoi($3.tipo));strcpy($$.tipo,$3.tipo);}else{$$.value=tan($3.value);}}
	| ABS ABRE_PARENTESES EXP FECHA_PARENTESES {strcat(RPN,"ABS ");if(function){calcFunc("ABS",atoi($3.tipo));strcpy($$.tipo,$3.tipo);}else{$$.value=abs($3.value);}}
	| ABRE_PARENTESES EXP FECHA_PARENTESES

EXP1: NUM_FORM1
	| VAR {function=true;montaFunc(atoi($1.tipo),integral_steps);$$=$1;}
	| EXP1 ADD EXP1 {verificaOp($1,$3,"+");}
	| EXP1 SUB EXP1 {verificaOp($1,$3,"-");}
	| EXP1 MUL EXP1 {verificaOp($1,$3,"*");}
	| EXP1 DIV EXP1 {verificaOp($1,$3,"/");}
	| EXP1 POW EXP1 {verificaOp($1,$3,"^");}
	| SEN ABRE_PARENTESES EXP1 FECHA_PARENTESES {if(function){calcFunc("SEN",atoi($3.tipo));strcpy($$.tipo,$3.tipo);function=false;}else{$$.value=sin($3.value);}}
	| COS ABRE_PARENTESES EXP1 FECHA_PARENTESES {if(function){calcFunc("COS",atoi($3.tipo));strcpy($$.tipo,$3.tipo);function=false;}else{$$.value=cos($3.value);}}
	| TAN ABRE_PARENTESES EXP1 FECHA_PARENTESES {if(function){calcFunc("TAN",atoi($3.tipo));strcpy($$.tipo,$3.tipo);function=false;}else{$$.value=tan($3.value);}}
	| ABS ABRE_PARENTESES EXP1 FECHA_PARENTESES {if(function){calcFunc("ABS",atoi($3.tipo));strcpy($$.tipo,$3.tipo);function=false;}else{$$.value=abs($3.value);}}
	| ABRE_PARENTESES EXP1 FECHA_PARENTESES;


%%

void montaFunc(int f,int s){
	tam=s;
	double espacX,attr;
	if(integral){
		espacX=(lSup-lInf)/integral_steps;
		attr=lInf;
	}else{
		espacX = (h_view_hi-h_view_lo)/tam;
		attr = h_view_lo;
	}
	int i;
	for(i=0;i<tam;i++){
		resulF[f][i]=attr;
		attr+=espacX;
	}
}

void montaNum(double value){
	int i;
	for(i=0;i<80;i++){
		resulF[f][i]=value;
	}
}

void verificaOp(Tipo exp1, Tipo exp2,char* op){
	if(strcmp(exp1.tipo,"D")!=0){
		if(strcmp(exp2.tipo,"D")==0){
			calcFuncLeft(op,atoi(exp2.tipo),exp2.value);
		}else{
			int i;
			int f1,f2;
			f1=atoi(exp1.tipo);
			f2=atoi(exp2.tipo);
			strcpy(exp2.tipo,exp1.tipo);

			if(strcmp(op,"+")==0){
				for(i=0;i<tam;i++)
					resulF[f1][i]=resulF[f1][i]+resulF[f2][i];
			}else if(strcmp(op,"-")==0){
				for(i=0;i<tam;i++)
					resulF[f1][i]=resulF[f1][i]-resulF[f2][i];
			}else if(strcmp(op,"*")==0){
				for(i=0;i<tam;i++)
					resulF[f1][i]=resulF[f1][i]*resulF[f2][i];
			}else if(strcmp(op,"/")==0){
				for(i=0;i<tam;i++)
					resulF[f1][i]=resulF[f1][i]/resulF[f2][i];
			}else if(strcmp(op,"^")==0){
				for(i=0;i<tam;i++)
					resulF[f1][i]=pow(resulF[f1][i],resulF[f2][i]);
			}	
		}
	}else{
		if(strcmp(exp2.tipo,"D")!=0){
			calcFuncRight(op,atoi(exp1.tipo),exp1.value);
		}else{
			int i;
			if(strcmp(op,"+")==0){
				for(i=0;i<tam;i++)
					resulF[0][i]=exp1.value+exp2.value;
			}else if(strcmp(op,"-")==0){
				for(i=0;i<tam;i++)
					resulF[0][i]=exp1.value-exp2.value;
			}else if(strcmp(op,"*")==0){
				for(i=0;i<tam;i++)
					resulF[0][i]=exp1.value*exp2.value;
			}else if(strcmp(op,"/")==0){
				for(i=0;i<tam;i++)
					resulF[0][i]=exp1.value/exp2.value;
			}else if(strcmp(op,"^")==0){
				for(i=0;i<tam;i++)
					resulF[0][i]=pow(exp1.value,exp2.value);
			}	
		}
	}
}

void calcFuncLeft(char* op,int f,double value){
	int i;
	if(strcmp(op,"+")==0){
		for(i=0;i<tam;i++)
			resulF[f][i]=resulF[f][i]+value;
	}else if(strcmp(op,"-")==0){
		for(i=0;i<tam;i++)
			resulF[f][i]=resulF[f][i]-value;
	}else if(strcmp(op,"*")==0){
		for(i=0;i<tam;i++)
			resulF[f][i]=resulF[f][i]*value;
	}else if(strcmp(op,"/")==0){
		for(i=0;i<tam;i++)
			resulF[f][i]=resulF[f][i]/value;
	}else if(strcmp(op,"^")==0){
		for(i=0;i<tam;i++)
			resulF[f][i]=pow(resulF[f][i],value);
	}	
}

void calcFuncRight(char* op,int f,double value){
	int i;
	if(strcmp(op,"+")==0){
		for(i=0;i<tam;i++)
			resulF[f][i]=value+resulF[f][i];
	}else if(strcmp(op,"-")==0){
		for(i=0;i<tam;i++)
			resulF[f][i]=value-resulF[f][i];
	}else if(strcmp(op,"*")==0){
		for(i=0;i<tam;i++)
			resulF[f][i]=value*resulF[f][i];
	}else if(strcmp(op,"/")==0){
		for(i=0;i<tam;i++)
			resulF[f][i]=value/resulF[f][i];
	}else if(strcmp(op,"^")==0){
		for(i=0;i<tam;i++)
			resulF[f][i]=pow(value,resulF[f][i]);
	}	
}

void calcFunc(char* op,int f){
	int i;
	if(strcmp(op,"SEN")==0){
		for(i=0;i<tam;i++)
			resulF[f][i]=sin(resulF[f][i]);
	}else if(strcmp(op,"COS")==0){
		for(i=0;i<tam;i++)
			resulF[f][i]=cos(resulF[f][i]);
	}else if(strcmp(op,"TAN")==0){
		for(i=0;i<tam;i++)
			resulF[f][i]=tan(resulF[f][i]);
	}else if(strcmp(op,"ABS")==0){
		for(i=0;i<tam;i++)
			resulF[f][i]=abs(resulF[f][i]);
	}
}

void configs(){
	printf("\n");
	printf("h_view_lo: %.6lf\n",h_view_lo);
	printf("h_view_hi: %.6lf\n",h_view_hi);
	printf("v_view_lo: %.6lf\n",v_view_lo);
	printf("v_view_hi: %.6lf\n",v_view_hi);
	printf("integral_steps: %d\n\n",integral_steps);
	printf("Draw Axis: %s.\n",draw_axis?"ON":"OFF");
	printf("Connect Dots: %s.\n",connect_dots?"ON":"OFF");
	printf("\n");
}

void integrate(){
	double soma=0;
	double delta=((lSup-lInf)/integral_steps);
	int i;
	for(i=0;i<tam;i++){
		soma+=resulF[0][i];
	}
	printf("\n%.6lf\n\n",soma*delta);

}

double min(){
	double minF = resulF[f][0];
	int i;
	for(i=1;i<80;i++)
		if(resulF[f][i]<minF) minF=resulF[f][i];
	return minF;
}

double max(){
	double minF = resulF[f][0];
	int i;
	for(i=1;i<80;i++)
		if(resulF[f][i]>minF) minF=resulF[f][i];
	return minF;
}

void plot(){
	preparaTela();
	int i,j;
	printf("\n");
	for(i=0;i<25;i++){
		for(j=0;j<80;j++)
			printf("%c",tela[i][j]);
		printf("\n");
	}
	printf("\n");
}

void preparaTela(){
	int i,j;
	double v_view[25];
	double dif = (v_view_hi-v_view_lo)/25;
	double som=v_view_lo;
	for(i=0;i<25;i++){
		v_view[i]=som;
		som+=dif;
		for(j=0;j<80;j++){
			if(draw_axis && j==40) tela[i][j]='|';
			else if(draw_axis && i==12) tela[i][j]='-';
			else tela[i][j]=' ';
		}
	}
	int k=0;
	for(i=24;i>=0;i--){
		for(j=0;j<80;j++){
			if(resulF[0][j]>=v_view[i] && resulF[0][j]<=v_view[i+1])
				tela[k][j]='*';
		}
		k++;
	}
	/*double minF=min(resulF,80);
	double maxF=max(resulF,80);
	double norm;
	int k=0;
	for(j=79;j>=0;j--){
		double v= resulF[f][k];
		k++;
		norm=(v-minF)/(maxF-minF);
		norm=(norm*25);
		int indice = (int) norm;
		tela[indice][j]='*';
	}*/

}


void resetConfigs(){
	h_view_lo = -6.500000;
	h_view_hi = 6.500000;
	v_view_lo= -3.500000;
	v_view_hi= 3.500000;
	integral_steps= 1000;
	draw_axis=true;
	connect_dots=false;
}

void ajustaMatrix(){
	linha=auxLinha;
	coluna+=1;
	int i=0,j=0,i1=0,j1=0;

	for(i=0;i<linha;i++){
		for(j=coluna-1;j>=0;j--){
			matrix[i1][j1]=aux[i][j];
			aux[i][j]=0;
			j1++;
		}
		j1=0;
		i1++;
	}
	auxLinha=0;
	auxColuna=0;
}

void showMatrix(){
	int i=0,j=0,k=coluna;
	char espaco[400] = "";
	printf("\n");
	while(k>0){
		strcat(espaco,"            \t\t");
		k--;
	}
	printf("+-\t\t%s-+\n",espaco);
	for(i=0;i<linha;i++){
		printf("|\t\t");
		for(j=0;j<coluna;j++){
			printf("%e\t\t",matrix[i][j]);
		}
		printf(" |\n");
	}	
	printf("+-\t\t%s-+\n\n",espaco);

}

void solveDeterminant(){
	// Encontrando a determinante
	int fdr = coluna,i=0,j=0,k=0;
	double matrixDet[10][10];
	for(i=0;i<linha;i++){
		for(j=0;j<coluna;j++){
			matrixDet[i][j]=matrix[i][j];
		}
	}

    float mult;
    float deter=1;
    for(i=0;i<fdr;i++){
		for(j=0;j<fdr;j++){
			if(matrixDet[i][i]==0)
				mult=0;
            else mult=matrixDet[j][i]/matrixDet[i][i];
            for(k=0;k<fdr;k++){
                if(i==j) break;
                matrixDet[j][k]=matrixDet[j][k]-matrixDet[i][k]*mult;
            }
        }
    }
    for(i=0;i<fdr;i++){
        deter=deter*matrixDet[i][i];
    }
	printf("\n%lf\n\n",deter);
}

void about(){
	printf("\n");
	printf("+--------------------------------------------------+\n");
	printf("|                                                  |\n");
	printf("|   201800560119 - João Alex de Oliveira Bergamo   |\n");
	printf("|                                                  |\n");
	printf("+--------------------------------------------------+\n");
	printf("\n");
}

// erro
void yyerror(char *s){
	printf("Erro de sintaxe: %s\n", yytext);
}


int main(int argc, char **argv){
    printf(">");
	yyparse();
	
    return 0;
}