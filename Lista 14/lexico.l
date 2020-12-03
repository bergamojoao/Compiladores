%option noyywrap

%{
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <sintatico.tab.h>
int cont=0;

%}

%%
"+"             { cont++;return ADD;}
"-"             { cont++;return SUB;}
"*"             { cont++;return MUL;}
"/"             { cont++;return DIV;}
"("             { cont++;return ABRE_PARENTESES;}
")"             { cont++;return FECHA_PARENTESES;}
"^"             { cont++;return POW;}
"sen"           { cont++;return SEN;}
"cos"           { cont++;return COS;}
"tan"           { cont++;return TAN;}
"abs"           { cont++;return ABS;}
[a-z][a-z0-9]* {cont+=strlen(yytext);return VAR;}
[0-9]*"."[0-9]+ { cont+=strlen(yytext);return NUM; }
[0-9]+          { cont+=strlen(yytext);return NUM; }
\n              { cont=0;return EOL; }
[ \t]           { cont+=strlen(yytext); }
.               { return ERRO_LEXICO; }


%%  
