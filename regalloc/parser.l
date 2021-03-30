%option noyywrap

%x COMENTARIO

%{
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
extern int yylval;
#include <sintatico.tab.h>


%}

%%

"Grafo"     {return(GRAFO);}
[0-9]+      {yylval=atoi(yytext);return(INTEGER);}
":"         {return(DOIS_PONTOS);}
"K"         {return(K);}
"="         {return(EQUALS);}
"-->"       {return(FLECHA);}
\n          { return EOL; }
[ \t]       { /* espaço em branco/tabulação */  }
.           { printf("ERRO LEXICO\n");exit(0); }

%%    