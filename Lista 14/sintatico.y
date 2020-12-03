%{


#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

extern int yylex();
extern void yyrestart(FILE *f);
extern char* yytext;
extern int cont;
void yyerror(char *s);


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
%token ERRO_LEXICO;

%start S

%%

S:  EXP EOL {printf("EXPRESSAO CORRETA\n");} S
	| ERRO_LEXICO {printf("Caractere(s) invalido(s) -> [#,@,$,!,=]\n");while(yylex()!=EOL);} S
	| error {};

NUM_FORM: ADD NUM
	| SUB NUM
	| NUM

	
EXP: NUM_FORM 
	| VAR 
	| EXP ADD EXP 
	| EXP SUB EXP 
	| EXP MUL EXP 
	| EXP DIV EXP 
	| EXP POW EXP 
	| SEN ABRE_PARENTESES EXP FECHA_PARENTESES 
	| COS ABRE_PARENTESES EXP FECHA_PARENTESES 
	| TAN ABRE_PARENTESES EXP FECHA_PARENTESES 
	| ABS ABRE_PARENTESES EXP FECHA_PARENTESES 
	| ABRE_PARENTESES EXP FECHA_PARENTESES



%%


// erro
void yyerror(char *s){
	printf("Erro de sintaxe na coluna [%d]: %s\n",cont, strcmp(yytext,"\n") == 0 ? " ":yytext);
	while(yylex()!=EOL);
	yyparse();
}


int main(int argc, char **argv){
	yyparse();
    return 0;
}