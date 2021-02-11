%{
#define YYSTYPE void*
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include"HashTable.h"
#include"Expression.h"
#include"Command.h"
#include"Function.h"
#include"Symbol.h"
#include"Program.h"
#include"semantico.h"
#include"ListaDinamica.h"

#define size_str 100000

extern int yylex();
extern char* yytext;

extern char STR_ERRO[size_str];
extern char STR_BACKUP[size_str];
extern char AUX[size_str];

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

Program AST;
HashTable symbolTable, globalSymbolTable;
bool criaST = true;
char tipoVar[10];
Expression arraySize;

int OPERACAO;

Lista listaPar = NULL;

char funcTipo[10];

char funcaoMsg[180];

char returnMsg[180];

int ponteiros=0;

char erro[250] = "";

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

S: { AST = createProgram(); symbolTable = getGlobalSymbolTable(AST); globalSymbolTable = symbolTable; }
	programa { setFunctionList(AST, $2); semantico(AST); if(strlen(erro)>1){printf("erro%s",erro);exit(0);} printf("SUCCESSFUL COMPILATION."); return 0;} ;
	
programa: declaracoes programa1 { $$ = $2; }
	| funcao programa1  { setNextFunction($1, $2); $$ = $1; };

programa1: programa { $$ = $1; }
	| { $$ = NULL; } ;

declaracoes: NUMBER_SIGN DEFINE IDENTIFIER expressao {  Symbol s = createVar(CONSTANTE, "int");
														setSymbolName(s, getSymbolName($3));
														setSymbolLinha(s, getSymbolLinha($3));
														setSymbolColuna(s, getSymbolColuna($3));
														setExpConstante(s, $4);
														verificaVariaveisIguais(symbolTable, globalSymbolTable, s, STR_BACKUP, erro);
														if(strlen(erro)<1) insertHashTable(symbolTable, s);
									   				}
	| declaracao_variaveis
	| declaracao_prototipos ;

funcao: tipo funcao1 { setPonteiroFunc($2, ponteiros);
					   ponteiros=0; setFunctionType($2, getSymbolName($1)); 
					   setFunctionSymbolTable($2, symbolTable); symbolTable = globalSymbolTable; criaST=true; $$ = $2; } ;

funcao1: MULTIPLY funcao1 { ponteiros++; $$ = $2; }
	| IDENTIFIER parametros { strlen(STR_BACKUP)<3 ? strcpy(funcaoMsg, AUX) : strcpy(funcaoMsg, STR_BACKUP); } 
							L_CURLY_BRACKET funcao2 { setListaParametrosFunc($5, listaPar);
													  listaPar = NULL; 
													  setFunctionMsg($5, funcaoMsg);
													  setLinhaColunaFunc($5, getSymbolLinha($1), getSymbolColuna($1)); 
													  setFunctionName($5, getSymbolName($1)); $$ = $5; } ;

funcao2: declaracao_variaveis funcao2 { $$ = $2; }
	| comandos R_CURLY_BRACKET { Function f = createFunction($1); setReturnMsg(f, returnMsg); $$ = f; };

declaracao_variaveis: tipo declaracao_variaveis1 ;

declaracao_variaveis1: MULTIPLY declaracao_variaveis1
	| IDENTIFIER declaracao_variaveis2 { setSymbolName($2, getSymbolName($1));
										 setSymbolLinha($2, getSymbolLinha($1));
										 setSymbolColuna($2, getSymbolColuna($1));
										 setArraySize($2, arraySize);
										 arraySize=NULL;
										 verificaVariaveisIguais(symbolTable, globalSymbolTable, $2, STR_BACKUP, erro);
										 if(strlen(erro)<1) insertHashTable(symbolTable, $2);
									   } ;

declaracao_variaveis2:L_SQUARE_BRACKET expressao R_SQUARE_BRACKET declaracao_variaveis2 { arraySize = $2;  $$ = $4;}
	| ASSIGN expressao_de_atribuicao declaracao_variaveis3 { $$ = $3; }
	| declaracao_variaveis3 { $$ = $1; };

declaracao_variaveis3: COMMA declaracao_variaveis1 { if(criaST){symbolTable = criaHashTable(108, getSymbolName);criaST=false;} $$ = createVar(VARIAVEL, tipoVar); }
	| SEMICOLON  { if(criaST){symbolTable = criaHashTable(108, getSymbolName);criaST=false;} $$ = createVar(VARIAVEL, tipoVar); };

declaracao_prototipos: tipo declaracao_prototipos1 {
											setSymbolType($2, getSymbolName($1));
											verificaVariaveisIguais(symbolTable, globalSymbolTable, $2, STR_BACKUP, erro);
											if(strlen(erro)<1)insertHashTable(symbolTable, $2);
};

declaracao_prototipos1: MULTIPLY declaracao_prototipos1
	| IDENTIFIER parametros SEMICOLON { Symbol s = createVar(PROTOTIPO, "");
										setSymbolName(s, getSymbolName($1));
										setListaParametros(s, listaPar);
										listaPar = NULL;	
										$$ = s;
									} ;

parametros: L_PAREN parametros1 ;

parametros1: R_PAREN
	| parametros2 ;

parametros2: tipo parametros3 { setSymbolType($2, getSymbolName($1)); listaPar = inserir(listaPar, $2); } ;

parametros3: MULTIPLY parametros3
	| IDENTIFIER parametros4 { $$ = $1; };

parametros4: L_SQUARE_BRACKET expressao R_SQUARE_BRACKET parametros4 { arraySize = $2;  $$ = $4;}
	| COMMA parametros2 { $$ = $2; }
	| R_PAREN ;

tipo: INT { strcpy(tipoVar,"int"); $$ = $1; }
	| CHAR { strcpy(tipoVar,"char"); $$ = $1; }
	| VOID { strcpy(tipoVar,"void"); $$ = $1; } ;

comandos: lista_de_comandos comandos1 { setNextCommand($1, $2); $$ = $1; } ;

comandos1: comandos { $$ = $1; }
	| { $$ = NULL; } ;

bloco: L_CURLY_BRACKET comandos R_CURLY_BRACKET { $$ = $2; } ;

lista_de_comandos: DO bloco WHILE L_PAREN expressao R_PAREN SEMICOLON
	| IF L_PAREN expressao R_PAREN bloco lista_de_comandos1 { $$ = createCommand(IF_CMD, $3, $5, $6, NULL, NULL); }
	| WHILE L_PAREN expressao R_PAREN bloco { $$ = createCommand(WHILE_CMD, $3, NULL, NULL, $5, NULL); }
	| FOR L_PAREN lista_de_comandos2 { $$ = $3; }
	| PRINTF L_PAREN STRING lista_de_comandos6 { $$ = $4; }
	| SCANF L_PAREN STRING COMMA BITWISE_AND IDENTIFIER R_PAREN SEMICOLON { $$ = NULL; }
	| EXIT L_PAREN expressao R_PAREN SEMICOLON { $$ = createCommand(EXPRESSAO, $1, NULL, NULL, NULL, NULL); }
	| RETURN lista_de_comandos7 { $$ = createReturn($2, getSymbolLinha($1), getSymbolColuna($1), STR_BACKUP); }
	| expressao SEMICOLON { setExpText($1, STR_BACKUP);  $$ = createCommand(EXPRESSAO, $1, NULL, NULL, NULL, NULL); }
	| SEMICOLON { $$ = NULL; }
	| bloco { $$ = $1; } ;

lista_de_comandos1: ELSE bloco { $$ = $2; }
	| { $$ = NULL; };
	
lista_de_comandos2: expressao SEMICOLON lista_de_comandos3 { setCmdExp1($3, $1); $$ = $3; }
	| SEMICOLON lista_de_comandos3 { $$ = $2; } ;

lista_de_comandos3: expressao SEMICOLON lista_de_comandos4 { setCmdExp2($3, $1); $$ = $3; }
	| SEMICOLON lista_de_comandos4 { $$ = $2; } ;

lista_de_comandos4: expressao lista_de_comandos5 { $$ = createCmdFor($1, $2); }
	| lista_de_comandos5 { $$ = createCmdFor(NULL, $1); } ;

lista_de_comandos5: R_PAREN bloco { $$ = $2; };

lista_de_comandos6: COMMA expressao R_PAREN SEMICOLON { $$ = createCommand(EXPRESSAO, $2, NULL, NULL, NULL, NULL); }
	| R_PAREN SEMICOLON { $$ = NULL; } ;

lista_de_comandos7: expressao SEMICOLON { $$ = $1; }
	| SEMICOLON { $$ = NULL; } ;

expressao: expressao_de_atribuicao expressao1 { $$ = $2 == NULL ? $1 : createExpression(OPERADOR, $1, $2); } ;

expressao1: COMMA expressao_de_atribuicao expressao1 { $$ = $2 == NULL ? $1 : createExpression(OPERADOR, $1, $2); }
	| { $$ = NULL; } ;

expressao_de_atribuicao: expressao_condicional { $$ = $1; }
	| expressao_unaria expressao_de_atribuicao1 { setLeftChild($2, $1); $$ = $2; } ;

expressao_de_atribuicao1: ASSIGN expressao_de_atribuicao { Expression exp = createExpression(EXP_ASSIGN, NULL, $2);
															setExpLinha(exp, getSymbolLinha($1));
															setExpColuna(exp, getSymbolColuna($1));
															setExpVarName(exp, getSymbolName($1));
															$$ = exp;	
														}
	| ADD_ASSIGN expressao_de_atribuicao { $$ = createExpression(OPERADOR, NULL, $2); }
	| MINUS_ASSIGN expressao_de_atribuicao { $$ = createExpression(OPERADOR, NULL, $2); } ;

expressao_condicional: expressao_or_logico ternario { $$ = $2 == NULL ? $1 : createExpression(OPERADOR, $1, $2); } ;

ternario: TERNARY_CONDITIONAL expressao COLON expressao_condicional { $$ = createExpression(OPERADOR, $2, $4); }
	| { $$ = NULL; } ;

expressao_or_logico: expressao_and_logico expressao_or_logico1 { $$ = $2 == NULL ? $1 : createExpression(OPERADOR, $1, $2); } ;

expressao_or_logico1: LOGICAL_OR expressao_and_logico expressao_or_logico1 { $$ = $3 == NULL ? $2 : createExpression(OPERADOR, $2, $3); }
	| { $$ = NULL; } ;

expressao_and_logico: expressao_or expressao_and_logico1 { $$ = $2 == NULL ? $1 : createExpression(OPERADOR, $1, $2); } ;

expressao_and_logico1: LOGICAL_AND expressao_or expressao_and_logico1 { $$ = $3 == NULL ? $2 : createExpression(OPERADOR, $2, $3); }
	| { $$ = NULL; } ;

expressao_or: expressao_xor expressao_or1 { $$ = $2 == NULL ? $1 : createExpression(OPERADOR, $1, $2); } ;

expressao_or1: BITWISE_OR expressao_xor expressao_or1 { $$ = $3 == NULL ? $2 : createExpression(OPERADOR, $2, $3); }
	| { $$ = NULL; } ;

expressao_xor: expressao_and expressao_xor1 { $$ = $2 == NULL ? $1 : createExpression(OPERADOR, $1, $2); } ;

expressao_xor1: BITWISE_XOR expressao_and expressao_xor1 { $$ = $3 == NULL ? $2 : createExpression(OPERADOR, $2, $3); }
	|  { $$ = NULL; } ;

expressao_and: expressao_igualdade expressao_and1 { $$ = $2 == NULL ? $1 : createExpression(OPERADOR, $1, $2); } ;

expressao_and1: BITWISE_AND expressao_igualdade expressao_and1 { $$ = $3 == NULL ? $2 : createExpression(OPERADOR, $2, $3); }
	| { $$ = NULL; } ;

expressao_igualdade: expressao_relacional expressao_igualdade1 { $$ = $2 == NULL ? $1 : createExpression(OPERADOR, $1, $2); } ;

expressao_igualdade1: EQUAL expressao_relacional expressao_igualdade1 { $$ = $3 == NULL ? $2 : createExpression(OPERADOR, $2, $3); }
	| NOT_EQUAL expressao_relacional expressao_igualdade1 { $$ = $3 == NULL ? $2 : createExpression(OPERADOR, $2, $3); }
	| { $$ = NULL; } ;

expressao_relacional: expressao_shift expressao_relacional1 { $$ = $2 == NULL ? $1 : createExpression(OPERADOR, $1, $2); } ;

expressao_relacional1: LESS_THAN expressao_shift expressao_relacional1 { $$ = $3 == NULL ? $2 : createExpression(OPERADOR, $2, $3); }
	| LESS_EQUAL expressao_shift expressao_relacional1 { $$ = $3 == NULL ? $2 : createExpression(OPERADOR, $2, $3); }
	| GREATER_THAN expressao_shift expressao_relacional1 { $$ = $3 == NULL ? $2 : createExpression(OPERADOR, $2, $3); }
	| GREATER_EQUAL expressao_shift expressao_relacional1 { $$ = $3 == NULL ? $2 : createExpression(OPERADOR, $2, $3); }
	| { $$ = NULL; } ;

expressao_shift: expressao_aditiva expressao_shift1 { $$ = $2 == NULL ? $1 : createExpression(OPERADOR, $1, $2); } ;

expressao_shift1: L_SHIFT expressao_aditiva expressao_shift1 { $$ = $3 == NULL ? $2 : createExpression(OPERADOR, $2, $3); }
	| R_SHIFT expressao_aditiva expressao_shift1 { $$ = $3 == NULL ? $2 : createExpression(OPERADOR, $2, $3); }
	| { $$ = NULL; } ;

expressao_aditiva: expressao_multiplicativa expressao_aditiva1 { $$ = $2 == NULL ? $1 : createExpression(OPERACAO, $1, $2); } ;

expressao_aditiva1: MINUS expressao_multiplicativa expressao_aditiva1 { OPERACAO = OPERADOR_SUB; $$ = $3 == NULL ? $2 : createExpression(OPERADOR_SUB, $2, $3); }
	| PLUS expressao_multiplicativa expressao_aditiva1 { OPERACAO = OPERADOR_PLUS; $$ = $3 == NULL ? $2 : createExpression(OPERADOR_PLUS, $2, $3); }
	| { $$ = NULL; } ;

expressao_multiplicativa: expressao_cast expressao_multiplicativa1 { $$ = $2 == NULL ? $1 : createExpression(OPERACAO, $1, $2); } ;

expressao_multiplicativa1: MULTIPLY expressao_cast expressao_multiplicativa1 { OPERACAO = OPERADOR_MULT; $$ = $3 == NULL ? $2 : createExpression(OPERADOR_MULT, $2, $3); }
	| DIV expressao_cast expressao_multiplicativa1 { OPERACAO = OPERADOR_DIV; $$ = $3 == NULL ? $2 : createExpression(OPERADOR_DIV, $2, $3); }
	| REMAINDER expressao_cast expressao_multiplicativa1 { $$ = $3 == NULL ? $2 : createExpression(OPERADOR, $2, $3); }
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
	| expressao_pos_fixa expressao_pos_fixa1 { setLeftChild($1, $2); $$ = $1; } ;

expressao_pos_fixa1: L_SQUARE_BRACKET expressao R_SQUARE_BRACKET
	| INC { Expression exp = createExpression(EXP_INC, NULL, NULL);
								 setExpLinha(exp, getSymbolLinha($1));
								 setExpColuna(exp, getSymbolColuna($1));
							   	 setExpVarName(exp, getSymbolName($1));
								 $$ = exp;	
		  }
	| DEC { Expression exp = createExpression(EXP_DEC, NULL, NULL);
								 setExpLinha(exp, getSymbolLinha($1));
								 setExpColuna(exp, getSymbolColuna($1));
							   	 setExpVarName(exp, getSymbolName($1));
								 $$ = exp;	
		  }
	| L_PAREN expressao_pos_fixa2 ;

expressao_pos_fixa2: R_PAREN
	| expressao_pos_fixa3 ;

expressao_pos_fixa3: expressao_de_atribuicao expressao_pos_fixa4 ;

expressao_pos_fixa4: COMMA expressao_pos_fixa3
	| R_PAREN ;

expressao_primaria: IDENTIFIER { Expression exp = createExpression(EXP_VARIAVEL, NULL, NULL);
								 setExpLinha(exp, getSymbolLinha($1));
								 setExpColuna(exp, getSymbolColuna($1));
							   	 setExpVarName(exp, getSymbolName($1));
								 $$ = exp;	
							   }
	| numero { $$ = $1; }
	| CHARACTER { $$ = createExpression(OPERANDO, NULL, NULL);}
	| STRING { $$ = createExpression(EXP_STRING, NULL, NULL); }
	| L_PAREN expressao R_PAREN { $$ = $2; }
;

numero: NUM_INTEGER { $$ = $1; }
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