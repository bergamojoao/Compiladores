%option noyywrap

%{
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
typedef struct T{
	char tipo[10];
	double value;
    char f[10];
}Tipo;
#define YYSTYPE Tipo
extern YYSTYPE yylval;
#include <sintatico.tab.h>
extern int f;

%}

%%

"+"             { return ADD;}
"-"             { return SUB;}
"*"             { return MUL;}
"/"             { return DIV;}
"("             { return ABRE_PARENTESES;}
")"             { return FECHA_PARENTESES;}
"^"             { return POW;}
"sen"           { return SEN;}
"cos"           { return COS;}
"tan"           { return TAN;}
"abs"           { return ABS;}
"x"             { sprintf(yylval.tipo,"%d",f);f++;return VAR;}
"show"          { return SHOW;}
"reset"         { return RESET;}
"settings"      { return SETTINGS;}
"quit"          { exit(0);}
"set"           { return SET;}
"h_view"        { return H_VIEW;}
"v_view"        { return V_VIEW;}
"axis"          { return AXIS;}
"on"            { return ON;}
"off"           { return OFF;}
"plot"          { return PLOT;}
"integral_steps" { return INTEGRAL_STEPS;}
"integrate"     { return INTEGRATE;}
"matrix"        { return MATRIX;}
"solve"         { return SOLVE;}
"determinant"   { return DET;}
"linear_system" { return LINEAR_S;}
"about"         { return ABOUT;}
"["             { return L_SQUARE_BRACKET;}
"]"             { return R_SQUARE_BRACKET;}
":"             { return COLON;}
";"             { return SEMI_COLON;}
","             { return COMMA;}
[0-9]+"."[0-9]+ { yylval.value = atof(yytext);strcpy(yylval.tipo,"D");return NUM; }
[0-9]+          { yylval.value = atof(yytext);strcpy(yylval.tipo,"D");return NUM; }
\n              { return EOL; }
[ \t]           { /* espaço em branco/tabulação */  }
.               { printf("Simbolo Invalido -> %c\n", *yytext);}


%%  
