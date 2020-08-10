/* Nao usar a biblioteca do flex*/
%option noyywrap

%{
	int pula=0;
%}

%%

"if"	{if(pula!=0){printf("\n");}printf("%s IF",yytext);pula++;}

[a-z][a-z0-9]* {if(pula!=0){printf("\n");}printf("%s ID",yytext);pula++;}

"--"[a-z]*[\n]	{
	int i=0;
	if(pula!=0){printf("\n");}
	for(i=0;i<strlen(yytext);i++){
		if(yytext[i]!='\n')
			printf("%c",yytext[i]);
	}
	printf(" comment");
	pula++;
}

"."[0-9]+	{if(pula!=0){printf("\n");}printf("%s REAL",yytext);pula++;}

[0-9]+"."[0-9]*	{if(pula!=0){printf("\n");}printf("%s REAL",yytext);pula++;}

[0-9]+	{if(pula!=0){printf("\n");}printf("%s NUM",yytext);pula++;}

" "		{if(pula!=0){printf("\n");}printf("white space");pula++;}

[\n]	{continue;}

.		{if(pula!=0){printf("\n");}printf("%s error",yytext);pula++;}

%%

int main(int argc, char **argv)
{
	yylex();
	return 0;
}
