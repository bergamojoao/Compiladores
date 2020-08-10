/* Nao usar a biblioteca do flex*/
%option noyywrap

%{
	int pula=0;
%}

%%

"aba"+ {if(pula!=0){printf("\n");}printf("(action 1)");pula++;}
"a""b"*"a" {if(pula!=0){printf("\n");}printf("(action 2)");pula++;}
"a"|"b" {if(pula!=0){printf("\n");}printf("(action 3)");pula++;}

%%

int main(int argc, char **argv)
{
	yylex();
	return 0;
}
