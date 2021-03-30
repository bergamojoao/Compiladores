%{
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include"ListaDinamica.h"
#include"Grafo.h"
#include"Vertice.h"
#include"Alocacao.h"

#define size_str 100000

extern int yylex();
extern void yyrestart(FILE *f);
extern char* yytext;
void yyerror(char *s);

Grafo grafo;
Lista vertices;
Lista adjacentes;


%}

%token GRAFO
%token INTEGER
%token DOIS_PONTOS
%token K
%token EQUALS
%token FLECHA
%token EOL


%start S

%%

S: GRAFO INTEGER DOIS_PONTOS EOL K EQUALS INTEGER EOL chamada_grafos {grafo = criaGrafo($2, $7, vertices); };

chamada_grafos: INTEGER FLECHA chamada_grafos1 { Vertice v = criaVertice($1,adjacentes); adjacentes=NULL; vertices=inserir(vertices, v); }
	| ;

chamada_grafos1: 
	| INTEGER chamada_grafos1 { Vertice adjacente = criaVertice($1, NULL); adjacentes = inserir(adjacentes, adjacente); }
	| EOL chamada_grafos ;

%%

void yyerror(char *s){
	printf("Erro de Sintaxe: [%s]\n\n", strcmp(yytext,"\n") == 0 ? " ":yytext);
}


int main(int argc, char **argv){
	char str_espaco[size_str];
	int indice = 0;
	yyparse();
	alocacao(grafo);
}