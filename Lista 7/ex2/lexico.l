/* Nao usar a biblioteca do flex*/
%option noyywrap

%%

"if"	{printf("%s IF\n",yytext);}

[a-z][a-z0-9]* {printf("%s ID\n",yytext);}

"--"[a-z]*[\n]	{
	int i=0;
	for(i=0;i<strlen(yytext);i++)
		if(yytext[i]!='\n')
			printf("%c",yytext[i]);
	printf(" comment\n");
}

"."[0-9]+	{printf("%s REAL\n",yytext);}

[0-9]+"."[0-9]*	{printf("%s REAL\n",yytext);}

[0-9]+	{printf("%s NUM\n",yytext);}

" "		{printf("white space\n");}

[\n]	{continue;}

.		{ printf("%s error\n",yytext);}

%%

int main(int argc, char **argv)
{
	yylex();
	return 0;
}
