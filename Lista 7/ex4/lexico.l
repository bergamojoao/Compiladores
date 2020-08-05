/* Nao usar a biblioteca do flex*/
%option noyywrap

%x COMMENT

%{
	int lines=1;
	int blankLines=0;
	int commentLines=0;
	int nbncLines=0;
	int semiColons=0;
	int directives=0;

	int aux=0;
%}

%%

";"						{semiColons++;aux++;}
"#include"|"#define"	{directives++;aux++;}
"//"(.)*("")			{commentLines++;aux++;}
"\n"					{lines++;if(aux==0){blankLines++;}else{nbncLines++;};aux=0;}

<INITIAL>{
    "/*"      			{commentLines++;aux++;}BEGIN(COMMENT);
}
<COMMENT>{
    <<EOF>>   			BEGIN(INITIAL);
    "*/"      			{aux++;}BEGIN(INITIAL);
	[^*\n]+   			{aux++;}
    "*"       			{aux++;}
    \n        			{lines++;commentLines++;if(aux==0){blankLines++;};aux=0;}

}

.						{aux++;continue;}
<<EOF>>					{if(aux==0){blankLines++;}else{nbncLines++;}return 0;}

%%

int main(int argc, char **argv)
{
	yylex();
	printf("diretivas: %d\n",directives);
	printf("comentarios: %d\n",commentLines);
	printf("linhas: %d\n",lines);
	printf("blanklines: %d\n",blankLines);
	printf("semiColons: %d\n",semiColons);
	printf("nbnc: %d\n",nbncLines);
	return 0;
}
