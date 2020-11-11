%{
#define YYSTYPE double
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



void configs();
void resetConfigs();
void about();


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
	| SET H_VIEW NUM_FORM COLON NUM_FORM SEMI_COLON {h_view_lo=$3;h_view_hi=$5;}
	| SET V_VIEW NUM_FORM COLON NUM_FORM SEMI_COLON {v_view_lo=$3;v_view_hi=$5;}
	| SET AXIS ON {draw_axis=true;}
	| SET AXIS OFF {draw_axis=false;}
	| ABOUT SEMI_COLON {about();}
	| EXP {printf("%lf\n",$$);}
	| ;

NUM_FORM: ADD NUM {$$=$2;}
	| SUB NUM {$$=-$2;}
	| NUM {$$=$1;}
	
EXP: NUM_FORM
	| EXP ADD EXP {$$ = $1+$3;}
	| EXP SUB EXP {$$ = $1-$3;}
	| EXP MUL EXP {$$ = $1*$3;}
	| EXP DIV EXP {$$ = $1/$3;}
	| EXP POW EXP {$$ = pow($1,$3);}
	| SEN ABRE_PARENTESES EXP FECHA_PARENTESES {$$ = sin($3);}
	| COS ABRE_PARENTESES EXP FECHA_PARENTESES {$$ = cos($3);}
	| TAN ABRE_PARENTESES EXP FECHA_PARENTESES {$$ = tan($3);}
	| ABS ABRE_PARENTESES EXP FECHA_PARENTESES {$$ = abs($3);}
	| ABRE_PARENTESES EXP FECHA_PARENTESES {$$ = $2;}

%%

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