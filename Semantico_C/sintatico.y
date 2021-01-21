%{

#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include"HashTable.h"
#include"Expression.h"

#define YYSTYPE void*
#define size_str 100000

extern int yylex();
extern char* yytext;

extern char STR_ERRO[size_str];
extern char STR_BACKUP[size_str];

extern int sintatico_aux;
extern int lexico_aux;
extern char v[size_str];
extern char v2[size_str];
extern int coluna;
extern int linha;

int tam;

int L = 0;

char str_token[size_str];

extern int nao_terminado;
extern int backupTamanho;

void yyerror(char *s);


%}

%token VOID
%token INT
%token CHAR
%token RETURN
%token BREAK
%token SWITCH
%token CASE
%token DEFAULT
%token DO
%token WHILE
%token FOR
%token IF
%token ELSE
%token TYPEDEF
%token STRUCT
%token PLUS
%token MINUS
%token MULTIPLY
%token DIV
%token REMAINDER
%token INC
%token DEC
%token BITWISE_AND
%token BITWISE_OR
%token BITWISE_NOT
%token BITWISE_XOR
%token NOT
%token LOGICAL_AND
%token LOGICAL_OR
%token EQUAL
%token NOT_EQUAL
%token LESS_THAN
%token GREATER_THAN
%token LESS_EQUAL
%token GREATER_EQUAL
%token R_SHIFT
%token L_SHIFT
%token ASSIGN
%token ADD_ASSIGN
%token MINUS_ASSIGN
%token SEMICOLON
%token COMMA
%token COLON
%token L_PAREN
%token R_PAREN
%token L_CURLY_BRACKET
%token R_CURLY_BRACKET
%token L_SQUARE_BRACKET
%token R_SQUARE_BRACKET
%token TERNARY_CONDITIONAL
%token NUMBER_SIGN
%token POINTER
%token PRINTF
%token SCANF
%token DEFINE
%token EXIT
%token NUM_OCTAL
%token NUM_INTEGER
%token NUM_HEXA
%token CHARACTER
%token STRING
%token IDENTIFIER

%start S

%%

S: programa { printf("SUCCESSFUL COMPILATION."); return 0;} ;
	
programa: declaracoes programa1
	| funcao programa1 ;

programa1: programa
	| ;

declaracoes: NUMBER_SIGN DEFINE IDENTIFIER expressao
	| declaracao_variaveis
	| declaracao_prototipos ;

funcao: tipo funcao1 ;

funcao1: MULTIPLY funcao1
	| IDENTIFIER parametros L_CURLY_BRACKET funcao2 ;

funcao2: declaracao_variaveis funcao2
	| comandos R_CURLY_BRACKET ;

declaracao_variaveis: tipo declaracao_variaveis1 ;

declaracao_variaveis1: MULTIPLY declaracao_variaveis1
	| IDENTIFIER declaracao_variaveis2 ;

declaracao_variaveis2:L_SQUARE_BRACKET expressao R_SQUARE_BRACKET declaracao_variaveis2
	| ASSIGN expressao_de_atribuicao declaracao_variaveis3
	| declaracao_variaveis3 ;

declaracao_variaveis3: COMMA declaracao_variaveis1
	| SEMICOLON ;

declaracao_prototipos: tipo declaracao_prototipos1 ;

declaracao_prototipos1: MULTIPLY declaracao_prototipos1
	| IDENTIFIER parametros SEMICOLON ;

parametros: L_PAREN parametros1 ;

parametros1: R_PAREN
	| parametros2 ;

parametros2: tipo parametros3 ;

parametros3: MULTIPLY parametros3
	| IDENTIFIER parametros4 ;

parametros4: L_SQUARE_BRACKET expressao R_SQUARE_BRACKET parametros4
	| COMMA parametros2
	| R_PAREN ;

tipo: INT
	| CHAR
	| VOID ;

comandos: lista_de_comandos comandos1 ;

comandos1: comandos
	| ;

bloco: L_CURLY_BRACKET comandos R_CURLY_BRACKET ;

