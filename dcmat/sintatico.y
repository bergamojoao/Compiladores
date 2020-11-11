%{
typedef struct T{
	char tipo[2];
	double value;
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
double resulF[80];




void configs();
void resetConfigs();
void about();
void montaFunc();
void calcFunc(char* op);
void verificaOp(Tipo exp1, Tipo exp2,char* op);
void calcFuncLeft(char* op,double value);
void calcFuncRight(char* op,double value);

%}

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
	| error {}

COMANDOS: SHOW SETTINGS SEMI_COLON {configs();}
	| RESET SETTINGS SEMI_COLON {resetConfigs();}
	| SET H_VIEW NUM_FORM COLON NUM_FORM SEMI_COLON {h_view_lo=$3.value;h_view_hi=$5.value;}
	| SET V_VIEW NUM_FORM COLON NUM_FORM SEMI_COLON {v_view_lo=$3.value;v_view_hi=$5.value;}
	| SET AXIS ON {draw_axis=true;}
	| SET AXIS OFF {draw_axis=false;}
	| ABOUT SEMI_COLON {about();}
	| EXP {printf("\nFunction in RPN format:\n\n%s\n\n",RPN);strcpy(RPN,"");}
	| ;

NUM_FORM: ADD NUM {$$.value=$2.value;strcpy($$.tipo,"D");}
	| SUB NUM {$$.value=-$2.value;strcpy($$.tipo,"D");}
	| NUM {$$.value=$1.value;strcpy($$.tipo,"D");}
	
EXP: NUM_FORM {char aux[100];sprintf(aux,"%.6lf ",$$.value);strcat(RPN,aux);}
	| VAR {strcat(RPN,"x ");function=true;montaFunc();$$=$1;}
	| EXP ADD EXP {strcat(RPN,"+ ");verificaOp($1,$3,"+");}
	| EXP SUB EXP {strcat(RPN,"- ");verificaOp($1,$3,"-");}
	| EXP MUL EXP {strcat(RPN,"* ");verificaOp($1,$3,"*");}
	| EXP DIV EXP {strcat(RPN,"/ ");verificaOp($1,$3,"/");}
	| EXP POW EXP {strcat(RPN,"^ ");verificaOp($1,$3,"^");}
	| SEN ABRE_PARENTESES EXP FECHA_PARENTESES {strcat(RPN,"SEN ");if(function){calcFunc("SEN");strcpy($$.tipo,"F");function=false;}else{$$.value=sin($3.value);}}
	| COS ABRE_PARENTESES EXP FECHA_PARENTESES {strcat(RPN,"COS ");if(function){calcFunc("COS");strcpy($$.tipo,"F");function=false;}else{$$.value=cos($3.value);}}
	| TAN ABRE_PARENTESES EXP FECHA_PARENTESES {strcat(RPN,"TAN ");if(function){calcFunc("TAN");strcpy($$.tipo,"F");function=false;}else{$$.value=tan($3.value);}}
	| ABS ABRE_PARENTESES EXP FECHA_PARENTESES {strcat(RPN,"ABS ");if(function){calcFunc("ABS");strcpy($$.tipo,"F");function=false;}else{$$.value=abs($3.value);}}
	| ABRE_PARENTESES EXP FECHA_PARENTESES;

%%

void montaFunc(){
	double espacX = (h_view_hi-h_view_lo)/80;
	int i;
	double attr = h_view_lo;
	for(i=0;i<80;i++){
		resulF[i]=attr;
		attr+=espacX;
	}
}

void verificaOp(Tipo exp1, Tipo exp2,char* op){
	if(strcmp(exp1.tipo,"F")==0){
		if(strcmp(exp2.tipo,"F")!=0){
			calcFuncLeft(op,exp2.value);
		}
	}else{
		if(strcmp(exp2.tipo,"F")==0){
			calcFuncRight(op,exp1.value);
		}
	}
}

void calcFuncLeft(char* op,double value){
	int i;
	if(strcmp(op,"+")==0){
		for(i=0;i<80;i++)
			resulF[i]=resulF[i]+value;
	}else if(strcmp(op,"-")==0){
		for(i=0;i<80;i++)
			resulF[i]=resulF[i]-value;
	}else if(strcmp(op,"*")==0){
		for(i=0;i<80;i++)
			resulF[i]=resulF[i]*value;
	}else if(strcmp(op,"/")==0){
		for(i=0;i<80;i++)
			resulF[i]=resulF[i]/value;
	}else if(strcmp(op,"^")==0){
		for(i=0;i<80;i++)
			resulF[i]=pow(resulF[i],value);
	}	

	for(i=0;i<80;i++)
			printf("%.6lf ",resulF[i]);
}

void calcFuncRight(char* op,double value){
	int i;
	if(strcmp(op,"+")==0){
		for(i=0;i<80;i++)
			resulF[i]=value+resulF[i];
	}else if(strcmp(op,"-")==0){
		for(i=0;i<80;i++)
			resulF[i]=value-resulF[i];
	}else if(strcmp(op,"*")==0){
		for(i=0;i<80;i++)
			resulF[i]=value*resulF[i];
	}else if(strcmp(op,"/")==0){
		for(i=0;i<80;i++)
			resulF[i]=value/resulF[i];
	}else if(strcmp(op,"^")==0){
		for(i=0;i<80;i++)
			resulF[i]=pow(value,resulF[i]);
	}	

	for(i=0;i<80;i++)
			printf("%.6lf ",resulF[i]);
}

void calcFunc(char* op){
	int i;
	if(strcmp(op,"SEN")==0){
		for(i=0;i<80;i++)
			resulF[i]=sin(resulF[i]);
	}else if(strcmp(op,"COS")==0){
		for(i=0;i<80;i++)
			resulF[i]=cos(resulF[i]);
	}else if(strcmp(op,"TAN")==0){
		for(i=0;i<80;i++)
			resulF[i]=tan(resulF[i]);
	}else if(strcmp(op,"ABS")==0){
		for(i=0;i<80;i++)
			resulF[i]=abs(resulF[i]);
	}

	for(i=0;i<80;i++)
			printf("%.6lf ",resulF[i]);
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

void resetConfigs(){
	h_view_lo = -6.500000;
	h_view_hi = 6.500000;
	v_view_lo= -3.500000;
	v_view_hi= 3.500000;
	integral_steps= 1000;
	draw_axis=true;
	connect_dots=false;
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