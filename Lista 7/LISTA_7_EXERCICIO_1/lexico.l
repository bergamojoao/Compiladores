/* Nao usar a biblioteca do flex*/
%option noyywrap

%{
	int pula=0;
%}

%%

"+"        {if(pula!=0){printf("\n");}printf("+");pula++;}
"-"        {if(pula!=0){printf("\n");}printf("-");pula++;}
[a-zA-Z][a-zA-Z0-9]* {if(pula!=0){printf("\n");}printf("%s",yytext);pula++;}
[0-9]+"e"([0-9]|"+"|"-")[0-9]+	{if(pula!=0){printf("\n");}printf("%s",yytext);pula++;}
[0-9]+	{if(pula!=0){printf("\n");}printf("%s",yytext);pula++;}
[\n]       {continue;}
.          {if(pula!=0){printf("\n");}printf("ERRO");pula++;}

%%

int main(int argc, char **argv)
{
	yylex();
	return 0;
}