lista_de_comandos: DO bloco WHILE L_PAREN expressao R_PAREN SEMICOLON
	| IF L_PAREN expressao R_PAREN bloco lista_de_comandos1
	| WHILE L_PAREN expressao R_PAREN bloco
	| FOR L_PAREN lista_de_comandos2
	| PRINTF L_PAREN STRING lista_de_comandos6
	| SCANF L_PAREN STRING COMMA BITWISE_AND IDENTIFIER R_PAREN SEMICOLON
	| EXIT L_PAREN expressao R_PAREN SEMICOLON
	| RETURN lista_de_comandos7
	| expressao SEMICOLON
	| SEMICOLON
	| bloco ;

lista_de_comandos1: ELSE bloco
	| ;
	
lista_de_comandos2: expressao SEMICOLON lista_de_comandos3
	| SEMICOLON lista_de_comandos3 ;

lista_de_comandos3: expressao SEMICOLON lista_de_comandos4
	| SEMICOLON lista_de_comandos4 ;

lista_de_comandos4: expressao lista_de_comandos5
	| lista_de_comandos5 ;

lista_de_comandos5: R_PAREN bloco ;

lista_de_comandos6: COMMA expressao R_PAREN SEMICOLON
	| R_PAREN SEMICOLON ;

lista_de_comandos7: expressao SEMICOLON
	| SEMICOLON ;

expressao: expressao_de_atribuicao expressao1 ;

expressao1: COMMA expressao_de_atribuicao expressao1
	| ;

expressao_de_atribuicao: expressao_condicional
	| expressao_unaria expressao_de_atribuicao1 ;

expressao_de_atribuicao1: ASSIGN expressao_de_atribuicao
	| ADD_ASSIGN expressao_de_atribuicao
	| MINUS_ASSIGN expressao_de_atribuicao ;

expressao_condicional: expressao_or_logico ternario ;

ternario: TERNARY_CONDITIONAL expressao COLON expressao_condicional
	| ;

expressao_or_logico: expressao_and_logico expressao_or_logico1 ;

expressao_or_logico1: LOGICAL_OR expressao_and_logico expressao_or_logico1
	| ;

expressao_and_logico: expressao_or expressao_and_logico1 ;

expressao_and_logico1: LOGICAL_AND expressao_or expressao_and_logico1
	| ;

expressao_or: expressao_xor expressao_or1 ;

expressao_or1: BITWISE_OR expressao_xor expressao_or1
	| ;

expressao_xor: expressao_and expressao_xor1 ;

expressao_xor1: BITWISE_XOR expressao_and expressao_xor1
	| ;

expressao_and: expressao_igualdade expressao_and1 ;

expressao_and1: BITWISE_AND expressao_igualdade expressao_and1
	| ;

expressao_igualdade: expressao_relacional expressao_igualdade1 ;

expressao_igualdade1: EQUAL expressao_relacional expressao_igualdade1
	| NOT_EQUAL expressao_relacional expressao_igualdade1
	| ;

expressao_relacional: expressao_shift expressao_relacional1 ;

expressao_relacional1: LESS_THAN expressao_shift expressao_relacional1
	| LESS_EQUAL expressao_shift expressao_relacional1
	| GREATER_THAN expressao_shift expressao_relacional1
	| GREATER_EQUAL expressao_shift expressao_relacional1
	| ;

expressao_shift: expressao_aditiva expressao_shift1 { $$ = $2 == NULL ? $1 : createExpression(OPERADOR, $1, $2); } ;

expressao_shift1: L_SHIFT expressao_aditiva expressao_shift1 { $$ = createExpression(OPERADOR, $2, $3); }
	| R_SHIFT expressao_aditiva expressao_shift1 { $$ = createExpression(OPERADOR, $2, $3); }
	| { $$ = NULL; } ;

expressao_aditiva: expressao_multiplicativa expressao_aditiva1 { $$ = $2 == NULL ? $1 : createExpression(OPERADOR, $1, $2); } ;

