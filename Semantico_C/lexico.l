%option noyywrap

%x COMENTARIO

%{
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define YYSTYPE void*
extern YYSTYPE yylval;
#include <sintatico.tab.h>
#include"Symbol.h"
#define size_str 100000


char v[size_str];
char v2[size_str];


int sintatico_aux = 0;
int lexico_aux = 0;

int caracteres = 1;
int caracteres2 = 1;
int tokens = 0;
int linha = 1;
int linha2 = 0;
int coluna = 0;

int pula_linha = 0;
char STR_ERRO[size_str];
char STR_BACKUP[size_str];
int i=0;
char *str;

int nao_terminado = 0;
int backupTamanho=0;
int comentarioUmalinha = 0;


void save_token();

%}

%%

"void"     {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(VOID);}
"int"      {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(INT);}
"char"     {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(CHAR);}
"return"   {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(RETURN);}
"break"    {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(BREAK);}
"switch"   {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(SWITCH);}
"case"     {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(CASE);}
"default"  {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(DEFAULT);}
"do"       {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(DO);}
"while"    {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(WHILE);}
"for"      {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(FOR);}
"if"       {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(IF);}
"else"     {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(ELSE);}
"typedef"  {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(TYPEDEF);}
"struct"   {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(STRUCT);}
"+"        {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(PLUS);}
"-"        {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(MINUS);}
"*"        {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(MULTIPLY);}
"/"        {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(DIV);}
"%"        {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(REMAINDER);}
"++"       {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(INC);}
"--"       {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(DEC);}
"&"        {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(BITWISE_AND);}
"|"        {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(BITWISE_OR);}
"~"        {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(BITWISE_NOT);}
"^"        {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(BITWISE_XOR);}
"!"        {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(NOT);}
"&&"       {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(LOGICAL_AND);}
"||"       {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(LOGICAL_OR);}
"=="       {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(EQUAL);}
"!="       {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(NOT_EQUAL);}
"<"  	   {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(LESS_THAN);}
">"	       {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(GREATER_THAN);}
"<="       {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(LESS_EQUAL);}
">="       {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(GREATER_EQUAL);}
">>"       {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(R_SHIFT);}
"<<"       {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(L_SHIFT);}
"="        {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(ASSIGN);}
"+="       {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(ADD_ASSIGN);}
"-="       {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(MINUS_ASSIGN);}
";"        {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(SEMICOLON);}
","        {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(COMMA);}
":"        {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(COLON);}
"("        {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(L_PAREN);}
")"        {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(R_PAREN);}
"{"        {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(L_CURLY_BRACKET);}
"}"        {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(R_CURLY_BRACKET);}
"["        {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(L_SQUARE_BRACKET);}
"]"        {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(R_SQUARE_BRACKET);}
"?"        {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(TERNARY_CONDITIONAL);}
"#"        {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(NUMBER_SIGN);}
"->"       {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(POINTER);}
"printf"   {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(PRINTF);}
"scanf"    {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(SCANF);}
"define"   {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(DEFINE);}
"exit"     {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(EXIT);}


0[1-7][0-7]*        {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(NUM_OCTAL);}
[0-9]+              {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(NUM_INTEGER);}
0[Xx][0-9a-fA-F]+   {strcat(v, yytext);save_token();caracteres+=strlen(yytext);tokens++;return(NUM_HEXA);}

'[\\]?(.)'	        {strcat(v, yytext);save_token(); str = malloc(strlen(yytext)*sizeof(char));strcpy(str, yytext); i = 0;
                     while(str[i] != '\0'){str[i] = str[i+1]; i++;} str[i-2] = '\0';
			         caracteres+=strlen(yytext);tokens++;return(CHARACTER);
                    }

\"([^\\\"]|\\.)*\"	{strcat(v, yytext);save_token(); str = malloc(strlen(yytext)*sizeof(char)); strcpy(str, yytext); i = 0;
			         while(str[i] != '\0'){str[i] = str[i+1];i++;} str[i-2] = '\0';
			         caracteres+=strlen(yytext);tokens++;return(STRING);
                    }

[_a-zA-Z][_a-zA-Z0-9]*	{char* tokenName = (char*) malloc(strlen(yytext)+1);
                         strcpy(tokenName,yytext);
                         yylval=createSymbol(tokenName, "", VARIAVEL, 0, linha, caracteres);strcat(v, yytext);
                         save_token();caracteres+=strlen(yytext);tokens++;return(IDENTIFIER);
                        }

" "		        { strcat(v, yytext);save_token();caracteres+= strlen(yytext); }
"\t"            { strcat(v, yytext);save_token();caracteres+= strlen(yytext); }   
"//"(.)*"\n"	{ strcat(v, yytext);save_token();linha++; caracteres=1; yylineno++;}
"\n"		    { if(sintatico_aux == 1 && lexico_aux == 0){lexico_aux=1;strcpy(v2,v);} strcpy(v,"");save_token();linha++; caracteres=1; yylineno++;}


<INITIAL>{
     "/*"  {save_token();linha2 = linha; caracteres2 = caracteres; caracteres+=2; }  BEGIN(COMENTARIO);
}

<COMENTARIO>{
     <<EOF>>   { if(sintatico_aux == 0){printf("error:lexical:%d:%d: unterminated comment",linha2,caracteres2); pula_linha++;exit(0);}}BEGIN(INITIAL);
     "*/"      { save_token();caracteres+=2; } BEGIN(INITIAL);
     [^*\n]+   { save_token();caracteres+= strlen(yytext);}
     "*"       { save_token();caracteres+= strlen(yytext);}
     \n        save_token();yylineno++;linha++;
}

\/\/([^\n])* 			{ comentarioUmalinha=1;save_token();caracteres += strlen(yytext); }
.                       { if(sintatico_aux == 0){printf("error:lexical:%d:%d: %s",linha,caracteres,yytext); caracteres+= strlen(yytext); pula_linha++;exit(0);}}

%%    

void save_token(){

    int i=0;


	for (i = 0; yytext[i] != '\0'; i++){

		if(yytext[i] == '\n'){

        	strcpy(STR_ERRO,"");
            strcpy(STR_BACKUP,"");
            backupTamanho=0;
            coluna = 0;
        }
		else if(yytext[i] == '\t')
        	coluna += 8 - (coluna % 8);

		else{

        	strcpy(STR_ERRO,yytext);
            coluna++;
        }  
    }
    strcat(STR_BACKUP,STR_ERRO);
    if(comentarioUmalinha==1){
        comentarioUmalinha=0;
    }else{
        backupTamanho=(int)strlen(STR_BACKUP);
    }
    

}