expressao_aditiva1: MINUS expressao_multiplicativa expressao_aditiva1 { $$ = createExpression(OPERADOR, $2, $3); }
	| PLUS expressao_multiplicativa expressao_aditiva1 { $$ = createExpression(OPERADOR, $2, $3); }
	| { $$ = NULL; } ;

expressao_multiplicativa: expressao_cast expressao_multiplicativa1 { $$ = $2 == NULL ? $1 : createExpression(OPERADOR, $1, $2); } ;

expressao_multiplicativa1: MULTIPLY expressao_cast expressao_multiplicativa1 { $$ = createExpression(OPERADOR, $2, $3); }
	| DIV expressao_cast expressao_multiplicativa1 { $$ = createExpression(OPERADOR, $2, $3); }
	| REMAINDER expressao_cast expressao_multiplicativa1 { $$ = createExpression(OPERADOR, $2, $3); }
	| { $$ = NULL; } ;


expressao_cast: expressao_unaria { $$ = $1; }
	| L_PAREN tipo expressao_cast1 ;

expressao_cast1: MULTIPLY expressao_cast1
	| R_PAREN expressao_cast ;


expressao_unaria: expressao_pos_fixa { $$ = $1; }
	| INC expressao_unaria
	| DEC expressao_unaria
	| BITWISE_AND expressao_cast
	| MULTIPLY expressao_cast
	| PLUS expressao_cast
	| MINUS expressao_cast
	| BITWISE_NOT expressao_cast
	| NOT expressao_cast ;


expressao_pos_fixa: expressao_primaria { $$ = $1; }
	| expressao_pos_fixa expressao_pos_fixa1 ;

expressao_pos_fixa1: L_SQUARE_BRACKET expressao R_SQUARE_BRACKET
	| INC
	| DEC
	| L_PAREN expressao_pos_fixa2 ;

expressao_pos_fixa2: R_PAREN
	| expressao_pos_fixa3 ;

expressao_pos_fixa3: expressao_de_atribuicao expressao_pos_fixa4 ;

expressao_pos_fixa4: COMMA expressao_pos_fixa3
	| R_PAREN ;

expressao_primaria: IDENTIFIER { $$ = createExpression(OPERANDO, NULL, NULL); }
	| numero { $$ = $1; }
	| CHARACTER { $$ = createExpression(OPERANDO, NULL, NULL); }
	| STRING { $$ = createExpression(OPERANDO, NULL, NULL); }
	| L_PAREN expressao R_PAREN { $$ = $2; }
;

numero: NUM_INTEGER { $$ = createExpression(OPERANDO, NULL, NULL); }
	| NUM_HEXA { $$ = createExpression(OPERANDO, NULL, NULL); }
	| NUM_OCTAL { $$ = createExpression(OPERANDO, NULL, NULL); } 
;


%%

// erro
void yyerror(char *s)
{   
	if(sintatico_aux == 0){
		if(strlen(STR_ERRO)==0){
			tam = backupTamanho+1;
			L = linha;
			nao_terminado=1;
			sintatico_aux=1;
			strcpy(str_token, STR_BACKUP);
		}else{
			tam = coluna - (strlen(STR_ERRO)-1);
			L = linha;
			strcpy(str_token, STR_ERRO);
			sintatico_aux = 1;
		}
	}
}

int main(int argc, char **argv)
{
	char str_espaco[size_str];
	int indice = 0;
	yyparse();
	while(yylex());
	while(v2[indice] != '\0'){

		if(v2[indice] == '\n')
			break;

		str_espaco[indice] = v2[indice];
		indice++;
	}
	str_espaco[indice] = '\0';

	if(sintatico_aux == 1){
		if(strlen(str_espaco)==0){
			tam = backupTamanho+1;
			L = linha;
			nao_terminado=1;
			sintatico_aux=1;
			strcpy(str_token, STR_BACKUP);
			printf("error:syntax:%d:%d: expected declaration or statement at end of input\n%s\n%*s",L,tam,str_token,tam, "^");
		}else{
			printf("error:syntax:%d:%d: %s\n%s\n%*s",L,tam,str_token,str_espaco,tam, "^");
		}
		
	}
}